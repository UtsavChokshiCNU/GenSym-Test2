;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module SLAVIC14

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.



;; 55 22 18 15 10 1999 4 T 
;; 10/15/1999



(def-ab-font
  SLAVIC14	; ab-font-name
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



;; IO
(add-character-description
  33 9 1 0 7 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1130714 #o1070710 #o30114 #o20703 #o5000601 #o1000201)
  2345)

;; DJE
(add-character-description
  34 10 0 0 9 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o5110712 #o7101011 #o10051111 #o7041105 #o3030704 #o2010312 #o601)
  2456)

;; GJE
(add-character-description
  35 8 1 0 7 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o30114 #o20703 #o3000501)
  2150)

;; E
(add-character-description
  36 10 0 0 9 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3110612 #o6100712 #o2100312 #o7071011 #o1070211 #o7061107 #o1040505 #o10031104
    #o30110 #o7021003 #o1020203 #o6011002 #o1010302 #o2000701)
  2536)

;; DZE
(add-character-description
  37 9 0 0 8 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2110612 #o6100711 #o1100211 #o70110 #o7061011 #o4050706 #o2040505 #o7031004
    #o1030205 #o6020703 #o20104 #o5010702 #o10202 #o2000601)
  2345)

;; I
(add-character-description
  38 4 1 0 1 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o112)
  986)

;; YI
(add-character-description
  39 4 0 0 3 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1020214 #o2000301 #o101)
  1063)

;; JE
(add-character-description
  40 7 0 0 6 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1110412 #o4100512 #o70111 #o5000611)
  1763)

;; LJE
(add-character-description
  41 13 0 0 12 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o7111212 #o110112 #o12101312 #o13051410 #o1050211 #o12041405 #o7031304 #o6010712
    #o2010305 #o2000701)
  3366)

;; NJE
(add-character-description
  42 14 1 0 12 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o7111212 #o12101312 #o13051410 #o12041405 #o1040605 #o7031304 #o6000712 #o112)
  3585)

;; TSHE
(add-character-description
  43 10 0 0 9 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o10051112 #o7041105 #o3030704 #o2010312 #o601)
  2456)

;; KJE
(add-character-description
  44 9 1 0 8 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o7131014 #o6120714 #o5100612 #o4070511 #o1070210 #o1060307 #o3050407 #o4040505
    #o5030604 #o6021003 #o20114 #o3010402 #o3000501)
  2345)

;; SHORT U
(add-character-description
  46 9 0 0 9 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1130314 #o3120414 #o4100512 #o5070611 #o3060411 #o6050707 #o2040307 #o7031005
    #o1030205 #o10021103 #o20203 #o3000701)
  2352)

;; DZHE
(add-character-description
  47 10 1 -1 7 11
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3120413 #o1110612 #o6000712 #o112)
  2536)

;; A
(add-character-description
  48 9 0 0 9 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o10111112 #o110112 #o7061011 #o3060607 #o1060211 #o2040307 #o6030707 #o5010603
    #o3010404 #o4000601)
  2327)

;; BE
(add-character-description
  49 9 1 0 8 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1110612 #o6100711 #o7061010 #o6051006 #o1040605 #o10112 #o701)
  2345)

;; VE
(add-character-description
  50 9 1 0 8 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1110612 #o6100711 #o7061010 #o6050706 #o1040505 #o5030605 #o6010704 #o10112
    #o601)
  2345)

;; GE
(add-character-description
  51 8 1 0 7 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o10112 #o701)
  2150)

;; DE
(add-character-description
  52 9 0 -1 9 11
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o10111113 #o2110712 #o110113 #o1070212 #o2030307 #o7011012 #o3010403 #o3001001)
  2407)

;; IE
(add-character-description
  53 9 1 0 7 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1110712 #o1040705 #o10112 #o701)
  2345)

;; ZHE
(add-character-description
  54 12 1 0 11 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o12111312 #o110112 #o11061211 #o1060211 #o10051106 #o2050306 #o6041005 #o3040505
    #o10031104 #o2030304 #o11011204 #o1010204 #o11001301 #o5000612 #o201)
  3146)

