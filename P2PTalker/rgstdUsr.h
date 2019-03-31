typedef struct rgstdUsr
{
	char	usrname[10];
	BYTE    ipFild[4];
	int		port;
	BOOL    onlStat;

} RgstdUsr, *pRgstdUsr;