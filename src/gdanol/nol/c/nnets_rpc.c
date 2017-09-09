/* -*- Mode: C -*-
 *
 * NNETS_RPC.C
 *
 * Main program for GSI interface
 * 
 * Copyright (C) 1986-2017 Gensym Corporation.
 * All Rights Reserved.
 *
 * Written by Mark A. Kramer
 *
 */

#include "matrix.h"
#include "gsi_main.h"

#include <time.h>

#if defined(_MSC_VER) && (_MSC_VER < 1900)
/* but remember that the result is actually not the same! */
#define snprintf _snprintf
#endif

#define PI 3.14159265358979
#define SQRTPI 1.772453851
#define GRAD_CHECK 0
#define IGNORE_COMMENT(x)  do { int M_c = getc(x); if ((M_c == EOF) || (M_c == '\n')) break; } while (1)
#define NORMAL(x,sd) (1.0/(2.0*SQRTPI*(sd)*(sd)))*exp(-((x)*(x))/(2.0*(sd)*(sd)))
#define LOGNORMAL(x,sd) (-(x)*(x)/(2.0*(sd)*(sd)) - 2.0*log(sd) - 1.265512124)
#define SIGN(a,b) ((b) >= 0.0 ? fabs(a):-fabs(a))
#define SIGMOID_LIM log(DBL_MAX)

/* MK 9/27/93  G2 has problems with numbers close to its advertised limits.
   For example, the quantity function doesn't work with numbers
   g.t. 1.e300 and 1.e-299 on HP 9000/700.  Therefore, define the
   following functions  */

#define G2_SMALL_FLOAT 1.0e-290
#define G2_BIG_FLOAT 1.0e+290
#define G2_LIMIT(x) (fabs(x) > G2_BIG_FLOAT ? SIGN(G2_BIG_FLOAT,(x)): (fabs(x) < G2_SMALL_FLOAT && (x) != 0.0? SIGN(G2_SMALL_FLOAT,(x)): (x)))


enum {
    CANT_OPEN_FILE = 246,
    OTHER_ERROR = 123
};



/**********************************************************************

Main

**********************************************************************/

char *err_file;  /* globalize name of outfile so all functions can have access, without passing through the entire chain of command */
static jmp_buf jmpenv;  /* jmp_buf from setjmp.h, jmpenv is environment for long jump */
int print_mode;  /* global print flag, 0 = off, 1 = on */



int main(int argc, char *argv[])
{
    pointer_to_stack local_ptr = ans;

    GSI_SET_OPTIONS_FROM_COMPILE();
    gsi_reset_option(GSI_ONE_CYCLE);

#if defined(_DEBUG) || !defined(NDEBUG)
    print_mode = 3;
#else
    print_mode = 1;
#endif
    if (print_mode >= 2) {
        printf("About to initialize memory pool\n");
    }

    /* Initialize memory pool to allow rows up to 32,000 elements */
    initialize_memory_pool(15);

    if (print_mode >= 2) {
        printf("About to call start_gsi\n");
    }
#ifdef WIN32
    gsi_initialize_for_win32(NULL, NULL);
#endif
    gsi_start(argc, argv);
    
    return 0;
}


char* untilde(char *filename)
{
  char *part;
  if(strtok(filename, "~") == NULL) return filename;
  while((part = strtok(NULL, "~")) != NULL) {
      strcat(filename, part);
  }	
  return filename;
}


void signal_block_error(char const *error_text)
{
    /* write error message into outfile */
    FILE *odrp = fopen (err_file, "w");
    if (odrp == NULL) {
        longjmp(jmpenv, CANT_OPEN_FILE);
    }
    fprintf(odrp, "%s", error_text);
    fclose (odrp);

    if (print_mode > 2) {
        printf("In signal_block_error, wrote error file.  About to longjmp \n");
    }

    longjmp(jmpenv, OTHER_ERROR);

    if (print_mode > 2) {
        printf("longjmp failed \n");
    }
}



void toggle_print_mode(gsi_item *args, gsi_int count, gsi_int call_index)
{
    print_mode = gsi_int_of(args[0]);
    if (print_mode == 0) printf("Turning off printing\n");
    else if (print_mode == 1) printf("Enabling printing\n");
    else if (print_mode == 2) printf("Enabling memory checking\n");
    else if (print_mode > 2) printf("Enabling debug mode\n");

    gsi_set_int(args[0], 1);
    gsi_rpc_return_values(args, 1, call_index, current_context);
}  


void bpn_trainer(char*, char*);
void autoassociative_net(char*, char*);
void rho_trainer(char*, char*);
void optimizer(char*, char*);

static void ping(char const* infile, char const* outfile)
{
    /* test to see if we can open the input file for reading */
    FILE *idrp = fopen(infile, "r");
    if (idrp == NULL) {
        longjmp(jmpenv, CANT_OPEN_FILE);
    }
    fclose(idrp);
    /* the following tests the output file by writing the error string into it */
    signal_block_error("Unknown block type: PING");
}


void rbfn_trainer(char*, char*);
void fit_tester(char*, char*);
void sensitivity_tester(char*, char*);


void rpc_run_block(gsi_item *args, gsi_int count, gsi_int call_index)
{
    int err_code;
    char *block_name = str_of(args[0]);
    char *infile = gsi_str_of(args[1]);
    char *outfile = gsi_str_of(args[2]);
    char *permission = gsi_str_of(args[3]);

    err_file = outfile; /*   globalized output file */

    if (print_mode > 2) {
        printf("in rpc_run_block\n");
        printf("Blockname = %s\n", block_name);
        printf("Infile = %s\n", infile);
        printf("Outfile = %s\n", outfile);
    }

    /* strip tilde characters from file names (important under NT since backslash is a special character) */
    infile = untilde(infile);
    outfile = untilde(outfile);
  
    srand(time(NULL));  /* initialize random number generator in case it is needed */
    err_code = setjmp(jmpenv);  /* from longjmp, error message in outfile */

    if (print_mode > 2) {
        printf("After setjmp, err_code = %d\n",err_code);
    }

    if (err_code == OTHER_ERROR) {
        gsi_set_int(args[0], 0);
        gsi_rpc_return_values(args, 1, call_index, current_context);
        return;
    }
    if (err_code == CANT_OPEN_FILE) {
        gsi_set_int(args[0], -1);
        gsi_rpc_return_values(args, 1, call_index, current_context);
        return;
    }
    else if (err_code != 0) {
        /* some unknown-unexpected error */
        gsi_set_int(args[0], -2);
        gsi_rpc_return_values(args, 1, call_index, current_context);
        return;
    }

    if (strcmp(permission, "pqowiekdsj") != 0) {
        signal_block_error("NOL-RPC-PERMISSION-DENIED\n");
    }

    if (strcmp(block_name, "BPN-TRAINER") == 0) bpn_trainer(infile, outfile);
    else if (strcmp(block_name, "AUTOASSOCIATIVE-NET") == 0) autoassociative_net(infile, outfile);
    else if (strcmp(block_name, "RBFN-TRAINER") == 0) rbfn_trainer(infile, outfile);
    else if (strcmp(block_name, "RHO-TRAINER") == 0) rho_trainer(infile, outfile);
    else if (strcmp(block_name, "FIT-TESTER") == 0) fit_tester(infile, outfile);
    else if (strcmp(block_name, "SENSITIVITY-TESTER") == 0) sensitivity_tester(infile, outfile); 
    else if (strcmp(block_name, "OPTIMIZER") == 0) optimizer(infile, outfile);
    else if (strcmp(block_name, "PING") == 0) ping(infile, outfile); 
    else {  
        char err_text[100];
        snprintf(err_text, sizeof err_text, "Unknown block type: %s", block_name);
        signal_block_error(err_text);
    }
    if (print_mode > 1) {
        memory_summary();
    }

    gsi_set_int(args[0], 1);
    gsi_rpc_return_values(args, 1, call_index, current_context);
}


void InitUsrRpcs()
{
    /* This function served the same purpose in the old version
        as `gsi_set_up()` in the new version, so we just delegate. 
        This function is left "just in case", should be removed 
        once we convince ourselves it's not needed any more.
        */
    gsi_set_up();
}

void gsi_set_up() 
{ 
    gsi_rpc_declare_local(rpc_run_block, "RPC_RUN_BLOCK");
    gsi_rpc_declare_local(toggle_print_mode, "TOGGLE_PRINT_MODE");
} 



 /*  FUNCTIONAL ROUTINES FOR BACKPROP NETWORKS */
matrix *quadratic(p)
matrix *p;
{
  pointer_to_stack local_ptr = ans;
  double discrim,p1,p2;
  matrix *x = NULL;
  p1 = p->pm[1][1];
  p2 = p->pm[1][2];
  discrim = p1*p1 - 4.0*p2;
  if(discrim < 0.0) {matrix_return(x);}
  set(x,newmat(1,2));
  x->pm[1][1] = 0.5*(-p1+sqrt(discrim));
  x->pm[1][2] = 0.5*(-p1-sqrt(discrim));
  matrix_return(x);
}

matrix *cubic(a)
matrix *a;
{
  pointer_to_stack local_ptr = ans;
  double p,q,r,t,y1,y2,y3,a1,a2,a3,pp,aa,bb;
  matrix *x = NULL;
  a1 = a->pm[1][1]; 
  a2 = a->pm[1][2];
  a3 = a->pm[1][3];
  p = (3*a2 - a1*a1)/3;
  q = (27*a3 - 9*a1*a2 + 2*a1*a1*a1)/27;
  r = p*p*p/27 + q*q/4;
  if(r <= 0) {
   t = -acos(sqrt((q*q/4)/(-p*p*p/27)));
   pp = sqrt(-p/3);
   if(q > 0) {
     y1 = -2*pp*cos(t/3);
     y2 = -2*pp*cos(t/3 + 2*PI/3);
     y3 = -2*pp*cos(t/3 + 4*PI/3); 
   }
   else {
     y1 = 2*pp*cos(t/3);
     y2 = 2*pp*cos(t/3 + 2*PI/3);
     y3 = 2*pp*cos(t/3 + 4*PI/3); 
   }
   set(x,newmat(1,3));
   x->pm[1][1] = y1 - a1/3;
   x->pm[1][2] = y2 - a1/3;
   x->pm[1][3] = y3 - a1/3;
   matrix_return(x);
 }
 else {
   aa = -q/2 + sqrt(r);
   if(aa>=0) aa = pow(aa,1./3.);
   else aa = - pow(fabs(aa),1./3.);
   bb = -q/2 - sqrt(r);
   if(bb>=0) bb = pow(bb,1./3.); 
   else bb = - pow(fabs(bb),1./3.);
   y1 = aa + bb;
   set(x,newmat(1,1));
   x->pm[1][1] = y1 - a1/3;
   matrix_return(x);
 }
}


matrix *quartic(b)
matrix *b;
{
 pointer_to_stack local_ptr = ans;
 double p,q,r,b1,b2,b3,b4,bb1,st0;

 matrix *t0=NULL,*z=NULL,*a=NULL,*c=NULL;
 if(b->pm[1][4]==0.0) {
     set(c,append_lr(cubic(part(b,1,1,1,3)),zeros(1,1)));
     matrix_return(c);
   }  
 b1 = b->pm[1][1];
 b2 = b->pm[1][2];
 b3 = b->pm[1][3];
 b4 = b->pm[1][4];
 bb1 = b1*b1;
 p = -(3./8.)*bb1 + b2;
 q = bb1*b1/8. - b1*b2/2. + b3;
 r = -3.*bb1*bb1/256. + b2*bb1/16. - b3*b1/4. + b4;
 set(a,newmat(1,3));
 a->pm[1][1] = -p;
 a->pm[1][2] = -4.*r;
 a->pm[1][3] = 4.*p*r - q*q;
 set(t0,cubic(a));
 set(t0,maximum(t0));
 st0 = t0->pm[1][1];
 if(st0 >= p) {
   set(c,newmat(1,2));
   c->pm[1][1] = sqrt(st0 - p);
   c->pm[1][2] = st0/2. - q/(2.*c->pm[1][1]);
   set(z,quadratic(c));
   if(z == NULL) {
     c->pm[1][2] = st0/2. + q/(2.*c->pm[1][1]);
     c->pm[1][1] = - c->pm[1][1];
     set(z,quadratic(c));
     if(z==NULL) {matrix_return(z);}
   }
 }
 else {
  fm(t0);fm(a);fm(c);
  matrix_return(z);
 }
 set(t0,scalar_mult(b1/4.,ones(1,z->n)));
 if(z->n > 0) {set(z,subtract(z,t0));}
 fm(t0);fm(a);fm(c);
 matrix_return(z);
}


matrix *fliplr(a)
matrix *a;
/*flips a matrix, so the leftmost column becomes the rightmost column */ 
{
  pointer_to_stack local_ptr = ans;
  int n,m,i,j;
  matrix *c=NULL;
  m = a->m;
  n = a->n;
  set(c,newmat(m,n));
  for(i=1; i<=m; ++i) 
    for(j=1; j<=n; ++j) c->pm[i][n-j+1] = a->pm[i][j];
  matrix_return(c);
}


matrix *polyder(a)
matrix *a;
{
  pointer_to_stack local_ptr = ans;
  int m,n,j;
  matrix *c=NULL;
  m = a->m;
  n = a->n;
  if(m != 1) printf("Warning: matrix with > 1 row in polyder\n");
  if(n<=1) {matrix_return(c);}
  set(c,newmat(1,n-1));
  for (j=1; j<=n-1; ++j) c->pm[1][j] = a->pm[1][j]*((double)(n-j));
  matrix_return(c);
}


