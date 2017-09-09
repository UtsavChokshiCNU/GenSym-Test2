;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module HEBREW18

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.



;; 45 54 13 12 1 2000 2 NIL 
;; 1/12/2000



(def-ab-font
  HEBREW18	; ab-font-name
  ROMAN	; ab-font-type
  18	; ab-font-size
  14	; ab-font-baseline
  24	; ab-font-maximum-width
  22	; ab-font-maximum-height

  ;; New, for 3.1 (4.0).  (MHD 5/26/93)
  18	; ab-font-point-size
  70	; ab-font-x-resolution
  70	; ab-font-y-resolution

  4480	; ab-font-width-in-x
  4480	; ab-font-width-in-y
  -2	; ab-font-x-offset
  -4	; ab-font-y-offset
  )



;; Hebrew Font Code 0x14, Unicode 0x1E7
(add-character-description
  20 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x15, Unicode 0x1E6
(add-character-description
  21 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x16, Unicode 0x15F
(add-character-description
  22 9 0 -4 8 14
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3150516 #o5130615 #o4120514 #o2100612 #o70211 #o7061010 #o5060607 #o6050711
    #o3040606 #o1040205 #o2030305 #o7021003 #o6010703 #o10204 #o2000602)
  2240)

;; Hebrew Font Code 0x17, Unicode 0x15E
(add-character-description
  23 12 0 -4 11 17
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3200521 #o5160620 #o4150517 #o3131015 #o10121115 #o1120314 #o110212 #o12101313
    #o11071214 #o6061110 #o2050607 #o11031304 #o1030206 #o20105 #o10011203 #o1010303
    #o3001002)
  2988)

;; Hebrew Font Code 0x18, Unicode 0x15D
(add-character-description
  24 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x19, Unicode 0x15C
(add-character-description
  25 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x1A, Unicode 0x130
(add-character-description
  26 5 1 0 2 16
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o30220 #o202)
  1245)

;; Hebrew Font Code 0x1B, Unicode 0x11F
(add-character-description
  27 10 0 -4 8 17
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o6170720 #o2170521 #o5160621 #o160220 #o3130515 #o5120614 #o2120315 #o2050306
    #o50113 #o5040606 #o1040214 #o6031017 #o2030505 #o2010502 #o5000601 #o1000201)
  2492)

;; Hebrew Font Code 0x1C, Unicode 0x11E
(add-character-description
  28 14 0 0 13 16
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5171220 #o13161417 #o4161217 #o12151317 #o3150417 #o2140317 #o13131516 #o7111513
    #o100114 #o14061507 #o2060307 #o13051407 #o11051206 #o1050216 #o12041307 #o2040506
    #o5031205 #o6011102 #o11001201 #o5000601)
  3485)

;; Hebrew Font Code 0x1D, Unicode 0x20A3
(add-character-description
  29 10 1 0 8 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3110513 #o110113 #o3050707 #o1020315 #o1001002)
  2492)

;; Hebrew Font Code 0x1E, Unicode 0x20AA
(add-character-description
  30 14 1 0 14 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o14111512 #o6101412 #o4040612 #o10021107 #o20212 #o11011207 #o14001611 #o1102)
  3653)

;; Hebrew Font Code 0x1F, Unicode 0x20AC
(add-character-description
  31 10 0 0 9 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5131015 #o10121114 #o4120515 #o3110414 #o3071010 #o70110 #o3051006 #o50106
    #o1040211 #o3030404 #o2020313 #o10011103 #o3010503 #o5001002)
  2492)

;; Hebrew Font Code 0x20, Unicode 0x5B0
(add-character-description
  32 6 2 -4 1 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o20103 #o101)
  1492)

;; Hebrew Font Code 0x21, Unicode 0x5B1
(add-character-description
  33 6 0 -4 5 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4020503 #o1020203 #o4000501 #o2000301 #o101)
  1492)

;; Hebrew Font Code 0x22, Unicode 0x5B2
(add-character-description
  34 6 0 -4 5 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4020503 #o4000501 #o301)
  1492)

;; Hebrew Font Code 0x23, Unicode 0x5B3
(add-character-description
  35 6 0 -4 5 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4020503 #o1010202 #o4000501 #o301)
  1492)

;; Hebrew Font Code 0x24, Unicode 0x5B4
(add-character-description
  36 6 2 -3 1 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o101)
  1492)

;; Hebrew Font Code 0x25, Unicode 0x5B5
(add-character-description
  37 6 2 -3 3 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2000301 #o101)
  1492)

;; Hebrew Font Code 0x26, Unicode 0x5B6
(add-character-description
  38 6 2 -4 3 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1020203 #o2000301 #o101)
  1492)

;; Hebrew Font Code 0x27, Unicode 0x5B7
(add-character-description
  39 6 1 -3 4 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o401)
  1492)

;; Hebrew Font Code 0x28, Unicode 0x5B8
(add-character-description
  40 6 2 -4 3 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1010203 #o301)
  1492)

;; Hebrew Font Code 0x29, Unicode 0x5B9
(add-character-description
  41 6 2 10 1 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o101)
  1492)

;; Hebrew Font Code 0x2A, Unicode 0x5BA
(add-character-description
  42 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x2B, Unicode 0x5BB
(add-character-description
  43 6 0 -4 5 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4020503 #o2010302 #o101)
  1492)

;; Hebrew Font Code 0x2C, Unicode 0x5BC
(add-character-description
  44 6 2 5 1 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o101)
  1492)

;; Hebrew Font Code 0x2D, Unicode 0x5BD
(add-character-description
  45 6 3 -4 1 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o103)
  1492)

