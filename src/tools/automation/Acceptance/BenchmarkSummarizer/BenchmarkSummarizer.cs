using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Diagnostics;

namespace BenchmarkSummarizer
{
    class BenchmarkSummarizer
    {
        public String[] _cmdArgs;

        public BenchmarkSummarizer(string[] cmdArgs) {
            _cmdArgs = cmdArgs;
        }
        public bool Go()
        {
            bool bOk = true;
            Configuration conf = new Configuration();
            if( _cmdArgs.Contains("-relBase") )
            {
                System.Reflection.Assembly a = System.Reflection.Assembly.GetEntryAssembly();
                string baseDir = System.IO.Path.GetDirectoryName(a.Location);
                baseDir = Directory.GetParent(baseDir).ToString();
                baseDir = Directory.GetParent(baseDir).ToString();
                conf.SetBaseDir(baseDir);
                System.Console.WriteLine("Affirmative - relative base directory identified: {0}", 
                    baseDir);
            }
            PerformanceSummary ps = new PerformanceSummary( conf.ProductName() );
            PerfUCRegister pucr = new PerfUCRegister(conf);
            pucr.ParseUC4aRes(ps);
            pucr.ParseUC7Res(ps);
            pucr.ParseUC8Res(ps);
            pucr.ParseUC9Res(ps);
            pucr.ParseUC10Res(ps);

            Directory.CreateDirectory( conf.ReportsDir() );
            ps.SaveTo(conf.GensymPerformanceReportFP());
            ps.SaveCommonFaster(conf.CommonFasterNbbReportDir());
            return bOk;
        }
        static void Main(string[] args)
        {
            bool bOk = new BenchmarkSummarizer(args).Go();
         
        }
    }
}