;; ZE
(add-character-description
  55 8 0 0 7 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2110512 #o5100611 #o1100212 #o70210 #o6060710 #o5050706 #o2040505 #o5030604
    #o6020703 #o20103 #o5010702 #o1010202 #o1000601)
  2031)

;; II
(add-character-description
  56 10 1 0 8 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1100212 #o2060310 #o3050407 #o4030505 #o7021012 #o5010603 #o6001002 #o112)
  2536)

;; SHORT II
(add-character-description
  57 10 1 0 8 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1120214 #o2100312 #o3070411 #o4050507 #o7041014 #o5030605 #o6021004 #o20114
    #o2000601)
  2536)

;; KA
(add-character-description
  58 9 1 0 8 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o7111012 #o6100712 #o5060610 #o4050507 #o1040206 #o2030405 #o3020503 #o4010602
    #o5000701 #o112)
  2345)

;; EL
(add-character-description
  59 9 0 0 8 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o110112 #o1060212 #o2020307 #o7011012 #o3010402 #o3001001)
  2299)

;; EM
(add-character-description
  60 11 1 0 9 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o4100512 #o5070612 #o3050411 #o10041112 #o6030707 #o2020306 #o20112 #o7001104
    #o202)
  2923)

;; EN
(add-character-description
  61 10 1 0 8 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1040705 #o7001012 #o112)
  2536)

;; O
(add-character-description
  62 11 0 0 10 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3110712 #o7101011 #o2100311 #o10071111 #o1070211 #o11031207 #o30107 #o10021103
    #o1020203 #o7011102 #o1010302 #o3000701)
  2731)

;; PE
(add-character-description
  63 10 1 0 8 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o7011012 #o10112 #o1001)
  2536)

;; ER
(add-character-description
  64 9 1 0 7 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1060507 #o5050607 #o6020705 #o5010602 #o10112 #o601)
  2345)

;; ES
(add-character-description
  65 10 0 0 8 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3110612 #o2100312 #o6070711 #o1070211 #o7061010 #o30110 #o7021003 #o1020203
    #o6010702 #o1010302 #o2000601)
  2536)

;; TE
(add-character-description
  66 8 0 0 7 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3010412 #o701)
  2150)

;; U
(add-character-description
  67 9 0 0 9 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1110312 #o3100412 #o4060510 #o5040607 #o3040407 #o6020705 #o2020305 #o7011003
    #o1010203 #o7001101 #o201)
  2352)

;; EF
(add-character-description
  68 12 1 0 9 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o5071010 #o1070410 #o10011107 #o4010512 #o10107 #o1001001)
  2965)

;; KHA
(add-character-description
  69 9 0 0 8 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o7111012 #o110112 #o1100212 #o6070711 #o2070310 #o5060610 #o3060407 #o4040506
    #o5020604 #o3020404 #o6010703 #o2010303 #o7001001 #o1000201)
  2345)

;; TSE
(add-character-description
  70 10 1 -1 9 11
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o10111113 #o1110712 #o7001012 #o112)
  2606)

;; CHE
(add-character-description
  71 9 1 0 7 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2050606 #o1040206 #o6000712 #o105)
  2366)

;; SHA
(add-character-description
  72 12 1 0 9 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o5111012 #o1110412 #o10001112 #o4000512 #o112)
  3146)

;; SHCHA
(add-character-description
  73 13 1 -1 11 11
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o12111313 #o5111112 #o1110412 #o11001212 #o4000512 #o112)
  3205)

;; HARD SIGN
(add-character-description
  74 10 0 0 9 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3110712 #o7101011 #o10051111 #o7041105 #o3030704 #o2010312 #o301)
  2456)

;; YERI
(add-character-description
  75 12 1 0 9 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1110512 #o5100611 #o6050711 #o5040705 #o1030504 #o10001112 #o112)
  2951)

;; SOFT SIGN
(add-character-description
  76 9 1 0 7 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1110512 #o5100612 #o6050710 #o5040705 #o1030604 #o112)
  2345)

;; REVERSED E
(add-character-description
  77 10 0 0 9 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3110612 #o6100711 #o2100312 #o7071011 #o1070211 #o60110 #o3041005 #o10031107
    #o7021003 #o20203 #o6011002 #o1010302 #o2000701)
  2547)

