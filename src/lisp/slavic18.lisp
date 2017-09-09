;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module SLAVIC18

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.



;; 56 22 18 15 10 1999 4 T 
;; 10/15/1999



(def-ab-font
  SLAVIC18	; ab-font-name
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



;; IO
(add-character-description
  33 12 1 0 9 16
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2161120 #o2101112 #o50220 #o31105 #o5000702 #o2000402)
  3015)

;; DJE
(add-character-description
  34 12 0 0 11 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o7131015 #o10121115 #o12061313 #o10061107 #o11051214 #o5041106 #o3020515 #o702)
  3158)

;; GJE
(add-character-description
  35 11 1 0 9 16
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o50220 #o31105 #o4010502 #o5000602)
  2764)

;; E
(add-character-description
  36 13 1 0 11 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o4141015 #o4131114 #o10121213 #o3120415 #o2110314 #o11101312 #o2060710 #o40112
    #o11031304 #o3020403 #o1020213 #o10011203 #o2010305 #o3001002)
  3261)

;; DZE
(add-character-description
  37 12 1 0 10 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o10131114 #o3130715 #o7121014 #o1120314 #o10101213 #o100212 #o7071110 #o3060707
    #o2050406 #o10031204 #o2020303 #o20105 #o7011103 #o1010206 #o2000702)
  3015)

;; I
(add-character-description
  38 5 1 0 2 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o215)
  1268)

;; YI
(add-character-description
  39 5 0 0 6 16
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2030420 #o4000602 #o202)
  1366)

;; JE
(add-character-description
  40 9 0 0 7 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2140415 #o5130614 #o1130414 #o4120515 #o100213 #o5000713)
  2267)

;; LJE
(add-character-description
  41 17 0 0 16 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o11131515 #o130115 #o15121615 #o1100215 #o17062013 #o15061607 #o16051714 #o11041606
    #o3040410 #o2030314 #o7021115 #o3020504 #o3001102)
  4328)

;; NJE
(add-character-description
  42 18 1 0 16 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o12131515 #o15121615 #o17062013 #o15061607 #o16051714 #o2051007 #o12041606 #o10001215
    #o215)
  4610)

;; TSHE
(add-character-description
  43 12 0 0 11 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o12061315 #o10061107 #o11051215 #o5041106 #o3020515 #o702)
  3158)

;; KJE
(add-character-description
  44 12 1 0 11 16
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o12171320 #o11161220 #o10151120 #o7141017 #o6120716 #o2110314 #o3100413 #o4070513
    #o5060614 #o6050710 #o11041205 #o7041007 #o12031304 #o10031106 #o30220 #o4010503
    #o5000602)
  3015)

;; SHORT U
(add-character-description
  46 12 0 0 10 16
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o170320 #o160417 #o3150516 #o4130615 #o3120414 #o4110713 #o6071011 #o2070412
    #o7051107 #o1050307 #o10031205 #o30205 #o4020603 #o3010602 #o6000702 #o2000301)
  3024)

;; DZHE
(add-character-description
  47 13 1 -2 10 15
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o4150617 #o2131015 #o10001215 #o215)
  3261)

;; A
(add-character-description
  48 12 0 0 11 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o140115 #o12121315 #o1120215 #o11071215 #o5070711 #o2070315 #o10051113 #o6040705
    #o3040412 #o7021011 #o4010511 #o5000704)
  2993)

;; BE
(add-character-description
  49 12 1 0 10 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2130715 #o7121015 #o11101213 #o7101011 #o10071114 #o2061010 #o20215 #o1002)
  3015)

;; VE
(add-character-description
  50 12 1 0 10 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2130715 #o7121015 #o11101213 #o10071114 #o2060610 #o6050710 #o10021106 #o6020703
    #o20215 #o7011011 #o702)
  3015)

;; GE
(add-character-description
  51 11 1 0 9 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o20215 #o1102)
  2764)

;; DE
(add-character-description
  52 12 0 -2 11 15
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o11151217 #o1150217 #o12131317 #o3131015 #o130117 #o1120315 #o2060412 #o10021215
    #o3020506 #o4001202)
  3096)

;; IE
(add-character-description
  53 12 1 0 10 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2131215 #o2061110 #o20215 #o1202)
  3015)

;; ZHE
(add-character-description
  54 16 1 0 14 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o15131615 #o130115 #o14071515 #o1070215 #o10051207 #o4050607 #o13021414 #o2020314
    #o12011310 #o3010410 #o13001602 #o6001015 #o302)
  4045)

