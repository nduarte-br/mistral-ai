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
IMP(int,wprintf,(const wchar_t*,...));
IMP(size_t,wcslen,(const wchar_t*));
IMP(int,MoveFileExW,(const wchar_t*,const wchar_t*,unsigned));
IMP(int,CopyFileW,(const wchar_t*,const wchar_t*,int)); IMP(int,DeleteFileW,(const wchar_t*));
IMP(unsigned,GetLastError,(void)); IMP(unsigned,GetFileAttributesW,(const wchar_t*));
IMP(int,GetTempFileNameW,(const wchar_t*,const wchar_t*,unsigned,wchar_t*));
#define fgetc imp_fgetc
#define fclose imp_fclose
#define ferror imp_ferror
#define fwrite imp_fwrite
#define realloc imp_realloc
#define free imp_free
#define wprintf imp_wprintf
#define wcslen imp_wcslen
#define CopyFileW imp_CopyFileW
#define GetLastError imp_GetLastError
#define GetFileAttributesW imp_GetFileAttributesW
#endif

#define UCMAXPATH 260

void lb_reset(LogBuf *b){b->len=0;if(b->data)b->data[0]=0;}
void lb_free(LogBuf *b){free(b->data);b->data=0;b->len=0;b->cap=0;}
static void lb_grow(LogBuf *b,size_t add){
 if(!b || b->len+add+1<=b->cap)return;
 if(!b)return;
 size_t cap=b->cap?b->cap:256;
 while(cap<b->len+add+1)cap*=2;
 void *d=realloc(b->data,cap*sizeof(wchar_t));
 if(!d)return;
 b->data=d;b->cap=cap;
}
void lb_wstr(LogBuf *b,const wchar_t *s){
 if(!b)return;
 size_t n=wcslen(s);lb_grow(b,n);
 if(!b->data || b->len+n+1>b->cap)return;
 for(size_t i=0;i<n;i++)b->data[b->len+i]=s[i];
 b->len+=n;b->data[b->len]=0;
}
void lb_bytes(LogBuf *b,const unsigned char *p,size_t n){
 if(!b)return;
 lb_grow(b,n);
 if(!b->data || b->len+n+1>b->cap)return;
 for(size_t i=0;i<n;i++)b->data[b->len+i]=(wchar_t)p[i];
 b->len+=n;b->data[b->len]=0;
}
void lb_u64(LogBuf *b,unsigned long long v){
 wchar_t tmp[24];size_t n=0;
 do{tmp[n++]=(wchar_t)('0'+v%10);v/=10;}while(v);
 wchar_t rev[24];
 for(size_t i=0;i<n;i++)rev[i]=tmp[n-1-i];
 rev[n]=0;lb_wstr(b,rev);
}
void lb_nl(LogBuf *b){lb_wstr(b,L"\n");}

