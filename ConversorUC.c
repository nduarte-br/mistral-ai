#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <stdint.h>
#include "uc_core.h"

#ifdef _WIN32
#define ABI __attribute__((ms_abi))
#define IMP(ret,name,args) extern ret (ABI *imp_##name) args
IMP(FILE*,_wfopen,(const wchar_t*,const wchar_t*));
IMP(int,fgetc,(FILE*)); IMP(int,fclose,(FILE*)); IMP(int,ferror,(FILE*));
IMP(size_t,fwrite,(const void*,size_t,size_t,FILE*));
IMP(void*,realloc,(void*,size_t)); IMP(void,free,(void*));
IMP(int,wprintf,(const wchar_t*,...)); IMP(int,getwchar,(void));
IMP(int,wcscmp,(const wchar_t*,const wchar_t*)); IMP(size_t,wcslen,(const wchar_t*));
IMP(int,MoveFileExW,(const wchar_t*,const wchar_t*,unsigned));
IMP(int,CopyFileW,(const wchar_t*,const wchar_t*,int)); IMP(int,DeleteFileW,(const wchar_t*));
IMP(unsigned,GetLastError,(void)); IMP(unsigned,GetFileAttributesW,(const wchar_t*));
IMP(int,GetTempFileNameW,(const wchar_t*,const wchar_t*,unsigned,wchar_t*));
IMP(void,exit,(int));
IMP(int,__wgetmainargs,(int*,wchar_t***,wchar_t***,int,void*)); IMP(void,ExitProcess,(unsigned));
#define wprintf imp_wprintf
#define wcscmp imp_wcscmp
#define wcslen imp_wcslen
#define getwchar imp_getwchar
#define realloc imp_realloc
#define free imp_free
#define fgetc imp_fgetc
#define fclose imp_fclose
#define ferror imp_ferror
#define fwrite imp_fwrite
#endif

