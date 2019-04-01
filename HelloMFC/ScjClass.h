#if !defined __SCJCLASS
#define __SCJCLASS
//#include "MyMessage.h"

class CDlyAct
{
	double t0,delay_t,length_t;

	int ov;
public:

	CDlyAct();

	void Set(double dt,double lt);

	int Check(double t);
};


class ByteBuf{
  protected:

	char *Buf;
	int size,head,tail;
  public:

	ByteBuf(unsigned int);

	void Put(char);

	char Get(char *);

	int io_out(int );
};


#define YING_EC
#ifndef YING_EC
class Light{
    int iLight,dLight,toLight;
    double toTime,dTime,cTime;
  public:
    Light(){toTime=0;}
    void Set(int L1st,int L2nd,int tt);
    int  Get(double tt);
};

class CLine{
	double A, B, C, rAApBB;
  public:
	double X1,Y1,X2,Y2,brg;
	double top,bottom,left,right;
  public:
	CLine(){
		X1=Y1=X2=Y2=brg=0;
		top=bottom=left=right=0;
	}
	void Set(double x1,double y1,double x2,double y2);
	double DistTo(double x,double y);
	int IsAt(double,double);
	int IsPort(double x,double y);
};
#endif


class CMatFile
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



class CCurveValue
{
protected:

	CWnd *pParent;
	int Invalid,id,parts;
	double LLimit,ULimit,Range;

	double *pValues;
public:

	CCurveValue(){};

	~CCurveValue();

	double GetValue(double xx, int mode=0);

	int SetCurve(char *fn,int pp=100);
public:
};

# endif
