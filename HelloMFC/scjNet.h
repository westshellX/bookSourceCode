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

	int DrillMode;          // 1:  �ݻ���һ�� 2��������;  3:�������
	int DrillShape;         // ���ͣ�1 2 3 4��
	int DrillSection;       // ���ţ� 1����  2���� 
	int DrillItem;          // ��Ŀ�� 1������ 2������ 3������

	float Pow1A;                //1#    �������� 
	float Pow1V;                //    ���ر���� 
	float Pow1MO;               //    ��ŷ�����  
	float Pow1W;                //    ���ʱ����
	float Pow1CosP;             //    ����ϵ��
	float Pow1Hz;               //    Ƶ�ʱ���� 

	float Pow2A;                //2#   �������� 
	float Pow2V;                //    ���ر���� 
	float Pow2MO;               //    ��ŷ�����  
	float Pow2W;                //    ���ʱ����
	float Pow2CosP;             //    ����ϵ��
	float Pow2Hz;               //    Ƶ�ʱ���� 

    bool bPow1Switch;             // 1�� ������       1����   0����
	bool bPow1Station;            //    �������     1������ 0��ֹͣ 

    bool bPow2Switch;            //2�� ������       1����   0����
	bool bPow2Station;           //    �������     1������ 0��ֹͣ 

	bool bBtn[8];                       //   ���ذ�Ŧ״̬

    int  CoHandle;                   //  �����ֱ�   0, 1, 2;
	int  PowOprt;                    // ��վ����״̬ 
	                                 //  0������  1�������� 2������ת�� ��

	bool bBtnL_Eng;                    // ��������Ŧ״̬
	bool bBtnR_Eng;                    // ��......

	int L_EngHandle;     //-5..0...5
	int R_EngHandle;          
 
	int  L_EngSpeed;        // �����ٶ�     
    int  R_EngSpeed;

    float  L_WaterTemp;       // ��ȴˮ�¶�   
	float  R_WaterTemp;

    float  L_LubePrs;         // ����ѹ�� 
	float  R_LubePrs; 

    float  L_LubeTemp;       // �����¶�   
	float  R_LubeTemp;

	float  L_CylinderTemp[6];   // 6#�����¶�
    float  R_CylinderTemp[6];

    int    FaultNo;                       //�������  

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

	//server��
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
