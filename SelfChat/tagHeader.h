typedef struct tagHeader
{
	char	type;
	int		len;	 
} Header, *pHeader;

#define LOGIN_IO		1
#define SEND_MESSAGE	3