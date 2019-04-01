// CjComNet.h : main header file for the CJCOMNET DLL
//

#if !defined(AFX_CJCOMNET_H__E8BB60B8_8BA5_493C_BA2A_FA9837D6C081__INCLUDED_)
#define AFX_CJCOMNET_H__E8BB60B8_8BA5_493C_BA2A_FA9837D6C081__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

//#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCjComNetApp
// See CjComNet.cpp for the implementation of this class
//

class CCjComNetApp : public CWinApp
{
public:
	CCjComNetApp();
	~CCjComNetApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCjComNetApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCjComNetApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};
__declspec(dllexport) void ShowStr(CView *p, int x, int y,char *str);

#define USECOMM 

#include <windows.h>
#include <commdlg.h>
#include <string.h>
#include <io.h>
#include <memory.h>
#include <afxsock.h>       

#define MY_MOUSEMOVE WM_USER+100
#define MY_LBUTTONDBLCLK WM_USER+101
#define MY_LBUTTONDOWN WM_USER+102
#define MY_LBUTTONUP WM_USER+103
#define MY_MBUTTONDBLCLK WM_USER+104
#define MY_MBUTTONDOWN WM_USER+105
#define MY_MBUTTONUP WM_USER+106
#define MY_RBUTTONDBLCLK WM_USER+107
#define MY_RBUTTONDOWN WM_USER+108
#define MY_RBUTTONUP WM_USER+109
#define SCJ_NETRECV WM_USER+110
#define SCJ_METER WM_USER+111
#define SCJ_MATFILE WM_USER+112
#define SCJ_COMMLINE WM_USER+113
#define SCJ_SHIPINIT WM_USER+114
#define SCJ_ENGCMD WM_USER+115



typedef struct pole
{
	double brg;
	double dis;
	double rx;
	double ry;
}POLE;

typedef struct  cart
{
	double x;
	double y;
	double g;
}CART;

typedef struct  sline
{
	double a;
	double b;
}SLINE;

typedef struct  latlon
{
	char lat[20];
	char lon[20];
}LATLON;

typedef struct  latlona
{
	char lat[16];
	char lon[16];
}LATLONA;

typedef struct  latlonb
{
	char lat[16];
	char lon[16];
}LATLONB;


__declspec(dllexport) int rdpos(POLE *rdb, CART *rdp);
__declspec(dllexport) int strll(CART *np, LATLON *sp);
__declspec(dllexport) int strllA(CART *np, LATLONA *sp);
__declspec(dllexport) int strllB(CART *np, LATLONB *sp);
__declspec(dllexport) int brgtolin(CART *bg,SLINE *l);
__declspec(dllexport) int crpoint(SLINE *l1,SLINE *l2,CART *crp);
__declspec(dllexport) double mlat(double mmp);      
__declspec(dllexport) double mlat1(double mmp);     
__declspec(dllexport)  double mpart(double );      
__declspec(dllexport) double mp(double lat);      
__declspec(dllexport) double lp(double lt);
__declspec(dllexport) double inpdeg(void);        
__declspec(dllexport) double inpsec(void);        
__declspec(dllexport) double inpdegbk(void);
__declspec(dllexport) int llstr(CART *np,LATLON *sp);
__declspec(dllexport) int strtollB(CART *np, LATLONB *sp);
__declspec(dllexport) int secll(CART *np,LATLON *sp);
__declspec(dllexport) int xytobd(double xx,double yy,POLE *pp);
__declspec(dllexport) int lnltstr(double llmin,char *llstrn,int lnt);
//__declspec(dllexport) double TransMP(double Latitude);

#define GWL_NPTTYINFO        0
#define TTYEXTRABYTES        sizeof( LONG )

#define ABOUTDLG_USEBITMAP  1

#define ATOM_TTYINFO       0x100

// hard coded maximum number of ports for device under Win32

#define MAXPORTS        8

// terminal size

#define MAXROWS         25
#define MAXCOLS         80

#define MAXBLOCK        1024

#define MAXLEN_TEMPSTR  81

#define RXQUEUE         4096
#define TXQUEUE         4096

// cursor states

#define CS_HIDE         0x00
#define CS_SHOW         0x01

// Flow control flags

#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04

// ascii definitions

#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x90
#define ASCII_XOFF      0x91

// data structures

