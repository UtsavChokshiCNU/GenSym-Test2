;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module HM14

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.



;; 40 29 16 3 9 1996 1 T 
;; 9/3/1996



(def-ab-font
  HM14	; ab-font-name
  ROMAN	; ab-font-type
  15	; ab-font-size
  12	; ab-font-baseline
  16	; ab-font-maximum-width
  18	; ab-font-maximum-height

  ;; New, for 3.1 (4.0).  (MHD 5/26/93)
  14	; ab-font-point-size
  75	; ab-font-x-resolution
  75	; ab-font-y-resolution

  15	; ab-font-width-in-x
  15	; ab-font-width-in-y
  -1	; ab-font-x-offset
  -3	; ab-font-y-offset
  )

;; Hand-edits for A, a, E, e ogonek; C, c, N, n, S, s, Z, z acute; and Z, z dot above
;; for GENSYMCID-1042 (Unability to display some polish characters)
;; -- Chun Tian (binghe), 5/22/2013

;; Aogonek [Hand-edited]

#2A((0 0 0 0 0 0 0 0 0 1 0 0 0 0)
    (0 0 0 0 0 0 1 1 1 0 0 0 0 0)
    (0 0 0 0 1 1 0 1 0 0 0 0 0 0)
    (0 1 1 1 0 0 0 1 0 0 0 0 0 0)
    (1 1 0 0 0 0 0 1 0 0 0 0 0 0)
    (0 1 1 1 0 0 0 1 0 0 0 0 0 0)
    (0 0 0 0 1 1 0 1 0 0 0 0 0 0)
    (0 0 0 0 0 0 1 1 1 0 0 1 1 0)
    (0 0 0 0 0 0 0 0 0 1 1 0 0 1))

(add-character-description
  05 11 1 -3 9 14
  '#(2150990 1880589 2134603 36938 553416 1860105 286857 1589702 540870 1315204 790788 1048898)
  2490)

;; aogonek [Hand-edited]

#2A((0 1 0 0 1 1 1 0 0 0 0)
    (1 1 0 1 1 0 1 1 0 0 0)
    (1 0 0 1 0 0 0 1 0 0 0)
    (1 0 0 1 0 0 0 1 0 0 0)
    (1 1 0 1 0 0 1 0 0 0 0)
    (0 1 1 1 1 1 1 1 0 1 1)
    (0 0 0 0 0 0 0 1 1 0 1))

(add-character-description
  06 8 1 -3 7 11
  '#(1614283 1347979 1601993 553224 1073479 286856 20551 16517 274756 1319304 1053058 4226 262465)
  2076)

;; Cacute [Hand-edited]

#2A((0 0 0 0 0 0 1 1 1 1 1 0 0 0)
    (0 0 0 0 1 1 0 0 0 0 0 1 1 0)
    (0 0 0 0 1 0 0 0 0 0 0 0 1 0)
    (0 1 0 1 0 0 0 0 0 0 0 0 0 1)
    (1 0 0 1 0 0 0 0 0 0 0 0 0 1)
    (0 0 0 1 0 0 0 0 0 0 0 0 0 1)
    (0 0 0 0 1 0 0 0 0 0 0 0 1 0)
    (0 0 0 0 1 1 0 0 0 0 0 1 1 0))

(add-character-description
  07 10 1 0 8 14
  '#(840078 1622477 573645 1880589 307341 24651 1856006 282758 1589765 278725 799108 790786
     1048897)
  2695)

;; cacute [Hand-edited]

#2A((0 0 0 0 1 1 1 1 1 1 0)
    (0 0 0 1 1 0 0 0 0 1 1)
    (0 1 0 1 0 0 0 0 0 0 1)
    (1 0 0 1 0 0 0 0 0 0 1)
    (0 0 0 1 1 0 0 0 0 1 1)
    (0 0 0 0 1 0 0 0 1 1 0))

(add-character-description
  08 8 1 0 6 11
  '#(565515 1085771 299147 1343882 20554 1065349 16517 274756 528578 786689)
  1867)

;; Eogonek [Hand-edited]

#2A((1 1 1 1 1 1 1 1 1 1 1 0 0 0)
    (1 0 0 0 0 1 0 0 0 0 1 0 0 0)
    (1 0 0 0 0 1 0 0 0 0 1 0 0 0)
    (1 0 0 0 0 1 0 0 0 0 1 0 0 0)
    (1 0 0 0 0 1 0 0 0 0 1 0 0 0)
    (1 0 0 0 0 1 0 0 0 0 1 0 1 0)
    (1 0 0 0 0 0 0 0 0 0 1 1 0 1))

(add-character-description
  09 9 1 -3 7 14
  '#(1626574 1360269 1618380 303563 283014 4171 449)
  2490)

;; eogonek [Hand-edited]

#2A((0 1 1 1 1 1 1 0 0 0 0)
    (1 1 0 1 0 0 1 1 0 0 0)
    (1 0 0 1 0 0 0 1 0 0 0)
    (1 0 0 1 0 0 0 1 0 0 0)
    (1 1 0 1 0 0 1 1 0 1 0)
    (0 1 1 1 0 0 1 1 1 0 1))

(add-character-description
  10 8 1 -3 6 11
  '#(1352075 1085770 1343881 553224 1073544 286856 274756 1319300 8263 1053058 4226 262465)
  2076)

;; Nacute [Hand-edited]

#2A((0 0 0 1 1 1 1 1 1 1 1 1 1 1)
    (0 0 0 1 0 0 0 0 0 0 0 0 0 0)
    (0 0 0 0 1 1 0 0 0 0 0 0 0 0)
    (0 1 0 0 0 0 1 1 0 0 0 0 0 0)
    (1 0 0 0 0 0 0 0 1 1 0 0 0 0)
    (0 0 0 0 0 0 0 0 0 0 1 1 0 0)
    (0 0 0 0 0 0 0 0 0 0 0 0 1 1)
    (0 0 0 1 1 1 1 1 1 1 1 1 1 1))

(add-character-description
  11 10 1 0 8 14
  '#(1622478 1352076 1081674 811272 540870 16462 1847822 12420 790786 1048897)
  2695)

;; nacute [Hand-edited]

#2A((0 0 0 1 1 1 1 1 1 1 1)
    (0 0 0 0 1 0 0 0 0 0 0)
    (0 1 0 1 0 0 0 0 0 0 0)
    (1 0 0 1 0 0 0 0 0 0 0)
    (0 0 0 1 1 0 0 0 0 0 0)
    (0 0 0 0 1 1 1 1 1 1 1))

(add-character-description
  12 8 1 0 6 11
  '#(1331595 1065349 278661 536900 12363 528578 786689)
  2076)

;; Sacute [Hand-edited]

#2A((0 0 0 0 1 1 1 0 0 0 0 1 1 0)
    (0 0 0 0 1 0 0 1 0 0 0 0 1 0)
    (0 0 0 1 0 0 0 1 0 0 0 0 0 1)
    (0 1 0 1 0 0 0 0 1 0 0 0 0 1)
    (1 0 0 1 0 0 0 0 1 0 0 0 0 1)
    (0 0 0 0 1 0 0 0 0 1 0 0 1 0)
    (0 0 0 0 1 1 0 0 0 1 1 1 1 0))

