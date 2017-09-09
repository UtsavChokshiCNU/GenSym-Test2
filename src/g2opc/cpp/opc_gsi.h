#if !defined(__GSIOPC_H__)
#define __GSIOPC_H__
#include <opcda.h>

#define GSI_UNSUPPORTED_TYPE     50
#define GSI_UNREGISTERED         51
#define GSI_DUPLICATED_ITEM      52
#define G2OPC_NO_GROUP_DEFINED  100
#define G2OPC_NO_SERVER_DEFINED 101
#define G2OPC_DEF_ATTR_BAD      102
#define G2OPC_CANT_ADD_TO_PUB   103
#define G2OPC_QI_FAILED         105
#define G2OPC_MEM_ALLOC_FAILED  106
#define G2OPC_READ_FAILURE      109
#define G2OPC_UNEXPECTED        110
#define G2OPC_MAX_ITEM_REACHED  111
#define G2OPC_BADRIGHTS         199
#define G2OPC_INVALIDITEMID     200
#define G2OPC_UNKNOWNITEMID     201
#define G2OPC_BAD_ACCESSPATH    202
#define G2OPC_BADTYPE           203
#define G2OPC_WRITE_FAILURE     205
#define G2OPC_ADD_ITEM_FAIL     206

    // Prototypes
    // ----------
    VOID        GsiLoop(LPSTR lpCmdLine) ;
    BOOL WINAPI ConsoleCtrlHandler(DWORD dwCtrlType) ;
    void        shutdown_context(gsi_int ctxNr, bool gone) ;

    extern  short   g_defaultQualityFilter ;
    extern  bool    g_chkServerStatus ;
    extern  long    g_srvrCheckFreq ;
    extern  bool    g_useG2TimeStamp ;
    extern  bool    g_initSecurity ;
    extern  gsi_int g_shutdown_ctx_nr ;
    extern  bool    g_shutdown_request ;
    extern  bool    g_lev1_good ;
    extern  bool    g_lev1_uncertain ;
    extern  bool    g_lev1_bad ;
    extern  bool    g_dlg_open ;
    extern  short   g_license_status ;

    const long  starting_table_size = 25 ;

    // Structure Definitions
    // ---------------------
    // Values returned for a single item
    // ---------------------------------
    struct item_values
    {
        VARIANT             value ;
        WORD                quality ;
        FILETIME            timestamp ;
        HRESULT             status ;
    } ;

    struct item_values_ptr
    {
        OPCHANDLE           hItem ;  // handle for item assigned by client.
                                     // same as GSI's handle for item
        OPCHANDLE           hItemS ; // handle for item assigned by server
        item_values*        pVals ;
    } ;


    // Information kept for each context
    // ---------------------------------
    struct context_info
    {
        CServer             *pServer ;
        IOPCItemMgt         *pItemMgt ;
        OPCHANDLE           hGroupS ;
        DWORD               dwUpdRateS ;
        bool                sync_mode ;
        bool                queued_for_async_processing ;
        gsi_int             icon_hndlr_proc ;

        //IOPCServer          *pServer ;
        // CLSID               serverCLSID ;

        // Browser paramenters
        // -------------------
        LPWSTR              branch_name ;
        LPWSTR              continuation_pt ;
        LPWSTR              elementNameFilter ;
        VARTYPE             typeFilter ;
        short               rightsFilter ;

        // Data Callback info
        // ------------------
        bool                b_usesV2dcb ;
        IConnectionPoint    *p_ConnectionPoint ;
        DWORD               dcb_cookie ;

        // Used for asynchronous updates
        // -----------------------------
        item_values_ptr     *pItemTable ;
        long                nrItems ;
        long                table_size ;

        // Quality filter
        // --------------
        bool                b_lev1_good ;
        bool                b_lev1_bad ;
        bool                b_lev1_uncertain ;

    } ;



    struct item_id_attrs
    {
        wchar_t             *item_id ;
        wchar_t             *access_path ;
    } ;

#endif