typedef struct tagTTYINFO
{
   HANDLE  idComDev ;
   BYTE    bPort, abScreen[ MAXROWS * MAXCOLS ] ;
   BOOL    fConnected, fXonXoff, fLocalEcho, fNewLine, fAutoWrap,
           fUseCNReceive, fDisplayErrors;
   BYTE    bByteSize, bFlowCtrl, bParity, bStopBits ;
   DWORD   dwBaudRate ;
   WORD    wCursorState ;
   HFONT   hTTYFont ;
   LOGFONT lfTTYFont ;
   DWORD   rgbFGColor ;
   int     xSize, ySize, xScroll, yScroll, xOffset, yOffset,
           nColumn, nRow, xChar, yChar ;
   HANDLE      hPostEvent, hWatchThread, hWatchEvent ;
   HWND        hTermWnd ;
   DWORD       dwThreadID ;
   OVERLAPPED  osWrite, osRead ;

} TTYINFO, *NPTTYINFO ;

#define GETHINST( x )  ((HINSTANCE) GetWindowLong( x, GWL_HINSTANCE ))
#define GETNPTTYINFO( x ) ((NPTTYINFO) GetWindowLong( x, GWL_NPTTYINFO ))
#define SETNPTTYINFO( x, y ) SetWindowLong( x, GWL_NPTTYINFO, (LONG) y )

#define COMDEV( x ) (x -> idComDev)
#define PORT( x )   (x -> bPort)
#define SCREEN( x ) (x -> abScreen)
#define CONNECTED( x ) (x -> fConnected)
#define XONXOFF( x ) (x -> fXonXoff)
#define LOCALECHO( x ) (x -> fLocalEcho)
#define NEWLINE( x ) (x -> fNewLine)
#define AUTOWRAP( x ) (x -> fAutoWrap)
#define BYTESIZE( x ) (x -> bByteSize)
#define FLOWCTRL( x ) (x -> bFlowCtrl)
#define PARITY( x ) (x -> bParity)
#define STOPBITS( x ) (x -> bStopBits)
#define BAUDRATE( x ) (x -> dwBaudRate)
#define CURSORSTATE( x ) (x -> wCursorState)
#define HTTYFONT( x ) (x -> hTTYFont)
#define LFTTYFONT( x ) (x -> lfTTYFont)
#define FGCOLOR( x ) (x -> rgbFGColor)
#define XSIZE( x ) (x -> xSize)
#define YSIZE( x ) (x -> ySize)
#define XSCROLL( x ) (x -> xScroll)
#define YSCROLL( x ) (x -> yScroll)
#define XOFFSET( x ) (x -> xOffset)
#define YOFFSET( x ) (x -> yOffset)
#define COLUMN( x ) (x -> nColumn)
#define ROW( x ) (x -> nRow)
#define XCHAR( x ) (x -> xChar)
#define YCHAR( x ) (x -> yChar )
#define USECNRECEIVE( x ) (x -> fUseCNReceive)
#define DISPLAYERRORS( x ) (x -> fDisplayErrors)

#define POSTEVENT( x ) (x -> hPostEvent)
#define TERMWND( x ) (x -> hTermWnd)
#define HTHREAD( x ) (x -> hWatchThread)
#define THREADID( x ) (x -> dwThreadID)
#define WRITE_OS( x ) (x -> osWrite)
#define READ_OS( x ) (x -> osRead)

#define SET_PROP( x, y, z )  SetProp( x, MAKEINTATOM( y ), z )
#define GET_PROP( x, y )     GetProp( x, MAKEINTATOM( y ) )
#define REMOVE_PROP( x, y )  RemoveProp( x, MAKEINTATOM( y ) )

#define _fmemset   memset
#define _fmemmove  memmove

#define LINEMAX 252
class __declspec(dllexport) CComm32  
{
protected:
	HWND hWnd;
	NPTTYINFO npTTYInfo ;
	int portNo,ShipWrite;
	HANDLE   idComDev;
	char *tmpc;
	CWinThread *WatchThread;
	BOOL WriteOK;
	DWORD  CommError;
	BOOL ReadOK;
	DWORD  RdError;

	int numread;
	char linmk;
	int LineCnt;

	void RecErr(char *str);

public:
	char LineBuf[256];

