;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module SLAVIC24

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.



;; 57 22 18 15 10 1999 4 T 
;; 10/15/1999



(def-ab-font
  SLAVIC24	; ab-font-name
  ROMAN	; ab-font-type
  24	; ab-font-size
  19	; ab-font-baseline
  31	; ab-font-maximum-width
  29	; ab-font-maximum-height

  ;; New, for 3.1 (4.0).  (MHD 5/26/93)
  24	; ab-font-point-size
  70	; ab-font-x-resolution
  70	; ab-font-y-resolution

  5973	; ab-font-width-in-x
  5973	; ab-font-width-in-y
  -3	; ab-font-x-offset
  -5	; ab-font-y-offset
  )



;; IO
(add-character-description
  33 16 2 0 12 21
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2231425 #o2131315 #o60225 #o41406 #o10001202 #o3000502)
  4020)

;; DJE
(add-character-description
  34 16 0 0 15 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o11171421 #o14161520 #o16111717 #o13101511 #o15071620 #o6061510 #o4020621 #o1202)
  4211)

;; GJE
(add-character-description
  35 14 2 0 12 21
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o60225 #o41406 #o5010603 #o6001002)
  3685)

;; E
(add-character-description
  36 17 1 0 15 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o5171221 #o12161321 #o4160520 #o13151420 #o3150420 #o15141616 #o2140317 #o14131517
    #o15121714 #o2071111 #o50114 #o16041705 #o14041505 #o15031605 #o3030404 #o1030216
    #o12021303 #o2020305 #o13011504 #o3010503 #o5001302)
  4348)

;; DZE
(add-character-description
  37 16 1 0 13 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o4171121 #o11161320 #o3160420 #o1160217 #o2150320 #o130216 #o14121516 #o12121313
    #o13111417 #o10101312 #o4071011 #o3060410 #o2040310 #o14031505 #o1030207 #o13021405
    #o11021203 #o12011305 #o2010404 #o4001202)
  4020)

;; I
(add-character-description
  38 7 2 0 2 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o221)
  1690)

;; YI
(add-character-description
  39 7 0 0 6 21
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2040425 #o4000602 #o202)
  1822)

;; JE
(add-character-description
  40 12 0 0 10 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o7201021 #o3170721 #o1170220 #o7161120 #o2160321 #o130217 #o10001216)
  3022)

;; LJE
(add-character-description
  41 23 0 0 21 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o23172420 #o14172221 #o170121 #o22162320 #o1150221 #o23112517 #o3110415 #o21102211
    #o2100320 #o22072411 #o14062210 #o3040511 #o12021421 #o4020604 #o4001402)
  5770)

;; NJE
(add-character-description
  42 24 2 0 21 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o15172221 #o22162321 #o24112517 #o22102311 #o23072420 #o2071311 #o15062310 #o13001521
    #o221)
  6146)

;; TSHE
(add-character-description
  43 16 0 0 15 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o16111721 #o13101511 #o15071621 #o6061510 #o4020621 #o1202)
  4211)

;; KJE
(add-character-description
  44 16 2 0 13 21
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o14241525 #o13221425 #o12211324 #o11171223 #o7171020 #o10161121 #o6151017 #o2140317
    #o3130416 #o4120715 #o5111012 #o6101111 #o7071210 #o10061307 #o11051406 #o12041505
    #o40225 #o6020703 #o5010603 #o6001002)
  4020)

;; SHORT U
(add-character-description
  46 16 0 0 15 21
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2230525 #o5220625 #o7161023 #o10151121 #o6140724 #o11131217 #o5120616 #o12111315
    #o4100514 #o13071413 #o2070311 #o15061607 #o3060413 #o14051511 #o1050307 #o15041706
    #o40305 #o6021103 #o5011202 #o12001301 #o4000601)
  4032)

;; DZHE
(add-character-description
  47 17 2 -2 14 19
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o6211023 #o2171421 #o14001621 #o221)
  4348)

;; A
(add-character-description
  48 16 0 0 15 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o200121 #o16171721 #o1160221 #o15141621 #o2130321 #o5121214 #o14111517 #o4110514
    #o3100416 #o13061414 #o4060611 #o12041314 #o10031104 #o5030706 #o11011207 #o6001103)
  3990)

;; BE
(add-character-description
  49 16 1 0 13 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2171121 #o11161221 #o12151320 #o14121516 #o13111417 #o11111212 #o12101312 #o2071211
    #o20221 #o1302)
  4020)

