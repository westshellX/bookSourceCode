#include "stdafx.h"
#include <mmsystem.h> 
#include "string.h"
#include "math.h"
#include <conio.h>
#include "scjclass.h"
char classtmp[100];

extern FILE *DebugStrm;

CDlyAct::CDlyAct()
{
	t0=0.0;
	delay_t=0.0;length_t=0.0; ov=0;
}

void CDlyAct::Set(double dt,double lt)
{
//    t0=timeGetTime();
	t0=GetTickCount();
	delay_t=dt;
	length_t=delay_t+lt;
	ov=2;
}

int CDlyAct::Check(double t)
{
	double tt=t-t0;
	if(tt>length_t){
		if(ov){ov--; return 2;}
		else return 0;
	}
	if(tt>delay_t){
		if(ov==2){ ov--;return 1;}
		else return 0;
	}
	return 0;
}

ByteBuf::ByteBuf(unsigned int sz)
{
	head=0;
	tail=0;
	Buf=new char[sz];
	if(Buf==NULL) AfxMessageBox("Buf alloc Failed");
	size=sz;
}

void ByteBuf::Put(char c)
{
	Buf[head++]=c;
	if(head==size) head=0;
}

char ByteBuf::Get(char *pc)
{
	if(tail==head){
		*pc=0;
		return -1;
	}
	*pc=Buf[tail++];
	if(tail==size) tail=0;
	return *pc;
}

int ByteBuf::io_out(int pt)
{
	if(tail==head){
		return 0;
	}
	int cc=Buf[tail++];
	_outp(pt,cc);
	if(tail==size) tail=0;
	return cc;
}

int CCurveValue::SetCurve(char *fn,int pp)
{
	double intv,li,ui,lv,uv,tv,rn,cx;
	int i;
	FILE *strm;
	parts=pp;
	pValues=NULL;
	strm=fopen(fn,"r");
	if(!strm){
		Invalid=1;
		return 0;
	}
	Invalid=0;
	pValues=new double[parts+10];
	fscanf(strm,"%lf %lf\n",&LLimit,&tv);
	while(fscanf(strm,"%lf %lf\n",&ULimit,&tv)==2);
	Range=ULimit-LLimit;
	intv=Range/parts;
	fclose(strm);

	strm=fopen(fn,"r");
	fscanf(strm,"%lf %lf\n",&li,&lv);
	fscanf(strm,"%lf %lf\n",&ui,&uv);
	rn=uv-lv;
	pValues[0]=lv;
	cx=li;
	for(i=1;i<parts;i++){
		cx+=intv;
		while(cx>ui){
			li=ui; lv=uv;
			if(fscanf(strm,"%lf %lf\n",&ui,&uv)!=2) break;
			rn=uv-lv;
		}
		pValues[i]=lv+rn*(cx-li)/(ui-li);
//		fprintf(DebugStrm,"%d %.2lf %.2lf\n",i,cx,pValues[i]);
	}
	pValues[parts]=uv;
	fclose(strm);
	return parts;
}

CCurveValue::~CCurveValue()
{
	if(pValues) delete pValues;
}

double CCurveValue::GetValue(double xx,int md)
{
	double v,d;
	int i;
	if(Invalid) return 0.0;
	if(xx<=LLimit) return pValues[0];
	if(xx>=ULimit) return pValues[parts];
	d=parts*(xx-LLimit)/Range;
	if(md){
		i=(d+.5);
		v=pValues[i]; 
	}
	else{
		i=floor(d);
		v=pValues[i]+(pValues[i+1]-pValues[i])*(d-i);
	}
	
//	fprintf(DebugStrm,"%d %.2lf %.2lf\n",i,xx,v);

	return v;
}

#ifndef YING_EC
#include "navlib.hpp"
void CLine::Set(double x1,double y1,double x2,double y2)
{
	POLE pp;
	X1=x1;Y1=y1;X2=x2;Y1=y2;
	if(x2>x1){
		left=x1;
		right=x2;
	}
	else{
		left=x2;
		right=x1;
	}
	if(y2>y1){
		xytobd(x2-x1,y2-y1,&pp);
		top=y2,bottom=y1;
	}
	else{
		xytobd(x1-x2,y1-y2,&pp);
		top=y1,bottom=y2;
	}
	brg=pp.brg;
	if(y1==y2){A=0.0;B=1.0;C=-y1; rAApBB=1.0; return;}
	if(x1==x2){A=1.0;B=0.0;C=-x1; rAApBB=1.0; return;}
	A=(y2-y1)/(x2-x1); B=-1;C=-A*x1+y1;
	rAApBB=sqrt(A*A+B*B);
}

