#ifndef _SCJNET
#define _SCJNET

#include <afxsock.h>       
/*#include "MyMessage.h"  */     

class scjNet; 

#define CLIENTMAX 100



class scjSocket:public CSocket
{
protected:
	scjNet *pOwner;
public:

	virtual void OnSend(int);

	int sockID;

	BOOL CanSend;

	scjSocket(scjNet *);

	virtual void OnReceive(int);

	virtual void OnConnect( int nErrorCode );

	virtual void OnAccept( int nErrorCode );

	virtual void OnClose( int nErrorCode );
};

typedef struct {
	char pmk[6];
	int OsNo;

	int DrillMode;          // 1:  驾机合一； 2：机独立;  3:电独立；
	int DrillShape;         // 船型：1 2 3 4；
	int DrillSection;       // 部门； 1：机  2：电 
	int DrillItem;          // 项目； 1：基本 2：故障 3：考核

	float Pow1A;                //1#    安培表读数 
	float Pow1V;                //    伏特表读数 
	float Pow1MO;               //    兆欧表读数  
	float Pow1W;                //    功率表读数
	float Pow1CosP;             //    功率系数
	float Pow1Hz;               //    频率表读数 

	float Pow2A;                //2#   安培表读数 
	float Pow2V;                //    伏特表读数 
	float Pow2MO;               //    兆欧表读数  
	float Pow2W;                //    功率表读数
	float Pow2CosP;             //    功率系数
	float Pow2Hz;               //    频率表读数 

    bool bPow1Switch;             // 1号 主开关       1：开   0：关
	bool bPow1Station;            //    发电机组     1：启动 0：停止 

    bool bPow2Switch;            //2号 主开关       1：开   0：关
	bool bPow2Station;           //    发电机组     1：启动 0：停止 

	bool bBtn[8];                       //   负载按纽状态

    int  CoHandle;                   //  并车手柄   0, 1, 2;
	int  PowOprt;                    // 电站工作状态 
	                                 //  0：单机  1：并车； 2：负载转移 ；

	bool bBtnL_Eng;                    // 左主机按纽状态
	bool bBtnR_Eng;                    // 右......

	int L_EngHandle;     //-5..0...5
	int R_EngHandle;          
 
	int  L_EngSpeed;        // 主机速度     
    int  R_EngSpeed;

    float  L_WaterTemp;       // 冷却水温度   
	float  R_WaterTemp;

    float  L_LubePrs;         // 滑油压力 
	float  R_LubePrs; 

    float  L_LubeTemp;       // 滑油温度   
	float  R_LubeTemp;

	float  L_CylinderTemp[6];   // 6#汽缸温度
    float  R_CylinderTemp[6];

    int    FaultNo;                       //故障序号  

}ENGPK;


class scjNet 
{
protected:
	unsigned short m_nOutId,DataSize,PortNum,idNum;

	unsigned char OutStr[256];
	char *TmpBuf,*RecvBuf,SvrAddr[40];

	CWnd *pParent;
	scjSocket *psockServer,*psockRecv[CLIENTMAX];
	int clientNum,connect;
	int i,j,k;
	long TimeSent,TimeGot;

	int TimeDiff;
	CString idStr,Ack;

	FILE *strm;

	unsigned short CalcChecksum( unsigned char *pData, int nSize );

	BOOL Pack( void *pMsgData, int nSize, int nType);	

	int UnPack( unsigned char *pData, int *nSize );

	int UnPackBuf( unsigned char *pData, int len=0);

	void Tianshu(char *str);

	void Tianshu(char *str,int len);

	void SpecMsg(void);

public:

	scjSocket *psockClient;

	ENGPK EngPk;
	UINT ShipRecvCnt,Running;
	int connected,SendAll;

	scjNet();

	scjNet(CWnd *,int,char *,int ptNum=0);

	//server端
	scjNet(CWnd *,int ptNum=0);

	~scjNet();

	int SendStr(LPSTR );

	int SendStr(int, LPSTR );

	int SendStr2All(LPSTR );

	int SendShip2All(void);
	
	int SendOSShip2All(void);//add for zj 2005.05.30

	int SendEngPk(void);

	int Accept();

	int Receive(scjSocket *);

	int Close(int);

	int IsConnected(){ return connected;}

	void RecvShip(int );

	int SendShip(int );

	//	int SendShip();

	int GetShipData(long *st,int md=0);

	int TimeSync0();

	int TimeSync();

	int GetTimeDiff(){return TimeDiff;} 

	void SetTimeDiff(int td){TimeDiff=td;}
	
	void Create(CWnd *,int,char *,int ptNum=0);
	
	void Create();

	
	LPSTR StrRecv[CLIENTMAX];
};

#ifndef __XXMESSAGE__
#define __XXMESSAGE__

#define BUFFSIZE 4096
#define INQUEUESIZE 20
#define FIRSTID 2
#define LASTID 32000

#pragma pack(1)
typedef struct{
	char Type[6];
	char DataSize[6];
	char Checksum[6];
	char Id[6];
	char Status[6];
	unsigned char *pData;
} MESSAGE;
#pragma pack()
#endif

#ifndef SHIPMAX
	#define SHIPMAX 130
	#define TSBASE 20
	#define OSNUM 20

	typedef struct {
		int cx,cy;
		float vx1,vy1,vx2,vy2,vsin,vcos;
		float PRoll,MRoll,PPitch,MPitch,fRoll,fPitch;
	} SHIPVAR;
	typedef struct {
		short act,type,revi1,revi2;
		float x,y,z,c,v,r,gc,gv;
		float roll,pitch,vy,vz,rr,rp;
		SHIPVAR *var;
	} SHIP;
	typedef struct {
		short act,type,revi1,revi2;
		double x,y,z,c,v,r,gc,gv;
		double roll,pitch,vy,vz,rr,rp;
		int cx,cy;
		double vx1,vy1,vx2,vy2,vsin,vcos;
	} PLANE;
/*
	typedef struct{
		int act;
		double x,y,z,c,v,r;
		double gv,gc;
	}SHIP;
*/
#endif

//extern SHIP vsl[];
extern SHIP *vsl;

#endif

/*
Usage:
1 App.cpp file:
	-include "scjNet.h"
	-in Instance(), call AfxSockInit() 
2 View.cpp file:
	-include "scjNet.h"
	-scjNet *pNet
	-in PreCreateWindow(CREATESTRUCT& cs), 
	  for server, call pNet=new scjNet(this)
	  cor client, call pNet=new scjNet(this,ClientID,"svraddr")
	-in MESSAGE_MAP, add ON_MESSAGE(SCJ_NETRECV,scjNetRecv)
	-add LRESULT  scjNetRecv(WPARAM wp,LPARAM lp) to View class
	     pNet->StrRecv[wp] is a CString received. 
3 Add scjNet.cpp file to Workspace.
	
*/
