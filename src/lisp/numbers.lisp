;; -*- Mode:Lisp; Package: CL-User; Base: 10; Syntax: Common-lisp -*-
(in-package "CL-USER")

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

#-lucid
(defmacro memq (item list)
  `(member ,item ,list :test 'eq))

#-lucid
(defmacro assq (item list)
  `(assoc ,item ,list :test 'eq))

;;; Normalize-key converts any string into a number by ignoring all
;;; non-alphanumneric characters, and treating what remains as a base 36 number.

(defun normalize-key (string)
  (loop with expt = 0
	with value = 0
	for i from 0 to (- (length string) 1)
	for weight = (digit-char-p (char string i) 36)
	do (when weight
	     (setq value (+ value (* weight (expt 36 expt))))
	     (incf expt))
	finally (return value)))



;;; The variables `block3' and `block4' are `permutation arrays'.  These serve
;;; effectively as the seeds for the randomness we put into the authorization
;;; codes.
;;;
;;; When the current codes want to be made not to work, we simply permute this
;;; arrays elements.  They should never be changed, just moved around a little.
;;; By convention, this is accomplished by simply taking two adjacent elements
;;; from anywhere and moving them somewhere else.  (Check to make sure the
;;; resulting permutation has never been used before.)
;;;
;;; Block3 is the permutation array corresponding to the codes for version 3 of
;;; G2.  Block4 is the permutation array corresponding to Version 4.  Block5 is
;;; the permutation array corresponding to Version 5.
;;;
;;; Whenever the permutation array is changed, so should be the "finger".
;;; Changing the `finger' eliminates innocent errors....
;;;
;;; The resulting permutation has to copied into choose-keytab, in sequences2.

(defparameter
  block3				; for version 3
  #(12 78 164 233 76 100 255 210 35 46 57 140 217 94 155 237 137 96 193 170 21 147 128 190
       194 253 199 90 222 196 181 108 109 84 6 93 40 160 166 156 175 254 219 243 235 136
       36 239 180 197 168 62 79 157 17 202 248 231 198 111 161 232 25 208 132 246 64 105
       119 204 153 139 213 121 50 97 185 129 82 14 83 252 10 200 211 24 151 39 7 122 174
       159 44 67 218 183 106 28 29 30 22 43 3 0 223 187 162 172 58 86 75 152 26 52 189 216
       177 126 242 23 42 47 182 209 163 63 98 33 220 250 171 149 5 48 95 230 251 212 74 32
       201 110 102 18 130 45 148 150 77 8 249 20 228 241 146 2 229 142 179 224 145 89 116
       9 61 51 69 56 91 184 133 114 221 244 59 225 205 31 144 191 131 138 38 11 203 16 71
       127 247 245 195 238 188 81 178 1 4 87 65 117 85 113 135 227 19 124 118 73 141
       41 123 236 169 99 186 80 125 115 134 158 54 37 206 240 70 13 49 234 176 101 103 107
       143 214 88 173 120 154 112 92 68 167 15 55 27 53 207 226 34 66 215 72 104 60
       192 165))

(defparameter
  block4				; permuted for version 4
  #(12 78 164 233 76 100 255 210 35 46 57 140 217 94 155 237
      137 96 193 170 21 147 128 190
      194 253 199 90 222 196 181 108 109 84 6 93 40 160 166
      156 175 254 219 243 235 136
      36 239 180 197 168 62 79 157 17 202 248 231 198 111
      161 232 25 208 132 246 64 105
      119 204 153 139 213 121 50 97 185 129 82 14 83 252 10
      200 211 24 151 39 7 122 174
      159 44 67 218 183 106 28 29 30 22 43 3 0 223 187 162 172
      58 86 75 152 26 52 189 216
      177 126 242 23 42 47 182 209 163 63 98 33 220 250 171 149 5
      48 95 230 251 212 
      201 110 102 18 130 45 148 150 77 8 249 20 228 241 146
      2 229 142 179 224 145 89 116
      9 61 51 69 56 91 184 133 114 221 244 59 225 205
      31 144 191 131 138 38 11 203 16 71 74 32
      127 247 245 195 238 188 81 178 1 4 87 65 117 85 113
      135 227 19 124 118 73 141
      41 123 236 169 99 186 80 125 115 134 158 54 37 206 240 70
      13 49 234 176 101 103 107
      143 214 88 173 120 154 112 92 68 167 15 55 27 53 207 226
      34 66 215 72 104 60
      192 165))

(defparameter
  block5				; permuted for version 5
  #(12 78 164 233 76 100 255 210 35 46 57 140 217 94 155 237
      137 96 193 170 21 147 128 190
      194 253 199 90 222 196 181 108 109 84 6 93 40 160 166
      156 175 254 219 243 235 136
      36 239 180 197 168 62 79 157 17 202 248 231 198 111
      161 232 25 208 132 246 64 105
      119 204 153 139 213 121 50 97 185 129 82 14 83 252 10
      200 211 24 151 39 7 174 122
      159 44 67 218 183 106 28 29 30 22 43 3 0 223 187 162 172
      58 86 75 152 26 52 189 216
      177 126 242 23 42 47 182 209 163 63 98 33 220 250 171 149 5
      48 95 230 251 212 
      201 110 102 18 130 45 148 150 77 8 249 20 228 241 146
      2 229 142 179 224 145 89 116
      9 61 51 69 56 91 184 133 114 221 244 59 225 205
      31 144 191 131 138 38 11 203 16 71 74 32
      127 247 245 195 238 188 81 178 1 4 87 65 117 85 113
      135 227 19 124 118 73 141
      41 123 236 169 99 186 80 125 115 134 158 54 37 206 240 70
      13 49 234 176 101 103 107
      143 214 88 173 120 154 112 92 68 167 15 55 27 53 207 226
      34 66 215 72 104 60
      192 165))

(defparameter
  block6				; ready to modify for version 6
  #(12 78 164 233 76 100 255 210 35 46 57 140 217 94 155 237
      137 96 193 170 21 147 128 190
      194 253 199 90 222 196 181 108 109 84 6 93 40 160 166
      156 175 254 219 243 235 136
      36 239 180 197 168 62 79 157 17 202 248 231 198 111
      161 232 25 208 132 246 64 105
      119 204 153 139 213 121 50 97 185 129 82 14 83 252 10
      200 211 24 151 39 7 174 122
      159 44 67 218 183 106 28 29 30 22 43 3 0 223 187 162 172
      58 86 75 152 26 52 189 216
      177 126 242 23 42 47 182 209 163 63 98 33 220 250 171 149 5
      48 95 230 251 212 
      201 110 102 18 130 45 148 150 77 8 249 20 228 241 146
      2 229 142 179 224 145 89 116
      9 61 51 69 56 91 184 133 114 221 244 59 225 205
      31 144 191 131 138 38 11 203 16 71 74 32
      127 247 245 195 238 188 81 178 1 4 87 65 117 85 113
      135 227 19 124 118 73 141
      41 123 236 169 99 186 80 125 115 134 158 54 37 206 240 70
      13 49 234 176 101 103 107
      143 214 88 173 120 154 112 92 68 167 15 55 27 53 207 226
      34 66 215 72 104 60
      192 165))

(defparameter
  block8				; permuted for version 8
       #(12 78 164 233 76 100 255 210 35 46 57 140 217 94 155 237
	 137 96 193 170 21 147 128 190
	 194 253 199 90 222 196 181 108 109 84 6 93 40 160 166
	 156 175 254 219 243 235 136
	 36 239 180 197 168 62 79 157 17 202 248 231 198 111
	 161 232 25 208 132 246 64 105
	 119 204 153 139 213 121 50 97 185 129 82 14 83 252 10
	 200 211 24 151 39 7 174 122
	 159 44 67 218 183 106 28 29 30 22 43 3 0 223 187 162 172
	 58 86 75 152 26 52 189 216
	 177 126 242 23 42 47 182 209 163 63 98 33 220 250 
	 48 95 230 251 212 
	 201 110 102 18 130 45 148 150 77 8 249 20 228 241 146
	 2 229 142 179 224 145 89 116
	 9 61 51 69 56 91 184 133 114 221 244 59 225 205
	 31 144 191 131 138 38 11 203 16 71 74 32 171 149 5 
	 127 247 245 195 238 188 81 178 1 4 87 65 117 85 113
	 135 227 19 124 118 73 141
	 41 123 236 169 99 186 80 125 115 134 158 54 37 206 240 70
	 13 49 234 176 101 103 107
	 143 214 88 173 120 154 112 92 68 167 15 55 27 53 207 226
	 34 66 215 72 104 60
	 192 165))

(defparameter
  block9				; permuted for version 9 (binghe, 10/2/2010)
       #(12 78 164 233 76 100 255 210 35 46 57 140 217 94 155 237
	 137 96 193 170 21 147 128 190
	 194 253 199 90 222 196 181 108 109 84 6 93 40 160 166
	 156 175 254 219 243 235 136
	 36 239 180 197 168 62 79 157 17 202 248 231 198 111
	 161 232 25 208 132 246 64 105
	 119 204 153 139 213 121 50 97 185 129 82 14 83 252 10
	 200 211 24 151 39 7 174 122
	 159 44 67 218 183 106 28 29 30 22 43 3 0 223 187 172 162 ; 162 172
	 58 86 75 152 26 52 189 216
	 177 126 242 23 42 47 182 209 163 63 98 33 220 250 
	 48 95 230 251 212 
	 201 110 102 18 130 45 148 150 77 8 249 20 228 241 146
	 2 229 142 179 224 145 89 116
	 9 61 51 69 56 91 184 133 114 221 244 59 225 205
	 31 144 191 131 138 38 11 203 16 71 74 32 171 149 5 
	 127 247 245 195 238 188 81 178 1 4 87 65 117 85 113
	 135 227 19 124 118 73 141
	 41 123 236 169 99 186 80 125 115 134 158 54 37 206 240 70
	 13 49 234 176 101 103 107
	 143 214 88 173 120 154 112 92 68 167 15 55 27 53 207 226
	 34 66 215 72 104 60
	 192 165))

(defparameter
  block11				; permuted for version 11 (tam.boirsyakovita@gdev.biz 06/13/2011)
       #(12 78 164 233 76 100 255 210 35 46 57 140 217 94 155 237
	 137 96 193 170 21 147 128 190
	 194 253 199 90 222 196 181 108 109 84 6 93 40 160 166
	 156 175 254 219 243 235 136
	 36 239 180 197 168 62 79 157 17 202 248 231 198 111
	 161 232 25 208 132 246 64 105
	 119 204 153 139 213 121 50 97 185 129 82 14 83 252 10
	 200 211 24 151 39 7 174 122
	 159 44 67 218 183 106 28 29 30 22 43 3 0 223 187 162 172
	 58 86 75 152 26 52 189 216
	 177 126 242 23 42 47 182 209 163 63 98 33 220 250 
	 48 95 230 251 212 
	 201 110 102 18 130 45 148 150 77 8 249 20 228 241 146
	 2 229 142 179 224 145 89 116
	 9 61 51 69 56 91 184 133 114 221 244 59 225 205
	 31 144 191 131 138 38 11 203 16 71 74 32 171 149 5 
	 127 247 245 195 238 188 81 178 1 4 87 65 117 85 113
	 135 227 19 124 118 73 141
	 115 134 158 41 123 236 169 99 186 80 125 54 37 206 240 70
	 13 49 234 176 101 103 107
	 143 214 88 173 120 154 112 92 68 167 15 55 27 53 207 226
	 34 66 215 72 104 60
	 192 165))
	 
; Consider making these fixnum arrays and adding declarations in the following code for speed.
(defparameter code-block (make-array 8))


;; Following is very fast and long.

(defmacro transpose-code-block ()
  (let ((r-var-list '(r0 r1 r2 r3 r4 r5 r6 r7))
	(s-var-list '(s0 s1 s2 s3 s4 s5 s6 s7)))
    
    `(let*
       ,(nconc
	  (loop for r-var in r-var-list
		   for i from 0
		   collecting `(,r-var (svref code-block ,i)))
	  (loop for s-var in s-var-list
		   collecting `(,s-var 0)))

       ,@(loop for i from 0 to 7
	       for r-var in r-var-list
	       nconcing
		 (loop for j from 0 to 7
		       for s-var in s-var-list
		       nconcing
			 `((if (/= 0 (logand ,r-var ,(ash 1 j)))
			       (setq ,s-var (logior ,s-var ,(ash 1 i)))))))

       ,@(loop for k from 0 to 7
	       for s-var in s-var-list
	       collecting
		 `(setf (svref code-block ,k) ,s-var)))))



(defmacro replace-code-block ()
  '(loop for i from 0 to 7 do
     (setf (svref code-block i)
	   (svref
	    (choose-g2-keytab-seed)
	    (svref code-block i)))))



