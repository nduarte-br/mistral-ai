#include <stdio.h>
#include <wchar.h>
#include "uc_core.h"

#ifdef _WIN32
#define ABI __attribute__((ms_abi))
#define IMP(ret,name,args) extern ret (ABI *imp_##name) args

IMP(int,RegisterClassW,(const void*));
IMP(void*,CreateWindowExW,(unsigned,const wchar_t*,const wchar_t*,unsigned,int,int,int,int,void*,void*,void*,void*));
IMP(void*,DefWindowProcW,(void*,unsigned,void*,void*));
IMP(int,ShowWindow,(void*,int));
IMP(int,GetMessageW,(void*,void*,unsigned,unsigned));
IMP(int,TranslateMessage,(const void*));
IMP(long,DispatchMessageW,(const void*));
IMP(void,PostQuitMessage,(int));
IMP(long,SendMessageW,(void*,unsigned,void*,void*));
IMP(int,EnableWindow,(void*,int));
IMP(int,InvalidateRect,(void*,const void*,int));
IMP(void*,LoadCursorW,(void*,const wchar_t*));
IMP(void*,SetCursor,(void*));
IMP(int,GetClientRect,(void*,void*));
IMP(int,GetCursorPos,(void*));
IMP(int,ScreenToClient,(void*,void*));
IMP(int,TrackMouseEvent,(const void*));
IMP(int,DrawTextW,(void*,const wchar_t*,int,void*,unsigned));
IMP(int,SetWindowTextW,(void*,const wchar_t*));
IMP(int,GetWindowTextW,(void*,wchar_t*,int));
IMP(void*,SetFocus,(void*));
IMP(int,UpdateWindow,(void*));
IMP(int,FillRect,(void*,const void*,void*));
IMP(void*,GetDC,(void*));
IMP(int,ReleaseDC,(void*,void*));
IMP(int,SetProcessDPIAware,(void));
IMP(int,AdjustWindowRect,(void*,unsigned,int));
IMP(void*,BeginPaint,(void*,void*));
IMP(int,EndPaint,(void*,void*));

IMP(void*,CreateSolidBrush,(unsigned));
IMP(void*,CreatePen,(int,int,unsigned));
IMP(void*,SelectObject,(void*,void*));
IMP(int,DeleteObject,(void*));
IMP(int,RoundRect,(void*,int,int,int,int,int,int));
IMP(void*,CreateFontW,(int,int,int,int,int,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,unsigned,const wchar_t*));
IMP(int,SetTextColor,(void*,unsigned));
IMP(int,SetBkColor,(void*,unsigned));
IMP(int,SetBkMode,(void*,int));
IMP(int,GetDeviceCaps,(void*,int));
IMP(int,GetTextExtentPoint32W,(void*,const wchar_t*,int,void*));

IMP(int,GetOpenFileNameW,(void*));
IMP(void,DragAcceptFiles,(void*,int));
IMP(unsigned,DragQueryFileW,(void*,unsigned,wchar_t*,unsigned));
IMP(void,DragFinish,(void*));

IMP(FILE*,_wfopen,(const wchar_t*,const wchar_t*));
IMP(int,fclose,(FILE*));
IMP(size_t,wcslen,(const wchar_t*));
#define wcslen imp_wcslen
IMP(unsigned,GetTempFileNameW,(const wchar_t*,const wchar_t*,unsigned,wchar_t*));
IMP(int,MoveFileExW,(const wchar_t*,const wchar_t*,unsigned));
IMP(int,DeleteFileW,(const wchar_t*));
IMP(unsigned,GetFileAttributesW,(const wchar_t*));
IMP(void*,GetModuleHandleW,(const wchar_t*));
IMP(void,ExitProcess,(unsigned));
IMP(int,__wgetmainargs,(int*,wchar_t***,wchar_t***,int,void*));
IMP(void,exit,(int));
#define exit imp_exit