matrix *array_insert_in_order(x,y)
double x;
matrix *y;
/* inserts x into its proper place in ascending-order array y and
   returns index i where insertion was made */
{
  pointer_to_stack local_ptr = ans;
  int ny,i,j;
  matrix *z=NULL,*index=NULL;
  ny = y->n;
  ++ny;
  set(z,zeros(1,ny));
  z->pm[1][ny] = DBL_MAX;
  for(i=1; i<ny; ++i) {
    if(x < y->pm[1][i]) break;
  }
  for(j=1; j<i; ++j) z->pm[1][j] = y->pm[1][j];
  z->pm[1][i] = x;
  for(j=i+1; j<=ny; ++j) z->pm[1][j] = y->pm[1][j-1];
  set(index,i2m(i));
  matrix_return2(z,index); 
}

#define FREE_NEXTSTEP fm(p);fm(dp);fm(rhs);fm(lhs);fm(sl)

double nextstep(dy0,x,y)
double dy0;
matrix *x, *y;
{
  pointer_to_stack local_ptr = ans;
  double dsl;
  int i,n;
  matrix *p=NULL,*dp=NULL,*rhs=NULL,*lhs=NULL,*sl=NULL;
  n = x->n;
  set(p,newmat(1,2));
  p->pm[1][1] = y->pm[1][1];
  p->pm[1][2] = dy0;
  set(rhs,subtract(part(y,1,2,1,n),add(scalar_mult(dy0,part(x,1,2,1,n)),scalar_mult(p->pm[1][1],ones(1,n-1)))));
  set(lhs,transpose(mult_ebe(part(x,1,2,1,n),part(x,1,2,1,n))));
  for(i=3; i<=n; ++i) {set(lhs,append_lr(lhs,mult_ebe(part(lhs,1,i-2,lhs->m,i-2),transpose(part(x,1,2,1,n)))));}
  set(rhs,linear_solve(lhs,transpose(rhs)));
  if(rhs==NULL) {  /* singular error return from linear_solve */
     dsl = -1.0;   /* use negative step length to signal error */
     FREE_NEXTSTEP;
     return(dsl);
  }
  else {set(dp,transpose(rhs));}
  set(p,append_lr(p,dp));
  set(dp,polyder(fliplr(p)));
if(print_mode>2) {
  print_matrix(dp, " In nextstep, solving polynomial: ");
}  
/* MK 2/1/94:  Strip potential leading zeros before solving */  
  while(dp->pm[1][1]==0.0) {
    if (dp->n == 2) {  /* error: degenerate polynomial */ 
       dsl = -1.0;
       FREE_NEXTSTEP;
       return(dsl);
    }
    set(dp,part(dp,1,2,1,dp->n));
  }

  set(dp,scalar_divide(dp->pm[1][1],dp));
  set(dp,part(dp,1,2,1,dp->n));
  if(dp->n==1) {set(sl,d2m(-dp->pm[1][1]));}
  else if (dp->n==2) {set(sl,quadratic(dp));}
  else if (dp->n==3) {set(sl,cubic(dp));}
  else if (dp->n==4) {set(sl,quartic(dp));}
  if(sl != NULL) {set(sl,find(sl,gt(sl,zeros(sl->m,sl->n))));}
  if(sl == NULL) {set(sl,scalar_mult(2.0,maximum(x)));}
  else {set(sl,minimum(sl));}
  dsl = sl->pm[1][1];
  FREE_NEXTSTEP;
  return(dsl);
}


#define INITIAL_SL 0.01
#define FREE_TRAIN fm(defalt);fm(h);fm(df);fm(nextw);fm(direc);fm(delw);fm(prevw);fm(dw);fm(prevdf);fm(deldf);fm(fa);fm(term1);fm(term2);fm(fvec);fm(wvec);fm(index)


matrix *train(w0,func,dfunc,cntrl0,opt_arg)
matrix *w0, *cntrl0;
matrix **opt_arg;
matrix* (*dfunc)();
double (*func)();
/* unconstrained nonlinear optimization routine with or without gradients */
{
 pointer_to_stack local_ptr = ans;
 matrix *defalt=NULL,*h=NULL,*df=NULL,*nextw=NULL,*direc=NULL,*delw=NULL,*prevw=NULL;
 matrix *w=NULL,*dw=NULL,*prevdf=NULL,*deldf=NULL,*fa=NULL,*term1=NULL,*term2=NULL;
 matrix *fvec=NULL,*wvec=NULL,*cntrl=NULL,*index=NULL;
 double gtol=5.e-5,ftol=5.e-5,steptol=1.e-15 /*1.e-7*/,dwmin=1.e-4,dwmax=0.1,sl=INITIAL_SL;
 double prevf,prevdls,f,func0,fold=0.0,slold,gg,dgg,gam,iterhold,startiter,fmin,fnew,slmin;
 double nextstep();
 int grad_reset,nvars,np,cg,i,j,k,go,polylen,imin,factor;
 int prog=0,count=0,method=0,loop=0;
 char meth[20],msg[100];
if(print_mode>2) {
print_matrix(cntrl0,"Entering train, cntrl = "); 
}
 set(w,copy(w0));
 nvars = max(w->m,w->n);
 if(w->m != 1) {set(w,reshape2(w,1,nvars));} /* make sure w is row vector */
 np = cntrl0->n;
 if(np<6) {
   set(defalt,zeros(1,6));
   if(nvars<100) defalt->pm[1][3] = 3;
   set(cntrl,append_lr(cntrl0,part(defalt,1,np+1,1,6)));
 }
 else {set(cntrl,copy(cntrl0));}
 grad_reset = min(50,ceil(0.7*((float) nvars)));
 if(cntrl->pm[1][3] < 2.5) cg = 1;
 else {set(h,eye(nvars));cg = 0;}
 startiter = cntrl->pm[1][4];
 cntrl->pm[1][4] = 1.0;
 f = func(w,opt_arg); func0 = f; 
if(print_mode>2) {
printf("INITIAL FUNCTION VALUE = %f\n",f);
}
 set(nextw,copy(w)); set(df,zeros(1,nvars)); set(direc,copy(nextw));
if(print_mode>2) {
print_matrix(direc,"INITIAL DIRECTION = ");
}
 if(print_mode > 0) {
    printf("\n\n GRADIENTS FUNCTIONS  OBJECTIVE METHOD\n");
    i = floor(cntrl->pm[1][5]+DBL_EPSILON) - 1;
    j = floor(startiter+cntrl->pm[1][4]+DBL_EPSILON);
    printf("%6d %8d %12.4g\n",max(0,i),j,f);
    strcpy(msg,"");
 }
 print_mode = abs(print_mode);
 while(loop != 2) {
if(print_mode>2) {
printf("Beginning of step, obj = %f, \n",f);
print_matrix(w,"w = ");
}
   set(w,copy(nextw));
   if(dfunc != NULL) { /* dfunc provided */
      cntrl->pm[1][5] += 1.0;
      set(df,dfunc(w,opt_arg));
#if GRAD_CHECK 
print_matrix(df,"ANALYTICAL DERIVATIVES ");
prevf=f;
set(dw,mult_ebe(sign(add(direc,scalar_mult(DBL_EPSILON,ones(1,nvars)))),bounds(scalar_mult(0.01,absolute(scalar_mult(sl,direc))),dwmin,dwmax)));
for(k=1; k<=nvars; ++k) {
  w->pm[1][k] +=  dw->pm[1][k];
  f = func(w,opt_arg);
  df->pm[1][k] = (f-prevf)/dw->pm[1][k];
  w->pm[1][k] -=  dw->pm[1][k]; 
}
f = prevf; cntrl->pm[1][4] = cntrl->pm[1][4] + (double) nvars;
print_matrix(df,"NUMERICAL DERIVATIVES");
#endif
    } 
   else { /* Numerical derivatives: dfunc = NULL */
      prevf=f;
      set(dw,mult_ebe(sign(add(direc,scalar_mult(DBL_EPSILON,ones(1,nvars)))),bounds(scalar_mult(0.01,absolute(scalar_mult(sl,direc))),dwmin,dwmax)));
      for(k=1; k<=nvars; ++k) {
        w->pm[1][k] +=  dw->pm[1][k];
        f = func(w,opt_arg);
        df->pm[1][k] = (f-prevf)/dw->pm[1][k];
        w->pm[1][k] -=  dw->pm[1][k]; 
      }
      f = prevf; cntrl->pm[1][4] = cntrl->pm[1][4] + (double) nvars;
if(print_mode>2) {
print_matrix(df,"NUMERICAL DERIVATIVES");      
}
   }
   if(loop==0) {
      set(direc,chsign(df));
      prevdls = m2d(mult(df,transpose(direc)));
      sl = max(0.01, min(1.0,2.0*fabs(f/prevdls)));
if(print_mode>2) {
printf("Initial steepest descent step SL = %f, prevdls = %g\n",sl,prevdls);
}
      strcpy(meth,"steepest descent");
    }
    else {  /* not first iter, get descent direction, not steepest descent */
if(print_mode>2) {
printf("Calculating descent direction, meth = %f\n", cntrl->pm[1][3]);
}
      ++count;
      if(cg && count>=grad_reset) {
         count=0; method=(int)cntrl->pm[1][3];cntrl->pm[1][3] = 0.0;
      }
      if(cntrl->pm[1][3]==0.0) {
         set(direc,chsign(df)); strcpy(meth,"steepest descent");
      }
      else if (cntrl->pm[1][3]==1.0) {
         gg=ssq(prevdf);
         dgg=ssq(df);
         gam = dgg/gg;
         set(direc,subtract(scalar_mult(gam,direc),df));
         strcpy(meth,"FR conj grad");
      }
      else if (cntrl->pm[1][3]==2.0) {
         gg=ssq(prevdf);
         dgg=m2d(mult(subtract(df,prevdf),transpose(df)));
         gam = dgg/gg;
         set(direc,subtract(scalar_mult(gam,direc),df));
         strcpy(meth,"PR conj grad");
      }
      else if (cntrl->pm[1][3]==3.0) {
	set(delw,subtract(nextw,prevw));
         set(deldf,subtract(df,prevdf));
         set(fa,mult(delw,h));
	 set(term1,scalar_divide(m2d(mult(delw,transpose(fa))),mult(transpose(fa),fa)));
	 set(term2,scalar_divide(m2d(mult(deldf,transpose(delw))),mult(transpose(deldf),deldf)));
         set(h,add(subtract(h,term1),term2));
         set(term1,linear_solve(h,transpose(chsign(df))));
         if(term1==NULL) {      /* error return from linear_solve */
            if(print_mode>0) printf("Warning: bad gradient calc by BFGS\n");
            loop = 2;
         }
         else {set(direc,transpose(term1));}
         strcpy(meth,"Broyden");
      }
      else if (cntrl->pm[1][3]==4.0) {
         set(delw,subtract(nextw,prevw));
         set(deldf,subtract(df,prevdf));
         set(fa,mult(deldf,h));
         set(term1,scalar_divide(m2d(mult(delw,transpose(deldf))),mult(transpose(delw),delw)));
         set(term2,scalar_divide(m2d(mult(deldf,transpose(fa))),mult(transpose(fa),fa)));
         set(h,subtract(add(h,term1),term2));
         set(direc,mult(chsign(df),h));
         strcpy(meth,"Davidon");
      }
    }  /* end of search direction calculation */
   if(loop != 2) {
     if(method != 0) {cntrl->pm[1][3]=(double)method;method=0;}
     set(prevw,copy(nextw));
     set(prevdf,copy(df));
     loop = 1; func0 = f;
     prevdls=m2d(mult(df,transpose(direc))); 
     set(nextw,add(nextw,scalar_mult(sl,direc))); 
   }
   if(prevdls > 0.0) {  /* bad descent direction, actually ascent (+ve) */
if(print_mode>2) {
printf("Calling recursively: prevdls = %f\n",prevdls); 
}
     set(w,copy(prevw));
     iterhold = cntrl->pm[1][1];
     print_mode = -print_mode;
     cntrl->pm[1][1] -= cntrl->pm[1][4];
     cntrl->pm[1][4] += (startiter - 1.0);
     set2(w,cntrl,train(w,func,dfunc,cntrl,opt_arg));
     cntrl->pm[1][1] += iterhold;
     FREE_TRAIN; 
     matrix_return2(w,cntrl);
   }
if(print_mode>2) {
printf("Prevdls = %g and direc = \n",prevdls);
print_matrix(direc,"");
}
   if(m2d(maximum(absolute(direc)))<gtol && fabs(prevdls)<gtol) {
     if(print_mode>0) strcpy(msg,"Training terminated: gradient criteria");
     loop = 2; set(nextw,copy(prevw));
   }
   else if(cntrl->pm[1][4] >= cntrl->pm[1][1]) {
     if(print_mode>0) strcpy(msg,"Maximum number of function calls exceeded");
     loop = 2; set(nextw,copy(prevw));
   }
   else if (loop==1) {  /* begin line search */
if(print_mode>2) {
printf("Beginning line search \n");
}
     set(fvec,zeros(1,2)); set(wvec,zeros(1,2));
     fvec->pm[1][1] = func0;
     set(w,copy(nextw));
     fmin = func(w,opt_arg);
if(print_mode>2) {
printf("New function value = %f\n",fmin);
}
     fvec->pm[1][2] = fmin;
     cntrl->pm[1][4] += 1.0;
     wvec->pm[1][2] = sl;
     go=2;factor=1;polylen=2;
     if(fmin < func0) imin=2; else imin = 1;  /** !!!!! **/
     if(imin == 1) fmin = func0;
     while(go>0) {
        slold = sl;
        sl = nextstep(prevdls,wvec,fvec);
        if(sl<0.0) {loop = 2; break;} /* error return from nextstep */
if(print_mode>2) {
printf("\nNextstep calculates SL = %f with prevdls = %g\n",sl,prevdls);
}
        if(polylen !=2 && fabs((slold-sl)/(sl+DBL_EPSILON))<0.001) break;
        ++polylen;
        set2(wvec,index,array_insert_in_order(sl,wvec));
        i = m2i(index);
if(print_mode>2) {
printf("Insertion point is %d\n",i);
}
        if(polylen > 5) go = 0;  /* maximum order polynomial */
        set(w,add(prevw,scalar_mult(sl,direc))); /*prevw corresponds wvec = 0 */
        fnew = func(w,opt_arg);
        set(fvec,insert(fvec,d2m(fnew),i));
        if(fnew < fmin) {
          set(nextw,copy(w)); fmin = fnew; imin = i;
        }
        else if(i<=imin) ++imin;
        cntrl->pm[1][4] += 1.0;
        if(imin != 1 && imin != polylen) --go;
if(print_mode>2) {
printf("imin = %d, polylen = %d, go = %d, ", imin,polylen,go);
printf("sl = %f, wvec and fvec are: ",sl);
print_matrix(wvec,"wvec");
print_matrix(fvec,"fvec");
}
        if(go !=0 && sl<steptol) {
          go = 0; loop = 2;
          if(print_mode>0)
            strcpy(msg,"Training terminated: step length criteria");
        }
     } /*while go*/
     if(imin==1) { /* Did not find a feasible step, reduce SL by factors of 10 */
        f = fmin;
        while(sl>=steptol) {  /* look for best small step */
           sl=sl/10.0;
           set(w,add(prevw,scalar_mult(sl,direc)));
           fnew = func(w,opt_arg);
	   cntrl->pm[1][4] += 1.0;
           if(fnew < fmin) {
             set(nextw,copy(w)); fmin = fnew; slmin = sl;
           }
 	   if(print_mode>2) {
             printf("Tried reduced step length = %g, fnew = %g, fmin = %g\n", sl, fnew, fmin);
           }
	}   
	if(fmin < f) {f = fmin; sl = slmin;}
	else {set(nextw,copy(prevw));loop = 2; strcpy(msg,"Training terminated: Steplength criteria 2");}
     } else {   /* imin > 1 */
       sl = wvec->pm[1][imin]; f = fmin;
     }
     if(fabs((f-fold)/f) < ftol) {
        ++prog;
        if(prog >= 5) {loop=2; strcpy(msg,"Training terminated: no more progress");}
     }
     else prog=0;
     fold = f;
     if(print_mode>0) {
        i = floor(cntrl->pm[1][5]+DBL_EPSILON);
        j = floor(startiter+cntrl->pm[1][4]+DBL_EPSILON);
        printf("%6d %8d %12.4g %s\n",max(0,i),j,f,meth);
     }
   } /* else if (loop == 1) */
   set(w,copy(nextw));
 } /* while(loop != 2) */
 cntrl->pm[1][4] += startiter;
 cntrl->pm[1][6] = func(w,opt_arg);
 if(print_mode>0) printf("\n%s\n",msg);
 FREE_TRAIN;
if(print_mode>2) {
 printf("Exiting train  \n");
}
 matrix_return2(w,cntrl);
}


