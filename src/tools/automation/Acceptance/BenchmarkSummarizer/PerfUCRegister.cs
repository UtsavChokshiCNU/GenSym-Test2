using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using BenchmarkSummarizer.UseCases;

namespace BenchmarkSummarizer
{
    class PerfUCRegister
    {
        private Configuration _conf;

        public PerfUCRegister(Configuration conf) {
            _conf = conf;
        }

        public Boolean ParseUC4aRes(PerformanceSummary psDest)
        {
            return new PerfUC4aResParser(_conf).Go(psDest);
        }
        
        public Boolean ParseUC7Res(PerformanceSummary psDest)
        {
            return new PerfUC7ResParser(_conf).Go(psDest);
        }
        
        public Boolean ParseUC8Res(PerformanceSummary psDest)
        {
            return new PerfUC8ResParser(_conf).Go(psDest);
        }

        public Boolean ParseUC9Res(PerformanceSummary psDest)
        {
            return new PerfUC9ResParser(_conf).Go(psDest);
        }

        public Boolean ParseUC10Res(PerformanceSummary psDest)
        {
            return new PerfUC10ResParser(_conf).Go(psDest);
        }
    }
}
