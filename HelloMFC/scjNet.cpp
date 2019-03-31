
#include "stdafx.h"
#include <mmsystem.h> 
#include "scjNet.h"
#include "memory.h"


//#define MYDEBUG

#define NEWNET

//SHIP vsl[SHIPMAX];

SHIP *vsl=NULL;

class scjNet;

scjSocket::scjSocket(scjNet *p)
{
	pOwner=p;
	CanSend=TRUE;
}

void scjSocket::OnReceive(int nErrorCode)
{
	pOwner->Receive(this);
}

void scjSocket::OnConnect( int nErrorCode)
{
	AfxMessageBox("OnConnect");
}

void scjSocket::OnAccept( int nErrorCode)
{
	pOwner->Accept();
}

void scjSocket::OnClose( int nErrorCode)
{
	pOwner->Close(sockID);
}

void scjSocket::OnSend(int nErrorCode)
{
//	AfxMessageBox("Sent");
}
scjNet::scjNet()
{
	int i;
	strm=NULL;
	SendAll=1;
	strm=fopen("netrec","w");
	if(!vsl) vsl=new SHIP[SHIPMAX];
	memset(vsl, 0, sizeof(SHIP)*SHIPMAX);
	DataSize=(SHIPMAX+16)*sizeof(SHIP);
	TmpBuf=new char[DataSize];
	RecvBuf=new char[(CLIENTMAX+1)*128];
	for(i=0;i<CLIENTMAX;i++){
		StrRecv[i]=&RecvBuf[i*128];
		StrRecv[i][0]=0;
	}
	for(i=0;i<CLIENTMAX;i++) psockRecv[i]=NULL;
	ShipRecvCnt=0;
	m_nOutId=FIRSTID;
	Running=0;
	TimeSent=0;	TimeGot=0; TimeDiff=99999999;
	memset(&EngPk,0,sizeof(ENGPK));
	strncpy(EngPk.pmk,"ENGPK",5);
}

scjNet::scjNet(CWnd *pp,int idn,char *svrAddr,int ptNum)
{
	char s[10];
	strm=NULL;
	idNum=idn;
	SendAll=1;
	if(!vsl) vsl=new SHIP[SHIPMAX];
	memset(vsl, 0, sizeof(SHIP)*SHIPMAX);
	DataSize=(SHIPMAX+16)*sizeof(SHIP);
	TmpBuf=new char[DataSize];
	RecvBuf=new char[(CLIENTMAX+1)*128];
	for(int i=0;i<CLIENTMAX;i++){
		StrRecv[i]=&RecvBuf[i*128];
		StrRecv[i][0]=0;
	}
	for(i=0;i<CLIENTMAX;i++) psockRecv[i]=NULL;
	ShipRecvCnt=0;
	pParent=pp;
	if(idNum<0 || idNum>CLIENTMAX) idNum=0;
	sprintf(s,"%d:",idNum);
	idStr=s;
	clientNum=idNum;
	strcpy((char*)SvrAddr,svrAddr);
	PortNum=ptNum;
	Create(pp, idNum, svrAddr, ptNum);
//	fprintf(strm,"vsl ptr=%lp",vsl);
	m_nOutId=FIRSTID;
	Running=0;
	TimeSent=0;	TimeGot=0; TimeDiff=99999999;
	memset(&EngPk,0,sizeof(ENGPK));
	strncpy(EngPk.pmk,"ENGPK",5);
}

scjNet::~scjNet()
{
	if(strm)fclose(strm);
	if(psockServer)delete psockServer;	
	if(psockClient)delete psockClient;	
	for(i=0;i<CLIENTMAX;i++) if(psockRecv[i]) delete psockRecv[i];
	if(vsl) delete [] vsl;
	vsl=NULL;
	delete [] TmpBuf;
	delete [] RecvBuf;
}