double f_bpn(weights,opt_arg)
matrix *weights;
matrix **opt_arg;  /* array of optional arguments */
{
  pointer_to_stack local_ptr = ans;
  matrix *run_bpn();
  matrix *y_pred=NULL,*f=NULL,*x=NULL,*y=NULL,*nodes=NULL,*tf=NULL;
  double sf;
if(print_mode>2) {
printf("Entering f_bpn\n");
}
  x = opt_arg[0];
  y = opt_arg[1];
  nodes = opt_arg[2];
  tf = opt_arg[3];
  set(y_pred,run_bpn(x,nodes,tf,weights));
  set(f,subtract(y,y_pred));
  set(f,mult_ebe(f,f));
  set(f,sum(sum(f)));
  sf = f->pm[1][1];
  fm(y_pred);fm(f);
if(print_mode>2) {
printf("Leaving f_bpn, sf = %f\n", sf);
}
  return sf;
} 

matrix *run_bpn(x,nodes,tf,weights)
matrix *x,*nodes,*tf,*weights;
{
  pointer_to_stack local_ptr = ans;
  int k,nin,nlayer;
  matrix *w1=NULL,*w2=NULL,*w3=NULL,*w4=NULL;
  matrix *wt_mat(),*sigmoid0(),*y_pred=NULL;
  matrix *act1=NULL,*act2=NULL,*act3=NULL,*act4=NULL;
if(print_mode>2) {
printf("Entering run_bpn\n");
}
  k = x->m;
  nin = x->n;
  nlayer = tf->n;
  set4(w1,w2,w3,w4,wt_mat(weights,nodes));
  set(act1,copy(x));
  if(tf->pm[1][1] > 0.0) {set(act1,sigmoid0(act1));}
  set(act1,append_lr(act1,ones(k,1)));
  set(act2,mult(act1,w1));
  if(tf->pm[1][2] > 0.0) {set(act2,sigmoid0(act2));}
  if(nlayer == 2) {
     y_pred = act2; act2 = NULL;
     goto exit;
   }
  set(act2,append_lr(act2,ones(k,1)));
  set(act3,mult(act2,w2));
  if(tf->pm[1][3] > 0.0) {set(act3,sigmoid0(act3));}
  if(nlayer == 3) {
     y_pred = act3; act3 = NULL;
     goto exit;
   }
  set(act3,append_lr(act3,ones(k,1)));
  set(act4,mult(act3,w3));
  if(tf->pm[1][4] > 0.0) {set(act4,sigmoid0(act4));}
  if(nlayer == 4) {
     y_pred = act4; act4 = NULL;
     goto exit;
   }
  set(act4,append_lr(act4,ones(k,1)));
  set(y_pred,mult(act4,w4));
  if(tf->pm[1][5] > 0.0) {set(y_pred,sigmoid0(y_pred));}
 exit:
if(print_mode>2) {
printf("Leaving run_bpn\n");
}
  fm(w1);  fm(w2); fm(w3); fm(w4);
  matrix_return5(y_pred,act1,act2,act3,act4);
}


matrix *sigmoid0(a)
matrix *a;
{
  pointer_to_stack local_ptr = ans;
  int i,j;

  matrix *c=NULL;
  set(c,newmat(a->m,a->n));
  for(i=1;i<=a->m;++i)
    for(j=1;j<=a->n;++j) {
      c->pm[i][j] = (a->pm[i][j] >= SIGMOID_LIM ? 1.0 : (a->pm[i][j] <= -SIGMOID_LIM ?  -1.0 : (2.0/(1.0 + exp(-a->pm[i][j])) - 1.0)));
    }
  matrix_return(c);
}

matrix *delta_rule(d,act)
matrix *d,*act;
{
  pointer_to_stack local_ptr = ans;
  int i,j;
  matrix *dout=NULL;
  set(dout,newmat(d->m,d->n));
  for(i=1;i<=d->m;++i)
    for(j=1;j<=d->n;++j) {
      dout->pm[i][j] = d->pm[i][j]*(1.0 + act->pm[i][j])*(1.0 - act->pm[i][j]);
    }
  matrix_return(dout);
}


matrix *wt_mat(weights,nodes)
matrix *weights,*nodes;
{
  pointer_to_stack local_ptr = ans;
  int nlayer,start=1,finish;
  matrix *w1=NULL,*w2=NULL,*w3=NULL,*w4=NULL;
  nlayer = nodes->n;
  finish = ((int)nodes->pm[1][1] + 1)*((int)nodes->pm[1][2]);
  set(w1, part(weights,1,start,1,finish));
  set(w1, reshape2(w1,(int)nodes->pm[1][1] + 1,(int)nodes->pm[1][2]));
  if(nlayer > 2) {
    start = finish + 1;
    finish += ((int)nodes->pm[1][2] + 1)*((int)nodes->pm[1][3]);
    set(w2, part(weights,1,start,1,finish));
    set(w2, reshape2(w2,(int)nodes->pm[1][2] + 1,(int)nodes->pm[1][3]));
  }
  if(nlayer > 3) {
    start = finish + 1;
    finish += ((int)nodes->pm[1][3] + 1)*((int)nodes->pm[1][4]);
    set(w3, part(weights,1,start,1,finish));
    set(w3, reshape2(w3,(int)nodes->pm[1][3] + 1,(int)nodes->pm[1][4]));
  }
  if(nlayer > 4) {
    start = finish + 1;
    finish += ((int)nodes->pm[1][4] + 1)*((int)nodes->pm[1][5]);
    set(w4, part(weights,1,start,1,finish));
    set(w4, reshape2(w4,(int)nodes->pm[1][4] + 1,(int)nodes->pm[1][5]));
  }
  matrix_return4(w1,w2,w3,w4);
}


matrix *wt_vec(w1,w2,w3,w4)
matrix *w1,*w2,*w3,*w4;
{
  pointer_to_stack local_ptr = ans;
  matrix *weights=NULL,*nodes=NULL;
  set(nodes,size(w1));
  nodes->pm[1][1] -= 1.0;
  set(weights,reshape2(w1,1,w1->m*w1->n));
  if(w2 != NULL) {
      set(nodes,append_lr(nodes,i2m(w2->n)));
      set(weights,append_lr(weights,reshape2(w2,1,w2->m*w2->n)));
  }
  if(w3 != NULL) {
      set(nodes,append_lr(nodes,i2m(w3->n)));
      set(weights,append_lr(weights,reshape2(w3,1,w3->m*w3->n)));
  }
  if(w4 != NULL) {
      set(nodes,append_lr(nodes,i2m(w4->n)));
      set(weights,append_lr(weights,reshape2(w4,1,w4->m*w4->n)));
  }
  matrix_return2(weights,nodes);
}



matrix *df_bpn(weights,opt_arg)
matrix *weights;
matrix **opt_arg;
{
  pointer_to_stack local_ptr = ans;
  int i,k,nout,layer,nlayer;
  matrix **a,**w,**dw; /* layer arrays of activations, weight matrices, wt differentials */
  matrix *y_pred=NULL,*d=NULL,*df=NULL,*delta_rule();
  matrix *x,*y,*nodes,*tf;
  x = opt_arg[0];
  y = opt_arg[1];
  nodes = opt_arg[2];
  tf = opt_arg[3];
  nlayer = nodes->n;
  a = (matrix **) calloc(4,sizeof(pointer_to_matrix)); a -= 1;
  set5(y_pred,a[1],a[2],a[3],a[4],run_bpn(x,nodes,tf,weights));
  k = y_pred->m;
  nout = y_pred->n;
  w = (matrix **) calloc(4,sizeof(pointer_to_matrix)); w -= 1;
  dw = (matrix **) calloc(4,sizeof(pointer_to_matrix)); dw -= 1;
  set4(w[1],w[2],w[3],w[4],wt_mat(weights,nodes));
  set(d,subtract(y_pred,y));
  if(tf->pm[1][nlayer]==1.0) {set(d,delta_rule(d,y_pred));}
  else {set(d,scalar_mult(2.0,d));}
  set(dw[nlayer-1],mult(transpose(a[nlayer-1]),d));
  for(layer=nlayer-1;layer>=2;--layer) {
      set(d,mult(d,transpose(part(w[layer],1,1,w[layer]->m - 1,w[layer]->n))));
      if(tf->pm[1][layer] > 0.0)
	{set(d,scalar_mult(0.5,delta_rule(d,part(a[layer],1,1,a[layer]->m,a[layer]->n - 1))));}
      set(dw[layer-1],mult(transpose(a[layer-1]),d));
  }
  for(i=1;i<=nlayer-1;++i) {set(df,append_lr(df,reshape2(dw[i],1,dw[i]->m*dw[i]->n)));}
  fm(y_pred); fm(d);
  for(i=1;i<=4;++i) {fm(dw[i]);fm(w[i]);fm(a[i]);}
  free(a + 1); free(w + 1); free(dw + 1);
  matrix_return(df);
}


matrix *wt_init(nodes,seed)
matrix *nodes;
unsigned seed;
{
  pointer_to_stack local_ptr = ans;
  int i,nlayer,nwt;
  matrix *w0=NULL;
  nlayer = nodes->n;
  nwt = 0;
  for(i=2;i<=nlayer;++i) nwt += (int) (nodes->pm[1][i] * (nodes->pm[1][i-1] + 1.0));
  srand(seed);
  set(w0,mat_random(1,nwt,-1.0,1.0));
  matrix_return(w0);
}


matrix *make_bpn(x,y,nodes,tf,w0,cntrl0)
matrix *x,*y,*nodes,*tf,*w0,*cntrl0;
{
  pointer_to_stack local_ptr = ans;
  matrix *w=NULL,*cntrl=NULL,*df_bpn();
  matrix **opt_arg;
  double f_bpn();
  int init_flag,check_specs_bpn();
  unsigned seed;
  set(w,copy(w0));  /* bug fix 2/16/94 -- Cannot use set on guments -- therefore copy first  */
  init_flag = check_specs_bpn(x,y,nodes,tf,w,cntrl0);
  if(!init_flag) {
    seed = time(NULL);
    set(w,wt_init(nodes,seed));
  }
  opt_arg = (matrix **) calloc(4,sizeof(pointer_to_matrix));
  opt_arg[0] = x;
  opt_arg[1] = y;
  opt_arg[2] = nodes;
  opt_arg[3] = tf;
  set2(w,cntrl,train(w,f_bpn,df_bpn,cntrl0,opt_arg));
  free(opt_arg);
  matrix_return2(w,cntrl);
}


