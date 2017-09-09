/*
 * equal_aux.h - helper macros fpr equal() and equalp() 
 *
 * Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
 * Use of this Library is subject to the terms of a license from
 * Chestnut Software, Inc.  Please refer to the License for details.
 *
 * Author:  
 *
 */

#define SI_STORED_NUMBER_P(a) \
   SI_ENUM_LE(SI_STORED_OBJECT_TYPE(a), COMPLEX_TYPE)

    