void scjNet::Create()
{
//	Create(pParent, clientNum, SvrAddr, PortNum);
	CString name;
	UINT npt;
//	LPCTSTR pc;
	char pc[40];
	BOOL b;
	char s[10];
	int i1,i2,i3,i4;
//	psockServer=NULL;	
	if(!psockClient){
		psockClient=new scjSocket(this);	
		psockClient->Create();
	}
	if(SvrAddr) b=psockClient->Connect(SvrAddr,700+PortNum);
	else b=0;
	if(!b){
//		AfxMessageBox("Network connection fail.");
		connected=0;
		return;
	}
	else connected=1;

	psockClient->GetSockName(name,npt);
	strcpy(pc,(LPCTSTR)name);
//	pc=(LPCTSTR)name;
	sscanf(pc,"%d.%d.%d.%d",&i1,&i2,&i3,&i4);
	psockClient->sockID=-i4;
//	psockClient->sockID=-atoi(&pc[12]);
#ifdef MYDEBUG
	AfxMessageBox(name);
#endif
	sprintf(s,"netrec%d",psockClient->sockID);
//	strm=fopen(s,"w");
 	fprintf(strm,"%s connected:%d, pParent=%p\n",pc,connected,pParent);
	for(i=0;i<CLIENTMAX;i++) psockRecv[i]=NULL;
	connect=0;
	s[0]='\255';s[1]='\0';
	Ack=s;
}

void scjNet::Create(CWnd *pp,int idNum,char *svrAddr,int ptNum)
{

	CString name;
	UINT npt;
//	PCTSTR pc;
	char pc[40];
	BOOL b;
	char s[10];
	int i1,i2,i3,i4;
	psockServer=NULL;	
	psockClient=new scjSocket(this);	
	psockClient->Create();
	if(svrAddr) b=psockClient->Connect(svrAddr,700+ptNum);
	else b=0;
	if(!b)
	{
		connected=0;
	}
	else connected=1;

	psockClient->GetSockName(name,npt);
//	pc=(LPCTSTR)name;
	strcpy(pc,(LPCTSTR)name);
	sscanf(pc,"%d.%d.%d.%d",&i1,&i2,&i3,&i4);
	psockClient->sockID=-i4;
//	psockClient->sockID=-atoi(&pc[12]);
#ifdef MYDEBUG
	AfxMessageBox(name);
#endif
	sprintf(s,"netrec%d",psockClient->sockID);
	strm=fopen(s,"w");
 	fprintf(strm,"%s connected:%d, pParent=%p\n",pc,connected,pParent);
	for(i=0;i<CLIENTMAX;i++) psockRecv[i]=NULL;
	connect=0;
	s[0]='\255';s[1]='\0';
	Ack=s;
	if(!TmpBuf) AfxMessageBox("Here");
}

scjNet::scjNet(CWnd *pp,int ptNum)
{
char s[10];
	strm=NULL;
	SendAll=1;
	if(!vsl) vsl=new SHIP[SHIPMAX];
	DataSize=(SHIPMAX+16)*sizeof(SHIP);
	TmpBuf=new char[DataSize];
	RecvBuf=new char[(CLIENTMAX+1)*128];
	for(i=0;i<CLIENTMAX;i++){
		StrRecv[i]=&RecvBuf[i*128];
		StrRecv[i][0]=0;
	}
	pParent=pp;
	clientNum=-1;
	psockClient=NULL;	
	psockServer=new scjSocket(this);	
	psockServer->Create(700+ptNum);
	psockServer->Listen();
	sprintf(s,"netrec");
	strm=fopen(s,"w");
	fprintf(strm,"Server ready.\n");
	for(i=0;i<CLIENTMAX;i++) psockRecv[i]=NULL;
	connect=0;
	s[0]='\255';s[1]='\0';
	Ack=s;
	m_nOutId=FIRSTID;
	Running=0;
	TimeSent=0;	TimeGot=0; TimeDiff=99999999;
	memset(&EngPk,0,sizeof(ENGPK));
	strncpy(EngPk.pmk,"ENGPK",5);
}


int scjNet::GetShipData(long *st,int md)
{
	if(TimeSent==TimeGot) return 0;
	*st=TimeSent+TimeDiff;
	TimeGot=TimeSent;
	if(!md){
//		if(vsl[SHIPMAX-2].v>-100.0 && vsl[SHIPMAX-2].v<100.0)
		memcpy((char *)(&vsl[0]),(char *)(&vsl[SHIPMAX-2]),sizeof(SHIP));
	}
	return vsl[SHIPMAX-3].act;
}

