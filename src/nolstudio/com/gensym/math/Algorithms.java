package com.gensym.math;

import java.io.Serializable;

public class Algorithms implements Cloneable, Serializable{

	/*  This class provides general-purpose algorithms. 
	They are kept separately for space and compilation efficiency. 
	The algorithms may not preserve their input arguments, nor do 
	they do much input validation, so it is advisable to use them only 
	through the corresponding matrix interfaces.  */

	Algorithms() {
		super();
	}
	
	@Override
	public Object clone() throws CloneNotSupportedException {
		return super.clone();
	}

	/** Solution of linear equations Ax=b, where A is a positive-definite,
	symmetric matrix.  On output, x contains the solution.  You can call this
	routine with b==x */
	public static final void cholsky(double a[][], int n, double[] b, double[] x) throws MathException {
		double[] p = new double[n];
		choldc(a,n,p);
		cholsl(a,n,p,b,x);
	}

	public static final void choldc(double a[][], int n, double p[]) throws MathException {
		int i,j,k;
		double sum;
		for (i=0;i<n;i++) {
			for (j=i;j<n;j++) {
				for (sum=a[i][j],k=i-1;k>=0;k--){
					sum -= a[i][k]*a[j][k];
				}
				if (i == j) {
					if (sum <= 0.0){
						throw new MathException("choldc: a not positive definite");
					}
					p[i]= Math.sqrt(sum);
				} else a[j][i]=sum/p[i];
			}
		}
	}

	public static final void cholsl(double[][] a, int n, double[] p, double[] b, double[] x) {
		int i,k;
		double sum;
		for (i=0;i<n;i++) {
			for (sum=b[i],k=i-1;k>=0;k--){
				sum -= a[i][k]*x[k];
			}
			x[i]=sum/p[i];
		}
		for (i=n-1;i>=0;i--) {
			for (sum=x[i],k=i+1;k<n;k++){
				sum -= a[k][i]*x[k];
			}
			x[i]=sum/p[i];
		}
	}

	public static final void gaussj(double[][] a, int n, double[][] b, int m) throws MathException {
		int[] indxc = new int[n];
		int[] indxr = new int[n];
		int[] ipiv = new int[n];
		int i,icol=-1,irow=-1,j,k,l,ll;
		double big,dum,pivinv,temp;
		double[] dumm;
		for (j=0;j<n;j++){
			ipiv[j]=0;
		}
		for (i=0;i<n;i++) {
			big=0.0;
			for (j=0;j<n;j++) {
				if (ipiv[j] != 1) {
					for (k=0;k<n;k++) {
						if (ipiv[k] == 0) {
							if (Math.abs(a[j][k]) >= big) {
								big=Math.abs(a[j][k]);
								irow=j;
								icol=k;
							}
						} else if (ipiv[k] > 1){
							throw new MathException("gaussj: Singular Matrix-1");
						}
					}
				}
			}
			++ipiv[icol];
			if (irow != icol) {
				dumm = a[irow]; 
				a[irow]=a[icol]; 
				a[icol]=dumm;
				dumm = b[irow]; 
				b[irow]=b[icol]; 
				b[icol]=dumm;
			}
			indxr[i]=irow;
			indxc[i]=icol;
			if (Double.compare(a[icol][icol], 0.0) == 0) 
				throw new MathException("gaussj: Singular Matrix-2");
			pivinv=1.0/a[icol][icol];
			a[icol][icol]=1.0;
			for (l=0;l<n;l++){
				a[icol][l] *= pivinv;
			}
			for (l=0;l<m;l++){
				b[icol][l] *= pivinv;
			}
			for (ll=0;ll<n;ll++) {
				if (ll != icol) {
					dum=a[ll][icol];
					a[ll][icol]=0.0;
					for (l=0;l<n;l++){
						a[ll][l] -= a[icol][l]*dum;
					}
					for (l=0;l<m;l++){
						b[ll][l] -= b[icol][l]*dum;
					}
				}
			}
		}
		for (l=n-1;l>=0;l--) {
			if (indxr[l] != indxc[l]) {
				for (k=0;k<n;k++) {
					dum = a[k][indxr[l]];
					a[k][indxr[l]] = a[k][indxc[l]];
					a[k][indxc[l]] = dum;
				}
			}
		}
	}

