/* -*- Mode: C -*-
 *
 * Utility STARTER
 *
 * Copyright (C) 1986-2017 Gensym Corporation.
 * All Rights Reserved.
 *
 * STARTER starts up g2 and matching tw processes on Windows.
 * The g2 is started -nowindow. When either process exits, the
 * other is killed (as well as ourselves).
 * 
 * Arguments on the command line are passed on to both g2 and tw.
 *
 * ISSUES:
 *  We assume that G2 is running on port 1111.
 *
 *  The console flashes on startup. You can work around that by creating
 *  a shortcut to starter.exe spcifying a minimized console. It's also
 *  handy to add default command line options there, such as a trailing "-kb ".
 *
 *  If you change this to a /subsystem:windows application, then you avoid
 *  the console flashing, but then you get a wait cursor for about 20
 *  seconds over top of the TW window. To fix that, I think we'd need to
 *  enter a message loop, and then find a new way of waiting for G2 or
 *  TW to exit.
 *
 * $Id: starter.cpp,v 1.2 2002-10-02 16:32:26 fmw Exp $
 */

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

static HWND win;

static BOOL CALLBACK getwin(HWND hwnd, LPARAM lparam)
{
  win = hwnd;
  return FALSE;
}

/* Kill Windows process gracefully. */
void kill_process(PROCESS_INFORMATION *pi)
{
  win = NULL;
  EnumThreadWindows(pi->dwThreadId, getwin, 0);
  if(win != NULL)
    PostMessage(win, WM_QUIT, 0, 0);
  CloseHandle(pi->hProcess);
}

/* Command line arguments without argv[0]. */
char *get_command_line(int argc, char **argv)
{
  static char buf[4096];
  char *cp;
  int i, n;

  buf[0]='\0';
  cp=buf;
  for(i=1; i<argc; i++) {
    *cp++ = ' ';
    *cp++ = '"';
    strncpy(cp, argv[i], 4000-(cp-buf));
    cp += strlen(argv[i]);
    *cp++ = '"';
  }
  *cp++ = '\0';
  return buf;
}

int main(int argc, char* argv[])
{
  STARTUPINFO si;
  PROCESS_INFORMATION g2, tw;
  HANDLE processes[2];
  char *cmdline;
  int port;
  char buf[4096];

  FreeConsole();

  cmdline = get_command_line(argc,argv);

  /* Start G2 */
  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&g2, sizeof(g2));
  sprintf(buf, ".\\g2.exe -nowindow %s", cmdline);
  if(! CreateProcess(NULL, buf, NULL, NULL, FALSE, 0, NULL, NULL, &si, &g2)) {
    /* MessageBox(NULL, "Cannot create g2 process.", "Starter Error", 0); */
    exit(1);
  }
  CloseHandle(g2.hThread);

  WaitForInputIdle(g2.hProcess, 1000);
  port = 1111;			/* TODO: figure out port number. */

  /* Start TW */
  ZeroMemory(&si, sizeof(si));
  si.cb = sizeof(si);
  ZeroMemory(&tw, sizeof(tw));
  sprintf(buf, ".\\tw.exe localhost %d %s", port, cmdline);
  if(! CreateProcess(NULL, buf, NULL, NULL, FALSE, 0, NULL, NULL, &si, &tw)) {
    /* MessageBox(NULL, "Cannot create tw process.", "Starter Error", 0); */
    kill_process(&g2);
    exit(2);
  }
  CloseHandle(tw.hThread);

  /* Wait for either G2 or TW to exit. */
  processes[0] = g2.hProcess;
  processes[1] = tw.hProcess;
  WaitForMultipleObjects(2, processes, FALSE, INFINITE);

  /* Kill other process. */
  kill_process(&g2);
  kill_process(&tw);
  return 0;
}