	LRESULT  CreateTTYInfo() ;
	BOOL  DestroyTTYInfo() ;
	BOOL  ResetTTYScreen(NPTTYINFO ) ;
	BOOL  WriteTTYBlock(LPSTR, int ) ;
	int  ReadCommBlock(LPSTR, int ) ;
	BOOL  WriteCommBlock(LPSTR, DWORD);
	BOOL  OpenConnection() ;
	BOOL  SetupConnection() ;
	BOOL  CloseConnection() ;
	int WrCommByte(char );
	int RdCommByte(char *);
	int WrCommStr(char *str);
	int WrCommLine(char *str);
	int RdCommLine(char *str);
	int ReadHh(unsigned char *str);
	int WriteSteer(char *cd, int dat);
	int ReadRdkb(unsigned char *str);
	int ReadSteer(unsigned char *str);
	//int Read0183Str(unsigned char *str);

	int ReadJms(unsigned char *str);
	int RdCommStr(LPSTR str, int sz){
		return (ReadCommBlock(str,sz));
	}
	void SetWriteMode(int m){ShipWrite=m;}
	CComm32(int );
	CComm32(char * );
	virtual ~CComm32();

};
DWORD CommWatchProc( LPSTR );
__declspec(dllexport) BOOL ScjCheck(int);
__declspec(dllexport) BOOL ScjGetName(char *);
__declspec(dllexport) char *user_strtok(char *str, char *token);
__declspec(dllexport) char *after_tok(char *str, char *token);
extern unsigned char VerInfo[];


//#define YING_EC
#ifndef YING_EC

class __declspec(dllexport) CDlyAct{
	double t0,delay_t,length_t;
	int ov;
public:
	CDlyAct();
	void Set(double dt,double lt);
	int Check(double t);
};

class __declspec(dllexport) ByteBuf{
  protected:
	char *Buf;
	int size,head,tail;
  public:
	ByteBuf(unsigned int);
	void Put(char);
	char Get(char *);
	int io_out(int );
};

//ScjClass.h
class __declspec(dllexport) SFunc{
	double FromY,ToY,aX,bX,rX;
	double dy;
public:
	SFunc();
	~SFunc();
	void Set(double fy,double ty, double ax, double bx, double rx);
	double Get(double x);
};

class __declspec(dllexport) Light{
    int iLight,dLight,toLight;
    double toTime,dTime,cTime;
  public:
    Light(){toTime=0;}
    void Set(int L1st,int L2nd,int tt);
    int  Get(double tt);
};

class __declspec(dllexport) CjLine{
	double A, B, C, rAApBB;
  public:
	double X1,Y1,X2,Y2,brg;
	double top,bottom,left,right;
  public:
	CjLine(){
		X1=Y1=X2=Y2=brg=0;
		top=bottom=left=right=0;
	}
	void Set(double x1,double y1,double x2,double y2);
	double DistTo(double x,double y);
	int IsAt(double,double);
	int IsPort(double x,double y);
};
#endif
/*
class __declspec(dllexport) CMatFile
{
protected:
	CWnd *pParent;
	long id;
	int RecvPos, SendPos,Channel,bufsize;
public:
	HANDLE hFileMap;
	LPVOID lpView;
	char *lpView1;
//	CString strRecv[40];
public:
	void SendStr(char *str);
	void SendBuf(char *buf, int cb);
	int RecvBuf(char *buf);
	int RecvBuf(char *buf, unsigned long *time);
	void Check();
	CMatFile(CWnd *,int ch=0);
	CMatFile(CWnd *, char *,int );
	~CMatFile();

};
*/

class __declspec(dllexport) CCurveValue
{
protected:
	CWnd *pParent;
	int Invalid,id,parts;
	double LLimit,ULimit,Range;
	double *pValues;
public:
	CCurveValue(void);
	~CCurveValue(void);
	double GetValue(double xx, int md=0);
	int SetCurve(char *fn,int pp=100);
public:
};

class __declspec(dllexport) CabgFilter
{
protected:
	double Intv,T0;
	double alfa, beta,gamma;
public:
	double Xn,Xnp,Xnpp;

	CabgFilter(void);
	~CabgFilter(void);
	double Observe(double x, double t);
	double ObserveC(double x, double t);
	double Observe0(double x, double t);
	double Observe(double x);
	void SetT(double intv);
	void SetValue0(double xn,double xnp=0.0,double xnpp=0.0);
	void Setabg(double a=1.021, double b=0.0285,double g=0.0005);
};

