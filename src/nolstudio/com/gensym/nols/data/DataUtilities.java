package com.gensym.nols.data;
public class DataUtilities {
	static final long serialVersionUID = 1L;
	private static double inverseLn10 = 1.0/Math.log(10.0);

/** Convert a data string to a string array. The substring can
	be seperated by Tab, Space and comma. */
	public static void string2Strings(final String S, final int nSting, final String[] subStrings){
		int i,endIndex,sep1,sep2,sep3;
		String str = S.trim();
		boolean noMoreVals = false;
		for(i=0;i<nSting;i++) {
			if(noMoreVals) {
				subStrings[i] = "";
			}else {
				sep1 = str.indexOf('\u0020');
				sep2 = str.indexOf('\u0009');
				sep3 = str.indexOf(",");
				endIndex = str.length();
				if(sep1>0) {
					endIndex = Math.min(endIndex,sep1);
				}
				if(sep2>0) {
					endIndex = Math.min(endIndex,sep2);
				}
				if(sep3>0) {
					endIndex = Math.min(endIndex,sep3);
				}
				subStrings[i] = str.substring(0,endIndex);
				try {
					str = str.substring(endIndex + 1);
				} catch (StringIndexOutOfBoundsException B) {
					noMoreVals = true;
				}
				str = str.trim();
			}
		}
	}

/** Sorts an integer array and replaces it by the sorted arrayusing bubble
sort algorithm. The integer index array is returned */
	public static int [] bubbleSort(int a[]) {
		int ind[] = new int[a.length];
		int id;
		int T;
		for(int i=0;i<a.length;i++){
			ind[i]=i;
		}
		for (int i = a.length; --i>=0; ) {
			boolean swapped = false;
			for (int j = 0; j<i; j++) {
				if (a[j] > a[j+1]) {
					T = a[j];
					a[j] = a[j+1];
					a[j+1] = T;
					id = ind[j];
					ind[j] = ind[j+1];
					ind[j+1] = id;
					swapped = true;
				}
			}
			if (!swapped)
			return ind;
		}
		return ind;
    }

	/** Calculate the median of a double array, ignoring NaNs.*/
	public static double median(double[] data) {
		int validCount = 0;
		int n = data.length;
		double mmm = 0;
		for(int i=0;i<n;i++){
			if(!Double.isNaN(data[i])){
				mmm = data[i];
				validCount++;
			}
		}
		if(validCount==0) {
			return Double.NaN;
		}
		if(validCount==1) {
			return mmm;
		}

		double[] d = new double[validCount];
		int c=0;
		for(int i=0;i<n;i++){
			if(!Double.isNaN(data[i])){
				d[c] = data[i];
				c++;
			}
		}
		n = validCount;
		if(n/2*2 == n){
			int med1 = n/2-1;
			int med2 = n/2;
			double m1 = select(med1,d);
			double m2 = select(med2,d);
			d = null;
//			System.out.println("med1 m1="+m1+" m2="+m2);
			return (m1+m2)/2;
		}else{
			int med = n/2;
			double m = select(med,d);
			d = null;
//			System.out.println("med2="+ m);
			return m;
		}
	}

		
	private static double select(int k,double[] arr){
		int n = arr.length;
		int l=0;
		int ir = n-1;
		double temp,a;
		int mid,i,j;
		while(true){
			if (ir <= l+1) {
				if (ir == l+1 && arr[ir] < arr[l]) {
					temp = arr[l];
					arr[l] = arr[ir];
					arr[ir] = temp;
				}
				return arr[k];
			} else {
				mid=(l+ir+1)/2;
				temp = arr[l+1];
				arr[l+1] = arr[mid];
				arr[mid] = temp;
				if (arr[l] > arr[ir]) {
					temp = arr[l];
					arr[l] = arr[ir];
					arr[ir] = temp;
				}
				if (arr[l+1] > arr[ir]) {
					temp = arr[l+1];
					arr[l+1] = arr[ir];
					arr[ir] = temp;
				}
				if (arr[l] > arr[l+1]) {
					temp = arr[l+1];
					arr[l+1] = arr[l];
					arr[l] = temp;
				}
				i = l+1;
				j=ir;
				a = arr[l+1];
				while(true){
					do {
						i++;
					}while(arr[i]<a);
					do {
						j--;
					}while(arr[j]>a);
					if(j<i) {
						break;
					}
					temp = arr[j];
					arr[j] = arr[i];
					arr[i] = temp;
				}
				arr[l+1]=arr[j];
				arr[j]=a;
				if (j >= k){
					ir=j-1;
				}
				if (j <= k){
					l=i;
				}
			}
		}
	}


	public static String doubleToString(final double value, final int sigDigits) {
		// rounds to given number of significant digits, and presents in shortest format
		double val = value;
		if (Double.isNaN(val)) 
			return "NaN";
		if (Double.isInfinite(val)) 
			return "Infinite";
		if (Double.compare(val, 0.0) == 0) 
			return "0.0";
		boolean negative;
		String sign;
		if (val < 0.0) {
			negative = true;
			sign = "-";
			val = Math.abs(val);
		} else {
			negative = false;
			sign = "";
		}
		if(val>=100000||val<0.01){
			double ord = Math.log(val)/Math.log(10.0);
			int iord = (int)Math.floor(ord);
			val = val/Math.pow(10,iord);
			String formatted = sign+doubleToString(val, sigDigits)+"E"+iord;
			return formatted;
		}

		int magnitude = (int) Math.floor(DataUtilities.inverseLn10*Math.log(val));
		String digits = ""+(int) Math.rint(Math.pow(10.0, -magnitude + sigDigits - 1.0d)*val);
		// must correct for rounding up into a new order of magnitude
		if (digits.length() > sigDigits) {
			++magnitude;
			digits = digits.substring(0, digits.length() - 1);
		}
		//System.out.println("val = "+value+" digits = "+digits+" magnitude = "+magnitude+" negative = "+negative);
		String formatted;
		if (magnitude < 0 || magnitude >= sigDigits) {
			// strip trailing zeros
			while (digits.endsWith("0")){
				digits = digits.substring(0, digits.length() - 1);
			}
		}
		//System.out.println("stripped to "+digits);
		if (magnitude < -3 || magnitude >= sigDigits) {
			// represent in scientific notation
			if(digits.length() > 1) {
				formatted = sign+digits.substring(0, 1)+"."+digits.substring(1)+"e"+magnitude;
			}else {
				formatted = sign+digits+"."+"e"+magnitude;
			}
			return formatted;
		} else if (magnitude >= 0) {
			if (magnitude == sigDigits - 1) {
				formatted = sign+digits.substring(0, magnitude+1)+".";
			}else {
				formatted = sign+digits.substring(0, magnitude+1)+"."+digits.substring(magnitude+1);
			}
			return formatted;
		}else if (magnitude == -1) {
			return sign+"0."+digits;
		} else if (magnitude == -2){
			return sign+"0.0"+digits;
		} else {
			return sign+"0.00"+digits;	  // magnitude = -3
		}
	}
}