;; VE
(add-character-description
  50 16 1 0 13 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2171121 #o11161221 #o12151320 #o14121516 #o13111417 #o12101312 #o2071111 #o11061212
    #o13031406 #o11021203 #o20221 #o12011307 #o1202)
  4020)

;; GE
(add-character-description
  51 14 2 0 12 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o20221 #o1402)
  3685)

;; DE
(add-character-description
  52 16 0 -2 15 19
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o15171723 #o4171321 #o170223 #o2130321 #o4100514 #o3070421 #o4030610 #o13021521
    #o5020703 #o5001502)
  4127)

;; IE
(add-character-description
  53 16 2 0 12 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2171421 #o2071311 #o20221 #o1402)
  4020)

;; ZHE
(add-character-description
  54 21 1 0 18 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o21172221 #o170121 #o20162121 #o1160221 #o16131717 #o3130417 #o17122020 #o2120320
    #o15111713 #o3110513 #o12071611 #o4071011 #o15061707 #o3060507 #o16022006 #o2020406
    #o17002202 #o10001221 #o1000302)
  5394)

;; ZE
(add-character-description
  55 14 0 0 12 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3200421 #o4171021 #o10161121 #o1160420 #o11151220 #o140316 #o13121416 #o12111317
    #o11101212 #o5071011 #o10061112 #o40205 #o11031207 #o12021306 #o7021003 #o3020403
    #o10011203 #o1010304 #o3001002)
  3482)

;; II
(add-character-description
  56 17 2 0 13 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2150321 #o3140417 #o4120516 #o5100614 #o6070712 #o7051011 #o13041521 #o10031107
    #o11021205 #o12001504 #o221)
  4348)

;; SHORT II
(add-character-description
  57 17 2 0 13 21
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2210325 #o3200423 #o4160522 #o5140620 #o6130716 #o7111015 #o13101525 #o10071113
    #o11061211 #o12041510 #o40225 #o5021003 #o4011102 #o10001201 #o3000501)
  4348)

;; KA
(add-character-description
  58 16 2 0 13 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o14201521 #o13161421 #o12151320 #o11131217 #o10121115 #o7111014 #o2100313 #o3070412
    #o4060511 #o5050611 #o6040713 #o11031204 #o7031006 #o10021105 #o11011303 #o12001501
    #o221)
  4020)

;; EL
(add-character-description
  59 15 0 0 13 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o200121 #o170220 #o1130317 #o2070413 #o3030507 #o13021521 #o4020603 #o4001502)
  3942)

;; EM
(add-character-description
  60 20 1 0 16 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o10161121 #o7151021 #o11131221 #o6120721 #o12101316 #o5070616 #o16052021 #o13051413
    #o4050513 #o50221 #o14021510 #o3020410 #o15002005 #o305)
  5011)

;; EN
(add-character-description
  61 17 2 0 13 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2071311 #o13001521 #o221)
  4348)

;; O
(add-character-description
  62 18 1 0 16 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o6201221 #o5171320 #o13161420 #o4160520 #o14151520 #o3150420 #o15141617 #o2140317
    #o17052014 #o50114 #o16031716 #o14031504 #o3030404 #o1030216 #o15021606 #o2020305
    #o13011503 #o3010503 #o5001302)
  4683)

;; PE
(add-character-description
  63 17 2 0 13 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o13021521 #o20221 #o1502)
  4348)

;; ER
(add-character-description
  64 16 2 0 13 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o11131214 #o2121114 #o11111413 #o13031511 #o20221 #o12011403 #o1202)
  4020)

;; ES
(add-character-description
  65 17 1 0 15 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o5171221 #o12161321 #o4160520 #o13151420 #o3150420 #o15141616 #o2140317 #o14131517
    #o15121714 #o50114 #o16041705 #o14041505 #o15031605 #o3030404 #o1030216 #o12021303
    #o2020306 #o13011504 #o3010503 #o5001302)
  4348)

;; TE
(add-character-description
  66 14 0 0 14 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o6021021 #o1602)
  3685)

;; U
(add-character-description
  67 16 0 0 15 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2170521 #o5160621 #o10131115 #o7121017 #o10111213 #o6100720 #o11071311 #o5060612
    #o12051407 #o4040510 #o13031505 #o2030305 #o3020406 #o14011603 #o1010303 #o15001701
    #o301)
  4032)

