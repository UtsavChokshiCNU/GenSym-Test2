// util.h
#ifndef _UTIL_H
#define _UTIL_H

// ERRORS
#define ERROR_BASE ((HRESULT)0x80041000L)

#define E_CANT_GET_BEAN_CLSID                             (ERROR_BASE +      1)
#define E_CANT_CREATE_BEAN_OBJ                            (ERROR_BASE +      2)
#define E_CANT_GET_CP_CONTAINER                           (ERROR_BASE +      3)
#define E_CANT_ENUM_CP                                    (ERROR_BASE +      4)
#define E_CANT_GET_CP                                     (ERROR_BASE +      5)
#define E_CANT_GET_CP2                                    (ERROR_BASE +      6)
#define E_CANT_GET_TYPEINFO                               (ERROR_BASE +      7)
#define E_CANT_GET_TYPELIB                                (ERROR_BASE +      8)
#define E_CANT_GET_CP_ID                                  (ERROR_BASE +      9)
#define E_CANT_GET_EVENTINFO                              (ERROR_BASE + 0x000A)
#define E_CANT_CREATE_JAVA_OBJ                            (ERROR_BASE + 0x000B)
#define E_CANT_CREATE_SINK_OBJ                            (ERROR_BASE + 0x000C)
#define E_CANT_CONNECT_SINK_OBJ                           (ERROR_BASE + 0x000D)
#define E_CANT_INIT_BEAN_OBJ                              (ERROR_BASE + 0x000E)
#define E_CANT_LOAD_BEAN_OBJ                              (ERROR_BASE + 0x000F)
#define E_CANT_INIT_NEW                                   (ERROR_BASE + 0x0010)
#define E_CANT_LOAD_FROM_STREAM                           (ERROR_BASE + 0x0011)
#define E_CANT_GET_SU_CLSID                               (ERROR_BASE + 0x0012)
#define E_CANT_CREATE_SU_BEAN                             (ERROR_BASE + 0x0013)
#define E_CANT_CREATE_SU_OBJ                              (ERROR_BASE + 0x0014)
#define E_CANT_CONNECT_AT_START                           (ERROR_BASE + 0x0015)

#define _SUBOBJECT_METHOD_IMPL(PPOBJ, SUBOBJECT_MEMBER) \
    { \
        (SUBOBJECT_MEMBER).CopyTo(PPOBJ);           \
        return S_OK; \
    }

#define SUBOBJECT_AS_VARIANT(OBJ, VARIANT) \
    { \
        (OBJ)->_subObject(&((VARIANT)->pdispVal)); \
        (VARIANT)->vt = VT_DISPATCH; \
    }


HRESULT CreateScriptUtilitiesInstance(IDispatch** ppSU);

HRESULT InvokeMethod(IDispatch *obj, OLECHAR *MethodName, VARIANTARG *args,
                     int nArg, VARIANT *Result);

BSTR CallDispatch(IDispatch *obj, OLECHAR *MethodName,VARIANTARG *args, int nArg, VARIANT *Result);

DISPID GetDispId(IDispatch *obj, OLECHAR *methodName);

BSTR CallInvoke(IDispatch *obj, DISPID dispid, VARIANTARG *args,
                  int nArg, VARIANT *Result);

HRESULT DispatchInvoke(IDispatch *obj, DISPID dispid, VARIANTARG *args,
                  int nArg, VARIANT *Result, EXCEPINFO *pExceptInfo);

#endif // _UTIL_H