int check_specs_bpn(x,y,nodes,tf,w,cntrl)
matrix *x,*y,*nodes,*tf,*w,*cntrl;
{
/* Checks specification of bpn.  Returns 1 if the network is properly initialized.
   Returns 0 if network needs to be initialized.  Otherwise, errors are signaled. */
  pointer_to_stack local_ptr = ans;
  int i,nw=0,init_flag=1;
  matrix *wsum=NULL;
  if(x->m != y->m) signal_block_error("NOL-INCONSISTENT-DATA-SET\n");
  if(nodes->n > 5 || nodes->n < 2)
     signal_block_error("NOL-BPN-NUMBER-OF-LAYERS\n");
  if(nodes->m != 1) 
     signal_block_error("NOL-BAD-FILE-FORMAT\n");
  if(tf->m != 1) 
     signal_block_error("NOL-BAD-FILE-FORMAT\n");
  if(x->n != (int)nodes->pm[1][1]) 
    signal_block_error("NOL-INPUT-VECTOR-CONFIGURATION-MISMATCH\n");
  if(y->n != (int)nodes->pm[1][nodes->n]) 
     signal_block_error("NOL-TARGET-VECTOR-CONFIGURATION-MISMATCH\n");
  if(((int)cntrl->pm[1][3] > 4) || ((int)cntrl->pm[1][3] < 1))
     signal_block_error("NOL-UNCONFIGURED-BLOCK\n");
  if(tf->n != nodes->n)
     signal_block_error("NOL-CONFIGURE-BPN-ERROR\n");
  for(i=1;i<=nodes->n; ++i) {
     if((int) tf->pm[1][i] != 0 && (int) tf->pm[1][i] != 1)  
       signal_block_error("NOL-CONFIGURE-BPN-ERROR\n");
     if((int) nodes->pm[1][i] <= 0)
       signal_block_error("NOL-CONFIGURE-BPN-ERROR\n");
   }
  if(w==NULL) init_flag = 0;
  else {
     for(i=1;i<nodes->n;++i) nw += (((int)nodes->pm[1][i]+1)*((int)nodes->pm[1][i+1]));
     if(w->n != nw || w->m != 1)
        signal_block_error("NOL-OPERAND-BLOCK-NOT-CONFIGURED\n");
     set(wsum,sum(w));
     if(fabs(wsum->pm[1][1]) < nw*DBL_EPSILON) init_flag = 0;
     fm(wsum);
  }
  return init_flag;
}


void fit_tester(infile,outfile)
char *infile,*outfile;
{
  pointer_to_stack local_ptr = ans;
  matrix *x=NULL,*y=NULL,*tf=NULL,*nodes=NULL,*w=NULL,*y_pred=NULL;
  matrix *m=NULL,*shape=NULL;
  FILE *idfp,*odfp;
  void write_matrix();
  matrix *read_bpn(),*run_bpn(),*read_ds(),*read_rbfn(),*run_rbfn();
  int net_type,metric;
  double err,fit_metric();
  if(print_mode) printf("Running fit tester\n");  
  idfp = fopen(infile,"r");
  if(idfp == NULL) signal_block_error("NOL-RPC-OPEN-INPUT-FILE-ERROR\n");
  set2(x,y,read_ds(idfp));
  fscanf(idfp,"%d",&net_type);
  IGNORE_COMMENT(idfp);
  if(net_type==0) { 
    set3(nodes,tf,w,read_bpn(idfp));
    set(y_pred,run_bpn(x,nodes,tf,w));
  }
  else {
    set3(m,shape,w,read_rbfn(idfp));
    set(y_pred,run_rbfn(x,m,shape,w));    
  }
  fscanf(idfp,"%d",&metric);
  IGNORE_COMMENT(idfp);
  fclose(idfp);
  err = fit_metric(y,y_pred,metric);
  if(print_mode) printf("Fitting error = %f\n",err);
  odfp = fopen(outfile,"w");
  if(odfp == NULL) signal_block_error("NOL-RPC-OPEN-OUTPUT-FILE-ERROR\n");
  write_matrix(odfp,y_pred," ; predictions matrix");
  fprintf(odfp,"%#g ; fitting error\n",G2_LIMIT(err));
  fclose(odfp);
  fm(nodes); fm(tf); fm(w); fm(y);
  fm(x); fm(y_pred); fm(m); fm(shape);
}


double fit_metric(y,y_pred,metric)
matrix *y,*y_pred;
int metric;
{
  pointer_to_stack local_ptr = ans;
  double err,log_product();
  matrix *diff=NULL,*index1=NULL,*index2=NULL,*dum=NULL; 
  if(metric==0) {  /* rmse */
     set(diff,subtract(y,y_pred));
     set(diff,mult_ebe(diff,diff));
     set(diff,sum(sum(diff)));
     err = sqrt((diff->pm[1][1])/(y->m * y->n));
  }
  else if (metric==1) { /* class */
     set2(dum,index1,maximum(transpose(y)));
     set2(dum,index2,maximum(transpose(y_pred)));
     set(dum,sum(equal(index1,index2))); 
     err = 1.0 - m2d(dum)/y->m;
  }
  else if (metric==2) { /* logprob */
     err = -log_product(y_pred)/(y->m * y->n);
  }
  else signal_block_error("NOL-UNCONFIGURED-BLOCK\n");  /*BAD FIT METRIC*/
  fm(diff);fm(index1);fm(dum);fm(index2);  
  return err;
}


void sensitivity_tester(infile,outfile)
char *infile,*outfile;
{
  pointer_to_stack local_ptr = ans;
  matrix *x=NULL,*y=NULL,*tf=NULL,*nodes=NULL,*w=NULL,*y0=NULL,*dx=NULL; 
  matrix *m=NULL,*shape=NULL,*sm=NULL,*xnew=NULL,*ynew=NULL,*sv=NULL;
  FILE *idfp,*odfp;
  void write_matrix();
  matrix *read_bpn(),*run_bpn(),*read_ds(),*read_rbfn(),*run_rbfn();
  int i,j,k,nout,nin,net_type;
  double tiny=0.00001;
  if(print_mode) printf("Running sensitivity tester\n");  
  idfp = fopen(infile,"r");
  if(idfp == NULL) signal_block_error("NOL-RPC-OPEN-INPUT-FILE-ERROR\n");
  set2(x,y,read_ds(idfp));
  fscanf(idfp,"%d",&net_type);
  IGNORE_COMMENT(idfp);
  if(net_type==0) { 
    set3(nodes,tf,w,read_bpn(idfp));
    set(y0,run_bpn(x,nodes,tf,w));
  }
  else {
    set3(m,shape,w,read_rbfn(idfp));
    set(y0,run_rbfn(x,m,shape,w));    
  }
  fclose(idfp);
  k = y0->m;
  nout = y0->n;
  nin = x->n;
  set(sm,newmat(nin,nout));
  set(dx,zeros(k,nin));
  for(j=1;j<=nin;++j) {
     if(print_mode) printf("Analyzing input %d of %d\n",j,nin);
     for(i=1;i<=k;++i) dx->pm[i][j] = 0.01*x->pm[i][j] + tiny;
     set(xnew,add(x,dx));
     if(net_type==0) {set(ynew,run_bpn(xnew,nodes,tf,w));}
     else {set(ynew,run_rbfn(xnew,m,shape,w));}
     set(sv,divide_ebe(subtract(ynew,y0),mult(column(dx,j),ones(1,nout))));
     set(sv,mult_ebe(sv,sv));
     set(sv,sqroot(mean(sv)));
     for(i=1;i<=nout;++i) sm->pm[j][i] = sv->pm[1][i];
     for(i=1;i<=k;++i) dx->pm[i][j] = 0.0;
  }
  set(sm,divide_ebe(sm,mult(ones(nin,1),sum(sm))));  /*normalize*/
  odfp = fopen(outfile,"w");
  if(odfp == NULL) signal_block_error("NOL-RPC-OPEN-OUTPUT-FILE-ERROR\n");
  write_matrix(odfp,sm," ; sensitivity matrix");
  fclose(odfp);
  fm(nodes); fm(tf); fm(w); fm(y); fm(sm); fm(ynew);
  fm(x); fm(m); fm(shape); fm(xnew); fm(sv); fm(dx); fm(y0);
}


matrix *read_rbfn(idfp)
FILE *idfp;
{
  pointer_to_stack local_ptr = ans;
  int h,nout,unit_type,bias,version,nin;
  double p;
  matrix *m=NULL,*shape=NULL,*w=NULL,*nodes=NULL;
  matrix *read_line(),*read_matrix();
  fscanf(idfp,"%d",&version); /* version number */
  IGNORE_COMMENT(idfp);
  set(nodes,read_line(idfp,3));
  h = (int) nodes->pm[1][2];  /* hidden layer dimension */
  fscanf(idfp,"%le",&p); /* unit overlap */
  IGNORE_COMMENT(idfp);
  fscanf(idfp,"%d",&unit_type); /* 0=spherical, 1=elliptical */
  IGNORE_COMMENT(idfp);
  fscanf(idfp,"%d",&bias); /* 0=no bias, 1=include bias */
  IGNORE_COMMENT(idfp);
  nin = (int) nodes->pm[1][1];
  nout = (int) nodes->pm[1][3];
  set(m,read_matrix(idfp,h,nin));
  if(unit_type) {set(shape,read_matrix(idfp,h*nin,nin));}
  else {set(shape,read_matrix(idfp,h,1));}
  set(w,read_matrix(idfp,h+bias,nout));
  fm(nodes);
  matrix_return3(m,shape,w);
}



matrix *read_matrix(ifp,k,n)
FILE *ifp;
int k,n;
{
  pointer_to_stack local_ptr = ans;
  int i,j;
  matrix *x=NULL;
  set(x,newmat(k,n));
  for(i=1;i<=k;++i) {
    for(j=1;j<n;++j) fscanf(ifp,"%le,",&x->pm[i][j]);
    fscanf(ifp,"%le",&x->pm[i][n]);  /* last element in row, no following comma */
    IGNORE_COMMENT(ifp);
  }
  matrix_return(x);
}


matrix *read_ds(dsp)
FILE *dsp;
{
  /* Updated 4/4/93 to read DS on another path if Version = 0 */
  pointer_to_stack local_ptr = ans;
  matrix *x=NULL,*y=NULL;
  char dsfile[100];
  FILE *dsp2;
  char ch;
  int i,j,k,nin,nout,vers;

  fscanf(dsp,"%d",&vers); /* version number */
  if(vers != 1 && vers != 0) signal_block_error("NOL-BAD-FILE-FORMAT\n");
  IGNORE_COMMENT(dsp);
  if(vers==0) { /* separate file containing data set, a 10b2 feature  */
     fscanf(dsp,"%s",dsfile);
     dsp2 = fopen(dsfile,"r");
     if(dsp2 == NULL) signal_block_error("NOL-RPC-OPEN-INPUT-FILE-ERROR\n");
     set2(x,y,read_ds(dsp2));
     fclose(dsp2);
     matrix_return2(x,y);
  }
  fscanf(dsp,"%d",&k);
  IGNORE_COMMENT(dsp);
  fscanf(dsp,"%d",&nin);
  IGNORE_COMMENT(dsp);
  fscanf(dsp,"%d",&nout);
  IGNORE_COMMENT(dsp);
  set(x,newmat(k,nin));
  set(y,newmat(k,nout));
  for(i=1;i<=k;++i) {
    for(j=1;j<=3;++j) {  /* discard the first three commas */
       while((ch = getc(dsp)) != ',') { }
    }
    for(j=1;j<=nin;++j) fscanf(dsp,"%le,",&x->pm[i][j]);
    for(j=1;j<nout;++j) fscanf(dsp,"%le,",&y->pm[i][j]);
    fscanf(dsp,"%le",&y->pm[i][nout]);  /* last one, no following comma */
  }
  matrix_return2(x,y);
}


matrix *read_line(FILE *f, int n)
{
    pointer_to_stack local_ptr = ans;
    matrix *vec = NULL;
    int i;

    if (n < 1) {
        signal_block_error("NOL-BAD-FILE-FORMAT\n");
    }
    set(vec, newmat(1, n));
    for (i = 1; i <= n; ++i) {
        fscanf(f, "%le,", &vec->pm[1][i]);
    }
    IGNORE_COMMENT(f);
    matrix_return(vec);
}


void  write_vector(ofp,x,comment)
FILE *ofp;
matrix *x;
char *comment;
{
  int i,n;
  n = x->n;
  for(i=1;i<n;++i) fprintf(ofp,"%#g,",G2_LIMIT(x->pm[1][i]));
  fprintf(ofp,"%#g %s\n",G2_LIMIT(x->pm[1][n]),comment);
}

void  write_line_of_ints(ofp,x,comment)
FILE *ofp;
matrix *x;
char *comment;
{
  int i,n;
  n = x->n;
  for(i=1;i<n;++i) fprintf(ofp,"%d,",(int)x->pm[1][i]);
  fprintf(ofp,"%d %s\n",(int)x->pm[1][n],comment);
}

matrix *read_bpn(nnp)
FILE *nnp;
{
  pointer_to_stack local_ptr = ans;
  matrix *tf=NULL,*nodes=NULL,*w=NULL;
  matrix *read_line();
  int i,c,nw,layer,nlayer,init_flag=0;

  fscanf(nnp,"%d",&c); /* version number */
  IGNORE_COMMENT(nnp);
  fscanf(nnp,"%d",&nlayer);
  IGNORE_COMMENT(nnp);
  set(nodes,read_line(nnp,nlayer));
  set(tf,read_line(nnp,nlayer));
  nw = 0;
  for(layer=1;layer<nlayer;++layer)
    nw += ((int)nodes->pm[1][layer]+1)*((int)nodes->pm[1][layer+1]);
  set(w,newmat(1,nw));
  for(i=1;i<=nw;++i) {
     if(fscanf(nnp,"%le",&w->pm[1][i])!=1) {init_flag=1;break;}
     IGNORE_COMMENT(nnp);
  }
  if(init_flag) {fm(w); w=NULL;}
  matrix_return3(nodes,tf,w);
}