(defmacro encode-code-block ()
  '(loop for i from 1 to 5 do
     (replace-code-block)
     (transpose-code-block)))

;;; Given block4 which is a key, and code-block which is a scratchpad, and does not
;;; have to be in any state, encode-whole-array takes any array of byte size
;;; integers and returns 4 fixnums which are the result, and a checksum, the fifth code.

;;; To make use of this, take any number of keys which are strings, concatenate them
;;; and normalize the result. Take this bignum and fill an array of appropriate size
;;; with its bytes.

;;; New? is t for use new algorithm.
;;; product code is a fixnum, default is 0.
;;; expiration-date? is nil or a universal-date.

(defun encode-whole-array (array new? product-code
			   expiration-date? number-of-processes?
			   maximum-number-of-concurrent-floating-telewindows-allowed
			   maximum-t2s-allowed)
  (loop with size = (length array)
	with bunch-count = (- (ceiling size 8) 1)
	for i from 1 to bunch-count
	initially (loop for i from 0 to 7 do
		    (setf (svref code-block i)
			  (if (< i size) (svref array i) i)))
	do (encode-code-block)
	   (loop for k from 0 to 7
		 for offset
		 = (* 8 (if new? i bunch-count))
		 for j = (+ k offset) do
	     (setf (svref code-block k)
		   (logxor (svref code-block k)
			   (if (< j size)
			       (svref array j)
			       j))))
	finally	
	  (when new?
	    (setf (svref code-block 7)
		  (logxor (svref code-block 7) (extract-byte product-code 0)))
	    (setf (svref code-block 6)
		  (logxor (svref code-block 6) (extract-byte product-code 1)))
	    
	    (when expiration-date?
	      (setf (svref code-block 5)
		    (logxor (svref code-block 5) (extract-byte expiration-date? 0)))
	      (setf (svref code-block 4)
		    (logxor (svref code-block 4) (extract-byte expiration-date? 1))))

	    (when number-of-processes?
	      (setf (svref code-block 3)
		    (logxor (svref code-block 3) number-of-processes?)))

	    (unless (= maximum-number-of-concurrent-floating-telewindows-allowed 0)
	      (setf (svref code-block 2)
		    (logxor (svref code-block 2)
			    (extract-byte 
			      maximum-number-of-concurrent-floating-telewindows-allowed
			      0)))
	      ;; The max is now 2^11-1 = 2047, no longer 2^8-1 = 255,
	      ;; so we need both bytes to get it all.
	      ;; The implemented max is actually 2^16-1 = 65535. - jpg 3/9/05
	      (setf (svref code-block 0)
		    (logxor (svref code-block 0)
			    (extract-byte 
			      maximum-number-of-concurrent-floating-telewindows-allowed
			      1))))

	    (unless (= maximum-t2s-allowed 0) ; default
	      (setf (svref code-block 1)
		    (logxor (svref code-block 1)
			    (extract-byte maximum-t2s-allowed 0)))
	      ;; the max is 2^16-1, so we need both bytes to get it all
	      (setf (svref code-block 0)
		    (logxor (svref code-block 0)
			    (extract-byte maximum-t2s-allowed 1)))))

	  (encode-code-block)
	  (return
	    (values (+ (svref code-block 0) (* 256 (svref code-block 1)))
		    (+ (svref code-block 2) (* 256 (svref code-block 3)))
		    (+ (svref code-block 4) (* 256 (svref code-block 5)))
		    (+ (svref code-block 6) (* 256 (svref code-block 7)))))))



;;; extract-byte has as value the nth byte from the left
;;; counting the leftmost byte as byte 0.

(defun extract-byte (fixnum byte)
  (logand (ash fixnum (* -8 byte)) 255))


