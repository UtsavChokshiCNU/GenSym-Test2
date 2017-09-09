using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;

namespace BenchmarkAnalizer
{
    class CompareTests
    {
        private Dictionary<string, float> actualResults;
        private Dictionary<string, float> thresholdResults;
        private Dictionary<string, long> durations;
        private string outputFile;
        private List<ComparatorResult> comparatorResults;

        private float actualPerformanceIndex = 1;        //default value
        private float thresholdPerformanceIndex = 1;     //default value 
        private float tolerance = 0;                     //default value 
        private float improvementTolerance = 1;          //default value 
//        private bool absolute = false;                   //default value 

        public CompareTests(Dictionary<string, float> actualResults, Dictionary<string, float> thresholdResults
                          , Dictionary<string, long> durations, string outputFile) {
            this.actualResults = actualResults;
            this.thresholdResults = thresholdResults;
            this.outputFile = outputFile;
            this.durations = durations;
        }

        public void setPerformanceParameters(float actualPerformanceIndex, float thresholdPerformanceIndex, float tolerance
                                           , /*bool absolute*/ float improvementTolerance)
        {
            this.actualPerformanceIndex = actualPerformanceIndex;
            this.thresholdPerformanceIndex = thresholdPerformanceIndex;
            this.tolerance = tolerance;
            this.improvementTolerance = improvementTolerance;
//            this.absolute = absolute;
        }

        public void makeComparatorResults()
        {
            ComparatorResult.setActualPerformanceIndex(actualPerformanceIndex);
            ComparatorResult.setThresholdPerformanceIndex(thresholdPerformanceIndex);
            comparatorResults = new List<ComparatorResult>();

            foreach (KeyValuePair<string, float> actualPair in actualResults)
            {
                if (thresholdResults.ContainsKey(actualPair.Key)) {
                    ComparatorResult comparatorResult = new ComparatorResult();
                    comparatorResult.setName(actualPair.Key);
                    comparatorResult.setValues(actualPair.Value, thresholdResults[actualPair.Key], tolerance, improvementTolerance);
                    if ((durations != null) && (durations.ContainsKey(actualPair.Key))){
                        comparatorResult.setDuration(durations[actualPair.Key]);
                    }
                    comparatorResults.Add(comparatorResult);
                }
            }
        }

        public void writeResultsToXmlFile(){
            XmlDocument xmlDocument = new XmlDocument();
            xmlDocument.PrependChild(xmlDocument.CreateXmlDeclaration("1.0", "utf-8", "yes"));

            XmlNode testSuiteNode = xmlDocument.CreateElement("testsuite");
            XmlAttribute testSuiteAttribute = xmlDocument.CreateAttribute("name");
            testSuiteAttribute.Value = "Thresholder tests";
            testSuiteNode.Attributes.Append(testSuiteAttribute);
            xmlDocument.AppendChild(testSuiteNode);

            foreach (ComparatorResult comparatorResult in comparatorResults)
            {
                XmlNode testCaseNode = xmlDocument.CreateElement("testcase");
                XmlAttribute testCaseNameAttribute = xmlDocument.CreateAttribute("name");
                testCaseNameAttribute.Value = comparatorResult.getName();
                testCaseNode.Attributes.Append(testCaseNameAttribute);
                XmlAttribute testCaseTimeAttribute = xmlDocument.CreateAttribute("time");
                testCaseTimeAttribute.Value = (comparatorResult.getDuration()/1000.0).ToString();
                testCaseNode.Attributes.Append(testCaseTimeAttribute);
                testSuiteNode.AppendChild(testCaseNode);
                if (!comparatorResult.isPass())
                {
                    XmlNode failureNode = xmlDocument.CreateElement("failure");
                    String text;
                    if (float.IsNaN(comparatorResult.getActualValue()))
                    {
                        text = String.Format("There is no data for {0}", comparatorResult.getName());
                    }
                    else
                    {
                        text = String.Format("Degradation is {0:0.##}% , current result is {1}, threshold is {2}"
                            , comparatorResult.getDifference() * 100
                            , comparatorResult.getActualValue().ToString()
                            , comparatorResult.getOriginalValue().ToString());
                    }
                    failureNode.AppendChild(xmlDocument.CreateTextNode(text));
                    testCaseNode.AppendChild(failureNode);
                }
            }
            try
            {
                XmlTextWriter writer = new XmlTextWriter(outputFile, null);
                writer.Formatting = Formatting.Indented;
                writer.Indentation = 2;
                xmlDocument.Save(writer);
                writer.Close();
                System.Console.WriteLine("\nJUnit report xml is written. File: {0}", outputFile);
            }
            catch (Exception e)
            {
                System.Console.WriteLine("\nComparator results xml File write error! File: {0}\n Exception: {1}"
                     , outputFile
                     , e.StackTrace);
            }
        }

        public bool isAllUpdatable()
        {
            bool allUpdatable = true;
            foreach (ComparatorResult comparatorResult in comparatorResults)
            {
                allUpdatable = allUpdatable && comparatorResult.isUpdatable();
                if (!allUpdatable)
                {
                    break;
                }
            }

            return allUpdatable;
        }

    }
}