#define RegisterClassW imp_RegisterClassW
#define CreateWindowExW imp_CreateWindowExW
#define DefWindowProcW imp_DefWindowProcW
#define ShowWindow imp_ShowWindow
#define GetMessageW imp_GetMessageW
#define TranslateMessage imp_TranslateMessage
#define DispatchMessageW imp_DispatchMessageW
#define PostQuitMessage imp_PostQuitMessage
#define SendMessageW imp_SendMessageW
#define EnableWindow imp_EnableWindow
#define InvalidateRect imp_InvalidateRect
#define LoadCursorW imp_LoadCursorW
#define SetCursor imp_SetCursor
#define GetClientRect imp_GetClientRect
#define GetCursorPos imp_GetCursorPos
#define ScreenToClient imp_ScreenToClient
#define TrackMouseEvent imp_TrackMouseEvent
#define DrawTextW imp_DrawTextW
#define SetWindowTextW imp_SetWindowTextW
#define GetWindowTextW imp_GetWindowTextW
#define SetFocus imp_SetFocus
#define UpdateWindow imp_UpdateWindow
#define FillRect imp_FillRect
#define GetDC imp_GetDC
#define ReleaseDC imp_ReleaseDC
#define SetProcessDPIAware imp_SetProcessDPIAware
#define AdjustWindowRect imp_AdjustWindowRect
#define BeginPaint imp_BeginPaint
#define EndPaint imp_EndPaint
#define CreateSolidBrush imp_CreateSolidBrush
#define CreatePen imp_CreatePen
#define SelectObject imp_SelectObject
#define DeleteObject imp_DeleteObject
#define RoundRect imp_RoundRect
#define CreateFontW imp_CreateFontW
#define SetTextColor imp_SetTextColor
#define SetBkColor imp_SetBkColor
#define SetBkMode imp_SetBkMode
#define GetDeviceCaps imp_GetDeviceCaps
#define GetTextExtentPoint32W imp_GetTextExtentPoint32W
#define GetOpenFileNameW imp_GetOpenFileNameW
#define DragAcceptFiles imp_DragAcceptFiles
#define DragQueryFileW imp_DragQueryFileW
#define DragFinish imp_DragFinish
#define _wfopen imp__wfopen
#define fclose imp_fclose
#define GetTempFileNameW imp_GetTempFileNameW
#define MoveFileExW imp_MoveFileExW
#define DeleteFileW imp_DeleteFileW
#define GetFileAttributesW imp_GetFileAttributesW
#define GetModuleHandleW imp_GetModuleHandleW
#define ExitProcess imp_ExitProcess
#define __wgetmainargs imp___wgetmainargs

#define RGBi(r,g,b) ((unsigned)((r)|((g)<<8)|((b)<<16)))
typedef struct { long l, t, r, b; } RECTw;
typedef struct { long x, y; } POINTw;
typedef struct { long cx, cy; } SIZEw;
typedef struct { void *hwnd; unsigned message; unsigned pad; void *wParam, *lParam; unsigned time; POINTw pt; } MSGw;
typedef struct { unsigned cbSize; unsigned dwFlags; void *hwndTrack; unsigned dwHoverTime; } TRACKw;
typedef struct { void *hdc; int fErase; RECTw rcPaint; int fRestore, fIncUpdate; unsigned char reserved[32]; } PAINTw;
typedef struct { unsigned style; void *lpfnWndProc; int cbClsExtra, cbWndExtra; void *hInstance, *hIcon, *hCursor, *hbrBackground; const wchar_t *lpszMenuName, *lpszClassName; } WNDCLASSw;
typedef struct { unsigned lStructSize; unsigned pad1; void *hwndOwner, *hInstance; const wchar_t *lpstrFilter; wchar_t *lpstrCustomFilter; unsigned nMaxCustFilter, nFilterIndex; wchar_t *lpstrFile; unsigned nMaxFile; wchar_t *lpstrFileTitle; unsigned nMaxFileTitle; const wchar_t *lpstrInitialDir, *lpstrTitle; unsigned Flags; unsigned short nFileOffset, nFileExtension; const wchar_t *lpstrDefExt; void *lCustData, *lpfnHook; const void *lpTemplateName; void *pvReserved; unsigned dwReserved, FlagsEx; } OFNw;

#define WM_DESTROY 2
#define WM_PAINT 15
#define WM_ERASEBKGND 20
#define WM_CTLCOLOREDIT 0x0133
#define WM_SETFONT 0x30
#define WM_SETCURSOR 0x20
#define WM_MOUSEMOVE 0x0200
#define WM_LBUTTONDOWN 0x0201
#define WM_MOUSELEAVE 0x02A3
#define WM_DROPFILES 0x0233
#define HTCLIENT 1
#define TME_LEAVE 2
#define IDC_ARROW ((const wchar_t*)32512)
#define IDC_HAND  ((const wchar_t*)32649)
#define SW_HIDE 0
#define SW_SHOWNORMAL 1
#define TRANSPARENT 1
#define PS_SOLID 0
#define PS_DASH 2
#define DEFAULT_CHARSET 1
#define CLEARTYPE_QUALITY 5
#define FW_NORMAL 400
#define FW_SEMIBOLD 600
#define LOGPIXELSX 88
#define DT_CALCRECT 0x400
#define DT_WORDBREAK 0x10
#define DT_SINGLELINE 0x20
#define DT_CENTER 0x25
#define DT_VCENTER 0x4
#define DT_NOPREFIX 0x800
#define DT_END_ELLIPSIS 0x8000
#define WS_CHILD 0x40000000u
#define WS_VISIBLE 0x10000000u
#define WS_TABSTOP 0x00010000u
#define ES_AUTOHSCROLL 0x80u
#define WS_CAPTION 0x00C00000u
#define WS_SYSMENU 0x00080000u
#define WS_MINIMIZEBOX 0x00020000u
#define OFN_HIDEREADONLY 0x4u
#define OFN_PATHMUSTEXIST 0x800u
#define OFN_FILEMUSTEXIST 0x1000u
#define FILE_ATTRIBUTE_DIRECTORY 0x10u
#define CLIENT_W 600
#define CLIENT_H 560