void write_bpn(nnp,nodes,tf,weights)
matrix *nodes,*tf,*weights;
FILE *nnp;
{
  pointer_to_stack local_ptr = ans;
  int i,j,layer,nlayer,nw;
  void write_line_of_ints();
  fprintf(nnp,"%d ; version number\n",1);
  nlayer = nodes->n;
  fprintf(nnp,"%d ; number of layers in bpn\n",nlayer);
  write_line_of_ints(nnp,nodes," ; layer sizes of bpn");
  write_line_of_ints(nnp,tf," ; transfer functions of bpn");
  nw = 0;
  for(layer=1;layer<nlayer;++layer) 
    for(i=1;i<=((int)nodes->pm[1][layer]+1);++i) 
       for(j=1;j<=((int)nodes->pm[1][layer+1]);++j) {
         ++nw;
         fprintf(nnp,"%#g ; %d %d %d\n",G2_LIMIT(weights->pm[1][nw]),i,j,layer);
  }
}


void bpn_trainer(char *infile, char *outfile)
{
  pointer_to_stack local_ptr = ans;
  matrix *x=NULL,*y=NULL,*cntrl=NULL,*tf=NULL,*nodes=NULL,*w=NULL,*y_pred=NULL;
  FILE *idfp,*odfp;
  void write_bpn();
  matrix *read_bpn(),*read_ds(),*read_line(),*nlpcr();
  int i;

  idfp = fopen(infile,"r");
  if(idfp == NULL) signal_block_error("NOL-RPC-OPEN-INPUT-FILE-ERROR\n");
  set2(x,y,read_ds(idfp));
  set(cntrl,read_line(idfp,4));
  set3(nodes,tf,w,read_bpn(idfp));
  fclose(idfp);
  if(cntrl->pm[1][4]==0.0) {  /* if cntrl(4) is zero then do not use pca analysis of x */
    set(cntrl,part(cntrl,1,1,1,3));
    set2(w,cntrl,make_bpn(x,y,nodes,tf,w,cntrl));
if(print_mode>2) {
  printf("Returned to bpn_trainer\n");
}  
    set(cntrl,append_lr(cntrl,zeros(1,2)));
  }
  else {  /* use pca analysis on x before training */
     set4(nodes,tf,w,cntrl,nlpcr(x,y,nodes,tf,w,cntrl));}
  odfp = fopen(outfile,"w");
  if(odfp == NULL) signal_block_error("NOL-RPC-OPEN-OUTPUT-FILE-ERROR\n");
  write_bpn(odfp,nodes,tf,w);
  for(i=1;i<6;++i) fprintf(odfp,"%d, ",(int)cntrl->pm[1][i]);
  fprintf(odfp,"%#g, ", G2_LIMIT(cntrl->pm[1][6]));
  fprintf(odfp,"%d, ", (int)cntrl->pm[1][7]);
  fprintf(odfp,"%#g ; cntrl vector\n", G2_LIMIT(cntrl->pm[1][8]));
  fclose(odfp);
  fm(nodes); fm(tf);fm(w);fm(x);fm(y);fm(y_pred);fm(cntrl);
}



void autoassociative_net(infile,outfile)
char *infile,*outfile;
/* variant based on one-at-a-time adjustment */
{
  pointer_to_stack local_ptr = ans;
  matrix *x=NULL,*nodes=NULL,*tf=NULL,*w=NULL,*y_temp=NULL,*y_pred=NULL;
  matrix *nsd=NULL,*adj=NULL,*fval=NULL,*bias=NULL;
  FILE *idfp,*odfp;
  matrix *read_bpn(),*read_line(),*run_aan();
  void write_vector();
  int i,nin;
  double f=0.0;
  idfp = fopen(infile,"r");
  if(idfp == NULL) signal_block_error("NOL-RPC-OPEN-INPUT-FILE-ERROR\n");
  set3(nodes,tf,w,read_bpn(idfp));
  nin = (int) nodes->pm[1][1];
  set(nsd,read_line(idfp,nin));
  IGNORE_COMMENT(idfp);  /*skip the line with run mode */
  set(x,read_line(idfp,nin));
  fclose(idfp);
  set(y_pred,run_bpn(x,nodes,tf,w));  /* normal case for base f */
  set(adj,subtract(y_pred,x));
  for(i=1;i<=nin;++i) {
    f -= LOGNORMAL(adj->pm[1][i],nsd->pm[1][i]);
  }
  if(print_mode) printf("For no fault, f = %g\n",f);
  for(i=1;i<=nin;++i) {  /* run once for each sensor */
    set3(y_temp,bias,fval,run_aan(i,x,nsd,nodes,tf,w));
    if(print_mode) printf("For sensor %d, f = %g, estimated bias = %f \n",i,fval->pm[1][1],bias->pm[1][1]);
    if(fval->pm[1][1] < f) {
         f = fval->pm[1][1];
	 set(y_pred,copy(y_temp));
       }
  }
  odfp = fopen(outfile,"w");
  if(odfp == NULL) signal_block_error("NOL-RPC-OPEN-OUTPUT-FILE-ERROR\n");
  write_vector(odfp,y_pred," ; Rectified values");
  fclose(odfp);
  fm(nodes); fm(tf); fm(w);fm(y_temp);fm(fval);fm(bias);
  fm(y_pred); fm(nsd);fm(adj);fm(x);
}


matrix *run_aan(isen,x,noise_sd,nodes,tf,w) 
matrix *x,*noise_sd,*nodes,*tf,*w;
int isen;
{
  pointer_to_stack local_ptr = ans;
  matrix *y_pred=NULL,*bias=NULL,*fval=NULL,*msen=NULL;
  matrix **opt_arg;
  double f_aan(),brent();
  void mnbrak();
  double ax,bx,cx,fa,fb,fc,fmin,xmin;
  int n;
  n = x->n;
  set(msen,i2m(isen));
  set(bias,zeros(1,1));
  set(fval,zeros(1,1));
  opt_arg = (matrix **) calloc(6,sizeof(pointer_to_matrix));
  opt_arg[0] = x;
  opt_arg[1] = noise_sd;
  opt_arg[2] = nodes;
  opt_arg[3] = tf;
  opt_arg[4] = w;
  opt_arg[5] = msen;
  ax = 0.0;
  bx = 0.1;
  mnbrak(&ax,&bx,&cx,&fa,&fb,&fc,f_aan,opt_arg);
if(print_mode>2) {
printf("Bracket is ax = %g, bx = %g, cx = %g, fa = %g, fb = %g, fc = %g\n",ax,bx,cx,fa,fb,fc);
}  
  fmin = brent(ax,bx,cx,fb,f_aan,1.e-2,&xmin,opt_arg);
  fval->pm[1][1] = fmin;
  bias->pm[1][1] = xmin;
  x->pm[1][isen] += xmin;
  set(y_pred,run_bpn(x,nodes,tf,w));
  x->pm[1][isen] -= xmin;
  fm(msen);free(opt_arg);
  matrix_return3(y_pred,bias,fval);
}


double f_aan(bias,opt_arg)
double bias;
matrix **opt_arg;
/* calculate the objective function given the current bias */
{
  pointer_to_stack local_ptr = ans;
  int i,n;
  double f=0.0;
  matrix *nsd,*nodes,*tf,*w,*x;
  matrix *adj=NULL,*y_pred=NULL;
/* unload info from opt_arg */
  x = opt_arg[0];
  nsd = opt_arg[1];
  nodes = opt_arg[2];
  tf = opt_arg[3];
  w = opt_arg[4];
  n = x->n;
  set(adj,zeros(1,n));
  adj->pm[1][m2i(opt_arg[5])] = bias;
  set(y_pred,run_bpn(add(x,adj),nodes,tf,w));
  set(adj,subtract(y_pred,add(x,adj)));  /* net in - out */
  for(i=1;i<=n;++i) {
    f -= LOGNORMAL(adj->pm[1][i],nsd->pm[1][i]);
  }
if(print_mode>2) {
printf("Bias = %f, Objective = %f\n",bias, f);
}
  fm(adj);fm(y_pred);
  return f;
}


void rbfn_trainer(infile,outfile)
char *infile,*outfile;
{
  pointer_to_stack local_ptr = ans;
  matrix *x=NULL,*y=NULL,*z=NULL,*m=NULL,*shape=NULL,*w=NULL,*y_pred=NULL,*nodes=NULL;
  FILE *idfp,*odfp;

  void write_rbfn();
  matrix *read_ds(),*read_line(),*make_rbfn();
  int version,unit_type,h,bias,classp;
  double f,p,f_rbfn();
  idfp = fopen(infile,"r");
  if(idfp == NULL) signal_block_error("NOL-RPC-OPEN-INPUT-FILE-ERROR\n");
  set2(x,y,read_ds(idfp));
  fscanf(idfp,"%d",&version); /* version number */
  IGNORE_COMMENT(idfp);
  set(nodes,read_line(idfp,3));
  h = (int) nodes->pm[1][2];  /* hidden layer dimension */
  fscanf(idfp,"%le",&p); /* unit overlap */
  IGNORE_COMMENT(idfp);
  fscanf(idfp,"%d",&unit_type); /* 0=spherical, 1=elliptical */
  IGNORE_COMMENT(idfp);
  fscanf(idfp,"%d",&bias); /* 0=no bias, 1=include bias */
  IGNORE_COMMENT(idfp);
  fscanf(idfp,"%d",&classp); /* indicates whether to do class-separate clustering */
  IGNORE_COMMENT(idfp);
  fclose(idfp);
  if(print_mode) printf("Training radial basis function network with specs:\nInputs = %d, Hidden = %d, Outputs = %d, Overlap = %f, Unit type = %d, Bias = %d\n", (int) nodes->pm[1][1],h,(int) nodes->pm[1][3],p,unit_type, bias);
  set3(m,shape,w, make_rbfn(x,y,h,p,unit_type,bias,classp));
  f = f_rbfn(x,m,shape,w,y);
  if(print_mode) printf("Final objective function value = %f\n",f);
  odfp = fopen(outfile,"w");
  if(odfp == NULL) signal_block_error("NOL-RPC-OPEN-OUTPUT-FILE-ERROR\n");
  write_rbfn(odfp,m,shape,w,p);
  fprintf(odfp,"%#g ; final objective value\n",G2_LIMIT(f));
  fclose(odfp);
  fm(m);fm(shape);fm(w);
  fm(x); fm(y);fm(y_pred); fm(nodes);
}


matrix *make_rbfn(x,y,h,p,unit_type,bias,classp)
matrix *x,*y;
int h,unit_type,bias,classp;
double p;  /* does not return optimal p */
{
  pointer_to_stack local_ptr = ans;
  matrix *m=NULL,*shape=NULL,*w=NULL,*a=NULL,*x_now=NULL,*munit=NULL,*mbias=NULL;
  matrix *cluster(),*ep_heur(),*p_heur(),*layer1(),*rbf_regr(),*class_i();
  matrix **opt_arg;
  void mnbrak();
  int i,nclass,ntrain,h_now,h_rem;
  double brent(),f_rbfn_p(),pa,pb,pc,fa,fb,fc,fmin;
  if(classp) { /* class separate clustering */
     if(print_mode) printf("Using class-separate clustering\n");
     h_rem = h;
     nclass = y->n;
     ntrain = x->m;
     for(i=1;i<=nclass;++i) {
        set(x_now,class_i(x,y,i));
	/* proportional distribution of centers, if possible */ 
        if(i!=nclass) {
           h_now = max(1,round((float)(h*x_now->m)/(float)ntrain));
           h_rem -= h_now; 
	   if(h_rem < nclass-i) {  /* in case too many centers are committed */
              h_now -= (nclass - i) - h_rem;
	      h_rem = nclass - i;  /* one center for each future class */
           }
        }
        else {
           h_now = h_rem;
           if(h_now<=0) signal_block_error("Bad magic number in make_rbfn"); /*ran out*/
        }
	if(print_mode) printf("Using %d units for class %d\n",h_now,i);
	if(x_now->m > 0) {
           set(m,append_ud(m,cluster(x_now,h_now)));
	}
     }
  }
  else {set(m,cluster(x,h));}  /* lumped clustering */
  if(p<=0.00000001) {  /* optimize p if p == 0.0 */
     if(print_mode) printf("Optimizing overlap paramter\n"); 
     pa = 1.0;
     pb = 2.0;
     set(munit,newmat(1,1));
     set(mbias,newmat(1,1));
     munit->pm[1][1] = (float) unit_type;
     mbias->pm[1][1] = (float) bias;
     opt_arg = (matrix **) calloc(5,sizeof(pointer_to_matrix));
     opt_arg[0] = m;
     opt_arg[1] = x;
     opt_arg[2] = y;
     opt_arg[3] = munit;
     opt_arg[4] = mbias;
     mnbrak(&pa,&pb,&pc,&fa,&fb,&fc,f_rbfn_p,opt_arg);
if(print_mode>2) {
printf("Bracket is pa = %g, pb = %g, pc = %g, fa = %g, fb = %g, fc = %g\n",pa,pb,pc,fa,fb,fc);
}     
     fmin = brent(pa,pb,pc,fb,f_rbfn_p,1.e-2,&p,opt_arg);
     if(print_mode) printf("\nOptimized overlap with p = %f\n",p);      
     free(opt_arg);
  }
  if(unit_type) {set(shape,ep_heur(m,p,x));}
  else {set(shape,p_heur(m,p,x));}
  set(a,layer1(m,shape,x));
  set(w,rbf_regr(x,m,shape,y,bias));
  if(w==NULL) signal_block_error("NOL-SINGULAR-REGRESSION\n");  
  fm(a);fm(x_now);fm(munit);fm(mbias);
  matrix_return3(m,shape,w);
}


