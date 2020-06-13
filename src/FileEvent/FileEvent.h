#ifndef _FILE_EVENT_H_
#define _FILE_EVNET_H_

#define  FE_SUCCESS                0
#define  FE_START_SERVER_FAILED    1
#define  FE_START_CLIENT_FAILED    2
#define  FE_SEND_DATA_FAILED       3
#define  FE_RECV_DATA_FAILED       4
#define  FE_CREATE_OBJECTF_FAILED  5
#define  FE_NOT_ALLOWED            6
#define  FE_OBJECT_NOT_FOUND       7
#define  FE_NO_PRIVILEGE           8
#define  FE_OP_FAILED              9
#define  FE_CONNECT_PORT_FAILED    10


#pragma pack(1)
typedef struct _FILE_PRIVILEGE
{
	BYTE     bDisableWrite; //=bDisableEdit
	BYTE     bDisablePrint;
	BYTE     bDisableOpen;
	BYTE     bDisableCopyToClipboard;
	BYTE     bDisableSaveAs;
	BYTE     bDisableDrag;
	BYTE     bUnused1;
	BYTE     bUnused2;

}FILE_PRIVILEGE,*PFILE_PRIVILEGE;

#define  VERIFY_SUBJECT_NAME_ONLY    0x00000001
#define  VERIFY_MD5_OF_EXE_ONLY      0x00000002
#define  VERIFY_SUBJECT_NAME_FIRST   0x00000004

typedef struct _EXE_SIG_INFO
{
	WCHAR  wszExeName[64];
	ULONG  Flags; 
	WCHAR  wszSubjectName[64];
	WCHAR  wszMD5List[512];

}EXE_SIG_INFO, *PEXE_SIG_INFO;

#define EVENT_ID_FILE_QUERY_PRIVILEGE   1
#define EVENT_ID_FILE_PRINT             2
#define EVENT_ID_FILE_OPEN_FROM_API     3
#define EVENT_ID_FILE_SAVE_AS           4
#define EVENT_ID_FILE_QUERY_SIG_INFO    5
#define EVENT_ID_FILE_FAKED_DETECTED    6
#define EVENT_ID_FILE_CLOSE_FROM_WND    7


typedef struct _FILE_EVENT_PACKET
{
	DWORD   dwEventID;
	DWORD   dwStatusCode;

	union
	{
		struct  
		{ 
			DWORD            dwPID;
			WCHAR            wszSrcFileName[MAX_PATH];
			WCHAR            NotUsed0[MAX_PATH];
			FILE_PRIVILEGE   Privilege;
		}QueryPrivilege;


		struct  
		{
			DWORD            dwPID;
			WCHAR            wszSrcFileName[MAX_PATH];
			WCHAR            NotUsed0[MAX_PATH];
			FILE_PRIVILEGE   NotUsed1;
		}FileCloseFromWnd;

		struct  
		{ 
			DWORD            dwPID;
			WCHAR            wszSrcFileName[MAX_PATH];
			WCHAR            NotUsed0[MAX_PATH];
			FILE_PRIVILEGE   NotUsed1;
		}FilePrint;

		struct  
		{ 
			DWORD            dwPID;
			WCHAR            wszSrcFileName[MAX_PATH];
			WCHAR            NotUsed0[MAX_PATH];
			FILE_PRIVILEGE   NotUsed1;
		}FileOpenFromApi;

		struct  
		{ 
			DWORD            dwPID;
			WCHAR            wszSrcFileName[MAX_PATH];
			WCHAR            wszDestFileName[MAX_PATH];
			FILE_PRIVILEGE   NotUsed0;
		}FileSaveAs;

		struct 
		{
			DWORD            dwPID;
			WCHAR            wszSrcFileName[MAX_PATH];
			WCHAR            NotUsed0[MAX_PATH];
			FILE_PRIVILEGE   NotUsed1;
			EXE_SIG_INFO     SigInfo;
		}FileQuerySigInfo;

		struct 
		{
			DWORD            dwPID;
			WCHAR            wszSrcFileName[MAX_PATH];
			WCHAR            NotUsed0[MAX_PATH];
			FILE_PRIVILEGE   NotUsed1;
		}FileFakedDected;
	};

}FILE_EVENT_PACKET,*PFILE_EVENT_PACKET;


#pragma pack( )
class IEventReceiver
{
public:
	~IEventReceiver(){};

	friend class CFileEventServer;
	friend class CFltPortEventServer;
protected:
	virtual DWORD  OnFileEvent(PFILE_EVENT_PACKET  pFileEventPacket) = 0;

};

class IFileEventServer
{
public:
	virtual ~IFileEventServer(    ){};
	virtual DWORD Startup( IEventReceiver*  receiver) = 0;
};

DWORD  CreateFileEventServer(IFileEventServer**  EventReportServer);
DWORD  DeleteFileEventServer(IFileEventServer*  EventReportServer);


class  IFileEventClient
{
public:
	virtual ~IFileEventClient(    ){};
	virtual DWORD   Connect( )= 0;
	virtual DWORD   ReportFileEvent(PFILE_EVENT_PACKET  pFileEventPacket)=0;
	virtual VOID    DisConnect( ) = 0;
};

DWORD  CreateFileEventClient(IFileEventClient**  FileEventClient);
DWORD  DeleteFileEventClient(IFileEventClient*   FileEventClient);

#endif