(add-character-description
  13 9 1 0 7 14
  '#(577870 1360269 311437 45133 1614285 1348042 819529 291016 1593798 20551 1327557 16517
     536900 790786 1048897)
  2490)

;; sacute [Hand-edited]

#2A((0 0 0 0 1 1 0 0 0 1 0)
    (0 0 0 1 0 0 1 0 0 0 1)
    (0 1 0 1 0 0 1 0 0 0 1)
    (1 0 0 1 0 0 1 0 0 0 1)
    (0 0 0 1 0 0 1 1 0 0 1)
    (0 0 0 0 1 0 0 1 1 1 0))

(add-character-description
  14 8 1 0 6 11
  '#(303435 36938 1343882 1077640 287047 1327493 16454 274756 528578 786689)
  1867)

;; Zacute [Hand-edited]

#2A((0 0 0 1 0 0 0 0 0 0 0 0 1 1)
    (0 0 0 1 0 0 0 0 0 0 1 1 0 1)
    (0 0 0 1 0 0 0 0 0 1 1 0 0 1)
    (0 1 0 1 0 0 0 1 1 0 0 0 0 1)
    (1 0 0 1 0 0 1 1 0 0 0 0 0 1)
    (0 0 0 1 0 1 0 0 0 0 0 0 0 1)
    (0 0 0 1 1 0 0 0 0 0 0 0 0 1))

(add-character-description
  15 9 1 0 7 14
  '#(315854 49230 303244 561355 815369 1073480 1331590 1589701 12740 790786 1048897)
  2281)

;; zacute [Hand-edited]

#2A((0 0 0 1 0 0 0 0 0 1 1)
    (0 0 0 1 0 0 0 0 1 0 1)
    (0 1 0 1 0 0 0 1 0 0 1)
    (1 0 0 1 0 0 1 0 0 0 1)
    (0 0 0 1 0 1 0 0 0 0 1)
    (0 0 0 1 1 0 0 0 0 0 1))

(add-character-description
  16 7 0 0 6 11
  '#(303499 36939 295049 553160 811271 1069382 1327493 12676 528578 786689)
  1867)

;; Zdotabove [Hand-edited]

#2A((0 0 0 1 0 0 0 0 0 0 0 0 1 1)
    (0 0 0 1 0 0 0 0 0 0 1 1 0 1)
    (0 0 0 1 0 0 0 0 0 1 1 0 0 1)
    (1 0 0 1 0 0 0 1 1 0 0 0 0 1)
    (0 0 0 1 0 0 1 1 0 0 0 0 0 1)
    (0 0 0 1 0 1 0 0 0 0 0 0 0 1)
    (0 0 0 1 1 0 0 0 0 0 0 0 0 1))

(add-character-description
  17 9 1 0 7 14
  '#(315854 49230 303244 561355 815369 1073480 1331590 1589701 12740 786689)
  2281)

;; zdotabove [Hand-edited]

#2A((0 0 0 1 0 0 0 0 0 1 1)
    (0 0 0 1 0 0 0 0 1 0 1)
    (0 0 0 1 0 0 0 1 0 0 1)
    (1 0 0 1 0 0 1 0 0 0 1)
    (0 0 0 1 0 1 0 0 0 0 1)
    (0 0 0 1 1 0 0 0 0 0 1))

(add-character-description
  18 7 0 0 6 11
  '#(303499 36939 295049 553160 811271 1069382 1327493 12676 786689)
  1867)

;; Hand-edits for U, u, O, and o double-acutes:  (MHD 8/1/98)

;; nonspacing hungarumlaut (nonspacing doubleacute)
(add-character-description
  19 5 0 8 5 3
  '#(#o2020303 #o20103 #o3010402 #o1010202 #o4000501 #o2000301)
  1243)

;; Udoubleacute (U with Hungarumlaut) [Hand-edited -- MHD, 8/1/98]
(add-character-description
  20 10 1 0 8 11
  '#(565643 1610186 299146 1847817 12361 1315202 528578 1573313 786689)
  2695)

;; uudoubleacute (u with Hungarumlaut) [Hand-edited -- MHD, 8/1/98]
(add-character-description
  21 8 1 0 6 11
  '#(565515 1085770 299147 1323403 12362 1052994 266370 1311105 524481)
  2076)

;; Odoubleacute (O with Hungarumlaut) [Hand-edited -- MHD, 8/1/98]
(add-character-description
  22 11 1 0 9 11
  '#(827787 1610186 561354 1868298 295050 2122312 24648 1856006 282758 1589765 278725 799108 1577410 790786 1835521 1048897)
  2905)

;; odoubleacute (o with Hungarumlaut) [Hand-edited -- MHD, 8/1/98]
(add-character-description
  23 8 1 0 6 11
  '#(565515 1085771 299147 1331594 20554 1065349 16517 274756 1052994 266370 1311105 524481)
  2076)

;; End hand-edits.



;; breve
(add-character-description
  24 5 0 9 5 2
  '#(#o1010402 #o4000501 #o101)
  1243)

;; caron
(add-character-description
  25 5 1 9 3 2
  '#(#o1010202 #o2000301 #o101)
  1243)

;; circumflex
(add-character-description
  26 5 1 9 3 2
  '#(#o2010302 #o10102 #o1000201)
  1243)

;; dotaccent
(add-character-description
  27 4 1 9 2 1
  '#(#o201)
  1243)

;; hungarumlaut
(add-character-description
  28 5 0 8 5 3
  '#(#o2020303 #o20103 #o3010402 #o1010202 #o4000501 #o2000301)
  1243)

;; ogonek
(add-character-description
  29 5 2 -3 3 3
  '#(#o1020303 #o10103 #o1000201)
  1243)

;; ring
(add-character-description
  30 5 0 8 4 3
  '#(#o1020303 #o3010402 #o10102 #o1000301)
  1243)

;; tilde
(add-character-description
  31 5 0 9 5 2
  '#(#o2010402 #o10102 #o4000501 #o1000301)
  1243)

;;  
(add-character-description
  32 4 0 0 1 1
  '#()
  1038)

;; !
(add-character-description
  33 4 2 0 1 11
  '#(#o110113 #o110)
  1038)

;; "
(add-character-description
  34 5 1 8 3 3
  '#(#o2000303 #o103)
  1325)

;; #
(add-character-description
  35 8 0 0 7 10
  '#(#o1070212 #o5060607 #o3060412 #o60207 #o2040307 #o6030704 #o4030507 #o1030304
    #o5000604 #o3000404)
  2076)

;; $
(add-character-description
  36 8 0 -2 7 14
  '#(#o4130614 #o1130314 #o110113 #o6100713 #o5070610 #o4060507 #o2060307 #o1050206
    #o6030705 #o30105 #o4020603 #o1020303 #o3000416)
  2076)

;; %
(add-character-description
  37 12 0 0 11 11
  '#(#o7121213 #o2120313 #o12101312 #o6100712 #o3100412 #o7071210 #o4060510 #o5050606
    #o6030705 #o1030404 #o7011003 #o4010503 #o10103 #o10001101 #o1000401)
  3319)

