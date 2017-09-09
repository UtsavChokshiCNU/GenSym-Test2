
package com.gensym.gsi;

import java.util.*;
import java.io.*;

public class InvalidICPInteger extends IOException {
    int i;
    public InvalidICPInteger (int i) {
	this.i = i;
    }
}
