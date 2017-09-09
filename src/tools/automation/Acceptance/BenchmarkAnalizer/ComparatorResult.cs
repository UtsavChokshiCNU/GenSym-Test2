using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BenchmarkAnalizer
{
    class ComparatorResult
    {
        private static float actualPerformanceIndex;
        private static float thresholdPerformanceIndex;

        private string name;
        private float actualValue = float.NaN;
        private float originalValue;
        private float difference;
        private bool pass;
        private bool updatable;
        private long duration = 0;         //duration in millisec

        public static void setActualPerformanceIndex(float actualIndex) {
            actualPerformanceIndex = actualIndex;
        }
        public static void setThresholdPerformanceIndex(float thresholdIndex) {
            thresholdPerformanceIndex = thresholdIndex;
        }


        public string getName() {
            return name;
        }
        public void setName(string name) {
            this.name = name;
        }

        public float getActualValue() {
            return actualValue;
        }
        public void setActualValue(float actualValue) {
            this.actualValue = actualValue;
        }

        public float getOriginalValue()
        {
            return originalValue;
        }
        public void setOriginalValue(float originalValue)
        {
            this.originalValue = originalValue;
        }

        public float getDifference()
        {
            return difference;
        }
        public void setDifference(float difference)
        {
            this.difference = difference;
        }

        public Boolean isPass(){
            return pass;
        }
        public void setPass(bool pass){
            this.pass = pass;
        }

        public Boolean isUpdatable()
        {
            return updatable;
        }
        public void setUpdatable(bool updatable)
        {
            this.updatable = updatable;
        }

        public long getDuration()
        {
            return duration;
        }
        public void setDuration(long duration)
        {
            this.duration = duration;
        }

        public void setValues(float actual, float threshold, float tolerance, float improvementTolerance)
        {
            actualValue = actual;
            originalValue = threshold;
            //(defun calculate-degradation (actual threshold actual-performance-index
            //          threshold-performance-index)
            //  (if (= threshold 0)
            //  (if (= actual 0) 0 1d++0)
            //  (- (/ (* actual (/ actual-performance-index threshold-performance-index)) threshold) 1)))
            if (threshold == 0) {
                difference = (actual == 0) ? 0 : 1;
            } 
            else {
                difference = actual/threshold - 1.0f;
            }
            updatable = ((-1 * improvementTolerance) <= difference) && (difference <= (-1 * tolerance));
            pass = updatable || (Math.Abs(difference) <= tolerance);
         }
    }
}
