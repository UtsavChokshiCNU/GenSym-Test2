using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Xml;

namespace BenchmarkAnalizer
{
    class PerformanceTests
    {
        private Configuration configuration;
        private String version;
        private bool verify;
        private XmlDocument xmlDocument;

        public PerformanceTests(Configuration configuration, String version, bool verify)
        {
            this.configuration = configuration;
            this.version = version;
            this.verify = verify;
        }
        public void Go()
        {
            float actualPerformanceIndex = getPerformanceIndex(
                                                configuration.ActualPerformanceIndexFile());
            float thresholdPerformanceIndex = getPerformanceIndex(
                                                configuration.ThresholdPerformanceIndexFile(version.ToLower()));
            Dictionary<string, float> performanceSummary = getBenchmarkObjectives(
                                                configuration.PerformanceSummaryFile());
            Dictionary<string, long> durationSummary = getDurationSummary(performanceSummary);
            Dictionary<string, float> performanceThreshold = getBenchmarkObjectives(
                                                configuration.PerformanceThresholdFile(version));

            CompareTests compareTests = new CompareTests(performanceSummary, performanceThreshold, durationSummary
                                                        , configuration.PerformanceOutputFile());
            compareTests.setPerformanceParameters(actualPerformanceIndex, thresholdPerformanceIndex
                                                , configuration.getTolerance(version)
                                                , configuration.getImprovementTolerance(version));
            compareTests.makeComparatorResults();

            if (verify)
            {
                System.Console.WriteLine("Writing comparison results to a file.");
                compareTests.writeResultsToXmlFile();
            }
            else if (compareTests.isAllUpdatable())
            {
                //copy actual to threshold
                try
                {
                    File.Copy(configuration.PerformanceSummaryFile()
                            , configuration.PerformanceThresholdFile(version), true);
                }
                catch (Exception e)
                {
                    System.Console.WriteLine("\nFile Copy error! PerformanceSummaryFile(): {0} PerformanceThresholdFile(): {1}\n Exception: {2}"
                          , configuration.PerformanceSummaryFile()
                          , configuration.PerformanceThresholdFile(version)
                          , e.StackTrace);
                }
                try
                {
                    File.Copy(configuration.ActualPerformanceIndexFile()
                            , configuration.ThresholdPerformanceIndexFile(version.ToLower()), true);
                }
                catch (Exception e)
                {
                    System.Console.WriteLine("\nFile Copy error! ActualPerformanceIndexFile(): {0} ThresholdPerformanceIndexFile(): {1}\n Exception: {2}"
                          , configuration.ActualPerformanceIndexFile()
                          , configuration.ThresholdPerformanceIndexFile(version.ToLower())
                          , e.StackTrace);
                }
            }

        }

        private float getPerformanceIndex(String indexFile)
        {
            float performanceIndex = 1;
            string scoreTitle = "Monte Carlo : ";
            string line = "";
            StreamReader streamReader = null;
            try
            {
                streamReader = new StreamReader(indexFile);
                while ((line = streamReader.ReadLine()) != null)
                {
                    if (line.Contains(scoreTitle))
                    {
                        performanceIndex = float.Parse(line.Substring(scoreTitle.Length));
                        break;
                    }
                }
            }
            catch (Exception e)
            {
                System.Console.WriteLine("\nPerformaceIndex File read or Parse error! indexFile: {0} parsed string: {1}\n Exception: {2}"
                     , indexFile
                     , (line.Length > scoreTitle.Length) ? line.Substring(scoreTitle.Length) : line
                     , e.StackTrace);
            }
            finally
            {
                if (streamReader != null) streamReader.Close();  
            }

            return performanceIndex;
        }

        private Dictionary<string, float> getBenchmarkObjectives(String benchmarkFile) 
        {
            Dictionary<string, float> objectives = new Dictionary<string, float>();
            xmlDocument = new XmlDocument();
            string innerText = "";
            float value = 0;
            try
            {
                xmlDocument.Load(benchmarkFile);
                XmlNodeList xmlNodeList = xmlDocument.SelectNodes("/Benchmark/Product/UseCase");
                foreach (XmlNode xmlNode in xmlNodeList)
                {
                    string key = xmlNode.Attributes.GetNamedItem("name").Value;  //name of UseCase: UC4a
                    foreach (XmlNode metricNode in xmlNode.ChildNodes)
                    {
                        if (metricNode.Attributes.GetNamedItem("name").Value.Equals("Objective"))
                        {
                            innerText = metricNode.InnerText;
                            value = float.Parse(innerText);
                            break;
                        }
                    }
 
                    objectives.Add(key, value);
                }
            }
            catch (Exception e)
            {
                System.Console.WriteLine("\nBenchmark XML File read or Parse error! benchmarkFile: {0} parsed string: {1}\n Exception: {2}"
                     , benchmarkFile
                     , innerText 
                     , e.StackTrace);
            }
            return objectives;
        }

        private Dictionary<string, long> getDurationSummary(Dictionary<string, float> performanceSummary){
            Dictionary<string, long> durationSummary = new Dictionary<string, long>();
            foreach (KeyValuePair<string, float> summaryPair in performanceSummary)
            {
                durationSummary.Add(summaryPair.Key, (long)Math.Round(summaryPair.Value * 1000));
            }

            return durationSummary;
        }

     }
}
