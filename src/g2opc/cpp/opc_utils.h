#if !defined(__OPC_UTILS_H__)
#define __OPC_UTILS_H__

#define OPC_GOOD_NONSPEC            0
#define OPC_BAD_NONSPEC             300
#define OPC_UNC_NONSPEC             400

#define OPC_BAD_CONFIG_ERROR        301
#define OPC_BAD_NOT_CONNECTED       302 
#define OPC_BAD_DEVICE_FAILURE      303
#define OPC_BAD_SENSOR_FAILURE      304
#define OPC_BAD_LAST_KNOWN_VAL      305
#define OPC_BAD_COMM_FAILURE        306
#define OPC_BAD_OUT_OF_SERVICE      307
#define OPC_BAD_NOT_INITIALIZED     308
#define OPC_UNC_LAST_USABLE_VAL     401
#define OPC_UNC_SENSOR_NOT_ACCUR    404
#define OPC_UNC_EGU_EXCEEDED        405
#define OPC_UNC_SUB_NORMAL          406
#define OPC_GOOD_LOCAL_OVERRIDE     506

#define OPC_BAD_INVALID_QUALITY     333
#define OPC_UNC_INVALID_QUALITY     444
#define OPC_GOOD_INVALID_QUALITY    555
#define OPC_INVALID_QUALITY         666

#define INI_FILE _T("configfile.ini")
#define INI_SEC_LOG _T("LogSetting")
#define INI_SEC_QUALITY _T("Quality")
#define INI_SEC_SERVERSTATUS _T("ServerStatus")
#define INI_LOG_FILENAME _T("LogFileName")
#define INI_LOG_FILE_MAX_SIZE _T("LogFileMaxSize")
#define INI_LOG_LEVEL _T("LogLevel")
#define INI_LOG_TO_G2 _T("LogToG2")
#define INI_LOG_SWITCH _T("EnableLog")
#define INI_LOG_ARCHIVE_LAST _T("ArchiveLastLog")
#define INI_LOG_TO_SCREEN _T("LogToScreen")
#define INI_QUALITY_FILTER _T("QualityFilter")
#define INI_SERVERSTATUS_CHECKSTATUS _T("CheckStatus")
#define INI_SERVERSTATUS_CHECKFREQUENCY _T("CheckFrequency")
#define INI_SERVERSTATUS_USEG2TIMESTAMP _T("UseG2TimeStamp")
#define INI_SERVERSTATUS_INITSECURITY _T("InitSecurity")

namespace OpcUtils
{
    bool    QualityPasses(long quality_code, gsi_int ctx_nr) ;
    BSTR    ConvertVariantTypeToText(VARTYPE) ;
    BSTR    CStr(VARIANT vx) ;
    void    GetWindowsErrorMsg(TCHAR *lpBuffer, int nBufferSize);
    HRESULT InitializeFromIniFile(LPWSTR szIniFileName) ;
    BOOL UpdateBooleanToIniFile(LPCTSTR szIniFileName,LPCTSTR sectionName,LPCTSTR name, bool value);
    BOOL UpdateIntToIniFile(LPCTSTR szIniFileName,LPCTSTR sectionName,LPCTSTR name, int value);

    HRESULT WinCmdLineToC(LPSTR lpCmdLine, char ***pppArg, int *pNrArgs) ;
    HRESULT AddItemHdl2Ctx(OPCHANDLE hdlC, OPCHANDLE hdlS, gsi_int ctx_nr) ;
    long    FindItemHdl(OPCHANDLE hdl, gsi_int ctx_nr, bool *found) ;
    long    OPCq2G2q(long) ;
    void    ServerReleased(CLSID clsid) ;
    VARTYPE GsiType2VT(gsi_int GsiType) ;
    time_t  FileTimeToUnixTime(FILETIME FileTime) ;
}
#endif