matrix *cluster(x,h)
matrix *x;
int h;
{
  pointer_to_stack local_ptr = ans;
  matrix *b=NULL,*m=NULL,*dist=NULL,*ncluster=NULL,*mnew=NULL,*mdiff=NULL;
  matrix *selectn(),*dist2();
  double rel_change;
  int i,ntrain,nin;
  ntrain = x->m;
  nin = x->n;
  set(m,selectn(x,h));  /* select h rows of x to initialize m */
if(print_mode>2) {print_matrix(m,"In cluster, initial m = ");}    
  rel_change = 99.0;
  while(rel_change > 0.0001) {
    set(dist,dist2(x,m));
    if(h==1) {set(b,ones(1,ntrain));}
    else {set(b,not(subtract(dist,mult(ones(h,1),minimum(dist)))));}
    set(ncluster,sum(transpose(b)));
/*check for clusters with no points assigned and call recursively if necessary*/ 
    for(i=1; i<=h; ++i)
      if(ncluster->pm[1][i]==0.0) {
        set(m,cluster(x,h)); 
	rel_change = 0.0;
        break;
    }
    if(rel_change == 0.0) break; /* true only if call was made recursively thus finished */
    set(mnew,divide_ebe(mult(b,x),transpose(mult(ones(nin,1),ncluster))));
    set(mdiff,subtract(m,mnew));
/* Post version 1.1 -- TO DO:  the following will bomb if m = 0 */
    rel_change = m2d(divide_ebe(sum(sum(mult_ebe(mdiff,mdiff))),sum(sum(mult_ebe(m,m)))));
    fm(m);
    m = mnew;
    mnew = NULL; /*must point to nothing*/
if(print_mode>2) {print_matrix(m,"In cluster, now m = ");}    
  }
  fm(dist);fm(ncluster);fm(mdiff);fm(b);
  matrix_return(m);
}



matrix *class_i(x,y,class_index)
matrix *x,*y;
int class_index;
/*  Extract data for the class corresponding to class_index from data set */
{
  void signal_block_error();
  pointer_to_stack local_ptr = ans;
  matrix *ypart=NULL,*xpart=NULL,*dum=NULL,*index=NULL;
  int i;
if(print_mode>2) {
printf("In class_i, locating members of class %d\n",class_index);
}
  for(i=1;i<=y->m;++i) {
    set2(dum,index,maximum(row(y,i)));
    if(m2i(index) == class_index) {
      set(xpart,append_ud(xpart,row(x,i)));
      set(ypart,append_ud(ypart,row(y,i)));
    }
  }
  if(xpart==NULL){
	if(print_mode) printf("Can not find enough data for class %d\n",class_index);
	signal_block_error("NOL-NO-TRAINING-EXAMPLES\n");
   }

if(print_mode>2) {
printf("In class_i, found %d members of class %d\n",xpart->m,class_index);
}  
  fm(dum);fm(index);
  matrix_return2(xpart,ypart);
}


matrix *selectn(x,h)
matrix *x;
int h;
/* Select h different rows of x for initial cluster centers */
{
  pointer_to_stack local_ptr = ans;
  matrix *index=NULL,*m=NULL,*diff=NULL;
  matrix *shuffle(), *row(), *dist2();
  int i,j,ntrain,nin,ii,nassigned;
if(print_mode>3) {
unsigned seed;
printf("Enter seed\n");
scanf("%d",&seed); 
printf("seed = %u\n",seed);
srand(seed);
}
  ntrain = x->m;
  nin = x->n;
  if(h > ntrain) signal_block_error("NOL-TOO-MANY-HIDDEN-UNITS\n");
  set(m,newmat(h,nin));
  set(index,shuffle(ntrain));
  i = 1;
  ii = (int) index->pm[1][1];
  for(j=1;j<=nin;++j)  m->pm[1][j] = x->pm[ii][j]; /* assign first center */
  nassigned = 1;
  while(nassigned < h && i < ntrain) {
    ++i;
    ii = (int) index->pm[1][i];
/* make sure not a repeated point by looking at distance from already-selected centers*/
    set(diff,minimum(dist2(part(m,1,1,nassigned,m->n),row(x,ii))));
    if(diff->pm[1][1] > 0.0) {
      ++nassigned;
      for(j=1;j<=nin;++j)  m->pm[nassigned][j] = x->pm[ii][j]; /* assign center */
    }
  }
  if(nassigned < h) signal_block_error("NOL-TOO-MANY-HIDDEN-UNITS\n");
  fm(index);fm(diff);
  matrix_return(m);
}


matrix *shuffle(n)
int n;
{
  pointer_to_stack local_ptr = ans;
  matrix *a=NULL;
  int i,ir1,ir2;
  double r1,r2,temp;
  set(a,newmat(1,n));
  for(i=1;i<=n;++i) a->pm[1][i] = (double) i;
/* 2n random swaps */  
  for(i=1;i<=2*n;++i) {
    r1 = (((double) rand())/((double) RAND_MAX)); /* 0.0 to 1.0 */  
    ir1 = (int) (floor(n*r1) + 1.0); /* 0 to n */
    r2 = (((double) rand())/((double) RAND_MAX)); /* 0.0 to 1.0 */  
    ir2 = (int) (floor(n*r2) + 1.0); /* 0 to n */
    temp = a->pm[1][ir1];
    a->pm[1][ir1] = a->pm[1][ir2];
    a->pm[1][ir2] = temp;
  }
 matrix_return(a);
}


matrix *dist2(x1,x2)
matrix *x1,*x2;
{
  pointer_to_stack local_ptr = ans;
  matrix *sqdist=NULL,*diff=NULL;
  int i,n1,n2,nx;
  n1 = x1->m;
  nx = x1->n;
  n2 = x2->m;
  for(i=1;i<=n2;++i) {
    set(diff,subtract(x1,mult(ones(n1,1),row(x2,i))));
    if(nx==1) {set(sqdist,append_ud(sqdist,transpose(mult_ebe(diff,diff))));}
    else {set(sqdist,append_ud(sqdist,sum(transpose(mult_ebe(diff,diff)))));}
  }
  fm(diff);
  matrix_return(sqdist);
}


matrix *p_heur(m,p,x)  /* here p is any positive double */
matrix *m,*x;
double p;
{
  pointer_to_stack local_ptr = ans;
  matrix *sigma=NULL,*dist=NULL;
  int i,h,nin;
  h = m->m;
  nin = m->n;
  if(h==1) {  /* special case of only one center */
    set(sigma,scalar_mult(p,mean(sqroot(diag(cov(x))))));
  } 
  else {
     set(dist,dist2(m,m));  /* all the center-to-center squared distances */
     for(i=1;i<=h;++i) dist->pm[i][i] = DBL_MAX;  /* put large number on diagonal */
     set(sigma,scalar_mult(p,transpose(sqroot(minimum(dist)))));
  }   
  fm(dist);
if(print_mode>2) {
print_matrix(sigma, "In p_heur, returning sigma = ");
}  
  matrix_return(sigma);
}

matrix *ep_heur(m,p,x)
matrix *m,*x;
double p;
{
  pointer_to_stack local_ptr = ans;
  matrix *a=NULL,*shape=NULL,*shape_i=NULL,*sigma=NULL,*sqdist=NULL;
  matrix *p_heur(),*layer1(),*wtcov(),*mahal2();
  int i,h,nin,ntrain;
  double sigmasq;
  h = m->m;
  nin = m->n;
  ntrain = x->m;
  set(sigma,p_heur(m,p,x));
  set(a,layer1(m,sigma,x));
  if(h==1) {  /* special case of only one center */
     set(shape,scalar_divide(p*p,inverse(cov(x))));
  } 
  else {
    for(i=1;i<=h;++i) {
      set(shape_i,inverse(wtcov(column(a,i),x)));
      if(shape_i==NULL) signal_block_error("NOL-SINGULAR-EBF\n");
      set(sqdist,mahal2(mult(ones(h,1),row(m,i)),m,shape_i)); /* dist from mh to all other m's */
      sqdist->pm[1][i] = DBL_MAX;
      sigmasq = p*p*m2d(minimum(sqdist));
      set(shape_i,scalar_divide(sigmasq,shape_i));
      set(shape,append_ud(shape,shape_i));
    }
  }
  fm(shape_i);fm(sqdist);fm(sigma);fm(a);
  matrix_return(shape);
}

matrix *layer1(m,shape,x)
matrix *m,*shape,*x;
{
  pointer_to_stack local_ptr = ans;
  matrix *invcov_i=NULL,*ah=NULL,*sqdist=NULL;
  matrix *mahal2(),*dist2(),*negexp();
  int i,k,nin,h,hx,start,finish;
  k = x->m;
  nin = x->n;
  h = m->m;
  hx = shape->m;
  if(hx==h) {
    set(sqdist,dist2(x,m));
    set(ah,negexp(transpose(divide_ebe(sqdist,mult(mult_ebe(shape,shape),ones(1,k))))));
  }
  else if(hx==h*nin) {
    for(i=1;i<=h;++i) {
      start = (i-1)*nin+1;
      finish = start+nin-1;
      set(invcov_i,part(shape,start,1,finish,shape->n));
      set(sqdist,mahal2(mult(ones(k,1),row(m,i)),x,invcov_i));
      set(ah,append_lr(ah,negexp(transpose(sqdist))));
    }
  }
  else signal_block_error("Shape is incorrectly specified in layer1\n");
  fm(sqdist);fm(invcov_i);
  matrix_return(ah);  
}


matrix *negexp(a)
matrix *a;
/* returns the negative exponential, element by element */
{
  pointer_to_stack local_ptr = ans;
  matrix *c=NULL;
  int i,j;
  set(c,newmat(a->m,a->n));
  for(i=1;i<=a->m;++i)
      for(j=1;j<=a->n;++j)
	c->pm[i][j] = exp(- a->pm[i][j]);
  matrix_return(c);
}


matrix *mahal2(x1,x2,shape)
matrix *x1,*x2,*shape;
{
  pointer_to_stack local_ptr = ans;
  matrix *sqdist=NULL,*diff=NULL;
  int i,k,nin;
  k = x1->m;
  nin = x1->n;
  set(sqdist,newmat(1,k));
  for (i=1;i<=k;++i) {
    set(diff,subtract(row(x1,i),row(x2,i)));
    sqdist->pm[1][i] = m2d(mult(mult(diff,shape),transpose(diff)));
  }
  fm(diff);
  matrix_return(sqdist);
}     


matrix *wtcov(wt,x)
matrix *wt,*x;
{
  pointer_to_stack local_ptr = ans;
  matrix *wcov=NULL,*wm=NULL, *wx=NULL;
  int k,n;
  double denom;
  k = x->m;
  n = x->n;
  denom = m2d(sum(wt));
  set(wm,scalar_divide(denom,mult(transpose(wt),x)));
  set(wx,subtract(x,mult(ones(k,1),wm)));
  set(wcov,mult(transpose(wx),mult_ebe(mult(wt,ones(1,n)),wx)));
  fm(wm); fm(wx);
  matrix_return(wcov);
}


matrix *rbf_regr(x,m,shape,y,bias)
matrix *x,*m,*shape,*y;
int bias;
/* Regression of 2nd layer weights, including bias if bias = 1.
   Returns w == NULL if regression is singular  */
{
  pointer_to_stack local_ptr = ans;
  matrix *w=NULL,*a=NULL;
  matrix *layer1();
  int ntrain,h,nin;
  ntrain = x->m;
  nin = x->n;
  h = m->m;
  set(a,layer1(m,shape,x));
  if(bias) {set(a,append_lr(a,ones(ntrain,1)));}
  set(w,least_squares(a,y));
  fm(a);
  matrix_return(w);
}


matrix *run_rbfn(x,m,shape,w)
matrix *x,*m,*shape,*w;
{
  pointer_to_stack local_ptr = ans;
  matrix *a=NULL,*y_pred=NULL;
  matrix *layer1();
  int k,hp,nout,h,nin;
  k = x->m;
  nin = x->n;
  h = m->m;
  hp = w->m;
  nout = w->n;
  set(a,layer1(m,shape,x));
  if(hp==h+1) {set(a,append_lr(a,ones(k,1)));}
  set(y_pred,mult(a,w));  
  fm(a);
  matrix_return(y_pred);
}


double f_rbfn(x,m,shape,w,y)
matrix *x,*m,*shape,*w,*y;
/* Objective function value for rbfn */
{
  pointer_to_stack local_ptr = ans;
  matrix *y_pred=NULL,*f=NULL;
  matrix *run_rbfn();
  double sf;
  set(y_pred,run_rbfn(x,m,shape,w));
  set(f,subtract(y,y_pred));
  set(f,mult_ebe(f,f));
  set(f,sum(sum(f)));
  sf = f->pm[1][1];
  fm(y_pred);
  fm(f);
  return sf;
}


double f_rbfn_p(p,opt_arg)
double p;
matrix **opt_arg;
/* Objective function value for rbfn given p.  On input, p may be infeasible
   (negative-valued or leading to singular weights).  If p is infeasible, we return
   a large number for the function value */
{
  pointer_to_stack local_ptr = ans;
  matrix *x,*m,*y;
  matrix *y_pred=NULL,*f=NULL,*shape=NULL,*w=NULL,*a=NULL;
  matrix *run_rbfn(),*ep_heur(),*p_heur(),*layer1(),*rbf_regr(),*run_rbfn(),*perturb();
  int unit_type,bias;
  double sf;
  if(p <= 0.1) return 0.001*DBL_MAX;
  m = opt_arg[0];
  x = opt_arg[1];
  y = opt_arg[2];
  unit_type = m2i(opt_arg[3]);
  bias = m2i(opt_arg[4]);
  if(unit_type) {set(shape,ep_heur(m,p,x));}
  else {set(shape,p_heur(m,p,x));}
  set(a,layer1(m,shape,x));
  set(w,rbf_regr(x,m,shape,y,bias));
  if(w==NULL) return 0.001*DBL_MAX;
/* assure robustness to small variation of w */
  set(w,perturb(w)); 
  set(y_pred,run_rbfn(x,m,shape,w));
  set(f,subtract(y,y_pred));
  set(f,mult_ebe(f,f));
  set(f,sum(sum(f)));
  sf = f->pm[1][1];
  if(print_mode) printf("  Trying p = %f, objective = %f\n",p,sf);
  fm(y_pred);fm(f);fm(shape);fm(w);fm(a);
  return sf;
}


