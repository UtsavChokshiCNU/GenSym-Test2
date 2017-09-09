;;; Test setups for misc g2 tests
;;; system :tests

(in-package :tests)

(proclaim '(optimize debug))

;;; OO is not initialized here
;;; tests::process-handle variable is defined inside this macro
(defmacro with-simplest-test-environment (() &body body)
  `(let ((process-handle (make-symbol "UNIT-TEST-PROCESS-HANDLE")))
     #+cons-checking (ab::cons-checking-start-common-part)
     (ab::with-system-variables ('ab::ab process-handle)
       ,@body)))

;;; OO is initialized and kb is present
;;; tests::process-handle variable is defined inside this macro
(defmacro with-connection-test-environment (() &body body)
  `(let ((process-handle (make-symbol "UNIT-TEST-PROCESS-HANDLE")))
     #+cons-checking (ab::cons-checking-start-common-part)
     (ab::with-system-variables ('ab::ab process-handle)
       ;; Might this be useful? 
         ;(ab::initialize-class-bit-numbers-and-vectors-to-nil)
       (setq ab::warning-message-level 0)
       (setq ab::loading-kb-p nil)
       ;; these are parts of RUN-AB
       (ab::assign-class-bit-numbers-and-vectors-to-system-classes)
       ;; for COLLECT-SUBCLASSES to work.
       (setq ab::classes-visited-byte-vector
             (ab::initialize-classes-visited-byte-vector))
       (ab::switch-to-new-empty-kb)
       ,@body)))


;; to be executed in the scope of with-connection-test-environment
(defun g2-test-setup-create-workspace ()
  (let ((ab::miscellaneous-parameters nil))
    (mock:with-wrapped-functions*
        (#+(or sbcl lispworks) ;; aligned with tests.asd
	 (ab::get-slot-value-function
          'aux-fn-get-slot-value-function-for-test--make-new-top-level-kb-workspace--returns-workspace)
         (ab::mutate-kb-specific-property-value 'ignore-all)
         (ab::put-module-this-is-part-of? 'ignore-all)
         (ab::recompute-selection-highlights 'ignore-all)
         (ab::|AB::FRAME-STATUS-AND-NOTES -Mock-function| 'ignore-all)
         (ab::|AB::TOP-LEVEL-KB-MODULE? -Mock-function| 'ignore-all)
         )
      (with-mocked-macros (ab::frame-status-and-notes
                           ab::module-system-table-belongs-to?
                           ab::top-level-kb-module?)
        (mock:expect
         (
          (:call (AB::|AB::MODULE-SYSTEM-TABLE-BELONGS-TO? -Mock-function| nil) :return (nil))
          )
         :for
         (ab::make-new-top-level-kb-workspace 'ab::kb-workspace t))))))

(defun make-connection-between-two-objects (node1 node2)
  ;; returns a list of 
  ;; (connection connection-frame connection-item-in connection-item-out)
  ;; connection-item-tables must be created for nodes before calling this.
  ;; NOTE there are several ways to create connections, we use one of them here
  ;; others are ab::make-transient-connection and ab::make-stubs
  (let* ((connection (ab::make-connection))
         (connection-item-in (ab::make-connection-item connection))
         (connection-item-out (ab::make-connection-item connection))
         ;; borrowed from ab::get-or-make-connection-frame-and-activate-if-appropriate
         (connection-frame (ab::make-entity 'ab::connection)))
    ;; borrowed from ab::make-new-connection-frame-for-connection
    (setf (ab::connection-for-this-connection-frame connection-frame)
          connection
          (ab::connection-frame-or-class connection)
          connection-frame)
    (setf (ab::input-end-object connection) node1)
    (setf (ab::output-end-object connection) node2)
    (setf (ab::connection-item-output-names connection-item-in) (list 'in))
    (setf (ab::connection-item-output-names connection-item-out) (list 'out))
    (setf (ab::input-end-position connection)
          (ab::combine-side-and-position-on-side-for-end-position 'ab::top 2))
    
    (setf (ab::output-end-position connection)
          (ab::combine-side-and-position-on-side-for-end-position 'ab::bottom 3))
    (setf (ab::get-connection-item connection (ab::connections node1))
          connection-item-in)
    (setf (ab::get-connection-item connection (ab::connections node2))
          connection-item-out)
    (list connection connection-frame connection-item-in connection-item-out)
    ))  


(defun create-two-blocks-on-a-workspace (&key (make-empty-connection-item-tables t))
  ;;; to be executed in the scope of with-connection-test-environment
  (let* ((workspace (g2-test-setup-create-workspace))
         (node1 (ab::make-frame 'ab::block))
         (node2 (ab::make-frame 'ab::free-text)))
      ; take symbol from ab package, just in case
    (setf (ab::name-or-names-for-frame node1) 'ab::node1)

    (setf (ab::left-edge-of-block node1) 10)
    (setf (ab::top-edge-of-block node1) 10)

    (setf (ab::left-edge-of-block node2) 100)
    (setf (ab::top-edge-of-block node2) 10)

    (setf (ab::superblock? node1) workspace)
    (when make-empty-connection-item-tables
      (setf (ab::connections node1) (ab::make-connection-item-table)))
    
      ; take symbol from ab package, just in case
    (setf (ab::name-or-names-for-frame node2) 'ab::node2)
    (setf (ab::superblock? node2) workspace)
    (when make-empty-connection-item-tables
      (setf (ab::connections node2) (ab::make-connection-item-table)))
    (list workspace node1 node2)))   
  

(defun create-two-blocks-and-one-connection-on-a-workspace ()
  ;;; to be executed in the scope of with-connection-test-environment
  ;; create instances
  (destructuring-bind (workspace node1 node2)
      (create-two-blocks-on-a-workspace)
    
    (destructuring-bind (connection connection-frame connection-item-in connection-item-out) (make-connection-between-two-objects node1 node2)
      (declare (ignore connection-item-in connection-item-out))
      
      ;; to extract workspace, use (ab::get-workspace-if-any node1)
      (list node1 node2 connection connection-frame workspace))))

;; creates and returns an ab::block named node3 on workspace
(defun create-node3-on-a-workspace (workspace)
  (let* ((node3 (ab::make-frame 'ab::block)))
    ; take symbol from ab package, just in case
    (setf (ab::name-or-names-for-frame node3) 'ab::node3)
    (setf (ab::superblock? node3) workspace)
    (setf (ab::connections node3) (ab::make-connection-item-table))
    node3))

(defun reclaim-what-was-created-by-create-two-blocks-on-a-workspace (workspace node1 node2 &key (reclaim-connection-item-tables t))
  (let ((register nil))

    (when reclaim-connection-item-tables
      (rotatef (ab::connections node1) register)
      (ab::reclaim-connection-item-table register)
      (setf register nil))

    (setf (ab::superblock? node1) nil)
    (setf (ab::name-or-names-for-frame node1) nil)
    (ab::delete-frame node1)
    
    (when reclaim-connection-item-tables
      (rotatef (ab::connections node2) register)
      (ab::reclaim-connection-item-table register)
      (setf register nil))

    (setf (ab::superblock? node2) nil)
    (setf (ab::name-or-names-for-frame node2) nil)
    (ab::delete-frame node2)
    
    (mock:expect
     (
      (:call (AB::UPDATE-MODULE-RELATED-FRAME-NOTES-FOR-ALL-WORKSPACES)
       :return
       nil) ; it errs so we mock it. It is a crap test.
      )
     :for
     (ab::delete-frame workspace))))
  

(defun reclaim-what-was-created-by-create-two-blocks-and-one-connection-on-a-workspace (node1 node2 connection connection-frame workspace)
  ;; We don't know the right way to do that, so we simply reverse 
  ;; what we did 
  (let* ((connection-item-in (ab::get-connection-item connection (ab::connections node1)))
         (connection-item-out (ab::get-connection-item connection (ab::connections node2))))
    (setf (ab::get-connection-item connection (ab::connections node1)) nil)
    (setf (ab::get-connection-item connection (ab::connections node1)) nil)
    (setf (ab::connection-item-output-names connection-item-out) nil)
    (setf (ab::connection-item-output-names connection-item-in) nil)
    ;; (SETF (AB::OUTPUT-END-POSITION CONNECTION) (AB::COMBINE-SIDE-AND-POSITION-ON-SIDE-FOR-END-POSITION 'AB::BOTTOM 3))
    ;; (SETF (AB::INPUT-END-POSITION CONNECTION) (AB::COMBINE-SIDE-AND-POSITION-ON-SIDE-FOR-END-POSITION 'AB::TOP 2))
    (setf (ab::output-end-object connection) nil)
    (setf (ab::input-end-object connection) nil)

    ;(setf (ab::connection-for-this-connection-frame connection-frame) nil)
    ;(setf (ab::connection-frame-or-class connection) nil)

    (ab::reclaim-connection-item connection-item-out)
    (ab::reclaim-connection-item connection-item-in)

    ;; deletion of connection is semi-empiric. We try to cut
    ;; the corners and use more high-level functions
    (ab::delete-frame connection-frame)
    (ab::reclaim-connection connection)

    (reclaim-what-was-created-by-create-two-blocks-on-a-workspace workspace node1 node2)

    ))
  

(defun create-three-blocks-chained-with-connections ()
  ;; returns the list of values as folows
  ;; workspace node1 <-- connection1 --> node2 <-- connection2 --> node3
  ;; connection2 is transient
  (destructuring-bind (node1 node2 connection1 connection-frame workspace)
      (create-two-blocks-and-one-connection-on-a-workspace)
    (declare (ignore connection-frame))
    (let* ((node3 (create-node3-on-a-workspace workspace))
           (connection-frame-2
            (mock:with-wrapped-functions*
                ((ab::recompute-selection-highlights 'ignore-all))
              (ab::make-transient-connection
               'ab::connection
               node2 t 'ab::top 6 nil
               node3 t 'ab::top 6 nil
               t 'ab::diagonal nil t)))
           (connection2 (ab::connection-for-this-connection-frame connection-frame-2)))
      (list workspace node1 connection1 node2 connection2 node3))))
  
;; to be executed in the scope of with-connection-test-environment
(defun create-two-blocks-connected-via-connection-post ()
  ;; create instances
  (let* ((ws1 (g2-test-setup-create-workspace))
         (ws2 (g2-test-setup-create-workspace))
         (node1 (ab::make-frame 'ab::block))
         (node2 (ab::make-frame 'ab::block))
         (cp1 (ab::make-frame 'ab::connection-post))
         (cp2 (ab::make-frame 'ab::connection-post))
         (c1 nil)
         (c2 nil))
    
    ; take symbol from ab package, just in case
    (setf (ab::name-or-names-for-frame node1) 'ab::node1)
    (setf (ab::superblock? node1) ws1)
    (setf (ab::connections node1) (ab::make-connection-item-table))

    (setf (ab::name-or-names-for-frame cp1) 'ab::connection-post-a)
    (setf (ab::superblock? cp1) ws1)
    (setf (ab::connections cp1) (ab::make-connection-item-table))

    (setf (ab::name-or-names-for-frame node2) 'ab::node2)
    (setf (ab::superblock? node2) ws2)
    (setf (ab::connections node2) (ab::make-connection-item-table))

    (setf (ab::name-or-names-for-frame cp2) 'ab::connection-post-a)
    (setf (ab::superblock? cp2) ws2)
    (setf (ab::connections cp2) (ab::make-connection-item-table))

    (setf c1 (first (make-connection-between-two-objects node1 cp1)))
    (setf c2 (first (make-connection-between-two-objects node2 cp2)))

    (list node1 node2 ws1 ws2 cp1 cp2 c1 c2)))