;; Hebrew Font Code 0x2E, Unicode 0x5BE
(add-character-description
  46 7 1 7 5 2
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o502)
  1715)

;; Hebrew Font Code 0x2F, Unicode 0x5BF
(add-character-description
  47 6 1 11 4 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o401)
  1492)

;; Hebrew Font Code 0x30, Unicode 0x5C0
(add-character-description
  48 5 1 0 2 11
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o213)
  1232)

;; Hebrew Font Code 0x31, Unicode 0x5C1
(add-character-description
  49 6 7 11 1 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o101)
  1492)

;; Hebrew Font Code 0x32, Unicode 0x5C2
(add-character-description
  50 6 -2 11 1 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o101)
  1492)

;; Hebrew Font Code 0x33, Unicode 0x5C3
(add-character-description
  51 5 2 0 2 9
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o70211 #o202)
  1245)

;; Hebrew Font Code 0x34, Unicode 0x5C4
(add-character-description
  52 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x35, Unicode 0x5C5
(add-character-description
  53 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x36, Unicode 0x5C6
(add-character-description
  54 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x37, Unicode 0x5C7
(add-character-description
  55 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x38, Unicode 0x5C8
(add-character-description
  56 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x39, Unicode 0x5C9
(add-character-description
  57 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x3A, Unicode 0x5CA
(add-character-description
  58 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x3B, Unicode 0x5CB
(add-character-description
  59 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x3C, Unicode 0x5CC
(add-character-description
  60 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x3D, Unicode 0x5CD
(add-character-description
  61 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x3E, Unicode 0x5CE
(add-character-description
  62 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x3F, Unicode 0x5CF
(add-character-description
  63 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x40, Unicode 0x5D0
(add-character-description
  64 10 1 0 9 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o7111112 #o6101011 #o5060710 #o60112 #o2050306 #o4040606 #o1040212 #o6030705
    #o2020405 #o1010302 #o6001003 #o201)
  2522)

;; Hebrew Font Code 0x41, Unicode 0x5D1
(add-character-description
  65 9 1 0 9 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o10101112 #o100612 #o6031012 #o5021003 #o1010702 #o601)
  2428)

;; Hebrew Font Code 0x42, Unicode 0x5D2
(add-character-description
  66 7 0 0 6 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5100612 #o100112 #o1060212 #o2050307 #o3020410 #o4010512 #o1000402)
  1787)

;; Hebrew Font Code 0x43, Unicode 0x5D3
(add-character-description
  67 9 1 0 8 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5020712 #o1002)
  2277)

;; Hebrew Font Code 0x44, Unicode 0x5D4
(add-character-description
  68 11 1 0 9 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o50212 #o7031012 #o10021112 #o6011003 #o602)
  2697)

;; Hebrew Font Code 0x45, Unicode 0x5D5
(add-character-description
  69 4 1 0 2 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o212)
  1105)

;; Hebrew Font Code 0x46, Unicode 0x5D6
(add-character-description
  70 7 1 0 6 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1040312 #o1030404 #o2020503 #o602)
  1713)

;; Hebrew Font Code 0x47, Unicode 0x5D7
(add-character-description
  71 10 1 0 9 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o10021112 #o6020703 #o20212 #o7011012 #o702)
  2682)

;; Hebrew Font Code 0x48, Unicode 0x5D8
(add-character-description
  72 10 1 0 9 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o7101011 #o3100612 #o1100211 #o6070711 #o2070311 #o7021110 #o4010503 #o5001002
    #o210)
  2643)

;; Hebrew Font Code 0x49, Unicode 0x5D9
(add-character-description
  73 4 1 5 2 5
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o205)
  1105)

;; Hebrew Font Code 0x4A, Unicode 0x5DA
(add-character-description
  74 9 0 -4 8 14
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o6030716 #o7021016 #o5010703 #o502)
  2282)

;; Hebrew Font Code 0x4B, Unicode 0x5DB
(add-character-description
  75 8 1 0 6 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o100312 #o3070411 #o5030610 #o3020403 #o4010511 #o402)
  2065)

;; Hebrew Font Code 0x4C, Unicode 0x5DC
(add-character-description
  76 8 1 0 6 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3110515 #o4050611 #o2030605 #o205)
  2074)

;; Hebrew Font Code 0x4D, Unicode 0x5DD
(add-character-description
  77 10 1 0 9 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2100712 #o10021112 #o6020703 #o20212 #o7011012 #o702)
  2682)

;; Hebrew Font Code 0x4E, Unicode 0x5DE
(add-character-description
  78 11 1 0 9 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4100712 #o100112 #o1070212 #o10021112 #o6020703 #o1020307 #o7011012 #o3010404
    #o4000702 #o202)
  2693)

;; Hebrew Font Code 0x4F, Unicode 0x5DF
(add-character-description
  79 4 1 -4 2 14
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o216)
  1105)

;; Hebrew Font Code 0x50, Unicode 0x5E0
(add-character-description
  80 6 1 0 4 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o100212 #o2020312 #o3010412 #o302)
  1579)

;; Hebrew Font Code 0x51, Unicode 0x5E1
(add-character-description
  81 10 1 0 8 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3100512 #o5070612 #o2070312 #o7031010 #o30110 #o5020603 #o2020303 #o6010711
    #o1010211 #o2000602)
  2573)

;; Hebrew Font Code 0x52, Unicode 0x5E2
(add-character-description
  82 9 1 -1 8 11
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4110512 #o110213 #o4100611 #o5060710 #o2030412 #o6001006 #o1000303)
  2371)

;; Hebrew Font Code 0x53, Unicode 0x5E3
(add-character-description
  83 10 1 -4 8 14
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1060407 #o6030716 #o7021016 #o20206 #o5010703 #o502)
  2538)

;; Hebrew Font Code 0x54, Unicode 0x5E4
(add-character-description
  84 10 1 0 8 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4110512 #o1100412 #o4070611 #o70111 #o1050406 #o6040711 #o7031007 #o4020503
    #o20205 #o5010704 #o502)
  2448)

;; Hebrew Font Code 0x55, Unicode 0x5E5
(add-character-description
  85 8 0 -4 7 14
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3050516 #o5040605 #o2030405 #o1010303 #o5000704 #o201)
  2067)

;; Hebrew Font Code 0x56, Unicode 0x5E6
(add-character-description
  86 8 0 0 8 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o7101012 #o100512 #o6070712 #o5060612 #o4050507 #o3040605 #o6030705 #o2020404
    #o1010302 #o6001003 #o201)
  2144)

;; Hebrew Font Code 0x57, Unicode 0x5E7
(add-character-description
  87 10 1 -4 8 14
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4070612 #o5050707 #o50216 #o6021005 #o1002)
  2463)

;; Hebrew Font Code 0x58, Unicode 0x5E8
(add-character-description
  88 9 0 0 8 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o6031012 #o5010703 #o502)
  2282)

;; Hebrew Font Code 0x59, Unicode 0x5E9
(add-character-description
  89 12 1 0 11 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4110712 #o2100711 #o7071011 #o1060310 #o10051111 #o1050506 #o11041210 #o4040605
    #o11001304 #o5000704 #o205)
  3111)

;; Hebrew Font Code 0x5A, Unicode 0x5EA
(add-character-description
  90 11 1 0 10 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2110312 #o1100212 #o70112 #o11021212 #o7021003 #o2020411 #o10011112 #o1002)
  2879)

;; Hebrew Font Code 0x5B, Unicode 0x5EB
(add-character-description
  91 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x5C, Unicode 0x5EC
(add-character-description
  92 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x5D, Unicode 0x5ED
(add-character-description
  93 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x5E, Unicode 0x5EE
(add-character-description
  94 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x5F, Unicode 0x5EF
(add-character-description
  95 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x60, Unicode 0x5F0
(add-character-description
  96 9 1 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5000712 #o212)
  2209)

;; Hebrew Font Code 0x61, Unicode 0x5F1
(add-character-description
  97 9 1 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5000712 #o205)
  2209)

;; Hebrew Font Code 0x62, Unicode 0x5F2
(add-character-description
  98 9 1 5 7 5
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5000705 #o205)
  2209)

;; Hebrew Font Code 0x63, Unicode 0x5F3
(add-character-description
  99 4 1 7 3 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o20103 #o10202 #o1000301)
  1057)

;; Hebrew Font Code 0x64, Unicode 0x5F4
(add-character-description
  100 7 1 7 7 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4020503 #o20103 #o4010602 #o10202 #o5000701 #o1000301)
  1868)

;; Hebrew Font Code 0x65, Unicode 0xFB1D
(add-character-description
  101 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x66, Unicode 0xFB1E
(add-character-description
  102 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x67, Unicode 0xFB1F
(add-character-description
  103 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x68, Unicode 0xFB20
(add-character-description
  104 9 1 0 8 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4100512 #o100212 #o5070611 #o6060711 #o2030312 #o3020412 #o6001006 #o1000303)
  2398)

;; Hebrew Font Code 0x69, Unicode 0xFB21
(add-character-description
  105 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x6A, Unicode 0xFB22
(add-character-description
  106 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x6B, Unicode 0xFB23
(add-character-description
  107 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x6C, Unicode 0xFB24
(add-character-description
  108 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x6D, Unicode 0xFB25
(add-character-description
  109 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x6E, Unicode 0xFB26
(add-character-description
  110 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x6F, Unicode 0xFB27
(add-character-description
  111 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x70, Unicode 0xFB28
(add-character-description
  112 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x71, Unicode 0xFB29
(add-character-description
  113 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x72, Unicode 0xFB2A
(add-character-description
  114 12 1 0 11 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4140715 #o2130714 #o7121014 #o1110313 #o10101114 #o1100511 #o11071213 #o4070610
    #o11031307 #o5030707 #o30210 #o11001201)
  3111)

;; Hebrew Font Code 0x73, Unicode 0xFB2B
(add-character-description
  115 12 1 0 11 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4140715 #o2130714 #o7121014 #o1110313 #o10101114 #o1100511 #o11071213 #o4070610
    #o11031307 #o5030707 #o30210 #o101)
  3111)

;; Hebrew Font Code 0x74, Unicode 0xFB2C
(add-character-description
  116 12 1 0 11 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4140715 #o2130714 #o7121014 #o10111114 #o1110313 #o11101213 #o7101011 #o1100511
    #o4070610 #o11031310 #o5030707 #o30210 #o11001201)
  3111)

;; Hebrew Font Code 0x75, Unicode 0xFB2D
(add-character-description
  117 12 1 0 11 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4140715 #o2130714 #o7121014 #o10111114 #o1110313 #o11101213 #o7101011 #o1100511
    #o4070610 #o11031310 #o5030707 #o30210 #o101)
  3111)

;; Hebrew Font Code 0x76, Unicode 0xFB2E
(add-character-description
  118 10 1 0 9 62
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o7751176 #o6741075 #o5720774 #o720176 #o2710372 #o4700672 #o1700276 #o6670771
    #o2660471 #o1650366 #o6641067 #o640265 #o2560657)
  2522)

;; Hebrew Font Code 0x77, Unicode 0xFB2F
(add-character-description
  119 10 1 0 9 62
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o7751176 #o6741075 #o5720774 #o720176 #o2710372 #o4700672 #o1700276 #o6670771
    #o2660471 #o1650366 #o6641067 #o640265 #o5560657 #o3560457)
  2522)

;; Hebrew Font Code 0x78, Unicode 0xFB30
(add-character-description
  120 10 1 0 9 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o7111112 #o6101011 #o3100411 #o5060710 #o60112 #o2050306 #o4040606 #o1040212
    #o6030705 #o2020405 #o1010302 #o6001003 #o201)
  2522)

;; Hebrew Font Code 0x79, Unicode 0xFB31
(add-character-description
  121 9 1 0 9 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o10101112 #o100612 #o2040305 #o6031012 #o5021003 #o1010702 #o601)
  2428)

;; Hebrew Font Code 0x7A, Unicode 0xFB32
(add-character-description
  122 7 0 0 6 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5100612 #o100112 #o1060212 #o2050307 #o30104 #o3020410 #o4010512 #o1000402)
  1787)

;; Hebrew Font Code 0x7B, Unicode 0xFB33
(add-character-description
  123 9 1 0 8 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2040305 #o5020712 #o1002)
  2277)

;; Hebrew Font Code 0x7C, Unicode 0xFB34
(add-character-description
  124 11 1 0 9 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4050506 #o50212 #o7031012 #o10021112 #o6011003 #o602)
  2697)

;; Hebrew Font Code 0x7D, Unicode 0xFB35
(add-character-description
  125 5 0 0 4 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o40105 #o2000412)
  1284)

;; Hebrew Font Code 0x7E, Unicode 0xFB36
(add-character-description
  126 7 0 0 8 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3040512 #o40105 #o3030604 #o4020703 #o1001002)
  1842)

;; Hebrew Font Code 0x7F, Unicode 0xFB37
(add-character-description
  127 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x80, Unicode 0xFB38
(add-character-description
  128 10 1 0 9 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o7101011 #o3100612 #o1100211 #o6070711 #o2070311 #o4040505 #o7021110 #o4010503
    #o5001002 #o210)
  2643)

;; Hebrew Font Code 0x81, Unicode 0xFB39
(add-character-description
  129 5 0 5 4 5
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o20103 #o2000405)
  1284)

;; Hebrew Font Code 0x82, Unicode 0xFB3A
(add-character-description
  130 9 0 -4 8 14
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3050406 #o6030716 #o7021016 #o5010703 #o502)
  2282)

;; Hebrew Font Code 0x83, Unicode 0xFB3B
(add-character-description
  131 8 1 0 6 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o100312 #o3070411 #o2040305 #o5030610 #o3020403 #o4010511 #o402)
  2065)

;; Hebrew Font Code 0x84, Unicode 0xFB3C
(add-character-description
  132 8 1 0 6 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3110515 #o2070310 #o4050611 #o2030605 #o205)
  2074)

;; Hebrew Font Code 0x85, Unicode 0xFB3D
(add-character-description
  133 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x86, Unicode 0xFB3E
(add-character-description
  134 11 1 0 9 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4100712 #o100112 #o1070212 #o5040605 #o10021112 #o6020703 #o1020307 #o7011012
    #o3010404 #o4000702 #o202)
  2693)

;; Hebrew Font Code 0x87, Unicode 0xFB3F
(add-character-description
  135 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x88, Unicode 0xFB40
(add-character-description
  136 6 1 0 4 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o100212 #o40105 #o2020312 #o3010412 #o302)
  1579)

;; Hebrew Font Code 0x89, Unicode 0xFB41
(add-character-description
  137 10 1 0 8 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3100512 #o5070612 #o2070312 #o4040505 #o7031010 #o30110 #o5020603 #o2020303
    #o6010711 #o1010211 #o2000602)
  2573)

;; Hebrew Font Code 0x8A, Unicode 0xFB42
(add-character-description
  138 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x8B, Unicode 0xFB43
(add-character-description
  139 10 1 -4 8 14
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1060307 #o4050506 #o7021016 #o5020603 #o20206 #o6010716 #o602)
  2538)

;; Hebrew Font Code 0x8C, Unicode 0xFB44
(add-character-description
  140 10 1 0 8 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4110512 #o1100412 #o4070611 #o70111 #o4050506 #o1050306 #o6040711 #o7031007
    #o4020503 #o20205 #o5010704 #o502)
  2448)

;; Hebrew Font Code 0x8D, Unicode 0xFB45
(add-character-description
  141 13 2 0 10 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1131114 #o11011214 #o10114 #o1201)
  3360)

;; Hebrew Font Code 0x8E, Unicode 0xFB46
(add-character-description
  142 8 0 0 8 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o7101012 #o100512 #o6070712 #o5060612 #o4050507 #o50106 #o3040605 #o6030705
    #o2020404 #o1010302 #o6001003 #o201)
  2144)

;; Hebrew Font Code 0x8F, Unicode 0xFB47
(add-character-description
  143 10 1 -4 8 14
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4070612 #o5050707 #o50216 #o3030404 #o6021005 #o1002)
  2463)

;; Hebrew Font Code 0x90, Unicode 0xFB48
(add-character-description
  144 9 0 0 8 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3050406 #o6031012 #o5010703 #o502)
  2282)

;; Hebrew Font Code 0x91, Unicode 0xFB49
(add-character-description
  145 12 1 0 11 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4110712 #o2100711 #o7071011 #o10061111 #o1060310 #o11051210 #o7051006 #o1050506
    #o4040605 #o11001305 #o5000704 #o205)
  3111)

;; Hebrew Font Code 0x92, Unicode 0xFB4A
(add-character-description
  146 11 1 0 10 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2110312 #o1100212 #o70112 #o5050606 #o11021212 #o7021003 #o2020411 #o10011112
    #o1002)
  2879)

;; Hebrew Font Code 0x93, Unicode 0xFB4B
(add-character-description
  147 4 1 0 2 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o30215 #o101)
  1105)

;; Hebrew Font Code 0x94, Unicode 0xFB4C
(add-character-description
  148 9 1 0 9 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o10131115 #o130615 #o6061015 #o5051006 #o1040705 #o30604 #o1000501)
  2428)

;; Hebrew Font Code 0x95, Unicode 0xFB4D
(add-character-description
  149 8 1 0 6 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o130315 #o3120414 #o5060613 #o3050406 #o4040514 #o30405 #o401)
  2065)

;; Hebrew Font Code 0x96, Unicode 0xFB4E
(add-character-description
  150 10 1 0 8 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4140515 #o1130415 #o4120614 #o120114 #o1100411 #o6070714 #o7061012 #o4050506
    #o50210 #o5040707 #o30505 #o1000501)
  2448)

;; Hebrew Font Code 0x97, Unicode 0xFB4F
(add-character-description
  151 10 0 0 10 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o10141215 #o7131114 #o6111013 #o1110215 #o5070711 #o2070315 #o7061010 #o4050510
    #o3040411 #o7031106 #o2030305 #o205)
  2579)