(defparameter test-array
	      #(43 217 47 184 84 6 227 184 88 23 167))

(defun test-speed ()
  (loop for i from 0 to 10 do
    (encode-whole-array test-array nil 0 nil nil 0 0)))

(defvar fingerprint "xyr5k46ds")		; version? = nil

(defvar toeprint    "md93rhjd")			; version? = t

(defvar bellyprint  "f3r56twe4")		; version? = 3

(defvar voiceprint  "gsa88z0q3")		; version? = 4 (MHD 10/15/92)

(defvar retinalprint  "htb99a1r4")		; version? = 5 (MHD/DDM 6/5/97)

(defvar noseprint  "htb99a1r4")                 ; version? = 6

(defvar eyeprint "if8pbys64")                   ; version? = 8 (jpg 5/4/04)

(defvar earprint "80jz0hrt9")                   ; version? = 9 (binghe, 10/2/2010)

(defvar elfprint "by21bel86")                   ; version? = 11 (tam.boirsyakovita@gdev.biz 06/13/2011)

;;; When these are updated (e.g. to make g2v6), go to the section on
;;; temporary licenses and change its reference time, e.g. to 1999 so
;;; that we are always good for another 11 years worth of temporary
;;; license start dates. There are other places where this goes in too,
;;; grepping on "1990" is a reasonable strategy.

;; The variable chaining-refresh-list points to a string with the same contents
;; as the current "print".  For 3.0 & 4.0 First Beta Release (Rev. 0), it was
;; bellyprint.  For 4.0 Beta Second Release and Final Release, it has been
;; changed to voiceprint. (MHD 12/12/94)


(defvar make-ok-version)

(defun choose-finger ()  
  (cond
    ((null make-ok-version) fingerprint)
    ((eq make-ok-version t) toeprint)
    ((eql make-ok-version 3) bellyprint)
    ((eql make-ok-version 4) voiceprint)
    ((eql make-ok-version 5) retinalprint)
    ((eql make-ok-version 6) noseprint)
    ((eql make-ok-version 8) eyeprint)
    ((eql make-ok-version 83) eyeprint)
    ((or (eql make-ok-version 9) ; never been actually used
	 (eql make-ok-version 12)) ; re-used in G2 2015
     earprint) ; Chun Tian (binghe), 10/2/2010
    ((eql make-ok-version 11) elfprint) ; tam.boirsyakovita@gdev.biz 06/13/2011
    (t 
     (error "Bad make-ok-version, which should be of type (MEMBER NIL T 3 4 5 6 8 83 11 12), is ~s"
	    make-ok-version))))

(defun choose-g2-keytab-seed ()
  (cond
    ;; Apparently, we have gone back to block3 in authorizing versions
    ;; prior to "3", i.e., the "t" and "nil" versions.  I'm changing
    ;; this code to give out block3, which is what it always did; it will
    ;; soon be tested with a customer, Coopers and Lybrand, which is using
    ;; version 2.0 software at present. (10/30/95)
    ((null make-ok-version) block3)
    ((eq make-ok-version t) block3)
    ((eql make-ok-version 3) block3)
    ((eql make-ok-version 4) block4)
    ((eql make-ok-version 5) block5)
    ((eql make-ok-version 6) block6)
    ((eql make-ok-version 8) block8)
    ((eql make-ok-version 83) block8)
    ((or (eql make-ok-version 9) ; never been actually used
	 (eql make-ok-version 12)) ; re-used in G2 2015
     block9) ; Chun Tian (binghe), 10/2/2010
    ((eql make-ok-version 11) block11) ; tam.boirsyakovita@gdev.biz 06/13/2011
    (t
     (error "Bad make-ok-version, which should be of type (MEMBER NIL T 3 4 5 6 8 83 11 12), is ~s"
	    make-ok-version))))

;; To up version, make up a new block-n with a permutation of the array
;; elements; I do this by moving two adjacent elements to different locations in
;; the array.  (MHD 1/12/94)

(defun choose-tw-numeric-seed ()
  (cond
    ((null make-ok-version) (error "can't go back that far"))
    ((eq make-ok-version t) 54321)	; (<= g2-version 2.1)
    ((eql make-ok-version 3) 97578)	; TW Version 3.0
    ((eql make-ok-version 4) 109225)
    ((eql make-ok-version 5) 74890)	; (MHD/DDM 6/5/97)
    ((eql make-ok-version 6) 74890)
    ((eql make-ok-version 8) 98312)    ; jpg 5/4/04
    ((eql make-ok-version 83) 98312)
    ((or (eql make-ok-version 9) ; never been actually used
	 (eql make-ok-version 12)) ; re-used in G2 2015
     57909) ; Chun Tian (binghe), 10/2/2010
    ((eql make-ok-version 11) 19863) ; tam.boirsyakovita@gdev.biz 06/13/2011
    (t
     (error "Bad make-ok-version, which should be of type (MEMBER NIL T 3 4 5 6 8 83 11 12), is ~s"
	    make-ok-version))))

;; To up version, make up a new number with a different bit pattern.  It's wise
;; to keep the number of bits the same. (MHD 1/12/94)


;;; The fields in the `optional-modules-map' are (1) the name of the
;;; module, (2) its bit pattern (usually just one bit is set), (3) whether
;;; it is an atomic product (true of all cases except the various licensing
;;; levels, which are also the only cases that have set multiple bits since
;;; they are ANDs of other modules), and (4) whether the module is 'invisible',
;;; meaning (originally) that it does not appear on the G2 title block.
;;; (Note that now what goes on the title block is determined by the value of
;;; all-user-visibile-optional-modules. -ddm 6/10/98)

;;; We cannot as a practical matter make changes to this list, in particular
;;; we can't remove anything or replace one option with another. This is
;;; because we are obligated to always be able to authorize old systems,
;;; forever, even if a particular option (say gspan) is no longer included
;;; in our product set. As there are only 20 bits in this field (why?) we
;;; only get to play this trick five more times before something has to be
;;; reconsidered (such as redefining what one of these tokens actually means
;;; in the current version of the system). -ddm 6/11/98, from Troy..

(defvar optional-modules-map
  '(
    (ent                     #B00010000000000000000 T   NIL) ; enterprise - boris.yakovito July 2011
    (al                      #B00001000000000000000 T   NIL) ; ActiveXLink -ddm 6/9/98
    (jp                      #B00000100000000000000 T   NIL) ; JavaLink Pro -ddm 6/9/98
    (jl                      #B00000010000000000000 T   NIL) ; JavaLink -ddm 6/9/98
    (g1                      #B00000001000000000000 T   NIL) ; -bhyde, 10/20/94
    (korean                  #B00000000100000000000 T   NIL) ; (MHD 10/19/92)
    (embedded-option         #B00000000010000000000 T   T  ) ; (jh, 7/12/91)
    (restricted-use-option   #B00000000001000000000 T   T  ) ; (jh, 7/12/91)
    (nupec                   #B00000000000100000000 T   NIL)
    (japanese                #B00000000000010000000 T   NIL)
    (runtime-option          #B00000000000001000000 T   T  )
    (chinese                 #B00000000000000100000 T   NIL) ; ddm 4/8/99
    (kfep                    #B00000000000000010000 T   T  ) ; obsolete, use JAPANESE
    (gfi                     #B00000000000000001000 T   NIL)
    (icp                     #B00000000000000000100 T   NIL)
    (gspan                   #B00000000000000000010 T   NIL)
    (gsi                     #B00000000000000000001 T   NIL)

    (offline                 #B00000000000000000000 NIL NIL)

    (online                  #B00000000000000001101 NIL NIL)
    (embedded                #B00000000010000001101 NIL NIL) ;Added (jh, 7/12/91)
    (restricted-use          #B00000000001000001101 NIL NIL) ;Added (jh, 7/12/91)
    (runtime                 #B00000000000001001101 NIL NIL)
    ))

;; Optional-modules-map must be kept in synch with the forms def-optional-module
;; forms in G2 proper.  Note also that this variable mimic of the same name in
;; the AB package, and that sadly they ain't EQUAL.

;; The pattern like #B...01101 is implies that a license ENABLES: gsi, icp, and
;; gfi.  For example the runtime entry is equivalent to (GSI, ICP, GFI,
;; RUNTIME-OPTION), (except that RUNTIME-OPTION isn't a toggle user's ever see).

;; The bits are OR'd together to control the behavior of the product.
;; OFFLINE, notice how it's code is zero, disables GSI, ICP, and GFI
;; unless they are enabled directly.

;; Note that sales/marketing can redefine the license they call "OFFLINE" by
;; having the licensing department add bits back in again.

;; The third entry (is this a bundle of bits) and fourth entry (is this module
;; visible to users) are not used in this data structure.



(defparameter old-modulus 893127)
(defparameter new-modulus 943223)

(define-modify-macro clearbits (bits)
  logandc2)

;;; Make-ok produces the 5 magic numbers.
;;; key-string: machine id as a string (case does not matter, non-
;;;   alphanumerics are ignored.)
;;; version?:
;;;       nil for 2.0 alpha or earlier versions
;;;       t   for 2.0 beta though 2.1
;;;       3   (a fixnum) for 3.0 Rev. 0 (and 3.0 alpha 
;;;             & beta versions, which came earlier)
;;;       4   (a fixnum) for the second beta shipment of 4.0
;;;

;; NOTE: Gensym Management reserves the right to change the version from time to
;; time without cause.  3->4 is such a change.  (MHD 10/15/92)

;;; products: a list of optional modules (order does not matter;
;;;   valid entries are in the grammar for the authorized-products
;;;   slot of an OK object.)
;;; expiration-date?: an expiration date in the form of a list of
;;;   the form (day month year), where day is a number, month is
;;;   a three-letter month abbreviation as a symbol, and year is
;;;   a year (since the common era began; i.e. 1989 CE is the
;;;   the number 1989).
;;; start-date? must be an earlier date than expiration-date?. We no
;;;   longer permit authorizations that do not have both of these dates.
;;; number-of-processes? is nil ("no limit") or a fixnum from 1 to 200.
;;; 
;;; maximum-number-of-concurrent-floating-telewindows-allowed is a fixnum
;;; between 0 and 8000 (ie. ~ 14 bits) this field is ignored for values of
;;; version? prior to 4.0

;; Note maximum-number-of-concurrent-floating-telewindows-allowed is always
;; ignored right now, waiting for mark to do the secret work below here and in
;; int1. -- ben oct/26/94
;; Why do we keep around out of date commentary? Is somebody into a
;; study of G2 Midrash? -ddm 6/26/98

(defun make-ok (key-string &optional version?
		products expiration-date? start-date?
		number-of-processes?
		(maximum-number-of-concurrent-floating-telewindows-allowed 0)
		(maximum-t2s-allowed 0))
  
  (let* ((modulus (if version? new-modulus old-modulus))
	 (make-ok-version version?)	; special
	 (finger (choose-finger))       ; not used for version 3
	 (key
	   (normalize-key
	     (concatenate 'string key-string finger)))
	 
	 (modularized-key
	   (if (numberp make-ok-version)
	       (modulo-string-hash
		 (if (> make-ok-version 3)
		     (concatenate 'string key-string finger)
		     key-string)
		 modulus)
	       (mod key modulus)))
	 (keylength
	   (integer-length key))
	 (size
	   (ceiling keylength 8))
	 (array
	   (if (numberp make-ok-version)
	       (make-array-from-strings key-string finger)
	       (loop with array = (make-array size)
		     for position from 0 below size
		     as remainder = key
		     then (ash remainder -8)
		     until (= remainder 0)
		     do (setf (svref array position)
			      (logand remainder #o377))
		     finally (return array))))
	 (product-code
	   (loop with result = 0
		 for product in products do
		 (setq result
		       (logior result		 
			       (second (assoc product optional-modules-map
					      ;; the following permits the 
					      ;; use of symbols in any packages:   (MHD 4/22/91)
					      :test 'string-equal))))
		 (when (member 'offline products :test 'string-equal)
		   (loop for product-1 in '(gsi gfi icp)
			 unless (member product-1 products :test 'string-equal)
			 do
			 (clearbits result
				    (second (assq product-1
						  optional-modules-map)))))
		 finally (return result)))
						; New on 16 Apr 1990
	 (converted-expiration-date?
	   (if expiration-date?
	       (if start-date?
		   (encode-authorization-interval
		     (convert-input-to-universal-date-offline start-date?)
		     (convert-input-to-universal-date-offline expiration-date?))
		   (convert-input-to-universal-date-offline expiration-date?)))))
    
    (multiple-value-bind (c1 c2 c3 c4)
	(encode-whole-array
	  array make-ok-version
	  product-code converted-expiration-date? number-of-processes?
	  maximum-number-of-concurrent-floating-telewindows-allowed
	  maximum-t2s-allowed)      
      (values c1 c2 c3 c4
	      (if make-ok-version
		  (let ((c1x
			  (if (>= c1 100)
			      c1
			      (+ 394 (* 185 c1))))
			(c2x
			  (if (>= c2 100)
			      c2
			      (+ 260 (* 165 c2))))
			(c3x
			  (if (>= c3 100)
			      c3
			      (+ 111 (* 64 c3))))
			(c4x
			  (if (>= c4 100)
			      c4
			      (+ 973 (* 469 c4)))))
		    (mod
		      (logxor
			(inner-multiply modularized-key c3x)
			(inner-multiply c1x product-code)
			(inner-multiply c2x c4x)
			(inner-multiply
			  (or converted-expiration-date? 0)
			  (or converted-expiration-date? 0))
			(if number-of-processes?
			    (inner-multiply c3x number-of-processes? )
			    0)
			(if number-of-processes?
			    (inner-multiply c4x (ash number-of-processes? 8) )
			    0)
			(inner-multiply
			  c1x
			  maximum-number-of-concurrent-floating-telewindows-allowed)
			(inner-multiply
			  c2x
			  (ash maximum-number-of-concurrent-floating-telewindows-allowed
			       8))
			;; The magic numbers are all formed by adding two 8 bit bytes
			;; offset so as to produce a 16 bit fixnum. Inner-multiply
			;; produces 24 bit fixnums and makes no change if one of its
			;; arguments is zero. If the goal of the shifts in the two cases
			;; above is to smear a relatively small number through a much
			;; larger one (the number of processes is constrained to be less
			;; than 200, it's a definitive instance since it goes back to v3),
			;; then given that we anticipate the possibility of markedly
			;; larger numbers of T2 floating licenses, I'm going to shift
			;; by 12 (4k) instead of 8 (256) so as to get more distribution
			;; and less overlap.  ddm 7/14/98
			(inner-multiply
			  c3x maximum-t2s-allowed)
			(inner-multiply
			  c4x (ash maximum-t2s-allowed 12)))			  

		      modulus)) ;; 24 bits
		  
		  (mod
		    (logxor
		      (mod key modulus)
		      c1 c2 c3 c4) modulus))))))

;; Don't know why finger wasn't used in version 3. ML



;;; (Authorization intervals were) New as of 16 April 90.

;;; ddm -- Revised 6/22/98 to permit the authorization interval scheme to be
;;; used for yet another eleven years.  (See comment with the equivalent code in
;;; sequences2.)  This revision was done for 5.1r0. If a temporary license is
;;; made for any system older than that it has to be made with the old (1990)
;;; reference date since a 1998-encoded interval, when read by the code in a
;;; 1990-based version of G2, will be seen as though its dates were eight years
;;; in the past. A bad thing.

;;; The hack that detects whether we are serving a temporary license for a
;;; pre- vs. post- 5.1r0 G2 is the value of the floating T2 licenses in the
;;; authorization request. Nil mean pre-5.1r0, any number means post-5.1r0.
;;; This is checked for by license-1 and reflected in the value of the global.

(defconstant jan-1-1990 32872)     ;(encode-universal-date 1 1 1990) forward ref.
(defconstant jan-1-1998 35794)     ;(encode-universal-date 1 1 1998)
(defconstant jan-1-1999 36159)     ;(encode-universal-date 1 1 1999)
(defconstant jan-1-2006 38716)     ;(encode-universal-date 1 1 2006)
(defconstant jan-1-2009 39812)     ;(encode-universal-date 1 1 2009)
(defconstant jan-1-2015 42003)     ; (ab::encode-universal-date 1 1 2015)

;;; This may be rebound to the 1990 date by license-1 if appropriate.
;;; Also this may be reset in bundleok.lisp.
(defvar reference-date-for-interval-encoding jan-1-2015) ; old: jan-1-2009


(defun encode-authorization-interval (start-date end-date)
  (+ #.(expt 2 23)
     (- start-date reference-date-for-interval-encoding)
     (ash (- end-date start-date) 12)))






;(defun ask-id ()
;  (format t "~%Type the machine id: ")
;  (let ((id (numbers-read-line t nil)))
;    (if (string-equal (string-trim " " id) "")
;	nil
;	id)))

;(defun ask-customer ()
;  (format t "~&~%Type a Return to quit, or the customer name: ")
;  (let ((name (numbers-read-line t t)))
;    (if (string-equal (string-trim " " name) "")
;	nil
;	name)))
  

;; See if we are allowed to run on this particular computer

;(defun validate-machine-p ()
;  #-:ccl  (and (boundp 'chaos::my-address)
;	       (member chaos::my-address
;		       '(#o420			; Texas
;			 #o421			; Oklahoma
;			 #o401			; Massachusetts
;			 #o402)))		; New York
;  #+:ccl (validate-macintosh-p))

;; Needs to accept date and products as input.

;(defun codes (&optional (new? nil) (file-name? nil))
;  (cond
;    ((not (validate-machine-p))
;     "You may not operate this procedure on this host.")
;    (T
;     (let ((username (get-name-of-authorized-user)))
;       (if (null username)
;	   (return-from codes '"Incorrect username or password."))
;       (let* ((default-namestring
;		(string-downcase
;		  (namestring
;		    (make-pathname
;		      ':name "codes" ':type "text" ':version ':newest
;		      ':defaults "ma:>codes>"))))
;	      (file-name
;		(merge-pathnames
;		  (or file-name?
;		      (progn		    
;			(format t "~%File name [default: ~s]: " default-namestring)
;			(numbers-read-line t nil)))
;		  default-namestring))
;	      truename-namestring
;	      (ok-exit? nil))
;	 (format t "~&Opening ~s ... " (namestring file-name))
;	 (with-open-file (file-output file-name :direction :output) 
;	   (unwind-protect
;	       (progn
;		 (format t "OK.~&")
;		 (setq truename-namestring (namestring (truename file-output)))
;		 (loop repeat 2
;		       as stream = file-output then *terminal-io*
;		       do (format stream "~%CODES File ~s" truename-namestring)
;		          (format stream "~%Created:")
;			  (multiple-value-bind
;			    (second minute hour date month year
;			     day-of-the-week daylight-savings-time-p time-zone)
;			      (decode-universal-time (get-universal-time))
;			    (declare
;			      (ignore day-of-the-week daylight-savings-time-p time-zone))
;			    (format stream "~2,' d ~a ~2,'0d  ~d:~2,'0d:~2,'0d"
;				    ;; e.g. "10 December 86  8:05:19"
;				    date
;				    (nth (- month 1)
;					 '("Jan" "Feb" "Mar" "Apr" "May" "Jun"
;					   "Jul" "Aug" "Sep" "Oct" "Nov" "Dec"))
;				    year
;				    hour minute second))
;			  (format stream "~%Username: ~s" username))
;		 (loop as customer = (ask-customer)
;		       until (null customer)
;		       as id = (ask-id)
;		       do (multiple-value-bind (c1 c2 c3 c4 c5)
;			      (make-ok id new?)
;			    (loop repeat 2 as stream = file-output then *terminal-io*
;				  do (format stream "

;Customer: ~a
;The codes for machine ID \"~a\" are:

;Code 1: ~d
;Code 2: ~d
;Code 3: ~d
;Code 4: ~d
;Code 5: ~d

;"
;					     customer id c1 c2 c3 c4 c5))))
;		 (format file-output "~& -- End of CODES File -- ~&")
;		 (setq ok-exit? t))
;	     (format t "~&~a ~s ... "
;		     (if ok-exit? "Saving" "Deleting")
;		     truename-namestring))
;	 (format t "DONE.")
;	 truename-namestring)
;	 (if (null ok-exit?)
;	     (format t "~%Problems writing file!")))))))


;; Used to determine whether a Mac Machine id is genuine

(defun macverify (string)
  (= 0
     (mod (parse-integer string) 8317)))





;(defun read-char-without-echo ()
;  #+symbolics
;  (funcall *terminal-io* :tyi)
;  #+ti
;  (read-char *terminal-io*)
;  #-lispm
;  (error "This function is not implemented!"))

;(defun numbers-read-line (echo? upcase?)
;  (let ((string
;	  (if echo?
;	      (read-line)
;	      (with-output-to-string (*standard-output*)
;		(loop as c = (read-char-without-echo)
;		      until (eql c #\newline)
;		      when (eql c #\rubout)
;			do (return-from numbers-read-line nil)
;		      do (write-char c))))))
;    (if upcase? (string-upcase string) string)))


;(defun get-name-of-authorized-user ()
;  (format t "~&Username: ")
;  (let ((username (numbers-read-line t t)))
;    (cond
;      (username
;       (format t "~&Password: ")
;       (if (string-equal
;	     (numbers-read-line nil t)
;	     (cdr (assoc username
;			 '((mhd . gensymmhda)
;			   (pvl . gensympvla)
;			   (blm . gensymblma)
;			   (rll . gensymrlla)
;			   (ml . gensymmla))
;			 :test 'string-equal)))
;	   username)))))


;; To finish the new encoding, need a way to convert expiration date and
;; products into their internal forms. This requires a portion of
;; a slot putter (date) encode universal-date, and the def-module stuff.



(defconstant map-month-to-number-code
	     '((Jan 1 31)
	       (Feb 2 28)
	       (Mar 3 31)
	       (Apr 4 30)
	       (May 5 31)
	       (Jun 6 30)
	       (Jul 7 31)
	       (Aug 8 31)
	       (Sep 9 30)
	       (Oct 10 31)
	       (Nov 11 30)
	       (Dec 12 31))) 


(defun convert-input-to-universal-date-offline (list)
  (let* ((day (first list))
	 (month-code (assoc (second list) map-month-to-number-code :test #'string-equal))
	 (month (second month-code))
	 (days-in-month (third month-code))
	 (year-abbrev (third list))
	 (year (interpret-year year-abbrev)))
    ;; This two-digit calculation is wrong for y2k. Troy tells me that they
    ;; now always use four digit years when the request codes, and I've put
    ;; a check into license-1 to enforce it. ddm 6/22/98
    ;; -- UPDATE: changed to interpret year reasonably relative to the
    ;; current year plus or minus about 50 years. (MHD 3/23/01)
    (cond
      ((and (< 1601 year 2399)
	    (<= 1 month 12)
	    (> day 0)
	    (or (<= day days-in-month)
		(and (leap-year-p year)
		     (= month 2)
		     (= day 29))))
       (encode-universal-date day month year))
      (t nil))))


(defun leap-year-p (year)
  (and (= 0 (mod year 4))
       (or (/= 0 (mod year 100))
	   (= 0 (mod year 400)))))



(defconstant days-before-this-month
	'(0 31 59 90 120 151 181 212 243 273 304 334 365))



(defun encode-universal-date (day month year)
  (assert (>= year 1900))		; no 2-digit years allowed here
  (let ((normalized-year (- year 1900)))
    (+
      ;; Component for years, without leap year correction
      (* normalized-year 365)
      ;; Leap year correction for years between 1900 and this year
      ;; as if every four years was a leap year.
      (floor (+ normalized-year 3) 4)
      ;; Correction for centenial years.
      (- (floor (+ normalized-year 99) 100))
      ;; Correction for every fourth centenial being a leap year.
      (floor (+ normalized-year 299) 400)
      ;; Days this year before start of this month, ignoring leap year.
      (nth (- month 1) days-before-this-month)
      ;; Days of this month before this day.
      (- day 1)
      ;; Correction for leap day if there is one this year,
      ;; and it has already happened.
      (if (and (leap-year-p year)
	       (> month 2))   ;March or later in a leap-year
	  1 0)
      )))



(defparameter mask12 #o7777)



;;; Inner-multiply is a combiner of numbers which always produces a
;;; positive fixnum as its value. It behave like multiply for quite small
;;; numbers, and by folding, uses up to 24 bits of each argument to produce
;;; a value. In the G2 version, x and y must be fixnums.

(defun inner-multiply (x y)
  (* (logxor (logand x mask12) (logand (ash x -12) mask12))
     (logxor (logand y mask12) (logand (ash y -12) mask12))))



;; A cheap and inefficient utility not designed for other than developer use!

(defun factor (n)
  (if (= n 1)
      (list 1)
      (factor-1 n nil)))

(defun factor-1 (n result)
  (cond
    ((= n 2) (cons 2 result))

    ((evenp n)
     (factor-1 (floor n 2) (cons 2 result)))

    (t     
     (loop for i from 2 to (floor (sqrt n)) doing
	   (if (= (mod n i) 0)
	       (return (factor-1 (floor n i) (cons i result))))
	   finally
	   (return (cons n result))))))
	 

(defun primes-below-n (n)
  (terpri)
  (loop for i from n downto 1 doing 
	(if (= (length (factor i)) 1)
	    (print i))))

  
;;;; Back door system


						       
(defparameter mm1 16776379)
(defparameter mm2 12184771)
(defparameter mm3 3720484)
(defparameter mm4 "g0934sd")




(defun find-back-door (key-as-string)
  (loop with first-key = (gensym-string-hash
			   (concatenate 'string key-as-string mm4 key-as-string)
			   mm1)
	with second-key = (logior
			    (ash first-key -12)
			    (ash (logand first-key 4095) 12))
	with reduced-key = (inner-multiply
			     (logxor second-key mm3) second-key)
	with xx = (logxor reduced-key mm2)
	with result = "KDF"
	for i from 1 to 8
	doing
	(setq result (concatenate 'string result (format nil "~d" (logand xx 7))))
	(setq xx (ash xx -3))
	finally
	(return result)))






(defun gensym-string-hash (string modulus)
  (loop with length = (length string)
	with accumulator = 0
	with packer = 0
	with packing-index = 0
	for name-index from 0
	until (= name-index length)
	for char = (char string name-index) do
    (when (alphanumericp char)  
      (setq packer (+ (ash packer 6) (digit-char-p char 36)))
      (incf packing-index)
      (when (= 0 (logand packing-index 3))
	(setq accumulator (mod (+ (mod accumulator modulus)
				    packer) modulus))
	(setq packer 0)))
    
	finally
	  (when (> packer 0)
	    (setq packer (ash packer (* 6 (- 4 (logand packing-index 3)))))
	    (setq accumulator (mod (+ (mod packer modulus)
					accumulator) modulus)))	    
	  (return accumulator)))








;(defun random-maker (size)
;  (loop for i from 1 to size summing (* (random 2) (expt 2 (1- i)))))




;;;; Telewindows Authorization



;;; Telewindows authorization information is kept in the tw.ok file, a text file.
;;; Each line of this file contains authorization information for a machine.  Such
;;; a line has the following format:

;;; line: machine-name machine-id code1 code2 code3 code4 code5 [options]
;;; options:  [asian-language-options] [n-processes] [dates]
;;; n-processes: 0 | 1 | 2 | ...
;;; asian-language-options: JAPANESE | KOREAN | JAPANESE KOREAN | KOREAN JAPANESE
;;; dates:  FROM day month year TO day month year

;;; Month must be a member of {jan feb mar apr may jun jul aug sep oct nov dec}.



(defconstant large-mask (1- (expt 2 23)))


(defvar rs-array nil)

(defvar rs-array-current-pointer 54)

(defvar rs-array-24-pointer 24)


(defvar chaining-refresh-list "md93rhjd")
(defvar chaining-refresh-list-1 "f3r56twe4")





;;; Compute-tw-codes arguments:
;;;  - - name -             - type -
;;;  - machine-id           string
;;;  - start-day?           (or null (integer 1 31))
;;;  - start-month?         (member JAN FEB MAR APR MAY
;;;                            JUN JUL AUG SEP OCT NOV DEC)
;;;  - start-year?          (or null (integer 1 99) (integer 1900))
;;;  - expiration-day?      same as for start-day?
;;;  - expiration-month?    same as for start-month?
;;;  - expiration-year?     same as for start-year?
;;;
;;; If a 2-digit year is used, it is interpreted reasonably, i.e., via
;;; interpret-year, q.v., below.
;;;
;; NEW:
;;;  - asian-language-options
;;;                         list
;;;    (A list of the form
;;;       ({ asian-language-option })
;;;     where asian-language-option is JAPANESE | KOREAN)
;;;                         
;; OLD:
;;  - japanese?            (member nil t)
;;;  - number-of-processes? (or null (integer 1 ???))
;;;  - g2-version           float

;;; G2-version being 3.0 produces codes for 3.0 images from before 1/28/92.
;;; G2-version being 3.01 or greater produces codes for 3.0 images after 1/28/92.
;;; (The above was all done for back during the Alpha release phases versions;
;;; thus 3.01 is what is always used for the first final release: 3.0 Rev. 0.)
;;; Now, 3.02 will be for 3.0 Rev. 1 and later.
;;;
;;; In G2/TW Version 4, the version should be 4.0 (for Beta Phase 2 and later).
;;;
;;; In G2/TW Version 5, the version should be 5.0 (for Beta Rev. 1 and later).
;;;
;;; This now binds make-ok-version, normalized to the G2 spec for versioning
;;; around the call to its subfuctions below.  Make-ok-version has a different
;;; format than g2-version.

(defun compute-tw-codes (machine-id start-day? start-month? start-year?
				    expiration-day? expiration-month? expiration-year?
				    asian-language-options
				    number-of-processes?
				    g2-version)
  (let* ((make-ok-version
	   (cond
	     ((<= g2-version 2.1)
	      t)
	     ((< g2-version 4)		; 3.x
	      3)
	     ((< g2-version 5)		; 4.x
	      4)
	     ((< g2-version 6)		; 5.x
	      5)
	     ((< g2-version 8)		; 6.x, 7.x
	      6)
	     ((< g2-version 9)		; 8.x
	      8)
	     (t
	      11))))			; 2011

    (cond 
      ((or start-day? start-month? start-year? 
	   expiration-day? expiration-month? expiration-year?)
       (multiple-value-bind (start-date end-date)
	   (vet-tw-temporary-license-intervals
	     start-day? start-month? start-year? 
	     expiration-day? expiration-month? expiration-year?)
	 (compute-tw-codes-1 
	   machine-id start-date end-date
	   asian-language-options number-of-processes? g2-version)))
      (t
       (compute-tw-codes-1
	 machine-id nil nil
	 asian-language-options number-of-processes? g2-version)))))

;; jh & agh, 7/2/91.  Added per-process checking to Telewindows authorization.



(defun vet-tw-temporary-license-intervals
    (start-day? start-month? start-year? 
     expiration-day? expiration-month? expiration-year?)
  (let ((start-date? nil)
	(expiration-date? nil))
    (when (valid-tw-date-p start-day? start-month? start-year?)
      (setq start-date? 
	    (convert-input-to-universal-date-offline 
	      (list start-day? start-month? start-year?))))
    (when (valid-tw-date-p expiration-day? expiration-month? expiration-year?)
      (setq expiration-date? 
	    (convert-input-to-universal-date-offline 
	      (list expiration-day? expiration-month? expiration-year?))))
    (cond
      ((null start-date?)
       (error "~%~%~s ~s ~s is not a valid date.~%"
	      start-day? start-month? start-year?))
      ((null expiration-date?)
       (error "~%~%~s ~s ~s is not a valid date.~%"
	      expiration-day? expiration-month? expiration-year?))
      (t
       (values start-date? expiration-date?)))))





(defparameter tw-months-of-the-year
	      `(jan feb mar apr may jun jul aug sep oct nov dec))

