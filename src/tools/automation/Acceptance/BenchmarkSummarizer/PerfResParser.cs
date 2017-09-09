using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BenchmarkSummarizer
{
    abstract class PerfResParser
    {
        public static readonly char[] _separators = new char[] { ' ', '\t' };
        public decimal invalidValue() { return -1; }

        protected Configuration _conf;


        public PerfResParser(Configuration conf) {
            _conf = conf;
        }

        public bool IsInvalidValue(decimal val) {
            return val == invalidValue();
        }
        public static string[] Tokenize(string text) {
            string[] ans = text.Split(
                _separators, 
                StringSplitOptions.RemoveEmptyEntries);
            return ans;
        }

        public static string[] ValueRequest(int n) {
            return new string[n]; // assume filled with null-s
        }
        
        public static string[] UniteArrays(params string[][] tokens) {
            int totLen = 0;
            for (int i = 0; i < tokens.Length; i++) {
                totLen += tokens[i].Length;
            }
            string[] ans = new string[totLen];
            int cp = 0;
            for (int i = 0; i < tokens.Length; i++) {
                for (int j = 0; j < tokens[i].Length; j++) {
                    ans[cp] = tokens[i][j];
                    cp++;
                }
            }
            return ans;
        }

        public List<decimal> extractValues(string text, string[] format) {
            List<decimal> ans = null;
            string[] textTokens = Tokenize(text);
            //REPERR: a conditional warning?
            if (textTokens.Length < format.Length) return null;
            
            ans = new List<decimal>();
            decimal curVal;
            for (int i = 0; i < format.Length; i++) {
                if (format[i] == null) {
                    if (decimal.TryParse(textTokens[i], out curVal)) {
                        ans.Add(curVal);
                    } else {
                        //REPERR: a conditional warning?
                        return null;
                    }
                } else {
                    if (!format[i].Equals(textTokens[i])) {
                        //REPERR: a conditional warning?
                        return null;
                    }
                }
            }
            return ans;
        }

        public abstract bool Go(PerformanceSummary psDest);
        public abstract string ExternalName();
    }
}
