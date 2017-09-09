using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BenchmarkSummarizer {
    class Checker {
        public static bool Must(bool allRight, object culprit) {
            if( !allRight ) {
                System.Console.WriteLine("\nCheck failed due to {0} at {1}\n",
                    culprit.ToString(),
                    Environment.StackTrace);
            }
            return allRight;
        }
    }
}
