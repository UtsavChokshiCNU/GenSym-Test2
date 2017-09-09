using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.IO;

namespace BenchmarkAnalizer
{
    class CPDTests
    {
        private Configuration configuration;
        private bool verify;
        private XmlDocument xmlDocument;
        private string[] moduleNames = new string[] {"ext", "fnt", "jpeg", "rtl", "scintilla"
                                                   , "twng", "twplug", "widgets", "xml", "xtp"};

        public CPDTests(Configuration configuration, bool verify)
        {
            this.configuration = configuration;
            this.verify = verify;
        }

        public void Go(){
            Dictionary<string, float> duplications = verify ? getCpdCheckFiles() : getSumaryFile(configuration.CpdSummaryFile());
            if (verify)
            {
                saveDuplicationSummary(configuration.CpdSummaryFile(), duplications);
            }
            Dictionary<string, float> thresholds = getSumaryFile(configuration.CpdThresholdFile());

            CompareTests compareTests = new CompareTests(duplications, thresholds, null      //durations = null !!!
                                            , configuration.CpdOutputFile());
            compareTests.setPerformanceParameters(1, 1, configuration.getTolerance("CPD")
                                                 , configuration.getImprovementTolerance("CPD"));
            compareTests.makeComparatorResults();

            if (verify)
            {
                compareTests.writeResultsToXmlFile();
            }
            else if (compareTests.isAllUpdatable())  //update
            {
                try
                {
                    File.Copy(configuration.CpdSummaryFile(), configuration.CpdThresholdFile(), true);
                }
                catch (Exception e)
                {
                    System.Console.WriteLine("\nFile Copy error! CpdSummaryFile: {0} CpdThresholdFile: {1}\n Exception: {2}"
                          , configuration.CpdSummaryFile()
                          , configuration.CpdThresholdFile()
                          , e.StackTrace);
                }
            }
        }

        private Dictionary<string, float> getCpdCheckFiles() {
            Dictionary<string, float> duplications = new Dictionary<string, float>();
            xmlDocument = new XmlDocument();
            foreach (string moduleName in moduleNames)
            {
                string cpdCheckFile = Path.Combine(configuration.CpdCheckDir(), "cpd_check_" + moduleName + ".xml");
                float duplicateLines = 0;
                string duplicateLine = "";
                try
                {
                    Stream ffStream = new FilterStream(new FileStream(cpdCheckFile, FileMode.Open, FileAccess.Read));
//                    xmlDocument.Load(cpdCheckFile);
                    xmlDocument.Load(ffStream);
                    XmlNodeList xmlNodeList = xmlDocument.SelectNodes("/pmd-cpd/duplication");
                    foreach (XmlNode xmlNode in xmlNodeList)
                    {
                        duplicateLine = xmlNode.Attributes.GetNamedItem("lines").Value;
                        duplicateLines += float.Parse(duplicateLine);
                    }
                }
                catch (Exception e)
                {
                    System.Console.WriteLine("\nCpd check XML File read or Parse error! cpdCheckFile: {0} parsed string: {1}\n Exception message: {2}\n Exception: {3}"
                         , cpdCheckFile
                         , duplicateLine
                         , e.Message
                         , e.StackTrace);
                }
                duplications.Add(moduleName, duplicateLines);
            }
            return duplications;
        }

        private void saveDuplicationSummary(string cpdSummaryFile, Dictionary<string, float> duplications) {
            xmlDocument = new XmlDocument();
            xmlDocument.PrependChild(xmlDocument.CreateXmlDeclaration("1.0", "utf-8", "yes"));

            XmlNode modulesNode = xmlDocument.CreateElement("Modules");
            xmlDocument.AppendChild(modulesNode);

            foreach (KeyValuePair<string, float> duplicationPair in duplications) {
                XmlNode moduleNode = xmlDocument.CreateElement("Module");
                XmlAttribute moduleNameAttribute = xmlDocument.CreateAttribute("name");
                moduleNameAttribute.Value = duplicationPair.Key;
                moduleNode.Attributes.Append(moduleNameAttribute);
                XmlAttribute moduleDuplicationAttribute = xmlDocument.CreateAttribute("duplication");
                moduleDuplicationAttribute.Value = duplicationPair.Value.ToString();
                moduleNode.Attributes.Append(moduleDuplicationAttribute);
                modulesNode.AppendChild(moduleNode);
            }
            try {
                XmlTextWriter writer = new XmlTextWriter(cpdSummaryFile, null);
                writer.Formatting = Formatting.Indented;
                writer.Indentation = 2;
                xmlDocument.Save(writer);
                writer.Close();
            }
            catch (Exception e)
            {
                System.Console.WriteLine("\ncpd-summary.xml File write error! File: {0}\n Exception: {1}"
                     , cpdSummaryFile
                     , e.StackTrace);
            }
        }

        private Dictionary<string, float> getSumaryFile(string summaryFile)
        {
            Dictionary<string, float> thresholds = new Dictionary<string, float>();
            xmlDocument = new XmlDocument();
            string duplicationAttribute = "";
            try {
                xmlDocument.Load(summaryFile);
                XmlNodeList xmlNodeList = xmlDocument.SelectNodes("/Modules/Module");
                foreach (XmlNode xmlNode in xmlNodeList)
                {
                    string module = xmlNode.Attributes.GetNamedItem("name").Value;
                    duplicationAttribute = xmlNode.Attributes.GetNamedItem("duplication").Value;
                    float duplication = float.Parse(duplicationAttribute);
                    thresholds.Add(module, duplication);
                }
            }
            catch (Exception e) {
                System.Console.WriteLine("\nCPD Summary XML File read or Parse error! summaryFile: {0} parsed string: {1}\n Exception: {2}"
                     , summaryFile
                     , duplicationAttribute
                     , e.StackTrace);
            }

            return thresholds;
        }
    }
}
