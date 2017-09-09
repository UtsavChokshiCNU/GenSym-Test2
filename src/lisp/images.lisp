;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module IMAGES

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Fred White


(declare-forward-reference drawing-to-printer-p variable) ; TELESTUBS
(declare-forward-reference note-progress-on-window function) ; TELESTUBS


;;;; Rotations and reflections



(defparameter inverse-reflection-and-rotation
  '((clockwise-90 . clockwise-270)
    (clockwise-180 . clockwise-180)
    (clockwise-270 . clockwise-90)))


(def-substitution-macro fast-invert-reflection-and-rotation (reflection-and-rotation)
  (or (cdr (assq reflection-and-rotation inverse-reflection-and-rotation))
      reflection-and-rotation))



;;; The function `rotated-by-90-p' is used in a number of places to decide
;;; whether to swap width and height.

(defmacro rotated-by-90-p-macro (reflection-and-rotation)
  `(memq ,reflection-and-rotation
         '(clockwise-90 reflected-clockwise-90 clockwise-270 reflected-clockwise-270)))

(defun rotated-by-90-p (reflection-and-rotation)
  (rotated-by-90-p-macro reflection-and-rotation))

;; Consider making this a macro and using it in the draw function for entity.


(defmacro identity-reflection-and-rotation-p (reflection-and-rotation)
  `(or (null ,reflection-and-rotation)
       (eq ,reflection-and-rotation 'normal)))





;;; The macro `orient-points-for-icon' transforms the given x and y
;;; points according to the reflection-and-rotation?.  x-and-y-point-variables
;;; should be a list of the form
;;;
;;;   ( {x y} )
;;;
;;; where each x and y (a) is a setf'able place, (b) may be evaluated either
;;; zero times or one time, and (c) starts out bound to appropriate x and
;;; y values.  Each x and y will be set if necessary as appropropriate based
;;; on reflection-and-rotation?, width, and height.  Reflection-and-rotation?
;;; may be either one of the eight standard reflection/rotation symbols or
;;; nil (meaning normal).  All arithmetic is done in terms of workspace
;;; coordinates (i.e. -w).

;;; Reflection-and-rotation?, width, and height are evaluated once and only
;;; once, in order, before any point variables are set or evaluated.

(defmacro orient-points-for-icon
          (reflection-and-rotation? width height
           . x-and-y-point-variables)
  `(let ((reflection-and-rotation? ,reflection-and-rotation?)
         (width ,width)
         (height ,height))
     (if reflection-and-rotation?
         (case reflection-and-rotation?
           (normal)
           (clockwise-90
            ,@(loop for (x y) on x-and-y-point-variables by 'cddr
                    collect `(psetf ,x (-w height ,y) ,y ,x)))
           (clockwise-270
            ,@(loop for (x y) on x-and-y-point-variables by 'cddr
                    collect `(psetf ,x ,y ,y (-w width ,x))))
           (reflected-clockwise-270
            ,@(loop for (x y) on x-and-y-point-variables by 'cddr
                    collect `(psetf ,x ,y ,y ,x)))
           (clockwise-180
            ,@(loop for (x y) on x-and-y-point-variables by 'cddr
                    collect `(setf ,x (-w width ,x))
                    collect `(setf ,y (-w height ,y))))
           (reflected-clockwise-90
            ,@(loop for (x y) on x-and-y-point-variables by 'cddr
                    collect `(psetf ,x (-w height ,y) ,y (-w width ,x))))
           (reflected
            ,@(loop for (x nil) on x-and-y-point-variables by 'cddr
                    collect `(setf ,x (-w width ,x))))
           (reflected-clockwise-180
            ,@(loop for (nil y) on x-and-y-point-variables by 'cddr
                    collect `(setf ,y (-w height ,y))))))))




;;;; Shredded Rasters




;;; A `shredded-raster' is the lisp representation of an image.  It is an array of
;;; byte vectors, one byte vector per scan line in the image.

(define-structure shredded-raster ()
  (:constructor make-shredded-raster-1)
  (:reclaimer reclaim-shredded-raster-1)
  (:managed t)
  (:conc-name t)
  (:predicate shredded-raster-p)
  width                                        ; Width in pixels (may be 1, 3, or 1/8 bytes/pixel)
  height                                ; Height in pixels
  height-received                        ; May be < height
  depth                                        ; Currently allowed: 1, 8, or 24 (bits/pixel)
  ncolors                                ; The length of the color-map array.
  color-map                                ; Array of packed RGB values, one per pixel value.
  buffers                                ; Managed-array of byte-vectors, one per scan line.
  transparent-color-index
  bytes-per-line                        ; Cached value
  format)                                ; File format of original data

;; This should be merged with the image-data structure, which came later.

;; RGB pixels are stored in three adjacent bytes of the byte vector, in that order.

(defmacro shredded-raster-buffer (shredded-raster row)
  `(managed-svref (shredded-raster-buffers ,shredded-raster)
                  ,row))

(defun ensure-shredded-raster-buffer (shredded-raster row)
  (or (shredded-raster-buffer shredded-raster row)
      (setf (shredded-raster-buffer shredded-raster row)
            (allocate-byte-vector (shredded-raster-bytes-per-line shredded-raster)))))


(defun shredded-raster-p-function (thing)
  (shredded-raster-p thing))


;;; The substitution-macro `rgb-pixel' returns a 24-bit pixel stored
;;; starting at the given index in the byte vector.

(def-substitution-macro rgb-pixel (byte-vector index)
  (logiorf (ashf (byte-vector-aref byte-vector index) 16)       ; R
           (ashf (byte-vector-aref byte-vector (+f index 1)) 8) ; G
           (byte-vector-aref byte-vector (+f index 2))))        ; B
;; TODO: reverse the RGB packing order here to be what Win32 wants.

;; setf-able
(defmacro shredded-raster-ref-8 (shredded-raster x y)
  `(byte-vector-aref (shredded-raster-buffer ,shredded-raster ,y) ,x))

(defmacro shredded-raster-ref-1 (shredded-raster x y)
  `(logandf 1 (ashf (byte-vector-aref (shredded-raster-buffer ,shredded-raster ,y) (ashf ,x -3))
                    (-f (logandf ,x 7)))))

(defmacro shredded-raster-ref-24 (shredded-raster x y)
  (avoiding-variable-capture (shredded-raster x y &aux buffer)
    `(let ((,buffer (shredded-raster-buffer ,shredded-raster ,y)))
       (rgb-pixel ,buffer (*f 3 ,x)))))

(defmacro shredded-raster-set-24 (shredded-raster x y rgb)
  (avoiding-variable-capture (shredded-raster x y rgb &aux buffer index)
    `(let ((,buffer (shredded-raster-buffer ,shredded-raster ,y))
           (,index (*f 3 ,x)))
       (setf (byte-vector-aref ,buffer ,index) (logandf (ashf rgb -16) 255)
             (byte-vector-aref ,buffer (+f ,index 1)) (logandf (ashf rgb -8) 255)
             (byte-vector-aref ,buffer (+f ,index 2)) (logandf rgb 255)))))

(defmacro shredded-raster-ref (shredded-raster x y)
  (avoiding-variable-capture (shredded-raster x y)
    `(fixnum-case (shredded-raster-depth ,shredded-raster)
       (24 (shredded-raster-ref-24 ,shredded-raster ,x ,y))
       (8 (shredded-raster-ref-8 ,shredded-raster ,x ,y))
       (1 (shredded-raster-ref-1 ,shredded-raster ,x ,y)))))

(defmacro shredded-raster-set (shredded-raster x y new-value)
  (avoiding-variable-capture (shredded-raster x y new-value &aux buffer index mask byte)
    `(fixnum-case (shredded-raster-depth ,shredded-raster)
       (24
        (shredded-raster-set-24 ,shredded-raster ,x ,y ,new-value))
       (8
        (setf (shredded-raster-ref-8 ,shredded-raster ,x ,y) ,new-value))
       (1
        ;; Hopefully, these shenanigans translate nicely.
        (let* ((,buffer (shredded-raster-buffer ,shredded-raster ,y))
               (,index (ashf ,x -3))
               (,mask (ashf (logandf ,x 7)))
               (,byte (byte-vector-aref ,buffer ,index)))
          (setf (byte-vector-aref ,buffer ,index)
                (if (=f ,new-value 0)
                    (logandf ,byte (lognotf ,mask))
                    (logiorf ,byte ,mask))))))))

(defsetf shredded-raster-ref shredded-raster-set)

#+development
(def-development-printer print-shredded-raster (raster &optional (stream *standard-output*))
  (when (shredded-raster-p raster)
    (printing-random-object (raster stream)
      (format stream "Shredded-Raster ~dx~d (~d)"
              (shredded-raster-width raster)
              (shredded-raster-height raster)
              (shredded-raster-depth raster)))
    raster))


;;; The macro `do-raster' runs body for each pixel in the raster in the pixel
;;; region [left,right) x [top,bottom).  Within the body, the pixel, rgb value,
;;; and x and y coordinates of the pixel can be referenced via the supplied
;;; symbols.

(defmacro do-raster ((pixel rgb x y raster &optional left top right bottom) &body body)
  `(do-raster-rows (,raster :y ,y :left ,left :top ,top :right ,right :bottom ,bottom)
    (do-row-pixels (,pixel ,rgb :x ,x)
      ,@body)))


;;; The macro `do-raster-rows' loops over each row (scanline) in the raster from
;;; top to bottom. In the body BUFFER is bound to the row buffer and Y to the
;;; row index.  Within the body, do-row-pixels can be used to loop over the
;;; pixel and RGB values in the row.

(defmacro do-raster-rows ((raster &key (buffer 'buffer)
                                  (y 'y)
                                  (left 0)
                                  (top 0)
                                  (bottom `(shredded-raster-height ,raster))
                                  (right  `(shredded-raster-width ,raster)))
                          &body body)
  (avoiding-variable-capture (raster &aux depth color-map index-start left* right*)
    `(let* ((,depth (shredded-raster-depth ,raster))
            (,color-map (shredded-raster-color-map ,raster))
            (,left* ,left)
            (,right* ,right)
            (,index-start (if (=f ,depth 24) (*f 3 ,left*) 0)))
       (declare (type fixnum ,depth ,left* ,right* ,index-start))
       ;; Use these here in case body does not use do-row-pixels.
        ,depth ,color-map ,left* ,right* ,index-start
       (macrolet ((do-row-pixels ((pixel rgb &key (index 'index) (x 'x))
                                  &body body)
                    ;; todo: move depth case outside of loop.
                    ;; means replicating body!
                    `(loop with ,pixel
                           with ,rgb
                           with ,index = ,',index-start
                           for ,x fixnum from ,',left* below ,',right* doing
                       (case ,',depth
                         (24
                          (setq ,pixel (rgb-pixel ,',buffer ,index)
                                ,rgb ,pixel
                                ,index (+f ,index 3)))
                         (8
                          (setq ,pixel (byte-vector-aref ,',buffer ,x)
                                ,rgb   (managed-svref ,',color-map ,pixel)))
                         (1
                          (setq ,pixel (if (logbitpf (logandf ,x 7)
                                                     (byte-vector-aref ,',buffer (ashf ,x -3)))
                                           1 0)
                                ,rgb (managed-svref ,',color-map ,pixel))))
                       (progn ,@body))))
         (loop for ,y fixnum from ,top below ,bottom
               for ,buffer = (shredded-raster-buffer ,raster ,y)
               doing
           (progn
             ,@body))))))


;;; The substitution-macro `unaligned-bytes-per-scan-line' computes the number
;;; of bytes per scan line as data is stored in shredded rasters.  It is simply
;;; the width in bits rounded up to the nearest whole number of bytes.

(def-substitution-macro unaligned-bytes-per-scan-line (width-in-pixels bits-per-pixel)
  (ashf (+f (*f width-in-pixels bits-per-pixel) 7) -3))

#+development
(defun print-raster (raster)
  (do-raster-rows (raster)
    (do-row-pixels (pixel rgb)
      (write-string (case pixel
                      (0 ".")
                      (1 "*")
                      (t (format nil "~d" (mod pixel 10))))))
    (terpri))
  raster)

#+development
(defun print-raster-bytes (raster)
  (let ((bytes-per-line
          (unaligned-bytes-per-scan-line
            (shredded-raster-width raster)
            (shredded-raster-depth raster))))
    (loop for y below (shredded-raster-height raster)
          for buffer = (shredded-raster-buffer raster y)
          doing
      (format t "~2d:" y)
      (loop for x below bytes-per-line doing
        (format t " ~2,'0x" (byte-vector-aref buffer x)))
      (format t "  ")
      (loop for x below bytes-per-line doing
        (format t " ~2,'0x" (reverse-bits-in-byte (byte-vector-aref buffer x))))
      (terpri))
    raster))





;;; The function `allocate-shredded-raster' allocates a raster with HEIGHT scan
;;; lines of WIDTH pixels each.  Pixels are of size DEPTH bits (1, 8, or 24).  If
;;; allocate-scan-line-buffers? is T, then we also allocate the height scan-line
;;; buffers.

(defun allocate-shredded-raster (width height depth ncolors color-map
                                       &optional allocate-scan-line-buffers?
                                       (transparent-color-index -1))
  (let ((shredded-raster (make-shredded-raster-1))
        (buffers (allocate-managed-array height))
        (bytes-per-line (unaligned-bytes-per-scan-line width depth)))
    (setf (shredded-raster-width shredded-raster) width
          (shredded-raster-height shredded-raster) height
          (shredded-raster-depth shredded-raster) depth
          (shredded-raster-ncolors shredded-raster) ncolors
          (shredded-raster-color-map shredded-raster) color-map
          (shredded-raster-transparent-color-index shredded-raster) transparent-color-index
          (shredded-raster-bytes-per-line shredded-raster) bytes-per-line
          (shredded-raster-buffers shredded-raster) buffers)
    ;; Note: byte vectors have a minimum length of 16 (= 128 bits).  So, a
    ;; large number of small images waste considerable space.
    (when allocate-scan-line-buffers?
      (loop for i below height doing
        (setf (shredded-raster-buffer shredded-raster i) (allocate-byte-vector bytes-per-line))))
    shredded-raster))


(defun-void reclaim-shredded-raster (shredded-raster)
  #+development
  (unless (shredded-raster-p shredded-raster)
    (error "Attempted to reclaim ~a as a shredded-raster." shredded-raster))

  ;; If the image was not fully downloaded, it may not have its full set of
  ;; byte vectors.  Note that this change is not strictly needed anyways since
  ;; interruptable image downloading has been removed from 4r0.  It was
  ;; hand-patched into the C code for G2 and TW.  -fmw, 6/23/95
  (loop for i below (shredded-raster-height shredded-raster)
        as buffer? = (shredded-raster-buffer shredded-raster i)
        doing
    (when buffer?
      (reclaim-byte-vector buffer?)))

  (when (shredded-raster-color-map shredded-raster)
    (reclaim-managed-array (shredded-raster-color-map shredded-raster))
    (setf (shredded-raster-color-map shredded-raster) nil))

  (when (shredded-raster-buffers shredded-raster)
    (reclaim-managed-array (shredded-raster-buffers shredded-raster)))
  (reclaim-shredded-raster-1 shredded-raster))

;; See `compute-tile-size-given-required-area' and minimum-tile-size-for-icons.



;;; This single large byte-vector is used to buffer an entire 8bit raster tile
;;; (400x400 = 160KB), before handing it off to X. See
;;; list-of-regular-raster-sizes.

;;; It's just a temporary buffer, reused for each drawing operation.  The
;;; persistant caches of image renderings are the actual X pixmaps themselves
;;; (or the windows equivalents).

(defvar large-byte-vector nil)

;; TODO: don't allocate this one if we already have the really-large one.
(defun large-byte-vector ()
  (or large-byte-vector
      (setq large-byte-vector
            (let ((length (squaref largest-regular-raster-size)))
              (allocate-byte-vector-internal
                length
                nil)))))

(defvar really-large-byte-vector nil)

;;; The function `really-large-byte-vector' returns a byte vector big enough
;;; for the largest RGB tile (400x400x3 = 480KB)

(defun really-large-byte-vector ()
  (or really-large-byte-vector
      (setq really-large-byte-vector
            (let ((length (*f (squaref largest-regular-raster-size)
                              3)))
              (allocate-byte-vector-internal
                length
                nil)))))

;; Are these in region 3?  Are their sizes included in the counts?


;;;; Image file progress notes


;;; The function `note-image-progress' updates the local progress bar for a
;;; newly arrived scan for an image of given height.

;;; Operation is SEND (G2 sending over ICP), RECEIVE (TW receiving over ICP), or
;;; READ (TW or G2 reading locally). Note that G2 has no progress bar currently.

(defun note-image-progress (gensym-window? operation pathname row height)
  ;; system-window is NIL when reading a pane background image!
  (when (and gensym-window?
             (memq operation '(receive read))) ; Do only for TW for now.
    (cond ((>=f row (1-f height))        ; Finished?
           (note-progress-on-window gensym-window? #w"" -1)) ; Hide progress bar
          ((=f 0 (logandf row 15))      ; Update only every 16 rows (arb).
           (let* ((doneness (compute-percentage row (1-f height)))
                  (message (twith-output-to-wide-string
                             (tformat "~a ~a ~d%"
                                      (case operation
                                        (send "Sending")
                                        (receive "Receiving")
                                        (read "Reading")
                                        (t "Processing"))
                                      pathname
                                      doneness))))
             (note-progress-on-window gensym-window? message doneness)
             (reclaim-wide-string message))))))

(defun compute-percentage (fixnum-numerator fixnum-denominator)
  (with-temporary-gensym-float-creation compute-percentage
    (let ((value (/e (*e (coerce-to-gensym-float 100) (coerce-to-gensym-float fixnum-numerator))
                     (coerce-to-gensym-float
                       (if (=f fixnum-denominator 0) 1 fixnum-denominator)))))
      (cond ((<e value 0.0) 0)
            ((>e value 100.0) 100)
            (t (rounde-first value))))))


;;;; Image file reading


;; This actually returns a G2pointer to the stream, or integer <0 for an error.
(def-gensym-c-function c-open-image-stream (:pointer "g2ext_open_image_stream")
  ((:string pathname)
   (:string error)
   (:fixnum-int errlen)))

(def-gensym-c-function c-read-image-row (:fixnum-int "g2ext_read_image_row")
  ((:pointer stream)
   (:byte-vector buffer)
   (:fixnum-int buflen)))

(def-gensym-c-function c-close-image-stream (:pointer "g2ext_close_image_stream")
  ((:pointer stream)))


(def-gensym-c-function c-image-stream-format (:fixnum-int "g2ext_image_stream_format")
  ((:pointer stream)))

(defun image-stream-format (stream)
  ;; Keep in sync with the #defines in ext/c/images.c
  (nth (c-image-stream-format stream) '(unknown xbm gif pbm ppm jpeg png bmp ico cur xpm)))


(def-gensym-c-function c-image-stream-height (:fixnum-int "g2ext_image_stream_height")
  ((:pointer stream)))

(def-gensym-c-function c-image-stream-width (:fixnum-int "g2ext_image_stream_width")
  ((:pointer stream)))

(def-gensym-c-function c-image-stream-depth (:fixnum-int "g2ext_image_stream_depth")
  ((:pointer stream)))

;; Unused
(def-gensym-c-function c-image-stream-size (:fixnum-int "g2ext_image_stream_size")
  ((:pointer stream)))

(def-gensym-c-function c-image-stream-ncolors (:fixnum-int "g2ext_image_stream_ncolors")
  ((:pointer stream)))

(def-gensym-c-function c-image-stream-color-map (:fixnum-int "g2ext_image_stream_color_map")
  ((:pointer stream)
   (:fixnum-int index)))

(def-gensym-c-function c-image-stream-transparentindex (:fixnum-int "g2ext_image_stream_transparentindex")
  ((:pointer stream)))

(def-gensym-c-function reverse-bits-in-byte (:fixnum-int "g2ext_reverse_bits_in_byte")
  ((:fixnum-int byte-value)))

(def-gensym-c-function c-image-stream-error ; Returns error code and error message(s)
    (:fixnum-int "g2ext_image_stream_error")
  ((:pointer stream)
   (:string string)
   (:fixnum-int bufsize)))


;;; The function `get-images-error-message' returns a newly consed gensym string
;;; with the error messages associated with the given image-string.  If there were
;;; no errors, NIL is returned.

(defun get-images-error-message (image-stream)
  (let* ((string (obtain-simple-gensym-string 200))
         (error-code (c-image-stream-error image-stream string 200)))
    (unless (=f error-code 0)
      (prog1 (copy-null-terminated-string-as-gensym-string string)
        (reclaim-gensym-string string)))))


(def-substitution-macro fill-byte-vector (byte-vector value)
  (loop for i below (byte-vector-length byte-vector) doing
    (setf (byte-vector-aref byte-vector i) value)))



;;; The defparameter `maximum-size-of-images' is the maximum width in BYTES,
;;; and the max height in scan lines. 65536 is the max byte vector length.  So
;;; we permit full color (24 bit) images up to 21845x21845 pixels.

(defparameter maximum-size-of-images 65536)

;; Actually, maximum-byte-vector-length is now 131072, not that we'd want to
;; allow images of that size. -fmw, 1/7/02


(defparameter read-raster-error-string (obtain-simple-gensym-string 80))


;;; The function `read-raster' returns either a newly created shredded-raster
;;; instance containing the image data from pathname, or a newly consed text
;;; string with an error message.  The format of the image file is guessed
;;; automatically.

(defun read-raster (ascii-pathname &optional header-only?)
  (let ((stream (c-open-image-stream ascii-pathname read-raster-error-string 80))
        (y 0)
        raster width height depth bytes-per-line ncolors
        transparent-color-index color-map)
    (declare (type fixnum y))
    (cond ((< stream 0)
           (copy-null-terminated-string-as-text-string read-raster-error-string))
          ((progn
             (setq width (c-image-stream-width stream)
                   height (c-image-stream-height stream)
                   depth (c-image-stream-depth stream)
                   bytes-per-line (unaligned-bytes-per-scan-line width depth)
                   ncolors (c-image-stream-ncolors stream)
                   transparent-color-index (c-image-stream-transparentindex stream))
             (or (>f bytes-per-line maximum-size-of-images)
                 (>f height maximum-size-of-images)))
           (copy-text-string #w"Image is too large."))
          (t
           (note-image-progress system-window 'read ascii-pathname 0 height)
           (setq color-map (if (>f ncolors 0)
                               (allocate-managed-array ncolors)
                               (allocate-managed-array 2))
                 raster (allocate-shredded-raster width height depth ncolors color-map nil
                                                  transparent-color-index))
           (setf (shredded-raster-format raster) (image-stream-format stream))

           ;; Read the color map, if any.
           (cond ((>f ncolors 0)
                  (loop for i below ncolors doing
                    (setf (managed-svref color-map i) (c-image-stream-color-map stream i))))
                 (t
                  ;; Assume pure bitmaps (XBM) are 1=black, 0=white.
                  (setf (managed-svref color-map 0) #xffffff
                        (managed-svref color-map 1) #x000000)))

           ;; Read the scanlines.
           (unless header-only?
             (loop while (<f y height)
                   as buffer = (ensure-shredded-raster-buffer raster y)
                   as n = (c-read-image-row stream buffer (byte-vector-length buffer))
                   ;; (<= n 0) here means a short read.
                   while (>f n 0)
                   doing
               (note-image-progress system-window 'read ascii-pathname y height)
               (incff y))

             ;; Fill missing rows with some random color.
             ;; Note that the IJG JPEG reader does this for us.
             (loop while (<f y height)
                   as buffer = (ensure-shredded-raster-buffer raster y)
                   doing
               (fill-byte-vector buffer 0)
               (note-image-progress system-window 'read ascii-pathname y height)
               (incff y)))
           (c-close-image-stream stream)
           raster))))

;; TODO: File progress display.
;; TODO: to avoid caching entire image twice, read directly into pixmap tiles.


;;;; Color mapping







;; TODO: Store the way X wants them, BGR??

(def-substitution-macro red-part-of-rgb (rgb)
  (logandf 255 (ashf rgb -16)))

(def-substitution-macro green-part-of-rgb (rgb)
  (logandf 255 (ashf rgb -8)))

(def-substitution-macro blue-part-of-rgb (rgb)
  (logandf 255 rgb))

(def-substitution-macro reverse-rgb-bits (rgb)
  (+f (ashf (blue-part-of-rgb rgb) 16)
      (logandf (ashf 255 8) rgb)  ;; keep the 8 green bits the same
      (red-part-of-rgb rgb)))



(defparameter max-distance-to-gray 0)
; (defparameter max-distance-to-standard-color 0)
; (defparameter max-distance-to-new-color 0)


(def-substitution-macro gray-color-p (red green blue)
  (<=f (+f (absf (-f red green))
           (absf (-f green blue))
           (absf (-f red blue)))
       max-distance-to-gray))


;;; `image-palette-is-gray-p'

(defun-simple image-palette-is-gray-p (palette)
  (memq-p-macro palette '(standard-grays extended-grays custom-grays)))



;;; The function `map-to-closest-color-value' returns a pixel value to use
;;; to render the given color on the given window.

(defun map-to-closest-color-value (gensym-window rgb)
  (let* ((red (red-part-of-rgb rgb))
         (green (green-part-of-rgb rgb))
         (blue (blue-part-of-rgb rgb))
         (palette (image-palette-of-gensym-window gensym-window))
         (gray? (or (image-palette-is-gray-p palette)
                    (gray-color-p red green blue)))
         (extended-color-entry? nil))

    (case palette
      (black-and-white
       (if (>=f (intensity-of-color red green blue) black-threshold-in-color-intensity)
           (map-to-color-value 'white)
           (map-to-color-value 'black)))

      ((standard-grays standard-colors)
       (multiple-value-bind (standard-color-entry error)
           (find-nearest-color standard-gensym-color-alist red green blue gray?)
         (declare (ignore error))
         (map-to-color-value (first standard-color-entry))))


      ((extended-grays extended-colors custom-grays custom-colors)
       (multiple-value-bind (standard-color-entry error)
           (find-nearest-color standard-gensym-color-alist red green blue gray?)

         (cond ((=f error 0)
                (map-to-color-value (first standard-color-entry)))
               ((null (setq extended-color-entry?
                            (find-nearest-color
                              (additional-colors-allocated-for-window gensym-window)
                              red green blue gray?)))
                (map-to-color-value (first standard-color-entry)))
               (t
                ;; For this alist, the car is already a pixel-value.
                (first extended-color-entry?))))))))


#+development
(defun print-cmap (colormap)
  (loop for i below (managed-array-length colormap)
        as rgb = (managed-svref colormap i)
        do (format t "~3d ~6x red ~2x green ~2x blue ~2x~%"
                   i rgb (red-part-of-rgb rgb) (green-part-of-rgb rgb) (blue-part-of-rgb rgb)))
  colormap)


;;;; Extended Palettes



;;; The `extended palettes' are FIXED lists of additional colors we may
;;; allocate for image display.  The important point is that they are fixed,
;;; and do not depend on the image we are displaying.  Thus, all of the images
;;; in a KB have equal rights for colors.  This is in contrast to custom
;;; palettes, which are tailored for some specific image we want to display,
;;; thus that image potentially looks better than any other image in the KB.

(def-concept extended-palette)

;; The standard grays are (all 7 of them):
;; ((BLACK . 0) (DIM-GRAY . 84) (DARK-GRAY . 128) (GRAY . 192)
;; (LIGHT-GRAY . 211) (EXTRA-LIGHT-GRAY . 229) (WHITE . 255))



(def-substitution-macro gray-in-color-alist-p (gray alist)
  (loop for entry in alist
        as (color r g b) = entry
        when (=f gray r g b)
          return entry))

(def-substitution-macro gray-is-already-allocated-for-gensym-window-p (gensym-window gray)
  (or (gray-in-color-alist-p gray standard-gensym-color-alist)
      (gray-in-color-alist-p gray (additional-colors-allocated-for-window gensym-window))))


;;; The function `allocate-extended-gray-palette' allocates the extended grays
;;; by sweeping over the spectrum for increasing values of nbits of gray, until
;;; no more pixels can be allocated.

(defun allocate-extended-gray-palette (gensym-window)
  (allocate-extended-gray-palette-1
    gensym-window
    number-of-bits-of-gray-in-the-extended-gray-palette))


(defun allocate-extended-gray-palette-1 (gensym-window number-of-bits-of-gray)
  (let ((max-pixel 256))
    (block outer-loop
      (loop for nbits from 1 to number-of-bits-of-gray
            as step = (floorf-positive max-pixel 2) then (floorf-positive step 2)
            doing
        (loop for gray from 0 by step below max-pixel doing
          (unless (gray-is-already-allocated-for-gensym-window-p gensym-window gray)
            (let ((pixel? (allocate-new-color-for-gensym-window gensym-window gray gray gray)))
              (unless pixel?
                (return-from outer-loop)))))))))

;; Should we avoid using up all of the colors remaining in the X color map?
;; G2 3.0 does not worry about it.  If there are less than 63 left, it uses 'em all.




;;; The `extended color palette' contains all combinations of these intensities
;;; for each of red, green, and blue, which gives us 5^3 = 125 possible new
;;; colors.  We skip any color which is already in the standard palette, within
;;; some small tolerance. We also try to get a decent set of grays.  So the
;;; total size of this palette ends up being 118.  We allocate the colors in
;;; some random order to attempt to cover the color space uniformly no matter at
;;; what point we run out of color map entries.

(defparameter color-intensities-for-extended-color-palette '(50 100 150 200 255))


;;; The function `allocate-extended-color-palette' allocates a carefully selected
;;; set of N additional colors which are optimal for displaying any GIF image
;;; which has ever been, or ever will be, created.  Gee, how is this possible in
;;; only a dozen lines of code?

(defun allocate-extended-color-palette (gensym-window)
  (let ((intensities color-intensities-for-extended-color-palette)
        (standard-alist standard-gensym-color-alist)
        (maximum-distance-to-standard-color 10))
    (block outer-loop
      (loop for red in intensities doing
        (loop for green in intensities doing
          (loop for blue in intensities doing
            (multiple-value-bind (entry error)
                (find-nearest-color standard-alist red green blue nil)
              (declare (ignore entry))
              (when (>f error maximum-distance-to-standard-color)
                (let ((pixel? (allocate-new-color-for-gensym-window
                                gensym-window red green blue)))
                  (when (null pixel?)
                    (return-from outer-loop))))))))

      ;; Add 32 grays, if we can.
      (allocate-extended-gray-palette-1 gensym-window 5))))

;; I'm not searching in the optimal order, like I should.




;;; The function `allocate-custom-palette' allocates a palette from the colors
;;; in the given color map.  If the color-map is nil, then we do nothing, which
;;; effectively means we revert to standard colors.  If gray? is true, then we
;;; project each color to gray before allocating.

(defun allocate-custom-palette (gensym-window color-map? gray?)
  (let ((maximum-distance-to-standard-color 5)
        (number-of-colors-allocated 0))
    (when color-map?
      (loop for i below (managed-array-length color-map?)
            as rgb = (managed-svref color-map? i)
            as red = (red-part-of-rgb rgb)
            as green = (green-part-of-rgb rgb)
            as blue = (blue-part-of-rgb rgb)
            as gray = (intensity-of-color red green blue)
            doing
        (multiple-value-bind (entry error)
            (find-nearest-color standard-gensym-color-alist red green blue gray?)
          (declare (ignore entry))
          (when (>f error maximum-distance-to-standard-color)
            (let ((pixel? (if gray?
                              (allocate-new-color-for-gensym-window
                                gensym-window gray gray gray)
                              (allocate-new-color-for-gensym-window
                                gensym-window red green blue))))
              (cond ((null pixel?)
                     (return))
                    (t
                     (incff number-of-colors-allocated))))))))
    number-of-colors-allocated))





;;; The function `allocate-new-color-for-gensym-window' tries to allocate a new
;;; pixel value for the given color on the given window.  If successful, we
;;; remember the color->pixel mapping in the
;;; additional-colors-allocated-for-window alist on the window.

(defun allocate-new-color-for-gensym-window (gensym-window red green blue)
  (let ((pixel? (get-x11-pixel-value-from-rgb
                  (native-window? gensym-window) red green blue t)))
    (when pixel?
      (gensym-push (gensym-list pixel? red green blue)
                   (additional-colors-allocated-for-window gensym-window))
      pixel?)))

;; Should know when to stop bothering to try to allocate more.


;;; The function `clear-all-extended-colors-for-window' deallocated all of the
;;; additional colors for the given window.. This puts us back to the standard
;;; Gensym palette.

(defun clear-all-extended-colors-for-window (gensym-window)
  (when (native-window? gensym-window)
    (let ((pixels (additional-colors-allocated-for-window gensym-window)))

      (when pixels
        (c-x11-free-extended-colors (native-window? gensym-window))

        (setf (additional-colors-allocated-for-window gensym-window) nil)
        (reclaim-gensym-tree pixels)))))




;;; The substitution-macro `rgb-to-gray' converts a packed RGB value into an
;;; 8bit gray level, for which 0=black and 255=white

(def-substitution-macro rgb-to-gray (rgb)
  (let* ((red (red-part-of-rgb rgb))
         (green (green-part-of-rgb rgb))
         (blue (blue-part-of-rgb rgb)))
    (intensity-of-color red green blue)))



;;; The function `create-gray-map-from-color-map' returns a managed array of
;;; the same length as color-map, filled with the gray level of each color.

(defun create-gray-map-from-color-map (color-map)
  (let* ((length (managed-array-length color-map))
         (gray-map (allocate-managed-array length)))
    (loop for i below length
          for rgb = (managed-svref color-map i)
          doing
      (setf (managed-svref gray-map i) (rgb-to-gray rgb)))
    gray-map))




;;;; Image Data


;;; The `image-data' structure is the thing corresponding to image-definition
;;; objects which can live in both G2 and TW.

(define-structure image-data ()
  (:constructor make-image-data-1)
  (:reclaimer reclaim-image-data-1)
  (:managed t)
  (:conc-name t)
  (pathname nil)      ; A simple string, in ASCII (not a g2 text-string).
  ;; Would be called corresponding-icp-object-map-for-image-data.
  (icp-ports ())      ; Alist of (icp-port . index)
  (format nil)              ; Only for use by describe-image.
  (image? nil)              ; Our image definition frame, unless TW.
  (width nil)
  (height nil)
  (depth nil)
  (number-of-colors nil)
  (color-map nil)     ; A managed array of packed RGB values.
  (cache? nil)              ; A shredded-raster instance.
  (next-scans nil)    ; alist of icp-port -> scans sent.
  (renderings ())     ; List of renderings, one per (G2 window,scale,rotation).
  (transparent-color-index -1)
  (was-constructed-p nil))                ; If T, then ignore the pathname.

;;; The system-variable `all-image-data-structures' is a gensym-list of all
;;; active image-data structures in this process.  It used when invalidating
;;; all image renderings after a change in the image-palette in drawing-parameters.

(def-system-variable all-image-data-structures images ())


#+development
(def-development-printer print-image-data (image-data &optional (stream *standard-output*))
  (when (image-data-p image-data)
    (printing-random-object (image-data stream)
      (format stream "IMAGE-DATA ~a" (image-data-pathname image-data)))
    image-data))


;;; The function `image-data-next-scan-to-send' returns the number of the
;;; next scan line which needs to be sent to the current ICP port.

(defun image-data-next-scan-to-send (image-data)
  (get-property-macro (image-data-next-scans image-data) current-icp-port 0))

(defun set-image-data-next-scan-to-send (image-data new-value)
  (setf (image-data-next-scans image-data)
        (set-property-macro
          (image-data-next-scans image-data)
          current-icp-port
          gensym-cons
          new-value)))

(defun icp-port-shutdown-for-image-data (image-data icp-port)
  (setf (image-data-next-scans image-data)
        (remove-property-macro (image-data-next-scans image-data)
                               icp-port
                               reclaim-gensym-cons)))

(defsetf image-data-next-scan-to-send set-image-data-next-scan-to-send)



;;; The function `image-data-has-been-transmitted-p' is true if the image-data
;;; object has already been sent across the wire to the current icp port.

(defun image-data-has-been-transmitted-p (image-data)
  (>=f (image-data-next-scan-to-send image-data)
       (image-data-height image-data)))




;;; The function `make-image-data' copies the pathname argument, but does NOT
;;; copy the color-map argument.  The pathname must be ASCII, but since we copy
;;; it, it need not be simple.  It is owned by our shredded-raster.

(defun make-image-data (ascii-pathname? &optional width height depth format number-of-colors
                                        color-map transparent-color-index)
  (setq transparent-color-index (or transparent-color-index -1))
  (let ((image-data (make-image-data-1)))
    (when ascii-pathname?
      (setf (image-data-pathname image-data) (copy-text-string ascii-pathname?)))
    (setf (image-data-width image-data) width
          (image-data-height image-data) height
          (image-data-depth image-data) depth
          (image-data-format image-data) format
          (image-data-number-of-colors image-data) number-of-colors
          (image-data-color-map image-data) color-map
          (image-data-transparent-color-index image-data) transparent-color-index)
    (gensym-push image-data all-image-data-structures)
    image-data))



;;; The function `reclaim-image-data' reclaims an image-data structure, which
;;; includes its shredded raster and all of its renderings.

(defun reclaim-image-data (image-data)
  (setq all-image-data-structures (delete-gensym-element image-data
                                                         all-image-data-structures))
  (when (image-data-pathname image-data)
    (reclaim-text-string (image-data-pathname image-data)))
  (when (image-data-cache? image-data)
    (reclaim-shredded-raster (image-data-cache? image-data))
    (setf (image-data-cache? image-data) nil))

  ;; Our color map is owned by the shredded raster.
  (clear-image-renderings-for-image-data image-data)

  ;; Delete our peers across the wire in TeleWindows.  Within TeleWindows, do
  ;; nothing.
  (when (eq current-system-name 'ab)
    (reclaim-icp-object-map-for-image-data image-data))
  (reclaim-image-data-1 image-data))



;;; The function `ensure-image-data-cache' is only called inside of
;;; TeleWindows, while receiving an image.

(defun ensure-image-data-cache (image-data)
  (or (image-data-cache? image-data)
      (let ((raster (allocate-shredded-raster
                      (image-data-width image-data)
                      (image-data-height image-data)
                      (image-data-depth image-data)
                      (image-data-number-of-colors image-data)
                      (image-data-color-map image-data)
                      nil
                      (image-data-transparent-color-index image-data))))
        (setf (image-data-cache? image-data) raster))))


;;; The function `image-data-complete-p' returns T iff the image-data has been
;;; completely loaded.

(defun image-data-complete-p (image-data)
  (and (image-data-cache? image-data)
       (shredded-raster-buffer (image-data-cache? image-data) 0)
       t))


;;; The function `ensure-image-data-pixels' tries to ensure that the scanline
;;; buffers for the given data are filled. It returns T iff it succeeds.

(defun ensure-image-data-pixels (image-data)
  (unless (image-data-complete-p image-data)
    (read-image-data image-data))        ; Read header and data.
  (neq (image-data-format image-data) 'unknown))

;; We must return NIL if file not found, is unreadable, OR has different
;; dimensions from the existing image-data.


;;; The function `read-image-data-header' reads just the header for the given
;;; image: width, height, etc.

(defun read-image-data-header (image-data)
  (read-image-data image-data t))


;;; The function `image-data-and-raster-dimensional-match-p' is true if the
;;; raster appears to be the same data as in image-data. If image-data is
;;; "empty" (key slots are NIL), then we match.

(defun image-data-and-raster-dimensional-match-p (image-data raster)
  (or (null (image-data-width image-data))
      (and (eql (image-data-width image-data) (shredded-raster-width raster))
           (eql (image-data-height image-data) (shredded-raster-height raster))
           (eql (image-data-depth image-data) (shredded-raster-depth raster))
           (eql (image-data-number-of-colors image-data)
                (shredded-raster-ncolors raster))
           (eql (image-data-transparent-color-index image-data)
                (shredded-raster-transparent-color-index raster)))))


;;; The function `read-image-data' reads new data into image-data's cache, a
;;; shredded-raster instance.  Returns the shredded raster if successful.  If
;;; there was already data present, then the new data must have the same
;;; dimensions (width, height, and depth) as the old data.

(defun read-image-data (image-data &optional header-only?)
  (let* ((pathname (image-data-pathname image-data))
         (raster-or-error (read-raster pathname header-only?)))
    (cond ((text-string-p raster-or-error)
           (notify-user-at-console "Error reading ~a: ~a" pathname raster-or-error)
           (reclaim-text-string raster-or-error)
           (setf (image-data-format image-data) 'unknown)
           nil)
          ((not (image-data-and-raster-dimensional-match-p image-data raster-or-error))
           (notify-user-at-console "Image file ~a changed on disk." pathname)
           ;; TODO: We read and throw away the pixels here.
           (reclaim-shredded-raster raster-or-error)
           (setf (image-data-format image-data) 'unknown)
           nil)
          (t
           (let ((old-raster? (image-data-cache? image-data)))
             (setf (image-data-cache? image-data) raster-or-error
                   (image-data-width image-data) (shredded-raster-width raster-or-error)
                   (image-data-height image-data) (shredded-raster-height raster-or-error)
                   (image-data-depth image-data) (shredded-raster-depth raster-or-error)
                   (image-data-format image-data) (shredded-raster-format raster-or-error)
                   (image-data-number-of-colors image-data) (shredded-raster-ncolors raster-or-error)

                   (image-data-color-map image-data) (shredded-raster-color-map raster-or-error)
                   (image-data-transparent-color-index image-data)
                   (shredded-raster-transparent-color-index raster-or-error))
             (when old-raster?
               (reclaim-shredded-raster old-raster?))
             raster-or-error)))))


;;; The function `image-data-is-gray-scale-p' returns True if the image
;;; is valid and is either 1bit deep or has a color-map which contains
;;; only shades of gray.  Eg, no color map means we are not gray scale.

(defun image-data-is-gray-scale-p (image-data)
  (fixnum-case (image-data-depth image-data)
    (1 t)                                ; What about 1-bit GIFs which define colors?
    (8
      (let ((color-map? (image-data-color-map image-data)))
        (and color-map?                        ; I think always non-NIL nowadays.
             (loop for i below (image-data-number-of-colors image-data)
                   as rgb = (managed-svref color-map? i)
                   always (=f (red-part-of-rgb rgb)
                              (green-part-of-rgb rgb)
                              (blue-part-of-rgb rgb))))))
    (t nil)))

;; Possibly worth caching this?



;;;; Image Renderings



;;; An `image-rendering' is a g2-window-specific tiled raster which contains an
;;; image rendered at some scale and rotation.  The raster has already been
;;; color-mapped, and is ready to blt.

(define-structure image-rendering ()
  (:constructor make-image-rendering-1)
  (:reclaimer reclaim-image-rendering-1)
  #+development (:print-function print-image-rendering)
  (:managed t)
  (:conc-name t)
  image-data          ; Our parent image-data structure.
  window              ; The gensym-window to which we apply.
  width                      ; The width&height after scaling and rotation.
  height
  depth
  x-scale
  y-scale
  rotation
  quality
  color-map              ; Byte vector of Image pixel -> X window pixel.
  tile-width
  tile-height
  tiled-raster)              ; A tiled raster. Each tile color-mapped for the window.

;; How are tiles recycled? Are individual tiles from a large icon ever lost? No.
;; Or do we always have either all of the tiles or none of them? Yes.



#+development
(defun print-image-rendering (rendering &optional (stream *standard-output*) depth)
  (declare (ignore depth))
  (printing-random-object (rendering stream)
    (let* ((x-scale (image-rendering-x-scale rendering))
           (y-scale (image-rendering-y-scale rendering))
           (name? (image-rendering-name rendering)))
      (cond ((and (numberp x-scale) (equal x-scale y-scale))
             (format stream "IMAGE-RENDERING ~@[~a ~]~d%"
                     name?
                     (round (* 100 x-scale) (normalized-scale))))
            (t
             (format stream "IMAGE-RENDERING~@[ ~a~]" name?))))))


#+development
(defun image-rendering-name (image-rendering)
  (let* ((image-data? (image-rendering-image-data image-rendering))
         (image? (and image-data? (image-data-image? image-data?))))
    (and image? (fboundp 'get-primary-name-for-frame-if-any)
         (funcall 'get-primary-name-for-frame-if-any image?))))




;;; The function `find-or-create-image-rendering' is the only interface for getting
;;; image-renderings.

(defun find-or-create-image-rendering (image-data window x-scale y-scale rotation quality)
  (or (find-image-rendering image-data window x-scale y-scale rotation quality)
      (create-image-rendering image-data window x-scale y-scale rotation quality)))

;; Quality is currently ignored, as is rotation.  Palette would be a more
;; useful variable to cache upon.


;;; The function `find-image-rendering' searches for an existing rendering with
;;; the same window, scale, and rotation.  The same window implies that it will
;;; be of the required depth, also.

(defun find-image-rendering (image-data window x-scale y-scale rotation quality)
  (loop for rendering in (image-data-renderings image-data)
        when (and (eq window (image-rendering-window rendering))
                  (=f x-scale (image-rendering-x-scale rendering))
                  (=f y-scale (image-rendering-y-scale rendering))
                  (eq rotation (image-rendering-rotation rendering))
                  (or (null quality)
                      (eq quality (image-rendering-quality rendering))))
          return rendering))

;; The check for the same window is actually unneeded at the moment.  Image
;; renderings exist only in the process which uses them, so G2 only has
;; renderings for its native window, and TW has the renderings for its window.


;;; The function `create-image-rendering' creates the rendering but not the
;;; tiled raster nor the color map.

(defun create-image-rendering
    (image-data gensym-window x-scale y-scale rotation quality)
  (let* ((image-rendering
           (make-image-rendering-1))
         (width
           (delta-x-in-window (image-data-width image-data) x-scale))
         (height
           (delta-y-in-window (image-data-height image-data) y-scale))
         (screen-depth
           (window-screen-depth gensym-window))
         (depth
             ;; Just allocate a 1bit rendering if the palette is b&w or
             ;; the image is a bitmap.
           (cond
             ((or (eq (image-palette-of-gensym-window gensym-window)
                      'black-and-white)
                  (=f 1 (image-data-depth image-data)))
              1)
             ((<=f screen-depth 8)  ;; should never be less than 8
              8)
             (t  ;; Use true color if greater than 8 bit depth.
                 ;; It doesn't matter if the screen depth is actually
                 ;; less than 24.
              24)))
         (exact-size-p (eq quality 'singleton)))

    (when (rotated-by-90-p rotation)
      (psetq width height
             height width))

    (let ((tiled-raster
            (allocate-just-tiled-raster
              gensym-window width height depth exact-size-p)))

      (setf (image-rendering-image-data image-rendering) image-data
            (image-rendering-window image-rendering) gensym-window
            (image-rendering-x-scale image-rendering) x-scale
            (image-rendering-y-scale image-rendering) y-scale
            (image-rendering-rotation image-rendering) rotation
            (image-rendering-width image-rendering) width
            (image-rendering-height image-rendering) height
            (image-rendering-depth image-rendering) depth
            (image-rendering-quality image-rendering) quality
            (image-rendering-tiled-raster image-rendering) tiled-raster
            (image-rendering-tile-width image-rendering) (if exact-size-p
                                                             (minf width largest-regular-raster-size)
                                                             (tile-size tiled-raster))
            (image-rendering-tile-height image-rendering) (if exact-size-p
                                                             (minf height largest-regular-raster-size)
                                                              (tile-size tiled-raster)))

      ;; We create the color-map and tiled raster later.  We may have to steal
      ;; tiled rasters from other renderings to use for our own.

      (gensym-push image-rendering (image-data-renderings image-data))
      image-rendering)))



(defun reclaim-image-rendering (image-rendering)
  (let ((image-data? (image-rendering-image-data image-rendering)))
    (when image-data?
      (setf (image-data-renderings image-data?)
            (delete-gensym-element image-rendering (image-data-renderings image-data?)))))
  (reclaim-image-rendering-tiled-raster image-rendering)
  (reclaim-image-rendering-color-map image-rendering)
  (reclaim-image-rendering-1 image-rendering))


(defun reclaim-image-rendering-color-map (image-rendering)
  (when (image-rendering-color-map image-rendering)
    (reclaim-byte-vector (image-rendering-color-map image-rendering))
    (setf (image-rendering-color-map image-rendering) nil)))


(defun reclaim-image-rendering-tiled-raster (image-rendering)
  (let ((tiled-raster (image-rendering-tiled-raster image-rendering)))
    (do-raster-tiles (tile? x y tiled-raster)
      (when tile?
        (reclaim-image-tile tile?)))
    (reclaim-tiled-raster tiled-raster)
    (setf (image-rendering-tiled-raster image-rendering) nil)))


;;; The function `clear-all-image-renderings-for-window' runs only on the local
;;; (native) window.  It deletes and reclaims all image renderings.

(defun clear-all-image-renderings-for-window (gensym-window)
  ;; To check for a local window, this used to test for a non-null
  ;; native-window?, but native-window? can be NIL here if we're closing MDI
  ;; child windows (see `set-window-show-status' and
  ;; `handle-telewindows-window-close-request-event').  So we check the type
  ;; instead. `clear-image-renderings-for-image-data' actually never uses the
  ;; native-window? slot, so it doesn't matter if it is NIL.
  (when (eq (type-of-gensym-window gensym-window) 'x11-window)
    (loop for image-data in all-image-data-structures doing
      (clear-image-renderings-for-image-data image-data gensym-window))))


(defun clear-image-renderings-for-image-data (image-data &optional gensym-window?)
  (dolist-safely (image-rendering (image-data-renderings image-data))
    (when (or (null gensym-window?)
              (eq gensym-window? (image-rendering-window image-rendering)))
      (reclaim-image-rendering image-rendering))))


;;;; Image tiles


(def-substitution-macro do-nothing-reclaimer (next-element)
  next-element
  nil)



;;; The structure `image-tile' are the elements of tiled-raster used for image
;;; rendering.

(define-structure image-tile (lru-element (lru-element-next-element nil :reclaimer do-nothing-reclaimer))
  (:constructor make-image-tile-1)
  (:reclaimer reclaim-image-tile-1)
  #+development (:print-function print-image-tile)
  (:conc-name t)
  rendering                                ; The rendering which owns us, if any.
  x                                        ; The column/row where we live there.
  y
  stored-raster                                ; The stored raster (a fixnum handle)
  stored-mask-raster                        ; The 1 bit stored raster for a mask
                                        ;  (also a fixnum handle)
  exact-size-p)


#+development
(defun print-image-tile (image-tile &optional (stream *standard-output*) depth)
  (declare (ignore depth))
  (printing-random-object (image-tile stream)
    (let ((rendering? (image-tile-rendering image-tile)))
      (if rendering?
          (format stream "IMAGE-TILE~@[ ~a~] ~a ~a (~dx~dx~d)"
                  (image-rendering-name rendering?)
                  (image-tile-x image-tile)
                  (image-tile-y image-tile)
                  (image-rendering-tile-width rendering?)
                  (image-rendering-tile-height rendering?)
                  (image-rendering-depth rendering?))
          (format stream "IMAGE-TILE"))))
  image-tile)



;;;; LRU cache of image-tiles



(def-system-variable image-tile-lru-queue images
  (:funcall make-lru-queue))

(def-system-variable bytes-allocated-for-image-tiles images 0)


;; We're either AB or Telewindows, but not both.

(defun maximum-bytes-for-image-tiles ()
  (region-info-desired (get-info-for-region 3)))

(defun set-maximum-bytes-for-image-tiles (new-value)
  (setf (region-info-desired (get-info-for-region 3)) new-value))

(defsetf maximum-bytes-for-image-tiles set-maximum-bytes-for-image-tiles)


;; Fwd referenced from os-memory
(defun bytes-allocated-for-image-tiles ()
  ;; During startup, the memory allocation routines call this before
  ;; the system variable is bound.
  (if (boundp 'bytes-allocated-for-image-tiles)
      bytes-allocated-for-image-tiles
      0))


;; We have to consider the effects of tiling: what is the maximum number of
;; 400x400 tiles which can be visible on the screen at once (including partial
;; visibility)?  Answer: (1+ceil(1152/400)) * (1+ceil(900/400)) = 16 tiles,
;; which is 16*400^2 = 2.56 MB.

;; The minimum space we can run in would be one tile of each size and depth,
;; which amounts to about 375KB.  But, icon rendering interferes and may
;; need more.  Also, unless we explictly allocate one of each size at startup,
;; we'll need more.

;; Memory regions: see define-g2-meters-of-memory-regions g2-region-memory-available
;; def-memory-limit-setup





;;; The substitution-macro `add-image-tile-to-lru-queue' adds a new image tile
;;; as the most recently used element.

(def-substitution-macro add-image-tile-to-lru-queue (image-tile)
  (install-lru-element-in-queue image-tile image-tile-lru-queue))



;;; The substitution-macro `record-usage-of-image-tile' makes the
;;; given image tile be most recently used.

(def-substitution-macro record-usage-of-image-tile (image-tile)
  (record-lru-element-usage image-tile image-tile-lru-queue))


(def-substitution-macro remove-image-tile-from-lru-queue (image-tile)
  (splice-out-lru-element image-tile)
  ;; Tidyness.
  (setf (lru-element-next-element image-tile) nil)
  (setf (lru-element-previous-element image-tile) nil))




;; In bytes.

(def-substitution-macro bytes-required-for-tile (tile-width tile-height depth)
  (roundf (*f tile-width tile-height depth) 8))



;;;; Rendering operations



;;; The function `make-image-tile' creates an image tile for the x,y-th
;;; position in the image rendering, and stuffs it there.

(defun make-image-tile (image-rendering x y transparentp exact-size-p)
  (let ((tiled-raster
          (image-rendering-tiled-raster image-rendering))
        (tile-width
          (image-rendering-tile-width image-rendering))
        (tile-height
          (image-rendering-tile-height image-rendering))
        (depth
          (image-rendering-depth image-rendering))
        (window
          (image-rendering-window image-rendering))
        (image-tile
          (make-image-tile-1)))

    #+development (when (tiled-raster-tile tiled-raster x y)
                    (cerror "Leaking an image tile" "Ignore it"))

    (setf (tiled-raster-tile tiled-raster x y) image-tile)

    (setf (image-tile-rendering image-tile) image-rendering
          (image-tile-x image-tile) x
          (image-tile-y image-tile) y
          (image-tile-exact-size-p image-tile) exact-size-p)

    ;; Allocate a raster.  If it did not come from a pool,
    ;; increment our memory meter.  Notice that the meter is
    ;; NEVER decremented, since rasters are NEVER truely deallocated.

    (multiple-value-bind (raster new-p)
        (allocate-stored-raster-1
          window tile-width tile-height depth exact-size-p)

      (setf (image-tile-stored-raster image-tile) raster)

      (when new-p
        (incff bytes-allocated-for-image-tiles
               (bytes-required-for-tile tile-width tile-height depth))))
    (when transparentp
      (multiple-value-bind (mask-raster new-p)
          (allocate-stored-raster-1
            window tile-width tile-height 1 nil)
        #+development
        (when (image-tile-stored-mask-raster image-tile)
          (cerror "Ignore it" "Mask raster shouldn't exist already"))
        (setf (image-tile-stored-mask-raster image-tile) mask-raster)

        (when new-p
          (incff bytes-allocated-for-image-tiles
                 (bytes-required-for-tile tile-width tile-height 1)))))

    (add-image-tile-to-lru-queue image-tile)

    image-tile))



;;; The function `reclaim-image-tile' removes the image-tile from the LRU
;;; queue, detaches the tile from its owner, then reclaims the tile structure
;;; itself.

(defun reclaim-image-tile (image-tile)
  (let ((rendering? (image-tile-rendering image-tile)))
    (when rendering?
      (let ((tiled-raster?
              (image-rendering-tiled-raster rendering?))
            (tile-width
              (image-rendering-tile-width rendering?))
            (tile-height
              (image-rendering-tile-height rendering?))
            (depth
              (image-rendering-depth rendering?))
            (window
              (image-rendering-window rendering?))
            (x (image-tile-x image-tile))
            (y (image-tile-y image-tile))
            (exact-size-p (image-tile-exact-size-p image-tile))
            (stored-raster? (image-tile-stored-raster image-tile))
            (stored-mask-raster? (image-tile-stored-mask-raster image-tile)))

        (remove-image-tile-from-lru-queue image-tile)

        (when tiled-raster?
          #+development
          (unless (eq image-tile (tiled-raster-tile tiled-raster? x y))
            (error "Inconsistent image-tile ~s." image-tile))
          (setf (tiled-raster-tile tiled-raster? x y) nil))

        (when stored-mask-raster?
          ;; FIXME: Is the mask raster created exact size? I think not.
          (reclaim-stored-raster-1 stored-mask-raster?
                                   window
                                   tile-width tile-height 1 nil)
          (setf (image-tile-stored-mask-raster image-tile) nil))
        (when stored-raster?
          (reclaim-stored-raster-1 stored-raster?
                                   window
                                   tile-width tile-height depth exact-size-p))))

    (reclaim-image-tile-1 image-tile)))



;;; The function `reuse-image-tile' attaches an image-tile to a new
;;; image-rendering.

(defun reuse-image-tile (image-tile new-image-rendering new-x new-y)
  (let* ((image-rendering?
           (image-tile-rendering image-tile))
         (tiled-raster?
           (and image-rendering?
                (image-rendering-tiled-raster image-rendering?)))
         (x (image-tile-x image-tile))
         (y (image-tile-y image-tile)))

    (when tiled-raster?
      #+development
      (unless (eq image-tile (tiled-raster-tile tiled-raster? x y))
        (error "Inconsistent image-tile ~s." image-tile))
      (setf (tiled-raster-tile tiled-raster? x y) nil))

    (setf (image-tile-rendering image-tile) new-image-rendering
          (image-tile-x image-tile) new-x
          (image-tile-y image-tile) new-y
          (tiled-raster-tile
            (image-rendering-tiled-raster new-image-rendering)
            new-x new-y) image-tile)

    (record-usage-of-image-tile image-tile)

    image-tile))



;; None of these size-xxx routines are used.

#+development
(defun size-of-all-image-data (&optional verbose)
  (loop for i in all-image-data-structures
        when verbose do (format t "~s~%" i)
        summing (size-of-image-data i verbose)))


#+development
(defun size-of-image-data (image-data &optional verbose)
  (loop for image-rendering in (image-data-renderings image-data)
        when verbose do (format t " ~s~%" image-rendering)
        summing (size-of-image-rendering image-rendering verbose)
          using +f))


;; Size currently allocated, not the size needed.
#+development
(defun size-of-image-rendering (image-rendering &optional verbose)
  (let ((tiled-raster? (image-rendering-tiled-raster image-rendering)))
    (cond (tiled-raster?
           (size-of-tiled-raster
             tiled-raster?
             (image-rendering-tile-width image-rendering)
             (image-rendering-tile-height image-rendering)
             verbose))
          (t
           0))))

#+development
(defun size-of-tiled-raster (tiled-raster tile-width tile-height &optional verbose)
  (let ((sum 0)
        (depth (bits-per-pixel-for-tiled-raster tiled-raster)))
    (do-raster-tiles (tile x y tiled-raster)
      (when tile
        (let ((nbytes (bytes-required-for-tile tile-width tile-height depth)))
          (when verbose
            (format t "  ~s ~s~%" tile nbytes))
          (incff sum nbytes))))
    sum))



(defun find-suitable-image-tile-to-reuse (window tile-width tile-height depth exact-size-p)
  (block search
    (do-lru-queue (image-tile image-tile-lru-queue)
      (let ((rendering? (image-tile-rendering image-tile)))
        (when (and rendering?
                   (eq window (image-rendering-window rendering?))
                   (=f tile-width (image-rendering-tile-width rendering?))
                   (=f tile-height (image-rendering-tile-height rendering?))
                   (=f depth (image-rendering-depth rendering?))
                   (eq (image-tile-exact-size-p image-tile) exact-size-p))
          (return-from search image-tile))))
    nil))



;;; The function `ensure-image-tile' implements the LRU decaching algorithm for
;;; image rasters. It always returns non-NIL for this reason: we ensure that
;;; there is at least one tile of each of the possible sizes and depths.  And
;;; if necessary, we'll keep returning that one tile over and over again.

(defun ensure-image-tile (image-rendering x y transparentp quality)
  (let* ((tiled-raster (image-rendering-tiled-raster image-rendering))
         (image-tile? (tiled-raster-tile tiled-raster x y))
         (window (image-rendering-window image-rendering))
         (tile-width
           (image-rendering-tile-width image-rendering))
         (tile-height
           (image-rendering-tile-height image-rendering))
         (depth (image-rendering-depth image-rendering))
         (tile-bytes (bytes-required-for-tile tile-width tile-height depth))
         (mask-bytes (bytes-required-for-tile tile-width tile-height 1))
         (exact-size-p (eq quality 'singleton)))

    (when transparentp
      (incff tile-bytes mask-bytes))
    #+development
    (when (and (not transparentp)
               image-tile?
               (image-tile-stored-mask-raster image-tile?))
      (cerror "Go on" "Already rendered non transparent tile had mask!")
                                        ;reclaim?
      (setf (image-tile-stored-mask-raster image-tile?) nil))

    (cond (image-tile?
           ;; The rendering already has a tile there.
           (record-usage-of-image-tile image-tile?))

          ((and (stored-raster-in-regular-pool? window tile-width tile-height depth)
                (or (not transparentp)
                    (stored-raster-in-regular-pool? window tile-width tile-height 1)))

           ;; No tile, but there is a free raster in a pool, so we know this
           ;; will not allocate. (Unless exact-size-p requested)
           (make-image-tile image-rendering x y transparentp exact-size-p))

          ((<=f tile-bytes (-f (maximum-bytes-for-image-tiles)
                               bytes-allocated-for-image-tiles))
           ;; No raster in the pool, but we've room to allocate a new one.
           (setq image-tile?
                 (make-image-tile image-rendering x y transparentp exact-size-p))
           #+development
           (when (and (not transparentp)
                      (image-tile-stored-mask-raster image-tile?))
             (cerror "Go on" "Newly created non transparent tile had mask!")
             ;;reclaim?
             (setf (image-tile-stored-mask-raster image-tile?) nil))
           image-tile?)

          ((and (setq image-tile? (find-suitable-image-tile-to-reuse
                                    window tile-width tile-height depth exact-size-p))
                (or (not transparentp)
                    (image-tile-stored-mask-raster image-tile?)))

           ;; No free raster, and have reached memory limit, so reuse the
           ;; least-recently-used one of the correct shape.
           (let ((mask?
                   (image-tile-stored-mask-raster image-tile?)))
             (unless transparentp
               (when mask?
                 (reclaim-stored-raster-1 mask?
                                          window
                                          tile-width tile-height 1 nil))
               (setf (image-tile-stored-mask-raster image-tile?) nil)))
           (reuse-image-tile image-tile? image-rendering x y))

          (t
           ;; No free rasters available, not even an in-use raster of the
           ;; correct shape, and have reached our memory limit: go ahead and
           ;; allocate and bump the limit. [Note A]
           (progn
             (setq image-tile?
                   (make-image-tile image-rendering x y transparentp exact-size-p))
             #+development
             (when (and (not transparentp)
                        (image-tile-stored-mask-raster image-tile?))
               (cerror "Go on" "Newly allocated non transparent tile had mask!")
               ;;reclaim?
               (setf (image-tile-stored-mask-raster image-tile?) nil))
             (setf (maximum-bytes-for-image-tiles) bytes-allocated-for-image-tiles)
             image-tile?)))))


;; Note A: At this point it must be the case that there are NO tiles out there
;; of the correct size and depth.  Otherwise, we should have found one above
;; since every raster is either in the pool or in the LRU queue [Note B].  So
;; make at least one of this size, increasing our memory limit to accomodate
;; it.

;; Note B: This is actually true only for 8bit rasters. 1bit rasters may be in
;; use by icon rendering.  The result is that images will always allocate one
;; 1bit raster for its own use in this case.  It would be possible for memory
;; use to increase indefinately if both image rendering and icon rendering keep
;; asking for new 1bit rasters.  But icon renderings can increase indefinately
;; themselves, so who cares.  In any case, it is not too important since most
;; images are 8bit (fatal last words).  -fmw, 8/1/94




;;; The function `ensure-image-rendering-color-map' returns the color-map for the
;;; image rendering, creating it as needed.  If the source image is actually
;;; a bitmap, then we create a map of length 2, even though it should never
;;; be used.
;;;   jv, 10/2/97 - adding a logandf to the pixel value.  If the pixel value
;;; is greater than 255, that presumably means that the screen depth is
;;; greater than 8, in which case the color map will not be used anyway.
;;; That's true for PCs, at least.  What happens on Unix is something
;;; to worry about some other time.  The logandf will prevent Telewindows
;;; from exploding.

(defun ensure-image-rendering-color-map (rendering)
  (or (image-rendering-color-map rendering)
      (let* ((image-data (image-rendering-image-data rendering))
             (window (image-rendering-window rendering))
             (shredded-raster (image-data-cache? image-data))
             (number-of-colors (shredded-raster-ncolors shredded-raster))
             (source-color-map? (shredded-raster-color-map shredded-raster)) ; Source-pixel -> packed rgb.
             (rendering-color-map (allocate-byte-vector (maxf number-of-colors 2))))
        (when source-color-map?
          (loop for i below number-of-colors
                for rgb = (managed-svref source-color-map? i)
                doing
            (multiple-value-bind (pixel error)
                (map-to-closest-color-value window rgb)
              (declare (ignore error))
              (setf (byte-vector-aref rendering-color-map i)
                    (logandf pixel 255)))))
        (setf (image-rendering-color-map rendering) rendering-color-map))))


(def-substitution-macro fast-map-image-color (color-map source-pixel)
  (byte-vector-aref color-map source-pixel))


;;; The function `image-rendering-last-tile-width' returns the width actually used
;;; in the rightmost tile of an image rendering.

(defun image-rendering-last-tile-width (rendering)
  (let* ((width (if (rotated-by-90-p (image-rendering-rotation rendering))
                    (delta-y-in-window (image-data-height (image-rendering-image-data rendering))
                                       (image-rendering-y-scale rendering))
                    (delta-x-in-window (image-data-width (image-rendering-image-data rendering))
                                       (image-rendering-x-scale rendering))))
         (tile-width (image-rendering-tile-width rendering))
         (w (modf width tile-width)))
    (if (=f w 0)
        tile-width
        w)))


;;; The function `image-rendering-last-tile-height' returns the height actually used
;;; in the bottom-most tile of an image rendering.

(defun image-rendering-last-tile-height (rendering)
  (let* ((height (if (rotated-by-90-p (image-rendering-rotation rendering))
                     (delta-x-in-window
                       (image-data-width (image-rendering-image-data rendering))
                       (image-rendering-x-scale rendering))
                     (delta-y-in-window
                       (image-data-height (image-rendering-image-data rendering))
                       (image-rendering-y-scale rendering))))
         (tile-height (image-rendering-tile-height rendering))
         (h (modf height tile-height)))
    (if (=f h 0)
        tile-height
        h)))




;;; The macro `do-overlapping-tiles-of-image-rendering' runs the body once for
;;; each tile in the rendering which overlaps the given rectangle.  Some tiles
;;; may be NIL.  If so, the x,y needed for allocation are in j,i.

(defmacro do-overlapping-tiles-of-image-rendering
    ((tile x0 y0 tile-width tile-height
           rendering left top right bottom)
     &body body)
  (let ((tiled-raster (make-symbol "TILED-RASTER")))
    `(let ((,tiled-raster (image-rendering-tiled-raster ,rendering)))
       (when (and (>f (tiled-raster-width ,tiled-raster) 0) ; For some very small renderings.
                  (>f (tiled-raster-height ,tiled-raster) 0))
         (iterate-over-tiles-to-be-painted (,left ,top ,right ,bottom ,tiled-raster)
           ;; Bind width, height here to the portion of the tile we actually use.
           (let ((,tile tile-to-paint)
                 (,x0 (*f j tile-size))
                 (,y0 (*f i tile-size))
                 (,tile-height (if (=f i number-of-rows-1)
                                   (image-rendering-last-tile-height ,rendering)
                                   tile-size))
                 (,tile-width (if (=f j number-of-columns-1)
                                  (image-rendering-last-tile-width ,rendering)
                                  tile-size)))
             ,@body))))))




;;; The function `invalidate-all-tiles-in-tiled-raster' ensures that all of the tile
;;; identifiers in the raster are negative.

(defun invalidate-all-tiles-in-tiled-raster (tiled-raster)
  (do-raster-tiles (tile x y tiled-raster)
    (setf (tiled-raster-tile tiled-raster x y)
          (-f (absf (tiled-raster-tile tiled-raster x y))))))



;;; The macro `tiled-raster-ref' returns the i,j-th (y,x-th) tile in
;;; a tiled raster.

(defmacro tiled-raster-ref (tiled-raster i j)
  `(managed-svref (managed-svref (tile-arrays ,tiled-raster) ,i) ,j))



;;; The macro `fast-delta-x-in-workspace' use floor instead of round.
;;; The arguments must be positive.

(defmacro fast-delta-x-in-workspace (positive-delta-x-in-window x-scale)
  `(floorf-positive (*f ,positive-delta-x-in-window ,(normalized-scale)) ,x-scale))

(defmacro fast-delta-y-in-workspace (positive-delta-y-in-window y-scale)
  `(floorf-positive (*f ,positive-delta-y-in-window ,(normalized-scale)) ,y-scale))

;; Roundf would be better here, but it is very bad news in Chestnut.



;;; The macro `bits-to-bytes' returns the number of bytes required to
;;; represent N bits.

(defmacro bits-to-bytes (n)
  `(floorf-positive (+f ,n 7) 8))


;;; The defparameter `ordered-dither-16' is a 16x16 ordered dither matrix for
;;; 256 shades of gray.  Created with "OrderDither 4" from the GraphicsGems
;;; library.

(defparameter ordered-dither-16
  (concatenate
    'vector
    (vector
      0 192  48 240  12 204  60 252   3 195  51 243  15 207  63 255
      128  64 176 112 140  76 188 124 131  67 179 115 143  79 191 127
      32 224  16 208  44 236  28 220  35 227  19 211  47 239  31 223
      160  96 144  80 172 108 156  92 163  99 147  83 175 111 159  95)
    (vector
      8 200  56 248   4 196  52 244  11 203  59 251   7 199  55 247
      136  72 184 120 132  68 180 116 139  75 187 123 135  71 183 119
      40 232  24 216  36 228  20 212  43 235  27 219  39 231  23 215
      168 104 152  88 164 100 148  84 171 107 155  91 167 103 151  87)
    (vector
      2 194  50 242  14 206  62 254   1 193  49 241  13 205  61 253
      130  66 178 114 142  78 190 126 129  65 177 113 141  77 189 125
      34 226  18 210  46 238  30 222  33 225  17 209  45 237  29 221
      162  98 146  82 174 110 158  94 161  97 145  81 173 109 157  93)
    (vector
      10 202  58 250   6 198  54 246   9 201  57 249   5 197  53 245
      138  74 186 122 134  70 182 118 137  73 185 121 133  69 181 117
      42 234  26 218  38 230  22 214  41 233  25 217  37 229  21 213
      170 106 154  90 166 102 150  86 169 105 153  89 165 101 149  85)))

;; The WATCOM C compiler for Windows couldn't handle a single 256-element
;; vector expression



;;; These macros return T if the designated pixel should be considered black.

(defmacro dithered-gray-black-p (gray x y)
  `(<f ,gray
       (svref ordered-dither-16 (+f (logandf ,x 15) (ashf (logandf ,y 15) 4)))))

(defmacro shredded-raster-ref-24-black-p
    (shredded-raster raster-x raster-y dither-x dither-y gray-map)
  (declare (ignore gray-map))
  `(dithered-gray-black-p
     (rgb-to-gray (shredded-raster-ref-24 ,shredded-raster ,raster-x ,raster-y))
     ,dither-x ,dither-y))

(defmacro shredded-raster-ref-8-black-p
    (shredded-raster raster-x raster-y dither-x dither-y gray-map)
  `(dithered-gray-black-p
     (managed-svref ,gray-map
                    (shredded-raster-ref-8 ,shredded-raster ,raster-x ,raster-y))
     ,dither-x ,dither-y))

(defmacro shredded-raster-ref-1-black-p (shredded-raster raster-x raster-y dither-x dither-y gray-map)
  (declare (ignore dither-x dither-y gray-map))
  `(>f (shredded-raster-ref-1 ,shredded-raster ,raster-x ,raster-y) 0))

;; This should be using the gray-map, rather than simply testing for pixel > 0.
;; On the other hand, we want to leave the rendering of color pixmaps in icons
;; essentially undefined, so that we can make them full-color someday.


;; If we already have the pixel.
(defmacro shredded-raster-pixel-black-p (shredded-raster pixel dither-x dither-y gray-map)
  `(case (shredded-raster-depth ,shredded-raster)
     (1 (>f ,pixel 0))
     (8 (dithered-gray-black-p (managed-svref ,gray-map ,pixel) ,dither-x ,dither-y))
     (t (dithered-gray-black-p (rgb-to-gray ,pixel) ,dither-x ,dither-y))))



;;; The function `align-image-scan-line-1' aligns buffer[index] appropriately
;;; for the diven depth by incrementing index as needed and zero-filling the
;;; bytes skipped.  The new index is returned.

;;; For 1bit and 8bit images: WORD align 1bit images, and DWORD align 8bit
;;; images.  This weirdness is a requirement of the MS Windows version of
;;; x11_put_image.

;;;   I believe that each scan line needs to be aligned *BOTH* on a DWORD
;;; boundary and on a bits-per-pixel boundary.  So, for 24 bit depth
;;; (for example), the total number of bits in a scan line needs to be
;;; a multiple of 96, or 12 bytes.  I haven't found this documented anywhere;
;;; it's just the way it seems to be from my testing.  - jv 9/30/97

(defvar overriding-alignment nil)

(defun compute-alignment (depth)
  (or overriding-alignment                ; stretch_bits needs a different value.
      (fixnum-case depth
        (1 2)                                ; 2-byte alignment.
        ((16 24) 12)                        ; 12-byte alignment, 3 bytes per pixel (width)
        (t 4))))                        ; 4 bytes by default.

(defun align-image-scan-line-1 (buffer index depth)
  (let ((alignment (compute-alignment depth)))
    (loop until (=f 0 (modf index alignment)) doing
      (setf (byte-vector-aref buffer index) 0)
      (incff index))
    index))

;; We assume that the start of the buffer is aligned in all cases.  So if index
;; is zero, we do nothing. In other cases, we increment index as needed to reach
;; the alignment boundary, and write zeroes to the bytes we passed over. -fmw,
;; 1/1/02

(def-substitution-macro align-image-scan-line (buffer index depth)
  (setq index (align-image-scan-line-1 buffer index depth)))


;;; The substitution-macro `compute-bytes-per-scan-line' returns the number of
;;; bytes required to store a raster scan line with WIDTH pixels of DEPTH bits
;;; each, as stored in the pixel buffer we pass to c-x11-put-image.  It must be
;;; 2-byte-aligned for 1bit images, 4-byte-aligned for 8-bit images, and 12-byte
;;; aligned for 24-bit images, requirements for the screwy MSWindows code.

(defun compute-bytes-per-scan-line (width depth)
  (let* ((nbytes (ashf (+f (*f width depth) 7) -3))
         (alignment (compute-alignment depth))
         (mod (modf nbytes alignment)))
    (cond ((=f mod 0)
           nbytes)
          (t
           (+f nbytes (-f alignment mod))))))


;;; The macro `copy-raster-bits-into-buffer' copys bits from the
;;; shredded-raster into buffer.  This is done by looping over bits in the
;;; buffer, computing the scaled, rotated, and translated image of that bit in
;;; the raster, and then setting the buffer bit if the raster bit is set
;;; (modulo dithering).  Bit x0,y0 in the image is mapped to bit tile-x1,tile-y1
;;; in the tile, in the absence of scaling or rotation.

;;; The buffer is assumed to cover the region [tile-x1,tile-x2] x
;;; [tile-y1,tile-y2] in the already scaled and rotated coordinate space of the
;;; tiled raster into which eventually bitblt.

;;; The following variables are referenced freely: BUFFER X-SCALE Y-SCALE
;;; SOURCE-HEIGHT-1 SOURCE-WIDTH-1 INVERSE-TRANSFORM X0 Y0 RASTER-WIDTH
;;; RASTER-HEIGHT GRAY-MAP? TILE-X1 TILE-X2 TILE-Y1 TILE-Y2

(defmacro copy-raster-bits-into-buffer (shredded-raster buffer raster-pixel-black-p)
  `(loop with index = 0
         for y fixnum from tile-y1 below tile-y2            ; *** Assuming open interval
         as y-in-workspace = (fast-delta-y-in-workspace y y-scale)
         as mask = 1
         as byte = 0
         doing
     (align-image-scan-line buffer index 1)
     (loop for x fixnum from tile-x1 below tile-x2            ; *** Assuming open interval
           as x-in-image = (fast-delta-x-in-workspace x x-scale)
           as y-in-image = y-in-workspace
           doing
       (orient-points-for-icon inverse-transform
           source-width-1 source-height-1 x-in-image y-in-image)

       ;; Convert from unit-scale icon coor to image coor.  This can be off by
       ;; one.  Ought to subtract in scaled (tile) space, instead.
       (decff x-in-image x0)
       (decff y-in-image y0)

       ;; Too bad we have to check. But, when the image is rotated, our rounding
       ;; may go towards higher numbers.
       (when (and (<f -1 x-in-image raster-width)
                  (<f -1 y-in-image raster-height))

         ;; Here is where dithering happens.
         (when (,raster-pixel-black-p ,shredded-raster x-in-image y-in-image
                                      x y gray-map?)
           (setq byte (logiorf byte mask))))
       (setq mask (ashf mask 1))
       (when (>=f mask 256)
         (setf (byte-vector-aref ,buffer index) byte
               byte 0
               mask 1)
         (incff index)))

     (when (>f mask 1)
       (setf (byte-vector-aref ,buffer index) byte)
       (incff index))))

;; For icon rendering only.  This is a very special purpose macro, with lots of
;; free variable references, which exists just so that I can instantiate this
;; code separately for 1bit and 8bit source rasters.  It also duplicates some
;; of the code in `draw-image-on-tile', unfortunately.

;; Faster version of this for 1-1 scaling?


;;;; Rendering onto tiles



;;; The function `draw-image-on-tile' fills the given tile with pixels from the
;;; source image-data structure.  x0,y0 are the coordinates in tile space
;;; (scaled image space) of the upper left corner of this tile.  Scan lines in
;;; the buffer are padded out to an integral number of words or double words
;;; (16bits or 32 bits), a requirement for the Windows version of
;;; c-x11-put-image.

;; This used only for drawing icon background images.

(defun draw-image-on-tile
    (image-data pixmap mask-pixmap? i j tile-size tile-width tile-height tile-depth
                x-scale y-scale reflection-and-rotation
                color-map rgb-color-map

                ;; Originally bound in draw-icon-for-entity
                image-left-offset-in-ws        ; What are these?
                image-top-offset-in-ws

                rotation-width rotation-height)
  (declare (ignore rotation-width rotation-height))
  (let* ((x0 (*f j tile-size))
         (y0 (*f i tile-size))
         (buffer (large-byte-vector))
         (shredded-raster (image-data-cache? image-data))
         (source-depth (shredded-raster-depth shredded-raster))
         (width (shredded-raster-width shredded-raster))
         (height (shredded-raster-height shredded-raster))
         (no-transform-p (identity-reflection-and-rotation-p reflection-and-rotation))
         (inverse-transform (fast-invert-reflection-and-rotation reflection-and-rotation))
         (transparent-color-index (image-data-transparent-color-index image-data))
         (transparent-color?
           (and transparent-color-index
                (/=f -1 transparent-color-index)
                (managed-svref rgb-color-map transparent-color-index)))
         (bytes-per-line
           (compute-bytes-per-scan-line tile-width tile-depth)))

    (when (rotated-by-90-p reflection-and-rotation)
      (psetq width height
             height width))

    ;; Draw into mask-pixmap? if image has transparency.
    (draw-mask-on-tile shredded-raster width height
                       source-depth  mask-pixmap?
                       tile-width tile-height
                       x-scale y-scale
                       inverse-transform
                       rgb-color-map
                       transparent-color?
                       buffer x0 y0
                       transparent-color-index
                       (eq (image-data-format image-data) 'gif))

    (cond ((=f source-depth tile-depth 8)
           (draw-image-on-tile-8-to-8
             shredded-raster width height
             tile-width tile-height tile-depth tile-size
             x-scale y-scale
             no-transform-p inverse-transform
             color-map rgb-color-map
             buffer
             x0
             y0
             image-left-offset-in-ws
             image-top-offset-in-ws))
          ((=f source-depth tile-depth 24)
           (setq buffer (really-large-byte-vector))
           (draw-image-on-tile-24-to-24
             shredded-raster width height
             tile-width tile-height tile-depth tile-size
             x-scale y-scale
             no-transform-p inverse-transform
             color-map rgb-color-map
             buffer
             x0
             y0
             image-left-offset-in-ws
             image-top-offset-in-ws))
          ((=f source-depth tile-depth 1)
           (draw-image-on-tile-1-to-1
             shredded-raster width height
             tile-width tile-height tile-depth tile-size
             x-scale y-scale
             no-transform-p inverse-transform
             color-map rgb-color-map
             buffer x0 y0))
          ((and (=f source-depth 8) (=f tile-depth 1))
           ;; 8bit -> 1bit: dithered.  Will only happen for a monochrome X server.
           (draw-image-on-tile-8-to-1
             shredded-raster width height
             tile-width tile-height tile-depth tile-size
             x-scale y-scale
             no-transform-p inverse-transform
             color-map rgb-color-map
             buffer x0 y0))
          ((and (=f source-depth 8) (or (=f tile-depth 24) (=f tile-depth 16)))
           (setq buffer (really-large-byte-vector))
           (draw-image-on-tile-8-to-truecolor
             shredded-raster width height
             tile-width tile-height tile-depth tile-size
             x-scale y-scale
             no-transform-p inverse-transform
             color-map rgb-color-map
             buffer
             x0
             y0
             image-left-offset-in-ws
             image-top-offset-in-ws
             (image-palette-is-gray-p
               (image-palette-of-gensym-window current-window))))
          (t
           (dwarn "Drawing from ~dbit to ~dbit rasters: should not happen."
                  source-depth tile-depth)))

    (c-x11-put-image pixmap 0 0 tile-width tile-height tile-depth 1 bytes-per-line buffer)
    pixmap))


(defun draw-image-on-tile-8-to-8
    (shredded-raster width height
                     tile-width tile-height tile-depth tile-size
                     x-scale y-scale
                     no-transform-p inverse-transform
                     color-map rgb-color-map
                     buffer x0 y0
                     image-left-offset-in-ws ; Additions vs -for-workspace version.
                     image-top-offset-in-ws)
  (declare (ignore rgb-color-map tile-size))
  (declare (ignore image-left-offset-in-ws)) ; Ignored!!
  (declare (ignore image-top-offset-in-ws))

  #+(and development (not lispworks)) (declare (optimize (speed 3) (safety 1) (space 0) (compilation-speed 0)))
  (cond ((and (=f x-scale y-scale (normalized-scale))
              no-transform-p)
         ;; Bummed loop for 1:1 scaling.  Knows about row buffers.
         (loop with index fixnum = 0
               with y1 = (+f y0 tile-height)
               with x1 = (+f x0 tile-width)
               for y-in-workspace fixnum from y0 below y1
               as row-buffer = (shredded-raster-buffer shredded-raster y-in-workspace)
               doing
           (align-image-scan-line buffer index tile-depth)
           (loop for x-in-workspace fixnum from x0 below x1
                 ;; Color dithering goes here.
                 as pixel = (fast-map-image-color
                              color-map
                              (byte-vector-aref row-buffer x-in-workspace))
                 doing
             (setf (byte-vector-aref buffer index) pixel)
             (incff index))))
        ;; Arbitrary scaling and rotation.
        (t
         (loop with index = 0
               with y1 = (+f y0 tile-height)
               with x1 = (+f x0 tile-width)
               with raster-width-1 = (-f (shredded-raster-width shredded-raster) 1)
               with raster-height-1 = (-f (shredded-raster-height shredded-raster) 1)
               for y fixnum from y0 below y1
               as y-in-workspace = (fast-delta-y-in-workspace y  y-scale)
               doing
           (align-image-scan-line buffer index tile-depth)
           (loop for x fixnum from x0 below x1
                 as x-in-raster = (fast-delta-x-in-workspace  x  x-scale)
                 as y-in-raster = y-in-workspace
                 do (orient-points-for-icon inverse-transform
                         (-f width 1)
                         (-f height 1)
                      x-in-raster y-in-raster)
                 as raster-val = (shredded-raster-ref-8
                                   shredded-raster
                                   (maxf (minf x-in-raster raster-width-1) 0)
                                   (maxf (minf y-in-raster raster-height-1) 0))
                 ;; Color dithering goes here.
                 as pixel = (fast-map-image-color
                              color-map
                              raster-val)
                 doing
             (setf (byte-vector-aref buffer index) pixel)
             (incff index))))))

;; We probably want to do some averaging here for very large reductions.
;; Unfortunately, for color images, we would have to average the original RGB
;; values and find the closest gensym color again.


;;; The function `draw-image-on-tile-24-to-24' is used for both workspace backgrounds
;;; and icon backgrounds.

(defun draw-image-on-tile-24-to-24
    (shredded-raster width height        ; Rotated raster width&height.
                     tile-width tile-height tile-depth tile-size
                     x-scale y-scale
                     no-transform-p inverse-transform
                     color-map rgb-color-map
                     buffer x0 y0
                     image-left-offset-in-ws
                     image-top-offset-in-ws)
  (declare (ignore color-map rgb-color-map tile-size))
  (declare (ignore image-left-offset-in-ws))
  (declare (ignore image-top-offset-in-ws))
  #+(and development (not lispworks)) 
  (declare (optimize (speed 3) (safety 1) (space 0) (compilation-speed 0)))
  (cond ((and (=f x-scale y-scale (normalized-scale))
              no-transform-p)
         ;; Bummed loop for 1:1 scaling.  Knows about row buffers.
         (loop with index fixnum = 0
               with y1 = (+f y0 tile-height)
               with x1 = (+f x0 tile-width)
               with k0 = (*f 3 x0)
               with k1 = (*f 3 x1)
               for y-in-workspace fixnum from y0 below y1
               as row-buffer = (shredded-raster-buffer shredded-raster y-in-workspace)
               doing
           (align-image-scan-line buffer index tile-depth)
           ;; TODO: Try to make this inner loop be memcpy()
           ;; If we chunked together scan lines (>1 per buffer), we could
           ;; do more here.  Perhaps, store entire image in one byte-vector,
           ;; ready to hand to X and Win32?
           (loop for x fixnum from k0 below k1 by 3 doing
             ;; Buffer wants BGR not RGB !!
             (setf (byte-vector-aref buffer index) (byte-vector-aref row-buffer (+f x 2)))
             (incff index)
             (setf (byte-vector-aref buffer index) (byte-vector-aref row-buffer (+f x 1)))
             (incff index)
             (setf (byte-vector-aref buffer index) (byte-vector-aref row-buffer x))
             (incff index))))

        ;; Arbitrary scaling and rotation.
        (t
         (loop with index fixnum = 0
               with y1 = (+f y0 tile-height)
               with x1 = (+f x0 tile-width)
               with raster-width-1 = (-f (shredded-raster-width shredded-raster) 1)
               with raster-height-1 = (-f (shredded-raster-height shredded-raster) 1)
               for y fixnum from y0 below y1
               as y-in-workspace = (fast-delta-y-in-workspace y  y-scale)
               doing
           (align-image-scan-line buffer index tile-depth)
           (loop for x fixnum from x0 below x1
                 as x-in-raster = (fast-delta-x-in-workspace  x  x-scale)
                 as y-in-raster = y-in-workspace
                 do (orient-points-for-icon inverse-transform
                        (-f width 1)
                        (-f height 1)
                      x-in-raster y-in-raster)
                 ;; TODO: we are packing then immediately unpacking the RGB value here.
                 as rgb = (shredded-raster-ref-24
                                   shredded-raster
                                   (maxf (minf x-in-raster raster-width-1) 0)
                                   (maxf (minf y-in-raster raster-height-1) 0))
                 doing
             ;; Buffer wants BGR not RGB !!
             (setf (byte-vector-aref buffer index) (blue-part-of-rgb rgb))
             (incff index)
             (setf (byte-vector-aref buffer index) (green-part-of-rgb rgb))
             (incff index)
             (setf (byte-vector-aref buffer index) (red-part-of-rgb rgb))
             (incff index))))))


;;; The function `draw-image-on-tile-8-to-truecolor' is used for icon background
;;; images.

(defun draw-image-on-tile-8-to-truecolor
    (shredded-raster width height
                     tile-width tile-height tile-depth tile-size
                     x-scale y-scale
                     no-transform-p inverse-transform
                     color-map                ; byte->screenpixel
                     rgb-color-map        ; byte->rgb color
                     buffer x0 y0
                     image-left-offset-in-ws
                     image-top-offset-in-ws
                     draw-in-gray-p)
  (declare (ignore color-map tile-size))
  (declare (ignore image-left-offset-in-ws))
  (declare (ignore image-top-offset-in-ws))
  #+(and development (not lispworks)) 
  (declare (optimize (speed 3) (safety 1) (space 0) (compilation-speed 0)))

  (cond ((and (=f x-scale y-scale (normalized-scale))
              no-transform-p)
         ;; Bummed loop for 1:1 scaling.  Knows about row buffers.
         (loop with index fixnum = 0
               with y1 = (+f y0 tile-height)
               with x1 = (+f x0 tile-width)
               for y-in-workspace fixnum from y0 below y1
               as row-buffer = (shredded-raster-buffer shredded-raster y-in-workspace)
               doing
           (align-image-scan-line buffer index tile-depth)
           (loop for x-in-workspace fixnum from x0 below x1
                 as rgb = (managed-svref
                              rgb-color-map
                              (byte-vector-aref row-buffer x-in-workspace))
                 doing
             (cond
               (draw-in-gray-p
                (let ((gray (rgb-to-gray rgb)))
                  (setf (byte-vector-aref buffer index) gray)
                  (setf (byte-vector-aref buffer (incff index)) gray)
                  (setf (byte-vector-aref buffer (incff index)) gray)))
               (t
                (setf (byte-vector-aref buffer index) (blue-part-of-rgb rgb))
                (setf (byte-vector-aref buffer (incff index)) (green-part-of-rgb rgb))
                (setf (byte-vector-aref buffer (incff index)) (red-part-of-rgb rgb))))
             (incff index))))
        ;; Arbitrary scaling and rotation.
        (t
         (loop with index = 0
               with y1 = (+f y0 tile-height)
               with x1 = (+f x0 tile-width)
               with raster-width-1 = (-f (shredded-raster-width shredded-raster) 1)
               with raster-height-1 = (-f (shredded-raster-height shredded-raster) 1)
               for y fixnum from y0 below y1
               as y-in-workspace = (fast-delta-y-in-workspace y  y-scale)
               doing
           (align-image-scan-line buffer index tile-depth)
           (loop for x fixnum from x0 below x1
                 as x-in-raster = (fast-delta-x-in-workspace  x  x-scale)
                 as y-in-raster = y-in-workspace
                 do (orient-points-for-icon inverse-transform
                         (-f width 1)
                         (-f height 1)
                      x-in-raster y-in-raster)
                 as rgb = (managed-svref
                              rgb-color-map
                              (shredded-raster-ref-8
                                shredded-raster
                                (maxf (minf x-in-raster raster-width-1) 0)
                                (maxf (minf y-in-raster raster-height-1) 0)))
                 doing
             (cond
               (draw-in-gray-p
                (let ((gray (rgb-to-gray rgb)))
                  (setf (byte-vector-aref buffer index) gray)
                  (setf (byte-vector-aref buffer (incff index)) gray)
                  (setf (byte-vector-aref buffer (incff index)) gray)))
               (t
                (setf (byte-vector-aref buffer index) (blue-part-of-rgb rgb))
                (setf (byte-vector-aref buffer (incff index)) (green-part-of-rgb rgb))
                (setf (byte-vector-aref buffer (incff index)) (red-part-of-rgb rgb))))
             (incff index))))))


(defun draw-mask-on-tile (shredded-raster width height
                                          source-depth mask-pixmap?
                                          tile-width tile-height
                                          x-scale y-scale
                                          inverse-transform
                                          color-map
                                          transparent-color?
                                          buffer x0 y0
                                          transparent-color-index
                                          is-gif)
  (cond ((null transparent-color?)
         #+development
         (when mask-pixmap?
           (cerror  "Go on" "Unused mask pixmap for non-transparent image.(see pbk)")))
        ((null mask-pixmap?)
         #+development
         (cerror "Go on" "Missing mask pixmap for transparencey implementation"))
        ((=f source-depth 8)
         (draw-mask-on-tile-1 shredded-raster width height
                              tile-width tile-height
                              x-scale y-scale
                              inverse-transform
                              color-map
                              transparent-color?
                              buffer x0 y0
                              transparent-color-index
                              is-gif)
         (c-x11-put-image mask-pixmap? 0 0 tile-width tile-height 1 1
                          (compute-bytes-per-scan-line tile-width 1)
                          buffer)
         t)
        ((=f source-depth 1)
         (dwarn "1 to 1 mask generation not implemented yet.(see pbk)"))
        (t
         #+development
         (cerror "Go on" "Unknown source depth for mask implementation.(see pbk)"))))


;;; The function `draw-image-on-tile-for-workspace' is used for rendering
;;; workspace background images.  It's at the bottom of a long call-chain
;;; starting with the ICP message `paint-image-in-current-window'.

(defun draw-image-on-tile-for-workspace
    (image-data pixmap? mask-pixmap?
                i j tile-size tile-width tile-height tile-depth
                x-scale y-scale reflection-and-rotation
                color-map rgb-color-map draw-opaque-p)
  (let* ((x0 (*f j tile-size))
         (y0 (*f i tile-size))
         (buffer (large-byte-vector))
         (shredded-raster (image-data-cache? image-data))
         (source-depth (shredded-raster-depth shredded-raster))
         (width (shredded-raster-width shredded-raster))
         (height (shredded-raster-height shredded-raster))
         (no-transform-p (identity-reflection-and-rotation-p reflection-and-rotation))
         (inverse-transform (fast-invert-reflection-and-rotation reflection-and-rotation))
         (transparent-color-index (image-data-transparent-color-index image-data))
         (transparent-color?
           (and transparent-color-index
                (not draw-opaque-p)
                (/=f -1 transparent-color-index)
                (managed-svref rgb-color-map transparent-color-index)))
         (bytes-per-line
           (compute-bytes-per-scan-line tile-width tile-depth)))

    ;; These are the width and height of the source image after rotation but
    ;; before scaling.
    (when (rotated-by-90-p reflection-and-rotation)
      (psetq width height
             height width))

    (draw-mask-on-tile shredded-raster width height
                       source-depth mask-pixmap?
                       tile-width tile-height
                       x-scale y-scale
                       inverse-transform
                       rgb-color-map
                       transparent-color?
                       buffer x0 y0
                       transparent-color-index
                       (eq (image-data-format image-data) 'gif))

    (cond ((=f source-depth tile-depth 8)
           (draw-image-on-tile-8-to-8-for-workspace
             shredded-raster width height
             tile-width tile-height tile-depth tile-size
             x-scale y-scale
             no-transform-p inverse-transform
             color-map rgb-color-map
             buffer x0 y0))
          ((=f source-depth tile-depth 24)
           (setq buffer (really-large-byte-vector))
           (draw-image-on-tile-24-to-24        ; ************** -for-workspace version?
             shredded-raster width height
             tile-width tile-height tile-depth tile-size
             x-scale y-scale
             no-transform-p inverse-transform
             color-map rgb-color-map        ; Ignored
             buffer
             x0
             y0
             0 0))
          ((=f source-depth tile-depth 1)
           (draw-image-on-tile-1-to-1
             shredded-raster width height
             tile-width tile-height tile-depth tile-size
             x-scale y-scale
             no-transform-p inverse-transform
             color-map rgb-color-map
             buffer x0 y0))
          ((and (=f source-depth 8) (=f tile-depth 1))
           ;; 8bit -> 1bit: dithered.  Will only happen for a monochrome X server.
           (draw-image-on-tile-8-to-1
             shredded-raster width height
             tile-width tile-height tile-depth tile-size
             x-scale y-scale
             no-transform-p inverse-transform
             color-map rgb-color-map
             buffer x0 y0))
          ((and (=f source-depth 8) (or (=f tile-depth 24) (=f tile-depth 16)))
           (setq buffer (really-large-byte-vector))
           (draw-image-on-tile-8-to-truecolor-for-workspace
             shredded-raster width height
             tile-width tile-height tile-depth tile-size
             x-scale y-scale
             no-transform-p inverse-transform
             color-map rgb-color-map
             buffer x0 y0
             (image-palette-is-gray-p
               (image-palette-of-gensym-window current-window))))
          (t
           (dwarn "Drawing from ~dbit to ~dbit rasters: should not happen." source-depth tile-depth)))

    ;; Now bitblt the buffer into the actual stored raster tile using OR.
    (when pixmap?
      (c-x11-put-image pixmap? 0 0 tile-width tile-height tile-depth 1 bytes-per-line buffer))
    buffer))



;;; The function `draw-image-on-tile-8-to-8-for-workspace' renders one tile's
;;; worth from raster into buffer, scaling and color mapping as needed.  Used
;;; for workspace background images.

(defun draw-image-on-tile-8-to-8-for-workspace
    (shredded-raster width height
                     tile-width tile-height tile-depth tile-size
                     x-scale y-scale
                     no-transform-p inverse-transform
                     color-map rgb-color-map
                     buffer x0 y0)
  (declare (ignore rgb-color-map tile-size))
  #+(and development (not lispworks)) 
  (declare (optimize (speed 3) (safety 1) (space 0) (compilation-speed 0)))

  ;; Pixmap to pixmap.  Fill buffer with color-mapped image data in the ZPixmap
  ;; format desired by XCreateImage.

  (cond ((and (=f x-scale y-scale (normalized-scale))
              no-transform-p)
         ;; Bummed loop for 1:1 scaling.  Knows about row buffers.
         (loop with index fixnum = 0
               with y1 = (+f y0 tile-height)
               with x1 = (+f x0 tile-width)
               for y-in-workspace fixnum from y0 below y1
               as row-buffer = (shredded-raster-buffer shredded-raster y-in-workspace)
               doing
           (align-image-scan-line buffer index tile-depth)
           (loop for x-in-workspace fixnum from x0 below x1
                 ;; Color dithering goes here.
                 as pixel = (fast-map-image-color
                              color-map
                              (byte-vector-aref row-buffer x-in-workspace))
                 doing
             (setf (byte-vector-aref buffer index) pixel)
             (incff index))))
        ;; Arbitrary scaling and rotation.
        (t
         (loop with index = 0
               with y1 = (+f y0 tile-height)
               with x1 = (+f x0 tile-width)
               for y fixnum from y0 below y1
               as y-in-workspace = (fast-delta-y-in-workspace y y-scale)
               doing
           (align-image-scan-line buffer index tile-depth)
           (loop for x fixnum from x0 below x1
                 as x-in-raster = (fast-delta-x-in-workspace x x-scale)
                 as y-in-raster = y-in-workspace
                 do (orient-points-for-icon inverse-transform width height x-in-raster y-in-raster)
             ;; Color dithering goes here.
                 as pixel = (fast-map-image-color
                              color-map
                              (shredded-raster-ref-8
                                shredded-raster
                                x-in-raster y-in-raster))
                 doing
             (setf (byte-vector-aref buffer index) pixel)
             (incff index))))))

;;; The function `draw-image-on-tile-8-to-truecolor-for-workspace' is used for
;;; workspace background drawing.

(defun draw-image-on-tile-8-to-truecolor-for-workspace
    (shredded-raster width height
                     tile-width tile-height tile-depth tile-size
                     x-scale y-scale
                     no-transform-p inverse-transform
                     color-map rgb-color-map
                     buffer x0 y0 draw-in-gray-p)
  (declare (ignore color-map tile-size))
  #+(and development (not lispworks)) 
  (declare (optimize (speed 3) (safety 1) (space 0) (compilation-speed 0)))

  ;; Pixmap to pixmap.  Fill buffer with color-mapped image data in the ZPixmap
  ;; format desired by XCreateImage.

  (cond ((and (=f x-scale y-scale (normalized-scale))
              no-transform-p)
         ;; Bummed loop for 1:1 scaling.  Knows about row buffers.
         (loop with index fixnum = 0
               with y1 = (+f y0 tile-height)
               with x1 = (+f x0 tile-width)
               for y-in-workspace fixnum from y0 below y1
               as row-buffer = (shredded-raster-buffer shredded-raster y-in-workspace)
               doing
           (align-image-scan-line buffer index tile-depth)
           (loop for x-in-workspace fixnum from x0 below x1
                 as pixel = (managed-svref
                              rgb-color-map
                              (byte-vector-aref row-buffer x-in-workspace))
                 doing
             (cond
               (draw-in-gray-p
                (let ((gray (rgb-to-gray pixel)))
                  (setf (byte-vector-aref buffer index) gray)
                  (setf (byte-vector-aref buffer (incff index)) gray)
                  (setf (byte-vector-aref buffer (incff index)) gray)))
               (t
                (setf (byte-vector-aref buffer index) (blue-part-of-rgb pixel))
                (setf (byte-vector-aref buffer (incff index)) (green-part-of-rgb pixel))
                (setf (byte-vector-aref buffer (incff index)) (red-part-of-rgb pixel))))
             (incff index))))
        ;; Arbitrary scaling and rotation.
        (t
         (loop with index fixnum = 0
               with y1 = (+f y0 tile-height)
               with x1 = (+f x0 tile-width)
               for y fixnum from y0 below y1
               as y-in-workspace = (fast-delta-y-in-workspace y y-scale)
               doing
           (align-image-scan-line buffer index tile-depth)
           (loop for x fixnum from x0 below x1
                 as x-in-raster = (fast-delta-x-in-workspace x x-scale)
                 as y-in-raster = y-in-workspace
                 do (orient-points-for-icon inverse-transform width height x-in-raster y-in-raster)
                 as pixel = (managed-svref
                              rgb-color-map
                              (shredded-raster-ref-8
                                shredded-raster
                                x-in-raster y-in-raster))
                 doing
             (cond
               (draw-in-gray-p
                (let ((gray (rgb-to-gray pixel)))
                  (setf (byte-vector-aref buffer index) gray)
                  (setf (byte-vector-aref buffer (incff index)) gray)
                  (setf (byte-vector-aref buffer (incff index)) gray)))
               (t
                (setf (byte-vector-aref buffer index) (blue-part-of-rgb pixel))
                (setf (byte-vector-aref buffer (incff index)) (green-part-of-rgb pixel))
                (setf (byte-vector-aref buffer (incff index)) (red-part-of-rgb pixel))))
             (incff index))))))


;;; The function `draw-image-on-tile-1-to-1' renders one tile's worth of bits
;;; from raster to buffer, scaling as needed.  Unlike the others, this one is
;;; used for BOTH icons AND workspaces!

(defun draw-image-on-tile-1-to-1
    (shredded-raster width height
                     tile-width tile-height tile-depth tile-size
                     x-scale y-scale
                     no-transform-p inverse-transform
                     color-map rgb-color-map
                     buffer x0 y0)
  (declare (ignore color-map rgb-color-map))
  #+(and development (not lispworks)) 
  (declare (optimize (speed 3) (safety 1) (space 0) (compilation-speed 0)))

  ;; Bitmap to bitmap.  For 1:1 scaling and a tile-size which is a multiple of
  ;; 8 (true for all the large tiles), we can copy entire bytes.  In all other
  ;; cases, we have to resort to bit-addressing.

  (cond ((and (=f x-scale y-scale (normalized-scale))
              (=f 0 (modf tile-size 8))
              no-transform-p)
         ;; 1:1 scaling, no rotation, nice tile size.
         (loop with index fixnum = 0
               with y1 = (+f y0 tile-height)
               with x0-byte = (bits-to-bytes x0)
               with x1-byte = (bits-to-bytes (+f x0 tile-width))
               for y-in-workspace fixnum from y0 below y1
               as row-buffer = (shredded-raster-buffer shredded-raster y-in-workspace)
               doing
           (align-image-scan-line buffer index tile-depth)
           (loop for x-in-workspace fixnum from x0-byte below x1-byte
                 as pixels = (byte-vector-aref row-buffer x-in-workspace)
                 doing
             (setf (byte-vector-aref buffer index) pixels)
             (incff index))))
        (t
         ;; Arbitrary scaling and rotation.
         (loop with index = 0
               with y1 = (+f y0 tile-height)
               with x1 = (+f x0 tile-width)
               for y fixnum from y0 below y1
               as y-in-workspace = (fast-delta-y-in-workspace y y-scale)
               as mask = 1
               as byte = 0
               doing
           (align-image-scan-line buffer index tile-depth)
           (loop for x fixnum from x0 below x1
                 as x-in-raster = (fast-delta-x-in-workspace x x-scale)
                 as y-in-raster = y-in-workspace
                 do
             (orient-points-for-icon inverse-transform (- width 1) (- height 1)
               x-in-raster y-in-raster)
                 as pixel = (progn
                              (shredded-raster-ref-1 shredded-raster
                                                     x-in-raster y-in-raster))
                 doing
             (when (>f pixel 0)
               (setq byte (logiorf byte mask)))
             (setq mask (ashf mask 1))
             (when (>=f mask 256)
               (setf (byte-vector-aref buffer index) byte
                     byte 0
                     mask 1)
               (incff index)))
           (when (>f mask 1)
             (setf (byte-vector-aref buffer index) byte)
             (incff index))))))


;;; The function `draw-mask-on-tile-1' is used for both icon background and
;;; workspace background drawing.  It is used to create the mask for the
;;; no-transparent bits of an image.

(defun draw-mask-on-tile-1
    (shredded-raster width height
                     tile-width tile-height
                     x-scale y-scale
                     inverse-transform
                     color-map
                     transparent-color
                     buffer x0 y0
                     transparent-color-index
                     is-gif)
  #+(and development (not lispworks)) 
  (declare (optimize (speed 3) (safety 1) (space 0) (compilation-speed 0)))
  (loop with index = 0
        with y1 = (+f y0 tile-height)
        with x1 = (+f x0 tile-width)
        with raster-width-1 = (-f (shredded-raster-width shredded-raster) 1)
        with raster-height-1 = (-f (shredded-raster-height shredded-raster) 1)
        for y fixnum from y0 below y1
        as y-in-workspace = (fast-delta-y-in-workspace y y-scale)
        as mask = 1
        as byte = 0
        doing
    (align-image-scan-line buffer index 1)
    (loop for x fixnum from x0 below x1
          as x-in-raster = (fast-delta-x-in-workspace x x-scale)
          as y-in-raster = y-in-workspace
          do (orient-points-for-icon inverse-transform
                 (-f width 1)(-f height 1)
               x-in-raster y-in-raster)
          as pixel = (shredded-raster-ref-8
                       shredded-raster
                       (maxf (minf x-in-raster raster-width-1) 0)
                       (maxf (minf y-in-raster raster-height-1) 0))
          as pixel-color = (managed-svref color-map pixel)
          as blackp = (if is-gif
                        (/=f pixel transparent-color-index)
                        (/=f pixel-color transparent-color))
          doing
      (when blackp
        (setq byte (logiorf byte mask)))
      (setq mask (ashf mask 1))
      (when (>=f mask 256)
        (setf (byte-vector-aref buffer index) byte
              byte 0
              mask 1)
        (incff index)))
    (when (>f mask 1)
      (setf (byte-vector-aref buffer index) byte)
      (incff index))))


;;; The function `draw-image-on-tile-8-to-1' dithers one tile's worth of pixels
;;; from raster into buffer.  Used by icon AND workspace drawing!

(defun draw-image-on-tile-8-to-1
    (shredded-raster width height
                     tile-width tile-height tile-depth tile-size
                     x-scale y-scale
                     no-transform-p inverse-transform
                     color-map rgb-color-map
                     buffer x0 y0)
  (declare (ignore tile-size no-transform-p color-map))
  #+(and development (not lispworks)) 
  (declare (optimize (speed 3) (safety 1) (space 0) (compilation-speed 0)))

  (let ((gray-map
          (create-gray-map-from-color-map rgb-color-map)))
    (loop with index = 0
          with y1 = (+f y0 tile-height)
          with x1 = (+f x0 tile-width)
          with raster-width-1 = (-f (shredded-raster-width shredded-raster) 1)
          with raster-height-1 = (-f (shredded-raster-height shredded-raster) 1)
          for y fixnum from y0 below y1
          as y-in-workspace = (fast-delta-y-in-workspace y y-scale)
          as mask = 1
          as byte = 0
          doing
      (align-image-scan-line buffer index tile-depth)
      (loop for x fixnum from x0 below x1
            as x-in-raster = (fast-delta-x-in-workspace x x-scale)
            as y-in-raster = y-in-workspace
            do (orient-points-for-icon inverse-transform (-f width 1) (-f height 1)
                 x-in-raster y-in-raster)
            as black? = (shredded-raster-ref-8-black-p        ; Dithered
                          shredded-raster
                          (maxf (minf x-in-raster raster-width-1) 0)
                          (maxf (minf y-in-raster raster-height-1) 0)
                          x y
                          gray-map)
            doing
        (when black?
          (setq byte (logiorf byte mask)))
        (setq mask (ashf mask 1))
        (when (>=f mask 256)
          (setf (byte-vector-aref buffer index) byte
                byte 0
                mask 1)
          (incff index)))
      (when (>f mask 1)
        (setf (byte-vector-aref buffer index) byte)
        (incff index)))
    (reclaim-managed-array gray-map)))

;; I would like to use an error diffusion algorithm here, but tiling greatly
;; complicates that approach.  To avoid artifacts at tile boundaries, I'd have
;; to keep around error sums for adjacent tiles (or something).

;; Solution: error diffuse over entire image and cache it long enough to draw
;; and cache the tiles, at each scale.  This must be redone at each image scale
;; else it looks horrible again.  The present dithering algorithm is so bad as
;; to be useless.  Nowadays we have the CPU power to do it right. -fmw, 1/3/02


;;; The function `draw-missing-image-on-window' draws a missing or incomplete
;;; image, assuming we at least know its width and height.

(defun draw-missing-image-on-window
    (image-data gensym-window x-in-window y-in-window
                left top right bottom
                x-scale y-scale rotation quality foreground-color background-color)
  (declare (ignore rotation quality))
  (let* ((width (image-data-width image-data))
         (height (image-data-height image-data))
         (dw (delta-x-in-window width x-scale))
         (dh (delta-y-in-window height y-scale))
         (x1 x-in-window)
         (y1 y-in-window)
         (x2 (+r x-in-window dw))
         (y2 (+r y-in-window dh)))
    (draw-missing-image gensym-window left top right bottom x1 y1 x2 y2
                        foreground-color background-color)))

(defun draw-missing-icon-background-image
    (image-data gensym-window
                x-in-window y-in-window
                left top right bottom ;draw-area-bounds
                x-scale y-scale
                rotation quality
                foreground-color background-color
                left-offset-in-workspace
                top-offset-in-workspace
                rotation-width                ; rotated-width-in-ws
                rotation-height)        ; rotated-height-in-ws
  (declare (ignore quality))
  (let ((rotated-by-90-p (rotated-by-90-p rotation)))
    (multiple-value-bind
        (oriented-image-left
          oriented-image-top
          oriented-image-right
          oriented-image-bottom)
        (compute-oriented-destination-for-image
          image-data
          x-in-window y-in-window
          left-offset-in-workspace top-offset-in-workspace
          (if rotated-by-90-p rotation-height rotation-width)
          (if rotated-by-90-p rotation-width rotation-height)
          rotation
          (if rotated-by-90-p y-scale x-scale)
          (if rotated-by-90-p x-scale y-scale))
      (draw-missing-image gensym-window
                          left top right bottom
                          oriented-image-left
                          oriented-image-top
                          oriented-image-right
                          oriented-image-bottom
                          foreground-color background-color))))


;;; The function `draw-missing-image' draws a pattern to represent a missing
;;; image, assuming we know its size. The clipping area is given by left, top,
;;; right, bottom, and the rectangle potentially affected by the image pixels
;;; is given by x1, y1, x2, y2, all in window coordinates.

(defun draw-missing-image (gensym-window left top right bottom x1 y1 x2 y2
                                         foreground-color background-color &optional no-box)
  (let ((x1 (maxr left x1))
        (y1 (maxr top y1))
        (x2 (minr right x2))
        (y2 (minr bottom y2)))
    (when (and (<r x1 x2) (<r y1 y2))
      (c-x11-draw-rectangle (native-window? gensym-window) x1 y1 (-f x2 x1) (-f y2 y1)
                            background-color x11-copy)))
  (unless no-box
    (draw-hollow-rectangle-on-window
      (native-window? gensym-window) x1 y1 (-r x2 1) (-r y2 1)
      left top right bottom foreground-color)))


;;; The function `draw-hollow-rectangle' draws a hollow rectangle on a native
;;; window given corners (xy12), clipping region (ltrb), and color.

(defun draw-hollow-rectangle-on-window (native-window x1 y1 x2 y2 left top right bottom color)
  (let ((points (gensym-list x1 y1 x2 y1 x2 y2 x1 y2 x1 y1)))
    (draw-wide-polyline-on-window native-window left top right bottom
                                  color x11-copy 0 ps-solid nil points)
    (reclaim-gensym-list points)))


;;; The function `draw-image-on-window' paints the rectangle of the given image
;;; plane given by left,top,right,bottom, in window coordinates from the given
;;; image-data.  We paint the correct portion of the given image, appropriately
;;; scaled and rotated.  X,Y-in-window is the position of the upper-left corner
;;; of the image in the window.  What we paint is cached in an image-rendering
;;; object.

(defun draw-image-on-window                ; Entry point
    (image-data gensym-window
                x-in-window y-in-window
                left top right bottom x-scale y-scale
                rotation quality
                foreground-color background-color)
  ;; Image-data may be missing if it was readable when the header was first
  ;; read, but unreadable or changed when the pixels were read.
  (cond ((null (ensure-image-data-pixels image-data))
         (draw-missing-image-on-window
           image-data gensym-window x-in-window y-in-window
           left top right bottom
           x-scale y-scale
           rotation quality
           foreground-color background-color))
        (t
         (draw-valid-image-on-window
           image-data gensym-window
           x-in-window y-in-window
           left top right bottom x-scale y-scale
           rotation quality
           foreground-color background-color))))

(defun draw-valid-image-on-window
    (image-data gensym-window
                x-in-window y-in-window
                left top right bottom x-scale y-scale
                rotation quality
                foreground-color background-color)
  (let* ((image-rendering
           (find-or-create-image-rendering
             image-data gensym-window x-scale y-scale rotation quality))
         (rgb-color-map                                            ; The byte->rgb color map
           (image-data-color-map image-data))
         (color-map                                            ; The byte->screenpixel map.
           (ensure-image-rendering-color-map image-rendering))
         (transparent-color-index
           (image-data-transparent-color-index image-data))
         (transparentp (/=f -1 transparent-color-index))
         (tiled-raster
           (image-rendering-tiled-raster image-rendering))
         (tile-depth (bits-per-pixel-for-tiled-raster tiled-raster))
         (window-depth
           (window-screen-depth gensym-window))
         (synced? nil))

    ;; GIFS have an opinion about their colors, even when 1bit deep.
    (when (and (=f 1 (image-data-depth image-data))
               (eq (image-data-format image-data) 'gif))
      (if (>f window-depth 8)
          (let ((rgb-foreground-color (managed-svref rgb-color-map 1))
                (rgb-background-color (managed-svref rgb-color-map 0)))

            (setq foreground-color (reverse-rgb-bits rgb-foreground-color)
                  background-color (reverse-rgb-bits rgb-background-color)))

          (setq foreground-color (fast-map-image-color color-map 1)
                background-color (fast-map-image-color color-map 0))))

    (do-overlapping-tiles-of-image-rendering
        (image-tile? x0 y0 tile-width tile-height image-rendering
                     (-r left x-in-window)
                     (-r top y-in-window)
                     (-r right x-in-window)
                     (-r bottom y-in-window))

      (let* ((dest-x (maxr left (+f x0 x-in-window)))
             (dest-y (maxr top (+f y0 y-in-window)))
             (dest-right (minr right (+f x0 x-in-window tile-width)))
             (dest-bottom (minr bottom (+f y0 y-in-window tile-height)))
             (width (-f dest-right dest-x))
             (height (-f dest-bottom dest-y))
             (src-x (-f dest-x (+f x0 x-in-window)))
             (src-y (-f dest-y (+f y0 y-in-window)))
             (cached? (not (null image-tile?))))

        (cond (drawing-to-printer-p
               (draw-image-tile-on-printer
                 gensym-window
                 image-data
                 i j tile-size tile-width tile-height
                 x-scale y-scale rotation
                 rgb-color-map
                 src-x src-y width height
                 dest-x dest-y
                 foreground-color background-color))

              ((setq image-tile? (ensure-image-tile image-rendering j i transparentp quality))
               (let ((pixmap (image-tile-stored-raster image-tile?))
                     (mask-pixmap?  (image-tile-stored-mask-raster image-tile?)))
                 (unless cached?
                   (unless synced?
                     (c-x11-sync (native-window? gensym-window))
                     (setq synced? t))
                   ;; Draws image portion to buffer, then blits buffer to pixmap
                   ;; and mask-pixmap if non-NIL.
                   (draw-image-on-tile-for-workspace
                     image-data pixmap mask-pixmap?
                     i j tile-size tile-width tile-height tile-depth
                     x-scale y-scale rotation
                     color-map rgb-color-map nil))
                 (when (and (>f width 0) (>f height 0))                    ; Should always be true.
                   (c-x11-draw-pixmap pixmap
                                      (native-window? gensym-window)
                                      -1 ;workspace backgrounds assumed to be opaque (ie no mask)
                                      src-x src-y width height
                                      dest-x dest-y foreground-color background-color))))
              (t
               ;; Out of mem. Draw a solid rectangle in the background color.
               ;; (Probably should draw some more distinctive pattern)
               (c-x11-draw-rectangle
                 (native-window? gensym-window) dest-x dest-y width height
                 background-color x11-copy)))))))


;;; The function `compute-rgbquads' returns a Win32 RGBQUADs color-map, suitable
;;; for passing to c-x11-stretch-bits.

(defun compute-rgbquads (rgb-color-map ncolors foreground background)
  (let ((buffer (allocate-byte-vector (*f ncolors 4)))
        (j -1))
    (macrolet ((addquad (rgb)
                 `(let ((v ,rgb))
                    (setf (byte-vector-aref buffer (incff j)) (blue-part-of-rgb v)
                          (byte-vector-aref buffer (incff j)) (green-part-of-rgb v)
                          (byte-vector-aref buffer (incff j)) (red-part-of-rgb v)
                          (byte-vector-aref buffer (incff j)) 0))))
      (cond ((=f ncolors 2)
             (addquad (reverse-rgb-bits background))
             (addquad (reverse-rgb-bits foreground)))
            (t
             (loop for i below ncolors
                   do (addquad (managed-svref rgb-color-map i))))))
    buffer))


(defparameter identity-color-map nil)

(defun identity-color-map ()
  (or identity-color-map
      (let ((map (allocate-byte-vector 256)))
        (loop for i below 256 doing
          (setf (byte-vector-aref map i) i))
        (setq identity-color-map map))))

;;; The function `draw-image-tile-on-printer' draws given image-data directly to
;;; the destination, without creating or caching an image-rendering.

(defun draw-image-tile-on-printer
    (gensym-window image-data
                   i j tile-size tile-width tile-height
                   x-scale y-scale rotation
                   rgb-color-map
                   src-x src-y width height
                   dest-x dest-y
                   foreground background)
  (let* ((overriding-alignment 4) ; c-x11-stretch-bits has different alignment requirements
         (src-depth (image-data-depth image-data))
         (ncolors (image-data-number-of-colors image-data))
         (buffer (draw-image-on-tile-for-workspace
                   image-data nil nil
                   i j tile-size tile-width tile-height src-depth
                   x-scale y-scale rotation
                   (identity-color-map) rgb-color-map t))
         (rgbquads (compute-rgbquads rgb-color-map ncolors foreground background))
         (buflen (*f height (compute-bytes-per-scan-line width src-depth))))
    (c-x11-stretch-bits
      (native-window? gensym-window)
      src-x src-y width height src-depth
      dest-x dest-y width height
      tile-width
      rgbquads ncolors
      buffer buflen)
    (reclaim-byte-vector rgbquads)))


(defun compute-oriented-destination-for-image
    (image-data x-in-window
                y-in-window
                image-left-offset-in-ws image-top-offset-in-ws ; specvars!
                rotation-width rotation-height
                rotation
                x-scale y-scale)
  (let* ((icon-width (delta-x-in-window rotation-width x-scale))
         (icon-height (delta-y-in-window rotation-height y-scale))
         (image-width (delta-x-in-window
                        (image-data-width image-data) x-scale))
         (image-height (delta-y-in-window
                         (image-data-height image-data) y-scale))
         (image-x-pos (+r x-in-window
                          (delta-x-in-window
                            image-left-offset-in-ws x-scale))) ; Only use of these
         (image-y-pos (+r y-in-window
                          (delta-y-in-window
                            image-top-offset-in-ws y-scale))) ; ditto
         (image-left (maxr x-in-window image-x-pos))
         (image-top (maxr y-in-window image-y-pos))
         (image-right (minr (+r x-in-window icon-width)
                            (+r image-x-pos image-width)))
         (image-bottom (minr (+r y-in-window icon-height)
                             (+r image-y-pos image-height)))
         (oriented-image-left (-r image-left x-in-window))
         (oriented-image-top (-r image-top y-in-window))
         (oriented-image-right (-r image-right x-in-window))
         (oriented-image-bottom (-r image-bottom y-in-window)))
    (orient-points-for-icon rotation icon-width icon-height
      oriented-image-left oriented-image-top
      oriented-image-right oriented-image-bottom)
    (psetf oriented-image-left
           (+r (minr oriented-image-left oriented-image-right)
               x-in-window)
           oriented-image-top
           (+r (minr oriented-image-top oriented-image-bottom)
               y-in-window)
           oriented-image-right
           (+r (maxr oriented-image-left oriented-image-right)
               x-in-window)
           oriented-image-bottom
           (+r (maxr oriented-image-top oriented-image-bottom)
               y-in-window))
    (values oriented-image-left
            oriented-image-top
            oriented-image-right
            oriented-image-bottom)))

(defun compute-oriented-bounds-of-icon-in-image-coordinates
    (image-data icon-width icon-height
                image-left-offset image-top-offset
                rotation
                x-scale y-scale)
  (let* ((image-width (image-data-width image-data))
         (image-height (image-data-height image-data))
         (left (-f image-left-offset))
         (top (-f image-top-offset))
         (right (+f left icon-width))
         (bottom (+f top icon-height)))
    (orient-points-for-icon rotation image-width image-height
      left top right bottom)
    (psetf left
           (delta-x-in-window (minf left right) x-scale)
           top
           (delta-y-in-window (minf top bottom) y-scale)
           right
           (delta-x-in-window (maxf left right) x-scale)
           bottom
           (delta-y-in-window (maxf top bottom) y-scale))
    (values left top right bottom)))

(defun compute-clipped-region-of-rendering-to-draw
     (image-data x-in-window y-in-window
                 left top right bottom
                 image-left-offset-in-ws image-top-offset-in-ws
                 rotation-width rotation-height
                 rotation
                 x-scale y-scale)
  (let* ((rotated-by-90-p
           (rotated-by-90-p rotation))
         (oriented-image-width
           (if rotated-by-90-p
               (delta-x-in-window (image-data-height image-data) x-scale)
               (delta-x-in-window (image-data-width image-data) x-scale)))
         (oriented-image-height
           (if rotated-by-90-p
               (delta-y-in-window (image-data-width image-data) y-scale)
               (delta-y-in-window (image-data-height  image-data) y-scale)))
         ;;shift drawing area ltrb into icon-coordinates
         (oriented-image-left (-r left x-in-window))
         (oriented-image-top (-r top y-in-window))
         (oriented-image-right (-r right x-in-window))
         (oriented-image-bottom (-r bottom y-in-window))
         ileft itop iright ibottom)
   (multiple-value-setf
     (ileft itop iright ibottom)
     (compute-oriented-bounds-of-icon-in-image-coordinates
       image-data rotation-width rotation-height
       image-left-offset-in-ws image-top-offset-in-ws
       rotation
       x-scale y-scale))
   ;; shift draw area ltrb into image coordinates
   (setf  oriented-image-left
          (maxf 0 (+f oriented-image-left ileft))
          oriented-image-top
          (maxf 0 (+f oriented-image-top itop))
          oriented-image-right
          (minf oriented-image-width
                (+f oriented-image-right ileft))
          oriented-image-bottom
          (minf  oriented-image-height
                (+f oriented-image-bottom itop)))
    (values oriented-image-left
            oriented-image-top
            oriented-image-right
            oriented-image-bottom)))


;;; The function `draw-icon-background-image-on-window' draws on icon background
;;; directly onto the window (no use of scratchpad rasters).

(defvar is-icon-mask-drawing nil)

(defun draw-icon-background-image-on-window
    (image-data gensym-window
                x-in-window y-in-window
                left-offset-in-workspace top-offset-in-workspace
                rotated-width-in-ws rotated-height-in-ws
                draw-area-left draw-area-top draw-area-right draw-area-bottom
                x-scale y-scale rotation quality
                foreground-color background-color)
  (cond ((null (ensure-image-data-pixels image-data))
         (draw-missing-icon-background-image
           image-data gensym-window
           x-in-window y-in-window
           draw-area-left draw-area-top draw-area-right draw-area-bottom
           x-scale y-scale rotation quality
           foreground-color background-color
           left-offset-in-workspace top-offset-in-workspace
           rotated-width-in-ws rotated-height-in-ws))
        (t
         (draw-icon-background-image-on-window-1
           image-data gensym-window
           x-in-window y-in-window
           draw-area-left draw-area-top draw-area-right draw-area-bottom
           x-scale y-scale rotation quality
           foreground-color background-color
           left-offset-in-workspace top-offset-in-workspace
           rotated-width-in-ws rotated-height-in-ws))))

(defun draw-icon-background-image-on-window-1
    (image-data gensym-window
                x-in-window y-in-window
                left top right bottom ;draw-area-bounds
                x-scale y-scale
                rotation quality
                foreground-color background-color
                image-left-offset-in-ws        ; Special variables!
                image-top-offset-in-ws
                rotation-width                ; rotated-width-in-ws
                rotation-height)        ; rotated-height-in-ws
  (let* ((rotated-by-90-p
           (rotated-by-90-p rotation))
         (image-rendering
           (find-or-create-image-rendering
             image-data gensym-window
             (if rotated-by-90-p y-scale x-scale)
             (if rotated-by-90-p x-scale y-scale)
             rotation quality))
         (transparent-color-index
           (or (image-data-transparent-color-index image-data) -1))
         (transparentp (/=f -1 transparent-color-index))
         (rgb-color-map            ; The byte->rgb color map
           (image-data-color-map image-data))
         (color-map            ; The byte->screenpixel map.
           (ensure-image-rendering-color-map image-rendering))
         (tiled-raster
           (image-rendering-tiled-raster image-rendering))
         oriented-image-left oriented-image-top
         oriented-image-right oriented-image-bottom
         source-left source-top source-right source-bottom
         initial-tile-x0 initial-tile-y0
         (synced? nil))
    (multiple-value-setf
      (oriented-image-left
        oriented-image-top
        oriented-image-right
        oriented-image-bottom)
      (compute-oriented-destination-for-image
        image-data
        x-in-window y-in-window
        image-left-offset-in-ws image-top-offset-in-ws
        (if rotated-by-90-p rotation-height rotation-width)
        (if rotated-by-90-p rotation-width rotation-height)
        rotation
        (if rotated-by-90-p y-scale x-scale)
        (if rotated-by-90-p x-scale y-scale)))
    (multiple-value-setf
      (source-left source-top source-right source-bottom)
      (compute-clipped-region-of-rendering-to-draw
        image-data
        x-in-window y-in-window
        left top right bottom
        image-left-offset-in-ws image-top-offset-in-ws
        (if rotated-by-90-p rotation-height rotation-width)
        (if rotated-by-90-p rotation-width rotation-height)
        rotation
        x-scale y-scale))

    (do-overlapping-tiles-of-image-rendering
        (image-tile? x0 y0 tile-width tile-height image-rendering
                     source-left source-top source-right source-bottom)
      (unless initial-tile-x0
        (setf initial-tile-x0 x0))
      (unless initial-tile-y0
        (setf initial-tile-y0 y0))
      (let* ((src-x  (maxf 0 (-f source-left x0)))
             (src-y  (maxf 0 (-f source-top y0)))
             (dest-x (maxr left
                           oriented-image-left
                           (+r (maxr oriented-image-left left)
                               (-f x0 source-left))))
             (dest-y (maxr top
                           oriented-image-top
                           (+r (maxr oriented-image-top top)
                               (-f y0 source-top))))
             (dest-right (minr right
                               oriented-image-right
                               (+f dest-x
                                   (-f tile-width src-x))))
             (dest-bottom (minr bottom
                                oriented-image-bottom
                                (+f dest-y
                                    (-f tile-height src-y))))
             (width (-f dest-right dest-x))
             (height (-f dest-bottom dest-y))
                                        ; Destination depth. Reliable?
             (tile-depth (bits-per-pixel-for-tiled-raster tiled-raster))
             (cached? (not (null image-tile?))))

        (cond (drawing-to-printer-p
               (draw-image-tile-on-printer
                 gensym-window
                 image-data
                 i j tile-size tile-width tile-height
                 x-scale y-scale rotation
                 rgb-color-map
                 src-x src-y width height
                 dest-x dest-y
                 foreground-color background-color))

              ((setq image-tile? (ensure-image-tile image-rendering j i transparentp quality))
               (let* ((pixmap (image-tile-stored-raster image-tile?))
                      (mask-pixmap? (image-tile-stored-mask-raster image-tile?)))
                 (unless cached?
                   (unless synced?
                     (c-x11-sync (native-window? gensym-window))
                     (setq synced? t))
                   (draw-image-on-tile image-data
                                       pixmap
                                       mask-pixmap?
                                       i j tile-size
                                       tile-width tile-height tile-depth
                                       x-scale y-scale
                                       rotation
                                       color-map rgb-color-map
                                       image-left-offset-in-ws
                                       image-top-offset-in-ws
                                       rotation-width
                                       rotation-height))
                 (when (and (>f width 0) (>f height 0))        ; Should always be true.
                   (if is-icon-mask-drawing
                     (c-x11-draw-mask-pixmap
                       pixmap
                       (native-window? gensym-window)
                       (or mask-pixmap? -1)
                       src-x src-y
                       width height
                       dest-x dest-y
                       foreground-color
                       background-color)
                     (c-x11-draw-pixmap
                       pixmap
                       (native-window? gensym-window)
                       (or mask-pixmap? -1)
                       src-x src-y
                       width height
                       dest-x dest-y
                       foreground-color
                       background-color))))) 
              (t
               ;; Out of mem. Draw a solid rectangle in the background color.
               ;; (Probably should draw some more distinctive pattern)
               (c-x11-draw-rectangle
                 (native-window? gensym-window) dest-x dest-y width height
                 background-color x11-copy)))))))

(def-gensym-c-function c-x11-draw-mask-pixmap
                       (:void "g2ext_x11_draw_mask_pixmap")
  ((:pointer pixmap-structure-pointer)
   (:pointer gensym-x-window)
   (:pointer mask-pixmap-structure-pointer)
   (:fixnum-int src-x)
   (:fixnum-int src-y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int dst-x)
   (:fixnum-int dst-y)
   (:fixnum-int foreground-color)
   (:fixnum-int background-color)))

;; Maybe assume current-window.  This runs on the TW side of the wire.
;; LTRB are in (X) window coordinates.


;;; The function `image-rendering-cached-p' returns T if the rendering
;;; of the image at the given scale is completely cached.

#+unused
(defun image-rendering-cached-p (image-data x-scale y-scale)
  (let* ((image-rendering?
           (find-image-rendering
             image-data current-window x-scale y-scale nil nil))
         (tiled-raster?
           (and image-rendering?
                (image-rendering-tiled-raster image-rendering?))))

    (when tiled-raster?
      (block LOOP
        (do-raster-tiles (tile? x y tiled-raster?)
          (when (null tile?)
            (return-from LOOP nil)))
        t))))


;;; The gensym-c-function `c-x11-draw-pixmap' draws the pixmap
;;; into the pixmap's corresponding window.  If the pixmap is
;;; actually a bitmap, then we use the given fg and bg color values
;;; for 1's and 0's, respectively.  Otherwise, fg and bg are ignored.

(def-gensym-c-function c-x11-draw-pixmap
                       (:void "g2ext_x11_draw_pixmap")
  ((:pointer pixmap-structure-pointer)
   (:pointer gensym-x-window)                ; argument added. (MHD 11/20/01)
   (:pointer mask-pixmap-structure-pointer)
   (:fixnum-int src-x)
   (:fixnum-int src-y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int dst-x)
   (:fixnum-int dst-y)
   (:fixnum-int foreground-color)
   (:fixnum-int background-color)))

;;; The gensym-c-function `c-x11-put-image' draws the image data into a pixmap
;;; at x,y.  This function assumes that each scan-line of the data has been
;;; WORD (16 bit) aligned.  This is a requirement of Windows NT.

(def-gensym-c-function c-x11-put-image
                       (:void "g2ext_x11_put_image")
  ((:pointer pixmap-structure-pointer)
   (:fixnum-int dest-x)
   (:fixnum-int dest-y)
   (:fixnum-int width)
   (:fixnum-int height)
   (:fixnum-int depth)
   (:fixnum-int function)                                    ; 1=OR, 0=andInvert.
   (:fixnum-int bytes-per-line)
   (:byte-vector data)))

;;; The gensym-c-function `c-x11-stretch-bits' provides access to native Win32
;;; image scaling. It is also the best way to draw to a printer DC.

(def-gensym-c-function c-x11-stretch-bits
    (:void "g2ext_stretch_bits")
  ((:pointer gensym-x-window)
   (:fixnum-int src-x)
   (:fixnum-int src-y)
   (:fixnum-int src-width)
   (:fixnum-int src-height)
   (:fixnum-int src-depth)
   (:fixnum-int dst-x)
   (:fixnum-int dst-y)
   (:fixnum-int dst-width)
   (:fixnum-int dst-height)
   (:fixnum-int stride)                        ; Pixels per scan
   (:byte-vector colormap)                ; Vector of Win32 RGBQUADs (B,G,R,0, ...)
   (:fixnum-int ncolors)
   (:byte-vector data)
   (:fixnum-int nbytes)))                ; In data

#+debugging
(def-gensym-c-function c-x11-print-pixmap
                       (:void "x11_print_pixmap")
  ((:pointer pixmap-structure-pointer)
   (:fixnum-int width)
   (:fixnum-int height)))



;;;; Drawing a bitmap into an icon layer



;;; The function `slowly-draw-image-data-on-current-scratchpad' is the
;;; slow-but-reliable version, written in terms of
;;; paint-solid-rectangle-in-current-scratchpad-raster. It is used to draw icon
;;; bitmaps onto old versions of Telewindows and for rendering small icons at
;;; small scales since it gives better results than the fast routine (see
;;; paint-icon-image-if-any).

(defun slowly-draw-image-data-on-current-scratchpad
    (image-data                                ; An image-data structure.
      x0 y0                                ; Destination x,y w/in icon. (unscaled)
      x-scale y-scale                        ; Fixed-point scale factors
      width height                        ; Original dimensions of the icon.
      reflection-and-rotation?
      color-value)
  (when (ensure-image-data-pixels image-data)
    (let* ((shredded-raster (image-data-cache? image-data))
           (image-width (image-data-width image-data))
           (image-height (image-data-height image-data))
           (x1 (pin-in-range 0 x0 width))                            ; Clip to icon space.
           (y1 (pin-in-range 0 y0 height))
           (x2 (pin-in-range 0 (+f x0 image-width) width))
           (y2 (pin-in-range 0 (+f y0 image-height) height))
           (normalized-scale (normalized-scale))
           (dx (if (<=f x-scale normalized-scale) 0 1))            ; Supposed size of an image bit.
           (dy (if (<=f y-scale normalized-scale) 0 1))
           (depth (shredded-raster-depth shredded-raster))
           (gray-map? (when (>f depth 1)
                        (create-gray-map-from-color-map
                          (shredded-raster-color-map shredded-raster)))))

      ;; Convert x1,y1,x2,y2 to image coor.
      (decff x1 x0)
      (decff y1 y0)
      (decff x2 x0)
      (decff y2 y0)

      ;; x0,y0 -- coordinates in the ICON where the origin of the image should be placed.
      ;; x1,y1 -- coordinates in the IMAGE of the upper left of the showing portion.
      ;; x2,y2 -- ditto for lower right, +1 (they are the exclusive limits)

      (do-raster (pixel rgb x y shredded-raster x1 y1 x2 y2)
        (let* ((xp (+f x0 x))
               (yp (+f y0 y))
               (x1 xp)                        ; UL coordinates in ICON of this bit,
               (y1 yp)                        ; before rotation & scale.
               (x2 (+f xp dx))                ; Ditto for LR coordinates (exclusive)
               (y2 (+f yp dy)))

          (orient-points-for-icon reflection-and-rotation?
              width height x1 y1 x2 y2)                            ; changes args

          (let ((left (delta-x-in-window (minw x1 x2) x-scale))
                (top (delta-y-in-window (minw y1 y2) y-scale))
                (right (+r (delta-x-in-window (maxw x1 x2) x-scale) 1))
                (bottom (+r (delta-y-in-window (maxw y1 y2) y-scale) 1)))

            (when (shredded-raster-pixel-black-p
                    shredded-raster pixel left top gray-map?)
              (paint-solid-rectangle-in-current-scratchpad-raster
                left top right bottom color-value)))))

      (when gray-map?
        (reclaim-managed-array gray-map?)))))


;;; The function `draw-image-data-on-local-scratchpad' draws the image into a
;;; local scratchpad raster, which is currently always one bit deep.  This is
;;; the routine used by icon rendering (the fast version).

(defun draw-image-data-on-local-scratchpad ; Entry point
    (image-data                                ; An image-data structure.
      x0 y0                                ; Destination x,y w/in icon. (unscaled)
      x-scale y-scale                        ; Fixed-point scale factors
      width height                        ; Original dimensions of the icon.
      reflection-and-rotation?
      quality
      draw-or-burn)                        ; 1 for draw, 0 for burn.
  (declare (ignore quality))
  #+lispworks4
  (cerror "Return nil"
          "draw-image-data-on-local-scratchpad is too big!!!")
  #-lispworks4
  (when (ensure-image-data-pixels image-data) ; Just draw nothing if no data.
    (let* ((shredded-raster (image-data-cache? image-data))
           (image-width (image-data-width image-data))
           (image-height (image-data-height image-data))
           (x1 (pin-in-range 0 x0 (-f width 1)))
           (y1 (pin-in-range 0 y0 (-f height 1)))
           (x2 (pin-in-range 0 (+f x0 image-width) (-f width 1)))    ; Inclusive
           (y2 (pin-in-range 0 (+f y0 image-height) (-f height 1))))
      ;; Now [x1,x2] x [y1,y2] is the rectangle in the icon rendering (at unit
      ;; scale, unrotated) which will be painted over by the image.  We need the
      ;; inclusive intervals here so that each point is actually a point in the
      ;; icon, to be transformed presently.  After the transformation, we compute
      ;; the EXclusive intervals in left top right bottom. Note that this is
      ;; different from the slow version of this routine, where these same
      ;; variables are bound to coordinates in the image's space.
      (orient-points-for-icon reflection-and-rotation? width height x1 y1 x2 y2)

      (let* ((left (delta-x-in-window (minr x1 x2) x-scale))
             (top (delta-y-in-window (minr y1 y2) y-scale))
             (right (delta-x-in-window (1+f (maxr x1 x2)) x-scale)) ; Exclusive
             (bottom (delta-y-in-window (1+f (maxr y1 y2)) y-scale))
             (tiled-raster current-scratchpad-raster)
             (tile-depth (bits-per-pixel-for-tiled-raster tiled-raster))
             (raster-width (shredded-raster-width shredded-raster))
             (raster-height (shredded-raster-height shredded-raster))
             (raster-depth (shredded-raster-depth shredded-raster))
             (color-map (shredded-raster-color-map shredded-raster))
             (gray-map? (when (>f raster-depth 1)
                          (create-gray-map-from-color-map color-map)))
             (raster-x-origin (or current-x-offset-for-stored-raster? 0))
             (raster-y-origin (or current-y-offset-for-stored-raster? 0)))

        ;; iterate-over-tiles-to-be-painted is expecting these to be
        ;; in the tiled-rasters units, with a 0 origin.
        (decff left raster-x-origin)
        (decff top raster-y-origin)
        (decff right raster-x-origin)
        (decff bottom raster-y-origin)

        ;; [Left,right) x [top,bottom) is now the rectangle in the scaled and
        ;; rotated space of the tiled raster which will be painted, accounting
        ;; for the x,y origin of the entire tiled raster (raster-x/y-origin).

        ;; Paint from the image bits into the raster tiles, using c-x11-put-image.
        (iterate-over-tiles-to-be-painted (left top right bottom tiled-raster)
          (let* ((tile-x-origin (*r j tile-size))
                 (tile-y-origin (*r i tile-size))
                 (tile-x1 (+f (maxr left tile-x-origin) raster-x-origin))
                 (tile-y1 (+f (maxr top tile-y-origin) raster-y-origin))
                 (tile-x2 (+f (minr right (+f tile-x-origin tile-size)) raster-x-origin))
                 (tile-y2 (+f (minr bottom (+f tile-y-origin tile-size)) raster-y-origin))
                 (tile-width (-r tile-x2 tile-x1))            ; Both should be gt 0.
                 (tile-height (-r tile-y2 tile-y1))
                 (source-width-1 (1-r width))
                 (source-height-1 (1-r height))
                 (tile tile-to-paint)
                 (buffer (large-byte-vector))
                 (inverse-transform (fast-invert-reflection-and-rotation
                                      reflection-and-rotation?))
                 (bytes-per-line (compute-bytes-per-scan-line tile-width tile-depth)))

            (when (rotated-by-90-p reflection-and-rotation?)
              (psetq source-width-1 source-height-1
                     source-height-1 source-width-1))

            ;; These are the tile coordinates which want to fill with ink,
            ;; relative to the origin of the first tile of the tiled raster.
            (case raster-depth
              (1 (copy-raster-bits-into-buffer shredded-raster buffer
                                               shredded-raster-ref-1-black-p))
              (8 (copy-raster-bits-into-buffer shredded-raster buffer
                                               shredded-raster-ref-8-black-p))
              (24 (copy-raster-bits-into-buffer shredded-raster buffer
                                                shredded-raster-ref-24-black-p))
              (t
               (dwarn "Unhandled depth ~d in draw-image-data-on-local-scratchpad" raster-depth)))
            (c-x11-put-image tile
                             (-r tile-x1 tile-x-origin raster-x-origin)
                             (-r tile-y1 tile-y-origin raster-y-origin)
                             tile-width tile-height tile-depth draw-or-burn bytes-per-line
                             buffer)))
        (when gray-map?
          (reclaim-managed-array gray-map?))))))


#+development
(defun print-image-buffer (buffer width height bytes-per-line)
  (format t "Width ~d  Height ~d  bytes-per-line ~d~%"
          width height bytes-per-line)
  (loop for y below height doing
    (format t "~3d: " y)

    (loop for i below bytes-per-line
          as byte = (byte-vector-aref buffer (+ i (* y bytes-per-line)))
          doing
      (format t "~8,'0b " byte))
    (format t "  ")
    (loop with nbits = 0
          for i below bytes-per-line
          as byte = (byte-vector-aref buffer (+ i (* y bytes-per-line)))
          doing
      (loop for j below 8
            as bit? = (> (logandf byte (ash 1 j)) 0)
            while (< nbits width)
            doing
        (format t "~a" (if bit? "*" "."))
        (incf nbits)))
    (terpri)))


;;;; ICP Stuff


(defparameter images-maximum-number-of-ICP-bytes-to-buffer 18000) ; ICP clogs at 20Kbytes
;; See telewindows-max-number-of-icp-bytes-before-clogged

(defparameter images-maximum-number-of-ICP-bytes-per-message-group 8000)

(defparameter images-time-to-sleep-before-clog 0.25)            ; Seconds.


(def-substitution-macro images-number-of-bytes-in-icp-buffers ()
  (+f number-of-icp-bytes-in-message-group
      (-f number-of-icp-bytes-for-message-series
          number-of-icp-bytes-to-fill-buffer)
      3))

;; This is really just the number in the message-group buffers.
;; There may be more bytes outstanding in the buffers ready for transmission.


(def-substitution-macro images-reset-icp-message-group-state ()
  (setf number-of-icp-bytes-for-message-series 0)
  (setf icp-buffers-for-message-group nil)
  (setf icp-byte-position-of-start-of-message-series? nil)
  (setf number-of-icp-bytes-to-fill-buffer 0)
  (setf current-icp-buffer nil)
  (setf current-write-icp-byte-position nil)
  (setf number-of-icp-bytes-in-message-group 0))

;; These functions were copied from GSI-RPC2.


(defun restart-icp-message-group ()
  (end-icp-message-group)
  (images-reset-icp-message-group-state))



;;; The function `maybe-restart-icp-window-update' will restart the
;;; current on-window context if more bytes are buffered than would
;;; take the given number of seconds to transmit.

(defun maybe-restart-icp-window-update (max-number-of-seconds max-number-of-bytes)
  (let ((bytes (images-number-of-bytes-in-icp-buffers))
        (rate (if (i-am-alive-info? current-icp-socket)
                  (icp-bytes-per-second-through-output-port
                    (i-am-alive-info? current-icp-socket))
                  0)))

    (when (or (>=f bytes max-number-of-bytes)
              (if (>f rate 10)                                    ; Hasn't been computed yet.
                  (>=f (floorf-positive bytes rate) max-number-of-seconds)))

      ;; Flush what we buffered on the far side.
      (sync-graphics-on-current-window)

      ;; Start a new message group.
      (restart-icp-message-group)

      (unless (=f (icp-connection-state current-icp-socket) icp-connection-closed)
        (synchronize-icp-on-window-with-drawing
         current-window
         left-edge-of-draw-area top-edge-of-draw-area
         right-edge-of-draw-area bottom-edge-of-draw-area)))))




;;; The function `images-too-many-buffered-ICP-bytes-p' is intended to return T
;;; just before the TW connection clogs.  We either go once more around the
;;; scheduling loop, or sleep for some seconds, when this happens.

(defun images-too-many-buffered-ICP-bytes-p ()
  (or (>=f (images-number-of-bytes-in-icp-buffers)
           images-maximum-number-of-ICP-bytes-per-message-group)
      (and (i-am-alive-info? current-icp-socket)
           (>=f (number-of-outstanding-icp-bytes (i-am-alive-info? current-icp-socket))
                images-maximum-number-of-ICP-bytes-to-buffer))))





;;;; Telewindows interface


;;; This is how image rendering on telewindows works: The image-definition
;;; object, being a frame, exists only within G2.  Below that, we have an
;;; image-data structure, with slots for pathname, format, data, renderings.
;;; Below image-data are a list of image renderings, one per window X
;;; scale-factor X rotation X rendering-quality

;;; We replicate the image-data object on both sides of the wire, by playing
;;; the file bytes over the wire.  Image renderings are created on each side of
;;; the wire as needed by that side's local window.

;;; When G2 tries to draw an image on a workspace background, we first send
;;; over the image data object, if needed.  Then we enter a schedulable loop
;;; which sends chunks of the image data across the wire.  This data includes
;;; the pixels as well as the color-map.

;;; Once the image-data exists cached on the TW side, then it can be rendered
;;; (scaled, etc) by the usual mechanisms fully on the TW side.

;;; New messages:
;;;   `begin-making-image-data'
;;; New ICP objects:
;;;    `image-data', `image-data-chunk', `byte-vector', `array-of-unsigned-integers'




(defconstant free-bits-per-icp-byte-mask (-f (ash 1 free-bits-per-icp-byte) 1))


;;; The icp-value-writer `byte-vector' packs a byte vector into 15-bit chunks,
;;; one per 16 bit ICP byte.

(def-icp-value-writer byte-vector
  (let* ((vector-length (length byte-vector)) ; Much more than bytes-in-use, for images!!
         (number-of-icp-bytes (floorf-positive (+f (*f vector-length 8) free-bits-per-icp-byte)
                                               free-bits-per-icp-byte))
         (accumulator 0)
         (index 0)
         (nbits 0))
    (write-icp-unsigned-integer vector-length)
    (write-icp-unsigned-integer number-of-icp-bytes)
    (loop for i below vector-length
          for byte = (byte-vector-aref byte-vector i)
          doing
      (setf accumulator (logiorf accumulator (ashf byte nbits)))
      (incff nbits 8)
      (loop while (and (<f index number-of-icp-bytes)
                       (or (>=f nbits free-bits-per-icp-byte)
                           (=f i (1-f vector-length))))            ; To disgorge the last byte.
            doing
        (write-icp-byte (logandf accumulator free-bits-per-icp-byte-mask))
        (setf accumulator (ashf accumulator (- free-bits-per-icp-byte))
              index (+f index 1)
              nbits (-f nbits free-bits-per-icp-byte))))))


(def-icp-value-reader byte-vector
  (let* ((vector-length (read-icp-unsigned-integer))
         (number-of-icp-bytes (read-icp-unsigned-integer))  ; Redundant, but why not.
         (byte-vector (allocate-byte-vector vector-length))
         (accumulator 0)
         (nbits 0)
         (index 0))
    (loop repeat number-of-icp-bytes
          for word = (read-icp-byte)
          doing
      (setf accumulator (logiorf accumulator (ashf word nbits)))
      (incff nbits free-bits-per-icp-byte)
      (loop while (and (>=f nbits 8)
                       (<f index vector-length))
            doing
        (setf (byte-vector-aref byte-vector index) (logandf accumulator 255)
              accumulator (ashf accumulator -8)
              index (+f index 1)
              nbits (-f nbits 8))))
    byte-vector))





;;; The icp-value-writer `array-of-unsigned-integers' looks just like
;;; list-of-unsigned-integers, but creates a managed array instead of a list.

(def-icp-value-writer array-of-unsigned-integers
  (let ((length (managed-array-length array-of-unsigned-integers)))
    (write-icp-unsigned-integer length)
    (write-icp-array-of-unsigned-integers-given-length length array-of-unsigned-integers)))

(defun write-icp-array-of-unsigned-integers-given-length (length array-of-unsigned-integers)
  (loop for i below length doing
    (write-icp-unsigned-integer (managed-svref array-of-unsigned-integers i))))

(def-icp-value-reader array-of-unsigned-integers
  (let ((length (read-icp-unsigned-integer)))
    (read-icp-array-of-unsigned-integers-given-length length)))

(defun read-icp-array-of-unsigned-integers-given-length (length)
  (let ((array (allocate-managed-array length)))
    (loop for i below length doing
      (setf (managed-svref array i) (read-icp-unsigned-integer)))
    array))

;; I'll worry about reclaimation myself, thank you!
;; (setf (icp-value-reclaimer 'array-of-unsigned-integers) 'reclaim-managed-array)



;;; The icp-value-writer `array-of-unsigned-integers?' writes either
;;; an array or nil.

(def-icp-value-writer array-of-unsigned-integers?
  (cond
    ((null array-of-unsigned-integers?)
     (write-icp-unsigned-integer? nil))
    (t
     (let ((length (managed-array-length array-of-unsigned-integers?)))
       (write-icp-unsigned-integer? length)
       (write-icp-array-of-unsigned-integers-given-length length array-of-unsigned-integers?)))))


(def-icp-value-reader array-of-unsigned-integers?
  (let ((length? (read-icp-unsigned-integer?)))
    (when length?
      (read-icp-array-of-unsigned-integers-given-length length?))))



#+development
(defun print-icp-buffer-sizes (&optional (header "ICP:"))
  (when (icp-window-p current-window)
    (format t "~a  buffered ~d/~d, out ~d/~d bytes, rate ~d Bps~%"
            header
            (images-number-of-bytes-in-icp-buffers)
            images-maximum-number-of-ICP-bytes-per-message-group

            (number-of-outstanding-icp-bytes (i-am-alive-info? current-icp-socket))

            images-maximum-number-of-ICP-bytes-to-buffer
            (icp-bytes-per-second-through-output-port
              (i-am-alive-info? current-icp-socket)))))

;; Image data transfer tracing for the build.

(defvar trace-images nil)

(defun trace-images ()
  (setq trace-images t))

(defun untrace-images ()
  (setq trace-images nil))

(defun trace-images-print (label row height)
  (when (zerop (mod row 10))
    (format t "~a Row ~4d/~d, Buffered ~6d, Out: ~6d  Tput: ~6d, Clog? ~s~%"
            label
            row height
            (images-number-of-bytes-in-icp-buffers)

            ;; The number we (and TW) checks against. See
            ;; `telewindows-connection-clogged?'
            (number-of-outstanding-icp-bytes (i-am-alive-info? current-icp-socket))

            (icp-bytes-per-second-through-output-port
              (i-am-alive-info? current-icp-socket))
            (not (icp-connection-unclogged-for-socket? current-icp-socket)))
    (force-output)))


(defun file-exists-p (pathname)
  (let ((pathname? (gensym-probe-file pathname)))
    (when pathname?
      (reclaim-gensym-pathname pathname?)
      t)))


;;; The function `telewindows-can-read-image-data-locally-p' returns T if G2
;;; thinks that TW will be able to read the given image-data itself, from the
;;; image's file. If it turns out that TW cannot read the file for some reason,
;;; then TW will be stuck and will never receive the bits from G2.  So, this
;;; predicate needs to conservative in returning true. Incorrectly returning NIL
;;; merely reverts us to 6.x behavior, while incorrectly returning T means the
;;; image will *never* be visible on TW.

(defun telewindows-can-read-image-data-locally-p (image-data gensym-window)
  (and (not (image-data-was-constructed-p image-data))
       (server-and-client-share-file-system-p gensym-window)
       (>=f (icp-window-protocol-version gensym-window)        ; Condition for 7.0
            icp-window-protocol-supports-nms-menus)))

;; TODO: Maybe image-definitions should have a flag which says to always clock
;; the data over the wire (6.x compatibility). That would provide a workaround
;; if this function incorrectly returns T.


;;; The defvar `send-image-data-immediately?', when bound to T, forces the
;;; actual scan lines for an image-data structure to be sent over, in a
;;; non-interruptable fashion, at the same time the image-data structure is
;;; sent on behalf of ICP.  Icon rendering binds this variable since it is not
;;; prepared to send the image-data later.

(defvar send-image-data-immediately? nil)


;;; The icp-object-type `image-data' will transmit an image structure,
;;; as well as all of the cached data in the image.  Very soon,
;;; we will have to transmit the data in a separate microtask.

(def-icp-object-type image-data (standard-icp-object-index-space
                                  (image-data-icp-ports image-data)
                                  reclaim-image-data
                                  icp-port-shutdown-for-image-data)
  (send-icp-begin-making-image-data
    corresponding-icp-object-index
    (image-data-pathname image-data)
    (image-data-format image-data)
    (image-data-width image-data)
    (image-data-height image-data)
    (image-data-depth image-data)
    (image-data-number-of-colors image-data)
    (image-data-color-map image-data)
    (image-data-transparent-color-index image-data))

  (when send-image-data-immediately?
    (send-all-image-data image-data)))

;; ICP object type definitions are a bit unusual in that they define only the
;; sending side of the protocol, usually via some message types, which in
;; turn define the receiving side of the protocol.  There isn't the declarative
;; method of defining both sides at once, as in Sun RPC.

(defvar supports-transparent-color-index 1) ; see icp-version-info-alist

(defun remote-side-supports-transparent-color-index-p (icp-socket)
  (=f 1 (get-remote-icp-version-info-value
          icp-socket 'supports-transparent-color-index 0)))

(def-icp-value-writer transparent-color-index
  (with-bifurcated-version-for-output (transparent-color-index-icp-version
                                        current-icp-socket
                                        (remote-side-supports-transparent-color-index-p current-icp-socket))
    nil
    (write-icp-fixnum (or transparent-color-index -1))))

(def-icp-value-reader transparent-color-index
  (with-bifurcated-version-for-input (transparent-color-index-icp-version
                                       current-icp-socket
                                       (remote-side-supports-transparent-color-index-p current-icp-socket))
    -1
    (read-icp-fixnum)))

;;; The icp-message-type `begin-making-image-data' creates an image-data object
;;; on the far side.  The image-data will NOT yet have a data cache (raster).

(def-icp-message-type begin-making-image-data
    (corresponding-icp-object-index
      (filtered-text-string ascii-pathname) ; This means an ASCII string.
      (symbol format)
      (unsigned-integer width)
      (unsigned-integer height)
      (unsigned-integer depth)
      (unsigned-integer number-of-colors)
      (array-of-unsigned-integers color-map)
      (transparent-color-index transparent-color-index))
  ;; This code runs on the far side.
  (let ((image-data (make-image-data
                      ascii-pathname
                      width height depth format number-of-colors color-map
                      transparent-color-index)))
    (store-corresponding-icp-object corresponding-icp-object-index image-data)))

;; Use managed simple vectors for the color map!



;;; The new ICP value type compressed-image-data-chunk has the following format:
;;; either
;;;   icp-byte=0, icp-byte-vector data-in-old-format
;;; or
;;;   icp-byte length, icp-byte bits-per-pixel, icp-fixnum pixels-per-row,
;;;   followed by pixels-per-row pixels of bit-data.

;;; The bit-data is a sequence of bit-data-groups.

;;; A bit-data-group is either a repeated-pixel-bit-data-group or
;;;   a multiple-pixel-bit-data-group.

;;; A repeated-pixel-bit-data-group is either
;;;   [1 (1 bit)], [0 (1 bit)], [numpixels (3 bits)], [a-pixel-value (bits-per-pixel bits)]
;;; or
;;;   [1 (1 bit)], [1 (1 bit)], [numpixels (12 bits)], [a-pixel-value (bits-per-pixel bits)]

;;; A multiple-pixel-bit-data-group is either
;;;   [1 (1 bit)], [0 (1 bit)], [numpixels (3 bits)], numpixels * [a-pixel-value (bits-per-pixel bits)]
;;; or
;;;   [1 (1 bit)], [1 (1 bit)], [numpixels (12 bits)], numpixels * [a-pixel-value (bits-per-pixel bits)]

;;; Note that this format can not handle images wider than 4095 pixels.

(defvar icp-bits-current-value 0)
(defvar icp-bits-current-bits 0)

(defun write-icp-bits (n value)
  (loop for value-to-write fixnum = value
                           then (right-shiftf value-to-write bits-this-time)
        for bits-to-write fixnum = n
                          then (-f bits-to-write bits-this-time)
        while (<f 0 bits-to-write)
        for bits-this-time fixnum = (minf bits-to-write
                                          (-f 16 icp-bits-current-bits))
        for mask-this-time fixnum = (1-f (left-shiftf 1 bits-this-time))
        for value-this-time fixnum = (logandf value-to-write mask-this-time)
        do (setq icp-bits-current-value
                 (+f icp-bits-current-value
                     (left-shiftf value-this-time icp-bits-current-bits)))
           (incff icp-bits-current-bits bits-this-time)
           (when (=f icp-bits-current-bits 16)
             (write-icp-byte icp-bits-current-value)
             (setq icp-bits-current-bits 0)
             (setq icp-bits-current-value 0))))

(defun write-icp-bits-flush ()
  (unless (=f 0 icp-bits-current-bits)
    (write-icp-byte icp-bits-current-value)))

(defun read-icp-bits (n)
  (loop for value-so-far = 0 then new-value-so-far
        for bits-to-read fixnum = n then (-f bits-to-read bits-this-time)
        while (<f 0 bits-to-read)
        for bits-so-far = 0 then (+f bits-so-far bits-this-time)
        for current-bits = (progn
                             (when (=f 0 icp-bits-current-bits)
                               (setq icp-bits-current-value (read-icp-byte))
                               (setq icp-bits-current-bits 16))
                             icp-bits-current-bits)
        for bits-this-time = (minf bits-to-read current-bits)
        for mask-this-time fixnum = (1-f (left-shiftf 1 bits-this-time))
        for value-this-time fixnum = (logandf icp-bits-current-value mask-this-time)
        for new-value-so-far fixnum = (+f value-so-far
                                          (left-shiftf value-this-time bits-so-far))
        do (setq icp-bits-current-value (right-shiftf icp-bits-current-value
                                                      bits-this-time))
           (decff icp-bits-current-bits bits-this-time)
        finally (return value-so-far)))

(def-icp-value-writer compressed-image-data-chunk
  (let* ((length (length compressed-image-data-chunk))
         (max-value (loop for i from 0 below length
                          maximize (byte-vector-aref compressed-image-data-chunk i)))
         (bits (cond ((>=f 1 max-value) 1)
                     ((>=f 3 max-value) 2)
                     ((>=f 7 max-value) 3)
                     ((>=f 15 max-value) 4)
                     ((>=f 31 max-value) 5)
                     ((>=f 63 max-value) 6)
                     ((>=f 127 max-value) 7)
                     (t 8))))
    (when (<=f 4096 length)
      (return-from write-icp-compressed-image-data-chunk
        (progn
          (write-icp-byte 0)
          (write-icp-byte-vector compressed-image-data-chunk))))
    (write-icp-byte bits) ; when 0, it means a byte vector follows, instead
    (write-icp-fixnum length)
    (loop with icp-bits-current-value = 0
          with icp-bits-current-bits = 0
          with vector = compressed-image-data-chunk
          for pos = 0 then next-pos
          while (<f pos length)
          for v = (byte-vector-aref vector pos)
          for samep = (or (=f (1+ pos) length)
                          (=f v (byte-vector-aref vector (1+f pos))))
          for next-pos = (or (if samep
                                 (loop for npos from (1+f pos) below length
                                       for nv = (byte-vector-aref vector npos)
                                       unless (=f nv v)
                                         return npos)
                                 (loop for npos from (1+f pos) below (1-f length)
                                       for v1 = (byte-vector-aref vector npos)
                                              then v2
                                       for v2 = (byte-vector-aref vector (1+f npos))
                                       when (=f v1 v2)
                                         return npos))
                             length)
          for len1 = (1-f (-f next-pos pos))
          for short-lenp = (<=f len1 7)
          do (write-icp-bits 1 (if samep 1 0))
             (write-icp-bits 1 (if short-lenp 0 1))
             (write-icp-bits (if short-lenp 3 12) len1)
             (if samep
                 (write-icp-bits bits v)
                 (loop for i from 0 to len1
                       for v = (byte-vector-aref vector (+f pos i))
                       do (write-icp-bits bits v)))
          finally (write-icp-bits-flush))))

(def-icp-value-reader compressed-image-data-chunk
  (let ((bits (read-icp-byte)))
    (when (=f 0 bits)
      (return-from read-icp-compressed-image-data-chunk
        (read-icp-byte-vector)))
    (loop with length = (read-icp-fixnum)
          with icp-bits-current-value = 0
          with icp-bits-current-bits = 0
          with vector = (if (<=f 4096 length)
                            (icp-error "Error in read-icp-compressed-image-data-chunk")
                            (allocate-byte-vector length))
          for pos = 0 then next-pos
          while (<f pos length)
          for samep = (=f 1 (read-icp-bits 1))
          for short-lenp = (=f 0 (read-icp-bits 1))
          for len1 = (read-icp-bits (if short-lenp 3 12))
          for next-pos = (+f pos (1+f len1))
          do (when (<f length next-pos)
               (icp-error "Error in read-icp-compressed-image-data-chunk"))
             (if samep
                 (loop with v = (read-icp-bits bits)
                       for i from pos below next-pos
                       do (setf (byte-vector-aref vector i) v))
                 (loop for i from pos below next-pos
                       do (setf (byte-vector-aref vector i) (read-icp-bits bits))))
          finally (return vector))))


(def-icp-value-writer image-data-chunk-byte-vector
  (with-bifurcated-version-for-output (compressed-image-data-chunk-icp-version)
    (write-icp-byte-vector image-data-chunk-byte-vector)
    (write-icp-compressed-image-data-chunk image-data-chunk-byte-vector)))

(def-icp-value-reader image-data-chunk-byte-vector
  (with-bifurcated-version-for-input (compressed-image-data-chunk-icp-version)
    (read-icp-byte-vector)
    (read-icp-compressed-image-data-chunk)))


;;; The icp-message-type `image-data-chunk' receives a single scan-line of an
;;; image as a byte vector, and stores it at the given row number.

(def-icp-message-type image-data-chunk
    ((image-data image-data)
     (unsigned-integer row)
     (image-data-chunk-byte-vector buffer)) ; Note new type here which may compress the data.
  (note-image-progress system-window 'receive (image-data-pathname image-data)
                       row (image-data-height image-data))
  (let* ((raster (ensure-image-data-cache image-data))
         (old-buffer? (shredded-raster-buffer raster row)))
    (when old-buffer?
      (reclaim-byte-vector old-buffer?))
    (setf (shredded-raster-buffer raster row) buffer
          (shredded-raster-height-received raster) (1+f row))))

;; Possible representations for the image data: raw bytes, GIF bytes, JPEG
;; bytes, pathname on remote file system (error if not the same width and
;; height, or file not found).  Unfortunately, even GIF bytes do not provide
;; enough compression.



;;; The function `send-some-image-data' transmits image data to the current ICP
;;; port, starting with the given scan.  Optionally, it will return early if
;;; the preemption-predicate? returns T.  In all cases, it returns the next
;;; scan line to send, or NIL if all were sent.

(defun send-some-image-data (image-data preemption-predicate? sleep-before-clog?)
  ;; Send the image data. There had better be some.
  (when (ensure-image-data-pixels image-data)
    (let ((raster? (image-data-cache? image-data))
          (height (image-data-height image-data))
          (scan (image-data-next-scan-to-send image-data))
          (pathname (image-data-pathname image-data)))
      (when raster?
        (note-image-progress current-window 'send pathname scan height)
        (loop while (<f scan height)
              ;; Abort a long transmission if the connection closes.
              while (icp-connection-open-p current-icp-socket)
              until (and preemption-predicate?
                         (funcall-simple-compiled-function
                           preemption-predicate?))
              for byte-vector = (shredded-raster-buffer raster? scan)
              doing (progn
                      (note-image-progress current-window 'send pathname scan height)
                      (send-icp-image-data-chunk image-data scan byte-vector)
                      (incff scan))

          ;; Since ICP is buffering all of these bytes and has not yet sent them
          ;; to the underlying OS, this sleep was a complete waste of time.
          ;; It was removed in the C code by hand for 4r0. -fmw, 6/23/95
              when (and sleep-before-clog?
                        (images-too-many-buffered-ICP-bytes-p))
                do (when trace-images
                     (format t "ICP about to clog.  Sleeping.~%"))
                   #+ignore (gensym-sleep images-time-to-sleep-before-clog))

        (setf (image-data-next-scan-to-send image-data) scan)

        (when (and trace-images (images-too-many-buffered-ICP-bytes-p))
          (format t "ICP about to clog. Returning.~%"))

        (when trace-images
          (unless (icp-connection-open-p current-icp-socket)
            (format t "ICP connection closed during transmission at scan ~d of ~d~%"
                    scan height)))

        ;; Note: the return value is ignored!  This block of code, which
        ;; is trying to ensure that we declare ourselves done if the ICP
        ;; connection is closed, does not work!  -fmw, 6/23/95
        (if (and (<f scan height)
                 (icp-connection-open-p current-icp-socket))
            scan
            nil)))))

;; If we have no preemption predicate, then we must sleep when the ICP buffers
;; are about to clog.


;;; The function `send-all-image-data' is called by G2 try to ensure that the
;;; pixels for the given image-data get over to the current Telewindow.

;;; This function makes a "best effort" to get the data across.  It is still
;;; possible that the data does not get there; for example, if the image's file
;;; is deleted between the time we check it and the time that TW tries to read
;;; it.  In that case, we can get into a persistent state where G2 and TW have
;;; different displays of the same image.

;;; That's not so great, but should occur rarely, can be fixed by refreshing the
;;; image-definition on G2, and can only happen if the user is mucking about
;;; with images' files and so should not be too surprised if odd things
;;; happen. Hopefully, the first thing a user will try is refreshing the image,
;;; which is guarenteed to make G2 and TW consistent as long as the file on disk
;;; is not changing.

(defun send-all-image-data (image-data)
  ;; If data already sent, do nothing.
  (cond ((>=f (image-data-next-scan-to-send image-data)
              (image-data-height image-data)))

        ;; If TW cannot read the file locally (either the TW is too old to know
        ;; how, or it is on a different host), try to send the pixels over the
        ;; wire.
        ((not (telewindows-can-read-image-data-locally-p image-data current-window))
         (send-some-image-data image-data nil nil)
         ;; The send may or may not have succeeded, but that was our only hope, so
         ;; declare ourselves done.
         (setf (image-data-next-scan-to-send image-data) (image-data-height image-data)))

        ;; If the file on disk has been removed, but G2 has a cache of the
        ;; pixels, then send those over.  This might not be the right thing
        ;; to do if the image is large. We know this will succeed.
        ((and (image-data-complete-p image-data)
              (not (file-exists-p (image-data-pathname image-data))))
         (send-some-image-data image-data nil nil))

        ;; Otherwise, TW will read the file itself, so we declare ourselves
        ;; done.  Even if TW cannot ultimately read the file, TW now has full
        ;; responsibility for doing so.
        (t
         (setf (image-data-next-scan-to-send image-data)
               (image-data-height image-data)))))


;;; The function `finished-transmitting-image-data-p' is true if we are done
;;; sending the image-data to the current ICP port.

(defun finished-transmitting-image-data-p (image-data)
  (>=f (image-data-next-scan-to-send image-data)
       (image-data-height image-data)))



;;; The function `window-supports-painting-this-image-data' returns true if the
;;; given window supports painting the given image-data.  Telewindows versions
;;; 4-6 can paint 8 bit images but not 24 bit images.

(defun window-supports-painting-this-image-data (gensym-window image-data)
  (and (current-window-supports-image-painting gensym-window)
       (or (printing-window-p gensym-window)
           (current-window-supports-24bit-image-painting gensym-window)
           (<f (image-data-depth image-data) 24))))

;; For now, we punt on 24bit images to old telewindows.  Soon, we will
;; color-reduce them to 8 bits before sending. -fmw, 1/31/02



;;;; ICP functions


;;; The function `paint-or-tile-image-in-current-window' is called first to
;;; dispatch on the capability of the current window.

(defun paint-or-tile-image-in-current-window (image-data x-in-window y-in-window
                                                         left top right bottom
                                                         x-scale y-scale
                                                         rotation quality
                                                         foreground-color
                                                         background-color)
  (cond ((or (neq quality 'tiled)
             (current-window-supports-image-tiling))
         ;; Move the origin so that it is above and left of the rectangle being
         ;; tiled.  This works around a bug in the graphics card in our Sparc
         ;; Ultra 300's, and may help with other graphics cards, too.
         ;; Hopefully, the floor and multiply don't noticeably slow things
         ;; down. -fmw, 7/9/02
         (when (eq quality 'tiled)
           ;; Note: we can ignore scaling here only because tiled images are
           ;; currently never scaled when drawn. This may change someday because
           ;; of user requests. Note also that this code more properly belongs
           ;; on the TW-side (where we know the platform), but if we moved it
           ;; over there now, then 70r0 TW's connecting to a 70r1 G2 would not
           ;; get the correction at all. Probably nobody cares about that, but
           ;; might as well leave things alone for now. -fmw, 3/27/03
           (let ((width (minf (image-data-width image-data) largest-regular-raster-size))
                 (height (minf (image-data-height image-data) largest-regular-raster-size)))
             (setq x-in-window (+f x-in-window (*f width (floorf (-f left x-in-window) width)))
                   y-in-window (+f y-in-window (*f height (floorf (-f top y-in-window) height))))))
         (paint-image-in-current-window
           image-data x-in-window y-in-window
           left top right bottom
           x-scale y-scale
           rotation quality
           foreground-color
           background-color))
        (t
         ;; Old TW or printing: tile by hand.
         (let ((width (image-data-width image-data))
               (height (image-data-height image-data)))
           (loop for x fixnum from (+f x-in-window (*f width (floorf (-f left x-in-window) width)))
                       below right by width
                 doing
             (loop for y fixnum from (+f y-in-window (*f height (floorf (-f top y-in-window) height)))
                         below bottom by height
                   doing
               (paint-image-in-current-window
                 image-data x y
                 (maxf left x) (maxf top y)
                 (minf right (+f x width)) (minf bottom (+f y height))
                 (normalized-scale) (normalized-scale)
                 rotation nil
                 foreground-color
                 background-color)))))))


;;; The icp-message-functions `paint-image-in-current-window' is used for
;;; rendering workspace background images.

(def-icp-message-functions paint-image-in-current-window
    ((image-data image-data)
     (coordinate x-in-window)                ; Where to put image origin.
     (coordinate y-in-window)
     (coordinate left)                        ; Window coordinates into which we paint.
     (coordinate top)
     (coordinate right)
     (coordinate bottom)
     (coordinate x-scale)
     (coordinate y-scale)
     (symbol rotation)                        ; Unused
     (symbol quality)
     (unsigned-integer foreground-color) ; For bitmaps.
     (unsigned-integer background-color))
  (case type-of-current-window
    (x11-window
     (cond ((eq quality 'tiled)
            (draw-tiled-image-on-window image-data current-window
                                        x-in-window y-in-window
                                        left top right bottom
                                        foreground-color background-color))
           (t
            (draw-image-on-window image-data current-window x-in-window y-in-window
                                  left top right bottom
                                  x-scale y-scale rotation quality
                                  foreground-color background-color))))))

;; paint-image-in-current-window ->
;;  draw-image-on-window ->
;;   draw-image-on-window-for-workspace ->
;;    draw-image-on-tile-for-workspace ->
;;      draw-image-on-tile-8-to-8-for-workspace
;;      draw-image-on-tile-1-to-1
;;      draw-image-on-tile-8-to-1
;;      draw-image-on-tile-8-to-truecolor-for-workspace

(def-icp-message-functions paint-icon-background-image-in-current-window
    ((image-data image-data)
     (coordinate x-in-window)                  ; Where to put image origin.
     (coordinate y-in-window)
     (coordinate draw-area-left)          ; Window coordinates into which we paint.
     (coordinate draw-area-top)
     (coordinate draw-area-right)
     (coordinate draw-area-bottom)
     (coordinate x-scale)
     (coordinate y-scale)
     (symbol rotation)                        ; Unused
     (symbol quality)                        ; Unused
     (unsigned-integer foreground-color) ; For bitmaps.
     (unsigned-integer background-color)
     (coordinate image-left-offset-in-ws) ; Unused??
     (coordinate image-top-offset-in-ws)  ; Unused??
     (unsigned-integer rotated-width-in-ws)
     (unsigned-integer rotated-height-in-ws))
  (case type-of-current-window
    (x11-window
     (draw-icon-background-image-on-window
       image-data current-window
       x-in-window y-in-window
       image-left-offset-in-ws image-top-offset-in-ws
       rotated-width-in-ws rotated-height-in-ws
       draw-area-left draw-area-top draw-area-right draw-area-bottom
       x-scale y-scale rotation quality
       foreground-color background-color))))

;; paint-icon-background-image-in-current-window ->
;;  draw-icon-background-image-on-window ->
;;    draw-image-on-window-1 ->
;;      draw-image-on-tile ->
;;       draw-image-on-tile-8-to-8
;;       draw-image-on-tile-1-to-1
;;         draw-image-on-tile-8-to-1
;;         draw-image-on-tile-8-to-truecolor


;;; The icp-message-functions `paint-image-in-current-scratchpad-raster' is used
;;; for rendering bitmap layers in icons.

(def-icp-message-functions paint-image-in-current-scratchpad-raster
    ((image-data image-data)
     (coordinate x-in-icon)                ; Destination x,y w/in icon. (unscaled)
     (coordinate y-in-icon)
     (coordinate x-scale)
     (coordinate y-scale)
     (coordinate width)                        ; Original dimensions of the icon.
     (coordinate height)
     (symbol rotation)
     (symbol quality)                        ; Unused.
     (unsigned-integer draw-or-burn))        ; 1 for draw, 0 for clear ("burn").
  (case type-of-current-window
    (x11-window
     (draw-image-data-on-local-scratchpad
       image-data x-in-icon y-in-icon x-scale y-scale width height
       rotation quality draw-or-burn))))

;; We should clip the coordinates to the image before sending them over the wire?



;;; The icp-message-functions `change-image-palette-of-window' sets the image
;;; palette of a window, clearing all existing image renderings.  It is also
;;; used for simply clearing all of the renderings.  For that reason, we do not
;;; check here that the new quality is actually different from the old.

(def-icp-message-functions change-image-palette-of-window
    ((gensym-window gensym-window)
     (symbol palette-name)
     (array-of-unsigned-integers? color-map?))
  (case (type-of-gensym-window gensym-window)
    (x11-window
     (change-image-palette-of-local-window gensym-window palette-name color-map?))))


;;; The function `change-image-palette-of-local-window' clears the image
;;; palette then allocates the new named palette.  Custom palettes take colors
;;; out of the given color-map.

(defun change-image-palette-of-local-window (gensym-window palette-name color-map?)
  (setf (image-palette-of-gensym-window gensym-window) palette-name)
  (clear-all-image-renderings-for-window gensym-window)
  (clear-all-extended-colors-for-window gensym-window)
  (case palette-name
    (extended-grays
     (allocate-extended-gray-palette gensym-window))
    (extended-colors
     (allocate-extended-color-palette gensym-window))
    (custom-grays
     (allocate-custom-palette gensym-window color-map? t))
    (custom-colors
     (allocate-custom-palette gensym-window color-map? nil))))



;;; The function `draw-tiled-image-on-window' fills the given rectangle on
;;; window by tiling image-data, if available.

(defun-void draw-tiled-image-on-window (image-data gensym-window
                                                   x-in-window y-in-window
                                                   left top right bottom
                                                   foreground-color
                                                   background-color)
  (cond ((null (ensure-image-data-pixels image-data))
         ;; A missing tiled image is drawn simply as the background color.
         (draw-missing-image gensym-window
                             left top right bottom
                             left top right bottom
                             foreground-color
                             background-color t))
        (t
         (c-x11-draw-tiles
           (native-window? current-window)
           (ensure-singleton-image-pixmap image-data current-window)
           x-in-window y-in-window
           left top (-f right left) (-f bottom top)
           foreground-color background-color))))


;;; The function `ensure-singleton-image-pixmap' is used to create a "singleton
;;; image rendering", which is a tiled-raster containing only one tile. We need
;;; such a thing (with the entire image in one native pixmap) for tiling.

(defun ensure-singleton-image-pixmap (image-data window)
  (let* ((image-rendering
           (find-or-create-image-rendering image-data window
                                           (normalized-scale)
                                           (normalized-scale)
                                           nil
                                           'singleton))
         (tiled-raster
           (image-rendering-tiled-raster image-rendering))
         (image-tile?
           (tiled-raster-tile tiled-raster 0 0)))
    (unless image-tile?
      (setq image-tile? (make-image-tile image-rendering 0 0 nil t))
      (setf (tiled-raster-tile tiled-raster 0 0) image-tile?)
      (draw-image-on-tile-for-workspace
        image-data
        (image-tile-stored-raster image-tile?)
        nil
        0 0
        (tile-size tiled-raster)
        (image-rendering-tile-width image-rendering)
        (image-rendering-tile-height image-rendering)
        (bits-per-pixel-for-tiled-raster image-rendering)
        (normalized-scale)
        (normalized-scale)
        nil
        (ensure-image-rendering-color-map image-rendering)
        (image-data-color-map image-data)
        t))
    (image-tile-stored-raster image-tile?)))


;;;; Support for Pane Background Tiling Patterns



(defun shredded-raster-to-background-tile (raster)
  (let ((height (shredded-raster-height raster))
        (width (shredded-raster-width raster)))
    (cond ((> (* height width) maximum-background-tile-area)
           (notify-user-at-console "Background tile pattern too large: ~d > ~d"
                                   (* width height) maximum-background-tile-area)
           nil)
          (t
           (let ((gray-map? (when (>f (shredded-raster-depth raster) 1)
                              (create-gray-map-from-color-map
                                (shredded-raster-color-map raster))))
                 row rows)
             (do-raster-rows (raster :y y)
               (setq row nil)
               (do-row-pixels (pixel rgb :x x)
                 (gensym-push
                   (if (shredded-raster-pixel-black-p raster pixel x y gray-map?) 1 0)
                   row))
               (gensym-push (nreverse row) rows))
             (prog1 (nreverse rows)
               (when gray-map?
                 (reclaim-managed-array gray-map?))))))))


;;; An `image-spec' is the image-name, the list (image-name x-user y-user), or
;;; nil.  X and Y are the user-visible workspace coordinates (what's returned
;;; by item-x/y-position) where the center of the image will be positioned.

(def-substitution-macro image-spec-image-name (image-spec)
  (first image-spec))

(def-substitution-macro image-spec-user-x-position (image-spec)
  (second image-spec))

(def-substitution-macro image-spec-user-y-position (image-spec)
  (third image-spec))

(def-substitution-macro image-spec-tiled-p (image-spec)
  (and (consp image-spec) (fourth image-spec)))