;; IU
(add-character-description
  78 12 1 0 11 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o5111112 #o11071211 #o4070511 #o1040305 #o12021310 #o3020407 #o11011203 #o4010503
    #o5001101 #o112)
  3132)

;; IA
(add-character-description
  79 9 0 0 7 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o110112 #o1100212 #o2070310 #o2060607 #o1050206 #o20106 #o6010712 #o10202
    #o1000701)
  2219)

;; a
(add-character-description
  80 8 0 0 7 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o6060707 #o1060407 #o4050506 #o40106 #o1030504 #o5010607 #o10202 #o1000501)
  1958)

;; be
(add-character-description
  81 8 0 0 7 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2110512 #o5100611 #o1100211 #o6050710 #o5040605 #o1040205 #o2030504 #o30111
    #o1020203 #o1010402 #o3000701)
  1958)

;; ve
(add-character-description
  82 7 1 0 6 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1060507 #o5040606 #o1030404 #o4010504 #o10107 #o401)
  1812)

;; ge
(add-character-description
  83 6 1 0 4 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o10107 #o401)
  1460)

;; de
(add-character-description
  84 8 0 -1 7 8
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o6060710 #o2060507 #o60110 #o1030207 #o5010607 #o2010303 #o2000601)
  2017)

;; ie
(add-character-description
  85 8 0 0 7 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2060507 #o5050606 #o1050206 #o6030704 #o1030504 #o20105 #o5010604 #o1010202
    #o2000501)
  1958)

;; zhe
(add-character-description
  86 11 0 0 9 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o10061107 #o60107 #o7041007 #o1040207 #o5030704 #o2030404 #o7011003 #o1010203
    #o7001101 #o4000507 #o201)
  2728)

;; ze
(add-character-description
  87 7 0 0 6 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1060507 #o50206 #o5040606 #o2030404 #o4020504 #o5010603 #o10102 #o1000501)
  1756)

;; ii
(add-character-description
  88 8 1 0 6 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1050207 #o2040305 #o5020607 #o3020404 #o4000602 #o107)
  2021)

;; short ii
(add-character-description
  89 8 1 0 6 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1100212 #o2070310 #o5050612 #o3050407 #o4030605 #o30112 #o2010402 #o4000501
    #o1000201)
  2021)

;; ka
(add-character-description
  90 7 1 0 6 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o5060607 #o4050507 #o3040405 #o1020304 #o2010402 #o4000601 #o107)
  1819)

;; el
(add-character-description
  91 7 0 0 6 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o60107 #o1040207 #o5010607 #o2010304 #o2000601)
  1864)

;; em
(add-character-description
  92 10 1 0 8 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3050507 #o7031007 #o30107 #o5020605 #o2020305 #o6001003 #o203)
  2512)

;; en
(add-character-description
  93 8 1 0 6 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1030504 #o5000607 #o107)
  1955)

;; o
(add-character-description
  94 8 0 0 7 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2060507 #o5050606 #o1050206 #o6020705 #o20105 #o5010602 #o1010202 #o2000501)
  1958)

;; pe
(add-character-description
  95 8 1 0 6 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o5010607 #o10107 #o601)
  1955)

;; er
(add-character-description
  96 8 1 -3 6 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2060407 #o4050506 #o1050206 #o5020606 #o20112 #o4010502 #o10202 #o401)
  1958)

;; es
(add-character-description
  97 7 0 0 6 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2060507 #o5050606 #o1050206 #o5020603 #o20105 #o4010602 #o1010202 #o2000501)
  1763)

;; te
(add-character-description
  98 7 0 0 5 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2010307 #o501)
  1700)

;; u
(add-character-description
  99 7 0 -3 7 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1100312 #o3060411 #o2040306 #o4030506 #o5010604 #o1010204 #o5000701 #o101)
  1794)

;; ef
(add-character-description
  100 11 0 -3 9 11
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o6070710 #o2070310 #o7061010 #o5060610 #o3060410 #o1060210 #o10031106 #o30106
    #o7021003 #o5020603 #o3020403 #o1020203 #o5011002 #o1010402 #o4000513)
  2812)