matrix *perturb(a)
matrix *a;
{
  pointer_to_stack local_ptr = ans;
  matrix *b=NULL;
  int i,j,m,n;
  double fact=0.001;
  m = a->m;
  n = a->n;
  set(b,newmat(m,n));
  for(i=1;i<=m;++i)
    for(j=1;j<=n;++j) {
       b->pm[i][j] = a->pm[i][j]*(1.0+fact);
       fact= -fact;
     }
  matrix_return(b);
}


void write_rbfn(nnp,m,shape,w,p)
matrix *m,*shape,*w;
double p;
FILE *nnp;
{
  pointer_to_stack local_ptr = ans;
  int nin,nout,h,bias,unit_type,hp,hx;
  matrix *nodes=NULL;
  void write_matrix();
if(print_mode>2) {
printf("In write_rbfn \n");
}
  nin = m->n;
  h = m->m;
  hp = w->m;
  nout = w->n;
  bias = (h==hp) ? 0: 1; 
  hx = shape->m;
  unit_type = (hx==h) ? 0: 1; 
  set(nodes,newmat(1,3));
  nodes->pm[1][1] = (double) nin;
  nodes->pm[1][2] = (double) h;
  nodes->pm[1][3] = (double) nout;
  fprintf(nnp,"%d ; version number\n",1);
  write_line_of_ints(nnp,nodes," ; layer sizes of rbfn");
  fprintf(nnp,"%#g ; Unit overlap\n",G2_LIMIT(p));
  fprintf(nnp,"%d ; Unit type (0 = spherical, 1 = elliptical)\n",unit_type);
  fprintf(nnp,"%d ; Bias (0 = omitted, 1 = included)\n",bias);
  write_matrix(nnp,m," ; unit centers");
  write_matrix(nnp,shape," ; unit shapes");
  write_matrix(nnp,w," ; second layer weights");
  fm(nodes);
}


void write_matrix(ofp,x,comment)
matrix *x;
FILE *ofp;
char *comment;
{
  pointer_to_stack local_ptr = ans;
  int i,j,m,n;
  char ext_comment[100];
  m = x->m;
  n = x->n;
  for(i=1;i<=m;++i) {
     sprintf(ext_comment,"%s row %d",comment,i);
     for(j=1;j<n;++j) fprintf(ofp,"%#g,",G2_LIMIT(x->pm[i][j]));
     fprintf(ofp,"%#g %s\n",G2_LIMIT(x->pm[i][n]),comment);
  }
}


void rho_trainer(infile,outfile)
char *infile,*outfile;
{
  pointer_to_stack local_ptr = ans;
  matrix *x=NULL,*y=NULL,*m=NULL,*shape=NULL,*w=NULL,*nodes=NULL;
  FILE *idfp,*odfp;
  void write_rbfn();
  matrix *read_ds(),*read_line(),*make_rho();
  int version,unit_type,h,bias,classp;
  double f,p,f_rho();
  idfp = fopen(infile,"r");
  if(idfp == NULL) signal_block_error("NOL-RPC-OPEN-INPUT-FILE-ERROR\n");
  set2(x,y,read_ds(idfp));
  fscanf(idfp,"%d",&version); /* version number */
  IGNORE_COMMENT(idfp);
  set(nodes,read_line(idfp,3));
  h = (int) nodes->pm[1][2];  /* hidden layer dimension */
  fscanf(idfp,"%le",&p); /* unit overlap */
  IGNORE_COMMENT(idfp);
  fscanf(idfp,"%d",&unit_type); /* 0=spherical, 1=elliptical */
  IGNORE_COMMENT(idfp);
  fscanf(idfp,"%d",&bias); /* 0=no bias, 1=include bias */
  IGNORE_COMMENT(idfp);
  fscanf(idfp,"%d",&classp); /* indicates whether to do class-separate clustering */
  IGNORE_COMMENT(idfp);
  fclose(idfp);
  if(print_mode) printf("Training rho net with specs:\nInputs = %d, Hidden = %d, Outputs = %d, Overlap = %f, Unit type = %d, Bias = %d\n", (int) nodes->pm[1][1],h,(int) nodes->pm[1][3],p,unit_type, bias);
  set3(m,shape,w, make_rho(x,y,nodes,h,p,unit_type,bias,classp));
  f = f_rho(x,m,shape,w);
  if(print_mode) printf("Final objective function value = %f\n",f);
  odfp = fopen(outfile,"w");
  if(odfp == NULL) signal_block_error("NOL-RPC-OPEN-OUTPUT-FILE-ERROR\n");
  write_rbfn(odfp,m,shape,w,p);
  fprintf(odfp,"%#g ; final value of log prob\n", G2_LIMIT(f));
  fclose(odfp);
  fm(m);fm(shape);fm(w);
  fm(x); fm(y); fm(nodes);
}


matrix *make_rho(x,y,nodes,h,p,unit_type,bias,classp)
matrix *x,*y,*nodes;
int h,unit_type,bias,classp;
double p;
{
  pointer_to_stack local_ptr = ans;
  matrix *m=NULL,*shape=NULL,*w=NULL,*munit=NULL;
  matrix *cluster(),*ep_heur(),*p_heur(),*rho_weights(),*class_i();
  matrix *m_now=NULL,*shape_now=NULL,*w_now=NULL,*x_now=NULL,*dummy=NULL;
  matrix **opt_arg;
  void mnbrak();
  double pa,pb,pc,fa,fb,fc,fmin,brent(),f_rho_p();
  int i,j,h_now,h_rem,nclass,ntrain;
  if(classp) {  /* essentially separate rho nets for each class, in one net */
     if(print_mode) printf("Using class-separate clustering\n");
     h_rem = h;
     nclass = nodes->pm[1][3];
     ntrain = x->m;
     set(w,zeros(h,nclass));
     for(i=1;i<=nclass;++i) {
        set(x_now,class_i(x,y,i));
/*  The following test should be refined.  Error if x_now = 1 w/spherical */
	if (x_now->m == 1) signal_block_error("NOL-NO-TRAINING-EXAMPLES\n");
        if(i!=nclass) { 
           h_now = max(1,round((float)(h*x_now->m)/(float)ntrain));
           h_rem -= h_now;
	   if(h_rem < nclass-i) {  /* in case too many centers are committed */
              h_now -= (nclass - i) - h_rem;
	      h_rem = nclass - i;  /* one center for each future class */
	    }
	 }
        else {
           h_now = h_rem; h_rem = 0;
           if(h_now==0) signal_block_error("Bad magic number in make_rho"); /*ran out of units*/
        }
        if(print_mode) printf("Using %d units for class %d\n",h_now,i);
        set3(m_now,shape_now,w_now,make_rho(x_now,dummy,nodes,h_now,p,unit_type,bias,0));
	set(m,append_ud(m,m_now));
	set(shape,append_ud(shape,shape_now));
        for(j=1;j<=h_now;++j) w->pm[h-h_rem-h_now+j][i] = w_now->pm[j][1]; 
     }
     fm(m_now);fm(shape_now);fm(w_now);fm(x_now);
  }
  else {
    if(print_mode) printf("Using regular clustering\n");
    set(m,cluster(x,h)); 
    if(print_mode) printf("Clustering succeeded\n");
    if(p<=0.00000001) {  /* optimize p */
       if(print_mode) printf("Optimizing unit overlap\n");
       pa = 1.0; pb = 2.0;
       set(munit,newmat(1,1));
       munit->pm[1][1] = (float) unit_type;
       opt_arg = (matrix **) calloc(3,sizeof(pointer_to_matrix));
       opt_arg[0] = m;
       opt_arg[1] = x;
       opt_arg[2] = munit;
       mnbrak(&pa,&pb,&pc,&fa,&fb,&fc,f_rho_p,opt_arg);
if(print_mode>2) {       
printf("Make_rho: bracket is pa = %f, pb = %f, pc = %f, fa = %f, fb = %f, fc = %f\n",pa,pb,pc,fa,fb,fc);
}
       fmin = brent(pa,pb,pc,fb,f_rho_p,1.e-3,&p,opt_arg);
       if(print_mode) printf("\nOptimized overlap for rho net, p = %f\n",p);      
       free(opt_arg);
    }
    if(unit_type) {set(shape,ep_heur(m,p,x));}
    else {set(shape,p_heur(m,p,x));}
    set(w,rho_weights(x,m,shape));
  }
  fm(munit);
  matrix_return3(m,shape,w);
}


double f_rho_p(p,opt_arg)
double p;
matrix **opt_arg;
/* Objective function value for rho net given p */
{
  pointer_to_stack local_ptr = ans;
  matrix *x,*m;
  matrix *rho=NULL,*shape=NULL,*w=NULL,*a=NULL;
  matrix *run_rbfn(),*ep_heur(),*p_heur(),*layer1(),*rho_weights(),*perturb();
  int unit_type;
  double f,log_product();
if(print_mode>1) {
printf("f_rbfn_p called with p = %f\n",p);
} 
  if(p <= 0.1) return 0.001*DBL_MAX;
  /*****!!!!!!!!***
  if(p<0.1) p = 0.1;*/
  m = opt_arg[0];
  x = opt_arg[1];
  unit_type = m2i(opt_arg[2]);
  if(unit_type) {set(shape,ep_heur(m,p,x));}
  else {set(shape,p_heur(m,p,x));}
  set(a,layer1(m,shape,x));
  set(w,rho_weights(x,m,shape));
  set(rho,run_rbfn(x,m,shape,w));
  f = -log_product(rho);
  if(print_mode) printf("  Trying p = %f, objective = %f\n",p,f);
  fm(rho);fm(shape);fm(w);fm(a);
  return f;
}


matrix *rho_weights(x,m,shape)
matrix *x,*m,*shape;
{
  pointer_to_stack local_ptr = ans;
  matrix *wvec=NULL,*nh=NULL,*invcov_i=NULL;
  double ntotal,pi_2_nin,vol,determinant;
  int h,k,i,hx,nin,finish,start;
  k = x->m;
  nin = x->n;
  h = m->m;
  hx = shape->m;
  set(wvec,newmat(h,1));
  set(nh,sum(layer1(m,shape,x)));
if(print_mode>2) {
print_matrix(nh,"In rho_weights, nh ");
}
  ntotal = m2d(sum(nh));
  pi_2_nin = sqrt(pow(PI,(double) nin));
  if(hx==h) { /* spherical units */
    for(i=1;i<=h;++i) {
       vol = pow(sqrt(PI)*shape->pm[i][1],(double) nin);
       wvec->pm[i][1] = nh->pm[1][i]/(ntotal*vol);
if(print_mode>2) {
printf("For spherical unit %d, vol = %g, weight = %g\n",i,vol,wvec->pm[i][1]);
}
     }
  }
  else if(hx==h*nin) {  /* elliptical units */
    for(i=1;i<=h;++i) {
      start = (i-1)*nin+1;
      finish = start+nin-1;
      set(invcov_i,part(shape,start,1,finish,shape->n));
      determinant = det(invcov_i);
      if(determinant <= 0.0) signal_block_error("NOL-SINGULAR-EBF\n");
      vol = pi_2_nin/sqrt(determinant);
      wvec->pm[i][1] = nh->pm[1][i]/(ntotal*vol);
if(print_mode>2) {
printf("For elliptical units %d, vol = %g, weight = %g\n",i,vol,wvec->pm[i][1]);
}
    }
  }
  fm(nh); fm(invcov_i);
  matrix_return(wvec);
}


double f_rho(x,m,shape,w)
matrix *x,*m,*shape,*w;
{
  pointer_to_stack local_ptr = ans;
  matrix *rho=NULL;
  matrix *run_rbfn();
  double p,log_product();
  set(rho,run_rbfn(x,m,shape,w));
  p = log_product(rho);
  fm(rho); 
  return p;
}


double log_product(x)
matrix *x;
{
  double y=0.0;
  int i,j;
  for(i=1;i<=x->m;++i)
    for(j=1;j<=x->n;++j) y += log10(max(DBL_MIN,x->pm[i][j]));
  return y;
}


matrix *nlpcr(x,y,nodes0,tf0,w0,cntrl0)
matrix *x,*y,*nodes0,*tf0,*w0,*cntrl0;
{
  pointer_to_stack local_ptr = ans;
  int k,nin,nf,nlayer;
  double stop_crit;
  matrix *t=NULL,*p=NULL,*e=NULL,*var_exp=NULL,*w=NULL,*w1=NULL,*w2=NULL,*w3=NULL,*w4=NULL;
  matrix *cntrl=NULL,*nodes=NULL,*tf=NULL,*taug=NULL,*xaug=NULL,*q=NULL,*pt=NULL,*c=NULL;
  matrix *pack_bpn(),*pca();
  nin = x->n;
  nlayer = nodes0->n;
  set(nodes,copy(nodes0));
  set(tf,copy(tf0));
  stop_crit = cntrl0->pm[1][4]; 
  set4(t,p,e,var_exp,pca(x,stop_crit));
  k = t->m;
  nf = t->n;
  printf("\nINPUT PROJECTION:\n    Input dimension reduced from %d to %d dimensions.\n\n", x->n, t->n);
  nodes->pm[1][1] = (double) nf;
  set(cntrl,part(cntrl0,1,1,1,3));
  if(w0==NULL || fabs(m2d(mean(w0)))<DBL_EPSILON) {set2(w,cntrl,make_bpn(t,y,nodes,tf,w0,cntrl));}
  else {
     set4(w1,w2,w3,w4,wt_mat(w0,nodes0));
     set(xaug,append_lr(x,ones(x->m,1)));
     set(taug,append_lr(t,ones(t->m,1)));
     set(w1,least_squares(taug,mult(xaug,w1)));
     if(w1==NULL) signal_block_error("NOL-PCA-FAILURE\n"); 
     set2(w,nodes,wt_vec(w1,w2,w3,w4));
     set2(w,cntrl,make_bpn(t,y,nodes,tf,w,cntrl));
   }
  set(cntrl,append_lr(cntrl,i2m(nf)));
  set(cntrl,append_lr(cntrl,var_exp));
  set4(w1,w2,w3,w4,wt_mat(w,nodes));
  set(pt,transpose(p));
  set(q,append_lr(pt,zeros(pt->m,1)));
  set(c,append_lr(mult(chsign(mean(x)),pt),ones(1,1)));
  set(q,append_ud(q,c));
  set(w1,mult(q,w1));
  set2(w,nodes,wt_vec(w1,w2,w3,w4));
  fm(t);fm(p);fm(e);fm(var_exp);fm(w1);fm(w2);fm(w3);fm(w4);fm(xaug);fm(taug);
  fm(q);fm(pt);fm(c);
  matrix_return4(nodes,tf,w,cntrl);
}

  
  