static int digit(int c){return c>='0' && c<='9';}
static int starts(const unsigned char *p,size_t n,const char *s){
 while(*s){if(!n || *p++!=(unsigned char)*s++)return 0;n--;}return 1;
}
static int formatted(const unsigned char *p,size_t n){
 size_t i=0;while(i<n && digit(p[i]))i++;
 if(!i || i>3)return 0;
 while(i<n && p[i]=='.'){if(n-i<4 || !digit(p[i+1]) || !digit(p[i+2]) || !digit(p[i+3]))return 0;i+=4;}
 return n-i==3 && p[i]=='-' && digit(p[i+1]) && digit(p[i+2]);
}
static int put(FILE *out,const void *p,size_t n){return !out || fwrite(p,1,n,out)==n;}
static void lecho(LogBuf *log,int cli,char ch){
 if(cli)wprintf(L"%lc",(int)(unsigned char)ch);
 else lb_bytes(log,(const unsigned char*)&ch,1);
}
static int line(FILE *out,const unsigned char *p,size_t n,unsigned long number,Counts *c,LogBuf *log,int cli){
 size_t last=0;
 for(size_t i=0;i<n;i++){
 if(!starts(p+i,n-i,"<codigo_UC>"))continue;
 c->total++;size_t begin=i+11,end=begin;
 while(end<n && p[end]!='<')end++;
 size_t len=end-begin,k=0;while(k<len && digit(p[begin+k]))k++;
 int closed=starts(p+end,n-end,"</codigo_UC>");
 if(closed && k==len && len>=3){
 if(!put(out,p+last,begin-last))return 0;
 if(!out){
 if(cli){
 wprintf(L"Linha %lu: ",number);
 for(size_t j=0;j<len;j++)wprintf(L"%lc",(int)p[begin+j]);
 wprintf(L" -> ");
 }else{
 size_t shown=len<80?len:80;
 lb_wstr(log,L"Linha ");lb_u64(log,number);lb_wstr(log,L": ");
 lb_bytes(log,p+begin,shown);
 if(len>80)lb_wstr(log,L"...");
 lb_wstr(log,L" -> ");
 }
 }
 for(size_t j=0;j<len;j++){
 char sep=0;if(j==len-2)sep='-';else if(j && j<len-2 && (len-2-j)%3==0)sep='.';
 if(sep){if(!put(out,&sep,1))return 0;if(!out)lecho(log,cli,sep);}
 if(!put(out,p+begin+j,1))return 0;if(!out)lecho(log,cli,(char)p[begin+j]);
 }
 if(!out){if(cli)wprintf(L"\n");else lb_nl(log);}
 last=end;c->updated++;
 }else if(closed && formatted(p+begin,len))c->good++;
 else{if(c->bad<10){if(cli)wprintf(L"Aviso: UC fora do padrao na linha %lu.\n",number);else{lb_wstr(log,L"Aviso: UC fora do padrao na linha ");lb_u64(log,number);lb_wstr(log,L".");lb_nl(log);}}c->bad++;}
 }
 return put(out,p+last,n-last);
}
int uc_convert(FILE *in,FILE *out,Counts *c,LogBuf *log,int cli){
 unsigned char *buf=NULL;size_t cap=0,n=0;unsigned long num=1;int ok=1,ch;
 while((ch=fgetc(in))!=EOF){
 if(!ch){if(cli)wprintf(L"Codificacao incompativel. Use XML em UTF-8 ou Windows-1252.\n");else{lb_wstr(log,L"Codificacao incompativel. Use XML em UTF-8 ou Windows-1252.");lb_nl(log);}ok=0;break;}
 if(n==cap){size_t next=cap?cap*2:8192;void *b=realloc(buf,next);if(!b){ok=0;break;}buf=b;cap=next;}
 buf[n++]=(unsigned char)ch;if(ch=='\n'){ok=line(out,buf,n,num++,c,log,cli);n=0;if(!ok)break;}
 }
 if(ok && n)ok=line(out,buf,n,num,c,log,cli);free(buf);return ok && !ferror(in);
}
#ifdef _WIN32
static int ujoin(wchar_t *dest,const wchar_t *src,size_t n,const wchar_t *suffix){
 if(n+wcslen(suffix)>=UCMAXPATH)return 0;for(size_t i=0;i<n;i++)dest[i]=src[i];do{dest[n++]=*suffix;}while(*suffix++);return 1;
}
int uc_make_backup(const wchar_t *in,wchar_t *backup){
 if(!ujoin(backup,in,wcslen(in),L".bak"))return 0;
 unsigned seq=0;
 while(!CopyFileW(in,backup,1)){
 if(GetLastError()!=80 && GetLastError()!=183)return 0;
 wchar_t suffix[24];size_t j=20;suffix[j]=0;unsigned x=++seq;
 do{suffix[--j]='0'+x%10;x/=10;}while(x);suffix[--j]='.';
 if(!ujoin(backup,in,wcslen(in),L".bak")||!ujoin(backup,backup,wcslen(backup),suffix+j))return 0;
 }
 return 1;
}
int uc_unique_output(const wchar_t *in,wchar_t *out,unsigned cap){
 size_t cut=wcslen(in);
 for(size_t i=cut;i>0;i--){if(in[i-1]=='.'){cut=i-1;break;}if(in[i-1]=='/'||in[i-1]=='\\')break;}
 if(cut+20>=cap)return 0;
 for(unsigned k=1;;k++){
 size_t n=cut;
 for(size_t i=0;i<n;i++)out[i]=in[i];
 const wchar_t *mid=L"_CPF.xml";
 for(size_t i=0;mid[i];i++)out[n++]=mid[i];
 if(k>1){
 wchar_t num[16];size_t m=0;unsigned x=k;
 do{num[m++]=(wchar_t)('0'+x%10);x/=10;}while(x);
 out[n++]='_';
 for(size_t i=0;i<m;i++)out[n++]=num[m-1-i];
 const wchar_t *ext=L".xml";
 for(size_t i=0;ext[i];i++)out[n++]=ext[i];
 }
 out[n]=0;
 if(GetFileAttributesW(out)==0xFFFFFFFF)return 1;
 if(k==999)return 1;
 }
}
#endif
