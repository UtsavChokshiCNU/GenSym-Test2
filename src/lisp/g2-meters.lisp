;;; -*- Mode: LISP; Syntax: Common-lisp; Base: 10; Package: AB -*-
(in-package "AB")

;;;; Module G2-METERS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Jim Allard






;;;; User Interface to G2 Internal Performance Meters





;;; G2 meter data service is not going to be made available to users within
;;; Release 1.0, however the code which implements it will be left in the
;;; system.  It is going to be hidden from users by commenting out the code
;;; which puts in grammar.  It will be possible to reenable this grammar by
;;; calling `define-g2-meter-grammar' outside of a G2 process.  This grammar is
;;; blocked in GRAMMAR2 and below in the def-capability by the final argument of
;;; t.  -jra 4/5/88
;;; The grammar for G2 meters has been enabled for 1.1.  Several of the
;;; meters which do not work across all G2 implementations have been
;;; commented out.	-pto 15aug88

#+obsolete
(defun define-g2-meter-grammar ()
  (add-grammar-rules
    `((data-server-spec ('g2 'meter) g2-meter-data-server)
      (data-server-map ('g2 'meter) g2-meter-data-server))))




;;; A user may set up a sensor to serve values of an G2 Lisp variable by
;;; defining a subclass of variable with the G2 Meter Data Service class mixed
;;; in.  This will define a slot called G2 Meter Name.  The user should set this
;;; slot to the internal meter which he wants to be reflected in the value of
;;; this variable.  Grammar is defined which determines the set of variables
;;; which may be served.

(def-class (g2-meter-data-service variable define-predicate
				  (only-compatible-with variable)
				  (foundation-class variable)
				  not-solely-instantiable
				  not-user-instantiable do-not-put-in-menus)
  (data-server-map g2-meter-data-server
		   (vector-slot) (system) (type data-server-map))
  (g2-meter-name nil (lookup-slot) (system) user-overridable
		 (save) (type g2-meter-name)))




;;; In an attempted bug fix, during the period from June 9th 1994 till January
;;; 5th, 1995, the meter for region-memory-available was switched from using
;;; g2-memory-region-available to g2-memory-region-allocatable, and the meter
;;; for region-memory-size was switched from g2-memory-region-size to
;;; g2-memory-region-available.  This leads to a confusion about whether
;;; g2-memory-region-available really means available or if it means size.  So,
;;; I'm making an arbitrary and capricious judgement that there are more 3.0 kbs
;;; than there are in 4.0 alpha through 4.0 Beta Rev. 19.  So, we will accept
;;; the meaning of available from 3.0, we will change all allocatables to
;;; availables, and we'll reinstate the size function.  The slot putter for
;;; G2-meter-name does this.

