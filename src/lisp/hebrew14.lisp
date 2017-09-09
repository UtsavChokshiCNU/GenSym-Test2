;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module HEBREW14

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.



;; 45 54 13 12 1 2000 2 NIL 
;; 1/12/2000



(def-ab-font
  HEBREW14	; ab-font-name
  ROMAN	; ab-font-type
  14	; ab-font-size
  12	; ab-font-baseline
  16	; ab-font-maximum-width
  18	; ab-font-maximum-height

  ;; New, for 3.1 (4.0).  (MHD 5/26/93)
  14	; ab-font-point-size
  70	; ab-font-x-resolution
  70	; ab-font-y-resolution

  3484	; ab-font-width-in-x
  3484	; ab-font-width-in-y
  -1	; ab-font-x-offset
  -3	; ab-font-y-offset
  )



;; Hebrew Font Code 0x14, Unicode 0x1E7
(add-character-description
  20 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x15, Unicode 0x1E6
(add-character-description
  21 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x16, Unicode 0x15F
(add-character-description
  22 7 0 -3 6 11
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2120413 #o4110513 #o3100411 #o1070510 #o60107 #o5050607 #o4040605 #o2030404
    #o1020204 #o5010602 #o10103 #o1000501)
  1742)

;; Hebrew Font Code 0x17, Unicode 0x15E
(add-character-description
  23 9 0 -3 8 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2140415 #o4130515 #o3120413 #o2110612 #o6100711 #o1100211 #o70110 #o7061011
    #o4050706 #o1040505 #o7021003 #o20104 #o6010702 #o10202 #o2000601)
  2324)

;; Hebrew Font Code 0x18, Unicode 0x15D
(add-character-description
  24 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x19, Unicode 0x15C
(add-character-description
  25 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x1A, Unicode 0x130
(add-character-description
  26 4 1 0 1 12
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o20114 #o101)
  968)

;; Hebrew Font Code 0x1B, Unicode 0x11F
(add-character-description
  27 8 0 -3 6 14
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1150416 #o4140516 #o140115 #o2120413 #o4110512 #o1110212 #o50111 #o4040505
    #o1040205 #o5030615 #o1030404 #o2010402 #o4000501 #o1000201)
  1938)

;; Hebrew Font Code 0x1C, Unicode 0x11E
(add-character-description
  28 11 0 0 10 13
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2141015 #o10131114 #o1130214 #o11111213 #o6101211 #o11051206 #o50113 #o10041105
    #o1040205 #o2031004 #o4010602 #o6000701 #o3000401)
  2710)

;; Hebrew Font Code 0x1D, Unicode 0x20A3
(add-character-description
  29 8 0 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2070410 #o70110 #o2040605 #o1010212 #o1000701)
  1938)

;; Hebrew Font Code 0x1E, Unicode 0x20AA
(add-character-description
  30 11 1 0 10 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4071110 #o3030410 #o6010706 #o10110 #o11001207 #o601)
  2841)

;; Hebrew Font Code 0x1F, Unicode 0x20AC
(add-character-description
  31 8 0 0 8 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4110712 #o7101011 #o3100411 #o2070311 #o2050706 #o50106 #o2030704 #o30104
    #o1020207 #o7011002 #o2010302 #o3000701)
  1938)

;; Hebrew Font Code 0x20, Unicode 0x5B0
(add-character-description
  32 5 2 -3 1 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o20103 #o101)
  1160)

;; Hebrew Font Code 0x21, Unicode 0x5B1
(add-character-description
  33 5 0 -3 5 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4020503 #o1020203 #o4000501 #o2000301 #o101)
  1160)

;; Hebrew Font Code 0x22, Unicode 0x5B2
(add-character-description
  34 5 0 -3 4 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3020403 #o3000401 #o201)
  1160)

;; Hebrew Font Code 0x23, Unicode 0x5B3
(add-character-description
  35 5 0 -3 5 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4020503 #o1010202 #o4000501 #o301)
  1160)

;; Hebrew Font Code 0x24, Unicode 0x5B4
(add-character-description
  36 5 2 -3 1 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o101)
  1160)

;; Hebrew Font Code 0x25, Unicode 0x5B5
(add-character-description
  37 5 1 -3 3 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2000301 #o101)
  1160)

;; Hebrew Font Code 0x26, Unicode 0x5B6
(add-character-description
  38 5 1 -3 3 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1020203 #o2000301 #o101)
  1160)

;; Hebrew Font Code 0x27, Unicode 0x5B7
(add-character-description
  39 5 1 -2 3 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o301)
  1160)

;; Hebrew Font Code 0x28, Unicode 0x5B8
(add-character-description
  40 5 1 -3 3 2
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1010202 #o301)
  1160)

;; Hebrew Font Code 0x29, Unicode 0x5B9
(add-character-description
  41 5 2 8 1 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o101)
  1160)

;; Hebrew Font Code 0x2A, Unicode 0x5BA
(add-character-description
  42 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x2B, Unicode 0x5BB
(add-character-description
  43 5 0 -3 5 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4020503 #o2010302 #o101)
  1160)

;; Hebrew Font Code 0x2C, Unicode 0x5BC
(add-character-description
  44 5 2 4 1 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o101)
  1160)

;; Hebrew Font Code 0x2D, Unicode 0x5BD
(add-character-description
  45 5 2 -3 1 2
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o102)
  1160)