	/** In-place heapsort of ra into ascending order */
	public static final void hpsort(double ra[], int n) {
		int i=-1,ir,j=-1,l;
		double rra =0;
		if (n < 2){
			return;
		}
		l=(n >> 1);		   // replaces l=(n>>1)+1;
		ir=n-1;
		for (;;) {
			if (l > 0){
				rra=ra[--l];
			}
			else {
				rra=ra[ir];
				ra[ir]=ra[0];
				if (--ir == 0) {
					ra[0]=rra;
					break;
				}
			}
			i=l;
			j=l+l+1; //gchen replaces j=l+l;
			while (j <= ir) {
				if (j < ir && ra[j] < ra[j+1]){
					j++;
				}
				if (rra < ra[j]) {
					ra[i]=ra[j];
					i=j;
					j = ((j+1)<<1) - 1;  // replaces j=(j<<1), since j starts at 0, we need to add 1 before left shift
						//gchen replace j = (j+1)<<1 - 1;
				} else j=ir+1;
			}
			ra[i]=rra;
		}
	}

	/** Sorts auxiliary array. */
	public static final void hpsort(double ra[], int n, double[] aux) {
		int i=-1,ir,j=-1,l;
		double rra, raux;
		if (n < 2){
			return;
		}
		l=(n >> 1);		   // replaces l=(n>>1)+1;
		ir=n-1;
		for (;;) {
	//System.out.println(" at 1:  ir="+ir+" l="+l+" j="+j+" i="+i);
			if (l > 0) {
				--l;
				rra=ra[l]; 
				raux=aux[l];
			}
			else {
				rra=ra[ir];
				raux=aux[ir];
				ra[ir]=ra[0];
				aux[ir]=aux[0];
				if (--ir == 0) {
					ra[0]=rra;
					aux[0]=raux;
					break;
				}
			}
			i=l;
			j=l+l+1;//gchen replaces j=l+l;
			while (j <= ir) {
				if (j < ir && ra[j] < ra[j+1]){
					j++;
				}
				if (rra < ra[j]) {
					ra[i]=ra[j];
					aux[i]=aux[j];
					i=j;
					j = ((j+1)<<1) - 1;  // replaces j=(j<<1), since j starts at 0, we need to add 1 before left shift
						//gchen replace j = (j+1)<<1 - 1;
				} else j=ir+1;
			}
			ra[i]=rra;
			aux[i]=raux;
		}
	}

	/** Sorts auxiliary matrix. */
	public static final void hpsort(double ra[], int n, double[][] aux) {
		int i=-1,ir,j=-1,l;
		double rra;
		double[] raux;
		if (n < 2){
			return;
		}
		l=(n >> 1);		   // replaces l=(n>>1)+1;
		ir=n-1;
		for (;;) {
	//System.out.println(" at 1:  ir="+ir+" l="+l+" j="+j+" i="+i);
			if (l > 0) {
				--l;
				rra=ra[l]; 
				raux=aux[l];
			}
			else {
				rra=ra[ir];
				raux=aux[ir];
				ra[ir]=ra[0];
				aux[ir]=aux[0];
				if (--ir == 0) {
					ra[0]=rra;
					aux[0]=raux;
					break;
				}
			}
			i=l;
			j=l+l+1;//gchen replaces j=l+l;
			while (j <= ir) {
				if (j < ir && ra[j] < ra[j+1]){
					j++;
				}
				if (rra < ra[j]) {
					ra[i]=ra[j];
					aux[i]=aux[j];
					i=j;
					j = ((j+1)<<1) - 1;  // replaces j=(j<<1), since j starts at 0, we need to add 1 before left shift
						//gchen replace j = (j+1)<<1 - 1;
				} else j=ir+1;
			}
			ra[i]=rra;
			aux[i]=raux;
		}
	}

		/* NMIC 47 */
	/** Matrix b is replaced by the solution.  Unlike original algorithm, 
	this deals directly with multiple right-hand sides.  */
	public static final void lubksb(double[][] a, int n, int[] indx, double[][] b, int m) {
		int i, ii=0,ip,j, col;
		double sum;
		for(col=0;col<m;col++) {
			for(i=0;i<n;i++) {
				ip = indx[i];
				sum=b[ip][col];
				b[ip][col] = b[i][col];
				if(ii != -1) {			
					for(j=ii;j<=i-1;j++){
						sum-= a[i][j]*b[j][col];
					}
				} else if (Double.compare(sum, 0.0) != 0) 
					ii=i;
				b[i][col]=sum;
			}
			for(i=n-1;i>=0;i--) {
				sum=b[i][col];
				for(j=i+1;j<n;j++){
					sum-=a[i][j]*b[j][col];
				}
				b[i][col] = sum/a[i][i];
			}
		}
	}