class __declspec(dllexport)CDisturb
{
protected:
	double time0,T0,aT,aM;
	double Mag,Tao,Prd;
public:
	CDisturb(double M, double t, double T);
	void Set(double M, double t, double T);
	double Get(void);
	double Get(double dt);
};


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

class __declspec(dllexport) scjNet 
{
protected:
	unsigned short m_nOutId,DataSize,PortNum,idNum;
	unsigned char OutStr[512];
	char *TmpBuf,*RecvBuf,SvrAddr[40];
	CWnd *pParent;
	scjSocket *psockServer,*psockRecv[CLIENTMAX];
	int clientNum,connect,StrChk;
	int i,j,k;
	long TimeSent,TimeGot;
	int StartId, EndId;
	int TimeDiff;
	CString idStr,Ack;
	FILE *strm;
	unsigned short CalcChecksum( unsigned char *pData, int nSize );
	BOOL Pack( void *pMsgData, int nSize, int nType);	
	int UnPack( unsigned char *pData, int *nSize );
	int UnPackBuf( unsigned char *pData, int len=0);
	void Tianshu(char *str);
	void Tianshu(char *str,int len);
	void SpecMsg(scjSocket *psockRecv);

public:
	char Name[20];
	scjSocket *psockClient;
	ENGPK EngPk;
	UINT ShipRecvCnt,Running;
	int connected,SendAll;
	scjNet();
	scjNet(CWnd *,int,char *,int ptNum=0);
	scjNet(CWnd *,int ptNum=0);
	~scjNet();
	int SendStr(LPSTR );
	int SendStr(int, LPSTR );
	int SendStr2All(LPSTR );
	int SendShip2All(void);
	int SendShip2All(int _start_id, int _end_id);
	int SendNoCheckStr(int, LPSTR );

	int SendEngPk(void);
	int Accept();
	int Receive(scjSocket *);
	int Close(int);
	int IsConnected(){ return connected;}
	void RecvShip(int );
	int SendShip(int );
//	int SendShip();
	int GetShipData(long *st,int md=0);
	int GetShipData(long *st,int *_start_id, int *_end_id, int md=0);
	int TimeSync0();
	int TimeSync();
	int GetTimeDiff(){return TimeDiff;} 
	void SetTimeDiff(int td){TimeDiff=td;}
	void Create(CWnd *,int,char *,int ptNum=0);
	void Create();
	void SetPP(CWnd *pp){pParent=pp;};
	BOOL ChkNetStr(WPARAM *wp,LPARAM *lp,int md=1);

	void GetName(char *name);

	LPSTR StrRecv[CLIENTMAX+2];
	LPARAM lp_ID[CLIENTMAX+2];
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
	#define SHIPMAX		130
	#define TSBASE		20
	#define OSNUM		20
	#define FIRSTTUG	90
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
	} PLANE_EX;
/*
	typedef struct{
		int act;
		double x,y,z,c,v,r;
		double gv,gc;
	}SHIP;
*/
#endif

extern int scj_check;

//extern SHIP *vsl;

#ifndef _WINDLL
__declspec(dllimport) SHIP  *vsl;
#endif

#define __SHIPAPP 

//#include "FzClass.h"
//#include "AutoPilot.h"

class __declspec(dllexport) FzMemFunc
{
	protected:
	int Num,Sat;
	double Left,Right,Bottom,Top;
	double Triangle(double u);
	public:
	int Lval1,Lval2,Lv[2];
	double *pCP,*pW;
	double Rval1,Rval2,Rv[2];
	FzMemFunc(double left,double right,double bottom,double top,int num, int sat);
	~FzMemFunc();
	int CheckValue(double u,int md=0);
	void SetCP(double *pVal);
};


class __declspec(dllexport) CjAutoPilot
{
protected:
	FILE *strm; 
	double CseSet,rud0;
	double Sens,Step,Prop,Rud0,Diff,rSens;
	double Cmax,Tmax,Rmax;
	double FzMin(double d1,double d2);
public:
	CjAutoPilot();
	CjAutoPilot(double cm,double tm,double rm);
	~CjAutoPilot();
	void SetShipPm(double cm,double tm,double rm);
	double Check(double cse,double rot);
	void SetCourse(double cse){CseSet=cse;};
	void SetSens(double ss);
	void SetDiff(double ss);
	void SetRud0(double ss);
	void SetProp(double ss);
	void CancelStep(void );
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CJCOMNET_H__E8BB60B8_8BA5_493C_BA2A_FA9837D6C081__INCLUDED_)
