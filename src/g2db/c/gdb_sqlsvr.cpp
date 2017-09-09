#import "msado15.dll" \
    no_namespace rename("EOF", "EOFile")

#include <ole2.h>
#include <shlwapi.h>
#include <string.h>
#include <stdlib.h>
#include <wchar.h>

extern "C" 
{
#include "gdb_sqlsvr.h"
}
#include <sql.h>
#include "stdio.h"
#include "gdb_genda.h"
#include "gsi_main.h"

#include "gdb_messages.h"
#include "gdb_globals.h"
#include "gdb_client_inter_sqlsvr.h"

extern "C" long	strcmpci ( wchar_t *str1, wchar_t *str2 );
extern "C" long	debug;
extern "C" long	iomsg (long flag, long layer, long write_logfile, long setstat, GENDA *sqlGen,
                       long row_reset, char *argtypes, ...);
extern "C" SQLDA_PTRS   *sqlda_ptrs[MAX_GDB_CONTEXTS];
extern "C" CONTEXT_INFO context[MAX_GDB_CONTEXTS];
extern "C" ODBCERR          g_sqlca;
extern long  max_col_array_size = DFLT_COLUMN_ARRAY_SZ;
extern long  max_value_array_size = DFLT_VALUE_ARRAY_SZ;
extern "C" long row_count[MAX_GDB_CONTEXTS];
extern "C" long sqlfetch_cnt[MAX_GDB_CONTEXTS];
extern "C" void* trig_hstmt[MAX_GDB_CONTEXTS];

/* SQLOLEDB globals */
/* Try to conclude this globald to any kind of structure */

_ConnectionPtr pConn = NULL;
_CommandPtr      pCmd = NULL;
_RecordsetPtr    pRst = NULL;
FieldsPtr ptrFlds = NULL;

gsi_int             context_num;
SQLRETURN           rc;

/* end Gensym*/

#define LAYER LAYER3
#define  XCALLOC(n,s) calloc(n,s)
#define SQL_NO_DATA_FOUND 100

long cpp_sql_setup()
{
    if (debug & DBG1)
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("SQL_SETUP"));
    if(FAILED(::CoInitialize(NULL)))
      return GDB_ERROR;

    return GDB_SUCCESS;
}

void fetch_dsn_detail(wchar_t* db_dsn, wchar_t* server_address, wchar_t* database_name)
{
    int ptr = 0;
    int has_server = 0;

    while (db_dsn[ptr]) {
      if (db_dsn[ptr] == L'/') {
        has_server = 1;
        break;
      } else
        ptr++;
    }

    if (has_server == 1) {
      wcsncpy(server_address, db_dsn, ptr);
      server_address[ptr] = L'\0';
      wcscpy(database_name, &db_dsn[ptr+1]);
    } else {
      wcscpy(server_address, L"(local)");
      wcscpy(database_name, db_dsn);
    }
}

long cpp_sql_connect(wchar_t* db_user,wchar_t* db_pass,wchar_t* db_dsn ){

    HRESULT hr = S_OK;
    context_num = gsi_current_context();
#define MAX_BUFFER_LEN 200
    wchar_t buffer[MAX_BUFFER_LEN+1] = {'\0'};
    wchar_t server_address[MAX_BUFFER_LEN+1];
    wchar_t database_name[MAX_BUFFER_LEN+1];

    fetch_dsn_detail(db_dsn, server_address, database_name);

    if (debug & DBG1)
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("SQL_CONNECT"));

    /* Make sure user, password, dsn are there */
    if (db_user == (wchar_t *)NULL) {
      iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE, "%d", ENOUSER);
      return (GDB_ERROR);
    }
    if (db_pass == (wchar_t *)NULL) {
      iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE, "%d", ENOPASS);
      return (GDB_ERROR);
    }
    if (db_dsn == (wchar_t *)NULL) {
      iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE, "%d", ENOCONS);
      return (GDB_ERROR);
    }

    try
    {
        hr = pConn.CreateInstance(__uuidof(Connection));
        _snwprintf( buffer, MAX_BUFFER_LEN, L"Provider=SQLOLEDB;Data Source=%s;Initial Catalog=%s;User ID=%s;Password=%s;",
                    server_address, database_name, db_user, db_pass);
        pConn->ConnectionTimeout = 30;
        pConn->ConnectionString = "";
        if(hr == S_OK)
            pConn->Open(buffer,"","",adConnectUnspecified);
        else
            return( GDB_ERROR );

        if(pCmd == NULL)
            pCmd.CreateInstance(__uuidof(Command));

        /* check for already connected */
        if ( pConn->GetState() == adStateOpen) {
            iomsg( DBG2,LAYER,TRUE,TRUE,NULL,TRUE, "%d", IDBCONE );
            cpp_display_sql_info();
            context[context_num].max_bind_name_len = 128; //Max length of column name for Sql Server 2005/2008
            return( GDB_SUCCESS );
        }
    }
    catch(_com_error e)
    {
        iomsg( DBG3,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EBADCON );
    }
    return( GDB_ERROR );
}

long cpp_sql_disconnect(long context_num)
{
    HRESULT hr = S_OK;
    context_num = gsi_current_context();
    if (debug & DBG1)
      iomsg (DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("SQL_DISCONNECT"));

    /* If the connection handle is null, send message that you are not connected */
    if ( pConn == NULL ) {        
      iomsg(DBG2,LAYER,TRUE,TRUE,NULL,TRUE, "%s", _T("Database is already disconnected."));
      return(GDB_SUCCESS);
    }

    if (pConn->State != adStateOpen){
      iomsg(DBG2,LAYER,TRUE,TRUE,NULL,TRUE, "%s", _T("Database is already disconnected."));
      return(GDB_SUCCESS);
    }

	try{
		if(pCmd != NULL)
			pCmd = NULL;

		if( pRst != NULL)
		{
			if(pRst->State == adStateOpen)
				pRst->Close();
			pRst = NULL;
		}
		pConn->Close();
		::CoUninitialize();
		return GDB_SUCCESS;

	}
	catch (_com_error e){
		iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not close connection"));
		iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
		return (GDB_ERROR);
	}
	return GDB_ERROR;
}

long cpp_sql_dealloc_descriptors(long shandle, long action )
{
    gSQLDA     *select_ptr;
    gSQLDA     *bind_ptr;
    long        status = 0;

    context_num = gsi_current_context();

    if (debug & DBG1)
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("SQL_DEALLOC_DESCRIPTORS"));

    if (shandle == 0) return (GDB_ERROR);

    if ( action == BIND )
    {
        if (debug & DBG6)
            iomsg(DBG6,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("- bind"));

        bind_ptr = sqlda_ptrs[context_num][shandle].bptr;

        if (bind_ptr ==  (gSQLDA *)NULL)
            return (GDB_SUCCESS);

        cpp_sql_release_bind( shandle, action );
        free((gSQLDA *)bind_ptr);
        bind_ptr = (gSQLDA *)NULL;
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("BIND Descriptor Memory Deallocated"));
        sqlda_ptrs[context_num][shandle].bptr = (gSQLDA *)NULL;
    }

    if (action == SELECT)
    {
        if (debug & DBG6)
            iomsg(DBG6,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("- select"));
        
        select_ptr = sqlda_ptrs[context_num][shandle].sptr;

        if (select_ptr ==  (gSQLDA *)NULL)
            return (GDB_SUCCESS);

        cpp_sql_release_bind( shandle, action );
        free((gSQLDA *)select_ptr);
        select_ptr = (gSQLDA *)NULL;
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("SELECT Descriptor Memory Deallocated"));
        sqlda_ptrs[context_num][shandle].sptr = (gSQLDA *)NULL;
    
        /* Make sure connection is valid */
        if ( pConn == NULL ) return GDB_EXT_ERROR ;
    }

    return (!status ? GDB_SUCCESS : GDB_EXT_ERROR);
}
long cpp_sql_alloc_descriptors(long shandle,long action)
{
    gSQLDA  *select_ptr;
    gSQLDA  *bind_ptr;
    long     retcode;

    context_num = gsi_current_context();

    if (debug & DBG1)
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("SQL_ALLOC_DESCRIPTORS"));

    if (shandle == 0) return (GDB_ERROR);

    if (action == BIND) 
    {
      /* cleanup if previously allocated */
      if ( sqlda_ptrs[context_num][shandle].bptr != (gSQLDA *)NULL)
        retcode = cpp_sql_dealloc_descriptors( shandle, BIND );

      /* alloc 1 descriptor for maximum bind vars */
      if ((bind_ptr = (gSQLDA *)calloc(context[context_num].max_bind_vars,
                       sizeof(gSQLDA))) == (gSQLDA *)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%d", EALDESC);
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
        return( GDB_ERROR );
      }

      /*** store bind addr in SQLDA_PTRS array ***/
      if (sqlda_ptrs[context_num] != (SQLDA_PTRS *)NULL)
        sqlda_ptrs[context_num][shandle].bptr = bind_ptr; 
      else {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could NOT store bind pointer in SQLDA_PTRS"));
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
        return (GDB_ERROR);                     
      } 
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Input (BIND) Descriptor Memory Allocated"));
    }

    if (action == SELECT)
    {
      /* cleanup if previously allocated */
      if ( sqlda_ptrs[context_num][shandle].sptr != (gSQLDA *)NULL)
        retcode = cpp_sql_dealloc_descriptors( shandle, SELECT );

      /* alloc 1 descriptor for each db column */
      if ((select_ptr = (gSQLDA *)calloc(max_col_array_size,sizeof(gSQLDA))) == (gSQLDA *)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%d", EALDESC);
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
        return( GDB_ERROR );
      }
           
      /*** store select addr in SQLDA_PTRS array ***/
      if (sqlda_ptrs[context_num] != (SQLDA_PTRS *)NULL)
        sqlda_ptrs[context_num][shandle].sptr = select_ptr; 
      else {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could NOT store select pointer in SQLDA_PTRS"));
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
        return (GDB_ERROR);                     
      } 
      iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Output (SELECT) Descriptor Memory Allocated"));
    }
    return (GDB_SUCCESS);
}