;; kha
(add-character-description
  101 7 0 0 7 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o6060707 #o60107 #o5050607 #o1050207 #o4040506 #o2040306 #o3020404 #o4010503
    #o2010303 #o5000701 #o1000201)
  1763)

;; tse
(add-character-description
  102 8 1 -1 7 8
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o6060710 #o1060507 #o5000607 #o107)
  2049)

;; che
(add-character-description
  103 7 0 0 6 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1030504 #o5000607 #o103)
  1867)

;; sha
(add-character-description
  104 11 1 0 9 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o5061007 #o1060407 #o10001107 #o4000507 #o107)
  2920)

;; shcha
(add-character-description
  105 12 1 -1 11 8
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o12061310 #o5061107 #o1060407 #o11001207 #o4000507 #o107)
  3003)

;; hard sign
(add-character-description
  106 8 0 0 7 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2060607 #o6030706 #o2020603 #o1010207 #o201)
  1979)

;; yeri
(add-character-description
  107 9 1 0 7 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1060407 #o4030506 #o1020403 #o6000707 #o107)
  2366)

;; soft sign
(add-character-description
  108 7 1 0 5 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1060407 #o4030506 #o1020403 #o107)
  1784)

;; reversed sign
(add-character-description
  109 7 0 0 7 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2060507 #o5050606 #o50206 #o3030604 #o6020705 #o5010602 #o10202 #o2000501)
  1836)

;; reversed e
(add-character-description
  110 9 1 0 8 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o4060607 #o6050707 #o3050407 #o1030204 #o7021005 #o2020306 #o6010702 #o3010402
    #o4000701 #o107)
  2421)

;; iu
(add-character-description
  111 7 0 0 6 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o60207 #o1050306 #o1040505 #o5010607 #o10104 #o1000601)
  1916)

;; io
(add-character-description
  113 8 0 0 7 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2110512 #o5100611 #o1100211 #o6060707 #o1060507 #o5050607 #o50110 #o4040605
    #o1040205 #o2030504 #o5000601 #o1000201)
  1958)

;; dje
(add-character-description
  114 8 0 -3 7 14
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o4150616 #o6050716 #o2050306 #o2040605 #o2010302 #o10102 #o1000213)
  2017)

;; gje
(add-character-description
  115 6 1 0 4 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o40112 #o30404 #o1010202 #o2000302)
  1460)

;; e
(add-character-description
  116 7 0 0 7 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2060507 #o5050706 #o1050206 #o1030404 #o20105 #o5010702 #o1010202 #o2000501)
  1801)

;; dze
(add-character-description
  117 7 0 0 6 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1060507 #o50106 #o5040606 #o1030504 #o4010602 #o10103 #o1000401)
  1763)

;; i
(add-character-description
  118 3 1 0 1 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o20112 #o101)
  798)

;; yi
(add-character-description
  119 4 0 0 3 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1030212 #o2000301 #o101)
  993)

;; je
(add-character-description
  120 3 0 -3 2 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o140115 #o1020214 #o1000201)
  791)

;; lje
(add-character-description
  121 10 0 0 9 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o6061007 #o60107 #o10031106 #o1030206 #o6021003 #o5010607 #o2010303 #o2000601)
  2606)

;; nje
(add-character-description
  122 11 1 0 9 7
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o6061007 #o10031106 #o1030504 #o6021003 #o5000607 #o107)
  2749)

;; tshe
(add-character-description
  123 8 0 0 7 11
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o6050713 #o2050306 #o2040605 #o2010302 #o10102 #o1000213)
  2017)

;; kje
(add-character-description
  124 7 1 0 6 10
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o5110612 #o4100512 #o3060410 #o1050307 #o2040405 #o3030504 #o30112 #o5020603
    #o2010302 #o2000401)
  1819)

;; short u
(add-character-description
  126 7 0 -3 7 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1130315 #o3110414 #o4060511 #o2060311 #o5040606 #o1040207 #o5030704 #o30104
    #o2010402 #o4000502 #o1000201)
  1794)

;; dzhe
(add-character-description
  127 8 1 -1 5 8
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2070310 #o1060407 #o4000507 #o107)
  1955)
