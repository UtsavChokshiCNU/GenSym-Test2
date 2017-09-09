;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-lisp -*-
(in-package "AB")

;;;; Module SITE

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David


;;; The entire SITE module is for development environments only -- it will not
;;; be loaded in distribution environments.  It is not really part of G2, but
;;; we automatically load it in when we make G2 for convenience. The code in
;;; this file is allowed to cons, since it is just used by people maintaining
;;; the Gensym file systems.






;; NOTE:  We should consider creating dump directories for spun off Lisp
;; machine and Mac distribution binaries.  This will enable us to work with the
;; distribution version without worrying about dumping an inconsistent set of
;; binaries for distribution using g2tape.  -pto 13jan89









;;;; Time Writing Functions



(defun write-universal-time (universal-time)
  (multiple-value-bind (second minute hour date month year
                        day-of-the-week daylight-savings-time-p time-zone)
      (gensym-decode-universal-time universal-time)
    (declare (ignore day-of-the-week daylight-savings-time-p time-zone))
    (write-time second minute hour date month year)))




(defun write-time (second minute hour date month year)
  (format t "~2,'0d ~a ~2,'0d  ~d:~2,'0d:~2,'0d"
          ;; e.g. "10 Dec 86  8:03:16"
          date
          (nth (- month 1)
               '("Jan" "Feb" "Mar" "Apr" "May" "Jun"
                 "Jul" "Aug" "Sep" "Oct" "Nov" "Dec"))
          year
          hour minute second))









;;;; Type-specific arithmetic for site.



;;; +F-for-site, et al, are for fixnums.
;;; +E-for-site, et al, are for floats.

;;; There is not necessarily a complete suite of arithmetic operators.  Developers
;;; should add more as necessary, i.e. when they find that the operation they want
;;; is not defined.

(defmacro +f-for-site (&rest integers)
  `(+ . ,integers))

(defmacro -f-for-site (&rest integers)
  `(- . ,integers))

(defmacro *f-for-site (&rest integers)
  `(* . ,integers))

(defmacro >=f-for-site (&rest integers)
  `(>=f . ,integers))

(defmacro <f-for-site (&rest integers)
  `(<f . ,integers))

(defmacro >f-for-site (&rest integers)
  `(>f . ,integers))

(defmacro minf-for-site (&rest integers)
  `(minf . ,integers))

(defmacro decff-for-site (&rest integers)
  `(decf . ,integers))

