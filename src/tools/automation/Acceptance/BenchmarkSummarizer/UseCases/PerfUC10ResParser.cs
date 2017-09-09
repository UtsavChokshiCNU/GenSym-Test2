using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Xml;

namespace BenchmarkSummarizer.UseCases
{
    class PerfUC10ResParser : PerfResParser
    {
        public PerfUC10ResParser(Configuration conf) : base(conf) { }

        override public string ExternalName() {
            return "UC10";
        }

        public static readonly string[] _avgTimeFmt = UniteArrays(
            Tokenize("Average time for kb  nokia-faster-1 ="),
            ValueRequest(1)
        );

        public string ResultFN()
        {
            return "nokia-faster-1.txt";
        }

        private bool extractAverageTime(string line, out decimal elapsedTime)
        {
            List<decimal> values = extractValues(line, _avgTimeFmt);
            if (values == null)
            {
                elapsedTime = invalidValue();
                return false;
            }
            elapsedTime = values[0];
            return true;
        }


        override public bool Go(PerformanceSummary psDest)
        {
            string[] lines = File.ReadAllLines(Path.Combine(
                _conf.PerformanceResultDir(),
                ResultFN()));

            decimal elapsedTime = invalidValue();
            for (int i = 0; i < lines.Length; i++)
            {
                if (extractAverageTime(lines[i], out elapsedTime))
                {
                    break;
                }
            }
            if (IsInvalidValue(elapsedTime))
            {
                //REPERR: no objective value in the measurement result
                return false;
            }
            XmlElement useCaseElm = psDest.PutUseCase(ExternalName());
            XmlElement mObjectiveElm = psDest.PutObjectiveMetric(useCaseElm, elapsedTime);
            XmlElement mElapsedTimeMins = psDest.PutElapsedTimeMins(useCaseElm, elapsedTime / 60);
            return true;
        }
    }
}
