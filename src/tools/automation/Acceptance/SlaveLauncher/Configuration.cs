using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace SlaveLauncher
{
    class Configuration
    {
        private  String _baseDir = "C:\\G2";

        public String ProductName() { return "Gensym"; }
        public String BaseDir() { return _baseDir; }
        internal void SetBaseDir(string baseDir) {
            _baseDir = baseDir;
        }
        public String SrcBoxDir() { return Path.Combine(BaseDir(), "src"); }
        public String ToolsBoxDir() { return Path.Combine(BaseDir(), "tools"); }
        public String AutomationDir() {
            return Path.Combine(BaseDir(), "automation");
        }
        public String ReportsDir() {
            return Path.Combine(AutomationDir(), "reports");
        }
        public String OutputsDir() {
            return Path.Combine( ReportsDir(), "outputs" );
        }
        public String SlaveLaunchOutsFP() {
            return Path.Combine(OutputsDir(), String.Format(
                "slaveLauncher_{0}.txt",DateTime.UtcNow.ToString("yyyy-MM-dd,HH-mm-ss")));
        }
        public String ImportsDir() {
            return Path.Combine(ToolsBoxDir(), "automation\\Acceptance\\Imported");
        }
        public String HudsonSlaveJarFP() {
            return Path.Combine(ImportsDir(), "Hudson\\slave.jar");
        }
        public int MinSlaveIndex() {
            return 1;
        }
        public int MaxSlaveIndex() {
            return 30;
        }
        public String SlaveNamePrefix() {
            return "Gensym-Faster-AAR-slave";
        }
        public String JnlpUrlPrefix() {
            return "http://aar.gdev.com/computer/";
        }
        public String JnlpCredentials() {
            return "aarjnlp:Bv8QPyh5UVPt";
        }
    }
}