void scjNet::SpecMsg()
{
	long t1,t2,t;
	switch(StrRecv[0][1]){
	case 'C':
		t1=timeGetTime(); t2=atol(&StrRecv[0][2]);
		TimeDiff=99999999;
	//	fprintf(strm,"TimeDiff=(%d-%d)=%d\n",t1,t2,TimeDiff);
		break;
	case 'T':
		t1=timeGetTime(); t2=atol(&StrRecv[0][2]);
		t=t1-t2;
		if(TimeDiff>t){TimeDiff=t;
			fprintf(strm,"t=(%d-%d)=%d,TimeDiff=%d\n",t1,t2,t,TimeDiff);
		}
		break;
	default:;
	}
}

int scjNet::SendStr(LPSTR s)
{
//	if(!psockClient) return 0;
	if(!connected) return -1;
//	while(psockClient->IsBlocking());
//	if(!psockClient->CanSend) return 0;
//CString ss=idStr+s;
	char cc[200];
	int len;
#if defined NEWNET
	sprintf(cc,"%s",s);
	len=strlen(cc);
	Pack((unsigned char *)cc,len,0);
#else
	sprintf((char *)OutStr,"%s",(LPCTSTR)s);
#endif
	psockClient->Send(OutStr,strlen((char *)OutStr));
//	psockClient->CanSend=FALSE;
	return 1;
}

int scjNet::SendStr2All(LPSTR s)
{
	char cc[200];
	int len,d=0,n;
	for(n=1;n<21;n++){
		if(!psockRecv[n]) continue;
		sprintf(cc,"%s",(LPCTSTR)s);
		len=strlen(cc);
		Pack((unsigned char *)cc,len,0);
		psockRecv[n]->Send(OutStr,strlen((char *)OutStr));
		d++;
	}
	return d;
}

int scjNet::SendStr(int n, LPSTR s)
{
	for(i=1;i<CLIENTMAX;i++){
		if((psockRecv[i])&&(psockRecv[i]->sockID==n)) break;
	}
	if(i==CLIENTMAX) return 0;
//	if(!psockRecv[n]) return 0;
	char cc[200];
	int len;
//	CString outs;
#if defined NEWNET
	sprintf(cc,"%s",(LPCTSTR)s);
	len=strlen(cc);
	Pack((unsigned char *)cc,len,0);
#else
	sprintf((char *)OutStr,"%s",(LPCTSTR)s);
#endif
//	outs=OutStr;
//	if(!psockRecv[i]->CanSend) return 0;
	psockRecv[i]->Send(OutStr,strlen((char *)OutStr));
//	psockRecv[i]->CanSend=FALSE;
	return 1;
}
/*
int scjNet::SendShip()
{
CString s="VPACK";
int num=1;
	if(!connected) return -1;
CSocketFile file(psockClient);
	CArchive arOut(&file,CArchive::store);
	arOut<<s;
	arOut<<num;
		arOut<<-psockClient->sockID;
		arOut<<vsl[0].act;
		arOut<<vsl[0].x;
		arOut<<vsl[0].y;
		arOut<<vsl[0].z;
		arOut<<vsl[0].c;
		arOut<<vsl[0].v;
		arOut<<vsl[0].r;
		arOut<<vsl[0].gv;
		arOut<<vsl[0].gc;
	arOut.Flush();
	return 1;
}
*/

int scjNet::SendEngPk()
{
	if(!psockClient) return 0;
	psockClient->Send(&EngPk,sizeof(ENGPK));
	return 1;
}