enum { Z_NONE = -1, Z_DROP = 0, Z_MODE0, Z_MODE1, Z_MODE2, Z_BTN };
enum { MD_SIM, MD_NEW, MD_INPLACE };
typedef struct { int x, y, w, h; } Box;

static void *g_win, *g_edit;
static unsigned g_dpi = 96;
static int g_mode = MD_SIM, g_hover = Z_NONE, g_hasfile, g_done, g_tracked;
static wchar_t g_input[512], g_output[512], g_openbuf[512], g_status[256];
static unsigned g_status_color;
static LogBuf g_log;
static Counts g_counts;
static void *f_title, *f_h2, *f_btn, *f_body, *f_small, *f_tiny, *f_chip;
static void *br_bg, *br_card, *br_accent, *br_hover, *br_dis, *br_tint, *br_white;
static void *pen_border, *pen_border2, *pen_accent, *pen_tint, *pen_dis, *pen_dark;
static Box r_drop, r_mode[3], r_out, r_btn, r_panel;

static int mm(int px){return (int)((long long)px*g_dpi/96);}

static void set_status(const wchar_t *s, unsigned color){
 size_t i=0;for(;s[i] && i<255;i++)g_status[i]=s[i];
 g_status[i]=0;g_status_color=color;
}
static void fill(Box *b,int x,int y,int w,int h){b->x=x;b->y=y;b->w=w;b->h=h;}