	/** Matrix a is replaced by its LU decomposition */
	public static final int ludcmp(double[][] a, int n, int[] indx) throws MathException {
		int i, imax=-1, j, k;
		double big,dum,sum,temp;		 
		double vv[] = new double[n];
		double TINY = 1.0e-20;
		int d = 1;
		for (i=0;i<n;i++) {
			big=0.0;
			for (j=0;j<n;j++)
				if ((temp=Math.abs(a[i][j])) > big) 
					big=temp;
			if (Double.compare(big, 0.0) == 0) 
				throw new MathException("ludcmp: Singular Matrix");	
			vv[i]=1.0/big;
		}
		for (j=0;j<n;j++) {
			for (i=0;i<j;i++) {
				sum=a[i][j];
				for (k=0;k<i;k++){
					sum -= a[i][k]*a[k][j];
				}
				a[i][j]=sum;
			}
			big=0.0;
			for (i=j;i<n;i++) {
				sum=a[i][j];
				for (k=0;k<j;k++){
					sum -= a[i][k]*a[k][j];
				}
				a[i][j]=sum;
				if ((dum=vv[i]*Math.abs(sum)) >= big) {
					big=dum;
					imax=i;
				}
			}
			if (j != imax) {
				for (k=0;k<n;k++) {
					dum=a[imax][k];
					a[imax][k]=a[j][k];
					a[j][k]=dum;
				}
				d = -d;
				vv[imax]=vv[j];
			}
			indx[j]=imax;
			if (Double.compare(a[j][j],0.0) == 0) 
				a[j][j]=TINY;
			if (j != n-1) {
				dum=1.0/(a[j][j]);
				for (i=j+1;i<n;i++){
					a[i][j] *= dum;
				}
			}
		}
		return d;
	}

	public static final double pythag(double a, double b) {
		double absa = Math.abs(a);
		double absb = Math.abs(b);
		if (absa > absb) 
			return absa*Math.sqrt(1.0+SQR(absb/absa));
		else {
			if (Double.compare(absb, 0.0) == 0) 
				return 0.0;
			else 
				return absb*Math.sqrt(1.0+SQR(absa/absb));
		}
	}

	public static final double remainder(double a, double b) {
//		if(b==0.0) throw new MathException("Remainder (a,b) not defined for b=0.0");
		int n = (int) Math.floor(a/b);
		return a - n*b;
	}

	public static final int remainder(int a, int b) {
//		if(b==0) throw new MathException("Remainder (a,b) not defined for b=0");
		return a - (a/b)*b;
	}


	public static final double SIGN(double a, double b) {
		if (b > 0.0){
			return Math.abs(a);
		}
		else return -Math.abs(a);
	}

	public static final double SQR(double a) {
		if (Double.compare(a,0.0) == 0) 
			return 0.0;
		else 
			return a*a;
	}

	/** Modified to handle multiple right-hand sides */
	public static final void svbksb(double[][] u, double[] w, double[][] v, int m, int n, double[][] b, int p, double[][] x) {
		int jj,j,i,k;
		double s;
		double[] tmp = new double[n];
		for (k=0;k<p;k++) {
			for (j=0;j<n;j++) {
				s=0.0;
				if (Double.compare(w[j],0.0) != 0) {
					for (i=0;i<m;i++){
						s += u[i][j]*b[i][k];
					}
					s /= w[j];
				}
				tmp[j]=s;
			}
			for (j=0;j<n;j++) {
				s=0.0;
				for (jj=0;jj<n;jj++){
					s += v[j][jj]*tmp[jj];
				}
				x[j][k]=s;
			}
		}
	}