int scjNet::SendShip(int n)
{
int mnum=0,cnt=1,i;
SHIP *sp;
	sp=(SHIP *)TmpBuf;
	i=0;	
	sp[cnt]=vsl[i];
	sp[cnt].act=i;
	cnt++;
	for(i=1;i<SHIPMAX-10;i++){
		if(!vsl[i].act) continue;
//		sp=(SHIP *)(&TmpBuf[cnt*sizeof(SHIP)]);
		sp[cnt]=vsl[i];
		sp[cnt].act=i;
		cnt++;
	}
	sprintf(TmpBuf,"VPACK%ld,%d",timeGetTime(),cnt);
	for(i=1;i<CLIENTMAX;i++){
		if((psockRecv[i])&&(psockRecv[i]->sockID==n)) break;
	}
	if(i==CLIENTMAX) return 0;
	psockRecv[i]->Send(TmpBuf,(SHIPMAX-10)*sizeof(SHIP));
	return 1;
}

int scjNet::SendShip2All()
{
int n,mnum=0,cnt=1,i;
SHIP *sp;
	sp=(SHIP *)TmpBuf;
	i=0;	
	sp[cnt]=vsl[i];
	sp[cnt].act=i;
	cnt++;
	j++;
	for(i=1; i < SHIPMAX-10;i++)
	{
		if(!vsl[i].act) continue;
//		sp=(SHIP *)(&TmpBuf[cnt*sizeof(SHIP)]);
		sp[cnt]=vsl[i];
		sp[cnt].act=i;
		cnt++;
	}
	sprintf(TmpBuf,"VPACK%ld,%d",timeGetTime(),cnt);
	for(n=1;n<21;n++){
		if(!psockRecv[n]) continue;
		if(SendAll)	
			psockRecv[n]->Send(TmpBuf,cnt*sizeof(SHIP));
		else
		{
			if(psockRecv[n]->sockID>60) 
				psockRecv[n]->Send(TmpBuf,cnt*sizeof(SHIP));
			else
			{
				if(j&0x0f) continue;
				psockRecv[n]->Send(TmpBuf,cnt*sizeof(SHIP));
			}
		}
		mnum++;
	}
	return mnum;
}
int scjNet::SendOSShip2All()
{
int n,mnum=0,cnt=1,i;
SHIP *sp;
	sp=(SHIP *)TmpBuf;
	i=0;	
	sp[cnt]=vsl[i];
	sp[cnt].act=i;
	cnt++;
	j++;
	for(i = 0;i < 20;i++){
		if(!vsl[i].act) continue;
//		sp=(SHIP *)(&TmpBuf[cnt*sizeof(SHIP)]);
		sp[cnt]=vsl[i];
		sp[cnt].act=i;
		cnt++;
	}
	sprintf(TmpBuf,"VPACK%ld,%d",timeGetTime(),cnt);
	for(n=1;n<21;n++){
		if(!psockRecv[n]) continue;
		if(SendAll)	
			psockRecv[n]->Send(TmpBuf,cnt*sizeof(SHIP));
		else
		{
			if(psockRecv[n]->sockID>60) 
				psockRecv[n]->Send(TmpBuf,cnt*sizeof(SHIP));
			else
			{
				if(j&0x0f) continue;
				psockRecv[n]->Send(TmpBuf,cnt*sizeof(SHIP));
			}
		}
		mnum++;
	}
	return mnum;
}


void scjNet::RecvShip(int cnt)
{
int i,tt,act,k;
SHIP *vp=(SHIP *)TmpBuf;
	vsl[SHIPMAX-2]=vp[1];
	vsl[SHIPMAX-3].act=cnt;
	for(i=2;i<cnt;i++){
		k=vp[i].act; if(!k) break;
//		vp[i].act=vsl[k].act;
		vsl[k]=vp[i];
	}
}

