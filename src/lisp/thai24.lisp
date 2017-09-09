;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module THAI24

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.



;; 50 1 11 18 12 2003 3 NIL 
;; 12/18/2003



(def-ab-font
  THAI24	; ab-font-name
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



;; Thai Font Code 0x20, Unicode 0xE00
(add-character-description
  32 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x21, Unicode 0xE01
(add-character-description
  33 14 2 0 10 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o50215 #o10041115 #o3040405 #o2030305 #o11021215 #o6020703 #o20204 #o7011104
    #o1010302 #o3000702)
  3555)

;; Thai Font Code 0x22, Unicode 0xE02
(add-character-description
  34 15 1 0 12 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o10131215 #o4130615 #o2060407 #o6040715 #o4040506 #o3030404 #o10021104 #o6020703
    #o2020304 #o20105 #o7011015 #o1010207 #o12001415 #o2000702)
  3870)

;; Thai Font Code 0x23, Unicode 0xE03
(add-character-description
  35 16 1 0 12 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o10131215 #o4130615 #o2060407 #o6040715 #o4040506 #o2030404 #o10021104 #o20105
    #o7011015 #o4010503 #o1010206 #o12001415 #o5000702 #o2000402)
  3972)

;; Thai Font Code 0x24, Unicode 0xE04
(add-character-description
  36 14 1 0 11 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1100215 #o5070710 #o2070315 #o7051007 #o3050510 #o4040705 #o11031215 #o30210
    #o12021315 #o7021003 #o3020403 #o10011203 #o1010303 #o3001002)
  3631)

;; Thai Font Code 0x25, Unicode 0xE05
(add-character-description
  37 14 1 0 11 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5100711 #o2100315 #o7061010 #o3060511 #o4050706 #o11031315 #o30110 #o5020604
    #o1020215 #o10011203 #o6010703 #o4010503 #o2010303 #o7001002 #o3000402)
  3631)

;; Thai Font Code 0x26, Unicode 0xE06
(add-character-description
  38 16 1 0 12 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4140615 #o11121214 #o3120414 #o10111112 #o4110512 #o5100611 #o2060407 #o6040715
    #o4040506 #o2030404 #o10021104 #o20105 #o7011014 #o4010503 #o1010206 #o12001415
    #o5000702 #o2000402)
  3972)

;; Thai Font Code 0x27, Unicode 0xE07
(add-character-description
  39 11 1 0 8 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5130615 #o4120515 #o3070414 #o2060312 #o50207 #o4030604 #o7021014 #o6010715
    #o3010403 #o4000601)
  2814)

;; Thai Font Code 0x28, Unicode 0xE08
(add-character-description
  40 13 1 0 10 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7131015 #o6110715 #o2100411 #o5070613 #o4060511 #o1060210 #o2050506 #o1030204
    #o11021214 #o7021003 #o20104 #o10011115 #o1010303 #o3001002)
  3322)

;; Thai Font Code 0x29, Unicode 0xE09
(add-character-description
  41 15 1 0 13 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o12141415 #o5130614 #o14121514 #o6120713 #o13111412 #o7111012 #o1110312 #o12101311
    #o3070515 #o70111 #o1060407 #o1030204 #o11021215 #o7021003 #o20104 #o10011113
    #o1010303 #o3001002)
  3894)

;; Thai Font Code 0x2A, Unicode 0xE0A
(add-character-description
  42 15 1 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o13151416 #o10141316 #o4140616 #o7061016 #o2060407 #o13051515 #o6050716 #o11041205
    #o4040506 #o1040206 #o12031306 #o7031106 #o3030404 #o30105 #o13021504 #o6021003
    #o1020304 #o3010602 #o14001602)
  3966)

;; Thai Font Code 0x2B, Unicode 0xE0B
(add-character-description
  43 16 1 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o10141316 #o4140616 #o2100411 #o4060510 #o14051516 #o6050716 #o2050406 #o13041416
    #o11041205 #o40107 #o12031306 #o10031106 #o2030304 #o13021504 #o7021016 #o4020504
    #o1020211 #o5010703 #o2010403 #o14001602)
  4069)

;; Thai Font Code 0x2C, Unicode 0xE0C
(add-character-description
  44 19 2 0 15 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6141015 #o2140415 #o14131514 #o1130214 #o13121513 #o4120614 #o12111412 #o6110712
    #o2110412 #o7101011 #o50213 #o3040405 #o10031115 #o2030305 #o11021214 #o6020703
    #o20204 #o7011103 #o1010302 #o15001715 #o3000702)
  4873)

;; Thai Font Code 0x2D, Unicode 0xE0D
(add-character-description
  45 20 2 -5 16 18
  #-thai-bitmaps nil #+thai-bitmaps '#(#o13211622 #o16201721 #o11201222 #o17172020 #o12171322 #o10171121 #o10161317 #o2140415
    #o13131615 #o4120514 #o2110412 #o60113 #o1050214 #o3040405 #o11031215 #o2030305
    #o12021315 #o7021003 #o20204 #o10011203 #o1010302 #o16002015 #o3001002)
  5072)

;; Thai Font Code 0x2E, Unicode 0xE0E
(add-character-description
  46 14 1 -5 11 18
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3210622 #o10201121 #o5170721 #o2170321 #o7161021 #o3160617 #o1140315 #o3130414
    #o120114 #o1110312 #o3050513 #o11041222 #o4040605 #o3030504 #o12021322 #o7021003
    #o1020304 #o10011204 #o2010402 #o4001002)
  3704)

;; Thai Font Code 0x2F, Unicode 0xE0F
(add-character-description
  47 14 1 -5 11 18
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2210422 #o10201121 #o6200722 #o7171021 #o4170521 #o1170221 #o2160517 #o5150621
    #o1140315 #o3130414 #o120114 #o1110312 #o3050513 #o11041222 #o4040605 #o3030504
    #o12021322 #o7021003 #o1020304 #o10011204 #o2010402 #o4001002)
  3704)

;; Thai Font Code 0x30, Unicode 0xE10
(add-character-description
  48 13 1 -5 9 18
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7211022 #o5210622 #o1210222 #o5201021 #o2200322 #o10171122 #o3170421 #o170121
    #o7161117 #o4160521 #o1160317 #o6130715 #o5110613 #o2110412 #o4070512 #o1070211
    #o2060507 #o10051114 #o6050706 #o7041015 #o2030705 #o20106 #o1010206 #o2001102)
  3231)

;; Thai Font Code 0x31, Unicode 0xE11
(add-character-description
  49 18 1 0 15 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o10101114 #o2060407 #o11051211 #o6040715 #o4040506 #o2030404 #o15021615 #o12021305
    #o10021104 #o20105 #o16011715 #o13011403 #o7011015 #o4010503 #o1010206 #o14001602
    #o5000702 #o2000402)
  4690)

;; Thai Font Code 0x32, Unicode 0xE12
(add-character-description
  50 19 1 0 16 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7141215 #o15131614 #o6130714 #o3130414 #o14121514 #o6121013 #o4120513 #o13111413
    #o10111112 #o5110612 #o5100711 #o1100315 #o7061010 #o4060510 #o5050706 #o11031314
    #o30210 #o5020604 #o10011203 #o6010703 #o4010503 #o1010303 #o16002015 #o7001002
    #o3000402)
  4935)

;; Thai Font Code 0x33, Unicode 0xE13
(add-character-description
  51 21 2 0 17 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o15142015 #o2140415 #o1130214 #o20122114 #o12121314 #o4120514 #o17112012 #o13111412
    #o2110412 #o16101711 #o50213 #o10041115 #o3040405 #o2030305 #o11021215 #o6020703
    #o20204 #o7011104 #o1010302 #o14001614 #o3000702)
  5299)

;; Thai Font Code 0x34, Unicode 0xE14
(add-character-description
  52 14 1 0 11 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3130414 #o3120513 #o4110612 #o1100315 #o5070711 #o7051010 #o4050507 #o5040705
    #o11031215 #o30210 #o12021315 #o7021003 #o3020403 #o10011203 #o1010303 #o3001002)
  3573)

;; Thai Font Code 0x35, Unicode 0xE15
(add-character-description
  53 14 1 0 11 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3130414 #o3120513 #o5110612 #o5100711 #o1100315 #o7061010 #o4060510 #o5050706
    #o11031315 #o30210 #o5020604 #o10011203 #o6010703 #o4010503 #o1010303 #o7001002
    #o3000402)
  3614)

;; Thai Font Code 0x36, Unicode 0xE16
(add-character-description
  54 14 2 0 10 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2140415 #o1130214 #o4120514 #o2110412 #o50213 #o10041115 #o3040405 #o2030305
    #o11021215 #o6020703 #o20204 #o7011104 #o1010302 #o3000702)
  3555)

;; Thai Font Code 0x37, Unicode 0xE17
(add-character-description
  55 15 1 0 12 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5100614 #o6050710 #o1030304 #o12021315 #o7021005 #o4020515 #o13011415 #o10011103
    #o3010415 #o10103 #o11001302 #o1000301)
  3882)

;; Thai Font Code 0x38, Unicode 0xE18
(add-character-description
  56 13 1 0 9 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3130715 #o130115 #o1070315 #o10051115 #o6050706 #o7041015 #o3030705 #o2020305
    #o20106 #o1010206 #o2001102)
  3231)

;; Thai Font Code 0x39, Unicode 0xE19
(add-character-description
  57 15 1 0 13 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o11141415 #o5130614 #o14121514 #o6120713 #o13111412 #o7111012 #o12101311 #o1030304
    #o4020515 #o3010415 #o10103 #o10001214 #o1000301)
  3894)

;; Thai Font Code 0x3A, Unicode 0xE1A
(add-character-description
  58 14 1 0 11 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5131115 #o1130315 #o1030304 #o4020515 #o3010415 #o10103 #o11001315 #o1000301)
  3631)

;; Thai Font Code 0x3B, Unicode 0xE1B
(add-character-description
  59 14 1 0 11 19
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5211123 #o1210323 #o1110312 #o4100523 #o3070423 #o70111 #o1060307 #o11001323)
  3631)

;; Thai Font Code 0x3C, Unicode 0xE1C
(add-character-description
  60 15 2 0 10 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7111014 #o2110314 #o6070712 #o3070412 #o4050610 #o2030404 #o20115 #o4010503
    #o1010215 #o10001215 #o2000401)
  3762)

;; Thai Font Code 0x3D, Unicode 0xE1D
(add-character-description
  61 15 2 0 10 19
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7171022 #o2170322 #o6150720 #o3150420 #o4130616 #o2110412 #o100123 #o4070511
    #o1070223 #o2060407 #o10001223)
  3762)

;; Thai Font Code 0x3E, Unicode 0xE1E
(add-character-description
  62 16 1 0 13 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o12101314 #o5100614 #o11041210 #o6040710 #o1030304 #o4020515 #o3010415 #o10103
    #o13001515 #o7001105 #o1000301)
  4150)

;; Thai Font Code 0x3F, Unicode 0xE1F
(add-character-description
  63 16 1 0 13 19
  #-thai-bitmaps nil #+thai-bitmaps '#(#o12161322 #o5160622 #o11121216 #o6120716 #o1110312 #o4100523 #o3070423 #o70111
    #o7061113 #o1060307 #o13001523)
  4150)

;; Thai Font Code 0x40, Unicode 0xE20
(add-character-description
  64 14 1 0 11 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1140315 #o3130414 #o120114 #o1110312 #o3050513 #o11041215 #o4040605 #o3030504
    #o12021315 #o7021003 #o1020304 #o10011204 #o2010402 #o4001002)
  3704)

;; Thai Font Code 0x41, Unicode 0xE21
(add-character-description
  65 14 1 0 10 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1140315 #o7131014 #o6120713 #o120114 #o5110612 #o1110212 #o2100311 #o1030304
    #o4020514 #o3010415 #o10103 #o10001215 #o1000301)
  3471)

;; Thai Font Code 0x42, Unicode 0xE22
(add-character-description
  66 14 2 0 10 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2131015 #o100115 #o1070215 #o3060507 #o2050310 #o2030404 #o20105 #o4010503
    #o1010206 #o10001215 #o1000401)
  3511)

;; Thai Font Code 0x43, Unicode 0xE23
(add-character-description
  67 12 1 0 9 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5140715 #o4120514 #o5110712 #o10051113 #o6050706 #o7041014 #o2030705 #o20106
    #o1010205 #o2001102)
  2992)

;; Thai Font Code 0x44, Unicode 0xE24
(add-character-description
  68 14 2 -5 10 18
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2140415 #o1130214 #o4120514 #o2110412 #o50213 #o10041122 #o3040405 #o2030305
    #o11021222 #o6020703 #o20204 #o7011104 #o1010302 #o3000702)
  3555)

;; Thai Font Code 0x45, Unicode 0xE25
(add-character-description
  69 13 2 0 9 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2140415 #o4120514 #o2110412 #o6070712 #o70113 #o5060610 #o1060214 #o2050507
    #o10021115 #o6020703 #o2020303 #o20104 #o7011015 #o1010204 #o2000702)
  3398)

;; Thai Font Code 0x46, Unicode 0xE26
(add-character-description
  70 14 1 -5 11 18
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1140315 #o3130414 #o120114 #o1110312 #o3050513 #o11041222 #o4040605 #o3030504
    #o12021322 #o7021003 #o1020304 #o10011204 #o2010402 #o4001002)
  3704)

;; Thai Font Code 0x47, Unicode 0xE27
(add-character-description
  71 12 1 0 9 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5140715 #o4120514 #o5110712 #o10021113 #o6020703 #o2020303 #o20104 #o7011014
    #o1010204 #o2000702)
  3100)

;; Thai Font Code 0x48, Unicode 0xE28
(add-character-description
  72 14 1 0 12 15
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1120217 #o5110712 #o2110317 #o7071011 #o3070512 #o5060707 #o11051317 #o50212
    #o7041305 #o3040405 #o1030305 #o3021204 #o11011302 #o12001401)
  3535)

;; Thai Font Code 0x49, Unicode 0xE29
(add-character-description
  73 15 1 0 13 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5131115 #o1130315 #o13051406 #o7051007 #o14041505 #o10041107 #o6040706 #o7031004
    #o1030304 #o4020515 #o3010415 #o10103 #o11001315 #o1000301)
  3937)

;; Thai Font Code 0x4A, Unicode 0xE2A
(add-character-description
  74 13 2 0 10 15
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2160417 #o4140516 #o2130414 #o6110714 #o110115 #o5100612 #o1100216 #o2070511
    #o7051117 #o50206 #o6041105 #o40305 #o1031004 #o2021103 #o10001202)
  3430)

;; Thai Font Code 0x4B, Unicode 0xE2B
(add-character-description
  75 15 1 0 13 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5110614 #o6070712 #o7061010 #o10051107 #o12031415 #o1030304 #o4020515 #o14011503
    #o11011206 #o3010415 #o10103 #o12001401 #o1000301)
  3905)

;; Thai Font Code 0x4C, Unicode 0xE2C
(add-character-description
  76 16 1 0 14 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o12141320 #o5140621 #o11101214 #o6100714 #o1070310 #o4060521 #o3050421 #o50107
    #o11041305 #o7041010 #o1040405 #o13021521 #o10021110 #o11011402 #o15001602)
  4150)

;; Thai Font Code 0x4D, Unicode 0xE2D
(add-character-description
  77 13 1 0 10 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3131015 #o3100511 #o1070215 #o5060610 #o2060315 #o2050506 #o1030204 #o11021215
    #o7021003 #o20104 #o10011115 #o1010303 #o3001002)
  3380)

;; Thai Font Code 0x4E, Unicode 0xE2E
(add-character-description
  78 13 2 0 10 15
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2150717 #o2130414 #o4110513 #o110217 #o1100411 #o2050507 #o5040607 #o10031117
    #o6030706 #o30206 #o7021017 #o2020604 #o10001203)
  3430)

;; Thai Font Code 0x4F, Unicode 0xE2F
(add-character-description
  79 12 1 0 9 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3050506 #o5040605 #o1040306 #o6020704 #o3020404 #o20104 #o1010302 #o7001115)
  3089)

;; Thai Font Code 0x50, Unicode 0xE30
(add-character-description
  80 11 1 1 8 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4120613 #o1120313 #o6110712 #o7101011 #o3100413 #o100112 #o1070310 #o4030604
    #o1030304 #o6020703 #o7011002 #o3010404 #o10103 #o1000301)
  2701)

;; Thai Font Code 0x51, Unicode 0xE31
(add-character-description
  81 0 -8 15 9 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3030604 #o6020703 #o1020203 #o7011003 #o2010304 #o10103 #o10001101 #o301)
  0)

;; Thai Font Code 0x52, Unicode 0xE32
(add-character-description
  82 12 1 0 8 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7021015 #o5020603 #o2020303 #o20104 #o6010715 #o1010204 #o2000602)
  2963)

;; Thai Font Code 0x53, Unicode 0xE33
(add-character-description
  83 12 -5 0 14 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o15061621 #o13061407 #o10061107 #o6060710 #o14051521 #o7051010 #o10041406 #o1020203
    #o2010302 #o10102 #o1000201)
  2963)

;; Thai Font Code 0x54, Unicode 0xE34
(add-character-description
  84 0 -11 14 9 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o10031104 #o1030704 #o7021004 #o20104 #o6010702 #o1010202 #o2000601)
  0)

;; Thai Font Code 0x55, Unicode 0xE35
(add-character-description
  85 0 -11 14 9 5
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1040705 #o7031005 #o30105 #o6021003 #o1020203 #o2010602 #o10001105)
  0)

;; Thai Font Code 0x56, Unicode 0xE36
(add-character-description
  86 0 -11 14 10 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1030704 #o7021104 #o20104 #o11011203 #o6011002 #o1010202 #o7001101 #o2000601)
  0)

;; Thai Font Code 0x57, Unicode 0xE37
(add-character-description
  87 0 -11 14 9 5
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1040705 #o7031005 #o30105 #o6021003 #o1020203 #o2010502 #o10001105 #o5000602)
  0)

;; Thai Font Code 0x58, Unicode 0xE38
(add-character-description
  88 0 -5 -5 3 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1020203 #o2010304 #o10102 #o301)
  0)

;; Thai Font Code 0x59, Unicode 0xE39
(add-character-description
  89 0 -8 -5 6 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3030504 #o1020203 #o2010304 #o10102 #o5000604 #o301)
  0)

;; Thai Font Code 0x5A, Unicode 0xE3A
(add-character-description
  90 0 -4 -3 2 2
  #-thai-bitmaps nil #+thai-bitmaps '#(#o202)
  0)

;; Thai Font Code 0x5B, Unicode 0xE3B
(add-character-description
  91 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x5C, Unicode 0xE3C
(add-character-description
  92 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x5D, Unicode 0xE3D
(add-character-description
  93 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x5E, Unicode 0xE3E
(add-character-description
  94 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x5F, Unicode 0xE3F ********** HAND-EDITED BITMAP HERE -- This
;; character + Bitstream rasterizer + this Monotype Thai font produce a bad
;; glyph. See note by make-character-image-if-appropriate in FONTS. This is for
;; bug HQ-4716813 "bad drawing for (Thai) character 0e3f (3647)". (MHD 9/1/04)
;; **********
(add-character-description
  95 16 2 -2 11 19
  '#(#o5201021 #o1200421 #o10171120 #o11161220 #o12131316 #o11121213
     #o10111212 #o5101011 #o1100411 #o10071110 #o11041207 #o7031104
     #o30121 #o5021003 #o20403 #o4000523)
  3469)

;; Thai Font Code 0x60, Unicode 0xE40
(add-character-description
  96 7 1 0 5 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2140415 #o1130214 #o4120514 #o2110412 #o213)
  1802)

;; Thai Font Code 0x61, Unicode 0xE41
(add-character-description
  97 13 2 0 10 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7141115 #o2140415 #o6130714 #o1130214 #o11121214 #o4120514 #o7111112 #o2110412
    #o5000713 #o213)
  3409)

;; Thai Font Code 0x62, Unicode 0xE42
(add-character-description
  98 11 1 0 10 19
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7221123 #o11201222 #o7171120 #o5060622 #o4050606 #o6040723 #o3030605 #o2020305
    #o20106 #o1010206 #o2001202)
  2855)

;; Thai Font Code 0x63, Unicode 0xE43
(add-character-description
  99 12 1 0 10 19
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7221123 #o11201222 #o7171120 #o2060407 #o4040506 #o2030404 #o6020723 #o20105
    #o5010622 #o1010206 #o2000502)
  3077)

;; Thai Font Code 0x64, Unicode 0xE44
(add-character-description
  100 12 0 0 11 19
  #-thai-bitmaps nil #+thai-bitmaps '#(#o10221223 #o12201322 #o10171220 #o3030405 #o6020722 #o7011023 #o4010503 #o2010304
    #o5000702 #o202)
  3077)

;; Thai Font Code 0x65, Unicode 0xE45
(add-character-description
  101 12 1 -5 8 18
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7021022 #o5020603 #o2020303 #o20104 #o6010722 #o1010204 #o2000602)
  2963)

;; Thai Font Code 0x66, Unicode 0xE46
(add-character-description
  102 12 1 -5 9 18
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2060407 #o4040506 #o2030404 #o10021122 #o6020703 #o20105 #o7011022 #o4010503
    #o1010206 #o5000702 #o2000402)
  3022)

;; Thai Font Code 0x67, Unicode 0xE47
(add-character-description
  103 0 -10 14 9 6
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6051006 #o1050306 #o10041106 #o5040705 #o3040405 #o6031104 #o3030504 #o20105
    #o1010702 #o6001001)
  0)

;; Thai Font Code 0x68, Unicode 0xE48
(add-character-description
  104 0 -4 20 1 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o104)
  0)

;; Thai Font Code 0x69, Unicode 0xE49
(add-character-description
  105 0 -7 21 7 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2030304 #o30104 #o3020503 #o1020204 #o5010603 #o6000702 #o202)
  0)

;; Thai Font Code 0x6A, Unicode 0xE4A
(add-character-description
  106 0 -8 20 10 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7021003 #o10011103 #o6010704 #o3010402 #o10204 #o11001202 #o4000601 #o1000301)
  0)

;; Thai Font Code 0x6B, Unicode 0xE4B
(add-character-description
  107 0 -4 20 3 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2010302 #o10102 #o1000203)
  0)

;; Thai Font Code 0x6C, Unicode 0xE4C
(add-character-description
  108 0 -8 21 8 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1030304 #o3010403 #o10103 #o1001001)
  0)

;; Thai Font Code 0x6D, Unicode 0xE4D
(add-character-description
  109 0 -5 14 3 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1020203 #o2010302 #o10102 #o1000201)
  0)

;; Thai Font Code 0x6E, Unicode 0xE4E
(add-character-description
  110 0 -4 20 3 5
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1040305 #o30104 #o1020203 #o10102 #o1000301)
  0)

;; Thai Font Code 0x6F, Unicode 0xE4F
(add-character-description
  111 13 1 0 11 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4110713 #o7101013 #o3100413 #o10071112 #o2070312 #o4040707 #o12031310 #o30110
    #o11021211 #o7021003 #o3020403 #o1020211 #o10011104 #o2010304 #o3001002)
  3316)

;; Thai Font Code 0x70, Unicode 0xE50
(add-character-description
  112 14 1 0 12 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4101012 #o10071111 #o3070412 #o11061211 #o2060311 #o13031406 #o30107 #o12021310
    #o10021103 #o3020403 #o1020210 #o11011204 #o2010304 #o3001102)
  3573)

;; Thai Font Code 0x71, Unicode 0xE51
(add-character-description
  113 15 1 0 13 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3110412 #o4100712 #o12071312 #o2070411 #o5060707 #o10051110 #o7041011 #o4040506
    #o14031510 #o12031304 #o5030704 #o2030304 #o30107 #o13021411 #o1020211 #o11011303
    #o2010403 #o4001102)
  3824)

;; Thai Font Code 0x72, Unicode 0xE52
(add-character-description
  114 16 2 0 12 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2131215 #o5111012 #o10071111 #o6061007 #o12051315 #o10051106 #o4050611 #o13041414
    #o11031305 #o5031005 #o215)
  4109)

;; Thai Font Code 0x73, Unicode 0xE53
(add-character-description
  115 16 2 0 12 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2110412 #o4070511 #o2060407 #o13021412 #o11021203 #o7021003 #o4020503 #o2020303
    #o20110 #o12011312 #o5010712 #o1010211 #o7001202 #o2000502)
  4121)

;; Thai Font Code 0x74, Unicode 0xE54
(add-character-description
  116 15 1 0 13 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o11151316 #o3150416 #o11141415 #o4140716 #o7131116 #o2130415 #o10121213 #o12101312
    #o6101013 #o7071210 #o2070310 #o70113 #o1060215 #o2050407 #o12041305 #o4041006
    #o10031205 #o12021404 #o13001502)
  3926)

;; Thai Font Code 0x75, Unicode 0xE55
(add-character-description
  117 15 1 0 13 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o11151316 #o3150416 #o11141415 #o4140716 #o1140215 #o7131116 #o2130415 #o10121213
    #o12101312 #o6101013 #o100214 #o7071210 #o70310 #o1060407 #o7051006 #o2050506
    #o7041205 #o5040606 #o11031304 #o11021403 #o6020706 #o7011102 #o13001502)
  3926)

;; Thai Font Code 0x76, Unicode 0xE56
(add-character-description
  118 15 0 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7151016 #o11141216 #o14131515 #o12131316 #o6131015 #o13121415 #o10111116 #o5110614
    #o14101613 #o6101011 #o12071310 #o13061510 #o3060510 #o5051307 #o2030406 #o1010303
    #o201)
  3791)

;; Thai Font Code 0x77, Unicode 0xE57
(add-character-description
  119 20 2 0 16 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2140415 #o14121515 #o4120514 #o15111614 #o2110412 #o16101713 #o13051415 #o11051206
    #o7051006 #o4050506 #o2050306 #o50113 #o12041315 #o5040715 #o1040214 #o7031205
    #o2030505 #o16002010)
  5011)

;; Thai Font Code 0x78, Unicode 0xE58
(add-character-description
  120 16 1 0 14 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o11141215 #o12131515 #o7131014 #o3130415 #o10121214 #o4120515 #o2120314 #o12111412
    #o5111013 #o15101613 #o14071512 #o11071211 #o12061507 #o2060307 #o60112 #o5050606
    #o1050214 #o11041205 #o2040506 #o5031105 #o14021503 #o11021304 #o13011404 #o14001602)
  4139)

;; Thai Font Code 0x79, Unicode 0xE59
(add-character-description
  121 18 2 0 15 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o11141215 #o2140415 #o4120514 #o10111115 #o2110412 #o14071510 #o7071014 #o14061607
    #o6060711 #o13051410 #o11051206 #o6051006 #o2050306 #o50113 #o12041307 #o5040607
    #o1040214 #o7031205 #o2030505 #o15001706)
  4593)

;; Thai Font Code 0x7A, Unicode 0xE5A
(add-character-description
  122 16 1 0 12 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2050406 #o4040505 #o1040305 #o5020604 #o3020404 #o20104 #o1010302 #o12001415
    #o6001015)
  4019)

;; Thai Font Code 0x7B, Unicode 0xE5B
(add-character-description
  123 23 1 0 21 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3100612 #o22072311 #o6070711 #o2070312 #o21062211 #o16061711 #o13061411 #o7061011
    #o23052410 #o15051607 #o20042110 #o12041307 #o10041107 #o24032505 #o17032006 #o14031506
    #o11031205 #o30107 #o2020303 #o7011002 #o1010211 #o2000702)
  5938)

;; Thai Font Code 0x7C, Unicode 0xE5C
(add-character-description
  124 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x7D, Unicode 0xE5D
(add-character-description
  125 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x7E, Unicode 0xE5E
(add-character-description
  126 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x7F, Unicode 0xE5F
(add-character-description
  127 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x80, Unicode 0xE60
(add-character-description
  128 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x81, Unicode 0xE61
(add-character-description
  129 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x82, Unicode 0xE62
(add-character-description
  130 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x83, Unicode 0xE63
(add-character-description
  131 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x84, Unicode 0xE64
(add-character-description
  132 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x85, Unicode 0xE65
(add-character-description
  133 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x86, Unicode 0xE66
(add-character-description
  134 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x87, Unicode 0xE67
(add-character-description
  135 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x88, Unicode 0xE68
(add-character-description
  136 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x89, Unicode 0xE69
(add-character-description
  137 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x8A, Unicode 0xE6A
(add-character-description
  138 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x8B, Unicode 0xE6B
(add-character-description
  139 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x8C, Unicode 0xE6C
(add-character-description
  140 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x8D, Unicode 0xE6D
(add-character-description
  141 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x8E, Unicode 0xE6E
(add-character-description
  142 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x8F, Unicode 0xE6F
(add-character-description
  143 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x90, Unicode 0xE70
(add-character-description
  144 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x91, Unicode 0xE71
(add-character-description
  145 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x92, Unicode 0xE72
(add-character-description
  146 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x93, Unicode 0xE73
(add-character-description
  147 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x94, Unicode 0xE74
(add-character-description
  148 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x95, Unicode 0xE75
(add-character-description
  149 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x96, Unicode 0xE76
(add-character-description
  150 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x97, Unicode 0xE77
(add-character-description
  151 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x98, Unicode 0xE78
(add-character-description
  152 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x99, Unicode 0xE79
(add-character-description
  153 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x9A, Unicode 0xE7A
(add-character-description
  154 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x9B, Unicode 0xE7B
(add-character-description
  155 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x9C, Unicode 0xE7C
(add-character-description
  156 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x9D, Unicode 0xE7D
(add-character-description
  157 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x9E, Unicode 0xE7E
(add-character-description
  158 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0x9F, Unicode 0xE7F
(add-character-description
  159 23 3 0 17 17
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1202021 #o20012121 #o10121 #o2101)
  5973)

;; Thai Font Code 0xA0, Unicode 0xF700
(add-character-description
  160 13 1 0 9 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6130715 #o5110613 #o2110412 #o4070512 #o1070211 #o2060507 #o10051114 #o6050706
    #o7041015 #o2030705 #o20106 #o1010206 #o2001102)
  3231)

;; Thai Font Code 0xA1, Unicode 0xF701
(add-character-description
  161 0 -13 14 9 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o10031104 #o1030704 #o7021004 #o20104 #o6010702 #o1010202 #o2000601)
  0)

;; Thai Font Code 0xA2, Unicode 0xF702
(add-character-description
  162 0 -13 14 9 5
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1040705 #o7031005 #o30105 #o6021003 #o1020203 #o2010602 #o10001105)
  0)

;; Thai Font Code 0xA3, Unicode 0xF703
(add-character-description
  163 0 -13 14 10 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1030704 #o7021104 #o20104 #o11011203 #o6011002 #o1010202 #o7001101 #o2000601)
  0)

;; Thai Font Code 0xA4, Unicode 0xF704
(add-character-description
  164 0 -13 14 9 5
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1040705 #o7031005 #o30105 #o6021003 #o1020203 #o2010502 #o10001105 #o5000602)
  0)

;; Thai Font Code 0xA5, Unicode 0xF705
(add-character-description
  165 0 -8 14 1 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o104)
  0)

;; Thai Font Code 0xA6, Unicode 0xF706
(add-character-description
  166 0 -11 15 7 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2030304 #o30104 #o3020503 #o1020204 #o5010603 #o6000702 #o202)
  0)

;; Thai Font Code 0xA7, Unicode 0xF707
(add-character-description
  167 0 -14 14 10 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7021003 #o10011103 #o6010704 #o3010402 #o10204 #o11001202 #o4000601 #o1000301)
  0)

;; Thai Font Code 0xA8, Unicode 0xF708
(add-character-description
  168 0 -8 14 3 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2010302 #o10102 #o1000203)
  0)

;; Thai Font Code 0xA9, Unicode 0xF709
(add-character-description
  169 0 -12 15 8 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1030304 #o3010403 #o10103 #o1001001)
  0)

;; Thai Font Code 0xAA, Unicode 0xF70A
(add-character-description
  170 0 -4 14 1 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o104)
  0)

;; Thai Font Code 0xAB, Unicode 0xF70B
(add-character-description
  171 0 -7 15 7 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2030304 #o30104 #o3020503 #o1020204 #o5010603 #o6000702 #o202)
  0)

;; Thai Font Code 0xAC, Unicode 0xF70C
(add-character-description
  172 0 -8 14 10 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7021003 #o10011103 #o6010704 #o3010402 #o10204 #o11001202 #o4000601 #o1000301)
  0)

;; Thai Font Code 0xAD, Unicode 0xF70D
(add-character-description
  173 0 -4 14 3 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2010302 #o10102 #o1000203)
  0)

;; Thai Font Code 0xAE, Unicode 0xF70E
(add-character-description
  174 0 -8 15 8 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1030304 #o3010403 #o10103 #o1001001)
  0)

;; Thai Font Code 0xAF, Unicode 0xF70F
(add-character-description
  175 20 2 0 16 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2140415 #o13131615 #o4120514 #o2110412 #o60113 #o1050214 #o3040405 #o11031215
    #o2030305 #o12021315 #o7021003 #o20204 #o10011203 #o1010302 #o16002015 #o3001002)
  5072)
