#ifndef _OFET_API_H_
#define _OFET_API_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define  ERR_SUCCESS           0
#define  ERR_OPEN_SRC_FILE     1
#define  ERR_OPEN_DEST_FILE    2
#define  ERR_NO_MEMORY         3
#define  ERR_NOT_IMPLEMENTED   4
#define  ERR_NOT_ENCRYPTED     5
#define  ERR_KEY_MISMATCH      6
#define  ERR_INVALID_PARAMETER 7
#define  ERR_WRITE_FAILED      8
#define  ERR_READ_FAILED       9
#define  ERR_OPEN_DRIVER_FAILED 10
#define  ERR_IOCTRL_FAILED      11

DWORD   SetStartFiltering(BOOL  bStart);
DWORD   GetStartFiltering(BOOL*  bStart);


#define  CIPHER_ID_XTEA    0
#define  CIPHER_ID_AES     1

DWORD   SetDriverCryptConfig(DWORD  CihperID,char* szKeyBuffer, int nKeyLength);

DWORD   GetCurrentCipherID(DWORD*  CihperID);
DWORD   SetRandomKeyMode(DWORD  Value);
DWORD   GetRandomKeyMode(DWORD*  Value);

DWORD   IsEncryptedFile(WCHAR* wszFileName );
DWORD   efs_DecryptFile(WCHAR* wszFileName );
DWORD   efs_EncryptFile(WCHAR* wszFileName );
DWORD   efs_IsEncryptedFileAlone(WCHAR* wszFileName, int CipherID,  void* FileKey, int KeyLength);
DWORD   efs_EncryptFileAlone(WCHAR* wszFileName, int CipherID, int bUseRandomKeyMode, void* FileKey, int KeyLength);
DWORD   efs_DecryptFileAlone(WCHAR* wszFileName, int CipherID, void* FileKey, int KeyLength);

typedef struct _FILE_CRYPT_CONFIG
{
	ULONG   dwCipherID;
	ULONG   dwOneKeyOneFile;
	CHAR    szFileKey[128];
}FILE_CRYPT_CONFIG,*PFILE_CRYPT_CONFIG;

DWORD   GetFileCryptConfig(WCHAR* wszFileName, PFILE_CRYPT_CONFIG cryptConfig);

#define  HEADER_BUFFER_SIZE   2048
#define  CUSTOM_DATA_SIZE     1024

DWORD   SetCustomData(WCHAR* wszFileName, PVOID CustomDataBuffer, ULONG BufferSize );
DWORD   GetCustomData(WCHAR* wszFileName, PVOID CustomDataBuffer, ULONG BufferSize );

DWORD   SetCustomDataAlone(WCHAR* wszFileName, PVOID CustomDataBuffer, ULONG BufferSize, 
						   int CipherID,  void* FileKey, int KeyLength, int *nErrCode
						   );

DWORD   GetCustomDataAlone(WCHAR* wszFileName, PVOID CustomDataBuffer, ULONG BufferSize, 
						   int CipherID,  void* FileKey, int KeyLength,
						   int *nErrCode
						   );

DWORD   SetCustomDataResident(DWORD dwValue );
DWORD   GetCustomDataResident(DWORD* dwValue );

DWORD   SetManualEncryptFile(DWORD dwValue );
DWORD   GetManualEncryptFile(DWORD* dwValue );

#define   PROC_FLAG_ENCRYPT_ON_OPEN   0x00000002

DWORD   SendPolicy( WCHAR* wszExeName, WCHAR* wszExtNameList, ULONG nFlags );
DWORD   SendPolicA( CHAR* szExeName, CHAR* szExtNameList, ULONG nFlags );

DWORD   CancelPolicy( WCHAR* wszExeName);
DWORD   CancelPolicyA( CHAR* szExeName);
DWORD   CancelAllPolicy( );

DWORD   AddExtName( WCHAR* wszExtName);
DWORD   GetOpenedFileCount(DWORD*  Count);

DWORD   AddWhiteDir(WCHAR* wszFileName );
DWORD   RemoveWhiteDir(WCHAR* wszFileName );


DWORD   SetWhitePID(int nPID);

DWORD   AddFile2Mfl( WCHAR* wszFileName);


DWORD   LoadNotepadPolicy( );
DWORD   UnloadNotepadPolicy( );
 
DWORD   LoadWordpadPolicy( );
DWORD   UnloadWordpadPolicy( );

DWORD   LoadWordPolicy( );
DWORD   UnloadWordPolicy( );

DWORD   LoadExcelPolicy( );
DWORD   UnloadExcelPolicy( );

DWORD   LoadPPTPolicy( );
DWORD   UnloadPPTPolicy( );

DWORD   LoadMsProjectPolicy( );
DWORD   UnloadMsProjectPolicy( );

DWORD   LoadMsVisioPolicy( );
DWORD   UnloadMsVisioPolicy( );

DWORD   LoadWPSWordPolicy( );
DWORD   UnloadWPSWordPolicy( );

DWORD   LoadWPSExcelPolicy( );
DWORD   UnloadWPSExcelPolicy( );

DWORD   LoadWPSPPTPolicy( );
DWORD   UnloadWPSPPTPolicy( );

DWORD   LoadAutoCADPolicy( );
DWORD   UnloadAutoCADPolicy( );

DWORD   LoadFoxitPDFPolicy( );
DWORD   UnloadFoxitPDFPolicy( );

DWORD   LoadAdobePDFPolicy( );
DWORD   UnloadAdobePDFPolicy( );

DWORD   LoadPhotoShopPolicy( );
DWORD   UnloadPhotoShopPolicy( );

DWORD   LoadMspaintPolicy( );
DWORD   UnloadMspaintPolicy( );

#ifdef __cplusplus
}
#endif
#endif

