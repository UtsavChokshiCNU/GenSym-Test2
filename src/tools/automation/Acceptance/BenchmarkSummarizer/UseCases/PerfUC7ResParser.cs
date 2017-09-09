using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Xml;
using System.IO;

namespace BenchmarkSummarizer.UseCases
{
    class PerfUC7ResParser : PerfResParser
    {
        override public string ExternalName() {
            return "UC7";
        }
        public string ResultFN() {
            return "washington-river-report.txt";
        }

        public static readonly string[] _oneResFmt = UniteArrays(
            Tokenize("Performance report for Washington-River:"),
            ValueRequest(1)
        );

        public PerfUC7ResParser(Configuration conf) : base(conf) { }
        
        private bool extractOneResult(string line, out decimal totalMinutes)
        {
            List<decimal> values = extractValues(line, _oneResFmt);
            if (values == null)
            {
                totalMinutes = invalidValue();
                return false;
            }
            totalMinutes = values[0] / 60;
            return true;
        }


        override public bool Go(PerformanceSummary psDest)
        {
            string[] lines = File.ReadAllLines(Path.Combine(
                _conf.PerformanceResultDir(),
                ResultFN()));

            decimal avgTotalMinutes = 0;
            int nMeasurements = 0;
            for (int i = 0; i < lines.Length; i++)
            {
                decimal totalMinutes;
                if (extractOneResult(lines[i], out totalMinutes))
                {
                    nMeasurements++;
                    avgTotalMinutes += totalMinutes;
                }
            }
            if( nMeasurements == 0 ) {
                //REPERR: no measurement results
                return false;
            }
            avgTotalMinutes /= nMeasurements;

            XmlElement useCaseElm = psDest.PutUseCase(ExternalName());
            XmlElement mObjectiveElm = psDest.PutObjectiveMetric(useCaseElm, avgTotalMinutes);
            XmlElement mElapsedTimeMins = psDest.PutElapsedTimeMins(useCaseElm, avgTotalMinutes);
            return true;
        }
    }
}