(defmacro incff-for-site (&rest integers)
  `(incf . ,integers))

;; Do not bother implementing these non-generically, since they usually only run
;; on Lisp machines in practice (and so would not benefit much), and in any
;; case are not speed-critical.








;;;; Local Explorer Namespace Tools



;;; (ip-address-string (decimal-ip-address "1.0.1.41")) => "1.0.1.41"
;;; (decimal-ip-address (ip-address-string 16777513)) => 16777513

(defun ip-address-string (decimal-ip-address)
  (format nil "~d.~d.~d.~d"
          (ldb (byte 8 24) decimal-ip-address)
          (ldb (byte 8 16) decimal-ip-address)
          (ldb (byte 8 8) decimal-ip-address)
          (ldb (byte 8 0) decimal-ip-address)))

(defun decimal-ip-address (ip-address-string)
  (loop for shift from 24 downto 0 by 8
        as string-start
           = 0 then (+ string-end? 1)
        as string-end?
           = (position #\. ip-address-string :start string-start)
        as shifted-byte = (ash (parse-integer
                                 ip-address-string
                                 :start string-start
                                 :end (or string-end?
                                          (length ip-address-string)))
                               shift)
        as result-so-far
           first shifted-byte
           then (+ result-so-far shifted-byte)
        finally (return result-so-far)))



(defparameter binary-file-types nil)


(defparameter source-file-types nil)




(defun same-day-p (utc1 utc2)
  (multiple-value-bind (second-1 minute-1 hour-1
                        day-1 month-1 year-1 daylight-savings-p-1 time-zone-1)
      (decode-universal-time utc1)
    (declare (ignore second-1 minute-1 hour-1))
    (multiple-value-bind (second-2 minute-2 hour-2
                          day-2 month-2 year-2 daylight-savings-p-2 time-zone-2)
        (decode-universal-time utc2)
      (declare (ignore second-2 minute-2 hour-2))
      (and (eql day-1 day-2)
           (eql month-1 month-2)
           (eql year-1 year-2)
           (eql daylight-savings-p-1 daylight-savings-p-2)
           (eql time-zone-1 time-zone-2)))))





(defun list-non-g2-files ()
  (let ((directory-pathname "ma:>ab>*.lisp.newest"))
    (format t "~&Non-G2 Files in Directory: ~a " directory-pathname)
    (loop for file in (directory directory-pathname)
          when (not (member (normalize-name (pathname-name file))
                            (system-modules 'ab)))
            do (format t "~&~a.lisp.~d~40t"
                       (string-downcase (pathname-name file))
                       (pathname-version file))
               (write-universal-time (file-write-date file))
            and collect file into non-g2-files
          finally
            (return non-g2-files))))









(defun directory-p (pathname)
  (cerror "continue" "Can't determine directory-p on ~a." pathname)
  nil)



;;;; Search Source Debugging Facility




;;; The function `source-search' and its associated other utilities give
;;; developers a way to load all Lisp system source files into their environment
;;; and perform efficient text searches across all files.  Note that this
;;; searcher does not find strings with Return characters in them, and in fact
;;; uses the line delimiters to help speed the search.  As a result, the fastest
;;; searches are performed by giving source-search a long string.

;;; The following function returns a list of the pathnames of the AB system
;;; sources which are compiled on the machine executing the function.

(defun system-source-files (&optional (system 'ab))
  (let* ((system-name (normalize-system-name system))
         (modules (system-modules system-name)))
    (loop for module in modules
          when (include-for-compile-p
                 module 'system-lisp-source-files system-name)
            collect (make-module-filename module system-name 'source))))




;;; The following function returns a list of the pathnames of ALL of the AB
;;; system source files, regardless of whether they can be compiled on this
;;; machine or not.

(defun all-system-source-files (&optional (system 'ab))
  (let* ((system-name (normalize-system-name system))
         (modules (system-modules system-name)))
    (loop for module in modules
          collect (make-module-filename module system-name 'source))))





(defvar *source-search-environment* nil)




;;; The structure `cached-source' is used to hold data for the source search and
;;; symbol search facilities.  It has four slots, cached-source-pathname,
;;; cached-source-truename?, cached-source-write-date?, and cached-source-data.

(def-structure (cached-source
                 (:constructor
                   make-cached-source (cached-source-pathname)))
  cached-source-pathname
  (cached-source-truename? nil)
  (cached-source-write-date? nil)
  (cached-source-data nil))




;;; The function `count-lines-in-source' will return a count of the number of
;;; text lines in all of our system sources.

(defun count-lines-in-source ()
  (setup-source-search)
  (loop with line-count fixnum = 0
        for file-and-lines in *source-search-environment*
        do
    (incff line-count (length (cached-source-data file-and-lines)))
        finally
          (return line-count)))

(setf (symbol-function #-ansi-cl 'user::count-lines-in-source #+ansi-cl 'cl-user::count-lines-in-source)
      (symbol-function 'count-lines-in-source))




;;; The function `count-code-lines-in-source' returns a count of the number of
;;; text lines in the system code which do not consist of all spaces

(defun count-code-lines-in-source ()
  (setup-source-search)
  (loop with line-count fixnum = 0
        for cached-source in *source-search-environment*
        do
    (loop for line in (cached-source-data cached-source)
          do
      (loop for char-index fixnum from 0 below (length line)
            for char = (schar line char-index)
            do
        (cond ((char-equal #\;
                           char)
               (return nil))
              ((and (char-not-equal char #\space)
                    (char-not-equal char #\tab))
               (incff line-count)
               (return nil)))))
        finally
          (return line-count)))

#-ansi-cl
(setf (symbol-function 'user::count-code-lines-in-source)
      (symbol-function 'count-code-lines-in-source))




;;; The function `count-characters-in-source' returns a count of all the characters
;;; in the system source files.


(defun count-characters-in-source ()
  (setup-source-search)
  (loop with char-count fixnum = 0
        for cached-source in *source-search-environment*
        do
    (loop for line in (cached-source-data cached-source)
          do
      (incff char-count (+f (length line) 1)))
        finally
          (return char-count)))

(setf (symbol-function #-ansi-cl 'user::count-characters-in-source #+ansi-cl 'cl-user::count-characters-in-source)
      (symbol-function 'count-characters-in-source))




;;; The function `long-lines-in-source' prints a report of the number of lines
;;; within each system file that are longer than 80 characters.

(defun long-lines-in-source (&optional (line-limit 80))
  (declare (type fixnum line-limit))
  (setup-source-search)
  (format t "~%Searching for lines longer than ~a characters:~
             Lines File"
          line-limit)
  (loop for cached-source in *source-search-environment*
        for long-line-count fixnum = 0
        do
    (loop for line in (cached-source-data cached-source)
          do
      (when (>f (length line) line-limit)
        (incff long-line-count)))
    (format t "~%~5d ~a"
            long-line-count
            (cached-source-pathname cached-source))))

(setf (symbol-function #-ansi-cl 'user::long-lines-in-source #+ansi-cl 'cl-user::long-lines-in-source)
      (symbol-function 'long-lines-in-source))




;;; The function `source-file-sizes' prints the line and character count for
;;; each file in the system sources.

(defun source-file-sizes ()
  (setup-source-search)
  (loop with total-lines fixnum = 0
        with total-characters fixnum = 0
        for cached-source in *source-search-environment*
        do
    (let ((line-count 0)
          (character-count 0))
      (declare (type fixnum line-count character-count))
      (loop for line in (cached-source-data cached-source)
            do
        (incff line-count)
        (incff character-count (+f (length line) 1)))
      (incff total-lines line-count)
      (incff total-characters character-count)
      (format t "~%~a, ~a lines, ~a characters"
              (cached-source-truename? cached-source)
              line-count
              character-count))
    finally
      (format t "~%Totals, ~a lines, ~a characters."
              total-lines
              total-characters)))




;;; The macro `substring-p-for-find-files' is a string searching function which is
;;; used only in the source-search facility.  It is Common Lisp, but has
;;; optimizations for string character reference on the Symbolics.

(defmacro substring-p-for-find-files
          (sub-string sub-string-length string start)
  `(let ((decoded-sub-string ,sub-string)
         (decoded-string ,string))
     (block substring-p
       (loop for index fixnum from ,start
                       to (-f (length decoded-string) ,sub-string-length)
             do
         (loop for search-index fixnum from 0 below ,sub-string-length
               do
           (when (char-not-equal (schar decoded-string (+f index search-index))
                                 (schar decoded-sub-string search-index))
             (return nil))
               finally
                 (return-from substring-p index))))))




;;; The global variable `copy-search-results-to-editor-buffer' is a flag which
;;; determines whether the source search and symbol search commands will write a
;;; copy of their output to a Zmacs editor buffer.  It is T by default.

(defvar copy-search-results-to-editor-buffer t)




;;; The variable *source-search-area* is used on the Lisp machines to hold the area
;;; number used for the system sources.  By packing all sources into one area, we
;;; increase the locality of reference of the file strings, increasing paging
;;; performance which searching.

(defvar *source-search-area* nil)




;;; The function `source-search' takes a string and searchs the text of all Lisp
;;; source files of the current system, showing the names of those files in
;;; which it is found.  It does this by loading all Lisp sources into lists of
;;; strings, and then performing the search on those strings.  Any subsequent
;;; searches will be performed on those cached strings, making it very fast.
;;; Note that this does not handle searches on strings across line boundaries,
;;; and in fact it uses the line boundaries to speed up its search.  It takes
;;; longer to look for a short string than a long one.  On the Lisp machines, it
;;; takes a little less than a minute for a search on a short string, and under
;;; 10 seconds to search for a very long string.

;;; Source-search takes two optional arguments.  The first controls whether or
;;; not the lines in which the string is found are shown.  It defaults to NIL,
;;; not showing lines.  The second argument is available on the Lisp machines,
;;; and will force the area in which the strings are stored to be paged in as a
;;; block.  It takes less time to page this way than to just get all the strings
;;; by demand when all of it is paged out, though the difference is not that
;;; great.  Note that if all the strings are paged in (e.g.  if you just
;;; finished one search and are starting a second) it never makes sense to
;;; supply this argument.  It defaults to NIL, don't explicitly force paging.

(defvar source-search-counter 0)

(defun source-search (string &optional (show-lines nil)
                      &key (from nil) (through nil))
  (with-open-stream (editor-output
                      (if copy-search-results-to-editor-buffer
                          (open-editor-stream-or-bitsink        ; in BOOTSTRAP
                            (format nil "~a-Source-Search-~a"
                                    (if (>f (length string) 15)
                                        (concatenate
                                          'string (subseq string 0 15) "...")
                                        string)
                                    (incff source-search-counter)))
                          (make-broadcast-stream)))
    (with-open-stream (*standard-output*
                        (make-broadcast-stream *standard-output* editor-output))
      (let ((found-files nil)
            (string-length (length string))
            (total-occurances 0))
        (declare (type fixnum string-length total-occurances))
        (setup-source-search)
        (format t "~%Searching for ~S in system AB...~%" string)
        (loop with occurances fixnum = 0
              for cached-source in
                  (if (null from)
                      *source-search-environment*
                      (loop with from-name = (symbol-name from)
                            for cached-source-cons on
                                *source-search-environment*
                            do
                        (when (string-equal
                                from-name
                                (pathname-name
                                  (cached-source-pathname
                                    (car-of-cons cached-source-cons))))
                          (return cached-source-cons))))
              for source-pathname = (cached-source-pathname cached-source)
              do
          (write-string ".")
          (loop with shown-file-name = nil
                for line in (cached-source-data cached-source)
                for sub-index? = 0
                for shown-line = nil
                do
            (loop while (setq sub-index?
                              (substring-p-for-find-files
                                string string-length line sub-index?))
                  do
              (incff occurances)
              (incff sub-index? string-length)
              (when (and show-lines (not shown-file-name))
                (format t "~%~%Occurances in ~a:" source-pathname)
                (setq shown-file-name t))
              (when (and show-lines (not shown-line))
                (format t "~%~A" line)
                (setq shown-line t))))
          (unless (=f occurances 0)
            (format t "~%Found in ~A ~A times" source-pathname occurances)
            (push source-pathname found-files)
            (incff total-occurances occurances)
            (setq occurances 0))
              until (and through (string-equal
                                   (symbol-name through)
                                   (pathname-name source-pathname))))
        (format t "~%~a total occurances." total-occurances)
        (reverse found-files)))))

(setf (symbol-function #-ansi-cl 'user::source-search #+ansi-cl 'cl-user::source-search)
      (symbol-function 'source-search))




;;; The function `clear-source-search' clears the cached source searching
;;; environment, forcing any subsequent search to go out and get the new system
;;; sources all over again.

(defun clear-source-search ()
  (setq *source-search-environment* nil))

(setf (symbol-function #-ansi-cl 'user::clear-source-search #+ansi-cl 'cl-user::clear-source-search)
      (symbol-function 'clear-source-search))




;;; The function `setup-source-search' checks if there is already a cached
;;; source searching environment, and if not, will load it.  On the Lisp
;;; machines, this code will load the environment into its own area, thereby
;;; increasing locality of data in the environment, and it will force cdr-coding
;;; on the lists of file lines, increasing the speed of traversing through the
;;; file and cutting in half the amount of memory required to store those lists.

(defun setup-source-search ()
  (when (null *source-search-environment*)

      (let* ((files (copy-list (all-system-source-files))))
        (format t "~%Setting up search environment, one moment please...")
        (loop for file-cons on files
              do
          (setf (car file-cons) (make-cached-source (car-of-cons file-cons))))
        (setq *source-search-environment* files)
        (update-source-search nil))))

(setf (symbol-function #-ansi-cl 'user::setup-source-search #+ansi-cl 'cl-user::setup-source-search)
      (symbol-function 'setup-source-search))

(defun set-up-source-search () (setup-source-search))

(setf (symbol-function #-ansi-cl 'user::set-up-source-search #+ansi-cl 'cl-user::set-up-source-search)
      (symbol-function 'set-up-source-search))

(defun directory-of-lisp-sources ()
  (declare (special current-system-name))     ; not always loaded (MHD 6/29/90)
  (directory (make-system-pathname
               (or (and (boundp 'current-system-name)
                        current-system-name)
                   'ab)
               :wild
               "lisp"
               :newest)))

(defun file-not-up-to-date-p (file truename? directory-list)
  (or (null truename?)
      (if (use-dates-instead-of-versions-p)
          (> (file-write-date file) (file-write-date truename?))
          (let ((truename-version (pathname-version truename?))
                (actual-version
                  (pathname-version
                    (find-file-with-same-name-in-directory
                      file directory-list))))
            (> actual-version truename-version)))))

(defun cached-source-not-up-to-date-p (cached-source directory-list?)
  (or (null (cached-source-truename? cached-source))
      (if (use-dates-instead-of-versions-p)
          (let ((current-write-date?
                  (file-write-date (cached-source-pathname cached-source)))
                (previous-write-date? (cached-source-write-date?
                                        cached-source)))
            (and current-write-date?
                 (or (null previous-write-date?)
                     ;; Beware of bignum times, can't use >f.
                     (> current-write-date? previous-write-date?))))
          (let ((truename-version
                  (pathname-version (cached-source-truename? cached-source)))
                (actual-version
                  (pathname-version
                    (find-file-with-same-name-in-directory
                      (cached-source-pathname cached-source) directory-list?))))
            (> actual-version truename-version)))))

(defun-allowing-unwind update-source-search (&optional (report? t))
  (if (null *source-search-environment*)
      (setup-source-search)
      (catch :abort

          (let* ((directory (if (not (use-dates-instead-of-versions-p))
                                (directory-of-lisp-sources))))
            (if report?
                (format t "~%Updating source search environment..."))
            (loop for cached-source in *source-search-environment*
                  for file = (cached-source-pathname cached-source)
                  for truename? = (cached-source-truename? cached-source)
                  for char = (read-char-no-hang)        ; allow aborts to occur
                  do
              (when (and char (char-equal char char-control-a))
                (format t "~%Aborting...")
                (throw :abort nil))
              (when (cached-source-not-up-to-date-p cached-source directory)
                (if report? (format t "~%Reading ~a..." file))
                (multiple-value-bind (forms-in-file new-truename write-date)
                    (read-lines-and-truename file)
                  (setf (cached-source-data cached-source) forms-in-file)
                  (setf (cached-source-truename? cached-source)
                        new-truename)
                  (setf (cached-source-write-date? cached-source)
                        write-date)))))))
  nil)

(setf (symbol-function #-ansi-cl 'user::update-source-search #+ansi-cl 'cl-user::update-source-search)
      (symbol-function 'update-source-search))

(defun read-lines-and-truename (file)
  (with-open-file (input file)
    (let* ((first-line-cons (cons nil nil)))
      (setf (car first-line-cons) (read-line input nil :eof))
      (if (eq :eof (car first-line-cons))
          (values nil (truename input) (file-write-date input))
          (progn
            (loop with last-lines-cons = first-line-cons
                  for line = (read-line input nil :eof)
                  for char = (read-char-no-hang)
                  until (eq line :eof)
                  do
              (when (and char (char-equal char char-control-a))
                (throw :abort nil))
              (setf (cdr last-lines-cons)
                    (cons line nil))
              (setf last-lines-cons (cdr last-lines-cons)))
            (values
              first-line-cons (truename input) (file-write-date input)))))))



;;;; Symbol Search


;;; The symbol search environment is like source search, except that it
;;; manipulates Lisp forms from the source files instead of text strings.  The
;;; functions which are available in this suite are `symbol-search' which finds
;;; the files and forms containing a given symbol, `setup-symbol-search' which
;;; loads all system source in as Lisp forms, `clear-symbol-search' which clears
;;; any currently loaded forms, and `count-forms-in-source' which returns a
;;; count of all the forms in the system source.

(defvar *symbol-search-environment* nil)

(defvar *symbol-search-area* nil)

(defun symbol-in-form-p (atom form)
  (loop until (atom form)
        for current-car = (car-of-cons form)
        do
    (if (if (atom current-car)
            (eq current-car atom)
            (symbol-in-form-p atom current-car))
        (return t)
        (setq form (cdr-of-cons form)))
        finally
          (if (eq atom form) (return t))))

(defvar symbol-search-counter 0)

(defvar current-module-name)




;;; `symbol-search' will scan all source S-Expressions in G2 modules.  These are
;;; loaded by reading the source files.  This does not include S-Expressions
;;; that read time conditionalization comments out.

;;; The first argument is the symbol to search for.  The second argument,
;;; show-form?, takes on one of three values, NIL, T, or ALL.  ALL will cause it
;;; to show the entire top level form.  I don't know what the fourth argument
;;; FORCE-PAGING?  does.  Keyword arguments for from and through.

(defun-allowing-unwind symbol-search (symbol &optional
                                             (show-form? nil)
                                             &key (from nil) (through nil))
  (catch :abort
    (with-open-stream (editor-output
                        (if copy-search-results-to-editor-buffer
                            (open-editor-stream-or-bitsink
                              (format nil "~a-Symbol-Search-~a"
                                      (if (>f (length (symbol-name symbol)) 15)
                                          (concatenate
                                            'string
                                            (subseq (symbol-name symbol) 0 15)
                                            "...")
                                          symbol)
                                      (incf symbol-search-counter)))
                            (make-broadcast-stream)))
      (with-open-stream (*standard-output*
                          (make-broadcast-stream *standard-output* editor-output))
        (let* ((found-files nil)
               (all? (and (symbolp show-form?)
                          (string-equal "ALL" (symbol-name show-form?))))
               (*print-length* (if all? 1000 4))
               (*print-level* (if all? 1000 2))
               (*print-pretty* (if all? T nil))
               (*print-case* :downcase)
               (cantidate-modules-for-symbol
                 (cantidate-modules-for-symbol symbol))
               (total-occurances 0))
          (if (not (symbolp symbol))
              (progn (format t "~%~a is not a symbol." symbol)
                     (return-from symbol-search nil)))
          (setup-symbol-search)
          (format t "~%Searching for the symbol ~S in system AB...~%" symbol)
          (loop with occurances = 0
                for cached-source in
                    (if (null from)
                        *symbol-search-environment*
                        (loop with from-name = (symbol-name from)
                              for cached-source-cons on
                                  *symbol-search-environment*
                              do
                          (if (string-equal
                                from-name
                                (pathname-name
                                  (cached-source-pathname
                                    (car-of-cons cached-source-cons))))
                              (return cached-source-cons))))
                for source-pathname = (cached-source-pathname cached-source)
                as module-index from 0
                do
            (cond
              ((not (or (eq t cantidate-modules-for-symbol)
                        (logbitp module-index cantidate-modules-for-symbol)))
               (write-char #\.))
              (t
               (write-char #\,)
               (loop with shown-file-name = nil
                     for form in (cached-source-data cached-source)
                     do
                 (when (symbol-in-form-p symbol form)
                   (incff occurances)
                   (when show-form?
                     (when (not shown-file-name)
                       (format t "~%~%; Occurances in ~a:" source-pathname)
                       (setq shown-file-name t))
                     (if (eq show-form? 'all)
                         (format t "~2%~S" (copy-tree form))
                         (format t "~%~S" (copy-tree form))))))
               ;; The presentation manager software on the Symbolics retains pointers
               ;; to printed data structures.  In order to control access to the
               ;; internal forms, a copy-tree of the printed form is made first.

               (when (not (=f occurances 0))
                 (format t "~%; Found in ~A in ~A forms"
                         source-pathname
                         occurances)
                 (push source-pathname found-files)
                 (setq total-occurances (+f total-occurances occurances))
                 (setq occurances 0))))
                until (and through
                           (string-equal (symbol-name through)
                                         (pathname-name source-pathname))))
          (format t "~%; Found in ~a total forms." total-occurances)
          (reverse found-files))))))

(setf (symbol-function #-ansi-cl 'user::symbol-search #+ansi-cl 'cl-user::symbol-search)
      (symbol-function 'symbol-search))

(defvar found-forms nil) ; set as a side effect of symbol-search of form-search
(defvar top-level-found-forms nil) ; Ditto

(defun occurances-in-form (atom form)
  (loop with total fixnum = 0
        for form-so-far = form then (cdr-of-cons form-so-far)
        do
    (cond ((consp form-so-far)
           (let ((car-of-form (car-of-cons form-so-far)))
             (cond ((consp car-of-form)
                    (incff total (occurances-in-form atom car-of-form)))
                   ((eq car-of-form atom)
                    (incff total)))))
          (t
           (when (eq atom form-so-far)
             (incff total))
           (return total)))))

(defvar current-form-search-test? nil)

(defun pattern-matches-form-p (pattern-form form)
  (let ((result (pattern-matches-form-p-1 pattern-form form)))
    (when (and result
               current-form-search-test?)
      (setf result (funcall current-form-search-test? form)))
    (when result
      (push form found-forms))
    result))

(defun pattern-matches-form-p-1 (pattern-form form)
  (typecase pattern-form
    (string
     (when (stringp form)
       (string-equal pattern-form form)))
    (atom
      (or (eql pattern-form form)
          (eq pattern-form '*)
          (eq pattern-form #-ansi-cl 'user::* #+ansi-cl 'cl-user::*)))
    (cons
      (and
           (loop until (or (atom pattern-form) (atom form))
                 for pattern-car = (car pattern-form)
                 for form-car = (car form)
                 do
             (when (not (if (atom pattern-car)
                            (or (eql pattern-car form-car)
                                (eq pattern-car '*)
                                (eq pattern-car #-ansi-cl 'user::* #+ansi-cl 'cl-user::*))
                            (pattern-matches-form-p-1
                              pattern-car form-car)))
               (return nil))
             (setq pattern-form (cdr pattern-form))
             (setq form (cdr form))
                 finally
                   (return
                     (and (atom pattern-form)
                          (or (eql pattern-form form)
                              (eq pattern-form '*)
                              (eq pattern-form #-ansi-cl 'user::* #+ansi-cl 'cl-user::*)))))))))

(defun pattern-in-form-p (pattern-form form)
  (or (pattern-matches-form-p pattern-form form)
      (and (consp form)
           (loop until (atom form)
                 do
             (when (pattern-in-form-p pattern-form (car form))
               (return t))
             (setq form (cdr form))
                 finally
                   (return (and (atom pattern-form)
                                (pattern-matches-form-p pattern-form form)))))))

(defvar form-search-counter 1)




;;; The function `form-search' does searches across the symbol-search
;;; environment much like symbol-search, except forms and form patterns with
;;; wildcards can be given as the search key, rather than just symbols.  So, if
;;; you wanted to find all occurances of calls to + where there were two
;;; arguments, you would type "(form-search '(+ * *))".  If you wanted to find
;;; all occurances of calls to + with any number of arguments, you would type
;;; "(form-search '(+ . *))".  Form-search prints its results and returns a list
;;; of the files in which the pattern was found.


(defun predicate-search (predicate-function
                         &optional
                         (show-form? nil)
                         (top-level-forms-only nil)
                         (from-module nil)
                         (thru-module nil))
  (let ((*print-length* 4)
        (*print-level* 2)
        (*print-pretty* nil)
        (*print-case* :downcase))
    (loop with ab-package = (find-package "AB")
          with enabled = (not from-module)
          for cached-source in *symbol-search-environment*
          for source-pathname = (cached-source-pathname cached-source)
          for current-module-name =
              (intern (pathname-name source-pathname) ab-package)
          for any-found? = nil
          do
      (write-char #\.)
      (when (and (not enabled)
                 (eq current-module-name from-module))
        (setq enabled t))
      (when enabled
        (loop for form in (cached-source-data cached-source)
              do
          (when (if top-level-forms-only
                    (funcall predicate-function form)
                    (predicate-search-form form predicate-function show-form?))
            (setq any-found? t)
            (when show-form?
              (format t "~%~%Above matches found in the following form.~%~s"
                      form)))))
      (when (and enabled
                 (eq current-module-name thru-module))
        (setq enabled nil))
      (when any-found?
        (format t "~%~%; Above matches in file ~a.~%"
                (cached-source-truename? cached-source))))))

(defun predicate-search-form (form predicate-function show-form?)
  (let ((found? nil))
    (when (funcall predicate-function form)
      (setq found? t)
      (when show-form?
        (format t "~%~%Predicate matched the following.~%~%~s"
                form)))
    (when (consp form)
      (loop while (consp form) do
        (setq found?
              (or (predicate-search-form
                    (car form) predicate-function show-form?)
                  found?))
        (setq form (cdr form)))
      (setq found?
            (or (predicate-search-form
                  form predicate-function show-form?)
                found?)))
    found?))

(defun-allowing-unwind form-search (pattern-form
                                     &optional
                                     (show-form? nil)
                                     &key
                                     test)
  (let ((current-form-search-test? test)
        (cantidate-modules-for-form-search
          (loop with symbols-in-pattern
                  = (let ((result ()))
                      (nsubst nil nil pattern-form
                              :test
                              #'(lambda (subform1 subform2)
                                  (let ((form (or subform1 subform2)))
                                    (when (and form
                                               (symbolp form)
                                               (not (eq '* form)))
                                      (pushnew form result))
                                    nil)))
                      result)
                with result = t
                for symbol in symbols-in-pattern
                for cantidate-modules-for-this-symbol = (cantidate-modules-for-symbol symbol)
                do
            (cond
              ((eq t result)
               (setq result cantidate-modules-for-this-symbol))
              ((eq t cantidate-modules-for-this-symbol)
               (setq result result))
              (t
               (setq result (logand result cantidate-modules-for-this-symbol))))
                finally (return result))))
    (with-open-stream (editor-output
                        (if copy-search-results-to-editor-buffer
                            (open-editor-stream-or-bitsink
                              (let ((name (format nil "~a" pattern-form)))
                                (format nil "~a-Form-Search-~a"
                                        (if (>f (length name) 15)
                                            (concatenate
                                              'string
                                              (subseq name 0 15)
                                              "...")
                                            name)
                                        (incf form-search-counter))))
                            (make-broadcast-stream)))
      (with-open-stream (*standard-output*
                          (make-broadcast-stream *standard-output* editor-output))
        (catch :abort
          (let* ((found-files nil)
                 (all? (and (symbolp show-form?)
                            (string-equal "ALL" (symbol-name show-form?))))
                 (*print-length* (if all? 1000 4))
                 (*print-level* (if all? 1000 2))
                 (*print-pretty* (if all? T nil))
                 (*print-case* :downcase)
                 (total-occurances 0))
            (setq found-forms nil)
            (setq top-level-found-forms nil)
            (setup-symbol-search)
            (format t "~%; Searching for the form ~S in system AB...~%; " pattern-form)
            (loop with occurances = 0
                  for cached-source in *symbol-search-environment*
                  for source-pathname = (cached-source-pathname cached-source)
                  as module-index from 0
                  for char = (read-char-no-hang)
                  do
              (when (and char (char-equal char char-control-a))
                (throw :abort found-files))

              (cond
                ((not (or (eq t cantidate-modules-for-form-search)
                          (logbitp module-index cantidate-modules-for-form-search)))
                 (write-char #\.))
                (t
                 (write-char #\,)
                 (loop with shown-file-name = nil
                       for form in (cached-source-data cached-source)
                       do

                   (when (pattern-in-form-p pattern-form form)
                     (incff occurances)
                     (push form top-level-found-forms)
                     (when show-form?
                       (when (not shown-file-name)
                         (format t "~%~%; Occurances in ~a:" source-pathname)
                         (setq shown-file-name t))
                       (if (eq show-form? 'all)
                           (format t "~2%~S" (copy-tree form))
                           (format t "~%~S" (copy-tree form))))))

                 (when (not (=f occurances 0))
                   (format t "~%; Found in ~A in ~A forms"
                           source-pathname
                           occurances)
                   (push source-pathname found-files)
                   (incff total-occurances occurances)
                   (setq occurances 0)))))
            (format t "~%; Found in ~a total forms." total-occurances)
            (reverse found-files)))))))

(setf (symbol-function #-ansi-cl 'user::form-search #+ansi-cl 'cl-user::form-search)
      (symbol-function 'form-search))

(defun form-search-walk (pattern-form &optional (show-form? nil))
  (with-open-stream (editor-output
                      (if copy-search-results-to-editor-buffer
                          (open-editor-stream-or-bitsink
                            (let ((name (format nil "~a" pattern-form)))
                              (format nil "~a-Form-Search-~a"
                                      (if (>f (length name) 15)
                                          (concatenate
                                            'string
                                            (subseq name 0 15)
                                            "...")
                                          name)
                                      (incf form-search-counter))))
                          (make-broadcast-stream)))
    (with-open-stream (*standard-output*
                        (make-broadcast-stream *standard-output* editor-output))
      (let ((found-files nil)
            (*print-length* 4)
            (*print-level* 2)
            (total-occurances 0))
        (setq found-forms nil)
        (setq top-level-found-forms nil)
        (setup-symbol-search)
        (format t "~%Searching for the form ~S in system AB...~%; " pattern-form)
        (loop with occurances = 0
              for cached-source in *symbol-search-environment*
              for file = (cached-source-pathname cached-source)
              do
          (write-string ".")

          (loop with shown-file-name = nil
                for raw-form in (cached-source-data cached-source)
                for form = (safe-walk-form raw-form file)
                do
            (when (pattern-in-form-p pattern-form form)
              (incff occurances)
              (push form top-level-found-forms)
              (when show-form?
                (when (not shown-file-name)
                  (format t "~%~%Occurances in ~a:" file)
                  (setq shown-file-name t))
                (format t "~%~a" form))))

          (when (not (= occurances 0))
            (format t "~%Found in ~A in ~A forms" file occurances)
            (push file found-files)
            (incff total-occurances occurances)
            (setq occurances 0)))
        (format t "~%Found in ~a total forms." total-occurances)
        (reverse found-files)))))

(defun safe-walk-form (form safe-walk-form-file)
  (declare (special safe-walk-form-file))
  (walk-form form))

(defun walk-form (form)
  (declare (ignore form))
  (error "Cannot walk given form, walk-form not implemented."))


(defun count-forms-in-source ()
  (setup-symbol-search)
  (loop with form-count fixnum = 0
        for cached-source in *symbol-search-environment*
        do
    (incff form-count (length (cached-source-data cached-source)))
        finally
          (return form-count)))

(setf (symbol-function #-ansi-cl 'user::count-forms-in-source #+ansi-cl 'cl-user::count-forms-in-source)
      (symbol-function 'count-forms-in-source))

(defun clear-symbol-search ()
  (setq *symbol-search-environment* nil))

(setf (symbol-function #-ansi-cl 'user::clear-symbol-search #+ansi-cl 'cl-user::clear-symbol-search)
      (symbol-function 'clear-symbol-search))



;;; `Setup-inverted-index-for-symbol-search' creates a 5K element array
;;; that maps from sxhash values (mod 5000) to modules that contain symbols
;;; with that hash hash value.  `Symbol-search-inverted-index-noise-words'
;;; is a list of symbols that are not entered in the table.  This allows
;;; symbol-search, and friends to skip a lot of modules on many searchs.

(defparameter symbol-search-inverted-index-noise-words
  '(nil t
        car cdr cddr first second third
        in-package
        defvar defun defmacro
        eval-when compile eval load
        let let* progn prog1
        loop with for in on from to downto below then as do until while nconc collect using finally return thereis
        quote function declare ignore
        if when unless cond case funcall #-ansi-cl lisp:funcall #+ansi-cl cl:funcall
        setf setq
        &rest &body &optional body
        list list* append
        and or not eq = null memq stringp symbolp
        >f =f -f +f <f + >=f

        values
        length format tformat
        class variable symbol string index block i type value fixnum        ; variable names probably
        declare-forward-reference def-substitution-macro def-system-variable
        multiple-value-setq multiple-value-bind
        cerror error

        ;;                                       # of modules
        consp                                        ;   91
        reclaim-text-string                        ;   77
        defparameter                                ;   75
        assq                                        ;   68
        with-temporary-gensym-float-creation        ;   66
        incff                                        ;   65
        system                                        ;   65
        -                                        ;   65
        text                                        ;   64
        x                                        ;   64
        of                                        ;   63
        eql                                        ;   63
        atom                                        ;   63
        gensym                                        ;   63
        twrite-string                                ;   62
        the                                        ;   62
        name                                        ;   62
        initially                                ;   61
        twith-output-to-text-string                ;   60
        <=f                                        ;   60
        item                                        ;   60

        ))

(defvar symbol-search-inverted-index-mask 0)

(defparameter symbol-search-inverted-index (make-array 5000 :initial-element 0))

;;; `Inverted-index-for-symbol-search-up-to-date-p' is set to nil
;;; when ever the symbol search data base is changed.  It is set
;;; to true when ever setup-inverted-index-for-symbol-search completes.
;;; When NIL symbol and form search behave as if there were no
;;; inverted index, that happens via cantidate-modules-for-symbol.

(defparameter inverted-index-for-symbol-search-up-to-date-p nil)


;;; `Setup-inverted-index-for-symbol-search' is responsible for
;;; filling out the symbol-search-inverted-index from the current
;;; *symbol-search-environment*.

(defun setup-inverted-index-for-symbol-search ()
  (format t "~%Updating inverted index for symbol search.")
  (setq inverted-index-for-symbol-search-up-to-date-p nil)
  (loop with total-module-count = (length *symbol-search-environment*)
        initially
          (setf symbol-search-inverted-index-mask 0)
          (setf (ldb (byte 1 (1+ total-module-count))
                     symbol-search-inverted-index-mask)
                1)
        for i from 0 below 5000 do
    (setf (svref symbol-search-inverted-index i) symbol-search-inverted-index-mask))
  (progn
    (loop with ab-package = (find-package "AB")
          for cached-source in *symbol-search-environment*
          as source-pathname = (cached-source-pathname cached-source)
          as current-module-name = (intern (pathname-name source-pathname) ab-package)
          as module-index from 0
          do
      (loop for form in (cached-source-data cached-source)
            do
        (nsubst nil nil form
                :test
                #'(lambda (subform1 subform2)
                    (let ((subform (or subform1 subform2)))
                      (when (and subform
                                 (symbolp subform)
                                 (not (memq subform
                                            symbol-search-inverted-index-noise-words)))
                        (let ((index (mod (sxhash subform) 5000)))
                          (setf (ldb (byte 1 module-index)
                                     (svref symbol-search-inverted-index index))
                                1))))
                    nil)))))
  (setq inverted-index-for-symbol-search-up-to-date-p t))




;;; `Cantidate-modules-for-symbol' returns a bignum or t.  The bignum will have
;;; bits set to T for each module that might contain that symbol, i.e.  (logbitp
;;; module-index (cantidate-modules-for-sybmol X)).  It returns T if the symbol
;;; is so common that searching all modules is approprate, or if the inverted
;;; index isn't uptodate.

(defun cantidate-modules-for-symbol (symbol)
  (if (or (not inverted-index-for-symbol-search-up-to-date-p)
          (memq symbol
                symbol-search-inverted-index-noise-words))
     t
     (let ((index (mod
                    (sxhash symbol)
                    5000)))
       (svref symbol-search-inverted-index index))))



(defun setup-symbol-search ()
  (when (null *symbol-search-environment*)

      (let* ((files (system-source-files)))
        (format t "~%Setting up symbol search environment, one moment please...")
        (loop for file-cons on files
              do
          (setf (car file-cons) (make-cached-source (car file-cons))))
        (setq *symbol-search-environment* files)
        (update-symbol-search nil))))


(setf (symbol-function #-ansi-cl 'user::setup-symbol-search
		       #+ansi-cl 'cl-user::setup-symbol-search)
      (symbol-function 'setup-symbol-search))

(setf (symbol-function 'set-up-symbol-search)
      (symbol-function 'setup-symbol-search))

(setf (symbol-function #-ansi-cl 'user::set-up-symbol-search
		       #+ansi-cl 'cl-user::set-up-symbol-search)
      (symbol-function 'setup-symbol-search))

(defun-allowing-unwind update-symbol-search (&optional (report? t))
  (if (null *symbol-search-environment*)
      (setup-symbol-search)
      (let ((*package* (find-package "AB")))
        (setq inverted-index-for-symbol-search-up-to-date-p nil)

          (catch :abort
            (if report? (format t "~%Updating symbol search, one moment please..."))
            (let* ((directory (if (not (use-dates-instead-of-versions-p))
                                  (directory-of-lisp-sources))))
              (loop for cached-source in *symbol-search-environment*
                    for file = (cached-source-pathname cached-source)
                    for truename? = (cached-source-truename? cached-source)
                    do
                (when (cached-source-not-up-to-date-p cached-source directory)
                  (if report? (format t "~%Reading ~a..." file))
                  (multiple-value-bind (forms new-truename write-date)
                      (read-forms-and-truename file)
                    (setf (cached-source-data cached-source) forms)
                    (setf (cached-source-truename? cached-source) new-truename)
                    (setf (cached-source-write-date? cached-source)
                          write-date)))))
            (setup-inverted-index-for-symbol-search))))
  nil)


(setf (symbol-function #-ansi-cl 'user::update-symbol-search
		       #+ansi-cl 'cl-user::update-symbol-search)
      (symbol-function 'update-symbol-search))


(defmacro read-without-bombout (stream eof-object)
  `(read ,stream nil ,eof-object))



(defun read-forms-and-truename (file)
  (with-open-file (input file)
    (let* ((truename (truename input))
           (first-form-cons (cons nil nil))
           (eof-object (cons nil nil)))
      (setf (car first-form-cons) (read-without-bombout input eof-object))
      (if (eq (car first-form-cons) eof-object)
          (values nil truename (file-write-date input))
          (progn
            (loop with last-form-cons = first-form-cons
                  for form = (read-without-bombout input eof-object)
                  for char = (read-char-no-hang)        ; Allow aborts to occur
                  until (eq form eof-object)
                  do
              (when (and char (char-equal char char-control-a))
                (throw :abort nil))
              (setf (cdr last-form-cons)
                    (cons form nil))
              (setf last-form-cons (cdr last-form-cons)))
            (values first-form-cons truename (file-write-date input)))))))





;;; A definition is found by basically the same rules as the Zmacs meta-.
;;; command.  A definition is any top-level form having in functional position a
;;; symbol whose name begins def.  The exceptions are def-evaluator
;;; and def-simulation-evaluator, so that operations like '- or 'and are not
;;; included, and defvar.

(defun find-definition (symbol)
  (loop named top
        for cached-source in *symbol-search-environment*
        do
    (loop for form in (cached-source-data cached-source)
          as functional-position-symbol = nil
          do
      (when (consp form)
        (setq functional-position-symbol (car form))
        (when (and (symbolp functional-position-symbol)
                   (symbol-implies-definition-p functional-position-symbol)
                   (eq symbol (second form)))
          (return-from top form))))))

(defun symbol-implies-definition-p (symbol)
  (let ((name-string (symbol-name symbol)))
    (and (>=f-for-site (length name-string) 3)
         (not (member symbol '(def-simulation-evaluator
                                def-evaluator defvar)))
         (or (eql (aref name-string 0) #\d)
             (eql (aref name-string 0) #\D))
         (or (eql (aref name-string 1) #\e)
             (eql (aref name-string 1) #\E))
         (or (eql (aref name-string 2) #\f)
             (eql (aref name-string 2) #\F)))))

(defun set-forms-in-form (form)
  (when (consp form)
    (if (form-implies-set-form-p form)
        (format t "~%~a" form))
    (loop for sub-form in form
          do (set-forms-in-form sub-form))))

(defun symbol-implies-set-form-p (symbol)
  (let ((name-string (symbol-name symbol)))
    (and (>= (length name-string) 3)
         (or (eql (aref name-string 0) #\s)
             (eql (aref name-string 0) #\S))
         (or (eql (aref name-string 1) #\e)
             (eql (aref name-string 1) #\E))
         (or (eql (aref name-string 2) #\t)
             (eql (aref name-string 2) #\T)))))

(defun form-implies-set-form-p (form)
  (let ((operator? (car form))
        (quoted-wrapper-operator? (second form)))
    (or (and (symbolp operator?)
             (symbol-implies-set-form-p operator?))
        (and quoted-wrapper-operator?
             (consp quoted-wrapper-operator?)
             (eq (car quoted-wrapper-operator?) 'quote)
             (symbol-implies-set-form-p
               (second quoted-wrapper-operator?))))))


(defvar set-form-search-counter 0)

(defun set-form-search (definition-symbol &optional
                        (search-only-within-temporary-wrappers? nil))
  (cond
    ((not (symbolp definition-symbol))
     (format t "~%~a is not a symbol." definition-symbol))
    (t
     (with-open-stream (editor-output
                         (if copy-search-results-to-editor-buffer
                             (open-editor-stream-or-bitsink
                               (format nil "~a-Set-Form-Search-~a"
                                       (if (>f (length
                                                 (symbol-name definition-symbol)) 15)
                                           (concatenate
                                             'string
                                             (subseq
                                               (symbol-name definition-symbol) 0 15)
                                             "...")
                                           definition-symbol)
                                       (incf set-form-search-counter)))
                             (make-broadcast-stream)))
       (with-open-stream (*standard-output*
                           (make-broadcast-stream *standard-output* editor-output))
         (setup-symbol-search)
         (let ((definition-form
                 (find-definition definition-symbol)))
           (cond
             ((null definition-form)
              (format t "No definition for ~%~a exists." definition-symbol))
             (t
              (format t "~%Searching for set forms in the body of ~%~a ~%"
                      definition-symbol)
              (if search-only-within-temporary-wrappers?
                  (loop for with-temporary-form
                            in (find-with-temporary-forms definition-form)
                        do
                    (format t "~%~%--Within temporary wrapper ~a ~%"
                            (car with-temporary-form))
                    (set-forms-in-form with-temporary-form))
                  (set-forms-in-form definition-form))))))))))

(defun find-with-temporary-forms (form)
  (when (consp form)
    (let ((with-temporary-forms nil))
      (if (form-implies-with-temporary-form-p form)
          (setq with-temporary-forms (list form)))
      (loop as rest-of-form
               = form
               then (cdr rest-of-form)
            until (not (consp rest-of-form))
            as sub-form = (car rest-of-form)
            do (setq with-temporary-forms
                     (nconc with-temporary-forms
                            (find-with-temporary-forms sub-form))))
      with-temporary-forms)))

(defun symbol-implies-with-temporary-form-p (symbol)
  (member symbol '(with-temporary-gensym-float-creation
                    with-temporary-bignum-creation)))

(defun form-implies-with-temporary-form-p (form)
  (let ((operator? (car form))
        (quoted-wrapper-operator? (second form)))
    (or (and (symbolp operator?)
             (symbol-implies-with-temporary-form-p operator?))
        (and quoted-wrapper-operator?
             (consp quoted-wrapper-operator?)
             (eq (car quoted-wrapper-operator?) 'quote)
             (symbol-implies-with-temporary-form-p
               (second quoted-wrapper-operator?))))))



;;;; Walked-Search




;;; The walked-search facility is like symbol-search, except that the lists of
;;; forms in the system have been macroexpanded using the walk-form facility of
;;; the WALK module.  This gives us a set of forms which have been macroexpanded
;;; into all of the actual functions that will be produced.

(defvar *walked-search-environment* nil)

(defvar *walked-search-area* nil)

(defun setup-walked-search (&optional (report? nil))
  (when (null *walked-search-environment*)
    (setup-symbol-search)
    (format t "~%Setting up walked search environment, one moment please...")
    (setq *walked-search-environment*
          (loop for cached-source in *symbol-search-environment*
                collect
                (make-cached-source
                  (cached-source-pathname cached-source))))
    (update-walked-search report?)))

(defun update-walked-search (&optional (report? t))
  (if (null *walked-search-environment*)
      (setup-walked-search t)
      (loop for cached-source in *walked-search-environment*
            for symbol-cached-source in *symbol-search-environment*
            initially
              (when report?
                (format t "~%Updating walked search, one moment please..."))
            do
        (when (not (equal (cached-source-pathname cached-source)
                          (cached-source-pathname symbol-cached-source)))
          (error
            "The entries in symbol-search and walked search are out of ~
             sync at ~a and ~a.  This facility cannot ~
             yet handle added or removed modules in the file list."
            (cached-source-pathname cached-source)
            (cached-source-pathname symbol-cached-source)))
        (when (or (not (equal (cached-source-truename? cached-source)
                              (cached-source-truename? symbol-cached-source)))
                  (not (eql (cached-source-write-date? cached-source)
                            (cached-source-write-date? symbol-cached-source))))
          (when report?
            (format t "~%Walking ~a." (cached-source-pathname cached-source)))
          (setf (cached-source-data cached-source)
                (walk-and-cdr-code-list-of-forms
                  (cached-source-data symbol-cached-source)))
          (setf (cached-source-truename? cached-source)
                (cached-source-truename? symbol-cached-source))
          (setf (cached-source-write-date? cached-source)
                (cached-source-write-date? symbol-cached-source))))))

(defvar dont-expand-macros nil)

(defun walk-and-cdr-code-list-of-forms (forms-list)
  (let ((walked-forms
          (let ((dont-expand-macros t))
            (loop for form in forms-list
                  collect (walk-form form)))))
    (copy-tree walked-forms)))







;;;; GREP (Get REgular exPression)




;;; The following functions implement a text search facility like GREP on the UNIX
;;; machines.  Note that this facility has been highly optimized for Lisp
;;; machines, but is rather inefficient on other architectures.  This is a
;;; development only facility.




;;; The function `copy-grep-simple-string' takes a string and copies it into a
;;; string which is known to be a simple-string.

(defun copy-grep-simple-string (string)
  (let* ((length (length string))
         (new-string (make-string length)))
    (loop for index from 0 below length do
      (setf (schar new-string index) (char string index)))
    new-string))




;;; The function `report-grep' takes a grep file search entry from a completed
;;; search and writes to *standard-output* a brief summary of the results of the
;;; search.

(defun report-grep (entry)
  (let ((file (car entry))
        (occurances (second entry)))
    (if (> occurances 0)
        (format t "~%Found ~a times in ~a" occurances file)
        (write-char #\.))))



(defun open-into-car (entry file)
  (when (eq (second entry) file)
    (let ((new-stream nil))
      (unwind-protect-for-development open-into-car
          (progn
            (setq new-stream (open file))
            (as-atomic-operation
              (when (eq (second entry) file)
                (setf (car entry) new-stream)
                (setq new-stream nil))))
        (when new-stream
          (close new-stream :abort t))))))




;;; The function `GREP' takes a string and a specification of files to search.
;;; It searches the files for the string and prints a report of the files it
;;; was found in and the number of times it was found to *standard-output*.  The
;;; file specification should either be a symbol naming a G2 system, or
;;; something acceptable to the pathname function which specifies a file or set
;;; of files to search.  The file specification defaults to the symbol AB.

(defun grep (string &optional (system-name-or-pathname 'ab))

    (let* ((cached-string (copy-grep-simple-string string))
           (entry (list nil nil nil nil))
           (start-time (get-internal-real-time))
           (total-bytes 0))
      (loop for file in (if (symbolp system-name-or-pathname)
                            (all-system-source-files system-name-or-pathname)
                            (directory (pathname system-name-or-pathname)))
            do
        (setf (first entry) file)
        (setf (second entry) t)
        (grep-in-file cached-string entry *standard-output*)
        (incff total-bytes (fourth entry))
        (report-grep entry))
      (let ((elapsed-time (/ (- (get-internal-real-time) start-time)
                             (float internal-time-units-per-second))))
        (format t "~%~a Kbytes searched in ~a seconds, ~a Kbytes/second."
                (/ total-bytes 1024.0)
                elapsed-time
                (/ (/ total-bytes elapsed-time) 1024.0)))))

(defun #-ansi-cl user::grep #+ansi-cl cl-user::grep (string &optional (system-name-or-pathname 'ab))
  (grep string system-name-or-pathname))

(defparameter newline-string (string #\newline))

(defmacro stream-input-buffer (stream)
  `(let ((line (read-line ,stream nil nil)))
     (if line
         (values line
                 0
                 (length line))
         (values nil 0 0))))

(defmacro stream-discard-input-buffer (stream)
  (declare (ignore stream))
  nil)



;;; The function `grep-in-file' is the internal function of GREP which actually
;;; searches a file for a string.  It reports its results by setting the second
;;; element of the given entry to the number of occurances of that string which
;;; were found.  Use GREP or PGREP to access this function.

(defun grep-in-file (control-pattern entry report-stream?)
  (let* ((controlling-cons (cdr entry))
         (file (car entry))
         (total-bytes 0)
         (pattern-length (length control-pattern))
         (cached-pattern control-pattern)
         (pattern-index 0)
         (input-buffer nil)
         (start-index 0)
         (count 0)
         (occurances 0)
         (pattern-elt-zero
           (if (>f pattern-length 0) (schar cached-pattern 0) nil)))
    (declare (type fixnum
		   total-bytes pattern-length pattern-index start-index
		   count occurances))
    (unwind-protect-for-development grep-in-file
        (when (and (pathnamep file)                        ; In case we're cancelled.
                   (>f pattern-length 0))
          (with-open-file (input file)
            (loop do
              (when (neq (car controlling-cons) t)
                (loop-finish))
              (multiple-value-setq (input-buffer start-index count)
                (stream-input-buffer input))
              (when (null input-buffer)
                (loop-finish))
              (incff total-bytes count)
              (let ((cached-input-buffer input-buffer)
                    (end-index (+f start-index count)))
                (declare (type fixnum end-index))
                (loop for read-index from start-index below end-index
                      do
                  (cond ((=f pattern-index 0)
                         (loop do                ; Tightest loop
                           (if (char-not-equal
                                 pattern-elt-zero
                                 (char cached-input-buffer read-index))
                               (incff read-index)
                               (progn
                                 (incff pattern-index)
                                 (when (>=f pattern-index pattern-length)
                                   (incff occurances)
                                   (when report-stream?
                                     (grep-report-file-and-line-around-index
                                       report-stream?
                                       (truename input)
                                       cached-input-buffer
                                       read-index
                                       start-index
                                       end-index))
                                   (setq pattern-index 0))
                                 (loop-finish)))
                               until (>=f read-index end-index)))
                        ((char-equal (schar cached-pattern pattern-index)
                                     (char cached-input-buffer read-index))
                         (incff pattern-index)
                         (when (>=f pattern-index pattern-length)
                           (incff occurances)
                           (when report-stream?
                             (grep-report-file-and-line-around-index
                               report-stream?
                               (truename input)
                               cached-input-buffer
                               read-index
                               start-index
                               end-index))
                           (setq pattern-index 0)))
                        (t
                         (setq pattern-index 0)))))
              (stream-discard-input-buffer input))
            (setf (car controlling-cons) occurances)
            (setf (fourth entry) total-bytes)))
      (progn
        (setf (car controlling-cons) occurances)
        (setf (fourth entry) total-bytes)))))

(defun grep-report-file-and-line-around-index
       (stream truename buffer index start-index end-index)
  (format stream "~%~a: " truename)
  (let ((start-of-line index)
        (true-start-found? nil)
        (end-of-line index)
        (true-end-found? nil)
        (newline-char #\newline))
    (when (char-not-equal (char buffer index) newline-char)
      ;; Search for the start of the line.
      (loop do
        (cond ((<f start-of-line start-index)
               (setq start-of-line start-index)
               (loop-finish))
              ((char-not-equal (char buffer start-of-line)
                               newline-char)
               (decff start-of-line))
              (t
               (incff start-of-line)
               (setq true-start-found? t)
               (loop-finish))))
      (loop do
        (cond ((>=f end-of-line end-index)
               (loop-finish))
              ((char-not-equal (aref buffer end-of-line)
                               newline-char)
               (incff end-of-line))
              (t
               (setq true-end-found? t)
               (loop-finish))))
      (loop for print-index from start-of-line below end-of-line
            do
        (write-char (char buffer print-index) stream))
      (if (not (and true-start-found? true-end-found?))
          (write-string " (Portion of line)" stream)))))

(defun grep-stream (input control-pattern)
  (let* ((pattern-length (length control-pattern))
         (cached-pattern control-pattern)
         (pattern-index 0)
         (input-buffer nil)
         (start-index 0)
         (count 0)
         (total-bytes 0)
         (occurances 0)
         (pattern-elt-zero
           (if (> pattern-length 0) (schar cached-pattern 0) nil)))
    (declare (type fixnum pattern-index start-index count total-bytes occurances))
    (when (>f pattern-length 0)
      (loop do
        (multiple-value-setq (input-buffer start-index count)
          (stream-input-buffer input))
        (when (null input-buffer)
          (loop-finish))
        (let ((cached-input-buffer input-buffer)
              (end-index (+f start-index count)))
          (declare (type fixnum end-index))
          (loop for read-index from start-index below end-index
                do
            (cond ((=f pattern-index 0)
                   (loop do                        ; Tightest loop
                     (if (char-not-equal
                           pattern-elt-zero
                           (char cached-input-buffer read-index))
                         (incff read-index)
                         (progn
                           (incf pattern-index)
                           (when (>= pattern-index pattern-length)
                             (incf occurances)
                             (setq pattern-index 0))
                           (loop-finish)))
                         until (>= read-index end-index)))
                  ((char-equal (schar cached-pattern pattern-index)
                               (char cached-input-buffer read-index))
                   (incff pattern-index)
                   (when (>=f pattern-index pattern-length)
                     (incff occurances)
                     (setq pattern-index 0)))
                  (t
                   (setq pattern-index 0)))))
        (incff total-bytes count)
        (stream-discard-input-buffer input)))
    (if (> occurances 0)
        (format t "~%Found ~a times in ~a" occurances (truename input))
        (write-char #\.))
    total-bytes))






;;;; External Symbols of Sets of Modules




;;; This debugging utility is used to determine which symbols defined in
;;; particular Lisp module are used in other modules with G2.  So, this utility
;;; can be used to determine what symbols defined in the module UTILITIES0 are
;;; used elsewhere in G2.  The interesting symbols define functions, macros,
;;; variables, parameters, and constants.  Modify macros, setf methods and other
;;; less used utilities won't be addressed directly by this tool at first.
;;; (-jra 2/18/93).

;;; This tool is Lisp implementation dependent, in that it uses non-Common Lisp
;;; operations on symbols to determine what symbols are defined in a module.
;;; For example, TI defines a property called :source-file-name, and Lucid
;;; provides a function called lcl:get-source-file.  The reason to do this is
;;; that we cannot determine from simple source analysis which symbols have
;;; definitions within a module.  This is true because so many of our utilities
;;; are defined by macro expansion.  In this tool we will not attempt to use
;;; macro expansion (i.e.  code walking) to determine the defined symbols of a
;;; file, since we have tried to build code walkers for G2 in the past, and have
;;; miserably failed.

;;; Instead of code walkers, this code will use the debugging utilities provided
;;; by TI and Lucid which provide operations on symbols which return the source
;;; file for the definition of that symbol.  This technique allows this facility
;;; to effectively piggyback on the code walking implemented by the compilers
;;; for these systems.

;;; The function `external-symbols-of-modules' takes a test function or NIL as
;;; its first argument and the rest of the arguments are symbols naming modules
;;; for which the external symbols should be found.  The external symbols of
;;; those modules which also pass the test function are returned from this
;;; function in an association list of external symbols to module names which
;;; use that symbol.  The list of internal symbols of these modules are returned
;;; as the second value of this function.

;;; The set of modules given as arguments to this function are treated as a
;;; single module.  For example, this will allow us to determine which
;;; operations defined in the files FRAMES1 through FRAMES5 are used outside of
;;; FRAMES1 though FRAMES5.

;;; This function will work by using do-symbols to iterate over every symbol in
;;; the AB package, determining the source file (if any) for each.  Those
;;; symbols whose source file matches any of the given modules will be kept in a
;;; list.  These are the defined symbols of the module set.  Then we will use
;;; symbol-search to find all files referencing these symbols.  Those symbols
;;; that are referenced by modules not in the given set are external defined
;;; symbols.  Those only referenced within the set (or not referenced at all)
;;; are internal defined symbols, and are returned in the second value of this
;;; function.

(defun external-symbols-of-modules (predicate? &rest modules)
  (let ((ab-package (find-package "AB"))
        (defined-symbols nil)
        (external-symbol-alist nil)
        (internal-symbols nil))
    ;; Check that the module names are in correct format.
    (loop for module in modules do
      (unless (and (symbolp module)
                   (eq (symbol-package module) ab-package))
        (format t "~%ERROR:  ~a is not a valid package.  It must be a symbol in ~
                   the AB package." module)
        (return-from external-symbols-of-modules nil)))

    ;; Collect the set of defined symbols for these modules.
    (format t "~%Log:  Finding defined symbols...")
    (do-symbols (symbol ab-package)
      (when (and (eq (symbol-package symbol) ab-package)
                 (or (null predicate?)
                     (funcall predicate? symbol)))
        (let ((source-file? (symbol-source-pathname-p symbol)))
          (when (and source-file?
                     (memq (pathname-module-name source-file? ab-package)
                           modules))
            (push symbol defined-symbols)))))
    (format t "  ~a found." (length defined-symbols))

    ;; Filter defined symbols into external and internal.
    (format t "~%Log:  Determining external symbols...")
    (let ((*standard-output* (make-broadcast-stream))
          (copy-search-results-to-editor-buffer nil))
      (loop for symbol in defined-symbols
            for source-pathnames = (symbol-search symbol)
            for external-modules = nil do
        (loop for pathname in source-pathnames
              for module-name = (pathname-module-name pathname ab-package) do
          (unless (memq module-name modules)
            (push module-name external-modules)))
        (if external-modules
            (push (cons symbol (reverse external-modules))
                  external-symbol-alist)
            (push symbol internal-symbols))))
    (format t "~a external symbols, ~a internal symbols."
            (length external-symbol-alist)
            (length internal-symbols))

    ;; Return resulting lists.
    (values external-symbol-alist internal-symbols)))




;;; The function `symbol-source-pathname-p' takes a symbol and returns a
;;; pathname naming the source file within which it was defined, or NIL if none
;;; can be found.

(defun symbol-source-pathname-p (symbol)
  #+lucid
  (cdr (first (lcl:get-source-file symbol nil t)))            ; Needed to avoid a error.
  #-lucid
  (declare (ignore symbol))
  #-lucid
  (error "Source pathnames for symbols can only be found in Lucid."))




;;; The function `pathname-module-name' takes a pathname and a package and
;;; returns the symbol that names the module for this pathname.  That symbol is
;;; interned in the given package.  In effect this is the interned, uppercased
;;; name of the file.

(defun pathname-module-name (pathname package)
  (values (intern (string-upcase (pathname-name pathname)) package)))

(defun car-symbol-name (list)
  (symbol-name (car list)))




;;; The function `write-external-symbols' takes an external symbol alist, a
;;; list of internal symbols, and a file name.  It writes those symbols is a
;;; pseudo-readable format into the file given.

(defun write-external-symbols (external internal file)
  (let ((line-length 80))
    (declare (type fixnum line-length))
    (with-open-file (output file :direction :output)
      (format output "**********~%* External and Internal Symbols Report~%")
      (format output "**********~%")
      (terpri output)
      (format output "**********~%* ~a External Symbols~%**********~%"
              (length external))
      (setq external
            (sort (copy-list external) #'string-lessp :key #'car-symbol-name))
      (loop for external-entry in external
            for symbol = (car-of-cons external-entry)
            for modules = (cdr-of-cons external-entry)
            for chars fixnum = (+f (length (symbol-name symbol)) 2) do
        (format output "~a: " symbol)
        (loop for module in modules
              for module-string = (symbol-name module)
              for module-name-length fixnum = (length module-string)
              for first-time? = t then nil do
          (unless first-time?
            (write-char #\, output)
            (incff chars))
          (when (>=f (+f chars module-name-length 1) line-length)
            (setq chars 5)
            (format output "~%     "))
          (format output " ~(~a~)" module-string)
          (incff chars (1+f module-name-length)))
        (terpri output))
      (format output "~%~%**********~%* ~a Internal Symbols~%**********~%"
              (length internal))
      (setq internal
            (sort (copy-list internal) #'string-lessp :key #'symbol-name))
      (loop for internal-symbol in internal do
        (format output "~a~%" (symbol-name internal-symbol))))))






;;;; Proposed Changes/Additions (Recently Implemented)


;;; 1.  Present all the update databases are kept on the SOURCE machine.
;;; (Presently, the SOURCE machine is MA, but it might be changed to a Vax/VMS.)
;;; Mark D. will be modifying the update functions so that the databases are
;;; stored on the target machines themselves instead on.

;;; 2.  (compile-g2) should be modified on the non-lisp machines so that they
;;; will check the SOURCE machine to ensure that they have the latest versions
;;; of each of the modules of the source code before compiling.  After this
;;; modification, (compile-g2) should run on any target machine just as it does
;;; on the SOURCE machine.  The proposed approach is as follows:

;;; 2a. At the start of (compile-g2), the database for the versions of the last
;;; updates is read in.

;;; 2b. Before compiling each file, check if the current source module is the
;;; latest version available on the SOURCE machine.

;;; 2c. Proceed with the compilation (if required and/or specified by the
;;; optional argument 'recompile).

;;; 2d. At the end of all the recompiles, the database for recording the latest
;;; version numbers is updated.

;;; In order to check if the current source modules are up-to-date (step 2b.),
;;; we have to login to the SOURCE machine and get the version numbers for each
;;; of the modules.  If a module is not up-to-date, then the version on the
;;; source machine can be copied over to the target machine.  There are two ways
;;; by which we can carry out step 2b.:  We could (1) execute one remote login
;;; for each module we are checking, or, (2) execute one one remote login and
;;; execute all the versions checking and file transer.  The former method could
;;; be easier to implement, but the latter method will definitely be more
;;; efficient.

;;; Implementation on Unix machines:  On Unix machines (Suns and HPs), we will
;;; probably mofidy (compile-g2) so that it will write a temporary Unix shell
;;; script to carry out all the required login's, versions checks, source file
;;; transfers, and logouts.  After writing this temporary shell script,
;;; (compile-g2) will then do a Unix system call to that shell script before
;;; deleting it.

;;;   -pto 31aug88






(defun delete-all-files-of-corresponding-pathname (wildcarded-pathname)
  (loop for pathname in (directory wildcarded-pathname)
        do (check-for-aborts-while-bootstrapping 'ab nil nil t)
           (delete-file pathname)))


(defmacro documentation (&rest args)
  #-chestnut-3
  `(ab-lisp::documentation ,@args)
  #+chestnut-3
  (declare (ignore args))
  #+chestnut-3
  nil
  )

(#-ansi-cl lisp::defmacro
 #+ansi-cl cl::defmacro
 #-ansi-cl user::g2tape
 #+ansi-cl cl-user::g2tape
    (&rest type-or-types)
    "Usage: (g2tape alpha | plain | gsi | gfi | gsi gfi | gfi gsi | mac-alpha-kbs | mac-beta-kbs | mac-kbs)"
  type-or-types
  `(let* ((number-of-types (length ',type-or-types))
          (unnormalized-type
            (case number-of-types
              (1 (car ',type-or-types))
              (2 (if (and (string-or-symbol-member 'gfi ',type-or-types)
                          (string-or-symbol-member 'gsi ',type-or-types))
                     'gfi+gsi
                     (g2tape-error)))
              (t
               (if (> (length ',type-or-types) 2)
                   (g2tape-error)))))
          (type
            (progn
                (if (and (not (atom unnormalized-type))
                         (eq (car unnormalized-type) 'quote))
                    (setq unnormalized-type (cadr unnormalized-type)))
                (if (stringp unnormalized-type)
                    (setq unnormalized-type
                          (intern (string-upcase unnormalized-type))))
                (normalize-name unnormalized-type))))

     (if (string-or-symbol-member type
                                  '(beta mac-beta-kbs))
         (error "Please choose:  plain, gfi, gsi, gspan, or gsi gfi.~% ~
                 See PTO or AC if you're confused."))

     (cond
       ((string-or-symbol-member type
                                 '(alpha plain gsi gfi gfi+gsi gsi+gfi
                                         mac-alpha-kbs mac-beta-kbs mac-kbs
                                         g2-online g2-offline))
        (make-distribution-tape type))
       (t
        (format t "~&~a~&" (documentation 'g2tape))))))

(defun same-file-contents-p (pathname-1 pathname-2)
  (let* ((stream-1? nil)
         (stream-2? nil))
    (unwind-protect-for-development same-file-contents-p
        (if (setq stream-1?
                  (open pathname-1 :if-does-not-exist nil))
            (if (setq stream-2?
                      (open pathname-2 :if-does-not-exist nil))
                (same-stream-contents-p stream-1? stream-2?)
                (values nil t))
            (values nil nil t))
      (if stream-1?
          (close stream-1?))
      (if stream-2?
          (close stream-2?)))))

(defun same-stream-contents-p (stream-1 stream-2)
  (loop for line-1? = (read-line stream-1 nil nil)
        as line-2? = (read-line stream-2 nil nil)
        do (cond
             ((and (null line-1?) (null line-2?))
              (return t))
             ((not (equal line-1? line-2?))        ; succeeds on EOF
              (return nil)))))









;;;; Updating Copyright Notices



;;; `Update-copyright-notices' ... rewrites all C, H, and Lisp files in the
;;; "MA: AB;" directory so that lines of the form
;;;
;;;    (0) The first two characters are
;;;           ;;
;;;
;;;        OR the second character is
;;;
;;;           *
;;;
;;;    (1) followed by any number of any character
;;;
;;;    (2) followed by
;;;           Copyright (c)
;;;
;;;    (3) followed by a series of one or more years, separated by commas if
;;;        necessary, up to but not including year
;;;
;;;    (4) followed by
;;;           Gensym Corporation
;;;
;;;    (5) followed by any number of any character
;;;
;;; will be written out so that year is inserted in the series of years
;;; in (3).

(defun update-copyright-notices (year)
  (loop for file-name in (directory "ma:>ab>*.*.newest")
        when (member
               (pathname-type file-name)
               '("c" "h" "lisp")
               :test #'string-equal)
          do (update-copyright-notice-in-file year file-name)))


(defun update-copyright-notice-in-file (new-year file-name)
  (with-open-file (input-stream file-name :direction :input)
    (with-open-file
      (output-stream
        (make-pathname :defaults file-name :version :newest)
        :direction :output)
      (loop with start-index?
            with search-sequence = "Copyright (c)"
            with minimum-length-for-matching-line
              = #.(+ 2                                ; for initialy ";;" or " *"
                     13                                ; (length "Copyright (c)")
                     18)                        ; (length "Gensym Corporation")
            with new-year-as-string = (format nil "~d" new-year)
            with previous-year-as-string = (format nil "~d" (- new-year 1))
            for line? = (read-line input-stream nil nil)
            while line?
            if (and (> (length line?)                ; cheapest test
                       minimum-length-for-matching-line)
                    (or (string-equal ";;" line? :end2 2)
                        (and (> (length line?) 2)
                             (eql (char line? 1) #\*)))
                    (setq start-index? (search search-sequence line?))
                    (setq start-index? (search previous-year-as-string line?))
                    (null (search new-year-as-string line?)))
              do (setq start-index? (+ start-index? (length previous-year-as-string)))
                 (write-string line? output-stream :end start-index?)
                 (format output-stream ", ~d" new-year-as-string)
                 (write-line line? output-stream :start start-index?)
            else do (write-line line? output-stream)))))






;;;; macroexpander <form> &optional <package-for-macros>

;;; The function macroexpander walks through form, macroexpanding as it goes.  For
;;; each subform, if the special variable test-in-walking-for-macroexpansion?  is
;;; bound to a function object, this is applied to the subform.  If this test
;;; returns non-nil and the special variable action-in-walking-for-macroexpansion?
;;; is bound to a function object, this function is applied to the subform

;; jh, 9/24/91.  Adapted macroexpander from JRA's code for the Chestnut setjmp
;; fix.  It could use some abstraction, as the need for a complete macroexpander
;; is likely to grow as we get more experience with Chestnut.

;; jh, 9/26/91.  Macroexpander is no longer used for the setjmp fix.  It is
;; replaced by defun-allowing-unwind in BOOTSTRAP.  Keep this code around for a
;; while in case it proves useful in our translation efforts.

#-no-macros
(#-ansi-cl lisp:defmacro
 #+ansi-cl cl::defmacro
        loop-for-var-in-list-collecting
               (variable list-form collection-form)
  (let ((collection-var (#-ansi-cl lisp:gensym #+ansi-cl cl:gensym)))
    `(let ((,collection-var nil))
       (dolist (,variable ,list-form)
         (setq ,collection-var (cons ,collection-form ,collection-var)))
       (nreverse ,collection-var))))




;;; The function `macroexpander-for-parameter-list' is used to macro expand
;;; lambda lists of functions and macros.  Note that it needs to handle
;;; destructuring lambda lists.  A description on p. 202 of CLtL II states that
;;; destructuring lists may be included whereever a symbol is allowed, but not
;;; where lists can occur, to avoid ambiguity for default value forms for
;;; optional arguments.  The following function should expand all of this
;;; correctly.

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(#-ansi-cl lisp:defun
 #+ansi-cl cl:defun
        macroexpander-for-parameter-list
            (parameter-list test? action? defaults-ok?)
  (let ((argument? (if (consp parameter-list) (car parameter-list))))
    ;; Dotted destructuring lambda lists exercise the first clause.
    (cond ((atom parameter-list)
           parameter-list)
          ;; Symbol arguments and keywords satisfy this clause.
          ((atom argument?)
           (when (member argument? '(&optional &key &aux))
             (setq defaults-ok? t))
           (cons argument?
                 (macroexpander-for-parameter-list
                   (cdr parameter-list) test? action? defaults-ok?)))
          ;; Non-atomic arguments which should be optional and keyword argument
          ;; specifications should satisfy this clause.
          (defaults-ok?
           (cons `(,(macroexpander-for-parameter-list
                      (car argument?) test? action? nil)
                   ,(macroexpander (second argument?) test? action?)
                   ,@(cddr argument?))
                 (macroexpander-for-parameter-list
                   (cdr parameter-list) test? action? defaults-ok?)))
          ;; Destructuring lambda lists fall into this clause.
          (t
           (cons (cons (macroexpander-for-parameter-list
                         (car argument?) test? action? nil)
                       (macroexpander-for-parameter-list
                         (cdr argument?) test? action? nil))
                 (macroexpander-for-parameter-list
                   (cdr parameter-list) test? action? defaults-ok?))))))
)

#-no-macros
(eval-when (:compile-toplevel :load-toplevel :execute)
(#-ansi-cl lisp:defun
 #+ansi-cl cl:defun
        macroexpander (form test? action?)
  (if (not (consp form))
      form
      (let ((name (car form)))
        (cond
          ;; If the car isn't a symbol, it could be a functional application of a
          ;; lambda-form.
          ((not (symbolp name))
           (if (and (consp name)
                    (eq (car name) 'lambda))
               `((,(first name)
                  ,(macroexpander-for-parameter-list
                     (second name) test? action? nil)
                  ,@(loop-for-var-in-list-collecting
                      lambda-body-form (cddr name)
                      (macroexpander lambda-body-form test? action?)))
                 ,@(loop-for-var-in-list-collecting
                     argument (cdr form)
                     (macroexpander argument test? action?)))
               (cerror "Continue" "MACROEXPANDER: ~
                      head of form ~a neither a lambda-expression nor a symbol."
                     form)))
          ;; Run test on form.
          ((and test? (#-ansi-cl lisp:funcall #+ansi-cl cl:funcall test?))
           (when action?
             (#-ansi-cl lisp:funcall #+ansi-cl cl:funcall action?)))
          (t
           (case name
             ;; Process all special forms.
             ((block)
              `(,name ,(second form)
                      ,@(loop-for-var-in-list-collecting
                         argument-form (cddr form)
                         (macroexpander argument-form test? action?))))
             ((catch #-ansi-cl lisp:catch #+ansi-cl cl:catch)
              `(,name ,(second form)
                      ,@(loop-for-var-in-list-collecting
                         argument-form (cddr form)
                         (macroexpander argument-form test? action?))))
             ((compiler-let let let*)
              `(,name
                ,(loop-for-var-in-list-collecting
                  binding (second form)
                  (if (symbolp binding)
                      binding
                      (list (first binding)
                            (macroexpander (second binding) test? action?))))
                ,@(loop-for-var-in-list-collecting
                   sub-form (cddr form) (macroexpander sub-form test? action?))))
             ((declare)
              form)
             ((eval-when)
              `(,name ,(second form)
                      ,@(loop-for-var-in-list-collecting
                         sub-form (cddr form)
                         (macroexpander sub-form test? action?))))
             ((labels flet)
              `(,name
                ,(loop-for-var-in-list-collecting
                  function-declaration (second form)
                  `(,(first function-declaration)
                    ,(macroexpander-for-parameter-list
                       (second function-declaration) test? action? nil)
                    ,@(loop-for-var-in-list-collecting
                       sub-dec-form (cddr function-declaration)
                       (macroexpander sub-dec-form test? action?))))
                ,@(loop-for-var-in-list-collecting
                   sub-form (cddr form) (macroexpander sub-form test? action?))))
             ((macrolet)
              (let ((symbols-and-expansions
                     (loop-for-var-in-list-collecting
                      macro-declaration (second form)
                      (let* ((macro-name (first macro-declaration))
                             (old-expander? (#-ansi-cl lisp:macro-function
                                             #+ansi-cl cl:macro-function macro-name))
                             (old-function-definition?
                              (and (null old-expander?)
                                   (fboundp macro-name)
                                   (#-ansi-cl lisp:symbol-function
                                    #+ansi-cl cl:symbol-function
                                           macro-name)))
                             (new-expander
                              (eval ;risky to use compile recursively, so we dare to be slow
                               `(function
                                 (lambda (form env)
                                   (declare (ignore env))
                                   ;; Common Lisp syntax, not Gensym's
                                   (,(progn
                                       #+lucid
                                       (intern "DESTRUCTURING-BIND" "LCL"))
                                    ,(second macro-declaration)
                                    (cdr form)
                                    ,@(cddr macro-declaration)))))))
                        (list (first macro-declaration)
                              old-expander?
                              new-expander
                              old-function-definition?)))))
                (#-ansi-cl lisp:unwind-protect #+ansi-cl cl:unwind-protect
                    (progn
                      (dolist (expander-spec symbols-and-expansions)
                        (setf (#-ansi-cl lisp:macro-function
                               #+ansi-cl cl:macro-function (first expander-spec))
                              (third expander-spec)))
                      `(progn
                         ,@(loop-for-var-in-list-collecting
                             sub-form
                             (cddr form)
                             (macroexpander sub-form test? action?))))
                  (dolist (expander-spec symbols-and-expansions)
                    ;; restore old macro definition
                    (setf (#-ansi-cl lisp:macro-function
                           #+ansi-cl cl:macro-function (first expander-spec)) (second expander-spec))
                    ;; restore old function definition if any
                    (when (fourth expander-spec)
                      (setf (#-ansi-cl lisp:symbol-function
                             #+ansi-cl cl:symbol-function
                                    (first expander-spec))
                            (fourth expander-spec)))))))
             ((function)
              (let ((function? (second form)))
                (cond ((or (symbolp function?)
                           (and (consp function?)
                                (eq (car function?) 'setf)))
                       form)
                      ((and (consp function?)
                            (or (eq (first function?) 'lambda)))
                       `(function
                         (lambda ,(second function?)
                           ,@(loop-for-var-in-list-collecting
                              function-form (cddr function?)
                              (macroexpander function-form test? action?)))))
                      ;; Otherwise, I dunno WHAT this is, just return it.
                      (t (cerror "Continue" "MACROEXPANDER: Strange functional object ~a"
                               form)
                         form))))
             ((go)
              form)
             ((if)
              `(if ,(macroexpander (second form) test? action?)
                   ,(macroexpander (third form) test? action?)
                   ,@(if (fourth form)
                         (list (macroexpander (fourth form) test? action?))
                         nil)))
             ((multiple-value-call multiple-value-prog1 progn locally
                                   multiple-value-list)
              `(,name
                ,@(loop-for-var-in-list-collecting
                   sub-form (cdr form) (macroexpander sub-form test? action?))))
             ((progv)
              `(,name ,(second form)
                      ,(loop-for-var-in-list-collecting
                        value-form (third form)
                        (macroexpander value-form test? action?))
                      ,@(loop-for-var-in-list-collecting
                         sub-form (cdddr form)
                         (macroexpander sub-form test? action?))))
             ((quote)
              form)
             ((return-from)
              `(,name ,(second form) ,(macroexpander (third form) test? action?)))
             ((setq)
              `(setq
                ,@(do ((result nil)
                       (symbol-value-pairs (cdr form) (cddr symbol-value-pairs)))
                      ((null symbol-value-pairs) result)
                      (setq result
                            (nconc result (list (first symbol-value-pairs)
                                                (macroexpander
                                                 (second symbol-value-pairs)
                                                 test? action?)))))))
             ((tagbody)
              `(,name ,@(loop-for-var-in-list-collecting
                         sub-form (cdr form)
                         (macroexpander sub-form test? action?))))
             ((the)
              `(the ,(second form) ,(macroexpander (third form) test? action?)))
             ((throw)
              `(throw ,(second form) ,(macroexpander (third form) test? action?)))
             ((unwind-protect #-ansi-cl lisp:unwind-protect #+ansi-cl cl:unwind-protect)
              `(,name
                ,@(loop-for-var-in-list-collecting
                   sub-form (cdr form) (macroexpander sub-form test? action?))))
             ;;
             ;; End of special forms.
             ;; Process the macros "defun", "defmacro", "cond", "and", "or",
             ;; "return", and "prog1" as if they were special forms.
             ;; They are macros, but their expansions into special implementation-
             ;; specific special forms makes them unreadable.
             ;;
             ((defun #-ansi-cl lisp:defun #+ansi-cl cl:defun defmacro #-ansi-cl lisp:defmacro #+ansi-cl cl:defmacro)
              `(,name ,(second form)
                      ,(macroexpander-for-parameter-list
                         (third form) test? action? nil)
                      ,@(loop-for-var-in-list-collecting
                         sub-form (cdddr form) (macroexpander sub-form test? action?))))
             ((cond)
              `(cond ,@(loop-for-var-in-list-collecting
                        clause (cdr form)
                        `(,(macroexpander (first clause) test? action?)
                          ,@(loop-for-var-in-list-collecting
                             clause-form (cdr clause)
                             (macroexpander clause-form test? action?))))))
             ((and or return prog1)
              `(,name ,@(loop-for-var-in-list-collecting
                         sub-form (cdr form)
                         (macroexpander sub-form test? action?))))
             ((defsetf) ;assumes we are in no-macros pass
              form)
             ((define-modify-macro #-ansi-cl lisp:define-modify-macro #+ansi-cl cl:define-modify-macro) ;assumes we are in no-macros pass
              form)
             ((do do*)
              `(,name
                ,(loop-for-var-in-list-collecting
                   iter-clause (second form)
                   `(,(first iter-clause)
                     ,(macroexpander (second iter-clause) test? action?)
                     ,@(when (third iter-clause)
                         (list (macroexpander (third iter-clause) test? action?)))))
                (,(macroexpander (first (third form)) test? action?)
                 ,@(loop-for-var-in-list-collecting
                     result-form (cdr (third form))
                     (macroexpander result-form test? action?)))
                ,@(loop-for-var-in-list-collecting
                    body-form (cdddr form)
                    (macroexpander body-form test? action?))))
             ((multiple-value-bind multiple-value-setq)
              `(,name ,(second form) ,@(loop-for-var-in-list-collecting
                                         body-form (cddr form)
                                         (macroexpander body-form test? action?))))
             ((defconstant defparameter defvar)
              `(,name ,(second form)
                ,@(when (third form)
                    (list (macroexpander (third form) test? action?)))))
             ((defstruct)
              `(,name
                ,(second form)
                ,@(loop-for-var-in-list-collecting
                    slot-clause (cddr form)
                    (if (consp slot-clause)
                        `(,(car slot-clause)
                          ,(macroexpander (second slot-clause) test? action?))
                        slot-clause))))

             ;;
             ;; In this region, we handle implementation specific special forms
             ;; which are emitted from system internal macros.
             ;;
             (otherwise
              (cond ((#-ansi-cl lisp:macro-function
                      #+ansi-cl cl:macro-function name)
                     (let ((result (macroexpand-1 form)))
                       (if (equal result form)
                           (progn
                             (cerror
                               "Continue" "MACROEXPANDER: The macro ~a seems to be a no-op."
                               name)
                             (warn "MACROEXPANDER: The macro ~a seems to be a no-op."
                                   name)
                             form)
                           (macroexpander result test? action?))))
                    ((special-form-p name)
                     (cerror "Continue" "MACROEXPANDER: Unknown special form ~a"
                             form)
                     form)
                    ;; Otherwise, it is (almost certainly) a function call.
                    (t
                     (if (= (length form) 1)
                         form
                         `(,name ,@(loop-for-var-in-list-collecting
                                    argument (cdr form)
                                    (macroexpander argument test? action?))) )))) ))))))
) ;end of eval-when (:compile-toplevel :load-toplevel :execute)

;;; The macro walking-for-macroexpansion takes a form as argument and walks
;;; through the form, macroexpanding as it goes.  If :test is true of a subform,
;;; :action is applied to that subform.  Walking-for-macroexpansion establishes a
;;; catcher which is the symbol walking-for-macroexpansion, should the action wish
;;; a non-local return.  If no such return is made, walking-for-macroexpansion
;;; returns the result of the :return form.

#-no-macros
(#-ansi-cl lisp:defmacro
 #+ansi-cl cl:defmacro
        walking-for-macroexpansion
  (form &key test action (return nil return-form-supplied-p))
  (labels ((variable-used-p (form variable)
             (cond ((eq form variable) (throw 'used-p t))
                   ((not (consp form)) nil)
                   (t (or (variable-used-p (car form) variable)
                          (variable-used-p (cdr form) variable))))))
    (let ((return-form
            (if return-form-supplied-p
                return
                'macroexpanded-form)))
      `(#-ansi-cl lisp:catch #+ansi-cl cl:catch 'walking-for-macroexpansion
         (let* ((test-in-walking-for-macroexpansion?
                  (function (lambda (form)
                              ,@(if (#-ansi-cl lisp:catch #+ansi-cl cl:catch 'used-p
                                      (variable-used-p test 'form))
                                    nil
                                    `((declare (ignore form))))
                              ,test)))
                (action-in-walking-for-macroexpansion?
                  (function (lambda (form)
                              ,@(if (#-ansi-cl lisp:catch #+ansi-cl cl:catch 'used-p
                                      (variable-used-p action 'form))
                                    nil
                                    `((declare (ignore form))))
                              ,action)))
                (macroexpanded-form
                  (macroexpander
                    ,form
                    test-in-walking-for-macroexpansion?
                    action-in-walking-for-macroexpansion?)))
           ,@(if (#-ansi-cl lisp:catch #+ansi-cl cl:catch 'used-p
                   (variable-used-p return-form 'macroexpanded-form))
                 nil
                 `((declare (ignore macroexpanded-form))))
           ,return-form)))))



;;;; Unix Miscellany

;;; The message given before booting USA after reconfiguring kernal to increase
;;; the allowed number of processes to 200 was
;;;
;;;   reboot -h -t +5 -m "USA rebooting to increase number of user processes allowed"
;;;
;;; This gives a 5-minute warning.  (MHD 1/23/92)
;;;
;;;
;;; Using Man when the thing you want is ambiguous
;;;
;;;   man 1m reboot
;;;
;;; This gets you the shell command reboot's documentation rather than the system
;;; call.  (MHD 2/3/93)










;;;; Generate Indent table for EMacs



;;; `Build-indent-table-for-emacs' creates a file suitable for
;;; loading into EMacs so that it will know how to indent all
;;; the macros defined in the AB package.

;; ben 6/7/93

#+Lucid
(defun build-indent-table-for-emacs (output-file)
  (let (result
        (tmp-file "/tmp/indent-table.el")
        (ab-package (find-package "AB")))
    (do-symbols (s (find-package "AB"))
      (when (and (macro-function s)
                 (eql (symbol-package s) ab-package))
        (let ((body-offset?
               (loop for p on (lcl:arglist s)
                     for cnt from 0
                     when (or (not (consp p))
                              (eql (car p) '&body))
                     do (return cnt))))
          (when body-offset?
            (push (list s body-offset?) result)))))
    (with-open-file (s tmp-file
                       :direction :output)
      (loop
        initially
          (format s ";; Automaticly generated by build-indent-table-for-emacs in SITE.")
          (format s "~&(let ((l '(")
        finally
          (loop for i in '(
                           "~&          )))"
                           "~&  (while l"
                           "~&    (put (car (car l)) 'common-lisp-indent-function"
                           "~&         (if (symbolp (cdr (car l)))"
                           "~&             (get (cdr (car l)) 'common-lisp-indent-function)"
                           "~&             (car (cdr (car l)))))"
                           "~&    (setq l (cdr l))))"
                           "~&;; Automaticly Generated, see top."
                           "~&")
                do (format s i))
        for (symbol where-is-body) in result
            do (format s "~(~&  (~A ~D)~)" symbol where-is-body)))
    (gensym-copy-file tmp-file output-file)))

;; Tedious Receipe
;; (build-indent-table-for-emacs "/tmp/foo.el")
;; cp /tmp/foo.el /home/ab/ab-lemacs/ab-indent-table.el
;; M-X byte-compile-file /home/ab/ab-lemacs/ab-indent-table.el
;; It would be nice if this was done in regularly by the automated build.