;; &
(add-character-description
  38 10 1 0 8 10
  '#(#o7111012 #o1110412 #o6100711 #o4100511 #o5070610 #o4060507 #o60111 #o6050707
    #o3050406 #o1050206 #o2040305 #o2030404 #o4010503 #o1010203 #o2000401)
  2490)

;; '
(add-character-description
  39 3 1 8 1 3
  '#(#o103)
  713)

;; (
(add-character-description
  40 5 1 -3 3 14
  '#(#o2150316 #o1130215 #o30113 #o1010203 #o2000301)
  1243)

;; )
(add-character-description
  41 5 1 -3 3 14
  '#(#o150116 #o1130215 #o2030313 #o1010203 #o101)
  1243)

;; *
(add-character-description
  42 7 1 6 5 5
  '#(#o4030504 #o30104 #o3020403 #o1020203 #o4010502 #o10102 #o2000305)
  1452)

;; +
(add-character-description
  43 9 1 1 7 7
  '#(#o4030704 #o30304 #o3000407)
  2180)

;; ,
(add-character-description
  44 3 0 -2 2 4
  '#(#o30104 #o1000203)
  1038)

;; -
(add-character-description
  45 5 0 4 4 1
  '#(#o401)
  1243)

;; .
(add-character-description
  46 3 1 0 1 2
  '#(#o102)
  1038)

;; /
(add-character-description
  47 4 0 0 4 11
  '#(#o100113 #o1050210 #o2020305 #o3000402)
  1038)

;; 0
(add-character-description
  48 8 1 0 6 10
  '#(#o1110512 #o5010611 #o10111 #o1000501)
  2076)

;; 1
(add-character-description
  49 8 2 0 3 10
  '#(#o10202 #o2000312)
  2076)

;; 2
(add-character-description
  50 8 1 0 6 10
  '#(#o1110612 #o70112 #o1060207 #o2050306 #o3040405 #o4030504 #o5010603 #o10103
    #o1000501)
  2076)

;; 3
(add-character-description
  51 8 1 0 6 10
  '#(#o110512 #o5050611 #o2040505 #o5010604 #o501)
  2076)

;; 4
(add-character-description
  52 8 1 0 7 10
  '#(#o6060707 #o1060507 #o40107 #o1030204 #o2020303 #o5010612 #o3010402 #o4000601)
  2076)

;; 5
(add-character-description
  53 8 1 0 6 10
  '#(#o1110512 #o70111 #o5040611 #o1030504 #o10104 #o601)
  2076)

;; 6
(add-character-description
  54 8 1 0 6 10
  '#(#o1110512 #o5050611 #o1050206 #o2040505 #o10111 #o1000501)
  2076)

;; 7
(add-character-description
  55 8 1 0 6 10
  '#(#o1100212 #o2060310 #o3040406 #o4020504 #o5010602 #o601)
  2076)

;; 8
(add-character-description
  56 8 1 0 6 10
  '#(#o1110512 #o5050611 #o50111 #o1040505 #o5010604 #o10104 #o1000501)
  2076)

;; 9
(add-character-description
  57 8 1 0 6 10
  '#(#o1110512 #o1050506 #o5010611 #o10105 #o1000501)
  2076)

;; :
(add-character-description
  58 3 1 0 1 8
  '#(#o60110 #o102)
  1038)

;; ;
(add-character-description
  59 4 0 -2 2 10
  '#(#o110112 #o1060211 #o1000202)
  1038)

;; <
(add-character-description
  60 8 1 2 6 5
  '#(#o4040605 #o2030404 #o20203 #o2010402 #o4000601)
  2180)

;; =
(add-character-description
  61 9 1 3 6 3
  '#(#o20603 #o601)
  2180)

;; >
(add-character-description
  62 8 1 2 6 5
  '#(#o40205 #o2030404 #o4020603 #o2010402 #o201)
  2180)

;; ?
(add-character-description
  63 8 1 0 6 11
  '#(#o2110313 #o2070310 #o3060407 #o4050506 #o5020605 #o20104 #o4010602 #o10202
    #o2000401)
  2076)

;; @
(add-character-description
  64 13 1 -1 11 12
  '#(#o3131014 #o10121113 #o2120313 #o1110213 #o10101111 #o4100611 #o11071210 #o6070710
    #o3050410 #o7041011 #o4040505 #o40111 #o10031104 #o5030704 #o12021307 #o1020204
    #o10011202 #o2010402 #o4001001)
  3789)

;; A
(add-character-description
  65 11 1 0 9 11
  '#(#o10111113 #o110113 #o2070710 #o7061011 #o1060211 #o6040706 #o2040306 #o5010604
    #o3010404 #o4000502)
  2490)

;; B
(add-character-description
  66 9 1 0 7 11
  '#(#o1120613 #o6060712 #o1050606 #o6020705 #o5010702 #o10113 #o601)
  2490)

;; C
(add-character-description
  67 10 1 0 8 11
  '#(#o3120613 #o6110712 #o2110312 #o7101012 #o1100212 #o30110 #o7021003 #o1020203
    #o6011002 #o1010302 #o3000601)
  2695)

;; D
(add-character-description
  68 10 1 0 8 11
  '#(#o1120513 #o5110612 #o6100712 #o7031010 #o6020703 #o5010702 #o10113 #o501)
  2695)

;; E
(add-character-description
  69 9 1 0 7 11
  '#(#o1120713 #o1050606 #o10113 #o701)
  2490)

;; F
(add-character-description
  70 9 1 0 7 11
  '#(#o1050606 #o10113 #o701)
  2281)

;; G
(add-character-description
  71 11 1 0 9 11
  '#(#o3120613 #o6111012 #o2110312 #o1100212 #o10061113 #o5051106 #o30110 #o10021103
    #o1020203 #o7011102 #o1010302 #o3000701)
  2905)

;; H
(add-character-description
  72 10 1 0 8 11
  '#(#o1050706 #o7001013 #o113)
  2695)

;; I
(add-character-description
  73 5 2 0 1 11
  '#(#o113)
  1038)

;; J
(add-character-description
  74 8 1 0 6 11
  '#(#o1120513 #o100112 #o5000612)
  1867)

;; K
(add-character-description
  75 10 1 0 8 11
  '#(#o7121013 #o6110712 #o5100611 #o4070510 #o3060407 #o1050206 #o2040306 #o3030404
    #o4020503 #o5010602 #o6000701 #o113)
  2490)

;; L
(add-character-description
  76 8 1 0 6 11
  '#(#o1120613 #o113)
  2076)

;; M
(add-character-description
  77 13 1 0 11 11
  '#(#o5110613 #o6070711 #o4070511 #o7051007 #o3050407 #o10031105 #o2030305 #o11011203
    #o1010203 #o12001313 #o113)
  3110)

;; N
(add-character-description
  78 10 1 0 8 11
  '#(#o6110713 #o5070611 #o4050507 #o3030405 #o2010303 #o10113 #o7001013 #o201)
  2695)

