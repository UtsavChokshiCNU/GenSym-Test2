/**
 * @undocumented
 */

/**
 * This class is for making summary report of RPCTrace and serve as data class.
 *
 *@author FY
 */

package com.gensym.jgi;

import com.gensym.util.Symbol;

class RPCSumRptEntry {
  Symbol pName;
  long tot;
  long avg;
  int calls;

  public RPCSumRptEntry(Symbol name, long t, long a, int c) {
    pName = name;
    tot = t;
    avg = a;
    calls = c;
  }

  Symbol getName() {
    return pName;
  }

  long getTotal() {
    return tot;
  }

  long getAverage() {
    return avg;
  }

  int getCalls() {
    return calls;
  }
} 