double CLine::DistTo(double x,double y)
{
	double dd=(A*x+B*y+C)/rAApBB;
	if(dd>=0) return dd;
	else return -dd;
}

int CLine::IsAt(double x,double y)
{
	if(x>left && x<right) return 1;
	if(y>bottom && y<top) return 1;
	return 0;
}

int CLine::IsPort(double x,double y)
{
	if(x<(left-0.2) || x>(right+0.2)) return 0;
	if(y<(bottom-0.2) || y>(top+0.2)) return 0;
	return 1;
}

void Light::Set(int L1st,int L2nd,int tt)
{
	if(L1st>100) L1st=100;
	if(L1st<-100) L1st=-100;
	if(L2nd>100) L2nd=100;
	if(L2nd<-100) L2nd=-100;
	if(L1st==L2nd) L1st--;
	if(tt<1) tt=1;
	iLight=L1st;
//	cTime=timer();
    cTime=timeGetTime();
	toTime=cTime+tt;
	toLight=L2nd;
	dTime=(double)tt/(double)(L2nd-L1st);
	if(dTime>0) dLight=1; else {dLight=-1;dTime=-dTime;}
}

int Light::Get(double tt)
{
int r=0;
    if(tt>toTime) return 0;
    while((tt-cTime)>dTime) {
        r++;
	iLight+=dLight;
	cTime+=dTime;
    }
    if(!r) return 0;
    return iLight;
}
#endif

#define STRSZ 128
#define BUFFNUM 32 
CMatFile::CMatFile(CWnd *pp, int ch)
{
//	CMatFile("MAP_NAME",1024);  can't just call like this!
	int i,exist=0;
	int *ip;
char fname[40],*cp;
	pParent=pp;
	Channel=ch;
	id=0;
	RecvPos=0;
//	for(i=0;i<BUFFNUM;i++) strRecv[i].Empty();
	if(Channel==0) strcpy(fname,"MAP_NAME");
	else sprintf(fname,"MAP_FILE%d",Channel);
	int cb=4096;
	hFileMap=CreateFileMapping((HANDLE) 0xffffffff,NULL, PAGE_READWRITE,0,cb,fname);
	if(!hFileMap) {AfxMessageBox("MatFile create error!"); return;}
	if(GetLastError()==ERROR_ALREADY_EXISTS){
		CloseHandle(hFileMap);
		hFileMap=OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE,FALSE,fname);
		if(!hFileMap) {AfxMessageBox("MatFile open error!"); return;}
		exist=1;
	}
	lpView=MapViewOfFile(hFileMap,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
	if(!lpView)AfxMessageBox("Can't map view!");
	cp=(char *)lpView;
	if(cb>4100){
		lpView1=&cp[4096]; 
		ip=(int *)lpView1;
		*ip=0;
		bufsize=cb-4100;
	}
	else{
		lpView1=NULL;
		bufsize=0;
	}
	if(!exist) strcpy((char *)lpView,"0,MatFile created.");
//	sprintf(classtmp,"%d",hFileMap);
}


CMatFile::CMatFile(CWnd *pp,char *fname,int cb)
{
	int i;
	int *ip;
	char *cp;
	pParent=pp;id=0;
	RecvPos=0;
//	for(i=0;i<BUFFNUM;i++) strRecv[i].Empty();
	if (cb<4096) cb=4096;
	hFileMap=CreateFileMapping((HANDLE) 0xffffffff,NULL, PAGE_READWRITE,0,cb+128,fname);
	if(!hFileMap) {AfxMessageBox("MatFile create error!"); return;}
	if(GetLastError()==ERROR_ALREADY_EXISTS){
		CloseHandle(hFileMap);
		hFileMap=OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE,FALSE,fname);
		if(!hFileMap) {AfxMessageBox("MatFile open error!"); return;}
	}
	lpView=MapViewOfFile(hFileMap,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
	if(!lpView)AfxMessageBox("Can't map view!");
	cp=(char *)lpView;
	if(cb>4100)
	{
		lpView1=&cp[4096]; 
		ip=(int *)lpView1;
		*ip=0;
		bufsize=cb-4100;
	}
	else{
		lpView1=NULL;
		bufsize=0;
	}
	strcpy((char *)lpView,"0,MatFile Recv.");
//	sprintf(classtmp,"%d",hFileMap);
//	AfxMessageBox(classtmp);
}

