using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.IO;

namespace BenchmarkSummarizer
{
    class PerformanceSummary
    {
        public const string _tagBenchmark = "Benchmark";
        public const string _tagProduct = "Product";
        public const string _tagUseCase = "UseCase";
        public const string _tagPhase = "Phase";
        public const string _tagMetric = "Metric";
        public const string _tagNameAttr = "name";
        public const string _objectiveMetricName = "Objective";
        public const string _elapsedTimeMinsMetricName = "ElapsedTimeMins";

        private XmlDocument _model;
        private XmlElement _root;
        private String _focusProduct;

        public PerformanceSummary(String focusProduct)
        {
            // example "CreateXMLDoc" from http://www.fincher.org/tips/Languages/csharp.shtml
            _model = new XmlDocument();
            _model.PrependChild(_model.CreateXmlDeclaration("1.0", "utf-8", "yes"));
            _root = _model.CreateElement(_tagBenchmark);
            _model.AppendChild(_root);
            _focusProduct = focusProduct;

        }

        public XmlElement ProductElm() {
            String xpath = String.Format( "{0}[@{1}='{2}']", 
                _tagProduct, _tagNameAttr, _focusProduct );
            XmlElement ans = (XmlElement)_root.SelectSingleNode( xpath );
            if (ans == null) {
                ans = _model.CreateElement(_tagProduct);
                ans.SetAttribute(_tagNameAttr, _focusProduct);
                _root.AppendChild(ans);
            }
            return ans;
        }

        public Boolean SaveTo(string xmlFP)
        {
            _model.Save(xmlFP);
            return true;
        }

        private static String Inside(String tag, String text)
        {
            return String.Format("<{0}>{1}</{0}>", tag, text);
        }
        public void SaveCommonFaster(string dir)
        {
            // Example: view-source:http://confluence.gdev.com/download/attachments/128880558/perfoutput.xml?version=1&modificationDate=1288969246516
            Directory.CreateDirectory(dir);
            XmlNodeList useCases = ProductElm().SelectNodes(_tagUseCase);
            foreach (XmlElement ucNode in useCases) {
                string ucName = ucNode.Attributes[_tagNameAttr].Value;
                string[] lines = new string[]{
                    "<?xml version=\"1.0\"?>",
                    "<Metric>",
                    Inside("UseCaseName", ucName),
                    Inside(_elapsedTimeMinsMetricName, GetElapsedTimeMins(ucNode)),
                    Inside(_objectiveMetricName, GetObjectiveMetric(ucNode)),
                    "</Metric>"
                };
                File.WriteAllLines(Path.Combine(dir, "FR_" + ucName + ".xml"), lines);
            }
        }

        public XmlElement PutUseCase(string name) {
            XmlElement ans = _model.CreateElement(_tagUseCase);
            ans.SetAttribute(_tagNameAttr, name);
            ProductElm().AppendChild(ans);
            return ans;
        }

        public bool isPhaseOrUseCase(XmlElement elm) {
            return _tagUseCase.Equals(elm.Name) ||
                _tagPhase.Equals(elm.Name);
        }

        public XmlElement PutPhase(XmlElement parent, string name) {
            Checker.Must( isPhaseOrUseCase(parent), parent.Name );
            XmlElement ans = _model.CreateElement(_tagPhase);
            ans.SetAttribute(_tagNameAttr, name);
            parent.AppendChild(ans);
            return ans;
        }

        public XmlElement PutMetric(XmlElement phaseOrUseCase, string name, decimal val) {
            Checker.Must( isPhaseOrUseCase(phaseOrUseCase), phaseOrUseCase.Name );
            XmlElement ans = _model.CreateElement(_tagMetric);
            ans.SetAttribute(_tagNameAttr, name);
            phaseOrUseCase.AppendChild(ans);
            XmlNode valNode = _model.CreateTextNode(val.ToString());
            ans.AppendChild(valNode);
            return ans;
        }

        public XmlElement PutObjectiveMetric(XmlElement phaseOrUseCase, decimal val) {
            return PutMetric(phaseOrUseCase, _objectiveMetricName, val);
        }
        public XmlElement PutElapsedTimeMins(XmlElement phaseOrUseCase, decimal val) {
            decimal friendly = Math.Round(val, 5);
            return PutMetric(phaseOrUseCase, _elapsedTimeMinsMetricName, friendly);
        }

        public string GetObjectiveMetric(XmlElement phaseOrUseCase)  {
            return GetMetric(phaseOrUseCase, _objectiveMetricName);
        }
        public string GetElapsedTimeMins(XmlElement phaseOrUseCase) {
            return GetMetric(phaseOrUseCase, _elapsedTimeMinsMetricName);
        }
        public string GetMetric(XmlElement phaseOrUseCase, string name)
        {
            Checker.Must(isPhaseOrUseCase(phaseOrUseCase), phaseOrUseCase.Name);
            XmlNode metric = phaseOrUseCase.SelectSingleNode(
                String.Format("{0}[@{1}='{2}']", _tagMetric, _tagNameAttr, name));
            if( metric == null ) return null;
            return metric.InnerText;
        }

    }
}
