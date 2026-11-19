import subprocess as sp
from pathlib import Path
def run(*args): sp.run(args,check=True)

MSVCRT='_wfopen fgetc fclose ferror fwrite realloc free wprintf getwchar wcscmp wcslen exit __wgetmainargs'
KERNEL32='MoveFileExW CopyFileW DeleteFileW GetLastError GetFileAttributesW GetTempFileNameW ExitProcess CreateFileW GetFileInformationByHandle CloseHandle'
USER32='RegisterClassW CreateWindowExW DefWindowProcW ShowWindow GetMessageW TranslateMessage DispatchMessageW PostQuitMessage SendMessageW EnableWindow InvalidateRect BeginPaint EndPaint FillRect TrackMouseEvent DrawTextW SetWindowTextW GetWindowTextW GetWindowTextLengthW LoadCursorW SetCursor GetClientRect GetCursorPos ScreenToClient SetFocus UpdateWindow GetDC ReleaseDC SetProcessDPIAware AdjustWindowRect'
GDI32='CreateSolidBrush CreatePen SelectObject DeleteObject RoundRect CreateFontW SetTextColor SetBkColor SetBkMode GetDeviceCaps GetTextExtentPoint32W'
COMDLG32='GetOpenFileNameW'
SHELL32='DragAcceptFiles DragQueryFileW DragFinish'

CLI_DLLS={'msvcrt':MSVCRT,'KERNEL32':KERNEL32}
GUI_DLLS={'msvcrt':MSVCRT,'KERNEL32':KERNEL32+' GetModuleHandleW','user32':USER32,'gdi32':GDI32,'comdlg32':COMDLG32,'shell32':SHELL32}

def imports_asm(dlls):
 asm=['.section .idata,"aw"']
 def rva(s):return '.long '+s+'-0x400000'
 for d in dlls:asm.extend([rva('lookup'+d),'.long 0,0',rva('dll'+d),rva('table'+d)])
 asm.append('.zero 20')
 for d, names in dlls.items():
  asm.extend(['.balign 8','lookup'+d+':'])
  for n in names.split():asm.extend([rva('hint'+n),'.long 0'])
  asm.extend(['.quad 0','table'+d+':'])
  for n in names.split():asm.extend(['.global imp_'+n,'imp_'+n+':',rva('hint'+n),'.long 0'])
  asm.extend(['.quad 0','dll'+d+':','.asciz "'+d+'.dll"'])
  for n in names.split():asm.extend(['.balign 2','hint'+n+':','.short 0','.asciz "'+n+'"'])
 return '\n'.join(asm)+'\n'

GCCF=['-Os','-mno-red-zone','-fshort-wchar','-fno-stack-protector','-fno-asynchronous-unwind-tables','-fno-builtin','-fno-pie','-D_WIN32']

def patch_pe(exe,dlls):
 import struct
 b=bytearray(exe.read_bytes())
 pe=struct.unpack_from('<I',b,60)[0]
 opt=pe+24
 sections=opt+240
 idir_size=(len(dlls)+1)*20
 for i in range(3):
  h=sections+i*40
  if b[h:h+6]==b'.idata':
   struct.pack_into("<I",b,h+36,0xc0000040)
   size,rva=struct.unpack_from('<II',b,h+8)
   struct.pack_into('<II',b,opt+120,rva,idir_size)
 struct.pack_into('<HH',b,opt+40,6,0)
 struct.pack_into('<HH',b,opt+48,6,0)
 struct.pack_into('<H',b,pe+22,0x23)
 struct.pack_into('<QQQQ',b,opt+72,1048576,4096,1048576,4096)
 exe.write_bytes(b)

def build(dlls,sources,out,subsystem):
 Path('imports.s').write_text(imports_asm(dlls))
 run('as','imports.s','-o','imports.o')
 objs=[]
 for s in sources:
  o=s.replace('.c','.o')
  run('gcc',*GCCF,'-c',s,'-o',o)
  objs.append(o)
 Path('layout.ld').write_text("SECTIONS { . = 0x401000; .text : { *(.text*) } . = ALIGN(4096); .rdata : { *(.rodata*) } . = ALIGN(4096); .idata : { *(.idata) } /DISCARD/ : { *(.comment) *(.note*) } }")
 run('ld','-T','layout.ld','-e','start',*objs,'imports.o','-o','linked')
 run('objcopy','-O','pei-x86-64','--image-base','0x400000','--subsystem',subsystem,'--section-alignment','4096','--file-alignment','512','--strip-all','linked',out)
 patch_pe(Path(out),dlls)

build(CLI_DLLS,['uc_core.c','ConversorUC.c'],'ConversorUC.exe','console')
build(GUI_DLLS,['uc_core.c','ConversorUC_gui.c'],'ConversorUC_gui.exe','windows')
