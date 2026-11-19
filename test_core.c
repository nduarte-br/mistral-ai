#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "uc_core.h"

static const char *sample =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
"<arquivo>\n"
"  <registro><codigo_UC>012345678901</codigo_UC></registro>\n"
"  <registro><codigo_UC>12345678901</codigo_UC></registro>\n"
"  <registro><codigo_UC>123.456.789-01</codigo_UC></registro>\n"
"  <registro><codigo_UC>xpto</codigo_UC></registro>\n"
"  <sem_uc>outro valor</sem_uc>\n"
"</arquivo>\n";

int main(void){
 FILE *f=fopen("sample.xml","wb");
 fwrite(sample,1,strlen(sample),f);
 fclose(f);

 LogBuf log={0};
 Counts c={0};
 FILE *in=fopen("sample.xml","rb");
 int ok=uc_convert(in,NULL,&c,&log,0);
 fclose(in);
 printf("simulacao ok=%d total=%zu updated=%zu good=%zu bad=%zu\n",ok,c.total,c.updated,c.good,c.bad);
 printf("--- log ---\n%ls--- serde ---\n",log.data?log.data:L"");

 Counts c2={0};
 in=fopen("sample.xml","rb");
 FILE *out=fopen("out.xml","wb");
 ok=uc_convert(in,out,&c2,0,0);
 fclose(in);fclose(out);
 printf("gravacao ok=%d updated=%zu\n",ok,c2.updated);

 Counts c3={0};
 in=fopen("out.xml","rb");
 ok=uc_convert(in,NULL,&c3,0,0);
 fclose(in);
 printf("releitura ok=%d total=%zu updated=%zu good=%zu bad=%zu\n",ok,c3.total,c3.updated,c3.good,c3.bad);

 printf("--- out.xml ---\n");
 out=fopen("out.xml","rb");
 int ch;int col=0;
 while((ch=fgetc(out))!=EOF){putchar(ch);col++;}
 fclose(out);

 LogBuf log2={0};
 in=fopen("bad.bin","wb+b");fclose(in);
 if((in=fopen("bad.bin","rb"))){
  unsigned char bin[4]={1,2,0,4};
  FILE *g=fopen("nul.bin","wb");fwrite(bin,1,4,g);fclose(g);
  fclose(in);
 }
 in=fopen("nul.bin","rb");
 ok=uc_convert(in,NULL,&c3,&log2,0);
 fclose(in);
 printf("nul-test ok=%d: %ls",ok,log2.data?log2.data:L"(sem log)\n");
 return 0;
}
