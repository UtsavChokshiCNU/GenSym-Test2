;; -*- mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module GBMAPR

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;; (Automatically Generated File from Code in CHARACTERS)


(defvar unicode-to-GB-2312-map
 (optimize-constant 
  '#.(let ((a (make-array 307)))
       (setf (svref a 0) (make-array 54 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x252D #x184  #x2660 #x215  #x2B2C #x3B7  #x2C5F #x448
          #x312B #x5EA  #x325E #x67B  #x372A #x81D  #x385D #x8AE
          #x3D29 #xA50  #x3E5C #xAE1  #x4328 #xC83  #x445B #xD14
          #x4927 #xEB6  #x4A5A #xF47  #x4F26 #x10E9  #x5059 #x117A
          #x5525 #x131C  #x5658 #x13AD  #x5B24 #x154F  #x5C57 #x15E0
          #x6123 #x1782  #x6256 #x1813  #x6722 #x19B5  #x6855 #x1A46
          #x6D21 #x1BE8  #x6E54 #x1C79  #x7453 #x1EAC)))
       (setf (svref a 1) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x252E #x185  #x2661 #x216  #x2B2D #x3B8  #x2C60 #x449
          #x312C #x5EB  #x325F #x67C  #x372B #x81E  #x385E #x8AF
          #x3D2A #xA51  #x3E5D #xAE2  #x4329 #xC84  #x445C #xD15
          #x4928 #xEB7  #x4A5B #xF48  #x4F27 #x10EA  #x505A #x117B
          #x5526 #x131D  #x5659 #x13AE  #x5B25 #x1550  #x5C58 #x15E1
          #x6124 #x1783  #x6257 #x1814  #x6723 #x19B6  #x6856 #x1A47
          #x6D22 #x1BE9  #x6E55 #x1C7A  #x7321 #x1E1C  #x7454 #x1EAD)))
       (setf (svref a 2) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x252F #x186  #x2662 #x217  #x2B2E #x3B9  #x2C61 #x44A
          #x312D #x5EC  #x3260 #x67D  #x372C #x81F  #x385F #x8B0
          #x3D2B #xA52  #x3E5E #xAE3  #x432A #xC85  #x445D #xD16
          #x4929 #xEB8  #x4A5C #xF49  #x4F28 #x10EB  #x505B #x117C
          #x5527 #x131E  #x565A #x13AF  #x5B26 #x1551  #x5C59 #x15E2
          #x6125 #x1784  #x6258 #x1815  #x6724 #x19B7  #x6857 #x1A48
          #x6D23 #x1BEA  #x6E56 #x1C7B  #x7322 #x1E1D  #x7455 #x1EAE)))
       (setf (svref a 3) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2530 #x187  #x2663 #x218  #x2B2F #x3BA  #x2C62 #x44B
          #x312E #x5ED  #x3261 #x67E  #x372D #x820  #x3860 #x8B1
          #x3D2C #xA53  #x3E5F #xAE4  #x432B #xC86  #x445E #xD17
          #x492A #xEB9  #x4A5D #xF4A  #x4F29 #x10EC  #x505C #x117D
          #x5528 #x131F  #x565B #x13B0  #x5B27 #x1552  #x5C5A #x15E3
          #x6126 #x1785  #x6259 #x1816  #x6725 #x19B8  #x6858 #x1A49
          #x6D24 #x1BEB  #x6E57 #x1C7C  #x7323 #x1E1E  #x7456 #x1EAF)))
       (setf (svref a 4) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2531 #x188  #x2664 #x219  #x2B30 #x3BB  #x2C63 #x44C
          #x312F #x5EE  #x3262 #x67F  #x372E #x821  #x3861 #x8B2
          #x3D2D #xA54  #x3E60 #xAE5  #x432C #xC87  #x445F #xD18
          #x492B #xEBA  #x4A5E #xF4B  #x4F2A #x10ED  #x505D #x117E
          #x5529 #x1320  #x565C #x13B1  #x5B28 #x1553  #x5C5B #x15E4
          #x6127 #x1786  #x625A #x1817  #x6726 #x19B9  #x6859 #x1A4A
          #x6D25 #x1BEC  #x6E58 #x1C7D  #x7324 #x1E1F  #x7457 #x1EB0)))
       (setf (svref a 5) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2532 #x189  #x2665 #x21A  #x2B31 #x3BC  #x2C64 #x44D
          #x3130 #x5EF  #x3263 #x680  #x372F #x822  #x3862 #x8B3
          #x3D2E #xA55  #x3E61 #xAE6  #x432D #xC88  #x4460 #xD19
          #x492C #xEBB  #x4A5F #xF4C  #x4F2B #x10EE  #x505E #x117F
          #x552A #x1321  #x565D #x13B2  #x5B29 #x1554  #x5C5C #x15E5
          #x6128 #x1787  #x625B #x1818  #x6727 #x19BA  #x685A #x1A4B
          #x6D26 #x1BED  #x6E59 #x1C7E  #x7325 #x1E20  #x7458 #x1EB1)))
       (setf (svref a 6) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2533 #x18A  #x2666 #x21B  #x2B32 #x3BD  #x2C65 #x44E
          #x3131 #x5F0  #x3264 #x681  #x3730 #x823  #x3863 #x8B4
          #x3D2F #xA56  #x3E62 #xAE7  #x432E #xC89  #x4461 #xD1A
          #x492D #xEBC  #x4A60 #xF4D  #x4F2C #x10EF  #x505F #x1180
          #x552B #x1322  #x565E #x13B3  #x5B2A #x1555  #x5C5D #x15E6
          #x6129 #x1788  #x625C #x1819  #x6728 #x19BB  #x685B #x1A4C
          #x6D27 #x1BEE  #x6E5A #x1C7F  #x7326 #x1E21  #x7459 #x1EB2)))
       (setf (svref a 7) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2534 #x18B  #x2667 #x21C  #x2B33 #x3BE  #x2C66 #x44F
          #x3132 #x5F1  #x3265 #x682  #x3731 #x824  #x3864 #x8B5
          #x3D30 #xA57  #x3E63 #xAE8  #x432F #xC8A  #x4462 #xD1B
          #x492E #xEBD  #x4A61 #xF4E  #x4F2D #x10F0  #x5060 #x1181
          #x552C #x1323  #x565F #x13B4  #x5B2B #x1556  #x5C5E #x15E7
          #x612A #x1789  #x625D #x181A  #x6729 #x19BC  #x685C #x1A4D
          #x6D28 #x1BEF  #x6E5B #x1C80  #x7327 #x1E22  #x745A #x1EB3)))
       (setf (svref a 8) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2535 #x18C  #x2668 #x21D  #x2B34 #x3BF  #x2C67 #x450
          #x3133 #x5F2  #x3266 #x683  #x3732 #x825  #x3865 #x8B6
          #x3D31 #xA58  #x3E64 #xAE9  #x4330 #xC8B  #x4463 #xD1C
          #x492F #xEBE  #x4A62 #xF4F  #x4F2E #x10F1  #x5061 #x1182
          #x552D #x1324  #x5660 #x13B5  #x5B2C #x1557  #x5C5F #x15E8
          #x612B #x178A  #x625E #x181B  #x672A #x19BD  #x685D #x1A4E
          #x6D29 #x1BF0  #x6E5C #x1C81  #x7328 #x1E23  #x745B #x1EB4)))
       (setf (svref a 9) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2536 #x18D  #x2669 #x21E  #x2B35 #x3C0  #x2C68 #x451
          #x3134 #x5F3  #x3267 #x684  #x3733 #x826  #x3866 #x8B7
          #x3D32 #xA59  #x3E65 #xAEA  #x4331 #xC8C  #x4464 #xD1D
          #x4930 #xEBF  #x4A63 #xF50  #x4F2F #x10F2  #x5062 #x1183
          #x552E #x1325  #x5661 #x13B6  #x5B2D #x1558  #x5C60 #x15E9
          #x612C #x178B  #x625F #x181C  #x672B #x19BE  #x685E #x1A4F
          #x6D2A #x1BF1  #x6E5D #x1C82  #x7329 #x1E24  #x745C #x1EB5)))
       (setf (svref a 10) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2537 #x18E  #x266A #x21F  #x2B36 #x3C1  #x2C69 #x452
          #x3135 #x5F4  #x3268 #x685  #x3734 #x827  #x3867 #x8B8
          #x3D33 #xA5A  #x3E66 #xAEB  #x4332 #xC8D  #x4465 #xD1E
          #x4931 #xEC0  #x4A64 #xF51  #x4F30 #x10F3  #x5063 #x1184
          #x552F #x1326  #x5662 #x13B7  #x5B2E #x1559  #x5C61 #x15EA
          #x612D #x178C  #x6260 #x181D  #x672C #x19BF  #x685F #x1A50
          #x6D2B #x1BF2  #x6E5E #x1C83  #x732A #x1E25  #x745D #x1EB6)))
       (setf (svref a 11) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2538 #x18F  #x266B #x220  #x2B37 #x3C2  #x2C6A #x453
          #x3136 #x5F5  #x3269 #x686  #x3735 #x828  #x3868 #x8B9
          #x3D34 #xA5B  #x3E67 #xAEC  #x4333 #xC8E  #x4466 #xD1F
          #x4932 #xEC1  #x4A65 #xF52  #x4F31 #x10F4  #x5064 #x1185
          #x5530 #x1327  #x5663 #x13B8  #x5B2F #x155A  #x5C62 #x15EB
          #x612E #x178D  #x6261 #x181E  #x672D #x19C0  #x6860 #x1A51
          #x6D2C #x1BF3  #x6E5F #x1C84  #x732B #x1E26  #x745E #x1EB7)))
       (setf (svref a 12) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2539 #x190  #x266C #x221  #x2B38 #x3C3  #x2C6B #x454
          #x3137 #x5F6  #x326A #x687  #x3736 #x829  #x3869 #x8BA
          #x3D35 #xA5C  #x3E68 #xAED  #x4334 #xC8F  #x4467 #xD20
          #x4933 #xEC2  #x4A66 #xF53  #x4F32 #x10F5  #x5065 #x1186
          #x5531 #x1328  #x5664 #x13B9  #x5B30 #x155B  #x5C63 #x15EC
          #x612F #x178E  #x6262 #x181F  #x672E #x19C1  #x6861 #x1A52
          #x6D2D #x1BF4  #x6E60 #x1C85  #x732C #x1E27  #x745F #x1EB8)))
       (setf (svref a 13) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x253A #x191  #x266D #x222  #x2B39 #x3C4  #x2C6C #x455
          #x3138 #x5F7  #x326B #x688  #x3737 #x82A  #x386A #x8BB
          #x3D36 #xA5D  #x3E69 #xAEE  #x4335 #xC90  #x4468 #xD21
          #x4934 #xEC3  #x4A67 #xF54  #x4F33 #x10F6  #x5066 #x1187
          #x5532 #x1329  #x5665 #x13BA  #x5B31 #x155C  #x5C64 #x15ED
          #x6130 #x178F  #x6263 #x1820  #x672F #x19C2  #x6862 #x1A53
          #x6D2E #x1BF5  #x6E61 #x1C86  #x732D #x1E28  #x7460 #x1EB9)))
       (setf (svref a 14) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x253B #x192  #x266E #x223  #x2B3A #x3C5  #x2C6D #x456
          #x3139 #x5F8  #x326C #x689  #x3738 #x82B  #x386B #x8BC
          #x3D37 #xA5E  #x3E6A #xAEF  #x4336 #xC91  #x4469 #xD22
          #x4935 #xEC4  #x4A68 #xF55  #x4F34 #x10F7  #x5067 #x1188
          #x5533 #x132A  #x5666 #x13BB  #x5B32 #x155D  #x5C65 #x15EE
          #x6131 #x1790  #x6264 #x1821  #x6730 #x19C3  #x6863 #x1A54
          #x6D2F #x1BF6  #x6E62 #x1C87  #x732E #x1E29  #x7461 #x1EBA)))
       (setf (svref a 15) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x253C #x193  #x266F #x224  #x2B3B #x3C6  #x2C6E #x457
          #x313A #x5F9  #x326D #x68A  #x3739 #x82C  #x386C #x8BD
          #x3D38 #xA5F  #x3E6B #xAF0  #x4337 #xC92  #x446A #xD23
          #x4936 #xEC5  #x4A69 #xF56  #x4F35 #x10F8  #x5068 #x1189
          #x5534 #x132B  #x5667 #x13BC  #x5B33 #x155E  #x5C66 #x15EF
          #x6132 #x1791  #x6265 #x1822  #x6731 #x19C4  #x6864 #x1A55
          #x6D30 #x1BF7  #x6E63 #x1C88  #x732F #x1E2A  #x7462 #x1EBB)))
       (setf (svref a 16) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x253D #x194  #x2670 #x225  #x2B3C #x3C7  #x2C6F #x458
          #x313B #x5FA  #x326E #x68B  #x373A #x82D  #x386D #x8BE
          #x3D39 #xA60  #x3E6C #xAF1  #x4338 #xC93  #x446B #xD24
          #x4937 #xEC6  #x4A6A #xF57  #x4F36 #x10F9  #x5069 #x118A
          #x5535 #x132C  #x5668 #x13BD  #x5B34 #x155F  #x5C67 #x15F0
          #x6133 #x1792  #x6266 #x1823  #x6732 #x19C5  #x6865 #x1A56
          #x6D31 #x1BF8  #x6E64 #x1C89  #x7330 #x1E2B  #x7463 #x1EBC)))
       (setf (svref a 17) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x253E #x195  #x2671 #x226  #x2B3D #x3C8  #x2C70 #x459
          #x313C #x5FB  #x326F #x68C  #x373B #x82E  #x386E #x8BF
          #x3D3A #xA61  #x3E6D #xAF2  #x4339 #xC94  #x446C #xD25
          #x4938 #xEC7  #x4A6B #xF58  #x4F37 #x10FA  #x506A #x118B
          #x5536 #x132D  #x5669 #x13BE  #x5B35 #x1560  #x5C68 #x15F1
          #x6134 #x1793  #x6267 #x1824  #x6733 #x19C6  #x6866 #x1A57
          #x6D32 #x1BF9  #x6E65 #x1C8A  #x7331 #x1E2C  #x7464 #x1EBD)))
       (setf (svref a 18) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x253F #x196  #x2672 #x227  #x2B3E #x3C9  #x2C71 #x45A
          #x313D #x5FC  #x3270 #x68D  #x373C #x82F  #x386F #x8C0
          #x3D3B #xA62  #x3E6E #xAF3  #x433A #xC95  #x446D #xD26
          #x4939 #xEC8  #x4A6C #xF59  #x4F38 #x10FB  #x506B #x118C
          #x5537 #x132E  #x566A #x13BF  #x5B36 #x1561  #x5C69 #x15F2
          #x6135 #x1794  #x6268 #x1825  #x6734 #x19C7  #x6867 #x1A58
          #x6D33 #x1BFA  #x6E66 #x1C8B  #x7332 #x1E2D  #x7465 #x1EBE)))
       (setf (svref a 19) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2540 #x197  #x2673 #x228  #x2B3F #x3CA  #x2C72 #x45B
          #x313E #x5FD  #x3271 #x68E  #x373D #x830  #x3870 #x8C1
          #x3D3C #xA63  #x3E6F #xAF4  #x433B #xC96  #x446E #xD27
          #x493A #xEC9  #x4A6D #xF5A  #x4F39 #x10FC  #x506C #x118D
          #x5538 #x132F  #x566B #x13C0  #x5B37 #x1562  #x5C6A #x15F3
          #x6136 #x1795  #x6269 #x1826  #x6735 #x19C8  #x6868 #x1A59
          #x6D34 #x1BFB  #x6E67 #x1C8C  #x7333 #x1E2E  #x7466 #x1EBF)))
       (setf (svref a 20) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2541 #x198  #x2674 #x229  #x2B40 #x3CB  #x2C73 #x45C
          #x313F #x5FE  #x3272 #x68F  #x373E #x831  #x3871 #x8C2
          #x3D3D #xA64  #x3E70 #xAF5  #x433C #xC97  #x446F #xD28
          #x493B #xECA  #x4A6E #xF5B  #x4F3A #x10FD  #x506D #x118E
          #x5539 #x1330  #x566C #x13C1  #x5B38 #x1563  #x5C6B #x15F4
          #x6137 #x1796  #x626A #x1827  #x6736 #x19C9  #x6869 #x1A5A
          #x6D35 #x1BFC  #x6E68 #x1C8D  #x7334 #x1E2F  #x7467 #x1EC0)))
       (setf (svref a 21) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2542 #x199  #x2675 #x22A  #x2B41 #x3CC  #x2C74 #x45D
          #x3140 #x5FF  #x3273 #x690  #x373F #x832  #x3872 #x8C3
          #x3D3E #xA65  #x3E71 #xAF6  #x433D #xC98  #x4470 #xD29
          #x493C #xECB  #x4A6F #xF5C  #x4F3B #x10FE  #x506E #x118F
          #x553A #x1331  #x566D #x13C2  #x5B39 #x1564  #x5C6C #x15F5
          #x6138 #x1797  #x626B #x1828  #x6737 #x19CA  #x686A #x1A5B
          #x6D36 #x1BFD  #x6E69 #x1C8E  #x7335 #x1E30  #x7468 #x1EC1)))
       (setf (svref a 22) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2543 #x19A  #x2676 #x22B  #x2B42 #x3CD  #x2C75 #x45E
          #x3141 #x600  #x3274 #x691  #x3740 #x833  #x3873 #x8C4
          #x3D3F #xA66  #x3E72 #xAF7  #x433E #xC99  #x4471 #xD2A
          #x493D #xECC  #x4A70 #xF5D  #x4F3C #x10FF  #x506F #x1190
          #x553B #x1332  #x566E #x13C3  #x5B3A #x1565  #x5C6D #x15F6
          #x6139 #x1798  #x626C #x1829  #x6738 #x19CB  #x686B #x1A5C
          #x6D37 #x1BFE  #x6E6A #x1C8F  #x7336 #x1E31  #x7469 #x1EC2)))
       (setf (svref a 23) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2544 #x19B  #x2677 #x22C  #x2B43 #x3CE  #x2C76 #x45F
          #x3142 #x601  #x3275 #x692  #x3741 #x834  #x3874 #x8C5
          #x3D40 #xA67  #x3E73 #xAF8  #x433F #xC9A  #x4472 #xD2B
          #x493E #xECD  #x4A71 #xF5E  #x4F3D #x1100  #x5070 #x1191
          #x553C #x1333  #x566F #x13C4  #x5B3B #x1566  #x5C6E #x15F7
          #x613A #x1799  #x626D #x182A  #x6739 #x19CC  #x686C #x1A5D
          #x6D38 #x1BFF  #x6E6B #x1C90  #x7337 #x1E32  #x746A #x1EC3)))
       (setf (svref a 24) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2545 #x19C  #x2678 #x22D  #x2B44 #x3CF  #x2C77 #x460
          #x3143 #x602  #x3276 #x693  #x3742 #x835  #x3875 #x8C6
          #x3D41 #xA68  #x3E74 #xAF9  #x4340 #xC9B  #x4473 #xD2C
          #x493F #xECE  #x4A72 #xF5F  #x4F3E #x1101  #x5071 #x1192
          #x553D #x1334  #x5670 #x13C5  #x5B3C #x1567  #x5C6F #x15F8
          #x613B #x179A  #x626E #x182B  #x673A #x19CD  #x686D #x1A5E
          #x6D39 #x1C00  #x6E6C #x1C91  #x7338 #x1E33  #x746B #x1EC4)))
       (setf (svref a 25) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2546 #x19D  #x2679 #x22E  #x2B45 #x3D0  #x2C78 #x461
          #x3144 #x603  #x3277 #x694  #x3743 #x836  #x3876 #x8C7
          #x3D42 #xA69  #x3E75 #xAFA  #x4341 #xC9C  #x4474 #xD2D
          #x4940 #xECF  #x4A73 #xF60  #x4F3F #x1102  #x5072 #x1193
          #x553E #x1335  #x5671 #x13C6  #x5B3D #x1568  #x5C70 #x15F9
          #x613C #x179B  #x626F #x182C  #x673B #x19CE  #x686E #x1A5F
          #x6D3A #x1C01  #x6E6D #x1C92  #x7339 #x1E34  #x746C #x1EC5)))
       (setf (svref a 26) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2547 #x19E  #x267A #x22F  #x2B46 #x3D1  #x2C79 #x462
          #x3145 #x604  #x3278 #x695  #x3744 #x837  #x3877 #x8C8
          #x3D43 #xA6A  #x3E76 #xAFB  #x4342 #xC9D  #x4475 #xD2E
          #x4941 #xED0  #x4A74 #xF61  #x4F40 #x1103  #x5073 #x1194
          #x553F #x1336  #x5672 #x13C7  #x5B3E #x1569  #x5C71 #x15FA
          #x613D #x179C  #x6270 #x182D  #x673C #x19CF  #x686F #x1A60
          #x6D3B #x1C02  #x6E6E #x1C93  #x733A #x1E35  #x746D #x1EC6)))
       (setf (svref a 27) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2548 #x19F  #x267B #x230  #x2B47 #x3D2  #x2C7A #x463
          #x3146 #x605  #x3279 #x696  #x3745 #x838  #x3878 #x8C9
          #x3D44 #xA6B  #x3E77 #xAFC  #x4343 #xC9E  #x4476 #xD2F
          #x4942 #xED1  #x4A75 #xF62  #x4F41 #x1104  #x5074 #x1195
          #x5540 #x1337  #x5673 #x13C8  #x5B3F #x156A  #x5C72 #x15FB
          #x613E #x179D  #x6271 #x182E  #x673D #x19D0  #x6870 #x1A61
          #x6D3C #x1C03  #x6E6F #x1C94  #x733B #x1E36  #x746E #x1EC7)))
       (setf (svref a 28) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2549 #x1A0  #x267C #x231  #x2B48 #x3D3  #x2C7B #x464
          #x3147 #x606  #x327A #x697  #x3746 #x839  #x3879 #x8CA
          #x3D45 #xA6C  #x3E78 #xAFD  #x4344 #xC9F  #x4477 #xD30
          #x4943 #xED2  #x4A76 #xF63  #x4F42 #x1105  #x5075 #x1196
          #x5541 #x1338  #x5674 #x13C9  #x5B40 #x156B  #x5C73 #x15FC
          #x613F #x179E  #x6272 #x182F  #x673E #x19D1  #x6871 #x1A62
          #x6D3D #x1C04  #x6E70 #x1C95  #x733C #x1E37  #x746F #x1EC8)))
       (setf (svref a 29) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x254A #x1A1  #x267D #x232  #x2B49 #x3D4  #x2C7C #x465
          #x3148 #x607  #x327B #x698  #x3747 #x83A  #x387A #x8CB
          #x3D46 #xA6D  #x3E79 #xAFE  #x4345 #xCA0  #x4478 #xD31
          #x4944 #xED3  #x4A77 #xF64  #x4F43 #x1106  #x5076 #x1197
          #x5542 #x1339  #x5675 #x13CA  #x5B41 #x156C  #x5C74 #x15FD
          #x6140 #x179F  #x6273 #x1830  #x673F #x19D2  #x6872 #x1A63
          #x6D3E #x1C05  #x6E71 #x1C96  #x733D #x1E38  #x7470 #x1EC9)))
       (setf (svref a 30) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x254B #x1A2  #x267E #x233  #x2B4A #x3D5  #x2C7D #x466
          #x3149 #x608  #x327C #x699  #x3748 #x83B  #x387B #x8CC
          #x3D47 #xA6E  #x3E7A #xAFF  #x4346 #xCA1  #x4479 #xD32
          #x4945 #xED4  #x4A78 #xF65  #x4F44 #x1107  #x5077 #x1198
          #x5543 #x133A  #x5676 #x13CB  #x5B42 #x156D  #x5C75 #x15FE
          #x6141 #x17A0  #x6274 #x1831  #x6740 #x19D3  #x6873 #x1A64
          #x6D3F #x1C06  #x6E72 #x1C97  #x733E #x1E39  #x7471 #x1ECA)))
       (setf (svref a 31) (make-array 54 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x254C #x1A3  #x2B4B #x3D6  #x2C7E #x467  #x314A #x609
          #x327D #x69A  #x3749 #x83C  #x387C #x8CD  #x3D48 #xA6F
          #x3E7B #xB00  #x4347 #xCA2  #x447A #xD33  #x4946 #xED5
          #x4A79 #xF66  #x4F45 #x1108  #x5078 #x1199  #x5544 #x133B
          #x5677 #x13CC  #x5B43 #x156E  #x5C76 #x15FF  #x6142 #x17A1
          #x6275 #x1832  #x6741 #x19D4  #x6874 #x1A65  #x6D40 #x1C07
          #x6E73 #x1C98  #x733F #x1E3A  #x7472 #x1ECB)))
       (setf (svref a 32) (make-array 52 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x254D #x1A4  #x2B4C #x3D7  #x314B #x60A  #x327E #x69B
          #x374A #x83D  #x387D #x8CE  #x3D49 #xA70  #x3E7C #xB01
          #x4348 #xCA3  #x447B #xD34  #x4947 #xED6  #x4A7A #xF67
          #x4F46 #x1109  #x5079 #x119A  #x5545 #x133C  #x5678 #x13CD
          #x5B44 #x156F  #x5C77 #x1600  #x6143 #x17A2  #x6276 #x1833
          #x6742 #x19D5  #x6875 #x1A66  #x6D41 #x1C08  #x6E74 #x1C99
          #x7340 #x1E3B  #x7473 #x1ECC)))
       (setf (svref a 33) (make-array 50 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x254E #x1A5  #x2B4D #x3D8  #x314C #x60B  #x374B #x83E
          #x387E #x8CF  #x3D4A #xA71  #x3E7D #xB02  #x4349 #xCA4
          #x447C #xD35  #x4948 #xED7  #x4A7B #xF68  #x4F47 #x110A
          #x507A #x119B  #x5546 #x133D  #x5679 #x13CE  #x5B45 #x1570
          #x5C78 #x1601  #x6144 #x17A3  #x6277 #x1834  #x6743 #x19D6
          #x6876 #x1A67  #x6D42 #x1C09  #x6E75 #x1C9A  #x7341 #x1E3C
          #x7474 #x1ECD)))
       (setf (svref a 34) (make-array 48 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x254F #x1A6  #x2B4E #x3D9  #x314D #x60C  #x374C #x83F
          #x3D4B #xA72  #x3E7E #xB03  #x434A #xCA5  #x447D #xD36
          #x4949 #xED8  #x4A7C #xF69  #x4F48 #x110B  #x507B #x119C
          #x5547 #x133E  #x567A #x13CF  #x5B46 #x1571  #x5C79 #x1602
          #x6145 #x17A4  #x6278 #x1835  #x6744 #x19D7  #x6877 #x1A68
          #x6D43 #x1C0A  #x6E76 #x1C9B  #x7342 #x1E3D  #x7475 #x1ECE)))
       (setf (svref a 35) (make-array 46 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2550 #x1A7  #x2B4F #x3DA  #x314E #x60D  #x374D #x840
          #x3D4C #xA73  #x434B #xCA6  #x447E #xD37  #x494A #xED9
          #x4A7D #xF6A  #x4F49 #x110C  #x507C #x119D  #x5548 #x133F
          #x567B #x13D0  #x5B47 #x1572  #x5C7A #x1603  #x6146 #x17A5
          #x6279 #x1836  #x6745 #x19D8  #x6878 #x1A69  #x6D44 #x1C0B
          #x6E77 #x1C9C  #x7343 #x1E3E  #x7476 #x1ECF)))
       (setf (svref a 36) (make-array 44 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2551 #x1A8  #x2B50 #x3DB  #x314F #x60E  #x374E #x841
          #x3D4D #xA74  #x434C #xCA7  #x494B #xEDA  #x4A7E #xF6B
          #x4F4A #x110D  #x507D #x119E  #x5549 #x1340  #x567C #x13D1
          #x5B48 #x1573  #x5C7B #x1604  #x6147 #x17A6  #x627A #x1837
          #x6746 #x19D9  #x6879 #x1A6A  #x6D45 #x1C0C  #x6E78 #x1C9D
          #x7344 #x1E3F  #x7477 #x1ED0)))
       (setf (svref a 37) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2552 #x1A9  #x2B51 #x3DC  #x3150 #x60F  #x374F #x842
          #x3D4E #xA75  #x434D #xCA8  #x494C #xEDB  #x4F4B #x110E
          #x507E #x119F  #x554A #x1341  #x567D #x13D2  #x5B49 #x1574
          #x5C7C #x1605  #x6148 #x17A7  #x627B #x1838  #x6747 #x19DA
          #x687A #x1A6B  #x6D46 #x1C0D  #x6E79 #x1C9E  #x7345 #x1E40
          #x7478 #x1ED1)))
       (setf (svref a 38) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2553 #x1AA  #x2B52 #x3DD  #x3151 #x610  #x3750 #x843
          #x3D4F #xA76  #x434E #xCA9  #x494D #xEDC  #x4F4C #x110F
          #x554B #x1342  #x567E #x13D3  #x5B4A #x1575  #x5C7D #x1606
          #x6149 #x17A8  #x627C #x1839  #x6748 #x19DB  #x687B #x1A6C
          #x6D47 #x1C0E  #x6E7A #x1C9F  #x7346 #x1E41  #x7479 #x1ED2)))
       (setf (svref a 39) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2421 #x11A  #x2554 #x1AB  #x2B53 #x3DE  #x3152 #x611
          #x3751 #x844  #x3D50 #xA77  #x434F #xCAA  #x494E #xEDD
          #x4F4D #x1110  #x554C #x1343  #x5B4B #x1576  #x5C7E #x1607
          #x614A #x17A9  #x627D #x183A  #x6749 #x19DC  #x687C #x1A6D
          #x6D48 #x1C0F  #x6E7B #x1CA0  #x7347 #x1E42  #x747A #x1ED3)))
       (setf (svref a 40) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2422 #x11B  #x2555 #x1AC  #x2A21 #x34E  #x2B54 #x3DF
          #x3153 #x612  #x3752 #x845  #x3D51 #xA78  #x4350 #xCAB
          #x494F #xEDE  #x4F4E #x1111  #x554D #x1344  #x5B4C #x1577
          #x614B #x17AA  #x627E #x183B  #x674A #x19DD  #x687D #x1A6E
          #x6D49 #x1C10  #x6E7C #x1CA1  #x7348 #x1E43  #x747B #x1ED4)))
       (setf (svref a 41) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2423 #x11C  #x2556 #x1AD  #x2A22 #x34F  #x2B55 #x3E0
          #x3021 #x582  #x3154 #x613  #x3753 #x846  #x3D52 #xA79
          #x4351 #xCAC  #x4950 #xEDF  #x4F4F #x1112  #x554E #x1345
          #x5B4D #x1578  #x614C #x17AB  #x674B #x19DE  #x687E #x1A6F
          #x6D4A #x1C11  #x6E7D #x1CA2  #x7349 #x1E44  #x747C #x1ED5)))
       (setf (svref a 42) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2424 #x11D  #x2557 #x1AE  #x2A23 #x350  #x2B56 #x3E1
          #x3022 #x583  #x3155 #x614  #x3621 #x7B6  #x3754 #x847
          #x3D53 #xA7A  #x4352 #xCAD  #x4951 #xEE0  #x4F50 #x1113
          #x554F #x1346  #x5B4E #x1579  #x614D #x17AC  #x674C #x19DF
          #x6D4B #x1C12  #x6E7E #x1CA3  #x734A #x1E45  #x747D #x1ED6)))
       (setf (svref a 43) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2425 #x11E  #x2558 #x1AF  #x2A24 #x351  #x2B57 #x3E2
          #x3023 #x584  #x3156 #x615  #x3622 #x7B7  #x3755 #x848
          #x3C21 #x9EA  #x3D54 #xA7B  #x4353 #xCAE  #x4952 #xEE1
          #x4F51 #x1114  #x5550 #x1347  #x5B4F #x157A  #x614E #x17AD
          #x674D #x19E0  #x6D4C #x1C13  #x734B #x1E46  #x747E #x1ED7)))
       (setf (svref a 44) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2426 #x11F  #x2559 #x1B0  #x2A25 #x352  #x2B58 #x3E3
          #x3024 #x585  #x3157 #x616  #x3623 #x7B8  #x3756 #x849
          #x3C22 #x9EB  #x3D55 #xA7C  #x4221 #xC1E  #x4354 #xCAF
          #x4953 #xEE2  #x4F52 #x1115  #x5551 #x1348  #x5B50 #x157B
          #x614F #x17AE  #x674E #x19E1  #x6D4D #x1C14  #x734C #x1E47)))
       (setf (svref a 45) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2427 #x120  #x255A #x1B1  #x2A26 #x353  #x2B59 #x3E4
          #x3025 #x586  #x3158 #x617  #x3624 #x7B9  #x3757 #x84A
          #x3C23 #x9EC  #x3D56 #xA7D  #x4222 #xC1F  #x4355 #xCB0
          #x4821 #xE52  #x4954 #xEE3  #x4F53 #x1116  #x5552 #x1349
          #x5B51 #x157C  #x6150 #x17AF  #x674F #x19E2  #x6D4E #x1C15
          #x734D #x1E48)))
       (setf (svref a 46) (make-array 44 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2428 #x121  #x255B #x1B2  #x2A27 #x354  #x2B5A #x3E5
          #x3026 #x587  #x3159 #x618  #x3625 #x7BA  #x3758 #x84B
          #x3C24 #x9ED  #x3D57 #xA7E  #x4223 #xC20  #x4356 #xCB1
          #x4822 #xE53  #x4955 #xEE4  #x4E21 #x1086  #x4F54 #x1117
          #x5553 #x134A  #x5B52 #x157D  #x6151 #x17B0  #x6750 #x19E3
          #x6D4F #x1C16  #x734E #x1E49)))
       (setf (svref a 47) (make-array 46 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2429 #x122  #x255C #x1B3  #x2A28 #x355  #x2B5B #x3E6
          #x3027 #x588  #x315A #x619  #x3626 #x7BB  #x3759 #x84C
          #x3C25 #x9EE  #x3D58 #xA7F  #x4224 #xC21  #x4357 #xCB2
          #x4823 #xE54  #x4956 #xEE5  #x4E22 #x1087  #x4F55 #x1118
          #x5421 #x12BA  #x5554 #x134B  #x5B53 #x157E  #x6152 #x17B1
          #x6751 #x19E4  #x6D50 #x1C17  #x734F #x1E4A)))
       (setf (svref a 48) (make-array 48 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x242A #x123  #x255D #x1B4  #x2A29 #x356  #x2B5C #x3E7
          #x3028 #x589  #x315B #x61A  #x3627 #x7BC  #x375A #x84D
          #x3C26 #x9EF  #x3D59 #xA80  #x4225 #xC22  #x4358 #xCB3
          #x4824 #xE55  #x4957 #xEE6  #x4E23 #x1088  #x4F56 #x1119
          #x5422 #x12BB  #x5555 #x134C  #x5A21 #x14EE  #x5B54 #x157F
          #x6153 #x17B2  #x6752 #x19E5  #x6D51 #x1C18  #x7350 #x1E4B)))
       (setf (svref a 49) (make-array 50 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x242B #x124  #x255E #x1B5  #x2A2A #x357  #x2B5D #x3E8
          #x3029 #x58A  #x315C #x61B  #x3628 #x7BD  #x375B #x84E
          #x3C27 #x9F0  #x3D5A #xA81  #x4226 #xC23  #x4359 #xCB4
          #x4825 #xE56  #x4958 #xEE7  #x4E24 #x1089  #x4F57 #x111A
          #x5423 #x12BC  #x5556 #x134D  #x5A22 #x14EF  #x5B55 #x1580
          #x6021 #x1722  #x6154 #x17B3  #x6753 #x19E6  #x6D52 #x1C19
          #x7351 #x1E4C)))
       (setf (svref a 50) (make-array 52 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x242C #x125  #x255F #x1B6  #x2A2B #x358  #x2B5E #x3E9
          #x302A #x58B  #x315D #x61C  #x3629 #x7BE  #x375C #x84F
          #x3C28 #x9F1  #x3D5B #xA82  #x4227 #xC24  #x435A #xCB5
          #x4826 #xE57  #x4959 #xEE8  #x4E25 #x108A  #x4F58 #x111B
          #x5424 #x12BD  #x5557 #x134E  #x5A23 #x14F0  #x5B56 #x1581
          #x6022 #x1723  #x6155 #x17B4  #x6621 #x1956  #x6754 #x19E7
          #x6D53 #x1C1A  #x7352 #x1E4D)))
       (setf (svref a 51) (make-array 54 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x242D #x126  #x2560 #x1B7  #x2A2C #x359  #x2B5F #x3EA
          #x302B #x58C  #x315E #x61D  #x362A #x7BF  #x375D #x850
          #x3C29 #x9F2  #x3D5C #xA83  #x4228 #xC25  #x435B #xCB6
          #x4827 #xE58  #x495A #xEE9  #x4E26 #x108B  #x4F59 #x111C
          #x5425 #x12BE  #x5558 #x134F  #x5A24 #x14F1  #x5B57 #x1582
          #x6023 #x1724  #x6156 #x17B5  #x6622 #x1957  #x6755 #x19E8
          #x6C21 #x1B8A  #x6D54 #x1C1B  #x7353 #x1E4E)))
       (setf (svref a 52) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x242E #x127  #x2561 #x1B8  #x2A2D #x35A  #x2B60 #x3EB
          #x302C #x58D  #x315F #x61E  #x362B #x7C0  #x375E #x851
          #x3C2A #x9F3  #x3D5D #xA84  #x4229 #xC26  #x435C #xCB7
          #x4828 #xE59  #x495B #xEEA  #x4E27 #x108C  #x4F5A #x111D
          #x5426 #x12BF  #x5559 #x1350  #x5A25 #x14F2  #x5B58 #x1583
          #x6024 #x1725  #x6157 #x17B6  #x6623 #x1958  #x6756 #x19E9
          #x6C22 #x1B8B  #x6D55 #x1C1C  #x7221 #x1DBE  #x7354 #x1E4F)))
       (setf (svref a 53) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x242F #x128  #x2562 #x1B9  #x2A2E #x35B  #x2B61 #x3EC
          #x302D #x58E  #x3160 #x61F  #x362C #x7C1  #x375F #x852
          #x3C2B #x9F4  #x3D5E #xA85  #x422A #xC27  #x435D #xCB8
          #x4829 #xE5A  #x495C #xEEB  #x4E28 #x108D  #x4F5B #x111E
          #x5427 #x12C0  #x555A #x1351  #x5A26 #x14F3  #x5B59 #x1584
          #x6025 #x1726  #x6158 #x17B7  #x6624 #x1959  #x6757 #x19EA
          #x6C23 #x1B8C  #x6D56 #x1C1D  #x7222 #x1DBF  #x7355 #x1E50)))
       (setf (svref a 54) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2430 #x129  #x2563 #x1BA  #x2A2F #x35C  #x2B62 #x3ED
          #x302E #x58F  #x3161 #x620  #x362D #x7C2  #x3760 #x853
          #x3C2C #x9F5  #x3D5F #xA86  #x422B #xC28  #x435E #xCB9
          #x482A #xE5B  #x495D #xEEC  #x4E29 #x108E  #x4F5C #x111F
          #x5428 #x12C1  #x555B #x1352  #x5A27 #x14F4  #x5B5A #x1585
          #x6026 #x1727  #x6159 #x17B8  #x6625 #x195A  #x6758 #x19EB
          #x6C24 #x1B8D  #x6D57 #x1C1E  #x7223 #x1DC0  #x7356 #x1E51)))
       (setf (svref a 55) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2431 #x12A  #x2564 #x1BB  #x2A30 #x35D  #x2B63 #x3EE
          #x302F #x590  #x3162 #x621  #x362E #x7C3  #x3761 #x854
          #x3C2D #x9F6  #x3D60 #xA87  #x422C #xC29  #x435F #xCBA
          #x482B #xE5C  #x495E #xEED  #x4E2A #x108F  #x4F5D #x1120
          #x5429 #x12C2  #x555C #x1353  #x5A28 #x14F5  #x5B5B #x1586
          #x6027 #x1728  #x615A #x17B9  #x6626 #x195B  #x6759 #x19EC
          #x6C25 #x1B8E  #x6D58 #x1C1F  #x7224 #x1DC1  #x7357 #x1E52)))
       (setf (svref a 56) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2432 #x12B  #x2565 #x1BC  #x2A31 #x35E  #x2B64 #x3EF
          #x3030 #x591  #x3163 #x622  #x362F #x7C4  #x3762 #x855
          #x3C2E #x9F7  #x3D61 #xA88  #x422D #xC2A  #x4360 #xCBB
          #x482C #xE5D  #x495F #xEEE  #x4E2B #x1090  #x4F5E #x1121
          #x542A #x12C3  #x555D #x1354  #x5A29 #x14F6  #x5B5C #x1587
          #x6028 #x1729  #x615B #x17BA  #x6627 #x195C  #x675A #x19ED
          #x6C26 #x1B8F  #x6D59 #x1C20  #x7225 #x1DC2  #x7358 #x1E53)))
       (setf (svref a 57) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2433 #x12C  #x2566 #x1BD  #x2A32 #x35F  #x2B65 #x3F0
          #x3031 #x592  #x3164 #x623  #x3630 #x7C5  #x3763 #x856
          #x3C2F #x9F8  #x3D62 #xA89  #x422E #xC2B  #x4361 #xCBC
          #x482D #xE5E  #x4960 #xEEF  #x4E2C #x1091  #x4F5F #x1122
          #x542B #x12C4  #x555E #x1355  #x5A2A #x14F7  #x5B5D #x1588
          #x6029 #x172A  #x615C #x17BB  #x6628 #x195D  #x675B #x19EE
          #x6C27 #x1B90  #x6D5A #x1C21  #x7226 #x1DC3  #x7359 #x1E54)))
       (setf (svref a 58) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2434 #x12D  #x2567 #x1BE  #x2A33 #x360  #x2B66 #x3F1
          #x3032 #x593  #x3165 #x624  #x3631 #x7C6  #x3764 #x857
          #x3C30 #x9F9  #x3D63 #xA8A  #x422F #xC2C  #x4362 #xCBD
          #x482E #xE5F  #x4961 #xEF0  #x4E2D #x1092  #x4F60 #x1123
          #x542C #x12C5  #x555F #x1356  #x5A2B #x14F8  #x5B5E #x1589
          #x602A #x172B  #x615D #x17BC  #x6629 #x195E  #x675C #x19EF
          #x6C28 #x1B91  #x6D5B #x1C22  #x7227 #x1DC4  #x735A #x1E55)))
       (setf (svref a 59) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2435 #x12E  #x2568 #x1BF  #x2A34 #x361  #x2B67 #x3F2
          #x3033 #x594  #x3166 #x625  #x3632 #x7C7  #x3765 #x858
          #x3C31 #x9FA  #x3D64 #xA8B  #x4230 #xC2D  #x4363 #xCBE
          #x482F #xE60  #x4962 #xEF1  #x4E2E #x1093  #x4F61 #x1124
          #x542D #x12C6  #x5560 #x1357  #x5A2C #x14F9  #x5B5F #x158A
          #x602B #x172C  #x615E #x17BD  #x662A #x195F  #x675D #x19F0
          #x6C29 #x1B92  #x6D5C #x1C23  #x7228 #x1DC5  #x735B #x1E56)))
       (setf (svref a 60) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2436 #x12F  #x2569 #x1C0  #x2A35 #x362  #x2B68 #x3F3
          #x3034 #x595  #x3167 #x626  #x3633 #x7C8  #x3766 #x859
          #x3C32 #x9FB  #x3D65 #xA8C  #x4231 #xC2E  #x4364 #xCBF
          #x4830 #xE61  #x4963 #xEF2  #x4E2F #x1094  #x4F62 #x1125
          #x542E #x12C7  #x5561 #x1358  #x5A2D #x14FA  #x5B60 #x158B
          #x602C #x172D  #x615F #x17BE  #x662B #x1960  #x675E #x19F1
          #x6C2A #x1B93  #x6D5D #x1C24  #x7229 #x1DC6  #x735C #x1E57)))
       (setf (svref a 61) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2437 #x130  #x256A #x1C1  #x2A36 #x363  #x2B69 #x3F4
          #x3035 #x596  #x3168 #x627  #x3634 #x7C9  #x3767 #x85A
          #x3C33 #x9FC  #x3D66 #xA8D  #x4232 #xC2F  #x4365 #xCC0
          #x4831 #xE62  #x4964 #xEF3  #x4E30 #x1095  #x4F63 #x1126
          #x542F #x12C8  #x5562 #x1359  #x5A2E #x14FB  #x5B61 #x158C
          #x602D #x172E  #x6160 #x17BF  #x662C #x1961  #x675F #x19F2
          #x6C2B #x1B94  #x6D5E #x1C25  #x722A #x1DC7  #x735D #x1E58)))
       (setf (svref a 62) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2438 #x131  #x256B #x1C2  #x2A37 #x364  #x2B6A #x3F5
          #x3036 #x597  #x3169 #x628  #x3635 #x7CA  #x3768 #x85B
          #x3C34 #x9FD  #x3D67 #xA8E  #x4233 #xC30  #x4366 #xCC1
          #x4832 #xE63  #x4965 #xEF4  #x4E31 #x1096  #x4F64 #x1127
          #x5430 #x12C9  #x5563 #x135A  #x5A2F #x14FC  #x5B62 #x158D
          #x602E #x172F  #x6161 #x17C0  #x662D #x1962  #x6760 #x19F3
          #x6C2C #x1B95  #x6D5F #x1C26  #x722B #x1DC8  #x735E #x1E59)))
       (setf (svref a 63) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2439 #x132  #x256C #x1C3  #x2A38 #x365  #x2B6B #x3F6
          #x3037 #x598  #x316A #x629  #x3636 #x7CB  #x3769 #x85C
          #x3C35 #x9FE  #x3D68 #xA8F  #x4234 #xC31  #x4367 #xCC2
          #x4833 #xE64  #x4966 #xEF5  #x4E32 #x1097  #x4F65 #x1128
          #x5431 #x12CA  #x5564 #x135B  #x5A30 #x14FD  #x5B63 #x158E
          #x602F #x1730  #x6162 #x17C1  #x662E #x1963  #x6761 #x19F4
          #x6C2D #x1B96  #x6D60 #x1C27  #x722C #x1DC9  #x735F #x1E5A)))
       (setf (svref a 64) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x243A #x133  #x256D #x1C4  #x2A39 #x366  #x2B6C #x3F7
          #x3038 #x599  #x316B #x62A  #x3637 #x7CC  #x376A #x85D
          #x3C36 #x9FF  #x3D69 #xA90  #x4235 #xC32  #x4368 #xCC3
          #x4834 #xE65  #x4967 #xEF6  #x4E33 #x1098  #x4F66 #x1129
          #x5432 #x12CB  #x5565 #x135C  #x5A31 #x14FE  #x5B64 #x158F
          #x6030 #x1731  #x6163 #x17C2  #x662F #x1964  #x6762 #x19F5
          #x6C2E #x1B97  #x6D61 #x1C28  #x722D #x1DCA  #x7360 #x1E5B)))
       (setf (svref a 65) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x243B #x134  #x256E #x1C5  #x2A3A #x367  #x2B6D #x3F8
          #x3039 #x59A  #x316C #x62B  #x3638 #x7CD  #x376B #x85E
          #x3C37 #xA00  #x3D6A #xA91  #x4236 #xC33  #x4369 #xCC4
          #x4835 #xE66  #x4968 #xEF7  #x4E34 #x1099  #x4F67 #x112A
          #x5433 #x12CC  #x5566 #x135D  #x5A32 #x14FF  #x5B65 #x1590
          #x6031 #x1732  #x6164 #x17C3  #x6630 #x1965  #x6763 #x19F6
          #x6C2F #x1B98  #x6D62 #x1C29  #x722E #x1DCB  #x7361 #x1E5C)))
       (setf (svref a 66) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x243C #x135  #x256F #x1C6  #x2A3B #x368  #x2B6E #x3F9
          #x303A #x59B  #x316D #x62C  #x3639 #x7CE  #x376C #x85F
          #x3C38 #xA01  #x3D6B #xA92  #x4237 #xC34  #x436A #xCC5
          #x4836 #xE67  #x4969 #xEF8  #x4E35 #x109A  #x4F68 #x112B
          #x5434 #x12CD  #x5567 #x135E  #x5A33 #x1500  #x5B66 #x1591
          #x6032 #x1733  #x6165 #x17C4  #x6631 #x1966  #x6764 #x19F7
          #x6C30 #x1B99  #x6D63 #x1C2A  #x722F #x1DCC  #x7362 #x1E5D)))
       (setf (svref a 67) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x243D #x136  #x2570 #x1C7  #x2A3C #x369  #x2B6F #x3FA
          #x303B #x59C  #x316E #x62D  #x363A #x7CF  #x376D #x860
          #x3C39 #xA02  #x3D6C #xA93  #x4238 #xC35  #x436B #xCC6
          #x4837 #xE68  #x496A #xEF9  #x4E36 #x109B  #x4F69 #x112C
          #x5435 #x12CE  #x5568 #x135F  #x5A34 #x1501  #x5B67 #x1592
          #x6033 #x1734  #x6166 #x17C5  #x6632 #x1967  #x6765 #x19F8
          #x6C31 #x1B9A  #x6D64 #x1C2B  #x7230 #x1DCD  #x7363 #x1E5E)))
       (setf (svref a 68) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x243E #x137  #x2571 #x1C8  #x2A3D #x36A  #x2B70 #x3FB
          #x303C #x59D  #x316F #x62E  #x363B #x7D0  #x376E #x861
          #x3C3A #xA03  #x3D6D #xA94  #x4239 #xC36  #x436C #xCC7
          #x4838 #xE69  #x496B #xEFA  #x4E37 #x109C  #x4F6A #x112D
          #x5436 #x12CF  #x5569 #x1360  #x5A35 #x1502  #x5B68 #x1593
          #x6034 #x1735  #x6167 #x17C6  #x6633 #x1968  #x6766 #x19F9
          #x6C32 #x1B9B  #x6D65 #x1C2C  #x7231 #x1DCE  #x7364 #x1E5F)))
       (setf (svref a 69) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x243F #x138  #x2572 #x1C9  #x2A3E #x36B  #x2B71 #x3FC
          #x303D #x59E  #x3170 #x62F  #x363C #x7D1  #x376F #x862
          #x3C3B #xA04  #x3D6E #xA95  #x423A #xC37  #x436D #xCC8
          #x4839 #xE6A  #x496C #xEFB  #x4E38 #x109D  #x4F6B #x112E
          #x5437 #x12D0  #x556A #x1361  #x5A36 #x1503  #x5B69 #x1594
          #x6035 #x1736  #x6168 #x17C7  #x6634 #x1969  #x6767 #x19FA
          #x6C33 #x1B9C  #x6D66 #x1C2D  #x7232 #x1DCF  #x7365 #x1E60)))
       (setf (svref a 70) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2440 #x139  #x2573 #x1CA  #x2A3F #x36C  #x2B72 #x3FD
          #x303E #x59F  #x3171 #x630  #x363D #x7D2  #x3770 #x863
          #x3C3C #xA05  #x3D6F #xA96  #x423B #xC38  #x436E #xCC9
          #x483A #xE6B  #x496D #xEFC  #x4E39 #x109E  #x4F6C #x112F
          #x5438 #x12D1  #x556B #x1362  #x5A37 #x1504  #x5B6A #x1595
          #x6036 #x1737  #x6169 #x17C8  #x6635 #x196A  #x6768 #x19FB
          #x6C34 #x1B9D  #x6D67 #x1C2E  #x7233 #x1DD0  #x7366 #x1E61)))
       (setf (svref a 71) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2441 #x13A  #x2574 #x1CB  #x2A40 #x36D  #x2B73 #x3FE
          #x303F #x5A0  #x3172 #x631  #x363E #x7D3  #x3771 #x864
          #x3C3D #xA06  #x3D70 #xA97  #x423C #xC39  #x436F #xCCA
          #x483B #xE6C  #x496E #xEFD  #x4E3A #x109F  #x4F6D #x1130
          #x5439 #x12D2  #x556C #x1363  #x5A38 #x1505  #x5B6B #x1596
          #x6037 #x1738  #x616A #x17C9  #x6636 #x196B  #x6769 #x19FC
          #x6C35 #x1B9E  #x6D68 #x1C2F  #x7234 #x1DD1  #x7367 #x1E62)))
       (setf (svref a 72) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2442 #x13B  #x2575 #x1CC  #x2A41 #x36E  #x2B74 #x3FF
          #x3040 #x5A1  #x3173 #x632  #x363F #x7D4  #x3772 #x865
          #x3C3E #xA07  #x3D71 #xA98  #x423D #xC3A  #x4370 #xCCB
          #x483C #xE6D  #x496F #xEFE  #x4E3B #x10A0  #x4F6E #x1131
          #x543A #x12D3  #x556D #x1364  #x5A39 #x1506  #x5B6C #x1597
          #x6038 #x1739  #x616B #x17CA  #x6637 #x196C  #x676A #x19FD
          #x6C36 #x1B9F  #x6D69 #x1C30  #x7235 #x1DD2  #x7368 #x1E63)))
       (setf (svref a 73) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2443 #x13C  #x2576 #x1CD  #x2A42 #x36F  #x2B75 #x400
          #x3041 #x5A2  #x3174 #x633  #x3640 #x7D5  #x3773 #x866
          #x3C3F #xA08  #x3D72 #xA99  #x423E #xC3B  #x4371 #xCCC
          #x483D #xE6E  #x4970 #xEFF  #x4E3C #x10A1  #x4F6F #x1132
          #x543B #x12D4  #x556E #x1365  #x5A3A #x1507  #x5B6D #x1598
          #x6039 #x173A  #x616C #x17CB  #x6638 #x196D  #x676B #x19FE
          #x6C37 #x1BA0  #x6D6A #x1C31  #x7236 #x1DD3  #x7369 #x1E64)))
       (setf (svref a 74) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2444 #x13D  #x2577 #x1CE  #x2A43 #x370  #x2B76 #x401
          #x3042 #x5A3  #x3175 #x634  #x3641 #x7D6  #x3774 #x867
          #x3C40 #xA09  #x3D73 #xA9A  #x423F #xC3C  #x4372 #xCCD
          #x483E #xE6F  #x4971 #xF00  #x4E3D #x10A2  #x4F70 #x1133
          #x543C #x12D5  #x556F #x1366  #x5A3B #x1508  #x5B6E #x1599
          #x603A #x173B  #x616D #x17CC  #x6639 #x196E  #x676C #x19FF
          #x6C38 #x1BA1  #x6D6B #x1C32  #x7237 #x1DD4  #x736A #x1E65)))
       (setf (svref a 75) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2445 #x13E  #x2578 #x1CF  #x2A44 #x371  #x2B77 #x402
          #x3043 #x5A4  #x3176 #x635  #x3642 #x7D7  #x3775 #x868
          #x3C41 #xA0A  #x3D74 #xA9B  #x4240 #xC3D  #x4373 #xCCE
          #x483F #xE70  #x4972 #xF01  #x4E3E #x10A3  #x4F71 #x1134
          #x543D #x12D6  #x5570 #x1367  #x5A3C #x1509  #x5B6F #x159A
          #x603B #x173C  #x616E #x17CD  #x663A #x196F  #x676D #x1A00
          #x6C39 #x1BA2  #x6D6C #x1C33  #x7238 #x1DD5  #x736B #x1E66)))
       (setf (svref a 76) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2446 #x13F  #x2579 #x1D0  #x2A45 #x372  #x2B78 #x403
          #x3044 #x5A5  #x3177 #x636  #x3643 #x7D8  #x3776 #x869
          #x3C42 #xA0B  #x3D75 #xA9C  #x4241 #xC3E  #x4374 #xCCF
          #x4840 #xE71  #x4973 #xF02  #x4E3F #x10A4  #x4F72 #x1135
          #x543E #x12D7  #x5571 #x1368  #x5A3D #x150A  #x5B70 #x159B
          #x603C #x173D  #x616F #x17CE  #x663B #x1970  #x676E #x1A01
          #x6C3A #x1BA3  #x6D6D #x1C34  #x7239 #x1DD6  #x736C #x1E67)))
       (setf (svref a 77) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2447 #x140  #x257A #x1D1  #x2A46 #x373  #x2B79 #x404
          #x3045 #x5A6  #x3178 #x637  #x3644 #x7D9  #x3777 #x86A
          #x3C43 #xA0C  #x3D76 #xA9D  #x4242 #xC3F  #x4375 #xCD0
          #x4841 #xE72  #x4974 #xF03  #x4E40 #x10A5  #x4F73 #x1136
          #x543F #x12D8  #x5572 #x1369  #x5A3E #x150B  #x5B71 #x159C
          #x603D #x173E  #x6170 #x17CF  #x663C #x1971  #x676F #x1A02
          #x6C3B #x1BA4  #x6D6E #x1C35  #x723A #x1DD7  #x736D #x1E68)))
       (setf (svref a 78) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2448 #x141  #x257B #x1D2  #x2A47 #x374  #x2B7A #x405
          #x3046 #x5A7  #x3179 #x638  #x3645 #x7DA  #x3778 #x86B
          #x3C44 #xA0D  #x3D77 #xA9E  #x4243 #xC40  #x4376 #xCD1
          #x4842 #xE73  #x4975 #xF04  #x4E41 #x10A6  #x4F74 #x1137
          #x5440 #x12D9  #x5573 #x136A  #x5A3F #x150C  #x5B72 #x159D
          #x603E #x173F  #x6171 #x17D0  #x663D #x1972  #x6770 #x1A03
          #x6C3C #x1BA5  #x6D6F #x1C36  #x723B #x1DD8  #x736E #x1E69)))
       (setf (svref a 79) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2449 #x142  #x257C #x1D3  #x2A48 #x375  #x2B7B #x406
          #x3047 #x5A8  #x317A #x639  #x3646 #x7DB  #x3779 #x86C
          #x3C45 #xA0E  #x3D78 #xA9F  #x4244 #xC41  #x4377 #xCD2
          #x4843 #xE74  #x4976 #xF05  #x4E42 #x10A7  #x4F75 #x1138
          #x5441 #x12DA  #x5574 #x136B  #x5A40 #x150D  #x5B73 #x159E
          #x603F #x1740  #x6172 #x17D1  #x663E #x1973  #x6771 #x1A04
          #x6C3D #x1BA6  #x6D70 #x1C37  #x723C #x1DD9  #x736F #x1E6A)))
       (setf (svref a 80) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x244A #x143  #x257D #x1D4  #x2A49 #x376  #x2B7C #x407
          #x3048 #x5A9  #x317B #x63A  #x3647 #x7DC  #x377A #x86D
          #x3C46 #xA0F  #x3D79 #xAA0  #x4245 #xC42  #x4378 #xCD3
          #x4844 #xE75  #x4977 #xF06  #x4E43 #x10A8  #x4F76 #x1139
          #x5442 #x12DB  #x5575 #x136C  #x5A41 #x150E  #x5B74 #x159F
          #x6040 #x1741  #x6173 #x17D2  #x663F #x1974  #x6772 #x1A05
          #x6C3E #x1BA7  #x6D71 #x1C38  #x723D #x1DDA  #x7370 #x1E6B)))
       (setf (svref a 81) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x244B #x144  #x257E #x1D5  #x2A4A #x377  #x2B7D #x408
          #x3049 #x5AA  #x317C #x63B  #x3648 #x7DD  #x377B #x86E
          #x3C47 #xA10  #x3D7A #xAA1  #x4246 #xC43  #x4379 #xCD4
          #x4845 #xE76  #x4978 #xF07  #x4E44 #x10A9  #x4F77 #x113A
          #x5443 #x12DC  #x5576 #x136D  #x5A42 #x150F  #x5B75 #x15A0
          #x6041 #x1742  #x6174 #x17D3  #x6640 #x1975  #x6773 #x1A06
          #x6C3F #x1BA8  #x6D72 #x1C39  #x723E #x1DDB  #x7371 #x1E6C)))
       (setf (svref a 82) (make-array 54 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x244C #x145  #x2A4B #x378  #x2B7E #x409  #x304A #x5AB
          #x317D #x63C  #x3649 #x7DE  #x377C #x86F  #x3C48 #xA11
          #x3D7B #xAA2  #x4247 #xC44  #x437A #xCD5  #x4846 #xE77
          #x4979 #xF08  #x4E45 #x10AA  #x4F78 #x113B  #x5444 #x12DD
          #x5577 #x136E  #x5A43 #x1510  #x5B76 #x15A1  #x6042 #x1743
          #x6175 #x17D4  #x6641 #x1976  #x6774 #x1A07  #x6C40 #x1BA9
          #x6D73 #x1C3A  #x723F #x1DDC  #x7372 #x1E6D)))
       (setf (svref a 83) (make-array 52 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x244D #x146  #x2A4C #x379  #x304B #x5AC  #x317E #x63D
          #x364A #x7DF  #x377D #x870  #x3C49 #xA12  #x3D7C #xAA3
          #x4248 #xC45  #x437B #xCD6  #x4847 #xE78  #x497A #xF09
          #x4E46 #x10AB  #x4F79 #x113C  #x5445 #x12DE  #x5578 #x136F
          #x5A44 #x1511  #x5B77 #x15A2  #x6043 #x1744  #x6176 #x17D5
          #x6642 #x1977  #x6775 #x1A08  #x6C41 #x1BAA  #x6D74 #x1C3B
          #x7240 #x1DDD  #x7373 #x1E6E)))
       (setf (svref a 84) (make-array 50 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x244E #x147  #x2A4D #x37A  #x304C #x5AD  #x364B #x7E0
          #x377E #x871  #x3C4A #xA13  #x3D7D #xAA4  #x4249 #xC46
          #x437C #xCD7  #x4848 #xE79  #x497B #xF0A  #x4E47 #x10AC
          #x4F7A #x113D  #x5446 #x12DF  #x5579 #x1370  #x5A45 #x1512
          #x5B78 #x15A3  #x6044 #x1745  #x6177 #x17D6  #x6643 #x1978
          #x6776 #x1A09  #x6C42 #x1BAB  #x6D75 #x1C3C  #x7241 #x1DDE
          #x7374 #x1E6F)))
       (setf (svref a 85) (make-array 48 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x244F #x148  #x2A4E #x37B  #x304D #x5AE  #x364C #x7E1
          #x3C4B #xA14  #x3D7E #xAA5  #x424A #xC47  #x437D #xCD8
          #x4849 #xE7A  #x497C #xF0B  #x4E48 #x10AD  #x4F7B #x113E
          #x5447 #x12E0  #x557A #x1371  #x5A46 #x1513  #x5B79 #x15A4
          #x6045 #x1746  #x6178 #x17D7  #x6644 #x1979  #x6777 #x1A0A
          #x6C43 #x1BAC  #x6D76 #x1C3D  #x7242 #x1DDF  #x7375 #x1E70)))
       (setf (svref a 86) (make-array 46 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2450 #x149  #x2A4F #x37C  #x304E #x5AF  #x364D #x7E2
          #x3C4C #xA15  #x424B #xC48  #x437E #xCD9  #x484A #xE7B
          #x497D #xF0C  #x4E49 #x10AE  #x4F7C #x113F  #x5448 #x12E1
          #x557B #x1372  #x5A47 #x1514  #x5B7A #x15A5  #x6046 #x1747
          #x6179 #x17D8  #x6645 #x197A  #x6778 #x1A0B  #x6C44 #x1BAD
          #x6D77 #x1C3E  #x7243 #x1DE0  #x7376 #x1E71)))
       (setf (svref a 87) (make-array 44 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2451 #x14A  #x2A50 #x37D  #x304F #x5B0  #x364E #x7E3
          #x3C4D #xA16  #x424C #xC49  #x484B #xE7C  #x497E #xF0D
          #x4E4A #x10AF  #x4F7D #x1140  #x5449 #x12E2  #x557C #x1373
          #x5A48 #x1515  #x5B7B #x15A6  #x6047 #x1748  #x617A #x17D9
          #x6646 #x197B  #x6779 #x1A0C  #x6C45 #x1BAE  #x6D78 #x1C3F
          #x7244 #x1DE1  #x7377 #x1E72)))
       (setf (svref a 88) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2452 #x14B  #x2A51 #x37E  #x3050 #x5B1  #x364F #x7E4
          #x3C4E #xA17  #x424D #xC4A  #x484C #xE7D  #x4E4B #x10B0
          #x4F7E #x1141  #x544A #x12E3  #x557D #x1374  #x5A49 #x1516
          #x5B7C #x15A7  #x6048 #x1749  #x617B #x17DA  #x6647 #x197C
          #x677A #x1A0D  #x6C46 #x1BAF  #x6D79 #x1C40  #x7245 #x1DE2
          #x7378 #x1E73)))
       (setf (svref a 89) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2453 #x14C  #x2A52 #x37F  #x3051 #x5B2  #x3650 #x7E5
          #x3C4F #xA18  #x424E #xC4B  #x484D #xE7E  #x4E4C #x10B1
          #x544B #x12E4  #x557E #x1375  #x5A4A #x1517  #x5B7D #x15A8
          #x6049 #x174A  #x617C #x17DB  #x6648 #x197D  #x677B #x1A0E
          #x6C47 #x1BB0  #x6D7A #x1C41  #x7246 #x1DE3  #x7379 #x1E74)))
       (setf (svref a 90) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2321 #xBC  #x2454 #x14D  #x2A53 #x380  #x3052 #x5B3
          #x3651 #x7E6  #x3C50 #xA19  #x424F #xC4C  #x484E #xE7F
          #x4E4D #x10B2  #x544C #x12E5  #x5A4B #x1518  #x5B7E #x15A9
          #x604A #x174B  #x617D #x17DC  #x6649 #x197E  #x677C #x1A0F
          #x6C48 #x1BB1  #x6D7B #x1C42  #x7247 #x1DE4  #x737A #x1E75)))
       (setf (svref a 91) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2322 #xBD  #x2455 #x14E  #x2921 #x2F0  #x2A54 #x381
          #x3053 #x5B4  #x3652 #x7E7  #x3C51 #xA1A  #x4250 #xC4D
          #x484F #xE80  #x4E4E #x10B3  #x544D #x12E6  #x5A4C #x1519
          #x604B #x174C  #x617E #x17DD  #x664A #x197F  #x677D #x1A10
          #x6C49 #x1BB2  #x6D7C #x1C43  #x7248 #x1DE5  #x737B #x1E76)))
       (setf (svref a 92) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2323 #xBE  #x2456 #x14F  #x2922 #x2F1  #x2A55 #x382
          #x2F21 #x524  #x3054 #x5B5  #x3653 #x7E8  #x3C52 #xA1B
          #x4251 #xC4E  #x4850 #xE81  #x4E4F #x10B4  #x544E #x12E7
          #x5A4D #x151A  #x604C #x174D  #x664B #x1980  #x677E #x1A11
          #x6C4A #x1BB3  #x6D7D #x1C44  #x7249 #x1DE6  #x737C #x1E77)))
       (setf (svref a 93) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2324 #xBF  #x2457 #x150  #x2923 #x2F2  #x2A56 #x383
          #x2F22 #x525  #x3055 #x5B6  #x3521 #x758  #x3654 #x7E9
          #x3C53 #xA1C  #x4252 #xC4F  #x4851 #xE82  #x4E50 #x10B5
          #x544F #x12E8  #x5A4E #x151B  #x604D #x174E  #x664C #x1981
          #x6C4B #x1BB4  #x6D7E #x1C45  #x724A #x1DE7  #x737D #x1E78)))
       (setf (svref a 94) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2325 #xC0  #x2458 #x151  #x2924 #x2F3  #x2A57 #x384
          #x2F23 #x526  #x3056 #x5B7  #x3522 #x759  #x3655 #x7EA
          #x3B21 #x98C  #x3C54 #xA1D  #x4253 #xC50  #x4852 #xE83
          #x4E51 #x10B6  #x5450 #x12E9  #x5A4F #x151C  #x604E #x174F
          #x664D #x1982  #x6C4C #x1BB5  #x724B #x1DE8  #x737E #x1E79)))
       (setf (svref a 95) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2326 #xC1  #x2459 #x152  #x2925 #x2F4  #x2A58 #x385
          #x2F24 #x527  #x3057 #x5B8  #x3523 #x75A  #x3656 #x7EB
          #x3B22 #x98D  #x3C55 #xA1E  #x4121 #xBC0  #x4254 #xC51
          #x4853 #xE84  #x4E52 #x10B7  #x5451 #x12EA  #x5A50 #x151D
          #x604F #x1750  #x664E #x1983  #x6C4D #x1BB6  #x724C #x1DE9)))
       (setf (svref a 96) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2327 #xC2  #x245A #x153  #x2926 #x2F5  #x2A59 #x386
          #x2F25 #x528  #x3058 #x5B9  #x3524 #x75B  #x3657 #x7EC
          #x3B23 #x98E  #x3C56 #xA1F  #x4122 #xBC1  #x4255 #xC52
          #x4721 #xDF4  #x4854 #xE85  #x4E53 #x10B8  #x5452 #x12EB
          #x5A51 #x151E  #x6050 #x1751  #x664F #x1984  #x6C4E #x1BB7
          #x724D #x1DEA)))
       (setf (svref a 97) (make-array 44 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2328 #xC3  #x245B #x154  #x2927 #x2F6  #x2A5A #x387
          #x2F26 #x529  #x3059 #x5BA  #x3525 #x75C  #x3658 #x7ED
          #x3B24 #x98F  #x3C57 #xA20  #x4123 #xBC2  #x4256 #xC53
          #x4722 #xDF5  #x4855 #xE86  #x4D21 #x1028  #x4E54 #x10B9
          #x5453 #x12EC  #x5A52 #x151F  #x6051 #x1752  #x6650 #x1985
          #x6C4F #x1BB8  #x724E #x1DEB)))
       (setf (svref a 98) (make-array 46 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2329 #xC4  #x245C #x155  #x2928 #x2F7  #x2A5B #x388
          #x2F27 #x52A  #x305A #x5BB  #x3526 #x75D  #x3659 #x7EE
          #x3B25 #x990  #x3C58 #xA21  #x4124 #xBC3  #x4257 #xC54
          #x4723 #xDF6  #x4856 #xE87  #x4D22 #x1029  #x4E55 #x10BA
          #x5321 #x125C  #x5454 #x12ED  #x5A53 #x1520  #x6052 #x1753
          #x6651 #x1986  #x6C50 #x1BB9  #x724F #x1DEC)))
       (setf (svref a 99) (make-array 48 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x232A #xC5  #x245D #x156  #x2929 #x2F8  #x2A5C #x389
          #x2F28 #x52B  #x305B #x5BC  #x3527 #x75E  #x365A #x7EF
          #x3B26 #x991  #x3C59 #xA22  #x4125 #xBC4  #x4258 #xC55
          #x4724 #xDF7  #x4857 #xE88  #x4D23 #x102A  #x4E56 #x10BB
          #x5322 #x125D  #x5455 #x12EE  #x5921 #x1490  #x5A54 #x1521
          #x6053 #x1754  #x6652 #x1987  #x6C51 #x1BBA  #x7250 #x1DED)))
       (setf (svref a 100) (make-array 50 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x232B #xC6  #x245E #x157  #x292A #x2F9  #x2A5D #x38A
          #x2F29 #x52C  #x305C #x5BD  #x3528 #x75F  #x365B #x7F0
          #x3B27 #x992  #x3C5A #xA23  #x4126 #xBC5  #x4259 #xC56
          #x4725 #xDF8  #x4858 #xE89  #x4D24 #x102B  #x4E57 #x10BC
          #x5323 #x125E  #x5456 #x12EF  #x5922 #x1491  #x5A55 #x1522
          #x5F21 #x16C4  #x6054 #x1755  #x6653 #x1988  #x6C52 #x1BBB
          #x7251 #x1DEE)))
       (setf (svref a 101) (make-array 52 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x232C #xC7  #x245F #x158  #x292B #x2FA  #x2A5E #x38B
          #x2F2A #x52D  #x305D #x5BE  #x3529 #x760  #x365C #x7F1
          #x3B28 #x993  #x3C5B #xA24  #x4127 #xBC6  #x425A #xC57
          #x4726 #xDF9  #x4859 #xE8A  #x4D25 #x102C  #x4E58 #x10BD
          #x5324 #x125F  #x5457 #x12F0  #x5923 #x1492  #x5A56 #x1523
          #x5F22 #x16C5  #x6055 #x1756  #x6521 #x18F8  #x6654 #x1989
          #x6C53 #x1BBC  #x7252 #x1DEF)))
       (setf (svref a 102) (make-array 54 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x232D #xC8  #x2460 #x159  #x292C #x2FB  #x2A5F #x38C
          #x2F2B #x52E  #x305E #x5BF  #x352A #x761  #x365D #x7F2
          #x3B29 #x994  #x3C5C #xA25  #x4128 #xBC7  #x425B #xC58
          #x4727 #xDFA  #x485A #xE8B  #x4D26 #x102D  #x4E59 #x10BE
          #x5325 #x1260  #x5458 #x12F1  #x5924 #x1493  #x5A57 #x1524
          #x5F23 #x16C6  #x6056 #x1757  #x6522 #x18F9  #x6655 #x198A
          #x6B21 #x1B2C  #x6C54 #x1BBD  #x7253 #x1DF0)))
       (setf (svref a 103) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x232E #xC9  #x2461 #x15A  #x292D #x2FC  #x2A60 #x38D
          #x2F2C #x52F  #x305F #x5C0  #x352B #x762  #x365E #x7F3
          #x3B2A #x995  #x3C5D #xA26  #x4129 #xBC8  #x425C #xC59
          #x4728 #xDFB  #x485B #xE8C  #x4D27 #x102E  #x4E5A #x10BF
          #x5326 #x1261  #x5459 #x12F2  #x5925 #x1494  #x5A58 #x1525
          #x5F24 #x16C7  #x6057 #x1758  #x6523 #x18FA  #x6656 #x198B
          #x6B22 #x1B2D  #x6C55 #x1BBE  #x7121 #x1D60  #x7254 #x1DF1)))
       (setf (svref a 104) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x232F #xCA  #x2462 #x15B  #x292E #x2FD  #x2A61 #x38E
          #x2F2D #x530  #x3060 #x5C1  #x352C #x763  #x365F #x7F4
          #x3B2B #x996  #x3C5E #xA27  #x412A #xBC9  #x425D #xC5A
          #x4729 #xDFC  #x485C #xE8D  #x4D28 #x102F  #x4E5B #x10C0
          #x5327 #x1262  #x545A #x12F3  #x5926 #x1495  #x5A59 #x1526
          #x5F25 #x16C8  #x6058 #x1759  #x6524 #x18FB  #x6657 #x198C
          #x6B23 #x1B2E  #x6C56 #x1BBF  #x7122 #x1D61  #x7255 #x1DF2
          #x7721 #x1F94)))
       (setf (svref a 105) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2330 #xCB  #x2463 #x15C  #x292F #x2FE  #x2A62 #x38F
          #x2F2E #x531  #x3061 #x5C2  #x352D #x764  #x3660 #x7F5
          #x3B2C #x997  #x3C5F #xA28  #x412B #xBCA  #x425E #xC5B
          #x472A #xDFD  #x485D #xE8E  #x4D29 #x1030  #x4E5C #x10C1
          #x5328 #x1263  #x545B #x12F4  #x5927 #x1496  #x5A5A #x1527
          #x5F26 #x16C9  #x6059 #x175A  #x6525 #x18FC  #x6658 #x198D
          #x6B24 #x1B2F  #x6C57 #x1BC0  #x7123 #x1D62  #x7256 #x1DF3
          #x7722 #x1F95)))
       (setf (svref a 106) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2331 #xCC  #x2464 #x15D  #x2930 #x2FF  #x2A63 #x390
          #x2F2F #x532  #x3062 #x5C3  #x352E #x765  #x3661 #x7F6
          #x3B2D #x998  #x3C60 #xA29  #x412C #xBCB  #x425F #xC5C
          #x472B #xDFE  #x485E #xE8F  #x4D2A #x1031  #x4E5D #x10C2
          #x5329 #x1264  #x545C #x12F5  #x5928 #x1497  #x5A5B #x1528
          #x5F27 #x16CA  #x605A #x175B  #x6526 #x18FD  #x6659 #x198E
          #x6B25 #x1B30  #x6C58 #x1BC1  #x7124 #x1D63  #x7257 #x1DF4
          #x7723 #x1F96)))
       (setf (svref a 107) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2332 #xCD  #x2465 #x15E  #x2931 #x300  #x2A64 #x391
          #x2F30 #x533  #x3063 #x5C4  #x352F #x766  #x3662 #x7F7
          #x3B2E #x999  #x3C61 #xA2A  #x412D #xBCC  #x4260 #xC5D
          #x472C #xDFF  #x485F #xE90  #x4D2B #x1032  #x4E5E #x10C3
          #x532A #x1265  #x545D #x12F6  #x5929 #x1498  #x5A5C #x1529
          #x5F28 #x16CB  #x605B #x175C  #x6527 #x18FE  #x665A #x198F
          #x6B26 #x1B31  #x6C59 #x1BC2  #x7125 #x1D64  #x7258 #x1DF5
          #x7724 #x1F97)))
       (setf (svref a 108) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2333 #xCE  #x2466 #x15F  #x2932 #x301  #x2A65 #x392
          #x2F31 #x534  #x3064 #x5C5  #x3530 #x767  #x3663 #x7F8
          #x3B2F #x99A  #x3C62 #xA2B  #x412E #xBCD  #x4261 #xC5E
          #x472D #xE00  #x4860 #xE91  #x4D2C #x1033  #x4E5F #x10C4
          #x532B #x1266  #x545E #x12F7  #x592A #x1499  #x5A5D #x152A
          #x5F29 #x16CC  #x605C #x175D  #x6528 #x18FF  #x665B #x1990
          #x6B27 #x1B32  #x6C5A #x1BC3  #x7126 #x1D65  #x7259 #x1DF6
          #x7725 #x1F98)))
       (setf (svref a 109) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2334 #xCF  #x2467 #x160  #x2933 #x302  #x2A66 #x393
          #x2F32 #x535  #x3065 #x5C6  #x3531 #x768  #x3664 #x7F9
          #x3B30 #x99B  #x3C63 #xA2C  #x412F #xBCE  #x4262 #xC5F
          #x472E #xE01  #x4861 #xE92  #x4D2D #x1034  #x4E60 #x10C5
          #x532C #x1267  #x545F #x12F8  #x592B #x149A  #x5A5E #x152B
          #x5F2A #x16CD  #x605D #x175E  #x6529 #x1900  #x665C #x1991
          #x6B28 #x1B33  #x6C5B #x1BC4  #x7127 #x1D66  #x725A #x1DF7
          #x7726 #x1F99)))
       (setf (svref a 110) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2335 #xD0  #x2468 #x161  #x2934 #x303  #x2A67 #x394
          #x2F33 #x536  #x3066 #x5C7  #x3532 #x769  #x3665 #x7FA
          #x3B31 #x99C  #x3C64 #xA2D  #x4130 #xBCF  #x4263 #xC60
          #x472F #xE02  #x4862 #xE93  #x4D2E #x1035  #x4E61 #x10C6
          #x532D #x1268  #x5460 #x12F9  #x592C #x149B  #x5A5F #x152C
          #x5F2B #x16CE  #x605E #x175F  #x652A #x1901  #x665D #x1992
          #x6B29 #x1B34  #x6C5C #x1BC5  #x7128 #x1D67  #x725B #x1DF8
          #x7727 #x1F9A)))
       (setf (svref a 111) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2336 #xD1  #x2469 #x162  #x2935 #x304  #x2A68 #x395
          #x2F34 #x537  #x3067 #x5C8  #x3533 #x76A  #x3666 #x7FB
          #x3B32 #x99D  #x3C65 #xA2E  #x4131 #xBD0  #x4264 #xC61
          #x4730 #xE03  #x4863 #xE94  #x4D2F #x1036  #x4E62 #x10C7
          #x532E #x1269  #x5461 #x12FA  #x592D #x149C  #x5A60 #x152D
          #x5F2C #x16CF  #x605F #x1760  #x652B #x1902  #x665E #x1993
          #x6B2A #x1B35  #x6C5D #x1BC6  #x7129 #x1D68  #x725C #x1DF9
          #x7728 #x1F9B)))
       (setf (svref a 112) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2337 #xD2  #x246A #x163  #x2936 #x305  #x2A69 #x396
          #x2F35 #x538  #x3068 #x5C9  #x3534 #x76B  #x3667 #x7FC
          #x3B33 #x99E  #x3C66 #xA2F  #x4132 #xBD1  #x4265 #xC62
          #x4731 #xE04  #x4864 #xE95  #x4D30 #x1037  #x4E63 #x10C8
          #x532F #x126A  #x5462 #x12FB  #x592E #x149D  #x5A61 #x152E
          #x5F2D #x16D0  #x6060 #x1761  #x652C #x1903  #x665F #x1994
          #x6B2B #x1B36  #x6C5E #x1BC7  #x712A #x1D69  #x725D #x1DFA
          #x7729 #x1F9C)))
       (setf (svref a 113) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2338 #xD3  #x246B #x164  #x2937 #x306  #x2A6A #x397
          #x2F36 #x539  #x3069 #x5CA  #x3535 #x76C  #x3668 #x7FD
          #x3B34 #x99F  #x3C67 #xA30  #x4133 #xBD2  #x4266 #xC63
          #x4732 #xE05  #x4865 #xE96  #x4D31 #x1038  #x4E64 #x10C9
          #x5330 #x126B  #x5463 #x12FC  #x592F #x149E  #x5A62 #x152F
          #x5F2E #x16D1  #x6061 #x1762  #x652D #x1904  #x6660 #x1995
          #x6B2C #x1B37  #x6C5F #x1BC8  #x712B #x1D6A  #x725E #x1DFB
          #x772A #x1F9D)))
       (setf (svref a 114) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2339 #xD4  #x246C #x165  #x2938 #x307  #x2A6B #x398
          #x2F37 #x53A  #x306A #x5CB  #x3536 #x76D  #x3669 #x7FE
          #x3B35 #x9A0  #x3C68 #xA31  #x4134 #xBD3  #x4267 #xC64
          #x4733 #xE06  #x4866 #xE97  #x4D32 #x1039  #x4E65 #x10CA
          #x5331 #x126C  #x5464 #x12FD  #x5930 #x149F  #x5A63 #x1530
          #x5F2F #x16D2  #x6062 #x1763  #x652E #x1905  #x6661 #x1996
          #x6B2D #x1B38  #x6C60 #x1BC9  #x712C #x1D6B  #x725F #x1DFC
          #x772B #x1F9E)))
       (setf (svref a 115) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x233A #xD5  #x246D #x166  #x2939 #x308  #x2A6C #x399
          #x2F38 #x53B  #x306B #x5CC  #x3537 #x76E  #x366A #x7FF
          #x3B36 #x9A1  #x3C69 #xA32  #x4135 #xBD4  #x4268 #xC65
          #x4734 #xE07  #x4867 #xE98  #x4D33 #x103A  #x4E66 #x10CB
          #x5332 #x126D  #x5465 #x12FE  #x5931 #x14A0  #x5A64 #x1531
          #x5F30 #x16D3  #x6063 #x1764  #x652F #x1906  #x6662 #x1997
          #x6B2E #x1B39  #x6C61 #x1BCA  #x712D #x1D6C  #x7260 #x1DFD
          #x772C #x1F9F)))
       (setf (svref a 116) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x233B #xD6  #x246E #x167  #x293A #x309  #x2A6D #x39A
          #x2F39 #x53C  #x306C #x5CD  #x3538 #x76F  #x366B #x800
          #x3B37 #x9A2  #x3C6A #xA33  #x4136 #xBD5  #x4269 #xC66
          #x4735 #xE08  #x4868 #xE99  #x4D34 #x103B  #x4E67 #x10CC
          #x5333 #x126E  #x5466 #x12FF  #x5932 #x14A1  #x5A65 #x1532
          #x5F31 #x16D4  #x6064 #x1765  #x6530 #x1907  #x6663 #x1998
          #x6B2F #x1B3A  #x6C62 #x1BCB  #x712E #x1D6D  #x7261 #x1DFE
          #x772D #x1FA0)))
       (setf (svref a 117) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x233C #xD7  #x246F #x168  #x293B #x30A  #x2A6E #x39B
          #x2F3A #x53D  #x306D #x5CE  #x3539 #x770  #x366C #x801
          #x3B38 #x9A3  #x3C6B #xA34  #x4137 #xBD6  #x426A #xC67
          #x4736 #xE09  #x4869 #xE9A  #x4D35 #x103C  #x4E68 #x10CD
          #x5334 #x126F  #x5467 #x1300  #x5933 #x14A2  #x5A66 #x1533
          #x5F32 #x16D5  #x6065 #x1766  #x6531 #x1908  #x6664 #x1999
          #x6B30 #x1B3B  #x6C63 #x1BCC  #x712F #x1D6E  #x7262 #x1DFF
          #x772E #x1FA1)))
       (setf (svref a 118) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x233D #xD8  #x2470 #x169  #x293C #x30B  #x2A6F #x39C
          #x2F3B #x53E  #x306E #x5CF  #x353A #x771  #x366D #x802
          #x3B39 #x9A4  #x3C6C #xA35  #x4138 #xBD7  #x426B #xC68
          #x4737 #xE0A  #x486A #xE9B  #x4D36 #x103D  #x4E69 #x10CE
          #x5335 #x1270  #x5468 #x1301  #x5934 #x14A3  #x5A67 #x1534
          #x5F33 #x16D6  #x6066 #x1767  #x6532 #x1909  #x6665 #x199A
          #x6B31 #x1B3C  #x6C64 #x1BCD  #x7130 #x1D6F  #x7263 #x1E00
          #x772F #x1FA2)))
       (setf (svref a 119) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x233E #xD9  #x2471 #x16A  #x293D #x30C  #x2A70 #x39D
          #x2F3C #x53F  #x306F #x5D0  #x353B #x772  #x366E #x803
          #x3B3A #x9A5  #x3C6D #xA36  #x4139 #xBD8  #x426C #xC69
          #x4738 #xE0B  #x486B #xE9C  #x4D37 #x103E  #x4E6A #x10CF
          #x5336 #x1271  #x5469 #x1302  #x5935 #x14A4  #x5A68 #x1535
          #x5F34 #x16D7  #x6067 #x1768  #x6533 #x190A  #x6666 #x199B
          #x6B32 #x1B3D  #x6C65 #x1BCE  #x7131 #x1D70  #x7264 #x1E01
          #x7730 #x1FA3)))
       (setf (svref a 120) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x233F #xDA  #x2472 #x16B  #x293E #x30D  #x2A71 #x39E
          #x2F3D #x540  #x3070 #x5D1  #x353C #x773  #x366F #x804
          #x3B3B #x9A6  #x3C6E #xA37  #x413A #xBD9  #x426D #xC6A
          #x4739 #xE0C  #x486C #xE9D  #x4D38 #x103F  #x4E6B #x10D0
          #x5337 #x1272  #x546A #x1303  #x5936 #x14A5  #x5A69 #x1536
          #x5F35 #x16D8  #x6068 #x1769  #x6534 #x190B  #x6667 #x199C
          #x6B33 #x1B3E  #x6C66 #x1BCF  #x7132 #x1D71  #x7265 #x1E02
          #x7731 #x1FA4)))
       (setf (svref a 121) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2340 #xDB  #x2473 #x16C  #x293F #x30E  #x2A72 #x39F
          #x2F3E #x541  #x3071 #x5D2  #x353D #x774  #x3670 #x805
          #x3B3C #x9A7  #x3C6F #xA38  #x413B #xBDA  #x426E #xC6B
          #x473A #xE0D  #x486D #xE9E  #x4D39 #x1040  #x4E6C #x10D1
          #x5338 #x1273  #x546B #x1304  #x5937 #x14A6  #x5A6A #x1537
          #x5F36 #x16D9  #x6069 #x176A  #x6535 #x190C  #x6668 #x199D
          #x6B34 #x1B3F  #x6C67 #x1BD0  #x7133 #x1D72  #x7266 #x1E03
          #x7732 #x1FA5)))
       (setf (svref a 122) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2341 #xDC  #x2474 #x16D  #x2940 #x30F  #x2A73 #x3A0
          #x2F3F #x542  #x3072 #x5D3  #x353E #x775  #x3671 #x806
          #x3B3D #x9A8  #x3C70 #xA39  #x413C #xBDB  #x426F #xC6C
          #x473B #xE0E  #x486E #xE9F  #x4D3A #x1041  #x4E6D #x10D2
          #x5339 #x1274  #x546C #x1305  #x5938 #x14A7  #x5A6B #x1538
          #x5F37 #x16DA  #x606A #x176B  #x6536 #x190D  #x6669 #x199E
          #x6B35 #x1B40  #x6C68 #x1BD1  #x7134 #x1D73  #x7267 #x1E04
          #x7733 #x1FA6)))
       (setf (svref a 123) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2342 #xDD  #x2475 #x16E  #x2941 #x310  #x2A74 #x3A1
          #x2F40 #x543  #x3073 #x5D4  #x353F #x776  #x3672 #x807
          #x3B3E #x9A9  #x3C71 #xA3A  #x413D #xBDC  #x4270 #xC6D
          #x473C #xE0F  #x486F #xEA0  #x4D3B #x1042  #x4E6E #x10D3
          #x533A #x1275  #x546D #x1306  #x5939 #x14A8  #x5A6C #x1539
          #x5F38 #x16DB  #x606B #x176C  #x6537 #x190E  #x666A #x199F
          #x6B36 #x1B41  #x6C69 #x1BD2  #x7135 #x1D74  #x7268 #x1E05
          #x7734 #x1FA7)))
       (setf (svref a 124) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2343 #xDE  #x2476 #x16F  #x2942 #x311  #x2A75 #x3A2
          #x2F41 #x544  #x3074 #x5D5  #x3540 #x777  #x3673 #x808
          #x3B3F #x9AA  #x3C72 #xA3B  #x413E #xBDD  #x4271 #xC6E
          #x473D #xE10  #x4870 #xEA1  #x4D3C #x1043  #x4E6F #x10D4
          #x533B #x1276  #x546E #x1307  #x593A #x14A9  #x5A6D #x153A
          #x5F39 #x16DC  #x606C #x176D  #x6538 #x190F  #x666B #x19A0
          #x6B37 #x1B42  #x6C6A #x1BD3  #x7136 #x1D75  #x7269 #x1E06
          #x7735 #x1FA8)))
       (setf (svref a 125) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2344 #xDF  #x2477 #x170  #x2943 #x312  #x2A76 #x3A3
          #x2F42 #x545  #x3075 #x5D6  #x3541 #x778  #x3674 #x809
          #x3B40 #x9AB  #x3C73 #xA3C  #x413F #xBDE  #x4272 #xC6F
          #x473E #xE11  #x4871 #xEA2  #x4D3D #x1044  #x4E70 #x10D5
          #x533C #x1277  #x546F #x1308  #x593B #x14AA  #x5A6E #x153B
          #x5F3A #x16DD  #x606D #x176E  #x6539 #x1910  #x666C #x19A1
          #x6B38 #x1B43  #x6C6B #x1BD4  #x7137 #x1D76  #x726A #x1E07
          #x7736 #x1FA9)))
       (setf (svref a 126) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2345 #xE0  #x2478 #x171  #x2944 #x313  #x2A77 #x3A4
          #x2F43 #x546  #x3076 #x5D7  #x3542 #x779  #x3675 #x80A
          #x3B41 #x9AC  #x3C74 #xA3D  #x4140 #xBDF  #x4273 #xC70
          #x473F #xE12  #x4872 #xEA3  #x4D3E #x1045  #x4E71 #x10D6
          #x533D #x1278  #x5470 #x1309  #x593C #x14AB  #x5A6F #x153C
          #x5F3B #x16DE  #x606E #x176F  #x653A #x1911  #x666D #x19A2
          #x6B39 #x1B44  #x6C6C #x1BD5  #x7138 #x1D77  #x726B #x1E08
          #x7737 #x1FAA)))
       (setf (svref a 127) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2346 #xE1  #x2479 #x172  #x2945 #x314  #x2A78 #x3A5
          #x2F44 #x547  #x3077 #x5D8  #x3543 #x77A  #x3676 #x80B
          #x3B42 #x9AD  #x3C75 #xA3E  #x4141 #xBE0  #x4274 #xC71
          #x4740 #xE13  #x4873 #xEA4  #x4D3F #x1046  #x4E72 #x10D7
          #x533E #x1279  #x5471 #x130A  #x593D #x14AC  #x5A70 #x153D
          #x5F3C #x16DF  #x606F #x1770  #x653B #x1912  #x666E #x19A3
          #x6B3A #x1B45  #x6C6D #x1BD6  #x7139 #x1D78  #x726C #x1E09
          #x7738 #x1FAB)))
       (setf (svref a 128) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2347 #xE2  #x247A #x173  #x2946 #x315  #x2A79 #x3A6
          #x2F45 #x548  #x3078 #x5D9  #x3544 #x77B  #x3677 #x80C
          #x3B43 #x9AE  #x3C76 #xA3F  #x4142 #xBE1  #x4275 #xC72
          #x4741 #xE14  #x4874 #xEA5  #x4D40 #x1047  #x4E73 #x10D8
          #x533F #x127A  #x5472 #x130B  #x593E #x14AD  #x5A71 #x153E
          #x5F3D #x16E0  #x6070 #x1771  #x653C #x1913  #x666F #x19A4
          #x6B3B #x1B46  #x6C6E #x1BD7  #x713A #x1D79  #x726D #x1E0A
          #x7739 #x1FAC)))
       (setf (svref a 129) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2348 #xE3  #x247B #x174  #x2947 #x316  #x2A7A #x3A7
          #x2F46 #x549  #x3079 #x5DA  #x3545 #x77C  #x3678 #x80D
          #x3B44 #x9AF  #x3C77 #xA40  #x4143 #xBE2  #x4276 #xC73
          #x4742 #xE15  #x4875 #xEA6  #x4D41 #x1048  #x4E74 #x10D9
          #x5340 #x127B  #x5473 #x130C  #x593F #x14AE  #x5A72 #x153F
          #x5F3E #x16E1  #x6071 #x1772  #x653D #x1914  #x6670 #x19A5
          #x6B3C #x1B47  #x6C6F #x1BD8  #x713B #x1D7A  #x726E #x1E0B
          #x773A #x1FAD)))
       (setf (svref a 130) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2349 #xE4  #x247C #x175  #x2948 #x317  #x2A7B #x3A8
          #x2F47 #x54A  #x307A #x5DB  #x3546 #x77D  #x3679 #x80E
          #x3B45 #x9B0  #x3C78 #xA41  #x4144 #xBE3  #x4277 #xC74
          #x4743 #xE16  #x4876 #xEA7  #x4D42 #x1049  #x4E75 #x10DA
          #x5341 #x127C  #x5474 #x130D  #x5940 #x14AF  #x5A73 #x1540
          #x5F3F #x16E2  #x6072 #x1773  #x653E #x1915  #x6671 #x19A6
          #x6B3D #x1B48  #x6C70 #x1BD9  #x713C #x1D7B  #x726F #x1E0C
          #x773B #x1FAE)))
       (setf (svref a 131) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x234A #xE5  #x247D #x176  #x2949 #x318  #x2A7C #x3A9
          #x2F48 #x54B  #x307B #x5DC  #x3547 #x77E  #x367A #x80F
          #x3B46 #x9B1  #x3C79 #xA42  #x4145 #xBE4  #x4278 #xC75
          #x4744 #xE17  #x4877 #xEA8  #x4D43 #x104A  #x4E76 #x10DB
          #x5342 #x127D  #x5475 #x130E  #x5941 #x14B0  #x5A74 #x1541
          #x5F40 #x16E3  #x6073 #x1774  #x653F #x1916  #x6672 #x19A7
          #x6B3E #x1B49  #x6C71 #x1BDA  #x713D #x1D7C  #x7270 #x1E0D
          #x773C #x1FAF)))
       (setf (svref a 132) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x234B #xE6  #x247E #x177  #x294A #x319  #x2A7D #x3AA
          #x2F49 #x54C  #x307C #x5DD  #x3548 #x77F  #x367B #x810
          #x3B47 #x9B2  #x3C7A #xA43  #x4146 #xBE5  #x4279 #xC76
          #x4745 #xE18  #x4878 #xEA9  #x4D44 #x104B  #x4E77 #x10DC
          #x5343 #x127E  #x5476 #x130F  #x5942 #x14B1  #x5A75 #x1542
          #x5F41 #x16E4  #x6074 #x1775  #x6540 #x1917  #x6673 #x19A8
          #x6B3F #x1B4A  #x6C72 #x1BDB  #x713E #x1D7D  #x7271 #x1E0E
          #x773D #x1FB0)))
       (setf (svref a 133) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x234C #xE7  #x294B #x31A  #x2A7E #x3AB  #x2F4A #x54D
          #x307D #x5DE  #x3549 #x780  #x367C #x811  #x3B48 #x9B3
          #x3C7B #xA44  #x4147 #xBE6  #x427A #xC77  #x4746 #xE19
          #x4879 #xEAA  #x4D45 #x104C  #x4E78 #x10DD  #x5344 #x127F
          #x5477 #x1310  #x5943 #x14B2  #x5A76 #x1543  #x5F42 #x16E5
          #x6075 #x1776  #x6541 #x1918  #x6674 #x19A9  #x6B40 #x1B4B
          #x6C73 #x1BDC  #x713F #x1D7E  #x7272 #x1E0F  #x773E #x1FB1)))
       (setf (svref a 134) (make-array 54 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x234D #xE8  #x294C #x31B  #x2F4B #x54E  #x307E #x5DF
          #x354A #x781  #x367D #x812  #x3B49 #x9B4  #x3C7C #xA45
          #x4148 #xBE7  #x427B #xC78  #x4747 #xE1A  #x487A #xEAB
          #x4D46 #x104D  #x4E79 #x10DE  #x5345 #x1280  #x5478 #x1311
          #x5944 #x14B3  #x5A77 #x1544  #x5F43 #x16E6  #x6076 #x1777
          #x6542 #x1919  #x6675 #x19AA  #x6B41 #x1B4C  #x6C74 #x1BDD
          #x7140 #x1D7F  #x7273 #x1E10  #x773F #x1FB2)))
       (setf (svref a 135) (make-array 52 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x234E #xE9  #x294D #x31C  #x2F4C #x54F  #x354B #x782
          #x367E #x813  #x3B4A #x9B5  #x3C7D #xA46  #x4149 #xBE8
          #x427C #xC79  #x4748 #xE1B  #x487B #xEAC  #x4D47 #x104E
          #x4E7A #x10DF  #x5346 #x1281  #x5479 #x1312  #x5945 #x14B4
          #x5A78 #x1545  #x5F44 #x16E7  #x6077 #x1778  #x6543 #x191A
          #x6676 #x19AB  #x6B42 #x1B4D  #x6C75 #x1BDE  #x7141 #x1D80
          #x7274 #x1E11  #x7740 #x1FB3)))
       (setf (svref a 136) (make-array 50 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x234F #xEA  #x294E #x31D  #x2F4D #x550  #x354C #x783
          #x3B4B #x9B6  #x3C7E #xA47  #x414A #xBE9  #x427D #xC7A
          #x4749 #xE1C  #x487C #xEAD  #x4D48 #x104F  #x4E7B #x10E0
          #x5347 #x1282  #x547A #x1313  #x5946 #x14B5  #x5A79 #x1546
          #x5F45 #x16E8  #x6078 #x1779  #x6544 #x191B  #x6677 #x19AC
          #x6B43 #x1B4E  #x6C76 #x1BDF  #x7142 #x1D81  #x7275 #x1E12
          #x7741 #x1FB4)))
       (setf (svref a 137) (make-array 48 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2350 #xEB  #x294F #x31E  #x2F4E #x551  #x354D #x784
          #x3B4C #x9B7  #x414B #xBEA  #x427E #xC7B  #x474A #xE1D
          #x487D #xEAE  #x4D49 #x1050  #x4E7C #x10E1  #x5348 #x1283
          #x547B #x1314  #x5947 #x14B6  #x5A7A #x1547  #x5F46 #x16E9
          #x6079 #x177A  #x6545 #x191C  #x6678 #x19AD  #x6B44 #x1B4F
          #x6C77 #x1BE0  #x7143 #x1D82  #x7276 #x1E13  #x7742 #x1FB5)))
       (setf (svref a 138) (make-array 46 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2351 #xEC  #x2950 #x31F  #x2F4F #x552  #x354E #x785
          #x3B4D #x9B8  #x414C #xBEB  #x474B #xE1E  #x487E #xEAF
          #x4D4A #x1051  #x4E7D #x10E2  #x5349 #x1284  #x547C #x1315
          #x5948 #x14B7  #x5A7B #x1548  #x5F47 #x16EA  #x607A #x177B
          #x6546 #x191D  #x6679 #x19AE  #x6B45 #x1B50  #x6C78 #x1BE1
          #x7144 #x1D83  #x7277 #x1E14  #x7743 #x1FB6)))
       (setf (svref a 139) (make-array 44 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2352 #xED  #x2951 #x320  #x2F50 #x553  #x354F #x786
          #x3B4E #x9B9  #x414D #xBEC  #x474C #xE1F  #x4D4B #x1052
          #x4E7E #x10E3  #x534A #x1285  #x547D #x1316  #x5949 #x14B8
          #x5A7C #x1549  #x5F48 #x16EB  #x607B #x177C  #x6547 #x191E
          #x667A #x19AF  #x6B46 #x1B51  #x6C79 #x1BE2  #x7145 #x1D84
          #x7278 #x1E15  #x7744 #x1FB7)))
       (setf (svref a 140) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2353 #xEE  #x2952 #x321  #x2F51 #x554  #x3550 #x787
          #x3B4F #x9BA  #x414E #xBED  #x474D #xE20  #x4D4C #x1053
          #x534B #x1286  #x547E #x1317  #x594A #x14B9  #x5A7D #x154A
          #x5F49 #x16EC  #x607C #x177D  #x6548 #x191F  #x667B #x19B0
          #x6B47 #x1B52  #x6C7A #x1BE3  #x7146 #x1D85  #x7279 #x1E16
          #x7745 #x1FB8)))
       (setf (svref a 141) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2221 #x5E  #x2354 #xEF  #x2953 #x322  #x2F52 #x555
          #x3551 #x788  #x3B50 #x9BB  #x414F #xBEE  #x474E #xE21
          #x4D4D #x1054  #x534C #x1287  #x594B #x14BA  #x5A7E #x154B
          #x5F4A #x16ED  #x607D #x177E  #x6549 #x1920  #x667C #x19B1
          #x6B48 #x1B53  #x6C7B #x1BE4  #x7147 #x1D86  #x727A #x1E17
          #x7746 #x1FB9)))
       (setf (svref a 142) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2222 #x5F  #x2355 #xF0  #x2821 #x292  #x2954 #x323
          #x2F53 #x556  #x3552 #x789  #x3B51 #x9BC  #x4150 #xBEF
          #x474F #xE22  #x4D4E #x1055  #x534D #x1288  #x594C #x14BB
          #x5F4B #x16EE  #x607E #x177F  #x654A #x1921  #x667D #x19B2
          #x6B49 #x1B54  #x6C7C #x1BE5  #x7148 #x1D87  #x727B #x1E18
          #x7747 #x1FBA)))
       (setf (svref a 143) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2223 #x60  #x2356 #xF1  #x2822 #x293  #x2955 #x324
          #x2E21 #x4C6  #x2F54 #x557  #x3553 #x78A  #x3B52 #x9BD
          #x4151 #xBF0  #x4750 #xE23  #x4D4F #x1056  #x534E #x1289
          #x594D #x14BC  #x5F4C #x16EF  #x654B #x1922  #x667E #x19B3
          #x6B4A #x1B55  #x6C7D #x1BE6  #x7149 #x1D88  #x727C #x1E19
          #x7748 #x1FBB)))
       (setf (svref a 144) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2224 #x61  #x2357 #xF2  #x2823 #x294  #x2956 #x325
          #x2E22 #x4C7  #x2F55 #x558  #x3421 #x6FA  #x3554 #x78B
          #x3B53 #x9BE  #x4152 #xBF1  #x4751 #xE24  #x4D50 #x1057
          #x534F #x128A  #x594E #x14BD  #x5F4D #x16F0  #x654C #x1923
          #x6B4B #x1B56  #x6C7E #x1BE7  #x714A #x1D89  #x727D #x1E1A
          #x7749 #x1FBC)))
       (setf (svref a 145) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2225 #x62  #x2358 #xF3  #x2824 #x295  #x2957 #x326
          #x2E23 #x4C8  #x2F56 #x559  #x3422 #x6FB  #x3555 #x78C
          #x3A21 #x92E  #x3B54 #x9BF  #x4153 #xBF2  #x4752 #xE25
          #x4D51 #x1058  #x5350 #x128B  #x594F #x14BE  #x5F4E #x16F1
          #x654D #x1924  #x6B4C #x1B57  #x714B #x1D8A  #x727E #x1E1B
          #x774A #x1FBD)))
       (setf (svref a 146) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2226 #x63  #x2359 #xF4  #x2825 #x296  #x2958 #x327
          #x2E24 #x4C9  #x2F57 #x55A  #x3423 #x6FC  #x3556 #x78D
          #x3A22 #x92F  #x3B55 #x9C0  #x4021 #xB62  #x4154 #xBF3
          #x4753 #xE26  #x4D52 #x1059  #x5351 #x128C  #x5950 #x14BF
          #x5F4F #x16F2  #x654E #x1925  #x6B4D #x1B58  #x714C #x1D8B
          #x774B #x1FBE)))
       (setf (svref a 147) (make-array 44 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2227 #x64  #x235A #xF5  #x2826 #x297  #x2959 #x328
          #x2E25 #x4CA  #x2F58 #x55B  #x3424 #x6FD  #x3557 #x78E
          #x3A23 #x930  #x3B56 #x9C1  #x4022 #xB63  #x4155 #xBF4
          #x4621 #xD96  #x4754 #xE27  #x4D53 #x105A  #x5352 #x128D
          #x5951 #x14C0  #x5F50 #x16F3  #x654F #x1926  #x6B4E #x1B59
          #x714D #x1D8C  #x774C #x1FBF)))
       (setf (svref a 148) (make-array 46 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2228 #x65  #x235B #xF6  #x2827 #x298  #x295A #x329
          #x2E26 #x4CB  #x2F59 #x55C  #x3425 #x6FE  #x3558 #x78F
          #x3A24 #x931  #x3B57 #x9C2  #x4023 #xB64  #x4156 #xBF5
          #x4622 #xD97  #x4755 #xE28  #x4C21 #xFCA  #x4D54 #x105B
          #x5353 #x128E  #x5952 #x14C1  #x5F51 #x16F4  #x6550 #x1927
          #x6B4F #x1B5A  #x714E #x1D8D  #x774D #x1FC0)))
       (setf (svref a 149) (make-array 48 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2229 #x66  #x235C #xF7  #x2828 #x299  #x295B #x32A
          #x2E27 #x4CC  #x2F5A #x55D  #x3426 #x6FF  #x3559 #x790
          #x3A25 #x932  #x3B58 #x9C3  #x4024 #xB65  #x4157 #xBF6
          #x4623 #xD98  #x4756 #xE29  #x4C22 #xFCB  #x4D55 #x105C
          #x5221 #x11FE  #x5354 #x128F  #x5953 #x14C2  #x5F52 #x16F5
          #x6551 #x1928  #x6B50 #x1B5B  #x714F #x1D8E  #x774E #x1FC1)))
       (setf (svref a 150) (make-array 50 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x222A #x67  #x235D #xF8  #x2829 #x29A  #x295C #x32B
          #x2E28 #x4CD  #x2F5B #x55E  #x3427 #x700  #x355A #x791
          #x3A26 #x933  #x3B59 #x9C4  #x4025 #xB66  #x4158 #xBF7
          #x4624 #xD99  #x4757 #xE2A  #x4C23 #xFCC  #x4D56 #x105D
          #x5222 #x11FF  #x5355 #x1290  #x5821 #x1432  #x5954 #x14C3
          #x5F53 #x16F6  #x6552 #x1929  #x6B51 #x1B5C  #x7150 #x1D8F
          #x774F #x1FC2)))
       (setf (svref a 151) (make-array 52 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x222B #x68  #x235E #xF9  #x282A #x29B  #x295D #x32C
          #x2E29 #x4CE  #x2F5C #x55F  #x3428 #x701  #x355B #x792
          #x3A27 #x934  #x3B5A #x9C5  #x4026 #xB67  #x4159 #xBF8
          #x4625 #xD9A  #x4758 #xE2B  #x4C24 #xFCD  #x4D57 #x105E
          #x5223 #x1200  #x5356 #x1291  #x5822 #x1433  #x5955 #x14C4
          #x5E21 #x1666  #x5F54 #x16F7  #x6553 #x192A  #x6B52 #x1B5D
          #x7151 #x1D90  #x7750 #x1FC3)))
       (setf (svref a 152) (make-array 54 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x222C #x69  #x235F #xFA  #x282B #x29C  #x295E #x32D
          #x2E2A #x4CF  #x2F5D #x560  #x3429 #x702  #x355C #x793
          #x3A28 #x935  #x3B5B #x9C6  #x4027 #xB68  #x415A #xBF9
          #x4626 #xD9B  #x4759 #xE2C  #x4C25 #xFCE  #x4D58 #x105F
          #x5224 #x1201  #x5357 #x1292  #x5823 #x1434  #x5956 #x14C5
          #x5E22 #x1667  #x5F55 #x16F8  #x6421 #x189A  #x6554 #x192B
          #x6B53 #x1B5E  #x7152 #x1D91  #x7751 #x1FC4)))
       (setf (svref a 153) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x222D #x6A  #x2360 #xFB  #x282C #x29D  #x295F #x32E
          #x2E2B #x4D0  #x2F5E #x561  #x342A #x703  #x355D #x794
          #x3A29 #x936  #x3B5C #x9C7  #x4028 #xB69  #x415B #xBFA
          #x4627 #xD9C  #x475A #xE2D  #x4C26 #xFCF  #x4D59 #x1060
          #x5225 #x1202  #x5358 #x1293  #x5824 #x1435  #x5957 #x14C6
          #x5E23 #x1668  #x5F56 #x16F9  #x6422 #x189B  #x6555 #x192C
          #x6A21 #x1ACE  #x6B54 #x1B5F  #x7153 #x1D92  #x7752 #x1FC5)))
       (setf (svref a 154) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x222E #x6B  #x2361 #xFC  #x282D #x29E  #x2960 #x32F
          #x2E2C #x4D1  #x2F5F #x562  #x342B #x704  #x355E #x795
          #x3A2A #x937  #x3B5D #x9C8  #x4029 #xB6A  #x415C #xBFB
          #x4628 #xD9D  #x475B #xE2E  #x4C27 #xFD0  #x4D5A #x1061
          #x5226 #x1203  #x5359 #x1294  #x5825 #x1436  #x5958 #x14C7
          #x5E24 #x1669  #x5F57 #x16FA  #x6423 #x189C  #x6556 #x192D
          #x6A22 #x1ACF  #x6B55 #x1B60  #x7021 #x1D02  #x7154 #x1D93
          #x7753 #x1FC6)))
       (setf (svref a 155) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x222F #x6C  #x2362 #xFD  #x282E #x29F  #x2961 #x330
          #x2E2D #x4D2  #x2F60 #x563  #x342C #x705  #x355F #x796
          #x3A2B #x938  #x3B5E #x9C9  #x402A #xB6B  #x415D #xBFC
          #x4629 #xD9E  #x475C #xE2F  #x4C28 #xFD1  #x4D5B #x1062
          #x5227 #x1204  #x535A #x1295  #x5826 #x1437  #x5959 #x14C8
          #x5E25 #x166A  #x5F58 #x16FB  #x6424 #x189D  #x6557 #x192E
          #x6A23 #x1AD0  #x6B56 #x1B61  #x7022 #x1D03  #x7155 #x1D94
          #x7621 #x1F36  #x7754 #x1FC7)))
       (setf (svref a 156) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2230 #x6D  #x2363 #xFE  #x282F #x2A0  #x2962 #x331
          #x2E2E #x4D3  #x2F61 #x564  #x342D #x706  #x3560 #x797
          #x3A2C #x939  #x3B5F #x9CA  #x402B #xB6C  #x415E #xBFD
          #x462A #xD9F  #x475D #xE30  #x4C29 #xFD2  #x4D5C #x1063
          #x5228 #x1205  #x535B #x1296  #x5827 #x1438  #x595A #x14C9
          #x5E26 #x166B  #x5F59 #x16FC  #x6425 #x189E  #x6558 #x192F
          #x6A24 #x1AD1  #x6B57 #x1B62  #x7023 #x1D04  #x7156 #x1D95
          #x7622 #x1F37  #x7755 #x1FC8)))
       (setf (svref a 157) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2231 #x6E  #x2364 #xFF  #x2830 #x2A1  #x2963 #x332
          #x2E2F #x4D4  #x2F62 #x565  #x342E #x707  #x3561 #x798
          #x3A2D #x93A  #x3B60 #x9CB  #x402C #xB6D  #x415F #xBFE
          #x462B #xDA0  #x475E #xE31  #x4C2A #xFD3  #x4D5D #x1064
          #x5229 #x1206  #x535C #x1297  #x5828 #x1439  #x595B #x14CA
          #x5E27 #x166C  #x5F5A #x16FD  #x6426 #x189F  #x6559 #x1930
          #x6A25 #x1AD2  #x6B58 #x1B63  #x7024 #x1D05  #x7157 #x1D96
          #x7623 #x1F38  #x7756 #x1FC9)))
       (setf (svref a 158) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2232 #x6F  #x2365 #x100  #x2831 #x2A2  #x2964 #x333
          #x2E30 #x4D5  #x2F63 #x566  #x342F #x708  #x3562 #x799
          #x3A2E #x93B  #x3B61 #x9CC  #x402D #xB6E  #x4160 #xBFF
          #x462C #xDA1  #x475F #xE32  #x4C2B #xFD4  #x4D5E #x1065
          #x522A #x1207  #x535D #x1298  #x5829 #x143A  #x595C #x14CB
          #x5E28 #x166D  #x5F5B #x16FE  #x6427 #x18A0  #x655A #x1931
          #x6A26 #x1AD3  #x6B59 #x1B64  #x7025 #x1D06  #x7158 #x1D97
          #x7624 #x1F39  #x7757 #x1FCA)))
       (setf (svref a 159) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2233 #x70  #x2366 #x101  #x2832 #x2A3  #x2965 #x334
          #x2E31 #x4D6  #x2F64 #x567  #x3430 #x709  #x3563 #x79A
          #x3A2F #x93C  #x3B62 #x9CD  #x402E #xB6F  #x4161 #xC00
          #x462D #xDA2  #x4760 #xE33  #x4C2C #xFD5  #x4D5F #x1066
          #x522B #x1208  #x535E #x1299  #x582A #x143B  #x595D #x14CC
          #x5E29 #x166E  #x5F5C #x16FF  #x6428 #x18A1  #x655B #x1932
          #x6A27 #x1AD4  #x6B5A #x1B65  #x7026 #x1D07  #x7159 #x1D98
          #x7625 #x1F3A  #x7758 #x1FCB)))
       (setf (svref a 160) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2234 #x71  #x2367 #x102  #x2833 #x2A4  #x2966 #x335
          #x2E32 #x4D7  #x2F65 #x568  #x3431 #x70A  #x3564 #x79B
          #x3A30 #x93D  #x3B63 #x9CE  #x402F #xB70  #x4162 #xC01
          #x462E #xDA3  #x4761 #xE34  #x4C2D #xFD6  #x4D60 #x1067
          #x522C #x1209  #x535F #x129A  #x582B #x143C  #x595E #x14CD
          #x5E2A #x166F  #x5F5D #x1700  #x6429 #x18A2  #x655C #x1933
          #x6A28 #x1AD5  #x6B5B #x1B66  #x7027 #x1D08  #x715A #x1D99
          #x7626 #x1F3B  #x7759 #x1FCC)))
       (setf (svref a 161) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2235 #x72  #x2368 #x103  #x2834 #x2A5  #x2967 #x336
          #x2E33 #x4D8  #x2F66 #x569  #x3432 #x70B  #x3565 #x79C
          #x3A31 #x93E  #x3B64 #x9CF  #x4030 #xB71  #x4163 #xC02
          #x462F #xDA4  #x4762 #xE35  #x4C2E #xFD7  #x4D61 #x1068
          #x522D #x120A  #x5360 #x129B  #x582C #x143D  #x595F #x14CE
          #x5E2B #x1670  #x5F5E #x1701  #x642A #x18A3  #x655D #x1934
          #x6A29 #x1AD6  #x6B5C #x1B67  #x7028 #x1D09  #x715B #x1D9A
          #x7627 #x1F3C  #x775A #x1FCD)))
       (setf (svref a 162) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2236 #x73  #x2369 #x104  #x2835 #x2A6  #x2968 #x337
          #x2E34 #x4D9  #x2F67 #x56A  #x3433 #x70C  #x3566 #x79D
          #x3A32 #x93F  #x3B65 #x9D0  #x4031 #xB72  #x4164 #xC03
          #x4630 #xDA5  #x4763 #xE36  #x4C2F #xFD8  #x4D62 #x1069
          #x522E #x120B  #x5361 #x129C  #x582D #x143E  #x5960 #x14CF
          #x5E2C #x1671  #x5F5F #x1702  #x642B #x18A4  #x655E #x1935
          #x6A2A #x1AD7  #x6B5D #x1B68  #x7029 #x1D0A  #x715C #x1D9B
          #x7628 #x1F3D  #x775B #x1FCE)))
       (setf (svref a 163) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2237 #x74  #x236A #x105  #x2836 #x2A7  #x2969 #x338
          #x2E35 #x4DA  #x2F68 #x56B  #x3434 #x70D  #x3567 #x79E
          #x3A33 #x940  #x3B66 #x9D1  #x4032 #xB73  #x4165 #xC04
          #x4631 #xDA6  #x4764 #xE37  #x4C30 #xFD9  #x4D63 #x106A
          #x522F #x120C  #x5362 #x129D  #x582E #x143F  #x5961 #x14D0
          #x5E2D #x1672  #x5F60 #x1703  #x642C #x18A5  #x655F #x1936
          #x6A2B #x1AD8  #x6B5E #x1B69  #x702A #x1D0B  #x715D #x1D9C
          #x7629 #x1F3E  #x775C #x1FCF)))
       (setf (svref a 164) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2238 #x75  #x236B #x106  #x2837 #x2A8  #x296A #x339
          #x2E36 #x4DB  #x2F69 #x56C  #x3435 #x70E  #x3568 #x79F
          #x3A34 #x941  #x3B67 #x9D2  #x4033 #xB74  #x4166 #xC05
          #x4632 #xDA7  #x4765 #xE38  #x4C31 #xFDA  #x4D64 #x106B
          #x5230 #x120D  #x5363 #x129E  #x582F #x1440  #x5962 #x14D1
          #x5E2E #x1673  #x5F61 #x1704  #x642D #x18A6  #x6560 #x1937
          #x6A2C #x1AD9  #x6B5F #x1B6A  #x702B #x1D0C  #x715E #x1D9D
          #x762A #x1F3F  #x775D #x1FD0)))
       (setf (svref a 165) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2239 #x76  #x236C #x107  #x2838 #x2A9  #x296B #x33A
          #x2E37 #x4DC  #x2F6A #x56D  #x3436 #x70F  #x3569 #x7A0
          #x3A35 #x942  #x3B68 #x9D3  #x4034 #xB75  #x4167 #xC06
          #x4633 #xDA8  #x4766 #xE39  #x4C32 #xFDB  #x4D65 #x106C
          #x5231 #x120E  #x5364 #x129F  #x5830 #x1441  #x5963 #x14D2
          #x5E2F #x1674  #x5F62 #x1705  #x642E #x18A7  #x6561 #x1938
          #x6A2D #x1ADA  #x6B60 #x1B6B  #x702C #x1D0D  #x715F #x1D9E
          #x762B #x1F40  #x775E #x1FD1)))
       (setf (svref a 166) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x223A #x77  #x236D #x108  #x2839 #x2AA  #x296C #x33B
          #x2E38 #x4DD  #x2F6B #x56E  #x3437 #x710  #x356A #x7A1
          #x3A36 #x943  #x3B69 #x9D4  #x4035 #xB76  #x4168 #xC07
          #x4634 #xDA9  #x4767 #xE3A  #x4C33 #xFDC  #x4D66 #x106D
          #x5232 #x120F  #x5365 #x12A0  #x5831 #x1442  #x5964 #x14D3
          #x5E30 #x1675  #x5F63 #x1706  #x642F #x18A8  #x6562 #x1939
          #x6A2E #x1ADB  #x6B61 #x1B6C  #x702D #x1D0E  #x7160 #x1D9F
          #x762C #x1F41  #x775F #x1FD2)))
       (setf (svref a 167) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x223B #x78  #x236E #x109  #x283A #x2AB  #x296D #x33C
          #x2E39 #x4DE  #x2F6C #x56F  #x3438 #x711  #x356B #x7A2
          #x3A37 #x944  #x3B6A #x9D5  #x4036 #xB77  #x4169 #xC08
          #x4635 #xDAA  #x4768 #xE3B  #x4C34 #xFDD  #x4D67 #x106E
          #x5233 #x1210  #x5366 #x12A1  #x5832 #x1443  #x5965 #x14D4
          #x5E31 #x1676  #x5F64 #x1707  #x6430 #x18A9  #x6563 #x193A
          #x6A2F #x1ADC  #x6B62 #x1B6D  #x702E #x1D0F  #x7161 #x1DA0
          #x762D #x1F42  #x7760 #x1FD3)))
       (setf (svref a 168) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x223C #x79  #x236F #x10A  #x283B #x2AC  #x296E #x33D
          #x2E3A #x4DF  #x2F6D #x570  #x3439 #x712  #x356C #x7A3
          #x3A38 #x945  #x3B6B #x9D6  #x4037 #xB78  #x416A #xC09
          #x4636 #xDAB  #x4769 #xE3C  #x4C35 #xFDE  #x4D68 #x106F
          #x5234 #x1211  #x5367 #x12A2  #x5833 #x1444  #x5966 #x14D5
          #x5E32 #x1677  #x5F65 #x1708  #x6431 #x18AA  #x6564 #x193B
          #x6A30 #x1ADD  #x6B63 #x1B6E  #x702F #x1D10  #x7162 #x1DA1
          #x762E #x1F43  #x7761 #x1FD4)))
       (setf (svref a 169) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x223D #x7A  #x2370 #x10B  #x283C #x2AD  #x296F #x33E
          #x2E3B #x4E0  #x2F6E #x571  #x343A #x713  #x356D #x7A4
          #x3A39 #x946  #x3B6C #x9D7  #x4038 #xB79  #x416B #xC0A
          #x4637 #xDAC  #x476A #xE3D  #x4C36 #xFDF  #x4D69 #x1070
          #x5235 #x1212  #x5368 #x12A3  #x5834 #x1445  #x5967 #x14D6
          #x5E33 #x1678  #x5F66 #x1709  #x6432 #x18AB  #x6565 #x193C
          #x6A31 #x1ADE  #x6B64 #x1B6F  #x7030 #x1D11  #x7163 #x1DA2
          #x762F #x1F44  #x7762 #x1FD5)))
       (setf (svref a 170) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x223E #x7B  #x2371 #x10C  #x283D #x2AE  #x2970 #x33F
          #x2E3C #x4E1  #x2F6F #x572  #x343B #x714  #x356E #x7A5
          #x3A3A #x947  #x3B6D #x9D8  #x4039 #xB7A  #x416C #xC0B
          #x4638 #xDAD  #x476B #xE3E  #x4C37 #xFE0  #x4D6A #x1071
          #x5236 #x1213  #x5369 #x12A4  #x5835 #x1446  #x5968 #x14D7
          #x5E34 #x1679  #x5F67 #x170A  #x6433 #x18AC  #x6566 #x193D
          #x6A32 #x1ADF  #x6B65 #x1B70  #x7031 #x1D12  #x7164 #x1DA3
          #x7630 #x1F45  #x7763 #x1FD6)))
       (setf (svref a 171) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x223F #x7C  #x2372 #x10D  #x283E #x2AF  #x2971 #x340
          #x2E3D #x4E2  #x2F70 #x573  #x343C #x715  #x356F #x7A6
          #x3A3B #x948  #x3B6E #x9D9  #x403A #xB7B  #x416D #xC0C
          #x4639 #xDAE  #x476C #xE3F  #x4C38 #xFE1  #x4D6B #x1072
          #x5237 #x1214  #x536A #x12A5  #x5836 #x1447  #x5969 #x14D8
          #x5E35 #x167A  #x5F68 #x170B  #x6434 #x18AD  #x6567 #x193E
          #x6A33 #x1AE0  #x6B66 #x1B71  #x7032 #x1D13  #x7165 #x1DA4
          #x7631 #x1F46  #x7764 #x1FD7)))
       (setf (svref a 172) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2240 #x7D  #x2373 #x10E  #x283F #x2B0  #x2972 #x341
          #x2E3E #x4E3  #x2F71 #x574  #x343D #x716  #x3570 #x7A7
          #x3A3C #x949  #x3B6F #x9DA  #x403B #xB7C  #x416E #xC0D
          #x463A #xDAF  #x476D #xE40  #x4C39 #xFE2  #x4D6C #x1073
          #x5238 #x1215  #x536B #x12A6  #x5837 #x1448  #x596A #x14D9
          #x5E36 #x167B  #x5F69 #x170C  #x6435 #x18AE  #x6568 #x193F
          #x6A34 #x1AE1  #x6B67 #x1B72  #x7033 #x1D14  #x7166 #x1DA5
          #x7632 #x1F47  #x7765 #x1FD8)))
       (setf (svref a 173) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2241 #x7E  #x2374 #x10F  #x2840 #x2B1  #x2973 #x342
          #x2E3F #x4E4  #x2F72 #x575  #x343E #x717  #x3571 #x7A8
          #x3A3D #x94A  #x3B70 #x9DB  #x403C #xB7D  #x416F #xC0E
          #x463B #xDB0  #x476E #xE41  #x4C3A #xFE3  #x4D6D #x1074
          #x5239 #x1216  #x536C #x12A7  #x5838 #x1449  #x596B #x14DA
          #x5E37 #x167C  #x5F6A #x170D  #x6436 #x18AF  #x6569 #x1940
          #x6A35 #x1AE2  #x6B68 #x1B73  #x7034 #x1D15  #x7167 #x1DA6
          #x7633 #x1F48  #x7766 #x1FD9)))
       (setf (svref a 174) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2242 #x7F  #x2375 #x110  #x2841 #x2B2  #x2974 #x343
          #x2E40 #x4E5  #x2F73 #x576  #x343F #x718  #x3572 #x7A9
          #x3A3E #x94B  #x3B71 #x9DC  #x403D #xB7E  #x4170 #xC0F
          #x463C #xDB1  #x476F #xE42  #x4C3B #xFE4  #x4D6E #x1075
          #x523A #x1217  #x536D #x12A8  #x5839 #x144A  #x596C #x14DB
          #x5E38 #x167D  #x5F6B #x170E  #x6437 #x18B0  #x656A #x1941
          #x6A36 #x1AE3  #x6B69 #x1B74  #x7035 #x1D16  #x7168 #x1DA7
          #x7634 #x1F49  #x7767 #x1FDA)))
       (setf (svref a 175) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2243 #x80  #x2376 #x111  #x2842 #x2B3  #x2975 #x344
          #x2E41 #x4E6  #x2F74 #x577  #x3440 #x719  #x3573 #x7AA
          #x3A3F #x94C  #x3B72 #x9DD  #x403E #xB7F  #x4171 #xC10
          #x463D #xDB2  #x4770 #xE43  #x4C3C #xFE5  #x4D6F #x1076
          #x523B #x1218  #x536E #x12A9  #x583A #x144B  #x596D #x14DC
          #x5E39 #x167E  #x5F6C #x170F  #x6438 #x18B1  #x656B #x1942
          #x6A37 #x1AE4  #x6B6A #x1B75  #x7036 #x1D17  #x7169 #x1DA8
          #x7635 #x1F4A  #x7768 #x1FDB)))
       (setf (svref a 176) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2244 #x81  #x2377 #x112  #x2843 #x2B4  #x2976 #x345
          #x2E42 #x4E7  #x2F75 #x578  #x3441 #x71A  #x3574 #x7AB
          #x3A40 #x94D  #x3B73 #x9DE  #x403F #xB80  #x4172 #xC11
          #x463E #xDB3  #x4771 #xE44  #x4C3D #xFE6  #x4D70 #x1077
          #x523C #x1219  #x536F #x12AA  #x583B #x144C  #x596E #x14DD
          #x5E3A #x167F  #x5F6D #x1710  #x6439 #x18B2  #x656C #x1943
          #x6A38 #x1AE5  #x6B6B #x1B76  #x7037 #x1D18  #x716A #x1DA9
          #x7636 #x1F4B  #x7769 #x1FDC)))
       (setf (svref a 177) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2245 #x82  #x2378 #x113  #x2844 #x2B5  #x2977 #x346
          #x2E43 #x4E8  #x2F76 #x579  #x3442 #x71B  #x3575 #x7AC
          #x3A41 #x94E  #x3B74 #x9DF  #x4040 #xB81  #x4173 #xC12
          #x463F #xDB4  #x4772 #xE45  #x4C3E #xFE7  #x4D71 #x1078
          #x523D #x121A  #x5370 #x12AB  #x583C #x144D  #x596F #x14DE
          #x5E3B #x1680  #x5F6E #x1711  #x643A #x18B3  #x656D #x1944
          #x6A39 #x1AE6  #x6B6C #x1B77  #x7038 #x1D19  #x716B #x1DAA
          #x7637 #x1F4C  #x776A #x1FDD)))
       (setf (svref a 178) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2246 #x83  #x2379 #x114  #x2845 #x2B6  #x2978 #x347
          #x2E44 #x4E9  #x2F77 #x57A  #x3443 #x71C  #x3576 #x7AD
          #x3A42 #x94F  #x3B75 #x9E0  #x4041 #xB82  #x4174 #xC13
          #x4640 #xDB5  #x4773 #xE46  #x4C3F #xFE8  #x4D72 #x1079
          #x523E #x121B  #x5371 #x12AC  #x583D #x144E  #x5970 #x14DF
          #x5E3C #x1681  #x5F6F #x1712  #x643B #x18B4  #x656E #x1945
          #x6A3A #x1AE7  #x6B6D #x1B78  #x7039 #x1D1A  #x716C #x1DAB
          #x7638 #x1F4D  #x776B #x1FDE)))
       (setf (svref a 179) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2247 #x84  #x237A #x115  #x2846 #x2B7  #x2979 #x348
          #x2E45 #x4EA  #x2F78 #x57B  #x3444 #x71D  #x3577 #x7AE
          #x3A43 #x950  #x3B76 #x9E1  #x4042 #xB83  #x4175 #xC14
          #x4641 #xDB6  #x4774 #xE47  #x4C40 #xFE9  #x4D73 #x107A
          #x523F #x121C  #x5372 #x12AD  #x583E #x144F  #x5971 #x14E0
          #x5E3D #x1682  #x5F70 #x1713  #x643C #x18B5  #x656F #x1946
          #x6A3B #x1AE8  #x6B6E #x1B79  #x703A #x1D1B  #x716D #x1DAC
          #x7639 #x1F4E  #x776C #x1FDF)))
       (setf (svref a 180) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2248 #x85  #x237B #x116  #x2847 #x2B8  #x297A #x349
          #x2E46 #x4EB  #x2F79 #x57C  #x3445 #x71E  #x3578 #x7AF
          #x3A44 #x951  #x3B77 #x9E2  #x4043 #xB84  #x4176 #xC15
          #x4642 #xDB7  #x4775 #xE48  #x4C41 #xFEA  #x4D74 #x107B
          #x5240 #x121D  #x5373 #x12AE  #x583F #x1450  #x5972 #x14E1
          #x5E3E #x1683  #x5F71 #x1714  #x643D #x18B6  #x6570 #x1947
          #x6A3C #x1AE9  #x6B6F #x1B7A  #x703B #x1D1C  #x716E #x1DAD
          #x763A #x1F4F  #x776D #x1FE0)))
       (setf (svref a 181) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2249 #x86  #x237C #x117  #x2848 #x2B9  #x297B #x34A
          #x2E47 #x4EC  #x2F7A #x57D  #x3446 #x71F  #x3579 #x7B0
          #x3A45 #x952  #x3B78 #x9E3  #x4044 #xB85  #x4177 #xC16
          #x4643 #xDB8  #x4776 #xE49  #x4C42 #xFEB  #x4D75 #x107C
          #x5241 #x121E  #x5374 #x12AF  #x5840 #x1451  #x5973 #x14E2
          #x5E3F #x1684  #x5F72 #x1715  #x643E #x18B7  #x6571 #x1948
          #x6A3D #x1AEA  #x6B70 #x1B7B  #x703C #x1D1D  #x716F #x1DAE
          #x763B #x1F50  #x776E #x1FE1)))
       (setf (svref a 182) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x224A #x87  #x237D #x118  #x2849 #x2BA  #x297C #x34B
          #x2E48 #x4ED  #x2F7B #x57E  #x3447 #x720  #x357A #x7B1
          #x3A46 #x953  #x3B79 #x9E4  #x4045 #xB86  #x4178 #xC17
          #x4644 #xDB9  #x4777 #xE4A  #x4C43 #xFEC  #x4D76 #x107D
          #x5242 #x121F  #x5375 #x12B0  #x5841 #x1452  #x5974 #x14E3
          #x5E40 #x1685  #x5F73 #x1716  #x643F #x18B8  #x6572 #x1949
          #x6A3E #x1AEB  #x6B71 #x1B7C  #x703D #x1D1E  #x7170 #x1DAF
          #x763C #x1F51  #x776F #x1FE2)))
       (setf (svref a 183) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x224B #x88  #x237E #x119  #x284A #x2BB  #x297D #x34C
          #x2E49 #x4EE  #x2F7C #x57F  #x3448 #x721  #x357B #x7B2
          #x3A47 #x954  #x3B7A #x9E5  #x4046 #xB87  #x4179 #xC18
          #x4645 #xDBA  #x4778 #xE4B  #x4C44 #xFED  #x4D77 #x107E
          #x5243 #x1220  #x5376 #x12B1  #x5842 #x1453  #x5975 #x14E4
          #x5E41 #x1686  #x5F74 #x1717  #x6440 #x18B9  #x6573 #x194A
          #x6A3F #x1AEC  #x6B72 #x1B7D  #x703E #x1D1F  #x7171 #x1DB0
          #x763D #x1F52  #x7770 #x1FE3)))
       (setf (svref a 184) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x224C #x89  #x284B #x2BC  #x297E #x34D  #x2E4A #x4EF
          #x2F7D #x580  #x3449 #x722  #x357C #x7B3  #x3A48 #x955
          #x3B7B #x9E6  #x4047 #xB88  #x417A #xC19  #x4646 #xDBB
          #x4779 #xE4C  #x4C45 #xFEE  #x4D78 #x107F  #x5244 #x1221
          #x5377 #x12B2  #x5843 #x1454  #x5976 #x14E5  #x5E42 #x1687
          #x5F75 #x1718  #x6441 #x18BA  #x6574 #x194B  #x6A40 #x1AED
          #x6B73 #x1B7E  #x703F #x1D20  #x7172 #x1DB1  #x763E #x1F53
          #x7771 #x1FE4)))
       (setf (svref a 185) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x224D #x8A  #x284C #x2BD  #x2E4B #x4F0  #x2F7E #x581
          #x344A #x723  #x357D #x7B4  #x3A49 #x956  #x3B7C #x9E7
          #x4048 #xB89  #x417B #xC1A  #x4647 #xDBC  #x477A #xE4D
          #x4C46 #xFEF  #x4D79 #x1080  #x5245 #x1222  #x5378 #x12B3
          #x5844 #x1455  #x5977 #x14E6  #x5E43 #x1688  #x5F76 #x1719
          #x6442 #x18BB  #x6575 #x194C  #x6A41 #x1AEE  #x6B74 #x1B7F
          #x7040 #x1D21  #x7173 #x1DB2  #x763F #x1F54  #x7772 #x1FE5)))
       (setf (svref a 186) (make-array 54 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x224E #x8B  #x284D #x2BE  #x2E4C #x4F1  #x344B #x724
          #x357E #x7B5  #x3A4A #x957  #x3B7D #x9E8  #x4049 #xB8A
          #x417C #xC1B  #x4648 #xDBD  #x477B #xE4E  #x4C47 #xFF0
          #x4D7A #x1081  #x5246 #x1223  #x5379 #x12B4  #x5845 #x1456
          #x5978 #x14E7  #x5E44 #x1689  #x5F77 #x171A  #x6443 #x18BC
          #x6576 #x194D  #x6A42 #x1AEF  #x6B75 #x1B80  #x7041 #x1D22
          #x7174 #x1DB3  #x7640 #x1F55  #x7773 #x1FE6)))
       (setf (svref a 187) (make-array 52 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x224F #x8C  #x284E #x2BF  #x2E4D #x4F2  #x344C #x725
          #x3A4B #x958  #x3B7E #x9E9  #x404A #xB8B  #x417D #xC1C
          #x4649 #xDBE  #x477C #xE4F  #x4C48 #xFF1  #x4D7B #x1082
          #x5247 #x1224  #x537A #x12B5  #x5846 #x1457  #x5979 #x14E8
          #x5E45 #x168A  #x5F78 #x171B  #x6444 #x18BD  #x6577 #x194E
          #x6A43 #x1AF0  #x6B76 #x1B81  #x7042 #x1D23  #x7175 #x1DB4
          #x7641 #x1F56  #x7774 #x1FE7)))
       (setf (svref a 188) (make-array 50 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2250 #x8D  #x284F #x2C0  #x2E4E #x4F3  #x344D #x726
          #x3A4C #x959  #x404B #xB8C  #x417E #xC1D  #x464A #xDBF
          #x477D #xE50  #x4C49 #xFF2  #x4D7C #x1083  #x5248 #x1225
          #x537B #x12B6  #x5847 #x1458  #x597A #x14E9  #x5E46 #x168B
          #x5F79 #x171C  #x6445 #x18BE  #x6578 #x194F  #x6A44 #x1AF1
          #x6B77 #x1B82  #x7043 #x1D24  #x7176 #x1DB5  #x7642 #x1F57
          #x7775 #x1FE8)))
       (setf (svref a 189) (make-array 48 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2251 #x8E  #x2850 #x2C1  #x2E4F #x4F4  #x344E #x727
          #x3A4D #x95A  #x404C #xB8D  #x464B #xDC0  #x477E #xE51
          #x4C4A #xFF3  #x4D7D #x1084  #x5249 #x1226  #x537C #x12B7
          #x5848 #x1459  #x597B #x14EA  #x5E47 #x168C  #x5F7A #x171D
          #x6446 #x18BF  #x6579 #x1950  #x6A45 #x1AF2  #x6B78 #x1B83
          #x7044 #x1D25  #x7177 #x1DB6  #x7643 #x1F58  #x7776 #x1FE9)))
       (setf (svref a 190) (make-array 46 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2252 #x8F  #x2851 #x2C2  #x2E50 #x4F5  #x344F #x728
          #x3A4E #x95B  #x404D #xB8E  #x464C #xDC1  #x4C4B #xFF4
          #x4D7E #x1085  #x524A #x1227  #x537D #x12B8  #x5849 #x145A
          #x597C #x14EB  #x5E48 #x168D  #x5F7B #x171E  #x6447 #x18C0
          #x657A #x1951  #x6A46 #x1AF3  #x6B79 #x1B84  #x7045 #x1D26
          #x7178 #x1DB7  #x7644 #x1F59  #x7777 #x1FEA)))
       (setf (svref a 191) (make-array 44 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2253 #x90  #x2852 #x2C3  #x2E51 #x4F6  #x3450 #x729
          #x3A4F #x95C  #x404E #xB8F  #x464D #xDC2  #x4C4C #xFF5
          #x524B #x1228  #x537E #x12B9  #x584A #x145B  #x597D #x14EC
          #x5E49 #x168E  #x5F7C #x171F  #x6448 #x18C1  #x657B #x1952
          #x6A47 #x1AF4  #x6B7A #x1B85  #x7046 #x1D27  #x7179 #x1DB8
          #x7645 #x1F5A  #x7778 #x1FEB)))
       (setf (svref a 192) (make-array 44 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2121 #x0  #x2254 #x91  #x2853 #x2C4  #x2E52 #x4F7
          #x3451 #x72A  #x3A50 #x95D  #x404F #xB90  #x464E #xDC3
          #x4C4D #xFF6  #x524C #x1229  #x584B #x145C  #x597E #x14ED
          #x5E4A #x168F  #x5F7D #x1720  #x6449 #x18C2  #x657C #x1953
          #x6A48 #x1AF5  #x6B7B #x1B86  #x7047 #x1D28  #x717A #x1DB9
          #x7646 #x1F5B  #x7779 #x1FEC)))
       (setf (svref a 193) (make-array 44 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2122 #x1  #x2255 #x92  #x2721 #x234  #x2854 #x2C5
          #x2E53 #x4F8  #x3452 #x72B  #x3A51 #x95E  #x4050 #xB91
          #x464F #xDC4  #x4C4E #xFF7  #x524D #x122A  #x584C #x145D
          #x5E4B #x1690  #x5F7E #x1721  #x644A #x18C3  #x657D #x1954
          #x6A49 #x1AF6  #x6B7C #x1B87  #x7048 #x1D29  #x717B #x1DBA
          #x7647 #x1F5C  #x777A #x1FED)))
       (setf (svref a 194) (make-array 44 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2123 #x2  #x2256 #x93  #x2722 #x235  #x2855 #x2C6
          #x2D21 #x468  #x2E54 #x4F9  #x3453 #x72C  #x3A52 #x95F
          #x4051 #xB92  #x4650 #xDC5  #x4C4F #xFF8  #x524E #x122B
          #x584D #x145E  #x5E4C #x1691  #x644B #x18C4  #x657E #x1955
          #x6A4A #x1AF7  #x6B7D #x1B88  #x7049 #x1D2A  #x717C #x1DBB
          #x7648 #x1F5D  #x777B #x1FEE)))
       (setf (svref a 195) (make-array 44 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2124 #x3  #x2257 #x94  #x2723 #x236  #x2856 #x2C7
          #x2D22 #x469  #x2E55 #x4FA  #x3321 #x69C  #x3454 #x72D
          #x3A53 #x960  #x4052 #xB93  #x4651 #xDC6  #x4C50 #xFF9
          #x524F #x122C  #x584E #x145F  #x5E4D #x1692  #x644C #x18C5
          #x6A4B #x1AF8  #x6B7E #x1B89  #x704A #x1D2B  #x717D #x1DBC
          #x7649 #x1F5E  #x777C #x1FEF)))
       (setf (svref a 196) (make-array 44 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2125 #x4  #x2258 #x95  #x2724 #x237  #x2857 #x2C8
          #x2D23 #x46A  #x2E56 #x4FB  #x3322 #x69D  #x3455 #x72E
          #x3921 #x8D0  #x3A54 #x961  #x4053 #xB94  #x4652 #xDC7
          #x4C51 #xFFA  #x5250 #x122D  #x584F #x1460  #x5E4E #x1693
          #x644D #x18C6  #x6A4C #x1AF9  #x704B #x1D2C  #x717E #x1DBD
          #x764A #x1F5F  #x777D #x1FF0)))
       (setf (svref a 197) (make-array 44 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2126 #x5  #x2259 #x96  #x2725 #x238  #x2858 #x2C9
          #x2D24 #x46B  #x2E57 #x4FC  #x3323 #x69E  #x3456 #x72F
          #x3922 #x8D1  #x3A55 #x962  #x3F21 #xB04  #x4054 #xB95
          #x4653 #xDC8  #x4C52 #xFFB  #x5251 #x122E  #x5850 #x1461
          #x5E4F #x1694  #x644E #x18C7  #x6A4D #x1AFA  #x704C #x1D2D
          #x764B #x1F60  #x777E #x1FF1)))
       (setf (svref a 198) (make-array 44 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2127 #x6  #x225A #x97  #x2726 #x239  #x2859 #x2CA
          #x2D25 #x46C  #x2E58 #x4FD  #x3324 #x69F  #x3457 #x730
          #x3923 #x8D2  #x3A56 #x963  #x3F22 #xB05  #x4055 #xB96
          #x4521 #xD38  #x4654 #xDC9  #x4C53 #xFFC  #x5252 #x122F
          #x5851 #x1462  #x5E50 #x1695  #x644F #x18C8  #x6A4E #x1AFB
          #x704D #x1D2E  #x764C #x1F61)))
       (setf (svref a 199) (make-array 46 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2128 #x7  #x225B #x98  #x2727 #x23A  #x285A #x2CB
          #x2D26 #x46D  #x2E59 #x4FE  #x3325 #x6A0  #x3458 #x731
          #x3924 #x8D3  #x3A57 #x964  #x3F23 #xB06  #x4056 #xB97
          #x4522 #xD39  #x4655 #xDCA  #x4B21 #xF6C  #x4C54 #xFFD
          #x5253 #x1230  #x5852 #x1463  #x5E51 #x1696  #x6450 #x18C9
          #x6A4F #x1AFC  #x704E #x1D2F  #x764D #x1F62)))
       (setf (svref a 200) (make-array 48 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2129 #x8  #x225C #x99  #x2728 #x23B  #x285B #x2CC
          #x2D27 #x46E  #x2E5A #x4FF  #x3326 #x6A1  #x3459 #x732
          #x3925 #x8D4  #x3A58 #x965  #x3F24 #xB07  #x4057 #xB98
          #x4523 #xD3A  #x4656 #xDCB  #x4B22 #xF6D  #x4C55 #xFFE
          #x5121 #x11A0  #x5254 #x1231  #x5853 #x1464  #x5E52 #x1697
          #x6451 #x18CA  #x6A50 #x1AFD  #x704F #x1D30  #x764E #x1F63)))
       (setf (svref a 201) (make-array 50 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x212A #x9  #x225D #x9A  #x2729 #x23C  #x285C #x2CD
          #x2D28 #x46F  #x2E5B #x500  #x3327 #x6A2  #x345A #x733
          #x3926 #x8D5  #x3A59 #x966  #x3F25 #xB08  #x4058 #xB99
          #x4524 #xD3B  #x4657 #xDCC  #x4B23 #xF6E  #x4C56 #xFFF
          #x5122 #x11A1  #x5255 #x1232  #x5721 #x13D4  #x5854 #x1465
          #x5E53 #x1698  #x6452 #x18CB  #x6A51 #x1AFE  #x7050 #x1D31
          #x764F #x1F64)))
       (setf (svref a 202) (make-array 52 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x212B #xA  #x225E #x9B  #x272A #x23D  #x285D #x2CE
          #x2D29 #x470  #x2E5C #x501  #x3328 #x6A3  #x345B #x734
          #x3927 #x8D6  #x3A5A #x967  #x3F26 #xB09  #x4059 #xB9A
          #x4525 #xD3C  #x4658 #xDCD  #x4B24 #xF6F  #x4C57 #x1000
          #x5123 #x11A2  #x5256 #x1233  #x5722 #x13D5  #x5855 #x1466
          #x5D21 #x1608  #x5E54 #x1699  #x6453 #x18CC  #x6A52 #x1AFF
          #x7051 #x1D32  #x7650 #x1F65)))
       (setf (svref a 203) (make-array 54 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x212C #xB  #x225F #x9C  #x272B #x23E  #x285E #x2CF
          #x2D2A #x471  #x2E5D #x502  #x3329 #x6A4  #x345C #x735
          #x3928 #x8D7  #x3A5B #x968  #x3F27 #xB0A  #x405A #xB9B
          #x4526 #xD3D  #x4659 #xDCE  #x4B25 #xF70  #x4C58 #x1001
          #x5124 #x11A3  #x5257 #x1234  #x5723 #x13D6  #x5856 #x1467
          #x5D22 #x1609  #x5E55 #x169A  #x6321 #x183C  #x6454 #x18CD
          #x6A53 #x1B00  #x7052 #x1D33  #x7651 #x1F66)))
       (setf (svref a 204) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x212D #xC  #x2260 #x9D  #x272C #x23F  #x285F #x2D0
          #x2D2B #x472  #x2E5E #x503  #x332A #x6A5  #x345D #x736
          #x3929 #x8D8  #x3A5C #x969  #x3F28 #xB0B  #x405B #xB9C
          #x4527 #xD3E  #x465A #xDCF  #x4B26 #xF71  #x4C59 #x1002
          #x5125 #x11A4  #x5258 #x1235  #x5724 #x13D7  #x5857 #x1468
          #x5D23 #x160A  #x5E56 #x169B  #x6322 #x183D  #x6455 #x18CE
          #x6921 #x1A70  #x6A54 #x1B01  #x7053 #x1D34  #x7652 #x1F67)))
       (setf (svref a 205) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x212E #xD  #x2261 #x9E  #x272D #x240  #x2860 #x2D1
          #x2D2C #x473  #x2E5F #x504  #x332B #x6A6  #x345E #x737
          #x392A #x8D9  #x3A5D #x96A  #x3F29 #xB0C  #x405C #xB9D
          #x4528 #xD3F  #x465B #xDD0  #x4B27 #xF72  #x4C5A #x1003
          #x5126 #x11A5  #x5259 #x1236  #x5725 #x13D8  #x5858 #x1469
          #x5D24 #x160B  #x5E57 #x169C  #x6323 #x183E  #x6456 #x18CF
          #x6922 #x1A71  #x6A55 #x1B02  #x6F21 #x1CA4  #x7054 #x1D35
          #x7653 #x1F68)))
       (setf (svref a 206) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x212F #xE  #x2262 #x9F  #x272E #x241  #x2861 #x2D2
          #x2D2D #x474  #x2E60 #x505  #x332C #x6A7  #x345F #x738
          #x392B #x8DA  #x3A5E #x96B  #x3F2A #xB0D  #x405D #xB9E
          #x4529 #xD40  #x465C #xDD1  #x4B28 #xF73  #x4C5B #x1004
          #x5127 #x11A6  #x525A #x1237  #x5726 #x13D9  #x5859 #x146A
          #x5D25 #x160C  #x5E58 #x169D  #x6324 #x183F  #x6457 #x18D0
          #x6923 #x1A72  #x6A56 #x1B03  #x6F22 #x1CA5  #x7055 #x1D36
          #x7521 #x1ED8  #x7654 #x1F69)))
       (setf (svref a 207) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2130 #xF  #x2263 #xA0  #x272F #x242  #x2862 #x2D3
          #x2D2E #x475  #x2E61 #x506  #x332D #x6A8  #x3460 #x739
          #x392C #x8DB  #x3A5F #x96C  #x3F2B #xB0E  #x405E #xB9F
          #x452A #xD41  #x465D #xDD2  #x4B29 #xF74  #x4C5C #x1005
          #x5128 #x11A7  #x525B #x1238  #x5727 #x13DA  #x585A #x146B
          #x5D26 #x160D  #x5E59 #x169E  #x6325 #x1840  #x6458 #x18D1
          #x6924 #x1A73  #x6A57 #x1B04  #x6F23 #x1CA6  #x7056 #x1D37
          #x7522 #x1ED9  #x7655 #x1F6A)))
       (setf (svref a 208) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2131 #x10  #x2264 #xA1  #x2730 #x243  #x2863 #x2D4
          #x2D2F #x476  #x2E62 #x507  #x332E #x6A9  #x3461 #x73A
          #x392D #x8DC  #x3A60 #x96D  #x3F2C #xB0F  #x405F #xBA0
          #x452B #xD42  #x465E #xDD3  #x4B2A #xF75  #x4C5D #x1006
          #x5129 #x11A8  #x525C #x1239  #x5728 #x13DB  #x585B #x146C
          #x5D27 #x160E  #x5E5A #x169F  #x6326 #x1841  #x6459 #x18D2
          #x6925 #x1A74  #x6A58 #x1B05  #x6F24 #x1CA7  #x7057 #x1D38
          #x7523 #x1EDA  #x7656 #x1F6B)))
       (setf (svref a 209) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2132 #x11  #x2265 #xA2  #x2731 #x244  #x2864 #x2D5
          #x2D30 #x477  #x2E63 #x508  #x332F #x6AA  #x3462 #x73B
          #x392E #x8DD  #x3A61 #x96E  #x3F2D #xB10  #x4060 #xBA1
          #x452C #xD43  #x465F #xDD4  #x4B2B #xF76  #x4C5E #x1007
          #x512A #x11A9  #x525D #x123A  #x5729 #x13DC  #x585C #x146D
          #x5D28 #x160F  #x5E5B #x16A0  #x6327 #x1842  #x645A #x18D3
          #x6926 #x1A75  #x6A59 #x1B06  #x6F25 #x1CA8  #x7058 #x1D39
          #x7524 #x1EDB  #x7657 #x1F6C)))
       (setf (svref a 210) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2133 #x12  #x2266 #xA3  #x2732 #x245  #x2865 #x2D6
          #x2D31 #x478  #x2E64 #x509  #x3330 #x6AB  #x3463 #x73C
          #x392F #x8DE  #x3A62 #x96F  #x3F2E #xB11  #x4061 #xBA2
          #x452D #xD44  #x4660 #xDD5  #x4B2C #xF77  #x4C5F #x1008
          #x512B #x11AA  #x525E #x123B  #x572A #x13DD  #x585D #x146E
          #x5D29 #x1610  #x5E5C #x16A1  #x6328 #x1843  #x645B #x18D4
          #x6927 #x1A76  #x6A5A #x1B07  #x6F26 #x1CA9  #x7059 #x1D3A
          #x7525 #x1EDC  #x7658 #x1F6D)))
       (setf (svref a 211) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2134 #x13  #x2267 #xA4  #x2733 #x246  #x2866 #x2D7
          #x2D32 #x479  #x2E65 #x50A  #x3331 #x6AC  #x3464 #x73D
          #x3930 #x8DF  #x3A63 #x970  #x3F2F #xB12  #x4062 #xBA3
          #x452E #xD45  #x4661 #xDD6  #x4B2D #xF78  #x4C60 #x1009
          #x512C #x11AB  #x525F #x123C  #x572B #x13DE  #x585E #x146F
          #x5D2A #x1611  #x5E5D #x16A2  #x6329 #x1844  #x645C #x18D5
          #x6928 #x1A77  #x6A5B #x1B08  #x6F27 #x1CAA  #x705A #x1D3B
          #x7526 #x1EDD  #x7659 #x1F6E)))
       (setf (svref a 212) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2135 #x14  #x2268 #xA5  #x2734 #x247  #x2867 #x2D8
          #x2D33 #x47A  #x2E66 #x50B  #x3332 #x6AD  #x3465 #x73E
          #x3931 #x8E0  #x3A64 #x971  #x3F30 #xB13  #x4063 #xBA4
          #x452F #xD46  #x4662 #xDD7  #x4B2E #xF79  #x4C61 #x100A
          #x512D #x11AC  #x5260 #x123D  #x572C #x13DF  #x585F #x1470
          #x5D2B #x1612  #x5E5E #x16A3  #x632A #x1845  #x645D #x18D6
          #x6929 #x1A78  #x6A5C #x1B09  #x6F28 #x1CAB  #x705B #x1D3C
          #x7527 #x1EDE  #x765A #x1F6F)))
       (setf (svref a 213) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2136 #x15  #x2269 #xA6  #x2735 #x248  #x2868 #x2D9
          #x2D34 #x47B  #x2E67 #x50C  #x3333 #x6AE  #x3466 #x73F
          #x3932 #x8E1  #x3A65 #x972  #x3F31 #xB14  #x4064 #xBA5
          #x4530 #xD47  #x4663 #xDD8  #x4B2F #xF7A  #x4C62 #x100B
          #x512E #x11AD  #x5261 #x123E  #x572D #x13E0  #x5860 #x1471
          #x5D2C #x1613  #x5E5F #x16A4  #x632B #x1846  #x645E #x18D7
          #x692A #x1A79  #x6A5D #x1B0A  #x6F29 #x1CAC  #x705C #x1D3D
          #x7528 #x1EDF  #x765B #x1F70)))
       (setf (svref a 214) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2137 #x16  #x226A #xA7  #x2736 #x249  #x2869 #x2DA
          #x2D35 #x47C  #x2E68 #x50D  #x3334 #x6AF  #x3467 #x740
          #x3933 #x8E2  #x3A66 #x973  #x3F32 #xB15  #x4065 #xBA6
          #x4531 #xD48  #x4664 #xDD9  #x4B30 #xF7B  #x4C63 #x100C
          #x512F #x11AE  #x5262 #x123F  #x572E #x13E1  #x5861 #x1472
          #x5D2D #x1614  #x5E60 #x16A5  #x632C #x1847  #x645F #x18D8
          #x692B #x1A7A  #x6A5E #x1B0B  #x6F2A #x1CAD  #x705D #x1D3E
          #x7529 #x1EE0  #x765C #x1F71)))
       (setf (svref a 215) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2138 #x17  #x226B #xA8  #x2737 #x24A  #x286A #x2DB
          #x2D36 #x47D  #x2E69 #x50E  #x3335 #x6B0  #x3468 #x741
          #x3934 #x8E3  #x3A67 #x974  #x3F33 #xB16  #x4066 #xBA7
          #x4532 #xD49  #x4665 #xDDA  #x4B31 #xF7C  #x4C64 #x100D
          #x5130 #x11AF  #x5263 #x1240  #x572F #x13E2  #x5862 #x1473
          #x5D2E #x1615  #x5E61 #x16A6  #x632D #x1848  #x6460 #x18D9
          #x692C #x1A7B  #x6A5F #x1B0C  #x6F2B #x1CAE  #x705E #x1D3F
          #x752A #x1EE1  #x765D #x1F72)))
       (setf (svref a 216) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2139 #x18  #x226C #xA9  #x2738 #x24B  #x286B #x2DC
          #x2D37 #x47E  #x2E6A #x50F  #x3336 #x6B1  #x3469 #x742
          #x3935 #x8E4  #x3A68 #x975  #x3F34 #xB17  #x4067 #xBA8
          #x4533 #xD4A  #x4666 #xDDB  #x4B32 #xF7D  #x4C65 #x100E
          #x5131 #x11B0  #x5264 #x1241  #x5730 #x13E3  #x5863 #x1474
          #x5D2F #x1616  #x5E62 #x16A7  #x632E #x1849  #x6461 #x18DA
          #x692D #x1A7C  #x6A60 #x1B0D  #x6F2C #x1CAF  #x705F #x1D40
          #x752B #x1EE2  #x765E #x1F73)))
       (setf (svref a 217) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x213A #x19  #x226D #xAA  #x2739 #x24C  #x286C #x2DD
          #x2D38 #x47F  #x2E6B #x510  #x3337 #x6B2  #x346A #x743
          #x3936 #x8E5  #x3A69 #x976  #x3F35 #xB18  #x4068 #xBA9
          #x4534 #xD4B  #x4667 #xDDC  #x4B33 #xF7E  #x4C66 #x100F
          #x5132 #x11B1  #x5265 #x1242  #x5731 #x13E4  #x5864 #x1475
          #x5D30 #x1617  #x5E63 #x16A8  #x632F #x184A  #x6462 #x18DB
          #x692E #x1A7D  #x6A61 #x1B0E  #x6F2D #x1CB0  #x7060 #x1D41
          #x752C #x1EE3  #x765F #x1F74)))
       (setf (svref a 218) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x213B #x1A  #x226E #xAB  #x273A #x24D  #x286D #x2DE
          #x2D39 #x480  #x2E6C #x511  #x3338 #x6B3  #x346B #x744
          #x3937 #x8E6  #x3A6A #x977  #x3F36 #xB19  #x4069 #xBAA
          #x4535 #xD4C  #x4668 #xDDD  #x4B34 #xF7F  #x4C67 #x1010
          #x5133 #x11B2  #x5266 #x1243  #x5732 #x13E5  #x5865 #x1476
          #x5D31 #x1618  #x5E64 #x16A9  #x6330 #x184B  #x6463 #x18DC
          #x692F #x1A7E  #x6A62 #x1B0F  #x6F2E #x1CB1  #x7061 #x1D42
          #x752D #x1EE4  #x7660 #x1F75)))
       (setf (svref a 219) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x213C #x1B  #x226F #xAC  #x273B #x24E  #x286E #x2DF
          #x2D3A #x481  #x2E6D #x512  #x3339 #x6B4  #x346C #x745
          #x3938 #x8E7  #x3A6B #x978  #x3F37 #xB1A  #x406A #xBAB
          #x4536 #xD4D  #x4669 #xDDE  #x4B35 #xF80  #x4C68 #x1011
          #x5134 #x11B3  #x5267 #x1244  #x5733 #x13E6  #x5866 #x1477
          #x5D32 #x1619  #x5E65 #x16AA  #x6331 #x184C  #x6464 #x18DD
          #x6930 #x1A7F  #x6A63 #x1B10  #x6F2F #x1CB2  #x7062 #x1D43
          #x752E #x1EE5  #x7661 #x1F76)))
       (setf (svref a 220) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x213D #x1C  #x2270 #xAD  #x273C #x24F  #x286F #x2E0
          #x2D3B #x482  #x2E6E #x513  #x333A #x6B5  #x346D #x746
          #x3939 #x8E8  #x3A6C #x979  #x3F38 #xB1B  #x406B #xBAC
          #x4537 #xD4E  #x466A #xDDF  #x4B36 #xF81  #x4C69 #x1012
          #x5135 #x11B4  #x5268 #x1245  #x5734 #x13E7  #x5867 #x1478
          #x5D33 #x161A  #x5E66 #x16AB  #x6332 #x184D  #x6465 #x18DE
          #x6931 #x1A80  #x6A64 #x1B11  #x6F30 #x1CB3  #x7063 #x1D44
          #x752F #x1EE6  #x7662 #x1F77)))
       (setf (svref a 221) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x213E #x1D  #x2271 #xAE  #x273D #x250  #x2870 #x2E1
          #x2D3C #x483  #x2E6F #x514  #x333B #x6B6  #x346E #x747
          #x393A #x8E9  #x3A6D #x97A  #x3F39 #xB1C  #x406C #xBAD
          #x4538 #xD4F  #x466B #xDE0  #x4B37 #xF82  #x4C6A #x1013
          #x5136 #x11B5  #x5269 #x1246  #x5735 #x13E8  #x5868 #x1479
          #x5D34 #x161B  #x5E67 #x16AC  #x6333 #x184E  #x6466 #x18DF
          #x6932 #x1A81  #x6A65 #x1B12  #x6F31 #x1CB4  #x7064 #x1D45
          #x7530 #x1EE7  #x7663 #x1F78)))
       (setf (svref a 222) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x213F #x1E  #x2272 #xAF  #x273E #x251  #x2871 #x2E2
          #x2D3D #x484  #x2E70 #x515  #x333C #x6B7  #x346F #x748
          #x393B #x8EA  #x3A6E #x97B  #x3F3A #xB1D  #x406D #xBAE
          #x4539 #xD50  #x466C #xDE1  #x4B38 #xF83  #x4C6B #x1014
          #x5137 #x11B6  #x526A #x1247  #x5736 #x13E9  #x5869 #x147A
          #x5D35 #x161C  #x5E68 #x16AD  #x6334 #x184F  #x6467 #x18E0
          #x6933 #x1A82  #x6A66 #x1B13  #x6F32 #x1CB5  #x7065 #x1D46
          #x7531 #x1EE8  #x7664 #x1F79)))
       (setf (svref a 223) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2140 #x1F  #x2273 #xB0  #x273F #x252  #x2872 #x2E3
          #x2D3E #x485  #x2E71 #x516  #x333D #x6B8  #x3470 #x749
          #x393C #x8EB  #x3A6F #x97C  #x3F3B #xB1E  #x406E #xBAF
          #x453A #xD51  #x466D #xDE2  #x4B39 #xF84  #x4C6C #x1015
          #x5138 #x11B7  #x526B #x1248  #x5737 #x13EA  #x586A #x147B
          #x5D36 #x161D  #x5E69 #x16AE  #x6335 #x1850  #x6468 #x18E1
          #x6934 #x1A83  #x6A67 #x1B14  #x6F33 #x1CB6  #x7066 #x1D47
          #x7532 #x1EE9  #x7665 #x1F7A)))
       (setf (svref a 224) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2141 #x20  #x2274 #xB1  #x2740 #x253  #x2873 #x2E4
          #x2D3F #x486  #x2E72 #x517  #x333E #x6B9  #x3471 #x74A
          #x393D #x8EC  #x3A70 #x97D  #x3F3C #xB1F  #x406F #xBB0
          #x453B #xD52  #x466E #xDE3  #x4B3A #xF85  #x4C6D #x1016
          #x5139 #x11B8  #x526C #x1249  #x5738 #x13EB  #x586B #x147C
          #x5D37 #x161E  #x5E6A #x16AF  #x6336 #x1851  #x6469 #x18E2
          #x6935 #x1A84  #x6A68 #x1B15  #x6F34 #x1CB7  #x7067 #x1D48
          #x7533 #x1EEA  #x7666 #x1F7B)))
       (setf (svref a 225) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2142 #x21  #x2275 #xB2  #x2741 #x254  #x2874 #x2E5
          #x2D40 #x487  #x2E73 #x518  #x333F #x6BA  #x3472 #x74B
          #x393E #x8ED  #x3A71 #x97E  #x3F3D #xB20  #x4070 #xBB1
          #x453C #xD53  #x466F #xDE4  #x4B3B #xF86  #x4C6E #x1017
          #x513A #x11B9  #x526D #x124A  #x5739 #x13EC  #x586C #x147D
          #x5D38 #x161F  #x5E6B #x16B0  #x6337 #x1852  #x646A #x18E3
          #x6936 #x1A85  #x6A69 #x1B16  #x6F35 #x1CB8  #x7068 #x1D49
          #x7534 #x1EEB  #x7667 #x1F7C)))
       (setf (svref a 226) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2143 #x22  #x2276 #xB3  #x2742 #x255  #x2875 #x2E6
          #x2D41 #x488  #x2E74 #x519  #x3340 #x6BB  #x3473 #x74C
          #x393F #x8EE  #x3A72 #x97F  #x3F3E #xB21  #x4071 #xBB2
          #x453D #xD54  #x4670 #xDE5  #x4B3C #xF87  #x4C6F #x1018
          #x513B #x11BA  #x526E #x124B  #x573A #x13ED  #x586D #x147E
          #x5D39 #x1620  #x5E6C #x16B1  #x6338 #x1853  #x646B #x18E4
          #x6937 #x1A86  #x6A6A #x1B17  #x6F36 #x1CB9  #x7069 #x1D4A
          #x7535 #x1EEC  #x7668 #x1F7D)))
       (setf (svref a 227) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2144 #x23  #x2277 #xB4  #x2743 #x256  #x2876 #x2E7
          #x2D42 #x489  #x2E75 #x51A  #x3341 #x6BC  #x3474 #x74D
          #x3940 #x8EF  #x3A73 #x980  #x3F3F #xB22  #x4072 #xBB3
          #x453E #xD55  #x4671 #xDE6  #x4B3D #xF88  #x4C70 #x1019
          #x513C #x11BB  #x526F #x124C  #x573B #x13EE  #x586E #x147F
          #x5D3A #x1621  #x5E6D #x16B2  #x6339 #x1854  #x646C #x18E5
          #x6938 #x1A87  #x6A6B #x1B18  #x6F37 #x1CBA  #x706A #x1D4B
          #x7536 #x1EED  #x7669 #x1F7E)))
       (setf (svref a 228) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2145 #x24  #x2278 #xB5  #x2744 #x257  #x2877 #x2E8
          #x2D43 #x48A  #x2E76 #x51B  #x3342 #x6BD  #x3475 #x74E
          #x3941 #x8F0  #x3A74 #x981  #x3F40 #xB23  #x4073 #xBB4
          #x453F #xD56  #x4672 #xDE7  #x4B3E #xF89  #x4C71 #x101A
          #x513D #x11BC  #x5270 #x124D  #x573C #x13EF  #x586F #x1480
          #x5D3B #x1622  #x5E6E #x16B3  #x633A #x1855  #x646D #x18E6
          #x6939 #x1A88  #x6A6C #x1B19  #x6F38 #x1CBB  #x706B #x1D4C
          #x7537 #x1EEE  #x766A #x1F7F)))
       (setf (svref a 229) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2146 #x25  #x2279 #xB6  #x2745 #x258  #x2878 #x2E9
          #x2D44 #x48B  #x2E77 #x51C  #x3343 #x6BE  #x3476 #x74F
          #x3942 #x8F1  #x3A75 #x982  #x3F41 #xB24  #x4074 #xBB5
          #x4540 #xD57  #x4673 #xDE8  #x4B3F #xF8A  #x4C72 #x101B
          #x513E #x11BD  #x5271 #x124E  #x573D #x13F0  #x5870 #x1481
          #x5D3C #x1623  #x5E6F #x16B4  #x633B #x1856  #x646E #x18E7
          #x693A #x1A89  #x6A6D #x1B1A  #x6F39 #x1CBC  #x706C #x1D4D
          #x7538 #x1EEF  #x766B #x1F80)))
       (setf (svref a 230) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2147 #x26  #x227A #xB7  #x2746 #x259  #x2879 #x2EA
          #x2D45 #x48C  #x2E78 #x51D  #x3344 #x6BF  #x3477 #x750
          #x3943 #x8F2  #x3A76 #x983  #x3F42 #xB25  #x4075 #xBB6
          #x4541 #xD58  #x4674 #xDE9  #x4B40 #xF8B  #x4C73 #x101C
          #x513F #x11BE  #x5272 #x124F  #x573E #x13F1  #x5871 #x1482
          #x5D3D #x1624  #x5E70 #x16B5  #x633C #x1857  #x646F #x18E8
          #x693B #x1A8A  #x6A6E #x1B1B  #x6F3A #x1CBD  #x706D #x1D4E
          #x7539 #x1EF0  #x766C #x1F81)))
       (setf (svref a 231) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2148 #x27  #x227B #xB8  #x2747 #x25A  #x287A #x2EB
          #x2D46 #x48D  #x2E79 #x51E  #x3345 #x6C0  #x3478 #x751
          #x3944 #x8F3  #x3A77 #x984  #x3F43 #xB26  #x4076 #xBB7
          #x4542 #xD59  #x4675 #xDEA  #x4B41 #xF8C  #x4C74 #x101D
          #x5140 #x11BF  #x5273 #x1250  #x573F #x13F2  #x5872 #x1483
          #x5D3E #x1625  #x5E71 #x16B6  #x633D #x1858  #x6470 #x18E9
          #x693C #x1A8B  #x6A6F #x1B1C  #x6F3B #x1CBE  #x706E #x1D4F
          #x753A #x1EF1  #x766D #x1F82)))
       (setf (svref a 232) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2149 #x28  #x227C #xB9  #x2748 #x25B  #x287B #x2EC
          #x2D47 #x48E  #x2E7A #x51F  #x3346 #x6C1  #x3479 #x752
          #x3945 #x8F4  #x3A78 #x985  #x3F44 #xB27  #x4077 #xBB8
          #x4543 #xD5A  #x4676 #xDEB  #x4B42 #xF8D  #x4C75 #x101E
          #x5141 #x11C0  #x5274 #x1251  #x5740 #x13F3  #x5873 #x1484
          #x5D3F #x1626  #x5E72 #x16B7  #x633E #x1859  #x6471 #x18EA
          #x693D #x1A8C  #x6A70 #x1B1D  #x6F3C #x1CBF  #x706F #x1D50
          #x753B #x1EF2  #x766E #x1F83)))
       (setf (svref a 233) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x214A #x29  #x227D #xBA  #x2749 #x25C  #x287C #x2ED
          #x2D48 #x48F  #x2E7B #x520  #x3347 #x6C2  #x347A #x753
          #x3946 #x8F5  #x3A79 #x986  #x3F45 #xB28  #x4078 #xBB9
          #x4544 #xD5B  #x4677 #xDEC  #x4B43 #xF8E  #x4C76 #x101F
          #x5142 #x11C1  #x5275 #x1252  #x5741 #x13F4  #x5874 #x1485
          #x5D40 #x1627  #x5E73 #x16B8  #x633F #x185A  #x6472 #x18EB
          #x693E #x1A8D  #x6A71 #x1B1E  #x6F3D #x1CC0  #x7070 #x1D51
          #x753C #x1EF3  #x766F #x1F84)))
       (setf (svref a 234) (make-array 60 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x214B #x2A  #x227E #xBB  #x274A #x25D  #x287D #x2EE
          #x2D49 #x490  #x2E7C #x521  #x3348 #x6C3  #x347B #x754
          #x3947 #x8F6  #x3A7A #x987  #x3F46 #xB29  #x4079 #xBBA
          #x4545 #xD5C  #x4678 #xDED  #x4B44 #xF8F  #x4C77 #x1020
          #x5143 #x11C2  #x5276 #x1253  #x5742 #x13F5  #x5875 #x1486
          #x5D41 #x1628  #x5E74 #x16B9  #x6340 #x185B  #x6473 #x18EC
          #x693F #x1A8E  #x6A72 #x1B1F  #x6F3E #x1CC1  #x7071 #x1D52
          #x753D #x1EF4  #x7670 #x1F85)))
       (setf (svref a 235) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x214C #x2B  #x274B #x25E  #x287E #x2EF  #x2D4A #x491
          #x2E7D #x522  #x3349 #x6C4  #x347C #x755  #x3948 #x8F7
          #x3A7B #x988  #x3F47 #xB2A  #x407A #xBBB  #x4546 #xD5D
          #x4679 #xDEE  #x4B45 #xF90  #x4C78 #x1021  #x5144 #x11C3
          #x5277 #x1254  #x5743 #x13F6  #x5876 #x1487  #x5D42 #x1629
          #x5E75 #x16BA  #x6341 #x185C  #x6474 #x18ED  #x6940 #x1A8F
          #x6A73 #x1B20  #x6F3F #x1CC2  #x7072 #x1D53  #x753E #x1EF5
          #x7671 #x1F86)))
       (setf (svref a 236) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x214D #x2C  #x274C #x25F  #x2D4B #x492  #x2E7E #x523
          #x334A #x6C5  #x347D #x756  #x3949 #x8F8  #x3A7C #x989
          #x3F48 #xB2B  #x407B #xBBC  #x4547 #xD5E  #x467A #xDEF
          #x4B46 #xF91  #x4C79 #x1022  #x5145 #x11C4  #x5278 #x1255
          #x5744 #x13F7  #x5877 #x1488  #x5D43 #x162A  #x5E76 #x16BB
          #x6342 #x185D  #x6475 #x18EE  #x6941 #x1A90  #x6A74 #x1B21
          #x6F40 #x1CC3  #x7073 #x1D54  #x753F #x1EF6  #x7672 #x1F87)))
       (setf (svref a 237) (make-array 54 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x214E #x2D  #x274D #x260  #x2D4C #x493  #x334B #x6C6
          #x347E #x757  #x394A #x8F9  #x3A7D #x98A  #x3F49 #xB2C
          #x407C #xBBD  #x4548 #xD5F  #x467B #xDF0  #x4B47 #xF92
          #x4C7A #x1023  #x5146 #x11C5  #x5279 #x1256  #x5745 #x13F8
          #x5878 #x1489  #x5D44 #x162B  #x5E77 #x16BC  #x6343 #x185E
          #x6476 #x18EF  #x6942 #x1A91  #x6A75 #x1B22  #x6F41 #x1CC4
          #x7074 #x1D55  #x7540 #x1EF7  #x7673 #x1F88)))
       (setf (svref a 238) (make-array 52 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x214F #x2E  #x274E #x261  #x2D4D #x494  #x334C #x6C7
          #x394B #x8FA  #x3A7E #x98B  #x3F4A #xB2D  #x407D #xBBE
          #x4549 #xD60  #x467C #xDF1  #x4B48 #xF93  #x4C7B #x1024
          #x5147 #x11C6  #x527A #x1257  #x5746 #x13F9  #x5879 #x148A
          #x5D45 #x162C  #x5E78 #x16BD  #x6344 #x185F  #x6477 #x18F0
          #x6943 #x1A92  #x6A76 #x1B23  #x6F42 #x1CC5  #x7075 #x1D56
          #x7541 #x1EF8  #x7674 #x1F89)))
       (setf (svref a 239) (make-array 50 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2150 #x2F  #x274F #x262  #x2D4E #x495  #x334D #x6C8
          #x394C #x8FB  #x3F4B #xB2E  #x407E #xBBF  #x454A #xD61
          #x467D #xDF2  #x4B49 #xF94  #x4C7C #x1025  #x5148 #x11C7
          #x527B #x1258  #x5747 #x13FA  #x587A #x148B  #x5D46 #x162D
          #x5E79 #x16BE  #x6345 #x1860  #x6478 #x18F1  #x6944 #x1A93
          #x6A77 #x1B24  #x6F43 #x1CC6  #x7076 #x1D57  #x7542 #x1EF9
          #x7675 #x1F8A)))
       (setf (svref a 240) (make-array 48 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2151 #x30  #x2750 #x263  #x2D4F #x496  #x334E #x6C9
          #x394D #x8FC  #x3F4C #xB2F  #x454B #xD62  #x467E #xDF3
          #x4B4A #xF95  #x4C7D #x1026  #x5149 #x11C8  #x527C #x1259
          #x5748 #x13FB  #x587B #x148C  #x5D47 #x162E  #x5E7A #x16BF
          #x6346 #x1861  #x6479 #x18F2  #x6945 #x1A94  #x6A78 #x1B25
          #x6F44 #x1CC7  #x7077 #x1D58  #x7543 #x1EFA  #x7676 #x1F8B)))
       (setf (svref a 241) (make-array 46 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2152 #x31  #x2751 #x264  #x2D50 #x497  #x334F #x6CA
          #x394E #x8FD  #x3F4D #xB30  #x454C #xD63  #x4B4B #xF96
          #x4C7E #x1027  #x514A #x11C9  #x527D #x125A  #x5749 #x13FC
          #x587C #x148D  #x5D48 #x162F  #x5E7B #x16C0  #x6347 #x1862
          #x647A #x18F3  #x6946 #x1A95  #x6A79 #x1B26  #x6F45 #x1CC8
          #x7078 #x1D59  #x7544 #x1EFB  #x7677 #x1F8C)))
       (setf (svref a 242) (make-array 44 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2153 #x32  #x2752 #x265  #x2D51 #x498  #x3350 #x6CB
          #x394F #x8FE  #x3F4E #xB31  #x454D #xD64  #x4B4C #xF97
          #x514B #x11CA  #x527E #x125B  #x574A #x13FD  #x587D #x148E
          #x5D49 #x1630  #x5E7C #x16C1  #x6348 #x1863  #x647B #x18F4
          #x6947 #x1A96  #x6A7A #x1B27  #x6F46 #x1CC9  #x7079 #x1D5A
          #x7545 #x1EFC  #x7678 #x1F8D)))
       (setf (svref a 243) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2154 #x33  #x2753 #x266  #x2D52 #x499  #x3351 #x6CC
          #x3950 #x8FF  #x3F4F #xB32  #x454E #xD65  #x4B4D #xF98
          #x514C #x11CB  #x574B #x13FE  #x587E #x148F  #x5D4A #x1631
          #x5E7D #x16C2  #x6349 #x1864  #x647C #x18F5  #x6948 #x1A97
          #x6A7B #x1B28  #x6F47 #x1CCA  #x707A #x1D5B  #x7546 #x1EFD
          #x7679 #x1F8E)))
       (setf (svref a 244) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2155 #x34  #x2621 #x1D6  #x2754 #x267  #x2D53 #x49A
          #x3352 #x6CD  #x3951 #x900  #x3F50 #xB33  #x454F #xD66
          #x4B4E #xF99  #x514D #x11CC  #x574C #x13FF  #x5D4B #x1632
          #x5E7E #x16C3  #x634A #x1865  #x647D #x18F6  #x6949 #x1A98
          #x6A7C #x1B29  #x6F48 #x1CCB  #x707B #x1D5C  #x7547 #x1EFE
          #x767A #x1F8F)))
       (setf (svref a 245) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2156 #x35  #x2622 #x1D7  #x2755 #x268  #x2C21 #x40A
          #x2D54 #x49B  #x3353 #x6CE  #x3952 #x901  #x3F51 #xB34
          #x4550 #xD67  #x4B4F #xF9A  #x514E #x11CD  #x574D #x1400
          #x5D4C #x1633  #x634B #x1866  #x647E #x18F7  #x694A #x1A99
          #x6A7D #x1B2A  #x6F49 #x1CCC  #x707C #x1D5D  #x7548 #x1EFF
          #x767B #x1F90)))
       (setf (svref a 246) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2157 #x36  #x2623 #x1D8  #x2756 #x269  #x2C22 #x40B
          #x2D55 #x49C  #x3221 #x63E  #x3354 #x6CF  #x3953 #x902
          #x3F52 #xB35  #x4551 #xD68  #x4B50 #xF9B  #x514F #x11CE
          #x574E #x1401  #x5D4D #x1634  #x634C #x1867  #x694B #x1A9A
          #x6A7E #x1B2B  #x6F4A #x1CCD  #x707D #x1D5E  #x7549 #x1F00
          #x767C #x1F91)))
       (setf (svref a 247) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2158 #x37  #x2624 #x1D9  #x2757 #x26A  #x2C23 #x40C
          #x2D56 #x49D  #x3222 #x63F  #x3355 #x6D0  #x3821 #x872
          #x3954 #x903  #x3F53 #xB36  #x4552 #xD69  #x4B51 #xF9C
          #x5150 #x11CF  #x574F #x1402  #x5D4E #x1635  #x634D #x1868
          #x694C #x1A9B  #x6F4B #x1CCE  #x707E #x1D5F  #x754A #x1F01
          #x767D #x1F92)))
       (setf (svref a 248) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2159 #x38  #x2625 #x1DA  #x2758 #x26B  #x2C24 #x40D
          #x2D57 #x49E  #x3223 #x640  #x3356 #x6D1  #x3822 #x873
          #x3955 #x904  #x3E21 #xAA6  #x3F54 #xB37  #x4553 #xD6A
          #x4B52 #xF9D  #x5151 #x11D0  #x5750 #x1403  #x5D4F #x1636
          #x634E #x1869  #x694D #x1A9C  #x6F4C #x1CCF  #x754B #x1F02
          #x767E #x1F93)))
       (setf (svref a 249) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x215A #x39  #x2626 #x1DB  #x2759 #x26C  #x2C25 #x40E
          #x2D58 #x49F  #x3224 #x641  #x3357 #x6D2  #x3823 #x874
          #x3956 #x905  #x3E22 #xAA7  #x3F55 #xB38  #x4421 #xCDA
          #x4554 #xD6B  #x4B53 #xF9E  #x5152 #x11D1  #x5751 #x1404
          #x5D50 #x1637  #x634F #x186A  #x694E #x1A9D  #x6F4D #x1CD0
          #x754C #x1F03)))
       (setf (svref a 250) (make-array 44 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x215B #x3A  #x2627 #x1DC  #x275A #x26D  #x2C26 #x40F
          #x2D59 #x4A0  #x3225 #x642  #x3358 #x6D3  #x3824 #x875
          #x3957 #x906  #x3E23 #xAA8  #x3F56 #xB39  #x4422 #xCDB
          #x4555 #xD6C  #x4A21 #xF0E  #x4B54 #xF9F  #x5153 #x11D2
          #x5752 #x1405  #x5D51 #x1638  #x6350 #x186B  #x694F #x1A9E
          #x6F4E #x1CD1  #x754D #x1F04)))
       (setf (svref a 251) (make-array 46 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x215C #x3B  #x2628 #x1DD  #x275B #x26E  #x2C27 #x410
          #x2D5A #x4A1  #x3226 #x643  #x3359 #x6D4  #x3825 #x876
          #x3958 #x907  #x3E24 #xAA9  #x3F57 #xB3A  #x4423 #xCDC
          #x4556 #xD6D  #x4A22 #xF0F  #x4B55 #xFA0  #x5021 #x1142
          #x5154 #x11D3  #x5753 #x1406  #x5D52 #x1639  #x6351 #x186C
          #x6950 #x1A9F  #x6F4F #x1CD2  #x754E #x1F05)))
       (setf (svref a 252) (make-array 48 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x215D #x3C  #x2629 #x1DE  #x275C #x26F  #x2C28 #x411
          #x2D5B #x4A2  #x3227 #x644  #x335A #x6D5  #x3826 #x877
          #x3959 #x908  #x3E25 #xAAA  #x3F58 #xB3B  #x4424 #xCDD
          #x4557 #xD6E  #x4A23 #xF10  #x4B56 #xFA1  #x5022 #x1143
          #x5155 #x11D4  #x5621 #x1376  #x5754 #x1407  #x5D53 #x163A
          #x6352 #x186D  #x6951 #x1AA0  #x6F50 #x1CD3  #x754F #x1F06)))
       (setf (svref a 253) (make-array 50 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x215E #x3D  #x262A #x1DF  #x275D #x270  #x2C29 #x412
          #x2D5C #x4A3  #x3228 #x645  #x335B #x6D6  #x3827 #x878
          #x395A #x909  #x3E26 #xAAB  #x3F59 #xB3C  #x4425 #xCDE
          #x4558 #xD6F  #x4A24 #xF11  #x4B57 #xFA2  #x5023 #x1144
          #x5156 #x11D5  #x5622 #x1377  #x5755 #x1408  #x5C21 #x15AA
          #x5D54 #x163B  #x6353 #x186E  #x6952 #x1AA1  #x6F51 #x1CD4
          #x7550 #x1F07)))
       (setf (svref a 254) (make-array 52 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x215F #x3E  #x262B #x1E0  #x275E #x271  #x2C2A #x413
          #x2D5D #x4A4  #x3229 #x646  #x335C #x6D7  #x3828 #x879
          #x395B #x90A  #x3E27 #xAAC  #x3F5A #xB3D  #x4426 #xCDF
          #x4559 #xD70  #x4A25 #xF12  #x4B58 #xFA3  #x5024 #x1145
          #x5157 #x11D6  #x5623 #x1378  #x5756 #x1409  #x5C22 #x15AB
          #x5D55 #x163C  #x6221 #x17DE  #x6354 #x186F  #x6953 #x1AA2
          #x6F52 #x1CD5  #x7551 #x1F08)))
       (setf (svref a 255) (make-array 54 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2160 #x3F  #x262C #x1E1  #x275F #x272  #x2C2B #x414
          #x2D5E #x4A5  #x322A #x647  #x335D #x6D8  #x3829 #x87A
          #x395C #x90B  #x3E28 #xAAD  #x3F5B #xB3E  #x4427 #xCE0
          #x455A #xD71  #x4A26 #xF13  #x4B59 #xFA4  #x5025 #x1146
          #x5158 #x11D7  #x5624 #x1379  #x5757 #x140A  #x5C23 #x15AC
          #x5D56 #x163D  #x6222 #x17DF  #x6355 #x1870  #x6821 #x1A12
          #x6954 #x1AA3  #x6F53 #x1CD6  #x7552 #x1F09)))
       (setf (svref a 256) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2161 #x40  #x262D #x1E2  #x2760 #x273  #x2C2C #x415
          #x2D5F #x4A6  #x322B #x648  #x335E #x6D9  #x382A #x87B
          #x395D #x90C  #x3E29 #xAAE  #x3F5C #xB3F  #x4428 #xCE1
          #x455B #xD72  #x4A27 #xF14  #x4B5A #xFA5  #x5026 #x1147
          #x5159 #x11D8  #x5625 #x137A  #x5758 #x140B  #x5C24 #x15AD
          #x5D57 #x163E  #x6223 #x17E0  #x6356 #x1871  #x6822 #x1A13
          #x6955 #x1AA4  #x6E21 #x1C46  #x6F54 #x1CD7  #x7553 #x1F0A)))
       (setf (svref a 257) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2162 #x41  #x262E #x1E3  #x2761 #x274  #x2C2D #x416
          #x2D60 #x4A7  #x322C #x649  #x335F #x6DA  #x382B #x87C
          #x395E #x90D  #x3E2A #xAAF  #x3F5D #xB40  #x4429 #xCE2
          #x455C #xD73  #x4A28 #xF15  #x4B5B #xFA6  #x5027 #x1148
          #x515A #x11D9  #x5626 #x137B  #x5759 #x140C  #x5C25 #x15AE
          #x5D58 #x163F  #x6224 #x17E1  #x6357 #x1872  #x6823 #x1A14
          #x6956 #x1AA5  #x6E22 #x1C47  #x6F55 #x1CD8  #x7421 #x1E7A
          #x7554 #x1F0B)))
       (setf (svref a 258) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2163 #x42  #x262F #x1E4  #x2762 #x275  #x2C2E #x417
          #x2D61 #x4A8  #x322D #x64A  #x3360 #x6DB  #x382C #x87D
          #x395F #x90E  #x3E2B #xAB0  #x3F5E #xB41  #x442A #xCE3
          #x455D #xD74  #x4A29 #xF16  #x4B5C #xFA7  #x5028 #x1149
          #x515B #x11DA  #x5627 #x137C  #x575A #x140D  #x5C26 #x15AF
          #x5D59 #x1640  #x6225 #x17E2  #x6358 #x1873  #x6824 #x1A15
          #x6957 #x1AA6  #x6E23 #x1C48  #x6F56 #x1CD9  #x7422 #x1E7B
          #x7555 #x1F0C)))
       (setf (svref a 259) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2164 #x43  #x2630 #x1E5  #x2763 #x276  #x2C2F #x418
          #x2D62 #x4A9  #x322E #x64B  #x3361 #x6DC  #x382D #x87E
          #x3960 #x90F  #x3E2C #xAB1  #x3F5F #xB42  #x442B #xCE4
          #x455E #xD75  #x4A2A #xF17  #x4B5D #xFA8  #x5029 #x114A
          #x515C #x11DB  #x5628 #x137D  #x575B #x140E  #x5C27 #x15B0
          #x5D5A #x1641  #x6226 #x17E3  #x6359 #x1874  #x6825 #x1A16
          #x6958 #x1AA7  #x6E24 #x1C49  #x6F57 #x1CDA  #x7423 #x1E7C
          #x7556 #x1F0D)))
       (setf (svref a 260) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2165 #x44  #x2631 #x1E6  #x2764 #x277  #x2C30 #x419
          #x2D63 #x4AA  #x322F #x64C  #x3362 #x6DD  #x382E #x87F
          #x3961 #x910  #x3E2D #xAB2  #x3F60 #xB43  #x442C #xCE5
          #x455F #xD76  #x4A2B #xF18  #x4B5E #xFA9  #x502A #x114B
          #x515D #x11DC  #x5629 #x137E  #x575C #x140F  #x5C28 #x15B1
          #x5D5B #x1642  #x6227 #x17E4  #x635A #x1875  #x6826 #x1A17
          #x6959 #x1AA8  #x6E25 #x1C4A  #x6F58 #x1CDB  #x7424 #x1E7D
          #x7557 #x1F0E)))
       (setf (svref a 261) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2166 #x45  #x2632 #x1E7  #x2765 #x278  #x2C31 #x41A
          #x2D64 #x4AB  #x3230 #x64D  #x3363 #x6DE  #x382F #x880
          #x3962 #x911  #x3E2E #xAB3  #x3F61 #xB44  #x442D #xCE6
          #x4560 #xD77  #x4A2C #xF19  #x4B5F #xFAA  #x502B #x114C
          #x515E #x11DD  #x562A #x137F  #x575D #x1410  #x5C29 #x15B2
          #x5D5C #x1643  #x6228 #x17E5  #x635B #x1876  #x6827 #x1A18
          #x695A #x1AA9  #x6E26 #x1C4B  #x6F59 #x1CDC  #x7425 #x1E7E
          #x7558 #x1F0F)))
       (setf (svref a 262) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2167 #x46  #x2633 #x1E8  #x2766 #x279  #x2C32 #x41B
          #x2D65 #x4AC  #x3231 #x64E  #x3364 #x6DF  #x3830 #x881
          #x3963 #x912  #x3E2F #xAB4  #x3F62 #xB45  #x442E #xCE7
          #x4561 #xD78  #x4A2D #xF1A  #x4B60 #xFAB  #x502C #x114D
          #x515F #x11DE  #x562B #x1380  #x575E #x1411  #x5C2A #x15B3
          #x5D5D #x1644  #x6229 #x17E6  #x635C #x1877  #x6828 #x1A19
          #x695B #x1AAA  #x6E27 #x1C4C  #x6F5A #x1CDD  #x7426 #x1E7F
          #x7559 #x1F10)))
       (setf (svref a 263) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2168 #x47  #x2634 #x1E9  #x2767 #x27A  #x2C33 #x41C
          #x2D66 #x4AD  #x3232 #x64F  #x3365 #x6E0  #x3831 #x882
          #x3964 #x913  #x3E30 #xAB5  #x3F63 #xB46  #x442F #xCE8
          #x4562 #xD79  #x4A2E #xF1B  #x4B61 #xFAC  #x502D #x114E
          #x5160 #x11DF  #x562C #x1381  #x575F #x1412  #x5C2B #x15B4
          #x5D5E #x1645  #x622A #x17E7  #x635D #x1878  #x6829 #x1A1A
          #x695C #x1AAB  #x6E28 #x1C4D  #x6F5B #x1CDE  #x7427 #x1E80
          #x755A #x1F11)))
       (setf (svref a 264) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2169 #x48  #x2635 #x1EA  #x2768 #x27B  #x2C34 #x41D
          #x2D67 #x4AE  #x3233 #x650  #x3366 #x6E1  #x3832 #x883
          #x3965 #x914  #x3E31 #xAB6  #x3F64 #xB47  #x4430 #xCE9
          #x4563 #xD7A  #x4A2F #xF1C  #x4B62 #xFAD  #x502E #x114F
          #x5161 #x11E0  #x562D #x1382  #x5760 #x1413  #x5C2C #x15B5
          #x5D5F #x1646  #x622B #x17E8  #x635E #x1879  #x682A #x1A1B
          #x695D #x1AAC  #x6E29 #x1C4E  #x6F5C #x1CDF  #x7428 #x1E81
          #x755B #x1F12)))
       (setf (svref a 265) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x216A #x49  #x2636 #x1EB  #x2769 #x27C  #x2C35 #x41E
          #x2D68 #x4AF  #x3234 #x651  #x3367 #x6E2  #x3833 #x884
          #x3966 #x915  #x3E32 #xAB7  #x3F65 #xB48  #x4431 #xCEA
          #x4564 #xD7B  #x4A30 #xF1D  #x4B63 #xFAE  #x502F #x1150
          #x5162 #x11E1  #x562E #x1383  #x5761 #x1414  #x5C2D #x15B6
          #x5D60 #x1647  #x622C #x17E9  #x635F #x187A  #x682B #x1A1C
          #x695E #x1AAD  #x6E2A #x1C4F  #x6F5D #x1CE0  #x7429 #x1E82
          #x755C #x1F13)))
       (setf (svref a 266) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x216B #x4A  #x2637 #x1EC  #x276A #x27D  #x2C36 #x41F
          #x2D69 #x4B0  #x3235 #x652  #x3368 #x6E3  #x3834 #x885
          #x3967 #x916  #x3E33 #xAB8  #x3F66 #xB49  #x4432 #xCEB
          #x4565 #xD7C  #x4A31 #xF1E  #x4B64 #xFAF  #x5030 #x1151
          #x5163 #x11E2  #x562F #x1384  #x5762 #x1415  #x5C2E #x15B7
          #x5D61 #x1648  #x622D #x17EA  #x6360 #x187B  #x682C #x1A1D
          #x695F #x1AAE  #x6E2B #x1C50  #x6F5E #x1CE1  #x742A #x1E83
          #x755D #x1F14)))
       (setf (svref a 267) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x216C #x4B  #x2638 #x1ED  #x276B #x27E  #x2C37 #x420
          #x2D6A #x4B1  #x3236 #x653  #x3369 #x6E4  #x3835 #x886
          #x3968 #x917  #x3E34 #xAB9  #x3F67 #xB4A  #x4433 #xCEC
          #x4566 #xD7D  #x4A32 #xF1F  #x4B65 #xFB0  #x5031 #x1152
          #x5164 #x11E3  #x5630 #x1385  #x5763 #x1416  #x5C2F #x15B8
          #x5D62 #x1649  #x622E #x17EB  #x6361 #x187C  #x682D #x1A1E
          #x6960 #x1AAF  #x6E2C #x1C51  #x6F5F #x1CE2  #x742B #x1E84
          #x755E #x1F15)))
       (setf (svref a 268) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x216D #x4C  #x2639 #x1EE  #x276C #x27F  #x2C38 #x421
          #x2D6B #x4B2  #x3237 #x654  #x336A #x6E5  #x3836 #x887
          #x3969 #x918  #x3E35 #xABA  #x3F68 #xB4B  #x4434 #xCED
          #x4567 #xD7E  #x4A33 #xF20  #x4B66 #xFB1  #x5032 #x1153
          #x5165 #x11E4  #x5631 #x1386  #x5764 #x1417  #x5C30 #x15B9
          #x5D63 #x164A  #x622F #x17EC  #x6362 #x187D  #x682E #x1A1F
          #x6961 #x1AB0  #x6E2D #x1C52  #x6F60 #x1CE3  #x742C #x1E85
          #x755F #x1F16)))
       (setf (svref a 269) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x216E #x4D  #x263A #x1EF  #x276D #x280  #x2C39 #x422
          #x2D6C #x4B3  #x3238 #x655  #x336B #x6E6  #x3837 #x888
          #x396A #x919  #x3E36 #xABB  #x3F69 #xB4C  #x4435 #xCEE
          #x4568 #xD7F  #x4A34 #xF21  #x4B67 #xFB2  #x5033 #x1154
          #x5166 #x11E5  #x5632 #x1387  #x5765 #x1418  #x5C31 #x15BA
          #x5D64 #x164B  #x6230 #x17ED  #x6363 #x187E  #x682F #x1A20
          #x6962 #x1AB1  #x6E2E #x1C53  #x6F61 #x1CE4  #x742D #x1E86
          #x7560 #x1F17)))
       (setf (svref a 270) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x216F #x4E  #x263B #x1F0  #x276E #x281  #x2C3A #x423
          #x2D6D #x4B4  #x3239 #x656  #x336C #x6E7  #x3838 #x889
          #x396B #x91A  #x3E37 #xABC  #x3F6A #xB4D  #x4436 #xCEF
          #x4569 #xD80  #x4A35 #xF22  #x4B68 #xFB3  #x5034 #x1155
          #x5167 #x11E6  #x5633 #x1388  #x5766 #x1419  #x5C32 #x15BB
          #x5D65 #x164C  #x6231 #x17EE  #x6364 #x187F  #x6830 #x1A21
          #x6963 #x1AB2  #x6E2F #x1C54  #x6F62 #x1CE5  #x742E #x1E87
          #x7561 #x1F18)))
       (setf (svref a 271) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2170 #x4F  #x263C #x1F1  #x276F #x282  #x2C3B #x424
          #x2D6E #x4B5  #x323A #x657  #x336D #x6E8  #x3839 #x88A
          #x396C #x91B  #x3E38 #xABD  #x3F6B #xB4E  #x4437 #xCF0
          #x456A #xD81  #x4A36 #xF23  #x4B69 #xFB4  #x5035 #x1156
          #x5168 #x11E7  #x5634 #x1389  #x5767 #x141A  #x5C33 #x15BC
          #x5D66 #x164D  #x6232 #x17EF  #x6365 #x1880  #x6831 #x1A22
          #x6964 #x1AB3  #x6E30 #x1C55  #x6F63 #x1CE6  #x742F #x1E88
          #x7562 #x1F19)))
       (setf (svref a 272) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2171 #x50  #x263D #x1F2  #x2770 #x283  #x2C3C #x425
          #x2D6F #x4B6  #x323B #x658  #x336E #x6E9  #x383A #x88B
          #x396D #x91C  #x3E39 #xABE  #x3F6C #xB4F  #x4438 #xCF1
          #x456B #xD82  #x4A37 #xF24  #x4B6A #xFB5  #x5036 #x1157
          #x5169 #x11E8  #x5635 #x138A  #x5768 #x141B  #x5C34 #x15BD
          #x5D67 #x164E  #x6233 #x17F0  #x6366 #x1881  #x6832 #x1A23
          #x6965 #x1AB4  #x6E31 #x1C56  #x6F64 #x1CE7  #x7430 #x1E89
          #x7563 #x1F1A)))
       (setf (svref a 273) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2172 #x51  #x263E #x1F3  #x2771 #x284  #x2C3D #x426
          #x2D70 #x4B7  #x323C #x659  #x336F #x6EA  #x383B #x88C
          #x396E #x91D  #x3E3A #xABF  #x3F6D #xB50  #x4439 #xCF2
          #x456C #xD83  #x4A38 #xF25  #x4B6B #xFB6  #x5037 #x1158
          #x516A #x11E9  #x5636 #x138B  #x5769 #x141C  #x5C35 #x15BE
          #x5D68 #x164F  #x6234 #x17F1  #x6367 #x1882  #x6833 #x1A24
          #x6966 #x1AB5  #x6E32 #x1C57  #x6F65 #x1CE8  #x7431 #x1E8A
          #x7564 #x1F1B)))
       (setf (svref a 274) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2173 #x52  #x263F #x1F4  #x2772 #x285  #x2C3E #x427
          #x2D71 #x4B8  #x323D #x65A  #x3370 #x6EB  #x383C #x88D
          #x396F #x91E  #x3E3B #xAC0  #x3F6E #xB51  #x443A #xCF3
          #x456D #xD84  #x4A39 #xF26  #x4B6C #xFB7  #x5038 #x1159
          #x516B #x11EA  #x5637 #x138C  #x576A #x141D  #x5C36 #x15BF
          #x5D69 #x1650  #x6235 #x17F2  #x6368 #x1883  #x6834 #x1A25
          #x6967 #x1AB6  #x6E33 #x1C58  #x6F66 #x1CE9  #x7432 #x1E8B
          #x7565 #x1F1C)))
       (setf (svref a 275) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2174 #x53  #x2640 #x1F5  #x2773 #x286  #x2C3F #x428
          #x2D72 #x4B9  #x323E #x65B  #x3371 #x6EC  #x383D #x88E
          #x3970 #x91F  #x3E3C #xAC1  #x3F6F #xB52  #x443B #xCF4
          #x456E #xD85  #x4A3A #xF27  #x4B6D #xFB8  #x5039 #x115A
          #x516C #x11EB  #x5638 #x138D  #x576B #x141E  #x5C37 #x15C0
          #x5D6A #x1651  #x6236 #x17F3  #x6369 #x1884  #x6835 #x1A26
          #x6968 #x1AB7  #x6E34 #x1C59  #x6F67 #x1CEA  #x7433 #x1E8C
          #x7566 #x1F1D)))
       (setf (svref a 276) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2175 #x54  #x2641 #x1F6  #x2774 #x287  #x2C40 #x429
          #x2D73 #x4BA  #x323F #x65C  #x3372 #x6ED  #x383E #x88F
          #x3971 #x920  #x3E3D #xAC2  #x3F70 #xB53  #x443C #xCF5
          #x456F #xD86  #x4A3B #xF28  #x4B6E #xFB9  #x503A #x115B
          #x516D #x11EC  #x5639 #x138E  #x576C #x141F  #x5C38 #x15C1
          #x5D6B #x1652  #x6237 #x17F4  #x636A #x1885  #x6836 #x1A27
          #x6969 #x1AB8  #x6E35 #x1C5A  #x6F68 #x1CEB  #x7434 #x1E8D
          #x7567 #x1F1E)))
       (setf (svref a 277) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2176 #x55  #x2642 #x1F7  #x2775 #x288  #x2C41 #x42A
          #x2D74 #x4BB  #x3240 #x65D  #x3373 #x6EE  #x383F #x890
          #x3972 #x921  #x3E3E #xAC3  #x3F71 #xB54  #x443D #xCF6
          #x4570 #xD87  #x4A3C #xF29  #x4B6F #xFBA  #x503B #x115C
          #x516E #x11ED  #x563A #x138F  #x576D #x1420  #x5C39 #x15C2
          #x5D6C #x1653  #x6238 #x17F5  #x636B #x1886  #x6837 #x1A28
          #x696A #x1AB9  #x6E36 #x1C5B  #x6F69 #x1CEC  #x7435 #x1E8E
          #x7568 #x1F1F)))
       (setf (svref a 278) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2177 #x56  #x2643 #x1F8  #x2776 #x289  #x2C42 #x42B
          #x2D75 #x4BC  #x3241 #x65E  #x3374 #x6EF  #x3840 #x891
          #x3973 #x922  #x3E3F #xAC4  #x3F72 #xB55  #x443E #xCF7
          #x4571 #xD88  #x4A3D #xF2A  #x4B70 #xFBB  #x503C #x115D
          #x516F #x11EE  #x563B #x1390  #x576E #x1421  #x5C3A #x15C3
          #x5D6D #x1654  #x6239 #x17F6  #x636C #x1887  #x6838 #x1A29
          #x696B #x1ABA  #x6E37 #x1C5C  #x6F6A #x1CED  #x7436 #x1E8F
          #x7569 #x1F20)))
       (setf (svref a 279) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2178 #x57  #x2644 #x1F9  #x2777 #x28A  #x2C43 #x42C
          #x2D76 #x4BD  #x3242 #x65F  #x3375 #x6F0  #x3841 #x892
          #x3974 #x923  #x3E40 #xAC5  #x3F73 #xB56  #x443F #xCF8
          #x4572 #xD89  #x4A3E #xF2B  #x4B71 #xFBC  #x503D #x115E
          #x5170 #x11EF  #x563C #x1391  #x576F #x1422  #x5C3B #x15C4
          #x5D6E #x1655  #x623A #x17F7  #x636D #x1888  #x6839 #x1A2A
          #x696C #x1ABB  #x6E38 #x1C5D  #x6F6B #x1CEE  #x7437 #x1E90
          #x756A #x1F21)))
       (setf (svref a 280) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2179 #x58  #x2645 #x1FA  #x2778 #x28B  #x2C44 #x42D
          #x2D77 #x4BE  #x3243 #x660  #x3376 #x6F1  #x3842 #x893
          #x3975 #x924  #x3E41 #xAC6  #x3F74 #xB57  #x4440 #xCF9
          #x4573 #xD8A  #x4A3F #xF2C  #x4B72 #xFBD  #x503E #x115F
          #x5171 #x11F0  #x563D #x1392  #x5770 #x1423  #x5C3C #x15C5
          #x5D6F #x1656  #x623B #x17F8  #x636E #x1889  #x683A #x1A2B
          #x696D #x1ABC  #x6E39 #x1C5E  #x6F6C #x1CEF  #x7438 #x1E91
          #x756B #x1F22)))
       (setf (svref a 281) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x217A #x59  #x2646 #x1FB  #x2779 #x28C  #x2C45 #x42E
          #x2D78 #x4BF  #x3244 #x661  #x3377 #x6F2  #x3843 #x894
          #x3976 #x925  #x3E42 #xAC7  #x3F75 #xB58  #x4441 #xCFA
          #x4574 #xD8B  #x4A40 #xF2D  #x4B73 #xFBE  #x503F #x1160
          #x5172 #x11F1  #x563E #x1393  #x5771 #x1424  #x5C3D #x15C6
          #x5D70 #x1657  #x623C #x17F9  #x636F #x188A  #x683B #x1A2C
          #x696E #x1ABD  #x6E3A #x1C5F  #x6F6D #x1CF0  #x7439 #x1E92
          #x756C #x1F23)))
       (setf (svref a 282) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x217B #x5A  #x2647 #x1FC  #x277A #x28D  #x2C46 #x42F
          #x2D79 #x4C0  #x3245 #x662  #x3378 #x6F3  #x3844 #x895
          #x3977 #x926  #x3E43 #xAC8  #x3F76 #xB59  #x4442 #xCFB
          #x4575 #xD8C  #x4A41 #xF2E  #x4B74 #xFBF  #x5040 #x1161
          #x5173 #x11F2  #x563F #x1394  #x5772 #x1425  #x5C3E #x15C7
          #x5D71 #x1658  #x623D #x17FA  #x6370 #x188B  #x683C #x1A2D
          #x696F #x1ABE  #x6E3B #x1C60  #x6F6E #x1CF1  #x743A #x1E93
          #x756D #x1F24)))
       (setf (svref a 283) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x217C #x5B  #x2648 #x1FD  #x277B #x28E  #x2C47 #x430
          #x2D7A #x4C1  #x3246 #x663  #x3379 #x6F4  #x3845 #x896
          #x3978 #x927  #x3E44 #xAC9  #x3F77 #xB5A  #x4443 #xCFC
          #x4576 #xD8D  #x4A42 #xF2F  #x4B75 #xFC0  #x5041 #x1162
          #x5174 #x11F3  #x5640 #x1395  #x5773 #x1426  #x5C3F #x15C8
          #x5D72 #x1659  #x623E #x17FB  #x6371 #x188C  #x683D #x1A2E
          #x6970 #x1ABF  #x6E3C #x1C61  #x6F6F #x1CF2  #x743B #x1E94
          #x756E #x1F25)))
       (setf (svref a 284) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x217D #x5C  #x2649 #x1FE  #x277C #x28F  #x2C48 #x431
          #x2D7B #x4C2  #x3247 #x664  #x337A #x6F5  #x3846 #x897
          #x3979 #x928  #x3E45 #xACA  #x3F78 #xB5B  #x4444 #xCFD
          #x4577 #xD8E  #x4A43 #xF30  #x4B76 #xFC1  #x5042 #x1163
          #x5175 #x11F4  #x5641 #x1396  #x5774 #x1427  #x5C40 #x15C9
          #x5D73 #x165A  #x623F #x17FC  #x6372 #x188D  #x683E #x1A2F
          #x6971 #x1AC0  #x6E3D #x1C62  #x6F70 #x1CF3  #x743C #x1E95
          #x756F #x1F26)))
       (setf (svref a 285) (make-array 58 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x217E #x5D  #x264A #x1FF  #x277D #x290  #x2C49 #x432
          #x2D7C #x4C3  #x3248 #x665  #x337B #x6F6  #x3847 #x898
          #x397A #x929  #x3E46 #xACB  #x3F79 #xB5C  #x4445 #xCFE
          #x4578 #xD8F  #x4A44 #xF31  #x4B77 #xFC2  #x5043 #x1164
          #x5176 #x11F5  #x5642 #x1397  #x5775 #x1428  #x5C41 #x15CA
          #x5D74 #x165B  #x6240 #x17FD  #x6373 #x188E  #x683F #x1A30
          #x6972 #x1AC1  #x6E3E #x1C63  #x6F71 #x1CF4  #x743D #x1E96
          #x7570 #x1F27)))
       (setf (svref a 286) (make-array 56 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x264B #x200  #x277E #x291  #x2C4A #x433  #x2D7D #x4C4
          #x3249 #x666  #x337C #x6F7  #x3848 #x899  #x397B #x92A
          #x3E47 #xACC  #x3F7A #xB5D  #x4446 #xCFF  #x4579 #xD90
          #x4A45 #xF32  #x4B78 #xFC3  #x5044 #x1165  #x5177 #x11F6
          #x5643 #x1398  #x5776 #x1429  #x5C42 #x15CB  #x5D75 #x165C
          #x6241 #x17FE  #x6374 #x188F  #x6840 #x1A31  #x6973 #x1AC2
          #x6E3F #x1C64  #x6F72 #x1CF5  #x743E #x1E97  #x7571 #x1F28)))
       (setf (svref a 287) (make-array 54 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x264C #x201  #x2C4B #x434  #x2D7E #x4C5  #x324A #x667
          #x337D #x6F8  #x3849 #x89A  #x397C #x92B  #x3E48 #xACD
          #x3F7B #xB5E  #x4447 #xD00  #x457A #xD91  #x4A46 #xF33
          #x4B79 #xFC4  #x5045 #x1166  #x5178 #x11F7  #x5644 #x1399
          #x5777 #x142A  #x5C43 #x15CC  #x5D76 #x165D  #x6242 #x17FF
          #x6375 #x1890  #x6841 #x1A32  #x6974 #x1AC3  #x6E40 #x1C65
          #x6F73 #x1CF6  #x743F #x1E98  #x7572 #x1F29)))
       (setf (svref a 288) (make-array 52 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x264D #x202  #x2C4C #x435  #x324B #x668  #x337E #x6F9
          #x384A #x89B  #x397D #x92C  #x3E49 #xACE  #x3F7C #xB5F
          #x4448 #xD01  #x457B #xD92  #x4A47 #xF34  #x4B7A #xFC5
          #x5046 #x1167  #x5179 #x11F8  #x5645 #x139A  #x5778 #x142B
          #x5C44 #x15CD  #x5D77 #x165E  #x6243 #x1800  #x6376 #x1891
          #x6842 #x1A33  #x6975 #x1AC4  #x6E41 #x1C66  #x6F74 #x1CF7
          #x7440 #x1E99  #x7573 #x1F2A)))
       (setf (svref a 289) (make-array 50 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x264E #x203  #x2C4D #x436  #x324C #x669  #x384B #x89C
          #x397E #x92D  #x3E4A #xACF  #x3F7D #xB60  #x4449 #xD02
          #x457C #xD93  #x4A48 #xF35  #x4B7B #xFC6  #x5047 #x1168
          #x517A #x11F9  #x5646 #x139B  #x5779 #x142C  #x5C45 #x15CE
          #x5D78 #x165F  #x6244 #x1801  #x6377 #x1892  #x6843 #x1A34
          #x6976 #x1AC5  #x6E42 #x1C67  #x6F75 #x1CF8  #x7441 #x1E9A
          #x7574 #x1F2B)))
       (setf (svref a 290) (make-array 48 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x264F #x204  #x2C4E #x437  #x324D #x66A  #x384C #x89D
          #x3E4B #xAD0  #x3F7E #xB61  #x444A #xD03  #x457D #xD94
          #x4A49 #xF36  #x4B7C #xFC7  #x5048 #x1169  #x517B #x11FA
          #x5647 #x139C  #x577A #x142D  #x5C46 #x15CF  #x5D79 #x1660
          #x6245 #x1802  #x6378 #x1893  #x6844 #x1A35  #x6977 #x1AC6
          #x6E43 #x1C68  #x6F76 #x1CF9  #x7442 #x1E9B  #x7575 #x1F2C)))
       (setf (svref a 291) (make-array 46 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2650 #x205  #x2C4F #x438  #x324E #x66B  #x384D #x89E
          #x3E4C #xAD1  #x444B #xD04  #x457E #xD95  #x4A4A #xF37
          #x4B7D #xFC8  #x5049 #x116A  #x517C #x11FB  #x5648 #x139D
          #x577B #x142E  #x5C47 #x15D0  #x5D7A #x1661  #x6246 #x1803
          #x6379 #x1894  #x6845 #x1A36  #x6978 #x1AC7  #x6E44 #x1C69
          #x6F77 #x1CFA  #x7443 #x1E9C  #x7576 #x1F2D)))
       (setf (svref a 292) (make-array 44 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2651 #x206  #x2C50 #x439  #x324F #x66C  #x384E #x89F
          #x3E4D #xAD2  #x444C #xD05  #x4A4B #xF38  #x4B7E #xFC9
          #x504A #x116B  #x517D #x11FC  #x5649 #x139E  #x577C #x142F
          #x5C48 #x15D1  #x5D7B #x1662  #x6247 #x1804  #x637A #x1895
          #x6846 #x1A37  #x6979 #x1AC8  #x6E45 #x1C6A  #x6F78 #x1CFB
          #x7444 #x1E9D  #x7577 #x1F2E)))
       (setf (svref a 293) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2652 #x207  #x2C51 #x43A  #x3250 #x66D  #x384F #x8A0
          #x3E4E #xAD3  #x444D #xD06  #x4A4C #xF39  #x504B #x116C
          #x517E #x11FD  #x564A #x139F  #x577D #x1430  #x5C49 #x15D2
          #x5D7C #x1663  #x6248 #x1805  #x637B #x1896  #x6847 #x1A38
          #x697A #x1AC9  #x6E46 #x1C6B  #x6F79 #x1CFC  #x7445 #x1E9E
          #x7578 #x1F2F)))
       (setf (svref a 294) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2653 #x208  #x2C52 #x43B  #x3251 #x66E  #x3850 #x8A1
          #x3E4F #xAD4  #x444E #xD07  #x4A4D #xF3A  #x504C #x116D
          #x564B #x13A0  #x577E #x1431  #x5C4A #x15D3  #x5D7D #x1664
          #x6249 #x1806  #x637C #x1897  #x6848 #x1A39  #x697B #x1ACA
          #x6E47 #x1C6C  #x6F7A #x1CFD  #x7446 #x1E9F  #x7579 #x1F30)))
       (setf (svref a 295) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2521 #x178  #x2654 #x209  #x2C53 #x43C  #x3252 #x66F
          #x3851 #x8A2  #x3E50 #xAD5  #x444F #xD08  #x4A4E #xF3B
          #x504D #x116E  #x564C #x13A1  #x5C4B #x15D4  #x5D7E #x1665
          #x624A #x1807  #x637D #x1898  #x6849 #x1A3A  #x697C #x1ACB
          #x6E48 #x1C6D  #x6F7B #x1CFE  #x7447 #x1EA0  #x757A #x1F31)))
       (setf (svref a 296) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2522 #x179  #x2655 #x20A  #x2B21 #x3AC  #x2C54 #x43D
          #x3253 #x670  #x3852 #x8A3  #x3E51 #xAD6  #x4450 #xD09
          #x4A4F #xF3C  #x504E #x116F  #x564D #x13A2  #x5C4C #x15D5
          #x624B #x1808  #x637E #x1899  #x684A #x1A3B  #x697D #x1ACC
          #x6E49 #x1C6E  #x6F7C #x1CFF  #x7448 #x1EA1  #x757B #x1F32)))
       (setf (svref a 297) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2523 #x17A  #x2656 #x20B  #x2B22 #x3AD  #x2C55 #x43E
          #x3121 #x5E0  #x3254 #x671  #x3853 #x8A4  #x3E52 #xAD7
          #x4451 #xD0A  #x4A50 #xF3D  #x504F #x1170  #x564E #x13A3
          #x5C4D #x15D6  #x624C #x1809  #x684B #x1A3C  #x697E #x1ACD
          #x6E4A #x1C6F  #x6F7D #x1D00  #x7449 #x1EA2  #x757C #x1F33)))
       (setf (svref a 298) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2524 #x17B  #x2657 #x20C  #x2B23 #x3AE  #x2C56 #x43F
          #x3122 #x5E1  #x3255 #x672  #x3721 #x814  #x3854 #x8A5
          #x3E53 #xAD8  #x4452 #xD0B  #x4A51 #xF3E  #x5050 #x1171
          #x564F #x13A4  #x5C4E #x15D7  #x624D #x180A  #x684C #x1A3D
          #x6E4B #x1C70  #x6F7E #x1D01  #x744A #x1EA3  #x757D #x1F34)))
       (setf (svref a 299) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2525 #x17C  #x2658 #x20D  #x2B24 #x3AF  #x2C57 #x440
          #x3123 #x5E2  #x3256 #x673  #x3722 #x815  #x3855 #x8A6
          #x3D21 #xA48  #x3E54 #xAD9  #x4453 #xD0C  #x4A52 #xF3F
          #x5051 #x1172  #x5650 #x13A5  #x5C4F #x15D8  #x624E #x180B
          #x684D #x1A3E  #x6E4C #x1C71  #x744B #x1EA4  #x757E #x1F35)))
       (setf (svref a 300) (make-array 40 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2526 #x17D  #x2659 #x20E  #x2B25 #x3B0  #x2C58 #x441
          #x3124 #x5E3  #x3257 #x674  #x3723 #x816  #x3856 #x8A7
          #x3D22 #xA49  #x3E55 #xADA  #x4321 #xC7C  #x4454 #xD0D
          #x4A53 #xF40  #x5052 #x1173  #x5651 #x13A6  #x5C50 #x15D9
          #x624F #x180C  #x684E #x1A3F  #x6E4D #x1C72  #x744C #x1EA5)))
       (setf (svref a 301) (make-array 42 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2527 #x17E  #x265A #x20F  #x2B26 #x3B1  #x2C59 #x442
          #x3125 #x5E4  #x3258 #x675  #x3724 #x817  #x3857 #x8A8
          #x3D23 #xA4A  #x3E56 #xADB  #x4322 #xC7D  #x4455 #xD0E
          #x4921 #xEB0  #x4A54 #xF41  #x5053 #x1174  #x5652 #x13A7
          #x5C51 #x15DA  #x6250 #x180D  #x684F #x1A40  #x6E4E #x1C73
          #x744D #x1EA6)))
       (setf (svref a 302) (make-array 44 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2528 #x17F  #x265B #x210  #x2B27 #x3B2  #x2C5A #x443
          #x3126 #x5E5  #x3259 #x676  #x3725 #x818  #x3858 #x8A9
          #x3D24 #xA4B  #x3E57 #xADC  #x4323 #xC7E  #x4456 #xD0F
          #x4922 #xEB1  #x4A55 #xF42  #x4F21 #x10E4  #x5054 #x1175
          #x5653 #x13A8  #x5C52 #x15DB  #x6251 #x180E  #x6850 #x1A41
          #x6E4F #x1C74  #x744E #x1EA7)))
       (setf (svref a 303) (make-array 46 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x2529 #x180  #x265C #x211  #x2B28 #x3B3  #x2C5B #x444
          #x3127 #x5E6  #x325A #x677  #x3726 #x819  #x3859 #x8AA
          #x3D25 #xA4C  #x3E58 #xADD  #x4324 #xC7F  #x4457 #xD10
          #x4923 #xEB2  #x4A56 #xF43  #x4F22 #x10E5  #x5055 #x1176
          #x5521 #x1318  #x5654 #x13A9  #x5C53 #x15DC  #x6252 #x180F
          #x6851 #x1A42  #x6E50 #x1C75  #x744F #x1EA8)))
       (setf (svref a 304) (make-array 48 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x252A #x181  #x265D #x212  #x2B29 #x3B4  #x2C5C #x445
          #x3128 #x5E7  #x325B #x678  #x3727 #x81A  #x385A #x8AB
          #x3D26 #xA4D  #x3E59 #xADE  #x4325 #xC80  #x4458 #xD11
          #x4924 #xEB3  #x4A57 #xF44  #x4F23 #x10E6  #x5056 #x1177
          #x5522 #x1319  #x5655 #x13AA  #x5B21 #x154C  #x5C54 #x15DD
          #x6253 #x1810  #x6852 #x1A43  #x6E51 #x1C76  #x7450 #x1EA9)))
       (setf (svref a 305) (make-array 50 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x252B #x182  #x265E #x213  #x2B2A #x3B5  #x2C5D #x446
          #x3129 #x5E8  #x325C #x679  #x3728 #x81B  #x385B #x8AC
          #x3D27 #xA4E  #x3E5A #xADF  #x4326 #xC81  #x4459 #xD12
          #x4925 #xEB4  #x4A58 #xF45  #x4F24 #x10E7  #x5057 #x1178
          #x5523 #x131A  #x5656 #x13AB  #x5B22 #x154D  #x5C55 #x15DE
          #x6121 #x1780  #x6254 #x1811  #x6853 #x1A44  #x6E52 #x1C77
          #x7451 #x1EAA)))
       (setf (svref a 306) (make-array 52 :element-type '(unsigned-byte 16) :initial-contents 
        '(#x252C #x183  #x265F #x214  #x2B2B #x3B6  #x2C5E #x447
          #x312A #x5E9  #x325D #x67A  #x3729 #x81C  #x385C #x8AD
          #x3D28 #xA4F  #x3E5B #xAE0  #x4327 #xC82  #x445A #xD13
          #x4926 #xEB5  #x4A59 #xF46  #x4F25 #x10E8  #x5058 #x1179
          #x5524 #x131B  #x5657 #x13AC  #x5B23 #x154E  #x5C56 #x15DF
          #x6122 #x1781  #x6255 #x1812  #x6721 #x19B4  #x6854 #x1A45
          #x6E53 #x1C78  #x7452 #x1EAB)))
       a))
)



(defun-substitution-macro map-unicode-to-GB-2312 (unicode)
  (NEW-get-cjk-code-mapping-if-any  unicode  unicode-to-GB-2312-map))