/*
int scjNet::SendShip(int n)
{
int i,mnum=0;
	for(i=1;i<CLIENTMAX;i++){
		if((psockRecv[i])&&(psockRecv[i]->sockID==n)) break;
	}
	if(i==CLIENTMAX) return 0;
//	if(!psockRecv[n]) return 0;
//	sn=i;
	memcpy(&TmpBuf[sizeof(SHIP)],(char *)(&vsl[0]), (SHIPMAX-10)*sizeof(SHIP));
	sprintf(TmpBuf,"VPACK%ld",timeGetTime());
	psockRecv[i]->Send(TmpBuf,(SHIPMAX-10)*sizeof(SHIP));
	return 1;
}

int scjNet::SendShip2All()
{
int n,mnum=0;
	memcpy(&TmpBuf[sizeof(SHIP)],(char *)(vsl), (SHIPMAX-10)*sizeof(SHIP));
	sprintf(TmpBuf,"VPACK%ld",timeGetTime());
	for(n=1;n<21;n++){
		if(!psockRecv[n]) continue;
		psockRecv[n]->Send(TmpBuf,(SHIPMAX-10)*sizeof(SHIP));
		mnum++;
	}
	return mnum;
}



void scjNet::RecvShip(int len)
{
int i,tt,act,k;
SHIP *vp=(SHIP *)TmpBuf;
	if(len<sizeof(SHIP)+sizeof(SHIP)) return;
//	fprintf(strm,"%12s\n",TmpBuf);
	TimeSent=atoi(&TmpBuf[5]);
//	memcpy((char *)(&vsl[1]),&TmpBuf[sizeof(SHIP)+sizeof(SHIP)], len-sizeof(SHIP)*2);
	memcpy((char *)(&vsl[1]),&TmpBuf[sizeof(SHIP)+sizeof(SHIP)], (SHIPMAX-10)*sizeof(SHIP));
	memcpy((char *)(&vsl[SHIPMAX-3]),TmpBuf,sizeof(SHIP)*2);
	vsl[SHIPMAX-3].act=len;
}
*/
/*
void scjNet::RecvShip(CArchive & arIn,int num)
{
int i,tt,act;
	for(i=0;i<num;i++){
		arIn>>act;
		if(act<1 || act>=SHIPMAX) break; 
		arIn>>tt;//vsl[act].act;
		arIn>>vsl[act].x;
		arIn>>vsl[act].y;
		arIn>>vsl[act].z;
		arIn>>vsl[act].c;
		arIn>>vsl[act].v;
		arIn>>vsl[act].r;
		arIn>>vsl[act].gv;
		arIn>>vsl[act].gc;
	}
}
*/

int scjNet::Accept()
{
char s[40];
LPCTSTR pc;
CString name;
UINT npt=0;
SOCKADDR sa;
int i1,i2,i3,i4;
int sal=sizeof(SOCKADDR); 
	connect++;
	for (i=1;i<CLIENTMAX;i++)
		if(!psockRecv[i]) break;
//	i=0;
	psockRecv[i]=new scjSocket(this);
	psockServer->Accept(*psockRecv[i],&sa,&sal);
	psockRecv[i]->GetPeerName(name,npt);
	pc=(LPCTSTR)name;
	sscanf(name,"%d.%d.%d.%d",&i1,&i2,&i3,&i4);
//	psockRecv[i]->sockID=atoi(&pc[12]);
	psockRecv[i]->sockID=i4;
	if(psockRecv[i]->sockID>=200){
		AfxMessageBox("Bad Ownship Id");
		return 0;
	}
	sprintf(s,"CONNECTED:%d\n",psockRecv[i]->sockID);
//	if(psockRecv[psockRecv[i]->sockID]) delete psockRecv[psockRecv[i]->sockID];
//	psockRecv[psockRecv[i]->sockID]=psockRecv[i];
	strcpy(StrRecv[0],s);
	pParent->PostMessage(SCJ_NETRECV,0,(long)psockRecv[i]->sockID);
#ifdef MYDEBUG
	AfxMessageBox(s);
#endif
	fprintf(strm,"%s check in\n",pc);

	sprintf(s,"@T%d\n",timeGetTime());
//	psockRecv[i]->Send(s,strlen(s));
	psockRecv[i]->Send(s,12);

	return connect;
}

int scjNet::TimeSync0()
{
	char cc[200];
	int len,d=0,n,i;
	long t0=timeGetTime();
	for(n=1;n<21;n++){
		if(!psockRecv[n]) continue;
		sprintf(cc,"@C%ld\n",timeGetTime());
		psockRecv[n]->Send(cc,12);
	}
	for(i=0;i<1;i++){
		while((timeGetTime()-t0)<100);
		t0=timeGetTime();			
		for(n=1;n<21;n++){
			if(!psockRecv[n]) continue;
			sprintf(cc,"@T%ld\n",timeGetTime());
			psockRecv[n]->Send(cc,12);
		}
	}
	return d;
}

