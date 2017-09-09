using System;
using System.Runtime.InteropServices;
using System.IO;

namespace G2MgrWebSvc
{
	/// <summary>
	/// Summary description for Launcher.
	/// </summary>
	public class Launcher
	{
		public Launcher()
		{
		}

		public void Launch()
		{
			StartupInfo si = new StartupInfo();
			si.cb = Marshal.SizeOf(typeof(StartupInfo));
			si.title = "This command prompt is running as Darryl";

			ProcessInfo pi = new ProcessInfo();
			string app = Path.Combine(Environment.SystemDirectory, "notepad.exe");
        
			// assumes you have a local account called "Alice"
			// with a password of "f00b!eBletch" (please make a real password!), 
			// and that she's allowed to log on locally
			string s = System.Configuration.ConfigurationSettings.AppSettings.Get("Default_Domain");
			if (CreateProcessWithLogonW("darrylr", ".", "",
				LogonFlags.LOGON_NETCREDENTIALS_ONLY,
				app, null,
				0, IntPtr.Zero, null,
				ref si, out pi)) 
			{
				CloseHandle(pi.hProcess);
				CloseHandle(pi.hThread);
			}
			else throw new System.ComponentModel.Win32Exception();// Exception(String.Format("CPWL failed with error code: {0}", Marshal.GetLastWin32Error()));		
		}

		[Flags]
			enum LogonFlags 
		{
			LOGON_WITH_PROFILE         = 0x00000001,
			LOGON_NETCREDENTIALS_ONLY  = 0x00000002        
		}
    
		[Flags]
			enum CreationFlags 
		{
			CREATE_SUSPENDED           = 0x00000004,
			CREATE_NEW_CONSOLE         = 0x00000010,
			CREATE_NEW_PROCESS_GROUP   = 0x00000200,
			CREATE_UNICODE_ENVIRONMENT = 0x00000400,
			CREATE_SEPARATE_WOW_VDM    = 0x00000800,
			CREATE_DEFAULT_ERROR_MODE  = 0x04000000,
		}
    
		[StructLayout(LayoutKind.Sequential)]
			struct ProcessInfo 
		{
			public IntPtr hProcess; 
			public IntPtr hThread; 
			public uint dwProcessId; 
			public uint dwThreadId; 
		}
    
		[StructLayout(LayoutKind.Sequential, CharSet=CharSet.Unicode)]
			struct StartupInfo 
		{
			public int     cb; 
			public string  reserved1; 
			public string  desktop; 
			public string  title; 
			public uint    dwX; 
			public uint    dwY; 
			public uint    dwXSize; 
			public uint    dwYSize; 
			public uint    dwXCountChars; 
			public uint    dwYCountChars; 
			public uint    dwFillAttribute; 
			public uint    dwFlags; 
			public ushort  wShowWindow; 
			public short   reserved2; 
			public int     reserved3; 
			public IntPtr  hStdInput; 
			public IntPtr  hStdOutput; 
			public IntPtr  hStdError; 
		}
    
		[DllImport("advapi32.dll", CharSet=CharSet.Unicode, ExactSpelling=true, SetLastError=true)]
		static extern bool CreateProcessWithLogonW(
			string principal,
			string authority,
			string password,
			LogonFlags logonFlags,
			string appName,
			string cmdLine,
			CreationFlags creationFlags,
			IntPtr environmentBlock,
			string currentDirectory,
			ref StartupInfo startupInfo,
			out ProcessInfo processInfo);

		[DllImport("kernel32.dll")]
		static extern bool CloseHandle(IntPtr h);
	}
}