matrix *pca(x0,stop_crit)
matrix *x0;
double stop_crit;
{
  pointer_to_stack local_ptr = ans;
  matrix *x=NULL,*t=NULL,*p=NULL,*tvec=NULL,*pvec=NULL,*err=NULL;
  matrix *tvecp=NULL,*e=NULL,*var_exp=NULL;
  int iter,i,k,nin,nf;
  double tol,scalar_err,var_ex,enorm,xnorm;
  k = x0->m;
  nin = x0->n;
  set(x,subtract(x0,mult(ones(k,1),mean(x0))));
  xnorm = ssq(x);
  if(stop_crit < 1.0) {nf=nin; tol = stop_crit;}
  else {nf = min(nin,(int) stop_crit); tol = -0.1;}
  for(i=1;i<=nf;++i) {
     iter = 0;
     set(tvec,part(x,1,1,k,1));  
     scalar_err = 999.0;
     while(iter < 100 && scalar_err > k*1.e-9) {
	 ++iter;
         set(pvec,mult(transpose(tvec),x));
	 set(pvec,scalar_divide(vnorm(pvec),pvec));
	 set(tvecp,mult(x,transpose(pvec)));
         set(err,subtract(tvec,tvecp));
         scalar_err = vnorm(err);
         set(tvec,copy(tvecp));
     }
     set(p,append_ud(p,pvec));
     set(t,append_lr(t,tvecp));
     set(e,subtract(x,mult(tvecp,pvec)));
     enorm = ssq(e);
     var_ex = 1.0 - enorm/xnorm;
     if(var_ex >= 1.0 - tol) break;
     set(x,copy(e)); 
    }
  fm(x);fm(tvec);fm(pvec);fm(err);fm(tvecp);
  set(var_exp,d2m(var_ex));
  matrix_return4(t,p,e,var_exp);
}


/* packing bpn, not tested

matrix *pack_bpn(addin,multin,nodes0,tf0,weights0,addout,multout)
matrix *addin,*multin,*nodes0,*tf0,*weights0,*addout,*multout;     
{
  pointer_to_stack local_ptr = ans;
  int i,nl,packin,packout,a,b,n,nl0,start=1;
  matrix *bias=NULL,*nodes=NULL,*tf=NULL,*weights=NULL;
  matrix **w;
  set(nodes,copy(nodes0));
  set(tf,copy(tf0));
  nl = nodes->n; nl0=nl;
  if(addin != NULL) packin = 1; else packin = 0; 
  if(addout != NULL) packout = 1; else packout = 0;
  w = (matrix **) calloc(6,sizeof(pointer_to_matrix));
  if(nl==2)     {set(w[1],wt_mat(weights0,nodes));}
  else if(nl==3) {set2(w[1],w[2],wt_mat(weights0,nodes));}
  else if(nl==4) {set3(w[1],w[2],w[3],wt_mat(weights0,nodes));}
  else if(nl==5) {set4(w[1],w[2],w[3],w[4],wt_mat(weights0,nodes));}
  if(packin) {
     a = multin->n; start = 0;
     set(w[0],diag(multin));
     set(bias,mult_ebe(addin,multin));
     set(w[0],append_ud(w[0],bias));
     set(nodes,append_lr(i2m(a),nodes));
     set(tf,append_lr(zeros(1,1),tf));
  }   
  if(packout) {
     a = multout->n;
     set(w[nl],diag(divide_ebe(ones(1,a),multout)));
     set(w[nl],append_ud(w[nl],chsign(addout)));
     set(nodes,append_lr(nodes,i2m(a)));
     set(tf,append_lr(tf,zeros(1,1)));
  }
  nl = nodes->n;
  for(n=start+1;n<=nl;++n) {
     if(tf->pm[1][n]==0.0) {
        a = w[n-1]->m; b = w[n-1]->n; 
        set(w[n-1],append_lr(w[n-1],zeros(a,1)));
	w[n-1]->pm[a][b+1] = 1.0;
	set(w[n-1],mult(w[n-1],w[n]));
	set(nodes,remove_col(nodes,n));
	set(tf,remove_col(tf,n));
	for(i=n;i<nl;++i) w[i]=w[i+1];
	w[nl]=NULL; --nl;
      }
  }
  set(weights,wt_vec(w[start],w[start+1],w[start+2],w[start+3]));
  for(i=0;i<=nl0;++i) {fm(w[i]);}
  free(w); fm(bias);
  matrix_return3(nodes,tf,weights);
}

*/



void optimizer(infile,outfile)
char *infile,*outfile;
{
  pointer_to_stack local_ptr = ans;
  matrix *xin=NULL,*xqw=NULL,*xlb=NULL,*xub=NULL,*yin=NULL,*yqw=NULL,*ylw=NULL;
  matrix *nodes=NULL,*tf=NULL,*w=NULL,*m=NULL,*shape=NULL,*x=NULL,*cntrl=NULL,*dummy=NULL;
  FILE *idfp,*odfp;
  void write_vector();
  matrix *read_bpn(),*read_rbfn(),*read_line(),*train();
  matrix **opt_arg;
  int nx,ny,net_type;
  double fopt_bpn(),fopt_rbfn();
if(print_mode>2) {
printf("Entering optimizer\n");
}
  idfp = fopen(infile,"r");
  if(idfp == NULL) signal_block_error("NOL-RPC-OPEN-INPUT-FILE-ERROR\n");
  fscanf(idfp,"%d",&nx); /* x dimension */
if(print_mode>2) {
printf("At 0, nx = %d\n",nx);
}
  IGNORE_COMMENT(idfp);
  fscanf(idfp,"%d",&ny); /* y dimension */
  IGNORE_COMMENT(idfp);
  set(xin,read_line(idfp,nx));
  set(xqw,read_line(idfp,nx));
  set(xlb,read_line(idfp,nx));
  set(xub,read_line(idfp,nx));
  set(yin,read_line(idfp,ny));
  set(yqw,read_line(idfp,ny));
  set(ylw,read_line(idfp,ny));
  fscanf(idfp,"%d",&net_type); /* 0=bpn, 1=rbfn */
  IGNORE_COMMENT(idfp);
if(print_mode>2) {
printf("At 2, net_type = %d\n",net_type);
}
  if(net_type==0) {set3(nodes,tf,w,read_bpn(idfp));}
    else if(net_type==1) {set3(m,shape,w,read_rbfn(idfp));}
    else signal_block_error("NOL-OPERAND-BLOCK-UNKNOWN\n");
  fclose(idfp);
/* now do it */
  set(x,mat_random(1,nx,-0.1,0.1));  /* random initial guess between -0.1 and 0.1 */
  set(cntrl,zeros(1,3));
  cntrl->pm[1][1] = nx*100.0; /* max iters */

  cntrl->pm[1][3] = 4.0; /* training method */
  opt_arg = (matrix **) calloc(10,sizeof(pointer_to_matrix));
  opt_arg[0] = xin;
  opt_arg[1] = xqw;
  opt_arg[2] = xlb;
  opt_arg[3] = xub;
  opt_arg[4] = yin;
  opt_arg[5] = yqw;
  opt_arg[6] = ylw;
  if(net_type==0) {
     opt_arg[7] = nodes;
     opt_arg[8] = tf;
     opt_arg[9] = w;
     set2(x,cntrl,train(x,fopt_bpn,dummy,cntrl,opt_arg));
  }
  else if(net_type==1) {
     opt_arg[7] = m;
     opt_arg[8] = shape;
     opt_arg[9] = w;
     set2(x,cntrl,train(x,fopt_rbfn,dummy,cntrl,opt_arg));
  }
  set(x,add(mult_ebe(subtract(xub,xlb),scalar_mult(0.5,sigmoid0(x))),mean(append_ud(xub,xlb))));
  free(opt_arg);
  odfp = fopen(outfile,"w");
  if(odfp == NULL) signal_block_error("NOL-RPC-OPEN-OUTPUT-FILE-ERROR\n");
  write_vector(odfp,x,"; Solution vector");
  write_vector(odfp,cntrl,"; Control vector");
  fclose(odfp);
  fm(nodes); fm(tf);fm(w);fm(shape);fm(m);fm(cntrl);fm(x);
  fm(xin);fm(xqw);fm(xlb);fm(xub);fm(yin);fm(yqw);fm(ylw);
}


double fopt_bpn(xopt,opt_arg)
matrix *xopt;
matrix **opt_arg;
{
  pointer_to_stack local_ptr = ans;
  matrix *x=NULL,*y_pred=NULL;
  matrix *xin,*xqw,*xlb,*xub,*yin,*yqw,*ylw,*nodes,*tf,*w;
  int i;
  double f=0.0;
  xin = opt_arg[0];
  xqw = opt_arg[1];
  xlb = opt_arg[2];
  xub = opt_arg[3];
  yin = opt_arg[4];
  yqw = opt_arg[5];
  ylw = opt_arg[6];
  nodes = opt_arg[7];
  tf = opt_arg[8];
  w = opt_arg[9];
  set(x,add(mult_ebe(subtract(xub,xlb),scalar_mult(0.5,sigmoid0(xopt))),mean(append_ud(xub,xlb))));
  set(y_pred,run_bpn(x,nodes,tf,w));
  for(i=1;i<=xopt->n;++i) {
      f += xqw->pm[1][i]*(x->pm[1][i] - xin->pm[1][i])*(x->pm[1][i] - xin->pm[1][i]) +
	   yqw->pm[1][i]*(y_pred->pm[1][i] - yin->pm[1][i])*(y_pred->pm[1][i] - yin->pm[1][i]) +
	   ylw->pm[1][i]*y_pred->pm[1][i];
  }
if(print_mode>2) {
printf("In fopt_bpn, x = %g %g %g, f = %g\n",x->pm[1][1], x->pm[1][2], x->pm[1][3], f);
}  
  fm(x);fm(y_pred);
  return f;
}


double fopt_rbfn(xopt,opt_arg)
matrix *xopt;
matrix **opt_arg;
{
  pointer_to_stack local_ptr = ans;
  matrix *x=NULL,*y_pred=NULL;
  matrix *xin,*xqw,*xlb,*xub,*yin,*yqw,*ylw,*m,*shape,*w;
  int i;
  double f=0.0;
  xin = opt_arg[0];
  xqw = opt_arg[1];
  xlb = opt_arg[2];
  xub = opt_arg[3];
  yin = opt_arg[4];
  yqw = opt_arg[5];
  ylw = opt_arg[6];
  m = opt_arg[7];
  shape = opt_arg[8];
  w = opt_arg[9];
  set(x,add(mult_ebe(subtract(xub,xlb),scalar_mult(0.5,sigmoid0(xopt))),mean(append_ud(xub,xlb))));
  set(y_pred,run_rbfn(x,m,shape,w));
  for(i=1;i<=xopt->n;++i) {
      f += xqw->pm[1][i]*(x->pm[1][i] - xin->pm[1][i])*(x->pm[1][i] - xin->pm[1][i]) +
	   yqw->pm[1][i]*(y_pred->pm[1][i] - yin->pm[1][i])*(y_pred->pm[1][i] - yin->pm[1][i]) +
	   ylw->pm[1][i]*y_pred->pm[1][i];
  }
  fm(x);fm(y_pred);
  return f;
}



/* constrained optimization, not finished 
matrix *constrained_opt(func,x0,cntrl0,vlb,vub,opt_arg)
matrix *x0, *cntrl0, *xlb, *xub;
matrix **opt_arg;
double (*func)();
{
 pointer_to_stack local_ptr = ans;
 matrix *cntrl=NULL,*x=NULL,*xout=NULL,*chg=NULL;
 int i,lenvlb,lenvub,nvars,flag;
 set(xout,copy(x0));
 lenvlb = vlb->n;
 lenvub = vub->n;
 if(lenvlb != lenvub) signal_block_error("Bounds infeasible");
 nvars = xout->n;
 if(nvars != lenvub) signal_block_error("Bounds do not match dimension of x variables");
 set(chg,scalar_mult(1.e-7,add(absolute(xout),ones(1,nvars)))); 
 if(lenvlb > 0) {
   if(m2i(maximum(gt(vlb,vub))) > 0) signal_block_error("Bounds infeasible");
   set(xout,bounds(xout,scalar_add(1.e-4,vlb),vub));
   for(i=1;i<=lenvub;++i) if(xout->pm[1][i]==vub->pm[1][i]) chg->pm[1][i] = -chg->pm[1][i];
 }  
 flag = 2;  
 set(x,copy(x0)); 
}  */








