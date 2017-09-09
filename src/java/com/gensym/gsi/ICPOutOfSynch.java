
package com.gensym.gsi;

import java.util.*;
import java.io.*;

public class ICPOutOfSynch extends IOException {
    int type;
    public ICPOutOfSynch (int type) {
	this.type = type;
    }
}
