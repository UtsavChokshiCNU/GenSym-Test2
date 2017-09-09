using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace BenchmarkSummarizer
{
    class Configuration
    {
        private  String _baseDir = "..\\..";

        public String ProductName() { return "Gensym"; }
        public String BaseDir() { return _baseDir; }
        internal void SetBaseDir(string baseDir) {
            _baseDir = baseDir;
        }
        public String SrcBoxDir() { return Path.Combine(BaseDir(), "src"); }
        public String ToolsBoxDir() { return Path.Combine(BaseDir(), "tools"); }
        public String PerformanceTestDir() {
            return Path.Combine(SrcBoxDir(), "tests\\performance"); 
        }
        public String PerformanceResultDir() {
            return Path.Combine(PerformanceTestDir(), "results");
        }
        public String AutomationDir() {
            return Path.Combine(BaseDir(), "automation");
        }
        public String ReportsDir() {
            return Path.Combine(AutomationDir(), "reports");
        }
        public String GensymPerformanceReportFP() {
            return Path.Combine(ReportsDir(), "GensymBenchmark.xml");
        }
        public String CommonFasterNbbReportDir() {
            return Path.Combine(ReportsDir(), "cnbb");
        }
    }
}