	public static final void svdcmp(double[][] a, int m, int n, double[] w, double[][] v) throws MathException {
		int flag,i,its,j,jj,k,l=0,nm=0;
		double anorm,c,f,g,h,s,scale,x,y,z;
		double[] rv1= new double[n];
		g=scale=anorm=0.0;
		for (i=0;i<n;i++) {
			l=i+1;
			rv1[i]=scale*g;
			g=s=scale=0.0;
			if (i <= m) {
				for (k=i;k<m;k++){
					scale += Math.abs(a[k][i]);
				}
				if (Double.compare(scale, 0.0) != 0) {
					for (k=i;k<m;k++) {
						a[k][i] /= scale;
						s += a[k][i]*a[k][i];
					}
					f=a[i][i];
					g = -SIGN(Math.sqrt(s),f);
					h=f*g-s;
					a[i][i]=f-g;
					for (j=l;j<n;j++) {
						for (s=0.0,k=i;k<m;k++){
							s += a[k][i]*a[k][j];
						}
						f=s/h;
						for (k=i;k<m;k++){
							a[k][j] += f*a[k][i];
						}
					}
					for (k=i;k<m;k++){
						a[k][i] *= scale;
					}
				}
			}
			w[i]=scale *g;
			g=s=scale=0.0;
			if (i < m && i != n-1) {
				for (k=l;k<n;k++){
					scale += Math.abs(a[i][k]);
				}
				if (Double.compare(scale, 0.0) != 0) {
					for (k=l;k<n;k++) {
						a[i][k] /= scale;
						s += a[i][k]*a[i][k];
					}
					f=a[i][l];
					g = -SIGN(Math.sqrt(s),f);
					h=f*g-s;
					a[i][l]=f-g;
					for (k=l;k<n;k++){
						rv1[k]=a[i][k]/h;
					}
					for (j=l;j<m;j++) {
						for (s=0.0,k=l;k<n;k++){
							s += a[j][k]*a[i][k];
						}
						for (k=l;k<n;k++){
							a[j][k] += s*rv1[k];
						}
					}
					for (k=l;k<n;k++){
						a[i][k] *= scale;
					}
				}
			}
			anorm=Math.max(anorm,(Math.abs(w[i])+Math.abs(rv1[i])));
		}
		for (i=n-1;i>=0;i--) {
			if (i < n-1) {
				if (Double.compare(g, 0.0) != 0) {
					for (j=l;j<n;j++)
						v[j][i]=(a[i][j]/a[i][l])/g;
					for (j=l;j<n;j++) {
						for (s=0.0,k=l;k<n;k++){
							s += a[i][k]*v[k][j];
						}
						for (k=l;k<n;k++){
							v[k][j] += s*v[k][i];
						}
					}
				}
				for (j=l;j<n;j++){
					v[i][j]=v[j][i]=0.0;
				}
			}
			v[i][i]=1.0;
			g=rv1[i];
			l=i;
		}
		for (i=Math.min(m,n)-1;i>=0;i--) {
			l=i+1;
			g=w[i];
			for (j=l;j<n;j++){
				a[i][j]=0.0;
			}
			if (Double.compare(g,0.0) != 0) {
				g=1.0/g;
				for (j=l;j<n;j++) {
					for (s=0.0,k=l;k<m;k++){
						s += a[k][i]*a[k][j];
					}
					f=(s/a[i][i])*g;
					for (k=i;k<m;k++){
						a[k][j] += f*a[k][i];
					}
				}
				for (j=i;j<m;j++){
					a[j][i] *= g;
				}
			} else for (j=i;j<m;j++){
				a[j][i]=0.0;
			}
			++a[i][i];
		}
		for (k=n-1;k>=0;k--) {
			for (its=1;its<=30;its++) {
				flag=1;
				for (l=k;l>=0;l--) {
					nm=l-1;
					if (Double.compare(Math.abs(rv1[l])+anorm,anorm) == 0) {
						flag=0;
						break;
					}
					if (Double.compare(Math.abs(w[nm])+anorm,anorm) == 0){
						break;
					}
				}
				if (flag != 0) {
					c=0.0;
					s=1.0;
					for (i=l;i<k;i++) {
						f=s*rv1[i];
						rv1[i]=c*rv1[i];
						if (Double.compare(Math.abs(f)+anorm,anorm) == 0){
							break;
						}
						g=w[i];
						h=pythag(f,g);
						w[i]=h;
						h=1.0/h;
						c=g*h;
						s = -f*h;
						for (j=0;j<m;j++) {
							y=a[j][nm];
							z=a[j][i];
							a[j][nm]=y*c+z*s;
							a[j][i]=z*c-y*s;
						}
					}
				}
				z=w[k];
				if (l == k) {
					if (z < 0.0) {
						w[k] = -z;
						for (j=0;j<n;j++){
							v[j][k] = -v[j][k];
						}
					}
					break;
				}
				if (its == 30){
					throw new MathException("svdcmp:no convergence in 30 iterations");
				}
				x=w[l];
				nm=k-1;
				y=w[nm];
				g=rv1[nm];
				h=rv1[k];
				f=((y-z)*(y+z)+(g-h)*(g+h))/(2.0*h*y);
				g=pythag(f,1.0);
				f=((x-z)*(x+z)+h*((y/(f+SIGN(g,f)))-h))/x;
				c=s=1.0;
				for (j=l;j<=nm;j++) {
					i=j+1;
					g=rv1[i];
					y=w[i];
					h=s*g;
					g=c*g;
					z=pythag(f,h);
					rv1[j]=z;
					c=f/z;
					s=h/z;
					f=x*c+g*s;
					g = g*c-x*s;
					h=y*s;
					y *= c;
					for (jj=0;jj<n;jj++) {
						x=v[jj][j];
						z=v[jj][i];
						v[jj][j]=x*c+z*s;
						v[jj][i]=z*c-x*s;
					}
					z=pythag(f,h);
					w[j]=z;
					if (Double.compare(z, 0.0) != 0) {
						z=1.0/z;
						c=f*z;
						s=h*z;
					}
					f=c*g+s*y;
					x=c*y-s*g;
					for (jj=0;jj<m;jj++) {
						y=a[jj][j];
						z=a[jj][i];
						a[jj][j]=y*c+z*s;
						a[jj][i]=z*c-y*s;
					}
				}
				rv1[l]=0.0;
				rv1[k]=f;
				w[k]=x;
			}
		}
	}
}