#include <stdio.h>

static int X=5;

void* ArrayAlloc (int type, int size) {

  fprintf (stderr, "ArrayAlloc (%d, %d) called.\n", type, size);
  return (void*)(&X);
}

void exceptionDescribe (void* EE) {

  fprintf (stderr, "exceptionDescribe(X) called.\n");
  return;
}

void* EE() {

  fprintf (stderr, "EE(X) called.");
  return (void*)(&X);
}


void* makeJavaString (char *str, int len) {

  fprintf (stderr, "makeJavaString (%s, %d) called.\n", str, len);
  return (void*)(&X);
}

void* FindClass (void* EE, char* class_name, int resolve) {

  fprintf (stderr, "FindClass (X, %s, %d) called.\n", class_name, resolve);
  return (void*)(&X);
}

void SignalError (void* EE, char* type, char* constructor) {

  fprintf (stderr, "SignalError (X, %s, %s) called.\n", type, constructor);
  return;
}

int javaStringLength (void* str) {

  fprintf (stderr, "javaStringLength (X) called.\n");
  return (0);
}

char* javaString2CString (void* str, char buffer[], int length) {

  fprintf (stderr, "javaString2CString (X, X, %d) called.\n", length);
  return (char*)(&X);
}

void* execute_java_constructor (void* EE, char* class_name, void* Class, char* signature) {

  fprintf (stderr, "execute_java_constructor (X, %s, X, %s) called.\n", class_name, signature);
  return (void*)(&X);
}

long execute_java_dynamic_method (void* EE, void* Obj, char* method_name, char* signature) {

  fprintf (stderr, "execute_java_dynamic_method (X, X, %s, %s) called.\n", method_name, signature);
  return 0L;
}