(def-slot-putter g2-meter-name (g2-meter-data-service new-value initializing?)
  (when (and initializing?
	     loading-kb-p
	     (not (reinstated-meter-g2-region-memory-size-p))
	     (consp new-value))
    (cond ((eq (car-of-cons new-value) 'g2-region-memory-allocatable)
	   (setf (car new-value) 'g2-region-memory-available))
	  ((eq (car-of-cons new-value) 'g2-memory-allocatable)
	   (setf (car new-value) 'g2-memory-available))))
  (setf (g2-meter-name g2-meter-data-service) new-value))
    




;;; The global variable `g2-meter-names-and-forms' contains a list of pairs of
;;; symbols, the first of which is the name that the user sees for a data
;;; servable G2 meter, the second of which is the symbol that this name actually
;;; maps to, i.e. the symbol whose value is going to be served.  This list is
;;; used by the slot value compiler and slot value writer for the
;;; G2-meter-name slot.

(defvar g2-meter-names-and-forms nil)




;;; Internal-variable-names can either be none, or any of the symbols declared in a
;;; define-internal-variable-names-and-symbols form.

(add-grammar-rules `((g2-meter-name 'none)))




;;; The macro `define-g2-meter-names-and-forms' should be used to define the
;;; set of G2 meter names and the lisp variables or functions that these names
;;; map onto.  This macro will define grammar for each given name, and put each
;;; name/variable pair onto a list which would cause the slot value compiler and
;;; writer to correctly translate between the name seen by the user and the
;;; internal form.

(defmacro define-g2-meter-names-and-forms
	  (&body name-and-symbol-pairs)
  `(progn
     (install-g2-meter-names-and-forms ',name-and-symbol-pairs)
     (add-grammar-rules
       ',(loop for name-and-symbol in name-and-symbol-pairs
	       for name = (car name-and-symbol)
	       collect `(g2-meter-name ',name)))))

(defun install-g2-meter-names-and-forms (list-of-name-and-symbol-pairs)
  (loop for name-and-symbol in list-of-name-and-symbol-pairs
	do
    (if (not (member name-and-symbol g2-meter-names-and-forms))
	(push (copy-tree name-and-symbol) g2-meter-names-and-forms))))





;;; The following is the slot value writer for G2 meter names.  Note that it
;;; uses the value of the G2-METER-NAMES-AND-FORMS list to provide a
;;; translation between internal Lisp symbols (which are stored in the slot) and
;;; the user visible name.

(def-slot-value-writer g2-meter-name (meter-name)
  (if (null meter-name)
      (tprinc "none")
      (loop for name-and-symbol-pair in g2-meter-names-and-forms
	    do
	(if (equal meter-name (second name-and-symbol-pair))
	    (progn
	      (tprinc (first name-and-symbol-pair))
	      (return nil)))
	    finally
	      (tprinc meter-name))))


       
   
;;; The slot value compiler for g2-meter-name expects parse-result to either
;;; be the symbol NONE or some other symbol, a name.  ... It translated between
;;; the user visible name for a G2 meter and the internal Lisp symbol which holds
;;; the value for that meter.

(def-slot-value-compiler g2-meter-name (parse-result)
  (if (eq parse-result 'none)
      nil
      (let ((name-and-form-pair
	      (assq parse-result g2-meter-names-and-forms)))
	(if name-and-form-pair
	    (if (atom (second name-and-form-pair))
		(second name-and-form-pair)
		(copy-list-using-phrase-conses (second name-and-form-pair)))
	    (values
	      bad-phrase
	      (tformat-text-string
		"The name ~a is not among the set of defined G2 meter names."
		parse-result))))))






;;;; Data Server for G2 Meters




;;; This is a data server for supplying values from the Lisp environment back
;;; into G2.


(def-data-server
  'g2-meter-data-server
  'collect-one-shot-data-for-g2-meters
  'begin-collecting-data-for-g2-meters
  'stop-collecting-data-for-g2-meters
  'accept-data-from-g2-meters
  nil
  'initialize-g2-meter-data-server
  'set-external-variable-for-g2-meter
  'shut-down-g2-meter-data-server
  'post-on-message-board
  nil
  nil
  nil)




;;; The macro `form-for-g2-meter' takes a sensor and returns either NIL or a
;;; form which has been defined as a G2 meter.

(def-substitution-macro form-for-g2-meter (sensor)
  (if (g2-meter-data-service-p sensor)
      (get-slot-value sensor 'g2-meter-name)))




;;; The function `collect-one-shot-data-for-g2-meters' will enqueue a value to
;;; be served for this variable.

;; On 04DEC92, we added a check for meter-value? being a bignum because 
;; memory-usage on lispm can exceed the value of most-positive-fixnum (cpm/ghw).

;; The code referencing bignum has been commented out because we no longer
;; support bignums in G2.  (ghw 2/29/95)

(defun-void collect-one-shot-data-for-g2-meters (variable)
  (let ((data-server (data-server 'g2-meter-data-server)))
    (if (server-is-in-use data-server)
	(with-temporary-creation collect-one-shot-data-for-g2-meters
	  (let* ((meter-form (form-for-g2-meter variable))
		 (meter-value?
		   (if meter-form
		       (if (consp meter-form)
			   (if (fboundp (car-of-cons meter-form))
			       (apply (car-of-cons meter-form)
				      (cdr-of-cons meter-form)))
			   (if (boundp meter-form)
			       (symbol-value meter-form))))))
	    (if meter-value?
		(let ((*current-computation-frame* variable)
		      (current-computation-instance data-server))
;                  (when (typep meter-value? 'bignum) 
;		    (setq meter-value?
;			  (coerce-bignum-to-gensym-float meter-value?)))
		  (put-current-value
		    variable
		    meter-value?
		    (cond ((numberp meter-value?)
			   'number)
			  ((symbolp meter-value?)
			   'symbol)
			  ((text-string-p meter-value?)
			   'text)
			  (t
			   'unknown-g2-meter-data-type))
		    nil
		    nil))
		(cond ((not (g2-meter-data-service-p variable))
		       (warning-message 1
			   "The variable ~NF ~A, ~A"
			 variable
			 "attempted to get a value from G2 meter data service"
			 "but its class has not been declared to have that capability."))
		      ((null meter-form)
		       (warning-message 3
			   "The variable ~NF attempted to get a value from the G2 ~
                              meter data service, but it had no G2 meter name ~
                              specified."
			 variable))
		      ;; jh, 5/14/92.  Added this clause before the "internal
		      ;; error" clause because it is a bit severe to call it an
		      ;; "internal error" when the only thing wrong is that the
		      ;; simulator is off.
		      ((and (equal meter-form '(simulator-time-lag))
			    (not (and (simulator-on? simulation-parameters)
				      (not (g1-authorized-p)))))
		       (warning-message 1
			   "The variable ~NF attempted to get a value for the ~
                          simulator time lag, but the simulator is not on."
			 variable))
		      ((consp meter-form)
		       (warning-message 1
			   "The variable ~NF attempted to get a value from the G2 ~
                          meter data service, but the meter's function failed ~
                          to return a value.  This is a G2 internal error!"
			 variable))
		      (t
		       (write-warning-message 1
			 (tformat
			   "The variable ~NF attempted to get a value from ~
                            the G2 meter data service for the meter "
			   variable)
			 (write-slot-value 'g2-meter-name meter-form variable)
			 (tformat
			   ", but failed since this meter was not defined.  ~
			    This is a G2 internal error!")))))))
	;; If the server is not on, give a warning message.
	(warning-message 1
	    "The variable ~NF attempted to get a value from the G2 Meter Data Server~
	 , but the G2 Meter Data Server was not turned on.  Change the G2 ~
         meter data service on? attribute of the data-server-parameters system ~
         table to enable data service to the variable."
	  variable))
    nil))




;;; The function `begin-collecting-data-for-g2-meters' takes as arguments a
;;; sensor frame and an interval.  It will immediately collect one data point
;;; for the sensor, and it will also schedule a task to continue collecting
;;; values at the given interval.

(defun-void begin-collecting-data-for-g2-meters (sensor interval)
  (with-temporary-gensym-float-creation begin-collecting-data-for-g2-meters
    (with-current-scheduling ((task-for-local-data-server? sensor)
			      (priority-of-data-service data-server-parameters)
			      (if (fixnump interval)
				  (coerce-fixnum-to-gensym-float interval)
				  (managed-float-value interval)))
      (collect-one-shot-data-for-g2-meters sensor))))




;;; The function `stop-collecting-data-for-g2-meters' takes a sensor as its
;;; argument, and will cancel the task to collect data for the sensor.  Note
;;; that there still may be a value in the queue for this variable, it will be
;;; allowed to propagate into the variable.

(defun stop-collecting-data-for-g2-meters (sensor)
  (cancel-task (task-for-local-data-server? sensor)))




;;; The function `accept-data-from-g2-meters' is a noop, since all requests for
;;; G2 meters are responded to within the contexts of the begin-collecting-data
;;; and collect-one-shot-data functions.  This function needs to return T to
;;; inform the scheduler that it is finished.

(defun accept-data-from-g2-meters ()
  t)




;;; The function `initialize-g2-meter-data-server' is a function of no arguments
;;; which sets up the G2 meter server for service.

(defun initialize-g2-meter-data-server ()
  (cond ((g2-meter-data-service-on? data-server-parameters)
	 (reset-g2-meters)
	 (setf (server-is-in-use (data-server 'g2-meter-data-server)) t))
	(t
	 (setf (server-is-in-use (data-server 'g2-meter-data-server)) nil)))
  nil)





;;; The function `set-external-variable-for-g2-meter' will set the value of the
;;; symbol associated with a G2 meter sensor to be the passed value.  I'm not
;;; sure that this option should be available, but tally ho and all that.

(defun set-external-variable-for-g2-meter (sensor value data-type)
  (declare (ignore data-type))
  (write-warning-message 1
    (tformat "An attempt was made to set the external value of the sensor ~NF, " sensor)
    (tprinc  "which gets data service through the G2 meter server for the meter ")
    (write-data-server-map-from-slot
      (get-slot-value-if-any sensor 'g2-meter-name)
      sensor)
    (tprinc ", to the value ")
    (write-evaluation-value value)
    (tprinc ".  The set operation is not allowed within this data server."))

  ;; This following code was used to set meter symbol values.  It could go back
  ;; in if we have some meter that we want to let users go in and clobber.  -jra
  ;; 1/27/88

;   (let ((meter-form (form-for-g2-meter sensor)))
;    (if meter-form
;	(setf (symbol-value meter-form) value)
;	(cond ((not (g2-meter-data-service-p sensor))
;	       (warning-message 1
;		 "G2 meter data service attempted to set a value for ~
;                  the sensor ~nf, but its class has not been declared ~
;                  to have that capability."
;		 sensor))
;	      ((null meter-form)
;	       (warning-message 1
;		 "G2 meter data service attempted to set a value for ~
;                  the sensor ~nf, but the sensor had no G2 meter name ~
;                  specified."
;		 sensor)))))
   )




;;; The function `shut-down-g2-meter-data-server' sets the "in use" flag to NIL.

(defun shut-down-g2-meter-data-server ()
  (setf (server-is-in-use (data-server 'g2-meter-data-server)) nil)
  nil)






;;;; Lagged Meter Value Computation




;;; The following code is used to compute the values of lagged meters.

;;; The function `make-boxed-floating-zero' is used to create a new number box
;;; containing a floating point zero when initializing system variables.

(defun make-boxed-floating-zero ()
  (box-value-if-necessary 0.0)) 



;;; The system variable `simulation-values-calculated-this-clock-tick' contains
;;; an integer count of how many values have been calculated for simulation
;;; variables during this clock tick.  The system variable
;;; `simulation-values-calculated-per-second' contains a managed gensym float
;;; which holds the lagged value of the number of simulation values per second.
;;; The function `simulated-values-per-second' returns a floating point number
;;; which meters the number of values for variables that the simulator has been
;;; computing per second.

;; Taken out of AAAI88 version of G2.  -pto 16aug88

; (def-system-variable simulation-values-calculated-this-clock-tick run 0)

; (def-system-variable simulation-values-per-second run
;   (:funcall make-boxed-floating-zero))

; (defun simulated-values-per-second ()
;   (extract-number simulation-values-per-second))




;;; The system variable `rules-invoked-this-clock-tick' counts the number of
;;; rules within a clock tick that have been run, not counting continuations.
;;; The system variable `rule-invocations-per-second' contains a managed gensym
;;; float which holds the lagged value of the number of rule invocations per
;;; second that the system has been running.  The function
;;; `rule-invocations-per-second' takes no arguments and returns a floating
;;; point number which meters a lagged value of the rules which have been
;;; started per second in the system.


;; Taken out of AAAI88 version of G2.  -pto 16aug88

; (def-system-variable rules-invoked-this-clock-tick run 0)

; (def-system-variable rule-invocations-per-second run
;   (:funcall make-boxed-floating-zero))

; (defun rule-invocations-per-second ()
;   (extract-number rule-invocations-per-second))




;;; The system varible `rule-iterations-this-clock-tick' is used to count the
;;; number of passes through iterative bodies in all levels of generic rule
;;; iterations per clock tick.  The system variable
;;; `generic-rule-iterations-per-second' contains a managed gensym float which
;;; holds the lagged value of the number of generic rule iterations per second.
;;; The function `generic-rule-iterations-per-second' returns the float which
;;; meters the number of generic rule iterations per second that the system has
;;; been running.


;; Taken out of AAAI88 version of G2.  -pto 16aug88

; (def-system-variable rule-iterations-this-clock-tick run 0)

; (def-system-variable generic-rule-iterations-per-second run
;   (:funcall make-boxed-floating-zero))

; (defun generic-rule-iterations-per-second ()
;   (extract-number generic-rule-iterations-per-second))




;;; The system variable `formulas-invoked-this-clock-tick' is used to count the
;;; number of successfully run variable formulas within a clock tick, whether
;;; they are specific formulas or generic formulas.  The system variable
;;; `formula-evaluations-per-second' contains the managed gensym float which
;;; meters the number of formulas that the system has been evaluating per
;;; second.  The function `formula-evaluations-per-second' returns a gensym
;;; float which meters the lagged value of the specific and generic formulas
;;; which have been evaluated per second.


;; Taken out of AAAI88 version of G2.  -pto 16aug88

; (def-system-variable formulas-invoked-this-clock-tick run 0)

; (def-system-variable formula-evaluations-per-second run
;   (:funcall make-boxed-floating-zero))

; (defun formula-evaluations-per-second ()
;   (extract-number formula-evaluations-per-second))




;;; The system variable `fixnum-time-units-of-sleep-this-clock-tick' is used to
;;; count the amount of sleep that the system has received during the clock
;;; tick.  This variable is defined in module "cycles".
;;;
;;; The system variable `percent-running' contains a managed gensym float which
;;; meters the lagged value of the percentage of time that the system is
;;; attempting to run versus the amount of time that it is idle.  Note that his
;;; may differ from the actual percentage of run time that the machine is giving
;;; the process, since the operating system scheduler will also schedule other
;;; processes which this process is trying to run.  The function
;;; `percent-running' will return a floating point number out of the
;;; `percent-running' variable.


(def-system-variable percent-running run
  (:funcall make-boxed-floating-zero))

(defun percent-running ()
  (extract-number percent-running))




;;; The system variable `metered-clock-tick-length' contains a managed
;;; gensym-float which meters a lagged value of the length of scheduler clock
;;; ticks.  The function `metered-clock-tick-length' returns the floating point
;;; number which is the value of this meter.


(def-system-variable metered-clock-tick-length run
  (:funcall make-boxed-floating-zero))

(defun metered-clock-tick-length ()
  (managed-float-value metered-clock-tick-length))




;;; The system variable `maximum-clock-tick-length' contains a managed
;;; gensym-float which meters the maximum clock tick length that the system has
;;; experienced this run.  The function `maximum-clock-tick-length' returns the
;;; floating point number that is the value of this variable.


(def-system-variable maximum-clock-tick-length run
  (:funcall make-boxed-floating-zero))

(defun maximum-clock-tick-length ()
  (extract-number maximum-clock-tick-length))





;;; The function `reset-g2-meters' is called by the initialization procedure
;;; after the clocks have been resynchronized.  Code should be placed in this
;;; function for each meter which needs to be reinitialized at the start of
;;; every run.

(defun reset-g2-meters ()
  ;; Reset the maximum tick length meter.
  (store-managed-number maximum-clock-tick-length 0.0)

  ;; Reset the simulation values per second meters.
  ;; Taken out of AAAI88 version of G2.  -pto 16aug88
;  (setq simulation-values-calculated-this-clock-tick 0)
;  (store-managed-number simulation-values-per-second 0.0)

  ;; Reset the rules-per-second meters.
  ;; Taken out of AAAI88 version of G2.  -pto 16aug88
;  (setq rules-invoked-this-clock-tick 0)
;  (store-managed-number rule-invocations-per-second 0.0)

  ;; Reset the formulas-per-second meters.
  ;; Taken out of AAAI88 version of G2.  -pto 16aug88
;  (setq formulas-invoked-this-clock-tick 0)
;  (store-managed-number formula-evaluations-per-second 0.0)

  ;; Reset the rule iterations per second meter.
  ;; Taken out of AAAI88 version of G2.  -pto 16aug88
;  (setq rule-iterations-this-clock-tick 0)
;  (store-managed-number generic-rule-iterations-per-second 0.0)

  ;; Reset the run time meter.
  (setq fixnum-time-units-of-sleep-this-clock-tick 0)
  (store-managed-number percent-running 0.0)

  ;; Reset the clock tick length meter.
  (mutate-managed-float-value metered-clock-tick-length 1.0)

  ;; Reset all the variables used for computing scheduler time lags.
  ;; The following function is defined in module "cycles", by the macro
  ;; define-scheduler-functions-and-variables-for-g2-meters.
  (reset-all-scheduler-lag-time-variables)

  nil)


  

;;; The function `update-meter-values' is called at the start of every new clock
;;; tick.  It takes as an argument the length of the previous clock tick in
;;; fixnum time units, and will update the interval values of all lagged G2
;;; meter values.

;;; Note that all performance meters which measure some characteristic in units
;;; per second are provided to the user as a lagged value, following actual
;;; values in a first order delay with a time constant given by a system table
;;; parameter.  If the lag time is greater than zero, then the following formula
;;; will be used to calculate the new lagged value.

;;;   new-lagged = (1 - beta) * previous-lagged + beta * current-value

;;; where beta = min (1.0, clock-tick-length / lag-time).  If the given lag time
;;; is 0 seconds, then the actual value per second of the previous clock tick
;;; will be used as the new lagged value.

;;; If the passed tick length is zero, then only the tick length meter should be
;;; updated, though the data servers should still be given their chance to run.
;;; Since the accumulators that the meters represent will not be cleared, the
;;; meter update occurring at the next tick will not lose any data.

(defun update-meter-values (fixnum-time-length-of-previous-tick)
  (declare (type fixnum fixnum-time-length-of-previous-tick))
  (when (/=f fixnum-time-length-of-previous-tick 0)
    (with-temporary-gensym-float-creation take-actions-at-start-of-clock-tick
      (let* ((meter-lag-time (meter-lag-time timing-parameters))
	     (float-tick-length (coerce-fixnum-to-gensym-float
				  fixnum-time-length-of-previous-tick))
	     (float-tick-length-in-seconds
	       (/e float-tick-length
		   (coerce-fixnum-to-gensym-float fixnum-time-units-per-second)))
	     (tmp-float 0.0d0))
	(declare (type gensym-float
		       float-tick-length
		       float-tick-length-in-seconds))

	;; Update the MAXIMUM TICK LENGTH meter.
	(if (>e float-tick-length-in-seconds
		(normalize-to-gensym-float maximum-clock-tick-length))
	    (store-managed-number maximum-clock-tick-length
				  float-tick-length-in-seconds))

	;; Update unaccounted for sleeps:
	(when record-fixnum-time-units-of-sleep-this-clock-tick?
	  (let ((wait-period (c-get-waited-period)))
	    (incff fixnum-time-units-of-sleep-this-clock-tick wait-period)
	    (c-reset-waited-period)))

	(setq tmp-float (*e (/e (coerce-fixnum-to-gensym-float
				 (-i fixnum-time-length-of-previous-tick
				     fixnum-time-units-of-sleep-this-clock-tick))
				float-tick-length)
			    100.0d0))

	(if (=f meter-lag-time 0)
	    ;;[THEN]
	    ;; This set of computations is for the ZERO LAG TIME CASE.
	    ;;
	    (progn

	      ;; Update the PERCENT RUNNING variable.
	      (mutate-managed-float-value percent-running tmp-float)

	      (setq fixnum-time-units-of-sleep-this-clock-tick 0)

	      ;; Update the CLOCK TICK LENGTH meter.
	      (mutate-managed-float-value
		metered-clock-tick-length float-tick-length-in-seconds))


	    ;;[ELSE]
	    ;; This set of computations is for the standard LAGGED VALUE CASE.
	    ;;
	    (let* ((beta (mine (/e float-tick-length-in-seconds
				   (coerce-fixnum-to-gensym-float meter-lag-time))
			       1.0d0))
		   (one-minus-beta (-e 1.0d0 beta))
		   (percent-running-calc (+e (*e (managed-float-value percent-running)
						 one-minus-beta)
					     (*e tmp-float beta))))

	      ;; Update the PERCENT-RUNNING meter.
	      ;; Protect the percent-running below 100%
	      (mutate-managed-float-value percent-running percent-running-calc)

	      (setq fixnum-time-units-of-sleep-this-clock-tick 0)

	      ;; Update the clock tick length meter.
	      (mutate-managed-float-value
		metered-clock-tick-length
		(+e (*e (managed-float-value metered-clock-tick-length)
			one-minus-beta)
		    (*e float-tick-length-in-seconds beta)))))))))






;;;; G2 Memory Statistics Report Generator Functions




;;; The following code is used to generate reports of memory usage inside of G2.
;;; Other functions can be added by pushing the symbol which names the function
;;; onto a global list.  These functions should accept one argument, a g2-stream
;;; for file output.

;;; The function `write-g2-stats-header' is called with g2-stream and should
;;; output header information about the current machine, date, and time to the
;;; stream.

(defun write-g2-stats-header (output)
  (g2-stream-write-line "G2 Run Time Statistics" output)
  (g2-stream-terpri output)
  (let ((description (twith-output-to-text-string
		       (twrite-system-version current-system-version))))
    (g2-stream-write-string "G2 " output)
    (g2-stream-write-line description output)
    (reclaim-text-string description))
  (multiple-value-bind (second minute hour date month year)
      (get-decoded-real-time)
    (let ((time (twith-output-to-text-string
		  (print-decoded-time second minute hour date month year))))
      (g2-stream-write-line time output)
      (reclaim-text-string time))))

;added by SoftServe
(def-hash-table uo-memory-usage-information
    :use-binary-tree t)

(defvar uo-memory-usage-information-hash-table (make-uo-memory-usage-information))

(def-structure class-instances-memory-info
 class-name
 instances-counter
 total-memory-usage
 delta-memory
 delta-instances
)

(defvar class-name-max-length 0)

(defun collect-user-objects-memory-consumption-data ()
 (let ((instances-memory 0)
       (instances-number 0) 
       (memory-usage-info nil) 
       (tmp 0))
 (loop for class being each subclass of 'item do
  (setf instances-memory 0)
  (setf memory-usage-info
   (get-uo-memory-usage-information class uo-memory-usage-information-hash-table))
  ;;no instances of this class in previous measure 
  (when (null memory-usage-info)
   (setf memory-usage-info (make-class-instances-memory-info))
   (setf (class-name memory-usage-info) (stringw class)))  
  (loop for instance being each class-instance of class  
   do
	(incff instances-memory (g2-measure-memory-lisp-side instance))
	(incff instances-number))
  ;;update the maximum length of a class name string	
  (setf tmp (wide-string-length (class-name memory-usage-info)))	
  (when (>f tmp class-name-max-length)
   (setf class-name-max-length tmp))
  ;;update delta of memory for the class 
  (setf tmp (total-memory-usage memory-usage-info))
  (setf (total-memory-usage memory-usage-info) instances-memory)
  (setf (delta-memory memory-usage-info) 
   (if (null tmp) instances-memory (-f instances-memory tmp)))
  ;;update delta of instances for the class 
  (setf tmp (instances-counter memory-usage-info))
  (setf (delta-instances memory-usage-info)
   (if (null tmp) instances-number (-f instances-number tmp)))
  ;;finish with data updates
  (setf (instances-counter memory-usage-info) instances-number)
  (setf instances-number 0)
  ;;store data in the hash table and return  
  (set-uo-memory-usage-information-hash-value class uo-memory-usage-information-hash-table memory-usage-info))
  (values class-name-max-length)))

(defconstant spaces-between-columns 6)
(defconstant class-name-column-title #w"Class Name")
(defconstant instances-count-column-title #w"Instances Count")
(defconstant delta-instances-column-title #w"Delta Instances")
(defconstant consumed-memory-column-title #w"Consumed Memory")
(defconstant delta-memory-column-title #w"Delta Memory")

(defun write-user-objects-memory-usage (output)
  (let ((len 0)
        (len-diff 0) 
        (number-string nil)
        (final-string-to-write nil)
        (class-name-max-length 0)
        (instances-count-column-title-len (wide-string-length instances-count-column-title))
        (delta-instances-column-title-len (wide-string-length delta-instances-column-title))
        (consumed-memory-column-title-len (wide-string-length consumed-memory-column-title)))
    (when (write-extended-memory-report? miscellaneous-parameters)
	  (setf class-name-max-length (collect-user-objects-memory-consumption-data))
	  ;;process spaces between columns
	  (incff class-name-max-length spaces-between-columns)
	  (g2-stream-write-line #w"Memory consumption breakdown by class instances" output)
	  (g2-stream-write-line #w"" output)
	  (g2-stream-write-line #w"" output)
	  ;;create and write the table header
	  (setf len-diff (-f class-name-max-length (wide-string-length class-name-column-title)))
	  (setf final-string-to-write 
	   (add-text-to-string-with-align class-name-column-title instances-count-column-title
		len-diff nil nil))
	  (setf final-string-to-write
	   (add-text-to-string-with-align final-string-to-write delta-instances-column-title
		spaces-between-columns t nil))
	  (setf final-string-to-write
	   (add-text-to-string-with-align final-string-to-write consumed-memory-column-title
		spaces-between-columns t nil))
	  (setf final-string-to-write
	   (add-text-to-string-with-align final-string-to-write delta-memory-column-title
		spaces-between-columns t nil))			
	  (g2-stream-write-line final-string-to-write output)								
	  (g2-stream-write-line #w"" output)
	  ;;write the table content
	  (loop for memory-usage-info being each hash-value of uo-memory-usage-information-hash-table do
	   ;;adding a class name and instances count
	   (setf len (wide-string-length (class-name memory-usage-info)))
	   (setf len-diff (-f class-name-max-length len))
	   (setf len (fixnum-twrite-length (instances-counter memory-usage-info)))
	   (setf number-string (make-stringw len))
	   (twrite-fixnum-into-wide-string (instances-counter memory-usage-info) number-string 0)
	   (setf final-string-to-write 
		(add-text-to-string-with-align (class-name memory-usage-info) number-string len-diff nil t))
	   ;;adding delta instances
	   (setf len-diff 
		(-f (+f spaces-between-columns instances-count-column-title-len) len))
	   (setf len (fixnum-twrite-length (delta-instances memory-usage-info)))
	   (setf number-string (make-stringw len))
	   (twrite-fixnum-into-wide-string (delta-instances memory-usage-info) number-string 0)
	   (setf final-string-to-write
		(add-text-to-string-with-align final-string-to-write number-string len-diff t t))
	   ;;adding the consumed memory
	   (setf len-diff 
		(-f (+f spaces-between-columns delta-instances-column-title-len) len))
	   (setf len (fixnum-twrite-length (total-memory-usage memory-usage-info)))
	   (setf number-string (make-stringw len))
	   (twrite-fixnum-into-wide-string (total-memory-usage memory-usage-info) number-string 0)
	   (setf final-string-to-write
		(add-text-to-string-with-align final-string-to-write number-string len-diff t t))
	   ;;adding delta memory
	   (setf len-diff
		(-f (+f spaces-between-columns consumed-memory-column-title-len) len))
	   (setf len (fixnum-twrite-length (delta-memory memory-usage-info)))
	   (setf number-string (make-stringw len))
	   (twrite-fixnum-into-wide-string (delta-memory memory-usage-info) number-string 0)
	   (setf final-string-to-write
		(add-text-to-string-with-align final-string-to-write number-string len-diff t t))		   
	   ;;flush the string 
	   (g2-stream-write-line final-string-to-write output)
	   (reclaim-wide-string final-string-to-write)))))
  
(pushnew 'write-user-objects-memory-usage system-statistics-writers)  
;end of changes


;;; The function `write-frame-vector-pool-statistics' is used when printing
;;; reports of memory usage into a g2-stats file.  It will print the allocated
;;; and reclaimed frame vector statistics for each allocated size of frame vector.

(pushnew 'write-frame-vector-pool-statistics system-statistics-writers)

(defun length-of-frame-vector-chain (frame-vector?)
  (loop for count from 0
	for vector? = frame-vector? then (lookup-structure vector?)
	while vector?
	finally (return count)))

(defun-void write-frame-vector-pool-statistics (output)
  #-SymScale
  (write-array-pool-statistics-table
    "Frame Vector Pools"
    frame-vector-pool-vector
    frame-vector-pool-counts-vector
    (gensym-list-integers
      (length-of-simple-vector frame-vector-pool-vector) 1 1)
    #'length-of-frame-vector-chain
    output)
  ;; In SymScale, we have to do statistics work on each active thread
  #+SymScale
  (loop for i from 0 upto number-of-scheduler-workers ; no need to use g2-max-threads
        do
    (let ((frame-vector-pool-vector (svref frame-vector-pool-array i))
          (title-string
           (tformat-text-string "Frame Vector Pools (thread ~a)" i)))
      ;; call per-thread statistics
      (write-array-pool-statistics-table
        title-string
        frame-vector-pool-vector
        frame-vector-pool-counts-vector
        (gensym-list-integers
          (length-of-simple-vector frame-vector-pool-vector) 1 1)
        #'length-of-frame-vector-chain
        output)
      (g2-stream-terpri output)
      (reclaim-text-string title-string))))

;;; The function `write-simple-vector-pool-statistics' is used when printing
;;; reports of memory usage into a g2-stats file.  It will print the allocated
;;; and reclaimed simple vector statistics for each allocated size of
;;; simple-vector.

(pushnew 'write-simple-vector-pool-statistics system-statistics-writers)

(defun length-of-vector-chain (simple-vector?)
  (loop for count from 0
	for vector? = simple-vector? then (svref vector? 0)
	while vector?
	finally (return count)))

(defun-void write-simple-vector-pool-statistics (output)
  (write-array-pool-statistics-table
    "Simple Vector Pools"
    vector-of-simple-vector-pools
    simple-vector-pool-counts
    (gensym-list-integers
      (length-of-simple-vector vector-of-simple-vector-pools)
      0 1)
    #'length-of-vector-chain
    output)
  (write-array-pool-statistics-table
    "Oversized Simple Vector Pools"
    vector-of-oversized-simple-vector-pools
    oversized-simple-vector-pool-counts
    (gensym-list-integers
      (length-of-simple-vector vector-of-oversized-simple-vector-pools)
      0 1024)
    #'length-of-vector-chain
    output))

(defun-simple gensym-list-integers (length base multiplier)
  (loop with list = (make-gensym-list length)
	for index from base
	for cons on list
	do
    (setf (car cons) (*f index multiplier))
	finally
	  (return list)))




;;; The functions `write-byte-vector-pool-statistics' and
;;; `write-byte-vector-16-pool-statistics' are used to print reports of the
;;; memory usage of these pools into a g2-stats file.

(pushnew `write-byte-vector-16-pool-statistics system-statistics-writers)

(defun-void write-byte-vector-16-pool-statistics (output)
  (write-array-pool-statistics-table
    "Byte-vector-16 Pools"
    byte-vector-16-pools
    byte-vector-16-pool-counts
    (gensym-list-maximum-buffer-sizes byte-vector-16-allocation-schemes)
    #'length
    output))



;;; The function `write-string-pool-statistics' is used when printing reports of
;;; memory usage into a g2-stats file.  It will print the allocated and
;;; reclaimed string statistics for each separate cluster of allocated strings.
;;; Note that this function must not use the string pools to generate its
;;; output, so that this facility cannot effect what it is reporting about.

;;; There are four sets of string pools, text-strings, short-simple-gensym-strings,
;;; long-simple-gensym-strings, and adjustable-gensym-strings.
;;; Short-simple-gensym-strings is a simple-vector that holds lists of strings of
;;; equal sizes, where the length is the index into the array.
;;; Long-simple-gensym-strings is a simple-vector of lists of strings of similar
;;; (but varying) sizes, allocated according to the string-allocation-schemes
;;; directive.  Adjustable-gensym-strings is a simple-vector of lists of
;;; fill-pointered strings of equal sizes allocated according to the
;;; string-allocation-schemes directive.

(pushnew 'write-string-pool-statistics system-statistics-writers)

(defun-void write-string-pool-statistics (output)

  ;; NOTHING YET FOR WIDE-STRIN/TEXT-STRING! (MHD 2/22/96)
  
  (write-array-pool-statistics-table
    "Short Simple Text String Pools"
    short-simple-gensym-strings
    short-simple-gensym-string-counts
    (gensym-list-integers
      (length-of-simple-vector short-simple-gensym-strings)
      0 1)
    #'length
    output)
  (g2-stream-terpri output)
  (write-array-pool-statistics-table
    "Long Simple Text String Pools"
    long-simple-gensym-strings
    long-simple-gensym-string-counts
    (gensym-list-maximum-buffer-sizes string-allocation-schemes)
    #'length
    output)
  (g2-stream-terpri output)
  (write-array-pool-statistics-table
    "Adjustable Text String Pools"
    adjustable-gensym-strings
    adjustable-gensym-string-counts
    (gensym-list-maximum-buffer-sizes string-allocation-schemes)
    #'length
    output))

(defun-void write-array-pool-statistics-table
    (pool-title pool-vector count-vector max-sizes-list length-function output)
  (g2-stream-write-line pool-title output)
  (loop with column-count = 3
	for pool from 0
	for max-size in max-sizes-list
	for reclaimed = (funcall length-function (svref pool-vector pool))
	for count = (svref count-vector pool)
	unless (and (=f reclaimed 0) (=f count 0))
	  collect (gensym-list max-size reclaimed count)
	    into entries using gensym-cons
	finally
	  (loop for column from 0 below column-count do
	    (unless (=f column 0) (g2-stream-write-string "   " output))
	    (g2-stream-write-string "Length    Out Count %Out" output))
	  (g2-stream-terpri output)
	  (loop with rows = (split-list-into-rows-of-columns entries column-count)
		for columns in rows do
	    (loop for column in columns
		  for first? = t then nil
		  for (max-size reclaimed count) = column
		  for out = (-f count reclaimed)
		  for percent-out = (floorf (*f out 100) (maxf count 1))
		  do
	      (unless first? (g2-stream-write-string "   " output))
	      (write-string-stats-field-value max-size 7 t #\. output)
	      (write-string-stats-field-value out 6 nil #\space output)
	      (write-string-stats-field-value count 6 nil #\space output)
	      (write-string-stats-field-value percent-out 4 nil #\space output)
	      (g2-stream-write-char #\% output)
	      (reclaim-gensym-list column))
	    (reclaim-gensym-list columns)
	    (g2-stream-terpri output)
		finally
		  (reclaim-gensym-list rows)))
  (reclaim-gensym-list max-sizes-list))

(defun split-list-into-rows-of-columns (entries columns)
  (let* ((count (length entries))
	 (row-count (ceilingf-positive count columns))
	 (row-list (fill (make-gensym-list row-count) nil)))
    (loop for row-cons = row-list
		       then (or (cdr row-cons) row-list)
	  for entry-cons = entries then next-entry
	  while entry-cons
	  for next-entry = (cdr-of-cons entry-cons)
	  do
      (setf (cdr entry-cons) nil)
      (setf (car row-cons) (nconc (car row-cons) entry-cons)))
    row-list))

(defun-void write-string-stats-field-value
    (fixnum-to-write field-width right-pad? pad-char g2-output-stream)
  (declare (type fixnum fixnum-to-write field-width))
  (let ((number-width
	  (if (=f fixnum-to-write 0)
	      1
	      (+f (fixnum-order-of-magnitude (absf fixnum-to-write))
		  (if (minuspf fixnum-to-write) 2 1)))))
    (declare (type fixnum number-width))
    (when right-pad?
      (write-string-stats-fixnum fixnum-to-write g2-output-stream))
    (loop repeat (-f field-width number-width) do
      (g2-stream-write-char pad-char g2-output-stream))
    (when (not right-pad?)
      (write-string-stats-fixnum fixnum-to-write g2-output-stream))))

(defun-void write-string-stats-fixnum (fixnum-to-write g2-output-stream)
  (declare (type fixnum fixnum-to-write))
  (cond ((=f fixnum-to-write most-negative-fixnum)
	 ;; Negating most-negative-fixnum yeilds a bignum, so special case it.
	 (g2-stream-write-string
	   most-negative-fixnum-as-string
	   g2-output-stream))
	((<f fixnum-to-write 0)
	 (g2-stream-write-char #\- g2-output-stream)
	 (write-string-stats-positive-fixnum (-f fixnum-to-write) g2-output-stream))
	(t
	 (write-string-stats-positive-fixnum fixnum-to-write g2-output-stream))))

(defun-void write-string-stats-positive-fixnum (fixnum-to-write g2-output-stream)
  (declare (type fixnum fixnum-to-write))
  (if (<f fixnum-to-write 10)
      (g2-stream-write-char (digit-char fixnum-to-write) g2-output-stream)
      (let ((quotient (floorf-positive fixnum-to-write 10))
	    (remainder (modf-positive fixnum-to-write 10)))
	(declare (type fixnum remainder))
	(write-string-stats-positive-fixnum quotient g2-output-stream)
	(g2-stream-write-char (digit-char remainder) g2-output-stream))))




;;; The function `write-lru-queue-statistics' is used when printing reports of
;;; system memory usage.  It receives a g2-stream as its only argument and writes
;;; a report of lru-queue statistics for the icon-rendering, graph-rendering, and
;;; scaled-font lru queues.  The report indicates the total memory allocated in
;;; each lru queue.  Most of the memory used by icon-renderings, graph-renderings,
;;; and scaled-fonts, is used for the rasters contained in these structures.
;;; Since no other structures in the system contain rasters, this report gives a
;;; good idea of the total amount of memory allocated to rasters.  The memory
;;; statistics written here are in units of 8 bit bytes.  It is assumed that one
;;; pixel in a raster takes up one bit.

(pushnew 'write-lru-queue-statistics system-statistics-writers)

(defun write-lru-queue-statistics (output)
  (g2-stream-write-line "LRU Queue Statistics" output)
  (let ((string-var nil))
    (setq string-var
	  (tformat-text-string "Scaled Font LRU Queue Memory Usage             = ~a"
			       (compute-memory-for-scaled-font-lru-queue)))
    (g2-stream-write-line string-var output)
    (reclaim-text-string string-var)
    (setq string-var
	  (tformat-text-string "Icon Rendering LRU Queue Memory Usage          = ~a"
			       (compute-memory-for-icon-rendering-lru-queue)))
    (g2-stream-write-line string-var output)
    (reclaim-text-string string-var)
    (setq string-var
	  (tformat-text-string "Graph Rendering LRU Queue Memory Usage         = ~a"
			       (compute-memory-for-graph-rendering-lru-queue)))
    (g2-stream-write-line string-var output)
    (reclaim-text-string string-var)))

(defun compute-memory-for-scaled-font-lru-queue ()
  (accumulate-lru-queue-memory-size
    scaled-font-lru-queue 'compute-true-size-of-scaled-font))

(defun compute-memory-for-icon-rendering-lru-queue ()
  (accumulate-lru-queue-memory-size
    icon-rendering-lru-queue 'compute-true-size-of-icon-rendering))

(defun compute-memory-for-graph-rendering-lru-queue ()
  (accumulate-lru-queue-memory-size
    graph-rendering-lru-queue 'compute-true-size-of-graph-rendering))

(defun accumulate-lru-queue-memory-size
    (lru-queue lru-element-size-function-name)
  (* 4   ; to get bytes rather than 32 bit words.
     (loop as lru-element? 
	      = (least-recently-used-lru-element lru-queue)
	      then (lru-element-next-element lru-element?)
	   while lru-element?
	   until (eq lru-element? lru-queue)
	   sum (funcall lru-element-size-function-name lru-element?))))




;;; The function `write-pool-memory-usage' produces the same output as the
;;; memory function, but receives a g2-stream to which the output should be
;;; sent.

(pushnew 'write-pool-memory-usage system-statistics-writers)


(defun-simple twrite-pool-entry-data-type-tersely (pool-entry-data-type)
  (when (consp pool-entry-data-type)
    (setq pool-entry-data-type (car pool-entry-data-type)))
  (case pool-entry-data-type
    (symbol        (twrite-string "SYMBOL"))
    (cons          (twrite-string "CONS"))
    (structure     (twrite-string "STRUCT"))
    (simple-vector (twrite-string "SVECTOR"))
    (vector        (twrite-string "VECTOR"))
    (simple-string (twrite-string "SSTRING"))
    (string        (twrite-string "STRING"))
    (simple-array  (twrite-string "SARRAY"))
    (array         (twrite-string "ARRAY"))
    (otherwise     (write-s-expression pool-entry-data-type))))

(defun write-pool-memory-usage (output)
  (g2-stream-write-line "System Object Pool Usage Statistics" output)
  (write-padded-string output "Pool Name" #\space 29 nil)
  (g2-stream-write-char #\space output)
  ;; The column sizes (fourth argument) must remain in synch with the numbers
  ;; below.  If you want to change the size of a column, you must do it in two
  ;; places.  This likely could be improved, if we cared enough. -jv, 11/26/04
  (write-padded-string output "Type" #\space 8 nil)
  (write-padded-string output "Out" #\space 10 t)
  (write-padded-string output "%Out" #\space 5 t)
  (write-padded-string output "Count" #\space 10 t)
  (write-padded-string output "dCount" #\space 8 t)
  (write-padded-string output "Memory" #\space 10 t)
  (write-padded-string output "dMemory" #\space 8 t)
  (g2-stream-terpri output)
  (loop with string-var = nil
	for meter-entry in object-pool-meters
	for snapshot-entry in last-memory-stats-snapshot
	for pool-name = (pool-entry-name meter-entry)
	for out = (pool-entry-outstanding-object-count meter-entry)
	for count = (pool-entry-object-count meter-entry)
	for old-count = (second snapshot-entry)
	for bytes = (pool-entry-memory-usage-in-bytes meter-entry)
	for old-bytes = (first snapshot-entry)
	do
    (unless (and (=f count 0) (=f out 0) (=f bytes 0))
      (write-padded-string output (symbol-name pool-name) #\space 29 nil)
      (g2-stream-write-char #\space output)
      (macrolet ((write-row (right-p form &optional (column-size 8))
		   `(progn
		      (setq string-var
			    (twith-output-to-text-string ,form))
		      (write-padded-string
			output string-var #\space ,column-size ,right-p)
		      (reclaim-text-string string-var))))
	(write-row nil (twrite-pool-entry-data-type-tersely
			 (pool-entry-data-type meter-entry)) 8)
	(write-row t (twrite out) 10)
	(write-row t (twrite (floorf (*f out 100) (maxf count 1))) 5)
	(write-row t (twrite count) 10)
	(let ((delta (-f count old-count)))
	  (write-row t (twrite (if (=f delta 0) "" delta)) 8))
	(write-row t (twrite bytes) 10)
	(let ((delta (-f bytes old-bytes)))
	  (write-row t (twrite (if (=f delta 0) "" delta)) 8)))
      (g2-stream-terpri output))))

;;; We'd like to gather some information on who is calling
;;; obtain-simple-gensym-string (as opposed to obtain-string, which gets an
;;; adjustable string for those that are longer than 64) for long lengths,
;;; since those essentially never get reused (since the lengths much
;;; match exactly). Heavy users of long simple-gensym-strings should probably
;;; be rewritten to use adjustable strings or byte-vector-16s or something,
;;; which have fill pointers, and can therefore round up the requested
;;; length and reuse reclaimed strings. This metering should help
;;; us find the heavy users. -alatto, 11/17/04 

(defvar simple-string-stats-namestring
  #w"gensym-string-metering.txt")

;;; Print a header the first time you print a string, and whenever the
;;; parameters change, but not for every string.
(defvar simple-string-stats-header-needed t)

(defvar reclaimed-strings-reported 0)
(defvar allocated-strings-reported 0)

(defun-for-system-procedure g2-set-simple-string-metering-parameters
    (filename min-string-length frequency chars-to-print)
  (declare (keeps-g2-local-variables-valid t))
  (reclaim-text-string simple-string-stats-namestring)
  (setq simple-string-stats-namestring
	(export-text-string
	  (evaluation-text-value filename)
	     'G2-DIRECTORY-PATHNAME))
  (setq min-string-length-to-report
	(evaluation-integer-value min-string-length))
  (unless (eql string-report-frequency (evaluation-integer-value frequency))
    (setq string-reclaims-until-next-report 0)
    (setq string-allocations-until-next-report 0))
  (setq string-report-frequency (evaluation-integer-value frequency))
  (setq string-chars-to-print (evaluation-integer-value chars-to-print))
  (when log-simple-string-data
    (write-g2-string-stats-header #w"Changing simple string metering parameters"))
  (notify-user-at-console-and-on-logbook
    "Setting parameters for string allocation metering: reporting data on string allocations and reclamations in file ~a, for one string in every ~a longer than ~a characters, including first ~a characters of reclaimed string"
    filename frequency min-string-length chars-to-print)
  (reclaim-evaluation-text filename))

(defun-for-system-procedure g2-turn-on-simple-string-metering ()
  (when (write-g2-string-stats-header #w"Starting simple string metering")
    (setq log-simple-string-data t)
    (notify-user-at-console-and-on-logbook
      "Turning on string allocation monitoring")))

(defun-for-system-procedure g2-turn-off-simple-string-metering ()
  (setq log-simple-string-data nil)
  (notify-user-at-console-and-on-logbook
    "Turning off string allocation monitoring")
  (write-g2-string-stats-header #w"Ending simple string metering"))

(defun-for-system-procedure g2-simple-string-metering-include-reclaims ()
  (unless log-simple-string-reclaims
    (setq log-simple-string-reclaims t)
    (when log-simple-string-data
      (write-g2-string-stats-header #w"Metering reclaims and allocations")))
  (notify-user-at-console-and-on-logbook
    "Turning on string reclaimation monitoring"))

(defun-for-system-procedure g2-simple-string-metering-exclude-reclaims ()
  (when log-simple-string-reclaims
    (setq log-simple-string-reclaims nil)
    (when log-simple-string-data
      (write-g2-string-stats-header #w"Metering only allocations")))
  (notify-user-at-console-and-on-logbook
    "Metering only allocations"))


(defun report-simple-string-allocation (length)
  (report-simple-string-metering-data length nil t))

(defun report-simple-string-reclamation (string length)
  (report-simple-string-metering-data length string nil))

(defun-allowing-unwind report-simple-string-metering-data (length string? allocation?)
  ;; Printing to a file allocates simple strings: avoid recursive calls here,
  ;; since the allocation by the metering tools is not what
  ;; we're interested in.
  (let ((log-simple-string-data nil))
    (handling-gensym-file-errors
      (protected-let* ((namestring
			 simple-string-stats-namestring
			 nil)
		       (namestring-for-user
			 (copy-text-string namestring)
			 (reclaim-text-string namestring-for-user)))
	;; :create-if-does-not-exist doesn't seem to work on the PC.
	;; This is a workaround.
	(unless (g2-stream-probe-file-for-exist simple-string-stats-namestring)
	  (g2-stream-with-open-stream
	      (open-g2-stream? namestring
			       :direction :output)
	    (cond (open-g2-stream?
		   (when simple-string-stats-header-needed
		     (write-g2-string-stats-header-to-stream open-g2-stream? nil)
		     (setq simple-string-stats-header-needed nil)))
		  (t (protected-let ((error-string-for-user
				       (import-text-string
					 (g2-stream-error-string)
					 'G2-STREAM-ERROR-STRING)
				       (reclaim-text-string error-string-for-user)))
		       (notify-user
			 "Unable to open G2 statistics file ~s, ~a."
			 namestring-for-user
			 error-string-for-user))))))
	(g2-stream-with-open-stream
	    (open-g2-stream? namestring
			     :direction :append
			     :create-if-does-not-exist :create)
	  (cond (open-g2-stream?
		 (when simple-string-stats-header-needed
		   (write-g2-string-stats-header-to-stream open-g2-stream? nil)
		   (setq simple-string-stats-header-needed nil))
		 (if allocation?
		     (incff allocated-strings-reported)
		     (incff reclaimed-strings-reported))
		 (let ((report-line
			 (if allocation?
			     (tformat-text-string "Allocated string #~a: length is ~a" allocated-strings-reported length)
			     (tformat-text-string "Reclaimed string #~a: length is ~a" reclaimed-strings-reported length))))
		   (g2-stream-write-line report-line open-g2-stream?)
		   (reclaim-text-string report-line))
		 (print-backtrace-to-stream open-g2-stream?)
		 (when (and (not allocation?)
			    (not (zerop string-chars-to-print)))
		   (let* ((length-to-copy
			    (minf (or (length-of-null-terminated-string string?)
				      string-chars-to-print)
				  length))
			  (substring (gensym-string-substring
				       string? 0 length-to-copy))
			  (report-line
			    (tformat-text-string "Initial ~a characters: <~a>"
						 length-to-copy
						 (replace-nulls-by-spaces substring))))
		     (g2-stream-write-line report-line open-g2-stream?)
		     (reclaim-text-string report-line)
		     (reclaim-gensym-string substring))))
		(t (protected-let ((error-string-for-user
				     (import-text-string
				       (g2-stream-error-string)
				       'G2-STREAM-ERROR-STRING)
				     (reclaim-text-string error-string-for-user)))
		     (notify-user
		       "Unable to open G2 statistics file ~s, ~a."
		       namestring-for-user
		       error-string-for-user)))))))))

(defun-allowing-unwind write-g2-string-stats-header (message)
  ;; Printing to a file allocates simple strings: avoid recursive calls here,
  ;; since the allocation by the metering tools is not what
  ;; we're interested in.
  (let ((log-simple-string-data nil))
    (handling-gensym-file-errors
      (protected-let* ((namestring
			 simple-string-stats-namestring
			 nil)
		       (namestring-for-user
			 (copy-text-string namestring)
			 (reclaim-text-string namestring-for-user)))
	;; :create-if-does-not-exist doesn't seem to work on the PC.
	;; This is a workaround. The macrolet is because
	;; g2-stream-with-open-stream insists that the direction be
	;; a compile-time constant.
	(macrolet
	    ((print-header-to-stream (direction)
	       `(g2-stream-with-open-stream
		    (open-g2-stream? namestring
				     :direction ,direction)
		  (cond (open-g2-stream?
			 (write-g2-string-stats-header-to-stream open-g2-stream? message)
			 (setq simple-string-stats-header-needed nil)
			 t)
			(t (protected-let ((error-string-for-user
					     (import-text-string
					       (g2-stream-error-string)
					       'G2-STREAM-ERROR-STRING)
					     (reclaim-text-string error-string-for-user)))
			     (notify-user
			       "Unable to open G2 statistics file ~s, ~a."
			       namestring-for-user
			       error-string-for-user))
			   nil)))))
	  (if (g2-stream-probe-file-for-exist simple-string-stats-namestring)
	      (print-header-to-stream :append)
	      (print-header-to-stream :output)))))))

(defun write-g2-string-stats-header-to-stream (stream message)
  (write-g2-stats-header stream)
  (let ((summary-string (tformat-text-string
			  "Reporting one string in every ~a of length over ~a"
			  string-report-frequency min-string-length-to-report)))
    (g2-stream-write-line summary-string stream)
    (reclaim-text-string summary-string))
  (let ((summary-string (tformat-text-string
			  (if log-simple-string-reclaims
			      "Metering both allocations and reclamations"
			      "Metering only allocations"))))
    (g2-stream-write-line summary-string stream)
    (reclaim-text-string summary-string))
  (when log-simple-string-reclaims
    (let ((summary-string (tformat-text-string
			    "Printing out up to ~a characters from reclaimed strings" string-chars-to-print)))
      (g2-stream-write-line summary-string stream)
      (reclaim-text-string summary-string)))
  (g2-stream-write-line message stream)
  (when message
    (g2-stream-write-line #w"" stream)))

;;; No harm in doing this destructively, since the string is about
;;; to be reclaimed anyway.
(defun replace-nulls-by-spaces (string)
  (loop for index from 0 below (length string) do
    (when (eql (schar string index) #\null)
      (setf (schar string index) #\space)))
  string)

(def-preallocated-text-string backtrace-text-buffer-for-string-metering 4000)
(def-preallocated-gensym-string buffer-for-string-metering 4000)

;;; Note that this macro is not hygenic; it will decrement the index
;;; as a side-effect. Index should be a local variable.
(defmacro get-next-backtrace-information (index)
  `(if (<f ,index 0)
       nil
       (prog1
	   (svref
	     backtrace-stack-for-internal-error
	     ,index)
	(decff ,index))))

(defun print-backtrace-to-stream (stream)
  (twith-output-to-preallocated-text-string
    backtrace-text-buffer-for-string-metering
    #+(and chestnut-3 chestnut-trans)
    (c-get_backtrace)
    #+(and chestnut-3 chestnut-trans)
    (loop with len = (c-print_backtrace_into_string
		       buffer-for-string-metering 0)
	  for i from 0 below len
	  for ch = (gchar buffer-for-string-metering i nil)
	  do (twrite-char (if (char= #\newline ch)
			      #.%line-separator
			      (code-wide-character (char-code ch)))))
    (tformat "Backtrace:")
    ;; This is in imitation of the code in
    ;; update-backtrace-text-buffer-for-internal-error, but
    ;; we don't want to destroy the backtrace stack so instead of using
    ;; pop-backtrace-information, we navigate the backtrace stack ourselves,
    ;; with our own index.
    (let ((local-backtrace-stack-index index-of-top-of-backtrace-stack))
      (loop until (<f local-backtrace-stack-index 0)
	    do
	(let ((old-top-of-stack local-backtrace-stack-index))
	  (tformat "~%  ~A" (get-next-backtrace-information
			      local-backtrace-stack-index))
	  (let ((twrite-function? (get-next-backtrace-information
				    local-backtrace-stack-index))
		(number-of-args (get-next-backtrace-information
				   local-backtrace-stack-index)))
	    (when twrite-function?
	      (tformat "~%  ")
	      ;; The twrite-function accesses the backtrace stack
	      ;; using index-of-top-of-backtrace-stack. We don't
	      ;; want to modify it globally, since we're trying to
	      ;; get a backtrace nondestructively, so we bind it.
	      (let ((index-of-top-of-backtrace-stack
		      local-backtrace-stack-index))
		(funcall twrite-function?)))
	    ;; The twrite function may have popped the wrong number of args, so we
	    ;; sidestep whatever it did by adjusting the stack pointer according
	    ;; to the number of actual arguments pushed by the backtrace form.
	    (setq local-backtrace-stack-index
		  (-f old-top-of-stack
		      (+f number-of-args size-of-basic-backtrace-information))))))
    (tformat "~%")))
  (g2-stream-write-line backtrace-text-buffer-for-string-metering stream))

(defun write-padded-string (g2-stream string pad-char field-size pad-left?)
  (let ((string-length (if (wide-string-p string)
			   (wide-string-length string)
			   (length string))))
    (cond ((>f string-length field-size)
	   (cond ((wide-string-p string)
		  (loop for index from 0 below field-size do
		    (g2-stream-write-char (charw string index) g2-stream)))
		 (t
		  (loop for index from 0 below field-size do
		    (g2-stream-write-char (char string index) g2-stream)))))
	  (t
	   (when (not pad-left?)
	     (g2-stream-write-string string g2-stream))
	   (loop repeat (-f field-size string-length) do
	     (g2-stream-write-char pad-char g2-stream))
	   (when pad-left?
	     (g2-stream-write-string string g2-stream))))))




;;; The function `write-global-memory-statistics' is used when printing reports
;;; of system memory usage.  It receives a g2-stream as its only argument and
;;; should write a report of global memory statistics to that stream.

(pushnew 'write-global-memory-statistics system-statistics-writers)

(defun write-global-memory-statistics (output)
  (g2-stream-write-line "Overall Memory Usage Statistics" output)
  (let ((string-var
	  (tformat-text-string "Total Memory Usage             = ~a"
			       (g2-memory-usage))))
    (g2-stream-write-line string-var output)
    (reclaim-text-string string-var)
    (setq string-var
	  (tformat-text-string "Total Pool Memory Usage        = ~a"
			       (total-pool-memory-usage)))
    (g2-stream-write-line string-var output)
    (reclaim-text-string string-var)
    (setq string-var
	  (tformat-text-string "Total Pool Objects Outstanding = ~a"
			       (total-pool-outstanding-object-count)))
    (g2-stream-write-line string-var output)
    (reclaim-text-string string-var)
    (setq string-var
	  (tformat-text-string "Total Pool Objects Allocated   = ~a"
			       (total-pool-object-count)))
    (g2-stream-write-line string-var output)
    (reclaim-text-string string-var)))







;;;; Defined G2 Meters




;;; The following is a list of the internal variables which can be served into
;;; G2 and the names that used to present these to the user.

;;; The meter `percent-microsecond-metered-code' meters a lagged value of the
;;; percentage of real time that G2 spends per clock tick inside of code that is
;;; wrapped with the meter-microsecond-performance variable.  This is a Lisp
;;; machine, development only meter for metering how much time we spend inside
;;; of particular sections of G2's code.  By inserting this macro you can meter
;;; the percentage of total time that is spent doing that code.




;;; The meter `percent-run-time' meters a lagged value of the percentage of real
;;; time that G2 is scheduled to run.  Note that this is not a meter of how much
;;; real time G2 is actually getting, since the operating system of the machine
;;; that G2 is running on will be scheduling other tasks to run.


(define-g2-meter-names-and-forms (percent-run-time (percent-running)))




;;; The meter `clock-tick-length' meters a lagged value of the actual length of
;;; the clock ticks in seconds that the scheduler is experiencing.


(define-g2-meter-names-and-forms (clock-tick-length (metered-clock-tick-length)))




;;; The meter `maximum-clock-tick-length' meters the maximum actual length of a
;;; clock tick in seconds that the scheduler has experienced.


(define-g2-meter-names-and-forms (maximum-clock-tick-length (maximum-clock-tick-length)))




;;; The meter `simulator-time-lag' meters the number of seconds of values that
;;; the simulator still needs to supply before it is up to date with the current
;;; time.  This be something other than zero when the simulator has more
;;; simulation to perform than can be done in the time allotted to it in
;;; run-scheduler.


(define-g2-meter-names-and-forms (simulator-time-lag (simulator-time-lag)))




(define-g2-meter-names-and-forms
  (instance-creation-count-as-float (g2-instance-creation-count-as-float)))

;;; The meter `memory-usage' returns an integer specifying the total amount of
;;; dynamic memory usage for this system.  This meter returns a true reading
;;; only for the Lisp machines and Lucid.  The g2-memory-usage function is
;;; defined in PRIMITIVES.


(define-g2-meter-names-and-forms (memory-usage (g2-memory-usage)))

(define-g2-meter-names-and-forms (memory-usage-as-float (g2-memory-usage-as-float)))

(define-g2-meter-names-and-forms (memory-size (g2-memory-size)))

(define-g2-meter-names-and-forms (memory-size-as-float (g2-memory-size-as-float)))

;; jh, 6/11/91.  Added meter for memory size, i.e., the total amount of non-code
;; memory, used and unused, in G2.



;; Added region-specific memory meters and a meter to measure total memory
;; available.  jh, 3/27/91.

(define-g2-meter-names-and-forms (memory-available (g2-memory-available)))

(define-g2-meter-names-and-forms (memory-available-as-float (g2-memory-available-as-float)))

;; jh, 6/10/91.  Changed maximum-memory-regions-in-any-model from 8 to 4, since
;; Chestnut only has 4 regions and it might be difficult explaining why we have 4
;; unused regions on every platform.  We can add more memory meters if needed
;; simply by increasing this constant.

;; jh, 9/11/91.  Changed number of meters to 2.  There are two regions provided by
;; Chestnut, static and dynamic.  G2 uses static memory only to hold symbols;
;; everything else is in dynamic memory (including ICP buffers, which in byegone
;; days were static).

;; fmw, 8/3/94.  Defined a region 3, which is space used for image renderings.


(eval-when (:compile-toplevel :load-toplevel :execute)
(defconstant maximum-memory-regions-in-any-model 3))

(defmacro define-g2-meters-of-memory-regions (usage-or-available-or-size)
  `(progn
     ,@(loop for region-index from 1 to maximum-memory-regions-in-any-model
	     collect
	     `(progn
	      (define-g2-meter-names-and-forms
		(,(intern (format nil "REGION-~a-MEMORY-~a"
				  region-index
				  usage-or-available-or-size))
		  
		 (,(intern (format nil "G2-REGION-MEMORY-~a"
				   usage-or-available-or-size))
		  ,region-index)))
	      (define-g2-meter-names-and-forms
		(,(intern (format nil "REGION-~a-MEMORY-~a-AS-FLOAT"
				  region-index
				  usage-or-available-or-size))
		  
		 (,(intern (format nil "G2-REGION-MEMORY-~a-AS-FLOAT"
				   usage-or-available-or-size))
		  ,region-index)))))))

(define-g2-meters-of-memory-regions usage)

(define-g2-meters-of-memory-regions available)

(define-g2-meters-of-memory-regions size)


;;; The macro `define-g2-meters-of-scheduler-time-lags' expands into
;;; a progn with one function for computing the scheduler time lag for
;;; each priority level.

;;; This macro assumes that the system variable `how-many-priorities?' has
;;; already been defined.  Thus, the module "schedule" should be loaded before
;;; this module "g2-meters".  -pto 16aug88

(defmacro define-functions-of-g2-meters-for-scheduler-time-lags ()
  (loop with meter-functions = nil
	with meter-name = nil
	for priority from 1 to how-many-priorities? doing
    (setq meter-name
	  (intern (format nil "PRIORITY-~a-SCHEDULER-TIME-LAG" priority)))
    ;; The constant g2-meters-scheduler-time-lag-variable-names-format is
    ;; defined in the module "cycles".

    ;; The generic function for extracting scheduler time lags for different
    ;; priority tasks is defined here.  We subtract 1 from the difference of
    ;; last and present gensym-time because the tasks for updating the last
    ;; gensym-time (one for each priority) was scheduled for the present clock
    ;; tick.  If the updating task completes before the meter is read, the
    ;; difference less 1 is -1, otherwise the difference less 1 is 0.  In either
    ;; case, the smallest lag returned is 0 (using max).
    (push `(defun ,meter-name ()
	     (maxe (-e (scheduler-time-lag ,priority) 1.0)
		   0.0))
	  meter-functions)

	finally
	  (return (cons 'progn meter-functions)
		  )))

(define-functions-of-g2-meters-for-scheduler-time-lags)




;;; The macro `define-g2-meters-of-scheduler-time-lags' expands into a
;;; define-g2-meter-names-and-forms which defines meters for each of the
;;; scheduler time lag meters.  This macro assumes that the system variable
;;; `how-many-priorities?' has already been defined.  Thus, the module
;;; "schedule" should be loaded before this module "g2-meters".  -pto 16aug88

(defmacro define-g2-meters-for-scheduler-time-lags ()
  (loop with meter-names-and-forms = nil
	with meter-name = nil
	for priority from 1 to how-many-priorities? doing
    (setq meter-name
	  (intern (format nil "PRIORITY-~a-SCHEDULER-TIME-LAG" priority)))

    (push `(,meter-name (,meter-name)) meter-names-and-forms)
	finally
	  (return (cons 'define-g2-meter-names-and-forms
			(nreverse meter-names-and-forms)))))

(define-g2-meters-for-scheduler-time-lags)




;;; The meter `total-pool-objects-allocated' meters the total number of system
;;; object pool objects which have been allocated into each system pool.  The
;;; meter `total-pool-objects-outstanding' returns a count of the total number
;;; of system object pool objects which have been given out and not yet returned
;;; to a pool.  The meter `total-pool-memory-usage' meters the number of words
;;; of memory that have been allocated to G2 system object pools in this
;;; process.  These are development only meters.

#+development
(define-g2-meter-names-and-forms (total-pool-objects-allocated (total-pool-object-count)))
  
#+development
(define-g2-meter-names-and-forms (total-pool-objects-outstanding
				   (total-pool-outstanding-object-count)))
  
#+development
(define-g2-meter-names-and-forms (total-pool-memory-usage (total-pool-memory-usage)))
  





;;; The macro `define-g2-meters-for-system-object-pools' expands into a
;;; define-g2-meter-names-and-forms which defines meters for each of the system
;;; object pools.  It defines a meter-name-ALLOCATED and a
;;; meter-name-OUTSTANDING which give counts of the numbers of meter pool
;;; objects that have been allocated and a count of the number of those that are
;;; still outstanding.  These are development only meters.

;;; This should be the last set of meters entered here in this file, since these
;;; take up so much space on the meters menu.

#+development
(defmacro define-g2-meters-for-system-object-pools ()
  (loop with meter-names-and-forms = nil
	with allocated-meter-names = nil
	with outstanding-meter-names = nil
	for pool-entry				;work with sorted list
	    in (sort (copy-list object-pool-meters)
		     #'string-greaterp
		     :key #'pool-entry-name)
	for pool-name = (pool-entry-name pool-entry)
	for allocated-meter-name
	    = (intern (format nil "~a-ALLOCATED" pool-name))
	for outstanding-meter-name
	    = (intern (format nil "~a-OUTSTANDING" pool-name))
	do
    (push allocated-meter-name allocated-meter-names)
    (push `(,allocated-meter-name
	    (pool-entry-object-count ,pool-entry))
	  meter-names-and-forms)
    (push outstanding-meter-name outstanding-meter-names)
    (push `(,outstanding-meter-name
	    (pool-entry-outstanding-object-count ,pool-entry))
	  meter-names-and-forms)
	finally
	  (return
	    `(progn
	       (define-g2-meter-names-and-forms ,@meter-names-and-forms)
	       (defparameter g2-outstanding-object-meters
			     ',outstanding-meter-names)
	       (defparameter g2-allocated-object-meters
			     ',allocated-meter-names)))))

#+development
(define-g2-meters-for-system-object-pools)




;;; The function define-system-object-pool-meter-variables is used to create
;;; variable frames which will monitor all system objects pools.  This function
;;; should be used to create a memory meter pool knowledge base for monitoring
;;; memory.  The function takes a new workspace on which all variables should be
;;; placed, a class name for the allocated object pool variables, and a class
;;; name for the outstanding object pool variables.  This function will
;;; instantiate the variables, and place them onto the given workspace.

#+development
(defun define-system-object-pool-meter-variables
       (workspace allocated-class? outstanding-class?)
  (loop with horizontal-spacing = 150
	with vertical-offset = 15
	for y from 0 by 100
	for allocated-meter in g2-allocated-object-meters
	for outstanding-meter in g2-outstanding-object-meters
	do
    (when allocated-class?
      (let ((allocated-variable (make-entity allocated-class?)))
	(add-to-workspace allocated-variable workspace 0 y)
	(change-slot-value allocated-variable 'name-or-names-for-frame
			   allocated-meter)
	(change-slot-value allocated-variable 'validity-interval 1)
	(change-slot-value allocated-variable 'g2-meter-name
			   (copy-tree-using-slot-value-conses
			     (second (assq allocated-meter
					   g2-meter-names-and-forms))))))
    (when outstanding-class?
      (let ((allocated-variable (make-entity outstanding-class?)))
	(add-to-workspace allocated-variable workspace
			  horizontal-spacing (+ y vertical-offset))
	(change-slot-value allocated-variable 'name-or-names-for-frame
			   outstanding-meter)
	(change-slot-value allocated-variable 'validity-interval 1)
	(change-slot-value allocated-variable 'g2-meter-name
			   (copy-tree-using-slot-value-conses
			     (second (assq outstanding-meter
					   g2-meter-names-and-forms))))))))

;;;





#+development
(defmacro define-g2-meters-for-decacheable-structures ()
  (loop with meter-names-and-forms = nil
	for name-and-size-info
	    in names-and-sizes-for-decacheable-structures
	as structure-name = (first name-and-size-info)
	as memory-limit-variable-name = (second name-and-size-info)
	do
    (cond
      ((nthcdr 5 name-and-size-info)
       (loop for size in (nthcdr 5 name-and-size-info)
	     do
	 (setq meter-names-and-forms
	       (nconc meter-names-and-forms
		      `((,(intern 
			    (format nil "DECACHEABLE-~aS-ALLOCATED-FOR-SIZE-~d" 
				    structure-name size))
			 (get-number-allocated-given-variable-and-size
			   ,memory-limit-variable-name ,size))
			(,(intern 
			    (format nil "~a-MEMORY-LIMIT-FOR-SIZE-~d" 
				    structure-name size))
			 (get-limit-given-variable-and-size
			   ,memory-limit-variable-name ,size))
			(,(intern 
			    (format nil "~a-THRASHING-COST-FOR-SIZE-~d" 
				    structure-name size))
			 (get-filtered-thrashing-given-variable-and-size
			   ,memory-limit-variable-name ,size)))))))
      (t
       (setq meter-names-and-forms
	     (nconc meter-names-and-forms
		    `((,(intern 
			  (format nil "DECACHEABLE-~aS-ALLOCATED" 
				  structure-name))
		       (get-number-allocated-given-memory-limit-variable
			 ,memory-limit-variable-name))
		      (,(intern 
			  (format nil "~a-MEMORY-LIMIT" structure-name))
		       (get-limit-given-memory-limit-variable
			 ,memory-limit-variable-name))
		      (,(intern 
			  (format nil "~a-THRASHING-COST" structure-name))
		       (get-filtered-thrashing-given-memory-limit-variable
			 ,memory-limit-variable-name)))))))
	finally
	  (return (cons 'define-g2-meter-names-and-forms 
			meter-names-and-forms))))


#+development
(defun get-number-allocated-given-memory-limit-variable (memory-limit-variable)
  (decacheable-structures-allocated-memory (symbol-value memory-limit-variable)))

#+development
(defun get-limit-given-memory-limit-variable (memory-limit-variable)
  (allocation-limit (symbol-value memory-limit-variable)))

#+development
(defun get-thrashing-given-memory-limit-variable (memory-limit-variable)
  (extract-number-or-value
    (newest-thrashing-ratio (symbol-value memory-limit-variable))))

#+development
(defun get-filtered-thrashing-given-memory-limit-variable 
       (memory-limit-variable)
  (extract-number-or-value
    (filtered-thrashing-ratio (symbol-value memory-limit-variable))))

#+development
(defun get-number-allocated-given-variable-and-size (memory-limit-variable size)
  (decacheable-structures-allocated-memory 
    (get-memory-limit-info-given-size
      (symbol-value memory-limit-variable) size)))

#+development
(defun get-limit-given-variable-and-size (memory-limit-variable size)
  (allocation-limit (get-memory-limit-info-given-size
		      (symbol-value memory-limit-variable) size)))

#+development
(defun get-filtered-thrashing-given-variable-and-size 
       (memory-limit-variable size)
  (extract-number-or-value
    (filtered-thrashing-ratio
      (get-memory-limit-info-given-size
	(symbol-value memory-limit-variable) size))))


#+development
(define-g2-meters-for-decacheable-structures)

;; This must be done here rather than directly in define-decacheable-structure
;; because it uses the macro define-g2-meter-names-and-forms which is 
;; defined in this module.
 