int scjNet::TimeSync()
{
	char cc[200];
	int len,d=0,n,i;
	long t0=timeGetTime();
	for(n=1;n<21;n++){
		if(!psockRecv[n]) continue;
		sprintf(cc,"@T%ld\n",timeGetTime());
		psockRecv[n]->Send(cc,12);
	}
	return d;
}

int scjNet::Close(int id)
{
char ss[40];
int i;
	if(id<0){
		delete psockClient;
		psockClient=NULL;
		for(i=1;i<CLIENTMAX;i++){
			if(StrRecv[i][0]==0) break;
		}
		if(i==CLIENTMAX) i=0;
		strcpy(StrRecv[i],"CLOSED");
		connected=0;
		pParent->PostMessage(SCJ_NETRECV,i,id);
		fprintf(strm,"Server closed.\n");
		return -id;
	}
	for(i=1;i<CLIENTMAX;i++){
		if(psockRecv[i]) if(psockRecv[i]->sockID==id) break;
	}
	if(i==CLIENTMAX) return 0;
//	i=id;
	if(psockRecv[i]) delete psockRecv[i];
	psockRecv[i]=NULL;
	connect--;
	sprintf(ss,"CLOSED:%d\n",id);
	fprintf(strm,"%s\n",ss);
	for(i=1;i<CLIENTMAX;i++){
		if(StrRecv[i][0]==0) break;
	}
	strcpy(StrRecv[i],ss);
	pParent->PostMessage(SCJ_NETRECV,i,(long)id);
	return 1;
}

int scjNet::UnPackBuf( unsigned char *pData, int len)
{
static unsigned char *ptr,*ptr0;
static int len2;
unsigned long t1;
int nSize,cnt,t;
	if (pData){
		ptr0=pData;
		ptr=ptr0;
		len2=len;
	}
	else ptr0=ptr;

	if(!strncmp((char *)ptr0,"CmNet",5)){
		MESSAGE *pInMessage= (MESSAGE *) ptr0;
		nSize = atoi( pInMessage->DataSize );
		if(len2<nSize){len2=0; return 0;}
		if( CalcChecksum( &ptr0[sizeof(MESSAGE)-sizeof(char *)], nSize ) != (unsigned short) atoi( pInMessage->Checksum ) ) return(0);
		ptr=ptr0+sizeof(MESSAGE)-sizeof(char *)+(nSize);
		if( nSize != 0 && pInMessage->pData != NULL ){
			memmove( OutStr, &ptr0[sizeof(MESSAGE)-sizeof(char *)], nSize );
			OutStr[nSize]=0;
	//		Tianshu((char*)pData,*nSize);
		}
		len2-=(sizeof(MESSAGE)-sizeof(char *)+(nSize));
		return 1;
	}
	if(!strncmp((char *)ptr0,"VPACK",5)){
		sscanf(TmpBuf,"VPACK%ld,%d",&TimeSent,&cnt);
		if(!TimeSent){len2=0; return 0;}
		t1=timeGetTime();
		t=t1-TimeSent; 
		if(TimeDiff>t){TimeDiff=t;			
			fprintf(strm,"t=(%d-%d)=%d,TimeDiff=%d\n",t1,TimeSent,t,TimeDiff);
		}
		nSize=cnt*sizeof(SHIP);
		if(len2<nSize) {len2=0; return 0;}
		ptr=ptr0+(nSize);
		if(TimeSent>TimeGot) RecvShip(cnt);
		len2-=nSize;
		return 2;
	}
	if(!strncmp((char *)ptr0,"ENGPK",5)){
		nSize=sizeof(ENGPK);
		if(len2<nSize) {len2=0; return 0;}
		ptr=ptr0+(nSize);
		len2-=nSize;
		return 3;
	}
	if(ptr0[0]=='@'){
		nSize=12;
		if(len2<nSize) {len2=0; return 0;}
		memcpy(StrRecv[0],ptr0,12);
		StrRecv[0][12]=0;
		ptr=ptr0+(nSize);
		len2-=nSize;
		return 4;
	}
	return( 0 );
}

