#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

char* search(char*,int,char*);


struct data
{
	data()
	{
		pr=1;
		lout=0;
		f=0;
		lincount=0;
		name=new char[10];
		//for(int i=0;i<300;i++)lin[i]=-1;
	}

	double pr,lout;
	int f,lincount;
	char *name;
	int lin[300];
};
data input[300];
int s[300];
int fnumber;


int isword(char a)
{
	return (a>='a'&&a<='z')||(a>='A'&&a<='Z')||(a>='0'&&a<='9');
}


char* search(char*key,int l,char*data)
{
	if(*data==0)return 0;
	char *p=data;
	while(*p!='\0')
	{
		int success=0;
		char *x =data;
		while(*p!='\0'&&*p!=*key)p++;
		if(*p==0||*p=='\0')return 0;
		if(p!=data)
		{
			if(isword(*(p-1)))
			{
				p++;
				goto notsuccess;
			}
		}
		for(char*k=key;k<key+l;k++)
		{
			
			if(*p=='\0')return 0;
			if(*k!=*p)goto notsuccess;
			//printf("%c",*p);
			p++;
		}
	
		success=1;
		
		/*while(*x!='\0')
		{printf("%c",*x);x++;}*/
		//printf("[%c]",*(p-1));
		//printf("\n");
notsuccess:		
		if(success)
		{
				if(!isword(*(p)))
				{
						//printf("OK!!\n");
					return p;
				}
		}
	}
	return 0;
}

int read(char*in)
{
	static int c=0;
	
	FILE *filein;
	char tmp[1000];
	strcpy(input[c].name,in);
	/*char*p=in;
	char*k=input[c].name;	
	while(*p!=0)
	{
		*k=*p;
		k++;p++;
		
	}*/
	//printf("-%s-\n",input[c].name);
	filein=fopen(in,"r");
	while(fgets(tmp,1000,filein)!=NULL)
	{
		if(search("#STARTLINK#",11,tmp))
		{
			
			while(fgets(tmp,1000,filein)!=NULL)
			{
				//if(search("#ENDLINK#",9,tmp)){printf("fuck!!");}
				if(search("#ENDLINK#",9,tmp)==0)
				{
					
					//printf("%s\n",tmp);
					input[c].lout++;
					//printf("%s OK!!\n",tmp);
					int k=atoi(tmp);
					input[k-1].lin[input[k-1].lincount]=c;
					input[k-1].lincount++;
					
				}
				else goto theend;
			}
		}
	}
	//printf("fuck!!");
theend:
	c++;
	return c;
}

void coculatepr()
{
	
	for(int i=0;i<5;i++)
	{
		double tmp[300];
		for(int j=0;j<fnumber;j++)
		{
			double part=0.15;
			//printf("now is %d",j);
			for(int k=0;k<input[j].lincount;k++)
			{
				//printf("[%d] ",k);
				part=part+0.85*(input[input[j].lin[k]].pr/input[input[j].lin[k]].lout);
			}
			tmp[j]=part;
			//printf("\n");
		}
		for(int l=0;l<fnumber;l++)input[l].pr=tmp[l];
	}
}
int filesearch(char*kw,int l)
{
	int max=0;
	for(int i=0;i<fnumber;i++)
	{
		
		char tmp[1000];
		FILE*f=fopen(input[i].name,"r");
		while(fgets(tmp,1000,f)!=NULL)
		{
			//printf("start[%d]!\n",i);
			char*p=tmp;
			while(p=search(kw,l,p),p!=0)
			{
				//printf("[%d]%s\n",i,p);
				input[i].f++;
			}
		}
		if(max<input[i].f)max=input[i].f;
	}
	return max;
}
void printans(int max,int l,char*key)
{
	
	FILE *output=fopen("output.html","w");
	//printf("OK!! ");
	int count=1;
	fprintf(output,"<html>");
	fprintf(output,"<head>");
	fprintf(output,"<title>output</title>");
	fprintf(output,"</head>");
	fprintf(output,"<body>");
	int i=0;
		while(input[s[i]].f!=0)
		{
			int j=s[i];
				FILE*f=fopen(input[j].name,"r");
				char tmp[1000];
				char *p=0,*t=0;
				while(fgets(tmp,1000,f)!=NULL)
				{
					
					p=search(key,l,tmp);
					if(p!=0)
					{
						t=tmp;
						p=p-l;
						break;
					}
				}
				fprintf(output,"<p>%d. <a href='%s'>%s</a><br/>",count,input[j].name,input[j].name);
				fprintf(output,"...");
				while(t!=p)
				{
					fprintf(output,"%c",*t);
					t++;
				}
				fprintf(output,"<font color='red'>");
				
				while(t!=p+l)
				{
					fprintf(output,"%c",*t);
					t++;
				}
				
				fprintf(output,"</font>");
			
					fprintf(output,"%s",t);
				
				printf("OK!");
				
				fprintf(output,"...<br/>");
				fprintf(output,"frequency:<font color='blue'>%d</font> pagerank:<font color='red'>%lf</font>",input[j].f,input[j].pr);
				fprintf(output,"</p>");
				count++;
			i++;
			
		}
			
	
	fprintf(output,"</body>");
	fprintf(output,"</html>");
}
void sort()
{
	
	for(int i=0;i<fnumber;i++)
	{
		s[i]=i;
	}
	for(int i=0;i<fnumber;i++)
	{
		printf("[%d] ",s[i]);
	}
	printf("\n");
	for(int i=fnumber-1;i>0;i--)
	{
		for(int j=0;j<i;j++)
		{
			if(input[s[j]].pr<input[s[j+1]].pr)
			{
				int tmp=s[j];s[j]=s[j+1];s[j+1]=tmp;
			}
		}
	}
	for(int i=0;i<fnumber;i++)
	{
		printf("[%d] ",s[i]);
	}
	printf("\n");
	for(int i=fnumber-1;i>0;i--)
	{
		for(int j=0;j<i;j++)
		{
			if(input[s[j]].f<input[s[j+1]].f)
			{
				
				int tmp=s[j];
				s[j]=s[j+1];
				s[j+1]=tmp;
			}
		}
	}
	for(int i=0;i<fnumber;i++)
	{
		printf("[%d] ",s[i]);
	}
	printf("\n");
	
}
int main()
{
	
	FILE *flist;
	char tmp[100];
	char intmp[100];
	flist=fopen("filelist.txt","r");
	
	while(fscanf(flist,"%s",tmp)!=EOF)
	{
		fnumber=read(tmp);
	}
	
	coculatepr();
	//filesearch("Cavaliers",9);
	scanf("%s",intmp);
	int l=0,max;
	char*p=intmp;
	while(*p!='\0')
	{
		p++;
		l++;
	}
	//printf("[%s][%d]",intmp,l);
	max=filesearch(intmp,l);
	sort();

	printans(max,l,intmp);
	
//system("output.html");
//	search();
}
