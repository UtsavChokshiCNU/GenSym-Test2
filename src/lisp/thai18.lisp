;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module THAI18

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.



;; 50 1 11 18 12 2003 3 NIL 
;; 12/18/2003



(def-ab-font
  THAI18	; ab-font-name
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



;; Thai Font Code 0x20, Unicode 0xE00
(add-character-description
  32 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x21, Unicode 0xE01
(add-character-description
  33 10 1 0 9 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o50212 #o2040405 #o10021112 #o6020703 #o2020303 #o20104 #o7011012 #o1010204
    #o2000702)
  2667)

;; Thai Font Code 0x22, Unicode 0xE02
(add-character-description
  34 11 0 0 11 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7101112 #o4100512 #o2050306 #o5040612 #o3040405 #o7021004 #o5020603 #o2020304
    #o20105 #o6010712 #o1010206 #o11001312 #o2000602)
  2903)

;; Thai Font Code 0x23, Unicode 0xE03
(add-character-description
  35 12 0 0 11 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7101112 #o4100512 #o2050306 #o3040405 #o5030712 #o2030304 #o20105 #o6011003
    #o3010503 #o1010206 #o11001312 #o5000602 #o2000302)
  2979)

;; Thai Font Code 0x24, Unicode 0xE04
(add-character-description
  36 11 1 0 9 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4060507 #o2060312 #o5050606 #o3050407 #o4040505 #o10021112 #o6020703 #o2020303
    #o20106 #o7011012 #o1010212 #o2000702)
  2723)

;; Thai Font Code 0x25, Unicode 0xE05
(add-character-description
  37 11 1 0 9 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4060507 #o2060312 #o5050606 #o3050407 #o4040505 #o10021112 #o6020703 #o2020303
    #o20106 #o7011012 #o4010503 #o1010212 #o5000702 #o2000402)
  2723)

;; Thai Font Code 0x26, Unicode 0xE06
(add-character-description
  38 12 0 0 11 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4110612 #o10101111 #o7071010 #o3070412 #o4060507 #o2050306 #o3040405 #o5030711
    #o2030304 #o20105 #o6011003 #o3010503 #o1010206 #o11001312 #o5000602 #o2000302)
  2979)

;; Thai Font Code 0x27, Unicode 0xE07
(add-character-description
  39 8 0 0 7 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5110612 #o4100512 #o3070411 #o1050207 #o2040310 #o30205 #o4020503 #o5010711
    #o3010402 #o4000601)
  2111)

;; Thai Font Code 0x28, Unicode 0xE08
(add-character-description
  40 10 0 0 9 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5110612 #o6100712 #o4070611 #o2060307 #o3050507 #o1050206 #o2040405 #o10021111
    #o6020703 #o2020303 #o20103 #o7011012 #o1010203 #o2000702)
  2492)

;; Thai Font Code 0x29, Unicode 0xE09
(add-character-description
  41 11 0 0 11 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o10111212 #o4110512 #o4100611 #o12071312 #o5070710 #o11061207 #o1060207 #o2050412
    #o50106 #o1040305 #o6020703 #o2020303 #o20103 #o7011111 #o1010203 #o2000702)
  2920)

;; Thai Font Code 0x2A, Unicode 0xE0A
(add-character-description
  42 12 0 0 12 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7111113 #o4110513 #o1050306 #o11041313 #o5040713 #o3040405 #o40205 #o10031204
    #o11021303 #o6021004 #o20304 #o2010702 #o12001402)
  2975)

;; Thai Font Code 0x2B, Unicode 0xE0B
(add-character-description
  43 12 0 0 12 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7111113 #o4110513 #o2060307 #o3050406 #o11041313 #o5040613 #o2040305 #o10031204
    #o6030713 #o30106 #o11021303 #o7021004 #o4020504 #o1020207 #o5010703 #o2010403
    #o12001402)
  3052)

;; Thai Font Code 0x2C, Unicode 0xE0C
(add-character-description
  44 14 1 0 13 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6110712 #o1110312 #o12101311 #o3100411 #o11071210 #o5070611 #o2070310 #o6060707
    #o50211 #o2040405 #o10021111 #o6020703 #o2020303 #o20104 #o7011012 #o1010204
    #o13001512 #o2000702)
  3655)

;; Thai Font Code 0x2D, Unicode 0xE0D
(add-character-description
  45 15 1 -4 13 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o12151316 #o10151116 #o13141415 #o11141216 #o7141015 #o14131514 #o7131214 #o1110312
    #o11101312 #o3100411 #o2070310 #o50211 #o2040405 #o10021112 #o6020703 #o2020303
    #o20104 #o7011012 #o1010204 #o13001512 #o2000702)
  3804)

;; Thai Font Code 0x2E, Unicode 0xE0E
(add-character-description
  46 11 0 -4 10 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4150616 #o6141015 #o3140415 #o4130714 #o1110312 #o100111 #o1070210 #o2050411
    #o3040505 #o11021216 #o7021003 #o3020403 #o1020204 #o10011116 #o2010304 #o3001002)
  2778)

;; Thai Font Code 0x2F, Unicode 0xE0F
(add-character-description
  47 11 0 -4 10 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5150616 #o2150316 #o6141015 #o3140416 #o1140215 #o2130414 #o4120515 #o1110312
    #o100111 #o1070210 #o2050411 #o3040505 #o11021216 #o7021003 #o3020403 #o1020204
    #o10011116 #o2010304 #o3001002)
  2778)

;; Thai Font Code 0x30, Unicode 0xE10
(add-character-description
  48 9 1 -4 8 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5150616 #o2150416 #o3140515 #o1140215 #o6131016 #o2130514 #o6110712 #o4110512
    #o5100612 #o2100311 #o3070511 #o1070210 #o2060407 #o6041011 #o2030605 #o20205
    #o1001002)
  2424)

;; Thai Font Code 0x31, Unicode 0xE11
(add-character-description
  49 14 0 0 13 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7061011 #o2050306 #o3040405 #o10031106 #o5030712 #o2030304 #o13021412 #o20105
    #o14011512 #o11011203 #o6011003 #o3010503 #o1010206 #o12001402 #o5000602 #o2000302)
  3518)

;; Thai Font Code 0x32, Unicode 0xE12
(add-character-description
  50 14 1 0 13 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6110712 #o12101311 #o3100411 #o11071210 #o2070312 #o6060707 #o4060510 #o5050611
    #o3050406 #o4040505 #o10021111 #o6020703 #o2020303 #o20106 #o7011012 #o4010503
    #o1010212 #o13001512 #o5000702 #o2000402)
  3701)

;; Thai Font Code 0x33, Unicode 0xE13
(add-character-description
  51 16 1 0 14 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o13111512 #o1110312 #o3100411 #o15071611 #o11071211 #o2070310 #o14061507 #o50211
    #o2040405 #o10021112 #o6020703 #o2020303 #o20104 #o7011012 #o1010204 #o12001411
    #o2000702)
  3975)

;; Thai Font Code 0x34, Unicode 0xE14
(add-character-description
  52 10 1 0 9 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3100411 #o4060510 #o2060312 #o5050607 #o3050406 #o4040505 #o10021112 #o6020703
    #o2020303 #o20106 #o7011012 #o1010212 #o2000702)
  2680)

;; Thai Font Code 0x35, Unicode 0xE15
(add-character-description
  53 11 1 0 9 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3100411 #o2070312 #o4060510 #o5050607 #o3050406 #o4040505 #o10021112 #o6020703
    #o2020303 #o20106 #o7011012 #o4010503 #o1010212 #o5000702 #o2000402)
  2710)

;; Thai Font Code 0x36, Unicode 0xE16
(add-character-description
  54 10 1 0 9 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1110312 #o3100411 #o2070310 #o50211 #o2040405 #o10021112 #o6020703 #o2020303
    #o20104 #o7011012 #o1010204 #o2000702)
  2667)

;; Thai Font Code 0x37, Unicode 0xE17
(add-character-description
  55 11 0 0 11 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4060511 #o5040606 #o11021212 #o6020704 #o1020203 #o12011312 #o2010412 #o10102
    #o7001202 #o1000301)
  2912)

;; Thai Font Code 0x38, Unicode 0xE18
(add-character-description
  56 9 1 0 8 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3100612 #o100112 #o1060312 #o6041012 #o2030605 #o20205 #o1001002)
  2424)

;; Thai Font Code 0x39, Unicode 0xE19
(add-character-description
  57 11 0 0 11 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o10111212 #o4110512 #o4100611 #o12071311 #o5070710 #o11061207 #o1020203 #o2010412
    #o10102 #o7001111 #o1000301)
  2920)

;; Thai Font Code 0x3A, Unicode 0xE1A
(add-character-description
  58 11 0 0 10 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4101012 #o1100212 #o1020203 #o2010412 #o10102 #o10001212 #o1000301)
  2723)

;; Thai Font Code 0x3B, Unicode 0xE1B
(add-character-description
  59 11 0 0 10 15
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4151017 #o1150217 #o1070210 #o2060417 #o60107 #o1050306 #o10001217)
  2723)

;; Thai Font Code 0x3C, Unicode 0xE1C
(add-character-description
  60 11 1 0 9 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6070711 #o2070311 #o5050607 #o3050407 #o4040505 #o2020303 #o3010402 #o10212
    #o7001112 #o1000301)
  2822)

;; Thai Font Code 0x3D, Unicode 0xE1D
(add-character-description
  61 11 1 0 9 15
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6140716 #o2140316 #o5120614 #o3120414 #o4110512 #o2070310 #o3060407 #o60217
    #o1050306 #o7001117)
  2822)

;; Thai Font Code 0x3E, Unicode 0xE1E
(add-character-description
  62 12 0 0 12 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o11061211 #o4060511 #o10041106 #o7031104 #o5030606 #o1020203 #o2010412 #o10102
    #o12001412 #o6001003 #o1000301)
  3113)

;; Thai Font Code 0x3F, Unicode 0xE1F
(add-character-description
  63 12 0 0 12 15
  #-thai-bitmaps nil #+thai-bitmaps '#(#o11131216 #o4130516 #o10111113 #o7101111 #o5100613 #o1070210 #o2060417 #o60107
    #o6051010 #o1050306 #o12001417)
  3113)

;; Thai Font Code 0x40, Unicode 0xE20
(add-character-description
  64 11 0 0 10 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1110312 #o100111 #o1070210 #o2050411 #o3040505 #o11021212 #o7021003 #o3020403
    #o1020204 #o10011112 #o2010304 #o3001002)
  2778)

;; Thai Font Code 0x41, Unicode 0xE21
(add-character-description
  65 10 0 0 9 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6110712 #o1110312 #o5100711 #o4070610 #o70111 #o1060207 #o1020203 #o2010411
    #o10102 #o7001112 #o1000301)
  2603)

;; Thai Font Code 0x42, Unicode 0xE22
(add-character-description
  66 10 1 0 9 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2100712 #o50212 #o2040405 #o2020303 #o3010402 #o10204 #o7001112 #o1000301)
  2634)

;; Thai Font Code 0x43, Unicode 0xE23
(add-character-description
  67 9 1 0 7 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4110512 #o3100411 #o4070510 #o5050612 #o6040711 #o2030605 #o1020205 #o10105
    #o1000702)
  2244)

;; Thai Font Code 0x44, Unicode 0xE24
(add-character-description
  68 10 1 -4 9 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1110312 #o3100411 #o2070310 #o50211 #o2040405 #o10021116 #o6020703 #o2020303
    #o20104 #o7011016 #o1010204 #o2000702)
  2667)

;; Thai Font Code 0x45, Unicode 0xE25
(add-character-description
  69 10 1 0 8 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2110312 #o3100411 #o2070310 #o4060507 #o60111 #o5050610 #o1050212 #o2040506
    #o7021012 #o5020603 #o20103 #o6010712 #o1010203 #o2000602)
  2548)

;; Thai Font Code 0x46, Unicode 0xE26
(add-character-description
  70 11 0 -4 10 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1110312 #o100111 #o1070210 #o2050411 #o3040505 #o11021216 #o7021003 #o3020403
    #o1020204 #o10011116 #o2010304 #o3001002)
  2778)

;; Thai Font Code 0x47, Unicode 0xE27
(add-character-description
  71 9 0 0 8 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5110612 #o4100511 #o5070610 #o7021011 #o5020603 #o20103 #o6010712 #o1010203
    #o2000602)
  2325)

;; Thai Font Code 0x48, Unicode 0xE28
(add-character-description
  72 10 1 0 10 12
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4100511 #o2100314 #o5070610 #o3070411 #o4060507 #o7051114 #o6041105 #o2040305
    #o40110 #o1030214 #o2021004 #o10011102 #o10001201)
  2651)

;; Thai Font Code 0x49, Unicode 0xE29
(add-character-description
  73 12 0 0 12 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4101012 #o1100212 #o6050706 #o12041305 #o7041006 #o5040605 #o13031404 #o6030704
    #o1020203 #o2010412 #o10102 #o10001212 #o1000301)
  2953)

;; Thai Font Code 0x4A, Unicode 0xE2A
(add-character-description
  74 10 1 0 9 12
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2130314 #o3120413 #o2110312 #o4100511 #o100113 #o5070612 #o1070214 #o2060510
    #o6051014 #o5041005 #o40205 #o1030704 #o2021003 #o7001102)
  2573)

;; Thai Font Code 0x4B, Unicode 0xE2B
(add-character-description
  75 11 0 0 11 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4070511 #o5060610 #o6050706 #o7041005 #o11021212 #o1020203 #o12011312 #o10011105
    #o2010412 #o10102 #o11001201 #o1000301)
  2929)

;; Thai Font Code 0x4C, Unicode 0xE2C
(add-character-description
  76 12 0 0 13 13
  #-thai-bitmaps nil #+thai-bitmaps '#(#o11111214 #o4110514 #o10061111 #o5060611 #o1050206 #o2040415 #o40105 #o11031204
    #o6031006 #o1030304 #o12021415 #o10021103 #o11011302 #o14001502)
  3113)

;; Thai Font Code 0x4D, Unicode 0xE2D
(add-character-description
  77 10 0 0 9 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3100712 #o3060407 #o4050506 #o1050312 #o2040405 #o6020703 #o2020303 #o20103
    #o7011112 #o1010203 #o2000702)
  2535)

;; Thai Font Code 0x4E, Unicode 0xE2E
(add-character-description
  78 10 1 0 8 12
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2120514 #o2100311 #o3070410 #o70214 #o1060307 #o5050714 #o1040405 #o4030705
    #o30204 #o1020703 #o6001002)
  2573)

;; Thai Font Code 0x4F, Unicode 0xE2F
(add-character-description
  79 9 0 0 8 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2040405 #o4030505 #o1030205 #o5020604 #o2020303 #o20104 #o1010202 #o6001012)
  2317)

;; Thai Font Code 0x50, Unicode 0xE30
(add-character-description
  80 8 1 1 6 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3070410 #o1070210 #o4060507 #o2060310 #o60107 #o5050606 #o1050206 #o3020403
    #o1020203 #o4010502 #o2010303 #o10102 #o5000601 #o1000201)
  2026)

;; Thai Font Code 0x51, Unicode 0xE31
(add-character-description
  81 0 -7 12 7 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3020503 #o1020203 #o5010602 #o2010303 #o10102 #o6000701 #o301)
  0)

;; Thai Font Code 0x52, Unicode 0xE32
(add-character-description
  82 9 0 0 8 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7021012 #o5020603 #o20103 #o6010712 #o1010203 #o2000602)
  2223)

;; Thai Font Code 0x53, Unicode 0xE33
(add-character-description
  83 9 -4 0 12 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o13061416 #o11061207 #o4060507 #o12051316 #o5050607 #o6041206 #o1020203 #o2010302
    #o10102 #o1000201)
  2223)

;; Thai Font Code 0x54, Unicode 0xE34
(add-character-description
  84 0 -9 11 7 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6020703 #o1020403 #o4010603 #o10103 #o1000401)
  0)

;; Thai Font Code 0x55, Unicode 0xE35
(add-character-description
  85 0 -9 11 7 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1030404 #o4020604 #o20104 #o1010502 #o6000704)
  0)

;; Thai Font Code 0x56, Unicode 0xE36
(add-character-description
  86 0 -9 11 8 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1030404 #o4020704 #o20104 #o7011003 #o1010602 #o6001001)
  0)

;; Thai Font Code 0x57, Unicode 0xE37
(add-character-description
  87 0 -9 11 7 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1030404 #o5020604 #o20104 #o1010402 #o6000704 #o4000504)
  0)

;; Thai Font Code 0x58, Unicode 0xE38
(add-character-description
  88 0 -4 -4 2 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1020203 #o202)
  0)

;; Thai Font Code 0x59, Unicode 0xE39
(add-character-description
  89 0 -6 -4 4 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1020303 #o3000403 #o202)
  0)

;; Thai Font Code 0x5A, Unicode 0xE3A
(add-character-description
  90 0 -3 -3 2 2
  #-thai-bitmaps nil #+thai-bitmaps '#(#o202)
  0)

;; Thai Font Code 0x5B, Unicode 0xE3B
(add-character-description
  91 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x5C, Unicode 0xE3C
(add-character-description
  92 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x5D, Unicode 0xE3D
(add-character-description
  93 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x5E, Unicode 0xE3E
(add-character-description
  94 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x5F, Unicode 0xE3F ********** HAND-EDITED BITMAP HERE -- This
;; character + Bitstream rasterizer + this Monotype Thai font produce a bad
;; glyph. See note by make-character-image-if-appropriate in FONTS. This is for
;; bug HQ-4716813 "bad drawing for (Thai) character 0e3f (3647)". (MHD 9/1/04)
;; **********
(add-character-description
  95 10 1 -2 8 15
  '#(#o4140615 #o1140315 #o6130714 #o7111014 #o6101011 #o4070610 #o1070310
     #o6030707 #o30115 #o4020603 #o20303 #o3000417)
  2602)


;; Thai Font Code 0x60, Unicode 0xE40
(add-character-description
  96 5 1 0 4 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1110312 #o3100411 #o2070310 #o211)
  1352)

;; Thai Font Code 0x61, Unicode 0xE41
(add-character-description
  97 10 1 0 9 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6111012 #o1110312 #o10101111 #o3100411 #o7071010 #o2070310 #o5000711 #o211)
  2557)

;; Thai Font Code 0x62, Unicode 0xE42
(add-character-description
  98 8 0 0 8 15
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6160717 #o7151016 #o6140715 #o4050516 #o5040617 #o2030505 #o20105 #o1010205
    #o2001002)
  2142)

;; Thai Font Code 0x63, Unicode 0xE43
(add-character-description
  99 9 0 0 8 15
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6160717 #o7151016 #o6140715 #o2050306 #o3040405 #o2030304 #o4020516 #o20105
    #o5010617 #o1010206 #o2000502)
  2308)

;; Thai Font Code 0x64, Unicode 0xE44
(add-character-description
  100 9 0 0 8 15
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6160717 #o7151016 #o6140715 #o2030304 #o4020516 #o1020303 #o5010617 #o3000502
    #o202)
  2308)

;; Thai Font Code 0x65, Unicode 0xE45
(add-character-description
  101 9 0 -4 8 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7021016 #o5020603 #o20103 #o6010716 #o1010203 #o2000602)
  2223)

;; Thai Font Code 0x66, Unicode 0xE46
(add-character-description
  102 9 0 -4 8 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2050306 #o3040405 #o2030304 #o20105 #o6011016 #o4010503 #o1010206 #o5000602
    #o2000402)
  2266)

;; Thai Font Code 0x67, Unicode 0xE47
(add-character-description
  103 0 -8 11 7 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4030504 #o1030204 #o5020704 #o2020403 #o10103 #o1000601)
  0)

;; Thai Font Code 0x68, Unicode 0xE48
(add-character-description
  104 0 -3 15 1 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o103)
  0)

;; Thai Font Code 0x69, Unicode 0xE49
(add-character-description
  105 0 -5 15 5 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1030204 #o2020303 #o20104 #o3010403 #o4000502 #o202)
  0)

;; Thai Font Code 0x6A, Unicode 0xE4A
(add-character-description
  106 0 -6 16 8 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5020603 #o6010702 #o4010503 #o2010302 #o10103 #o7001001 #o3000401 #o1000201)
  0)

;; Thai Font Code 0x6B, Unicode 0xE4B
(add-character-description
  107 0 -4 15 3 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2010302 #o10102 #o1000203)
  0)

;; Thai Font Code 0x6C, Unicode 0xE4C
(add-character-description
  108 0 -6 16 6 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1020203 #o2010302 #o10102 #o1000601)
  0)

;; Thai Font Code 0x6D, Unicode 0xE4D
(add-character-description
  109 0 -4 11 3 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1020203 #o2010302 #o10102 #o1000201)
  0)

;; Thai Font Code 0x6E, Unicode 0xE4E
(add-character-description
  110 0 -4 14 3 5
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1040305 #o20104 #o1010202 #o301)
  0)

;; Thai Font Code 0x6F, Unicode 0xE4F
(add-character-description
  111 10 0 0 9 9
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3070611 #o6061010 #o2060310 #o7031106 #o3030505 #o30106 #o2020303 #o6011003
    #o1010210 #o2000602)
  2487)

;; Thai Font Code 0x70, Unicode 0xE50
(add-character-description
  112 10 1 0 9 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3060610 #o6050710 #o2050310 #o10021106 #o6020703 #o2020303 #o20106 #o7011007
    #o1010207 #o2000702)
  2680)

;; Thai Font Code 0x71, Unicode 0xE51
(add-character-description
  113 11 1 0 10 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3070510 #o7061010 #o3060607 #o6050706 #o2050310 #o10041110 #o4040705 #o3030604
    #o1030207 #o11021206 #o6020703 #o20106 #o7011104 #o1010303 #o3000702)
  2868)

;; Thai Font Code 0x72, Unicode 0xE52
(add-character-description
  114 12 1 0 10 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6101012 #o2100412 #o5070612 #o6060707 #o5050606 #o10041112 #o6040705 #o4040512
    #o11031212 #o3030407 #o7021104 #o4020604 #o212)
  3082)

;; Thai Font Code 0x73, Unicode 0xE53
(add-character-description
  115 12 1 0 10 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2070310 #o3060407 #o2050306 #o10021110 #o1020210 #o11011210 #o4010610 #o10107
    #o6001102 #o1000402)
  3091)

;; Thai Font Code 0x74, Unicode 0xE54
(add-character-description
  116 12 0 0 11 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7121213 #o7111312 #o3110513 #o1110212 #o2100313 #o6070713 #o7061007 #o5060613
    #o60211 #o6050706 #o50306 #o1040505 #o2031104 #o5021203 #o11001302)
  2944)

;; Thai Font Code 0x75, Unicode 0xE55
(add-character-description
  117 12 0 0 11 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7121213 #o7111312 #o3110513 #o1110212 #o2100313 #o6070713 #o7061007 #o5060613
    #o60211 #o6050706 #o50306 #o5040605 #o1040405 #o5031104 #o6021203 #o4020505
    #o5010602 #o11001302)
  2944)

;; Thai Font Code 0x76, Unicode 0xE56
(add-character-description
  118 11 0 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6111013 #o4100512 #o5070613 #o11061211 #o4060507 #o10051112 #o3050411 #o4041006
    #o1020205 #o2010307 #o202)
  2844)

;; Thai Font Code 0x77, Unicode 0xE57
(add-character-description
  119 15 1 0 13 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o12111312 #o2110312 #o3100411 #o12071411 #o2070310 #o10041112 #o1040212 #o11031212
    #o4030612 #o30111 #o6021104 #o1020404 #o13001507)
  3758)

;; Thai Font Code 0x78, Unicode 0xE58
(add-character-description
  120 12 1 0 10 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7101112 #o5100611 #o3100412 #o6070711 #o2070312 #o10061107 #o3060610 #o11051211
    #o7051006 #o1050211 #o10041105 #o3040405 #o40110 #o1030305 #o10021103 #o3020704
    #o7011003 #o10001202)
  3104)

;; Thai Font Code 0x79, Unicode 0xE59
(add-character-description
  121 13 1 0 12 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6111012 #o2110312 #o3100411 #o2070310 #o5060711 #o12051306 #o11041206 #o1040212
    #o10031105 #o4030606 #o30111 #o6021004 #o1020404 #o12001405)
  3445)

;; Thai Font Code 0x7A, Unicode 0xE5A
(add-character-description
  122 12 1 0 10 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2040305 #o3030405 #o1030205 #o4020504 #o2020303 #o20104 #o1010202 #o10001212
    #o5000712)
  3014)

;; Thai Font Code 0x7B, Unicode 0xE5B
(add-character-description
  123 17 1 0 16 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o16061707 #o3060510 #o5050607 #o2050310 #o15041706 #o13041407 #o11041207 #o10031105
    #o6030706 #o17022005 #o14021505 #o12021304 #o7021004 #o20106 #o5010602 #o1010207
    #o2000502)
  4454)

;; Thai Font Code 0x7C, Unicode 0xE5C
(add-character-description
  124 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x7D, Unicode 0xE5D
(add-character-description
  125 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x7E, Unicode 0xE5E
(add-character-description
  126 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x7F, Unicode 0xE5F
(add-character-description
  127 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x80, Unicode 0xE60
(add-character-description
  128 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x81, Unicode 0xE61
(add-character-description
  129 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x82, Unicode 0xE62
(add-character-description
  130 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x83, Unicode 0xE63
(add-character-description
  131 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x84, Unicode 0xE64
(add-character-description
  132 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x85, Unicode 0xE65
(add-character-description
  133 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x86, Unicode 0xE66
(add-character-description
  134 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x87, Unicode 0xE67
(add-character-description
  135 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x88, Unicode 0xE68
(add-character-description
  136 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x89, Unicode 0xE69
(add-character-description
  137 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x8A, Unicode 0xE6A
(add-character-description
  138 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x8B, Unicode 0xE6B
(add-character-description
  139 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x8C, Unicode 0xE6C
(add-character-description
  140 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x8D, Unicode 0xE6D
(add-character-description
  141 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x8E, Unicode 0xE6E
(add-character-description
  142 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x8F, Unicode 0xE6F
(add-character-description
  143 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x90, Unicode 0xE70
(add-character-description
  144 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x91, Unicode 0xE71
(add-character-description
  145 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x92, Unicode 0xE72
(add-character-description
  146 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x93, Unicode 0xE73
(add-character-description
  147 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x94, Unicode 0xE74
(add-character-description
  148 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x95, Unicode 0xE75
(add-character-description
  149 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x96, Unicode 0xE76
(add-character-description
  150 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x97, Unicode 0xE77
(add-character-description
  151 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x98, Unicode 0xE78
(add-character-description
  152 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x99, Unicode 0xE79
(add-character-description
  153 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x9A, Unicode 0xE7A
(add-character-description
  154 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x9B, Unicode 0xE7B
(add-character-description
  155 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x9C, Unicode 0xE7C
(add-character-description
  156 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x9D, Unicode 0xE7D
(add-character-description
  157 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x9E, Unicode 0xE7E
(add-character-description
  158 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0x9F, Unicode 0xE7F
(add-character-description
  159 18 2 0 14 14
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1151516 #o15011616 #o10116 #o1601)
  4480)

;; Thai Font Code 0xA0, Unicode 0xF700
(add-character-description
  160 9 1 0 8 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6110712 #o4110512 #o5100612 #o2100311 #o3070511 #o1070210 #o2060407 #o6041011
    #o2030605 #o20205 #o1001002)
  2424)

;; Thai Font Code 0xA1, Unicode 0xF701
(add-character-description
  161 0 -11 11 7 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6020703 #o1020403 #o4010603 #o10103 #o1000401)
  0)

;; Thai Font Code 0xA2, Unicode 0xF702
(add-character-description
  162 0 -11 11 7 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1030404 #o4020604 #o20104 #o1010502 #o6000704)
  0)

;; Thai Font Code 0xA3, Unicode 0xF703
(add-character-description
  163 0 -11 11 8 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1030404 #o4020704 #o20104 #o7011003 #o1010602 #o6001001)
  0)

;; Thai Font Code 0xA4, Unicode 0xF704
(add-character-description
  164 0 -11 11 7 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1030404 #o5020604 #o20104 #o1010402 #o6000704 #o4000504)
  0)

;; Thai Font Code 0xA5, Unicode 0xF705
(add-character-description
  165 0 -6 11 1 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o103)
  0)

;; Thai Font Code 0xA6, Unicode 0xF706
(add-character-description
  166 0 -8 11 5 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1030204 #o2020303 #o20104 #o3010403 #o4000502 #o202)
  0)

;; Thai Font Code 0xA7, Unicode 0xF707
(add-character-description
  167 0 -11 12 8 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5020603 #o6010702 #o4010503 #o2010302 #o10103 #o7001001 #o3000401 #o1000201)
  0)

;; Thai Font Code 0xA8, Unicode 0xF708
(add-character-description
  168 0 -7 11 3 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2010302 #o10102 #o1000203)
  0)

;; Thai Font Code 0xA9, Unicode 0xF709
(add-character-description
  169 0 -9 12 6 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1020203 #o2010302 #o10102 #o1000601)
  0)

;; Thai Font Code 0xAA, Unicode 0xF70A
(add-character-description
  170 0 -3 11 1 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o103)
  0)

;; Thai Font Code 0xAB, Unicode 0xF70B
(add-character-description
  171 0 -5 11 5 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1030204 #o2020303 #o20104 #o3010403 #o4000502 #o202)
  0)

;; Thai Font Code 0xAC, Unicode 0xF70C
(add-character-description
  172 0 -6 12 8 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5020603 #o6010702 #o4010503 #o2010302 #o10103 #o7001001 #o3000401 #o1000201)
  0)

;; Thai Font Code 0xAD, Unicode 0xF70D
(add-character-description
  173 0 -4 11 3 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2010302 #o10102 #o1000203)
  0)

;; Thai Font Code 0xAE, Unicode 0xF70E
(add-character-description
  174 0 -6 12 6 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1020203 #o2010302 #o10102 #o1000601)
  0)

;; Thai Font Code 0xAF, Unicode 0xF70F
(add-character-description
  175 15 1 0 13 10
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1110312 #o11101312 #o3100411 #o2070310 #o50211 #o2040405 #o10021112 #o6020703
    #o2020303 #o20104 #o7011012 #o1010204 #o13001512 #o2000702)
  3804)