long cpp_sql_release_bind(long shandle,long action )
{
    long     col;
    gSQLDA  *select_ptr;
    gSQLDA  *bind_ptr;
    long     status = 0;

    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("SQL_RELEASE_BIND"));

    if (shandle == 0) return (GDB_ERROR);

    if (action == BIND) {
        bind_ptr = sqlda_ptrs[context_num][shandle].bptr;

        if (bind_ptr == (gSQLDA *)NULL)
            return (GDB_SUCCESS);

        for (col=0;col < context[context_num].max_bind_vars;col++) {

            /* deallocate the data and NULL indicator portions of the bind_ptr */
            if ( bind_ptr[col].data ) {
                free( bind_ptr[col].data );
                bind_ptr[col].data = NULL;
            }
            if ( bind_ptr[col].bdata ) {
                free( bind_ptr[col].bdata );
                bind_ptr[col].bdata = NULL;
            }
            if ( bind_ptr[col].ind ) {
                free( bind_ptr[col].ind );
                bind_ptr[col].ind = NULL;
            }
        }
    } /* end if (action == BIND) */


    if (action == SELECT) {
        select_ptr = sqlda_ptrs[context_num][shandle].sptr;

        if (select_ptr ==  (gSQLDA *)NULL)
            return (GDB_SUCCESS);

        for (col=0;col<select_ptr[0].ncols;col++) {

            if (select_ptr[col].colname != NULL) {
                free(select_ptr[col].colname);
                select_ptr[col].colname = NULL;
            }

            /* deallocate the data and NULL indicator portions of the select_ptr */
            if ( select_ptr[col].data ) {
                free( select_ptr[col].data );
                select_ptr[col].data = NULL;
            }
            if ( select_ptr[col].ind ) {
                free( select_ptr[col].ind );
                select_ptr[col].ind = NULL;
            }
        }
    } /* end if (action == SELECT) */

    return (GDB_SUCCESS);
}