(defun valid-tw-date-p (day month year)
  (and (fixnump day)
       (>= day 1)
       (<= day 31)
       (memq month tw-months-of-the-year)
       (fixnump year)))

(defun compute-tw-codes-1 
       (machine-id start-date? expiration-date?
	asian-language-options number-of-processes? g2-version)
  (multiple-value-bind
    (code1 code2 code3 code4)
      (enlarge-telewindows-memory 
	machine-id start-date? expiration-date?
	asian-language-options number-of-processes? g2-version)
    (values
      code1 code2 code3 code4
      (check-small-workspace-1
	machine-id code1 code2 code3 code4
	start-date? expiration-date?
	asian-language-options
	number-of-processes?
	g2-version))))





;;; Compute-telewindows-authorization-numbers (given misleading name
;;; enlarge-telewindows-memory) takes a machine id as argument and computes the
;;; four authorization numbers from it using the rs-array mechanism.
;;; Machine-id is a string.  Generate-large-random is called iteratively to modify
;;; this array in a manner similar to that used by g2-random for generating random
;;; numbers.  However, because rs-array, and the pointers
;;; rs-array-current-pointer and rs-array-24-pointer are
;;; initialized to the same value each time, the results are completely
;;; deterministic; the same four numbers will always be computed for any given
;;; machine id.


