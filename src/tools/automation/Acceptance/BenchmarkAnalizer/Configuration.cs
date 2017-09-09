using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace BenchmarkAnalizer
{
    class Configuration
    {
        private  String _baseDir = "..\\..";

        public String ProductName() { 
            return "Gensym"; 
        }
        public String BaseDir() { 
            return _baseDir; 
        }
        internal void SetBaseDir(string baseDir) {
            _baseDir = baseDir;
        }
        public String SrcBoxDir() { 
            return Path.Combine(BaseDir(), "src"); 
        }
        public String ToolsBoxDir() { 
            return Path.Combine(BaseDir(), "tools"); 
        }
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
        public String ResultsDir()
        {
            return Path.Combine(BaseDir(), "results");
        }
        public String CommonFasterNbbReportDir()
        {
            return Path.Combine(ReportsDir(), "cnbb");
        }
        public String ThresholdsDir()
        {
            return Path.Combine(ToolsBoxDir(), "automation\\thresholds");
        }
        public String ThresholdCheckerTestsDir()
        {
            return Path.Combine(ToolsBoxDir(), "automation\\threshold-checker\\tests");
        }
        public String ThresholdCheckerDir()
        {
            return Path.Combine(ToolsBoxDir(), "automation\\threshold-checker");
        }
        //Performance Index
        public String ActualPerformanceIndexFile()
        {
//            return Path.Combine(SrcBoxDir(), "tests\\results\\performancetests\\performance-index.txt");
            return Path.Combine(ResultsDir(), "performancetests\\performance-index.txt");
        }
        public String ThresholdPerformanceIndexFile(String version)  //version: 'enterprise' / 'standard'
        {
            return Path.Combine(ThresholdsDir(), version + "-threshold-performance-index.txt");
        }
        //Benchmark sumary
        public String PerformanceSummaryFile()
        {
            return Path.Combine(ReportsDir(), "GensymBenchmark.xml");
        }
        public String PerformanceThresholdFile(String version)    //version: 'Enterprise' / 'Standard'
        {
            return Path.Combine(ThresholdsDir(), version + "BenchmarkThreshold.xml");
        }
        public String PerformanceOutputFile()
        {
            return Path.Combine(ThresholdCheckerDir(), "performance-tests.xml");
        }

        //verify CPD
        public String CpdCheckDir()
        {
//            return Path.Combine(SrcBoxDir(), "tests\\results\\cpd\\c");
            return Path.Combine(ResultsDir(), "cpd\\c");
        }
        public String CpdSummaryFile()
        {
            return Path.Combine(ThresholdCheckerTestsDir(), "cpd-summary.xml");
        }
        public String CpdThresholdFile()    
        {
            return Path.Combine(ThresholdsDir(), "CPDThreshold.xml");
        }
        public String CpdOutputFile()
        {
            return Path.Combine(ThresholdCheckerDir(), "cpd-tests.xml");
        }

        //Tolerance values
        public float getTolerance(String version)    //version: 'Enterprise' / 'Standard' / 'CPD'
        {
            float tolerance = 0F;    //CPD
//            float enterprisePerformanceTolerance = 0.05F;
//            float standardPerformanceTolerance = 0.2F;
            if (version.Equals("Enterprise"))
            {
                tolerance = 0.03F;
            }
            if (version.Equals("Standard"))
            {
                tolerance = 0.03F;
            }
            return tolerance;
        }
        public float getImprovementTolerance(String version)    //version: 'Enterprise' / 'Standard' / 'CPD'
        {
            float tolerance = 1F; //CPD
            if (version.Equals("Enterprise"))
            {
                tolerance = 0.1F;
            }
            if (version.Equals("Standard"))
            {
                tolerance = 0.1F;
            }
            return tolerance;
        }


    }
}