long cpp_check_connection_hdl()
{   
    context_num = gsi_current_context();
    
    /* Check to see if the bridge thinks its connected */
    if ( pConn == NULL ) {
        g_sqlca.code = SQL_ERROR;
        iomsg( DBG3,LAYER,TRUE,TRUE,NULL,TRUE, "%d", ENODBCT );
        context[context_num].gbl_status.status = NOCONNECT_CD;
        return( FALSE );
    }
    if(pConn->State != adStateOpen)
        return( FALSE );

    /* We have a valid connection */
    return ( TRUE );
}
long cpp_sql_prepare(long shandle, long *stmt_id, wchar_t *sql_str )
{
	long      len;
        wchar_t  *odbc_sql_stmt;
	gSQLDA    *select_ptr;

	context_num = gsi_current_context();

	if (debug & DBG1)
	iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("SQL_PREPARE"));

	if (shandle == 0) return (GDB_ERROR);

	select_ptr = sqlda_ptrs[context_num][shandle].sptr;

	len = wcslen(sql_str);
	if (( odbc_sql_stmt = (wchar_t*)calloc(len+1,sizeof(wchar_t))) == NULL) {
	iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for sqlsvr_sql_stmt"));
	iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
	return (GDB_ERROR);
	}
	wcscpy(odbc_sql_stmt,sql_str);

	try{
		if(pCmd != NULL)
		{
			pCmd.Detach();
			pCmd = NULL;
		}
		pCmd.CreateInstance(__uuidof(Command));		
		pCmd->CommandType = adCmdText;
		pCmd->ActiveConnection = pConn;
		pCmd->CommandText = odbc_sql_stmt;
	}
	catch (_com_error e){
		iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not prepeared sql_str statement"));
		iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
		return (GDB_ERROR);
	}

	*stmt_id = shandle;

	free (odbc_sql_stmt);

	return GDB_SUCCESS;
}
short cpp_sql_describe_input(long  shandle,BIND_STRUCT *bind_vars,long *stmt_id,long *bind_processed,long action )
{
    gSQLDA         *bind_ptr;
    short           i,bvl;
    SQLSMALLINT     num_params;
	SQLSMALLINT   dnullable = 0;

    context_num = gsi_current_context();

	if( bind_vars == NULL)
		bind_vars = (BIND_STRUCT *)calloc(1,sizeof(BIND_STRUCT));
    if (debug & DBG1)
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("SQL_DESCRIBE_INPUT"));

    if (shandle == 0) return (GDB_ERROR);
    
    /* Make sure connection is valid */
    if ( !cpp_check_connection_hdl() ) return( GDB_EXT_ERROR );

    bind_ptr = sqlda_ptrs[context_num][shandle].bptr;
    if (bind_ptr == (gSQLDA *) NULL) {
        iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE, "%d", ENOTINI);
        return (GDB_ERROR);
    }
       
    /* Determine how many parameters the statement has */
    pConn->Errors->Clear();
	pCmd->Parameters->Refresh();
	num_params = (short)pCmd->GetParameters()->Count;
    rc = cpp_load_sql_err();
    if ( (rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO) ) {
        iomsg(DBG6,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not get parameter count for %"));
        return ( GDB_EXT_ERROR );
	}
	  if ( action == GDB_INIT ) {
        /* Make sure number of parameters is within range */
        if ( num_params > context[context_num].max_bind_vars) {
            iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE, "%d%d%d", EMBVEXD, num_params, context[context_num].max_bind_vars );
            num_params = 0; /* set to 0 to avoid dealloc problems */
            return ( GDB_ERROR );
        }
        bind_ptr[0].ncols = num_params;

        /* If there are no input parameters, return */
		if(bind_vars == NULL && num_params > 0)
		{
			g_sqlca.code = GDB_BIND_ERROR;
			return GDB_BIND_ERROR;
		}


        /*
        ** Load bind pointer structure with the existing info
        ** from the parameters (descriptors)
        */
		_variant_t vIndx;
		vIndx.vt = VT_I2;
		for(vIndx.iVal = 0;vIndx.iVal < num_params; vIndx.iVal++)
		{
			_variant_t vData;
			_ParameterPtr pParam = NULL;
			pParam =  pCmd->GetParameters()->GetItem(vIndx);          
			bind_ptr[vIndx.iVal].datatype = pParam->Type;
			bind_ptr[vIndx.iVal].colsize = pParam->Size;
			bind_ptr[vIndx.iVal].decdigs = pParam->Precision;
			//Check field is NULLBALE
			if (pParam->Attributes & adFldIsNullable)
				dnullable = 1;
			bind_ptr[vIndx.iVal].nullable = dnullable;

            rc = cpp_load_sql_err();
            if ( (rc != SQL_SUCCESS) && 
                 (rc != SQL_SUCCESS_WITH_INFO) ) {
                return ( GDB_EXT_ERROR );
            }

            /* Fudge colsize for date datatypes */
			switch(bind_ptr[vIndx.iVal].datatype )
			{
				case adDate:
				case adDBDate:
				case adDBTime:
				case adDBTimeStamp:					
					bind_ptr[vIndx.iVal].colsize = MAX_DATE_LEN;
					break;
			}
        }
 
    } /* end GDB_INIT */

    /* Check to see if bind vars are required */
    if ( (!bind_ptr[0].ncols) || (!bind_vars->nBind) ) {
        *bind_processed = TRUE;
        return( GDB_SUCCESS );
    }
    if (bind_ptr[0].ncols != bind_vars->nBind) {
        iomsg(DBG3,LAYER,TRUE,TRUE,NULL,FALSE, "%d%d%d", ENUMVAL, bind_vars->nBind, bind_ptr[0].ncols);
        return (GDB_ERROR);  
    }
      
    for (i=0;i<bind_ptr[0].ncols;i++) {
        bvl = wcslen(bind_vars->bind_array[i]);

        /* allocate space for the bind data */
        if ((bind_ptr[i].bdata = (wchar_t *)calloc(bvl+1,sizeof(wchar_t))) == (wchar_t *)NULL) {
            iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for bdata"));
            iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
            return (GDB_ERROR);
        }

        /* allocate space for the indicator */
        if ((bind_ptr[i].ind = (long *)calloc(1,sizeof(long))) == (long *)NULL) {
            iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc ind array"));
            iomsg(DBGM,LAYER,TRUE,TRUE,NULL,FALSE, "%d", EINSMEM);
            return (GDB_ERROR);
        }
        /* Copy into bind data into bdata */
        wcscpy(bind_ptr[i].bdata, bind_vars->bind_array[i]);

        /* Set the null indicator */
        /* ---------------------- */
        *bind_ptr[i].ind = SQL_NTS;
        if ((context[context_num].set_null_options & 0x2) && 
                ! _wcsicmp(bind_ptr[i].bdata, context[context_num].set_null_string))
            *bind_ptr[i].ind = SQL_NULL_DATA;
        else 
            if ((context[context_num].set_null_options & 0x4) && !_wcsicmp(bind_ptr[i].bdata, _T("NULL")))
                *bind_ptr[i].ind = SQL_NULL_DATA;

        rc = cpp_bind_parameter( bind_ptr, bind_ptr[i].datatype, i, context_num, shandle );
        if ( rc != GDB_SUCCESS ) return ( rc );

    }
    
    iomsg(DBG6,LAYER,TRUE,FALSE,NULL,FALSE, "%s%d", _T("Bind variables processed: %"), bind_ptr[0].ncols);
    *bind_processed = TRUE;

    /* close the cursor.  Do not worry about the error code */
    //rc = SQLCloseCursor( hstmt[context_num][shandle] );

    return ( GDB_SUCCESS );
}
SQLRETURN cpp_bind_parameter(gSQLDA *bind_ptr,long datatype,SQLSMALLINT bcol,long ctx,long hdl )
{
	SQLSMALLINT     pnum;	
    pnum = bcol + 1;
	_ParameterPtr pParam = NULL;
	VARIANT vtParam;
	char Chardata[100] = {'\0'};
	short dataLen = 0;
	_variant_t vIndx;
	vIndx.vt = VT_I2;
	vIndx.intVal = bcol;

	pParam =  pCmd->GetParameters()->GetItem(vIndx);
    switch ( datatype )
    {
	
		case adInteger:            
			vtParam.vt = VT_I2;
			vtParam.iVal = _wtoi(bind_ptr[bcol].bdata);
			break;
		case adBigInt:				
			vtParam.vt = VT_I4;
			vtParam.lVal = _wtol(bind_ptr[bcol].bdata);
			break;
		case adUnsignedBigInt:
		case adUnsignedInt:
		case adUnsignedSmallInt:                
		case adUnsignedTinyInt: 
			vtParam.vt = VT_UI4;
			vtParam.lVal = (unsigned int)_wtol(bind_ptr[bcol].bdata);			
			break;
		case adVarChar:
		case adChar:            
		case adBSTR:
			vtParam.vt = VT_BSTR;
			vtParam.bstrVal = (_bstr_t) bind_ptr[bcol].bdata;		
			break;
		case adCurrency:
			break;
		case adDate:
		case adDBDate:
		case adDBTime:
		case adDBTimeStamp:
			vtParam.vt = VT_BSTR;
			vtParam.bstrVal = (_bstr_t) bind_ptr[bcol].bdata;					
			break;
		case adDouble:			
			vtParam.vt = VT_R8;			
			dataLen = sizeof(vtParam.dblVal)+1;
			WideCharToMultiByte(CP_ACP,0,bind_ptr[bcol].bdata,-1,Chardata,dataLen,NULL,NULL);
			Chardata[dataLen] = '\0';							
			vtParam.dblVal = atof(Chardata);
			break;
		case adVarNumeric:
		case adDecimal:
		case adNumeric:
			break;
		case adSingle:		   
		   vtParam.vt = VT_R4;
		   dataLen = sizeof(vtParam.dblVal)+1;
		   WideCharToMultiByte(CP_ACP,0,bind_ptr[bcol].bdata,-1,Chardata,dataLen,NULL,NULL);
		   Chardata[dataLen] = '\0';							
		   vtParam.dblVal = atof(Chardata);
		   break;
		case adBoolean:            
		case adSmallInt:
		case adTinyInt:               
			vtParam.vt = VT_I2;
			vtParam.iVal = _wtoi(bind_ptr[bcol].bdata);
			break;
		case adVarWChar:
		case adWChar:			 			
			break;
		default:
			iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE, "%d%d%d",EINVDTY,
				bind_ptr[bcol].datatype, bcol);
			return (GDB_ERROR);
    } /* end switch */
	if( pParam != NULL )
		pParam->PutValue(vtParam);
	else
	{
		pParam = pCmd->CreateParameter("",(DataTypeEnum)bind_ptr[bcol].datatype,adParamInput,bind_ptr[bcol].colsize,vtParam);
		pCmd->Parameters->Append(pParam);
		pParam->PutValue(vtParam);
	}
    return cpp_load_sql_err();

}
long cpp_sql_describe_output(GENDA *sqlGen, long query_type )
{
	FieldPtr ptrFld = NULL;
	_variant_t Index;
    Index.vt = VT_I2;
	_variant_t vData;

	gSQLDA       *select_ptr;
    gSQLDA       *bind_ptr;
    SQLSMALLINT   scol;
    SWORD         num_cols;
    UWORD         dcol;
    SQLUINTEGER   ddatalen;
    SWORD         ddatatype;
    SQLUINTEGER   dcolsize;
    SQLSMALLINT   ddecdigs = 0;
	SQLSMALLINT   dprecisions = 0;
    SQLSMALLINT   dnullable = 0;
    static wchar_t   *dname=NULL;
    long          shandle;
    long          *stmt_id;
    long          *ncols; 
	
	/*OLEDB support next cursors*/
	/*    
	adOpenUnspecified = -1,
    adOpenForwardOnly = 0,
    adOpenKeyset = 1,
    adOpenDynamic = 2,
    adOpenStatic = 3	
	*/

    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("SQL_DESCRIBE_OUTPUT"));

    if (sqlGen == NULL) return (GDB_ERROR);
    shandle = sqlGen->stmt_handle ;
    stmt_id = &(sqlGen->stmt_id) ;
    ncols = &(sqlGen->ncols) ;
    if (shandle == 0) return (GDB_ERROR);

    /* Make sure connection is valid */
    if ( ! cpp_check_connection_hdl() ) return( GDB_EXT_ERROR );
	
    select_ptr = sqlda_ptrs[context_num][shandle].sptr;
    bind_ptr = sqlda_ptrs[context_num][shandle].bptr;

    /* get the actual # of columns */
	if(sqlGen->bind_processed != TRUE && pCmd->GetParameters()->Count != 0)
	{
		g_sqlca.code = GDB_BIND_ERROR;
		return( GDB_BIND_ERROR );	
	}
	
	if( bind_ptr->bdata == NULL && pCmd->GetParameters()->Count != 0)
	{
		g_sqlca.code = GDB_BIND_ERROR;
		return( GDB_BIND_ERROR );
	}

	try{
		if( pCmd->ActiveConnection == NULL){
			iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Internal Error!\nSQL command has not initialized"));            
			return (GDB_ERROR);
		}	
		if(pRst == NULL)
			pRst.CreateInstance(__uuidof(Recordset));
		switch( query_type )
		{
			case GDB_INIT:
				pRst->Open((_Command*)pCmd,vtMissing,adOpenForwardOnly,adLockOptimistic,adOptionUnspecified);
				break;
			case SELECT:
				pRst->Open((_Command*)pCmd,vtMissing,adOpenForwardOnly,adLockOptimistic,adOptionUnspecified);
				break;
			case STORED_PROC:      
				pRst = pCmd->Execute(NULL,NULL,adCmdStoredProc);
				break;
			case GDB_UPDATE:
			case GDB_EXECUTE:
			case BIND:
			default:
				 return( GDB_EXT_ERROR );
		}		
	}
	catch(_com_error e){  			
		return  0 ;
	}
	ptrFlds = pRst->GetFields();
    num_cols = (short)ptrFlds->GetCount();

    if ( num_cols > max_col_array_size) {
        iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE, "%d%d%d", ENCOLEX, num_cols, max_col_array_size);
        *ncols = 0; /* set to 0 to avoid dealloc problems */
        return (GDB_ERROR);
    }

    *ncols = (long)num_cols;
    /* decimal_flags is an array of flags used for tracking which columns are */
    /* type DECIMAL(x,0) where x >=9.  If we have already allocated it from a */
    /* prior query, release its memory.  Then, allocate a new array based upon*/
    /* the number of columns we currently have.  XCALLOC initializes all      */
    /* element to 0.                                                          */
    /* ---------------------------------------------------------------------- */
    if (sqlGen->decimal_flags) free(sqlGen->decimal_flags) ;
    sqlGen->decimal_flags = NULL ;
    if (*ncols)
    {
        sqlGen->decimal_flags = (char*)XCALLOC(*ncols, sizeof(char)) ;
        if (sqlGen->decimal_flags == NULL)
        {
            iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for decimal_flags array"));
            iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
            return (GDB_ERROR);
        }
    }

    /* realloc nSQLDA to the actual n needed */
    if ( (sqlda_ptrs[context_num][shandle].sptr = select_ptr = 
         (gSQLDA *)realloc(select_ptr, num_cols*sizeof(gSQLDA))) == (gSQLDA *)NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could NOT realloc memory for gSQLDA select pointer"));
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINMEMR);
        return (GDB_ERROR);                     
    }
    iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s%d", _T("SQLDA memory reallocated for % select-list items"), num_cols);
        
	if ( dname == (wchar_t *)NULL )
        if ((dname = (wchar_t *)calloc(context[context_num].max_bind_name_len+1,sizeof(wchar_t))) == (wchar_t *)NULL) {
            iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for dname"));
            iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
            return (GDB_ERROR);
        }

    for ( dcol=0; dcol< num_cols; dcol++ ) {
        /* describe each output column */
		Index.iVal = dcol;
		ptrFld = ptrFlds->GetItem(Index);
		vData.Clear();
		if(!wcslen(ptrFld->Name))
			vData = "UNKNOWN";
		else
			vData = ptrFld->Name;
		wcscpy(dname,vData.bstrVal);
		ddatalen = (long)ptrFld->DefinedSize;
		ddatatype = (int)ptrFld->GetType();
		dcolsize  = (long)ptrFld->DefinedSize;
		dprecisions = (long)ptrFld->Precision;		

		//Check field is NULLBALE
		if (ptrFld->GetAttributes()  & adFldIsNullable)
			dnullable = 1;

		if (ptrFld->Type == adNumeric || ptrFld->Type == adDecimal)                    
		{
			ddecdigs = ptrFld->GetNumericScale();
			dcolsize = dprecisions;
		}

		if(ptrFld->Type == adCurrency)
		{
			dcolsize = dprecisions;
			ddecdigs = 2;
		}
		if(ptrFld->Type == adGUID)
			dcolsize = dcolsize * 2 + 6;
		rc = cpp_load_sql_err();
                                 
        if ( rc < SQL_SUCCESS ) {
            iomsg(DBG6,LAYER,TRUE,FALSE,NULL,FALSE, "%s%d", _T("Could not get descriptor column info for %"), shandle );
            return (GDB_EXT_ERROR);
        }

        scol = dcol;

        /* assign values to select_ptr */
		select_ptr[scol].colname = (wchar_t *)calloc(context[context_num].max_bind_name_len+1,sizeof(wchar_t));
        wcscpy(select_ptr[scol].colname,dname);
        select_ptr[scol].ncols      = num_cols;
        select_ptr[scol].datatype   = ddatatype;
        select_ptr[scol].datalen    = ddatalen;
        select_ptr[scol].colsize    = dcolsize;   
        select_ptr[scol].decdigs    = ddecdigs;
        select_ptr[scol].nullable   = dnullable;
         
        /* Bind the data for the column */
        rc = cpp_bind_column( select_ptr, scol, context_num, shandle);
        //load_odbc_err( henv, hdbc[context_num], hstmt[context_num][shandle], rc );
        if ( rc != GDB_SUCCESS ) return ( GDB_ERROR );

    } /* end for loop */
	pRst->Close();
	pRst = NULL;
    return ( GDB_SUCCESS );
}
short cpp_bind_column(gSQLDA* select_ptr,short scol,long ctx,long hdl)
{
	FieldPtr		ptrFld = NULL;
	SQLSMALLINT     bind_col = 0;
	long            tlen = 0;	

	if(ptrFlds == NULL){
		iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Filed does not exist."));
		return (GDB_ERROR);
	}

	switch ( select_ptr[scol].datatype )
	{
		case adInteger:
			select_ptr[scol].datalen = sizeof( GDB_INT );
			if ( (select_ptr[scol].data = (wchar_t *) calloc(max_value_array_size+1, sizeof(long))) == (wchar_t *)NULL) {
				iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for column data"));
				iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
				return (GDB_ERROR);
			}
			if ( (select_ptr[scol].ind = (long *) calloc(max_value_array_size+1, sizeof(long))) == (long *)NULL) {
				iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for indicator data"));
				iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d" ,EINSMEM);
				return (GDB_ERROR);
			}

			break;
		case adBigInt:		
		case adUnsignedBigInt:
		case adUnsignedInt:
			select_ptr[scol].datalen = sizeof( GDB_INT );
			if ( (select_ptr[scol].data = (wchar_t *) calloc(max_value_array_size+1, sizeof(int))) == (wchar_t *)NULL) {
				iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for column data"));
				iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
				return (GDB_ERROR);
			}
			if ( (select_ptr[scol].ind = (long *) calloc(max_value_array_size+1, sizeof(long))) == (long *)NULL) {
				iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for indicator data"));
				iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
				return (GDB_ERROR);
			}			
			break;
		case adVarChar:
		case adChar:            
		case adBSTR:
		case adGUID:
			select_ptr[scol].datalen = select_ptr[scol].colsize;
			/* G2 can only handle strings 64k long */
			if ( select_ptr[scol].datalen > PR_MAX_GSI_STRING_LEN )
				select_ptr[scol].datalen = PR_MAX_GSI_STRING_LEN;

			/* allocate space for data and null indicator */      
			if ( (select_ptr[scol].data = (wchar_t *) calloc((select_ptr[scol].datalen+1)*(MAX_GSI_STRING_LEN / 100 +1), sizeof(wchar_t))) == (wchar_t *)NULL) {
				iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for column data"));
				iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
				return (GDB_ERROR);
			}
			if ( (select_ptr[scol].ind = (long *) calloc(max_value_array_size+1, sizeof(long))) == (long *)NULL) {
				iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for indicator data"));
				iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
				return (GDB_ERROR);
			}			
			break;
		case adDate:
		case adDBDate:
		case adDBTime:
		case adDBTimeStamp:
			select_ptr[scol].datalen = MAX_DATE_LEN;
			if ( (select_ptr[scol].data = (wchar_t *) calloc((select_ptr[scol].datalen+1)*(max_value_array_size+1), sizeof(wchar_t))) == (wchar_t *)NULL) {
				iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for column data"));
				iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
				return (GDB_ERROR);
			}
			if ( (select_ptr[scol].ind = (long *) calloc(max_value_array_size+1, sizeof(long))) == (long *)NULL) {
				iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for indicator data"));
				iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
				return (GDB_ERROR);
			}				
			break;
		case adDouble:
			select_ptr[scol].datalen = sizeof( GDB_DBL );
			if ( (select_ptr[scol].data = (wchar_t *) calloc(max_value_array_size+1, sizeof(double))) == (wchar_t *)NULL) {
			  iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for column data"));
			  iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
			  return (GDB_ERROR);
			}
			if ( (select_ptr[scol].ind = (long *) calloc(max_value_array_size+1, sizeof(long))) == (long *)NULL) {
			  iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for indicator data"));
			  iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
			  return (GDB_ERROR);
			}
			break;
		case adLongVarWChar:
		case adLongVarChar:
			/* allocate space for data and null indicator */  
			if ( select_ptr[scol].datalen > PR_MAX_GSI_STRING_LEN )
				select_ptr[scol].datalen = PR_MAX_GSI_STRING_LEN;
			if ( (select_ptr[scol].data = (wchar_t *) calloc((select_ptr[scol].datalen+1)*(MAX_XML_LEN  + 1), sizeof(wchar_t))) == (wchar_t *)NULL) {
				iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for column data"));
				iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
				return (GDB_ERROR);
			}
			if ( (select_ptr[scol].ind = (long *) calloc(max_value_array_size+1, sizeof(long))) == (long *)NULL) {
				iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for indicator data"));
				iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
				return (GDB_ERROR);
			}	
			break;
		case adVarNumeric:
		case adDecimal:
		case adNumeric:
		case adCurrency:
			//select_ptr[scol].datalen = select_ptr[scol].colsize;
			select_ptr[scol].datalen = select_ptr[scol].datalen + select_ptr[scol].decdigs + 2;
			/* allocate space for data and null indicator */
			tlen = select_ptr[scol].datalen + select_ptr[scol].decdigs + 2;
			if ( (select_ptr[scol].data =
			  (wchar_t *) calloc(tlen*(max_value_array_size+1), sizeof(wchar_t))) == (wchar_t *)NULL) {
			  iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for column data"));
			  iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
			  return (GDB_ERROR);
			}
			if ( (select_ptr[scol].ind = (long *) calloc(max_value_array_size+1, sizeof(long))) == (long *)NULL) {
			  iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for indicator data"));
			  iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
			  return (GDB_ERROR);
			}
			break;
		case adSingle:
		  select_ptr[scol].datalen = sizeof( GDB_FLOAT );
		  if ( (select_ptr[scol].data = 
			  (wchar_t *) calloc(sizeof(wchar_t)*max_value_array_size+1, sizeof(float))) == (wchar_t *)NULL) {
			  iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for column data"));
			  iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
			  return (GDB_ERROR);
		  }
		  if ( (select_ptr[scol].ind = (long *) calloc(max_value_array_size+1, sizeof(long))) == (long *)NULL) {
			  iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for indicator data"));
			  iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
			  return (GDB_ERROR);
		  }
		   break;
		case adBoolean:            
		case adSmallInt:
		case adTinyInt:
		case adUnsignedSmallInt:                
		case adUnsignedTinyInt:                
			select_ptr[scol].datalen = sizeof( GDB_SHORT );
			if ( (select_ptr[scol].data = (wchar_t *) calloc(max_value_array_size+1, sizeof(int))) == (wchar_t *)NULL) {
				iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for column data"));
				iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
				return (GDB_ERROR);
			}
			if ( (select_ptr[scol].ind = (long *) calloc(max_value_array_size+1, sizeof(long))) == (long *)NULL) {
				iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for indicator data"));
				iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
				return (GDB_ERROR);
			}
			break;
		case adVarWChar:
		case adWChar:			 
			/* G2 can only handle strings 64k long */
			if ( select_ptr[scol].datalen > PR_MAX_GSI_STRING_LEN )
				select_ptr[scol].datalen = PR_MAX_GSI_STRING_LEN;
			/* allocate space for data and null indicator */      
			if ( (select_ptr[scol].data = (wchar_t *) calloc((select_ptr[scol].datalen+1)*(MAX_VARWCHAR_LEN + 1), sizeof(short))) == (wchar_t *)NULL) {
				iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for column data"));
				iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
				return (GDB_ERROR);
			}
			if ( (select_ptr[scol].ind = (long *) calloc(max_value_array_size+1, sizeof(long))) == (long *)NULL) {
				iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for indicator data"));
				iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d",EINSMEM);
				return (GDB_ERROR);
			}			
			break;
		case adBinary:
		case adVarBinary:
		case adLongVarBinary:
			/* allocate space for data and null indicator */  
			if ( select_ptr[scol].datalen > MAX_BINARY_LEN )
				select_ptr[scol].datalen = MAX_BINARY_LEN;
			else
				select_ptr[scol].datalen = select_ptr[scol].datalen * 2 + 16;
			if ( (select_ptr[scol].data = (wchar_t *) calloc((select_ptr[scol].datalen+1)*(MAX_XML_LEN  + 1), sizeof(wchar_t))) == (wchar_t *)NULL) {
				iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for column data"));
				iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
				return (GDB_ERROR);
			}
			if ( (select_ptr[scol].ind = (long *) calloc(max_value_array_size+1, sizeof(long))) == (long *)NULL) {
				iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for indicator data"));
				iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
				return (GDB_ERROR);
			}	
			break;
		case adPropVariant:
		case adChapter:
		case adEmpty:
		case adError:
		case adFileTime:		
		case adIDispatch:
		case adIUnknown:				
		case adUserDefined:
		case adVariant:
		default:
			iomsg(DBG3,LAYER,TRUE,TRUE,NULL,TRUE, "%d%d%d", EINVDTY,
				select_ptr[scol].datatype, bind_col);
			return (GDB_ERROR);
			break;
	}  	
	return cpp_load_sql_err();

}
short cpp_load_sql_err()
{
    HRESULT  hr = S_OK;
    ErrorPtr  pError = NULL;
    long nCount = 0;
	_bstr_t  strError;
	g_sqlca.state_array[0].native_errlen = 0;
    g_sqlca.state_array[0].native_errmsg[0] = '\0';
    g_sqlca.code = 0; //l_rc;
    try
    {
		nCount = pConn->Errors->Count;
        long nCount = pConn->Errors->Count;
		if(!nCount)
			return GDB_SUCCESS;    

		g_sqlca.code = -1;
		for(long i = 0; i < nCount; i++ ) 
		{
            pError = pConn->Errors->GetItem(i);
			//
			strError = (LPCSTR)pError->SQLState;	
			wcscpy(g_sqlca.state_array[i].sqlstate,strError);
			//			
            g_sqlca.state_array[i].native_errcode = (DWORD)pError->NativeError;
			//
			strError = (LPCSTR)pError->Description;
			g_sqlca.state_array[i].native_errlen = strError.length() + 1;
            wcscpy(g_sqlca.state_array[i].native_errmsg,strError);
			//
		} 	
		pConn->Errors->Clear();
    }
    catch(_com_error e)
    {    
		return -1;
    }

	return -1;
}

   
/*======================================================================
cpp_display_sql_info
  - queries the SQLNCLI driver manager about the driver and displays results
  
  Arguments:
  - none
======================================================================*/
void cpp_display_sql_info()
{
	_RecordsetPtr  pRstSchema  = NULL;

	printf("SQL Server Info:\n" );
	printf("    Driver Manager Version: %s\n",(LPCSTR) pConn->Version);
	printf("    DBMS: %s  Version: %s\n", (LPCSTR) (_bstr_t) 
			pConn->Properties->GetItem("DBMS Name")->Value, (LPCSTR) (_bstr_t)
			pConn->Properties->GetItem("DBMS Version")->Value);
	pRstSchema = pConn->OpenSchema(adSchemaCatalogs);
	_bstr_t catalog_name = pRstSchema->Fields->GetItem("CATALOG_NAME")->Value;
	printf("Catalog Name: %s\n",(LPCSTR) catalog_name);
	pRstSchema->Close();
}
long cpp_sql_refresh_cursor(wchar_t *curs_name,long shandle)
{
	gSQLDA   *select_ptr;

    context_num = gsi_current_context();

    if (debug & DBG1) {
        if ( curs_name != (wchar_t *)NULL )
            iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s%s", _T("SQL_REFRESH: "),curs_name);
        else 
            iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("SQL_REFRESH"));
    }
    /* Make sure connection is valid */
    if ( ! cpp_check_connection_hdl()) return( GDB_EXT_ERROR );
    
    select_ptr = sqlda_ptrs[context_num][shandle].sptr;
	try
	{
		if(pRst != NULL)
			if(pRst->State == adStateOpen)
			{
				pRst->Close();
				pRst = NULL;
			}
	}
	catch(_com_error e){    
		return GDB_ERROR;
    }
    select_ptr[0].row_count = 0;
 
    return ( GDB_SUCCESS );
}
long cpp_sql_fetch(wchar_t* curs_name,long shandle )
{
    gSQLDA			*select_ptr;
	FieldPtr		ptrFld = NULL;
	_variant_t		Index;
	_variant_t		vData;
	wchar_t*		wChardata;
	long			num_cols = 0;
	long			nRecRead = 0;
	long			dataLen  = 0;
	long			Count	 = 0;
	unsigned char	*p		 = 0;
	int				i		 = 0;

#define MAX_ST_LEN 1024
	wchar_t			st[MAX_ST_LEN+1] = {'\0'};
    Index.vt = VT_I4;
    context_num = gsi_current_context();

    if (shandle == 0) return (GDB_ERROR);

    /* Make sure connection is valid */
    if ( !cpp_check_connection_hdl() ) return( GDB_EXT_ERROR );

    if (debug & DBG1)
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s%s", _T("SQL_FETCH: %"), curs_name);
    
    select_ptr = sqlda_ptrs[context_num][shandle].sptr;

    /* fetch record(s) */
	if(sqlfetch_cnt[context_num] != 0){
		sqlfetch_cnt[context_num] = 0;
		row_count[context_num] = select_ptr[0].row_count;
		g_sqlca.code = SQL_NO_DATA;
		return ( GDB_SUCCESS );
	}
	try{

		if(pRst != NULL && pRst->State == adStateOpen)
		{
			pRst->Close();
			pRst = NULL;
		}
		CMD_TYPE cmd_type = cpp_get_cmd_type(pCmd->CommandText);
		switch(cmd_type)
		{
			case CMD_SELECT:
				pRst = pCmd->Execute(NULL,NULL,adCmdText);
				break;
			case CMD_INSERT:
			case CMD_UPDATE:
			case CMD_DELETE:
				pCmd->Execute(NULL, NULL, adCmdStoredProc);
				break;
	
		}		
		ptrFlds = pRst->GetFields();
		num_cols = ptrFlds->GetCount();
		if(sqlfetch_cnt[context_num] == 0)
			pRst->MoveFirst();

		if(pRst->EOFile) {
			printf("Empty recordset!\n");
			sqlfetch_cnt[context_num] = nRecRead;    		
			select_ptr[0].row_count += sqlfetch_cnt[context_num];
			g_sqlca.code = SQL_ERROR;
			row_count[context_num] = select_ptr[0].row_count;
			return (GDB_SUCCESS);
		}
		while(!pRst->EOFile) {

			for (int scol=0; scol< num_cols; scol++ ) {
				Index.intVal = scol;
				ptrFld = ptrFlds->GetItem(Index);
				*select_ptr[scol].ind = (long) ptrFld->DefinedSize;	
				switch ( select_ptr[scol].datatype ){
				case adVarChar:
				case adChar:            
				case adBSTR:
				case adGUID: 
					dataLen = select_ptr[scol].datalen + 1;
					vData.Clear();
					vData = ptrFld->Value;
					if(vData.vt == VT_NULL)					
						vData.bstrVal = L"NULL";
					wChardata = new wchar_t[dataLen];
					wcscpy(wChardata,vData.bstrVal);
					wChardata[dataLen -1] = '\0';
					cpp_write_segment_data(select_ptr[scol].data,wChardata,dataLen,nRecRead);	
					delete [] wChardata;
					wChardata = NULL;
					break;
				case adUnsignedTinyInt:
				case adInteger:
				case adSmallInt:
				case adTinyInt:
					vData.Clear();
					vData = ptrFld->Value;
					((long*)select_ptr[scol].data)[nRecRead] = vData.intVal;
					select_ptr[scol].datalen = (long) ptrFld->DefinedSize;					
					break;
				case adBoolean:
					vData.Clear();
					vData = ptrFld->Value;
					((long*)select_ptr[scol].data)[nRecRead] = abs(vData.boolVal);
					select_ptr[scol].datalen = (long) ptrFld->DefinedSize;					
					break;
				case adDate:
				case adDBDate:
				case adDBTime:
				case adDBTimeStamp:
					dataLen = select_ptr[scol].datalen + 1;
					vData.Clear();
					vData = ptrFld->Value;	
					if(vData.vt == VT_NULL)					
						vData.bstrVal = L"NULL";	
					VariantChangeType(&vData, &vData, 0, VT_BSTR);
					wChardata = new wchar_t[dataLen];	
					wcscpy(wChardata,vData.bstrVal);
					wChardata[dataLen -1] = '\0';
					cpp_write_segment_data(select_ptr[scol].data,wChardata,dataLen,nRecRead);
					*select_ptr[scol].ind = dataLen - 1;
					delete [] wChardata;
					wChardata = NULL;
					break;	
				case adSingle:
					vData.Clear();
					vData.vt = VT_R4;
					vData.dblVal = ptrFld->Value;
					((float*)select_ptr[scol].data)[nRecRead] = (float)vData.dblVal;
					select_ptr[scol].datalen = (long) ptrFld->DefinedSize;
					*select_ptr[scol].ind = (long) ptrFld->ActualSize;
					break;
					break;
				case adDouble:
					vData.Clear();
					vData.vt = VT_R8;
					vData.dblVal = ptrFld->Value;
					((double*)select_ptr[scol].data)[nRecRead] = (double)vData.dblVal;
					select_ptr[scol].datalen = (long) ptrFld->DefinedSize;
					break;
				case adWChar:
				case adVarWChar:
				case adLongVarWChar:
				case adLongVarChar:
					vData.Clear();
					dataLen = select_ptr[scol].datalen + 1;
					vData = ptrFld->Value;
					if(vData.vt == VT_NULL)					
						vData.bstrVal = L"NULL";				
					wChardata = new wchar_t[dataLen];
					wcscpy(wChardata,vData.bstrVal);					
					wChardata[dataLen -1] = '\0';
					cpp_write_segment_data(select_ptr[scol].data,wChardata,dataLen,nRecRead);	
					delete [] wChardata;
					wChardata = NULL;
					break;
				case adBinary:
				case adVarBinary:
				case adLongVarBinary:
					dataLen = select_ptr[scol].datalen + 1;
					wChardata = new wchar_t[dataLen];
					memset(wChardata,0,dataLen);
					vData.Clear();
					vData = ptrFld->Value;	
					if(vData.vt == VT_NULL)					
						vData.bstrVal = L"NULL";
					else
					{

						p=(unsigned char *)vData.parray->pvData;					
						Count=vData.parray->rgsabound[0].cElements;
						wcscpy(wChardata,L"0x");
						for(i = 0;i<Count;i++)
						{
							_snwprintf(st, MAX_ST_LEN, L"%02x", p[i]);
							wcscat(wChardata,st);
						}
					}
					wChardata[dataLen -1] = '\0';
					cpp_write_segment_data(select_ptr[scol].data,wChardata,dataLen,nRecRead);	
					delete [] wChardata;
					wChardata = NULL;
					break;
				case adVarNumeric:
				case adDecimal:
				case adNumeric:
				case adCurrency:
					vData.Clear();
					vData = ptrFld->Value;
					if(vData.vt == VT_NULL)					
						vData.bstrVal = L"NULL";
					else
						vData.ChangeType(VT_BSTR,NULL);
					dataLen = select_ptr[scol].datalen + select_ptr[scol].decdigs + 2;
					wChardata = new wchar_t[dataLen];
					wcscpy(wChardata,vData.bstrVal);
					wChardata[dataLen -1] = '\0';
					cpp_write_segment_data(select_ptr[scol].data,wChardata,dataLen,nRecRead);	
					delete [] wChardata;
					wChardata = NULL;
					break;
				}
			}
			nRecRead++;
			pRst->MoveNext();
		}		
		pRst.Detach();
		pRst = NULL;
	}
    catch(_com_error e){    
		printf("Error\n");
		printf("\tCode = %08lx\n", e.Error());
		printf("\tCode meaning = %s", e.ErrorMessage());
		sqlfetch_cnt[context_num] = 0;		
		pRst.Detach();
		pRst = NULL;
		return GDB_ERROR;
    }
	sqlfetch_cnt[context_num] = nRecRead;
    
	if(num_cols > 0 ){
      select_ptr[0].row_count += sqlfetch_cnt[context_num];
      row_count[context_num] = select_ptr[0].row_count;
      return (GDB_SUCCESS);
    }
    return ( GDB_EXT_ERROR );
}

