using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace BenchmarkAnalizer
{
    class BenchmarkAnalizer
    {
        public String[] _cmdArgs;

        public BenchmarkAnalizer(string[] cmdArgs) {
            _cmdArgs = cmdArgs;
        }
        public bool Go()
        {
            bool bOk = true;
            Configuration configuration = new Configuration();
            if( _cmdArgs.Contains("-relBase") )
            {
                System.Reflection.Assembly a = System.Reflection.Assembly.GetEntryAssembly();
                string baseDir = System.IO.Path.GetDirectoryName(a.Location);
                baseDir = Directory.GetParent(baseDir).ToString();
                baseDir = Directory.GetParent(baseDir).ToString();
                configuration.SetBaseDir(baseDir);
                System.Console.WriteLine("Affirmative - relative base directory identified: {0}", 
                    baseDir);
            } else if (_cmdArgs.Contains("-debug"))
            {
                configuration.SetBaseDir("C:\\G2");
            }

            if (_cmdArgs.Contains("-verifyCPD"))
            {
                CPDTests cPDTests = new CPDTests(configuration, true) ;
                cPDTests.Go();
            }
            if (_cmdArgs.Contains("-verifyEntPerformance"))
            {
                PerformanceTests performanceTests = new PerformanceTests(configuration, "Enterprise", true);
                performanceTests.Go();
            }
            if (_cmdArgs.Contains("-verifyStdPerformance"))
            {
                PerformanceTests verifyPerformance = new PerformanceTests(configuration, "Standard", true);
                verifyPerformance.Go();
            }
            if (_cmdArgs.Contains("-updateMetrics"))
            {
                CPDTests cPDTests = new CPDTests(configuration, false);
                cPDTests.Go();

                PerformanceTests performanceTests = new PerformanceTests(configuration, "Enterprise", false);
                performanceTests.Go(); 
                
            }
 
            return bOk;
        }
        static void Main(string[] args)
        {
            System.Console.WriteLine("Running Benchmark Analizer");
            bool bOk = new BenchmarkAnalizer(args).Go();
        }
    }
}