#ifdef _WIN32
#define MAXPATH 260
static int ask(wchar_t *buf){int c;size_t n=0;while((c=(unsigned short)getwchar())!=65535 && c!='\n'){if(n>=MAXPATH-2)return 0;if(c!='"' && c!='\r')buf[n++]=c;}buf[n]=0;return c!=65535;}
static int join(wchar_t *dest,const wchar_t *src,size_t n,const wchar_t *suffix){
 if(n+wcslen(suffix)>=MAXPATH)return 0;for(size_t i=0;i<n;i++)dest[i]=src[i];do{dest[n++]=*suffix;}while(*suffix++);return 1;
}
static int usage(void){wprintf(L"ConversorUC [-i | -o saida.xml] [-q] [-n | --dry-run] [--] entrada.xml\n");return 2;}
static int run(int argc,wchar_t **argv){
 wchar_t *in=NULL,*out=NULL,input[MAXPATH],answer[MAXPATH],suggest[MAXPATH],temp[MAXPATH],dir[MAXPATH],backup[MAXPATH];int inplace=0,dry=0,quiet=0,literal=0;
 for(int i=1;i<argc;i++){
 wchar_t *a=argv[i];if(!literal && a[0]=='-'){
 if(!wcscmp(a,L"--"))literal=1;
 else if(!wcscmp(a,L"-q"))quiet=1;
 else if(!wcscmp(a,L"--help")||!wcscmp(a,L"-h")){usage();return 0;}
 else if(!wcscmp(a,L"-n")||!wcscmp(a,L"--dry-run")||!wcscmp(a,L"--dryrun"))dry=1;
 else if(!wcscmp(a,L"-i")&&!out&&!inplace)inplace=1;
 else if(!wcscmp(a,L"-o")&&!out&&!inplace && ++i<argc)out=argv[i];
 else return usage();
 }else if(!in)in=a;else return usage();
 }
 if(!in){if(out||inplace)return usage();wprintf(L"Arraste o XML para esta janela e pressione Enter:\n");if(!ask(input))return 1;in=input;}
 if(wcslen(in)>=MAXPATH-20)return 1;
 if(!out&&!inplace&&!dry){
 wprintf(L"1 - Simular\n2 - Gerar novo XML\n3 - Alterar original com backup\n0 - Sair\nEscolha: ");
 if(!ask(answer))return 1;
 if(!wcscmp(answer,L"0"))return 0;
 if(!wcscmp(answer,L"1"))dry=1;
 else if(!wcscmp(answer,L"3"))inplace=1;
 else if(!wcscmp(answer,L"2")){
 size_t cut=wcslen(in);for(size_t i=cut;i>0;i--){if(in[i-1]=='.'){cut=i-1;break;}if(in[i-1]=='/'||in[i-1]=='\\')break;}
 if(!join(suggest,in,cut,L"_CPF.xml"))return 1;
 wprintf(L"Saida [Enter = %ls]: ",suggest);if(!ask(answer))return 1;
 if(*answer && !join(suggest,answer,wcslen(answer),L""))return 1;out=suggest;
 if(imp_GetFileAttributesW(out)!=0xffffffff){wprintf(L"Substituir arquivo existente? [s/N]: ");if(!ask(answer)|| (wcscmp(answer,L"s")&&wcscmp(answer,L"S")))return 0;}
 }else return usage();
 }
 if(inplace)out=in;
 FILE *src=imp__wfopen(in,L"rb"),*dst=NULL;if(!src){wprintf(L"Falha ao abrir a entrada.\n");return 1;}
 int rc=1,hasTemp=0;Counts counts={0};
 if(out && !inplace){
 extern int same_file(const wchar_t*,const wchar_t*);if(same_file(in,out)){wprintf(L"Entrada e saida iguais. Use -i.\n");goto done;}
 }
 if(!dry){
 size_t k=wcslen(out);while(k && out[k-1]!='/' && out[k-1]!='\\')k--;
 if(!join(dir,out,k,k?L"":L"."))goto done;
 if(!imp_GetTempFileNameW(dir,L"cuc",0,temp))goto done;hasTemp=1;
 dst=imp__wfopen(temp,L"wb");if(!dst)goto done;
 }
 if(!uc_convert(src,dst,&counts,0,1))goto done;
 if(dst){int failed=fclose(dst);dst=NULL;if(failed)goto done;}
 if(inplace&&!dry){
 if(!uc_make_backup(in,backup))goto done;
 if(!quiet)wprintf(L"Backup: %ls\n",backup);
 }
 fclose(src);src=NULL;
 if(!dry && !imp_MoveFileExW(temp,out,9))goto done;
 hasTemp=0;
 if(!quiet)wprintf(L"%ls | Total: %I64u | Conversoes: %I64u | Ja formatadas: %I64u | Fora do padrao: %I64u\n",dry?L"Simulacao":L"Concluido",counts.total,counts.updated,counts.good,counts.bad);
 if(!counts.total)wprintf(L"Aviso: nenhuma tag <codigo_UC> encontrada.\n");rc=counts.bad?3:0;
 done:if(dst)fclose(dst);if(src)fclose(src);if(hasTemp)imp_DeleteFileW(temp);if(rc==1)wprintf(L"Falha ao concluir. Verifique o caminho, o espaco e as permissoes.\n");return rc;
}
IMP(void*,CreateFileW,(const wchar_t*,unsigned,unsigned,void*,unsigned,unsigned,void*));
IMP(int,GetFileInformationByHandle,(void*,unsigned*));IMP(int,CloseHandle,(void*));
int same_file(const wchar_t *a,const wchar_t *b){
 void *x=imp_CreateFileW(a,0,7,NULL,3,0,NULL),*y=imp_CreateFileW(b,0,7,NULL,3,0,NULL);
 unsigned u[13],v[13];int same=0;
 if(x!=(void*)-1 && y!=(void*)-1){same=!imp_GetFileInformationByHandle(x,u)||!imp_GetFileInformationByHandle(y,v)||(u[7]==v[7]&&u[11]==v[11]&&u[12]==v[12]);}
 if(x!=(void*)-1)imp_CloseHandle(x);if(y!=(void*)-1)imp_CloseHandle(y);return same;
}
void start(void){int argc=0,mode=0;wchar_t **argv,**env;if(imp___wgetmainargs(&argc,&argv,&env,0,&mode))imp_ExitProcess(1);
 int rc=run(argc,argv);if(argc==1||(argc==2&&argv[1][0]!='-')){wprintf(L"Pressione Enter para fechar.");getwchar();}imp_exit(rc);}
#endif