;;; Machine-id is a text string which should be the same as the result of
;;; get-local-machine-id-as-text-string although it can contain superfluous
;;; non-alphanumeric characters.


(defun enlarge-telewindows-memory
       (machine-id start-date? expiration-date? asian-language-options number-of-processes? g2-version)
  (shrink-telewindows-memory 
    machine-id start-date? expiration-date? asian-language-options number-of-processes? g2-version)
  (setq rs-array-current-pointer 54)
  (setq rs-array-24-pointer 30)
  (loop for i from 1 to 500
	do (generate-large-random))
  (values (aref rs-array 0) (aref rs-array 1)
	  (aref rs-array 2) (aref rs-array 3)))




(defmacro normalize-key-online-1 (string)
  (let ((string-value (gensym)))
    `(loop with ,string-value = ,string
	   with expt = 1
	   with value = 0	   
	   for i from 0 to (- (length ,string-value) 1)
	   for weight = (digit-char-p (char ,string-value i) 36) doing
       (when weight
	 (setq value (+ value (* weight expt)))
	 (setq expt (* expt 36)))
	   finally (return value))))



;;; Make-last-telewindows-authorization-number (given misleading name
;;; check-small-workspace) takes the four principal telewindows authorization
;;; numbers and generates the fifth.

(defun check-small-workspace-1
    (machine-id number1 number2 number3 number4
		start-date? expiration-date? optional-product-modules 
		number-of-processes?
		g2-version)
  (let* ((finger (choose-finger))
         (keystring
           (concatenate 'string machine-id finger))
	 (modularized-key
           (mod (normalize-key-online-1 keystring)
                new-modulus))
         (number-of-processes-default
           (if (>= g2-version 3.01)
               1001 
               2))
	 (japanese? (memq 'japanese optional-product-modules)) ; obsolete as of 4.0
	 (korean? (memq 'korean optional-product-modules)))
    (if (< number1 100) (setq number1 (+ 253 (* 792 number1))))
    (if (< number2 100) (setq number2 (+ 468 (* 905 number2))))
    (if (< number3 100) (setq number3 (+ 167 (* 312 number3))))
    (if (< number4 100) (setq number4 (+ 833 (* 398 number4))))
    (cond
      ((<= g2-version 2.1)
       (mod
         (logxor
           (inner-multiply modularized-key number1)
           (inner-multiply number2 number3)
           (inner-multiply number4 number4)
           (inner-multiply (or start-date? 0) (or expiration-date? 0))
           (inner-multiply
             (if (memq 'japanese optional-product-modules) 5781 0)
             (if (memq 'japanese optional-product-modules) number4 0))
           )
         new-modulus))
      (t
       (mod
	 (let* ((t1 (or start-date? 0))
		(t2 (or expiration-date? 0))
		(t3 (+ (if japanese? 5781 0) (if korean? 2556 0)))
		(t4 (+ (if japanese? number4 0) (if korean? number3 0)))
		(t5 (or number-of-processes? number-of-processes-default))
		(t6 (or number-of-processes? number-of-processes-default))
		;; license type: the type DEVELOPMENT is the default, and correspond to
		;; the following being all nil; the following are mutually exclusive:
		(license-type-multiplier
		  (cond
		    ((memq 'runtime-option optional-product-modules)
		     number1)
		    ((memq 'restricted-use-option optional-product-modules)
		     number2)
		    ((memq 'embedded-option optional-product-modules)
		     number3)
		    (t
		     0)))
		(t7 (inner-multiply license-type-multiplier number1))
		(t8 (inner-multiply license-type-multiplier number2)))	
	   (logxor
	     (inner-multiply modularized-key number1)
	     (inner-multiply number2 number3)
	     (inner-multiply number4 number4)
	     (inner-multiply t1 t2)
	     (inner-multiply t3 t4)
	     (inner-multiply t5 t6)
	     (inner-multiply t7 t8)))
	 new-modulus)))))



;; Previous version.  Remove after a few days:   (MHD 1/26/95)

;(defun check-small-workspace-1 (machine-id number1 number2 number3 number4
;                                start-date? expiration-date? asian-language-options
;                                number-of-processes?
;                                g2-version)
;  (let* ((finger (choose-finger))
;         (keystring
;           (concatenate 'string machine-id finger))
;         (modularized-key
;           (mod (normalize-key-online-1 keystring)
;                new-modulus))
;         (number-of-processes-default
;           (if (>= g2-version 3.01)
;               1001 
;               2))
;         )
;    (if (< number1 100)
;        (setq number1
;              (+ 253 (* 792 number1))))
;    (if (< number2 100)
;        (setq number2
;              (+ 468 (* 905 number2))))
;    (if (< number3 100)
;        (setq number3
;              (+ 167 (* 312 number3))))
;    (if (< number4 100)
;        (setq number4
;              (+ 833 (* 398 number4))))
;    (cond
;      ((<= g2-version 2.1)
;       (mod
;         (logxor
;           (inner-multiply modularized-key number1)
;           (inner-multiply number2 number3)
;           (inner-multiply number4 number4)
;           (inner-multiply (or start-date? 0) (or expiration-date? 0))
;           (inner-multiply
;             (if (memq 'japanese asian-language-options) 5781 0)
;             (if (memq 'japanese asian-language-options) number4 0))
;           )
;         new-modulus))
;      (t
;       (mod
;         (let ((t1 (or start-date? 0))
;               (t2 (or expiration-date? 0))
;               (t3 (+ (if (memq 'japanese asian-language-options)
;                          5781
;                          0)
;                      (if (memq 'korean asian-language-options)
;                          2556
;                          0)))
;               (t4 (+ (if (memq 'japanese asian-language-options)
;                          number4
;                          0)
;                      (if (memq 'korean asian-language-options)
;                          number3
;                          0)
;                      ;; use number2 for Chinese, number1 next, then ask ML.
;                      ;; ML: just use an inner-multiply of two of these after
;                      ;;  that.
;                      ;; (MHD 11/9/92))
;                      ))
;               (t5 (or number-of-processes? number-of-processes-default))
;               (t6 (or number-of-processes? number-of-processes-default))
;               )
;           (logxor
;             (inner-multiply modularized-key number1)
;             (inner-multiply number2 number3)
;             (inner-multiply number4 number4)
;             (inner-multiply t1 t2)
;             (inner-multiply t3 t4)
;             (inner-multiply t5 t6)
;             ))
;         new-modulus)))))




;;; Initialize-state-array-for-telewindows-authorization (given misleading name
;;; shrink-telewindows-memory) takes a machine id (a string) as argument and
;;; initializes rs-array.  It does this by converting each alphanumeric
;;; digit in the machine id to a number between 0 and 35, and then looping through
;;; these numbers until the array is full.

(defun shrink-telewindows-memory
       (machine-id start-date? expiration-date? asian-language-options
	number-of-processes? g2-version)
  (unless rs-array
    (setq rs-array
	  (make-array 55 :element-type 'fixnum)))
  (loop for state-array-index from 0 to 54 do 
    (setf (aref rs-array state-array-index)
	  ;; Seed:
	  (choose-tw-numeric-seed)))
  (loop with state-array-index = 0
	for i from 0 below (length machine-id)
	as weight = (digit-char-p (char machine-id i) 36)
	do
    (when weight
      (setf (aref rs-array state-array-index) weight)
      (setq state-array-index (+ state-array-index 1)))
	until (= state-array-index 55))
  (setf (aref rs-array 54) 1)
  ;; to ensure at least one odd number

  (cond
    ((<= g2-version 2.1)
     (when start-date?
       (setf (aref rs-array 3) start-date?))
     (when expiration-date?
       (setf (aref rs-array 4) expiration-date?)
       (setf (aref rs-array 5) expiration-date?))
     (when (memq 'japanese asian-language-options)
       (setf (aref rs-array 6) 89342)
       (setf (aref rs-array 5) 14867)))
    (t
     (when start-date?
       (setf (aref rs-array 3) 
	     (logxor (aref rs-array 3) start-date?)
	     (aref rs-array 4) 
	     (logxor (aref rs-array 4) start-date?)
	     (aref rs-array 5) 
	     (logxor (aref rs-array 5) start-date?)
	     (aref rs-array 6) 
	     (logxor (aref rs-array 6) start-date?)))
     (when expiration-date?
       (setf (aref rs-array 7)
	     (logxor (aref rs-array 7) expiration-date?)
	     (aref rs-array 8)
	     (logxor (aref rs-array 8) expiration-date?)
	     (aref rs-array 9)
	     (logxor (aref rs-array 9) expiration-date?)
	     (aref rs-array 10)
	     (logxor (aref rs-array 10) expiration-date?)))
     (when (memq 'japanese asian-language-options)
       (setf (aref rs-array 11)
	     (logxor (aref rs-array 11) 89342)
	     (aref rs-array 12)
	     (logxor (aref rs-array 12) 14783)
	     (aref rs-array 13)
	     (logxor (aref rs-array 13) 28335)
	     (aref rs-array 14)
	     (logxor (aref rs-array 14) 67482)))
     (when (memq 'korean asian-language-options)
       (setf (aref rs-array 11)
	     (logxor (aref rs-array 11) 29138)
	     (aref rs-array 12)
	     (logxor (aref rs-array 12) 40417)
	     (aref rs-array 13)
	     (logxor (aref rs-array 13) 57969)
	     (aref rs-array 14)
	     (logxor (aref rs-array 14) 15408)))
     (when number-of-processes?
       (setf (aref rs-array 15)
	     (logxor (aref rs-array 15) 
		     (if (>= g2-version 3.01)
			 (* number-of-processes? 47)
			 47731))
	     (aref rs-array 16)
	     (logxor (aref rs-array 16) 11963)
	     (aref rs-array 17)
	     (logxor (aref rs-array 17) 67802)
	     (aref rs-array 18)
	     (logxor (aref rs-array 17) 19575))) ; yes, ....
     ;; ... yes, 18 would have made sense, but the 17 wants to remain forever
     ;; now that it's been there, unless we "rev" this.  Not likely.

     ;; Added in 4.0 beta phase 2:  (MHD 1/28/95)
     (let* ((key-in-modules-map?
	      (cond
		((memq 'runtime-option asian-language-options)
		 'runtime-option)
		((memq 'restricted-use-option asian-language-options)
		 'restricted-use-option)
		((memq 'embedded-option asian-language-options)
		 'embedded-option)))
	    (optional-module-entry-map?
	      (assq key-in-modules-map? optional-modules-map))
	    (authorized-products-bitmask (second optional-module-entry-map?)))
       (when key-in-modules-map?
	 ;; development is the default, and is implied by the other ones not present;
         ;; the others are mutually exclusive; the Japanese and Korean options are
         ;; obsolete, but were historically included in other slots; see above
         (setf (aref rs-array 19)
               (logxor (aref rs-array 19) authorized-products-bitmask)))))))

;; The only thing that's version dependent in terms of authorization codes is
;; the "seed" for the random-state (rs) array.  The rest of the
;; version-dependencies are for improvements of various sorts in the
;; functionality.  (MHD 1/12/95)

;; Note that there is no need to explicitly check for non-alphanumeric characters
;; since the call to digit-char-p returns nil for them.  Also, digit-char-p
;; returns the same weight for upper and lower case alphabetic characters so there
;; is no need to explicitly convert to upper case.

;; The initialization to 12345 (rather than 0) helps make authorization numbers
;; large.  Iterating more than 500 times would also do this.




(defun generate-large-random ()
  (let ((current-pointer rs-array-current-pointer)
	(24-pointer rs-array-24-pointer))
    (incf current-pointer)
    (if (= current-pointer 55) (setq current-pointer 0))
    (setq rs-array-current-pointer current-pointer)
    (incf 24-pointer)
    (if (= 24-pointer 55) (setq 24-pointer 0))
    (setq rs-array-24-pointer 24-pointer)

    (setf (aref rs-array current-pointer)
	  (logand large-mask (+ (aref rs-array current-pointer)
				(aref rs-array 24-pointer))))))










(defun number-of-alphanumerics-in-string (string)
  (loop with length =  (length string)
	for i from 0 below length
	when (digit-char-p (char string i) 36)
	  count t))


;;; normalized-string-equal is true if its arguments are strings
;;; which would be equal if all letters were the same case and all
;;; non alpahnumeric characters were removed. It is nill for
;;; any other pair of strings.

(defun normalized-string-equal (string1 string2)
  (loop with length1 = (length string1)
	with length2 = (length string2)
	with w1 = nil
	with w2 = nil
	with i1 = 0
	with i2 = 0 do
    (loop until (>= i1 length1) do
      (when (setq w1 (digit-char-p (char string1 i1) 36))
	(incf i1)
	(return (values)))
      (incf i1)
	  finally
	    (setq w1 nil))
    (loop until (>= i2 length2) do      
      (when (setq w2 (digit-char-p (char string2 i2) 36))
	(incf i2)
	(return (values)))
      (incf i2)
	  finally
	    (setq w2 nil))
    (if (not (eql w1 w2)) (return nil))
    (if (and (>= i1 length1) (>= i2 length2)) (return t))))




;;; make-array-from-strings forms an array whose length is the sum
;;; the number of alphanumeric characters in both strings and
;;; whose contents are fixnums in the range 0-255 derrived from
;;; the strings in a deterministic manner. A modest attempt is made
;;; to make the array contents unreadable from the source text.
				
(defun make-array-from-strings (string1 string2)
  (loop with length1 = (length string1)
	with length2 = (length string2)	
	with nlength1 = (number-of-alphanumerics-in-string string1)
	with nlength2 = (number-of-alphanumerics-in-string string2)
	with array = (make-array (+ nlength1 nlength2))
	with w1 = nil
	with w2 = nil
	with i1 = 0
	with i2 = 0
	for i from 0 below (max nlength1 nlength2) do
    (loop until (>= i1 length1) do
      (when (setq w1 (digit-char-p (char string1 i1) 36))
	(incf i1)
	(return (values)))
      (incf i1)
	  finally
	    (setq w1 nil))
    (loop until (>= i2 length2) do      
      (when (setq w2 (digit-char-p (char string2 i2) 36))
	(incf i2)
	(return (values)))
      (incf i2)
	  finally
	    (setq w2 nil))
    (when (< i nlength1)
      (setf (aref array i) w1))
    (when (< i nlength2)
      (setf (aref array (+ i nlength1)) w2))
	finally
	  (loop for i from 0 to (+ nlength1 nlength2 -2) do
	    (setf (aref array (+ i 1))
		  (mod (+ (* 3769 (aref array i))
			    (* 6237 (aref array (+ i 1))))
			256)))
	  (return array)))




(defun array-made-from-strings-p (string1 string2 array)
  (loop with length1 = (length string1)
	with length2 = (length string2)	
	with nlength1 = (number-of-alphanumerics-in-string string1)
	with nlength2 = (number-of-alphanumerics-in-string string2)
	with w1 = nil
	with w2 = nil
	with i1 = 0
	with i2 = 0
	for i from 0 below nlength1
	initially
	  (when (/= (length array) (+ nlength1 nlength2)) (return nil))
	do
    (loop until (>= i1 length1) do
      (when (setq w1 (digit-char-p (char string1 i1) 36))
	(incf i1)
	(return (values)))
      (incf i1)
	  finally
	    (setq w1 nil))
    (when (/= (aref array i)
	       (if (= i 0)
		   w1
		   (mod (+ (* 3769 (aref array (- i 1)))
			     (* 6237 w1))
			 256)))
      (return nil))
    
	finally
	  (return
	    (loop for i from nlength1 below nlength2 do
	      (loop until (>= i2 length2) do      
		(when (setq w2 (digit-char-p (char string2 i2) 36))
		  (incf i2)
		  (return (values)))
		(incf i2)
		    finally
		      (setq w2 nil))
	      (when (/= (aref array i)
			 (mod (+ (* 3769 (aref array (- i 1)))
				   (* 6237 w2))
			       256))
		(return nil))
		  finally
		    (return t)))))



;;; modulo-string-hash computes a non-negative fixnum less than
;;; the modulus from the string.






(defun modulo-string-hash (string modulus)
  (loop with length = (length string)
	with w = nil
	with i = 0
	with result = 0 do
    (loop until (>= i length) do
      (when (setq w (digit-char-p (char string i) 36))
	(incf i)
	(return (values)))
      (incf i)
	  finally
	    (setq w nil))
    when (null w) do (return result)
	do
    (setq result
	  (mod (logxor result
			 (* w 354673))
		modulus))))







;;;; Computing Telewindows 2 Authorizations

;;; This set of obscurely, if similarly, named variables and functions
;;; is the equivalent of the `finger' for G2 -- it provides version-
;;; specific seeds for the hash routines. Changing just the seed will
;;; result in different codes, thereby allowing us to make the codes
;;; generated for older versions unusable in later versions whenever we
;;; choose to do that. The design is a straight adaption of what is
;;; done for G2. 

(eval-when (compile load eval)
(defvar pulse-rate-multiplier 1)  ; cf.chaining-refresh-version

;;; The burned-in value of pulse-rate-multiplier tells us what version
;;; these sources are currently. It is dynamically rebound by the
;;; license-server's code as needed so that we can generated the codes
;;; for any version that the software has had.


;;; This number is the base value that goes into the code-generation
;;; array. See initialize-random-state-array-for-tw2.

(defmacro choose-tw2-numeric-seed-macro ()
  `(case pulse-rate-multiplier
     (1 87975)))  ; chaining-refresh-version #3 is 97578


;;; The value returned by `choose-pulse-rate-multiplier' becomes
;;; the value of `pulse-rate-options' which is used in the checksum
;;; calculation. See compute-tw2-code-checksum. 

(defun choose-pulse-rate-multiplier ()
  (case pulse-rate-multiplier
    (1 "q4b14f8gs")  ; chosen at random. Same length as 
    (t (error        ; chaining-refresh-versions.
	 "unknown version: ~d" pulse-rate-multiplier))))

(defvar pulse-rate-options nil)

) ; end eval-when



;;; N.b. All the names of these routines are in the clear. This file
;;; is encrypted after all.  The obscured equivalents used for the
;;; deep runtime check are in sequences1. The clear names are there
;;; as macros.


;;; `Compute-tw2-codes' is the entry-point the License Server. All that
;;; happens here is that we bind the version flags to the value dictated
;;; by the call to the server. This aspect was pulled out as its own
;;; function so I could get the deep checker by copying rather than
;;; jiggling the modularity. 

(defun compute-tw2-codes (machine-id
			  start-day? start-month? start-year?
			  expiration-day? expiration-month? expiration-year?
			  license-level
			  version)

  (let* ((pulse-rate-multiplier version)
	 (pulse-rate-options (choose-pulse-rate-multiplier)))
    (compute-tw2-codes-for-current-version
      machine-id start-day? start-month? start-year?
      expiration-day? expiration-month? expiration-year?
      license-level)))



;;; All that happens in `compute-tw2-codes-for-current-version that we look
;;; at the spread arguments for the temporary license interval (if there is
;;; one) and convert them to a pair of encoded times. This is the entry
;;; point (in sequences3) for the deep check that recomputes what the codes
;;; should be from first principles.

(defun compute-tw2-codes-for-current-version
    (machine-id
      start-day? start-month? start-year?
      expiration-day? expiration-month? expiration-year?
      license-level)
  
  (cond 
    ((or start-day? start-month? start-year? 
	 expiration-day? expiration-month? expiration-year?)
     (multiple-value-bind (start-date end-date)
	 (vet-tw-temporary-license-intervals
	   start-day? start-month? start-year? 
	   expiration-day? expiration-month? expiration-year?)
       (compute-tw2-codes-1 
	 machine-id start-date end-date license-level)))
    (t
     (compute-tw2-codes-1
       machine-id nil nil license-level))))




;;; This is a straight copy&specialization of compute-tw-codes-1.
;;; That calls the two components of the code generator to get
;;; the work done and return the expected values.

(defun compute-tw2-codes-1
       (machine-id start-date? expiration-date? license-level)
  (multiple-value-bind
      (code1 code2 code3 code4)
      (create-tw2-authorization-codes
	machine-id start-date? expiration-date? license-level)
    (values
      code1 code2 code3 code4
      (compute-tw2-code-checksum
	machine-id code1 code2 code3 code4
	start-date? expiration-date? license-level))))



;;; `Create-tw2-authorization-codes' computes the four codes that
;;; are the the result of the array-driven hash of the authorization
;;; information that is being protected, i.e. the machine this copy
;;; is licensed to, its validity interval if it is a temporary license,
;;; and the level of its license visa vie the G2 it connects to.
;;; This is an unembellished copy of enlarge-telewindows-memory.

(defun create-tw2-authorization-codes (machine-id
				       start-date end-date
				       authorization-level)
  
  ;; Initialize. Fill up the early parts of the array
  ;; with the information we're trying to smear through
  ;; the codes. 
  (initialize-random-state-array-for-tw2
    machine-id start-date end-date authorization-level)
  (setq rs-array-current-pointer 54)
  (setq rs-array-24-pointer 30)

  ;; Churn. This algorithm walks not quite ten times through a fixnum array
  ;; that was initially populated with a version specific seed number. As
  ;; it goes it resets the array values to be the sum the values at two
  ;; different points in the array and'ed with a fixnum's length (23 bits)
  ;; worth of 1s. I.m.h.o. the resulting codes don't have nearly enough
  ;; entropy in them, as becomes obvious if you compare what them with
  ;; the codes generated for G2 licenses. -ddm
  (loop for i from 1 to 500
	do (generate-large-random))

  ;; Read out
  (values (aref rs-array 0) (aref rs-array 1)
	  (aref rs-array 2) (aref rs-array 3)))



;;; This initialization routine is a straight adaption of the code
;;; in `shrink-telewindows-memory'. The primary difference is that
;;; there isn't as much potential information in a tw2 license as
;;; there can be in a tw license, so this is markedly shorter.

(defun initialize-random-state-array-for-tw2
    (machine-id start-date? expiration-date? authorization-level)
  
  (macrolet ((launder-tw2-license-level (level)
	       ;; The documentation of what the permitted license levels are for
	       ;; a telewindowss (which we are cloning for tw2) is out of
	       ;; sync. with the reality of what the code accepts.This acts as
	       ;; an impedence matcher to bring them into sync. It returns a
	       ;; fresh list that is reclaimed in the section that calls this.
	       `(gensym-list
		  (case ,level
		    (deployment 'restricted-use)
		    (t (error "Unknown license level for a tw2: ~a" ,level))))))
    
    (unless rs-array
      (setq rs-array
	    (make-array 55 :element-type 'fixnum)))
    
    (loop for state-array-index from 0 to 54 do 
      (setf (aref rs-array state-array-index)
	    (choose-tw2-numeric-seed-macro)))

    (loop with state-array-index = 0
	  for i from 0 below (length machine-id)
	  as weight? = (digit-char-p (char machine-id i) 36)
	  do
      (when weight?
	(setf (aref rs-array state-array-index) weight?)
	(setq state-array-index (+ 1 state-array-index)))
	  until (= state-array-index 55))
    
    (setf (aref rs-array 54) 1)
    ;; why do we need at least one odd number?

    (when start-date?
      (setf (aref rs-array 3) 
	    (logxor (aref rs-array 3) start-date?)
	    (aref rs-array 4) 
	    (logxor (aref rs-array 4) start-date?)
	    (aref rs-array 5) 
	    (logxor (aref rs-array 5) start-date?)
	    (aref rs-array 6) 
	    (logxor (aref rs-array 6) start-date?)))

    (when expiration-date?
      (setf (aref rs-array 7)
	    (logxor (aref rs-array 7) expiration-date?)
	    (aref rs-array 8)
	    (logxor (aref rs-array 8) expiration-date?)
	    (aref rs-array 9)
	    (logxor (aref rs-array 9) expiration-date?)
	    (aref rs-array 10)
	    (logxor (aref rs-array 10) expiration-date?)))


    (when authorization-level
      ;; development is defined as the absense of a retriction to
      ;; restricted, runtime, or embedded. In principle we could
      ;; imagine that the level here is given as 'development
      ;; explicitly, but that would conflict with the check that
      ;; is made in license-1 that allows only symbols that
      ;; are given in the optional modules list to be used, and
      ;; development is not there. (And shouldn't be since bits
      ;; are scarce in that facility.)
      (let* ((authorization-level-entry
	       (assq authorization-level optional-modules-map))
	     (authorization-level-bitmask
	       (second authorization-level-entry)))

	  (setf (aref rs-array 11)
		(logxor (aref rs-array 11)
			authorization-level-bitmask))))))



;;; `Compute-tw2-code-checksum' is adapted from check-small-workspace

(defun compute-tw2-code-checksum (machine-id code1 code2 code3 code4
	                          start-date? expiration-date?
           	                  license-level)
  (let* ((keystring
	   (concatenate 'string machine-id pulse-rate-options))
	 (modularized-key
	   (mod (normalize-key-online-1 keystring)
		new-modulus)))

    (when (< code1 100) (setq code1 (+ 173 (* 477 code1)))) ; random
    (when (< code2 100) (setq code2 (+ 931 (*  73 code2))))
    (when (< code3 100) (setq code3 (+ 575 (* 637 code3))))
    (when (< code4 100) (setq code4 (+ 347 (+ 782 code4))))

    (mod
      (let* ((t1 (or start-date? 0))
	     (t2 (or expiration-date? 0))
	     (license-multiplier
	       (cond ((eq license-level 'runtime) code1)
		     ((eq license-level 'restricted) code2)
		     ((eq license-level 'embedded) code3)
		     (t 0))) ; development
	     (t3 (inner-multiply license-multiplier code1))
	     (t4 (inner-multiply license-multiplier code4)))
	
	(logxor
	  (inner-multiply modularized-key code1)
	  (inner-multiply code2 code3)
	  (inner-multiply code4 code4)
	  (inner-multiply t1 t2)
	  (inner-multiply t3 t4)))

      new-modulus)))








;;;; Computing Bridge Authorizations




;;; Bridge authorization is documented in a memo of Jon Anthony's
;;; titled "GSI Authorization"  That memo outlines the algorithums
;;; implemented below.  The names used in that memo are slightly
;;; different than the ones used here.



;;; `Compute-bridge-authorizations' is known as gencodes in Jon
;;; Anthony's specification of how these are computed.  All strings are
;;; required to met the specifications shown in that document, i.e they
;;; are all uppercase, containing only alphanumerics, period, dash, and
;;; underscore.  In Grep rexpr syntax they are:
;;;   machine-id-string   
;;;   product-string      [A-Z][~-0-9_A-Z]*
;;;   version-string      V[0-9].[0-0]  or V[0-9].[0-9]A or V[0-9].[0-9]B
;;; start-date-as-bridge-universal-date and end-date-as-bridge-universal-date
;;; are computed by bridge-universal-date below.
						;
;;; So far, 10/14/92, this spec has had two major revisions.  In revision-1 the
;;; entire version string was included in the computation.  In revision-2, "only
;;; characters up to but not including the period (".") are used in the
;;; calculation of codes"  The argument revision specifies which variant this
;;; particular bridge product utilizes

(defun compute-bridge-authorizations 
       (machine-id-string
	product-string
	version-string
	start-date-as-bridge-universal-date
	end-date-as-bridge-universal-date
	revision  ;; (member revision-1 revision-2)                                  
	) ;; --> (values c1 .. c5)
  
  ;; GENSYMCID-607: Fix licensing issues for all G2 bridges
  ;; The version adjust to "V*" for site licenses is NOT supported by bridges.
  #+ignore
  (setq version-string
	(adjust-version-if-necessary machine-id-string version-string))
	  
  (let ((prime 25173))
    (flet ((weighted
	     (string)
	     (loop with h = 0
		   for i from 0 below (length string)
		   as char = (char string i)
		   as ordinal-value-of-character = (char-code char)
		   do (setf h (+ (mod (* 16 h) (expt 2 26)) 
				 ordinal-value-of-character))
		   finally (return h))))
      (let ((weighted-machine-id (weighted machine-id-string))
	    (weighted-product (weighted product-string))
	    (weighted-version (weighted (case revision
					  (revision-1 version-string)
					  (revision-2 (subseq version-string 0 2))
					  (otherwise
					   (error "Unknown revision of compute-bridge-authorizations"))))))
	(flet ((f
		 ()
		 (let ((modulus (expt 2 23))
		       (mixer-cage-array (make-array 55)))
		   (macrolet ((mixer-cage (x) `(svref mixer-cage-array ,x)))
		     (loop 
		       for e from 0 below 55
		       do
		       (setf (mixer-cage e) prime)
		       (macrolet ((z (mod-integer weight)
				     `(when (zerop (mod e ,mod-integer))
					  (setf (mixer-cage e) (logxor (mixer-cage e) ,weight)))))
			     (z  2 weighted-machine-id)
			     (z  3 weighted-product)
			     (z  5 weighted-version)
			     (z  7 start-date-as-bridge-universal-date)
			     (z 11 end-date-as-bridge-universal-date)
			     (setf (mixer-cage e) (mod (mixer-cage e) modulus))))
		     (loop for i from 55 to 555
			   do (setf (mixer-cage (mod i 55))
				 (mod (+ (mixer-cage (mod (- i 24) 55))
					 (mixer-cage (mod (- i 55) 55)))
				      modulus)))
		     (values (mixer-cage 0) (mixer-cage 1) (mixer-cage 2) (mixer-cage 3)))))
	       (g (c1 c2 c3 c4)
		  (let ((modulus (expt 2 15))
			(value weighted-machine-id))
		    (macrolet ((step-sum 
				 (mixin)
				 `(setf value (+ (* (mod value modulus) prime) ,mixin))))
		      (step-sum 0)
		      (step-sum start-date-as-bridge-universal-date)
		      (step-sum end-date-as-bridge-universal-date)
		      (step-sum weighted-product)
		      (step-sum weighted-version)
		      (step-sum c1)
		      (step-sum c2)
		      (step-sum c3)
		      (step-sum c4)
		      value))))
	  (multiple-value-bind (c1 c2 c3 c4)
	      (f)
	    (values c1 c2 c3 c4 (g c1 c2 c3 c4))))))))



(defun machine-id-of-site-p (id-string)
  (and (> (length id-string) 9)
       (string-equal (subseq id-string 0 5) "site:")
       ;; require some non-trivial identifying content -- what appears
       ;; after the colon will show up in the Title Block as "This
       ;; software is exclusively licensed for use by xxxx"
       (not (string-equal (subseq id-string 5 9) "   "))))



;;; `Legal-machine-id-p' exists so that no one can create a site
;;; license except those few we designate. Of course we could add
;;; more stuff here if we liked, but blocking casual creation of
;;; site licenses is its raison de etre.

(defun legal-machine-id-p (machine-id)
  (not (machine-id-of-site-p machine-id)))


;;; `Adjust-version-if-necessary' is called from compute-bridge-
;;; type-authorization. Its purpose is to return the correct kind of
;;; version number when the bridge is authorized as a site license. 

(defun adjust-version-if-necessary (machine-id-string version-string)
  (if (machine-id-of-site-p machine-id-string)
      "V*"
      version-string))



;;; `bridge-universal-date' fufills the same role as Jon's routine
;;; universal_date

(defun bridge-universal-date (day month year)
  (- (encode-universal-date day month (interpret-year year))
     (encode-universal-date 1 1 1970)))



;;; `interpret-year' interprets a 1 or 2 digit year reasonably with respect to
;;; this-year?, if it's non-nil, or, if it's nil, the current time. That is,
;;; this adds the century that's no more than half a century away from the
;;; current time.
;;;
;;; This follows the Common Lisp spec for 2-digit year handling, quoted here:
;;;
;;;    if this integer is between 0 and 99, the "obvious" year is used; more
;;;    precisely, that year is assumed that is equal to the integer modulo 100
;;;    and within fifty years of the current year (inclusive backwards and
;;;    exclusive forwards). Thus, in the year 1978, year 28 is 1928 but year 27
;;;    is 2027. (Functions that return time in this format always return a full
;;;    year number.) [CLtL2, 25.4.1., p. 702]
;;;
;;; Examples:
;;;
;;; > (interpret-year 28 1978)
;;; 1928
;;; > (interpret-year 27 1978)
;;; 2027
;;; > (interpret-year 103 2000)
;;; 103
;;; > (interpret-year 2001 2001)
;;; 2001
;;; > (interpret-year 1971 2001)
;;; 1971

(defun interpret-year (year &optional this-year?)
  (if (< year 100)
      (let* ((this-year
	      (or this-year?
		  (multiple-value-bind (s mi h d mo y)
		      (decode-universal-time (get-universal-time))
		    (declare (ignore s mi h d mo))
		    y)))
	     (this-year-century
	      (* 100 (floor this-year 100)))
	     (this-2-digit-year
	      (mod this-year 100))
	     (diff (- this-2-digit-year year)))
	(+ year
	   (cond
	     ((<= diff -50)		; inclusive backwards
	      (- this-year-century 100))
	     ((> diff 50)		; exclusive forwards
	      (+ this-year-century 100))
	     (t this-year-century))))
      year))


;; Note that this function is grossly not Y2K compliant. We're
;; saved because you can't get to this point in the construction
;; of a bridge license unless your dates have been checked
;; (in LICENSE) and that check now prohibits years with fewer
;; than four characters.
;;
;; -- UPDATE:
;;
;; This just needs to interpret year in a reasonable way relative to the current
;; time.  We'll change this to the Common Lisp spec, for lack of a better one or
;; any need, and then we'll be all set forever.  (MHD 3/23/01)



;;; `test-bridge-authorizations' checks a number of input output pairs to see if 
;;; we are getting what the Jon's code got.

;(defun test-bridge-authorizations ()
;  (loop for (case-id input 
;		     output)
;	in '((ludlow ("08-00-2B-0F-9D-BD" "GSI-BASESTAR" "V1.0" 0 0) 
;		     (4014321 6223371 3067905 3585337 537026380))
;	     (action ("08-00-2B-05-1A-17" "GSI-BASESTAR" "V1.0" 0 0)
;		     (2405765 1101188 2517969 4722 172263561))
;	     (holden ("08-00-2B-0F-3D-4B" "GSI-BASESTAR" "V1.0" 0 0)
;		     (1815213 8037249 1476729 3471987 265447398))
;	     (carver ("08-00-2B-16-43-8C" "GSI-BASESTAR" "V1.0" 0 0)
;		     (2095013 1444200 1945073 6701862 468550893))
;	     (boston ("08-00-2B-23-3D-98" "GSI-BASESTAR" "V1.0" 0 0)
;		     (1661329 8200343 1669345 3414773 806710376))
;	     (boston ("08-00-2B-23-3D-98" "GSI-SETCON" "V1.1" 0 0)
;		     (1554076 7841635 1301194 3330309 79252077))
;	     (jon-1A ("11-22-33-44-55-66" "GSI-ABPLC" "V3.1B" (12 1 1991) (13 8 91))
;		     (7488445 2774670 5510661 6143328 219862098))
;	     (jon-1B ("11-22-33-44-55-66" "GSI-ABPLC" "V3.1B" (12 1 91) (12 3 1992))
;		     (8007389 3066258 6128141 6569252 230759990))
;	     (kjon    ("08-00-2B-1D-E9-02" "GSI-BASESTAR" "V1.0" (11 10 91) (11 11 91))
;		     (3667795 625473 402873 2630032 29766526))
;	     )
;	as (machine-id-string
;	     product-string
;	     version-string
;	     start-date?
;	     end-date?) = input
;	do
;	(format t "~&Trial: ~S" case-id)
;	(format t " ~A."
;		(if (equal (multiple-value-list 
;			     (compute-bridge-authorizations 
;			       machine-id-string
;			       product-string
;			       version-string
;			       (if (atom start-date?) start-date? (apply 'bridge-universal-date start-date?))
;			       (if (atom   end-date?)   end-date? (apply 'bridge-universal-date   end-date?))))
;			   output)
;		    "passed"
;		    "failed"))))








;;;; Fixing Up or Setting Up the G2.OK File


;;; Do-codes-for-all-oks-and-remove-japanese ...

;;; USUALLY COMMENTED OUT:
;;; 
;;; To be compiled in the AB Package -- most of this module is to be
;;; compiled in the User package; therefore, comment this out for saving
;;; and compiling the buffer, and just uncomment it and make the package
;;; be AB when you want to use it, if ever.  (I only needed it once on
;;; 4/18/91, but we tend to do this KIND of thing occasionally.)
;;; 
;;; (MHD 4/18/91)

;; Please move this into G2. But first, see bless-them, and other stuff in
;; SEQUENCES2.

;(defun do-codes-for-all-oks-and-remove-japanese ()
;  (loop for ok being each class-instance of 'ok
;	when (machine-id ok)
;	  do (setf (authorized-products ok)
;		   (delq 'japanese (authorized-products ok)))
;	     (multiple-value-bind (code-1 code-2 code-3 code-4 code-5)
;		 (cl-user::make-ok
;		   (machine-id ok) 3
;		   (loop for product-in-ab-package in (authorized-products ok)
;			 collect (intern (symbol-name product-in-ab-package) 'cl-user)))
;	       (setf (code-1 ok) code-1)
;	       (setf (code-2 ok) code-2)
;	       (setf (code-3 ok) code-3)
;	       (setf (code-4 ok) code-4)
;	       (setf (code-5 ok) code-5))))




;; In CL-User Package:


;; This file is not part of G2 or used in conjunction with G2. It is designed to
;; compile independently. There is #+development stuff in G2 that does this sort
;; of thing. Please see me. -ML- July 16, 1991



;(defun fill-in-ok-codes (ok)
;  (cond
;    ((null (ab::machine-id ok))
;     "OK ~a has no machine id; it must be filled in before calling this." ok)
;    (t 
;     (multiple-value-bind (code-1 code-2 code-3 code-4 code-5)
;	 (cl-user::make-ok
;	   (ab::machine-id ok)
;	   (if (ab::system-version-greater-p
;		 (ab::system-version 'ab::ab)
;		 '#.(ab::make-system-version  2 1))
;	       3
;	       t)
;	   (ab::authorized-products ok))
;       (ab::change-slot-value ok 'ab::code-1 code-1)
;       (ab::change-slot-value ok 'ab::code-2 code-2)
;       (ab::change-slot-value ok 'ab::code-3 code-3)
;       (ab::change-slot-value ok 'ab::code-4 code-4)
;       (ab::change-slot-value ok 'ab::code-5 code-5)))))


;ab::
;(defun print-ok-info (ok)
;  (terpri)
;  (format t "~a~20T~a~42t~a~%"
;	  (or (name-or-names-for-frame ok) "none")
;	  (machine-id ok)
;	  (name-or-names-for-frame (superblock? ok)))
;  (loop with products = (authorized-products ok)
;	for (product . rest) on products
;	initially (when products (format t "     "))
;	doing
;	(format t "~a " product)
;	finally
;	(when products (format t "~%")))
;  (format t "     ~d  ~d  ~d  ~d  ~d~%"
;	  (code-1 ok) (code-2 ok) (code-3 ok) (code-4 ok) (code-5 ok))
;  (loop with packages = (authorized-kb-packages ok)
;	for (pk x y z) in packages
;	doing
;	(format t "     ~a~15T~d  ~d  ~d~%" pk x y z))

;  )



;ab::(defun name-or-names-for-frame-function (ok) (name-or-names-for-frame ok))

;ab::
;(defun print-all-oks ()
;  (loop with ok-list =
;	(loop for ok being each class-instance of 'ok collect ok)
;	with ordered-list =
;	(sort ok-list #'string< :key #'name-or-names-for-frame-function)
;	for ok in ordered-list
;	do (print-ok-info ok)))


;  (loop for ok being each class-instance of 'ok do (print-ok-info ok)))






;ab::
;(defun print-oks-to-file (pathname)
;  (with-open-file (*standard-output* pathname
;				     :direction :output
;				     :if-exists :new-version
;				     :if-does-not-exist :create)
;    (print-all-oks)))





;;;; Testing

;;; As of 2/3/95, these were some expected results:
;;;
;;;   (compute-tw-codes "723397eb" nil nil nil nil nil nil nil nil 4.0)
;;;   =>  2269074 7179848 4314855 7200787 379584
;;;
;;;   which wants a line in the tw.ok file like
;;;
;;;     isr 723397eb  2269074 7179848 4314855 7200787 379584
;;;
;;;   (optionally, the word DEVELOPMENT can appear after the 5 codes).
;;;   
;;;
;;;   (compute-tw-codes "723397eb" nil nil nil nil nil nil '(runtime-option) nil 4.0)
;;;   => 2269074 7215688 4314855 7200787 349725
;;;
;;;   which wants a line in the tw.ok file like
;;;
;;;   isr 723397eb  2269074 7215688 4314855 7200787 349725 runtime
;;;
;;;   
;;;   (make-ok "723397eb" 4 '(online gspan)  nil nil 10 0)
;;;   =>  37614 59965 9058 10079 688782
;;;
;;;   which wants the OK object filled out with ONLINE and GSPAN as the optional
;;;   authorized modules, the machine-id of "723397eb", and the 5 codes as
;;;   shown.


;;; To construct a GSI OK file for the PI bridge for the bundle, to be
;;; placed in /home/development/installers/release-files/pi-gsi.ok :

;;;   (compute-bridge-authorizations machine-id-string product-string
;;;      version-string start-date end-date revision)

;;;   (cl-user::compute-bridge-authorizations "GENSYM SITE:GENSYM-SOFTWARE"
;;;      "G2-PI" "V*" 0 0 'cl-user::revision-2)

;;; which produces

;;; gensym site:gensym-software G2-PI         V* 5645891 1815987 8154993 6731432 717491087

;;; - jpg 1/29/03

;;; Please note that this uses V* which means it can be used with 
;;; *any* version of G2-PI! - jpg 5/10/04