;; ZE
(add-character-description
  55 10 0 0 9 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2140615 #o1130614 #o6120715 #o110213 #o10101113 #o7071014 #o4060610 #o7021006
    #o5020603 #o2020303 #o20104 #o6010711 #o1010204 #o2000602)
  2612)

;; II
(add-character-description
  56 13 1 0 10 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2100314 #o3060412 #o4040510 #o10031215 #o5020607 #o6010705 #o7001203 #o215)
  3261)

;; SHORT II
(add-character-description
  57 13 1 0 10 16
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2130317 #o3110415 #o4070513 #o10061220 #o5050612 #o6040710 #o7031206 #o30220
    #o4020603 #o3010702 #o6001001 #o2000401)
  3261)

;; KA
(add-character-description
  58 12 1 0 11 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o12141315 #o11131215 #o10121115 #o7111014 #o6070713 #o2060311 #o3050410 #o4040510
    #o7031004 #o5030611 #o6020705 #o7011103 #o10001301 #o215)
  3015)

;; EL
(add-character-description
  59 12 0 0 10 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o130115 #o1120215 #o2060314 #o10021215 #o4020506 #o3010413 #o4001202)
  2957)

;; EM
(add-character-description
  60 15 1 0 12 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o6120715 #o5110615 #o7071015 #o4070515 #o12041315 #o10041112 #o3040412 #o1040215
    #o13031415 #o30115 #o11011207 #o2010307 #o12001403 #o203)
  3759)

;; EN
(add-character-description
  61 13 1 0 10 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2051007 #o10001215 #o215)
  3261)

;; O
(add-character-description
  62 14 0 0 12 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o4131015 #o10121114 #o3120414 #o11111214 #o2110314 #o13041411 #o40111 #o12021313
    #o10021103 #o3020403 #o1020213 #o11011204 #o2010304 #o3001102)
  3512)

;; PE
(add-character-description
  63 13 1 0 10 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o10021215 #o20215 #o1202)
  3261)

;; ER
(add-character-description
  64 12 1 0 9 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2070611 #o6060711 #o10021107 #o6020703 #o20215 #o7011010 #o702)
  3015)

;; ES
(add-character-description
  65 13 1 0 11 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o4131015 #o10121114 #o3120415 #o11111213 #o2110314 #o11101311 #o40112 #o11031304
    #o3020403 #o1020213 #o10011203 #o2010304 #o3001002)
  3261)

;; TE
(add-character-description
  66 11 0 0 10 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o4020615 #o1202)
  2764)

;; U
(add-character-description
  67 12 0 0 10 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o130315 #o3120414 #o4110513 #o3060511 #o5050612 #o2040406 #o6030710 #o10021104
    #o1020304 #o7011006 #o10001202 #o202)
  3024)

;; EF
(add-character-description
  68 15 1 0 14 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o10101412 #o2100612 #o15021610 #o6021015 #o20110 #o14011511 #o1010211 #o2001402)
  3812)

;; KHA
(add-character-description
  69 12 0 0 11 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o12141315 #o140115 #o11131215 #o1130215 #o2120315 #o10111115 #o6110712 #o3100414
    #o7071013 #o4070512 #o5040711 #o10031104 #o3030404 #o7021006 #o4020506 #o10011203
    #o2010403 #o10001301 #o1000301)
  3015)

;; TSE
(add-character-description
  70 13 1 -2 11 15
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o11151217 #o12131317 #o2131015 #o10001215 #o215)
  3351)

;; CHE
(add-character-description
  71 12 1 0 9 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3060710 #o1060210 #o2050310 #o7001115 #o206)
  3042)

;; SHA
(add-character-description
  72 16 1 0 14 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o10131415 #o2130615 #o14001615 #o6001015 #o215)
  4045)

;; SHCHA
(add-character-description
  73 16 1 -2 14 15
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o14151517 #o15131617 #o10131315 #o2130615 #o13001515 #o6001015 #o215)
  4122)

;; HARD SIGN
(add-character-description
  74 12 0 0 11 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o5131015 #o10121115 #o12061313 #o10061107 #o11051214 #o5041106 #o3020515 #o502)
  3158)

;; YERI
(add-character-description
  75 15 1 0 12 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2130515 #o5120615 #o7061013 #o5060607 #o6050714 #o2040606 #o12001415 #o215)
  3795)

;; SOFT SIGN
(add-character-description
  76 12 1 0 9 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2130615 #o6120715 #o10061113 #o6060707 #o7051014 #o2040706 #o215)
  3015)

;; REVERSED E
(add-character-description
  77 13 1 0 11 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3140715 #o2130714 #o7121015 #o1120313 #o10111114 #o100212 #o4061110 #o12041311
    #o30104 #o11021213 #o7021003 #o1020204 #o10011105 #o2010303 #o3001002)
  3275)

