;; Code to report total coverage from sb-cover stats
(in-package :sb-cover)
 
(defun report-with-expression-totals (directory &key ((:form-mode *source-path-mode*) :whole)
               (external-format :default))
  "Modified version of sb-cover::report. Also prints total expression coverage for all files"
  (let ((paths)
        (total-covered-exprs 0)
        (total-exprs 0)
        (*default-pathname-defaults* (pathname-as-directory directory)))
    (ensure-directories-exist *default-pathname-defaults*)
    (maphash (lambda (k v)
               (declare (ignore v))
               (let* ((n (format nil "~(~{~2,'0X~}~)"
                                (coerce (sb-md5:md5sum-string
                                         (sb-ext:native-namestring k))
                                        'list)))
                      (path (make-pathname :name n :type "html")))
                 (when (probe-file k)
                   (with-open-file (stream path
                                           :direction :output
                                           :if-exists :supersede
                                           :if-does-not-exist :create)
                     (push (list* k n (report-file k stream external-format))
                           paths)))))
             *code-coverage-info*)
    (let ((report-file (make-pathname :name "cover-index" :type "html"))
          (even t))
      (with-open-file (stream report-file
                              :direction :output :if-exists :supersede
                              :if-does-not-exist :create)
        (write-styles stream)
        (unless paths
          (warn "No coverage data found for any file, producing an empty report. Maybe you~%forgot to (DECLAIM (OPTIMIZE SB-COVER:STORE-COVERAGE-DATA))?")
          (format stream "<h3>No code coverage data found.</h3>")
          (close stream)
          (return-from report-with-expression-totals))
        (format stream "<table class='summary'>")
        (format stream "<tr class='head-row'><td></td><td class='main-head' colspan='3'>Expression</td><td class='main-head' colspan='3'>Branch</td></tr>")
        (format stream "<tr class='head-row'>~{<td width='80px'>~A</td>~}</tr>"
                (list "Source file"
                      "Covered" "Total" "%"
                      "Covered" "Total" "%"))
        (setf paths (sort paths #'string< :key #'car))
        (loop for prev = nil then source-file
              for (source-file report-file expression branch) in paths
              do (setf even (not even))
              do (when (or (null prev)
                           (not (equal (pathname-directory (pathname source-file))
                                       (pathname-directory (pathname prev)))))
                   (format stream "<tr class='subheading'><td colspan='7'>~A</td></tr>~%"
                           (namestring (make-pathname :directory (pathname-directory (pathname source-file))))))
              do (format stream "<tr class='~:[odd~;even~]'><td class='text-cell'><a href='~a.html'>~a</a></td>~{<td>~:[-~;~:*~a~]</td><td>~:[-~;~:*~a~]</td><td>~:[-~;~:*~5,1f~]</td>~}</tr>"
                         even
                         report-file
                         (enough-namestring (pathname source-file)
                                            (pathname source-file))
                         (list (ok-of expression)
                               (all-of expression)
                               (percent expression)
                               (ok-of branch)
                               (all-of branch)
                               (percent branch)))
             do (incf total-covered-exprs (ok-of expression))
             do (incf total-exprs (all-of expression))
             )
        (format stream "<tr class='~:[odd~;even~]'><td class='text-cell'><a href='~a.html'>~a</a></td>~{<td>~:[-~;~:*~a~]</td><td>~:[-~;~:*~a~]</td><td>~:[-~;~:*~5,1f~]</td>~}</tr>"
                even
                "N/A"
                "TOTAL"
                (list total-covered-exprs
                      total-exprs
                      (format nil "~6,4f"
                              (unless (zerop total-exprs) 
                                (* 100 (/ total-covered-exprs total-exprs))))
                      nil
                      nil
                      nil))
        (format stream "</table>")
      report-file))))
 
(defun delete-unnecessary-coverage-stats ()
  "Delete test themselves and lisp-unit components from coverage stats"
  (let ((h sb-c::*code-coverage-info*)
        (*print-circle* t)
        )
    (loop for fn being the hash-keys of h
          ; fn is just file name
          when (or (search "/tests/" fn)
                   (search "/asdf/" fn)
                   (search "/lisp-unit" fn))
          do (remhash fn h))))
