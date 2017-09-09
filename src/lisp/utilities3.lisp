;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module UTILITIES3

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark David, Lowell Hawkinson, Michael Levin, Stephen DeVoy, Jim Allard,
;;; and Nick Caruso




;;;; Forward References in UTILITIES3




;; to LAUNCH

(declare-forward-reference current-system-name variable)

;; To EVAL

(declare-forward-reference warn-of-big-bignum function)

;; To FRAMES1

(declare-forward-reference framep-function function)

;; To TYPES

(declare-forward-reference reclaim-evaluation-value function)
(declare-forward-reference copy-evaluation-value-1 function)

;; To SEQUENCES1
(declare-forward-reference encode-user-password-string-function function)

(declare-forward-reference print-first-string-in-pool-group function)

;; To INT3B
(declare-forward-reference get-local-host-name function)

;; To INT4
(declare-forward-reference get-local-host-addresses function)
(declare-forward-reference reclaim-network-addresses function)

;; To UTILITIES4
(declare-forward-reference make-call-hash-function function)

;; To WINDOWS1
(declare-forward-reference rgb-from-color function)
(declare-forward-reference get-gensym-window-parameter function)

;; To WINDOWS2
(declare-forward-reference get-tiling-pattern function)

;; To FRAMES2B
(declare-forward-reference framep-function function)

;; To CONNECT1
(declare-forward-reference connection-p-function function)

;; To DEBUG
(declare-forward-reference notify-user function)

;; declared later in this file
#+development
(declare-forward-reference reclaimed-managed-float-array-value-holder variable)




;;;; Pseudo Rest Args (How to Live Without Rest Args)


;;; You cannot use &rest args in Gensym software used at run time, since it
;;; is not guaranteed not to cons.  Instead, you simulate them by using an
;;; indefinitely large number of optional args, usually about 9 or so,
;;; defaulting them all to the unique value in the special variable no-arg.
;;; These args that use to simulate rest args are collectively referred to as
;;; `pseudo rest args'.  You then call functions on them using using call-per-
;;; number-of-actual-args, simulating using apply with a final argument that
;;; is a rest arg.  It is the programmer's responsibility to supply "enough"
;;; args so that the problem of too many args being supplied can never be
;;; a problem.  Accordingly, this kind of a facility should only be supplied
;;; when it can known the maximum number of args that will ever be needed
;;; by any possible call site.

;;; Note that one needn't necessarily be concerned that system functions that
;;; are documented as having an &rest arg will cons.  For example, one should
;;; not expect the function + to cons just because its arglist is documented
;;; as (&rest numbers).

;;; Here is an example, illustrating how to implement the function
;;; format-to-debug-io, which takes a format string and format args and applies
;;; them to the Lisp system function FORMAT, supplying *debug-io* as the
;;; stream argument.
;;;
;;;   (defun format-to-debug-io
;;;          (format-control-string
;;;           &optional                               ; pseudo rest args
;;;           (arg1 no-arg) (arg2 no-arg) (arg3 no-arg)
;;;           (arg4 no-arg) (arg5 no-arg) (arg6 no-arg)
;;;           (arg7 no-arg) (arg8 no-arg) (arg9 no-arg))
;;;     (call-per-number-of-actual-args
;;;       format 2 *debug-io* format-control-string
;;;       arg1 arg2 arg3
;;;       arg4 arg5 arg6
;;;       arg7 arg8 arg9))


;;; `No-arg' is a unique value used to represent as the value of a missing arg.

(defvar no-arg (list 'no-arg))



;;; Call-per-number-of-actual-args calls function with at least the minimum
;;; number of args given by minimum-number-of-actual-args, and further with
;;; the args remaining in args that are not eq to the value of special
;;; variable no-arg.

(defmacro call-per-number-of-actual-args
          (function minimum-number-of-actual-args &rest args)
  `(cond
     . ,(nconc
         (loop as count from minimum-number-of-actual-args below (length args)
               collect
                 `((eq ,(nth count args) no-arg)
                   (,function . ,(loop for arg in args
                                       repeat count
                                       collect arg))))
         `((t (,function . ,(copy-list args)))))))







;;;; Notifying the User in the Parent Window


;;; moved from telestubs.lisp -ncc, 21 Dec 1994

;;; `Notify-user-if-possible' is sort of union between notify-user and format
;;; (to "standard output", or the like).  Its purpose is to provide a way to
;;; have messages the user should see right away go out to them by whichever
;;; means is available.  Accordingly, for G2, this calls notify-user to print
;;; its arguments.  In other systems (only Telewindows, at present) this uses
;;; the console printing mechanisms.
;;;
;;; In all cases, this formats the text using tformat-text-string.  This leaves
;;; open only the issue of printing the resulting string for the user.  Note
;;; that tformat is similar to but not identical to format in its argument
;;; interpretation behavior. (Previously, this sometimes called format,
;;; sometimes tformat.  That was a poor design choice, which has now been
;;; corrected.) Prior to printing on the console, this calls export-text-string
;;; with purpose NOTIFY-USER-IF-POSSIBLE-VIA-CONSOLE.  This purpose may be
;;; enhanced at some point, but for now, this will only properly print out
;;; messages entirely in the ASCII subset of Unicode, and possibly ISO Latin 1
;;; subset, too, but not more.
;;;
;;; Since this is primarily intended for printing complete messages that should
;;; be seen at once in their entirety, a call to force-output is included after
;;; the call to format.
;;;
;;; Except the case of GSI, this also calls force-output immediately after the
;;; printing in order to get the output on screen as soon as possible.  This is
;;; not done in GSI simply to avoid paging in extra libraries.

(defmacro notify-user-if-possible
          (notification-as-format-string &rest args)
  `(current-system-case
    (ab (notify-user ,notification-as-format-string ,@args))
    (t  (notify-user-at-console ,notification-as-format-string ,@args))))


;;; The function `notify-user-at-console-and-on-logbook' calls both of the
;;; routines (notify-user and notify-user-at-console) for G2 (system AB) rather
;;; than choosing between them. For other systems, e.g., TW or GSI, notify-user
;;; is unavailable, so it will not be called, but notify-user-at-console will be
;;; called in any case.

(defun notify-user-at-console-and-on-logbook
    (notification-as-format-string
      &optional
      (arg1 no-arg) (arg2 no-arg) (arg3 no-arg)
      (arg4 no-arg) (arg5 no-arg) (arg6 no-arg)
      (arg7 no-arg) (arg8 no-arg) (arg9 no-arg))
  (call-per-number-of-actual-args
    notify-user-at-console 1 notification-as-format-string
    arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9)
  (current-system-case
    (ab
      (call-per-number-of-actual-args
        notify-user 1 notification-as-format-string
        arg1 arg2 arg3 arg4 arg5 arg6 arg7 arg8 arg9))))


;;; `Notify-user-at-console' sends output to the "console".  This is used by
;;; notify-user-if-possible when in Telewindows.  It may also be used by G2 code
;;; in order to have the same effect.  Note that this takes format control strings
;;; and args through TFORMAT, not FORMAT.  Therefore callers must exercise caution
;;; to use only the features common to both tformat and format.

(defvar *write-console-p* nil)

(defun notify-user-at-console
    (notification-as-format-string
      &optional                                ; pseudo rest args
      (arg1 no-arg) (arg2 no-arg) (arg3 no-arg)
      (arg4 no-arg) (arg5 no-arg) (arg6 no-arg)
      (arg7 no-arg) (arg8 no-arg) (arg9 no-arg))
  (let* ((formatted-text-string
           (tformat-text-string
             notification-as-format-string
             arg1 arg2 arg3
             arg4 arg5 arg6
             arg7 arg8 arg9))
         (gensym-string
           (export-text-string
             formatted-text-string
             'iso-8859-1-gensym-string)))
    #+development
    (force-output *standard-output*) ; keep output in sync with tracing
    (c-write-string-to-console gensym-string (if *write-console-p* 1 0))
    (reclaim-text-string formatted-text-string)
    (reclaim-gensym-string gensym-string)))

;; The call to force-output is new -- nice get rid of them all over Telewindows.
;; (MHD 10/14/94)

;; Why isn't this defined for GSI (in Lisp)?!  Should be made to work for all
;; known possible values of current-system-name.  (MHD 10/14/94)

;; Apparently because we had intended to use notify-user-in-parent-window,
;; below.  I am replacing our one use of it, and all uses of format t in GSI,
;; with notify-user-if-possible. -ncc, 21 Dec 1994

;; There was a thought at one time that this should put its info on the
;; Telewindows window.  Also, a notion of sending the text back to G2 to be
;; send back here as a notification.  That's history.  Now there's the notion
;; of making this the central place at which we can decide to send output to
;; a file (or special windows), rather than to "standard output".  This is
;; especially a problem Windows(tm), where writing to "standard output" ends
;; up overwriting the screen in an awful-looking way. (MHD 10/14/94)

;; Note: this may send "garbage" arguments on to format or notify-user, but
;; it still "works" because format allows more arguments to be supplied than
;; can be processed by the string.  Note that it would be an error to begin
;; with if the caller did not supply enough arguments; here, however, that
;; case would be masked by having the no-arg garbage argument supplied.
;;
;; Note that passing on the arguments in this was is done to save space, since
;; the alternative of using call-per-number-of-actual-args expands into a
;; lot of code.  Note also that &rest args are banned in runtime Gensym software
;; because of uncertainties about consing behavior.
;;
;; (MHD 4/17/91)


;;; `Notify-user-in-parent-window' attempts to print a message in the window
;;; which spawned G2.  Its syntax is like notify-user.  This abstraction is
;;; useful because it lets us distinguish this purpose for using format from a
;;; myriad other purposes.

;;; NOTE: as of 4/29/96, this does the same thing as calling
;;; notify-user-at-console, q.v., especially regarding use of (T)FORMAT.

;; jh per mhd, 6/28/91.

;; jh, 10/20/93.  Moved notify-user-in-parent-window from BOOKS so that other
;; systems (e.g. the GSI extension in Lisp) can use it.

(defun notify-user-in-parent-window
    (notification-as-format-string
      &optional                        ; pseudo rest args
      (arg1 no-arg) (arg2 no-arg) (arg3 no-arg)
      (arg4 no-arg) (arg5 no-arg) (arg6 no-arg)
      (arg7 no-arg) (arg8 no-arg) (arg9 no-arg))
  (notify-user-at-console
    notification-as-format-string
    arg1 arg2 arg3
    arg4 arg5 arg6
    arg7 arg8 arg9))

;; This used to call FORMAT, not notify-user-at-console. q.v. for some
;; discussion.  This also used to call format using
;;
;;   (call-per-number-of-actual-args 2 ...)
;;
;; but that was not really necessary, since extra args in a call to format are
;; OK, and error checking the two required args is not really called for.  So
;; I've dropped it in today's transformation.  Finally, this used to output to
;; *terminal-io*, whereas notify-user-at-console uses *standard-output*, but (a)
;; that should be left up to notify-user-at-console, which should do so as well
;; if it feels it's necessary, and (b) both variables should be bound to the
;; same output streams, for all intents and purposes, in our software.
;;
;; (MHD 4/29/96)




(def-side-effect-free-inlined-pseudo-function inline-extract-c-string (array)
  array)

(def-side-effect-free-inlined-pseudo-function inline-extract-c-wide-string (array)
  array)

(def-side-effect-free-inlined-pseudo-function inline-restore-lisp-gensym-string (array)
  array)

(def-side-effect-free-inlined-pseudo-function inline-restore-lisp-text-string (array)
  array)

(def-side-effect-free-inlined-pseudo-function inline-get-long-from-fixnum (fixnum)
  fixnum)

;VMS G float is 64 bits, with 11 bits of exponent
;VMS D float is 64 bits, with  8 bits of exponent

(def-inlined-pseudo-function-with-side-effects (inline-convert-to-local-float-format :double-float)
    ((managed-float-value :double-float) (use-gfloats-p :fixnum-int))
  (declare (ignore use-gfloats-p))
  managed-float-value)

(def-inlined-pseudo-function-with-side-effects (inline-convert-from-local-float-format :double-float)
    ((managed-float-value :double-float) (use-gfloats-p :fixnum-int))
  (declare (ignore use-gfloats-p))
  managed-float-value)

(def-inlined-pseudo-function-with-side-effects (inline-maybe-swap-float-bytes-for-alpha-gfloats :double-float)
    ((managed-float-value :double-float) (use-gfloats-p :fixnum-int))
  (declare (ignore use-gfloats-p))
  managed-float-value)

;;; Call-per-actual-arg-if-necessary ...

(defvar actual-arg "the ~(~A~) ")

(defmacro call-per-actual-arg-if-necessary (arg1 block-name &body body)
  `(cond
     ((eq ,arg1 actual-arg)
      (progn . ,body)
      (return-from ,block-name nil))))

;; Talk to ML or MHD about this function if interested. (MHD 4/18/88)





;;;; Shared Utilities Converting Between Gensym Strings and C Strings

(def-side-effect-free-inlined-pseudo-function inline-get-length-of-c-string (c-string)
  (length c-string))

(def-side-effect-free-inlined-pseudo-function inline-get-c-string-element (c-string index)
  (schar c-string index))

(defun-simple c-string-to-gensym-string (c-string)
  (loop with length fixnum =
        (if (null c-string)
            0
            (inline-get-length-of-c-string c-string))
        with lisp-string = (obtain-simple-gensym-string length)
        for i fixnum from 0 below length
        do (setf (schar lisp-string i)
                 (inline-get-c-string-element c-string i))
        finally (return lisp-string)))







;;;; Floating Point Number Management Primitives




;;; The following functions are used to control consing of floating point number
;;; boxes.  There are two parts to this facility, the facilities for explicit
;;; management of floating point number boxes which are stored permanently, and
;;; the facilities for fast collection of temporary numbers.  The facility for
;;; permanent number box management consists of a pool of numbers which have
;;; been created, a macro for storing numbers into places which should hold
;;; these numbers, and a macro for pulling numbers back out.  The facility for
;;; temporary numbers is used to declare a dynamic scope in which all newly
;;; created floating point numbers will be temporary and the memory for them
;;; will be reclaimed on exit from the form.

;;; These functions need only deal with floating point numbers, since we have
;;; made immediate fixnums a requirement of any Lisp we use.  An immediate
;;; number is one that is stored in the same spot in memory that would normally
;;; hold a pointer to the object in that spot.  Some Lisp implementations have
;;; data type bits in pointer words which say whether that word is a pointer or
;;; some other kind of immediate data object, such as an immediate fixnum of
;;; short float.  We require immediate fixnums of at least 25 bits.  The Lisp
;;; machines also have immediate short floats, but we are no longer using this
;;; format.  This means that Lisps on all architectures require floating point
;;; number management.

;;; We currently only create and manipulate fixnums and gensym-float numbers.
;;; Gensym floats are defined per machine.  Bignums are created and manipulated
;;; only as temporary objects.  Complex numbers, rationals, and floats other
;;; than the default gensym-float type are not created.

;;; The only primitive required for management of permanent floating point
;;; number boxes which is not a part of CLtL is the ability to destructively
;;; modify a previously allocated floating point number box.  In Lisp
;;; implementations which supply immediate floating point arrays (such as Lucid)
;;; this can be performed by doing a setf on a unit floating point array.  In
;;; other implementations (such as Coral) we need a primitive to destructively
;;; modify an existing number.

;;; We have also defined a class of numbers we will call temporary numbers.
;;; These are numbers which are created by system calls to numeric operations
;;; which we cannot manage explicitly ourselves.  However, because we don't hold
;;; on to them, they are guaranteed to become garbage on exit from the function
;;; in which they were created.

;;; The following specification has been generated to inform our Lisp vendors
;;; about our needs concerning temporary numbers.

;;; Note: The memo below is obsolete, and has been replaced with a document
;;; describing all of Gensym's needed enhancements in Lisp implementations.
;;; However, the managed number facilities have not changed in spirit or
;;; specification detail from what is found below.  For the actual requirements
;;; document sent to vendors, see the Platform Engineering group.  -jra 10/24/90

;;;       Memory Management for Real-Time Lisp Applications

;;;                       Gensym Corporation


;;; For our purposes, a real-time application is a program which
;;; must run continuously for an indefinitely long period of time,
;;; and must always be ready to respond promptly to inputs from its
;;; environment.  Requirements vary, but it would not be unusual to
;;; have an application that must run for the better part of a year,
;;; and have a response time of a second or two.

;;; In order to meet these requirements, the memory management
;;; techniques that are adapted must not remove the computer from
;;; service or seriously degrade its performance long enough to
;;; interfere with its response time.  While some garbage collection
;;; techniques have an acceptable computational burden when averaged
;;; over time, none that we are aware of meets the requirement of
;;; never interfering with the response time of the application.
;;; Therefore, we must be able to write code that causes no garbage
;;; collection.

;;; Garbage-free operation requires that a certain coding discipline
;;; be observed by the application program writers, aided by a few
;;; extra features of the Lisp system that must be provided by the
;;; Lisp vendor.  The basic idea is that all storage allocation fall
;;; into one of two distinct modes without there being any middle
;;; ground:  (1) Managed allocation means that the allocated object
;;; will be managed by the application program throughout the life
;;; of the process, and that it will never be abandoned.  This
;;; requires that the application program has its own resource
;;; recycling mechanism for managed objects.  (2) Temporary
;;; allocation means that the allocation takes place within a
;;; dynamically scoped context, and that the application guarantees
;;; that there will not be any references to the allocated object at
;;; the time the dynamically scoped context is exited.

;;; Our software manipulates three types of objects: conses, arrays
;;; and boxed numbers.  (Immediate numbers, such as fixnums, and
;;; stack numbers are not an allocation problem and are not regarded
;;; as being objects.)  All of our conses and arrays are treated as
;;; managed objects, and are recycled by our software.  Running our
;;; software does not create garabge in the form of conses or
;;; arrays.  The major problem is with numbers.

;;; We propose the following features be added to Common Lisp for
;;; the purpose of handling numbers as temporary objects:


;;;         with-temporary-numbers {form}*                [macro]

;;; All numbers created within the dynamic scope of this form (but
;;; not within a further nesting of a with-permanent-numbers) are
;;; created in a separate space called the temporary number space.
;;; The user of this form must guarantee that no such numbers will
;;; be referenced upon exiting from the form.  With-temporary-
;;; numbers should evaluate all the body forms, and return the
;;; values of the last form inside of it.


;;;         with-permanent-numbers {form}*                [macro]

;;; This form only needs to be used inside of with-temporary-
;;; numbers.  It causes numbers to be allocated from their usual
;;; place.  With-permanent-numbers should evaluate all the body
;;; forms, and return the values of the last form inside of it.
;;; (This form will be used to allocate numbers within
;;; with-temporary-numbers which must survive the dynamic scope of
;;; that form.)

;;; The temporary number space need not be very large because the
;;; dynamic scope of with-temporary-numbers will be kept small.  But
;;; the switching of contexts should be rapid, perhaps no longer
;;; than it takes to bind a special variable or unbind it.

;;; We also must manage number boxes.  In order to do this, we must
;;; be able to destructively copy a floating point number into a
;;; managed floating point box.  This operation can be provided by
;;; setf's into floating point arrays which use immediate numbers,
;;; or else through the following supplied primitive for destructive
;;; number copying.


;;;         copy-into-float place source                [function]

;;; This function destructively copies the floating point number in
;;; source into the floating point number box specified by place.

;;; We will discuss in a separate memo storage management issues
;;; relating to system features such as file service, compilers,
;;; etc.  In some cases there is no problem, and in others, more
;;; cooperation between vendor and application developer may be
;;; needed.

;;; End of memo to vendors.






;;;; Number Types




;;; The following paragraph describes, for each Lisp vendor, the subtype of
;;; float which we have picked as gensym-float, how float-vectors are
;;; implemented, and what the layout is of the rest of their float and fixnum
;;; types.  Float-vectors are always used to implement mutable float point
;;; number boxes, and are the basis for managed-floats.

;;;   Lucid 3.0, or new Lucid 2.0 ports (Sun Sparc, HP9000 800 series):
;;;     gensym-float = double-float
;;;     float-vectors are immediate double-float arrays
;;;     double-float = long-float = single-float = short-float = 64 bits, i.e.
;;;       53 bits mantissa, 11 bits exponent, about 16 digits precision, IEEE,
;;;       most-positive-double-float = 1.7976931348623157d308,
;;;       least-positive-normalized-double-float = 2.2250738585072014d-308,
;;;       most-negative-double-float = -1.7976931348623157d308,
;;;       least-negative-normalized-double-float = -2.2250738585072014d-308
;;;     fixnums = 30 bits, most-positive-fixnum = 536870911,
;;;       most-negative-fixnum = -536870912
;;;     NOTE:  In these systems, an immediate array of single floats holds its
;;;       values as 32 bit values, even though single floats are supposed to be
;;;       64 bits long.  So, we use double float as the gensym-float type, which
;;;       then gives us 64 bit values in immediate double float arrays.
;;;
;;;   Coral (Apple Allegro Common Lisp, now Macintosh Common Lisp):
;;;     gensym-float = single-float
;;;     float-vectors are simple-vectors containing floating point numbers.  The
;;;       floating point numbers are mutated using a destructive overwrite
;;;       function supplied by Coral
;;;     short-float = single-float = double-float = long-float = 64 bits, i.e.
;;;       53 bits mantissa, 11 bits exponent, about 16 digits precision, IEEE,
;;;       most-positive-double-float = 1.7976931348623157d308,
;;;       least-positive-normalized-double-float = 2.2250738585072014d-308,
;;;       most-negative-double-float = -1.7976931348623157d308,
;;;       least-negative-normalized-double-float = -2.2250738585072014d-308
;;;     fixnums = 31 bits, most-positive-fixnum = 1073741823,
;;;       most-negative-fixnum = -1073741824
;;;
;;;   Chestnut:
;;;     gensym-float = double-float
;;;     float-vectors are immediate double-float arrays
;;;     short-float = single-float = double-float = long-float = 64 bits, i.e.
;;;       53 bits mantissa, 11 bits exponent, about 16 digits precision, IEEE,
;;;       most-positive-double-float = 1.7976931348623157d308,
;;;       least-positive-normalized-double-float = 2.2250738585072014d-308,
;;;       most-negative-double-float = -1.7976931348623157d308,
;;;       least-negative-normalized-double-float = -2.2250738585072014d-308
;;;     fixnums = 30 bits, most-positive-fixnum = 536870911,
;;;     most-negative-fixnum = -536870912






;;;; Permanent Floats




;;; Permanent floating point numbers are used on the Coral platform as number
;;; boxes, since this implementation does not have immediate double-float
;;; arrays.  They are also used at the moment by facilities which do not manage
;;; numbers, but leak floats.  The second kind of usage should be removed as
;;; soon as possible.  Permanent numbers are made by copying existing numbers in
;;; a permanent allocation context.

(defparameter floating-zero 0.0)

(defmacro copy-lucid-float (float)
  `(+e ,float floating-zero))

(defmacro copy-allegro-float (float)
  `(+e ,float floating-zero))

(defmacro copy-vanilla-float (float)
  `(+ ,float floating-zero))




;;; The macro `copy-gensym-float' takes a gensym float as its argument and will
;;; create and return a new float which is a copy of the given float.  This can
;;; be used inside of either a temporary or permanent number creation context to
;;; return a new number created into that context.

(defmacro copy-gensym-float (gensym-float)
  (cond
    ((eval-feature :lucid) `(copy-lucid-float ,gensym-float))
    ((eval-feature :allegro) `(copy-allegro-float ,gensym-float))
    ((eval-feature :vanilla-numbers) `(copy-vanilla-float ,gensym-float))
    ))




;;; The function `make-permanent-gensym-float' makes a new permanent gensym
;;; float equivalent in value to gensym-float.

(defmacro make-permanent-gensym-float (gensym-float)
  (if (or (symbolp gensym-float) (constantp gensym-float))
      `(with-permanent-gensym-float-creation
         (copy-gensym-float ,gensym-float))
      (let ((float (gensym)))
        `(let ((,float ,gensym-float))
           (with-permanent-gensym-float-creation
             (copy-gensym-float ,float))))))







;;;; Float-Vectors




;;; The following code provides creation, accessing, and mutation operations for
;;; float vectors.  Float vectors are the basis of all floating point number
;;; management facilities.  They are used as a primitive for
;;; managed-simple-float-arrays, which are used in managed-float-arrays, which
;;; themselves are used to implement managed-floats.

;;; The function `generate-float-vector' takes length argument and returns a
;;; vector of number boxes, suitable for storing gensym-floats.  This vector is
;;; guaranteed to be the most efficient way of storing a large number of
;;; gensym-floats.

(defun-simple generate-float-vector (length)
  (let ((array
          (with-permanent-array-creation
            (make-array length
                        :element-type (gensym-float-type)
                        :initial-element 0.0))))
    #+development
    (setf (aref array 0) reclaimed-managed-float-array-value-holder)
    array))



;;; The macro `float-vector-aref' takes a float-vector and an index and returns
;;; the value of the float stored in that place.  Note that this macro conses
;;; temporary floats and should only be used in a temporary gensym-float
;;; context.  This accessor should be used with SETF to mutate the values of a
;;; float-vector.  The macro `cached-float-vector-aref' is a possibly faster
;;; version of this macro which performs the same function, though it may return
;;; a value which shares substructure with the managed-floats in the vector.


(defmacro float-vector-aref (float-vector index)
  (cond
    ((eval-feature :vanilla-numbers)
     `(the ,(gensym-float-type)
           (aref (the (simple-array ,(gensym-float-type) (*)) ,float-vector)
                 (the fixnum ,index))))
    ((eval-feature :lucid)
     `(potentially-rigorous-operation
        (the ,(gensym-float-type)
             (aref (the (simple-array ,(gensym-float-type) (*)) ,float-vector)
                   (the fixnum ,index)))))))

(defmacro cached-float-vector-aref (float-vector index)
  (cond
    ((eval-feature :vanilla-numbers) `(float-vector-aref ,float-vector ,index))
    ((eval-feature :lucid) `(float-vector-aref ,float-vector ,index))))

(defmacro float-vector-aset (float-vector index float)
  (cond
    ((eval-feature :vanilla-numbers)
     `(setf (aref (the (simple-array ,(gensym-float-type) (*)) ,float-vector)
                  (the fixnum ,index))
            (the ,(gensym-float-type) ,float)))
    ((eval-feature :lucid)
     `(potentially-rigorous-operation
        (setf (aref (the (simple-array ,(gensym-float-type) (*)) ,float-vector)
                    (the fixnum ,index))
              (the ,(gensym-float-type) ,float))))))

(defsetf float-vector-aref float-vector-aset)




;;; The macro `mutate-float-vector' takes a float-vector, an index within the
;;; float vector, and a new gensym-float to place into the vector at the given
;;; index.  This macro always returns NIL.  It is optimized on those platforms
;;; that can handle it.  Note that the return value of NIL is to ensure that the
;;; value of this operation is never used, which might end up consing a
;;; double-float for the unwary.

(defmacro mutate-float-vector (float-vector index gensym-float)
  `(progn
     (setf (float-vector-aref ,float-vector ,index) ,gensym-float)
     nil))




;;; The macro `float-vector-length' takes a float-vector and returns its length,
;;; using the most efficient fetching means possible.

(defmacro float-vector-length (float-vector)
  `(the fixnum (length (the (simple-array ,(gensym-float-type) (*))
                            ,float-vector))))




;;; The macro `float-vector-p' takes a thing and returns whether or not it is a
;;; float-vector.

(defmacro float-vector-p (thing)
  `(double-float-vector-p ,thing))






;;;; Simple Float Array Pool




;;; The Simple Float Array Pool manages simple arrays of floats of lengths from
;;; 1 through `maximum-managed-simple-float-array-size' (which is currently
;;; 1024).  The function `allocate-managed-simple-float-array' allocates simple
;;; arrays of floats, and the function `reclaim-managed-simple-float-array'
;;; returns simple float arrays to the pool.  The pool is metered under the name
;;; `managed-simple-float-arrays'.

;;; There are also a set of oversized managed simple float arrays.  They closely
;;; mirror the simple float array implementation, but are for float vectors
;;; larger than the maximum-managed-simple-float-array-size.  Their limitation
;;; is that they are not allocated to requested size, but the size is rounded up
;;; to the next largest multiple of 1024.  The maximum oversized float vector is
;;; 1Meg. (i.e. 1,048,576) elements long.  When
;;; allocate-managed-simple-float-array is asked to make a vector over 1024
;;; elements long, then it will use an oversized vector instead.
;;; Reclaim-managed-simple-float-array will receive and do the right thing with
;;; oversized vectors.

(defconstant maximum-managed-simple-float-array-size 1024)

(defconstant maximum-oversized-managed-simple-float-array-size 1048576)



;;; The cons pool `float-array' contains conses for the simple float array and
;;; float array pools.

(defconser float-array)




;;; The system variable `vector-of-simple-float-array-pools' contains a simple
;;; vector whose elements are the pools of simple vectors.  Element N of this
;;; vector contains the pool of vectors of length N.  Each pool is a float-array
;;; list of the simple float arrays of the given length.  The
;;; `vector-of-oversized-simple-float-array-pools' is similar, except that
;;; element N of this vector contains the pool of vectors of size 1024 * N.

(defun allocate-initial-vector-of-simple-float-array-pools ()
  (make-static-array (+f maximum-managed-simple-float-array-size 1)
                     :initial-element nil))


(def-system-variable vector-of-simple-float-array-pools utilities0
  (:funcall allocate-initial-vector-of-simple-float-array-pools)
  nil t)                                ; see note (MHD 2/7/96)

(def-system-variable vector-of-oversized-simple-float-array-pools utilities0
  (:funcall allocate-initial-vector-of-simple-float-array-pools)
  nil t)                                ; see note (MHD 2/7/96)

;;; The variable `created-simple-float-array-pool-arrays' contains the integer
;;; count of the number of simple float arrays created in this pool.  The
;;; function `outstanding-simple-float-array-pool-arrays' returns the count of
;;; the number of simple float arrays which have been created but not yet
;;; reclaimed.  It does this by subtracting the count of all of the arrays in
;;; the pool from the created count.  The function `sflap-memory-usage' returns
;;; the number of words used by all of the created simple float arrays for this
;;; pool.  Each of these is mirrored by a similar implementation for the
;;; oversized pool.

(def-system-variable created-simple-float-array-pool-arrays
    utilities0 0
    nil t)                                ; see note (MHD 2/7/96)

(def-system-variable created-oversized-simple-float-array-pool-arrays
    utilities0 0
    nil t)                                ; see note (MHD 2/7/96)

(defun outstanding-simple-float-array-pool-arrays ()
  (loop with vectors-in-pools fixnum = 0
        for index from 1 to maximum-managed-simple-float-array-size
        do
    (incff vectors-in-pools
           (length (svref vector-of-simple-float-array-pools index)))
        finally (return (-f created-simple-float-array-pool-arrays
                            vectors-in-pools))))

(defun outstanding-oversized-simple-float-array-pool-arrays ()
  (loop with vectors-in-pools fixnum = 0
        for index from 1 to maximum-managed-simple-float-array-size
        do
    (incff vectors-in-pools
           (length (svref vector-of-oversized-simple-float-array-pools index)))
        finally (return (-f created-oversized-simple-float-array-pool-arrays
                            vectors-in-pools))))

(def-system-variable simple-float-array-pool-memory-usage
    utilities0 0
    nil t)                                ; see note (MHD 2/7/96)

(def-system-variable oversized-simple-float-array-pool-memory-usage
    utilities0 0
    nil t)                                ; see note (MHD 2/7/96)

;; NOTE: (MHD 2/7/96) bind these system variables globally as well as of 2/7/96
;; -- because slot init forms are now copied at load time -- done for the
;; Unicode/ wide strings project. (MHD 2/7/96)

(defun sflap-memory-usage ()
  simple-float-array-pool-memory-usage)

(defun oversized-sflap-memory-usage ()
  oversized-simple-float-array-pool-memory-usage)

(def-system-object-pool managed-simple-float-arrays
    (simple-array gensym-float)
  created-simple-float-array-pool-arrays
  nil outstanding-simple-float-array-pool-arrays
  sflap-memory-usage)

(def-system-object-pool managed-oversized-simple-float-arrays
    (simple-array gensym-float)
  created-oversized-simple-float-array-pool-arrays
  nil outstanding-oversized-simple-float-array-pool-arrays
  oversized-sflap-memory-usage)

(defparameter replenished-simple-float-array-size-limit 10)

(defparameter replenished-simple-float-arrays-to-make-at-a-time 10)

;; Note that managed-floats satisfy this predicate.
(def-substitution-macro managed-simple-float-array-p (thing)
  (float-vector-p thing))

;;; The function `allocate-managed-simple-float-array' takes a size and
;;; allocates and returns a simple float array.  The contents of this array are
;;; undefined on allocation, other than that they are of type gensym-float.

(defun-simple allocate-managed-simple-float-array (requested-length)
  (declare (type fixnum requested-length))
  #+development
  (when (or (<=f requested-length 0)
            (>f requested-length maximum-oversized-managed-simple-float-array-size))
    (error "Requested managed simple float array size, ~a, exceeds limits."
           requested-length))
  (let* ((oversized? (>f requested-length maximum-managed-simple-float-array-size))
         (length (if (and oversized?
                          (/=f (logandf requested-length 1023) 0))
                     (+f (logandf requested-length -1024) 1024)
                     requested-length))
         (vector-of-pools (if oversized?
                              vector-of-oversized-simple-float-array-pools
                              vector-of-simple-float-array-pools))
         (index (if oversized? (ashf length -10) length))
         (available-array-cons? (svref vector-of-pools index))
         (result
           (cond (available-array-cons?
                  (let ((array (car-of-cons available-array-cons?)))
                    #+development
                    (unless (reclaimed-managed-float-array-p array)
                      (error "Corruption of float array pool"))
                    (setf (svref vector-of-pools index)
                          (cdr-of-cons available-array-cons?))
                    (reclaim-float-array-cons-macro available-array-cons?)
                  array))
                 ((and (<=f length replenished-simple-float-array-size-limit)
                       (<=f length maximum-managed-simple-float-array-size)) ; for safety's sake
                  (loop with new-vector-list
                          = (make-float-array-list
                              (-f replenished-simple-vectors-to-make-at-a-time 1))
                        for new-vector-cons on new-vector-list
                        do
                    (setf (car new-vector-cons) (generate-float-vector length))
                        finally
                          (setf (svref vector-of-pools index)
                                new-vector-list))
                  (atomic-incff created-simple-float-array-pool-arrays
                         replenished-simple-float-arrays-to-make-at-a-time)
                  (atomic-incff simple-float-array-pool-memory-usage
                         (*f replenished-simple-float-arrays-to-make-at-a-time
                             (bytes-per-double-float-simple-array length)))
                  (generate-float-vector length))
                 ((not oversized?)
                  (atomic-incff created-simple-float-array-pool-arrays)
                  (atomic-incff simple-float-array-pool-memory-usage
                         (bytes-per-double-float-simple-array length))
                  (generate-float-vector length))
                 (t
                  (atomic-incff created-oversized-simple-float-array-pool-arrays)
                  (atomic-incff oversized-simple-float-array-pool-memory-usage
                         (bytes-per-double-float-simple-array length))
                  (generate-float-vector length)))))
    (declare (type fixnum length index))
    #+development
    (setf (aref result 0) 0.0d0)
    (note-allocate-cons result 'managed-simple-float-array)
    result))

(defun-simple allocate-managed-simple-float-array-of-length-1 ()
  (let* ((available-array-cons? (svref vector-of-simple-float-array-pools 1))
         (result
           (cond (available-array-cons?
                  (let ((array (car-of-cons available-array-cons?)))
                    #+development
                    (unless (reclaimed-managed-float-array-p array)
                      (error "Corruption of float array pool"))
                    (setf (svref vector-of-simple-float-array-pools 1)
                          (cdr-of-cons available-array-cons?))
                    (reclaim-float-array-cons-macro available-array-cons?)
                  array))
                 (t
                  (loop with new-vector-list
                          = (make-float-array-list
                              #|(-f replenished-simple-vectors-to-make-at-a-time 1)|# 9) ;known at compile time
                        for new-vector-cons on new-vector-list
                        do
                    (setf (car new-vector-cons) (generate-float-vector 1))
                        finally
                          (setf (svref vector-of-simple-float-array-pools 1)
                                new-vector-list))
                  (atomic-incff created-simple-float-array-pool-arrays
                         #|replenished-simple-float-arrays-to-make-at-a-time|# 10) ;efficiency hardcode
                  (atomic-incff simple-float-array-pool-memory-usage
                         (*f #|replenished-simple-float-arrays-to-make-at-a-time|# 10
                             (bytes-per-double-float-simple-array 1)))
                  (generate-float-vector 1)))))
    (note-allocate-cons result 'managed-simple-float-array)
    result))

(defun-simple reclaim-managed-simple-float-array (managed-simple-float-array)
  #+development
  (progn
    ;; Note: Neither = nor =e work here.  -rh 6/18/96
    (when (reclaimed-managed-float-array-p managed-simple-float-array)
      (error "Corruption of float array pool"))
    (setf (aref managed-simple-float-array 0) reclaimed-managed-float-array-value-holder))
  (let* ((length (float-vector-length managed-simple-float-array))
         (oversized? (>f length maximum-managed-simple-float-array-size))
         (vector-of-pools (if oversized?
                              vector-of-oversized-simple-float-array-pools
                              vector-of-simple-float-array-pools))
         (index (if oversized? (ashf length -10) length)))
    (declare (type fixnum length index))
    #+development
    (when (or (<=f length 0)
              (>f length maximum-oversized-managed-simple-float-array-size))
      (error "Reclaimed managed simple float array size, ~a, exceeds limits."
             length))
    (note-reclaim-cons managed-simple-float-array 'managed-simple-float-array)
    (setf (svref vector-of-pools index)
          (float-array-cons-macro
            managed-simple-float-array
            (svref vector-of-pools index)))
    nil))

(defun-simple reclaim-managed-simple-float-array-of-length-1
    (managed-simple-float-array)
  #+development
  (progn
    ;; Note: Neither = nor =e work here.  -rh 6/18/96
    (when (reclaimed-managed-float-array-p managed-simple-float-array)
      (error "Corruption of float array pool"))
    (setf (aref managed-simple-float-array 0) reclaimed-managed-float-array-value-holder))

  (note-reclaim-cons managed-simple-float-array 'managed-simple-float-array)
  (setf (svref vector-of-simple-float-array-pools 1)
        (float-array-cons-macro
          managed-simple-float-array
          (svref vector-of-simple-float-array-pools 1)))
  nil)

;;;; Managed Float Array Specification




;;; Within G2 there is a need for managed arrays of floats of arbitrary length.
;;; This facility is provided by the Managed Float Array Pool.  Arrays of
;;; arbitrary lengths up to 64K long can be created and reclaimed.  These arrays
;;; can be grown and shrunk, and portions of these arrays can be efficiently
;;; copied.  The function `allocate-managed-float-array' gives out managed
;;; arrays, and the function `reclaim-managed-float-array' returns them to the
;;; pool.  The macro `managed-float-aref' is used to access and SETF their
;;; contents.  This facility contains other tools for adjusting array sizes and
;;; copying array contents.

;;; This facility uses the pool of simple float arrays as its source for
;;; buffers, and used the pool of managed simple vectors for spine arrays.

;;; Buffer sizes are determined using the function `buffer-size-for-partial-
;;; buffer', thereby adopting the buffer management scheme used for managed
;;; arrays.

;;; The macro `managed-float-array-identity-marker' takes a vector at least one
;;; element long, and returns the contents of the identity marker spot in that
;;; vector.

(defmacro managed-float-array-identity-marker (non-empty-vector)
  `(svref ,non-empty-vector 0))




;;; The macro `managed-float-array-length' takes a managed array and returns its
;;; allocated length.

(defmacro managed-float-array-length (managed-float-array)
  `(svref ,managed-float-array 1))




;;; The macro `managed-float-array-buffer' takes a managed-array and a zero
;;; based index to a buffer in that array, and returns the buffer.

(defmacro managed-float-array-buffer (managed-float-array buffer-index)
  (if (constantp buffer-index)
      `(svref ,managed-float-array ,(+ (eval buffer-index) 2))
      `(svref ,managed-float-array (+f ,buffer-index 2))))




;;; The object stored in `managed-float-array-unique-marker' is placed in
;;; element zero of managed-float-arrays and is queried by
;;; managed-float-array-p.

(defvar-of-special-global managed-float-array-unique-marker
  (cons 'managed-float-array nil))




;;; The macro `managed-float-array-p' returns whether or not this object is an
;;; allocated managed-float-array.

(def-substitution-macro managed-float-array-p (thing)
  (and (simple-vector-p thing)
;       (>f (length thing) 0)
       (eq (managed-float-array-identity-marker thing)
           managed-float-array-unique-marker)))

;; We don't allocate zero length simple vectors in anything I know, and this is
;; becoming a performance concern after looking at profiling.  Commenting out
;; the length test.  -jra 1/22/92




;;; The parameter `maximum-managed-float-array-buffer-size' contains the maximum
;;; length of a buffer of a managed array, currently 1024.  The parameter
;;; `maximum-managed-float-array-size' contains the maximum size of a managed
;;; float array, currently 1046528.  This number is 2K less than 1Meg since, one
;;; element of the spine array needs to hold the total size of a managed array,
;;; and one element holds the managed-float-array identifying marker, leaving
;;; two fewer spots for buffers.

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defconstant maximum-managed-float-array-buffer-size 1024))


(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant maximum-managed-float-array-size
             #.(* (- maximum-managed-simple-vector-size 2)
                  maximum-managed-float-array-buffer-size))
)





;;; The function `allocate-managed-float-array' takes a number from 1 through
;;; 1046528 (1Meg - 2K) and returns a managed float array of that length.  These
;;; vectors are the most efficient way to store boxed gensym-floats.

;;; As a feature for use in future run time versions of G2, it takes an optional
;;; second argument called make-exactly which can be used when this vector is
;;; very unlikely to be reclaimed.  If this is true, then the returned managed
;;; array will have buffer sizes which are exactly as long as is requested.  This
;;; should only be used in run-time versions of G2 where different knowledge
;;; bases will not be loaded over one another, and then only for code bodies or
;;; history buffers.  Since we don't have those now, this feature should not
;;; currently be used.

(defun allocate-managed-float-array (length &optional (make-exactly nil))
  #+development
  (when (or (<f length 0) (>f length maximum-managed-float-array-size))
    (error "Can't make a managed float array ~a elements long." length))
  (multiple-value-bind (full-size-buffers size-of-partial-buffer)
      (floorf length maximum-managed-float-array-buffer-size)
    (let* ((total-buffers (+f full-size-buffers
                              (if (>f size-of-partial-buffer 0)
                                  1
                                  0)))
           (spine-vector (allocate-managed-simple-vector-for-float-array
                           (if make-exactly
                               (+f total-buffers 2)
                               (buffer-size-for-partial-buffer
                                 (+f total-buffers 2)
                                 managed-array-allocation-schemes)))))
      (setf (managed-float-array-identity-marker spine-vector)
            managed-float-array-unique-marker)
      (setf (managed-float-array-length spine-vector) length)
      (loop for full-buffer-index from 0 below full-size-buffers
            do
        (setf (managed-float-array-buffer spine-vector full-buffer-index)
              (allocate-managed-simple-float-array
                maximum-managed-float-array-buffer-size)))
      (when (>f size-of-partial-buffer 0)
        (setf (managed-float-array-buffer spine-vector (-f total-buffers 1))
              (allocate-managed-simple-float-array
                (if make-exactly
                    size-of-partial-buffer
                    (buffer-size-for-partial-buffer
                      size-of-partial-buffer
                      managed-array-allocation-schemes)))))
      spine-vector)))




;;; The macro `managed-float-aref' takes a managed float array and an index, and
;;; returns that element of the given array.  This form can be used with SETF to
;;; mutate a value in the array.  In development this form will do bounds
;;; checking on the given index, but in distribution code it performs direct
;;; svrefs on the internal structures of the managed array.  The macro
;;; `cached-managed-float-aref' performs the same function as
;;; managed-float-aref, but may be faster.  The value it returns may share
;;; structure with the managed-float-array, so the value should be used and
;;; discarded before any mutations can occur on the managed-float-array.

;; Note that there are optimizations done in the code below for the case where
;; the index is a form which calls CAR.  This is optimized specially here since
;; managed-floats use managed-float-arrays as their implementation, where the
;; indices are always fetched from the CARs of conses.  -jra 3/26/91

(defmacro managed-float-aref (managed-float-array index)
  (let ((index-shift
          (+ (- (integer-length maximum-managed-float-array-buffer-size)) 1))
        (index-mask (- maximum-managed-float-array-buffer-size 1)))
    (cond ((constantp index)
           (multiple-value-bind (spine-index buffer-index)
               (floor (eval index) maximum-managed-float-array-buffer-size)
             `(float-vector-aref
                (managed-float-array-buffer ,managed-float-array ,spine-index)
                ,buffer-index)))
          ((and (or (symbolp index)
                    (and (consp index)
                         (eq (car index) 'car-of-cons)
                         (symbolp (second index))))
                (not (eval-feature :development)))
           `(float-vector-aref
              (managed-float-array-buffer
                ,managed-float-array (ashf ,index ,index-shift))
              (logandf ,index ,index-mask)))

          (t
           (let ((array-var (if (symbolp managed-float-array)
                                managed-float-array
                                (gensym)))
                 (index-var (gensym))
                 (buffer-var (gensym)))
             `(let* (,@(if (neq array-var managed-float-array)
                           `((,array-var ,managed-float-array))
                           nil)
                     (,index-var ,index)
                     (,buffer-var
                      (managed-float-array-buffer
                        ,array-var (ashf ,index-var ,index-shift))))
                (declare (type fixnum ,index-var))
                (assert-for-development
                   (<f ,index-var (managed-float-array-length ,array-var))
                    "Managed-float-aref out of range.  Array = ~a, Length = ~a, Index = ~a"
                    ,array-var (managed-float-array-length ,array-var) ,index-var)
                (float-vector-aref
                  ,buffer-var
                  (logandf ,index-var ,index-mask))))))))

#+development
(defun managed-float-aref-error (array index)
  (error "Managed-float-aref out of range.  Array = ~a, Length = ~a, Index = ~a"
         array (managed-float-array-length array) index))

(defmacro cached-managed-float-aref (managed-float-array index)
  (if (constantp index)
      (multiple-value-bind (spine-index buffer-index)
          (floor (eval index) maximum-managed-float-array-buffer-size)
        `(cached-float-vector-aref
           (managed-float-array-buffer ,managed-float-array ,spine-index)
           ,buffer-index))
      (let ((array-var (if (or (symbolp managed-float-array)
                               (symbolp index))
                           managed-float-array
                           (gensym)))
            (index-var (if (symbolp index)
                           index
                           (gensym)))
            (index-shift
              (+ (- (integer-length maximum-managed-float-array-buffer-size))
                 1))
            (index-mask (- maximum-managed-float-array-buffer-size 1)))
        `(let* (,@(if (neq array-var managed-float-array)
                      `((,array-var ,managed-float-array))
                      nil)
                ,@(if (neq index-var index)
                      `((,index-var ,index))
                      nil))
           ,@(if (neq index-var index)
                 `((declare (type fixnum ,index-var)))
                 nil)
           (assert-for-development
             (<f ,index-var (managed-float-array-length ,array-var))
             "Managed-float-aref out of range.  Array = ~a, Length = ~a, Index = ~a"
             ,array-var (managed-float-array-length ,array-var) ,index-var)
           (cached-float-vector-aref
             (managed-float-array-buffer ,array-var (ashf ,index-var ,index-shift))
             (logandf ,index-var ,index-mask))))))

(defmacro managed-float-aset (managed-float-array index value)
  (if (constantp index)
      (multiple-value-bind (spine-index buffer-index)
          (floor (eval index) maximum-managed-float-array-buffer-size)
        `(setf (float-vector-aref
                 (managed-array-buffer ,managed-float-array ,spine-index)
                 ,buffer-index)
               ,value))
      (let ((array-var (if (or (symbolp managed-float-array)
                               (symbolp index))
                           managed-float-array
                           (gensym)))
            (index-var (if (symbolp index)
                           index
                           (gensym)))
            (index-shift
              (+ (- (integer-length maximum-managed-float-array-buffer-size)) 1))
            (index-mask (- maximum-managed-float-array-buffer-size 1)))
        `(let* (,@(if (neq array-var managed-float-array)
                      `((,array-var ,managed-float-array))
                      nil)
                ,@(if (neq index-var index)
                      `((,index-var ,index))
                      nil))
           ,@(if (neq index-var index)
                 `((declare (type fixnum ,index-var)))
                 nil)
           (assert-for-development
             (<f ,index-var (managed-float-array-length ,array-var))
             "Managed-float-aref out of range.  Array = ~a, Length = ~a, Index = ~a"
             ,array-var (managed-float-array-length ,array-var) ,index-var)
           (setf (float-vector-aref
                   (managed-float-array-buffer
                     ,array-var (ashf ,index-var ,index-shift))
                   (logandf ,index-var ,index-mask))
                 ,value)))))

(defsetf managed-float-aref managed-float-aset)




;;; The macro `mutate-managed-float-array' is the preferred operation for
;;; modifying managed-float-arrays.  It modifies the given index of the managed
;;; float array to contain the passed gensym-float.  It always returns NIL.  If
;;; you must have a version of this operation which returns the gensym-float,
;;; use setf of the managed-float-aref of the array.

(defmacro mutate-managed-float-array (managed-float-array index gensym-float)
  (let ((index-shift
          (+ (- (integer-length maximum-managed-float-array-buffer-size)) 1))
        (index-mask (- maximum-managed-float-array-buffer-size 1)))
    (if (or (constantp index)
            (symbolp index)
            (and (consp index)
                 (eq (car index) 'car-of-cons)
                 (symbolp (second index))))
        `(mutate-float-vector
           (managed-float-array-buffer
             ,managed-float-array (ashf ,index ,index-shift))
           (logandf ,index ,index-mask)
           ,gensym-float)
        (let ((array-var (gensym))
              (index-var (gensym)))
          `(let ((,array-var ,managed-float-array)
                 (,index-var ,index))
             (mutate-float-vector
               (managed-float-array-buffer
                 ,array-var (ashf ,index-var ,index-shift))
               (logandf ,index-var ,index-mask)
               ,gensym-float))))))




;;; The function `reclaim-managed-float-array' takes a managed float array and
;;; reclaims it.

(defun reclaim-managed-float-array (managed-float-array)
  #+development
  (unless (managed-float-array-p managed-float-array)
    (error "Attempted to reclaim ~a as a managed-float-array."
           managed-float-array))
  (let* ((length (managed-float-array-length managed-float-array)))
    (multiple-value-bind (full-buffers remainder)
        (floorf length maximum-managed-float-array-buffer-size)
      (let ((buffer-count (if (>f remainder 0)
                              (+f full-buffers 1)
                              full-buffers)))
        (declare (type fixnum buffer-count))
        (loop for buffer-index from 0 below buffer-count
              for buffer = (managed-float-array-buffer
                             managed-float-array buffer-index)
              do
          (reclaim-managed-simple-float-array buffer)))))
  (setf (managed-float-array-identity-marker managed-float-array) nil)
  (reclaim-managed-simple-vector-for-float-array managed-float-array)
  nil)




;;; The macro `copy-simple-float-array-portion' takes a source simple array with
;;; element type gensym-float, a source start index, an element count, a
;;; destination simple gensym-float array, and a destination start index.  It
;;; then copies element count elements of the source array starting at source
;;; index into the destination array starting at destination-index.  This
;;; operation should be optimized for each system as much as is possible.

(defmacro copy-simple-float-array-portion
          (source-simple-float-array
            source-index element-count
            destination-simple-float-array
            destination-index)
  (let ((vector1 (gensym))
        (index1 (gensym))
        (index1-limit (gensym))
        (vector2 (gensym))
        (index2 (gensym)))
    `(let* ((,vector1 ,source-simple-float-array)
            (,index1 ,source-index)
            (,index1-limit (+f ,index1 ,element-count))
            (,vector2 ,destination-simple-float-array)
            (,index2 ,destination-index))
       (declare (type fixnum ,index1 ,index1-limit ,index2)
                ;; jh, 7/3/93.  Switched in for the new Chestnut rev.
                #+chestnut-3
                (type (simple-array ,(gensym-float-type) (*))
                      ,vector1 ,vector2)
                )
       #+development
       (when (or (>f ,index1-limit (length ,vector1))
                 (>f (+f ,index2 (-f ,index1-limit ,index1))
                     (length ,vector2)))
         (error "Copy simple vector portion out of bounds"))
       (with-temporary-gensym-float-creation copy-simple-float-array-portion
         (loop while (<f ,index1 ,index1-limit)
               do
           (mutate-float-vector
             ,vector2 ,index2
             (cached-float-vector-aref ,vector1 ,index1))
           (incff ,index1)
           (incff ,index2))))))

(defun copy-simple-float-array-portion-function
       (source-simple-float-array
        source-index element-count
        destination-simple-float-array
        destination-index)
  (declare (eliminate-for-gsi))
  (copy-simple-float-array-portion
    source-simple-float-array
    source-index element-count
    destination-simple-float-array
    destination-index))




;;; The function `adjust-managed-float-array' takes a managed float array and a
;;; new length, and returns a managed float array of the requested length.  Note
;;; that the returned managed array may or may not be EQ to the managed array
;;; passed in, so you must receive the new value and replace old pointers to the
;;; managed array with pointers to the new array.  By default the new array
;;; contains all of the elements of the old array which are still in bounds.
;;; The optional argument, dont-copy, controls whether this function will make
;;; any effort to copy old contents from the buffers of the old array to any
;;; buffers of the new array.

(defun adjust-managed-float-array
       (managed-float-array new-length &optional (dont-copy nil))
  (declare (eliminate-for-gsi))
  (let ((old-length (managed-float-array-length managed-float-array)))
    (when (=f new-length old-length)
      (return-from adjust-managed-float-array managed-float-array))
    (let* ((old-full-buffers
             (floorf-positive old-length maximum-managed-float-array-buffer-size))
           (old-remainder
             (modf-positive old-length maximum-managed-float-array-buffer-size))
           (new-full-buffers
             (floorf-positive new-length maximum-managed-float-array-buffer-size))
           (new-remainder
             (modf-positive new-length maximum-managed-float-array-buffer-size))
           (old-total-buffers
             (if (>f old-remainder 0)
                 (+f old-full-buffers 1)
                 old-full-buffers))
           (new-total-buffers
             (if (>f new-remainder 0)
                 (+f new-full-buffers 1)
                 new-full-buffers)))
      (cond
        ((=f new-total-buffers old-total-buffers)
         (adjust-final-buffer-of-managed-float-array
           managed-float-array dont-copy new-total-buffers
           (if (=f old-remainder 0)
               maximum-managed-float-array-buffer-size
               old-remainder)
           (if (=f new-remainder 0)
               maximum-managed-float-array-buffer-size
               new-remainder))
         (setf (managed-float-array-length managed-float-array) new-length)
         managed-float-array)
        ((>f new-total-buffers old-total-buffers)
         (grow-managed-float-array
           managed-float-array dont-copy
           old-full-buffers old-remainder old-total-buffers
           new-length new-full-buffers new-remainder new-total-buffers))
        (t
         (shrink-managed-float-array
           managed-float-array dont-copy
           old-total-buffers
           new-length new-full-buffers new-remainder new-total-buffers))))))



;;; The function adjust-final-buffer-of-managed-float-array is called when the
;;; size of an existing buffer within the managed float array changes.  This
;;; function attempts to continue using the old buffer in that location, but if
;;; the buffer vector must be replaced, this function will do that.  If the
;;; buffer is replaced and dont-copy is nil, then the elements shared by the old
;;; and new buffers are copied into the new buffer.  This is an internal
;;; function to adjust-managed-float-array.

(defun adjust-final-buffer-of-managed-float-array
       (managed-float-array dont-copy total-buffers
        old-final-buffer-size new-final-buffer-size)
  (declare (eliminate-for-gsi))
  (let* ((old-buffer (managed-float-array-buffer
                       managed-float-array (-f total-buffers 1)))
         (old-actual-buffer-length (length old-buffer))
         (new-actual-buffer-length
           (buffer-size-for-partial-buffer
             new-final-buffer-size
             managed-array-allocation-schemes)))
    (when (/=f new-actual-buffer-length old-actual-buffer-length)
      (let ((new-buffer (allocate-managed-simple-float-array
                          new-actual-buffer-length)))
        (unless dont-copy
          (copy-simple-float-array-portion-function
            old-buffer 0
            (minf new-final-buffer-size old-final-buffer-size)
            new-buffer 0))
        (setf (managed-float-array-buffer
                managed-float-array (-f total-buffers 1))
              new-buffer)
        (reclaim-managed-simple-float-array old-buffer)))))




;;; The function grow-managed-float-array is called when a managed float array
;;; is adjusted so that it now will contain additional buffers.  This function
;;; first adjusts the last buffer of the old array to be maximum size, replaces
;;; the spine array if necessary, resets the managed-float-array-length,
;;; allocates as many new full buffers as are necessary, and then allocates any
;;; partially filled buffer required.  This is an internal function to
;;; adjust-managed-float-array.

(defun grow-managed-float-array
       (managed-float-array dont-copy
        old-full-buffers old-remainder old-total-buffers
        new-length new-full-buffers new-remainder new-total-buffers)
  (declare (eliminate-for-gsi))
  (when (/=f old-full-buffers old-total-buffers)
    (adjust-final-buffer-of-managed-float-array
      managed-float-array dont-copy old-total-buffers
      old-remainder maximum-managed-float-array-buffer-size))
  (let ((new-spine-length
          (buffer-size-for-partial-buffer
            (+f new-total-buffers 2)
            managed-array-allocation-schemes)))
    (when (/=f (length managed-float-array) new-spine-length)
      (let ((new-spine (allocate-managed-simple-vector-for-float-array new-spine-length)))
        (copy-simple-vector-portion-function
          managed-float-array 2 old-total-buffers new-spine 2)
        (setf (managed-float-array-identity-marker managed-float-array) nil)
        (reclaim-managed-simple-vector-for-float-array managed-float-array)
        (setf (managed-float-array-identity-marker new-spine)
              managed-float-array-unique-marker)
        (setq managed-float-array new-spine)))
    (setf (managed-float-array-length managed-float-array) new-length)
    (loop for spine-index from old-total-buffers below new-full-buffers
          do
      (setf (managed-float-array-buffer managed-float-array spine-index)
            (allocate-managed-simple-float-array
              maximum-managed-float-array-buffer-size)))
    (when (/=f new-full-buffers new-total-buffers)
      (setf (managed-float-array-buffer
              managed-float-array (-f new-total-buffers 1))
            (allocate-managed-simple-float-array
              (buffer-size-for-partial-buffer
                new-remainder
                managed-array-allocation-schemes))))
    managed-float-array))




;;; The function shrink-managed-float-array is called when a managed float array
;;; is adjusted such that it requires fewer total buffers.  First this function
;;; reclaims any buffers which are being discarded.  If the final buffer of the
;;; newly sized array does not need to be full sized, it is adjusted to its new
;;; partial size.  If the buffer count has decreased enough that a smaller spine
;;; array is needed, the old spine is replaced.  Finally, the managed-float-
;;; array-length is reset to the new length.

(defun shrink-managed-float-array
       (managed-float-array dont-copy old-total-buffers
        new-length new-full-buffers new-remainder new-total-buffers)
  (declare (eliminate-for-gsi))
  (loop for buffer-index from new-total-buffers below old-total-buffers
        for buffer = (managed-float-array-buffer
                       managed-float-array buffer-index)
        do
    (reclaim-managed-simple-float-array buffer))
  (when (/=f new-full-buffers new-total-buffers)
    (adjust-final-buffer-of-managed-float-array
      managed-float-array dont-copy new-total-buffers
      maximum-managed-float-array-buffer-size new-remainder))
  (let ((new-spine-length
          (buffer-size-for-partial-buffer
            (+f new-total-buffers 2)
            managed-array-allocation-schemes)))
    (when (/=f new-spine-length (length managed-float-array))
      (let ((new-spine (allocate-managed-simple-vector-for-float-array new-spine-length)))
        (copy-simple-vector-portion
          managed-float-array 2 new-total-buffers new-spine 2)
        (setf (managed-float-array-identity-marker managed-float-array) nil)
        (reclaim-managed-simple-vector-for-float-array managed-float-array)
        (setf (managed-float-array-identity-marker new-spine)
              managed-float-array-unique-marker)
        (setq managed-float-array new-spine))))
  (setf (managed-float-array-length managed-float-array) new-length)
  managed-float-array)




;;; The function `copy-from-simple-vector-into-managed-float-array' takes a
;;; simple-vector, an index into the simple vector, a count of the elements to
;;; copy, a managed float array, and an index into the managed float array at
;;; which to begin the copy.  Note that this function does not perform bounds
;;; checks on either the simple vector or the managed float array, and so it
;;; must be handed valid copying instructions.

(defun copy-from-simple-float-array-into-managed-float-array
       (simple-float-array vector-index count managed-float-array array-index)
  (declare (type fixnum vector-index count array-index)
           (type (simple-array gensym-float (*)) simple-float-array)
           (type simple-vector managed-float-array)
           (eliminate-for-gsi))
  #+development
  (when (or (>f (+f vector-index count) (length simple-float-array))
            (>f (+f array-index count)
                (managed-float-array-length managed-float-array)))
    (error
      "Copy-from-simple-float-array-into-managed-float-array out of bounds."))
  (multiple-value-bind (managed-buffer-number buffer-index)
      (floorf array-index maximum-managed-float-array-buffer-size)
    (declare (type fixnum managed-buffer-number buffer-index))
    (loop while (>f count 0)
          for elements-to-copy fixnum
              = (minf (-f maximum-managed-float-array-buffer-size buffer-index)
                      count)
          do
      (copy-simple-float-array-portion-function
        simple-float-array vector-index elements-to-copy
        (managed-float-array-buffer managed-float-array managed-buffer-number)
        buffer-index)
      (decff count elements-to-copy)
      (incff vector-index elements-to-copy)
      (incff managed-buffer-number)
      (setq buffer-index 0))))




;;; The function `copy-from-managed-float-array-into-simple-float-array' takes a
;;; managed float array, an index into the managed float array, a count of the
;;; elements to copy, a simple float array, and an index into the simple float
;;; array at which to begin the copy.  Note that this function does not perform
;;; bounds checks on either the of the arrays, and so it must be handed valid
;;; copying instructions.

(defun copy-from-managed-float-array-into-simple-float-array
       (managed-float-array array-index count simple-float-array vector-index)
  (declare (type fixnum array-index count vector-index)
           (type simple-vector managed-float-array)
           (type (simple-array gensym-float (*)) simple-float-array)
           (eliminate-for-gsi))
  #+development
  (when (or (>f (+f array-index count)
                (managed-float-array-length managed-float-array))
            (>f (+f vector-index count) (length simple-float-array)))
    (error
      "Copy-from-managed-float-array-into-simple-float-array out of bounds."))
  (multiple-value-bind (managed-buffer-number buffer-index)
      (floorf array-index maximum-managed-float-array-buffer-size)
    (declare (type fixnum managed-buffer-number buffer-index))
    (loop while (>f count 0)
          for elements-to-copy fixnum
              = (minf (-f maximum-managed-float-array-buffer-size buffer-index)
                      count)
          do
      (copy-simple-float-array-portion-function
        (managed-float-array-buffer managed-float-array managed-buffer-number)
        buffer-index elements-to-copy
        simple-float-array vector-index)
      (decff count elements-to-copy)
      (incff vector-index elements-to-copy)
      (incff managed-buffer-number)
      (setq buffer-index 0))))




;;; The function `copy-managed-float-array-portion' takes a source managed float
;;; array, a start point, an element count, a destination managed float array,
;;; and a destination point.  The function will copy those elements of the
;;; source managed float array starting at start point and copy element count
;;; elements into the destination array, starting at the destination point.
;;; This function is more efficient than performing the iteration yourself using
;;; managed-float-aref, because of the utilization of implementation specific
;;; optimizations and the internals of managed float arrays.

;;; At the top level this function works by organizing copy operations out of
;;; the source array.  These copies out of source arrays will turn a copy into
;;; either one or two of the destination array's buffers.

(defun copy-managed-float-array-portion
       (source-array source-index element-count
        destination-array destination-index)
  (declare (type fixnum source-index element-count destination-index)
           (type simple-vector source-array destination-array)
           (eliminate-for-gsi))
  #+development
  (when (or (>f (+f source-index element-count)
                (managed-float-array-length source-array))
            (>f (+f destination-index element-count)
                (managed-float-array-length destination-array)))
    (error "Copy-managed-float-array-portion referencing more elements than ~
            the arrays have."))
  (when (>f element-count 0)
    (multiple-value-bind (source-buffer-number source-buffer-index)
        (floorf source-index maximum-managed-float-array-buffer-size)
      (declare (type fixnum source-buffer-number source-buffer-index))
      (loop while (>f element-count 0)
            for elements-to-copy fixnum
                = (minf (-f maximum-managed-float-array-buffer-size
                            source-buffer-index)
                        element-count)
                then (minf maximum-managed-float-array-buffer-size
                           element-count)
            do
        (copy-from-simple-float-array-into-managed-float-array
          (managed-float-array-buffer source-array source-buffer-number)
          source-buffer-index elements-to-copy
          destination-array destination-index)
        (decff element-count elements-to-copy)
        (incff destination-index elements-to-copy)
        (incff source-buffer-number)
        (setq source-buffer-index 0)))))




;;; The function `fill-managed-float-array' takes a managed float array and some
;;; gensym-float, and will set all elements of the array to the given value.

(defun fill-managed-float-array (managed-float-array gensym-float)
  (declare (type simple-vector managed-float-array))
  (let* ((length (managed-float-array-length managed-float-array))
         (cached-float gensym-float))
    (declare (type fixnum length)
             (type gensym-float cached-float))
    (multiple-value-bind (full-buffers partial-buffer)
        (floorf length maximum-managed-float-array-buffer-size)
      (declare (type fixnum full-buffers partial-buffer))
      (loop for buffer-index from 0 below full-buffers
            for full-buffer = (managed-float-array-buffer
                                managed-float-array buffer-index)
            do
        (loop for index from 0 below maximum-managed-float-array-buffer-size
              do
          (mutate-float-vector full-buffer index cached-float)))
      (when (/=f partial-buffer 0)
        (loop with last-buffer = (managed-float-array-buffer
                                   managed-float-array full-buffers)
              for index from 0 below partial-buffer
              do
          (mutate-float-vector last-buffer index cached-float)))
      managed-float-array)))




;;; The function `rotate-managed-float-array' performs rotations of the values
;;; inside a managed float array, such that the value in a given index is moved
;;; to index 0, and all other values are rotated such that they are in the same
;;; relative position in terms of the new value in zero.  This operation is
;;; provided so that managed float arrays being used as ring buffers can
;;; efficiently move the date line back to element zero before adding new
;;; elements onto the end of the array.

(defun rotate-managed-float-array (managed-float-array index-to-rotate)
  (declare (eliminate-for-gsi))
  (when (/=f index-to-rotate 0)
    (let* ((length (managed-float-array-length managed-float-array))
           (new-array (allocate-managed-float-array length))
           (high-shift-size (-f length index-to-rotate)))
      (declare (type fixnum length high-shift-size))
      (copy-managed-float-array-portion
        managed-float-array index-to-rotate high-shift-size
        new-array 0)
      (copy-managed-float-array-portion
        managed-float-array 0 index-to-rotate
        new-array high-shift-size)
      (loop for buffer-index
                from 0
                below (ceilingf-positive
                        length maximum-managed-float-array-buffer-size)
            for buffer = (managed-float-array-buffer
                           managed-float-array buffer-index)
            do
        (reclaim-managed-simple-float-array buffer)
        (setf (managed-float-array-buffer managed-float-array buffer-index)
              (managed-float-array-buffer new-array buffer-index)))
      (reclaim-managed-simple-vector new-array)
      managed-float-array)))




;;; The function `copy-managed-float-array' takes a managed float array and
;;; returns a copy of that array, will all elements copied.  Note that this
;;; function handles its own temporary float context wrapping and so need not be
;;; called from a temporary gensym float context.

(defun copy-managed-float-array (managed-float-array)
  (declare (eliminate-for-gsi))
  (let* ((length (managed-float-array-length managed-float-array))
         (new-array (allocate-managed-float-array length)))
    (copy-managed-float-array-portion
      managed-float-array 0 length new-array 0)
    new-array))




;;; The function `print-managed-float-array' takes a managed float array and
;;; prints out its contents.  This is a development only function.

#+development
(defun print-managed-float-array (managed-float-array)
  (loop with length = (managed-float-array-length managed-float-array)
        with buffer-count
          = (ceiling length maximum-managed-float-array-buffer-size)
        for index from 0 below length
        initially
          (format t "~%~a is ~a elements long, ~a buffers."
                  managed-float-array length buffer-count)
        do
    (format t "~%~2d : ~s"
            index (managed-float-aref managed-float-array index))))






;;;; Floating Point Number Management Macros and Functions




;;; Managed-floats have been redefined for Version 3.0.  Previously we did not
;;; have a true predicate which could be used to distinguish between
;;; managed-floats and data structures.  There was also a large memory overhead
;;; in Ibuki [no longer a platform] per float.  Both of these limitations have
;;; been fixed in the new implementation, allowing us to finally control number
;;; consing in the parser and in saved knowledge base structures.  Facilities in
;;; G2 using the `obsolete permanent float' facilities should convert over to
;;; the new managed-floats.  Note that managed-number-or-values use these
;;; managed-floats for floating point numbers as well.

(def-concept managed-float)

;;; The functions which users of this facility should be interested in are:
;;; allocate-managed-float, managed-float-p, reclaim-managed-float,
;;; managed-float-value, and cached-managed-float-value.

;;; Other functions are available for managed-values, see the doc below (until I
;;; can describe them better here -jra 2/14/91).

;;; Note that some of the managed-float allocation functions defined below are
;;; being declared as side-effect free functions.  This is valid under a special
;;; case of the definition of side-effect free as long as the memory metering
;;; functions are not themselves declared side-effect free.  See the
;;; documentation for declare-side-effect-free-function for a further
;;; description of this special case.  -jra 3/26/91


;;; The macro `number-needing-boxing-p' returns non-nil if the passed number
;;; needs to be managed.  This is true for gensym-float and gensym-long.

(defmacro number-needing-boxing-p (number)
  `(or (gensym-float-p ,number)
       (gensym-long-p ,number)))




;;; The global variable `managed-float-unique-marker' contains a value used to
;;; uniquely mark the CDRs of conses representing managed-floats.

;; Moved to UTILITIES0 to help in development error checking.  -jra 3/25/91

;; Leaving it in UTILITIES0 for now to avoid rewriting the error checking in
;; defconser.  -jra 8/31/94




;;; The substitution-macro `managed-float-p' takes any thing and returns whether
;;; or not it is a managed-float.

(def-substitution-macro managed-float-p (thing)
  (and (float-vector-p thing)
       (=f (float-vector-length thing) 1)))

(defun managed-float-p-function (thing)
  (managed-float-p thing))



;;; The macro `managed-float-value' takes a managed-float and returns the value
;;; of the gensym-float stored within it.

(defmacro managed-float-value (managed-float)
  `(float-vector-aref ,managed-float 0))

;;; The function `managed-float-value-function' is a functionized version of
;;; managed-float-value.

(defun managed-float-value-function (managed-float)
  (managed-float-value managed-float))


#+development
(def-development-printer print-managed-float (thing stream)
  (declare (special write-floats-accurately-p))
  (when (managed-float-p thing)
    (printing-random-object (thing stream)
      (if write-floats-accurately-p
          (format stream "Managed-Float ~f" (managed-float-value thing))
          (format stream "Managed-Float ~,3f" (managed-float-value thing))))
    thing))



;;; The preferred interface to modifying managed-floats is the macro
;;; `mutate-managed-float-value'.  It modifies the value of the managed-float,
;;; and always returns NIL.  In cases where the expression to compute the new
;;; float is directly in line as the argument to this function, the best
;;; optimizations of this arithmatic can be made.

(defmacro mutate-managed-float-value (managed-float gensym-float)
  `(mutate-float-vector ,managed-float 0 ,gensym-float))

;;; The macro `cached-managed-float-value' takes a managed-float and returns the
;;; value, possibly as a cached value sharing storage with the managed-float.
;;; Mutations to the managed-float may affect the value of the result of this
;;; operation.

;; Note that this operation is obsolete, and all of the "cached" fetchers for
;; managed values should be eliminated.  -jra 8/31/94

(defmacro cached-managed-float-value (managed-float)
  `(managed-float-value ,managed-float))

;;; The function `allocate-managed-float-box' takes no arguments and returns the
;;; next available managed float.  If none are available, it allocates new ones
;;; and returns one of them.  Note that the value within the box is not modified
;;; and retains whatever value it had on reclamation into the pool.

(declare-side-effect-free-function allocate-managed-float-box)

(defvar bytes-per-double-float-simple-array-cached (bytes-per-double-float-simple-array 1))

(defmacro allocate-managed-float-box-macro ()
  `(let* ((amf-available-array-cons? (svref vector-of-simple-float-array-pools 1))
          (amf-result
            (cond (amf-available-array-cons?
                   (let ((amf-array (car-of-cons amf-available-array-cons?)))
                     #+development
                     (unless (reclaimed-managed-float-array-p amf-array)
                       (error "Corruption of float array pool"))
                     (setf (svref vector-of-simple-float-array-pools 1)
                           (cdr-of-cons amf-available-array-cons?))
                     (reclaim-float-array-cons-macro amf-available-array-cons?)
                     amf-array))
                  (t
                   (atomic-incff created-simple-float-array-pool-arrays)
                   (atomic-incff simple-float-array-pool-memory-usage
                                 (bytes-per-double-float-simple-array 1))
                   (generate-float-vector 1)))))
     amf-result))

(defun-simple allocate-managed-float-box ()
  (allocate-managed-float-box-macro))

;;; The macro `allocate-managed-float' takes a gensym-float and returns the next
;;; available managed-float with the given gensym-value stored as its value.  If
;;; none are available, it makes more, modifies the new one and returns it.

(defmacro allocate-managed-float (gensym-float)
  (let ((new-float (make-symbol "NEW-FLOAT")))
    `(let ((,new-float (allocate-managed-float-box-macro)))
       (mutate-managed-float-value ,new-float ,gensym-float)
       ,new-float)))




;;; The macro `copy-managed-float' takes a managed-float and returns a newly
;;; allocated managed value which contains the same floating point value as the
;;; argument.

(declare-side-effect-free-function copy-managed-float)

(defun-simple copy-managed-float (managed-float)
  (let ((new-float (allocate-managed-float-box-macro)))
    (mutate-managed-float-value new-float (managed-float-value managed-float))
    new-float))

;;; The macro `reclaim-managed-float' returns a managed-float the pool for
;;; recycling.

(def-substitution-macro reclaim-managed-float (managed-float)
  #+development
  (when (not (managed-float-p managed-float))
    (managed-float-reclaim-error managed-float))
  (reclaim-managed-simple-float-array-of-length-1 managed-float)
  nil)

#+development
(defun managed-float-reclaim-error (non-managed-float)
  (error "Attempted to reclaim ~a as a managed-float." non-managed-float))

(defun-void reclaim-if-managed-float (maybe-managed-float)
  (when (managed-float-p maybe-managed-float)
    (reclaim-managed-float maybe-managed-float)))

;;;; GENSYMCID-1365: GSI example TYPETEST failed (int64)
;;;;
;;;; by Chun Tian (binghe) <tian.chun@gensym.com>

;;; Part I: Long-Vectors

(defun-simple generate-long-vector (length)
  (let ((vector
	 (with-permanent-array-creation
	   (make-array length
		       :element-type (gensym-long-type)
		       :initial-element 0))))
    vector))

(defmacro long-vector-aref (long-vector index)
  `(the ,(gensym-long-type)
	(aref (the (simple-array ,(gensym-long-type) (*)) ,long-vector)
	      (the fixnum ,index))))

(defmacro long-vector-aset (long-vector index long)
  `(setf (aref (the (simple-array ,(gensym-long-type) (*)) ,long-vector)
	       (the fixnum ,index))
	 (the ,(gensym-long-type) ,long)))

(defsetf long-vector-aref long-vector-aset)

(defmacro mutate-long-vector (long-vector index gensym-long)
  `(progn
     (setf (long-vector-aref ,long-vector ,index) ,gensym-long)
     nil))

(defmacro long-vector-length (long-vector)
  `(the fixnum (length (the (simple-array ,(gensym-long-type) (*))
			    ,long-vector))))

;;; Part II: Simple Long Array Pool

(defconstant maximum-managed-simple-long-array-size 1024)

(defconser long-array)

(def-system-variable vector-of-simple-long-array-pools utilities0
  (:funcall allocate-initial-vector-of-simple-float-array-pools)
  nil t)

(def-system-variable created-simple-long-array-pool-arrays utilities0
  0
  nil t)

(defun outstanding-simple-long-array-pool-arrays ()
  (loop with vectors-in-pools fixnum = 0
	for index from 1 to maximum-managed-simple-long-array-size
	do
    (incff vectors-in-pools
	   (length (svref vector-of-simple-long-array-pools index)))
	finally (return (-f created-simple-long-array-pool-arrays
			    vectors-in-pools))))

(def-system-variable simple-long-array-pool-memory-usage utilities0
  0
  nil t)

(defun simple-long-array-pool-memory-usage ()
  simple-long-array-pool-memory-usage)

(def-system-object-pool managed-simple-long-arrays
    (simple-array gensym-long)
  created-simple-float-array-pool-arrays
  nil outstanding-simple-long-array-pool-arrays
  simple-long-array-pool-memory-usage)

(eval-when (:compile-toplevel :load-toplevel :execute)
  (defparameter replenished-simple-long-array-size-limit 10)
  (defparameter replenished-simple-long-arrays-to-make-at-a-time 10))

(def-substitution-macro managed-simple-long-array-p (thing)
  (long-vector-p thing))

(defun-simple allocate-managed-simple-long-array-of-length-1 ()
  (let* ((available-array-cons? (svref vector-of-simple-long-array-pools 1))
	 (result
	   (cond (available-array-cons?
		  (let ((array (car-of-cons available-array-cons?)))
		    (setf (svref vector-of-simple-long-array-pools 1)
			  (cdr-of-cons available-array-cons?))
		    (reclaim-long-array-cons-macro available-array-cons?)
		    array))
		 (t
		  (loop with new-vector-list
			  = (make-long-array-list
			      #.(-f replenished-simple-vectors-to-make-at-a-time 1))
			for new-vector-cons on new-vector-list
			do
		    (setf (car new-vector-cons) (generate-long-vector 1))
			finally
			  (setf (svref vector-of-simple-long-array-pools 1)
				new-vector-list))
		  (atomic-incff created-simple-long-array-pool-arrays
		    #.replenished-simple-long-arrays-to-make-at-a-time)
		  (atomic-incff simple-long-array-pool-memory-usage
		    (*f #.replenished-simple-long-arrays-to-make-at-a-time
			(bytes-per-long-simple-array 1)))
		  (generate-long-vector 1)))))
    (note-allocate-cons result 'managed-simple-long-array)
    result))

(defun-simple reclaim-managed-simple-long-array-of-length-1
    (managed-simple-long-array)
  (note-reclaim-cons managed-simple-long-array 'managed-simple-long-array)
  (setf (svref vector-of-simple-long-array-pools 1)
	(long-array-cons-macro
	  managed-simple-long-array
	  (svref vector-of-simple-long-array-pools 1)))
  nil)

;;; Part III: Managed Long

(def-concept managed-long)

(def-substitution-macro managed-long-p (thing)
  (and (long-vector-p thing)
       (=f (long-vector-length thing) 1)))

(defun managed-long-p-function (thing)
  (managed-long-p thing))

(defmacro managed-long-value (managed-long)
  `(long-vector-aref ,managed-long 0))

(defun managed-long-value-function (managed-long)
  (managed-long-value managed-long))

#+development
(def-development-printer print-managed-long (thing stream)
  (when (managed-long-p thing)
    (printing-random-object (thing stream)
      (format stream "Managed-Long ~D" (managed-long-value thing)))
    thing))

(defmacro mutate-managed-long-value (managed-long gensym-long)
  `(mutate-long-vector ,managed-long 0 ,gensym-long))

(defmacro cached-managed-long-value (managed-long)
  `(managed-long-value ,managed-long))

(declare-side-effect-free-function allocate-managed-long-box)

(defvar bytes-per-long-simple-array-cached
  (bytes-per-long-simple-array 1))

(defmacro allocate-managed-long-box-macro ()
  `(let* ((amf-available-array-cons? (svref vector-of-simple-long-array-pools 1))
	  (amf-result
	    (cond (amf-available-array-cons?
		   (let ((amf-array (car-of-cons amf-available-array-cons?)))
		     (setf (svref vector-of-simple-long-array-pools 1)
			   (cdr-of-cons amf-available-array-cons?))
		     (reclaim-long-array-cons-macro amf-available-array-cons?)
		     amf-array))
		  (t
		   (atomic-incff created-simple-long-array-pool-arrays)
		   (atomic-incff simple-long-array-pool-memory-usage
				 bytes-per-long-simple-array-cached)
		   (generate-long-vector 1)))))
     amf-result))

(defun-simple allocate-managed-long-box ()
  (allocate-managed-long-box-macro))

(defmacro allocate-managed-long (gensym-long)
  (let ((new-long (make-symbol "NEW-LONG")))
    `(let ((,new-long (allocate-managed-long-box)))
       (mutate-managed-long-value ,new-long ,gensym-long)
       ,new-long)))

(defun-simple allocate-managed-long-function (gensym-long)
  (allocate-managed-long gensym-long))

(declare-side-effect-free-function copy-managed-long)

(defun-simple copy-managed-long (managed-long)
  (let ((new-long (allocate-managed-long-box-macro)))
    (mutate-managed-long-value new-long (managed-long-value managed-long))
    new-long))

(def-substitution-macro reclaim-managed-long (managed-long)
  #+development
  (when (not (managed-long-p managed-long))
    (managed-long-reclaim-error managed-long))
  (reclaim-managed-simple-long-array-of-length-1 managed-long)
  nil)

#+development
(defun managed-long-reclaim-error (non-managed-long)
  (error "Attempted to reclaim ~a as a managed-long." non-managed-long))

(defun-void reclaim-if-managed-long (maybe-managed-long)
  (when (managed-long-p maybe-managed-long)
    (reclaim-managed-long maybe-managed-long)))

;;; END of GENSYMCID-1365.



;;; The modifying macro `reclaim-managed-number' given a place, will check if
;;; that place holds a managed-float, and if so it will reclaim it.  Whatever
;;; was in there before, the place will be set to NIL.

(define-modify-macro reclaim-managed-number () reclaim-managed-number-1)

(def-substitution-macro reclaim-managed-number-1 (managed-float-or-number)
  (cond ((managed-float-p managed-float-or-number)
	 (reclaim-managed-float managed-float-or-number))
	((managed-long-p managed-float-or-number)
	 (reclaim-managed-long managed-float-or-number)))
  nil)




;;; The modifying macro `reclaim-managed-number-or-value' takes a place which
;;; has been stored into with store-managed-number-or-value, and it will reclaim
;;; any managed-number or text string stored in that place.  Whatever was in the
;;; place, this form will replace it with NIL.

(define-modify-macro reclaim-managed-number-or-value ()
  reclaim-managed-number-or-value-function)

(declare-function-type reclaim-managed-number-or-value-function (t) (t))

(defun-simple reclaim-managed-number-or-value-function (managed-number-or-value)
  (cond ((managed-float-p managed-number-or-value)
	 (reclaim-managed-float managed-number-or-value))
	((managed-long-p managed-number-or-value)
	 (reclaim-managed-long managed-number-or-value))
	((text-string-p managed-number-or-value)
	 (reclaim-text-string managed-number-or-value))
	((or (fixnump managed-number-or-value)
	     (symbolp managed-number-or-value))
	 ;; Do nothing
	 nil)
	(t
	 (reclaim-evaluation-value managed-number-or-value)))
  nil)

(defun-void reclaim-possible-managed-float (managed-float?)
  (when (managed-float-p managed-float?)
    (reclaim-managed-float managed-float?)))


;;; The modifying macro `store-managed-number' takes a place and number to put
;;; into that place.  This macro will put the given number into one of our
;;; managed number boxes if it is of a type that we manage, or else it will just
;;; store the number into that place.  If the place already held a managed
;;; number box it will be modified to hold the new number, or reclaimed if the
;;; new number is not a managed type.

(defmacro define-modify-macro-of-store-managed-number ()
  (if (eq current-system-being-loaded 'gsi)
      nil
      `(define-modify-macro store-managed-number (number)
                            store-managed-number-function)))

(define-modify-macro-of-store-managed-number)

(defun-simple store-managed-number-function (old-value new-number)
  (declare (eliminate-for-gsi))
  #+(and development lucid)
  (if (null (type-of new-number))
      (error "Corrupted object ~s being stored into a managed number."
             new-number))
  #+development
  (when (and (floatp new-number)
             (not (number-needing-boxing-p new-number)))
    (cerror "Coerce it"
            "Attempting to store a managed-number that is a float, but isn't a gensym-float.")
    (setf new-number (coerce-to-gensym-float new-number)))
  (cond ((number-needing-boxing-p new-number)
         (cond ((managed-float-p old-value)
                (setf (managed-float-value old-value) new-number)
                old-value)
	       ((managed-long-p old-value)
		(setf (managed-long-value old-value) new-number))
               ((gensym-float-p new-number)
                (allocate-managed-float new-number))
	       (t ; (gensym-long-p new-number)
		(allocate-managed-long new-number))))
        ((fixnump new-number)
         (when (managed-float-p old-value)
           (reclaim-managed-float old-value))
         new-number)
        ((managed-float-p new-number)
         ;; In version 3.0, the new-value argument could be a managed-float.
         (cond ((managed-float-p old-value)
		(reclaim-managed-float old-value))
	       ((managed-long-p old-value)
		(reclaim-managed-long old-value)))
         new-number)
        ((managed-long-p new-number)
         (cond ((managed-float-p old-value)
		(reclaim-managed-float old-value))
	       ((managed-long-p old-value)
		(reclaim-managed-long old-value)))
         new-number)

        ;; The following case should never happen, but our attempt to remove it
        ;; was incomplete and proved embarrassing.  See comment in header for
        ;; coerce-bignum-to-gensym-float.  - jv, 10/31/98
        ((typep new-number 'bignum)
         #+development
         (cerror "Coerce it to a float, as in distribution."
                 "Bignum ~a given to store-managed-number."
                 new-number)
         (cond ((managed-float-p old-value)
                (setf (managed-float-value old-value)
                      (coerce-bignum-to-gensym-float new-number))
                old-value)
               ((gensym-float-p old-value)
                (allocate-managed-float
                  (coerce-bignum-to-gensym-float new-number)))
	       ((managed-long-p old-value)
		(setf (managed-long-value old-value) new-number))
	       (t ; (gensym-long-p old-value)
		(allocate-managed-long new-number))))
        (t
         ;; Argument isn't a number!
         (error "Non-number ~a given to store-managed-number." new-number))))




;;; The macro `box-value-if-necessary' takes a value which is a cons, a symbol,
;;; a number, or a string and returns that value, boxed for permanent storage if
;;; the value was a float which needed to be boxed, or copied for permanent
;;; storage if it was a text string.  Any bignums passed in get coerced into
;;; floats and then boxed.

(defmacro box-value-if-necessary (value)
  (cond ((or (constantp value)
             (text-string-p value) ;  -- consider reordering tests -- previously tested stringp?! (MHD 2/6/96)
             (gensym-float-p value)
	     (gensym-long-p value)
             (fixnump value))
         (let ((new-value (eval value)))
           (cond ((number-needing-boxing-p new-value)
                  ;; Bignum code commented out because bignums are no longer
                  ;; supported (ghw 2/29/95).
                  ;; We're reinstating some bignum code, but since number-
                  ;; needing-boxing-p is going to return nil for a bignum,
                  ;; there's no point to reinstating this here.  Perhaps
                  ;; we should have another case in the cond for bignums.
                  ;; jv, 10/31/98
;                      (and (typep new-value 'bignum)
;                           (setq new-value
;                                 (coerce-bignum-to-gensym-float new-value))))
		  (cond ((gensym-float-p new-value)
			 `(allocate-managed-float ,new-value))
			(t ; (gensym-long-p new-value)
			 `(allocate-managed-long ,new-value))))
                 ((text-string-p new-value)
                  `(copy-text-string ,new-value))
                 (t
                  new-value))))
        ((not (symbolp value))
         (let ((new-value (gensym)))
           `(let ((,new-value ,value))
              (cond ((or (gensym-float-p ,new-value)
                         (and (typep ,new-value 'bignum)
                              (setq ,new-value
                                    (coerce-bignum-to-gensym-float ,new-value))))
                     (allocate-managed-float ,new-value))
		    ((gensym-long-p ,new-value)
		     (allocate-managed-long ,new-value))
                    ((text-string-p ,new-value)
                     (copy-text-string ,new-value))
                    (t
                     ,new-value)))))
        (t
         `(cond ((or (fixnump ,value) (symbolp ,value))
                 ,value)
                ((gensym-float-p ,value)
                 (allocate-managed-float ,value))
		((gensym-long-p ,value)
		 (allocate-managed-long ,value))
                ((text-string-p ,value)
                 (copy-text-string ,value))
                ((typep ,value 'bignum)
                 (allocate-managed-float
                   (coerce-bignum-to-gensym-float ,value)))
                (t ,value)))))




;;; The macro `copy-managed-number-or-value' takes a managed-number-or-value and
;;; returns a copy of that value.

(def-substitution-macro copy-managed-number-or-value (managed-number-or-value)
  (current-system-case
    (ab
      (if (or (fixnump managed-number-or-value)
              (symbolp managed-number-or-value))
          managed-number-or-value
          (copy-evaluation-value-1 managed-number-or-value)))
    (t
      (cond ((managed-float-p managed-number-or-value)
             (copy-managed-float managed-number-or-value))
	    ((managed-long-p managed-number-or-value)
	     (copy-managed-long managed-number-or-value))
            ((text-string-p managed-number-or-value)
             (copy-text-string managed-number-or-value))
            (t
             managed-number-or-value)))))


;;; The function `coerce-number-to-fixnum' takes any numerical value and returns a
;;; fixnum. The function should be used on only small values which can fit into a
;;; fixnum. Moved here from KB-SAVE4, with EVALUATION-*-P changed to MANAGED-*-P.
;;;
;;; -- Chun Tian (binghe), Sep 1, 2016.

(defun-simple coerce-number-to-fixnum (number)
  (cond ((managed-float-p number)
	 (round (managed-float-value number)))
	((gensym-float-p number)
	 (round number))
	((fixnump number)
	 number)
	((managed-long-p number)
	 (with-dynamic-creation
	   (let ((long-value (managed-long-value number)))
	     (coerce long-value 'fixnum))))
	((gensym-long-p number)
	 (with-dynamic-creation (coerce number 'fixnum)))
	(t
	 0)))


;;; The macro `convert-to-managed-value-and-reclaim' takes a datum and returns a
;;; managed value which encapsulates that value.  If the datum is of a type
;;; which needs to be reclaimed, it is reclaimed.  (Note that strings are
;;; currently the only type for which this is true.)

(def-substitution-macro convert-to-managed-value-and-reclaim (datum)
  (cond ((number-needing-boxing-p datum)
         (allocate-managed-float datum))
        ((typep datum 'bignum)
         (allocate-managed-float (coerce-bignum-to-gensym-float datum)))
        (t datum)))

(defun-simple convert-g2longint-to-double (gensym-long)
  (declare (type #.(gensym-long-type) gensym-long))
  (coerce-to-gensym-float gensym-long))

;;; `normalize-to-gensym-float' was a macro.

(defmacro normalize-to-gensym-float-macro (x)
  (let ((val (gensym))
	(long-value (make-symbol "LONG-VALUE")))
    `(let ((,val ,x))
       (cond ((fixnump ,val)
	      (coerce-fixnum-to-gensym-float ,val))
	     ((managed-float-p ,val)
	      (managed-float-value ,val))
	     ((gensym-float-p ,val)
	      ,val)
	     ((managed-long-p ,val)
	      (let ((,long-value (managed-long-value ,val)))
		(convert-g2longint-to-double ,long-value)))
	     ((gensym-long-p ,val)
	      (convert-g2longint-to-double ,val))
	     (t
	      (coerce ,val 'gensym-float))))))

(defun normalize-to-gensym-float (x)
  (normalize-to-gensym-float-macro x))

;;; The macro `extract-number' takes a managed number and returns a normal
;;; number suitable for use in temporary arithmetic.  This function should be
;;; used whenever accessing a number stored into a place using
;;; store-managed-number.

(def-substitution-macro extract-number (managed-number)
  (cond ((managed-float-p managed-number)
	 (managed-float-value managed-number))
	((managed-long-p managed-number)
	 (managed-long-value managed-number))
	(t
	 managed-number)))
 

;;; The macro `extract-cached-number' takes a managed number and returns a
;;; number for inspection.  Note that this number may be the object being used
;;; as the managed number box, and so should only be inspected and then dropped.
;;; This accessor is included for those cases where it is known that the number
;;; need not be used for value and so can be looked at without a copy operation.

(def-substitution-macro extract-cached-number (managed-number)
  (cond ((managed-float-p managed-number)
	 (cached-managed-float-value managed-number))
	((managed-long-p managed-number)
	 (cached-managed-long-value managed-number))
	(t
	 managed-number)))


;;; The macro `extract-number-or-value' is used to take a value (typically from
;;; a frame slot), and return a value for use.  If the thing is a managed
;;; number, it should return the unboxed number.  If it is a text string, it
;;; should return a copy of the string.  If it is anything else, it should just
;;; return it.

(def-substitution-macro extract-number-or-value (managed-number-or-value)
  (cond ((managed-float-p managed-number-or-value)
	 (managed-float-value managed-number-or-value))
	((managed-long-p managed-number-or-value)
	 (managed-long-value managed-number-or-value))
	((text-string-p managed-number-or-value)
	 (copy-text-string managed-number-or-value))
	(t
	 managed-number-or-value)))




;;; The macro `extract-cached-number-or-value' will unbox any and return a value
;;; for inspection from a place that has been stored into using
;;; store-managed-number-or-value.  Unlike extract-number-or-value, this macro
;;; will make every attempt to not copy the object stored in the place, so the
;;; user need not worry about reclaiming a copied text string.  This macro is to
;;; be used in situations where the value returned is going to be inspected and
;;; then immediately dropped.

;;; As well as being more efficient in terms of managed objects, this macro also
;;; has to call fewer predicates on the managed number or value before
;;; dispatching to the appropriate code.

(def-substitution-macro extract-cached-number-or-value (managed-number-or-value)
  (cond ((managed-float-p managed-number-or-value)
	 (cached-managed-float-value managed-number-or-value))
	((managed-long-p managed-number-or-value)
	 (cached-managed-long-value managed-number-or-value))
	(t
	 managed-number-or-value)))




;;; The modifying macro `store-managed-number-or-value' is used to store a
;;; managed number, a symbol, a cons, or a text string into a place.  If the
;;; value is a number needing managing, it will be boxed and placed into the
;;; given spot.  If the value is a bignum, it will be coerced into a short
;;; float, boxed, and stored.  If it is a text string, it will be copied, and
;;; the value placed into the place.  If it is anything else, the passed value
;;; will be stored.  It will reclaim a managed number box or text string from
;;; the place if necessary.  This macro is somewhat optimized for the case where
;;; the thing stored is a managed number box and the value coming in is a number
;;; needing boxing.

(define-modify-macro store-managed-number-or-value (number-or-value)
  store-managed-number-or-value-function)

;(proclaim '(inline store-managed-number-or-value-function))

(declare-function-type store-managed-number-or-value-function (t t) (t))

(defun store-managed-number-or-value-function (old-value new-value)
  #+(and development lucid)
  (if (null (type-of new-value))
      (error "Corrupted object ~s being stored into a managed number box or value spot."
             new-value))
  ;; Check for floats in development systems with array based number boxes.
  #+(and development (or ti lucid))
  (when (gensym-float-p old-value)
    (error
      "Managed number spot contained a float, not a number box, memory Leak!"))
  (cond ((or (fixnump new-value) (symbolp new-value))
         (unless (or (fixnump old-value) (symbolp old-value))
           (cond ((managed-float-p old-value)
                  (reclaim-managed-float old-value))
                 ((text-string-p old-value)
                  (reclaim-text-string old-value))))
         new-value)
        ((managed-float-p new-value)
         (cond ((managed-float-p old-value)
                (setf (managed-float-value old-value)
                      (managed-float-value new-value))
                old-value)
               (t
                (when (text-string-p old-value)
                  (reclaim-text-string old-value))
                (copy-managed-float new-value))))
        ((gensym-float-p new-value)
         (cond ((managed-float-p old-value)
                (setf (managed-float-value old-value) new-value)
                old-value)
               (t
                (when (text-string-p old-value)
                  (reclaim-text-string old-value))
                (allocate-managed-float new-value))))
        ((text-string-p new-value)
         (when (text-string-p old-value)
           (reclaim-text-string old-value))
         (copy-text-string new-value))

        ((managed-long-p new-value)
         (cond ((managed-long-p old-value)
		(setf (managed-long-value old-value)
		      (managed-long-value new-value))
		old-value)
	       (t
		(when (text-string-p old-value)
                  (reclaim-text-string old-value))
		(copy-managed-long new-value))))

	((gensym-long-p new-value)
	 (cond ((managed-long-p old-value)
		(setf (managed-long-value old-value) new-value)
		old-value)
	       (t
		(when (text-string-p old-value)
                  (reclaim-text-string old-value))
		(allocate-managed-long new-value))))

        ;; The following case should never happen, but our attempt to remove it
        ;; was incomplete and proved embarrassing.  See comment in header for
        ;; coerce-bignum-to-gensym-float.  - jv, 10/31/98
        ((typep new-value 'bignum)
         #+development
         (cerror "Coerce it to a float, as in distribution."
                 "Bignum ~a given to store-managed-number-or-value."
                 new-value)
         (setq new-value (coerce-bignum-to-gensym-float new-value))
         (cond ((managed-float-p old-value)
                (setf (managed-float-value old-value) new-value)
                old-value)
               (t
                (when (text-string-p old-value)
                  (reclaim-text-string old-value))
                (allocate-managed-float new-value))))
        (t
         #+development
         (cerror "Return it, as in distribution."
                 "Unknown thing ~a given to store-managed-number-or-value."
                 new-value)
         new-value)))


;;; `coerce-bignum-to-gensym-float' - Tried to eliminate calls to this for
;;; 5.0r0.  Removed it from store-managed-number, which meant that if a bignum
;;; was passed to store-managed-number, G2 would abort.  We found that, in G2
;;; versions 5.0r0 - 5.1r0, the code which performs calculations on variable
;;; histories (in histories.lisp) can create bignums and give them to
;;; store-managed-number (easy by calculating standard deviation; other
;;; history operations can also create bignums).  We will fix that code
;;; not to generate bignums in the first place, but we still won't be
;;; guaranteed that there won't be other code that could abort G2, and
;;; the bignum predicate is only performed immediately before we're about
;;; to abort, so there's really very little harm in catching the bignum.
;;; If we're serious about getting rid of bignums, we should print a warning
;;; and backtrace whenever this function is called. -  jv, 10/31/98

(defun coerce-bignum-to-gensym-float (bignum)
  (declare (no-op-for-gsi))
  (cond ((< bignum most-negative-gensym-float)
         (warn-of-big-bignum t)
         -1.0)
        ((> bignum most-positive-gensym-float)
         (warn-of-big-bignum nil)
         1.0)
        (t
         (coerce-to-gensym-float bignum))))



;;; The macro `managed-number-p' can be called on arbitrary Lisp objects and
;;; returns whether or not the thing is a managed-number.  Managed numbers are
;;; either managed-floats or fixnums.  This predicate is used in place of
;;; numberp when the number may have been placed into a spot with
;;; store-managed-number-or-value.

(def-substitution-macro managed-number-p (thing)
  (or (fixnump thing)
      (managed-float-p thing)
      (managed-long-p thing)))






;;;; Partitioning and Reconstructing Floats


;; This code used to live in INT3B, because it was introduced specifically
;; to handle sending floats over ICP.  However, it has since come into
;; somewhat more general usage, and so I'm moving it here, closer to the
;; managed-float code.  -jv, 6/21/07

;; jh, 9/10/91.  Removed the with-unmoveable-object-creation wrapper from the
;; variable partition-float-union.  This wrapper is only necessary when we intend
;; to pass a pointer to a C asynchronous process and then resume Lisp processing,
;; thereby creating the risk that the pointer will be relocated by garbage
;; collection.  There is no such risk for partition-float-union, since it is never
;; passed to an asynchronous C process.

;;; The macro partition-float takes a float and returns four values, corresponding
;;; to the first, second, third, and fourth 16-bit section of the float being
;;; partitioned.  The ordering is the same on all platforms, so as not to cause
;;; problems for ICP and other users.


(def-gensym-c-function c-partition_float
                       (:fixnum-int "g2ext_foreign_partition_float")
  ((:double-float input-float)
   (:byte-vector-16 byte-array)))

(def-gensym-c-function c-partition_long
		       (:fixnum-int "g2ext_foreign_partition_long")
  ((:int64 input-long)
   (:byte-vector-16 byte-array)))

#+development
(progn
  (defvar check-for-exceptional-floats-p nil)

  (defun check-for-exceptional-float (float)
    (when (and check-for-exceptional-floats-p (exceptional-float-p float))
      ;;(format t "~&exceptional float encountered ~S~%" (make-lisp-backtrace))
      (cerror "Continue" "exceptional float encountered: ~S" float))
    float))

;; The variable partition-float-or-long-union divides the float into 4 16-bit bytes
;; suitable for icp transmission and for use in ML's new KB save algorithm.
;; jh, 2/11/91.

(defun-simple make-partition-float-or-long-union ()
  (make-static-array 4 :element-type '(unsigned-byte 16)))

(defvar partition-float-union (make-partition-float-or-long-union))
(defvar partition-long-union  (make-partition-float-or-long-union))

(defmacro partition-float (float &optional write-icp-byte-function)
  (let ((accessor 'byte-vector-16-aref))
    `(progn
       ;; Always returns 1  - rmh 2/21/96
       (c-partition_float ;SS_G2L removed due to the bad input type
         (#-development progn #+development check-for-exceptional-float ,float)
         partition-float-union)
       (let* ((b0 (,accessor partition-float-union 0))
              (b1 (,accessor partition-float-union 1))
              (b2 (,accessor partition-float-union 2))
              (b3 (,accessor partition-float-union 3)))
         ,(if write-icp-byte-function
              `(progn
                 (,write-icp-byte-function b0)
                 (,write-icp-byte-function b1)
                 (,write-icp-byte-function b2)
                 (,write-icp-byte-function b3))
              `(values b0 b1 b2 b3))))))

(defmacro partition-long (long &optional write-icp-byte-function)
  (let ((accessor 'byte-vector-16-aref))
    `(progn
       (c-partition_long ,long partition-long-union)
       (let* ((b0 (,accessor partition-long-union 0))
	      (b1 (,accessor partition-long-union 1))
	      (b2 (,accessor partition-long-union 2))
	      (b3 (,accessor partition-long-union 3)))
	 ,(if write-icp-byte-function
	      `(progn
		 (,write-icp-byte-function b0)
		 (,write-icp-byte-function b1)
		 (,write-icp-byte-function b2)
		 (,write-icp-byte-function b3))
	      `(values b0 b1 b2 b3))))))

(defun partition-managed-float (managed-float)
  (partition-float (managed-float-value managed-float)))

;;; The macro reconstruct-float takes as argument the first, second, third, and
;;; fourth bytes which make up a double float.  This function returns a new float,
;;; and so must always be called inside a managed context.  Note that
;;; reconstruct-float adheres to Lisp's left-to-right evaluation order, so using
;;; temporary variables to assure this order is unnecessary and inefficient.

(def-gensym-c-function c-reconstruct_float
                       (:double-float "g2ext_foreign_reconstruct_float")
  ((:fixnum-int byte0)
   (:fixnum-int byte1)
   (:fixnum-int byte2)
   (:fixnum-int byte3)))

(def-gensym-c-function c-reconstruct_long
		       (:int64 "g2ext_foreign_reconstruct_long")
  ((:fixnum-int byte0)
   (:fixnum-int byte1)
   (:fixnum-int byte2)
   (:fixnum-int byte3)))

;; Future developers NB: The macro reconstruct-float guarantees to adhere to
;; Common Lisp left-to-right order of argument evaluation.

;; jh, 11/17/92.  Note that the translator undertakes to temp properly in the
;; function call c-reconstruct-float, as long as the left-to-right switch is on
;; and it lacks any declaration to the contrary.

(defmacro reconstruct-float (byte0 byte1 byte2 byte3)
  `(#-development progn #+development check-for-exceptional-float
     (let* ((b0 ,byte0) (b1 ,byte1) (b2 ,byte2) (b3 ,byte3))
       (c-reconstruct_float
         b0 b1 b2 b3))))

(defmacro reconstruct-long (byte0 byte1 byte2 byte3)
  `(let* ((b0 ,byte0) (b1 ,byte1) (b2 ,byte2) (b3 ,byte3))
     (c-reconstruct_long
       b0 b1 b2 b3)))

(defun-simple reconstruct-managed-float (byte0 byte1 byte2 byte3)
  (allocate-managed-float
    (reconstruct-float byte0 byte1 byte2 byte3)))




;;;; Exceptional Floats

;;; An `exceptional float' is a floating-point representation of a special
;;; number, usually the result of an undefined arithmetic operation.
;;; Exceptional floats include positive infinity (obtained by 1.0 / 0.0),
;;; negative infinity (obtained by -1.0 / 0.0), and not-a-number (obtained by
;;; 0.0 / 0.0, sqrt(-1.0), and so on).

;;; In the IEEE standard, an exceptional float is one which has 1s in each of
;;; its 11 exponent bits.  Infinity is represented by 0s in all 52 fractional
;;; bits.  The sign bit has its usual meaning, so we can distinguish between
;;; positive and negative infinity.  NaN (not-a-number) is any other
;;; exceptional float.  Note that there are 2 ^ 53 possible NaNs.  This leaves
;;; room for a very fine-grained numeric error reporting system.

;; jh, 5/22/92.  Added predicates to detect exceptional floats.

;; By a fortunate coincidence, mask-for-ieee-exponent is the mask for the
;; VMS g-float exponent field, too.

;; sign exponent    4 most sig fractional bits
;; 0    11111111111 0000

(defconstant mask-for-ieee-exponent 32752) ; = #b 0 111 1111 1111 0000



;;; Declaration:     positive-infinity-p (thing)
;;; Type:            Lisp function.
;;; Purpose:         Determine if an object is the exceptional float positive
;;;                  infinity.
;;; Arguments:       A Lisp object.
;;; Return behavior: non-nil if the object is positive infinity, nil otherwise.
;;; Users:           None.
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

(defun-simple positive-infinity-p (thing)
  (and (gensym-float-p thing)
       (if (eq g2-machine-type 'vms) ;i.e., VaxVMS (as opposed to Alpha VMS)
           nil ;stub for now (jh, 5/26/92)
           (multiple-value-bind (byte0 byte1 byte2 byte3)
               (let (#+development (check-for-exceptional-floats-p nil))
                 (partition-float thing))
             ;; sign exponent    4 most sig fractional bits
             ;; 0    11111111111 0000
             (and (=f byte0 mask-for-ieee-exponent)
                                   ; remaining fractional bits
                  (=f byte1 0)     ;0000000000000000
                  (=f byte2 0)     ;0000000000000000
                  (=f byte3 0)     ;0000000000000000
                  )))))



;;; Declaration:     negative-infinity-p (thing)
;;; Type:            Lisp function.
;;; Purpose:         Determine if an object is the exceptional float negative
;;;                  infinity.
;;; Arguments:       A Lisp object.
;;; Return behavior: non-nil if the object is negative infinity, nil otherwise.
;;; Users:           None.
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

(defun-simple negative-infinity-p (thing)
  (and (gensym-float-p thing)
       (if (eq g2-machine-type 'vms) ;i.e., VaxVMS (as opposed to Alpha VMS)
           nil ;stub for now (jh, 5/26/92)
           (multiple-value-bind (byte0 byte1 byte2 byte3)
               (let (#+development (check-for-exceptional-floats-p nil))
                 (partition-float thing))
                                   ;sign exponent    4 most sig fractional bits
             (and (=f byte0 65520) ;1    11111111111 0000
                                   ; remaining fractional bits
                  (=f byte1 0)     ;0000000000000000
                  (=f byte2 0)     ;0000000000000000
                  (=f byte3 0)     ;0000000000000000
                  )))))


;;; Declaration:     nanp (thing)
;;; Type:            Lisp function.
;;; Purpose:         Determine if an object is the exceptional float not-a-number.
;;; Arguments:       A Lisp object.
;;; Return behavior: non-nil if the object is not-a-number, nil otherwise.
;;; Users:           None.
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

(defun-simple nanp (thing)
  (and (gensym-float-p thing)
       (if (eq g2-machine-type 'vms) ;i.e., VaxVMS (as opposed to Alpha VMS)
           nil ;stub for now (jh, 5/26/92)
           (multiple-value-bind (byte0 byte1 byte2 byte3)
               (let (#+development (check-for-exceptional-floats-p nil))
                 (partition-float thing))
             (and
               ;; following form tests for all 1s in the 11-bit IEEE exponent field
               (=f (logandf byte0 mask-for-ieee-exponent) mask-for-ieee-exponent)
               ;; following form tests for at least one 1 in the 52-bit IEEE fraction
               (or (pluspf byte1)
                   (pluspf byte2)
                   (pluspf byte3)
                   ;; IEEE fraction includes 4 bits in byte0
                   (pluspf (logandf byte0 15))
               ))))))



;;; Declaration:     exceptional-float-p (thing)
;;; Type:            Lisp function.
;;; Purpose:         Determine if an object is an exceptional float.
;;; Arguments:       A Lisp object.
;;; Return behavior: non-nil if the object is an exceptional float, nil otherwise.
;;; Users:           G2 Charts (CHARTS1).
;;; Prerequisites:   None.
;;; Side effects:    None.
;;; Non-local exits: None.
;;; Memory impact:   None.

(defun-simple exceptional-float-p (thing)
  (and (gensym-float-p thing)
       (if (eq g2-machine-type 'vms) ;i.e., VaxVMS (as opposed to Alpha VMS)
           nil ;stub for now (jh, 5/26/92)
           (multiple-value-bind (byte0 byte1 byte2 byte3)
               (let (#+development (check-for-exceptional-floats-p nil))
                 (partition-float thing))
             (declare (ignore byte1 byte2 byte3))
             ;; following form tests for all 1s in the 11-bit IEEE exponent field
             (=f (logandf byte0 mask-for-ieee-exponent) mask-for-ieee-exponent)))))



;; The initialization of this variable calls into ext/c at load time. - jv

#+development
(defvar-of-special-global reclaimed-managed-float-array-value-holder
  (let ((check-for-exceptional-floats-p nil))
    (reconstruct-float mask-for-ieee-exponent #xde #xad 15)))

#+(and development allegro)
(defvar-of-special-global allegro-mask-for-ieee-exponent
  (partition-float reclaimed-managed-float-array-value-holder))

#+development
(defun-simple reclaimed-managed-float-array-p (managed-float-array)
  (multiple-value-bind (b0 b1 b2 b3)
      (partition-float (float-vector-aref managed-float-array 0))
    (and (=f b0 #+(and development allegro) allegro-mask-for-ieee-exponent
		#-(and development allegro) mask-for-ieee-exponent)
	 (=f b1 #xde)
	 (=f b2 #xad)
	 (=f b3 15))))

;;;; Filling Managed Float Arrays from Managed Floats




;;; The function `fill-managed-float-array-with-managed-float' takes a managed
;;; float array and a managed-float, and will set all elements of the array to
;;; the given value.  Note that this is more efficient than filling from a
;;; gensym-float.

(defun fill-managed-float-array-with-managed-float
       (managed-float-array managed-float)
  (declare (simple-vector managed-float-array))
  (let* ((length (managed-float-array-length managed-float-array))
         (full-buffers
           (floorf-positive length maximum-managed-float-array-buffer-size))
         (partial-buffer
           (modf-positive length maximum-managed-float-array-buffer-size))
         (float (managed-float-value managed-float)))
    (declare (type fixnum length full-buffers partial-buffer)
             (type gensym-float float))
    (loop for buffer-index from 0 below full-buffers
          for full-buffer = (managed-float-array-buffer
                              managed-float-array buffer-index)
          do
      (loop for index from 0 below maximum-managed-float-array-buffer-size
            do
        (mutate-float-vector full-buffer index float)))
    (when (/=f partial-buffer 0)
      (loop with last-buffer = (managed-float-array-buffer
                                 managed-float-array full-buffers)
            for index from 0 below partial-buffer
            do
        (mutate-float-vector last-buffer index float)))
    managed-float-array))


;;; In delivery, a managed bignum is just a bignum that is not in
;;; the temporary area. But the values of these can be changed by
;;; tx:store-bignum, and we can't do this in development. So
;;; A managed bignum is represented by a managed-development-bignum structure.

;;; Functions with bignum in their name are internals that should only
;;; be called on bignums. Functions with general-integer in their names
;;; can be called on any integers, and storing and allocating will be
;;; done as needed for bignums, while fixnums will work transparently.

;;; In development, numbers are stored
;;; as managed-developent-bignums whenever they are large enough to be
;;; bignums in delivery, regardless of the development value of
;;; most-positive-fixnum.

;;; fixnums are considered to have a length of 0.

;;; For more detail on the use of this facility, see the trail document
;;; 0304-using-bignums.txt

;;; Note that if #-development and #-chestnut-3, bignums will just be consed,
;;; and unless GC is running, the heap will grow.
#+development
(def-structure (managed-development-bignum
                 (:constructor
                   make-managed-development-bignum-internal
                   (managed-development-bignum-value
                    managed-development-bignum-length))
                 (:print-function print-managed-development-bignum))
  managed-development-bignum-value
  managed-development-bignum-length)

#+development
(defun print-managed-development-bignum (bignum stream depth)
  (declare (ignore depth))
      (printing-random-object (bignum stream) ; wraps result in #<..>
        (format stream "Managed ~S-word bignum ~S"
                (managed-development-bignum-length bignum)
                (managed-development-bignum-value bignum))))

(defmacro general-integer-length (x)
  (feature-case
    (development
      `(development-general-integer-length ,x))
    #+chestnut-3
    ((and :chestnut-3 :chestnut-trans)
     `(chestnut-general-integer-length ,x))
    ;; If we are delivering in a non-chestnut environment,
    ;; then we can't reuse bignums, so we must be using
    ;; GC. In this case, we have no need for
    ;; general-integer-length.
    (t 0)))

#+chestnut-3
(def-substitution-macro chestnut-general-integer-length (x)
  (if (typep x 'bignum)
      (tx:bignum-length x)
      0))

#+development
(defparameter bits-per-bignum-digit 32)

;;; This function, whether called in delivery or development,
;;; returns whether the argument would be represented as a fixnum
;;; in delivery. Used instead of fixnum-p, so that exactly the same
;;; integers are stored and reclaimed in delivery and development.
;;;
;;; Current implementation is correct only because at the moment, both
;;; delivery and development use 30-bit fixnums;
;;; Change this if delivery and development have different maximum
;;; fixnum lengths.
(defmacro delivery-fixnum-p (n)
  `(fixnump ,n))

#+development
(defun development-general-integer-length (x)
  (cond
    ((managed-development-bignum-p x)
     (managed-development-bignum-length x))
    ((integerp x)
     (if (delivery-fixnum-p x)
         0
         (let* ((bits (integer-length (abs x))))
           (ceiling bits bits-per-bignum-digit))))
    (t (cerror "Just return 0"
               "Attempt to take the general-integer-length of ~S, which is not an integer" x)
       0)))

(defun-substitution-macro managed-general-integer-value (x)
  #+development
  (if (managed-development-bignum-p x)
      (managed-development-bignum-value x)
      x)
  #-development
  x)

#+chestnut-3
(defmacro allocate-managed-general-integer-internal (value target)
  (feature-case
    ((and chestnut-3 chestnut-trans)
      `(tx:store-bignum ,value ,target))
    ;; In the non-chestnut delivery case, bignums are GC'ed and not
    ;; managed, so just return the value. Target is not used, but this is
    ;; OK, since there is only one call to this macro
    ;; (in allocate-general-integer), and the second argument is just a symbol,
    ;; so it doesn't matter whether it gets evaluated.
    (t value)))

#+development
(defun allocate-managed-general-integer-internal (value target)
  (let* ((value-to-store (managed-general-integer-value value))
         (length (general-integer-length value-to-store)))
    (unless (and (managed-development-bignum-p target)
                 (eql (managed-development-bignum-length target) length))
      (error
        "Attempt to store bignum ~S in incorrectly-sized target ~S"
        value
        target))
    (setf (managed-development-bignum-value target) value-to-store)
    target))

;;; copy-general-integer takes an integer (possibly a managed bignum) and
;;; produces a temporary copy of it. Should only be called within
;;; the dynamic scope of a with-temporary-bignums macro. Since there is
;;; no need to make a temporary copy of a temporary integer, this only
;;; should be used in a case where you wish to reclaim a
;;; managed-general-integer, but still want its value available for
;;; (temporary) use.

#+chestnut-3
(def-substitution-macro chestnut-copy-general-integer (x)
  (if (typep x 'bignum)
      (tx:copy-of-bignum x)
      x))

#-development
(defmacro delivery-copy-general-integer (x)
  (feature-case
    ((and chestnut-3 chestnut-trans)
     `(chestnut-copy-general-integer ,x))
    (t x)))

(defun-substitution-macro copy-general-integer (x)
  #+development
  (if (managed-development-bignum-p x)
      (managed-development-bignum-value x)
      x)
  #-development
  (delivery-copy-general-integer x))

;;; This can be called on either a managed or a temporary integer.
(defun-substitution-macro allocate-managed-general-integer (x)
  #+(or development chestnut-3)
  (if (delivery-fixnum-p x)
      x
      (let* ((value-to-store
               #+development
               (if (managed-development-bignum-p x)
                   (managed-development-bignum-value x)
                   x)
               #-development
               x)
             (length (general-integer-length value-to-store))
             (target (get-managed-bignum length value-to-store)))
        (allocate-managed-general-integer-internal value-to-store target)
        target))
  #+(and (not development) (not chestnut-3))
  x)

;;; We will probably never use bignums of more than 320 digits.
(def-system-variable managed-bignum-pool utilities3
    (:funcall allocate-managed-array 10))

#+(or development chestnut-3)
(defun-substitution-macro reclaim-managed-general-integer (integer)
  (let ((length (general-integer-length integer)))
    (unless (eql length 0)
      (gensym-push integer (managed-svref managed-bignum-pool length)))))

#+(and (not development) (not chestnut-3))
(defmacro reclaim-managed-general-integer (integer)
  (declare (ignore integer))
  nil)

#+development
(defun allocate-bignum-internal (length value)
  (make-managed-development-bignum-internal value length))

#+chestnut-3
(defmacro allocate-bignum-internal (length value)
  (declare (ignore length))
  (feature-case
    (chestnut-trans
      `(with-permanent-non-gensym-float-creation
         (tx:copy-of-bignum ,value)))
    (t value)))

#+(and (not development) (not chestnut-3))
(defun allocate-bignum-internal (length value)
  (declare (ignore length))
  value)

(defun get-managed-bignum (length value)
  (when (>=f length (managed-array-length managed-bignum-pool))
    (setf managed-bignum-pool (adjust-managed-array managed-bignum-pool (1+f length))))
  (let ((available (managed-svref managed-bignum-pool length)))
    (if available
        (gensym-pop (managed-svref managed-bignum-pool length))
        (allocate-bignum-internal length value))))

;;; arg-types is either t or a list; each t in the list indicates
;;; a general-integer argument each nil indicates an argument of another type.
;;; a value of "t" means the function takes an arbitrary number of arguments,
;;; all of which are (potentially managed) bignums.

(defmacro define-bignum-op (name base-operation arg-types)
  (if (listp arg-types)
      `(defmacro ,name (&rest args)
         (cons ',base-operation
               (loop for arg in args
                     for arg-type in ',arg-types
                     collect (if arg-type
                                 (list 'managed-general-integer-value
                                       arg)
                                 arg))))
      `(defmacro ,name (&rest args)
         `(,',base-operation
             ,@(loop for arg in args
                     collect `(managed-general-integer-value ,arg))))))

;;; Base operations are currently generic. If this is too slow, and
;;; benchmarks indicate it would produce a speedup, we can write RTL
;;; functions that are specialized to take only a fixnum or a bignum
;;; as an argument, and call those instead here.

;;; Need to do something smarter for ops like +g and *g that should be
;;; able to take arbitrarily many arguments instead of just 2.

(defparameter-for-macro bignum-operators
  `((1+g 1+ (t))
    (1-g  1- (t))
    (+g  + t)
    (-g  - t)
    (*g  * t)
    (=g  = t)
    (/=g /= t)
    (<g < t)
    (>g > t)
    (<=g  <= t)
    (>=g >= t)
    (minuspg  minusp (t))
    (pluspg plusp (t))
    (ming min t)
    (maxg max t)
    (absg abs (t))
    ;; actually only 1 or two arguments, but this is harmless; it will
    ;; still get caught at compile time if called with too many arguments
    (floorg floor t)
    (ceilingg  ceiling t)    ;ditto
    (truncateg truncate t)
    (roundg  round t)
    (logandg logand t)
    (logandc2g logandc2 (t t))
    (logxorg logxor t)
    (logiorg logior t)
    (logbitpg  logbitp t)
    (ashg ash (t nil))
    (modg  mod t)))

(defmacro halfg (integer)
  `(ashf (general-integer-value ,integer -1)))

(defmacro twiceg (integer)
  `(ashf (general-integer-value ,integer 1)))

;;; Use incfg and decfg if the place is one that holds a temporary
;;; bignum; use incfg-stored and decfg-stored if it is a place that
;;; holds a managed bignum; this will automatically take care of reclaiming
;;; the old bignum that was in the place beforehand, if necessary.
(define-modify-macro incfg (&optional (increment 1)) +g)
(define-modify-macro decfg (&optional (increment 1)) -g)

;;; This could be made slightly more efficient if we checked whether
;;; the value currently in the place, and the new value were bignums
;;; of the same length. In this case, instead of reclaiming the old
;;; value and allocating the new one, we can just copy the new value
;;; into the old one.
(defmacro incfg-managed (place &optional (value 1))
  (multiple-value-bind (temps vals stores store-form access-form)
      (get-setf-method place)
    (let ((result-temp (make-symbol "value-temp"))) ;;make-symbol-for-avoiding-variable-capture?
          `(let* ,(mapcar #'list temps vals)
             (let ((,result-temp
                      (allocate-managed-general-integer (+g ,access-form ,value))))
               (reclaim-managed-general-integer ,access-form)
               (let ((,(car stores) ,result-temp))
                 ,store-form))))))

(defmacro decfg-managed (place &optional (value 1))
  (multiple-value-bind (temps vals stores store-form access-form)
      (get-setf-method place)
    (let ((result-temp (make-symbol "value-temp"))) ;;make-symbol-for-avoiding-variable-capture?
          `(let* ,(mapcar #'list temps vals)
             (let ((,result-temp
                      (allocate-managed-general-integer (-g ,access-form ,value))))
               (reclaim-managed-general-integer ,access-form)
               (let ((,(car stores) ,result-temp))
                 ,store-form))))))

;;; *** Still need to define incfg and decfg! This is tricky!
(defmacro define-bignum-ops ()
  (let ((defmacros
            (loop for op in bignum-operators
                  collect `(define-bignum-op ,@op))))
    `(progn
       ,@defmacros)))

(define-bignum-ops)

;;; Test code
#+testing-bignums(progn

(defvar current-value 1000)

(defun increase-current-value ()
  (with-temporary-bignum-creation
    (let* ((old-value current-value)
           (new-value (*g old-value 998))
           copied-old-value)
      (setq current-value (allocate-managed-general-integer new-value))
      (incfg-managed current-value old-value)
      (setq copied-old-value (copy-general-integer old-value))
      (reclaim-managed-general-integer old-value)
      (incfg-managed current-value copied-old-value)
      (with-permanent-non-gensym-float-creation
        (format t "~%Stored new value ~S" current-value)))))

(defun reclaimed-bignum-statistics ()
  (loop for i from 0 below (managed-array-length managed-bignum-pool) do
    (let ((length (length (managed-svref managed-bignum-pool i))))
      (unless (eql length 0)
        (with-permanent-non-gensym-float-creation
          (format t "~%~S managed bignums of length ~S" length i))))))
)  ;; bignum tests

;;;; Temporary-constants




;;; A temporary constant is the form returned by `evaluate-designation' when it
;;; has obtained a datum rather than a constant or entity.  A temporary-constant
;;; must be released by whoever gets the value of entity evaluate.  Typically, a
;;; temporary-constant must be put on an alist, and then recycled when the alist
;;; is recycled.  It has slots for a value, a type, and an expiration.  Note
;;; that the value is stored as a managed number if necessary, and extracted
;;; from the box on access with constant-value, if necessary.  A temporary
;;; constant must NEVER be stored in a saved kb.

;;; Temporary constants are produced by calling the macro
;;; `make-temporary-constant' with three arguments, the value, the expiration,
;;; and the type.  Temporary constants are returned their pool by calling the
;;; macro `reclaim-temporary-constant'.

(def-structure (temporary-constant
                 (:constructor
                   make-temporary-constant-1
                   (constant-value-internal
                     ;;constant-expiration
                     constant-type)))
  (constant-value-internal nil :reclaimer reclaim-managed-number-or-value)
  ;;constant-expiration
  constant-type)

(defmacro constant-value (temporary-constant)
  `(extract-number-or-value (constant-value-internal ,temporary-constant)))




;;; The macro `cached-constant-value' returns the constant value of the given
;;; temporary constant.  However, the value given is not copied out of the
;;; constant, so the user of this value must not reclaim or modify the returned
;;; value.  In fact, the user must be sure to drop the pointer to it, since the
;;; value may be modified if this temporary constant is reclaimed.  This macro
;;; is useful if the user merely wants to inspect the value, and then drop it
;;; without worrying about reclaimation.

(defmacro cached-constant-value (temporary-constant)
  `(extract-cached-number-or-value
     (constant-value-internal ,temporary-constant)))




;;; The macro `cached-constant-managed-value' returns the managed value cached
;;; within the given temporary constant.  Note that if the temporary constant is
;;; reclaimed or modified, then cached value returned will be reclaimed or
;;; modified as well.  This macro is useful if the user wants to inspect the
;;; value without consing a temporary float (as cached-constant-value can do) or
;;; going through the somewhat expensive extract operations.

(defmacro cached-constant-managed-value (temporary-constant)
  `(constant-value-internal ,temporary-constant))




;;; Note that there is NO setf form for the constant-value slot of temporary
;;; constants.  If you want to modify the constant-value of a
;;; temporary-constant, use the macro `store-constant-value' instead.

(defmacro store-constant-value (temporary-constant value)
  (let ((temp-constant (gensym))
        (new-value (gensym)))
    `(let ((,temp-constant ,temporary-constant)
           (,new-value ,value))
       (store-managed-number-or-value
         (constant-value-internal ,temp-constant)
         ,new-value)
       ,new-value)))

#+ignore
(declare-function-type make-temporary-constant (t #|t|# t) (t))
(declare-function-type make-temporary-constant-no-expiration (t t) (t))

#+ignore
(defun make-temporary-constant (value #|expiration|# type)
  #+development
  (when (managed-float-p value)
    (error "Managed float given to make-temporary-constant, instead of a ~
            double-float."))
  (make-temporary-constant-1-macro
     (box-value-if-necessary value) #|expiration|# type))

(defun make-temporary-constant-no-expiration (value type)
  #+development
  (when (managed-float-p value)
    (error "Managed float given to make-temporary-constant-no-expiration, instead of a ~
            double-float."))
  (make-temporary-constant-1-macro
     (box-value-if-necessary value) #|'never|# type))




;;; The function `make-temporary-constant-given-managed-value' takes a
;;; managed-value, an expiration, and a type and returns a new temporary
;;; constant containing that value.  The given managed-value is reclaimed or
;;; incorporated into the new temporary-constant.
#+ignore
(defun make-temporary-constant-given-managed-value
       (managed-value #|expiration|# type)
  (make-temporary-constant-1-macro
    managed-value
    ;;expiration
    type))

(defun make-temporary-constant-given-managed-value-no-expiration
       (managed-value type)
  (make-temporary-constant-1-macro
    managed-value
    ;;'never
    type))




;;; The function `make-temporary-constant-copying-managed-value' takes managed
;;; value, an expiration, and a type and returns a new temporary constant
;;; containing a copy of the value given in the managed value.
#+ignore
(defun make-temporary-constant-copying-managed-value
       (managed-value #|expiration|# type)
  (make-temporary-constant-1-macro
    (copy-managed-number-or-value managed-value)
    ;;expiration
    type))

(defun make-temporary-constant-copying-managed-value-no-expiration
       (managed-value type)
  (make-temporary-constant-1-macro
    (copy-managed-number-or-value managed-value)
    ;;'never
    type))

;;;




;;; The function `copy-temporary-constant' copies the passed temporary constant
;;; and returns the new copy.  Note that if the value of the passed temporary
;;; constant is a text string, this function will correctly reclaim the
;;; intermediate string.

(declare-function-type copy-temporary-constant (t) (t))

(defun copy-temporary-constant (temporary-constant)
  (make-temporary-constant-1-macro
    (copy-managed-number-or-value (constant-value-internal temporary-constant))
    (constant-type temporary-constant)))




;;; The macro `copy-if-temporary-constant' checks if the passed object is a
;;; temporary constant, and if so will return a copy of it.  Note that if the
;;; value of the temporary constant is a text string, this macro will take care
;;; to reclaim the string created when accessing the value of this constant.  If
;;; value is not a temporary constant, then value itself is returned.

(def-substitution-macro copy-if-temporary-constant (value)
  (if (temporary-constant-p value)
      (make-temporary-constant-1-macro
        (copy-managed-number-or-value (constant-value-internal value))
        (constant-type value))
      value))




;;; The substitution macro `reclaim-if-temporary-constant' checks if the passed
;;; thing is a temporary constant, and if it is the temporary constant gets
;;; reclaimed.  Since this is a fairly large macro when expanded, a function
;;; version is provided, called `reclaim-if-temporary-constant-function'.

(def-substitution-macro reclaim-if-temporary-constant (thing)
  (if (temporary-constant-p thing)
      (reclaim-temporary-constant thing)))

(declare-function-type reclaim-if-temporary-constant-function (t) (t))

(defun reclaim-if-temporary-constant-function (thing)
  (reclaim-if-temporary-constant thing))




;;; The macro `unpack-and-reclaim-temporary-constant' takes a temporary
;;; constant, reclaims it, and returns three values, the constant's value,
;;; expiration, and type.  Note that this may return a text string as the value,
;;; and if so the caller is responsible for reclaiming it.

(def-substitution-macro unpack-and-reclaim-temporary-constant
                        (temporary-constant)
  (let* ((expiration 'never #|(constant-expiration temporary-constant)|#)
         (type (constant-type temporary-constant))
         (internal-value (constant-value-internal temporary-constant)))
    (if (text-string-p internal-value)
        (setf (constant-value-internal temporary-constant) nil)
        (setq internal-value (constant-value temporary-constant)))
    (reclaim-temporary-constant temporary-constant)
    (values internal-value expiration type)))




;;; The macro `reclaim-temporary-constant-returning-managed-value' takes a
;;; temporary constant and reclaims it, returning the managed value that was
;;; stored within it.

(def-substitution-macro reclaim-temporary-constant-returning-managed-value
                        (temporary-constant)
  (prog1 (constant-value-internal temporary-constant)
         (setf (constant-value-internal temporary-constant) nil)
         (reclaim-temporary-constant temporary-constant)))



;;; The macro `with-some-temporary-constants-of-type-number' provides a creates
;;; creates a dynamic extent for N temporary constants.  These constants are
;;; bound to the variables given, those variables should not be rebound.
;;; The body may return one, and only one value.  There should be no nonlocal
;;; transfers of control out of this construct, since it does not use an
;;; unwind protect to reclaim the temporary constants.

;; - ben 2/14/91

(defmacro with-some-temporary-constants-of-type-number (variables &body body)
  (assert (every #'symbolp variables))
  `(let ,(loop
           for variable in variables
           collect `(,variable
                       (make-temporary-constant-no-expiration 1.0 'number)))
     (prog1
       (progn ,@body)
       ,@(loop
           for variable in variables
           collect `(reclaim-temporary-constant ,variable)))))






;;;; Suspendable Tasks



;;; A `suspendable task' is a task that can be suspended before it is finished
;;; and `resumed' later.  (An alternative to suspending and resuming a task is
;;; to have the task spawn some number of subtasks.)

;;; Suspendable tasks are implemented in terms of `suspendable functions' and
;;; `resumption stacks'.  A suspendable function takes as arguments a list of
;;; objects to process (remaining-objects), a list of "other args" (other-args),
;;; and a flag to indicate whether this is a resumption of the function
;;; (resumption?).  Other-args must be a list consisting of unshared, and hence
;;; recyclable, conses that may have been allocated using
;;; recycled-resumption-conses.  A suspendable function sf may return either
;;;
;;;    (1) nil, to indicate that it is finished;
;;;
;;;    (2) four values (remaining-objects, suspendable-subfunction, subobjects,
;;;        and other-args-for-suspendable-subfunction), to ask that
;;;        suspendable-subfunction be called with subobjects,
;;;        other-args-for-suspendable-subfunction, and nil, where, after the
;;;        subfunction has finished, sf will be resumed with remaining-objects,
;;;        other-args, and t;
;;;

;;;    (3) two values (remaining-objects and nil), to ask that the entire
;;;        suspendable task be suspended and resumed later by calling sf with
;;;        remaining-objects, other-args, and t.

;; This code is not, at present, in use anywhere.  It was commented out 7/30/87
;; just to take up a little less space.

;; Put back in by agh on 1/10/88.  It is used now to make the simulator
;; suspendable.

;;; Values-for-calling-suspendable-subfunction is used within a suspendable
;;; function sf to imply a call to suspendable-subfunction with subobjects,
;;; other-args-for-suspendable-subfunction, and nil, where sf should resume with
;;; remaining-objects after subfunction is finished.  This should be used within
;;; a explicit or implicit return or return-from form; see above.
;;; Other-args-for-suspendable-subfunction must consist of unshared, and hence
;;; recyclable, conses that should be allocated using recycled-resumption-
;;; conses.

(defmacro values-for-calling-suspendable-subfunction
          (remaining-objects suspendable-subfunction subobjects
           other-args-for-suspendable-subfunction)
  `(values ,remaining-objects ,suspendable-subfunction ,subobjects
           ,other-args-for-suspendable-subfunction))



;;; Values-for-suspending-task is used within a suspendable function sf to imply
;;; a suspension of the task that sf is working on, where sf should resume later
;;; with remaining-objects.  This should be used within a explicit or implicit
;;; return or return-from form; see above.

(defmacro values-for-suspending-task
          (remaining-objects)
  `(values ,remaining-objects nil))



(def-system-variable recycled-resumption-conses schedule nil)



;;; Work-on-suspendable-task starts, or resumes if resumption? is non-nil,
;;; working on a suspendable task by calling suspendable-function with objects,
;;; other-args, and resumption? as the arguments.  Other-args must be a list
;;; consisting of unshared, and hence recyclable, conses that may have been
;;; allocated using recycled-resumption-conses.

;;; Work-on-suspendable-task returns either nil, to indicate that the task is
;;; finished, or a resumption-stack, to indicate that the task has been
;;; suspended and needs to be resumed later using resume-task.

(defun work-on-suspendable-task
       (suspendable-function objects other-args resumption? resumption-stack)
  (declare (eliminate-for-gsi))
  (loop while
          (multiple-value-bind
            (remaining-objects suspendable-subfunction? subobjects
             other-args-for-suspendable-subfunction)
              (funcall-symbol
                suspendable-function objects other-args resumption?)
            (cond
              ((null remaining-objects)
               (if resumption?
                   (let ((cdddr-of-resumption-stack (cdddr resumption-stack)))
                     (setf (cdddr resumption-stack) recycled-resumption-conses)
                     (setq recycled-resumption-conses
                           (nconc (third resumption-stack) resumption-stack))
                     ;; clear the cars of the recycled conses?
                     (setq resumption-stack cdddr-of-resumption-stack)))
               (cond
                 (resumption-stack
                  (setq suspendable-function (first resumption-stack))
                  (setq objects (second resumption-stack))        ; these change args
                  (setq other-args (third resumption-stack))
                  (setq resumption? t))))
              (t (if (null resumption?)
                     (setq resumption-stack
                           (let ((remaining-recycled-resumption-conses
                                   (cdddr recycled-resumption-conses)))
                             (if (null remaining-recycled-resumption-conses)
                                 (let ((new-top-of-stack
                                         (gensym-list suspendable-function nil other-args)))
                                   (setf (cdddr new-top-of-stack) resumption-stack)
                                   new-top-of-stack)
                                 (prog1
                                   recycled-resumption-conses
                                   (setf (first recycled-resumption-conses)
                                         suspendable-function)
                                   (setf (third recycled-resumption-conses) other-args)
                                   (setf (cdddr recycled-resumption-conses)
                                         resumption-stack)
                                   (setq recycled-resumption-conses
                                         remaining-recycled-resumption-conses))))))
                 (setf (second resumption-stack) remaining-objects)
                 (cond
                   (suspendable-subfunction?
                  (setq suspendable-function suspendable-subfunction?)        ; these change args
                  (setq objects subobjects)
                  (setq other-args other-args-for-suspendable-subfunction)
                  (setq resumption? nil)
                  t)))))
        finally
          (return resumption-stack)))



;;; Resume-task ... returns either nil, to indicate that the suspendable task is
;;; finished, or a resumption-stack, to indicate that the task has been
;;; suspended and needs to be resumed later using resume-task.

(defun resume-task (resumption-stack)
  (declare (eliminate-for-gsi))
  (gensym-dstruct-bind ((function objects other-args) resumption-stack)
    (work-on-suspendable-task
      function objects other-args
      t resumption-stack)))

;; Consider defining this as a macro.






;;;; Multiple Value Setf



;;; Multiple-value-setf is a macro having the same syntax as multiple-value-setq
;;; except that instead of a list of variables to receive the multiple values,
;;; the list may contain any place acceptable to setf. (If all the places are
;;; variables, it turns into multiple-value-setq.)

(defmacro multiple-value-setf (list-of-places form)
  (loop with only-variables? = t
        for place in list-of-places
        collecting (gensym) into binding-list
        unless (symbolp place) do (setq only-variables? nil)
        finally
          (if only-variables?
              (return `(multiple-value-setq ,list-of-places ,form))
              (return `(multiple-value-bind ,binding-list ,form
                         ,@(loop for place in list-of-places
                                 for binding in binding-list
                                 collecting `(setf ,place ,binding)))))))








;;;; Development Tools


#+development
(defvar brakeon-functions nil)

#+development
(defun brakeon (&optional function-spec (condition t))
  (cond
    (function-spec
     (eval
       `(advise ,function-spec :before brakeon-advice nil
          (if ,condition
              (cerror "Continue" "Brake on entry to function ~a" ',function-spec))))
     (eval
       `(advise ,function-spec :after brakeon-advice nil
          (if ,condition
              (cerror "Continue" "Brake on entry to function ~a" ',function-spec))))))
  (push function-spec brakeon-functions))

#+development
(defun unbrakeon (&optional function-spec)
  (if function-spec
      (eval `(unadvise ,function-spec))
      (loop for function-spec in brakeon-functions
            do (eval `(unadvise ,function-spec)))))



;;; Mexp for Lucid. Any keyword or NIL exits the loop.
;;; This code should actually work in any common lisp,
;;; but first make sure they do not already define mexp.

#+(and Lucid development)
(defun mexp (&optional form)
  (let ((*print-pretty* t)
        (interactive-p (null form)))
    (loop
     (when interactive-p
       (format t "Macro form: ")
       (force-output)
       (setq form (read))
       (when (or (null form)
                 (keywordp form))
         (return)))

     (let ((m1 (macroexpand-1 form))
           (m2 (macroexpand form)))
       (format t "~s" form)
       (format t " -->~%~s" m1)
       (unless (equal m1 m2)
         (format t " -->~%~s" m2))
       (terpri))

     (unless interactive-p
       (return)))
    (values)))






;;;; Defining List Structures


;; Beginning of contribution by SD.

#+development
(def-global-property-name list-structure-description)

;;; Def-list-structure ...

;;; An expression of the form
;;;
;;; (def-list-structure (structure-name
;;;                        [(:constructor nil|constructor-name)]
;;;                        [(:consing-function nil|consing-function-name)])
;;;    list-structure)
;;;
;;; defines a list structure.  A list structure is a structure made of conses.
;;; Optionally, a function to construct such a structure can be defined.

;;; (:constructor nil|constructor-name) allows the user to choose a name for the
;;; constructor. If the feature is not present, then the default constructor is
;;; defined. The default name for the constructor will be the name of the structure
;;; prefixed by "MAKE-".  If (:constructor nil) is specified, then no constructure
;;; is defined.  If (:constructor constructor-name) is specified, then a constructor
;;; function with the specified name is defined.

;;; (:consing-function [nil|consing-function-name>]) allows the user to specify what
;;; function should be used to cons up the structure. If the feature is not present,
;;; then the function CONS is used. If (:consing-function nil) is specified, then no
;;; consing function is defined.  If (:consing-function function-name) is specified,
;;; then a consing function with the specified name is defined.

;;; The last form, list-structure, models the structure of the defined list structure.
;;; Any non-nil atoms present in the structure are interpreted as names for accessors
;;; into the structure. Nil can be used to fill in structure without causing the
;;; definition of an accessor. The accessors are all setf'able macros.

;;; The following is an example of a structure being defined by def-list-structure.

;;; (def-list-structure (foo (:consing-function frame-cons))
;;;   (bar (baz mumble . blatt) . others))


;; Using dotted-pair notation instead of &rest in a sublist of a defmacro
;; lambda-list causes Lucid to emit an "unknown go tag" message.  (jh, 9/24/90)

(defmacro def-list-structure
    ((structure-name &rest list-structure-features) structure-form)
  (let* ((constructor?
           (let ((spot? (assq :constructor list-structure-features)))
             (if spot?
                 (cadr spot?)                                    ; nil => don't define one
                 (intern (format nil "MAKE-~A" structure-name)))))
         (optimize?
           (cadr (assq :optimize list-structure-features)))
         (definer
             (if optimize? 'def-substitution-macro 'defun))
         (car-function
             (if optimize? 'car-of-cons 'car))
         (cdr-function
             (if optimize? 'cdr-of-cons 'cdr))
         (consing-function
           (or (cadr (assq :consing-function list-structure-features))
               'cons)))

    (multiple-value-bind (names-of-accessors accessing-sequences constructor-body)
        (disect-list-structure structure-name structure-form
                               consing-function car-function cdr-function)

      ;; FIX PRIMARILY FOR CHESTNUT/C Compiler BUG! (But OK for all.)
      ;; (MHD/AC 4/25/91)
      (loop for l on accessing-sequences
            when (consp (car l))
              do (setf (car l)
                       (compact-repeated-cxrs-in-list (car l))))

      `(progn
         #+development
         (setf (list-structure-description ',structure-name)
               '((,structure-name ,@list-structure-features) ,structure-form))
         ,@(loop for accessor? in names-of-accessors
                 as accessing-sequence
                    = (car accessing-sequences)
                    then (car rest-of-accessing-sequences)
                 as rest-of-accessing-sequences
                    = (cdr accessing-sequences)
                    then (cdr rest-of-accessing-sequences)
                 when accessor?
                   collect
                   `(defmacro ,accessor? (,structure-name)
                      ,(let ((accessor-body structure-name))
                         (loop for operation in accessing-sequence
                               do (setq accessor-body
                                        (list 'list (list 'quote operation) accessor-body)))
                         accessor-body)))
         ,@(if constructor?
               `((,definer ,constructor? ,(delete nil names-of-accessors)
                   ,constructor-body)))
         ',structure-name))))







;;; `Compact-repeated-cxrs-in-list' takes a list of the form
;;;
;;;    ( {CAR|CDR} )
;;;
;;; and returns a list where each sequence of up to four successive CDR's
;;; is replaced with CDDR, CDDDR, or CDDDDR, and each sequence of up to four
;;; successive CAR's is replaced with CAAR, CAAAR, or CAAAAR.

(defun-for-macro compact-repeated-cxrs-in-list (list-of-cxrs)
  (loop with result = nil
        for cxr in list-of-cxrs
        do (case cxr
             ((cdr cdr-of-cons)
              (case (car result)
                ((cdr cdr-of-cons) (setf (car result) 'cddr))
                (cddr (setf (car result) 'cdddr))
                (cdddr (setf (car result) 'cddddr))
                (t (setq result (cons cxr result)))))
             ((car car-of-cons)
              (case (car result)
                ((car car-of-cons) (setf (car result) 'caar))
                (caar (setf (car result) 'caaar))
                (caaar (setf (car result) 'caaaar))
                (t (setq result (cons cxr result)))))
             (t
              (error "illegal element: ~s; not CAR or CDR" cxr)))
        finally
          (return (nreverse result))))




(defun-for-macro disect-list-structure (structure-name structure-form
                                                       cons-function
                                                       car-function
                                                       cdr-function)
  (cond
    ((null structure-form)
     (values nil nil nil))
    ((atom structure-form)
     (values
       (list structure-form)
       (list nil)
       structure-form))
    ((atom (car structure-form))
     (multiple-value-bind
       (accessor-names lists-of-accessor-names constructor-body)
         (disect-list-structure structure-name (cdr structure-form)
                                cons-function car-function cdr-function)
       (values
         (cons (car structure-form) accessor-names)
         (cons (list car-function)
               (mapcar #'(lambda (accessor-list) (cons cdr-function accessor-list))
                       lists-of-accessor-names))
         (list cons-function
               (car structure-form)
               constructor-body))))
    (t (multiple-value-bind
         (accessor-names1 lists-of-accessor-names1 constructor-body1)
           (disect-list-structure structure-name (car structure-form)
                                  cons-function car-function cdr-function)
         (multiple-value-bind
           (accessor-names2 lists-of-accessor-names2 constructor-body2)
             (disect-list-structure structure-name (cdr structure-form)
                                    cons-function car-function cdr-function)
           (values
             (nconc accessor-names1 accessor-names2)
             (nconc
               (mapcar
                 #'(lambda (accessor-list) (cons 'car accessor-list))
                 lists-of-accessor-names1)
               (mapcar
                 #'(lambda (accessor-list) (cons 'cdr accessor-list))
                 lists-of-accessor-names2))
             (list cons-function
                   constructor-body1
                   constructor-body2)))))))

;; The above function is strictly a subfunction of the macro def-list-structure and
;; therefore should be eliminated in the run-time environment.  Consider defining
;; def-macro-expander to be used instead of defun for functions only needed for macro
;; expansions. -- DONE (with defun-for-macro).





;; End of contribution by SD.








;;;; Interning Text Strings and Generating Symbols



;;; Intern-gensym-string is like intern, except that it takes a gensym-string which is to
;;; be reclaimed unless it is incorporated into the resulting symbol.

;; jh per ml & jra, 7/1/91.  Changed intern-gensym-string to keep track of
;; user-interned symbols.  This is done by concocting a system-object-pool which
;; will measure their allocation.  Now that "change the text of" has given G2
;; users the ability to intern symbols under program control, it is possible to
;; crash G2 by overflowing the part of memory devoted to storing symbols, which
;; are not currently reclaimable.  Keeping track of user-interned symbols will
;; help us troubleshoot such cases.

(def-system-variable count-of-interned-gensym-strings UTILITIES3 0)
(def-system-variable memory-used-for-interned-gensym-strings UTILITIES3 0)

;; Bytes-in-symbol is an approximation for now: the function cell, value cell,
;; package cell, symbol-name, and symbol-plist are each a 4-byte word.  We add the
;; size of the symbol's name, including a 1-byte terminator, and 1 word of
;; unspecified overhead.

(def-substitution-macro bytes-in-symbol (symbol-name)
  (+f 25 (length symbol-name)))

(defun-simple gensym-symbol-name (symbol)
  #-chestnut-trans
  (copy-gensym-string (symbol-name symbol))
  #+chestnut-trans
  (let* ((name (trun:isymbol-name symbol))
         (len (trun:strlen name))
         (gensym-string (obtain-gensym-string len)))
    (if (simple-string-p gensym-string)
        (loop for i fixnum below len
              do (setf (schar gensym-string i)
                       (tx:typed-foreign-aref '(:pointer (:array :char (*))) name i)))
        (loop for i fixnum below len
              do (setf (char gensym-string i)
                       (tx:typed-foreign-aref '(:pointer (:array :char (*))) name i))))
    gensym-string))

;;; `Nil-interned' is the result of calling INTERN on the string "NIL".
;;;
;;; This is part of a Chestnut bug workaround for intern-gensym-string.
;;; Nil-interned _should_, of course, be in the symbol nil (i.e., lisp::nil,
;;; i.e., the result of evaluating (not T)), but it is not so in Chestnut due to
;;; a bug.  This is used now in order for intern-gensym-string to have a
;;; workaround: if the result of interning is nil-interned, it always returns
;;; the proper symbol nil, whether or not that symbol is eq to nil-interned as
;;; it should be.

(defvar nil-interned (intern "NIL"))

#+chestnut-trans
(tx:def-foreign-function (inline-cached-symbol-name
                           (:name "INLINE_CACHED_SYMBOL_NAME")
                           (:return-type :object))
    (name :object))

(defun intern-gensym-string (gensym-string &optional (package? nil))
  (multiple-value-bind (symbol pre-existing-symbol-p)
      (intern gensym-string (or package? *package*))
    (unless pre-existing-symbol-p
      (atomic-incff count-of-interned-gensym-strings)
      (atomic-incff memory-used-for-interned-gensym-strings (bytes-in-symbol gensym-string)))
    (unless (eq (#-chestnut-trans symbol-name
                 #+chestnut-trans inline-cached-symbol-name
                   symbol)
                gensym-string)        ; if symbol existed already or
      (reclaim-gensym-string gensym-string))                ;   if string is not used
    (if (eq symbol nil-interned)        ; In Chestnut, nil-interned is ab::nil,
        nil                                ;   due to a bug, but it should be lisp::nil!
        symbol)))                        ;   This is a workaround for that bug.

;; jh & mhd, 2/7/92.  Changed intern-gensym-string to ensure that only
;; simple strings are interned.  We did this after encountering a
;; not-quite-explained bug wherein typing in a symbol to a Chestnut G2
;; with over 100 characters produces a printname which indeed has the
;; first 100 characters but then seems to postpend some characters from
;; the reclaimed gensym-string pool.  The number 100 is too magic to be a
;; coincidence, since it also
;; maximum-suggested-length-for-simple-gensym-strings.  Note that
;; copy-gensym-string is guaranteed always to return a simple text string.

(defun-simple intern-using-string-buffer (string-buffer length package?)
  (setf (char string-buffer length) (code-char 0))
  (setf (fill-pointer string-buffer) length)
  (multiple-value-bind (symbol pre-existing-symbol-p)
      (intern string-buffer (or package? *package*))
    (unless pre-existing-symbol-p
      (atomic-incff count-of-interned-gensym-strings)
      (atomic-incff memory-used-for-interned-gensym-strings length))
    (if (eq symbol nil-interned)        ; In Chestnut, nil-interned is ab::nil,
        nil                                ;   due to a bug, but it should be lisp::nil!
        symbol)))



;;; The substitution-macro `intern-substring' returns the symbol
;;; in AB named by the given substring of string.

(def-substitution-macro intern-substring (string start? end?)
  (let ((substring (gensym-string-substring string start? end?)))
    (intern-gensym-string substring ab-package-1)))





(defun-simple position-of-two-colons (string)
  (if (text-string-p string)
      (loop with length = (lengthw string)
            for i from 0 below (1-f length)
            when (and (char=w (charw string i) #.%\:)
                      (char=w (charw string (+f i 1)) #.%\:))
              do (return i))
      (loop with length = (length string)
            for i from 0 below (1-f length)
            when (and (char= (char string i) #\:)
                      (char= (char string (+f i 1)) #\:))
              do (return i))))



(def-system-object-pool user-interned-symbols symbol
  count-of-interned-gensym-strings        ;counter
  count-of-interned-gensym-strings        ;outstanding counter
  nil                                        ;outstanding counter function
  get-memory-used-for-interned-text-strings  ;total-memory-use-function
  )

(defun get-memory-used-for-interned-text-strings ()
  memory-used-for-interned-gensym-strings)

;; Note: this was not changed over to "gensym-string", but remains
;; "text-string".  Perhaps it should be renamed to have "text-string", or, more
;; simply, replace "interned-text-string" with "symbol".  (MHD 2/6/96)





;;; (def-interned-symbol-supply string) is used to create a supply of interned symbols
;;; having the form foo-1, foo-2, etc. These can be used with a wrap-around
;;; macro (with-interned-foo-symbols &body) where "foo" in this documentation
;;; represents the string.  Symbols are obtained sequentially within the wrap-around
;;; as the value of (interned-foo-symbol).

;;; Example: After (def-interned-symbol-supply "compiler") in the source
;;; code, it is  possible to write code such as:
;;;   (with-interned-compiler-symbol-supply
;;;       ...   (interned-compiler-symbol)   ... )
;;; where sequential evaluations of (interned-compiler-symbol) within any invocation
;;; of the wrap-around will have as values the interned symbols compiler-1, compiler-2, ...

(defmacro def-interned-symbol-supply (string)
  (let* ((upcase-string (string-upcase string))
         (symbol-supply (intern (format nil "~A-SYMBOL-SUPPLY" upcase-string)))
         (symbol-counter (intern (format nil "~A-SYMBOL-COUNTER" upcase-string)))
         (listed-next-symbol (intern (format nil "~A-LISTED-NEXT-SYMBOL" upcase-string))))
    `(progn

       (defvar ,symbol-counter)
       (defvar ,listed-next-symbol)

       (def-system-variable ,symbol-supply utilities3
         (:funcall list ,(intern (format nil "~A-1" upcase-string)))
         nil t)

       (defmacro ,(intern (format nil "WITH-INTERNED-~A-SYMBOLS" upcase-string)) (&body body)
	 `(let ((,',symbol-counter 1)
		(,',listed-next-symbol ,',symbol-supply))
	    ,@body))

       (defun ,(intern (format nil "INTERNED-~A-SYMBOL" upcase-string)) ()
	 ;; Gensym-1110-TAM2-IM-BF-JIRA-47071-G2 abort when runing the escor-demo-test.kb
	 ;; if listed-next-symbol is not list, set it to new symbol with symbol-counter,
	 ;; this is to avoid G2 abort.
	 (when (not (consp ,listed-next-symbol))
	   (atomic-incff ,symbol-counter)
	   (setq ,listed-next-symbol
		 (with-dynamic-creation
		   (list (intern (format nil "~A-~D", upcase-string ,symbol-counter))))))
	 (if (cdr ,listed-next-symbol)
	     (prog1 (car ,listed-next-symbol)
	       (atomic-incff ,symbol-counter)
	       (setf ,listed-next-symbol (cdr ,listed-next-symbol)))
	   (prog1 (car ,listed-next-symbol)
	     (atomic-incff ,symbol-counter)
	     (setf (cdr ,listed-next-symbol)
		   (with-dynamic-creation
		     (list (intern (format nil "~A-~D" ,upcase-string ,symbol-counter)))))
	     (setf ,listed-next-symbol (cdr ,listed-next-symbol))))))))







;;;; Miscellany




;;; (setbits place bits) stores logior of place and bits
;;; in place, and has the same for a value. The value of place
;;; before the operation must be a fixnum.

(define-modify-macro setbits (bits)
  logiorf)


;;; (clearbits place bits) stores logandc2 of place and bits
;;; in place, and has the same for a value. The value of place
;;; before the operation must be a fixnum.

(define-modify-macro clearbits (bits)
  logandc2f)








;;;; Truth Values



;;; `Truth-values' are represented by integers within [-1000, 1000]
;;; internally, but the user will be presented with an apparent fractional range
;;; of [-1, 1].  *Truth-threshhold* must be converted to this form upon reading.

(defconstant truth 1000)

(defconstant falsity -1000)








;;;; Utility Functions for Read-From-String Functions:




;;; The substitution macros
;;; `value-times-ten-plus-weight-<=-most-positive-fixnum-p',
;;; `value-times-ten-plus-weight->=-most-negative-fixnum-p', and
;;; `value-times-ten-minus-weight->=-most-negative-fixnum-p ' test to see if a
;;; value, when multiplied by ten and offset by weight, will still be a fixnum.
;;; The parameters value and weight must be fixnums.  Weight must also be a
;;; single digit number (0 <= weight <= 9).  These macros are useful to
;;; functions which read numbers.

(defconstant most-positive-fixnum-floor-10
  (floorf most-positive-fixnum 10))

(def-substitution-macro value-times-ten-plus-weight-<=-most-positive-fixnum-p
    (value weight)
  (and (<=f value most-positive-fixnum-floor-10)
       ;; We assume that "and" does not check the second argument if the first
       ;; is non-nil.  If it does, we might generate numbers bigger than
       ;; most-positive-fixnum.
       (<=f weight (-f most-positive-fixnum (*f value 10)))))

(defconstant most-negative-fixnum-ceiling-10
  (ceilingf most-negative-fixnum 10))

(def-substitution-macro value-times-ten-plus-weight->=-most-negative-fixnum-p
    (value weight)
  (and (>=f (-f value) most-negative-fixnum-ceiling-10)
       (>=f weight (-f most-negative-fixnum (*f (-f value) 10)))))

(defun-simple value-times-ten-minus-weight->=-most-negative-fixnum-p
    (value weight)
  (and (>=f (-f value) most-negative-fixnum-ceiling-10)
       (<=f weight (-f (*f value 10) most-negative-fixnum))))

;;; `Read-number-without-exponent' reads a decimal number from string, starting
;;; at position start-index and ending either at the first non-useful character
;;; or at position end-index (the first position this function will not read).
;;; The number read may have an optional initial sign and/or decimal point, but
;;; any exponent is ignored.  There must be at least one digit between start-
;;; index and end-index.  Three values are returned:
;;;
;;;    (1) a fixnum (or a bignum or a gensym float, according to which
;;;    of these, if either, is specified by allowed-non-fixnum-number-type?),
;;;
;;;    (2) a fixnum power of 10 by which the first value should be
;;;    multiplied (equal, in most cases, to minus the number of digits
;;;    past the decimal point, if any), and,
;;;
;;;    (3) the index where reading ended (i.e. the position in the string
;;;    just after the last character read as part of the number.)
;;;
;;; This function will return fixnum if the value read can be stored as one,
;;; otherwise, a gensym float is returned.

;;; Note that as long as allowed-non-fixnum-number-type? is nil, the first value
;;; returned will be a fixnum and this function will not cons floats or bignums.
;;; Otherwise, this should be called in a temporary number consing context (or
;;; "wrapper") to avoid consing.

;; Modified this function to handle the case of a plus or minus sign without a
;; number, such as "+", "-", "+foo", or "-foo".  This was incorrectly returning
;; the values 0, 0, and 1 which indicate a result of 0.  It now returns the
;; values 0, 0, and 0 which indicate a non-numeric result.  This bug was causing
;; incorrect results in the quantity and text-begins-with-quantity G2 functions.
;; - cpm, 12/31/91

;; Also, fixed a bug (separate from the above fix) where a "-" or "+" argument
;; would cause an error in trying to reference the character after the sign.  -
;; cpm, 12/31/91

(defun read-number-without-exponent
       (the-string start-index end-index allowed-non-fixnum-number-type?)
  (declare (eliminate-for-gsi))
  (loop with non-fixnum-number-type? = nil
        with value-so-far = 0
        with character = (charw the-string start-index)
        with negative? = (char=w character #.%\-)
        with positive-char? = (char=w character #.%\+)
        with number-of-ignored-digits = 0
        with index-of-decimal-point? = nil
        with initial-index = start-index
        with weight?
        initially
          (when (or negative? positive-char?)        ; changes arg
            (if (=f (incff start-index) end-index)
                (loop-finish)
                (setq character (charw the-string start-index))))
        do (cond
             ((setq weight? (digit-char-pw character))
              (if negative? (setq weight? (-f weight?)))
              (cond
                ((and (or non-fixnum-number-type?
                          (<f (absf value-so-far)        ; absf added -- MHD -- 5/8/90
                              most-positive-fixnum-floor-10)
                          (if (setq non-fixnum-number-type?
                                    allowed-non-fixnum-number-type?)
                              (progn
                                (if (eq allowed-non-fixnum-number-type?
                                        'gensym-float)
                                    (setq value-so-far
                                          (coerce-to-gensym-float value-so-far)))
                                t))
                          (if negative?
                              (value-times-ten-plus-weight->=-most-negative-fixnum-p
                                value-so-far weight?)
                              (value-times-ten-plus-weight-<=-most-positive-fixnum-p
                                value-so-far weight?)))
                      (or (not (eq non-fixnum-number-type? 'gensym-float))
                          ;; This allows reasonably huge numbers without allowing them
                          ;; to become larger than the most positive or negative float;
                          ;; added for 5.0. (JV/MHD 5/29/97)
                          (<=e #.(/ most-negative-gensym-float 10)
                               value-so-far
                               #.(/ most-positive-gensym-float 10))))
                 (setq value-so-far
                       (cond
                         ((not non-fixnum-number-type?)
                          (+f (*f 10 value-so-far) weight?))
                         ((eq allowed-non-fixnum-number-type? 'gensym-float)
                          (+ (*e 10.0 value-so-far) weight?))        ; weight? is a fixnum
                         (t (+ (* 10 value-so-far) weight?)))))
                (t
                 (incff number-of-ignored-digits))))
             ((and (char=w character #.%\.)
                   (null index-of-decimal-point?))
              (setq index-of-decimal-point? start-index))
             (t (loop-finish)))
        until (=f (incff start-index) end-index)
        do (setq character (charw the-string start-index))
        finally
          (return
            (values
              value-so-far
              (if index-of-decimal-point?        ; -number-type? ?
                  (+f (-f index-of-decimal-point? start-index)
                      1
                      number-of-ignored-digits)
                  number-of-ignored-digits)
              (cond ((and (or negative? positive-char?)
                          ;; + or - and possible non-numeric char should return
                          ;; the initial value which indicates a non-numeric
                          ;; result.  - cpm, 12/31/91
                          (<=f start-index (+f initial-index 1)))
                     initial-index)
                    (t start-index))))))





;;;; Read-From-String Functions:



;;; `Read-from-string' functions: These functions take a string (always a text
;;; string -- i.e., a wide string), a start-index and an end-index, and attempt
;;; to read the appropriate value from the string starting from the position
;;; given by start-index.  End-index is the first position that these functions
;;; are NOT supposed to read.  As the index for strings start at 0, the maximum
;;; value of end-index is (lengthw string).
;;;
;;; The string passed to these functions must be at least of length 1, and
;;; end-index is at most the length of the string.
;;;
;;; These functions return three values:
;;;
;;; (1) the number or value as a managed number or value, or nil if an error
;;; occurred while reading the string,
;;;
;;; (2) the position just after the last character which was read as part of the
;;; number or value, and,
;;;
;;; (3) nil if the value was correctly read or is there is no error message, or
;;; a non-reclaimable string containing an error message if the value was not
;;; present or could not be read.  If (3) is a string, (1) will be nil.
;;;
;;; The following are read-from-string functions:
;;; `read-positive-fixnum-from-string', `read-negative-fixnum-from-string',
;;; `read-fixnum-from-string', `read-number-from-string',
;;; `read-symbol-from-string', `read-truth-value-from-string',
;;; `read-text-string-from-string', `read-time-stamp-from-string'.
;;;
;;; The exception to the values returned is in read-time-stamp-from-string. This
;;; function returns the values: seconds, minutes, hours, day, month, year, (2),
;;; and (3).  Only one of the returned values, the seconds, may be managed
;;; numbers.  This seconds return value should be owned or reclaimed by the
;;; caller.
;;;
;;; The true test for an error is if (1) is nil.  If both (1) and (3) are nil,
;;; then the error is because the string starting at start-index is simply not
;;; of the correct data type.  An error message is returned if an error such as
;;; a numerical overflow occurs.  The value returned in (2) will be start-index
;;; if there was an error.




;;; The function `read-positive-fixnum-from-string' reads a string of digits and
;;; returns a positive fixnum.  The + sign is NOT read as part of the number.

(defun read-positive-fixnum-from-string (string start-index end-index)
  (let ((string-index start-index)
        (digit-character #.%\a)
        (digit? nil)
        (fixnum-so-far 0))
    (declare (type fixnum string-index fixnum-so-far))
    (loop while (<f string-index end-index)
          do
      (setq digit-character (charw string string-index))
      (if (setq digit? (digit-char-pw digit-character))
          (if (or (<f fixnum-so-far most-positive-fixnum-floor-10)
                  (value-times-ten-plus-weight-<=-most-positive-fixnum-p
                    fixnum-so-far digit?))
              (setq fixnum-so-far (+f (*f fixnum-so-far 10) digit?))
              (return (values nil (+f string-index 1) "number is too large")))
          (loop-finish))
      (incff string-index)                ; point to next character
          finally
            (return
              (values
                (if (not (=f string-index start-index)) fixnum-so-far)
                string-index nil)))))

;;; The function `read-negative-fixnum-from-string' reads a string of digits,
;;; starting with a "-" sign, and returns a negative fixnum.

(defun read-negative-fixnum-from-string (string start-index end-index)
  (loop with string-index = (+f start-index 1)
        and digit-character
        and digit?
        and fixnum-so-far = 0
        initially
          (if (not (char=w (charw string start-index) #.%\-))
              (return (values nil start-index nil)))
        while (<f string-index end-index)
        do (setq digit-character (charw string string-index))
           (if (setq digit? (digit-char-pw digit-character))
               (if (or (>f fixnum-so-far most-negative-fixnum-ceiling-10)
                       (value-times-ten-minus-weight->=-most-negative-fixnum-p
                         fixnum-so-far digit?))
                   (setq fixnum-so-far (-f (*f fixnum-so-far 10) digit?))
                   (return
                     (values
                       nil (+f string-index 1) "negative number is too large")))
               (loop-finish))
           (incff string-index)                ; point to next character
        finally
          (return
            (values
              (if (not (=f string-index start-index)) fixnum-so-far)
              string-index nil))))

(defun read-fixnum-from-string (string &optional start-index? end-index?)
  (let* ((start-index (or start-index? 0))
         (end-index (or end-index? (text-string-length string)))
         (digit-character (charw string start-index)))
    (cond
      ((char=w digit-character #.%\-)
       (read-negative-fixnum-from-string string start-index end-index))
      ((char=w digit-character #.%\+)
       (read-positive-fixnum-from-string string (+f start-index 1) end-index))
      (t
       (read-positive-fixnum-from-string string start-index end-index)))))

(defparameter most-positive-int64-floor-10 ; 922337203685477580
  #+chestnut-trans
  (coerce-to-gensym-long (* 66024901 77608531 180))
  #-chestnut-trans
  (floor most-positive-int64 10))

(defun-simple value-times-ten-plus-weight-<=-most-positive-int64-p
    (value weight)
  (declare (type #.(gensym-long-type) value weight))
  (and (<=l value most-positive-int64-floor-10)
       ;; We assume that "and" does not check the second argument if the first
       ;; is non-nil.  If it does, we might generate numbers bigger than
       ;; most-positive-fixnum.
       (<=l weight (-l most-positive-int64 (*l value 10)))))

(defun read-positive-long-from-string (string start-index end-index)
  (declare (eliminate-for-gsi))
  (let ((string-index start-index)
	(digit-character #.%\a)
	(digit? nil)
	(num-so-far 0))
    (declare (type fixnum string-index)
	     (type #.(gensym-long-type) num-so-far))
    (loop while (<f string-index end-index)
	  do
      (setq digit-character (charw string string-index))
      (if (setq digit? (digit-char-pw digit-character))
	  (if (or (<l num-so-far most-positive-int64-floor-10)
		  (value-times-ten-plus-weight-<=-most-positive-int64-p
		    num-so-far digit?))
	      (setq num-so-far (+l (*l num-so-far 10) digit?))
	    (return (values 'overflow (+f string-index 1) "number is too large")))
	(loop-finish))
      (incff string-index) ; point to next character
	  finally
	    (return
	      (values
		(if (not (=f string-index start-index)) num-so-far)
		string-index nil)))))

(defparameter most-negative-int64-ceiling-10 ; -922337203685477580
  #+chestnut-trans
  (coerce-to-gensym-long (* (* 66024901 77608531) -180))
  #-chestnut-trans
  (ceiling most-negative-int64 10))

(defun-simple value-times-ten-minus-weight->=-most-negative-int64-p
    (value weight)
  (declare (type #.(gensym-long-type) value weight))
  (and (>=l (-l value) most-negative-int64-ceiling-10)
       (<=l weight (-l (*l value 10) most-negative-int64))))

(defun read-negative-long-from-string (string start-index end-index)
  (declare (eliminate-for-gsi))
  (let ((string-index start-index)
        (digit-character #.%\a)
        (digit? nil)
	(num-so-far 0))
    (declare (type fixnum string-index))
    (loop while (<f string-index end-index)
	  do
      (setq digit-character (charw string string-index))
      (if (setq digit? (digit-char-pw digit-character))
	  (if (or (>l num-so-far most-negative-int64-ceiling-10)
		  (value-times-ten-minus-weight->=-most-negative-int64-p
		    num-so-far digit?))
	      (setq num-so-far (-l (*l num-so-far 10) digit?))
	    (return (values 'underflow (+f string-index 1)
			    "negative number is too large")))
	(loop-finish))
      (incff string-index) ; point to next character
	  finally
	    (return
	      (values
		(if (not (=f string-index start-index)) num-so-far)
		string-index nil)))))

(defun read-long-from-string (string &optional start-index? end-index?)
  (declare (eliminate-for-gsi))
  (let* ((start-index (or start-index? 0))
	 (end-index (or end-index? (text-string-length string)))
	 (digit-character (charw string start-index)))
    (cond
      ((char=w digit-character #.%\-)
       (read-negative-long-from-string string (+f start-index 1) end-index))
      ((char=w digit-character #.%\+)
       (read-positive-long-from-string string (+f start-index 1) end-index))
      (t
       (read-positive-long-from-string string start-index end-index)))))

(def-gensym-c-function c-read_float_from_string
    (:double-float "g2ext_read_float_from_string")
  ((:string string)))


;;; `Read-float-from-string' ... String must be a text string, and
;;; inclusive-start-index and exclusive-final-index must be fixnum indexes
;;; between 0 and the length of the string.

(defun read-float-from-string
    (string inclusive-start-index exclusive-final-index)
  (let ((substring
          (obtain-simple-gensym-string
            (-f exclusive-final-index inclusive-start-index))))
    (copy-portion-of-wide-string-octets-into-simple-gensym-string
      string
      inclusive-start-index
      exclusive-final-index
      substring
      0)
    (prog1 (c-read_float_from_string substring)
      (reclaim-gensym-string substring))))

;;; (read-number-from-string #w"9.9e-306" 0 8)
;;; returns NIL, 0, "exponent of number is out of range"
;;; which is bogus.  This value shouldn't underflow.
;;; Compare e.g.  with  (tokenize-number-from-user #w"9.9e-306" 0 8)
;;; - jpg 6/30/00

(defconstant most-positive-fixnum-floor-2 (floorf most-positive-fixnum 2))

(defun read-number-from-string (string start-index end-index)
  (declare (eliminate-for-gsi))
  (let ((current-index 0)
        (managed-value? nil)
        (number-exists-p t))
    (declare (type fixnum current-index))
    (with-temporary-gensym-float-creation read-number-from-string
      (multiple-value-bind (whole-number exponent? end-index-of-mantissa)
          (read-number-without-exponent
            string start-index end-index 'gensym-float)
        (cond
          ((<=f end-index-of-mantissa start-index)
           (setq number-exists-p nil))
          (t
           (let* ((start-index-for-exponent (+f end-index-of-mantissa 1)))
             (declare (type fixnum start-index-for-exponent))
             (setq current-index end-index-of-mantissa)
             (when (and (<f start-index-for-exponent end-index)
                        (g2-exponent-marker-p
                          (charw string end-index-of-mantissa)))
               (multiple-value-bind (whole-number-for-exponent
                                      exponent-for-exponent end-index-of-exponent)
                   (read-number-without-exponent
                     string start-index-for-exponent end-index nil)
                 (setq
                   exponent?                               ; nil => probable overflow
                                        ; overflow imposs.
                   (cond ((=f end-index-of-exponent start-index-for-exponent)       ; nothing read
                          exponent?)                       ; eg. "12.03ex" -> don't read the "e"
                         ((and (=f exponent-for-exponent 0)
                               (<f (absf whole-number-for-exponent)
				   most-positive-fixnum-floor-2))
                          (setq current-index end-index-of-exponent)
                          (+f exponent? whole-number-for-exponent))
                         (t nil)))))               ; nil means
             (if (or (null exponent?)
                     (and (not (=f exponent? 0))      ; overflow probable
                          (>f (absf exponent?)
                              (floor (- #.(log most-positive-gensym-float 10)
                                        (log (+ (abs whole-number) 1) 10))))))
                 (setq managed-value? nil)
                 (if (and (=f exponent? 0)
                          (<= most-negative-fixnum whole-number)
                          (<= whole-number most-positive-fixnum))
                     (store-managed-number-or-value managed-value? whole-number)
                     (store-managed-number-or-value
                       managed-value?
                       (coerce-to-gensym-float
                         (read-float-from-string string start-index end-index))))))))))
    (if managed-value?
        (values managed-value? current-index nil)
        (values nil start-index
                (if number-exists-p
                    "exponent of number is out of range")))))




;;; The constant `maximum-length-of-g2-symbol-name' gives the maximum length of
;;; a symbol that will be read by the `read-symbol-from-string' function.


(defconstant maximum-length-of-g2-symbol-name 5000)




;;; The function `read-symbol-from-string' reads a simple G2 symbol of maximum length
;;; given by the constant maximum-length-of-g2-symbol-name.  G2 symbols are defined
;;; in CHARACTERS.

;; FIX FOR QUOTING CHARACTERS!

(defun read-symbol-from-string (string start-index end-index)
  (declare (eliminate-for-gsi))
  (let ((current-index start-index)
        (string-length-so-far 0)
        character
        string-to-intern)
    (setq string-to-intern
          (twith-output-to-text-string
            (if (<=f (-f end-index start-index)
                     maximum-length-of-g2-symbol-name)

                ;; Faster loop - without check for length
                (loop while (<f current-index end-index)
                      do (if (simple-symbol-character-p
                               (setq character (charw string current-index)))
                             (progn
                               (twrite-char (char-upcasew character))
                               (incff current-index))
                             (return)))

                ;; Slower loop - check for length of string
                (loop while (and (<f current-index end-index)
                                 (<=f string-length-so-far
                                      maximum-length-of-g2-symbol-name))
                      ;; Need the "=" in "<=f" above so that we can exceed
                      ;; the maximum length, to detect for error.
                      do (if (simple-symbol-character-p
                               (setq character (charw string current-index)))
                             (progn
                               (twrite-char (char-upcasew character))
                               (incff string-length-so-far)
                               (incff current-index))
                             (return))))))
    (cond
      ((>f string-length-so-far maximum-length-of-g2-symbol-name)
       (reclaim-text-string string-to-intern)
       (values nil current-index "symbol is too big"))
      ((=f current-index start-index)
       (reclaim-text-string string-to-intern)
       (values nil current-index nil))
      (t
       (let (managed-symbol)
         (store-managed-number-or-value managed-symbol
           (or (intern-text-string string-to-intern) :nil))
         (values managed-symbol current-index nil))))))





;;; The function `substring-equal' has the same functionallity as string-equal.
;;; However, it takes text-string string arguments, and requires the start and
;;; end indexes to be explicitly specified.  This way we can be sure that no key
;;; arguments, which might cause consing, need be used.  Also this function is
;;; as fast as it can be.  -pto 18oct88

(defun substring-equal (string-1 start-index-1 end-index-1
                        string-2 start-index-2 end-index-2)
  (declare (eliminate-for-gsi))
  (if (=f (-f end-index-1 start-index-1)
          (-f end-index-2 start-index-2))
      (loop with current-index-1 = start-index-1
            and current-index-2 = start-index-2
            while (<f current-index-1 end-index-1)
            do (if (not (char=w (char-upcasew (charw string-1 current-index-1))
                                (char-upcasew (charw string-2 current-index-2))))
                   (return nil))
               (incff current-index-1)
               (incff current-index-2)
            finally
              (return t))))




;;; The function `skip-spaces-in-string' returns the index of the first
;;; non-space character after start-index, before end-index.  Consider making
;;; this a macro.  -pto 13oct88


(defun-simple skip-spaces-in-string (string start-index end-index)
  (declare (eliminate-for-gsi))
  (loop while (and (<f start-index end-index)
                   (char=w (charw string start-index) #.%Space))
        do (incff start-index)
        finally
          (return start-index)))




;;; The function `skip-whitespace-in-string' returns the index of the first
;;; non-whitespace character after start-index, before end-index.

;; Modified so that a string of all whitespace does not cause an error.  It
;; returns the end-index.  cpm, 8/6/91.

(defun skip-whitespace-in-string (string start-index end-index)
  (declare (eliminate-for-gsi))
  (loop with char
        while (<f start-index end-index)
        do (setq char (charw string start-index))
           (cond
             ((blank-p char)
              (incff start-index))
             (t (loop-finish)))
        finally
          (return start-index)))




;;; The function `read-truth-value-from-string' reads a truth value if the form
;;; of <number_between_one_and_minus_one><zero_or_more_spaces>true | true |
;;; false.


(defun read-truth-value-from-string (string start-index end-index)
  (declare (eliminate-for-gsi))
  (let ((length-of-rest-of-string (-f end-index start-index))
        (certainty nil)
        (error-message nil)
        (managed-certainty nil))
    (cond ((<f length-of-rest-of-string 4)
           (values nil start-index nil))
          ((substring-equal string start-index (+f start-index 4)
                            #w"TRUE" 0 4)
           (store-managed-number-or-value managed-certainty truth)
           (values managed-certainty (+f start-index 4) nil))
          ((substring-equal string  start-index (+f start-index 5)
                            #w"FALSE" 0 5)
           (store-managed-number-or-value managed-certainty falsity)
           (values managed-certainty (+f start-index 5) nil))
          (t                                        ;<number><spaces><true>
           (multiple-value-bind (certainty? current-index ignored-message?)
               (read-number-from-string string start-index end-index)
             (declare (ignore ignored-message?))
             (with-temporary-gensym-float-creation
               read-truth-value-from-string
               (cond
                 ((null certainty?) (values nil start-index nil))
                 (t
                  (setq certainty
                        (round (* 1000 (extract-number-or-value certainty?))))
                  (reclaim-managed-number-or-value certainty?)
                  (setq current-index
                        (skip-spaces-in-string string current-index end-index))
                  (cond
                    ((<f (-f end-index current-index) 4)
                      (setq current-index start-index))
                    ((not (substring-equal string current-index (+f current-index 4)
                                           #w"TRUE" 0 4))
                     (setq current-index start-index))
                    ((> certainty truth)
                     (setq error-message
                           #w"certainty factor of truth value is greater than 1"))
                    ((< certainty falsity)
                     (setq error-message
                           #w"certainty factor of truth value is less than -1"))
                    (t
                     (store-managed-number-or-value managed-certainty certainty)
                     (setq current-index (+f current-index 4)))))))
             (values managed-certainty current-index error-message))))))





;;; The macro `read-text-string-ending-in-a-delimitter-from-string' takes a
;;; string, a start-index, an end-index, and a character which is a delimitter,
;;; reads the string until it reads the delimitter character, and returns (1)
;;; all a string with all the characters read until just before the delimitter
;;; or the end of the string, (2) the index of the position of the character
;;; after the last character read, and (3) a flag indicating whether the string
;;; ended without the delimitter.


(defun read-text-string-ending-in-a-delimitter-from-string
    (string start-index end-index delimitter)
  (let* ((current-index start-index)
         string-ends-in-delimitter-p
         (text-string
           (twith-output-to-text-string
             (setq string-ends-in-delimitter-p
                   (loop with character
                         while (<f current-index end-index)
                         do (if (char=w
                                  (setq character (charw string current-index))
                                  delimitter)
                                (return t))
                            (incff current-index)
                            (twrite-char character)
                         finally (return nil))))))
    (values text-string current-index string-ends-in-delimitter-p)))




;;; The function `read-text-string-from-string' reads a string, starting with
;;; the first character after the double quote (") at position start-index, and
;;; reads everything until the next double quote.  If no second double quoute is
;;; encountered, we an error is assumed.


(defun read-text-string-from-string (string start-index end-index)
  (declare (eliminate-for-gsi))
  (if (char=w (charw string start-index) #.%\")
      (let ((current-index (+f start-index 1))
            string-in-string
            string-is-ok-p
            managed-string)
        (multiple-value-setq (string-in-string current-index string-is-ok-p)
          (read-text-string-ending-in-a-delimitter-from-string
            string current-index end-index #.%\"))
        (cond
          (string-is-ok-p
           (store-managed-number-or-value managed-string string-in-string)
           (reclaim-text-string string-in-string)
           (values managed-string current-index nil))
          (t
           (reclaim-text-string string-in-string)
           (values nil start-index nil))))
      (values nil start-index nil)))




;;; The function `read-three-letter-month-from-string' reads a three letter
;;; month from string, a text string, starting at start-index, and returns the
;;; number corresponding to the month or nil.  This is a non-conventional
;;; read-from-string function.

(defun read-three-letter-month-from-string (string start-index end-index)
  (declare (eliminate-for-gsi))
  (let ((limit (+f start-index 3)))
    (cond
      ((>f limit end-index) nil)
      (t (loop for month
                   in '#.(strings-to-text-strings-in-list
                           '("Jan" "Feb" "Mar" "Apr" "May" "Jun"
                             "Jul" "Aug" "Sep" "Oct" "Nov" "Dec"))
               as i from 1
               when (substring-equal string start-index limit month 0 3)
                 return i)))))




;;; The function `read-date-from-string' reads a date in the form dd mmm yyyy
;;; from the string starting at position start-index.  The values returned are
;;; day, month, year, position at end of read of date, and an error message if
;;; applicable.  If day is nil, then there was either an error or there was no
;;; date in the string.  This function doesn't check if there exist the actual
;;; time.  For example, 31 Feb 9999 is accepted as a legal date.

(defun read-date-from-string (string start-index end-index)
  (declare (eliminate-for-gsi))
  (loop with month                                ; No looping, really.
        and current-index = start-index                ; just using convenient return
        do
    (if (>=f (-f end-index start-index) 10)
        (multiple-value-bind (day end-index-of-day ignored-message?)
            (read-positive-fixnum-from-string string current-index
                                              (+f current-index 2))
          (declare (ignore ignored-message?))
          (when day                                        ; DAY
            (setq current-index
                  (skip-spaces-in-string string end-index-of-day end-index))
            (setq month
                  (read-three-letter-month-from-string string current-index
                                                       end-index))
            (when month                                                ; MONTH
              (setq current-index
                    (skip-spaces-in-string string
                                           (+f current-index 3) end-index))
              (multiple-value-bind (year end-index-of-year
                                    ignored-message?)
                  (read-positive-fixnum-from-string
                    string current-index (+f current-index 4))
                (declare (ignore ignored-message?))
                (when (and year                                        ; YEAR
                           (=f end-index-of-year (+f current-index 4)))
                  (return (values day month year end-index-of-year nil))))))))
          (return (values nil nil nil start-index nil))))




;;; The function `read-time-from-string' reads a time in the format [h]h:mm:ss
;;; [a.m. | p.m.] and returns hours, minutes, seconds, position after the read,
;;; and and error message (non-reclaimable) if applicable.  Examples of legal
;;; times:  "9:00:29", "20:59:10", "12:20:00  a.m.", "24:00:00".  Examples of
;;; illegal times:  "19:20:40 p.m.", "19:20:40  a.m.", "7:59:60", "7:59:9".

;;; Note that as of version 4.0, the seconds return value can be a
;;; managed-number.  This is necessary to read subsecond times, such as
;;; "9:00:29.5".  This managed-number should be reclaimed or held onto by the
;;; caller.

(defun read-time-from-string (string start-index end-index)
  (declare (eliminate-for-gsi))
  (loop with current-index = start-index
        do
    (if (>=f (-f end-index start-index) 7)
        (multiple-value-bind (hours end-index-of-hours ignored-message?)
            (read-positive-fixnum-from-string string current-index
                                              (+f current-index 2))
          (declare (ignore ignored-message?))
          (when (and hours (<=f hours 24)                        ; HOURS
                     (char=w (charw string end-index-of-hours) #.%\:))
            (setq current-index (+f end-index-of-hours 1))
            (multiple-value-bind (minutes end-index-of-minutes ignored-message?)
                (read-positive-fixnum-from-string string current-index
                                                  (+f current-index 2))
              (declare (ignore ignored-message?))
            (when (and minutes (<=f minutes 59)                        ; MINUTES
                       (=f (-f end-index-of-minutes current-index) 2)
                       (char=w (charw string end-index-of-minutes) #.%\:))
              (setq current-index (+f end-index-of-minutes 1))
              (multiple-value-bind (seconds end-index-of-seconds
                                    ignored-message?)
                  (read-number-from-string string current-index end-index)
                (declare (ignore ignored-message?))
                (let ((valid-seconds?
                        (when seconds
                          (cond
                             ((fixnump seconds)
                              (and (<=f seconds 59)  ; SECONDS
                                   (=f (-f end-index-of-seconds current-index)
                                       2)))
                             ((managed-float-p seconds)
                              (with-temporary-gensym-float-creation
                                  read-time-from-string
                                (and (<e (managed-float-value seconds) 60.0d0)
                                     (>=f (-f end-index-of-seconds
                                              current-index)
                                          4))))
                             (t nil))))) ; At least "nn.n" long.
                  (when valid-seconds?
                    (setq current-index
                          (skip-spaces-in-string
                            string end-index-of-seconds end-index))
                    (if (=f hours 24) (setq hours 0))
                    (cond
                      ((<f (-f end-index current-index) 4)
                       (return
                         (values hours minutes seconds end-index-of-seconds
                                 nil)))
                      ((substring-equal
                         string current-index (+f current-index 4)
                         #w"A.M." 0 4)
                       (when (and (>f hours 0) (<=f hours 12))
                         (if (=f hours 12) (setq hours 0))
                         (return (values hours minutes seconds
                                         (+f current-index 4) nil))))
                      ((substring-equal
                         string current-index (+f current-index 4)
                         #w"P.M." 0 4)
                       (when (and (>f hours 0) (<=f hours 12))
                         (if (/=f hours 12) (setq hours (+f hours 12)))
                         (return (values hours minutes seconds
                                         (+f current-index 4) nil))))
                      (t
                       (return (values hours minutes seconds
                                       end-index-of-seconds nil))))))))))))
    (return (values nil nil nil start-index nil))))




;;; The function `read-time-stamp-from-string' reads a time stamp of the format:
;;; dd mmm yyyy hh:mm:ss[.<subsecond>] [a.m. | p.m.].  This function returns the
;;; values: seconds, minutes, hours, day, month, year, (2), and (3).

;;; Only one of the returned values, the seconds, may be a managed number.  If
;;; seconds is nil, then no time stamp was read.  In this function, I will
;;; assume that a managed fixnum is just the fixnum itself.  I.e. when
;;; read-positive-fixnum-from-string returns a number, we assume that the
;;; managed number returned is just a fixnum and do not perform an
;;; extract-number-or-value to access the number.

;;; Note that as of version 4.0, the seconds return value can be a
;;; managed-number.  This is necessary to read subsecond times, such as
;;; "9:00:29.5".  This managed-number should be reclaimed or held onto by the
;;; caller.

(defun read-time-stamp-from-string (string start-index end-index)
  (declare (eliminate-for-gsi))
  (when (>=f (-f end-index start-index) 18)
    (multiple-value-bind (day month year end-index-of-date ignored-message?)
        (read-date-from-string string start-index end-index)
      (declare (ignore ignored-message?))
      (when day
        (setq end-index-of-date
              (skip-spaces-in-string string end-index-of-date end-index))
        (multiple-value-bind (hours minutes seconds
                                    end-index-of-time ignored-message?)
            (read-time-from-string string end-index-of-date end-index)
          (declare (ignore ignored-message?))
          (if hours
              (return-from read-time-stamp-from-string
                (values seconds minutes hours day month year
                        end-index-of-time nil)))))))
  (values nil nil nil nil nil nil start-index nil))





;;;; Random Number Generator



;;; From Knuth, Vol. 2, Semi-numerical Algorithms, pp 26-27.
;;; The algorithm for generating a pseudo random series after being given
;;; terms 0 through 54 as a starter is:
;;;
;;;     X(n) = (X(n-24) + X(n-55)) mod 2^e     for n>=55

;;; The subscripts 24 and 55 are important and not chosen randomly.
;;; Provided that the initial series has at least 1 odd number, the period
;;; is guaranteed to be at least 2^55 - 1, and almost certainly much larger.
;;; The algorithm is fast and "may prove to be the very best source of random numbers.
;;; The only reason it is difficult to recommend [it] wholeheartledly is that there
;;; is still little theory to prove that it does or does not not have desirable
;;; randomness properties." However, the algorithm has been around since 1958
;;; when it was invented by G.J. Mitchell and D.P. Moore, and it "has consistently
;;; produced reliable results in extensive tests since its invention."

;;; In this implementation, e = 23. This number was chosen so that all numbers
;;; stored in arrays are less than half of most-positive-fixnum on all g2
;;; implementations, and in particular on Explorers. When two of these numbers are
;;; added in generate-large-random, the result is a fixnum. Number size
;;; is uniform across implementations so that the algorithm generates repeatable
;;; results across all implementations. (The Common Lisp random number generator is only
;;; repeatable within an implementation.)

;(defconstant large-power (expt 2 23))
(defconstant large-mask (1- (expt 2 23)))

;; large mask is referenced in file PROTECTION.
(defconstant large-shift 23)

;; NOTE: they cannot be def-system-variable any more.
(defvar *random-state-array* nil)
(defvar *random-state-array-current-pointer* 54)
(defvar *random-state-array-24-pointer* 24)

(defconstant random-seed-0 6460045)
(defconstant random-seed-1 4757733)
(defconstant random-seed-2 6397164)
(defconstant random-seed-3 7884262)


;;; Reset-g2-random-state creates the random state the first time it is
;;; called, and resets it thereafter. After being reset, the function g2-random
;;; called with a fixnum argument meets the specification of Common Lisp random,
;;; and furthermore provides identical behavior on all implementations of G2.

(defvar random-variation 0)

;;; A second random variation is needed to cover the 55 element
;;; *random-state-array*.  Using only one random variation only
;;; covers 42 of the 55 elements, i.e. 13 of the elements were
;;; never changed! - jpg 2/28/01

(defvar random-variation-2 0)


;;; The parameter `user-random-seed?' is either nil or a
;;; non-negative fixnum.  It can be bound to non-nil only
;;; within a call to the system procedure `g2-set-random-seed'.
;;; - jpg 3/4/03

(defvar user-random-seed? nil)


(defun reset-g2-random-state (non-deterministic?)
  (declare (eliminate-for-gsi))
  (unless *random-state-array*
    (setq *random-state-array*
          (with-permanent-array-creation
            (make-array 55 :element-type 'fixnum))))
  (setf (aref *random-state-array* 0) random-seed-0)
  (setf (aref *random-state-array* 1) random-seed-1)
  (setf (aref *random-state-array* 2) random-seed-2)
  (setf (aref *random-state-array* 3) random-seed-3)
  (loop for i from 4 to 54 doing
       (setf (aref *random-state-array* i) (*f i 103)))
  (setq *random-state-array-current-pointer* 54)
  (setq *random-state-array-24-pointer* 30)

  (when non-deterministic?
      (setq random-variation
            ;; `user-random-seed?' is bound to non-nil, a
            ;; fixnum, only within a call to the system
            ;; procedure `g2-set-random-seed'. - jpg 3/4/03
            (or user-random-seed? (get-fixnum-time)))
      (setq random-variation-2 (1-f random-variation)))

  (setf (aref *random-state-array* 4) random-variation)
  (setf (aref *random-state-array* 5) random-variation-2)

  (loop for i from 0 to 1000 doing (generate-large-random)))

(defun generate-large-random ()
  (declare (eliminate-for-gsi))
  (let ((current-pointer *random-state-array-current-pointer*)
        (24-pointer *random-state-array-24-pointer*))
    (incff current-pointer)
    (if (=f current-pointer 55) (setq current-pointer 0))
    (setq *random-state-array-current-pointer* current-pointer)
    (incff 24-pointer)
    (if (=f 24-pointer 55) (setq 24-pointer 0))
    (setq *random-state-array-24-pointer* 24-pointer)

    (setf (aref *random-state-array* current-pointer)
          (logandf large-mask (+f (aref *random-state-array* current-pointer)
                                  (aref *random-state-array* 24-pointer))))))

#+skip-list
(reset-g2-random-state nil)

;;; G2-random generates a random number between 0 and n-1. The argument must be
;;; a fixnum. It works by taking the residue mod n of a number which is 46 bits
;;; long. Even with quite large fixnums, the distribution should be almost uniform
;;; because this number is considerably larger than fixnums on all implementations.
;;; The large number is concatenated from two 23 bit random numbers generated by
;;; generate-large-random. By using modulo arithmetic throughout, bignums are avoided.
;;; G2-random should not cons on any implementation.

;(defun g2-random (n)
;  (with-temporary-bignum-creation
;    (modf (+f (modf (generate-large-random) n)
;              ;; The following is a fixnum, but its first argument may be a bignum.
;              (mod (* (modf large-power n) (modf (generate-large-random) n)) n))
;          n)))






;; New implementation does not use bignums. It generates random numbers
;; of a size sufficient to mask the argument n. It discards the random number
;; if it greater than the largest multiple of n that is within the mask
;; size of the generated random. (It discards less than half of the generated randoms).
;; This assures even distributions. If it does not succeed in 30 tries, it
;; uses the number any way (the worse consequence is a biased distribution of
;; random numbers. In development mode, it prints a warning message. The worse
;; case should produce a message every billion tries. For samller values of n,
;; this should be even rarer. This algorithm is machine independent for n <=
;; 2^23.

(defun g2-random (n)
  (declare (eliminate-for-gsi))
  (if (<=f n large-mask)
      (loop with lim = (*f n (floorf large-mask n))
            for i from 1 to 30
            for rand = (generate-large-random)
            doing
        (if (<=f rand lim) (return (modf rand n)))
            finally
              (return (modf rand n)))

      (loop with shift and new-mask and lim
            for i from 1 to 30
            ;; This iterator depends on values computed in the initial code.
            for rand = (logxor (generate-large-random)
                               (ashf (generate-large-random) shift))

            initially
              ;; The purpose of this loop is to find the smallest mask
              ;; (number which is all 1's in binary) that covers n.
              ;; Since n is a fixnum, this will also be a fixnum.
              ;; Shift is the amount of left shifting of a random to
              ;; "cover" n.
              (loop for j from 0
                    for mask = large-mask then (+f 1 (ashf mask 1))
                    until (>=f mask n)
                    finally
                      (setq shift j)
                      (setq new-mask mask))
              (setq lim (*f n (floorf new-mask n)))
            doing
        (if (<=f rand lim) (return (modf rand n)))
            finally
              (return (modf rand n)))))








;;; Note on installation:

;;; reset-g2-random-state resets the state of the random number generator.
;;; It should be called upon G2 start, and earlier if g2-random is to be
;;; used other than while system is running.

;;; It makes use of a seed consisting of 5 random numbers of size less than
;;; ranom-mask. These 5 numbers are placed in the state array of the random
;;; number generator, and other numbers are added deterministically, so that
;;; there will be many odd numbers in the array. The algorithm is then
;;; exercised 1000 times which ranomizes the rest of the array.

;;; Consider a command for creating a new random seed.





;; Moved avoiding-variable-capture to UTILITIES2 because of a bug in macrolet.  A
;; local macroexpander generated by macrolet cannot use a global macro defined in
;; the same file as the macrolet to perform its macroexpansion.  Global macros
;; have no trouble seeing each other.  jh, 10/18/90.





;;; Declaring Ignorable Variables in Macroexpansions

;; jh, 10/11/90

;;; ignoring-variables-appropriately
;;; possibly-ignorable-variables implicit-progn-body

;;; The macro ignoring-variables-appropriately is used in cases where a
;;; macroexpander may encounter ignorable variables but has no way of knowing this
;;; for sure until macroexpansion time.  Possibly-ignorable-variables is an
;;; unevaluated list of variables which may or may not appear in the lexical scope
;;; of implicit-progn-body, which is evaluated.  If any variables do not appear,
;;; ignore declarations are created and placed at the front of
;;; implicit-progn-body.  Ignoring-variables-appropriately can only be wrapped
;;; around a form that will return an implicit progn (a list of forms).  This
;;; implicit progn is to be inserted into the body of a special form that admits
;;; declarations.

;;; example:
;;;
;;;(defmacro disturb-the-compiler ()
;;;  `(defun compiler-is-disturbed (a b)
;;;     (list a)))
;;;
;;; When the form (disturb-the-compiler) is compiled, the compiler prints a
;;; warning message along the lines of "Variable B is bound but never used".
;;;
;;;(defmacro please-the-compiler ()
;;;  `(defun compiler-is-pleased (a b)
;;;     ,@(ignoring-variables-appropriately (a b)
;;;         `((list a)))))
;;;
;;; When the form (please-the-compiler) is compiled, the compiler prints no
;;; warning message.



(defmacro ignoring-variables-appropriately
          (possibly-ignorable-variables implicit-progn-body)
  (avoiding-variable-capture (implicit-progn-body)
    `(let ((variables ',possibly-ignorable-variables))
       (labels ((search-for-ignorable-variables (body)
                 (cond ((null variables) nil)
                       ((null body) nil)
                       ((stringp body) nil)
                       ((not (consp body))
                        (when (memq body variables)
                          (setq variables
                                (remove body
                                        variables))))
                       (t (search-for-ignorable-variables
                             (car body))
                          (search-for-ignorable-variables
                             (cdr body))))))
         (search-for-ignorable-variables ,implicit-progn-body)
         (if variables
             `((declare (ignore ,@variables))
               ,@,implicit-progn-body)
             ,implicit-progn-body)))))





;;; Removing Unnecessary Macroexpansion Code

;;; jh, 10/18/90.

;;; The idea is to walk through a form at macroexpansion time and collapse any
;;; subforms which we can already evaluate.  We do this by executing beforehand a
;;; declare-condensable-form for common special forms like if and case.  This
;;; declaration indicates under what conditions a form can be collapsed (a progn
;;; with one subform, for example, or an if whose test is known to be true at
;;; compile time).  As well, the user can specify side-effect-free functions which
;;; condensing-superfluous-subforms can use to try to determine the value of a
;;; form at macroexpansion time.  Using these two techniques, the macroexpander
;;; inside a condensing-superfluous-subforms scope often can determine when a
;;; subform can be collapsed, leading to more perspicuous and economical
;;; macroexpanded code.

;;; Examples:
;;;
;;;(declare-condensable-form and (&rest clauses)
;;;  (loop-through-form for clause in clauses
;;;        with every-clause-known-true-p = t
;;;     when (known-false-p clause)
;;;          do (collapse 'nil)
;;;        when (and every-clause-known-true-p
;;;                  (last-subform-p))
;;;          do (if (known-false-p clause)
;;;                 (collapse 'nil)
;;;                 (collapse clause))
;;;        when (known-true-p clause)
;;;          do (omit)
;;;        when (unknown-p clause)
;;;          do (setq every-clause-known-true-p nil)
;;;        collect clause))
;;;CONDENSE-SUPERFLUOUS-SUBFORMS-IN-AND
;;;
;;;(defmacro condensing-and (&rest clauses)
;;;  (condensing-superfluous-subforms (numberp)
;;;    `(and ,@clauses)))
;;;CONDENSING-AND
;;;
;;;(macroexpand-1
;;;  '(condensing-and first-clause (numberp 'not-a-number) fourth-clause))
;;;NIL
;;;
;;;(macroexpand-1
;;;  '(condensing-and (numberp 1) (numberp 2)))
;;;T
;;;
;;;(macroexpand-1
;;;  '(condensing-and (numberp 1) (numberp x)))
;;;(NUMBERP X)
;;;
;;;(macroexpand-1
;;;  '(condensing-and (numberp 'not-a-number) (numberp "Neither am I.")))
;;;NIL
;;;
;;;
;;;(macroexpand-1
;;;  '(condensing-and first-clause (not (numberp (numberp 1))) third-clause))
;;;(AND FIRST-CLAUSE (NOT NIL) THIRD-CLAUSE)
;;;
;;;(declare-condensable-form not (thing)
;;;  (cond ((known-true-p thing) (collapse nil))
;;;        ((known-false-p thing) (collapse t))
;;;              ((unknown-p thing) (original-form))))
;;;CONDENSE-SUPERFLUOUS-SUBFORMS-IN-NOT
;;;
;;;(macroexpand-1
;;;  '(condensing-and first-clause (not (numberp (numberp 1))) third-clause))
;;;(AND FIRST-CLAUSE THIRD-CLAUSE)



;;; declare-condensable-form
;;;   <special-form-name> &rest <body>

;;; Several new local macros exist in the scope of a declare-condensable-form:

;;; (loop-through-form ...)  like loop but includes the following local macros:
;;; (original-form)          the form being walked
;;; (omit)                   don't include clause in result
;;; (collapse <form>)        discard result being built and just use <form>
;;; (last-subform-p)         true if we are at the last clause
;;; (unknown-p <form>)       value of <form> is unknown at expansion time
;;; (known-false-p <form>)   value of <form> is known false at expansion time
;;; (known-true-p <form>)    value of <form> is known true at expansion time
;;; (known-value <form>)     extracts the value from quoted forms and the like

;;; The above local macros may be used outside the scope of a loop-through-form,
;;; but not (of course) globally.  Omit will have no effect.

;;  - implementation -
;;
;; collapse
;;   wrap block with <tag> and substitute
;;   do (return-from <tag> form)
;;
;; last-subform-p
;;   if encounter (loop ... for <x> in <y> ...)
;;   change to (loop ... for <x> in <y> for <x'> on y ...)
;;   (last-subform-p) then expands to (null (cdr <x'>))
;;
;; omit
;;   if encounter (loop ... collect <x> ...)
;;   change to (loop with <flag> = t ... if <flag> collect <x> ... )
;;   (omit) then expands to (setq <flag> nil)
;;
;; loop-through-form
;;   (loop for <clause> in <clauses>
;;         ...
;;         collect <clause>)
;;     should be replaced with
;;   (loop with <omit-flag> = t then t
;;         for <clause> in <clauses>
;;         for <clause-sublist> on <clauses>
;;         ...
;;         when <omit-flag> collect <clause>)




;;; condensing-superfluous-subforms
;;;   <functions-to-try-at-macroexpansion-time> <form-to-examine>

;;; <Functions-to-try-at-macroexpansion-time> is an unevaluated list of function
;;; names which should exist at compile time and be side-effect-free at run time.

;;; <Form-to-examine> is the form whose unnecessary expansion code is to be pruned.

;;; Note that condensing-superfluous-subforms does more than simply check for ts
;;; and nils.  If a function name appears in
;;; <functions-to-try-at-macroexpansion-time> and its arguments are constant, then
;;; condensing-superfluous-subforms tries to evaluate the function.  This check
;;; occurs in the actual macro, so the declare-condensable-form expansion only has
;;; to check for base cases: t, nil, and self-evaluating objects like strings and
;;; numbers.



#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(defvar declare-condensable-form-registry nil)
)



(defmacro collapse-condensable-form (form implicit-progn-p collapse-tag)
  (avoiding-variable-capture (form)
    `(return-from
       ,collapse-tag
       ,(if implicit-progn-p
            `(cond ((and (consp ,form)
                         (= (length ,form) 1))
                    (car ,form))
                   ((consp ,form)
                    (cons 'progn ,form))
                   (t ,form))
            form))))

(defmacro known-false-condensable-form-p (form)
  (avoiding-variable-capture (form)
    `(or (null ,form)
         (equal ,form '(quote nil))
         )))

(defmacro known-true-condensable-form-p (form)
  (avoiding-variable-capture (form)
    `(or (eq t ,form)
         (numberp ,form)
         (stringp ,form)
         (and (consp ,form)
              (eq (car ,form) 'quote)
              (not (eq (cadr ,form) nil)))
         )))

(defmacro known-condensable-form-value (form)
  (avoiding-variable-capture (form)
    `(if (and (consp ,form)
              (eq (car ,form) 'quote))
         (cadr ,form)
         ,form)))

(defmacro condensable-form-neither-true-nor-false-p (form)
  (avoiding-variable-capture (form)
    `(and (not (known-false-p ,form))
          (not (known-true-p ,form)))))

(defmacro last-condensable-subform-p (hidden-sublist-var)
  `(null (cdr ,hidden-sublist-var)))

(defmacro loop-through-condensable-form
          (hidden-sublist-var collect-p-var &rest loop-forms)
  (let ((collect-encountered-p
          (memq 'collect loop-forms)))
    `(cons (car (original-form))
           ;; Inner macrolet allows us to restrict references
           ;; to collect-p.  Otherwise, we get "setq'd but not used"
           ;; complaints from the symbolics compiler.  jh, 12/28/90.
           (macrolet ((omit ()
                        ,(if collect-encountered-p
                             ``(setq ,',collect-p-var nil)
                             nil)))
             ,(loop for loop-form in `(loop ,@loop-forms)
                    for loop-sublist on `(loop ,@loop-forms)
                    with clauses-variable = nil
                    with loop-segment = nil
                    with added-hidden-sublist-p = nil
                    do
                    (cond ((and (not added-hidden-sublist-p)
                                (eq (second loop-sublist)
                                    'for)
                                (eq (fourth loop-sublist)
                                    'in))
                           (setq clauses-variable
                                 (fifth loop-sublist)
                                 added-hidden-sublist-p
                                 t
                                 loop-segment
                                 (if collect-encountered-p
                                     `(,loop-form
                                       for ,hidden-sublist-var
                                       on ,clauses-variable
                                       for ,collect-p-var = t)
                                     `(,loop-form
                                       for ,hidden-sublist-var
                                       on ,clauses-variable))))
                          ((eq (cadr loop-sublist) 'collect)
                           (setq loop-segment
                                 `(,loop-form when
                                   ,collect-p-var)))
                          (t (setq loop-segment
                                   (list loop-form))))
                    append loop-segment)))))



(defmacro declare-condensable-form (condensable arglist &rest body)
  (let ((name-for-condenser
          (intern
            (format nil "CONDENSE-SUPERFLUOUS-SUBFORMS-IN-~a"
                    condensable))))
    (avoiding-variable-capture
        (&aux collapse-tag collect-p hidden-sublist)
      (let ((fn-def
              `(defun-for-macro ,name-for-condenser
                   (expression ,@arglist)
                 (macrolet ((collapse (form &key implicit-progn-p)
                              `(collapse-condensable-form
                                 ,form
                                 ,implicit-progn-p
                                 ,',collapse-tag))
                            (known-false-p (form)
                              `(known-false-condensable-form-p
                                 ,form))
                            (known-true-p (form)
                              `(known-true-condensable-form-p
                                 ,form))
                            (known-value (form)
                              `(known-condensable-form-value ,form))
                            (unknown-p (form)
                              `(condensable-form-neither-true-nor-false-p
                                 ,form))
                            (last-subform-p ()
                              `(last-condensable-subform-p
                                 ,',hidden-sublist))
                            (omit () ;a no-op outside of loop-through-form
                              nil)
                            (loop-through-form (&rest loop-forms)
                              `(loop-through-condensable-form
                                 ,',hidden-sublist
                                 ,',collect-p
                                 ,@loop-forms))
                            (original-form ()
                              `expression))
                   (block ,collapse-tag
                     ,@body)))))
        (unless (eval-feature :no-macros)
          `(eval-when (:compile-toplevel :load-toplevel :execute)
             ,fn-def

             (pushnew (cons ',condensable ',name-for-condenser)
                      declare-condensable-form-registry
                      :test #'equal)))))))






(declare-condensable-form progn (&rest subforms)
  (case (length subforms)
    (0 nil)
    (1 (car subforms))
    (otherwise (original-form))))

(declare-condensable-form let (specs &rest body)
  (if (null specs)
      (case (length body)
        (0 nil)
        (1 (car body))
        (otherwise (cons 'progn body)))
      (case (length body)
        (0 nil)
        (1 (if (eq (caar body) 'progn)
               (cons 'let (cons specs (cdar body)))
               (original-form)))
        (otherwise (original-form)))))


(declare-condensable-form let* (specs &rest body)
  (if (null specs)
      (case (length body)
        (0 nil)
        (1 (car body))
        (otherwise (cons 'progn body)))
      (case (length body)
        (0 nil)
        (1 (if (eq (caar body) 'progn)
               (cons 'let* (cons specs (cdar body)))
               (original-form)))
        (otherwise (original-form)))))


(declare-condensable-form not (thing)
  (cond ((known-true-p thing) (collapse nil))
        ((known-false-p thing) (collapse t))
        ((unknown-p thing) (original-form))))


(declare-condensable-form if (test then &optional else)
  (cond ((known-true-p test) (collapse then))
        ((known-false-p test) (collapse else))
        ((unknown-p test) (original-form))))


(declare-condensable-form and (&rest clauses)
  (loop-through-form for clause in clauses
        with every-clause-known-true-p = t
        when (known-false-p clause)
          do (collapse 'nil)
        when (and every-clause-known-true-p
                  (last-subform-p))
          do (if (known-false-p clause)
                 (collapse 'nil)
                 (collapse clause))
        when (known-true-p clause)
          do (omit)
        when (unknown-p clause)
          do (setq every-clause-known-true-p nil)
        collect clause))

(declare-condensable-form or (&rest clauses)
  (loop-through-form for clause in clauses
        with every-clause-known-false-p = t
        when (known-true-p clause)
          do (collapse clause)
        when (and every-clause-known-false-p
                  (last-subform-p))
          do (if (known-false-p clause)
                 (collapse 'nil)
                 (collapse clause))
        when (known-false-p clause)
          do (omit)
        when (unknown-p clause)
          do (setq every-clause-known-false-p nil)
        collect clause))

(declare-condensable-form case (keyform &rest clauses)
  (if (unknown-p keyform)
      (original-form)
      (let ((known-keyform
              (known-value keyform)))
        (loop-through-form for (keys . actions) in clauses
              when (memq keys '(otherwise t))
                do (collapse actions :implicit-progn-p t)
              if (if (consp keys)
                     (memq known-keyform keys)
                     (eq known-keyform keys))
                 do (collapse actions :implicit-progn-p t)
              else
                 do (omit)
              finally (return nil)))))


(declare-condensable-form cond (&rest clauses)
  (loop-through-form for clause in clauses
        for (pred . actions) in clauses
        with all-preds-known-p = t
        when (known-false-p pred)
          do (omit)
        when (and all-preds-known-p
                  (known-true-p pred))
          do (collapse actions :implicit-progn-p t)
        when (unknown-p pred)
          do (setq all-preds-known-p nil)
        collect clause))


;; The expander for condensing-superfluous-subforms uses continuations to rebuild
;; form-to-examine "from the inside out".  This way, if a more deeply-nested
;; subform is of known value, that can contribute to pruning less deeply-nested
;; subforms.  The local function condense-and-recurse performs the actual check on
;; the subform.  If the head of the subform is a symbol mentioned by a
;; declare-condensable-form or a function name from
;; functions-to-try-at-macroexpansion-time, an attempt will be made to eliminate
;; dead branches or replace the subform with the result of evaluating it at
;; runtime, if that can be determined.  Note that the continuations generate
;; garbage at macroexpansion time, not at runtime.

(defmacro condensing-superfluous-subforms
          (functions-to-try-at-macroexpansion-time form-to-examine)
  (avoiding-variable-capture (form-to-examine)
    `(flet ((condense-and-recurse (head tail continuation)
              (let ((condensing-function
                      (cdr (assoc head
                                  declare-condensable-form-registry))))
                (if condensing-function
                    (funcall continuation
                             (apply condensing-function
                                    (cons head tail)
                                    tail))
                    (if (and (symbolp head)
                             (memq head
                                   ',functions-to-try-at-macroexpansion-time)
                             (every #'constantp tail))
                        (funcall continuation
                                 (apply head tail))
                        (funcall continuation
                                 (cons head tail)))))))
       (labels ((rebuild-car (tree car-continuation)
                  (if (not (consp tree))
                      (funcall car-continuation tree)
                      (rebuild-car
                        (car tree)
                        #'(lambda (head)
                            (rebuild-cdr
                              (cdr tree)
                              #'(lambda (tail)
                                  (condense-and-recurse
                                    head
                                    tail
                                    car-continuation)))))))
                (rebuild-cdr (tree cdr-continuation)
                  (if (not (consp tree))
                      (funcall cdr-continuation tree)
                      (rebuild-cdr
                        (cdr tree)
                        #'(lambda (tail)
                            (rebuild-car
                              (car tree)
                              #'(lambda (head)
                                  (condense-and-recurse
                                    head
                                    tail
                                    cdr-continuation))))))))
         (rebuild-car ,form-to-examine #'identity)))))




;;;; Run-time Version Checking

;; (jh, 3/23/90)

;;; With the advent of network-based Gensym products comes a need for `run-time
;;; version checking'.  The motivating case here is GSI, for which extension
;;; processes exist which will crash if they receive ICP messages from the GSI 2.0
;;; code.  Since a G2 can communicate with more than one GSI extension process,
;;; and since that communication is opened while G2 is running, version data has
;;; to be acquired at run-time and stored in a `version registry'.  Then a
;;; `with-appropriate-version' wrapper will declare a minimum version number
;;; necessary to execute the code within its scope.

;;; Note that run-time `version checking' is distinct from compile-time version
;;; checking.  This machinery is based in the bootstrap module and is designed to
;;; assure that a G2 system is formed from a consistent and up-to-date set of
;;; modules.  We might want to consolidate the two systems someday, at least to
;;; the extent of incorporating knowledge about the local module versions, which
;;; can be known at compile time.

;;; The programmer must take the following steps when designing version-dependent
;;; code: declare how version data is to be stored, arrange for version data to be
;;; acquired, sequester the version-dependent sections of the program, and reclaim
;;; storage in the version registry when no longer needed.  The following
;;; describes these steps in detail.

;;; 1> Declare how version data is to be stored.  This is necessary because in
;;; some cases version data must be associated with many instances of a module,
;;; each of which can have a different version.  The prime example again is GSI,
;;; where multiple extension processes can be running, each with a different
;;; version.  Therefore, version data must be stored for each extension process.
;;; This is done at compile-time, using the macro `def-version-registry-format'.
;;; This macro takes two unevaluated subforms, a module name and a parameter list.
;;; The parameter list specifies a list of `version registry keys', additional
;;; keys used to store version data for the given module.  This list could be used
;;; for type-checking, but for now (3/23/90, jh) it simply arranges to check the
;;; argument count of version registry keys.  To use the GSI example, the form
;;;
;;;   (def-version-registry-format remote-gsi-extension (icp-socket))
;;;
;;; tells the version registry about the format of keys which will store version
;;; data for GSI extension processes.  These keys will be two-element lists, whose
;;; first element is the symbol remote-gsi-extension and whose second element is
;;; the specific icp-socket structure which communicates with that extension
;;; process.  Def-registry-version-format also creates a reclaimer function for
;;; inaccessible entries (described in 4> below).

;;; 2> Arrange for version data to be acquired.  The means by which version data
;;; is acquired is of course application-specific.  Once acquired, version data
;;; should be represented as integers which give the major version and minor
;;; version respectively.  These integers are then used by the macros
;;; set-major-version and set-minor-version.  The argument structure of these
;;; macros is <version number> <module name> . <version keys>.  For example, the
;;; forms
;;;
;;;  (set-major-version 1 'remote-gsi-process current-icp-socket)
;;;  (set-minor-version 11 'remote-gsi-process current-icp-socket)
;;;
;;; will update the version registry so that version 1.11 is associated with
;;; current-icp-socket.  Making things completely symmetrical (i.e., defining
;;; setf methods for major-version and minor-version) is beyond the capacity
;;; of some lisps we use.

;;; The rationale behind the design decision not to present the programmer with a
;;; "version-registry-entry" structure was that of convenience and upward
;;; compatibility.  We may want to specify versions in other, more finely-grained,
;;; ways in the future.

;;; 3> Sequester the version-dependent sections of the program.  The programmer
;;; can now use version-checking wrappers around version-dependent sections of the
;;; code.  There are currently (jh, 4/17/90) two such wrappers,
;;; with-appropriate-version and with-bifurcated-version.

;;; The syntax of with-appropriate-version is as follows:
;;;
;;;   (with-appropriate-version (  <lowest-allowed-icp-protocol-version> .
;;;                                icp-socket )
;;;      [ <inappropriate version function> ]
;;;      .  <body> )

;;; In what follows, we will refer to the second (parenthesized) subform of a
;;; with-appropriate-version call as the specs-list.  The <module name> form in
;;; the specs-list is an unevaluated symbol; all others are evaluated.  Note that
;;; this differs from the lower-level major-version and minor-version forms,
;;; where all subforms are evaluated.  The rationale is convenience and extensibility.
;;; If the version of the module is at least as recent as the lowest allowed major
;;; and minor versions, <body> will be executed and its results returned.  The
;;; recency comparison is that the module major version should exceed the allowed
;;; major version, or if the major versions are equal, the module minor version
;;; should exceed the allowed minor version.

;;; If a symbol for the <inappropriate version function> is supplied, the function
;;; named by this symbol will be called when the version test fails.  This
;;; function must take as arguments the additional registry keys given in the
;;; with-appropriate-version spec-list, in the order given.  The
;;; with-appropriate-version form will return whatever the function returns.  If
;;; the first form after the spec-list is anything other than a non-nil symbol,
;;; the with-appropriate-version form will return nil if the version test fails.
;;; This syntax is only ambiguous when the with-appropriate-version body consists
;;; of a solitary unquoted symbol, with no subsequent forms.  In this case it will
;;; not be interpreted as a function, since the programmer's intent is probably to
;;; access the value of that symbol.

;;; The syntax of with-bifurcated-version is as follows:
;;;   (with-bifurcated-version (   <icp-protocol-version-allowing-new-form> .
;;;                                icp-socket )
;;;      <form-to-execute-under-old-version>
;;;      <form-to-execute-under-new-version> )

;;; If the version of the module is at least as recent as the version specified,
;;; the single form <form-to-execute-under-new-version> is evaluated.  If the
;;; module version is less recent, or if the version of the module cannot be
;;; determined, the single form <form-to-execute-under-old-version> is evaluated.
;;; With-bifurcated-version uses the same version check as with-appropriate
;;; version: if the current major version is greater than the required major
;;; version, or if the major versions are equal and the current minor version is
;;; at least as recent as the required minor version.  In contrast to
;;; with-appropriate-version, however, with-bifurcated-version always executes one
;;; set of body forms.

;;; Note that <module name> is unevaluated.  This is different from its use in
;;; the lower-level major-version and minor-version forms, where it must
;;; evaluate to a symbol naming the module whose version we are interested in.

;;; The programmer can also use the macros
;;;
;;;   (major-version <module> . <keys>)
;;;   (minor-version <module> . <keys>)
;;;
;;; for finer-grained control of version dependencies.  The <module>
;;; argument should evaluate to a symbol naming the module whose
;;; version we are interested in.  Note that this syntax differs from the
;;; specs-list in with-appropriate-version and with-bifurcated-version
;;; forms.  There, the <module> argument is unevaluated in order
;;; to provide some syntactic sugar.

;;; In the GSI example, a form like
;;;
;;; (with-appropriate-version ( 2 0 current-icp-socket)
;;;   complain-about-RPC-version-mismatch
;;;   (send-RPC-start ...))
;;;
;;; will cloak version-dependent code correctly, calling
;;; (complain-about-RPC-version-mismatch current-icp-socket) if the version test
;;; fails.




(defmacro with-appropriate-version
          ((lowest-allowed-icp-version &optional (icp-socket 'current-icp-socket)) &body body)
  (let (value)
    (unless (and (symbolp lowest-allowed-icp-version)
                 (boundp lowest-allowed-icp-version)
                 (fixnump (setq value (symbol-value lowest-allowed-icp-version))))
      (error "with-appropriate-version: the lowest-allowed-icp-version, ~S, is not a symbol evaluating to a fixnum"
             lowest-allowed-icp-version))
    `(when (>=f (minf (icp-protocol-version-for-input ,icp-socket)
                      (icp-protocol-version-for-output ,icp-socket))
                ,value)
       ,@body)))

(defmacro with-appropriate-version-for-output
          ((lowest-allowed-icp-version &optional (icp-socket 'current-icp-socket)) &body body)
  (let (value)
    (unless (and (symbolp lowest-allowed-icp-version)
                 (boundp lowest-allowed-icp-version)
                 (fixnump (setq value (symbol-value lowest-allowed-icp-version))))
      (error "with-appropriate-version: the lowest-allowed-icp-version, ~S, is not a symbol evaluating to a fixnum"
             lowest-allowed-icp-version))
    `(when (>=f (icp-protocol-version-for-output ,icp-socket) ,value)
       ,@body)))

(defmacro with-appropriate-version-for-input
          ((lowest-allowed-icp-version &optional (icp-socket 'current-icp-socket)) &body body)
  (let (value)
    (unless (and (symbolp lowest-allowed-icp-version)
                 (boundp lowest-allowed-icp-version)
                 (fixnump (setq value (symbol-value lowest-allowed-icp-version))))
      (error "with-appropriate-version: the lowest-allowed-icp-version, ~S, is not a symbol evaluating to a fixnum"
             lowest-allowed-icp-version))
    `(when (>=f (icp-protocol-version-for-input ,icp-socket) ,value)
       ,@body)))



(defmacro with-bifurcated-version
          ((lowest-icp-version-allowing-new-form &optional (icp-socket 'current-icp-socket) predicate)
           old-form
           new-form)
  (let (value)
    (unless (and (symbolp lowest-icp-version-allowing-new-form)
                 (boundp lowest-icp-version-allowing-new-form)
                 (fixnump (setq value (symbol-value lowest-icp-version-allowing-new-form))))
      (error "with-bifurcated-version the lowest-icp-version-allowing-new-form ~S, is not a symbol evaluating to a fixnum"
             lowest-icp-version-allowing-new-form))
    `(if (or (>=f (minf (icp-protocol-version-for-input ,icp-socket)
                        (icp-protocol-version-for-output ,icp-socket))
                  ,value)
             ,@(when predicate `(,predicate)))
         ,new-form
         ,old-form)))

(defmacro with-bifurcated-version-for-output
          ((lowest-icp-version-allowing-new-form &optional (icp-socket 'current-icp-socket) predicate)
           old-form
           new-form)
  (let (value)
    (unless (and (symbolp lowest-icp-version-allowing-new-form)
                 (boundp lowest-icp-version-allowing-new-form)
                 (fixnump (setq value (symbol-value lowest-icp-version-allowing-new-form))))
      (error "with-bifurcated-version the lowest-icp-version-allowing-new-form ~S, is not a symbol evaluating to a fixnum"
             lowest-icp-version-allowing-new-form))
    `(if (or (>=f (icp-protocol-version-for-output ,icp-socket) ,value)
             ,@(when predicate `(,predicate)))
         ,new-form
         ,old-form)))

(defmacro with-bifurcated-version-for-input
          ((lowest-icp-version-allowing-new-form &optional (icp-socket 'current-icp-socket) predicate)
           old-form
           new-form)
  (let (value)
    (unless (and (symbolp lowest-icp-version-allowing-new-form)
                 (boundp lowest-icp-version-allowing-new-form)
                 (fixnump (setq value (symbol-value lowest-icp-version-allowing-new-form))))
      (error "with-bifurcated-version the lowest-icp-version-allowing-new-form ~S, is not a symbol evaluating to a fixnum"
             lowest-icp-version-allowing-new-form))
    `(if (or (>=f (icp-protocol-version-for-input ,icp-socket) ,value)
             ,@(when predicate `(,predicate)))
         ,new-form
         ,old-form)))






;;;; Pseudo-keyworded string utilities


;; jh, 6/19/91.

;;; Gensym search is a macro designed to emulate the Common Lisp search function.
;;; It duplicates the behavior described on p 407 of CLtL/2e.  The keyword behavior
;;; adheres to the description on pp 388-392 of CLtL/2e.  We include it because
;;; some Common Lisp implementations (e.g.  Chestnut) cons a &rest list whenever
;;; search is called.

;;; Note that as of 5.0, this has been extended to deal with wide strings, in
;;; addition to standard CL sequences.  Access is through ELTW instead of ELT,
;;; and comparison by default uses EQLW instead of EQL.

(defmacro gensym-search
          (sequence1 sequence2
           &rest keys &key from-end test test-not key start1 start2 end1 end2)
  (when (and test test-not)
    (error "GENSYM-SEARCH: :TEST and :TEST-NOT keywords may not occur together."))
  (when (and (null test) (null test-not))
    (setq test `(function eql)))
  (cond ((every #'null keys)
         `(gensym-search-simple ,sequence1 ,sequence2))
        (t `(gensym-search-complex ,sequence1 ,sequence2
              ,from-end
              ,test
              ,test-not
              ,key
              ,(or start1 0)
              ,(or start2 0)
              ,end1
              ,end2))))

(defun gensym-search-simple
       (sequence1 sequence2)
  (declare (eliminate-for-gsi))
  (let ((sequence1-length (lengthw sequence1))
        (sequence2-length (lengthw sequence2)))
    (if (> sequence1-length sequence2-length)
        nil
        (loop for sequence2-index
                  from 0
                  to (- sequence2-length sequence1-length)
              thereis
              (and (loop for sequence1-index
                             from 0
                             below sequence1-length
                         always
                         (eqlw (eltw sequence1 sequence1-index)
                               (eltw sequence2
                                     (+ sequence1-index sequence2-index))))
                   sequence2-index)))))

(defun gensym-search-complex
       (sequence1 sequence2
        from-end test test-not key start1 start2 end1 end2)
  (declare (eliminate-for-gsi))
  (unless end1 (setq end1 (lengthw sequence1)))
  (unless end2 (setq end2 (lengthw sequence2)))
  (let ((span1 (- end1 start1)))
    (if (> span1 (- end2 start2))
        nil
        (if from-end
            (loop for sequence2-index
                      from (- end2 span1)
                      downto start2
                  thereis
                  (and (loop for sequence1-index
                                 from start1
                                 below end1
                             for raw-element1 = (eltw sequence1
                                                      sequence1-index)
                             for raw-element2 = (eltw sequence2
                                                      (+ sequence1-index
                                                         sequence2-index))
                             for element1 = (if key
                                                (funcall key raw-element1)
                                                raw-element1)
                             for element2 = (if key
                                                (funcall key raw-element2)
                                                raw-element2)
                             always
                             (if test
                                 (funcall test element1 element2)
                                 t)
                             never
                             (and test-not
                                  (funcall test-not element1 element2)))
                       sequence2-index))
            (loop for sequence2-index
                      from start2
                      to (- end2 span1)
                  thereis
                  (and (loop for sequence1-index
                                 from start1
                                 below end1
                             for raw-element1 = (eltw sequence1
                                                      sequence1-index)
                             for raw-element2 = (eltw sequence2
                                                      (+ sequence1-index
                                                         sequence2-index))
                             for element1 = (if key
                                                (funcall key raw-element1)
                                                raw-element1)
                             for element2 = (if key
                                                (funcall key raw-element2)
                                                raw-element2)
                             always
                             (if test
                                 (funcall test element1 element2)
                                 t)
                             never
                             (and test-not
                                  (funcall test-not element1 element2)))
                       sequence2-index))))))

#+development
(defparameter gensym-search-validation-suite
  (append
    '(
      ((gensym-search "HIT" "HI")                     nil)
      ((gensym-search "HI" "HI")                      0)
      ((gensym-search "HI" "HIxxx")                   0)
      ((gensym-search "HI" "xxxHI")                   3)
      ((gensym-search "HI" "xxxHIxxx")                3)
      ((gensym-search "HI" "xHIxxxHIx")               1)
      ((gensym-search "HI" "xHIxxxHIx" :from-end t)   6)
      ((gensym-search '(a b c) '(x x a b c x x x))    2)
      ((gensym-search '("A" "B" "C")
        '(x x "A" "B" "C" x x))         nil)
      ((gensym-search '("A" "B" "C")
        '(x x "A" "B" "C" x x)
        :test #'equal)                  2)
      ((gensym-search '((a) (b) (c))
        '((x) (x) (a) (b) (c) (x) (x))) nil)
      ((gensym-search '((a) (b) (c))
        '((x) (x) (a) (b) (c) (x) (x))
        :key #'car)                     2)
      ((gensym-search "HHH" "III"
        :test-not #'eql)                0)
      ((gensym-search "HHHHHH" "IIIIIH"
        :test-not #'eql)                nil)
      ((gensym-search "HHHHHH" "IIIIIH"
        :test-not #'eql :end1 4)        0)
      )

    ;; copy of the above adopted for testing wide strings:

    (copy-tree-changing-strings-to-text-strings
      '(
        ((text-string-search+ "HIT" "HI")                     nil)
        ((text-string-search+ "HI" "HI")                      0)
        ((text-string-search+ "HI" "HIxxx")                   0)
        ((text-string-search+ "HI" "xxxHI")                   3)
        ((text-string-search+ "HI" "xxxHIxxx")                3)
        ((text-string-search+ "HI" "xHIxxxHIx")               1)
        ((text-string-search+ "HI" "xHIxxxHIx" :from-end t)   6)
        ((text-string-search+ '(a b c) '(x x a b c x x x))    2)
        ((text-string-search+ '("A" "B" "C")
          '(x x "A" "B" "C" x x))         nil)
        ((text-string-search+ '("A" "B" "C")
          '(x x "A" "B" "C" x x)
          :test #'equalw)                  2)
        ((text-string-search+ '((a) (b) (c))
          '((x) (x) (a) (b) (c) (x) (x))) nil)
        ((text-string-search+ '((a) (b) (c))
          '((x) (x) (a) (b) (c) (x) (x))
          :key #'car)                     2)
        ((text-string-search+ "HHH" "III"
          :test-not #'eqlw)                0)
        ((text-string-search+ "HHHHHH" "IIIIIH"
          :test-not #'eqlw)                nil)
        ((text-string-search+ "HHHHHH" "IIIIIH"
          :test-not #'eqlw :end1 4)        0)
        ))))

#+development
(defun validate-gensym-lisp-facility (validation-suite &optional verbose-p)
  (loop for (form result) in validation-suite
        for test-result
            = (eval (copy-tree form)) ;weirdness from SYS:DISPLACE on TIs otherwise
        for passed-p = (tree-equal test-result result)
        with bad-forms = nil
        do
        (when verbose-p
          (format t "~&~:[!!! incorrect: ~;  OK:~] ~a => ~a~%"
                  passed-p form test-result))
        (unless passed-p
          (push form bad-forms))
        finally (return (values (null bad-forms) bad-forms))))

#+development
(defun validate-gensym-search (&optional verbose-p)
  (validate-gensym-lisp-facility gensym-search-validation-suite verbose-p))

;; `Gensym-string-equal' is replaced by text-string-equal+

;; `Gensym-string=' is replaced by gensym-string=

;; `Gensym-string=-given-indices' is replaced by
;; text-string-equal-given-indices

;; `gensym-string-equal-given-indices' is replaced by
;; text-string-equal-given-indices

;; `Gensym-parse-integer' is replaced by text-string-parse-integer

;; `gensym-parse-symbol-function' is replaced by
;; text-string-parse-symbol-function




;;;; Simplified Fundimental Lisp Operations: Eval, and Typep



;;; `Simple-eval' provides only the special forms quote and progn.
;;; It can only call functions of zero to five arguments.  It doesn't
;;; suport macros.  It doesn't support any bindings.

;;; A few caveats must be born in mind prior to applying simple-eval
;;; to a problem.  First you must be certain that all the functions
;;; called by simple-eval are funcallable at runtime in the distribution
;;; G2.  That implies that whatever mechanism generates the forms
;;; is strictly generative from a well-enumerated set of primitives.

;;; Secondly, in simple-eval managed-numbers are evaluated by having their
;;; value copied.  These semantics allow managed-numbers to appear as
;;; constants in the form.  Any forms which manipulate managed floats
;;; should consume their inputs to assure this doesn't lead to leakage.

(defun simple-eval (form)
  (declare (eliminate-for-gsi))
  (cond
    ((managed-float-p form)
     (copy-managed-float form))
    (T
     (typecase form
       (symbol (symbol-value form))
       (atom form)
       (list
        (let ((head (first form)))
          (case head
            (progn
             (loop with result = nil
                   for statement in (rest form)
                   do (setf result (simple-eval statement))
                   finally (return result)))
            (quote (second form))
            (otherwise
             (case (length form)
               (1 (funcall head))
               (2 (funcall head
                           (simple-eval (second form))))
               (3 (funcall head
                           (simple-eval (second form))
                           (simple-eval (third  form))))
               (4 (funcall head
                           (simple-eval (second form))
                           (simple-eval (third  form))
                           (simple-eval (fourth form))))
               (5 (funcall head
                           (simple-eval (second form))
                           (simple-eval (third  form))
                           (simple-eval (fourth form))
                           (simple-eval (fifth  form))))
               (6 (funcall head
                           (simple-eval (second form))
                           (simple-eval (third  form))
                           (simple-eval (fourth form))
                           (simple-eval (fifth  form))
                           (simple-eval (sixth  form))))
               (otherwise
                (error "simple eval suports only 5 argument calls or less.")))))))))))



;;; `Simple-typep' is a nonconsing version of typep for a subset of the
;;; known types.  This currently suports this set of types: null, boolean,
;;; symbol, fixnum, T, managed-float, slot-value-float, temporary-constant,
;;; and member.

(eval-when (:compile-toplevel :load-toplevel :execute)
(def-global-property-name simple-type-specification)
)


;;; `Deftype-simple' is the direct equivalent of deftype, but currently it only
;;; supports the (satisfies <function-name) form.  See also deftype-error-printer.

(defmacro deftype-simple (type-name args-list &body body)
  ;; Check that the body looks like so:
  ;;   <body>        : (<q-type-spec>)
  ;;   <q-type-spec> : '<type-spec>
  ;;   <type-spec>   : (satisfies <function>)
  ;;   <function>    : <symbol>
  (unless (and (null args-list)
               (consp body)
               (consp (first body))
               (eq 'quote (first (first body))))
          (warn
            "deftype-simple is very primitive: the body must be a quoted form."))
  (let ((type-spec (second (first body))))
    (unless (or
              (and (symbolp type-spec)
                   (valid-simple-type-specification type-spec))
              (and  (consp type-spec)
                    (or
                      (and (eq 'satisfies (first type-spec))
                           (consp (cdr type-spec))
                           (symbolp (second type-spec))
                           (null (cddr type-spec)))
                      (and (eq 'member (first type-spec))))))
            (warn
              "deftype-simple is very primitive: the body must be either a ~
               type-name, (member ...), or (satisfies <fn>)."))
    `(eval-when (:compile-toplevel :load-toplevel :execute)
       (setf (simple-type-specification ',type-name)
             ',type-spec)
       ',type-name)))


(deftype-simple symbol () '(satisfies symbolp))

(deftype-simple cons () '(satisfies consp))

(defun simple-typep (instance type-spec)
  (typecase type-spec
    (symbol
     (case type-spec
       ((T) t)
       (null nil)
       (fixnum   ;; not a subtype of common.
        (fixnump instance))
       (boolean  ;; not a subtype of common.
        (or (null instance)
            (eq instance t)))
       (gensym-float
        (gensym-float-p instance))
       (managed-number
        (managed-number-p instance))
       (temporary-constant
        (temporary-constant-p instance))
       (otherwise
        (let ((simple-type-specification (simple-type-specification type-spec)))
          (if simple-type-specification
              (simple-typep instance simple-type-specification)
              #+development
              (cerror "proceed" "Invalid simple type specification ~S" type-spec))))))
    (cons
     (case (first type-spec)
       (satisfies
        (funcall (second type-spec) instance))
       (member
        (memq instance (rest type-spec)))
       (or
        (loop for spec in (rest type-spec)
              when (simple-typep instance spec)
                do (return t)
              finally (return nil)))))))

;; Any edits to simple-typep must be reflected in the following function.



;;; `Valid-simple-type-specification' to check the syntatic validity of
;;; a type specification that will later be passed to simple-typep.

(eval-when (:compile-toplevel :load-toplevel :execute)
(defun-for-macro valid-simple-type-specification (type-specification)
  (typecase type-specification
    (symbol
     (or
       (memq type-specification '(boolean fixnum t null
                                          managed-number gensym-float temporary-constant))
       (simple-type-specification type-specification)))
    (cons
     (case (first type-specification)
       (member
        t)
       (or
        (loop for spec in (rest type-specification)
              unless (valid-simple-type-specification spec)
                do (return nil)
              finally
                (return t)))
       (otherwise
        nil)))))
)


;;; When an instance provided by the user in input does not match a
;;; simple type specification, an error is displayed that discribes the
;;; type expected.  These error messages are created by
;;; tformat-type-error which, in turn, calls type-error-printers defined
;;; for various kinds of types.  The global property
;;; `type-error-printer' maps from type names to a function name or
;;; string.  The function names are of the form "~A-TYPE-ERROR-PRINTER",
;;; and are created via the macro `deftype-error-printer'. These
;;; functions may assume they are called in a twith-output-to-text-string
;;; context.  They should add to that output a phrase appropriate to fill
;;; in the remainder of the sentence "Foo is ...".  For example, "Foo is
;;; niether true nor false"  If the value of type-error-printer
;;; is a string, it is appended to the output.

(def-global-property-name type-error-printer)

(defmacro deftype-error-printer (type-name arglist &body body)
  (assert (valid-simple-type-specification type-name) ()
          "Unknown type name in def-type-error-printer.")
  (if (and (null (cddr body))
           (stringp (first body)))
      `(setf (type-error-printer ',type-name) ,(first body))
      (let ((type-error-printer (intern (format nil "~A-TYPE-ERROR-PRINTER" type-name))))
        `(progn
           (defun ,type-error-printer (,type-name ,@arglist)
             ,@body)
           (setf (type-error-printer ',type-name) ',type-error-printer)))))

(deftype-error-printer boolean () "neither true nor false")

(deftype-error-printer symbol () "not a symbol")

(deftype-error-printer fixnum () "not a simple integer")

(deftype-error-printer gensym-float () "not a number")

(deftype-error-printer managed-number () "not a number")

(deftype-error-printer temporary-constant () "not a number")

(defun tformat-type-error (value type-spec)
  (declare (eliminate-for-gsi))
  (tformat "~(~A is ~)" value)
  (typecase type-spec
    (symbol
     (case type-spec
       ((gensym-float managed-float slot-value-float)
        (tformat " not a number."))
       (T
        (let ((type-error-printer (type-error-printer type-spec)))
          (typecase type-error-printer
            (string
             (tformat "~A." type-error-printer))
            (null
             (tformat "~( not ~A~A~)." (supply-a-or-an type-spec) type-spec))
            (symbol
             (funcall type-error-printer value)
             (tformat ".")))))))
    (cons
     (case (first type-spec)
       (member
        (let ((length (length type-spec)))
          (cond
            ((=f length 1)
             (tformat "~(not ~A~)." (second type-spec)))
            ((=f length 2)
             (tformat
               "~( neither ~A nor ~A~)." (second type-spec) (third type-spec)))
            ((<f length 10)
             (tformat "not one of ")
             (loop for l in (cdr type-spec)
                   do (tformat "~(~A~)" (car l))
                      (tformat
                        (if (null (cdr l)) ", or " ", ")))
             (tformat "."))
            (t
             (tformat
               "~(not an appropriate value (e.g., ~A, ~A, etc.)~)"
               (second type-spec) (third type-spec))))))))))


;;; `Simple-type-writer' is a global property used to map from a simple type
;;; name to a routine name known as a simple type writer.  A simple type
;;; writer will, using the tformat family of routines, emit a printed
;;; representation for an instance of a simple type.  You define new instances
;;; of a simple type using deftype-writer.

;;; The prefered interface to these writers is write-instance-of-simple-type.

(def-global-property-name simple-type-writer)

(defmacro deftype-writer (type-name (instance) &body body)
  (assert (valid-simple-type-specification type-name) ()
          "Unknown type name in deftype-writer.")
  (let ((type-writer (intern (format nil "~A-TYPE-WRITER" type-name))))
    `(progn
       (defun ,type-writer (,instance)
         ,@body)
       (setf (simple-type-writer ',type-name) ',type-writer))))



;;; `Write-instance-of-simple-type' emit using the tformat family of
;;; routines a printed representation for and instance of a simple type.
;;; It will use the simple type writer if one is defined, otherwise it
;;; will use "~S" and tformat.

;;; If the simple-type-name provided is constant, and has a defined
;;; simple-type-writer then the macro will expand into a direct call
;;; to that type writer.

(defmacro write-instance-of-simple-type (simple-type-name instance)
  (if (and (consp simple-type-name)
           (null (cddr simple-type-name))
           (eq 'quote (first simple-type-name))
           (valid-simple-type-specification (second simple-type-name))
           (and (symbolp (second simple-type-name)) ; second = cadr
                (simple-type-writer (second simple-type-name))))
      `(,(simple-type-writer (second simple-type-name)) ,instance)
      `(write-instance-of-simple-type-1 ,simple-type-name ,instance)))

(defun write-instance-of-simple-type-1 (simple-type-name instance)
  (let ((type-writer (simple-type-writer simple-type-name)))
    (if type-writer
        (funcall (simple-type-writer simple-type-name) instance)
        (tformat "~(~S~)" instance))))





;;;; Basic Intervals and Rectangles


;; Basic operations on intervals and rectangles, taking spread arguments.


(def-substitution-macro closed-intervals-intersect-p-macro
    (left-1 right-1 left-2 right-2)
  (and (<=f left-1 right-2)
       (<=f left-2 right-1)))


(def-substitution-macro right-open-intervals-intersect-p-macro
    (left-1 right-1 left-2 right-2)
  (and (<f left-1 right-2)
       (<f left-2 right-1)))


;;; The macro `rectangles-overlap-p' is a boolean macro of eight arguments,
;;; i.e.  two rectangles.  It generates efficent code for checking if the
;;; rectangles overlap.  All intervals are assumed to include their endpoints.

(defmacro rectangles-overlap-p (l1 t1 r1 b1 l2 t2 r2 b2)
  (avoiding-variable-capture (l1 t1 r1 b1 l2 t2 r2 b2)
    `(and (or (>=f ,b2 ,b1 ,t2) (>=f ,b1 ,b2 ,t1))
          (or (>=f ,r2 ,r1 ,l2) (>=f ,r1 ,r2 ,l1)))))


;;; The macro `rectangle-inside-rectangle-p' is true if the first rectangle
;;; is inside or identical to the second rectangle.

(defmacro rectangle-inside-rectangle-p (l1 t1 r1 b1 l2 t2 r2 b2)
  `(and (<=f ,l2 ,l1 ,r1 ,r2)
        (<=f ,t2 ,t1 ,b1 ,b2)))

(defmacro point-inside-rectangle-p (point-x point-y left top right bottom)
  (avoiding-variable-capture (point-x point-y left top right bottom)
    `(and (<=f ,left ,point-x)
          (<f ,point-x ,right)
          (<=f ,top ,point-y)
          (<f ,point-y ,bottom))))

(defmacro rectangle-not-empty-p (left top right bottom)
  (avoiding-variable-capture (left top right bottom)
    `(and (<r ,left ,right)
          (<r ,top ,bottom))))




;;; The macro `half-open-rectangles-overlap-p' is the same except that the
;;; intervals are assumed to be open on the right and bottom.

(defmacro half-open-rectangles-overlap-p (l1 t1 r1 b1 l2 t2 r2 b2)
  (avoiding-variable-capture (l1 t1 r1 b1 l2 t2 r2 b2)
    `(and (right-open-intervals-intersect-p-macro
            ,l1 ,r1 ,l2 ,r2)
          (right-open-intervals-intersect-p-macro
            ,t1 ,b1 ,t2 ,b2))))





;;;; Regions and their Component Substructures



;;; Currently both regions and all their components are list-structures that are
;;; consed in the region pool.  There is no reason why the components could not be
;;; moved into their own pools.

(defconser region)


;;; These conses are used to create data structures that are instances of the
;;; following grammar:

;;;    region-strip-top, interval-left, interval-right : fixnum
;;;    interval  : (interval-left . interval-right)
;;;    intervals : (interval*)
;;;    region-strip : (region-strip-top . region-strip-intervals)
;;;    region-strips : (region-strip*)
;;;    region-bounding-box :
;;;            (region-bounding-box-x-interval . region-bounding-box-y-interval)
;;;    region : (region-strips . region-bounding-box)

;;; The intervals and region-strips are just lists, they have no special
;;; accessors.  The other forms are all declared using def-list-structure
;;; and the accessors are as shown.  The fixnum are all absolute, not relative,
;;; i.e. to offset a region you must tinker with all the numbers.

;;; Region-bounding-box is an usual representation for a rectangle, and in the
;;; region-bounding-box-y-interval the terms the "left" and "right" are misleading.

;;; The bottom of a region strip is infered by the top of the next strip.
;;; the last region-strip will always have a NULL intervals.

;; - ben 11/18/93






;;;; The `Interval' and `Intervals' List-Structures and Operations



;;; An `interval' is simply an ordered pair of fixnums.  Their is no state maintained
;;; in the interval data structure which indicates if the interval is open or closed
;;; at its endpoints - this is left to interpretation of the user.  Those interval
;;; operations that depend on open/closed properties should incorporate the term
;;; `left-open' or `right-open' in their name if they depend upon the interval not
;;; including its left or right endpoint, respectively. For example, see the function
;;; right-open-intervals-intersect-p below.

;;; Note that intervals are used in contexts where their points may be strict
;;; subtypes of fixnum (such as window or raster coordinates).

;;; Intervals are often used as components of higher-dimensional geometric objects
;;; since many geometric algorithms reduce naturally to operations on lower
;;; dimensional objects by projecting along an axis.  A simple example of this
;;; dimensional reduction is the reduction of rectangle intersections to the
;;; intersection of the intervals comprising the projections of the rectangle along
;;; each axis (see region-bounding-box-intersect-p below).  A more complicated
;;; example can be seen in the algorithm used in union-region below, where the
;;; projection along the y-axis reduces to refining partitions and the projection
;;; along the x-axis reduces to computing a union of intervals.

(def-list-structure (interval (:consing-function region-cons-macro)
                              (:optimize t))
  (interval-left . interval-right))

(def-substitution-macro copy-interval (interval)
  (make-interval
    (interval-left interval)
    (interval-right interval)))

(def-substitution-macro reclaim-interval (interval)
  (reclaim-region-cons-macro interval))

(def-substitution-macro set-interval (interval left right)
  (setf (interval-left  interval) left)
  (setf (interval-right interval) right))

(def-substitution-macro right-open-interval-empty-p (interval)
  (<=f (interval-right interval) (interval-left interval)))

(def-substitution-macro shift-interval (interval delta)
  (incff (interval-left  interval) delta)
  (incff (interval-right interval) delta))


(defmacro transform-interval-macro (interval left-transform &optional (right-transform left-transform))
  (avoiding-variable-capture (interval)
    `(progn
       (setf (interval-left ,interval) (,left-transform (interval-left ,interval))
             (interval-right ,interval) (,right-transform (interval-right ,interval)))
       ,interval)))


(def-substitution-macro bounding-interval (interval-1 interval-2)
  (make-interval (minf (interval-left  interval-1) (interval-left  interval-2))
                       (maxf (interval-right interval-1) (interval-right interval-2))))

(def-substitution-macro point-in-right-open-interval-p (interval point)
  (and (>=f point (interval-left  interval))
       (<f  point (interval-right interval))))


(defun right-open-intervals-intersect-p (interval-1 interval-2)
  (declare (eliminate-for-gsi))
  (right-open-intervals-intersect-p-macro
    (interval-left interval-1) (interval-right interval-1)
    (interval-left interval-2) (interval-right interval-2)))




;;; `Intervals' are simply (region pool consed) lists whose elements are intervals.

;;; Note that it would be slightly more efficient to define specialized operations
;;; for intervals rather than using the generic tree-based operations below. Such
;;; specialized operations would not need to do consp checks at leaves.

(defmacro intervals-equal (intervals1 intervals2)
  `(equal ,intervals1 ,intervals2))

(defmacro copy-intervals (intervals)
  (avoiding-variable-capture (&aux left right)
    `(loop for (,left . ,right) in ,intervals
           collect (make-interval ,left ,right)
             using region-cons-macro)))

(defmacro reclaim-intervals (intervals)
  (avoiding-variable-capture (intervals &aux interval)
    `(loop for ,interval in ,intervals
           doing (reclaim-interval ,interval)
           finally (reclaim-region-list ,intervals))))



;;; `Intersect-intervals' returns three values: the intervals representing the
;;; intersection of the two given intervals, and the min and max value found
;;; in those intervals.  All three values maybe nil.

(defun intersect-intervals (A-intervals B-intervals)
  (declare (eliminate-for-gsi))
  (let (result a0 a1 b0 b1 min?)
    (macrolet ((advance-a ()
                 `(progn
                    (unless a-intervals (return nil))
                    (setq a0 (interval-left (first A-intervals)))
                    (setq a1 (interval-right (pop A-intervals)))))
               (advance-b ()
                 `(progn
                    (unless b-intervals (return nil))
                    (setq b0 (interval-left (first b-intervals)))
                    (setq b1 (interval-right (pop b-intervals)))))
               (emit (left right)
                 `(unless (=f ,left ,right)
                    ;; Combine with prior interval if approprate.
                    (unless min? (setf min? ,left))
                    (if (eq (cddr result) ,left)
                     (setf (cddr result) ,right)
                     (region-push (make-interval ,left ,right) result)))))
      (loop
        initially
          (advance-a)
          (advance-b)
        do
        (tagbody
           (cond
             ((<f a0 b0)    ;; a0 .. b0
              (cond
                ((<f a1 b0)       ;;  [a0..a1)..[b0..b1)        advance A
                 (go adv-a))
                ((<=f b1 a1)      ;;  [a0..[b0..b1)..a1)  emit, advance B
                 (emit b0 b1)
                 (go adv-b))
                ((<f a1 b1)       ;;  [a0..[b0..a1)..b1)  emit, advance A
                 (emit b0 a1)
                 (go adv-a))))
             (t            ;; b0 .. a0
              (cond
                ((<f b1 a0)       ;;  [b0..b1)..[a0..a1)        advance B
                 (go adv-b))
                ((<=f a1 b1)      ;;  [b0..[a0..a1)..b1)  emit, advance B
                 (emit a0 a1)
                 (go adv-a))
                ((<f b1 a1)       ;;  [b0..[a0..b1)..a1)  emit, advance A
                 (emit a0 b1)
                 (go adv-b)))))
         adv-a
           (advance-a)
           (go next)
         adv-b
           (advance-b)
         next))
      (let ((max? (if result
                      (interval-right (first result))
                      nil)))
        (values (nreverse result)
                min?
                max?)))))

;;; `Subtract-intervals' returns three values: the intervals representing the
;;; difference of taking the second intervals out of the first, and the min and
;;; maximum values found in that resulting intervals.  All three values maybe
;;; nil.

(defun subtract-intervals (A-intervals B-intervals)
  (declare (eliminate-for-gsi))
  (unless B-intervals
    ;; copy A intervals, and measure their extent.
    (return-from subtract-intervals
      (if a-intervals
          (loop for (left . right) in a-intervals
                minimize left into left-max using minf
                maximize right into right-max using maxf
                collect (region-cons left right) into result using region-cons
                finally (return (values result left-max right-max)))
          nil)))
  (unless A-intervals
    (return-from subtract-intervals nil))
  (let (result a0 a1 b0 b1 min? max?)
    (macrolet ((format (&rest args)
                 (declare (ignore args))
                 nil)
               (advance-a ()
                 `(progn
                    (format t "~&adv a")
                    (unless a-intervals (go finished-a))
                    (setq a0 (interval-left (first A-intervals)))
                    (setq a1 (interval-right (pop A-intervals)))))
               (advance-b ()
                 `(progn
                    (format t "~&adv b")
                    (unless b-intervals (go finished-b))
                    (setq b0 (interval-left (first b-intervals)))
                    (setq b1 (interval-right (pop b-intervals)))))
               (emit (left right)
                 ;; Combine with prior interval is approprate.
                 `(progn
                    (format t " emit ~D ~D" ,left ,right)
                    (unless (=f ,left ,right)
                      (cond
                        ((eq (cddr result) ,left)
                         (setf max? ,right)
                         (setf (cddr result) ,right))
                        (t
                         (cond
                           (max?
                            (setf min? (minf min? ,left))
                            (setf max? (maxf max? ,right)))
                           (t
                            (setf min? ,left)
                            (setf max? ,right)))
                         (region-push (make-interval ,left ,right) result)))))))
      (block nil
        (tagbody
           (advance-a)
           (advance-b)
         loop-head
           (format t " ~10t ~D ~D ~20T~D ~D" a0 a1 b0 b1)
           (cond
             ((<f a0 b0)        ;; a0 .. b0
              (cond
                ((<f a1 b0)       ;;  [a0,,a1)..[b0..b1)
                 (emit a0 a1)
                 (go adv-a))
                ((<=f b1 a1)      ;;  [a0,,[b0..b1)..a1)
                 (emit a0 b0)
                 (setf a0 b1)
                 (go adv-b))
                ((<f a1 b1)       ;;  [a0,,[b0..a1)..b1)
                 (emit a0 b0)
                 (go adv-a))))
             (t                 ;; b0 .. a0
              (cond
                ((<f b1 a0)       ;;  [b0..b1)..[a0..a1)
                 (go adv-b))
                ((<=f a1 b1)      ;;  [b0..[a0..a1)..b1)
                 (go adv-a))
                ((<f b1 a1)       ;;  [b0..[a0..b1)..a1)
                 (setf a0 b1)
                 (go adv-b)))))
         adv-a
           (advance-a)
           (go next)
         adv-b
           (advance-b)
           (go next)
         finished-a
           (format t "~&finish-a")
           (format t " ~10t ~D ~D ~20T~D ~D" a0 a1 b0 b1)
           (return (values (nreverse result) min? max?))
         finished-b
           (emit a0 a1)
           (cond
             (a-intervals
              (loop for (left . right) in a-intervals
                    minimize left into left-min using minf
                    maximize right into right-max using maxf
                    collect (region-cons left right) into tail using region-cons
                    finally (return-from
                              subtract-intervals
                              (values (nreconc result tail)
                                      (minf min? left-min)
                                      (maxf max? right-max)))))
             (t
              (return (values (nreverse result) min? max?))))
         next
           (go loop-head))))))


;;; `Union-intervals' computes (nodestructively) the union of the two argument
;;; intervals.

(defun union-intervals (A-intervals B-intervals)
  (declare (eliminate-for-gsi))

  (let ((union-intervals ())
        a0 a1 b0 b1)

    (loop (when (or (null A-intervals) (null B-intervals))
            (return (nreconc union-intervals
                             (copy-intervals (or A-intervals B-intervals)))))

          ;; Normalize so that [a0, a1) = the first interval in A-intervals is leftmost
          (setq a0 (interval-left (first A-intervals)))
          (setq b0 (interval-left (first B-intervals)))
          (unless (<=f a0 b0)
            (rotatef A-intervals B-intervals)
            (rotatef a0 b0))

          ;; A = [ ...                <- here a0 <= b0 so the intervals are ordered like this
          ;; B =    [ ...

          (setq a1 (interval-right (pop A-intervals)))

          ;; Extend [a0, a1) on the right to the maximal contiguous sequence of intervals

          (loop        ;; here we have an interval a = [a0, a1) disjoint from A but possibly
                ;; intersecting B = [b0, b1) U B'

                (cond ((or (null B-intervals)
                           (<f a1 (interval-left (first B-intervals))))

                       ;; A = [  ) ...        <- here a1 < b0 so the intervals
                       ;;                  are ordered like this
                       ;; B =      [ ...
                       (region-push (make-interval a0 a1) union-intervals)
                       (return))
                      (t
                       (setq b1 (interval-right (pop B-intervals)))

                       (cond ((<=f b1 a1)
                              ;; A = [      ) ...   <- here b1 <= a1 so b is inside a
                              ;; B =   [  ) ...
                              )
                             (t
                              ;; A = [    )  U  A'       =>  [      ))  U  B'
                              ;; B =   [[     ))  U  B'  =>  A'
                              ;; Coalesce from a1 to b1 and continue coalescing from A

                              (setq a1 b1)
                              (rotatef A-intervals B-intervals)))))))))



;;;; Testing Interval Operations


;;; This section implements a full coverage test for interval operations.
;;; It works by defining a mapping from intervals into bit vectors stored
;;; in fixnum.  Each interval operation has an equivalent logical operation,
;;; for example union-intervals is equivalent to logior.  Functions are
;;; defined in here which will ring all the changes for bit vectors of
;;; N bits.

#+development
(defun intervals-to-bits (intervals low high)
  (let ((result 0)
        (index (- high low)))
    (flet ((f (b) (setf (ldb (byte 1 (decf index)) result) b)))
      (loop as start = low then right
            for (left . right) in intervals
            do
        (loop for i from start below left do (f 0))
        (loop for i from left below right do  (f 1))))
    result))

#+development
(defun bits-to-intervals (bits low high)
  (loop with result = nil
        finally (return (nreverse result))
        with entering-edge? = nil
        for index from (- high low -1) downto 0
        as in = (logbitp index bits)
        do (cond
             ((and in (not entering-edge?))
              (setf entering-edge? index))
             ((and (not in) entering-edge?)
              (push (make-interval
                      (- high (shiftf entering-edge? nil) 1)
                      (- high index 1))
                 result)))))

#+development
(defun test-interval-test-harness ()
  (loop for a from 0 to 300
        for i = (ash a 1)
        unless (= i (intervals-to-bits (bits-to-intervals i 0 10) 0 10))
          do (error "~10B" i))
  :ok)

#+development
(defun intervals-to-string (intervals low high)
  (substitute
    #\0 #\space
    (format
      nil
      "~VB"
      (- high low) (intervals-to-bits intervals low high))))


#+development
(defun test-inner (bit-function interval-function)
  (loop for a from 0 to 1024
        as in1 = (ash a 1)
        as int1 = (bits-to-intervals in1 0 12)
        do
    (loop for a from 0 to 1024
          as in2 = (ash a 1)
          as int2 = (bits-to-intervals in2 0 12)
          as result = (funcall bit-function  in1 in2)
          as intr = (funcall interval-function  int1 int2)
          as result? = (intervals-to-bits intr 0 12)
         unless (= result result?)
         do (error "Oh No.")))
  :ok)

#+development
(defun test-subtract-intervals ()
  (test-inner #'logandc2 'subtract-intervals))

#+development
(defun test-union-intervals ()
  (test-inner #'logior 'union-intervals))

#+development
(defun test-intersect-intervals ()
  (test-inner #'logand 'intersect-intervals))

#+development
(defun test-all-interval-operations ()
  (macrolet ((f (x) `(progn (print ',x) (print (,x)))))
    (f test-subtract-intervals)
    (f test-union-intervals)
    (f test-intersect-intervals)))

;; This takes a LONG time.




;;;; The `Region-Strip' List-Structure and Operations



;;; A `region-strip' is simply a pair consisting of a fixnum along with a list of
;;; intervals.  They are used to represent the horizontal strips of rectangles
;;; that comprise the region data structure.  The region-strip-top fixnum
;;; specifies the top (y-coordinate) of the strip and the intervals list
;;; specifies the list of right-open intervals [left, right) of the rectangles
;;; within the strip.  Note that the bottom of the strip is not specified but is
;;; implicitly determined as the top of any following strip in the region (the
;;; bottom of the bottom-most strip is specified by appending a dummy
;;; bottom-most strip whose intervals is null). The intervals are disjoint and
;;; are ordered left-to-right by increasing coordinate value.

(def-list-structure (region-strip (:consing-function region-cons-macro)
                                  (:constructor make-region-strip-function))
  (region-strip-top . region-strip-intervals))

;; Can't optimize the accessors since a region-strip may be NIL.

(def-substitution-macro make-region-strip (region-strip-top region-strip-intervals)
  (region-cons-macro region-strip-top region-strip-intervals))


;;; An `empty-region-strip' may be defined as any region-strip whose
;;; region-strip-interval is null (i.e. whose cdr is null).  We choose to
;;; define the empty-region-strip to be () since this allows us to avoid
;;; consing in the common case that the empty-region-strip is used as an
;;; initial value.  Note that the region-strip-top of an empty-region-strip is
;;; undefined.

(defmacro make-empty-region-strip () ())

(def-substitution-macro copy-region-strip (strip)
  (when strip
    (make-region-strip
      (region-strip-top strip)
      (copy-intervals (region-strip-intervals strip)))))

(def-substitution-macro reclaim-region-strip (region-strip)
  (when region-strip
    (reclaim-intervals (cdr-of-cons region-strip))
    (reclaim-region-cons-macro region-strip)))

(def-substitution-macro copy-region-strips (strips)
  (loop for strip in strips
        collect (copy-region-strip strip)
          using region-cons-macro))

(def-substitution-macro region-strip-equal (strip1 strip2)
  (and (=f (region-strip-top strip1)
           (region-strip-top strip2))
       (=f (length (region-strip-intervals strip1))
           (length (region-strip-intervals strip2)))
       (loop for i1 in (region-strip-intervals strip1)
             for i2 in (region-strip-intervals strip2)
             always (intervals-equal i1 i2))))





;;;; The `Region-Bounding-Box' List-Structure and Operations



;;; A `region-bounding-box' is simply a rectangle specified by the intervals which
;;; comprise its horizontal and vertical sides. It is used as a component of
;;; regions in order to optimize certain region operations (and is otherwise not
;;; needed in regions since the bounding box is computable from the regions
;;; strips). The box boundary is assumed to be open on its right and bottom
;;; borders and closed elsewhere (i.e. the points comprising the right and
;;; bottom borders of the box are not considered as included in the box).

(def-list-structure (region-bounding-box (:consing-function region-cons-macro)
                                         (:optimize t))
  (region-bounding-box-x-interval . region-bounding-box-y-interval))

(def-substitution-macro reclaim-region-bounding-box (box)
  (reclaim-interval (region-bounding-box-x-interval box))
  (reclaim-interval (region-bounding-box-y-interval box))
  (reclaim-region-cons box))

(def-substitution-macro copy-region-bounding-box (box)
  (make-region-bounding-box
    (copy-interval (region-bounding-box-x-interval box))
    (copy-interval (region-bounding-box-y-interval box))))

(defmacro left-edge-of-region (region)
  `(interval-left
     (region-bounding-box-x-interval (region-bounding-box ,region))))

(defmacro top-edge-of-region (region)
  `(interval-left
     (region-bounding-box-y-interval (region-bounding-box ,region))))

(defmacro right-edge-of-region (region)
  `(interval-right
     (region-bounding-box-x-interval (region-bounding-box ,region))))

(defmacro bottom-edge-of-region (region)
  `(interval-right
     (region-bounding-box-y-interval (region-bounding-box ,region))))

(def-substitution-macro set-region-bounding-box (box left top right bottom)
  (set-interval (region-bounding-box-x-interval box) left right)
  (set-interval (region-bounding-box-y-interval box) top  bottom)
  box)

(defun point-in-region-bounding-box-p (box x y)
  (and (point-in-right-open-interval-p (region-bounding-box-x-interval box) x)
       (point-in-right-open-interval-p (region-bounding-box-y-interval box) y)))


(def-substitution-macro bounding-box-equal (box1 box2)
  (and (intervals-equal (region-bounding-box-x-interval box1)
                        (region-bounding-box-x-interval box2))
       (intervals-equal (region-bounding-box-y-interval box1)
                        (region-bounding-box-y-interval box2))))

(defun region-bounding-box-empty-p (box)
  (declare (eliminate-for-gsi))
  (or (right-open-interval-empty-p (region-bounding-box-x-interval box))
      (right-open-interval-empty-p (region-bounding-box-y-interval box))))

(defun union-region-bounding-box (box1 box2)
  (declare (eliminate-for-gsi))
  (and box1 box2         ; todo: remove these guards when done debugging
       (cond ((region-bounding-box-empty-p box1) (copy-region-bounding-box box2))
             ((region-bounding-box-empty-p box2) (copy-region-bounding-box box1))
             (t (make-region-bounding-box
                  (bounding-interval (region-bounding-box-x-interval box1)
                                     (region-bounding-box-x-interval box2))
                  (bounding-interval (region-bounding-box-y-interval box1)
                                     (region-bounding-box-y-interval box2)))))))

(defun region-bounding-box-intersect-p (box1 box2)
  (declare (eliminate-for-gsi))
  (and (right-open-intervals-intersect-p (region-bounding-box-x-interval box1)
                                         (region-bounding-box-x-interval box2))
       (right-open-intervals-intersect-p (region-bounding-box-y-interval box1)
                                         (region-bounding-box-y-interval box2))))






;;;; The `Region' List-Structure and Operations



;;; A region specifies a set of rectangles whose coordinates are fixnums (or a
;;; subtype of fixnum, such as window coordinate).  Each non-empty region has a
;;; bounding box which in included only to optimize certain region operations (and is
;;; otherwise not needed in regions since the bounding box is computable from the
;;; regions strips).  The bounding box (and the rectangles in the region) are assumed
;;; to be open on the right and bottom borders and closed elsewhere (i.e.  the points
;;; comprising the right and bottom borders are not included).

;;; The rectangles are grouped into horizontal strips containing rectangles all
;;; of the same height.  The list of strips in the region is ordered
;;; top-to-bottom (by increasing y-coordinate) and the rectangles within the
;;; strip are representated as a list of intervals ordered left-to-right (by
;;; increasing x-coordinate).  A strip is specified by its top (y-coordinate)
;;; and by the list of intervals [left, right) giving the sides of the
;;; rectangles within the strip.  The intervals in the strip are disjoint and
;;; are ordered left-to-right by increasing coordinate value.

;;; Note that the bottom of a strip is not specified in the strip itself - the
;;; bottom is implicitly determined as the top of any following strip in the
;;; region (the bottom of the bottom-most strip is specified by appending a
;;; dummy bottom-most strip whose list of intervals is null).

(def-list-structure (region (:consing-function region-cons-macro)
                            (:optimize t))
  (region-strips . region-bounding-box))

(defun reclaim-region (region?)
  (declare (eliminate-for-gsi))
  ;; TODO: temporary disable it.
  #+SymScale
  nil
  #-SymScale
  (when region?
    #+development (assert (development-region-p region?))
    (reclaim-region-bounding-box (region-bounding-box region?))
    (loop for strip in (region-strips region?) doing
      (reclaim-region-strip strip))
    (reclaim-region-list-macro (region-strips region?))
    (reclaim-region-cons-macro region?)))

(defun copy-region (region)
  (declare (eliminate-for-gsi))
  #+development (assert (development-region-p region))
  (make-region
    (copy-region-strips (region-strips region))
    (copy-region-bounding-box (region-bounding-box region))))


(defmacro empty-region-p (region)
  `(null (region-strips ,region)))

(defun make-empty-region ()
  (declare (eliminate-for-gsi))
  (make-region
    ;; An empty region has no region-strips
    ()
    ;; The bounding-box of an empty region is undefined. Don't use it.
    (make-region-bounding-box (make-interval 0 0)
                              (make-interval 0 0))))

;; We could keep just a one of these around, like evaluation-true-value.
;; Or do we mutate them?

;;; The function `make-unbounded-region' creates an "unbounded" region, which
;;; would be the identity element for intersect-region. We need this to be
;;; bigger than any scaled workspace coordinate we may encounter, and want it to
;;; be less that most-positive-fixnum so that we can add or subtract two of them
;;; without overflow.

(defun make-unbounded-region ()
  (declare (eliminate-for-gsi))
  (let ((infinity (ash most-positive-fixnum -2)))
    (make-region-from-rectangle (-f infinity) (-f infinity) infinity infinity)))

#+development
(defun unbounded-region-p (region)
  (multiple-value-bind (left top right bottom)
      (region-bounding-rectangle region)
    (let ((infinity (ash most-positive-fixnum -2)))
      (and (=f left (-f infinity))
           (=f top  (-f infinity))
           (=f right  infinity)
           (=f bottom infinity)))))

(defun region-bounding-rectangle (region)
  (declare (eliminate-for-gsi))
  (let* ((region-bounding-box (region-bounding-box region))
         (bounding-box-x (region-bounding-box-x-interval region-bounding-box))
         (bounding-box-y (region-bounding-box-y-interval region-bounding-box)))
    (values (interval-left  bounding-box-x)
            (interval-left  bounding-box-y)
            (interval-right bounding-box-x)
            (interval-right bounding-box-y))))

(defun make-region-from-rectangle (left top right bottom)
  (declare (no-op-for-gsi))
  (cond ((and (<=f left right)
              (<=f top bottom))
         (make-region
           (region-list-macro
             (make-region-strip top
                                (region-list-macro
                                  (make-interval left right)))
             (make-region-strip bottom (region-list)))
           (make-region-bounding-box
             (make-interval left right)
             (make-interval top bottom))))
        (t
         (make-empty-region))))

;;; `with-region-from-rectangle-void' executes a body with a region
;;; with the give rectangular shape.  The body can return no values.

(defmacro with-region-from-rectangle-void
    ((region left top right bottom) &body body)
  `(let ((,region (make-region-from-rectangle ,left ,top ,right ,bottom)))
     ,@body
     (reclaim-region ,region)))



;;; The function `simplify-region' replaces the region with another region,
;;; guarenteed to enclose the given region, and usually of lower complexity.

(defun simplify-region (region)
  (declare (eliminate-for-gsi))
  (multiple-value-bind (left top right bottom)
      (region-bounding-rectangle region)
    (prog1
        (make-region-from-rectangle left top right bottom)
      (reclaim-region region))))


;;; The function `region-complexity' returns a non-negative fixnum which
;;; is larger for more complex regions.  An empty region has complexity
;;; zero.  A rectangular region has complexity one.

(defun region-complexity (region)
  (declare (eliminate-for-gsi))
  (maxf 0 (1-f (length (region-strips region)))))



;;; The function `regions-possibly-intersect-p' is true if the regions
;;; could possibly have a non-empty intersection.

(defun regions-possibly-intersect-p (region-1 region-2)
  (declare (eliminate-for-gsi))
  (and (not (empty-region-p region-1))
       (not (empty-region-p region-2))
       (multiple-value-bind (left-1 top-1 right-1 bottom-1)
           (region-bounding-rectangle region-1)
         (multiple-value-bind (left-2 top-2 right-2 bottom-2)
             (region-bounding-rectangle region-2)
           (rectangles-overlap-p
             left-1 top-1 right-1 bottom-1
             left-2 top-2 right-2 bottom-2)))))


(defun region-equal (region1 region2)
  (declare (eliminate-for-gsi))
  (and (bounding-box-equal (region-bounding-box region1)
                           (region-bounding-box region2))
       (=f (length (region-strips region1))
           (length (region-strips region2)))
       (loop for s1 in (region-strips region1)
             for s2 in (region-strips region2)
             always (region-strip-equal s1 s2))))



(def-system-variable scratch-rectangle-region utilities3
  (:funcall make-region-from-rectangle 0 0 0 0))

(def-substitution-macro set-scratch-rectangle-region (left top right bottom)
  (let ((strips (region-strips scratch-rectangle-region)))
    (setf (region-strip-top (first  strips)) top)
    (setf (region-strip-top (second strips)) bottom)
    (set-interval (first (region-strip-intervals (first strips))) left right))
  (set-region-bounding-box (region-bounding-box scratch-rectangle-region)
                           left top right bottom)
  scratch-rectangle-region)



(defun rectangle-in-region-p (left top right bottom region)
  (declare (eliminate-for-gsi))
  (let ((rectangle (set-scratch-rectangle-region left top right bottom)))
    (and (regions-possibly-intersect-p rectangle region)
         (let ((intersection (intersect-region rectangle region)))
           (prog1
               (region-equal rectangle intersection)
             (reclaim-region intersection))))))



;;; The function `add-rectangle-to-region' checks for the given
;;; rectangle being empty in either dimension.

(defun-simple add-rectangle-to-region (left top right bottom region)
  (declare (eliminate-for-gsi))
  (cond ((and (<=f left right)
              (<=f top bottom))
         (let ((result (union-region
                         (set-scratch-rectangle-region left top right bottom)
                         region)))
           (reclaim-region region)
           result))
        (t
         region)))


(defun-simple remove-rectangle-from-region (left top right bottom region)
  (declare (eliminate-for-gsi))
  (declare (eliminate-for-gsi))
  (cond ((and (<=f left right)
              (<=f top bottom))
         (prog1
             (subtract-region region
                              (set-scratch-rectangle-region left top right bottom))
           (reclaim-region region)))
        (t
         region)))



;;; `Shift-region' distructively offsets the region given by the x/y delta
;;; given.

(defun shift-region (region delta-x delta-y)
  (declare (eliminate-for-gsi))
  (dolist (strip (region-strips region))
    (incff (region-strip-top strip) delta-y)
    (unless (=f 0 delta-x)
      (dolist (interval (region-strip-intervals strip))
        (shift-interval interval delta-x))))
  (let ((box (region-bounding-box region)))
    (shift-interval (region-bounding-box-x-interval box) delta-x)
    (shift-interval (region-bounding-box-y-interval box) delta-y))
  region)






;;; `Union-region' computes (nondestructively) the union of the its two argument
;;; regions.  The algorithm reduces the two-dimensional problem to two
;;; one-dimensional problems by projecting along each axis.  On projection to the y
;;; axis the problem reduces to computing the (partition) refinement of the intervals
;;; specified by the boundaries of the horizontal strips.  On projection to the x
;;; axis the problem reduces to computing a union of intervals.  In simpler language:
;;; the problem is reduced to combining two ordered lists of points - each point
;;; corresponding to a strip boundary.  The points are colored with intervals, and
;;; the colors are combined via interval union.
;;;
;;; Note that union-region depends on the fact that the intervals list of the
;;; terminal dummy strip is () = identity element for union-intervals.

(defun union-region (region1 region2)
  (declare (eliminate-for-gsi))
  #+development (assert (development-region-p region1))
  #+development (assert (development-region-p region2))

  ;; Special Cases
  (when (empty-region-p region1) (return-from union-region (copy-region region2)))
  (when (empty-region-p region2) (return-from union-region (copy-region region1)))

  ;; The hard work.
  (macrolet ((swap-strips ()
               '(progn (rotatef strips1 strips2)
                 (rotatef top1 top2)
                 (rotatef prior-strip1 prior-strip2))))

    (loop with strips-union = ()

          with strips2 = (region-strips region2)
          and  prior-strip2 = (make-empty-region-strip)
          with top2 = (region-strip-top (first strips2))

          for strips1 on (region-strips region1)
          and prior-strip1 = (make-empty-region-strip) then (first strips1)
          for top1 = (region-strip-top (first strips1))

          initially
            (when (null strips2) (swap-strips)) ; skip loop if either strip is null

          unless (=f top1 top2)

            do (when (>f top1 top2) (swap-strips))        ; get topmost strips into strips1

               (let ((strip-intervals
                       (union-intervals (region-strip-intervals (first strips1))
                                        (region-strip-intervals prior-strip2))))

                 ;; Two identical contiguous strips simply coalesce into one taller strip

                 (if (intervals-equal strip-intervals
                                      (region-strip-intervals (first strips-union)))
                     (reclaim-intervals strip-intervals)
                     (region-push (make-region-strip top1 strip-intervals)
                                  strips-union)))
          finally
            (return
              (make-region
                (nreconc strips-union (copy-region-strips strips2))
                (union-region-bounding-box (region-bounding-box region1)
                                           (region-bounding-box region2)))))))


;;; `Intersect-region-p-1' returns true if the two regions might overlap.
;;; It is fast checking only for empty regions and the region bounding boxs.

(defun intersect-region-p-1 (region-a region-b)
  (declare (eliminate-for-gsi))
  (not
    (or (empty-region-p region-a)
        (empty-region-p region-b)
        (let ((bounding-box-a (region-bounding-box region-a))
              (bounding-box-b(region-bounding-box region-b)))
          (or (not (right-open-intervals-intersect-p
                     (region-bounding-box-x-interval bounding-box-a)
                     (region-bounding-box-x-interval bounding-box-b)))
              (not (right-open-intervals-intersect-p
                     (region-bounding-box-y-interval bounding-box-a)
                     (region-bounding-box-y-interval bounding-box-b))))))))



;;; The function `regions-intersect-p' returns T if the two regions intersect
;;; and NIL otherwise.

(defun regions-intersect-p (region-a region-b)
  (declare (eliminate-for-gsi))
  (when (intersect-region-p-1 region-a region-b)
    (let ((intersection (intersect-region region-a region-b)))
      (prog1
          (not (empty-region-p intersection))
        (reclaim-region intersection)))))




;;; `Intersect-region' returns a fresh region containing those portions that
;;; region-a and region-b share in common.

(defun intersect-region (region-a region-b)
  (declare (eliminate-for-gsi))
  #+development (assert (development-region-p region-a))
  #+development (assert (development-region-p region-b))
  (unless (intersect-region-p-1 region-a region-b)
    (return-from intersect-region (make-empty-region)))
  (let ((region-strips-a (region-strips region-a))
        (region-strips-b (region-strips region-b))
        result-top  result-strips
        result-left result-right
        a0 a1 ai
        b0 b1 bi
        last-bottom? last-intervals?)
    (block nil
      (macrolet ((db (&rest args)
                   ;; `(format t ,@args)
                   nil)
                 (advance-a ()
                   `(progn
                      (db "~&adv-a")
                      (unless (cdr region-strips-a) (go finished-a))
                      (let ((a (pop region-strips-a)))
                        (setf ai (region-strip-intervals a))
                        (setf a0 (region-strip-top a))
                        (setf a1 (region-strip-top (first region-strips-a))))))
                 (advance-b ()
                   `(progn
                      (db "~&adv-b")
                      (unless (cdr region-strips-b) (go finished-b))
                      (let ((b (pop region-strips-b)))
                        (setf bi (region-strip-intervals b))
                        (setf b0 (region-strip-top b))
                        (setf b1 (region-strip-top (first region-strips-b))))))
                 (emit (top bottom)
                   `(progn
                      (db " emit ~D ~D" ,top ,bottom)
                      (unless (=f ,top ,bottom)
                        (multiple-value-bind (cantidate-intervals? left? right?)
                            (intersect-intervals ai bi)
                          (when cantidate-intervals?
                            (cond
                              (last-bottom?
                               (setf result-left (minf result-left left?))
                               (setf result-right (maxf result-right right?)))
                              (t
                               (setf result-left left?)
                               (setf result-right right?)
                               (setf result-top ,top)))
                            (cond
                              ;; merge with previous strip?
                              ((and last-bottom?
                                    (=f last-bottom? ,top)
                                    (intervals-equal cantidate-intervals?
                                                     last-intervals?))
                               (db " merge")
                               (reclaim-intervals cantidate-intervals?))
                              (t
                               ;; Gap before this strip
                               (when last-bottom?
                                 (unless (=f last-bottom? ,top)
                                   (db " gap")
                                   (region-push (make-region-strip last-bottom? nil)
                                                result-strips)))
                               ;; Emit this strip
                               (db " !")
                               (region-push (make-region-strip ,top cantidate-intervals?)
                                            result-strips)
                               (setf last-intervals? cantidate-intervals?)))
                            (setf last-bottom? ,bottom)))))))
        (tagbody
           (advance-a)
           (advance-b)
         loop-body
           (db "~20t ~D ~D ~26T~D ~D ~32T" a0 a1 b0 b1)
           (cond
             ((<f a0 b0)    ;; [a0 .. [b0
              (cond
                ((<f a1 b0)       ;;  [a0..a1)..[b0..b1)        advance A
                 (go adv-a))
                ((<=f b1 a1)      ;;  [a0..[b0..b1)..a1)  emit, advance B
                 (emit b0 b1)
                 (go adv-b))
                ((<f a1 b1)       ;;  [a0..[b0..a1)..b1)  emit, advance A
                 (emit b0 a1)
                 (go adv-a))))
             (t        ;; [b0 .. [a0
              (cond
                ((<f b1 a0)       ;;  [b0..b1)..[a0..a1)        advance B
                 (go adv-b))
                ((<=f a1 b1)      ;;  [b0..[a0..a1)..b1)  emit, advance B
                 (emit a0 a1)
                 (go adv-a))
                ((<f b1 a1)       ;;  [b0..[a0..b1)..a1)  emit, advance A
                 (emit a0 b1)
                 (go adv-b)))))
         adv-a
           (advance-a)
           (go next)
         adv-b
           (advance-b)
           (go next)

         finished-a
         finished-b
           (db " finish")
           (return
             (cond
               (last-bottom?
                (db " .")
                (make-region
                  (progn (region-push (make-region-strip last-bottom? nil)
                                      result-strips)
                         (nreverse result-strips))
                  (make-region-bounding-box
                    (make-interval result-left result-right)
                    (make-interval result-top last-bottom?))))
               (t
                (db " empty")
                (make-region
                  nil
                  (make-region-bounding-box
                    (make-interval 0 0)
                    (make-interval 0 0))))))

         next
           (go loop-body))))))

;;; `Subtract-region' returns a fresh region that represents those portions of
;;; region-a not obscured by region-b.

(defun subtract-region (region-a region-b)
  (declare (eliminate-for-gsi))
  (unless (intersect-region-p-1 region-a region-b)
    (return-from subtract-region (copy-region region-a)))
  (let ((region-strips-a (region-strips region-a))
        (region-strips-b (region-strips region-b))
        result-top  result-strips
        result-left result-right
        a0 a1 ai
        b0 b1 bi
        last-bottom? last-intervals?)
    (block nil
      (macrolet ((db (&rest args)
                   nil ; `(format t ,@args)
                   )
                 (advance-a ()
                   `(progn
                      (db "~&adv-a")
                      (unless (cdr region-strips-a) (go finished-a))
                      (let ((a (pop region-strips-a)))
                        (setf ai (region-strip-intervals a))
                        (setf a0 (region-strip-top a))
                        (setf a1 (region-strip-top (first region-strips-a))))))
                 (advance-b ()
                   `(progn
                      (db "~&adv-b")
                      (unless (cdr region-strips-b) (go finished-b))
                      (let ((b (pop region-strips-b)))
                        (setf bi (region-strip-intervals b))
                        (setf b0 (region-strip-top b))
                        (setf b1 (region-strip-top (first region-strips-b))))))
                 (emit-1 (top bottom cantidate-intervals? left? right?)
                   ;; Fold these intervals into the current output strips.
                   `(when ,cantidate-intervals?
                      (cond
                        (last-bottom?
                         (setf result-left (minf result-left ,left?))
                         (setf result-right (maxf result-right ,right?)))
                        (t
                         (setf result-left ,left?)
                         (setf result-right ,right?)
                         (setf result-top ,top)))
                      (cond
                        ;; merge with previous strip?
                        ((and last-bottom?
                              (=f last-bottom? ,top)
                              (intervals-equal ,cantidate-intervals?
                                               last-intervals?))
                         (db " merge")
                         (reclaim-intervals ,cantidate-intervals?))
                        (t
                         ;; Gap before this strip
                         (when last-bottom?
                           (unless (=f last-bottom? ,top)
                             (db " gap")
                             (region-push (make-region-strip last-bottom? nil)
                                          result-strips)))
                         ;; Emit this strip
                         (db " !")
                         (region-push (make-region-strip ,top ,cantidate-intervals?)
                                      result-strips)
                         (setf last-intervals? ,cantidate-intervals?)))
                      (setf last-bottom? ,bottom)))
                 (emit-a (top bottom)
                   ;; Emit a strip of A, uneffected by B.
                   ;;; TBD
                   `(progn
                      (db " emit-a ~D ~D" ,top ,bottom)
                      (unless (=f ,top ,bottom)
                        (loop for (left . right) in ai
                              minimize left into left-max
                              maximize right into right-max
                              collect (region-cons left right)
                                into cantidate-intervals? using region-cons
                              finally
                                (emit-1 ,top ,bottom
                                        cantidate-intervals?
                                        left-max
                                        right-max)))))

                 (emit-a-b (top bottom)
                   ;; Emit a strip of A minus B.
                   `(progn
                      (db " emit-a-b ~D ~D" ,top ,bottom)
                      (unless (=f ,top ,bottom)
                        (multiple-value-bind (cantidate-intervals? left? right?)
                            (subtract-intervals ai bi)
                          (emit-1 ,top ,bottom cantidate-intervals? left? right?))))))

        (tagbody
           (advance-a)
           (advance-b)
         loop-body
           (db "~20t ~D ~D ~26T~D ~D ~32T" a0 a1 b0 b1)
           (cond
             ((<f a0 b0)    ;; [a0 .. [b0
              (cond
                ((<f a1 b0)       ;;  [a0..a1)..[b0..b1)
                 (emit-a a0 a1)
                 (go adv-a))
                ((<=f b1 a1)      ;;  [a0..[b0..b1)..a1)
                 (emit-a a0 b0)
                 (emit-a-b b0 b1)
                 (setf a0 b1)
                 (go adv-b))
                ((<f a1 b1)       ;;  [a0..[b0..a1)..b1)
                 (emit-a a0 b0)
                 (emit-a-b b0 a1)
                 (go adv-a))))
             (t        ;; [b0 .. [a0
              (cond
                ((<f b1 a0)       ;;  [b0..b1)..[a0..a1)
                 (go adv-b))
                ((<=f a1 b1)      ;;  [b0..[a0..a1)..b1)
                 (emit-a-b a0 a1)
                 (go adv-a))
                ((<f b1 a1)       ;;  [b0..[a0..b1)..a1)
                 (emit-a-b a0 b1)
                 (setf a0 b1)
                 (go adv-b)))))
         adv-a
           (advance-a)
           (go next)
         adv-b
           (advance-b)
           (go next)



         finished-b
           (db " finished-b")
           ;; record the remaining parts of A.
           (when (<f b1 a1)
             (emit-a a0 a1))
           (loop
             (advance-a)
             (emit-a a0 a1))

         finished-a
           (db " finished-a")
           (db " ~10t ~D ~D ~20T~D ~D" a0 a1 b0 b1)
           (return
             (cond
               (last-bottom?
                (make-region
                  (progn (region-push (make-region-strip last-bottom? nil)
                                      result-strips)
                         (nreverse result-strips))
                  (make-region-bounding-box
                    (make-interval result-left result-right)
                    (make-interval result-top last-bottom?))))
               (t
                (make-region
                  nil
                  (make-region-bounding-box
                    (make-interval 0 0)
                    (make-interval 0 0))))))

         next
           (go loop-body))))))



;;;; Testing Harness of Region Arithmetic

#+development
(defun bits-to-region (bits)
  (setf bits (ash bits 1))
  (if (zerop bits)
      nil
      (loop with result-strips
            with left = 5
            with right = 10
            with top?
            with bottom?
            finally (return (make-region (nreverse result-strips)
                                         (make-region-bounding-box
                                           (make-interval left right)
                                           (make-interval top? bottom?))))
            with intervals = (list (make-interval left right))
            with in-edge?
            for i from 0 to (integer-length bits)
            as bit-is-inside = (logbitp i bits)
            do
        ;; (print (list i in-edge? bit-is-inside))
        (cond
          ((and in-edge? (not bit-is-inside))
           (unless top?
             (setf top? in-edge?))
           (region-push (make-region-strip
                          (shiftf in-edge? nil)
                          (copy-intervals intervals)) result-strips)
           (setf bottom? i)
           (region-push (make-region-strip bottom? nil) result-strips))
          ((and (not in-edge?) bit-is-inside)
           (setf in-edge? i))))))

#+development
(defun region-to-bits (region)
  (let ((result 0))
    (loop for (strip . remaining-strips) = (region-strips region)
                                         then remaining-strips
          while remaining-strips
          when (region-strip-intervals strip)
            do
              (loop for i from (region-strip-top strip)
                          below (region-strip-top (first remaining-strips))
                    do (setf (ldb (byte 1 i) result) 1)))
    (ash result -1)))

#+development
(defun test-region-harness ()
  (loop for i from 0 to 1024
        as region = (bits-to-region i)
        as i2 = (region-to-bits region)
        unless (eql i i2)
          do (error "Oh No"))
  :OK)

#+development
(defun test-region-inner (bit-function region-function)
  (loop with extent-of-test = 1050
        for a from 0 to extent-of-test
        as in1 = (ash a 1)
        as int1 = (bits-to-region in1)
        do
    (loop for a from 0 to extent-of-test
          as in2 = (ash a 1)
          as int2 = (bits-to-region in2)
          as result = (funcall bit-function  in1 in2)
          as intr = (funcall region-function  int1 int2)
          as result? = (region-to-bits intr)
         unless (= result result?)
         do (error "Oh No.")))
  :ok)

#+development
(defun test-regions ()
  (declare (eliminate-for-gsi))
  (macrolet ((f (a b)
               `(progn
                  (print ',a)
                  (print (test-region-inner ',b ',a)))))
    (f intersect-region logand)
    (f union-region logior)
    (f subtract-region logandc2)))






;;; `Do-region-rectangles' iterates over the rectangles in region binding left,
;;; top, right, bottom appropriately for each component rectangle.  The
;;; iteration proceeds in the order english text is read.  The :new-strip-p key
;;; specifies a boolean variable to be bound true if the current rectangle is
;;; the first rectangle in a strip.  :clip-to is an optional clipping rectangle
;;; to which all region rectangles will be clipped.

;;; The two-dimensional iteration maps naturally to two separate loops over the
;;; horizontal and vertical components, both of which may be viewed as a
;;; one-dimensional iteration over intervals (by appropriately defining left,
;;; right, and empty-p for the vertical intervals in region strips and for the
;;; horizontal intervals in a strip).

(defmacro do-region-rectangles (((left top right bottom) region
                                 &key reverse-horizontal-p reverse-vertical-p
                                 clip-to new-strip-p)
                                &body body)
  (gensym-dstruct-bind ((left-edge-of-clip?
                         top-edge-of-clip?
                         right-edge-of-clip?
                         bottom-edge-of-clip?)
                       clip-to)
    (avoiding-variable-capture (region reverse-horizontal-p reverse-vertical-p
                                       left-edge-of-clip?
                                       top-edge-of-clip?
                                       right-edge-of-clip?
                                       bottom-edge-of-clip?
                                       &aux region-strip)
      `(do-region-strips ((,top ,bottom ,region-strip)
                          (,region ,reverse-vertical-p ,top-edge-of-clip? ,bottom-edge-of-clip?))
         (do-intervals-of-region-strip ((,left ,right ,new-strip-p)
                                        (,region-strip ,reverse-horizontal-p
                                                       ,left-edge-of-clip? ,right-edge-of-clip?))
           ,@body)))))



;;; `Do-region-strips' is a internal macro in support of do-region-rectangles.

(defmacro do-region-strips (((top bottom region-strip)
                             (region &optional reverse-p top-edge-of-clip? bottom-edge-of-clip?))
                            &body body)
  `(progn
     ,@(when reverse-p
         `((when ,reverse-p
             (setf (region-strips ,region) (nreverse (region-strips ,region))))))


     (loop with ,region-strip
           with ,top
           with ,bottom
           for (region-strip-1 . remaining-region-strips) on (region-strips ,region)
           while remaining-region-strips
           as region-strip-2 = (first remaining-region-strips)
           as a = (region-strip-top region-strip-1)
           as b = (region-strip-top region-strip-2)
           do

       ,@(when top-edge-of-clip?
           `((when ,top-edge-of-clip?
               (setf a (pin-in-range ,top-edge-of-clip? a ,bottom-edge-of-clip?))
               (setf b (pin-in-range ,top-edge-of-clip? b ,bottom-edge-of-clip?)))))

         (unless (=f a b)
           ,@(if reverse-p
                 `((cond (,reverse-p
                          (setf ,top b)
                          (setf ,bottom a)
                          (setf ,region-strip region-strip-2))
                         (t
                          (setf ,top a)
                          (setf ,bottom b)
                          (setf ,region-strip region-strip-1))))

                 `((setf ,top a)
                   (setf ,bottom b)
                   (setf ,region-strip region-strip-1)))
           ,@body))

     ,@(when reverse-p
         `((when ,reverse-p
             (setf (region-strips ,region) (nreverse (region-strips ,region))))))))





;;; `Do-intervals-of-region-strip' is an internal macro of do-region-rectangles.

(defmacro do-intervals-of-region-strip (((left right first-rectangle-p?)
                                         (region-strip
                                           reverse-p
                                           left-edge-of-clip?
                                           right-edge-of-clip?)) &body body)
  `(progn
     ,@(when reverse-p
         `((when ,reverse-p
             (setf (region-strip-intervals ,region-strip)
                   (nreverse (region-strip-intervals ,region-strip))))))


     (loop for (,left . ,right) in (region-strip-intervals ,region-strip)
           ,@(when first-rectangle-p? `(as ,first-rectangle-p? = t then nil))
           do
       ,@(when left-edge-of-clip?
           `((when ,left-edge-of-clip?
               (setf ,left (pin-in-range ,left-edge-of-clip? ,left ,right-edge-of-clip?))
               (setf ,right (pin-in-range ,left-edge-of-clip? ,right ,right-edge-of-clip?)))))
         (unless (=f ,left ,right)
           ,@body))

     ,@(when reverse-p
         `((when ,reverse-p
             (setf (region-strip-intervals ,region-strip)
                   (nreverse (region-strip-intervals ,region-strip))))))))


;;; `Pin-in-range' forces the fixnum x into the given range.

(defmacro pin-in-range (low x high)
  (avoiding-variable-capture (low x high)
    `(if (<=f ,x ,low) ,low
         (if (<=f ,high ,x) ,high
             ,x))))


;;; The macro `transform-region-in-place-macro' destructively applies the given
;;; transforms to each x and y coordinate in the region.  Each transform must
;;; be the name of an operator (function or macro) which takes a single
;;; argument, the coordinate value, and returns the new value.

(defmacro transform-region-in-place-macro (region x-transform y-transform)
  (avoiding-variable-capture (region &aux strip interval box)
    `(progn
       (dolist (,strip (region-strips ,region))
         (setf (region-strip-top ,strip) (,y-transform (region-strip-top ,strip)))
         (dolist (,interval (region-strip-intervals ,strip))
           (transform-interval-macro ,interval ,x-transform ,x-transform)))

       (let ((,box (region-bounding-box ,region)))
         (transform-interval-macro (region-bounding-box-x-interval ,box)
                                   ,x-transform ,x-transform)
         (transform-interval-macro (region-bounding-box-y-interval ,box)
                                   ,y-transform ,y-transform))
       ,region)))


(defun transform-region-in-place (region x-transform y-transform)
  (declare (eliminate-for-gsi))
  (macrolet ((transform-x (x) `(funcall x-transform ,x))
             (transform-y (y) `(funcall y-transform ,y)))
    (transform-region-in-place-macro region transform-x transform-y)))



;;; The macro `transform-region-macro' transforms the region non-destructively
;;; using the given transforms.  Each rectangle of the region is transformed by
;;; the 4-argument transform.

(defmacro transform-region-macro (region transform)
  (avoiding-variable-capture (region &aux left top right bottom
                                     new-left new-top new-right new-bottom
                                     new-region)
    `(let ((,new-region (make-empty-region)))
       (do-region-rectangles ((,left ,top ,right ,bottom) ,region)
         (multiple-value-bind (,new-left ,new-top ,new-right ,new-bottom)
             (,transform ,left ,top ,right ,bottom)
           (setq ,new-region (add-rectangle-to-region ,new-left ,new-top ,new-right ,new-bottom ,new-region))))
       ,new-region)))


#+development
(defun transform-region-test (region)
  (macrolet ((transform (left top right bottom)
               `(values ,left ,top ,right ,bottom)))
    (transform-region-macro region transform)))








#+development
(defun development-region-p (thing)
  (and (consp thing)
       (listp (car thing))
       (let ((box (cdr thing)))
         (and (consp box)
              (consp (car box))
              (consp (cdr box))
              (fixnump (caar box))
              (fixnump (cadr box))
              (fixnump (cdar box))
              (fixnump (cddr box))))))


#+development
(defun area-of-region (region)
  (let ((sum 0))
    (do-region-rectangles ((left top right bottom) region)
      (incf sum (* (- right left) (- bottom top))))
    sum))


(defun number-of-rectangles-in-region (region)
  (declare (eliminate-for-gsi))
  (let ((sum 0))
    (do-region-rectangles ((left top right bottom) region)
      left top right bottom
      (incff sum))
    sum))


;;; `Exactly-one-rectangle-in-region-p' is true if regions contains exactly one
;;; rectangle; otherwise, it returns nil.

(defun exactly-one-rectangle-in-region-p (region)
  (declare (eliminate-for-gsi))
  (let ((sum 0))
    (block count
      (do-region-rectangles ((left top right bottom) region)
	left top right bottom
        (incff sum)
        (if (>=f sum 2)
            (return-from count))))
    (=f sum 1)))



#+development
(defun print-region-rectangles (region)
  (let ((i 0))
    (do-region-rectangles ((left top right bottom) region)
      (format t "~d: ~4d ~4d ~4d ~4d  = ~dx~d~%"
              (incf i)
              left top right bottom
              (-f right left) (-f bottom top))))
  region)


#+development
(defun print-region-bounding-rectangle (region &optional (stream *standard-output*))
  (multiple-value-bind (left top right bottom)
      (region-bounding-rectangle region)
    (format stream "~dx~d+~d+~d"
            (-f right left) (-f bottom top) left top)))

#+development
(def-development-printer print-region (region &optional (stream *standard-output*))
  (when (development-region-p region)
    (printing-random-object (region stream)
      (format stream "Region ")
      (if (unbounded-region-p region)
          (format stream "Unbounded")
          (print-region-bounding-rectangle region stream))
      (format stream " (~d)" (number-of-rectangles-in-region region)))
    region))



#+development
(def-development-describer describe-region
    (region &key (clip-left (maxf)) (clip-top (maxf))
            (clip-right (minf)) (clip-bottom (minf)))
  (when (development-region-p region)
    (when (region-bounding-box region)
      (multiple-value-bind (left top right bottom)
          (region-bounding-rectangle region)
        (format t "Bounding Box: ~3d ~3d  ~3d ~3d,  Linear area: ~d~%"
                left top right bottom (round (sqrt (abs (area-of-region region)))))))
    (format t "Number of rectangles: ~d~%" (number-of-rectangles-in-region region))
    (format t "Complexity: ~d~%" (region-complexity region))
    (format t "top bottom   left..right~%")
    (let (prior-bottom)
      (do-region-rectangles ((left top right bottom) region
                             :clip-to (clip-left clip-top clip-right clip-bottom)
                             :new-strip-p start-of-new-strip-p)

        (when start-of-new-strip-p        ; herald each strip with its top coordinate
          (format t "~&~3d ~3d " top bottom))
        (format t "      ~3d..~3d  ~dx~d" left right (-f right left) (-f bottom top))
        (setq prior-bottom bottom))
      (when prior-bottom
        (format t "~&~3D " prior-bottom)))        ; print bottom of any final strip
    region))


#+development
(defun display-region (region)
  (multiple-value-bind (left-1 top-1 right-1 bottom-1)
      (region-bounding-rectangle region)
    (let* ((width-1 (- right-1 left-1))
           (height-1 (- bottom-1 top-1))
           (scale (if (or (> width-1 40)
                          (> height-1 40))
                      5 1))
           (width (floor width-1 scale))
           (height (floor height-1 scale))
           (rows (loop repeat (1+ height)
                       collect (make-string (1+ width) :initial-element #\space)))
           (map (concatenate 'array rows))
           (rectangle 0)
           (char #\*))
      (format t "~s~%" region)
      (do-region-rectangles ((left top right bottom) region)
        (setq char (aref "0123456789" (mod (incf rectangle) 10)))
        (loop for i from top below bottom
              as row = (aref map (floor (- i top-1) scale))
              doing
          (loop for j from left below right
                as col = (floor (- j left-1) scale)
                doing
            (setf (char row col) char))))

      (loop for i from top-1 below bottom-1 by scale
            for row in rows
            doing
        (format t "~3d: ~a~%" i row))
      region)))





;;;; Generating Code From Patterns




;;; In G2 we typically store rectangles are four adjacent slot values,
;;; four parameters, or four locals.  This gives rise to lots of very
;;; stylized code, for example:

;;;      (setf (left-edge-of-workspace-area-in-window image-plane)
;;;            (x-in-window (left-edge-of-block workspace) image-plane))
;;;      (setf (top-edge-of-workspace-area-in-window image-plane)
;;;            (y-in-window (top-edge-of-block workspace) image-plane))
;;;      (setf (right-edge-of-workspace-area-in-window image-plane)
;;;            (x-in-window (right-edge-of-block workspace) image-plane))
;;;      (setf (bottom-edge-of-workspace-area-in-window image-plane)
;;;            (y-in-window (bottom-edge-of-block workspace) image-plane))

;;; In an on-going attempt to avoid real work, and so I can stop
;;; making all the tedious little typing errors I make in these fragments
;;; of code I have implemented a macro for doing this kind of cruft:

;;;  (with-generated-code-from-pattern-1 ((<left> left top right bottom)
;;;                                         (<x> x y))
;;;     (setf (<left>-edge-of-workspace-area-in-window image-plane)
;;;           (<x>-in-window (<left>-edge-of-block workspace) image-plane)))

;;; The down side ofthis construct is that you can't grep for bottom-edge-of
;;; and find all the uses any more.  To get around that we have
;;; with-code-matching-pattern that shows both the pattern and the expansion
;;; lexically.  That's the preferable interface.

;;; Sadly this isn't useful for predicates, call sites, or bindings.
;;; i.e.
;;;  (or (>w ,left-edge-in-workspace loose-right-edge-of-visible-workspace-area)
;;;         (>w ,top-edge-in-workspace loose-bottom-edge-of-visible-workspace-area)
;;;         (<w ,right-edge-in-workspace loose-left-edge-of-visible-workspace-area)
;;;         (<w ,bottom-edge-in-workspace loose-top-edge-of-visible-workspace-area))

;;; `Generate-code-from-pattern-2' takes a string and replaces
;;; substrings that match those found in the alist of rewirtes.
;;;   "<A>-<B>" & (("<A>" . "BOO") ("<B>" . "FOO")) -> BOO-FOO
;;; This a subfunction of the macro with-generated-code-from-pattern-1.

(defun-for-macro generate-code-from-pattern-2 (string rewrites)
  (loop with length = (length string)
        with result
        finally (return (apply #'concatenate 'string (nreverse result)))
        for start = 0 then (1+ end2?)
        as end1 = (or (position #\< string :start start) length)
        as end2? = (position #\> string :start end1)
        as rewrite? = (when end2?
                        (loop finally (error "Unknown key.")
                              with old = (subseq string end1 (1+ end2?))
                              for (key . value) in rewrites
                              when (string= old key) return value))
        unless (= start end1) do (push (subseq string start end1) result)
        when rewrite? do (push rewrite? result)
        while rewrite?))



;;; `Generate-code-from-pattern-1' recursively walks form and uses
;;; generate-code-from-pattern-2 to rewrite symbols containing "<foo>" in them.
;;; This a subfunction of the macro with-generated-code-from-pattern-1.

(defun-for-macro generate-code-from-pattern-1 (form rewrites)
  (cond
    ((and (symbolp form)
          (position #\< (symbol-name form))
          (position #\> (symbol-name form)))
     (intern (generate-code-from-pattern-2 (symbol-name form) rewrites)))
    ((listp form)
     (loop for i in form collect (generate-code-from-pattern-1 i rewrites)))
    (t
     form)))



;;; `With-generated-code-from-pattern-1' see introduction to section.

(defmacro with-generated-code-from-pattern-1 (rewrites &body body)
  `(progn
    ,@(loop with body-1 = (if (cdr body) `(progn ,@body) (car body))
            with stringy-rewrites
            = (loop for i in rewrites collect (mapcar #'string i))
            for i from 0
                  below (loop for (nil . rest) in rewrites maximize (length rest))
            as rewrites-1
            = (loop for (key . values) in stringy-rewrites
                    collect (cons key
                                  (nth (rem i (length values)) values)))
            collect (generate-code-from-pattern-1 body-1 rewrites-1))))



;;; `With-code-matching-pattern' is perferable to with-generated-code-from-pattern-1
;;; since it leaves the expanded code lexically apparent.  That's good because
;;; the the lexical analysis tools continue to work, i.e. you can see all the
;;; call sites of a function using grep.

(defmacro with-code-matching-pattern (rewrites pattern noise
                                               &body body
                                               &environment env)
  (unless (equal noise '-->)
    (warn "Missing --> with-code-matching-pattern"))
  (let ((expected
          (macroexpand `(with-generated-code-from-pattern-1 ,rewrites ,pattern) env)))
    (unless (equal expected `(progn ,@body))
      (warn "Code does not match pattern in with-code-matching-pattern expected:")
      (let ((*print-case* :downcase))
        (pprint expected)))
    `(progn ,@body)))







;;;; Some String Functions



;;; The substitution-macro `position-of-char-in-string' returns the position of
;;; the character in the string.  The search begins at position START, but the
;;; returned position is always relative to the beginning of the string.

(def-substitution-macro position-of-char-in-string (character string start)
  (loop for i from start below (length string)
        when (char-equal character (char string i))
          return i))




;;; The function `split-symbol' is a specialized, run-time version of
;;; parse-string-into-words.  It returns a gensym list of symbols interned from
;;; the delimiter-separated substrings of the name of the given symbol.  Rather
;;; than return empty symbols, consecutive delimiters in the string will intern
;;; the delimiter itself. That is, control++ splits into (control +), if the
;;; delimiter is #\+.  As you might have guessed, split-symbol is used in
;;; parsing the names of G2 keys.

(defun split-symbol (symbol delimiter)
  (declare (eliminate-for-gsi))
  (let* ((string (symbol-name symbol))
         (end (length string)))
    (loop for i = 0 then (1+f j)
          while (<f i end)
          as j = (or (position-of-char-in-string delimiter string (1+f i))
                     end)
          if (/=f i j)
            collect (intern-substring string i j)
              using gensym-cons)))




;;;; Pending Activities.


;;; A `pending-activity' represents a continuation that should fire once some set
;;; of events takes place.  Each event is represented by a subnode in a tree.
;;; When all the children of node have finished then that node is treated as
;;; finshed and reclaimed.  Just prior to finishing a node it's continuation is
;;; called with the node.

;;; This is used to trigger processing when a batch of drawing when we must wait
;;; for that to do the full round trip before proceeding.  For each batch we
;;; place one root in the window.  We then generate one child in each workspace
;;; effected by the batch in question.  Those will create children in each of
;;; the image-planes.  The image-plane children will wait until the client side
;;; returns a message that they have finished.  As they come in portions of the
;;; the tree collapse until the pending activity in the window may proceed.

(def-structure (pending-activity
                 (:constructor make-pending-activity
                               (parent-of-pending-activity?
                                 name-of-pending-activity
                                 continuation-of-pending-activity?)))
  name-of-pending-activity
  parent-of-pending-activity?
  (blocking-subactivites-of-pending-activity ())
  (continuation-enabled-of-pending-activity T)
  continuation-of-pending-activity?)


;;; `Block-pending-activity' adds child on a parent activity,

(defun block-pending-activity (parent-activity child-activity)
  (gensym-push child-activity
               (blocking-subactivites-of-pending-activity
                 parent-activity))
  child-activity)

;;; `Finish-pending-activity' calls the continuation and unblocks the
;;; parent.  If the parent is completely unblocked it clears the parent.
;;; It then reclaims the activity.

(defun-void finish-pending-activity (pending-activity)
  #+development
  (when (blocking-subactivites-of-pending-activity pending-activity)
    (error "~S has blocking-subactivites-activity" pending-activity))
  (when (continuation-of-pending-activity? pending-activity)
    (funcall-simple-compiled-function
      (continuation-of-pending-activity? pending-activity)
      pending-activity
      :finished))
  (let ((parent? (parent-of-pending-activity? pending-activity)))
    (when parent?
      (setf (blocking-subactivites-of-pending-activity parent?)
            (delete-gensym-element
              pending-activity
              (blocking-subactivites-of-pending-activity parent?)))
      (unless (blocking-subactivites-of-pending-activity parent?)
        (finish-pending-activity parent?))))
  (reclaim-structure pending-activity))


;;; `Cancel-pending-activity' reclaims the tree of pending activities
;;; given.  It is an error to call this on an activity that has a
;;; parent.

(defun-void cancel-pending-activity (pending-activity)
  #+development
  (when (parent-of-pending-activity? pending-activity)
    (error "Error #3009123952"))
  (cancel-pending-activity-1 pending-activity))

(defun cancel-pending-activity-1 (pending-activity)
  (loop for child
            in (blocking-subactivites-of-pending-activity
                 pending-activity)
        do
    (setf (parent-of-pending-activity? child) nil)
    (cancel-pending-activity-1 child))
  (when (continuation-of-pending-activity? pending-activity)
    (funcall-simple-compiled-function
      (continuation-of-pending-activity? pending-activity)
      pending-activity
      :canceled))
  (reclaim-structure pending-activity))

(defun cancel-identified-drawing-activity-if-any (pending-activity?)
  (when pending-activity?
    (cancel-pending-activity pending-activity?)))

(defun cancel-list-of-pending-activity (list-of-pending-activities)
  (loop with parents
          = (loop for pending-activity in list-of-pending-activities
                  when (parent-of-pending-activity? pending-activity)
                    collect pending-activity using gensym-cons)
        for parent in parents
        do (cancel-pending-activity parent)
    finally
          (reclaim-gensym-list list-of-pending-activities)
          (reclaim-gensym-list parents)))






;;;; Flag bits



;;; The development-only function `deletion-check-for-flag-bit' is called from
;;; code generated from define-flag-bit, to check for a flag being
;;; inappropriately accessed on a deleted connection or frame, or on something
;;; that's not a frame or connection.
;;;
;;; [comment by dkuznick, 3/5/02:] This code is kind of nasty because there are
;;; cases where a reclaimed frame can be encountered when trying to access a
;;; frame-flag, and a partially reclaimed connection can be encountered when
;;; trying to access a connection-flag.  It's may be too difficult to rewrite
;;; the code which does this to do the right thing. See bug HQ-4172766.
;;;
;;; [comments by mhd, 2/20/03:] Also, see bug HQ-4237437 "double reclaim of
;;; connections when clearing certain kbs", which was resolved. It was in fact
;;; resolved by rewriting code slightly, which turned out to not be difficult
;;; upon review in this case.
;;;
;;; We could consider exempting FRAME-BEING-DELETED and/or
;;; CONNECTION-BEING-DELETED from this check, and say that the frame/connection
;;; may be deleted.  But it's not clear these are really meant to be applied to
;;; actually reclaimed frames or connections, but rather to frames/connections
;;; just prior to actually being officially reclaimed. Note, too, that the
;;; deletion check is in any case not foolproof, since it doesn't handle the
;;; recycling case, i.e., the case where a frame/connection is deleted, and then
;;; put back into use, thus seeming to never have been deleted from the point of
;;; view of the caller.

#+development
(defun deletion-check-for-flag-bit
    (frame-or-connection flag-name &optional for-connection)
  (assert-for-development
    (if for-connection
        (connection-p-function frame-or-connection)
        (framep-function frame-or-connection))
    "Trying to access the flag-bit ~s of ~s, but it's not a ~a.~
     ~%However, this may be a normal condition: refer to this bug:~
     ~%  HQ-4172766 \"Development-only: frame- and connection-flag checking too stupid or too smart\""
    flag-name
    frame-or-connection
    (if for-connection "connection" "frame")))



;;; The macro `define-flag-bit' defines a host of macros for accessing
;;; the bit-index'th bit of the given slot name of objects of the
;;; given frame-type.

(defmacro define-flag-bit (flag-name (pretty-slot-name frame-type)
                                     bit-index
                                     &key set clear test for-connection)
  #-development (declare (ignore for-connection))
  (let ((flag-mask
          (ash 1 bit-index))
        (variable-name
          (build-ab-symbol flag-name 'FLAG))
        (vector-predicate-name
          (build-ab-symbol flag-name 'OF-FLAG-VECTOR-P))
        (set-operation-name
          (or set (build-ab-symbol 'SET flag-name)))
        (clear-operation-name
          (or clear (build-ab-symbol 'CLEAR flag-name)))
        (predicate-name
          (or test (build-ab-symbol flag-name 'P)))
        (value-store-operation-name
          (build-ab-symbol 'SET-VALUE-OF flag-name))
        (listed-frame-assertion?
          #-development nil
          #+development
          `((deletion-check-for-flag-bit
              ,frame-type ',flag-name
              ,@(if for-connection '(t))))))
    `(progn
       (defparameter ,variable-name ,flag-mask)
       (defmacro ,vector-predicate-name (fixnum)
         `(/=f 0 (logandf ,fixnum ,',flag-mask)))
       (def-substitution-macro ,predicate-name (,frame-type)
         ,@listed-frame-assertion?
         (,vector-predicate-name (,pretty-slot-name ,frame-type)))
       (def-substitution-macro ,set-operation-name (,frame-type)
         ,@listed-frame-assertion?
         (setf (,pretty-slot-name ,frame-type)
               (logiorf (,pretty-slot-name ,frame-type) ,flag-mask)))
       (def-substitution-macro ,clear-operation-name (,frame-type)
         ,@listed-frame-assertion?
         (setf (,pretty-slot-name ,frame-type)
               (logandc2f (,pretty-slot-name ,frame-type) ,flag-mask)))
       (defmacro ,value-store-operation-name (,frame-type value)
         (if (constantp value)
             (if (eval value)
                 `(progn (,',set-operation-name ,,frame-type) ,value)
                 `(progn (,',clear-operation-name ,,frame-type) ,value))
             (avoiding-variable-capture (,frame-type value)
               `(progn
                  (if ,value
                      (,',set-operation-name ,,frame-type)
                      (,',clear-operation-name ,,frame-type))
                  ,value))))
       (defsetf ,predicate-name ,value-store-operation-name)
       ',flag-name)))

;; Used for frame-flags, frame-flags-2, and connection-flags.





;;;; Pseudo-keyworded String Utilities for Text Strings


;; jh, 6/19/91.  & MHD, 2/16/96

;; Adapted from section ";;;; Pseudo-keyworded String Utilities" in UTILITIES3
;; for text strings; gensym => text-string.  However, gensym-search was made
;; text-string-search+, since text-string-search was in use. Also, made the
;; arithmetic be type-specific (fixnum arithmetic).  I've not checked and sorted
;; out the relationship between text-string-search+ and text-string-search.  Two
;; different authors -- mhd/jh.  Similarly for gensym-string-equal, which became
;; text-string-equal+. (MHD 2/15/96)

;;; Text-String-search+ is a macro designed to emulate Common Lisp's SEARCH
;;; function.  It duplicates the behavior described on p 407 of CLtL/2e.  The
;;; keyword behavior adheres to the description on pp 388-392 of CLtL/2e.  We
;;; include it because some Common Lisp implementations (e.g.  Chestnut) cons a
;;; &rest list whenever search is called.

(defmacro text-string-search+
    (text-string1 text-string2
                  &rest keys &key from-end test test-not key start1 start2 end1 end2)
  (when (and test test-not)
    (error "TEXT-STRING-SEARCH+: :TEST and :TEST-NOT keywords may not occur together."))
  (when (and (null test) (null test-not))
    (setq test `(function eql)))
  (cond ((every #'null keys)
         `(text-string-search-simple ,text-string1 ,text-string2))
        (t `(text-string-search-complex
              ,text-string1 ,text-string2
              ,from-end
              ,test
              ,test-not
              ,key
              ,(or start1 0)
              ,(or start2 0)
              ,end1
              ,end2))))

(defun text-string-search-simple
    (text-string1 text-string2)
  (declare (eliminate-for-gsi))
  (let ((text-string1-length (text-string-length text-string1))
        (text-string2-length (text-string-length text-string2)))
    (if (>f text-string1-length text-string2-length)
        nil
        (loop for text-string2-index
              from 0
                  to (-f text-string2-length text-string1-length)
              thereis
              (and (loop for text-string1-index
                         from 0
                             below text-string1-length
                         always
                         (char=w
                           (charw text-string1 text-string1-index)
                           (charw text-string2
                                  (+f text-string1-index text-string2-index))))
                   text-string2-index)))))

(defun text-string-search-complex
    (text-string1 text-string2
                  from-end test test-not key start1 start2 end1 end2)
  (declare (eliminate-for-gsi))
  (unless end1 (setq end1 (text-string-length text-string1)))
  (unless end2 (setq end2 (text-string-length text-string2)))
  (let ((span1 (-f end1 start1)))
    (if (>f span1 (-f end2 start2))
        nil
        (if from-end
            (loop for text-string2-index
                  from (-f end2 span1)
                  downto start2
                  thereis
                  (and (loop for text-string1-index
                             from start1
                                 below end1
                             for raw-element1 = (charw text-string1
                                                       text-string1-index)
                             for raw-element2 = (charw text-string2
                                                       (+f text-string1-index
                                                           text-string2-index))
                             for element1 = (if key
                                                (funcall key raw-element1)
                                                raw-element1)
                             for element2 = (if key
                                                (funcall key raw-element2)
                                                raw-element2)
                             always
                             (if test
                                 (funcall test element1 element2)
                                 t)
                             never
                             (and test-not
                                  (funcall test-not element1 element2)))
                       text-string2-index))
            (loop for text-string2-index
                  from start2
                      to (-f end2 span1)
                  thereis
                  (and (loop for text-string1-index
                             from start1
                                 below end1
                             for raw-element1 = (charw text-string1
                                                       text-string1-index)
                             for raw-element2 = (charw text-string2
                                                       (+f text-string1-index
                                                           text-string2-index))
                             for element1 = (if key
                                                (funcall key raw-element1)
                                                raw-element1)
                             for element2 = (if key
                                                (funcall key raw-element2)
                                                raw-element2)
                             always
                             (if test
                                 (funcall test element1 element2)
                                 t)
                             never
                             (and test-not
                                  (funcall test-not element1 element2)))
                       text-string2-index))))))

#+development
(defparameter text-string-search-validation-suite
  (copy-tree-changing-strings-to-text-strings
  '(
    ((text-string-search+ "HIT" "HI")                     nil)
    ((text-string-search+ "HI" "HI")                      0)
    ((text-string-search+ "HI" "HIxxx")                   0)
    ((text-string-search+ "HI" "xxxHI")                   3)
    ((text-string-search+ "HI" "xxxHIxxx")                3)
    ((text-string-search+ "HI" "xHIxxxHIx")               1)
    ((text-string-search+ "HI" "xHIxxxHIx" :from-end t)   6)
    ((text-string-search+ '(a b c) '(x x a b c x x x))    2)
    ((text-string-search+ '("A" "B" "C")
               '(x x "A" "B" "C" x x))         nil)
    ((text-string-search+ '("A" "B" "C")
               '(x x "A" "B" "C" x x)
               :test #'equalw)                  2)
    ((text-string-search+ '((a) (b) (c))
               '((x) (x) (a) (b) (c) (x) (x))) nil)
    ((text-string-search+ '((a) (b) (c))
               '((x) (x) (a) (b) (c) (x) (x))
               :key #'car)                     2)
    ((text-string-search+ "HHH" "III"
               :test-not #'eqlw)                0)
    ((text-string-search+ "HHHHHH" "IIIIIH"
               :test-not #'eqlw)                nil)
    ((text-string-search+ "HHHHHH" "IIIIIH"
               :test-not #'eqlw :end1 4)        0)
    )))

#+development
(defun validate-text-string-lisp-facility (validation-suite &optional verbose-p)
  (loop for (form result) in validation-suite
        for test-result = (eval form)        ; any reason this would need copying?
        for passed-p
            = (equalw test-result result) ; note: the gensym-string version
        with bad-forms = nil                  ;    used tree-equal (MHD)
        do
        (when verbose-p
          (format t "~&~:[!!! incorrect: ~;  OK:~] ~a => ~a~%"
                  passed-p form test-result))
        (unless passed-p
          (push form bad-forms))
        finally (return (values (null bad-forms) bad-forms))))

#+development
(defun validate-text-string-search (&optional verbose-p)
  (validate-text-string-lisp-facility
    text-string-search-validation-suite verbose-p))



;; jh, 8/16/91.  There are some occurrences of string-equal in our code which use
;; keywords!  This causes Chestnut to cons, so we need to convert them to macro
;; forms which expand to calls without keywords.

;; This code is at the end of UTILITIES3 (instead of in UNICODE) because it uses
;; condensing-superfluous-subforms, defined earlier in this file.

(defmacro text-string-equal+ (string1 string2 &key start1 end1 start2 end2)
  (expander-for-text-string-equality-tests
    string1 string2 start1 end1 start2 end2 'char-equalw))

(defmacro text-string= (string1 string2 &key start1 end1 start2 end2)
  (expander-for-text-string-equality-tests
    string1 string2 start1 end1 start2 end2 'char=w))

(defun-for-macro expander-for-text-string-equality-tests
       (string1 string2 start1 end1 start2 end2 character-equality-test)
  (if (not (or start1 end1 start2 end2 character-equality-test))
      `(string-equalw ,string1 ,string2)
      (condensing-superfluous-subforms (length)
        (avoiding-variable-capture (string1 string2
                                    &optional (start1 0)
                                              (end1 `(text-string-length ,string1))
                                              (start2 0)
                                              (end2 `(text-string-length ,string2)))
          `(let* ((length1 (-f ,end1 ,start1))
                  (length2 (-f ,end2 ,start2)))
             (if (=f length1 length2)
                 (loop for index1 from ,start1 below ,end1
                       for index2 from ,start2 below ,end2
                       always (,character-equality-test
                                 (charw ,string1 index1)
                                 (charw ,string2 index2)))
                 nil))))))

#+development
(defparameter validation-suite-for-text-string-equal
  (copy-tree-changing-strings-to-text-strings
    '(
      ((text-string-equal+"hello" "Hello")    t)
      ((text-string-equal+ "hello" "hello")    t)
      ((let ((greeting "-hello"))
         (text-string-equal+ greeting "HELLO" :start1 1)) t)
      ((text-string-equal+ "-hello" "HELLO" :start1 1)    t)
      ((text-string-equal+ "HELLO" "-hello" :start1 1)    nil)
      ((text-string-equal+ "-hello" "Hi, Hello"
        :start1 1 :start2 4)           t)
      ((text-string-equal+ "-hello" "Hi, Jello"
        :start1 1 :start2 4)           nil)
      ((text-string-equal+ "01234567890" "123456789"
        :start1 1 :end1 10)            t)
      ((text-string-equal+ "01234567890" "1234567890"
        :start1 1 :end1 10)            nil)
      ((text-string-equal+ "01234567890" "123456789"
        :start1 1 :end1 (+f 5 5))       t)
      ((text-string-equal+ "01234567890" "123456789"
        :start1 1 :end1 (+f 5 15))      nil)
      ((text-string-equal+ "01234567890" "123456789"
        :start1 1 :start2 (-f 12 12)
        :end1 (+f 5 5))                 t)
      ((text-string-equal+ "01234567890" "123456789"
        :start1 1 :start2 (-f 12 12)
        :end1 (+f 5 15))                nil)
      )))

#+development
(defun validate-text-string-equal (&optional verbose-p)
  (validate-text-string-lisp-facility
    validation-suite-for-text-string-equal
    verbose-p))

#+development
(defparameter validation-suite-for-text-string=
  (copy-tree-changing-strings-to-text-strings
  '(
    ((text-string= "hello" "Hello")    nil)
    ((text-string= "hello" "hello")    t)
    ((let ((greeting "-hello"))
       (text-string= greeting "HELLO" :start1 1)) nil)
    ((let ((greeting "-hello"))
       (text-string= greeting "hello" :start1 1)) t)
    ((text-string= "-hello" "HELLO" :start1 1)    nil)
    ((text-string= "-hello" "hello" :start1 1)    t)
    ((text-string= "HELLO" "-hello" :start1 1)    nil)
    ((text-string= "-hello" "Hi, Hello"
                     :start1 1 :start2 4)           nil)
    ((text-string= "-hello" "Hi, hello"
                     :start1 1 :start2 4)           t)
    ((text-string= "-hello" "Hi, Jello"
                     :start1 1 :start2 4)           nil)
    ((text-string= "01234567890" "123456789"
                     :start1 1 :end1 10)            t)
    ((text-string= "01234567890" "1234567890"
                     :start1 1 :end1 10)            nil)
    ((text-string= "01234567890" "123456789"
                     :start1 1 :end1 (+f 5 5))       t)
    ((text-string= "01234567890" "123456789"
                     :start1 1 :end1 (+f 5 15))      nil)
    ((text-string= "01234567890" "123456789"
                     :start1 1 :start2 (-f 12 12)
                     :end1 (+f 5 5))                 t)
    ((text-string= "01234567890" "123456789"
                     :start1 1 :start2 (-f 12 12)
                     :end1 (+f 5 15))                nil)
    )))

#+development
(defun validate-text-string= (&optional verbose-p)
  (validate-text-string-lisp-facility
    validation-suite-for-text-string=
    verbose-p))




;;; The functions `text-string-equal-given-indices' and `text-string=-given-
;;; indices' were written to deal with references to this operation from files
;;; preceeding utilities.

(defun text-string=-given-indices
       (string1 string2 start1 end1 start2 end2)
  (let* ((length1 (-f end1 start1))
         (length2 (-f end2 start2)))
    (declare (type fixnum length1 length2))
    (cond ((/=f length1 length2)
           nil)
          (t
           (loop for index1 fixnum from start1 below end1
                 for index2 fixnum from start2 below end2
                 always (char=w
                          (charw string1 index1)
                          (charw string2 index2)))))))

(defun text-string-equal-given-indices
       (string1 string2 start1 end1 start2 end2)
  (let* ((length1 (-f end1 start1))
         (length2 (-f end2 start2)))
    (declare (type fixnum length1 length2))
    (cond ((/=f length1 length2)
           nil)
          (t
           (loop for index1 fixnum from start1 below end1
                 for index2 fixnum from start2 below end2
                 always (char-equalw
                          (charw string1 index1)
                          (charw string2 index2)))))))




;;; `Text-string-parse-integer' resembles the Common Lisp parse-integer except that it
;;; is a macro and therefore will not cons keyword lists at run time.  The radix
;;; argument is not available as of 8/21/91.

;; jh, 8/21/91.  Now that we let the user parse command lines, we are closer to
;; needing this, though currently we don't let the user call this to transform
;; keyword arguments.

(defmacro text-string-parse-integer (string &key (start 0) end junk-allowed)
  `(text-string-parse-integer-function ,string ,start ,end ,junk-allowed))

(defun text-string-parse-integer-function (string start end junk-allowed)
  (let ((length (text-string-length string)))
    (unless end
      (setq end length))
    (if (or (<f start 0)
            (<f end 0)
            (>f start length)
            (>f end length)
            (>f start end))
        nil
        (loop for index from start below end
              with accum = 0
              with parsing-started-p = nil
              for this-char = (charw string index)
              for this-digit? =
              (wide-character-case this-char
                (#.%\0 0) (#.%\1 1) (#.%\2 2) (#.%\3 3) (#.%\4 4)
                (#.%\5 5) (#.%\6 6) (#.%\7 7) (#.%\8 8) (#.%\9 9)
                (otherwise nil))
              do
          (when (and (not parsing-started-p) this-digit?)
            (setq parsing-started-p t))
          (cond ((blank-p this-char)
                 ;; previoiusly was more like:
;                 (wide-character-member
;                   this-char
;                   '(#.%Space #.%Newline #.%Tab))
                 (cond ((and parsing-started-p junk-allowed)
                        (return (values accum (1+f index))))
                       (parsing-started-p
                        (if (loop for index2 from index below end
                                  for this-char = (charw string index2)
                                  always (blank-p this-char)
                                  ;; previoiusly was more like:
;                                         (wide-character-member
;                                           this-char
;                                           '(#.%Space #.%Newline #.%Tab))
                                  )
                            (return (values accum (1+f index)))
                            (return (values nil nil))))))
                (this-digit?
                 (setq accum (+f (*f accum 10) this-digit?)))
                (t (cond ((and junk-allowed parsing-started-p)
                          (return (values accum (1+f index))))
                         (junk-allowed)
                         (t (return (values nil nil))))))
              finally
                (return (values accum index))))))

;; Inconsistencies with the CL cognate: (1) when junk-allowed is true, this
;; allows junk even at the beginning, but that's not consistent with CL; (2)
;; this doesn't handle negative numbers, sees the unary minus sign as "junk".




(defun text-string-parse-symbol-function (text-string start end)
  (declare (eliminate-for-gsi))
  (let ((length (text-string-length text-string))
;        (whitespace '(#.%Space #.%Newline #.%Tab))
        text-for-symbol
        end-index)
    (unless end
      (setq end length))
    (cond
      ((or (<f start 0)
           (<f end 0)
           (>f start length)
           (>f end length)
           (>f start end))
       nil)
      (t
       (setq text-for-symbol
             (twith-output-to-text-string
               (loop for index from start below end
                     with parsing-started-p = nil
                     for this-char = (charw text-string index)
                     do (when (and (not parsing-started-p)
                                   (not (blank-p this-char)
                                        ;; previoiusly was more like:
;                                        (wide-character-member
;                                          this-char whitespace)
                                        ))
                          (setq parsing-started-p t))
                        (cond ((blank-p this-char)
                               ;; previoiusly was more like:
;                               (wide-character-member
;                                 this-char whitespace)
                               (setq end-index (1+f index))
                               (return))
                              (t
                               (twrite-char this-char)))
                     finally
                       (setq end-index index))))
       (nstring-upcasew text-for-symbol)
       (values (intern-text-string text-for-symbol) end-index)))))



#+development
(defparameter validation-suite-for-text-string-parse-integer
  (copy-tree-changing-strings-to-text-strings
  '(
    ((text-string-parse-integer "123" :junk-allowed t)       123)
    ((text-string-parse-integer "123" :junk-allowed nil)     123)
    ((text-string-parse-integer "        123" :junk-allowed t)   123)
    ((text-string-parse-integer "        123" :junk-allowed nil) 123)
    ((text-string-parse-integer "   x123" :junk-allowed t)   123)
    ((text-string-parse-integer "   x123" :junk-allowed nil) nil)
    ((text-string-parse-integer "123x" :junk-allowed t)      123)
    ((text-string-parse-integer "123x" :junk-allowed nil)    nil)

    ((text-string-parse-integer "xxx123" :junk-allowed nil :start 3) 123)
    ((text-string-parse-integer "xxx123" :junk-allowed nil :start 2) nil)
    ((text-string-parse-integer "xxx123" :junk-allowed t :start 2)   123)

    ((text-string-parse-integer "123xxx" :junk-allowed nil :end 3) 123)
    ((text-string-parse-integer "123xxx" :junk-allowed nil :end 2) 12)
    ((text-string-parse-integer "123xxx" :junk-allowed t :end 2)   12)
    ((text-string-parse-integer "123xxx" :junk-allowed nil :end 4) nil)
    ((text-string-parse-integer "123xxx" :junk-allowed t :end 3)   123)
    ((text-string-parse-integer "123xxx" :junk-allowed t :end 5)   123)

    ((text-string-parse-integer "xxx123" :junk-allowed t :start 3 :end 2) nil)
    ((text-string-parse-integer "xxx123" :junk-allowed t :start -1 :end 2) nil)
    ((text-string-parse-integer "xxx123" :junk-allowed t :start -2 :end -2) nil)
    )))

#+development
(defun validate-text-string-parse-integer (&optional verbose-p)
  (validate-text-string-lisp-facility
    validation-suite-for-text-string-parse-integer
    verbose-p))




;;;; Getting Command Line Arguments, Environment Variables, and the User Name



;;; These utility functions were moved here to UTILITIES0 from OS-SETTINGS so
;;; that they could use the UNICODE module's string processing functions.  Some
;;; of the documentation the big picture remain documented in OS-SETTINGS.  The
;;; core primitive functions of course remain there.  (MHD 2/26/96)

;;; At present, for reasons of practicality, all of these functions accept
;;; either a text string or gensym string as their string-like args.  This
;;; feature is primarily intended to allow modules that load before the text
;;; string facility even exists to call forward to these functions.  However,
;;; where practical, callers should pass in only text strings.  Note, too, that
;;; the string-like results of these functions are always text strings.  (MHD
;;; 2/26/96)




;; jh, 8/18/91.  Changed the keyworded calls to string-equal and string= in
;; get-command-line-keyword-argument and get-command-line-flag-argument to
;; text-string-equal and text-string=.  These two equality tests are macros,
;; so their keyword lists go away at compile time, instead of leaking at runtime.
;; The terminology of the above is confusing, since "keyword" could also mean a
;; command-line keyword, like the "-display" in the command line
;;   "g2 -display nj:0.0".
;; Here, however, it means a Common Lisp keyword, such as the :start1 in
;;   (string-equal " hi" "hi" :start1 1).

;; Note that this introduced a forward reference to a macro.  I've made
;; function versions of these operations and called them from this file.
;; -jra 2/13/92


;; Consider changing get-command-line-keyword-argument and
;; get-command-line-flag-argument to optionally or always treat case as
;; significant, which seems more unix-like.  Similar consideration might be
;; given to allowing keywords or flags to be specified with or without hyphens
;; on the command line.

;; jh, 3/25/93.  Note that if we implement the above suggestion, we will have to
;; make an exception on VMS, where the command-line arguments always are
;; uppercase.  Use the following abstraction if this suggestion is implemented.

;; unused -dkuznick, 3/5/02
(defun command-line-token-equal-given-indices
       (token1 token2 start1 end1 start2 end2)
  (if (eq g2-machine-type 'vms)
      (text-string-equal-given-indices
        token1 token2 start1 end1 start2 end2)
      (text-string=-given-indices
        token1 token2 start1 end1 start2 end2)))

(defun command-line-keyword-p (keyword-as-text-string)
  (text-string-equal-given-indices
    keyword-as-text-string #w"-" 0 1 0 1))

;; Consider combining get-command-line-keyword-argument and
;; get-command-line-flag-argument into one with args to control difference in
;; cases.


;;; `Get-command-line-keyword-argument' returns the argument on the command line
;;; which matches keyword, if present; otherwise, nil.  Keyword may be in the
;;; form of a symbol or a string in any alphabetic case (upper, lower, or mixed)
;;; with or without a leading hyphen (-).  On the command line, however, it must
;;; be specified with a leading hyphen, although alphabetic case is still not
;;; significant.  The result is a shared, constant string, which should never be
;;; reclaimed or mutated.

;;; Added optional argument keyword-instance-number to cause the function to
;;; search for a particular instance of a keyword.  The default value is 1.
;;; This to support cases where a keyword may appear more than once on a command
;;; line. 26oct93 paf!

;;; The optional argument no-import-p suppresses the normal text import (as ISO
;;; 8859-1 as of G2 5.0), including, possibly (*), conversion from a lisp string
;;; to a wide string.  This is to support the -name and -icon arguments that
;;; supply the window title bar and icon text. (MHD 10/15/00)
;;;
;;; * Note: in development, the string result is a Lisp string, whereas in
;;; production it's a wide string.  The caller therefore should do runtime type
;;; checking or only pass the result on to functions that can handle either
;;; type, such as, for example, gensym c function.

(defun get-command-line-keyword-argument
    (keyword &optional (keyword-instance-number 1) (no-import-p nil))
  (let ((keyword-as-text-string (copy-text-string keyword)))
    (prog1
        (loop with keyword-comparison-start-index
                = (if (command-line-keyword-p keyword-as-text-string)
                      1
                      0)
              and matching-keyword-instance = 0
              for i from 1
              as arg?
                 = (get-gensym-command-line-argument-as-text-string i)
              while arg?
              when (and (command-line-keyword-p arg?)
                        (if (text-string-equal-given-indices
                              arg? keyword-as-text-string
                              1 (text-string-length arg?)
                              keyword-comparison-start-index
                              (text-string-length keyword-as-text-string))
                            (incff matching-keyword-instance)
                            nil)
                        (=f matching-keyword-instance keyword-instance-number))
                return
                (if no-import-p
                    (get-gensym-command-line-argument (+f i 1))
                    (get-gensym-command-line-argument-as-text-string (+f i 1))))
      (reclaim-text-string keyword-as-text-string))))




;;; `Get-command-line-keyword-argument-as-integer' ... is like get-command-line-
;;; keyword-argument, but returns the arg as an integer if the arg is present
;;; and is an integer.

;;; Added optional argument keyword-instance-number? - see doc above for
;;; get-command-line-keyword-argument.  26oct93 paf!

(defun get-command-line-keyword-argument-as-integer
       (keyword &optional (keyword-instance-number? 1))
  (let ((arg? (get-command-line-keyword-argument keyword keyword-instance-number?)))
    (if arg?
        ;; The Gensym Common Lisp Requirements document does not forbid
        ;; parse-integer to leak.  So we replace it with the macro
        ;; text-string-parse-integer, which undertakes not to cons a keyword
        ;; list or otherwise leak.  jh, 8/21/91.
        (text-string-parse-integer-function arg? 0 nil t))))

(defun get-command-line-keyword-argument-as-memory-size
       (keyword &optional (keyword-instance-number? 1))
  (let ((arg? (get-command-line-keyword-argument keyword keyword-instance-number?)))
    (if arg?
        (read-memory-size-from-string arg?))))

(defun read-memory-size-from-string (string)
  (abs (read-float-from-string string 0 (length string))))



;;; `Get-command-line-flag-argument' ... like the above, but just returns the
;;; flag if it is present; otherwise, nil.  If require-hyphen? is true, a
;;; leading hyphen must accompany the flag on the command line.  In either
;;; case, a leading hyphen is allowed.

(defun get-command-line-flag-argument (flag &optional require-hyphen?)
  (let ((flag-as-text-string (copy-text-string flag)))
    (prog1
        (loop with flag-comparison-start-index
                = (if (command-line-keyword-p flag-as-text-string)
                      1
                      0)
              for i from 1
              as arg? = (get-gensym-command-line-argument-as-text-string i)
              while arg?
              when (if (not (command-line-keyword-p arg?)) ;arg? has no "-"
                       (if (not require-hyphen?) ;good, because it's not required
                           (text-string-equal-given-indices
                             arg? flag-as-text-string
                             0 (text-string-length arg?)
                             flag-comparison-start-index
                             (text-string-length flag-as-text-string)))
                       (text-string-equal-given-indices
                         arg? flag-as-text-string
                         1 (text-string-length arg?)
                         flag-comparison-start-index
                         (text-string-length flag-as-text-string)))
                return arg?)
      (reclaim-text-string flag-as-text-string))))




;;; The macro `get-gensym-environment-variable' ...

(defun get-gensym-environment-variable (variable-name-string)
  (foreign-get-environment-variable variable-name-string))

(defun read-number-for-gensym-environment-variable (variable-name)
  (let ((string-to-parse?
          (get-gensym-environment-variable variable-name)))
    (if string-to-parse?
        (prog1
            (text-string-parse-integer-function
              string-to-parse? 0 nil t)
          (reclaim-text-string string-to-parse?))
        nil)))

(defun read-memory-size-for-gensym-environment-variable (variable-name)
  (let ((string-to-parse?
          (get-gensym-environment-variable variable-name)))
    (if string-to-parse?
        (prog1 (read-memory-size-from-string string-to-parse?)
          (reclaim-text-string string-to-parse?))
        nil)))


(defvar cached-gensym-user-home-directory nil)

#+unused
(defun gensym-user-home-directory ()
  (or cached-gensym-user-home-directory
      (setq cached-gensym-user-home-directory
            (or (foreign-get-user-homedir)
                (get-gensym-environment-variable
                  #w"HOME")))))



;;; `Get-all-command-line-keyword-arguments' returns a gensym list of all
;;; command-line keyword arguments with the given key, otherwise nil.  It is the
;;; responsibility of the caller to reclaim this list.  Keyword may be in the
;;; form of a symbol or a string in any alphabetic case (upper, lower, or mixed)
;;; with or without a leading hyphen (-).  On the command line, however, it must
;;; be specified with a leading hyphen, although alphabetic case is still not
;;; significant.  The result is a fresh gensym list make up of constant strings,
;;; which should not be altered.

;; jh, 10/4/94. Necessary to put get-all-command-line-keyword-arguments instead
;; of someplace more general because OS-SETTINGS doesn't have defconser at its
;; current place in the loading order.  So far, though,
;; get-all-command-line-keyword-arguments is only used once, immediately below
;; its definition here.
;;
;; -- UPDATE: Moved to UTILITIES3 along with the higher level command line
;; argument stuff from OS-SETTINGS. (MHD 2/27/96)

(def-system-variable all-command-line-keyword-arguments UTILITIES3
  nil)

(defun get-all-command-line-keyword-arguments (keyword)
  (loop with keyword-comparison-start-index
          = (if (command-line-keyword-p keyword)
                1
                0)
        for i from 1
        as arg? = (get-gensym-command-line-argument-as-text-string i)
        while arg?
        with this-keyword-argument?
        when (and (command-line-keyword-p arg?)
                  (text-string-equal-given-indices
                    arg? keyword
                    1 (text-string-length arg?)
                    keyword-comparison-start-index
                    (text-string-length keyword))
                  (setq this-keyword-argument?
                        (get-gensym-command-line-argument-as-text-string
                          (+f i 1))))
          collect this-keyword-argument?
            using gensym-cons))






;;;; Defining Command Line Args

;; "YACLIA" (yet another command line interface abstraction)

;; This has so far just been used in Telewindow; it should be used elsewhere, at
;; least for getting command line args for the local G2 window! It was moved
;; here from TELEWINDOWS today. (MHD 2/27/96)


;;; The macro `def-command-line-argument' is used to define a command line
;;; argument.  The first argument, indicator-or-indicator-and-options, is either
;;; an indicator or a list of the indicator and a list of options. "Indicator"
;;; functions as the indicator in the plist of command line arguments returned
;;; by this function.  Options is a list of one or more of the following
;;; options: (note: at present, there is only one option defined).
;;;
;;;    (:systems . system-names)
;;;
;;; An indicator functions as the indicator in the plist of command line
;;; where system-names is a list of system-name symbols, e.g., AB, Telewindows,
;;; etc., as declared by a declare-system form in the module SYSTEMS.  If this
;;; is not specified at all, or is specified with system-names nil, then this
;;; defines the argument for all systems.

;;; Note to do as an improvement: To specify it for no systems, e.g., for
;;; debugging or to disable an argument, by convention system-names should be
;;; specified as the list (NONE).  The system named NONE will be recognized as
;;; indicating a "no-op".
;;;
;;; Examples:
;;;
;;;       (def-command-line-argument language (:keyword))  ;; works for all systems
;;;       (def-command-line-argument (user-name (:systems ab telewindows)) (:keyword))
;;;
;;; This generates a "getter" function, that gets the arg from the command line,
;;; and possibly does some further processing on it, and may even have side
;;; effects.  (Note, however, that there's no guarantee that the getter will be
;;; called, or that it will only be called once.)
;;;
;;; Arg-processing-spec is of one of the following forms
;;;
;;;    :keyword
;;;    | <index>
;;;    | (<variable-name?> [:keyword | <index>] [<keyword-spelling> | <default>])
;;;    | :flag
;;;
;;; If an <index> is specified, an optional <default> can be specified as well.
;;; This must be a wide-string and is the value that will be used if a keyword is
;;; present in its place.  It will also be used if any default has already been
;;; used for an indexed argument.  Currently this is being used by Telewindows
;;; for defaulting of the remote-host-name and remote-port-name-or-number
;;; positional arguments as follows:
;;;
;;; tw myhost 1112 -junk blah => tw myhost 1112
;;; tw myhost -junk blah  =====> tw myhost 1111
;;; tw -junk blah =============> tw localhost 1111
;;;
;;; If :flag, the arg will appear in the plist with either T or NIL depending
;;; on its presence in the command line.
;;;
;;; The body is optional.  If it is omitted, the arg, if any, is returned by the
;;; getter function. If it is provided, it may do other processing and return a
;;; value of its own.  Within body, code may refer to the argument or nil, if
;;; none, via either the variable provided in the arg-processing-spec, or, if
;;; not provided or nil, the variable ARG?.
;;;
;;; This normally uses the print name of indicator to search for keyword args.
;;; If keyword-spelling is provided, however, that is preferred, allowing it to
;;; be different.
;;;
;;; The function `get-command-line-arguments' returns the arguments so defined
;;; from the command line as a plist.  The top level list is made up of gensym
;;; conses, and the elements are, by convention, either strings, integer
;;; numbers, or unshared text strings.

(def-global-property-name command-line-plist-element-getter)
(def-global-property-name command-line-argument-processor)

(defvar all-known-command-line-plist-elements nil)

;; see also: def-suite-for-loading-file-at-launch-time, get-command-line-flag-argument,
;; get-gensym-command-line-argument-as-text-string, get-command-line-keyword-argument

(defmacro def-command-line-argument
    (indicator-or-indicator-and-options
      (arg-processing-spec) &body body)
  (let* ((indicator
           (if (atom indicator-or-indicator-and-options)
               indicator-or-indicator-and-options
               (car indicator-or-indicator-and-options)))
         (options
           (if (atom indicator-or-indicator-and-options)
               nil
               (cdr indicator-or-indicator-and-options)))
         (systems-this-runs-in-or-t-for-all
           (let ((systems-spec? (assq ':systems options)))
             (if (or (null systems-spec?)
                     (null (cdr systems-spec?)))
                 't
                 (cdr systems-spec?))))
         (arg-variable
           (or (if (consp arg-processing-spec)
                   (first arg-processing-spec))
               'arg?))
         (argument-index?
           (if (consp arg-processing-spec)
               (if (fixnump (second arg-processing-spec))
                   (second arg-processing-spec))
               (if (fixnump arg-processing-spec)
                   arg-processing-spec)))
         ;; The following case will be used when a keyword appears where a
         ;; positional argument was expected.  This allows defaulting of
         ;; positional arguments if unspecified.  -dkuznick, 2/28/02
         (default-for-positional-argument?
             (when (and (consp arg-processing-spec)
                        (fixnump (second arg-processing-spec)))
               (stringw (third arg-processing-spec))))
         (keyword?
           (if (eq arg-processing-spec ':keyword)
               (stringw indicator)
               (if (and (consp arg-processing-spec)
                        (eq (second arg-processing-spec) ':keyword))
                   (or (if (third arg-processing-spec)
                           (stringw (third arg-processing-spec)))
                       (stringw indicator)))))
         (flag?
           (if (eq arg-processing-spec ':flag)
               (stringw indicator)
               (if (and (consp arg-processing-spec)
                        (eq (second arg-processing-spec) ':flag))
                   (or (if (third arg-processing-spec)
                           (stringw (third arg-processing-spec)))
                       (stringw indicator)))))
         (get-function-name
           (build-ab-symbol
             'get-command-line-plist-element-for
            indicator))
         (processor-function-name
           (build-ab-symbol 'command-line-process indicator))
         (form
           `(let ((,arg-variable
                     ,(cond (argument-index?
                             (let ((arg? (gensym)))
                               `(let ((,arg? (get-gensym-command-line-argument-as-text-string
                                              ,argument-index?)))
                                  ,(if default-for-positional-argument?
                                       ;; Once we've used positional defaulting,
                                       ;; we have to keep doing it
                                       `(if (or used-positional-command-line-argument-default
                                                (null ,arg?)
                                                (command-line-keyword-p ,arg?))
                                            ;; convert to text string
                                            (progn
                                              (setq used-positional-command-line-argument-default t)
                                              ,default-for-positional-argument?)
                                            ,arg?)
                                       `,arg?))))
                            (flag? ; require hyphen
                             `(get-command-line-flag-argument ,flag? t))
                            (keyword?
                             `(get-command-line-keyword-argument ,keyword?)))))
              (funcall (command-line-argument-processor ',indicator) ,arg-variable))))
    `(progn
       (defun-funcallable ,processor-function-name (,arg-variable)
         ,arg-variable                        ; ignored if not used
         ,(if (eq systems-this-runs-in-or-t-for-all 't)
              `(progn
                 ,arg-variable                ; returned if no body
                 . ,body)
              `(current-system-case
                 (,systems-this-runs-in-or-t-for-all
                    ,arg-variable        ; ditto.
                    . ,body)
                 (t
                   nil))))
       (setf (command-line-argument-processor ',indicator)
             ',processor-function-name)
       (defun-funcallable ,get-function-name ()
         ,(if (eq systems-this-runs-in-or-t-for-all 't)
              form
               `(current-system-case
                   (,systems-this-runs-in-or-t-for-all
                      ,form)
                   (t
                     nil))))
       (setf (command-line-plist-element-getter ',indicator)
             ',get-function-name)
       (pushnew ',(cons indicator (or argument-index? 0))
                all-known-command-line-plist-elements)
       ',indicator)))

;; Note: there is only one option supported now, but we have made
;; it general to allow for later expansion.

(defvar used-positional-command-line-argument-default)
(defun get-command-line-arguments ()
  (let ((used-positional-command-line-argument-default nil))
    (loop for (indicator . nil) in all-known-command-line-plist-elements
          as value? = (funcall (command-line-plist-element-getter indicator))
          nconc (if value? (gensym-list indicator value?)))))


(defun get-initial-command-line-arguments ()
  (setq all-known-command-line-plist-elements
        (sort-list all-known-command-line-plist-elements '< 'cdr))
  (get-command-line-arguments))

(declare-special-global command-line-arguments)
(def-system-variable command-line-arguments utilities3 ; move later!
  (:funcall get-initial-command-line-arguments))





;;;; Command Line Arguments for G2, Telewindows, and GSI



;;; Arguments defined here are common to both Telewindows and AB (G2). At present,
;;; many other command line args are documented and working for G2, Telewindows,
;;; and GSI, but are not defined through this facility.  We expect to move
;;; them into this facility at some future date.  Note that some additional
;;; documentation for Telewindows command line arguments, some of which may be
;;; common to G2, is in TELEWINDOWS.

;;; The following args are used to fill in the values in the G2-login instance
;;; whose table is presented in the user settings editor, i.e., when a user logs
;;; in, changes mode, etc.
;;;
;;; These are all keyword arguments.  The following table shows the command
;;; line argument name in the left-hand column, and the corresponding slot
;;; names in workstation structures, gensym window structures, g2-window frames,
;;; and g2-login frames.
;;;
;;;
;;;   command                 workstation/                g2-window                 g2-login
;;;    line arg                 gensym-window
;;;   ------------        ----------------------        ---------------------        ------------------------------
;;;   `user-name'        g2-user-name-for-        g2-user-name                g2-login-user-name?
;;;                            this-workstation?
;;;
;;;   `password'        g2-user-password-        (not available)                g2-login-user-password?
;;;                            for-this-workstation?
;;;
;;;   `discard-user-settings' g2-user-discard- (not available)        (not available)
;;;                             user-settings-for-this-workstation-p
;;;
;;;   `user-mode'        g2-user-mode-for-        g2-user-mode                 g2-login-user-mode
;;;                            this-workstation?
;;;
;;;   `window'                g2-window-name-or-        (not available)                g2-login-window-name-or-class
;;;                            class-for-this-
;;;                            workstation
;;;
;;;   `window-style'     specific-language-        g2-window-style                g2-login-style-  [NOTE: not currently exposed to users]
;;;                            for-this-workstation?                            specifically-for-this-workstation?
;;;
;;;   `language'         specific-language-for-        specific-language-        g2-login-specific-language-for-
;;;                            this-workstation?         for-this-g2-window?          this-g2-window?
;;;
;;;   `cjk-language'    cjk-typeface-preference-   (not available)      (not available)
;;;                       for-this-workstation?
;;;
;;;
;;;   `init-string'        g2-window-init-string?        g2-window-initial-        g2-login-init-string?
;;;                                                      window-configuration-
;;;                                                      string?
;;;
;;;                     time-of-telewindows-    g2-window-time-of-
;;;                       connection?             last-connection?
;;;

(def-command-line-argument (password  (:systems ab telewindows)) ((value? :keyword))
  (if value? (encode-user-password-string-function value?)))
(def-command-line-argument (language (:systems ab telewindows)) (:keyword))

(def-command-line-argument (cjk-language (:systems ab telewindows)) ; New! (MHD 4/9/99)
    ((value? :keyword))
  (cond
    (value?
     (cond
       ((member value? '(chinese japanese korean chinese-simplified chinese-traditional))
        (notify-user-at-console
          "Note: ~A is not valid for the -cjk-language option.~
         ~%It should be either Chinese, Japanese, or Korean." value?)
        nil)
       (t value?)))))

;; Note that a command line with "-language x" and no mention of cjk-language
;; implies "-cjk-language x".  Thus, users who already were specifying their
;; language as either Japanese, Korean, or Chinese will typically not have to
;; use the new command line argument.  (MHD 4/9/99)


(def-command-line-argument (init-string (:systems ab telewindows)) (:keyword))
(def-command-line-argument (discard-user-settings (:systems ab telewindows))
    ((value? :flag))
  (if value? t nil))
(def-command-line-argument (user-mode (:systems ab telewindows)) (:keyword))
(def-command-line-argument (window (:systems ab telewindows)) (:keyword))
(def-command-line-argument (user-name (:systems ab telewindows)) (:keyword))

;;; `windowhandle' - declaring systems as both TW and G2.  We've never used it
;;; for G2, but I tested it, and in fact G2 has supported this flag from the
;;; very beginning (5.0r0) on Windows.  It used to be a Windows-only flag, and
;;; was handled in WinMain in msmain.c.  We want to support the Netscape plugins
;;; on Unix too, now, so adding it to Lisp and removing it from C.

(def-command-line-argument (windowhandle (:systems ab telewindows)) (:keyword))


;;; `get-parent-windowhandle' - we don't want to send nil to C; send an empty
;;; string instead.

(defun get-parent-windowhandle ()
  (or (get-command-line-keyword-argument "windowhandle") ""))



;;; The command line argument `window-style' can be one of the three supported
;;; styles:
;;;
;;;   standard, standard-large, g2-5.x
;;;
;;; and affects only the local window (the G2 if given on the G2 command line,
;;; or the telewindows window if given on the TW command line).  It is stored in
;;; command-line-arguments as either nil or the corresponding symbol provided
;;; its print name matches (not counting case).

(def-command-line-argument (window-style  (:systems ab telewindows)) ((value? :keyword))
  (if value?
      (validate-window-style-command-line-argument value? "-window-style")))

(defun validate-window-style-command-line-argument (argument argument-string)
  (loop with styles = '(standard-large standard g2-5.x)
        for style in styles
        when (string-equalw argument (symbol-namew style))
          return style
        finally
          (notify-user-at-console
            "The ~a argument ~s is not recognized. It should be one of ~L,|"
            argument-string argument styles)))




;;; The native-fonts feature is available in G2 5.0.  Using this feature, if
;;; fonts are available with G2 or Telewindows running under the X Window
;;; System, and their character style and spacing can be seen to match those of
;;; a certain G2 font, the built-in X text drawing routine may be used in order
;;; to optimize the performance of text drawing operations.

;;; For example, the X Windows System typically ships with a font whose X-style
;;; specification is
;;;
;;;   -Adobe-Helvetica-Medium-R-Normal--14-140-75-75-P-77-ISO8859-1
;;;
;;; This happens to match most of the characters in G2's small, sans-serif
;;; Latin-alphabet font at full scale.  So, it may be used to render certain
;;; runs of text in G2.  If this font should not be available, then the
;;; traditional renderer will be used, and this may be more or less unnoticably
;;; slower, depending on the X implementation and the configuration of networks
;;; and nodes currently in use.
;;;
;;; This feature may be disabled through a new command-line argument,
;;; `no-native-fonts', which turns off the feature entirely.  It may be
;;; enabled through the new command-line argument `native-fonts'.
;;;
;;; As of now (5.0 Rev. 0), it is disabled by default, and must be explicitly
;;; enabled in order to be in effect.  This choice is primarily due to the
;;; problems described for Solaris, below.

;;; Generally, it need not be disabled.  Occasionally, however, there are
;;; problems that may call for this to be disabled.  The most important problem
;;; case found is the fonts under Sun/Solaris.  These don't have the same set
;;; widths as are used for, say, the SunOS 4.1 system, and so, turding may
;;; result when fine incremental changes occur, as happens when adding and
;;; deleting characters in the editor.  One other case that has been observed is
;;; that certain X emulators running under Microsoft Windows give bad or
;;; incorrectly interpreted font data.  On such systems, this features causes
;;; fonts to be incorrectly displayed, and therefore this feature should be
;;; disabled on on such a system.

(def-command-line-argument (no-native-fonts (:systems ab telewindows)) (:flag))
(def-command-line-argument (native-fonts (:systems ab telewindows)) (:flag))



;;; In G2 5.0, with a local window or a 5.0 Telewindows window, the native
;;; clipboard is used by default for cutting and pasting operations.  Since this
;;; involves considerable complexity, e.g., the use of one or more protocols for
;;; exchange of data involving one, two, or more applications, it is possible
;;; that this can be less stable than the pre-5.0 implementation of cut and
;;; paste in G2 which involved only G2; it supported only cut and paste within
;;; G2, but it did not have any risk of crashing due to bugs in other
;;; applications.  Also, despite extensive testing by Gensym, it is impossible
;;; to test all of the possible configurations that our users may possibly
;;; encounter.
;;;
;;; Therefore, we have provided a way to disable this feature.  The command
;;; line argument `no-native-clipboard' turns off the feature entirely.  Note
;;; that a G2 5.0 working with a Telewindows 4.0 window functions as though
;;; no-native-clipboard had been specified on the command line.

(def-command-line-argument (no-native-clipboard (:systems ab telewindows))
    ((value? :flag))
  (if value? t nil))



;;; In G2 5.0, Rev. 3, or later versions, the command line argument
;;; `g2passwdexe' is to be followed by an argument giving the file name of the
;;; g2passwd executable.  In general, normal type extensions for executables, if
;;; any, e.g., ".exe", need not be included.  In general, the final, physical
;;; file name is resolved by the operating system with respect to G2's current
;;; working directory and with the value of the PATH environment variable, or
;;; the equivalent environment variable for non-Unix OS's.  Thus, a string
;;; containing no directory delimiter characters, e.g., slash (/) for Unix,
;;; resolves to be the file name of the file with the specified name in the
;;; first directory in the list given by PATH (or equivalent).  Note that
;;; typically the working directory is the first directory specified in
;;; PATH, and, thus, an unqualified name typically denotes the file with
;;; that name in the G2's working directory.
;;;
;;; The type of the value inside of G2 is a wide string.
;;;
;;; The default value for this is the wide string "g2passwd", which is the name
;;; given to the g2passwd executable as it is shipped with G2.
;;;
;;; The "exe" suffix is a bit ugly, but this is an ugly, obscure feature, and it
;;; is short and quite likely to be understood by the most likely users:
;;; administrators.  It is also pretty well known in the DOS (Windows) world.

(def-command-line-argument (g2passwdexe (:systems ab)) ((value? :keyword))
  (or value? #w"g2passwd"))



;;; `no-backing-store' is used to turn off the default behavior added for
;;; 5.0r3 to use a backing store to avoid TW pestering G2 to redraw it
;;; for something as simple as a window being moved over the TW window.
;;; Since using a backing store takes up memory, and since you may want
;;; to see problems in TW (or the G2 local window) when G2 is slow or
;;; nonresponsive, we're allowing users to turn the feature off with
;;; this command line flag.

(def-command-line-argument (no-backing-store (:systems ab telewindows)) (:flag))


;;; `private-colormap'

(def-command-line-argument (private-colormap (:systems ab telewindows)) (:flag))


;;; `file-operation-timeout'

(def-command-line-argument (file-operation-timeout (:systems ab)) ((value? :keyword))
  value?)


;;; `use-os-emulation'

(def-command-line-argument (use-os-emulation (:systems ab telewindows)) (:flag))


(def-command-line-argument (copy-messages-on-logbook (:systems ab)) (:flag))
(def-command-line-argument (copy-logbook-on-console (:systems ab)) (:flag))

;;; GENSYMCID-1214: Error while saving KB
(def-command-line-argument (debug-frame-reference-balance (:systems ab)) (:flag))


;;; `Xclip' is new for g2 5.1r5, only used in X Windows, enables clipping of
;;; bitmap rectangles, which may affect performance, good or bad.  NOTE: this is
;;; for the X Window System only!  On other systems, this will be processed to a
;;; very limited extent, but basically ignored.  It is not planned that this be
;;; documented for general users, except maybe in internal or "advanced"
;;; documentation.

(def-command-line-argument (xclip (:systems ab telewindows)) (:flag))



;;; `Background' ... at present, this can be a color (i.e., a color name symbol,
;;; e.g., red), which will override the default background pattern (the GENSYM
;;; brick pattern) or a pathname string for a ... format pattern.  If it's a
;;; color, then this will be a symbol in command-line-args; otherwise, it should
;;; be regarded as a pathname string.  When it's used, it will still have to be
;;; probed to see if a corresponding file really exists.

(def-command-line-argument (background (:systems ab telewindows)) (:keyword)
  (macrolet ((color-name-p (name)
               `(rgb-from-color ,name)))
    (when arg?
      (let ((arg-with-case-conversion
              (copy-wide-string-with-case-conversion arg? :all)))
        (let ((symbol (intern-text-string arg-with-case-conversion)))
          (cond ((color-name-p symbol)
                 symbol)
                ;; support known tiling patterns named with symbols
                ((get-tiling-pattern symbol)
                 symbol)
                (t
                 ;; Otherwise, it could be a pathname, to be checked
                 ;; later.
                 (copy-wide-string arg?))))))))



;;; The command line argument `ui' can be one of these styles:
;;;
;;;   classic, standard
;;;
;;; and affects only the local window (the G2 local window if given on the G2
;;; command line, or the telewindows window if given on the TW command line).
;;; It is stored in command-line-arguments as either nil or the corresponding
;;; symbol provided its print name matches (not counting case).

;;; The standard UI is a selection-style UI with as many native widgets as are
;;; supported by the platform. "Standard" here refers to the Windows standard.
;;; The classic UI means the UI from G2 6.x or earlier.

;;; This command line argument together with -windowhandle determine how all the
;;; various bits of the new UI are enabled. See selection-ui-p and friends in
;;; WINDOWS4.

;;; If you change this, you must also update the help message in
;;; g2ext_print_command_line_usage in ext/c/cprim.c

(defconstant known-ui-styles '(classic standard))

(def-command-line-argument (ui (:systems ab telewindows)) ((value? :keyword))
  (or (parse-ui-style value?)
      (progn (notify-user-at-console
               "The -ui argument ~s must either be ~(~L,|~). Assuming ~(~s~)."
               value? known-ui-styles (gensym-default-ui))
             (gensym-default-ui))))

(defun parse-ui-style (value?)
  (cond ((null value?)
         (gensym-default-ui))
        ((loop for ui in known-ui-styles doing
           (when (string-equalw value? (stringw ui))
             (return ui))))))

(defun gensym-default-ui ()
  'standard)





;;; The command line argument `netinfo' adds network information (host and port
;;; identification) to the G2 window title bar. It does this calling
;;; add-network-info-to-title-if-appropriate, q.v., in INT4.

(def-command-line-argument (netinfo (:systems ab)) (:flag))



;;; The command line arguments `verbose' and `silent' control whether
;;; G2 or Telewindows print more (or less in TW) than the usual amount
;;; of status information, including information on the authorization
;;; used to license the process.

(def-command-line-argument (verbose (:systems ab telewindows)) (:flag))

(def-command-line-argument (silent (:systems ab telewindows)) (:flag))


;;; The command line argument exit-on-abort indicates that if G2 should abort
;;; due to an internal error, it should write its information to the log file
;;; and shut down, rather than waiting for a user to acknowledge the error and
;;; shut down manually.

(def-command-line-argument (exit-on-abort (:systems ab)) (:flag))

(defun-simple exit-on-abort-p ()
  (get-command-line-flag-argument #w"-exit-on-abort"))

;;;
;;; The command line argument for JIT enable/disable
;;;  

(def-command-line-argument (use-jit (:systems ab)) (:flag))

(defvar use-jit-p nil)  


;;;; Secure ICP


(def-concept secure-icp)

(defparameter secure-icp-initialized-p nil)
(defparameter secure-icp-default-p nil)
(defparameter cache-server-cert-name nil)

;;; The command-line-argument `secure' causes G2 or TW to attempt to use SSL for
;;; all network connections. If unable to do so, then we revert to clear-text
;;; communications.

(def-command-line-argument (secure (:systems ab gsi telewindows)) (:flag))

(defun secure-icp-requested-p ()
  (get-command-line-flag-argument #w"secure"))


;;; The command-line-argument `cert' specifies the server certificate to use for
;;; secure communications. On Unix systems, it must be the pathname of a
;;; PEM-format file containing public and private keys. On IntelNT, it must be
;;; the common name (CN) of a certificate in the local machine's "MY"
;;; certificate store.

(def-command-line-argument (cert (:systems ab gsi)) (:keyword))

(defun update-server-certificate (newcert)
  (unless secure-icp-initialized-p
    (setq cache-server-cert-name newcert)))

(defun server-certificate-name ()
  (or (get-command-line-keyword-argument "cert")
      cache-server-cert-name
      (setq cache-server-cert-name
            (get-gensym-environment-variable "G2_CERT"))))

(defun string-prefix=w (prefix string)
  (and (<=f (wide-string-length prefix) (wide-string-length string))
       (loop for i from 0 below (wide-string-length prefix)
             always (char=w (charw prefix i)
                            (charw string i)))))

;;; `secure-icp-string' is a bit of a DWIMmy function whose purpose is to return
;;; "/SSL" if a listener port is secure.  It gets called in several places, such
;;; as initial startup screens.

;;;yduJ 6/06: It used to be simpler, back when security was all-or-nothing, but
;;;with individual ports choosing their own security, it needed updating:
;;;Made everything keywords, and added :use-default keyword.  The
;;;reasoning here is that with TW, you'll only use the default (the -secure
;;;commandline option), and for the G2 main port you'll use the default during
;;;startup (before you'd have an opportunity to create any specialized sockets).
;;;The default is to try to be secure, but sometimes we override it with NIL to
;;;mean that THIS socket isn't secure and we shouldn't print the /SSL.
(defun secure-icp-string (&key network-type use-default (secure-p t))
  (if (and secure-p
           (or (null network-type)
               (string-prefix=w #w"TCP" network-type)) ; eg #w"TCP/IP Port"
           (if use-default secure-icp-default-p secure-icp-initialized-p))
      "/SSL" ""))

(def-gensym-c-function c-set-secure-icp
    (:fixnum-int "g2ext_set_secure_icp")
  ((:string certificate)))              
              
(defun set-up-secure-icp (&optional default-p)
  (unless secure-icp-initialized-p
    (let* ((rc (c-set-secure-icp
                 (or (server-certificate-name) ""))))
      (when (=f rc 0)
        (notify-user-at-console "WARNING: SSL encryption is not available in this executable."))
      (setq secure-icp-default-p default-p)
      (setq secure-icp-initialized-p (/=f rc 0)))))

(def-command-line-argument icp-log-intensity ((value? :keyword))
  (let ((integer?
      (if value?
          (or (read-fixnum-from-string value?)
              7);means invalid option value
          nil)));no tracing by default 
    (when integer?
      (when (or (<f integer? 0) (>f integer? 6))
    (setq integer? 7))) ;means invalid option value
      integer?))              

;;;; Simplified GL <-> C Interface



;;; This interface is based on a thin layer above the Lucid/Chestnut
;;; foreign function and structure stuff.  It will all remain as a
;;; development-only facility until Rick applies the Chestnut patches
;;; and upgrades.

#+c-struct-interface
(defmacro def-c-function (name-and-options &body arg-descriptions)
  (unless (and (listp name-and-options)
               (assq :return-type (cdr name-and-options))
               (assq :name (cdr name-and-options)))
    (error "Name and return type must be specified"))
  (let* ((name (car name-and-options))
         (options (cdr name-and-options))
         (macro-name
           (if (and (eval-feature :chestnut-3)
                    (eval-feature :chestnut-trans))
               (intern "DEF-FOREIGN-FUNCTION" "TX")
               'lcl::def-foreign-function))
         (foreign-function-name
           (cadr (assq :name options)))
         (real-name
           (feature-case
             ((and (not :translator) :sunos-but-not-solaris)
              (format nil "_~a" foreign-function-name))
             ((and (not :translator) :solaris)
              (format nil "~a" foreign-function-name))
             (t foreign-function-name))))
    (let ((pair (assq :name options)))
      (setf (cadr pair) real-name))
    (unless (assq :language options)
      (push (list :language :c) options))
    `(,macro-name (,name ,@options)
       ,@arg-descriptions)))

#+c-struct-interface
(defmacro def-c-callback (name-and-options &body body)
  `(,(if (and (eval-feature :chestnut-3)
              (eval-feature :chestnut-trans))
         (intern "DEF-FOREIGN-CALLABLE" "TX")
         'lcl::def-foreign-callable)
     ,name-and-options
     ,@body))

(def-global-property-name foreign-struct-info)

(def-structure foreign-struct-info
  (foreign-struct-constructor nil)
  (foreign-struct-reclaimer nil)
  (foreign-struct-free-list nil)
  (foreign-struct-allocated-count 0)
  (foreign-struct-in-use-count 0)
  (foreign-struct-describer nil))

#+c-struct-interface
(defmacro foreign-pointer-type (x)
  `(,(if (and (eval-feature :chestnut-3)
              (eval-feature :chestnut-trans))
         (intern "FOREIGN-POINTER-TYPE" "TX")
         'lcl::foreign-pointer-type)
     ,x))

#+c-struct-interface
(defmacro foreign-struct-type-name (foreign-type)
  `(car-of-cons
     (cdr-of-cons
       (,(if (and (eval-feature :chestnut-3)
                  (eval-feature :chestnut-trans))
             (intern "FOREIGN-TYPE-NAME" "TX")
             'lucid::foreign-type-name)
           (foreign-pointer-type
             ,foreign-type)))))

(defun-for-macro parse-c-struct-slot-specs
    (struct-name slot-specs-with-reclaimers)
  (loop with slot-specs = '()
        with slots-with-reclaimers = '()
        with full-names = '()
        for (name . plist) in slot-specs-with-reclaimers
        as reclaimer? = (getf plist :reclaimer)
        as concatenated-name = (build-ab-symbol struct-name name)
        as slot-spec = (list name)
        do
    (push concatenated-name full-names)
    (when reclaimer?
      (push (cons concatenated-name reclaimer?)
            slots-with-reclaimers))
    (when (getf plist :type)
      (setf (getf (cdr slot-spec) :type) (getf plist :type)))
    (when (getf plist :overlays)
      (setf (getf (cdr slot-spec) :overlays) (getf plist :overlays)))
    (when (getf plist :offset)
      (setf (getf (cdr slot-spec) :offset) (getf plist :offset)))
    (push slot-spec slot-specs)
        finally
          (return (values (nreverse slot-specs)
                          (nreverse slots-with-reclaimers)
                          (nreverse full-names)))))

#+c-struct-interface
(defmacro def-c-struct (name-and-options &body slot-specs-with-reclaimers)
  (let* ((name (if (consp name-and-options)
                   (car name-and-options)
                   name-and-options))
         (macro-name
           (if (and (eval-feature :chestnut-3)
                    (eval-feature :chestnut-trans))
               (intern "DEF-FOREIGN-STRUCT" "TX")
               'lcl::def-foreign-struct))
         (describer-name (build-ab-symbol 'describe name))
         (constructor-name (build-ab-symbol 'make name))
         (reclaimer-name (build-ab-symbol 'reclaim name 'internal)))
    (multiple-value-bind (slot-specs slots-with-reclaimers full-names)
        (parse-c-struct-slot-specs name slot-specs-with-reclaimers)
      `(progn
         (,macro-name ,name-and-options
                      ,@slot-specs)
         (defun ,describer-name (struct)
           (format t "~s a struct of type ~s~%"
                   struct ',name)
           ,@(loop for name in full-names
                   collect
                   `(format t "  ~s        ~40T~s~%"
                            ',name (,name struct))))
         (let ((info (or (foreign-struct-info ',name)
                         (setf (foreign-struct-info ',name)
                               (make-foreign-struct-info)))))
           (setf (foreign-struct-constructor info)
                 ',constructor-name)
           (setf (foreign-struct-describer info)
                 ',describer-name)
           (setf (foreign-struct-reclaimer info)
                 ',(and slots-with-reclaimers reclaimer-name)))
         ,(and
            slots-with-reclaimers
            `(defun ,reclaimer-name (foreign-pointer)
               ,@(loop for (slot-name . reclaimer) in slots-with-reclaimers
                   collect
                       `(,reclaimer (,slot-name foreign-pointer)))))))))

#+c-struct-interface
(defun-simple allocate-c-struct (type)
  (let* ((info (foreign-struct-info type))
         (free-list (foreign-struct-free-list info)))
    (cond
      (free-list
       (incff (foreign-struct-in-use-count info))
       (gensym-pop (foreign-struct-free-list info)))
      (t
       (let ((new-struct (funcall (foreign-struct-constructor info))))
         (incff (foreign-struct-allocated-count info))
         (incff (foreign-struct-in-use-count info))
         new-struct)))))

#+c-struct-interface
(defun-void reclaim-c-struct (c-struct)
  (let* ((info (foreign-struct-info
                 (foreign-struct-type-name c-struct)))
         (reclaimer? (foreign-struct-reclaimer info)))
    (when reclaimer?
      (funcall reclaimer? c-struct))
    (decff (foreign-struct-allocated-count info))
    (decff (foreign-struct-in-use-count info))
    (gensym-push c-struct (foreign-struct-free-list info))))

#+c-struct-interface
(defun describe-c-struct (struct)
  (let* ((foreign-type-name (foreign-struct-type-name struct))
         (info (foreign-struct-info foreign-type-name)))
    (funcall (foreign-struct-describer info) struct)))




;;;; Testing Code for C structs and functions

#|

typedef struct c_struct_1
  {
    unsigned long a;
    short b;
} c_struct_1;


long c_struct_fill(c_struct_1 *the_struct)
{
  the_struct->a = 777777;
  the_struct->b = -19;
  return 123;
}

|#


#+testing-only
(def-c-struct c-struct-1
  (a :type :unsigned-32bit)
  (b :type :signed-16bit))

#+testing-only
(def-c-function (c-struct-fill
                  (:return-type :signed-32bit)
                  (:name "c_struct_fill"))
    (the-struct (:pointer c-struct-1)))

#+testing-only
(defun foreign-struct-test ()
  (let ((struct (allocate-c-struct 'c-struct-1)))
    (describe-c-struct struct)
    (let ((res (c-struct-fill struct)))
      (format t "~&res=~s~%" res)
      (describe-c-struct struct)
      (reclaim-c-struct struct))))





;;;; Eq Hash Tables




;; This is broken in develelopment unless thing-exp was allocated in
;; static-memory, or GC (including ephemeral) is completely turned off.  This is
;; because sys:%pointer (and presumably excl::pointer-to-address) will return a
;; diferrent value before and after a GC, thus losing the entry in the hash
;; table.  But this tends to not be a problem, since we allocate basically
;; everything in static areas, but it's something to be aware of. -dkuznick,
;; 10/5/00
;; The last sentence above is wrong.  We do in fact allocate everything in
;; relocatable memory so it does get moved around by a GC. So this basically IS
;; broken in development -dkuznick, 1/15/03

;;; We fix this by, in development, assigning a hash value to each
;;; object the first time it is inserted in a hash table. We store
;;; this value in a common-lisp hash table. This is silly from the
;;; point of view of efficiency, since it means that we are implementing
;;; an eq-hash table (that is, the thing we create using make-eq-hash-table
;;; by building it out of an eq hash table (that is, the thing
;;; that is created by (make-hash-table :test #'eq). But it
;;; allows us to use the delivery hash table code in development,
;;; which is good on general priciples because it lets us
;;; debug eq hash table problems. -alatto, 2/10/03

;;; To avoid keeping transient objects around forever because
;;; of the hash table we use to store their hash values, we
;;; reference count them. -alatto, 2/18/03
#+development
(defvar eq-hash-values-table (make-hash-table :size 1000 :test #'eq))

;;; The reference count for an item in eq-hash-values-table is one
;;; for each place the hash table is currently being stored. This
;;; includes both the hash tables, and temporary storage in
;;; a local variable. So any call to eqhash increments the reference
;;; count, since the code is now storing it in a local. This code
;;; is then responsible for decrementing the reference count when
;;; it is done using the variable. Thus the reference count is incremented
;;; in eqhash, and every call to eqhash (with one exception) is
;;; paired with a call to decf-eqhash-reference-count, when the
;;; code is done with its reference to the eqhash. The one exception
;;; is the call to eqhash in puthash. Here, if a new key is being
;;; added to an eqhash table, there is a permanent new reference, so
;;; we don't decrement the hash value. If the key already exists
;;; in the hash table, so we are just changing the associated value,
;;; we decrement the reference count as usual.

#+development
(defvar eq-reference-count-table (make-hash-table :size 1000 :test #'eq))

(defvar next-eq-hash-value 0)

#+development
(defmacro incf-eqhash-reference-count (key)
  (avoiding-variable-capture (key)
    `(let ((refcount (gethash ,key eq-reference-count-table)))
       (if refcount
           (setf (gethash ,key eq-reference-count-table) (1+f refcount))
           (setf (gethash ,key eq-reference-count-table) 1)))))

#+development
(defmacro decf-eqhash-reference-count (key)
  (avoiding-variable-capture (key)
    `(unless (fixnump ,key)
       (let ((refcount (gethash ,key eq-reference-count-table)))
         (if refcount
             (if (=f refcount 1)
                 #-ansi-cl
                 (progn
                   (lisp:remhash ,key eq-reference-count-table)
                   (lisp:remhash ,key eq-hash-values-table))
                 #+ansi-cl
                 (progn
                   (common-lisp:remhash ,key eq-reference-count-table)
                   (common-lisp:remhash ,key eq-hash-values-table))
                 (setf (gethash ,key eq-reference-count-table) (1-f refcount)))
             (cerror "continue anyway"
                     "Could not find key ~A in eq-reference-count-table" ,key))))))


(defmacro eqhash (thing-exp)
  `(let ((thing ,thing-exp))
     (if (fixnump thing)
         (if (<f thing 0)
             (-f thing)
             thing)
         ,(if (and (eval-feature :chestnut-3)
                   (eval-feature :chestnut-trans))
              `(logandf (sxhash-symbol-1 thing) most-positive-fixnum)
              #-development
              `(logandf (sxhash thing) most-positive-fixnum)
              #+development
              `(let ((value (gethash thing eq-hash-values-table)))
                 (unless value
                   (setf value
                         next-eq-hash-value)
                   (setf (gethash thing eq-hash-values-table) value)
                   (incf next-eq-hash-value)
                   (when (eql next-eq-hash-value most-positive-fixnum)
                     (setf next-eq-hash-value 0)))
                 (incf-eqhash-reference-count thing)
                 value)))))

(def-structure (eq-hash-table
                 (:constructor make-eq-hash-table-internal)
                 (:reclaimer reclaim-eq-hash-table-internal))
  (eq-hash-table-vector nil)
  (eq-hash-table-size nil)
  (eq-hash-table-count nil)
  (eq-hash-table-key-reclaimer nil)
  (eq-hash-table-value-reclaimer nil))

;;; `make-eq-hash-table' makes a hash table with eq as its comparison
;;; function.  It takes a size and resolves collisions by chaining,
;;; so don't give it sizes that are vastly underestimated.  It takes
;;; key and value reclaimers which can be null.  Null indicates that
;;; the keys or values do not need any reclamation.  The value-reclaimer
;;; will be called on eq-puthash over-writes and on eq-remhash.  The
;;; key-reclaimer will be called on remash.  Both will be called in
;;; by reclaim-eq-hash-table.

(defun make-eq-hash-table (size key-reclaimer? value-reclaimer?)
  (let ((table (make-eq-hash-table-internal)))
    (setf (eq-hash-table-vector table)
          (loop with vec = (allocate-managed-simple-vector size)
                for i from 0 below size
                do
            (setf (svref vec i) nil)
                finally
                  (return vec)))
    (setf (eq-hash-table-size table) size)
    (setf (eq-hash-table-count table) 0)
    (setf (eq-hash-table-key-reclaimer table)
          #-development key-reclaimer?
          #+development (if key-reclaimer?
                            #'(lambda (key) (funcall key-reclaimer? key)
                                      (decf-eqhash-reference-count key))
                            #'(lambda (key) (decf-eqhash-reference-count key))))
    (setf (eq-hash-table-value-reclaimer table) value-reclaimer?)
    table))

;;; Useful debugging function, to see what's in a hash table.
#+development
(defun dump-hash-table (table)
  (let ((pairs nil))
    (maphash #'(lambda (k v) (push (cons k v) pairs)) table)
    pairs))

;;; Returns a fresh gensym-list of all table keys
(defun eq-hash-table-keys (table)
  (let ((vector (eq-hash-table-vector table))
	(length (eq-hash-table-size table))
	(result (gensym-list)))
    (loop for i from 0 below length
       as chain = (svref vector i)
       when chain
       do (loop for pair in chain
	     as key = (car pair)
	     do (gensym-push key result)))
    result))
  
(defun reclaim-eq-hash-table (table)
  (let ((vector (eq-hash-table-vector table))
        (length (eq-hash-table-size table))
        (key-reclaimer? (eq-hash-table-key-reclaimer table))
        (value-reclaimer? (eq-hash-table-value-reclaimer table)))
    (loop for i from 0 below length
          as chain = (svref vector i)
          when chain
            do (cond
                 ((and key-reclaimer? value-reclaimer?)
                  (loop for pair in chain
                        as (key . value) = pair
                        do
                    (funcall key-reclaimer? key)
                    (funcall value-reclaimer? value)
                    (reclaim-gensym-cons pair))
                  (reclaim-gensym-list chain))
                 (value-reclaimer?
                  (loop for pair in chain
                        as (nil . value) = pair
                        do
                    (funcall value-reclaimer? value)
                    (reclaim-gensym-cons pair))
                  (reclaim-gensym-list chain))
                 (key-reclaimer?
                  (loop for pair in chain
                        as (key . nil) = pair
                        do
                    (funcall key-reclaimer? key)
                    (reclaim-gensym-cons pair))
                  (reclaim-gensym-list chain))
                 (t
                  (loop for pair in chain
                        do
                    (reclaim-gensym-cons pair))
                  (reclaim-gensym-list chain))))
    (reclaim-managed-simple-vector vector)
    (reclaim-eq-hash-table-internal table)))

;;; `eq-gethash' does what you think it does and also provides a default-value?
;;; argument so nils that are in the table can be recognized as distinct from
;;; a key not being present.

(defun-simple eq-gethash (table key-object default-value?)
  (let* ((hash-code (eqhash key-object))
         (length (eq-hash-table-size table))
         (vector (eq-hash-table-vector table))
         (chain (svref vector (modf-positive hash-code length))))
    #+development(decf-eqhash-reference-count key-object)
    (loop
       (when (or (null chain) (not (consp chain))) (return default-value?))
       (let ((pair (car-of-cons chain)))
	 (when (consp pair)
	   (when (eq (car-of-cons pair) key-object)
	     (return (cdr-of-cons pair)))))
       (setf chain (cdr-of-cons chain)))))


(defun-simple eq-puthash (table key-object value-object)
  (let* ((hash-code (eqhash key-object))
         (length (eq-hash-table-size table))
         (vector (eq-hash-table-vector table))
         (index  (modf-positive hash-code length))
         (chain (svref vector index))
         (tail chain)
         (value-reclaimer? (eq-hash-table-value-reclaimer table)))
    (loop
      (when (null tail)
        (setf (svref vector index)
              (gensym-cons (gensym-cons key-object value-object)
                           chain))
        (return))
      (let ((pair (car-of-cons tail)))
        (when (eq (car-of-cons pair) key-object)
          (let ((old-value-object (cdr-of-cons pair)))
            (setf (cdr-of-cons pair) value-object)
            (when value-reclaimer?
              (funcall value-reclaimer? old-value-object)))
          #+development(decf-eqhash-reference-count key-object)
          (return)))
      (setf tail (cdr-of-cons tail)))
    value-object))

(defsetf eq-gethash eq-puthash)

(defun-simple eq-remhash (table key-object)
  (let* ((hash-code (eqhash key-object))
         (length (eq-hash-table-size table))
         (vector (eq-hash-table-vector table))
         (index (modf-positive hash-code length))
         (chain (svref vector index))
         (tail chain)
         (prev-tail nil)
         (key-reclaimer? (eq-hash-table-key-reclaimer table))
         (value-reclaimer? (eq-hash-table-value-reclaimer table)))
    #+development(decf-eqhash-reference-count key-object)
    (loop
      (when (null tail)
        (return nil))
      (let ((pair (car-of-cons tail)))
        (when (eq (car-of-cons pair) key-object)
          (let ((old-value-object (cdr-of-cons pair)))
            (cond (prev-tail
                   (setf (cdr-of-cons prev-tail) (cdr-of-cons tail)))
                  (t
                   (setf (svref vector index) (cdr-of-cons tail))))
            (when key-reclaimer?
              (funcall key-reclaimer? key-object))
            (when value-reclaimer?
              (funcall value-reclaimer? old-value-object))
            (reclaim-gensym-cons tail)
            (reclaim-gensym-cons pair)
            (return))))
      (setf prev-tail tail)
      (setf tail (cdr-of-cons tail)))))

;;; Eq item hash tables
;;;
;;;  If the keys or values for your eq-hash-table are frames,
;;;  and you'd like your hash table to deal more gracefully with
;;; deleted items, you probably want to use eq-item-hash-tables instead.
;;; Code for these is in types.lisp.


;;; `Twrite-system-version' ...
;;; N.b. As an alternative to using twrite-system-version there is now
;;; a routine that returns this information as a structure. See
;;; system-version-information-as-structure in file-sysproc. (ddm 7/7/99)

;;; NOTE: this function may be used to print system versions written in
;;; old KB files, DO NOT remove the support for old version formats !!!
;;; -- Chun Tian (binghe), Sep 2013.

(defun twrite-system-version
    (system-version &optional suppress-brief-description-of-system-version?)
  (tformat "Version ~d." (first system-version))
  (multiple-value-bind (tenths hundredths)
      (round (second system-version) 10)
    (tformat "~d" tenths)
    (if (/= hundredths 0)
        (tformat "~d" hundredths)))
  (let ((alpha-or-beta?
	  (alpha-or-beta-of-system-version system-version))
	(patch-level?
	  (patch-level-of-system-version system-version)))
    (if alpha-or-beta?
	(if patch-level?
	    (tformat " ~a~c" alpha-or-beta?
		     (code-char (+ patch-level?
				   #.(1- (char-code #\a)))))
	    (tformat " ~a" alpha-or-beta?))))
  (unless suppress-brief-description-of-system-version?
    (let ((brief-description?
	    (brief-description-of-system-version system-version)))
      (if brief-description?
	  (tformat " ~a" brief-description?)))))

;; This is for G2 2011 and newer title display, won't affect KB
;; compatibility.
(defun twrite-system-version-in-g2-title
    (system-version &optional suppress-brief-description-of-system-version?)
  (tformat "Gensym.~a." (if (g2-enterprise-p) "Enterprise" "Standard"))
  (tformat "~d." external-version)
  (when (<f revision-number-of-current-gensym-product-line 10)
    (twrite-string "0"))
  (tformat "~d" revision-number-of-current-gensym-product-line)
  (unless suppress-brief-description-of-system-version?
    (let ((brief-description?
            (brief-description-of-system-version system-version)))
      (if brief-description?
          (tformat ", ~a" brief-description?)))))

(defun-allowing-unwind write-local-identification-info-text-string ()
  (twith-output-to-text-string
    (write-local-identification-info-text-string-1 t)))

;; Moved this parameter from sequences2.lisp, which is not in GSI. --binghe, 2013/11/22
(defparameter *expiration-date-for-display-in-title* nil)

(defun write-local-identification-info-text-string-1 (write-machine-id-p)
  (multiple-value-bind (host-name port-list)
      (get-raw-network-info)
    (tformat "Host: ~a" host-name)
    (loop for (network-type address secure-p) in port-list
          do (tformat "; ~a: ~a~a" network-type address
                      (secure-icp-string :secure-p secure-p
                                         :network-type network-type)))
    (reclaim-raw-network-info host-name port-list))
  (when write-machine-id-p
    (current-system-case
      (ab (print-first-string-in-pool-group)))) ; print machine ID
  (if *expiration-date-for-display-in-title*
      (tformat "~%Expiration Day:~a~%" *expiration-date-for-display-in-title*)
    (tformat "~%")))

;;; `Get-raw-network-info' returns two values:
;;;   (1) the host name as a reclaimable string
;;;   (2) a slot-value list of slot-value lists detailing the listener addresses
;;;       the first element of which is a reclaimable text string of the form "xxx Port",
;;;       where <xxx> is the English name of a transport layer, i.e., "TCP/IP".
;;;       the second element is a reclaimable text string containing the platform-specific
;;;       name of the port, e.g., "1111" or "G20", and the third element is a boolean
;;;       specifying whether the connection is secure or not.

;; jh, 1/21/92.  Abstracted get-raw-network-info so we can achieve more
;; consistency between the "Network Info" table and the message we put up in the
;; parent window when G2 launches.
;; yduJ, 6/25/06: reformatted, added security flag.

(defun get-raw-network-info ()
  (values
    ;; host name
    (copy-text-string
      (or (get-local-host-name)
          "(Unknown Host)")) ;"anonymous" ??

    ;; address list, a tree of the form
    ;; ( { ( <port type text string>
    ;;       <port address text string>
    ;;       <secure ICP boolean>) } )
    (loop with network-addresses = (get-local-host-addresses)
          for (type-of-network address secure-p) in network-addresses
          collect
            (gensym-list
              (copy-text-string
                (cond
                  ((equalw type-of-network #w"TCP_IP")
                   #w"TCP/IP Port")
                  ;; DECNet no longer supported.  -jv, 10/4/05
                  (t #w"unknown network Port")))
              (tformat-text-string "~a" address)
              secure-p)
            using gensym-cons
          finally
            (reclaim-network-addresses network-addresses))))

(defun reclaim-raw-network-info (host-name port-list)
  (reclaim-if-text-string host-name)
  (reclaim-gensym-tree-with-text-strings port-list))


(defmacro increment-profiled-time (activity-form amount)
  (unless (constantp activity-form)
    (error "~S is not a constant" activity-form))
  (let* ((activity (eval activity-form))
         (accessor (intern (format nil "PROFILING-~A-TIME" activity))))
    `(current-system-case
       (ab (mutate-managed-float-value
             (,accessor profiling-enabled?)
             (+e ,amount (managed-float-value (,accessor profiling-enabled?))))))))

(defmacro register-profiling-activity (activity)
  (let ((incrementp
          (cond ((eq activity 'start)
                 nil)
                ((member activity '(clock-tick icp workstation redraw idle))
                 t)
                (t
                 (error "Unknown activity ~a" activity)))))
    `(current-system-case
       (ab (when profiling-enabled?
             (let ((current-time (gensym-get-unix-time)))
               ,@(when incrementp
                   `((increment-profiled-time
                       ',activity
                       (-e current-time
                           (managed-float-value
                             (start-time-of-last-profile-change profiling-enabled?))))))
               (mutate-managed-float-value
                 (start-time-of-last-profile-change profiling-enabled?)
                 current-time)
               nil))))))

(defmacro with-temporary-profiling-context (activity &rest body)
  (let ((previous-start-time-value-name (gensym))
        (current-last-start-time-value-name (gensym))
        (profiling-initially-enabled? (gensym))
        (start-time-of-this-scope-value-name (gensym))
        (current-time-name (gensym))
        (time-delta-name (gensym))
        (permitted-activities '(clock-tick icp workstation redraw)))
    (assert (member activity permitted-activities) nil
            "~a is not one of the permitted activities: ~a" activity permitted-activities)
    `(let ((,profiling-initially-enabled? nil)
           (,previous-start-time-value-name 0.0)
           (,start-time-of-this-scope-value-name 0.0))
       (declare (type gensym-float
                      ,previous-start-time-value-name
                      ,start-time-of-this-scope-value-name))
       ,profiling-initially-enabled?
       ,previous-start-time-value-name
       ,start-time-of-this-scope-value-name
       (current-system-case
         (ab (when profiling-enabled?
               (setq ,profiling-initially-enabled? t)
               (setq ,previous-start-time-value-name
                     (managed-float-value
                       (start-time-of-last-profile-change profiling-enabled?)))
               (setq ,start-time-of-this-scope-value-name
                     (gensym-get-unix-time))
               (mutate-managed-float-value
                 (start-time-of-last-profile-change profiling-enabled?)
                 ,start-time-of-this-scope-value-name))))
       (prog1 ,@body
         (current-system-case
           (ab (when profiling-enabled?
                 (let* ((,current-time-name (gensym-get-unix-time))
                        (,current-last-start-time-value-name
                           (managed-float-value
                             (start-time-of-last-profile-change profiling-enabled?)))
                        (,time-delta-name
                           (-e ,current-time-name ,current-last-start-time-value-name)))
                   (increment-profiled-time ',activity ,time-delta-name)
                   (mutate-managed-float-value
                     (start-time-of-last-profile-change profiling-enabled?)
                     (if ,profiling-initially-enabled?
                         (+e ,previous-start-time-value-name
                             ;;time spent in this context
                             ,time-delta-name
                             ;;time spent in `interior' contexts
                             (-e ,current-last-start-time-value-name
                                 ,start-time-of-this-scope-value-name))
                         ,current-time-name))))))))))

(defun allocate-managed-simple-vector-with-zeros (len)
  (let ((v (allocate-managed-simple-vector len)))
    (loop for i from 0 to (- len 1) do
      (setf (svref v i) 0))
    v))

;;; This function is covered by regression-test: HEX (quantitytests.kb)
(defun read-hex-number-from-text-string (str si ei)
  (declare (type fixnum si ei))
  (let ((number 0))
    (decff ei)
    (incff si 2)
    (when (and (char=w (charw str 0) #.%\0)
	       (or (char=w (charw str 1) #.%\x)
		   (char=w (charw str 1) #.%\X)))
      (let ((result 1)
	    (length (-f ei si)))
	(loop for x from 0 to length
	      while result
	      do
	  (let ((tmp (charw str (-f ei x))))
	    (declare (type fixnum tmp))
	    (setq result (digit-char-pw tmp))
	    (when (not result)
	      (cond ((or (char=w tmp #.%\a) (char=w tmp #.%\A))
		     (setq result 10))
		    ((or (char=w tmp #.%\b) (char=w tmp #.%\B))
		     (setq result 11))
		    ((or (char=w tmp #.%\c) (char=w tmp #.%\C))
		     (setq result 12))
		    ((or (char=w tmp #.%\d) (char=w tmp #.%\D))
		     (setq result 13))
		    ((or (char=w tmp #.%\e) (char=w tmp #.%\E))
		     (setq result 14))
		    ((or (char=w tmp #.%\f) (char=w tmp #.%\F))
		     (setq result 15))
		    ((not result)
		     (setq number 0))))
	    (when result
	      (incf number
		    (* result
		       (let ((y 1))
			 (loop for i from 1 to x do
			    (setq y (* y 16)))
			 y))))))))
    number))
