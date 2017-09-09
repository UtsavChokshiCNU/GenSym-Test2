#include "custview.h"
#include <stdlib.h>

#define SYMBOL_NAME_LENGTH 32

HRESULT FormatSYMBOL(unsigned int type, DEBUGHELPER *pHelper, unsigned __int64 dlDataPtr, char *pResult, size_t maxResult)
{
    DWORD dwNumRead = 0;
    HRESULT ReadResult;
    SI_Noninitial_symbol *non_initial_symbol;
    size_t data_length;
    char *iname;

    if (type != MSYMBOL_TYPE && type != MKEYWORD_TYPE) {
        sprintf_s(pResult, maxResult, "#<other symbol (%d %d)>", type, MSYMBOL_TYPE);
        return S_OK;
    }

    data_length = sizeof(SI_Noninitial_symbol) + 1 + SYMBOL_NAME_LENGTH;
    non_initial_symbol = (SI_Noninitial_symbol*) malloc(data_length);

    ReadResult = pHelper->ReadDebuggeeMemoryEx(pHelper, dlDataPtr, data_length, non_initial_symbol, &dwNumRead);
    if (FAILED(ReadResult)) {
        sprintf_s(pResult, maxResult, "Error reading symbol");
        return S_OK;
    } else if (dwNumRead != data_length) {
        sprintf_s(pResult, maxResult, "Error reading symbol (%d)", data_length);
        return S_OK;
    }

    iname = MSYMBOL_NAME(non_initial_symbol);
    sprintf_s(pResult, maxResult, "%s", iname);
    return S_OK;
}

HRESULT FormatDOUBLE(DEBUGHELPER *pHelper, unsigned __int64 dlDataPtr, char *pResult, size_t maxResult)
{
    DWORD dwNumRead = 0;
    HRESULT ReadResult;
    SI_Double_float dfloat;

    ReadResult = pHelper->ReadDebuggeeMemoryEx(pHelper, dlDataPtr, sizeof(SI_Double_float), &dfloat, &dwNumRead);
    if (FAILED(ReadResult) || dwNumRead != sizeof(SI_Double_float)) {
        sprintf_s(pResult, maxResult, "Error reading double (%d)", dwNumRead);
        return S_OK;
    }

    sprintf_s(pResult, maxResult, "%f", dfloat.value);
    return S_OK;
}