;; EF
(add-character-description
  68 20 1 0 16 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o11141516 #o3140716 #o15131616 #o2130316 #o17022014 #o15021603 #o7021121 #o2020303
    #o20114 #o16011715 #o1010215 #o2001602)
  5083)

;; KHA
(add-character-description
  69 16 0 0 14 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o15201621 #o200121 #o14171521 #o1170221 #o13151421 #o2150321 #o12141317 #o3140417
    #o11131216 #o4130516 #o10111115 #o5110615 #o6061013 #o11051206 #o4050506 #o10041110
    #o5040610 #o11031305 #o3030505 #o12021403 #o2020403 #o12011502 #o1010402 #o13001601
    #o301)
  4020)

;; TSE
(add-character-description
  70 17 2 -2 15 19
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o15171723 #o2171321 #o13001521 #o221)
  4468)

;; CHE
(add-character-description
  71 16 1 0 13 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3120413 #o4111313 #o1100412 #o13001521 #o210)
  4056)

;; SHA
(add-character-description
  72 21 2 0 18 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o12172021 #o2171021 #o20002221 #o10001221 #o221)
  5394)

;; SHCHA
(add-character-description
  73 21 2 -2 19 19
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o21172323 #o12171721 #o2171021 #o17002121 #o10001221 #o221)
  5495)

;; HARD SIGN
(add-character-description
  74 16 0 0 15 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o6171421 #o14161520 #o16111717 #o13101511 #o15071620 #o6061510 #o4020621 #o602)
  4211)

;; YERI
(add-character-description
  75 20 2 0 16 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2171021 #o10161120 #o12111317 #o7101111 #o11071220 #o2061110 #o16002021 #o221)
  5059)

;; SOFT SIGN
(add-character-description
  76 16 2 0 13 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o13171420 #o2171221 #o12161320 #o13111517 #o11101211 #o12071411 #o2061210 #o221)
  4020)

;; REVERSED E
(add-character-description
  77 17 1 0 15 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o5171221 #o12161320 #o4160521 #o13151420 #o3150420 #o1150216 #o14131517 #o2130320
    #o120215 #o6071511 #o16051713 #o50106 #o15031615 #o1030205 #o14021505 #o12021303
    #o4020503 #o2020305 #o13011403 #o3010404 #o4001302)
  4366)

;; IU
(add-character-description
  78 21 2 0 18 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o12201521 #o11171520 #o15161720 #o10161120 #o17142017 #o7141017 #o2070511 #o21052214
    #o6050716 #o5040614 #o20032116 #o17022005 #o15021603 #o11021203 #o6021005 #o16011703
    #o10011103 #o11001602 #o221)
  5370)

;; IA
(add-character-description
  79 15 0 0 13 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2200321 #o200121 #o1170221 #o2160420 #o3150516 #o3140615 #o4131314 #o2121313
    #o1110412 #o30211 #o13021521 #o1010303 #o3001502)
  3805)

;; a
(add-character-description
  80 13 1 0 12 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3130614 #o12121414 #o3120713 #o1120213 #o6111012 #o2110314 #o70212 #o1060307
    #o3051006 #o11021214 #o7021003 #o10011113 #o1010303 #o3001002)
  3357)

;; be
(add-character-description
  81 13 1 0 11 18
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o4200722 #o7171022 #o3170422 #o10161121 #o2160321 #o12111316 #o11071220 #o7071010
    #o2070312 #o70117 #o10061112 #o3060410 #o1060220 #o4051007 #o1050306 #o1040405
    #o2030504 #o3021003 #o6011102 #o11001202)
  3357)

;; ve
(add-character-description
  82 12 1 0 10 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2120714 #o7111014 #o10101113 #o11071212 #o7061110 #o2050607 #o6040707 #o10021105
    #o6020703 #o20214 #o7011005 #o702)
  3106)

;; ge
(add-character-description
  83 10 1 0 7 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o20214 #o702)
  2503)

;; de
(add-character-description
  84 14 0 -2 12 14
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o12141316 #o13121416 #o3121114 #o120116 #o1110216 #o2050314 #o11021314 #o4020505
    #o3010411 #o4001302)
  3458)

;; ie
(add-character-description
  85 13 1 0 11 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3131014 #o3121213 #o10111312 #o2100313 #o2051107 #o40111 #o12031307 #o11021207
    #o3020403 #o1020212 #o10011103 #o2010304 #o3001002)
  3357)