void cpp_write_segment_data(wchar_t* dest_data,wchar_t* segm_data,long len,long nrow)
{
	if(dest_data == NULL || segm_data == NULL)
		return;
	
	int seg_len = wcslen(segm_data);
	for(int i = 0; i< len;i++)
	{
		int j = nrow * len;
		if(i<= seg_len)
			dest_data[j + i] = segm_data[i];
		else
			dest_data[j + i] = '\0';
	}
}
long cpp_sql_exec_sql( wchar_t *stmt_str )
{
	long        len = 0;
	_variant_t	vRowAffect;  
    wchar_t       *sql_stmt = NULL;
    HSTMT       exec_hstmt;
    SQLINTEGER  rows_affected = 0;
	_CommandPtr     pCmdStmt = NULL;
	SQLRETURN rc = 0;
    context_num = gsi_current_context();

    if (debug & DBG1)
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("SQL_EXEC_SQL"));

    /* Make sure connection is valid */
    if ( !cpp_check_connection_hdl()) return GDB_EXT_ERROR ;
 
    /* allocate a statement handle */
	try{
    
	pCmdStmt.CreateInstance(__uuidof(Command));
    len = wcslen(stmt_str);
    if ((sql_stmt = (wchar_t*)calloc(len+1,sizeof(wchar_t))) == NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for odbc_sql_stmt"));
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
        return ( GDB_ERROR );
    }
    wcscpy( sql_stmt, stmt_str );
    /* execute the statement */
	pConn->Errors->Clear();
	pCmdStmt->ActiveConnection = pConn;
	pConn->BeginTrans();
    pCmdStmt->CommandText = sql_stmt;
	CMD_TYPE cmd_type = cpp_get_cmd_type(sql_stmt);
	switch(cmd_type)
	{
		case CMD_SELECT:
			vRowAffect.lVal = -1;
			break;
		case CMD_INSERT:
		case CMD_UPDATE:
		case CMD_DELETE:
			pCmdStmt->Execute(&vRowAffect, NULL, adCmdText);
			break;
		}	
	}
	catch(_com_error e){   
		rc = cpp_load_sql_err();
		printf("Error: \n");
		sqlfetch_cnt[context_num] = 0;
		if ( rc < SQL_SUCCESS ) {
			free ((wchar_t *)sql_stmt);
			pCmdStmt.Detach();
			pCmdStmt = NULL;
		}
		pConn->RollbackTrans();
		return( GDB_EXT_ERROR );
    }   

    if ( rc == SQL_NO_DATA ) {
        /* Do not call SQLRowCount if statement returns no data */
        rows_affected = 0;
    }
    else {
        /* Get the number of rows affected */
		rows_affected = vRowAffect.lVal;
        rc = cpp_load_sql_err();
        if ( (rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO) ) {
            return ( GDB_EXT_ERROR );
        }
    }
    row_count[context_num] = rows_affected;

    /* free the statement handle */
   
    rc = cpp_load_sql_err();
    exec_hstmt = NULL;

    free ( (wchar_t *)sql_stmt );
	pCmdStmt.Detach();
	pCmdStmt = NULL;
    return ( rc < SQL_SUCCESS ? GDB_EXT_ERROR : GDB_SUCCESS);
}
long cpp_sql_commit()
{
	RETCODE    lrc = -1;
	HRESULT	   hr = 1;
	SQLRETURN  rc = -1;

    context_num = gsi_current_context();

    if (debug & DBG1)
      iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("SQL_COMMIT"));
	if(pConn != NULL)
	{
		if(pConn->State == adStateOpen)
		{
			hr = pConn->raw_CommitTrans();
			if(hr != 0)
				g_sqlca.code = SQL_ERROR;
			else
    rc = cpp_load_sql_err();
		}
		else
			g_sqlca.code = SQL_NO_DATA_FOUND;
	}
	else
		g_sqlca.code = SQL_ERROR;

    return ( lrc < 0 ? GDB_EXT_ERROR : GDB_SUCCESS );
}
long cpp_sql_rollback()
{
	RETCODE    lrc = -1;
	HRESULT	   hr = 1;
	SQLRETURN  rc = -1;

    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("SQL_ROLLBACK"));
    
	if(pConn != NULL)
	{
		if(pConn->State == adStateOpen)
		{
			hr = pConn->raw_RollbackTrans();
			if(hr != 0)
				g_sqlca.code = SQL_ERROR;
			else
    rc = cpp_load_sql_err();
		}
		else
			g_sqlca.code = SQL_NO_DATA_FOUND;
	}
	else
		g_sqlca.code = SQL_ERROR;	
    return ( lrc < SQL_SUCCESS ? GDB_EXT_ERROR : GDB_SUCCESS );
}
CMD_TYPE cpp_get_cmd_type(wchar_t* sql_stmt)
{
	CMD_TYPE cmd_type;
	sql_stmt = _wcsupr(sql_stmt);
	if(wcsstr(sql_stmt,L"SELECT") != NULL)
		cmd_type = CMD_SELECT;
	else if(wcsstr(sql_stmt,L"INSERT") != NULL)
		cmd_type = CMD_INSERT;
	else if(wcsstr(sql_stmt,L"UPDATE") != NULL)
		cmd_type = CMD_UPDATE;
	else if(wcsstr(sql_stmt,L"DELETE") != NULL)
		cmd_type = CMD_DELETE;
	return cmd_type;
}
long cpp_sql_trigger(wchar_t* trig_name,long trig_timeout,wchar_t* trig_ret_msg,long context_num )
{
	short       i;
    int         len;
    wchar_t        test_trig_name[MAX_TRIGGER_NAME_LEN+1];
    SQLINTEGER  parmlen1=SQL_NTS, parmlen2=SQL_NTS, parmlen3=SQL_NTS;
    SQLINTEGER  parmlen=0;
    static long p_stat;
    static wchar_t t_msg[200];
    static wchar_t t_datetime[100];

	_CommandPtr pCmdTrig = NULL;
	_RecordsetPtr pRstRes = NULL;
    
    /* 
    ** CAUTION: context_num is passed from L1 as we are outside of
    ** run-loop during check (i.e. not within a context). Therefore
    ** you MUST NOT call any other function that utilizes a context
    ** number derived from gsi_current_context()
	*/

    len = wcslen(trig_name);
    if (len > MAX_TRIGGER_NAME_LEN) {
        return (GDB_ERROR);
    }
    wcscpy( test_trig_name, trig_name );

    /*
    ** Only allocate the statement handle and do the bindings
    ** once.
    */
    if ( ! trig_hstmt[context_num] ) {

		if ( !cpp_check_connection_hdl()) return GDB_EXT_ERROR ;
		rc = cpp_load_sql_err();
        if ( rc < SQL_SUCCESS ) return( GDB_EXT_ERROR );

        /*
        ** Fetch a row of information for the given trigger name from the
        ** trigger table and then delete that row. Both of these operations
        ** are done in the g2odbc_proc_trigs procedure
        */
	        
		try{
			if(pCmdTrig == NULL)
				pCmdTrig.CreateInstance(__uuidof(Command));			
			pCmdTrig->ActiveConnection = pConn;
			pConn->Errors->Clear();		
			pCmdTrig->CommandType = adCmdStoredProc;
			pCmdTrig->CommandText = _bstr_t("g2odbc_proc_trigs");
			pCmdTrig->Parameters->Refresh();			

			/* Bind the first parameter: trigger name (input) */
			VARIANT vTrigName;		
			vTrigName.vt = VT_BSTR;
			vTrigName.bstrVal = _bstr_t(test_trig_name);
			_ParameterPtr trigParam = NULL;
			trigParam = pCmdTrig->CreateParameter("@t_name",adChar,adParamInput,len,vTrigName);
			pCmdTrig->Parameters->Item[ _variant_t( (long) 1 ) ]->Value = vTrigName;

			/* Bind the second parameter: msg (output) */						
			VARIANT vMsg;
			vMsg.vt = VT_BSTR;
			vMsg.bstrVal = _bstr_t("");

			/* Bind the third parameter: timestamp (output) */
			VARIANT vTime;
			vTime.vt = VT_DATE;

			/* Bind the fourth parameter: status output */
			VARIANT vStatus;
			vStatus.vt = VT_I4;
			vStatus.intVal = 0;

			pRstRes = pCmdTrig->Execute(NULL,NULL,adCmdStoredProc); 		

			vMsg = pCmdTrig->Parameters->Item[ _variant_t( (long) 2 ) ]->Value ;
			vTime = pCmdTrig->Parameters->Item[ _variant_t( (long) 3 ) ]->Value ;
			vStatus = pCmdTrig->Parameters->Item[ _variant_t( (long) 4 ) ]->Value ;			
			wcscpy(t_msg,vMsg.bstrVal);
			//WideCharToMultiByte(CP_ACP,0,vMsg.bstrVal,-1,t_msg,sizeof(t_msg),NULL,NULL);
			VariantChangeType(&vTime, &vTime, 0, VT_BSTR);				
			wcscpy(t_datetime,vTime.bstrVal);
			//WidewCharToMultiByte(CP_ACP,0,vTime.bstrVal,-1,t_datetime,sizeof(t_datetime),NULL,NULL);
			p_stat = vStatus.intVal;
			pCmdTrig.Detach();
			pCmdTrig = NULL;
		}
		catch(_com_error e){  			
			rc = cpp_load_sql_err();
			*trig_ret_msg = 0;
			if ( rc < SQL_SUCCESS ) {
				pCmdTrig.Detach();
				pCmdTrig = NULL;
			}
			return( GDB_EXT_ERROR );
		}
    }

    if ( (rc == SQL_SUCCESS) || (rc == SQL_SUCCESS_WITH_INFO) ) {
        if ( p_stat != SQL_NO_DATA ) {
            /* Remove the trailing blanks from message and date */
            for (i=wcslen(t_msg)-1; (i>=0) && (t_msg[i]==' '); t_msg[i--]='\0' );
            for (i=wcslen(t_datetime)-1; (i>=0) && (t_datetime[i]==' '); t_datetime[i--]='\0' );
            _snwprintf( trig_ret_msg, MAX_TRIGGER_NAME_LEN,_T("%s <%s>"), t_msg, t_datetime );
        }
        else
            *trig_ret_msg = 0;
    }
    else {
        /* 
        ** The following prevents a continuous loop in check_triggers
        ** (never returning to gsi_run_loop) if the database connection
        ** gets dropped.
        */
        *trig_ret_msg = 0;
        if (context[context_num].console_output) {
            if (context[context_num].name != (wchar_t *)NULL)
                wprintf(_T("G2-MSSQL: %s: %s: %d %s\n"), context[context_num].name,
                    ERROR_SYM, rc, _T("an error"));
            else
                wprintf(_T("G2-MSSQL: %d: %s: %d %s\n"), context_num, ERROR_SYM,
		            rc, _T("an error"));
        }
        return( GDB_EXT_ERROR );
    }
    return (GDB_SUCCESS);
}
long cpp_sql_exec_stored_proc( wchar_t* sql_stmt )
{
    long		len_f,len_l,datatype;
	short		col;
    wchar_t*    odbc_sql_stmt;
	wchar_t*	proc_name;
	short		num_args = 0;
	short		dataLen = 0;  
	wchar_t*	token;
	wchar_t** data_args = NULL;
	_CommandPtr pCmdProc = NULL;
	char Chardata[100] = {'\0'};
    context_num = gsi_current_context();

    if (debug & DBG1)
        iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("SQL_EXEC_STORED_PROC"));

    /* Make sure connection is valid */
   		if ( !cpp_check_connection_hdl()) return GDB_EXT_ERROR ;
			rc = cpp_load_sql_err();
		if ( rc < SQL_SUCCESS ) return( GDB_EXT_ERROR );

    len_f = wcslen( sql_stmt );
	proc_name = wcsstr(sql_stmt,L"(");
	len_l = (proc_name - sql_stmt) + 1;

    if ((odbc_sql_stmt = (wchar_t*)calloc(len_l,sizeof(wchar_t))) == NULL) {
        iomsg(DBG6|DBG9,LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("Could not alloc mem for odbc_sql_stmt"));
        iomsg(DBGM,LAYER,TRUE,TRUE,NULL,TRUE, "%d", EINSMEM);
        return ( GDB_ERROR );
    }
	wcsncpy(odbc_sql_stmt,sql_stmt,len_l - 1);
	sql_stmt = proc_name + 1;
	sql_stmt[len_f - len_l - 1] = '\0';
	//int dataLen = sizeof(vtParam.dblVal)+1;
	//WideCharToMultiByte(CP_ACP,0,data_args[vIndx.iVal - 1],-1,Chardata,dataLen,NULL,NULL);
	//Chardata[dataLen] = '\0';							
	//vtParam.dblVal = atof(Chardata);
	//StrTrim(odbc_sql_stmt,L" \0");
	try
	{

		/* execute the statement */
		pCmdProc.CreateInstance(__uuidof(Command));
		pCmdProc->ActiveConnection = pConn;
		pCmdProc->CommandText = odbc_sql_stmt;
		pCmdProc->CommandType = adCmdStoredProc;
		pCmdProc->Parameters->Refresh();
		num_args = (short)pCmdProc->GetParameters()->Count;
		if( num_args > 1 )		
			data_args = (wchar_t**)calloc(num_args - 1,sizeof(wchar_t*)); 
		
		token = wcstok( sql_stmt, L",");
		for(col = 0;col < num_args - 1;col++)
		{			
			
			if(token != NULL)
			{
				//StrTrim(token,L" '\0");
				short len = wcslen(token);
				data_args[col] = (wchar_t*)calloc(len + 1,sizeof(wchar_t));
				wcsncpy(data_args[col],token,len);
				data_args[col][len] = '\0';
			}
			token = wcstok( NULL, L",");

		}

		_variant_t vIndx;
		vIndx.vt = VT_I2;
		for(vIndx.iVal = 1;vIndx.iVal < num_args ; vIndx.iVal++)
		{
			_variant_t vtParam;
			_ParameterPtr pParam = NULL;
			_ParameterPtr pNew= NULL;
			pParam =  pCmdProc->GetParameters()->GetItem(vIndx);  
			datatype = pParam->Type;
			wchar_t* pName = pParam->GetName();
			pNew = pCmdProc->CreateParameter(pName,pParam->Type,pParam->Direction,pParam->GetSize(),vtParam);
			switch ( datatype )
			{
			
				case adInteger:            
					vtParam.vt = VT_I2;
					vtParam.iVal = _wtoi(data_args[vIndx.iVal - 1]);
					pCmdProc->Parameters->Item[ vIndx.iVal ]->Value = vtParam;
					break;
				case adBigInt:				
					vtParam.vt = VT_I4;
					vtParam.lVal = _wtol(data_args[vIndx.iVal - 1]);
					pCmdProc->Parameters->Item[ vIndx.iVal ]->Value = vtParam;
					break;
				case adUnsignedBigInt:
				case adUnsignedInt:
				case adUnsignedSmallInt:                
				case adUnsignedTinyInt: 
					vtParam.vt = VT_UI4;
					vtParam.lVal = (unsigned int)_wtol(data_args[vIndx.iVal - 1]);	
					pCmdProc->Parameters->Item[ vIndx.iVal ]->Value = vtParam;
					break;
				case adVarChar:
				case adChar:            
				case adBSTR:
					pCmdProc->Parameters->Item[ vIndx.iVal ]->Value = _bstr_t(data_args[vIndx.iVal - 1]);
					break;				
				case adCurrency:
					break;
				case adDate:
				case adDBDate:
				case adDBTime:
				case adDBTimeStamp:								
					if(wcsstr(data_args[vIndx.iVal - 1],L"NULL\0") != NULL)
					{
						vtParam.vt = VT_NULL;										
						pCmdProc->Parameters->Item[ vIndx.iVal ]->Value = vtParam;
					}
					else
						pCmdProc->Parameters->Item[ vIndx.iVal ]->Value = _bstr_t(data_args[vIndx.iVal - 1]);
					break;
				case adDouble:
					vtParam.vt = VT_R8;
					dataLen = sizeof(vtParam.dblVal)+1;
					WideCharToMultiByte(CP_ACP,0,data_args[vIndx.iVal - 1],-1,Chardata,dataLen,NULL,NULL);
					Chardata[dataLen] = '\0';							
					vtParam.dblVal = atof(Chardata);					
					pCmdProc->Parameters->Item[ vIndx.iVal ]->Value = vtParam;
					break;
				case adVarNumeric:
				case adDecimal:
				case adNumeric:
					break;
				case adSingle:		   
				   vtParam.vt = VT_R4;
				   dataLen = sizeof(vtParam.dblVal)+1;
				   WideCharToMultiByte(CP_ACP,0,data_args[vIndx.iVal - 1],-1,Chardata,dataLen,NULL,NULL);
				   Chardata[dataLen] = '\0';							
				   vtParam.dblVal = atof(Chardata);
				   pCmdProc->Parameters->Item[ vIndx.iVal ]->Value = vtParam;
				   break;
				case adBoolean:            
				case adSmallInt:
				case adTinyInt:               
					vtParam.vt = VT_I2;
					vtParam.iVal = _wtoi(data_args[vIndx.iVal - 1]);
					pCmdProc->Parameters->Item[ vIndx.iVal ]->Value = vtParam;
					break;
				case adVarWChar:
				case adWChar:			 			
					break;
				default:
					return (GDB_ERROR);
			} 
		}

        rc = cpp_load_sql_err();
        if ( (rc != SQL_SUCCESS) && 
             (rc != SQL_SUCCESS_WITH_INFO) ) {
            return ( GDB_EXT_ERROR );
        }

		pCmdProc->Execute(NULL, NULL, adCmdStoredProc);

		//free ADO resources
		rc = cpp_load_sql_err();
		if ( rc < SQL_SUCCESS ) return( GDB_EXT_ERROR );
		pCmdProc.Detach();
		pCmdProc = NULL;
		free ( (wchar_t *)odbc_sql_stmt );
		if(data_args != NULL)
		{
			if(num_args > 1)
			{
				for(col = 0;col < num_args - 1;col++)
					free ( (wchar_t *)data_args[col]);				
			}
			free ( (wchar_t**)data_args );
		}
	}
	catch(_com_error e){  			
		rc = cpp_load_sql_err();

		if ( rc < SQL_SUCCESS ) {
			pCmdProc.Detach();
			pCmdProc = NULL;	
			free ( (wchar_t *)odbc_sql_stmt );
			if(data_args != NULL)
			{
				if(num_args > 1)
				{
					for(col = 0;col < num_args - 1;col++)
						free ( (wchar_t *)data_args[col]);				
				}
				free ( (wchar_t**)data_args );
			}
		}
		return( GDB_EXT_ERROR );
	}

    return ( rc < SQL_SUCCESS ? GDB_EXT_ERROR : GDB_SUCCESS);

}
long cpp_sql_exec_stored_proc_return(wchar_t *proc_name, wchar_t *proc_args, wchar_t *proc_ret_val )
{
	_CommandPtr pCmdProc = NULL;
    context_num = gsi_current_context();
	wchar_t ret_val[1024];	
	VARIANT vRet;
	vRet.vt = VT_BSTR;
	vRet.bstrVal = _bstr_t("");	

    if (debug & DBG1)
        iomsg(DBG1,-LAYER,TRUE,FALSE,NULL,FALSE, "%s", _T("SQL_EXEC_STORED_PROC"));

    /* Make sure connection is valid */
   	if ( !cpp_check_connection_hdl()) return GDB_EXT_ERROR ;
		rc = cpp_load_sql_err();
	if ( rc < SQL_SUCCESS ) return( GDB_EXT_ERROR );

	/* Initialize return string to null string */
	/* --------------------------------------- */
	memset(proc_ret_val,0,EXSPRET_SZ+1) ;
	try
	{
		/* execute the statement */
		pCmdProc.CreateInstance(__uuidof(Command));
		pCmdProc->ActiveConnection = pConn;
		pCmdProc->CommandText = "sp_handler";
		pCmdProc->CommandType = adCmdStoredProc;
		pCmdProc->Parameters->Refresh();
		pCmdProc->Parameters->Item[ _variant_t( (long) 1 ) ]->Value = _bstr_t(proc_name);
		pCmdProc->Parameters->Item[ _variant_t( (long) 2 ) ]->Value =  _bstr_t(proc_args);																				
		
		pCmdProc->Execute(NULL,NULL,adCmdStoredProc); 
		
		vRet = pCmdProc->Parameters->Item[ _variant_t( (long) 3 ) ]->Value;
		wcscpy(ret_val,vRet.bstrVal);
		//Widewchar_tToMultiByte(CP_ACP,0,vRet.bstrVal,-1,ret_val,sizeof(ret_val),NULL,NULL);
		wcscpy(proc_ret_val,ret_val);
		pCmdProc.Detach();
		pCmdProc = NULL;		
        rc = cpp_load_sql_err();
        if ( (rc != SQL_SUCCESS) && 
             (rc != SQL_SUCCESS_WITH_INFO) ) {
            return ( GDB_EXT_ERROR );
        }
	}
	catch(_com_error e){  			
		rc = cpp_load_sql_err();

		if ( rc < SQL_SUCCESS ) {
			pCmdProc.Detach();
			pCmdProc = NULL;
		}
		return( GDB_EXT_ERROR );
	}
    return ( rc < SQL_SUCCESS ? GDB_EXT_ERROR : GDB_SUCCESS);
}
