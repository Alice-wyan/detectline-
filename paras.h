#ifndef PARAS_H
#define PARAS_H

class paras
{
public:
	paras(void);
	~paras(void);
int file_size(char* fn);
int para_load(char* fn,char* pd, int length);
int para_number(char* in);
int para_value(char* in,char**v);
int para(char *a);
int run(char* para_file);
char * v(int i);

int gargc;
int cp;
int help;
char** gargv;
char* para_data;
int para_size;

};
paras::paras(void)
{
	para_data=0;
	help=0;
}

paras::~paras(void)
{
	if(para_data!=0) delete []para_data;
}

int paras::file_size(char* fn){FILE *p =fopen(fn,"rb");fseek(p,0L,SEEK_END);int fz=ftell(p);fclose(p);	return fz;}
int paras::para_load(char* fn,char* pd, int length){FILE *fp=fopen(fn,"rb");if(fp==NULL){printf("FILE %s Is Not Open",fn);return 0;}fread(pd,1,length,fp);fclose(fp);	return 1;}

int paras::para_number(char* in){int len=strlen(in);int i=0;int ret=0;for(i=0;i<len-1;i++){if(i==0&&in[i]!=' '&&in[i]!='\t'&&in[i]!='\r'&&in[i]!='\n'){ret++;
continue;}if(in[i  ]==' '||in[i  ]=='\t'||in[i  ]=='\r'||in[i  ]=='\n'){if(in[i+1]!=' '&&in[i+1]!='\t'&&in[i+1]!='\r'&&in[i+1]!='\n'){ret++;}}}	return ret;}

int paras::para_value(char* in,char**v){	int len=strlen(in);
	int i=0;	int ret=0;
	for(i=0;i<len-1;i++)	{
		if(i==0&&in[i]!=' '&&in[i]!='\t'&&in[i]!='\r'&&in[i]!='\n')
		{v[ret]=in+i;ret++;continue;}
		if(in[i  ]==' '||in[i  ]=='\t'||in[i  ]=='\r'||in[i  ]=='\n')
		{	in[i]=0;
			if(in[i+1]!=' '&&in[i+1]!='\t'&&in[i+1]!='\r'&&in[i+1]!='\n')
			{v[ret]=in+i+1;ret++;}
		}}return ret;}
int paras::para(char *a){if(help==1)cout<<a<<" ";int i;for(i=0;i<gargc;i++){if(strcmp(a,gargv[i])==0) { cp=i; return i;}}cp=-1;return -1;}

int paras::run(char* para_file){
	para_size=file_size(para_file);	
	para_data=new char[para_size+1];
	para_data[para_size]=0;
	para_load(para_file,para_data,para_size);
	gargc=para_number(para_data);gargv=new char*[gargc];para_value(para_data,gargv);
	return 0;
}

char * paras::v(int i){
if(cp+i>=gargc) return 0;
return gargv[cp+i];
}


#endif