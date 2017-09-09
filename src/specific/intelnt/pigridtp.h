/*-----------------------------------------------------------------------------

$Archive: /pi/freeze/intel/piapi/pigridtp.h $
$Revision: 11 $     $Date: 5/27/08 3:21p $

-------------------------------------------------------------------------------
    
Copyright (c) 1994-2000 OSIsoft, Inc. All rights reserved.

THIS SOFTWARE CONTAINS CONFIDENTIAL INFORMATION AND TRADE SECRETS OF
OSIsoft, INC.  USE, DISCLOSURE, OR REPRODUCTION IS PROHIBITED
WITHOUT THE PRIOR EXPRESS WRITTEN PERMISSION OF OSIsoft, INC.

RESTRICTED RIGHTS LEGEND
Use, duplication, or disclosure by the Government is subject to re-
strictions as set forth in subparagraph (c)(1)(ii) of the Rights in
Technical Data and Computer Software clause at DFARS 252.227.7013

OSIsoft, Inc.
777 Davis St., San Leandro CA 94577

-------------------------------------------------------------------------------

Description:

Include file containing definitions of supported PIgrid data types.

-------------------------------------------------------------------------------

History:

931117	RCV	Original Version
940826  RAB     Added keywords

-----------------------------------------------------------------------------*/ 
#define PIGRID_UNKNOWN     0
#define PIGRID_CHAR        1
#define PIGRID_INT         2
#define PIGRID_FLOAT       3
#define PIGRID_TIME        4	
#define PIGRID_PERIOD      5
#define PIGRID_DIGITAL     6
#define PIGRID_LASTDTYPE   PIGRID_DIGITAL