;; O
(add-character-description
  79 11 1 0 9 11
  '#(#o3120613 #o6110712 #o2110312 #o7101012 #o1100212 #o10031110 #o30110 #o7021003
    #o1020203 #o6011002 #o1010302 #o3000601)
  2905)

;; P
(add-character-description
  80 9 1 0 7 11
  '#(#o1050506 #o5040606 #o6020705 #o5010702 #o10113 #o601)
  2490)

;; Q
(add-character-description
  81 11 1 0 9 11
  '#(#o10121113 #o3120613 #o2110312 #o6101012 #o1100212 #o5070610 #o4060507 #o10031110
    #o30110 #o7021003 #o1020203 #o6011002 #o1010302 #o3000601)
  2905)

;; R
(add-character-description
  82 9 1 0 7 11
  '#(#o6070713 #o5060607 #o1050506 #o5040605 #o6020704 #o5010702 #o10113 #o601)
  2695)

;; S
(add-character-description
  83 9 1 0 7 11
  '#(#o2120513 #o5110612 #o1110212 #o100112 #o6070712 #o5060707 #o3050506 #o1040305
    #o6020703 #o20104 #o5010702 #o10202 #o2000501)
  2490)

;; T
(add-character-description
  84 9 0 0 9 11
  '#(#o4010513 #o1101)
  2281)

;; U
(add-character-description
  85 10 1 0 8 11
  '#(#o2120613 #o6110712 #o1110212 #o7001011 #o111)
  2695)

;; V
(add-character-description
  86 11 1 0 9 11
  '#(#o4110513 #o5070611 #o3070411 #o6040707 #o2040307 #o7021005 #o1020205 #o10001102
    #o102)
  2490)

;; W
(add-character-description
  87 15 1 0 13 11
  '#(#o11111213 #o3110413 #o12061311 #o10061111 #o4060511 #o2060311 #o13031406 #o1030206
    #o7021006 #o5020606 #o14001503 #o6000702 #o103)
  3524)

;; X
(add-character-description
  88 10 1 0 8 11
  '#(#o7111013 #o110113 #o6070712 #o1070212 #o5060610 #o2060310 #o3040506 #o5020604
    #o2020304 #o6010703 #o1010203 #o7001002 #o102)
  2490)

;; Y
(add-character-description
  89 9 0 0 9 11
  '#(#o4060513 #o5050607 #o3050407 #o6030705 #o2030305 #o7011003 #o1010203 #o10001102
    #o102)
  2490)

;; Z
(add-character-description
  90 9 1 0 7 11
  '#(#o1120713 #o110113 #o1070211 #o2060310 #o3040406 #o4030505 #o5020603 #o6010702
    #o701)
  2281)

;; [
(add-character-description
  91 4 1 -3 3 14
  '#(#o1150316 #o10116 #o301)
  1038)

;; \
(add-character-description
  92 4 0 0 4 11
  '#(#o3100413 #o2050310 #o1020205 #o102)
  1038)

;; ]
(add-character-description
  93 4 0 -3 3 14
  '#(#o150216 #o2010316 #o301)
  1038)

;; ^
(add-character-description
  94 7 1 8 5 3
  '#(#o4020503 #o20103 #o3010402 #o1010202 #o2000301)
  1751)

;; _
(add-character-description
  95 8 0 -3 8 1
  '#(#o1001)
  2076)