static const wchar_t *mode_name(int m){
 static const wchar_t *n[3]={L"Simular",L"Gerar novo XML",L"Alterar (backup)"};
 return n[m];
}
static int dir_of(const wchar_t *p,wchar_t *dir){
 size_t k=0;while(p[k])k++;
 while(k && p[k-1]!='/' && p[k-1]!='\\')k--;
 size_t n=0;
 if(k>=502)return 0;
 for(;n<k;n++)dir[n]=p[n];
 dir[n]=0;return 1;
}
static void update_output_suggest(void){
 if(!uc_unique_output(g_input,g_output,512))g_output[0]=0;
 SetWindowTextW(g_edit,g_output);
}
static void set_input(const wchar_t *p){
 unsigned attr=GetFileAttributesW(p);
 size_t i=0;for(;p[i]&&i<511;i++)g_input[i]=p[i];
 g_input[i]=0;
 g_done=0;lb_reset(&g_log);
 if(attr==0xFFFFFFFF){g_hasfile=0;set_status(L"Arquivo nao encontrado.",RGBi(185,28,28));InvalidateRect(g_win,0,1);return;}
 if(attr&FILE_ATTRIBUTE_DIRECTORY){g_hasfile=0;set_status(L"Selecione um arquivo XML (a selecao e uma pasta).",RGBi(185,28,28));InvalidateRect(g_win,0,1);return;}
 g_hasfile=1;g_status[0]=0;
 update_output_suggest();
 InvalidateRect(g_win,0,1);
}
static void pick_file(void){
 static wchar_t filter[] = L"XML (*.xml)\0*.xml\0Todos os arquivos\0*.*\0";
 OFNw o;
 unsigned char *z=(unsigned char*)&o;
 for(size_t i=0;i<sizeof o;i++)z[i]=0;
 g_openbuf[0]=0;
 o.lStructSize=(unsigned)sizeof o;
 o.hwndOwner=g_win;
 o.lpstrFilter=filter;
 o.lpstrFile=g_openbuf;
 o.nMaxFile=512;
 o.Flags=OFN_HIDEREADONLY|OFN_PATHMUSTEXIST|OFN_FILEMUSTEXIST;
 set_status(L"Escolha o arquivo XML, arraste-o para a janela ou clique na area de selecao.",RGBi(107,114,128));
 InvalidateRect(g_win,0,1);UpdateWindow(g_win);
 if(GetOpenFileNameW(&o)){ShowWindow(g_win,SW_SHOWNORMAL);set_input(g_openbuf);}
}
static void run_conversion(void){
 wchar_t out[512], dir[512], temp[520], backup[512];
 FILE *in,*dst;int ok;

 lb_reset(&g_log);
 g_counts.total=g_counts.updated=g_counts.good=g_counts.bad=0;
 g_done=0;

 if(g_mode==MD_SIM){
 in=_wfopen(g_input,L"rb");
 if(!in){set_status(L"Falha ao abrir o arquivo. Verifique o caminho e as permissoes.",RGBi(185,28,28));g_done=1;InvalidateRect(g_win,0,1);return;}
 ok=uc_convert(in,0,&g_counts,&g_log,0);
 fclose(in);
 if(!ok){set_status(L"Falha ao ler o arquivo.",RGBi(185,28,28));g_done=1;InvalidateRect(g_win,0,1);return;}
 set_status(L"Simulacao concluida. Nenhum arquivo foi alterado.",g_counts.bad?RGBi(180,83,9):RGBi(21,128,61));
 }else if(g_mode==MD_NEW){
 int n=GetWindowTextW(g_edit,out,511);out[n<0?0:n]=0;
 if(!out[0]){set_status(L"Informe o caminho do arquivo de saida.",RGBi(185,28,28));g_done=1;InvalidateRect(g_win,0,1);return;}
 if(GetFileAttributesW(out)!=0xFFFFFFFF){set_status(L"O arquivo de saida ja existe. Escolha outro nome.",RGBi(185,28,28));g_done=1;InvalidateRect(g_win,0,1);return;}
 if(!dir_of(out,dir)||!GetTempFileNameW(dir,L"cuc",0,temp)){set_status(L"Caminho de saida invalido ou sem espaco para arquivo temporario.",RGBi(185,28,28));g_done=1;InvalidateRect(g_win,0,1);return;}
 in=_wfopen(g_input,L"rb");dst=_wfopen(temp,L"wb");
 ok=in&&dst;
 if(ok)ok=uc_convert(in,dst,&g_counts,&g_log,0);
 if(in)fclose(in);
 if(dst){int fl=fclose(dst);dst=0;if(fl)ok=0;}
 if(!ok){DeleteFileW(temp);set_status(L"Falha ao processar ou gravar. Veja os avisos abaixo.",RGBi(185,28,28));g_done=1;InvalidateRect(g_win,0,1);return;}
 if(!MoveFileExW(temp,out,9)){DeleteFileW(temp);set_status(L"Nao foi possivel criar o arquivo final.",RGBi(185,28,28));g_done=1;InvalidateRect(g_win,0,1);return;}
 lb_wstr(&g_log,L"Gerado: ");lb_wstr(&g_log,out);lb_nl(&g_log);
 set_status(L"Concluido. Novo XML gerado.",g_counts.bad?RGBi(180,83,9):RGBi(21,128,61));
 }else{
 if(!dir_of(g_input,dir)||!GetTempFileNameW(dir,L"cuc",0,temp)){set_status(L"Sem espaco na pasta do arquivo original.",RGBi(185,28,28));g_done=1;InvalidateRect(g_win,0,1);return;}
 in=_wfopen(g_input,L"rb");dst=_wfopen(temp,L"wb");
 ok=in&&dst;
 if(ok)ok=uc_convert(in,dst,&g_counts,&g_log,0);
 if(in)fclose(in);
 if(dst){int fl=fclose(dst);dst=0;if(fl)ok=0;}
 if(!ok){DeleteFileW(temp);set_status(L"Falha ao processar. Veja os avisos abaixo. Nada foi alterado.",RGBi(185,28,28));g_done=1;InvalidateRect(g_win,0,1);return;}
 if(!uc_make_backup(g_input,backup)){DeleteFileW(temp);set_status(L"Falha ao criar o backup .bak. Nada foi alterado.",RGBi(185,28,28));g_done=1;InvalidateRect(g_win,0,1);return;}
 if(!MoveFileExW(temp,g_input,9)){DeleteFileW(temp);set_status(L"Nao foi possivel substituir o arquivo original.",RGBi(185,28,28));g_done=1;InvalidateRect(g_win,0,1);return;}
 lb_wstr(&g_log,L"Backup: ");lb_wstr(&g_log,backup);lb_nl(&g_log);
 set_status(L"Concluido. Original substituido e backup criado.",g_counts.bad?RGBi(180,83,9):RGBi(21,128,61));
 }
 if(!g_counts.total){lb_wstr(&g_log,L"Aviso: nenhuma tag <codigo_UC> encontrada.");lb_nl(&g_log);}
 g_done=1;
 InvalidateRect(g_win,0,1);
}