int scjNet::Receive(scjSocket *psockRecv)
{
static cnt;
CString s;
int nSize,num,i,len,more=0;
char cc[50];
	len=psockRecv->Receive(TmpBuf,DataSize);
	if(len<12) return 0;
//	strncpy(cc,TmpBuf,20);cc[20]=0;	fprintf(strm,"%d:%s\n",psockRecv->sockID,cc);
	more=UnPackBuf((unsigned char *)TmpBuf,len);
	while(more){
		switch(more){
		case 1:
			for(i=1;i<CLIENTMAX;i++){
				if(StrRecv[i][0]==0) break;
			}
			if(i==CLIENTMAX){
				fprintf(strm,"Net buffer full for: %s\n",OutStr);
				return -1;
			}
			memcpy(StrRecv[i],(char *)OutStr, 120);
			pParent->PostMessage(SCJ_NETRECV,i,(long)psockRecv->sockID);
			break;
		case 3:
			memcpy(&EngPk,TmpBuf,sizeof(ENGPK));
			for(i=1;i<CLIENTMAX;i++){
				if(StrRecv[i][0]==0) break;
			}
			if(i==CLIENTMAX){
				fprintf(strm,"Net buffer full for EngPk\n");
				return -1;
			}
			strcpy(StrRecv[i],"L0\n");
			pParent->PostMessage(SCJ_NETRECV,i,(long)psockRecv->sockID);
			break;
		case 4:
			SpecMsg();
			break;
		default:;
		}
		more=UnPackBuf(NULL);
	}
	return 1;
}

/*
int scjNet::Receive(scjSocket *psockRecv)
{
static cnt;
CString s;
int nSize,num,i,len,more=0;
char cc[50];
	len=psockRecv->Receive(TmpBuf,12);
	if(len<12) return 0;
	if(TmpBuf[0]=='@'){
		TmpBuf[len]=0;
		SpecMsg();
		return 2;
	}
	if(!strncmp(TmpBuf,"VPACK",5)){
		i=DataSize-12;
		len=psockRecv->Receive(&TmpBuf[12],i)+12;
		TmpBuf[len]=0;
		RecvShip(len);
		return 2;
	}
	if(!strncmp(TmpBuf,"ENGPK",5)){
		i=sizeof(ENGPK)-12;
		len=psockRecv->Receive(&TmpBuf[12],i)+12;
		TmpBuf[len]=0;
		memcpy(&EngPk,TmpBuf,sizeof(ENGPK));
		for(i=1;i<CLIENTMAX;i++){
			if(StrRecv[i][0]==0) break;
		}
		if(i==CLIENTMAX){
			fprintf(strm,"Net buffer full for EngPk\n");
			return -1;
		}
		strcpy(StrRecv[i],"L0\n");
		pParent->PostMessage(SCJ_NETRECV,i,(long)psockRecv->sockID);
		return 2;
	}
	if(!strncmp(TmpBuf,"CmNet",5)){
		nSize=atoi(&TmpBuf[6]);
		i=sizeof(MESSAGE)-sizeof(char *)+nSize-12;
		len=psockRecv->Receive(&TmpBuf[12],i)+12;
		TmpBuf[len]=0;
		more=UnPack((unsigned char *)TmpBuf,&len);
		for(i=1;i<CLIENTMAX;i++){
			if(StrRecv[i][0]==0) break;
		}
		if(i==CLIENTMAX){
			fprintf(strm,"Net buffer full for: %s\n",OutStr);
			return -1;
		}
		memcpy(StrRecv[i],(char *)OutStr, 120);
		pParent->PostMessage(SCJ_NETRECV,i,(long)psockRecv->sockID);
		return 1;
	}
//	fprintf(strm,"Unknown:%12s\n",TmpBuf);
	psockRecv->Receive(TmpBuf,DataSize);
	return 0;
}
*/