;; Hebrew Font Code 0x2E, Unicode 0x5BE
(add-character-description
  46 5 1 6 4 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o401)
  1334)

;; Hebrew Font Code 0x2F, Unicode 0x5BF
(add-character-description
  47 5 1 8 3 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o301)
  1160)

;; Hebrew Font Code 0x30, Unicode 0x5C0
(add-character-description
  48 4 1 0 1 9
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o111)
  958)

;; Hebrew Font Code 0x31, Unicode 0x5C1
(add-character-description
  49 5 5 8 1 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o101)
  1160)

;; Hebrew Font Code 0x32, Unicode 0x5C2
(add-character-description
  50 5 -2 8 1 1
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o101)
  1160)

;; Hebrew Font Code 0x33, Unicode 0x5C3
(add-character-description
  51 4 1 0 1 7
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o60107 #o101)
  968)

;; Hebrew Font Code 0x34, Unicode 0x5C4
(add-character-description
  52 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x35, Unicode 0x5C5
(add-character-description
  53 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x36, Unicode 0x5C6
(add-character-description
  54 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x37, Unicode 0x5C7
(add-character-description
  55 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x38, Unicode 0x5C8
(add-character-description
  56 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x39, Unicode 0x5C9
(add-character-description
  57 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x3A, Unicode 0x5CA
(add-character-description
  58 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x3B, Unicode 0x5CB
(add-character-description
  59 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x3C, Unicode 0x5CC
(add-character-description
  60 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x3D, Unicode 0x5CD
(add-character-description
  61 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x3E, Unicode 0x5CE
(add-character-description
  62 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x3F, Unicode 0x5CF
(add-character-description
  63 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x40, Unicode 0x5D0
(add-character-description
  64 8 1 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5070610 #o4060507 #o3040406 #o40110 #o4030504 #o2030304 #o1010205 #o5000603
    #o101)
  1961)

;; Hebrew Font Code 0x41, Unicode 0x5D1
(add-character-description
  65 7 1 0 7 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o6070710 #o70510 #o5020610 #o4010502 #o401)
  1888)

;; Hebrew Font Code 0x42, Unicode 0x5D2
(add-character-description
  66 5 1 0 4 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o70110 #o1060207 #o2050306 #o3010410 #o1000301)
  1390)

;; Hebrew Font Code 0x43, Unicode 0x5D3
(add-character-description
  67 7 1 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4010510 #o601)
  1771)

;; Hebrew Font Code 0x44, Unicode 0x5D4
(add-character-description
  68 8 1 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o40110 #o5020610 #o4010502 #o401)
  2098)

;; Hebrew Font Code 0x45, Unicode 0x5D5
(add-character-description
  69 3 1 0 1 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o110)
  859)

;; Hebrew Font Code 0x46, Unicode 0x5D6
(add-character-description
  70 5 1 0 4 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1020210 #o1010302 #o401)
  1332)

;; Hebrew Font Code 0x47, Unicode 0x5D7
(add-character-description
  71 8 1 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5020610 #o4010502 #o10110 #o401)
  2086)

;; Hebrew Font Code 0x48, Unicode 0x5D8
(add-character-description
  72 8 1 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2070410 #o4060510 #o1060210 #o5010606 #o3010402 #o3000501 #o106)
  2055)

;; Hebrew Font Code 0x49, Unicode 0x5D9
(add-character-description
  73 3 1 4 1 4
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o104)
  859)

;; Hebrew Font Code 0x4A, Unicode 0x5DA
(add-character-description
  74 7 0 -3 6 11
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5020613 #o4010502 #o401)
  1774)

;; Hebrew Font Code 0x4B, Unicode 0x5DB
(add-character-description
  75 6 1 0 4 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o70210 #o2060310 #o3010406 #o301)
  1606)

;; Hebrew Font Code 0x4C, Unicode 0x5DC
(add-character-description
  76 6 0 0 5 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2070312 #o3060407 #o4030506 #o1020503 #o103)
  1613)

;; Hebrew Font Code 0x4D, Unicode 0x5DD
(add-character-description
  77 8 1 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1070510 #o5020610 #o4010502 #o10110 #o401)
  2086)

;; Hebrew Font Code 0x4E, Unicode 0x5DE
(add-character-description
  78 8 1 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3070510 #o50110 #o1020205 #o5010610 #o2010302 #o3000501 #o103)
  2094)

;; Hebrew Font Code 0x4F, Unicode 0x5DF
(add-character-description
  79 3 1 -3 1 11
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o113)
  859)

;; Hebrew Font Code 0x50, Unicode 0x5E0
(add-character-description
  80 5 1 0 3 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o70210 #o2010310 #o201)
  1228)

;; Hebrew Font Code 0x51, Unicode 0x5E1
(add-character-description
  81 8 1 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1070410 #o4060510 #o5020606 #o4010502 #o10107 #o1000501)
  2001)

;; Hebrew Font Code 0x52, Unicode 0x5E2
(add-character-description
  82 7 0 -1 6 9
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o100211 #o3070410 #o4060507 #o2020310 #o5000606 #o1000202)
  1844)

;; Hebrew Font Code 0x53, Unicode 0x5E3
(add-character-description
  83 8 1 -3 6 11
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1040305 #o5020613 #o4010502 #o10104 #o401)
  1973)

;; Hebrew Font Code 0x54, Unicode 0x5E4
(add-character-description
  84 7 1 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o70410 #o3060507 #o1040305 #o5030606 #o4020603 #o3010502 #o10104 #o401)
  1904)

;; Hebrew Font Code 0x55, Unicode 0x5E5
(add-character-description
  85 6 0 -3 5 11
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2040313 #o3030404 #o1010204 #o4000503 #o101)
  1608)

;; Hebrew Font Code 0x56, Unicode 0x5E6
(add-character-description
  86 7 0 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5070610 #o70410 #o4050510 #o3040405 #o4030504 #o2020304 #o1010202 #o5000603
    #o101)
  1667)

;; Hebrew Font Code 0x57, Unicode 0x5E7
(add-character-description
  87 7 1 -3 6 11
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3050410 #o4040506 #o40113 #o5010604 #o601)
  1916)

;; Hebrew Font Code 0x58, Unicode 0x5E8
(add-character-description
  88 7 0 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5020610 #o4010502 #o401)
  1774)

;; Hebrew Font Code 0x59, Unicode 0x5E9
(add-character-description
  89 9 1 0 8 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2070610 #o1050207 #o6040707 #o1040305 #o7001004 #o3000404 #o104)
  2419)

;; Hebrew Font Code 0x5A, Unicode 0x5EA
(add-character-description
  90 9 1 0 7 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1070210 #o60110 #o6010710 #o2010310 #o601)
  2239)

;; Hebrew Font Code 0x5B, Unicode 0x5EB
(add-character-description
  91 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x5C, Unicode 0x5EC
(add-character-description
  92 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x5D, Unicode 0x5ED
(add-character-description
  93 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x5E, Unicode 0x5EE
(add-character-description
  94 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x5F, Unicode 0x5EF
(add-character-description
  95 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x60, Unicode 0x5F0
(add-character-description
  96 7 1 0 4 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3000410 #o110)
  1718)

;; Hebrew Font Code 0x61, Unicode 0x5F1
(add-character-description
  97 7 1 0 4 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3000410 #o104)
  1718)

;; Hebrew Font Code 0x62, Unicode 0x5F2
(add-character-description
  98 7 1 4 4 4
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3000404 #o104)
  1718)

;; Hebrew Font Code 0x63, Unicode 0x5F3
(add-character-description
  99 3 1 5 2 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o10103 #o1000202)
  822)

;; Hebrew Font Code 0x64, Unicode 0x5F4
(add-character-description
  100 6 1 5 5 3
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3010403 #o10103 #o4000502 #o1000202)
  1453)

;; Hebrew Font Code 0x65, Unicode 0xFB1D
(add-character-description
  101 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x66, Unicode 0xFB1E
(add-character-description
  102 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x67, Unicode 0xFB1F
(add-character-description
  103 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x68, Unicode 0xFB20
(add-character-description
  104 7 1 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3070410 #o70210 #o4060507 #o2020310 #o5000606 #o1000202)
  1864)

;; Hebrew Font Code 0x69, Unicode 0xFB21
(add-character-description
  105 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x6A, Unicode 0xFB22
(add-character-description
  106 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x6B, Unicode 0xFB23
(add-character-description
  107 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x6C, Unicode 0xFB24
(add-character-description
  108 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x6D, Unicode 0xFB25
(add-character-description
  109 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x6E, Unicode 0xFB26
(add-character-description
  110 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x6F, Unicode 0xFB27
(add-character-description
  111 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x70, Unicode 0xFB28
(add-character-description
  112 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x71, Unicode 0xFB29
(add-character-description
  113 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x72, Unicode 0xFB2A
(add-character-description
  114 9 1 0 8 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2110612 #o1070211 #o6060711 #o1060307 #o7021006 #o3020406 #o20106 #o7001001)
  2419)

;; Hebrew Font Code 0x73, Unicode 0xFB2B
(add-character-description
  115 9 1 0 8 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2110612 #o1070211 #o6060711 #o1060307 #o7021006 #o3020406 #o20106 #o101)
  2419)

;; Hebrew Font Code 0x74, Unicode 0xFB2C
(add-character-description
  116 9 1 0 8 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2110612 #o1070211 #o6060711 #o4060507 #o1060307 #o7021006 #o3020406 #o20106
    #o7001001)
  2419)

;; Hebrew Font Code 0x75, Unicode 0xFB2D
(add-character-description
  117 9 1 0 8 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2110612 #o1070211 #o6060711 #o4060507 #o1060307 #o7021006 #o3020406 #o20106
    #o101)
  2419)

;; Hebrew Font Code 0x76, Unicode 0xFB2E
(add-character-description
  118 8 1 -66 6 74
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2130514 #o5070610 #o4060507 #o3040406 #o40110 #o4030504 #o2030304 #o1010205
    #o5000603 #o101)
  1961)

;; Hebrew Font Code 0x77, Unicode 0xFB2F
(add-character-description
  119 8 1 -67 6 75
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o4130514 #o2130314 #o5070610 #o4060507 #o3040406 #o40110 #o4030504 #o2030304
    #o1010205 #o5000603 #o101)
  1961)

;; Hebrew Font Code 0x78, Unicode 0xFB30
(add-character-description
  120 8 1 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5070610 #o4060507 #o2060307 #o3040406 #o40110 #o4030504 #o2030304 #o1010205
    #o5000603 #o101)
  1961)

;; Hebrew Font Code 0x79, Unicode 0xFB31
(add-character-description
  121 7 1 0 7 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o6070710 #o70510 #o2040305 #o5020610 #o4010502 #o401)
  1888)

;; Hebrew Font Code 0x7A, Unicode 0xFB32
(add-character-description
  122 5 1 0 4 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o70110 #o1060207 #o2050306 #o1030204 #o3010410 #o1000301)
  1390)

;; Hebrew Font Code 0x7B, Unicode 0xFB33
(add-character-description
  123 7 1 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2030304 #o4010510 #o601)
  1771)

;; Hebrew Font Code 0x7C, Unicode 0xFB34
(add-character-description
  124 8 1 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3040405 #o40110 #o5020610 #o4010502 #o401)
  2098)

;; Hebrew Font Code 0x7D, Unicode 0xFB35
(add-character-description
  125 4 0 0 3 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o30104 #o2000310)
  999)

;; Hebrew Font Code 0x7E, Unicode 0xFB36
(add-character-description
  126 6 0 0 7 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o30104 #o3020410 #o3010502 #o1000701)
  1432)

;; Hebrew Font Code 0x7F, Unicode 0xFB37
(add-character-description
  127 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x80, Unicode 0xFB38
(add-character-description
  128 8 1 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2070410 #o4060510 #o1060210 #o3040405 #o5010606 #o3010402 #o3000501 #o106)
  2055)

;; Hebrew Font Code 0x81, Unicode 0xFB39
(add-character-description
  129 4 0 4 3 4
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o20103 #o2000304)
  999)

;; Hebrew Font Code 0x82, Unicode 0xFB3A
(add-character-description
  130 7 0 -3 6 11
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2040305 #o5020613 #o4010502 #o401)
  1774)

;; Hebrew Font Code 0x83, Unicode 0xFB3B
(add-character-description
  131 6 1 0 4 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o70210 #o2060310 #o1040205 #o3010406 #o301)
  1606)

;; Hebrew Font Code 0x84, Unicode 0xFB3C
(add-character-description
  132 6 0 0 5 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2070312 #o3060407 #o1050206 #o4030506 #o1020503 #o103)
  1613)

;; Hebrew Font Code 0x85, Unicode 0xFB3D
(add-character-description
  133 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x86, Unicode 0xFB3E
(add-character-description
  134 8 1 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3070510 #o50110 #o3040405 #o1020205 #o5010610 #o2010302 #o3000501 #o103)
  2094)

;; Hebrew Font Code 0x87, Unicode 0xFB3F
(add-character-description
  135 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x88, Unicode 0xFB40
(add-character-description
  136 5 1 0 3 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o70210 #o40105 #o2010310 #o201)
  1228)

;; Hebrew Font Code 0x89, Unicode 0xFB41
(add-character-description
  137 8 1 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1070410 #o4060510 #o3030404 #o5020606 #o4010502 #o10107 #o1000501)
  2001)

;; Hebrew Font Code 0x8A, Unicode 0xFB42
(add-character-description
  138 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x8B, Unicode 0xFB43
(add-character-description
  139 8 1 -3 6 11
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3040405 #o1040205 #o5020613 #o4010502 #o10104 #o401)
  1973)

;; Hebrew Font Code 0x8C, Unicode 0xFB44
(add-character-description
  140 7 1 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o70410 #o3060507 #o3040405 #o1040205 #o5030606 #o4020603 #o3010502 #o10104
    #o401)
  1904)

;; Hebrew Font Code 0x8D, Unicode 0xFB45
(add-character-description
  141 10 2 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1110612 #o6010712 #o10112 #o701)
  2613)

;; Hebrew Font Code 0x8E, Unicode 0xFB46
(add-character-description
  142 7 0 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5070610 #o70410 #o4050510 #o3040405 #o40105 #o4030504 #o2020304 #o1010202
    #o5000603 #o101)
  1667)

;; Hebrew Font Code 0x8F, Unicode 0xFB47
(add-character-description
  143 7 1 -3 6 11
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o3050410 #o4040506 #o40113 #o2030304 #o5010604 #o601)
  1916)

;; Hebrew Font Code 0x90, Unicode 0xFB48
(add-character-description
  144 7 0 0 6 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2040305 #o5020610 #o4010502 #o401)
  1774)

;; Hebrew Font Code 0x91, Unicode 0xFB49
(add-character-description
  145 9 1 0 8 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o2070610 #o1050207 #o6040707 #o4040505 #o1040305 #o7001004 #o3000404 #o104)
  2419)

;; Hebrew Font Code 0x92, Unicode 0xFB4A
(add-character-description
  146 9 1 0 7 8
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o1070210 #o60110 #o4040505 #o6010710 #o2010310 #o601)
  2239)

;; Hebrew Font Code 0x93, Unicode 0xFB4B
(add-character-description
  147 3 1 0 1 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o20112 #o101)
  859)

;; Hebrew Font Code 0x94, Unicode 0xFB4C
(add-character-description
  148 7 1 0 7 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o6110712 #o110512 #o5040612 #o4030504 #o20403 #o301)
  1888)

;; Hebrew Font Code 0x95, Unicode 0xFB4D
(add-character-description
  149 6 1 0 4 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o110212 #o2100312 #o3030410 #o20303 #o301)
  1606)

;; Hebrew Font Code 0x96, Unicode 0xFB4E
(add-character-description
  150 7 1 0 6 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o110412 #o3100511 #o1060307 #o5050610 #o4040605 #o3030504 #o30106 #o20403
    #o1000401)
  1904)

;; Hebrew Font Code 0x97, Unicode 0xFB4F
(add-character-description
  151 8 1 0 6 10
  #-hebrew-bitmaps nil #+hebrew-bitmaps '#(#o5110612 #o4070511 #o70112 #o3060407 #o3050506 #o1050207 #o2030306 #o5020605
    #o1020203 #o103)
  2006)