static unsigned blob_w(void *dc,const wchar_t *s){
 SIZEw sz;sz.cx=0;sz.cy=0;
 GetTextExtentPoint32W(dc,s,(int)wcslen(s),&sz);
 return (unsigned)sz.cx;
}
static void tx(void *dc,void *f,unsigned color,int x,int y,const wchar_t *s){
 SelectObject(dc,f);SetTextColor(dc,color);
 RECTw rc={x,y,x+mm(560),y+mm(40)};
 DrawTextW(dc,s,-1,&rc,DT_SINGLELINE|DT_NOPREFIX);
}
static void rc_box(void *dc,Box q,void *br,void *pn,int rad){
 if(pn)SelectObject(dc,pn);
 SelectObject(dc,br);
 RoundRect(dc,q.x,q.y,q.x+q.w,q.y+q.h,rad*2,rad*2);
}
static void chip_box(void *dc,Box q,unsigned color){
 void *br=CreateSolidBrush(color),*pn=CreatePen(PS_SOLID,1,color);
 SelectObject(dc,pn);SelectObject(dc,br);
 RoundRect(dc,q.x,q.y,q.x+q.w,q.y+q.h,mm(20),mm(20));
 DeleteObject(pn);DeleteObject(br);
}
static void draw_chips(void *dc,int *cyPx){
 if(!g_done)return;
 wchar_t line[64];
 struct { const wchar_t *label; unsigned long long v; unsigned fg, bg; } chips[4]={
 {L"Total",0,0,0},{L"Convertidas",0,0,0},{L"Ja formatadas",0,0,0},{L"Fora do padrao",0,0,0}
 };
 chips[0].v=(unsigned long long)g_counts.total;
 chips[1].v=(unsigned long long)g_counts.updated;
 chips[2].v=(unsigned long long)g_counts.good;
 chips[3].v=(unsigned long long)g_counts.bad;
 chips[1].fg=chips[1].v?RGBi(21,128,61):RGBi(107,114,128);
 chips[1].bg=chips[1].v?RGBi(232,245,233):RGBi(238,242,254);
 if(chips[3].v){chips[3].fg=RGBi(185,28,28);chips[3].bg=RGBi(253,232,232);}
 else{chips[3].fg=RGBi(21,128,61);chips[3].bg=RGBi(232,245,233);}
 chips[0].fg=RGBi(27,31,46);chips[0].bg=RGBi(238,242,254);
 chips[2].fg=RGBi(27,31,46);chips[2].bg=RGBi(238,242,254);
 int x=r_panel.x+mm(14),base=*cyPx;
 for(int i=0;i<4;i++){
 size_t n=0;const wchar_t *l=chips[i].label;
 for(;l[n];n++)line[n]=l[n];
 line[n++]=' ';
 unsigned long long v=chips[i].v;wchar_t rev[24];size_t m=0;
 do{rev[m++]=(wchar_t)('0'+v%10);v/=10;}while(v);
 for(size_t d=0;d<m;d++)line[n++]=rev[m-1-d];
 line[n]=0;
 unsigned w=blob_w(dc,line)+mm(18);
 if(x+(int)w>r_panel.x+r_panel.w-mm(14))break;
 Box q={x,base,(int)w,mm(22)};
 chip_box(dc,q,chips[i].bg);
 tx(dc,f_chip,chips[i].fg,x+mm(9),base+mm(3),line);
 x+=(int)w+mm(8);
 }
 *cyPx=base+mm(30);
}
static void paint(void){
 PAINTw ps;
 void *dc=BeginPaint(g_win,&ps);
 SetBkMode(dc,TRANSPARENT);
 RECTw full={0,0,mm(CLIENT_W),mm(CLIENT_H)};
 FillRect(dc,&full,br_bg);
 SelectObject(dc,f_title);SetTextColor(dc,RGBi(27,31,46));
 RECTw rt={mm(28),mm(20),mm(572),mm(56)};
 DrawTextW(dc,L"Conversor UC",-1,&rt,DT_SINGLELINE|DT_NOPREFIX);
 SelectObject(dc,f_small);SetTextColor(dc,RGBi(107,114,128));
 RECTw rs={mm(28),mm(54),mm(572),mm(74)};
 DrawTextW(dc,L"Formatacao de codigos UC em arquivos XML",-1,&rs,DT_SINGLELINE|DT_NOPREFIX);

 int hov=g_hover==Z_DROP;
 unsigned dashcol=hov?RGBi(59,112,240):RGBi(147,165,216);
 void *pn=CreatePen(PS_DASH,1,dashcol);
 void *br=hov&&g_hasfile==0?br_tint:br_card;
 rc_box(dc,r_drop,br,pn,mm(12));
 DeleteObject(pn);
 const wchar_t *name=g_input,*slash=0;
 for(size_t i=0;g_input[i];i++)if(g_input[i]=='/'||g_input[i]=='\\')slash=g_input+i;
 if(slash)name=slash+1;
 if(!g_hasfile){
 SelectObject(dc,f_btn);SetTextColor(dc,RGBi(27,31,46));
 RECTw r1={r_drop.x,r_drop.y+mm(24),r_drop.x+r_drop.w,r_drop.y+mm(56)};
 DrawTextW(dc,L"Arraste o arquivo XML aqui",-1,&r1,DT_SINGLELINE|DT_CENTER|DT_NOPREFIX);
 SelectObject(dc,f_tiny);SetTextColor(dc,RGBi(107,114,128));
 RECTw r2={r_drop.x,r_drop.y+mm(56),r_drop.x+r_drop.w,r_drop.y+mm(86)};
 DrawTextW(dc,L"ou clique para escolher",-1,&r2,DT_SINGLELINE|DT_CENTER|DT_NOPREFIX);
 }else{
 SelectObject(dc,f_h2);SetTextColor(dc,RGBi(27,31,46));
 RECTw r1={r_drop.x+mm(18),r_drop.y+mm(14),r_drop.x+r_drop.w-mm(18),r_drop.y+mm(40)};
 DrawTextW(dc,name,-1,&r1,DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX);
 SelectObject(dc,f_tiny);SetTextColor(dc,RGBi(107,114,128));
 RECTw r2={r_drop.x+mm(18),r_drop.y+mm(44),r_drop.x+r_drop.w-mm(18),r_drop.y+mm(66)};
 DrawTextW(dc,g_input,-1,&r2,DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX);
 RECTw r3={r_drop.x,r_drop.y+mm(70),r_drop.x+r_drop.w,r_drop.y+mm(94)};
 DrawTextW(dc,L"clique para escolher outro arquivo",-1,&r3,DT_SINGLELINE|DT_CENTER|DT_NOPREFIX);
 }

 SelectObject(dc,f_tiny);SetTextColor(dc,RGBi(107,114,128));
 RECTw rc={mm(28),mm(200),mm(572),mm(216)};
 DrawTextW(dc,L"O que fazer com o arquivo:",-1,&rc,DT_SINGLELINE|DT_NOPREFIX);
 for(int i=0;i<3;i++){
 int act=g_mode==i;
 int hovp=g_hover==i+1;
 void *brp=act?br_accent:(hovp?br_tint:br_card);
 void *pnp=act?pen_accent:(hovp?pen_tint:pen_border);
 rc_box(dc,r_mode[i],brp,pnp,mm(20));
 SelectObject(dc,f_btn);
 SetTextColor(dc,act?RGBi(255,255,255):(hovp?RGBi(59,112,240):RGBi(68,73,94)));
 RECTw rl={r_mode[i].x,r_mode[i].y+mm(11),r_mode[i].x+r_mode[i].w,r_mode[i].y+r_mode[i].h};
 DrawTextW(dc,mode_name(i),-1,&rl,DT_SINGLELINE|DT_CENTER|DT_NOPREFIX);
 }

 if(g_mode==MD_NEW){
 SelectObject(dc,f_tiny);SetTextColor(dc,RGBi(107,114,128));
 RECTw rl={mm(28),mm(268),mm(572),mm(284)};
 DrawTextW(dc,L"Salvar em:",-1,&rl,DT_SINGLELINE|DT_NOPREFIX);
 }

 int ben=g_hasfile;
 int hbv=g_hover==Z_BTN&&ben;
 rc_box(dc,r_btn,ben?(hbv?br_hover:br_accent):br_dis,ben?(hbv?pen_dark:pen_accent):pen_dis,mm(24));
 SelectObject(dc,f_btn);SetTextColor(dc,RGBi(255,255,255));
 RECTw rb={r_btn.x,r_btn.y+mm(13),r_btn.x+r_btn.w,r_btn.y+r_btn.h};
 DrawTextW(dc,ben?L"Converter":L"Escolha um arquivo primeiro",-1,&rb,DT_SINGLELINE|DT_CENTER|DT_NOPREFIX);

 rc_box(dc,r_panel,br_card,pen_border,mm(12));
 int cy=r_panel.y+mm(12);
 if(g_status[0]){
 SelectObject(dc,f_h2);SetTextColor(dc,g_status_color);
 RECTw rst={r_panel.x+mm(14),cy,r_panel.x+r_panel.w-mm(14),cy+mm(22)};
 DrawTextW(dc,g_status,-1,&rst,DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX);
 cy+=mm(24);
 }else{
 SelectObject(dc,f_small);SetTextColor(dc,RGBi(107,114,128));
 RECTw rst={r_panel.x+mm(14),cy,r_panel.x+r_panel.w-mm(14),cy+mm(20)};
 DrawTextW(dc,L"Escolha o arquivo, o modo e clique em Converter.",-1,&rst,DT_SINGLELINE|DT_NOPREFIX);
 cy+=mm(24);
 }
 draw_chips(dc,&cy);
 int haveLog=g_log.data&&g_log.data[0];
 if(haveLog){
 int lh=mm(16);
 int avail=r_panel.y+r_panel.h-mm(12)-cy;
 int total=0;
 for(const wchar_t *s=g_log.data;*s;s++)if(*s=='\n')total++;
 int skip=total>avail/lh?total-avail/lh:0;
 int y=cy,idx=0;
 for(const wchar_t *s=g_log.data;;){
 const wchar_t *e=s;
 while(*e&&*e!='\n')e++;
 if(idx>=skip&&y+lh<=r_panel.y+r_panel.h-mm(8)){
 SelectObject(dc,f_small);SetTextColor(dc,RGBi(68,73,94));
 RECTw rl={r_panel.x+mm(14),y,r_panel.x+r_panel.w-mm(14),y+lh};
 DrawTextW(dc,s,(int)(e-s),&rl,DT_SINGLELINE|DT_END_ELLIPSIS|DT_NOPREFIX);
 }
 y+=lh;idx++;
 if(!*e)break;
 s=e+1;
 }
 }
 EndPaint(g_win,&ps);
}
static int zone_at(int x,int y){
 if(x>=r_drop.x&&y>=r_drop.y&&x<r_drop.x+r_drop.w&&y<r_drop.y+r_drop.h)return Z_DROP;
 for(int i=0;i<3;i++){Box*q=&r_mode[i];if(x>=q->x&&y>=q->y&&x<q->x+q->w&&y<q->y+q->h)return i+1;}
 if(x>=r_btn.x&&y>=r_btn.y&&x<r_btn.x+r_btn.w&&y<r_btn.y+r_btn.h)return Z_BTN;
 return Z_NONE;
}
static int mouse_xy(int *x,int *y){
 POINTw p;if(!GetCursorPos(&p))return 0;ScreenToClient(g_win,&p);
 *x=(int)p.x;*y=(int)p.y;return 1;
}
static long ABI wndproc(void *h,unsigned m,void *wp,void *lp){
 switch(m){
 case WM_DESTROY:PostQuitMessage(0);return 0;
 case WM_ERASEBKGND:return 1;
 case WM_CTLCOLOREDIT:{
 void *dc=wp;
 SetTextColor(dc,RGBi(27,31,46));SetBkColor(dc,RGBi(255,255,255));
 return (long)br_white;
 }
 case WM_SETCURSOR:
 if(((unsigned long long)(size_t)lp&0xFFFF)==HTCLIENT){
 int x,y;int z=mouse_xy(&x,&y)?zone_at(x,y):Z_NONE;
 SetCursor(z>=0?LoadCursorW(0,IDC_HAND):LoadCursorW(0,IDC_ARROW));
 return 1;
 }
 break;
 case WM_DROPFILES:{
 wchar_t buf[512];
 unsigned n=DragQueryFileW(wp,0xFFFFFFFF,0,0);
 if(n>=1&&DragQueryFileW(wp,0,buf,512)){
 DragFinish(wp);
 set_input(buf);
 }else DragFinish(wp);
 return 0;
 }
 case WM_MOUSELEAVE:
 g_hover=Z_NONE;g_tracked=0;InvalidateRect(g_win,0,0);
 break;
 case WM_MOUSEMOVE:{
 int x,y;
 if(!mouse_xy(&x,&y))break;
 if(!g_tracked){
 TRACKw t;t.cbSize=sizeof t;t.dwFlags=TME_LEAVE;t.hwndTrack=g_win;t.dwHoverTime=0;
 if(TrackMouseEvent(&t))g_tracked=1;
 }
 int z=zone_at(x,y);
 if(z!=g_hover){g_hover=z;InvalidateRect(g_win,0,0);}
 break;
 }
 case WM_LBUTTONDOWN:{
 int x,y;
 if(!mouse_xy(&x,&y))break;
 int z=zone_at(x,y);
 if(z==Z_DROP)pick_file();
 else if(z>=Z_MODE0&&z<=Z_MODE2){
 int nm=z-1;
 if(nm!=g_mode){
 g_mode=nm;
 ShowWindow(g_edit,g_mode==MD_NEW?SW_SHOWNORMAL:SW_HIDE);
 if(g_hasfile&&g_mode==MD_NEW)SetWindowTextW(g_edit,g_output);
 InvalidateRect(g_win,0,1);
 }
 }
 else if(z==Z_BTN&&g_hasfile)run_conversion();
 break;
 }
 }
 return (long)DefWindowProcW(h,m,wp,lp);
}
int uc_gui_main(void){
 SetProcessDPIAware();
 void *dc=GetDC(0);
 if(dc){int d=GetDeviceCaps(dc,LOGPIXELSX);if(d>0)g_dpi=(unsigned)d;ReleaseDC(0,dc);}

 WNDCLASSw wc;
 wc.style=0;wc.lpfnWndProc=wndproc;wc.cbClsExtra=0;wc.cbWndExtra=0;
 wc.hInstance=GetModuleHandleW(0);wc.hIcon=0;wc.hCursor=LoadCursorW(0,IDC_ARROW);
 wc.hbrBackground=0;wc.lpszMenuName=0;wc.lpszClassName=L"UC_GUI_WIN";

 f_title=CreateFontW(-mm(22),0,0,0,FW_SEMIBOLD,0,0,0,DEFAULT_CHARSET,0,0,CLEARTYPE_QUALITY,0,L"Segoe UI");
 f_h2=CreateFontW(-mm(14),0,0,0,FW_SEMIBOLD,0,0,0,DEFAULT_CHARSET,0,0,CLEARTYPE_QUALITY,0,L"Segoe UI");
 f_btn=CreateFontW(-mm(15),0,0,0,FW_SEMIBOLD,0,0,0,DEFAULT_CHARSET,0,0,CLEARTYPE_QUALITY,0,L"Segoe UI");
 f_body=CreateFontW(-mm(14),0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,0,0,CLEARTYPE_QUALITY,0,L"Segoe UI");
 f_small=CreateFontW(-mm(13),0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,0,0,CLEARTYPE_QUALITY,0,L"Segoe UI");
 f_tiny=CreateFontW(-mm(12),0,0,0,FW_NORMAL,0,0,0,DEFAULT_CHARSET,0,0,CLEARTYPE_QUALITY,0,L"Segoe UI");
 f_chip=CreateFontW(-mm(12),0,0,0,FW_SEMIBOLD,0,0,0,DEFAULT_CHARSET,0,0,CLEARTYPE_QUALITY,0,L"Segoe UI");

 br_bg=CreateSolidBrush(RGBi(246,247,251));
 br_card=CreateSolidBrush(RGBi(255,255,255));
 br_accent=CreateSolidBrush(RGBi(59,112,240));
 br_hover=CreateSolidBrush(RGBi(38,86,214));
 br_dis=CreateSolidBrush(RGBi(205,214,236));
 br_tint=CreateSolidBrush(RGBi(240,244,255));
 br_white=CreateSolidBrush(RGBi(255,255,255));
 pen_border=CreatePen(PS_SOLID,1,RGBi(227,230,239));
 pen_border2=CreatePen(PS_SOLID,1,RGBi(213,218,230));
 pen_accent=CreatePen(PS_SOLID,1,RGBi(59,112,240));
 pen_tint=CreatePen(PS_SOLID,1,RGBi(189,209,250));
 pen_dark=CreatePen(PS_SOLID,1,RGBi(38,86,214));
 pen_dis=CreatePen(PS_SOLID,1,RGBi(205,214,236));

 if(!RegisterClassW(&wc))return 1;
 int w=mm(CLIENT_W),h=mm(CLIENT_H);
 RECTw adj={0,0,w,h};
 AdjustWindowRect(&adj,WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,0);
 int ww=adj.r-adj.l,wh=adj.b-adj.t;
 g_win=CreateWindowExW(0,L"UC_GUI_WIN",L"Conversor UC",WS_CAPTION|WS_SYSMENU|WS_MINIMIZEBOX,
 0x80000000u,0x80000000u,ww,wh,0,0,wc.hInstance,0);
 if(!g_win)return 1;
 DragAcceptFiles(g_win,1);

 g_edit=CreateWindowExW(0,L"EDIT",L"",WS_CHILD|WS_VISIBLE|WS_TABSTOP|ES_AUTOHSCROLL,
 mm(42),mm(292),w-mm(84),mm(22),g_win,0,wc.hInstance,0);
 SendMessageW(g_edit,WM_SETFONT,(void*)f_body,0);
 ShowWindow(g_edit,SW_HIDE);

 fill(&r_drop,mm(28),mm(88),w-mm(56),mm(104));
 fill(&r_mode[0],mm(28),mm(216),mm(174),mm(44));
 fill(&r_mode[1],mm(212),mm(216),mm(174),mm(44));
 fill(&r_mode[2],mm(396),mm(216),w-mm(28)-mm(396),mm(44));
 fill(&r_out,mm(28),mm(284),w-mm(56),mm(38));
 fill(&r_btn,mm(28),mm(334),w-mm(56),mm(50));
 fill(&r_panel,mm(28),mm(400),w-mm(56),h-mm(400)-mm(24));

 set_status(L"Arraste o XML para a janela ou clique na area de selecao.",RGBi(107,114,128));
 ShowWindow(g_win,SW_SHOWNORMAL);
 UpdateWindow(g_win);
 MSGw msg;
 long rc=0;
 while((rc=GetMessageW(&msg,0,0,0))>0){TranslateMessage(&msg);DispatchMessageW(&msg);}
 return (int)rc;
}
void start(void){
 int argc=0,mode=0;wchar_t **argv,**env;
 if(imp___wgetmainargs(&argc,&argv,&env,0,&mode))imp_ExitProcess(1);
 imp_ExitProcess((unsigned)uc_gui_main());
}
#endif