;; zhe
(add-character-description
  86 18 1 0 16 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1130214 #o17122014 #o120114 #o16101714 #o15071613 #o1070313 #o11051307 #o5050707
    #o13041407 #o4040507 #o15021605 #o2020305 #o14011510 #o3010410 #o15002002 #o7001114
    #o302)
  4677)

;; ze
(add-character-description
  87 12 1 0 10 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2130714 #o1120713 #o7111014 #o110212 #o11071212 #o10061113 #o4050707 #o10021105
    #o6020703 #o2020303 #o20104 #o7011010 #o1010204 #o2000702)
  3010)

;; ii
(add-character-description
  88 14 1 0 11 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2110314 #o3100413 #o4060512 #o5050610 #o11031314 #o6030707 #o7021005 #o10001303
    #o214)
  3464)

;; short ii
(add-character-description
  89 14 1 0 11 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2160321 #o3150420 #o4130517 #o5120615 #o11101321 #o6100714 #o7071012 #o10051310
    #o50221 #o4020703 #o3011002 #o7001101 #o2000301)
  3464)

;; ka
(add-character-description
  90 12 1 0 11 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o12131314 #o11121214 #o10111114 #o6100711 #o7071013 #o5060710 #o2050307 #o3040606
    #o4030704 #o5021003 #o6011102 #o7001201 #o214)
  3118)

;; el
(add-character-description
  91 12 0 0 11 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o120314 #o2070412 #o11021314 #o3020507 #o4001302)
  3196)

;; em
(add-character-description
  92 17 1 0 14 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o6110714 #o7101014 #o5070614 #o10061113 #o50214 #o14041614 #o11041211 #o4040512
    #o3020407 #o12011306 #o13001604 #o305)
  4307)

;; en
(add-character-description
  93 13 1 0 10 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2051007 #o10001214 #o214)
  3351)

;; o
(add-character-description
  94 13 0 0 11 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o4120714 #o7111014 #o3110414 #o10101113 #o2100313 #o12031311 #o30111 #o11021212
    #o7021003 #o3020403 #o1020212 #o10011104 #o2010304 #o3001002)
  3357)

;; pe
(add-character-description
  95 13 1 0 10 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o10021214 #o20214 #o1202)
  3351)

;; er
(add-character-description
  96 13 1 -5 11 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3120714 #o7111014 #o10101113 #o2100313 #o11041212 #o12031311 #o7021003 #o10011204
    #o2010304 #o3001002 #o221)
  3357)

;; es
(add-character-description
  97 12 0 0 10 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3131014 #o3121113 #o7111212 #o2100313 #o30111 #o11021205 #o7021003 #o3020403
    #o1020212 #o10011105 #o2010304 #o3001002)
  3022)

;; te
(add-character-description
  98 11 0 0 10 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o4020614 #o1202)
  2915)

;; u
(add-character-description
  99 12 0 -5 12 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2170421 #o1160221 #o4150521 #o5140620 #o4110614 #o6100716 #o3060511 #o7051013
    #o11031205 #o2030406 #o10021110 #o11011303 #o1010303 #o11001401 #o301)
  3076)

;; ef
(add-character-description
  100 19 1 -5 16 19
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o12141516 #o3140616 #o15131616 #o11131215 #o6130715 #o2130316 #o17052013 #o50113
    #o14041605 #o2040405 #o16031715 #o11031205 #o6030705 #o1030215 #o12021604 #o2020604
    #o7001123)
  4820)

;; kha
(add-character-description
  101 12 0 0 10 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o11131214 #o130114 #o10121114 #o1120214 #o7101014 #o2100314 #o6070712 #o3070412
    #o6040705 #o3040405 #o4030611 #o6021004 #o2020404 #o7011102 #o1010302 #o7001201
    #o301)
  3022)

;; tse
(add-character-description
  102 14 1 -2 12 14
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o12121416 #o2121014 #o10001214 #o214)
  3512)

;; che
(add-character-description
  103 13 1 0 10 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3061010 #o1060207 #o2050310 #o10001214 #o206)
  3202)

;; sha
(add-character-description
  104 20 1 0 16 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o11121614 #o2120714 #o16002014 #o7001114 #o214)
  5005)

;; shcha
(add-character-description
  105 20 1 -2 18 14
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o20122216 #o11121614 #o2120714 #o16002014 #o7001114 #o214)
  5149)