;; IU
(add-character-description
  78 16 1 0 14 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o7131215 #o12121315 #o6120715 #o13111414 #o5110614 #o2060310 #o15041611 #o3040412
    #o14021513 #o12021303 #o6020703 #o4020513 #o13011404 #o5010604 #o6001302 #o215)
  4028)

;; IA
(add-character-description
  79 11 0 0 9 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2140315 #o140115 #o1130215 #o2120414 #o3110512 #o3070711 #o2060311 #o7021115
    #o2020303 #o20107 #o1010210 #o2001102)
  2854)

;; a
(add-character-description
  80 10 0 0 9 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1100411 #o10071111 #o2070510 #o5060610 #o50210 #o2040505 #o5030604 #o6020710
    #o20103 #o7011011 #o1010202 #o2000702)
  2518)

;; be
(add-character-description
  81 10 0 0 9 14
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3140616 #o6130716 #o2130316 #o10071114 #o6070710 #o7061015 #o2060310 #o3050707
    #o50114 #o1040215 #o1030304 #o2020503 #o5011002 #o10001101)
  2518)

;; ve
(add-character-description
  82 9 1 0 7 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2070511 #o6050710 #o2040506 #o5020611 #o20211 #o6010704 #o602)
  2330)

;; ge
(add-character-description
  83 7 1 0 6 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o20211 #o602)
  1877)

;; de
(add-character-description
  84 10 0 -2 9 11
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o7111013 #o10071113 #o3070611 #o70113 #o1050213 #o6021011 #o3020405 #o2010311
    #o3001002)
  2594)

;; ie
(add-character-description
  85 10 0 0 8 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2100711 #o2071010 #o2040706 #o7021006 #o2020303 #o20107 #o6010703 #o1010210
    #o2000602)
  2518)

;; zhe
(add-character-description
  86 14 0 0 12 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o13071411 #o70111 #o12051311 #o1050211 #o7041106 #o3040506 #o12021304 #o1020204
    #o11011210 #o2010310 #o12001402 #o5000711 #o202)
  3508)

;; ze
(add-character-description
  87 9 0 0 7 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1070511 #o5060611 #o60207 #o6050710 #o4040606 #o1020203 #o5010704 #o10103
    #o1000502)
  2258)

;; ii
(add-character-description
  88 10 1 0 8 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2060311 #o6051011 #o3040410 #o4020507 #o5001005 #o211)
  2598)

;; short ii
(add-character-description
  89 10 1 0 8 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2120315 #o6111015 #o3100414 #o4060513 #o5041011 #o40215 #o3020503 #o2010602
    #o5000701 #o1000301)
  2598)

;; ka
(add-character-description
  90 9 1 0 8 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o7101011 #o5100611 #o6070711 #o4060610 #o3050506 #o2030505 #o3020603 #o4010702
    #o5001001 #o211)
  2339)

;; el
(add-character-description
  91 9 0 0 8 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o70311 #o2030407 #o6021011 #o2020503 #o3001002)
  2397)

;; em
(add-character-description
  92 13 1 0 10 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o4060611 #o6040711 #o3030410 #o7021007 #o2010305 #o10001211 #o211)
  3230)

;; en
(add-character-description
  93 10 1 0 7 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2040506 #o5000711 #o211)
  2513)

;; o
(add-character-description
  94 10 0 0 9 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3070611 #o6060711 #o2060311 #o10021107 #o6020703 #o2020303 #o20107 #o7011010
    #o1010210 #o2000702)
  2518)

;; pe
(add-character-description
  95 10 1 0 7 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o5020711 #o20211 #o702)
  2513)

;; er
(add-character-description
  96 10 1 -4 8 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3070511 #o5060611 #o2060310 #o7021007 #o5020603 #o6010710 #o2010303 #o3000602
    #o215)
  2518)

;; es
(add-character-description
  97 9 0 0 7 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3070611 #o6060710 #o2060311 #o2020303 #o20107 #o6010703 #o1010210 #o2000602)
  2267)

;; te
(add-character-description
  98 9 0 0 8 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3020511 #o1002)
  2186)

;; u
(add-character-description
  99 9 0 -4 8 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1130315 #o4050513 #o2040306 #o5030610 #o3030415 #o6020705 #o1010304 #o6001002
    #o201)
  2307)

;; ef
(add-character-description
  100 14 0 -4 14 14
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o11101312 #o3100512 #o13071412 #o10071111 #o5070611 #o2070312 #o15031610 #o13031404
    #o2030304 #o30110 #o14021511 #o10021104 #o5020604 #o1020211 #o11011403 #o2010503
    #o6001016)
  3615)

