(in-package :tests)

(define-test test-rdf-string-for-refid-for-node
 (let
  ((test-xml-object (cons t 'ab::structure))
   (ab::traversing-xml-object-p t))
   (assert-eq nil
    ; this is a corrected example of mock. 
    ; Note that if call/return sequence is not as expected,
    ; it will incf "execution errors", not "failed" 
    ; only if embracing assert-eq does not hold, we get "failed" -- budden
    (mock::expect (
            (:call (ab::structure-slot-1 t 'ab::type nil) :return ('ab::test-value))
            (:call (ab::structure-slot-1 t 'ab::unit nil) :return ('ab::test-value))
            (:call (ab::structure-slot-1 t 'ab::value nil) :return ('ab::test-value))
            (:call (ab::structure-slot-1 t 'ab::attributes nil) :return ('ab::test-value))
            (:call (ab::GET-XML-FIXUPS test-xml-object 'ab::|rdf:resource| NIL) :return ('ab::symbol))
            ) :for
             (ab::rdf-string-for-refid-for-node 
              test-xml-object 
              nil 
              nil)
             ))))

(define-test test-start-with-w
  (assert-true
    (not (ab::start-with-w #w"" #w"g2:" 0 0 3)))
  (assert-true
    (not (ab::start-with-w #w"g2123" #w"g2:" 0 5 3)))
  (assert-true
    (ab::start-with-w  #w"g2:sa." #w"g2:" 0 6 3)))

(define-test test-symbol-from-rdf-symbol-name
  (let ((ab::count-of-interned-gensym-strings 0)
        (ab::memory-used-for-interned-gensym-strings 0))
    (let ((head-list (list #w"" #w"g2:" #w"g2m:"))
          (type-cons-list (list (cons 'ab::class #w"c.")
                                (cons 'ab::attribute #w"a.")
                                (cons 'ab::user-attribute #w"ua.")
                                (cons 'ab::qualified-attribute #w"uq.")
                                (cons 'ab::structure-attribute #w"sa.")))
          (attr-name-list (list #w"non-unicode" #w"直線接続123")))
            (loop for head in head-list do
              (loop for (type-symbol . type-name) in type-cons-list do
                (loop for attr-name in attr-name-list do
                  (let* ((rdf-name (ab::concatenate-wide-strings
                                     (ab::concatenate-wide-strings head type-name)
                                      attr-name))
                         (rdf-symbol (ab::intern-text-string-no-reclaim rdf-name)))
                        (ab::bind-symbol-to-rdf-symbol-name rdf-symbol rdf-name)
                        (multiple-value-bind (symbol target-type)
                          (ab::symbol-from-rdf-symbol-name rdf-symbol)
                          (assert-true (ab::eq symbol (ab::intern-text-string-no-reclaim attr-name)))
                          (assert-true (ab::eq target-type type-symbol))))))))))
