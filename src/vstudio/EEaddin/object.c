#include "custview.h"

HRESULT FormatLIST(DEBUGHELPER*, unsigned __int64, char*, size_t);
HRESULT FormatARRAY(unsigned int, unsigned int, DEBUGHELPER*, unsigned __int64, char*, size_t);
HRESULT FormatSYMBOL(unsigned int, DEBUGHELPER*, unsigned __int64, char*, size_t);
HRESULT FormatDOUBLE(DEBUGHELPER*, unsigned __int64, char*, size_t);

ADDIN_API HRESULT WINAPI AddIn_OBJECT( DWORD dwAddress,
                                       DEBUGHELPER *pHelper,
                                       int nBase,
                                       BOOL bUniStrings,
                                       char *pResult,
                                       size_t maxResult,
                                       DWORD reserved )
{
    /* Get the 64-bit pointer we want to inspect */
    unsigned __int64 dlDataPtr = pHelper->GetRealAddress(pHelper);
    Object o = (Object) dlDataPtr;
    SI_Header header;
    DWORD dwNumRead = 0;
    HRESULT ReadResult;

    /* handle NIL */
    if (o == NIL) {
        sprintf_s(pResult, maxResult, "NIL");
        return S_OK;
    }

    /* Handle immediate (sometimes NIL is immediate too) */
    if (SI_IMMEDIATEP(o)) {
        if (FIXNUMP(o)) {
            sprintf_s(pResult, maxResult, "%d", IFIX(o));
        } else if (CHARACTERP(o)) {
            sprintf_s(pResult, maxResult, "#\\%c", CHR_CODE(o));
        } else if (o == _) {
            sprintf_s(pResult, maxResult, "_UNSUPPLIED");
        } else if (o == UNBOUND) {
            sprintf_s(pResult, maxResult, "_UNBOUND");
        } else if (o == PROTECT_MARKER) {
            sprintf_s(pResult, maxResult, "_PROTECT_MARKER");
        } else if (o == SI_UNWIND_PROTECT_MARKER) {
            sprintf_s(pResult, maxResult, "_UNWIND_PROTECT_MARKER");
        } else if (o == SI_NO_APPLICABLE_METHOD_MARKER) {
            sprintf_s(pResult, maxResult, "_NO_APPLICABLE_METHOD_MARKER");
        } else if (o == SI_UNINITIALIZED_MARKER) {
            sprintf_s(pResult, maxResult, "_UNINITIALIZED");
        } else if (o == SI_ALIGNMENT_MARKER) {
            sprintf_s(pResult, maxResult, "_GC_ALIGNING");
        } else if (o == SI_FORWARDING_MARKER) {
            sprintf_s(pResult, maxResult, "_GC_FORWARDING");
        } else if (o == SI_NONRELOCATABLE_MARKER) {
            sprintf_s(pResult, maxResult, "_GC_NONRELOCATABLE");
        } else {
            sprintf_s(pResult, maxResult, "unknown immediate?!");
        }
        return S_OK;
    }

    /* Read the first 4 bytes Object */
    ReadResult = pHelper->ReadDebuggeeMemoryEx(pHelper, dlDataPtr, sizeof(SI_Header), &header, &dwNumRead);

    /* Check for read Errors */
    if (FAILED(ReadResult) || dwNumRead != sizeof(SI_Header))
    {
        sprintf_s(pResult, maxResult, "Error reading SI_Header (%d)", sizeof(SI_Header));
        return S_OK; // always return S_OK
    }

    switch (header.type) {
    case SI_GENERAL_ARRAY_TYPE:
    case SI_PRIMITIVE_VECTOR_TYPE:
        return FormatARRAY(header.type, header.stuff, pHelper, dlDataPtr, pResult, maxResult);
        break;
    case SYMBOL_TYPE:   /* non-external initial symbol */
    case MSYMBOL_TYPE:  /* non-external non-initial symbol */
    case USYMBOL_TYPE:  /* uninterned symbol */
    case ESYMBOL_TYPE:  /* external initial symbol */
    case EMSYMBOL_TYPE: /* external non-initial symbol */
    case KEYWORD_TYPE:	/* initial keyword */
    case MKEYWORD_TYPE:	/* non-initial keyword */
        return FormatSYMBOL(header.type, pHelper, dlDataPtr, pResult, maxResult);
        break;
    case DOUBLE_TYPE:
        return FormatDOUBLE(pHelper, dlDataPtr, pResult, maxResult);
        break;
    }

    /* CONS is special: in current config it doesn't have a SI_Header */
    if (header.tag != SI_HEADER_TAG) {
        return FormatLIST(pHelper, dlDataPtr, pResult, maxResult);
    } else {
        sprintf_s(pResult, maxResult, "other object (%d)", header.type);
        return S_OK;
    }
}

void g2ext_heap_command_line(int argc, char *argv[]) {}
void g2ext_print_backtrace() {}
long g2ext_write_string_to_console() { return 0;}
Object Gensym_error_message_buffer = 0;
Object g2int_error_handler() { return 0;}
Object g2_region_memory_usage(Object region_number) { return 0;}

/* Code from the project wizard (normally in dllmain.cpp) */
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