;; kha
(add-character-description
  101 9 0 0 8 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o7101011 #o100111 #o6070711 #o1070211 #o5050611 #o2050311 #o3040507 #o2020604
    #o5010702 #o1010302 #o5001001 #o301)
  2267)

;; tse
(add-character-description
  102 10 1 -2 9 11
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o7071113 #o2070511 #o5000711 #o211)
  2634)

;; che
(add-character-description
  103 9 0 0 7 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1050206 #o2040506 #o5000711 #o205)
  2401)

;; sha
(add-character-description
  104 15 1 0 12 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o7071211 #o2070511 #o12001411 #o5000711 #o211)
  3754)

;; shcha
(add-character-description
  105 15 1 -2 14 11
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o14071613 #o7071211 #o2070511 #o12001411 #o5000711 #o211)
  3862)

;; hard sign
(add-character-description
  106 10 0 0 9 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o4070711 #o7051011 #o10041110 #o4031005 #o2020411 #o402)
  2545)

;; yeri
(add-character-description
  107 12 1 0 10 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2070411 #o4050511 #o5040610 #o2030505 #o10001211 #o211)
  3042)

;; soft sign
(add-character-description
  108 9 1 0 7 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2070511 #o5050611 #o6040710 #o2030605 #o211)
  2294)

;; reversed sign
(add-character-description
  109 9 0 0 7 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1070511 #o60110 #o3040506 #o6020707 #o4020503 #o5010610 #o10103 #o1000502)
  2361)

;; reversed e
(add-character-description
  110 12 1 0 10 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o6070711 #o7061011 #o5060611 #o3060410 #o2040406 #o11021207 #o7021003 #o5020603
    #o10011110 #o4010510 #o5001002 #o211)
  3114)

;; iu
(add-character-description
  111 10 0 0 9 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o100311 #o1070410 #o2060507 #o3040706 #o7021111 #o2020305 #o1010204 #o2001102)
  2464)

;; io
(add-character-description
  113 10 0 0 8 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3140615 #o3130714 #o6121013 #o2120315 #o3070611 #o2060311 #o60113 #o6051011
    #o1050214 #o2040606 #o5000702 #o2000402)
  2518)

;; dje
(add-character-description
  114 10 0 -4 9 18
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o6200722 #o7071022 #o10061121 #o3060410 #o4051007 #o3010403 #o10103 #o1000316)
  2594)

;; gje
(add-character-description
  115 7 1 0 6 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o60215 #o40606 #o2020303 #o3010402 #o3000501)
  1877)

;; e
(add-character-description
  116 9 0 0 8 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2070611 #o6060710 #o7051006 #o2040406 #o7021003 #o2020303 #o20107 #o6010703
    #o1010210 #o2000602)
  2316)

;; dze
(add-character-description
  117 9 0 0 8 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2100611 #o1070610 #o7061007 #o60110 #o6050710 #o2040605 #o1030204 #o6010702
    #o10203 #o2000602)
  2267)

;; i
(add-character-description
  118 4 1 0 2 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o40215 #o202)
  1026)

;; yi
(add-character-description
  119 5 0 0 6 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2040415 #o4000602 #o202)
  1277)

;; je
(add-character-description
  120 4 0 -4 3 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1200221 #o170121 #o1040320 #o1000302)
  1017)

;; lje
(add-character-description
  121 13 0 0 12 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o10071211 #o70111 #o12051311 #o1050211 #o13041410 #o10031305 #o6021011 #o3020405
    #o2010310 #o3001002)
  3351)

;; nje
(add-character-description
  122 14 1 0 12 9
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o7071211 #o12051311 #o13041410 #o2040506 #o7031305 #o5000711 #o211)
  3535)

;; tshe
(add-character-description
  123 10 0 0 9 14
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o7071016 #o10061116 #o3060410 #o4051007 #o3010403 #o10103 #o1000316)
  2594)

;; kje
(add-character-description
  124 9 1 0 8 13
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o7141015 #o5140615 #o6130715 #o4120614 #o3110512 #o2070511 #o3060607 #o4050706
    #o5041005 #o40215 #o3010403 #o4000502)
  2339)

;; short u
(add-character-description
  126 9 0 -4 8 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1170321 #o4140517 #o4110614 #o2100312 #o3070421 #o5060711 #o1050310 #o6041006
    #o40305 #o3010603 #o6000701 #o2000302)
  2307)

;; dzhe
(add-character-description
  127 10 1 -2 8 11
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3110513 #o2070611 #o6001011 #o211)
  2513)