;; hard sign
(add-character-description
  106 13 0 0 12 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o4121114 #o11111214 #o13061412 #o11061207 #o12051313 #o4041206 #o2020414 #o402)
  3393)

;; yeri
(add-character-description
  107 16 1 0 13 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2120514 #o5110614 #o7061012 #o5060607 #o6050713 #o2040606 #o13001514 #o214)
  4056)

;; soft sign
(add-character-description
  108 12 1 0 9 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2120614 #o6110714 #o10061112 #o6060707 #o7051013 #o2040706 #o214)
  3058)

;; reversed sign
(add-character-description
  109 12 0 0 10 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2130714 #o1120613 #o6111013 #o110212 #o4051007 #o11041211 #o10021112 #o6020703
    #o2020303 #o20104 #o7011004 #o1010204 #o2000702)
  3148)

;; reversed e
(add-character-description
  110 16 1 0 14 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o7121314 #o13101413 #o6100713 #o2050407 #o4040511 #o15031611 #o14021513 #o5020613
    #o13011404 #o6010704 #o7001302 #o214)
  4151)

;; iu
(add-character-description
  111 13 0 0 10 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o130314 #o1120413 #o2110512 #o3100611 #o3071010 #o2061007 #o10021214 #o20106
    #o1010207 #o2001202)
  3285)

;; io
(add-character-description
  113 13 1 0 11 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3201021 #o3171220 #o10161317 #o2150320 #o2121114 #o110116 #o12101314 #o11071214
    #o3070410 #o1070217 #o10061111 #o2060311 #o3051007 #o7001102 #o2000402)
  3357)

;; dje
(add-character-description
  114 14 0 -5 12 24
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o10261230 #o13111427 #o11111212 #o5110612 #o12101330 #o4100513 #o5071211 #o4020604
    #o20204 #o2000423)
  3458)

;; gje
(add-character-description
  115 10 1 0 7 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o70221 #o50707 #o2020403 #o3000502)
  2503)

;; e
(add-character-description
  116 12 1 0 10 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o3131014 #o4121113 #o10111212 #o2110413 #o2050607 #o40111 #o11021204 #o7021003
    #o3020403 #o1020212 #o10011104 #o2010304 #o3001002)
  3088)

;; dze
(add-character-description
  117 12 0 0 10 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o10121113 #o3120714 #o1120213 #o7111014 #o2110314 #o100212 #o10071212 #o5061107
    #o3050606 #o2040306 #o11031204 #o7021003 #o2020303 #o20105 #o10011103 #o1010205
    #o2001002)
  3022)

;; i
(add-character-description
  118 5 1 0 2 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o40221 #o202)
  1368)

;; yi
(add-character-description
  119 7 0 0 6 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2050421 #o4000602 #o202)
  1702)

;; je
(add-character-description
  120 5 0 -5 4 22
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o2250326 #o240226 #o2040425 #o2000402)
  1356)

;; lje
(add-character-description
  121 17 0 0 16 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o1130214 #o12121514 #o120114 #o15111614 #o1110313 #o17062012 #o15061607 #o16051713
    #o2050411 #o12041606 #o10021214 #o3020505 #o3001202)
  4468)

;; nje
(add-character-description
  122 18 1 0 16 12
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o12121514 #o15111614 #o17062012 #o15061607 #o16051713 #o2051007 #o12041606 #o10001214
    #o214)
  4713)

;; tshe
(add-character-description
  123 14 0 0 12 19
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o13111423 #o11111212 #o5110612 #o12101323 #o4100513 #o5071211 #o4020604 #o20204
    #o2000423)
  3458)

;; kje
(add-character-description
  124 12 1 0 11 17
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o12201321 #o11171221 #o10161121 #o6150716 #o7141020 #o5130715 #o2120314 #o3110613
    #o4100711 #o5071010 #o6061107 #o7051206 #o50221 #o4020603 #o5000702)
  3118)

;; short u
(add-character-description
  126 12 0 -5 12 22
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o4250526 #o2240426 #o1230226 #o4220625 #o4160521 #o5150722 #o3130516 #o7121020
    #o11101212 #o2100413 #o10071115 #o1060310 #o11051310 #o50306 #o13041405 #o4020703
    #o3011002 #o10001101 #o2000401)
  3076)

;; dzhe
(add-character-description
  127 13 1 -2 10 14
  #-slavic-bitmaps nil #+slavic-bitmaps '#(#o4140616 #o2121014 #o10001214 #o214)
  3351)