//extern FILE *DebugStrm;

void CMatFile::SendBuf(char *buf, int cb)
{
	int *ip=(int *)lpView1,*ti=(int *)(&lpView1[8]);
	if(!lpView1) return;
	if(cb>bufsize) cb=bufsize;
	memcpy(&lpView1[128],buf,cb);
	*ip=cb; *ti=timeGetTime();
}

int CMatFile::RecvBuf(char *buf)
{
	int cb,*ip=(int *)lpView1;
	if(!lpView1) return 0;
	cb=*ip;
	if(!cb) return 0;
	memcpy(buf,&lpView1[128],cb);
	*ip=0;
	return cb;
}

int CMatFile::RecvBuf(char *buf, unsigned long *time)
{
	int cb,*ip=(int *)lpView1;
	if(!lpView1) return 0;
	cb=*ip;
	if(!cb) return 0;
	memcpy(buf,&lpView1[128],cb);
	*ip=0;
	ip=(int *)(&lpView1[8]);
	*time=*ip;
	return cb;
}


void CMatFile::SendStr(char *strn)
{
	long i,j,ip,pos;
	if(!lpView) return;
	if(strlen(strn)<1) return;
	char *tp=(char *)lpView,*tp4=&tp[8];
//	char str[STRSZ];
	i=atoi(tp);
//	sscanf(tp,"%d",&i);
	if(i>=BUFFNUM){
		sprintf(tp,"%d",0);
		i=0;
	}
	while(i!=RecvPos){
		pos=(++RecvPos); if(pos>=BUFFNUM) pos=0;
//		strcpy(str,&tp4[pos<<7]);
		 
//		for(j=0;j<BUFFNUM;j++) if(strRecv[j].IsEmpty()) break;
//		if(j==BUFFNUM) j=0;
//		strRecv[pos]=str;
		pParent->PostMessage(SCJ_MATFILE,(Channel<<8)+(pos&0xff),(long)(&tp4[pos<<7]));
//		if(strlen(str)>0) pParent->PostMessage(SCJ_MATFILE,pos,0);
		RecvPos=pos;
	}
/*
	for(i=0;i<20;i++) if(tp[i]==','|| tp[i]==0) break;
		pParent->PostMessage(SCJ_MATFILE,0,(long)strRecv);
	}
*/	
//	pos=(RecvPos++)&(4096/STRSZ-1);
	pos=(++RecvPos); if(pos>=BUFFNUM) pos=0;
	sprintf(tp,"%d",pos);
	sprintf(&tp4[pos<<7],"%s",strn);
//	fprintf(DebugStrm,"%d:\n",pos);
//	fprintf(DebugStrm,&tp4[pos<<7]);
	RecvPos=pos;
}

void CMatFile::Check()
{
	if(!lpView) return;
	long i,j,pos;
	char *tp=(char *)lpView,*tp4=&tp[8];
	char str[STRSZ];
	i=atoi(tp);
//	sscanf(tp,"%d",&i);
	if(i==RecvPos) return;
	if(i>=BUFFNUM){
		sprintf(tp,"%d",0);
		i=0;
	}
	while(i!=RecvPos){
		pos=(++RecvPos); if(pos>=BUFFNUM) pos=0;
//		pos=(RecvPos++)&(4096/STRSZ-1);
//		strcpy(str,&tp4[pos<<7]);
//		for(j=0;j<BUFFNUM;j++) if(strRecv[j].IsEmpty()) break;
//		if(j==BUFFNUM){j=0; strRecv[j].Empty();}
//		strRecv[pos]=str;
		pParent->PostMessage(SCJ_MATFILE,(Channel<<8)+(pos&0xff),(long)(&tp4[pos<<7]));
//		if(strlen(str)>0) pParent->PostMessage(SCJ_MATFILE,pos,0l);
		RecvPos=pos;
	}
}

CMatFile::~CMatFile()
{
	UnmapViewOfFile(lpView);
	CloseHandle(hFileMap);
}


