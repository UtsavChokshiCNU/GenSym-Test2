;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module THAI14

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.



;; 50 1 11 18 12 2003 3 NIL 
;; 12/18/2003



(def-ab-font
  THAI14	; ab-font-name
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



;; Thai Font Code 0x20, Unicode 0xE00
(add-character-description
  32 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x21, Unicode 0xE01
(add-character-description
  33 8 1 0 6 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o40110 #o1030204 #o20103 #o5010610 #o1010202 #o2000501)
  2074)

;; Thai Font Code 0x22, Unicode 0xE02
(add-character-description
  34 9 0 0 8 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5070710 #o3070410 #o1040205 #o4030510 #o2030304 #o5020603 #o1020203 #o4010602
    #o10104 #o7001010 #o1000501)
  2257)

;; Thai Font Code 0x23, Unicode 0xE03
(add-character-description
  35 9 0 0 8 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5070710 #o3070410 #o1040205 #o4030510 #o2030304 #o1020203 #o5010603 #o2010402
    #o10104 #o7001010 #o4000501 #o1000201)
  2317)

;; Thai Font Code 0x24, Unicode 0xE04
(add-character-description
  36 8 1 0 7 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3050406 #o1050210 #o4040505 #o2040305 #o3030404 #o20105 #o6010710 #o1010202
    #o1000601)
  2118)

;; Thai Font Code 0x25, Unicode 0xE05
(add-character-description
  37 8 1 0 7 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3050406 #o1050210 #o4040505 #o2040305 #o3030404 #o6020710 #o5010702 #o3010402
    #o10105 #o4000601 #o1000301)
  2118)

;; Thai Font Code 0x26, Unicode 0xE06
(add-character-description
  38 9 0 0 8 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3070410 #o6060707 #o2060307 #o5050607 #o3050406 #o1040205 #o4030507 #o2030304
    #o1020203 #o5010603 #o2010402 #o10104 #o7001010 #o4000501 #o1000201)
  2317)

;; Thai Font Code 0x27, Unicode 0xE07
(add-character-description
  39 6 0 0 6 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4070510 #o3060407 #o2040306 #o30204 #o4020503 #o5010610 #o3010402 #o4000501)
  1642)

;; Thai Font Code 0x28, Unicode 0xE08
(add-character-description
  40 8 0 0 7 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5070610 #o4050507 #o2050306 #o3040405 #o1040205 #o2030304 #o6020710 #o5010702
    #o10202 #o1000601)
  1938)

;; Thai Font Code 0x29, Unicode 0xE09
(add-character-description
  41 9 0 0 9 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7071010 #o3070410 #o10061107 #o4060507 #o7051006 #o5050606 #o1050206 #o2040310
    #o40105 #o1030204 #o6020707 #o5010702 #o10202 #o1000601)
  2271)

;; Thai Font Code 0x2A, Unicode 0xE0A
(add-character-description
  42 9 0 0 9 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5070710 #o3070410 #o1040205 #o7031010 #o4030510 #o2030304 #o30104 #o6021003
    #o5010603 #o10203 #o10001102 #o2000501)
  2314)

;; Thai Font Code 0x2B, Unicode 0xE0B
(add-character-description
  43 9 0 0 10 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5071010 #o3070410 #o1040205 #o10031110 #o4030510 #o2030304 #o6021103 #o1020203
    #o5010603 #o3010402 #o10104 #o11001202 #o4000501 #o1000301)
  2373)

;; Thai Font Code 0x2C, Unicode 0xE0C
(add-character-description
  44 11 1 0 9 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4070510 #o1070210 #o7061007 #o2060407 #o6050707 #o4050506 #o1050206 #o40107
    #o1030204 #o20103 #o5010607 #o1010202 #o10001110 #o2000501)
  2843)

;; Thai Font Code 0x2D, Unicode 0xE0D
(add-character-description
  45 12 1 -3 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7121113 #o11111212 #o5110713 #o6071110 #o1070210 #o2060307 #o1050206 #o40107
    #o1030204 #o20103 #o5010610 #o1010202 #o11001210 #o2000501)
  2958)

;; Thai Font Code 0x2E, Unicode 0xE0E
(add-character-description
  46 8 0 -3 8 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6120713 #o4120513 #o5110612 #o3110412 #o4100611 #o1070210 #o60107 #o1050206
    #o2040307 #o3030404 #o2020303 #o7011013 #o3010402 #o4000701)
  2160)

;; Thai Font Code 0x2F, Unicode 0xE0F
(add-character-description
  47 8 0 -3 8 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5120613 #o1120313 #o6110712 #o3110512 #o110112 #o2100411 #o4070510 #o1070211
    #o60107 #o1050206 #o2040307 #o3030404 #o2020303 #o7011013 #o3010402 #o4000701)
  2160)

;; Thai Font Code 0x30, Unicode 0xE10
(add-character-description
  48 7 1 -3 6 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4120513 #o2120313 #o3110412 #o1110212 #o2100411 #o4070510 #o3060407 #o1060207
    #o2050306 #o50106 #o1040205 #o5030613 #o1020503 #o10103 #o1000601)
  1885)

;; Thai Font Code 0x31, Unicode 0xE11
(add-character-description
  49 11 0 0 10 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5050607 #o1040205 #o6030705 #o4030510 #o2030304 #o1020203 #o11011210 #o7011003
    #o5010603 #o2010402 #o10104 #o10001101 #o4000501 #o1000201)
  2735)

;; Thai Font Code 0x32, Unicode 0xE12
(add-character-description
  50 11 1 0 10 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5070610 #o10061107 #o4060507 #o2060307 #o7051007 #o5050606 #o3050406 #o1050210
    #o4040505 #o2040305 #o3030404 #o6020707 #o5010702 #o3010402 #o10105 #o11001210
    #o4000601 #o1000301)
  2878)

;; Thai Font Code 0x33, Unicode 0xE13
(add-character-description
  51 12 1 0 11 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o11071210 #o1070210 #o12061307 #o6060707 #o2060307 #o11051206 #o7051007 #o1050206
    #o40107 #o1030204 #o20103 #o5010610 #o1010202 #o10001107 #o2000501)
  3091)

;; Thai Font Code 0x34, Unicode 0xE14
(add-character-description
  52 8 1 0 7 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2060307 #o3050406 #o1050210 #o4040505 #o2040305 #o3030404 #o6010710 #o10105
    #o1000601)
  2084)

;; Thai Font Code 0x35, Unicode 0xE15
(add-character-description
  53 8 1 0 7 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2060307 #o3050406 #o1050210 #o4040505 #o2040305 #o3030404 #o6020710 #o5010702
    #o3010402 #o10105 #o4000601 #o1000301)
  2108)

;; Thai Font Code 0x36, Unicode 0xE16
(add-character-description
  54 8 1 0 6 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1070210 #o2060307 #o1050206 #o40107 #o1030204 #o20103 #o5010610 #o1010202
    #o2000501)
  2074)

;; Thai Font Code 0x37, Unicode 0xE17
(add-character-description
  55 9 0 0 8 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3050407 #o4030505 #o1020203 #o7011010 #o5010603 #o2010310 #o10102 #o6000701
    #o1000201)
  2264)

;; Thai Font Code 0x38, Unicode 0xE18
(add-character-description
  56 7 1 0 6 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2070510 #o70110 #o1040210 #o5030610 #o1020503 #o10103 #o1000601)
  1885)

;; Thai Font Code 0x39, Unicode 0xE19
(add-character-description
  57 9 0 0 9 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7071010 #o3070410 #o10061107 #o4060507 #o7051006 #o5050606 #o1020203 #o2010310
    #o10102 #o6000707 #o1000201)
  2271)

;; Thai Font Code 0x3A, Unicode 0xE1A
(add-character-description
  58 8 0 0 8 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3070710 #o1070210 #o1020203 #o2010310 #o10102 #o7001010 #o1000201)
  2118)

;; Thai Font Code 0x3B, Unicode 0xE1B
(add-character-description
  59 8 0 0 8 12
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3130714 #o1130214 #o1060207 #o2050314 #o50106 #o1040205 #o7001014)
  2118)

;; Thai Font Code 0x3C, Unicode 0xE1C
(add-character-description
  60 9 1 0 7 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5060607 #o1060207 #o4050506 #o2050306 #o3040405 #o1020203 #o2010302 #o10110
    #o6000710 #o1000201)
  2195)

;; Thai Font Code 0x3D, Unicode 0xE1D
(add-character-description
  61 9 1 0 7 12
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5120613 #o1120213 #o4110512 #o2110312 #o3100411 #o1060207 #o2050306 #o50114
    #o1040205 #o6000714)
  2195)

;; Thai Font Code 0x3E, Unicode 0xE1E
(add-character-description
  62 9 0 0 9 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7051007 #o3050407 #o6020705 #o4020505 #o1020203 #o2010310 #o10102 #o10001110
    #o5000602 #o1000201)
  2421)

;; Thai Font Code 0x3F, Unicode 0xE1F
(add-character-description
  63 9 0 0 9 12
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7111013 #o3110413 #o6060711 #o4060511 #o1060207 #o2050314 #o50106 #o5040606
    #o1040205 #o10001114)
  2421)

;; Thai Font Code 0x40, Unicode 0xE20
(add-character-description
  64 8 0 0 8 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1070210 #o60107 #o1050206 #o2040307 #o3030404 #o2020303 #o7011010 #o3010402
    #o4000701)
  2160)

;; Thai Font Code 0x41, Unicode 0xE21
(add-character-description
  65 8 0 0 7 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5070610 #o1070210 #o4060507 #o60107 #o3050406 #o1050206 #o1020203 #o2010307
    #o10102 #o6000710 #o1000201)
  2024)

;; Thai Font Code 0x42, Unicode 0xE22
(add-character-description
  66 8 1 0 6 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1070510 #o50110 #o1040305 #o1020203 #o2010302 #o10104 #o5000610 #o1000201)
  2048)

;; Thai Font Code 0x43, Unicode 0xE23
(add-character-description
  67 7 1 0 5 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3070410 #o2060307 #o3050406 #o4030507 #o1020403 #o10103 #o1000501)
  1745)

;; Thai Font Code 0x44, Unicode 0xE24
(add-character-description
  68 8 1 -3 6 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1070210 #o2060307 #o1050206 #o40107 #o1030204 #o20103 #o5010613 #o1010202
    #o2000501)
  2074)

;; Thai Font Code 0x45, Unicode 0xE25
(add-character-description
  69 8 1 0 6 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1070210 #o2060307 #o4050506 #o1050206 #o3040505 #o40107 #o1030404 #o5010610
    #o10102 #o1000501)
  1982)

;; Thai Font Code 0x46, Unicode 0xE26
(add-character-description
  70 8 0 -3 8 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1070210 #o60107 #o1050206 #o2040307 #o3030404 #o2020303 #o7011013 #o3010402
    #o4000701)
  2160)

;; Thai Font Code 0x47, Unicode 0xE27
(add-character-description
  71 7 0 0 6 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4070510 #o3060407 #o4050506 #o5010607 #o10102 #o1000501)
  1808)

;; Thai Font Code 0x48, Unicode 0xE28
(add-character-description
  72 8 1 0 6 9
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3060407 #o1060211 #o4050506 #o2050306 #o3040405 #o5020611 #o20106 #o1010502
    #o5000601)
  2062)

;; Thai Font Code 0x49, Unicode 0xE29
(add-character-description
  73 9 0 0 10 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3070710 #o1070210 #o5040705 #o10031104 #o11021203 #o4020604 #o1020203 #o2010310
    #o10102 #o7001010 #o1000201)
  2297)

;; Thai Font Code 0x4A, Unicode 0xE2A
(add-character-description
  74 8 1 0 7 9
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1100211 #o2070310 #o4060507 #o1060207 #o3050506 #o50110 #o1040405 #o5020611
    #o20103 #o1010602 #o6000701)
  2001)

;; Thai Font Code 0x4B, Unicode 0xE2B
(add-character-description
  75 9 0 0 8 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3060407 #o4040506 #o5030604 #o6020703 #o1020203 #o7011010 #o5010602 #o2010310
    #o10102 #o6000701 #o1000201)
  2278)

;; Thai Font Code 0x4C, Unicode 0xE2C
(add-character-description
  76 9 0 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7101012 #o3100412 #o6050710 #o4050510 #o1050206 #o2040313 #o40105 #o7031004
    #o5030605 #o1030204 #o10021113 #o6020703 #o7011002 #o11001202)
  2421)

;; Thai Font Code 0x4D, Unicode 0xE2D
(add-character-description
  77 8 1 0 6 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1070510 #o1050206 #o2040305 #o40110 #o1030204 #o5010610 #o10102 #o1000501)
  1972)

;; Thai Font Code 0x4E, Unicode 0xE2E
(add-character-description
  78 8 1 0 7 9
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1100511 #o1060207 #o2050306 #o50111 #o1040205 #o1030404 #o4020503 #o20103
    #o5010611 #o1010402 #o6000702)
  2001)

;; Thai Font Code 0x4F, Unicode 0xE2F
(add-character-description
  79 7 0 0 6 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3030404 #o1030204 #o2020304 #o20103 #o4010503 #o1010202 #o5000610)
  1802)

;; Thai Font Code 0x50, Unicode 0xE30
(add-character-description
  80 6 0 1 5 6
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3050406 #o1050206 #o2040306 #o40105 #o4030505 #o3020403 #o1020204 #o2010303
    #o10102 #o4000502 #o1000201)
  1575)

;; Thai Font Code 0x51, Unicode 0xE31
(add-character-description
  81 0 -6 9 5 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1020303 #o3010402 #o4000501 #o202)
  0)

;; Thai Font Code 0x52, Unicode 0xE32
(add-character-description
  82 7 0 0 6 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5010610 #o10102 #o1000501)
  1728)

;; Thai Font Code 0x53, Unicode 0xE33
(add-character-description
  83 7 -4 0 10 12
  #-thai-bitmaps nil #+thai-bitmaps '#(#o11051214 #o4050506 #o5041105 #o1020203 #o2010302 #o10102 #o1000201)
  1728)

;; Thai Font Code 0x54, Unicode 0xE34
(add-character-description
  84 0 -7 9 5 2
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4010502 #o10102 #o1000402)
  0)

;; Thai Font Code 0x55, Unicode 0xE35
(add-character-description
  85 0 -7 9 5 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o20103 #o1010403 #o4000503)
  0)

;; Thai Font Code 0x56, Unicode 0xE36
(add-character-description
  86 0 -7 9 5 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o10303 #o3000503)
  0)

;; Thai Font Code 0x57, Unicode 0xE37
(add-character-description
  87 0 -7 9 5 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3010403 #o10203 #o4000503 #o2000303)
  0)

;; Thai Font Code 0x58, Unicode 0xE38
(add-character-description
  88 0 -3 -3 2 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1020203 #o202)
  0)

;; Thai Font Code 0x59, Unicode 0xE39
(add-character-description
  89 0 -5 -3 4 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1020303 #o3000403 #o202)
  0)

;; Thai Font Code 0x5A, Unicode 0xE3A
(add-character-description
  90 0 -2 -2 1 1
  #-thai-bitmaps nil #+thai-bitmaps '#(#o101)
  0)

;; Thai Font Code 0x5B, Unicode 0xE3B
(add-character-description
  91 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x5C, Unicode 0xE3C
(add-character-description
  92 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x5D, Unicode 0xE3D
(add-character-description
  93 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x5E, Unicode 0xE3E
(add-character-description
  94 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x5F, Unicode 0xE3F ********** HAND-EDITED BITMAP HERE -- This
;; character + Bitstream rasterizer + this Monotype Thai font produce a bad
;; glyph. See note by make-character-image-if-appropriate in FONTS. This is for
;; bug HQ-4716813 "bad drawing for (Thai) character 0e3f (3647)". (MHD 9/1/04)
;; **********
(add-character-description
  95 9 2 -1 6 11
  '#(#o3110512 #o1110212 #o5060611 #o3050506 #o1050206
     #o5020605 #o20112 #o3010502 #o10202 #o2000313)
  1951)

;; Thai Font Code 0x60, Unicode 0xE40
(add-character-description
  96 4 1 0 3 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1070210 #o2060307 #o1050206 #o107)
  1051)

;; Thai Font Code 0x61, Unicode 0xE41
(add-character-description
  97 8 1 0 7 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5070610 #o1070210 #o6060707 #o2060307 #o5050606 #o1050206 #o4000507 #o107)
  1989)

;; Thai Font Code 0x62, Unicode 0xE42
(add-character-description
  98 7 0 0 7 12
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5130614 #o6120713 #o5110612 #o4030513 #o1020403 #o10103 #o1000701)
  1665)

;; Thai Font Code 0x63, Unicode 0xE43
(add-character-description
  99 7 0 0 7 12
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5130614 #o6120713 #o5110612 #o1030204 #o2020303 #o20103 #o4010513 #o10202
    #o1000401)
  1795)

;; Thai Font Code 0x64, Unicode 0xE44
(add-character-description
  100 7 0 0 7 12
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5130614 #o6120713 #o5110612 #o4010513 #o2010303 #o3000501 #o201)
  1795)

;; Thai Font Code 0x65, Unicode 0xE45
(add-character-description
  101 7 0 -3 6 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5010613 #o10102 #o1000501)
  1728)

;; Thai Font Code 0x66, Unicode 0xE46
(add-character-description
  102 7 0 -3 6 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1040205 #o2030304 #o1020303 #o5010613 #o3010402 #o10104 #o4000501 #o1000301)
  1762)

;; Thai Font Code 0x67, Unicode 0xE47
(add-character-description
  103 0 -6 9 5 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1020503 #o10102 #o1000401)
  0)

;; Thai Font Code 0x68, Unicode 0xE48
(add-character-description
  104 0 -3 12 1 2
  #-thai-bitmaps nil #+thai-bitmaps '#(#o102)
  0)

;; Thai Font Code 0x69, Unicode 0xE49
(add-character-description
  105 0 -4 11 5 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o30204 #o1020303 #o3010403 #o4000501 #o202)
  0)

;; Thai Font Code 0x6A, Unicode 0xE4A
(add-character-description
  106 0 -5 12 6 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4010503 #o2010302 #o10103 #o5000602 #o3000403 #o1000201)
  0)

;; Thai Font Code 0x6B, Unicode 0xE4B
(add-character-description
  107 0 -3 12 3 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2010302 #o10102 #o1000203)
  0)

;; Thai Font Code 0x6C, Unicode 0xE4C
(add-character-description
  108 0 -5 12 5 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o10203 #o1000501)
  0)

;; Thai Font Code 0x6D, Unicode 0xE4D
(add-character-description
  109 0 -4 9 3 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1020203 #o2010302 #o10102 #o1000201)
  0)

;; Thai Font Code 0x6E, Unicode 0xE4E
(add-character-description
  110 0 -4 11 3 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1030304 #o20103 #o1010202 #o301)
  0)

;; Thai Font Code 0x6F, Unicode 0xE4F
(add-character-description
  111 8 1 0 6 6
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2050406 #o4040505 #o1040205 #o5020604 #o2020404 #o20104 #o4010502 #o1010202
    #o2000401)
  1934)

;; Thai Font Code 0x70, Unicode 0xE50
(add-character-description
  112 8 1 0 6 6
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2050406 #o4040506 #o1040206 #o5020605 #o20104 #o4010502 #o1010202 #o1000501)
  2084)

;; Thai Font Code 0x71, Unicode 0xE51
(add-character-description
  113 9 1 0 7 6
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2050406 #o5040606 #o1040205 #o4030505 #o6020705 #o2020404 #o20104 #o5010602
    #o1010202 #o2000501)
  2230)

;; Thai Font Code 0x72, Unicode 0xE52
(add-character-description
  114 9 1 0 8 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4070710 #o1070310 #o3060410 #o4050506 #o3040405 #o7031010 #o4030504 #o2030306
    #o5020703 #o3020403 #o110)
  2397)

;; Thai Font Code 0x73, Unicode 0xE53
(add-character-description
  115 9 1 0 7 6
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1050206 #o2040305 #o1030204 #o6010706 #o3010406 #o10106 #o4000601 #o1000301)
  2404)

;; Thai Font Code 0x74, Unicode 0xE54
(add-character-description
  116 9 0 0 8 9
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6101011 #o2100511 #o5070611 #o1070210 #o6060707 #o4060507 #o5050606 #o50107
    #o1040305 #o3030604 #o5020703 #o7001002)
  2290)

;; Thai Font Code 0x75, Unicode 0xE55
(add-character-description
  117 9 0 0 8 9
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6101011 #o2100511 #o5070611 #o1070210 #o6060707 #o4060507 #o5050606 #o50107
    #o1040205 #o4030504 #o2030304 #o5020603 #o3020404 #o6010703 #o4010502 #o7001002)
  2290)

;; Thai Font Code 0x76, Unicode 0xE56
(add-character-description
  118 9 0 0 8 9
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6100711 #o4100511 #o5070611 #o3070410 #o4060507 #o7051010 #o6040705 #o3040405
    #o4030604 #o2030305 #o1010203 #o101)
  2212)

;; Thai Font Code 0x77, Unicode 0xE57
(add-character-description
  119 11 1 0 10 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o7071010 #o1070210 #o2060307 #o10051107 #o1050206 #o6030710 #o3030410 #o30110
    #o4020603 #o1020303 #o11001205)
  2923)

;; Thai Font Code 0x78, Unicode 0xE58
(add-character-description
  120 9 1 0 9 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6070710 #o2070310 #o7061010 #o4060607 #o1060307 #o10051107 #o6050706 #o3050506
    #o7041005 #o40106 #o1030304 #o3020703 #o7011002 #o10001101)
  2414)

;; Thai Font Code 0x79, Unicode 0xE59
(add-character-description
  121 10 1 0 9 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o5070610 #o1070210 #o2060307 #o1050206 #o7041005 #o4040507 #o6030704 #o3030405
    #o30107 #o4020603 #o1020303 #o10001104)
  2679)

;; Thai Font Code 0x7A, Unicode 0xE5A
(add-character-description
  122 9 0 0 8 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3030404 #o1030204 #o2020304 #o20103 #o4010503 #o1010202 #o7001010 #o5000610)
  2344)

;; Thai Font Code 0x7B, Unicode 0xE5B
(add-character-description
  123 14 1 0 12 6
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2050406 #o12041305 #o1040206 #o10031105 #o6030705 #o4030505 #o13021404 #o11021204
    #o7021003 #o5020603 #o3010402 #o10105 #o1000301)
  3464)

;; Thai Font Code 0x7C, Unicode 0xE5C
(add-character-description
  124 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x7D, Unicode 0xE5D
(add-character-description
  125 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x7E, Unicode 0xE5E
(add-character-description
  126 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x7F, Unicode 0xE5F
(add-character-description
  127 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x80, Unicode 0xE60
(add-character-description
  128 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x81, Unicode 0xE61
(add-character-description
  129 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x82, Unicode 0xE62
(add-character-description
  130 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x83, Unicode 0xE63
(add-character-description
  131 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x84, Unicode 0xE64
(add-character-description
  132 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x85, Unicode 0xE65
(add-character-description
  133 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x86, Unicode 0xE66
(add-character-description
  134 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x87, Unicode 0xE67
(add-character-description
  135 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x88, Unicode 0xE68
(add-character-description
  136 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x89, Unicode 0xE69
(add-character-description
  137 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x8A, Unicode 0xE6A
(add-character-description
  138 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x8B, Unicode 0xE6B
(add-character-description
  139 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x8C, Unicode 0xE6C
(add-character-description
  140 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x8D, Unicode 0xE6D
(add-character-description
  141 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x8E, Unicode 0xE6E
(add-character-description
  142 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x8F, Unicode 0xE6F
(add-character-description
  143 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x90, Unicode 0xE70
(add-character-description
  144 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x91, Unicode 0xE71
(add-character-description
  145 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x92, Unicode 0xE72
(add-character-description
  146 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x93, Unicode 0xE73
(add-character-description
  147 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x94, Unicode 0xE74
(add-character-description
  148 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x95, Unicode 0xE75
(add-character-description
  149 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x96, Unicode 0xE76
(add-character-description
  150 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x97, Unicode 0xE77
(add-character-description
  151 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x98, Unicode 0xE78
(add-character-description
  152 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x99, Unicode 0xE79
(add-character-description
  153 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x9A, Unicode 0xE7A
(add-character-description
  154 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x9B, Unicode 0xE7B
(add-character-description
  155 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x9C, Unicode 0xE7C
(add-character-description
  156 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x9D, Unicode 0xE7D
(add-character-description
  157 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x9E, Unicode 0xE7E
(add-character-description
  158 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0x9F, Unicode 0xE7F
(add-character-description
  159 14 2 0 10 11
  #-thai-bitmaps nil #+thai-bitmaps '#(#o1121113 #o11011213 #o10113 #o1201)
  3484)

;; Thai Font Code 0xA0, Unicode 0xF700
(add-character-description
  160 7 1 0 6 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4070510 #o3060407 #o1060207 #o2050306 #o50106 #o1040205 #o5030610 #o1020503
    #o10103 #o1000601)
  1885)

;; Thai Font Code 0xA1, Unicode 0xF701
(add-character-description
  161 0 -8 9 5 2
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4010502 #o10102 #o1000402)
  0)

;; Thai Font Code 0xA2, Unicode 0xF702
(add-character-description
  162 0 -8 9 5 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o20103 #o1010403 #o4000503)
  0)

;; Thai Font Code 0xA3, Unicode 0xF703
(add-character-description
  163 0 -8 9 5 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o10303 #o3000503)
  0)

;; Thai Font Code 0xA4, Unicode 0xF704
(add-character-description
  164 0 -8 9 5 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o3010403 #o10203 #o4000503 #o2000303)
  0)

;; Thai Font Code 0xA5, Unicode 0xF705
(add-character-description
  165 0 -5 9 1 2
  #-thai-bitmaps nil #+thai-bitmaps '#(#o102)
  0)

;; Thai Font Code 0xA6, Unicode 0xF706
(add-character-description
  166 0 -6 8 5 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o30204 #o1020303 #o3010403 #o4000501 #o202)
  0)

;; Thai Font Code 0xA7, Unicode 0xF707
(add-character-description
  167 0 -9 9 6 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4010503 #o2010302 #o10103 #o5000602 #o3000403 #o1000201)
  0)

;; Thai Font Code 0xA8, Unicode 0xF708
(add-character-description
  168 0 -5 9 3 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2010302 #o10102 #o1000203)
  0)

;; Thai Font Code 0xA9, Unicode 0xF709
(add-character-description
  169 0 -7 9 5 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o10203 #o1000501)
  0)

;; Thai Font Code 0xAA, Unicode 0xF70A
(add-character-description
  170 0 -3 9 1 2
  #-thai-bitmaps nil #+thai-bitmaps '#(#o102)
  0)

;; Thai Font Code 0xAB, Unicode 0xF70B
(add-character-description
  171 0 -4 8 5 4
  #-thai-bitmaps nil #+thai-bitmaps '#(#o30204 #o1020303 #o3010403 #o4000501 #o202)
  0)

;; Thai Font Code 0xAC, Unicode 0xF70C
(add-character-description
  172 0 -5 9 6 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o4010503 #o2010302 #o10103 #o5000602 #o3000403 #o1000201)
  0)

;; Thai Font Code 0xAD, Unicode 0xF70D
(add-character-description
  173 0 -3 9 3 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o2010302 #o10102 #o1000203)
  0)

;; Thai Font Code 0xAE, Unicode 0xF70E
(add-character-description
  174 0 -5 9 5 3
  #-thai-bitmaps nil #+thai-bitmaps '#(#o10203 #o1000501)
  0)

;; Thai Font Code 0xAF, Unicode 0xF70F
(add-character-description
  175 12 1 0 10 8
  #-thai-bitmaps nil #+thai-bitmaps '#(#o6071110 #o1070210 #o2060307 #o1050206 #o40107 #o1030204 #o20103 #o5010610
    #o1010202 #o11001210 #o2000501)
  2958)
