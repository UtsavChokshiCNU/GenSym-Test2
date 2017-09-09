using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Diagnostics;

namespace SlaveLauncher
{
    class SlaveLauncher
    {
        public String[] _cmdArgs;

        public SlaveLauncher(string[] cmdArgs) {
            _cmdArgs = cmdArgs;
        }
        static void Main(string[] args)
        {
            bool bOk = new SlaveLauncher(args).Go();
            System.Console.WriteLine("Final success: {0}", bOk);
        }

        public bool Go() {
            bool bOk = true;
            Configuration conf = new Configuration();
            if (_cmdArgs.Contains("-relBase"))
            {
                System.Reflection.Assembly a = System.Reflection.Assembly.GetEntryAssembly();
                string baseDir = System.IO.Path.GetDirectoryName(a.Location);
                baseDir = Directory.GetParent(baseDir).ToString();
                baseDir = Directory.GetParent(baseDir).ToString();
                conf.SetBaseDir(baseDir);
                System.Console.WriteLine("Affirmative - relative base directory identified: {0}",
                    baseDir);
            }
            
            Directory.CreateDirectory(conf.OutputsDir());
            // prevent SVN lock
            File.Copy(conf.HudsonSlaveJarFP(), "hudsonSlave.jar", true);
            StreamWriter swrOuts = new StreamWriter(conf.SlaveLaunchOutsFP());

            for (int i = conf.MinSlaveIndex(); i <= conf.MaxSlaveIndex(); i++) {
                SlaveNaming slna = new SlaveNaming(conf);
                String childArgs = String.Format("-jar \"{0}\" -jnlpUrl {1} -jnlpCredentials {2}",
                    "hudsonSlave.jar", slna.GetJnlpUrl(i), conf.JnlpCredentials() );
                ProcessStartInfo psi = new ProcessStartInfo("java", childArgs);
                // psi.RedirectStandardOutput = true;
                psi.RedirectStandardError = true;
                System.Console.Write("Attempt to launch slave #{0} with {1} ...", i, childArgs);
                psi.UseShellExecute = false;
                Process child = Process.Start(psi);
                // StreamReader srdChiOut = child.StandardOutput;
                StreamReader srdChiOut = child.StandardError;
                String allOut = srdChiOut.ReadToEnd();
                swrOuts.WriteLine( allOut );
                if (allOut.Contains("SEVERE: The server rejected the connection: "
                    + slna.GetFor(i) +
                    " is already connected to this master. Rejecting this connection."))
                {
                    System.Console.WriteLine("Seems already connected.");
                }
                else
                {
                    System.Console.WriteLine("Seems success! Exiting...");
                    return true;
                }
            }
            System.Console.WriteLine("No slave launch done.");
            swrOuts.Close();
            return true;
        }
    }
}