;; `
(add-character-description
  96 5 1 9 2 2
  '#(#o1010202 #o101)
  1243)

;; a
(add-character-description
  97 8 1 0 7 8
  '#(#o6070710 #o2070410 #o4060507 #o1060210 #o50107 #o40205 #o1030504 #o5020610
    #o4010602 #o10202 #o1000501)
  2076)

;; b
(add-character-description
  98 8 1 0 6 11
  '#(#o2120413 #o4110513 #o1110212 #o5050612 #o4040605 #o1040205 #o2030504 #o113)
  2076)

;; c
(add-character-description
  99 8 1 0 6 8
  '#(#o2070410 #o4060510 #o1060210 #o5050607 #o20107 #o4010602 #o10202 #o1000501)
  1867)

;; d
(add-character-description
  100 8 1 0 6 11
  '#(#o2120413 #o4110512 #o1110213 #o50112 #o4040505 #o40205 #o1030404 #o5000613)
  2076)

;; e
(add-character-description
  101 8 1 0 6 8
  '#(#o2070510 #o4060607 #o1060210 #o1030504 #o5020604 #o20107 #o4010602 #o10202
    #o1000501)
  2076)

;; f
(add-character-description
  102 3 0 0 4 11
  '#(#o2030304 #o30104 #o1010213 #o2000401)
  1038)

;; g
(add-character-description
  103 8 1 -3 6 11
  '#(#o1120413 #o4110513 #o110212 #o2070410 #o4060507 #o1060210 #o20107 #o4010502
    #o10202 #o5000612 #o1000401)
  2076)

;; h
(add-character-description
  104 8 1 0 6 11
  '#(#o5050613 #o4040605 #o1040205 #o2030504 #o113)
  2076)

;; i
(add-character-description
  105 3 1 0 1 11
  '#(#o30113 #o102)
  829)

;; j
(add-character-description
  106 3 -1 -3 3 14
  '#(#o150216 #o2030315 #o2000302)
  829)

;; k
(add-character-description
  107 7 1 0 6 11
  '#(#o5120613 #o4110512 #o3100411 #o2070310 #o1060207 #o2050306 #o3040405 #o4030504
    #o113)
  1867)

;; l
(add-character-description
  108 3 1 0 1 11
  '#(#o113)
  829)

;; m
(add-character-description
  109 11 1 0 9 8
  '#(#o4020510 #o10011110 #o4010602 #o1010202 #o6001001 #o2000401 #o110)
  3110)

;; n
(add-character-description
  110 8 1 0 6 8
  '#(#o5020610 #o4010602 #o1010202 #o2000501 #o110)
  2076)

;; o
(add-character-description
  111 8 1 0 6 8
  '#(#o2070410 #o4060510 #o1060210 #o5020607 #o20107 #o4010602 #o10202 #o1000501)
  2076)

;; p
(add-character-description
  112 8 1 -3 6 11
  '#(#o2070410 #o4060510 #o1060207 #o5020607 #o4010602 #o1010202 #o2000501 #o113)
  2076)

;; q
(add-character-description
  113 8 1 -3 6 11
  '#(#o2070410 #o4060507 #o1060210 #o20107 #o4010502 #o10202 #o5000613 #o1000401)
  2076)

;; r
(add-character-description
  114 5 1 0 4 8
  '#(#o1010202 #o2000401 #o110)
  1243)

;; s
(add-character-description
  115 8 1 0 6 8
  '#(#o1070510 #o60107 #o5050607 #o4040605 #o1030504 #o5010602 #o10103 #o1000501)
  1867)

;; t
(add-character-description
  116 4 0 0 4 10
  '#(#o2110412 #o2020303 #o20103 #o1000211)
  1038)

;; u
(add-character-description
  117 8 1 0 6 8
  '#(#o2070410 #o4060507 #o1060210 #o5000610 #o107)
  2076)

;; v
(add-character-description
  118 8 1 0 6 8
  '#(#o2060410 #o4030506 #o1030206 #o5000603 #o103)
  1867)

;; w
(add-character-description
  119 9 0 0 9 8
  '#(#o6060710 #o2060310 #o5050606 #o3050406 #o7031006 #o1030206 #o10001103 #o4000505
    #o103)
  2695)

;; x
(add-character-description
  120 7 0 0 7 8
  '#(#o6070710 #o70110 #o5060610 #o1060210 #o4050506 #o2050306 #o3030405 #o4020503
    #o2020303 #o5010602 #o1010202 #o5000701 #o201)
  1867)

;; y
(add-character-description
  121 7 0 -3 7 11
  '#(#o1120213 #o2110313 #o3060412 #o4050507 #o2040306 #o5020605 #o1010204 #o6000702
    #o102)
  1867)

;; z
(add-character-description
  122 7 0 0 6 8
  '#(#o1070610 #o60110 #o1050206 #o2040305 #o3030404 #o4020503 #o5010602 #o601)
  1867)

;; {
(add-character-description
  123 5 0 -3 5 14
  '#(#o3150516 #o2100315 #o1070210 #o60107 #o1050206 #o2010305 #o3000501)
  1247)

;; |
(add-character-description
  124 3 1 -3 1 14
  '#(#o116)
  971)

;; }
(add-character-description
  125 5 0 -3 5 14
  '#(#o150216 #o2100315 #o3070410 #o4060507 #o3050406 #o2010305 #o201)
  1247)

;; ~
(add-character-description
  126 8 1 3 6 3
  '#(#o3020503 #o2010402 #o10103 #o5000602 #o1000301)
  2180)

;; bullet
(add-character-description
  128 5 1 3 3 4
  '#(#o2010303 #o10103 #o1000204)
  1307)

;; dagger
(add-character-description
  129 8 0 -3 7 14
  '#(#o4040705 #o40305 #o3000416)
  2076)

;; daggerdbl
(add-character-description
  130 8 0 -3 7 14
  '#(#o4110712 #o110312 #o4040705 #o40305 #o3000416)
  2076)

;; ellipsis
(add-character-description
  131 15 1 0 12 1
  '#(#o12001401 #o5000701 #o201)
  3733)

;; emdash
(add-character-description
  132 14 0 4 14 1
  '#(#o1601)
  3733)

;; endash
(add-character-description
  133 8 0 4 8 1
  '#(#o1001)
  2076)

;; florin
(add-character-description
  134 8 0 -3 8 13
  '#(#o140215 #o2110314 #o3040411 #o5030704 #o1030404 #o4010504 #o5001001)
  2076)

;; fraction
(add-character-description
  135 3 -1 0 5 10
  '#(#o100112 #o1060210 #o2040306 #o3020404 #o4000502)
  623)

;; guilsinglleft
(add-character-description
  136 5 1 2 3 5
  '#(#o2040305 #o1030204 #o20103 #o1010202 #o2000301)
  1243)

;; guilsinglright
(add-character-description
  137 5 1 2 3 5
  '#(#o40105 #o1030204 #o2020303 #o1010202 #o101)
  1243)

;; minus
(add-character-description
  138 9 1 4 7 1
  '#(#o701)
  2262)

;; perthousand
(add-character-description
  139 13 1 0 11 11
  '#(#o10121213 #o5120713 #o1120213 #o12101312 #o7101012 #o4100512 #o2100312 #o10071210
    #o5070710 #o3060410 #o4050506 #o1040305 #o5030605 #o3020404 #o20104 #o6010703
    #o1010302 #o7001001)
  3733)

;; quotedblbase
(add-character-description
  140 5 0 -2 5 3
  '#(#o3020403 #o20103 #o4010502 #o1010202 #o3000501 #o201)
  1243)

;; quotedblleft
(add-character-description
  141 6 0 8 5 3
  '#(#o4020503 #o1020203 #o3010403 #o10103 #o4000501 #o1000201)
  1243)

;; quotedblright
(add-character-description
  142 6 1 8 5 3
  '#(#o3020403 #o20103 #o4010502 #o1010202 #o3000501 #o201)
  1243)

;; quoteleft
(add-character-description
  143 3 0 8 2 3
  '#(#o1020203 #o10103 #o1000201)
  829)

;; quoteright
(add-character-description
  144 3 1 8 2 3
  '#(#o20103 #o1010202 #o201)
  829)

;; quotesinglbase
(add-character-description
  145 3 1 -2 2 3
  '#(#o20103 #o1010202 #o201)
  829)

;; trademark
(add-character-description
  146 13 1 4 11 6
  '#(#o10021106 #o11011202 #o7011002 #o2010306 #o12001306 #o6000706 #o501)
  3214)

;; fi
(add-character-description
  147 6 0 0 5 11
  '#(#o4030513 #o2030304 #o30104 #o1010213 #o2000501)
  1867)

;; fl
(add-character-description
  148 6 0 0 5 11
  '#(#o2030304 #o30104 #o4010513 #o1010213 #o2000501)
  1867)

;; Lslash
(add-character-description
  149 9 0 0 8 11
  '#(#o3121013 #o60107 #o1050206 #o3040405 #o4030504 #o2000313)
  2076)

;; OE
(add-character-description
  150 15 1 0 13 11
  '#(#o10121513 #o3120613 #o6110713 #o2110312 #o1100212 #o10051506 #o30110 #o7021013
    #o1020203 #o6011002 #o1010302 #o3001501)
  3733)

;; Scaron
(add-character-description
  151 9 1 0 7 11
  '#(#o1120613 #o110112 #o6070712 #o1060607 #o6040705 #o40106 #o1030604 #o3010402
    #o4000501 #o2000301)
  2490)

;; Ydieresis
(add-character-description
  152 9 1 0 7 11
  '#(#o3070413 #o4060507 #o2060307 #o5040606 #o1040206 #o6030704 #o30104 #o4000601
    #o1000301)
  2490)

;; Zcaron
(add-character-description
  153 9 1 0 7 11
  '#(#o1120713 #o110113 #o1100211 #o2070310 #o3060407 #o4050506 #o5040605 #o1030704
    #o3010402 #o4000501 #o2000301)
  2281)

;; dotlessi
(add-character-description
  154 3 1 0 1 8
  '#(#o110)
  1038)

;; lslash
(add-character-description
  155 3 0 0 3 11
  '#(#o50106 #o2040305 #o1000213)
  829)

;; oe
(add-character-description
  156 13 1 0 11 8
  '#(#o7071210 #o2070410 #o11061307 #o6060710 #o4060510 #o1060210 #o6031204 #o12021304
    #o5020607 #o20107 #o11011302 #o4010702 #o10202 #o6001201 #o1000501)
  3524)

;; scaron
(add-character-description
  157 8 1 0 6 11
  '#(#o1120513 #o110112 #o5100612 #o4070610 #o1060507 #o5040605 #o40106 #o1030504
    #o2010302 #o3000401 #o1000201)
  1867)

;; zcaron
(add-character-description
  158 7 0 0 6 11
  '#(#o1120613 #o110113 #o1100211 #o2070310 #o3060407 #o4050506 #o5040605 #o30604
    #o2010302 #o3000401 #o1000201)
  1867)

;; exclamdown
(add-character-description
  161 4 1 -3 1 11
  '#(#o30113 #o102)
  1243)

;; cent
(add-character-description
  162 8 1 -1 6 10
  '#(#o110112 #o2100411 #o4070511 #o1070211 #o5060610 #o2050307 #o3030405 #o30110
    #o4020603 #o20203 #o1010502 #o5000601)
  2076)

;; sterling
(add-character-description
  163 8 0 0 7 10
  '#(#o3110512 #o110112 #o5100612 #o2100311 #o6070711 #o1070212 #o3040505 #o40205
    #o2030307 #o5010602 #o1010203 #o2000501)
  2076)

;; currency
(add-character-description
  164 8 1 2 6 6
  '#(#o5050606 #o50106 #o2040405 #o4020505 #o1020205 #o1010502 #o5000601 #o101)
  2076)

;; yen
(add-character-description
  165 7 0 0 7 10
  '#(#o4070710 #o70310 #o5050706 #o3050412 #o50206 #o4040506 #o2040306 #o5020604
    #o1020204 #o6000702 #o102)
  2076)

;; brokenbar
(add-character-description
  166 3 1 -3 1 14
  '#(#o100116 #o106)
  971)

;; section
(add-character-description
  167 8 2 -3 5 14
  '#(#o2150316 #o3140416 #o1140216 #o4130515 #o130115 #o3120513 #o2110412 #o1100212
    #o4060511 #o3050506 #o50111 #o2040405 #o1030205 #o4020503 #o20104 #o3010502
    #o10202 #o1000401)
  2076)

;; dieresis
(add-character-description
  168 5 0 9 5 1
  '#(#o3000501 #o201)
  1243)

;; copyright
(add-character-description
  169 12 1 0 10 10
  '#(#o3110712 #o7101011 #o2100311 #o10071111 #o4070610 #o1070211 #o6060707 #o11031207
    #o6030704 #o3030407 #o30107 #o10021103 #o4020603 #o1020203 #o7011102 #o1010302
    #o3000701)
  2789)

;; ordfeminine
(add-character-description
  170 6 1 4 4 7
  '#(#o60407 #o1040205 #o30105 #o1020303 #o3010405 #o301)
  1381)

;; guillemotleft
(add-character-description
  171 8 1 2 6 5
  '#(#o5040605 #o2040305 #o4030504 #o1030204 #o3020403 #o20103 #o4010502 #o1010202
    #o5000601 #o2000301)
  2076)

;; logicalnot
(add-character-description
  172 9 1 3 7 4
  '#(#o6010704 #o701)
  2262)

;; registered
(add-character-description
  174 12 1 0 10 10
  '#(#o3110712 #o7101011 #o2100311 #o10071111 #o1070211 #o6060710 #o4050606 #o11031207
    #o6030705 #o3030410 #o30107 #o10021103 #o3020603 #o1020203 #o7011102 #o1010302
    #o3000701)
  2789)

;; macron
(add-character-description
  175 4 0 9 4 1
  '#(#o401)
  1243)

;; degree
(add-character-description
  176 6 1 6 4 4
  '#(#o1030304 #o3010403 #o10103 #o1000301)
  1493)

;; plusminus
(add-character-description
  177 9 1 0 7 9
  '#(#o100711 #o4030704 #o30304 #o3000407)
  2180)

;; twosuperior
(add-character-description
  178 5 0 4 4 6
  '#(#o2050406 #o50106 #o1040206 #o2030304 #o3010403 #o10102 #o1000301)
  2076)

;; threesuperior
(add-character-description
  179 5 0 4 4 6
  '#(#o1050306 #o40105 #o3030405 #o2020303 #o3010402 #o10102 #o1000301)
  2076)

;; acute
(add-character-description
  180 5 2 9 2 2
  '#(#o10102 #o1000201)
  1243)

;; mu
(add-character-description
  181 8 1 -3 6 11
  '#(#o2070410 #o4060507 #o1060207 #o5000610 #o113)
  2076)

;; paragraph
(add-character-description
  182 8 0 -3 7 14
  '#(#o3070416 #o2060407 #o20105 #o5010616 #o1010406 #o2000701)
  2005)

;; periodcentered
(add-character-description
  183 4 1 4 2 1
  '#(#o201)
  1038)

;; cedilla
(add-character-description
  184 5 0 -3 4 3
  '#(#o1020303 #o3010402 #o10102 #o2000301)
  1243)

;; onesuperior
(add-character-description
  185 5 1 4 2 6
  '#(#o10102 #o1000206)
  2076)

;; ordmasculine
(add-character-description
  186 6 1 4 4 7
  '#(#o60407 #o1040305 #o3010404 #o10104 #o1000301)
  1363)

;; guillemotright
(add-character-description
  187 8 1 2 6 5
  '#(#o3040405 #o40105 #o4030504 #o1030204 #o5020603 #o2020303 #o4010502 #o1010202
    #o3000401 #o101)
  2076)

;; onequarter
(add-character-description
  188 12 1 0 10 10
  '#(#o11101211 #o6101011 #o2100312 #o5070611 #o6060707 #o3060410 #o7051006 #o10041112
    #o4040506 #o5020604 #o10102 #o6000702 #o1000206)
  623)

;; onehalf
(add-character-description
  189 12 1 0 9 10
  '#(#o7111112 #o5110612 #o6100712 #o2100312 #o7071010 #o3060410 #o10051107 #o5050606
    #o6041005 #o4040506 #o5020604 #o10102 #o6000702 #o1000206)
  623)

;; threequarters
(add-character-description
  190 12 0 0 11 10
  '#(#o12101311 #o7101111 #o3100412 #o6070711 #o7061007 #o4060510 #o10051106 #o1050306
    #o11041212 #o5040606 #o40105 #o3030405 #o6020704 #o2020303 #o3010402 #o10102
    #o7001002 #o1000301)
  623)

;; questiondown
(add-character-description
  191 8 1 -3 6 11
  '#(#o2120413 #o4110512 #o1110212 #o5070612 #o60112 #o1050206 #o2040305 #o3030404
    #o3000402)
  2281)

;; Agrave
(add-character-description
  192 11 1 0 9 11
  '#(#o10111113 #o110113 #o7071011 #o3070610 #o1070211 #o6060710 #o2060310 #o5040606
    #o3040406 #o4030505 #o4010502 #o3000401)
  2490)

;; Aacute
(add-character-description
  193 11 1 0 9 11
  '#(#o10111113 #o110113 #o7071011 #o3070610 #o1070211 #o6060710 #o2060310 #o5040606
    #o3040406 #o4030505 #o4010502 #o5000601)
  2490)

;; Acircumflex
(add-character-description
  194 11 1 0 9 11
  '#(#o10111113 #o110113 #o7071011 #o3070610 #o1070211 #o6060710 #o2060310 #o5040606
    #o3040406 #o4030505 #o5010602 #o3010402 #o4000501)
  2490)

;; Atilde
(add-character-description
  195 11 1 0 9 11
  '#(#o10111113 #o110113 #o7071011 #o3070610 #o1070211 #o6060710 #o2060310 #o5040606
    #o3040406 #o4030505 #o4010602 #o2010302 #o6000701 #o3000501)
  2490)

;; Adieresis
(add-character-description
  196 11 1 0 9 11
  '#(#o10111113 #o110113 #o7071011 #o3070610 #o1070211 #o6060710 #o2060310 #o5040606
    #o3040406 #o4030505 #o5000701 #o2000401)
  2490)

;; Aring
(add-character-description
  197 11 1 0 9 11
  '#(#o10111113 #o110113 #o7071011 #o3070610 #o1070211 #o6060710 #o2060310 #o5040606
    #o3040406 #o4030505 #o3020503 #o5010602 #o2010302 #o3000501)
  2490)

;; AE
(add-character-description
  198 14 1 0 12 11
  '#(#o6121413 #o110113 #o2070510 #o1060211 #o6051306 #o2040306 #o5020613 #o3020404
    #o3010602 #o4001401)
  3733)

;; Ccedilla
(add-character-description
  199 10 1 -3 8 14
  '#(#o3150516 #o5140615 #o2140315 #o4130514 #o3120613 #o6110712 #o2110312 #o7101012
    #o1100212 #o30110 #o7021003 #o1020203 #o6011002 #o1010302 #o3000601)
  2695)

;; Egrave
(add-character-description
  200 9 1 0 7 11
  '#(#o1120713 #o1060707 #o40113 #o30704 #o3010402 #o2000301)
  2490)

;; Eacute
(add-character-description
  201 9 1 0 7 11
  '#(#o1120713 #o1060707 #o40113 #o30704 #o2010302 #o3000401)
  2490)

;; Ecircumflex
(add-character-description
  202 9 1 0 7 11
  '#(#o1120713 #o1060707 #o40113 #o30704 #o4010502 #o2010302 #o3000401)
  2490)

;; Edieresis
(add-character-description
  203 9 1 0 7 11
  '#(#o1120713 #o1060707 #o40113 #o30704 #o4000601 #o1000301)
  2490)

;; Igrave
(add-character-description
  204 5 1 0 2 11
  '#(#o1030213 #o1010202 #o101)
  1038)

;; Iacute
(add-character-description
  205 5 2 0 2 11
  '#(#o30113 #o10102 #o1000201)
  1038)

;; Icircumflex
(add-character-description
  206 5 1 0 3 11
  '#(#o1030213 #o2010302 #o10102 #o1000201)
  1038)

;; Idieresis
(add-character-description
  207 5 1 0 3 11
  '#(#o1030213 #o2000301 #o101)
  1038)

;; Eth
(add-character-description
  208 10 0 0 9 11
  '#(#o2120613 #o6110712 #o7101012 #o2050406 #o50106 #o10031110 #o7021003 #o6011002
    #o1010213 #o1000601)
  2695)

;; Ntilde
(add-character-description
  209 10 1 0 8 11
  '#(#o6110713 #o5100611 #o4070510 #o3060407 #o2050306 #o50113 #o7031013 #o30205
    #o3010502 #o1010202 #o5000601 #o2000401)
  2695)

;; Ograve
(add-character-description
  210 11 1 0 9 11
  '#(#o3120613 #o6110712 #o2110312 #o7101012 #o1100212 #o10061110 #o60110 #o7051006
    #o1050206 #o6041005 #o1040305 #o3030604 #o4010502 #o3000401)
  2905)

;; Oacute
(add-character-description
  211 11 1 0 9 11
  '#(#o3120613 #o6110712 #o2110312 #o7101012 #o1100212 #o10061110 #o60110 #o7051006
    #o1050206 #o6041005 #o1040305 #o3030604 #o4010502 #o5000601)
  2905)

;; Ocircumflex
(add-character-description
  212 11 1 0 9 11
  '#(#o3120613 #o6110712 #o2110312 #o7101012 #o1100212 #o10061110 #o60110 #o7051006
    #o1050206 #o6041005 #o1040305 #o3030604 #o5010602 #o3010402 #o4000501)
  2905)

;; Otilde
(add-character-description
  213 11 1 0 9 11
  '#(#o3120613 #o6110712 #o2110312 #o7101012 #o1100212 #o10061110 #o60110 #o7051006
    #o1050206 #o6041005 #o1040305 #o3030604 #o4010602 #o2010302 #o6000701 #o3000501)
  2905)

;; Odieresis
(add-character-description
  214 11 1 0 9 11
  '#(#o3120613 #o6110712 #o2110312 #o7101012 #o1100212 #o10061110 #o60110 #o7051006
    #o1050206 #o6041005 #o1040305 #o3030604 #o5000701 #o2000401)
  2905)

;; multiply
(add-character-description
  215 9 1 1 7 7
  '#(#o6060707 #o60107 #o5050606 #o1050206 #o4040505 #o2040305 #o3030404 #o4020503
    #o2020303 #o5010602 #o1010202 #o6000701 #o101)
  2180)

;; Oslash
(add-character-description
  216 11 0 0 11 11
  '#(#o4120713 #o120113 #o7111012 #o3110412 #o1110212 #o10101112 #o2100312 #o3070410
    #o4060507 #o5050606 #o6040705 #o11031210 #o7031004 #o1030210 #o10021103 #o2020303
    #o7011202 #o2010402 #o12001301 #o4000701)
  2905)

;; Ugrave
(add-character-description
  217 10 1 0 8 11
  '#(#o2120613 #o6110712 #o1110212 #o7031011 #o30111 #o4010502 #o3000401)
  2695)

;; Uacute
(add-character-description
  218 10 1 0 8 11
  '#(#o2120613 #o6110712 #o1110212 #o7031011 #o30111 #o3010402 #o4000501)
  2695)

;; Ucircumflex
(add-character-description
  219 10 1 0 8 11
  '#(#o2120613 #o6110712 #o1110212 #o7031011 #o30111 #o4010502 #o2010302 #o3000401)
  2695)

;; Udieresis
(add-character-description
  220 10 1 0 8 11
  '#(#o2120613 #o6110712 #o1110212 #o7031011 #o30111 #o4000601 #o1000301)
  2695)

;; Yacute
(add-character-description
  221 9 1 0 7 11
  '#(#o3070413 #o4060507 #o2060307 #o5040606 #o1040206 #o6030704 #o30104 #o3010402
    #o4000501)
  2490)

;; Thorn
(add-character-description
  222 9 1 0 7 11
  '#(#o1070510 #o5060610 #o6040707 #o5030704 #o1020603 #o113)
  2490)

;; germandbls
(add-character-description
  223 7 1 0 5 11
  '#(#o2120413 #o4060512 #o3050406 #o2040405 #o4010504 #o10113 #o1000401)
  2281)

;; agrave
(add-character-description
  224 8 1 0 7 11
  '#(#o6120713 #o2120413 #o4110512 #o1110213 #o100112 #o70210 #o1060507 #o5050613
    #o4040605 #o40205 #o1030504 #o3010402 #o2000301)
  2076)

;; aacute
(add-character-description
  225 8 1 0 7 11
  '#(#o6120713 #o2120413 #o4110512 #o1110213 #o100112 #o70210 #o1060507 #o5050613
    #o4040605 #o40205 #o1030504 #o2010302 #o3000401)
  2076)

;; acircumflex
(add-character-description
  226 8 1 0 7 11
  '#(#o6120713 #o2120413 #o4110512 #o1110213 #o100112 #o70210 #o1060507 #o5050613
    #o4040605 #o40205 #o1030504 #o4010502 #o2010302 #o3000401)
  2076)

;; atilde
(add-character-description
  227 8 1 0 7 11
  '#(#o6120713 #o2120413 #o4110512 #o1110213 #o100112 #o70210 #o1060507 #o5050613
    #o4040605 #o40205 #o1030504 #o3010502 #o1010202 #o5000601 #o2000401)
  2076)

;; adieresis
(add-character-description
  228 8 1 0 7 10
  '#(#o6110712 #o2110412 #o4100511 #o1100212 #o70111 #o60207 #o1050506 #o5040612
    #o4030604 #o30204 #o1020503 #o4000601 #o1000301)
  2076)

;; aring
(add-character-description
  229 8 1 0 7 11
  '#(#o6120713 #o2120413 #o4110512 #o1110213 #o100112 #o70210 #o1060507 #o5040613
    #o40105 #o4030505 #o1030205 #o2020404 #o4010502 #o1010202 #o2000401)
  2076)

;; ae
(add-character-description
  230 13 1 0 11 8
  '#(#o7071210 #o2070410 #o11061307 #o6060710 #o4060510 #o1060210 #o50107 #o40205
    #o6031204 #o1030504 #o12021304 #o5020607 #o11011302 #o5010702 #o10202 #o6001201
    #o1000501)
  3319)

;; ccedilla
(add-character-description
  231 8 1 -3 6 11
  '#(#o2120413 #o4110512 #o1110212 #o3100411 #o2070410 #o4060510 #o1060210 #o5050607
    #o20107 #o4010602 #o10202 #o1000501)
  1867)

;; egrave
(add-character-description
  232 8 1 0 6 11
  '#(#o2120513 #o4110612 #o1110213 #o1060507 #o5050607 #o50112 #o4040605 #o40205
    #o1030504 #o3010402 #o2000301)
  2076)

;; eacute
(add-character-description
  233 8 1 0 6 11
  '#(#o2120513 #o4110612 #o1110213 #o1060507 #o5050607 #o50112 #o4040605 #o40205
    #o1030504 #o2010302 #o3000401)
  2076)

;; ecircumflex
(add-character-description
  234 8 1 0 6 11
  '#(#o2120513 #o4110612 #o1110213 #o1060507 #o5050607 #o50112 #o4040605 #o40205
    #o1030504 #o3010402 #o1010202 #o2000301)
  2076)

;; edieresis
(add-character-description
  235 8 1 0 6 10
  '#(#o2110512 #o4100611 #o1100212 #o1050506 #o5040606 #o40111 #o4030604 #o30204
    #o1020503 #o3000501 #o201)
  2076)

;; igrave
(add-character-description
  236 3 1 0 2 11
  '#(#o30113 #o1010202 #o101)
  1038)

;; iacute
(add-character-description
  237 3 1 0 2 11
  '#(#o30113 #o10102 #o1000201)
  1038)

;; icircumflex
(add-character-description
  238 3 0 0 3 11
  '#(#o1030213 #o2010302 #o10102 #o1000201)
  1038)

;; idieresis
(add-character-description
  239 3 0 0 3 10
  '#(#o1020212 #o2000301 #o101)
  1038)

;; eth
(add-character-description
  240 8 1 0 6 11
  '#(#o2120413 #o4110513 #o1110213 #o50112 #o5040612 #o40205 #o4030505 #o1030304
    #o3020404 #o20103 #o1010402 #o3000501 #o201)
  2076)

;; ntilde
(add-character-description
  241 8 1 0 6 11
  '#(#o5050613 #o4040605 #o1040205 #o2030504 #o30113 #o2010402 #o10102 #o4000501
    #o1000301)
  2076)

;; ograve
(add-character-description
  242 8 1 0 6 11
  '#(#o2120413 #o4110513 #o1110213 #o5050612 #o50112 #o4040605 #o40205 #o1030504
    #o3010402 #o2000301)
  2076)

;; oacute
(add-character-description
  243 8 1 0 6 11
  '#(#o2120413 #o4110513 #o1110213 #o5050612 #o50112 #o4040605 #o40205 #o1030504
    #o2010302 #o3000401)
  2076)

;; ocircumflex
(add-character-description
  244 8 1 0 6 11
  '#(#o2120413 #o4110513 #o1110213 #o5050612 #o50112 #o4040605 #o40205 #o1030504
    #o3010402 #o1010202 #o2000301)
  2076)

;; otilde
(add-character-description
  245 8 1 0 6 11
  '#(#o2120413 #o4110513 #o1110213 #o5050612 #o50112 #o4040605 #o40205 #o1030504
    #o2010402 #o10102 #o4000501 #o1000301)
  2076)

;; odieresis
(add-character-description
  246 8 1 0 6 10
  '#(#o2110412 #o4100512 #o1100212 #o5040611 #o40111 #o4030604 #o30204 #o1020503
    #o3000501 #o201)
  2076)

;; divide
(add-character-description
  247 9 1 1 7 7
  '#(#o3050407 #o30704 #o3000402)
  2180)

;; oslash
(add-character-description
  248 8 0 0 8 8
  '#(#o2070510 #o70110 #o5060610 #o2050306 #o3040405 #o4030504 #o5020603 #o1020207
    #o6010707 #o1010302 #o7001001 #o2000601)
  2281)

;; ugrave
(add-character-description
  249 8 1 0 6 11
  '#(#o2120413 #o4110512 #o1110213 #o5030613 #o30112 #o3010402 #o2000301)
  2076)

;; uacute
(add-character-description
  250 8 1 0 6 11
  '#(#o2120413 #o4110512 #o1110213 #o5030613 #o30112 #o2010302 #o3000401)
  2076)

;; ucircumflex
(add-character-description
  251 8 1 0 6 11
  '#(#o2120413 #o4110512 #o1110213 #o5030613 #o30112 #o3010402 #o1010202 #o2000301)
  2076)

;; udieresis
(add-character-description
  252 8 1 0 6 10
  '#(#o2110412 #o4100511 #o1100212 #o5020612 #o20111 #o3000501 #o201)
  2076)

;; yacute
(add-character-description
  253 7 0 -3 7 14
  '#(#o1150216 #o2140316 #o3110415 #o4100512 #o2070311 #o5050610 #o1040207 #o6030705
    #o30105 #o3010402 #o4000501)
  1867)

;; thorn
(add-character-description
  254 8 1 -3 6 14
  '#(#o2120413 #o4110513 #o1110212 #o5050612 #o4040605 #o1040205 #o2030504 #o116)
  2076)

;; ydieresis
(add-character-description
  255 7 0 -3 7 13
  '#(#o1140215 #o2130315 #o3100414 #o4070511 #o2060310 #o5040607 #o1030206 #o6020704
    #o20104 #o4000601 #o1000301)
  1867)
