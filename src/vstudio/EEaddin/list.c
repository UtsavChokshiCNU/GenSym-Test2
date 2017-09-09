#include "custview.h"

HRESULT FormatLIST(DEBUGHELPER *pHelper, unsigned __int64 dlDataPtr, char *pResult, size_t maxResult)
{
    DWORD dwNumRead = 0;
    HRESULT ReadResult;
    SI_Cons *cons;
    Object o, car, cdr;

    ReadResult = pHelper->ReadDebuggeeMemoryEx(pHelper, dlDataPtr, sizeof(SI_Cons), &cons, &dwNumRead);

    if (FAILED(ReadResult) || dwNumRead != sizeof(SI_Cons))
    {
        strcpy_s(pResult, maxResult, "Error reading list");
	return S_OK;
    }

    o = (Object) cons;
    car = CAR(o);
    cdr = CDR(o);

    sprintf_s(pResult, maxResult, "(%d . %d)", car, cdr);

    return S_OK;
}

#define MAX_ARRAY_LENGTH 32

HRESULT FormatARRAY(unsigned int type, unsigned int stuff,
                    DEBUGHELPER *pHelper, unsigned __int64 dlDataPtr, char *pResult, size_t maxResult)
{
    DWORD dwNumRead = 0;
    HRESULT ReadResult;
    size_t data_length;
    size_t arr_length;
    void *arr;

    if (type == SI_PRIMITIVE_VECTOR_TYPE) {
        if ((enum SI_type) stuff == A_STRING_CHAR) /* SIMPLE_STRING_P */ {
            data_length = sizeof(SI_PVT_Char) + 1 + MAX_ARRAY_LENGTH; 
            arr = malloc(data_length);
            ReadResult = pHelper->ReadDebuggeeMemoryEx(pHelper, dlDataPtr, data_length, arr, &dwNumRead);

            if (FAILED(ReadResult) || dwNumRead != data_length)
            {
                strcpy_s(pResult, maxResult, "Error reading simple string");
                return S_OK;
            }

            arr_length = IFIX(((SI_PVT_Char*) arr)->h.length);
            sprintf_s(pResult, maxResult, "\"%s\" (%d)", ((SI_PVT_Char*) arr)->contents, arr_length);
        } else {
            sprintf_s(pResult, maxResult, "other primitive vector");
        }
    } else if (type == SI_GENERAL_ARRAY_TYPE) {
        sprintf_s(pResult, maxResult, "general array");
        return S_OK;
    }

    return S_OK;
}