void scjNet::Tianshu(char *str)
{
	int len=strlen(str);
	Tianshu(str, len);
}
void scjNet::Tianshu(char *str,int len)
{
	str[len]=0;
	len &=0x7f;
	for(int i=0;i<len;i++) str[i]^=0x8a; //pScjCode[i];
}
/*
static char *ptr,*ptr0;
     if (str) ptr0=str;
     else ptr0=ptr;
     ptr=strstr(ptr0,token);
     if(ptr){ptr+=strlen(token);}
     return ptr;
*/

int scjNet::UnPack( unsigned char *pData, int *nSize)
{
static unsigned char *ptr,*ptr0;
     if (pData) ptr0=pData;
     else ptr0=ptr;
    if(strncmp((char *)ptr0,"CmNet",5))	return( 0 );
	MESSAGE *pInMessage= (MESSAGE *) ptr0;
	*nSize = atoi( pInMessage->DataSize );
	if( CalcChecksum( &ptr0[sizeof(MESSAGE)-sizeof(char *)], *nSize ) != (unsigned short) atoi( pInMessage->Checksum ) ) return(0);
	ptr=ptr0+sizeof(MESSAGE)-sizeof(char *)+(*nSize);
	if( *nSize != 0 && pInMessage->pData != NULL ){
		memmove( OutStr, &ptr0[sizeof(MESSAGE)-sizeof(char *)], *nSize );
		OutStr[*nSize]=0;
//		Tianshu((char*)pData,*nSize);
	}
	else return 0;
	return 1;
//	if(!strncmp((char *)ptr,"CmNet",5))	return( 1 );
//	else return 0;
}

BOOL scjNet::Pack( void *pMsgData, int nSize, int nType)
{
	MESSAGE *pMessage;
	unsigned char *pucBuffer;
//	char *pMessageData=new char[nSize+8];
	char *pMessageData=(char *)malloc(nSize+8+256);
	if(  pMessageData== NULL ) return( FALSE );
	memset(pMessageData, 0, nSize + 8 );
	memcpy(pMessageData,pMsgData,nSize);
//	Tianshu((char*)pMessageData,nSize);
//	pucBuffer = new unsigned char [sizeof(MESSAGE)+nSize+8];
	pucBuffer = (unsigned char *) malloc(sizeof(MESSAGE)+nSize+8+256);
	if( pucBuffer == NULL ) return( FALSE );

	memset( pucBuffer, 0, sizeof( MESSAGE ) + nSize + 8 +256 );
	pMessage = (MESSAGE *) pucBuffer;
	wsprintf( pMessage->DataSize, "%05u", nSize );
	pMessage->DataSize[5] = ' ';
	wsprintf( pMessage->Checksum, "%05u", CalcChecksum( (unsigned char *) pMessageData, nSize ) );
	pMessage->Checksum[5] = ' ';
	wsprintf( pMessage->Id, "%05u", m_nOutId++ );
	pMessage->Id[5] = ' ';
	if( m_nOutId >= LASTID ) m_nOutId = FIRSTID;
	wsprintf( pMessage->Type, "CmNet");
//	wsprintf( pMessage->Type, "%05u",nType);
	pMessage->Type[5] = ' ';
	memcpy( pMessage->Status, "00000 ", 6 );
	if( nSize != 0 ){
		memcpy( &pucBuffer[sizeof(MESSAGE)-sizeof(char *)], pMessageData, nSize );
		memcpy( OutStr,pucBuffer,sizeof(MESSAGE)-sizeof(char *)+nSize );
//		OutStr[pucBuffer,sizeof(MESSAGE)-sizeof(char *)+nSize]=0;
		OutStr[sizeof(MESSAGE)-sizeof(char *)+nSize]=0;
	}
//	delete [] pucBuffer;
//	delete [] pMessageData;
	free(pucBuffer);
	free(pMessageData);
	return( TRUE );
}

unsigned short scjNet::CalcChecksum( unsigned char *pData, int nSize )
{
	unsigned short Checksum = 0, t;
	int i;

	for( i=0; i<nSize; i++ ){
		t = (unsigned short) pData[i];
		t &= 0x00ff;
		Checksum += t;
		}
	return( Checksum );

}

