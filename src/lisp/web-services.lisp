;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module WEB-SERVICES - W3C Web Services for G2

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Doug Orleans



;;;; Introduction

;;; According to the World Wide Web Consortium (W3C) Web Services Glossary
;;; (http://www.w3.org/TR/ws-gloss/):

;;;  A Web service is a software system designed to support interoperable
;;;  machine-to-machine interaction over a network. It has an interface
;;;  described in a machine-processable format (specifically WSDL). Other
;;;  systems interact with the Web service in a manner prescribed by its
;;;  description using SOAP messages, typically conveyed using HTTP with an XML
;;;  serialization in conjunction with other Web-related standards.

;;; This module enables G2 to act as a Web service requester agent (aka client)
;;; and/or provider agent (aka server).


;;; The main interface to this module is through the following system procedures
;;; in g2web.kb:
;;;
;;;   g2-import-web-service-description
;;;   g2-import-web-service-description-from-xml-text
;;;   g2-invoke-web-service-operation
;;;   g2-send-soap-request
;;;   g2-send-web-request
;;;   g2-check-http-response-status-code
;;;   g2-read-http-entity-body
;;;   g2-start-http-server
;;;   g2-shutdown-http-server
;;;   g2-handle-http-request-as-soap
;;;
;;; This module also defines some system classes:
;;;
;;;   web-service-description
;;;   web-service
;;;   web-service-endpoint
;;;   web-service-http-binding
;;;   web-service-http-operation
;;;   web-service-soap-binding
;;;   web-service-soap-operation
;;;   web-service-interface
;;;   web-service-interface-operation
;;;   http-server
;;;
;;; These are all described in detail separately below.

;; TO DO: export WSDL document from local Web service
;; TO DO: "call across" syntax





;;;; References

;;; WSDL 1.1:               http://www.w3.org/TR/wsdl
;;; WSDL 2.0 Part 0:        http://www.w3.org/TR/wsdl20-primer/
;;; WSDL 2.0 Part 1:        http://www.w3.org/TR/wsdl20/
;;; WSDL 2.0 Part 2:        http://www.w3.org/TR/wsdl20-adjuncts/
;;; SOAP 1.1 and 1.2:       http://www.w3.org/TR/soap/
;;; HTTP 1.1:               http://www.w3.org/Protocols/rfc2616/
;;; WS-I Basic Profile 1.1: http://www.ws-i.org/Profiles/BasicProfile-1.1.html






;;;; URI/URL parsing and formatting

;;; URI syntax is specified by RFC 3896.
;;; http://www.gbiv.com/protocols/uri/rfc/rfc3986.html
;;;
;;; [<scheme>:][//[<userinfo>@]<host>[:<port>]]<path>[?<query>][#<fragment>]


;;; The structure `uri-reference' contains the parsed components of a URI
;;; reference.  The userinfo, host, query, and fragment components are text
;;; strings.  The scheme component is a symbol.  The port component is a
;;; nonnegative fixnum integer.  The path component is a gensym list of text
;;; strings.  Each component is nil if absent, except the path component is
;;; never absent (but it might be empty, i.e. a list with one empty string).

(def-structure (uri-reference
         (:constructor make-uri-reference
                   (uri-scheme uri-userinfo uri-host uri-port
                uri-path uri-query uri-fragment)))
  (uri-scheme      nil)
  (uri-userinfo    nil :reclaimer reclaim-if-text-string)
  (uri-host        nil :reclaimer reclaim-if-text-string)
  (uri-port        nil)
  (uri-path        nil :reclaimer reclaim-gensym-tree-with-text-strings)
  (uri-query       nil :reclaimer reclaim-if-text-string)
  (uri-fragment    nil :reclaimer reclaim-if-text-string))


;;; The function `parse-uri' parses a text-string as a URI reference, returning
;;; a new uri-reference structure instance.  Invalid percent encodings are left
;;; undecoded.  A port with more than 5 digits is left as part of the host.

(defun parse-uri (string)
  (let ((uri (make-uri-reference nil nil nil nil nil nil nil))
    (mark 0) (point 0) (end (text-string-length string)))
    (macrolet 
    ;; The macro `seek' looks for a character in the `find' text string,
    ;; starting at mark.  If one is found, t is returned.  If any characters
    ;; in the `avoid' text string are found first, or the end is reached,
    ;; nil is returned.  In either case, point is set to the position of the
    ;; found character (or the end position).
    ((seek (find &optional (avoid #w""))
       `(loop initially (setf point mark)
          while (<f point end)
          for char = (charw string point)
          when (position-in-text-string char ,find) return t
          when (position-in-text-string char ,avoid) return nil
          do (incff point)))
     ;; The macro `check' returns t if the given prefix appears next at
     ;; mark, in which case mark is advanced past it, or nil otherwise.
     (check (prefix)
       (let ((len (text-string-length prefix)))
         `(unless (<f (-f end mark) ,len)
        (loop for i below ,len for j from mark
              always (char=w (charw ,prefix i) (charw string j))
              finally (incff mark ,len)))))
      ;; The macro `decode' percent-decodes the substring between mark,
      ;; inclusive, and point, exclusive.  Mark is set to point.
     (decode ()
       `(twith-output-to-text-string
          (loop for i from mark below point for char = (charw string i) do
        (twrite-char
          (or (when (and (char=w char #.%\%) (>=f (-f point i) 2))
            (let ((d1 (digit-char-pw (charw string (+f i 1)) 16))
                  (d2 (digit-char-pw (charw string (+f i 2)) 16)))
              (when (and d1 d2) (incff i 2) (+f (ashf d1 4) d2))))
              char))
            finally (setf mark point)))))
      ;; Scheme component.  This is not percent-decoded, but is converted to
      ;; a symbol.
      (when (seek #w":" #w"/?#")
    (unless (zerop point) ;scheme must not be empty
      (let ((scheme-string (text-string-substring string mark point)))
        (upcase-text-string-in-place scheme-string)
        (setf (uri-scheme uri) (intern-text-string scheme-string)))
      (setf mark (1+f point))))
      ;; Authority components: userinfo, host, and port.
      (when (check #w"//")
    (when (seek #w"@" #w"/?#")
      (setf (uri-userinfo uri) (decode)) (incff mark))
    (seek #w"/?#")
    (let ((host-and-port-end point))
      ;; Scan backwards, accumulating the digits into the port number, until
      ;; a colon or non-digit is found, more than 5 digits are read, or mark
      ;; is reached.  Point is set to the end of the host component.
      (loop for port = nil then (+f (or port 0) (*f digit factor))
        for factor = 1 then (*f factor 10) until (>f factor 100000)
        for i from (1-f point) downto mark
        for char = (charw string i)
        when (char=w char #.%\:)
          do (setf (uri-port uri) port)
             (setf point i) (loop-finish)
        for digit = (digit-char-pw char) while digit)
      ;; TO DO: parse non-registry host address?
      (setf (uri-host uri) (decode))
      (setf mark host-and-port-end)))
      ;; Path component.
      (setf (uri-path uri)
        (loop for more-segments-p = (seek #w"/" #w"?#")
          collect (decode) using gensym-cons
          while more-segments-p do (incff mark))) ;skip the slash
      ;; Query component.
      (when (check #w"?") (seek #w"#") (setf (uri-query uri) (decode)))
      ;; Fragment component.
      (when (check #w"#") (setf point end) (setf (uri-fragment uri) (decode))))
    uri))


;;; The function `uri-path-is-empty-p' returns true iff the path component of
;;; the URI reference is empty, i.e. a list with one empty string.

(defun-simple uri-path-is-empty-p (uri)
  (and (null (cdr (uri-path uri)))
       (=f 0 (text-string-length (car (uri-path uri))))))


;;; The function `twrite-percent-encoded-wide-character' percent-encodes a wide
;;; character and writes the resulting three characters (percent followed by two
;;; uppercase hex digits) to the current twriting context.  The wide character
;;; code must be 255 or lower.

(defun-void twrite-percent-encoded-wide-character (char)
  (multiple-value-bind (hex1 hex2) (floorf (char-codew char) 16)
    (twrite-char #\%)
    (twrite-char (digit-char hex1 16))
    (twrite-char (digit-char hex2 16))))


;;; The macro `wide-character-safe-for-uri-p' returns t iff the given wide
;;; character is safe for including in a URI without being percent-encoded.  An
;;; optional literal sequence may be provided containing extra characters to be
;;; considered safe, in addition to those in the unreserved and sub-delims
;;; categories defined by RFC 3896.

(defmacro wide-character-safe-for-uri-p (char &optional safe-chars)
  (let ((allowed-chars (concatenate 'list "-._~!$&'()*+,;=" safe-chars)))
    `(let ((char ,char))
       (fixnum-case (char-codew char)
     (,(mapcar #'char-code allowed-chars) t)
     (t (alphanumericpw char))))))


;;; The macro `twrite-percent-encoded-text-string' writes a text string to the
;;; current twriting context, percent-encoding characters as needed.  An
;;; optional literal sequence may be provided containing extra chars to be
;;; considered safe, in addition to those in the unreserved and sub-delims
;;; categories defined by RFC 3896.

(defmacro twrite-percent-encoded-text-string (text-string &optional safe-chars)
  `(loop with s = ,text-string
     for i below (text-string-length s)
     for char = (charw s i)
     do (if (wide-character-safe-for-uri-p char ,safe-chars)
        (twrite-char char)
        (twrite-percent-encoded-wide-character char))))


;;; The function `twrite-uri-path' writes a URI path (a list of segments) to the
;;; current twriting context.  Characters are percent-encoded only if needed to
;;; prevent ambiguity.

(defun-void twrite-uri-path (path)
  (loop for segment in path for slash-p = nil then t do
    (when slash-p (twrite-string "/"))
    (twrite-percent-encoded-text-string segment ":@")))


;;; The function `twrite-uri' writes a URI reference structure to the current
;;; twriting context.  Characters are percent-encoded only if needed to prevent
;;; ambiguity.

(defun-void twrite-uri (uri)
  (when (uri-scheme uri) (tformat "~(~a~):" (uri-scheme uri)))
  (when (uri-host uri)
    (twrite-string "//")
    (when (uri-userinfo uri)
      (twrite-percent-encoded-text-string (uri-userinfo uri) ":")
      (twrite-string "@"))
    (twrite-percent-encoded-text-string (uri-host uri))
    (when (uri-port uri) (tformat ":~d" (uri-port uri))))
  (twrite-uri-path (uri-path uri))
  (when (uri-query uri)
    (twrite-string "?")
    (twrite-percent-encoded-text-string (uri-query uri) ":@/?"))
  (when (uri-fragment uri)
    (twrite-string "#")
    (twrite-percent-encoded-text-string (uri-fragment uri) ":@/?")))


;;; The slot type `uri' is used for slots that contain text strings that are
;;; URIs.  Currently no parsing or validation is done at the slot level.  This
;;; slot type is also allowed to be NIL when an item is first created (which is
;;; displayed as a blank table entry), but the user can only enter a text in the
;;; slot value editor (and can only conclude a text into the slot).

(def-grammar-category uri ()
  (whole-string))

(def-slot-value-writer uri (uri)
  (when uri
    (let ((write-strings-parsably? t))
      (twrite-string uri))))




;;;; HTTP form submission

;;; HTTP form submission is used by the HTTP GET/POST binding extension to WSDL.
;;;
;;; Form submission is not actually part of the HTTP spec, it comes from HTML:
;;; http://www.w3.org/TR/html401/interact/forms.html#submit-format


;;; The function `urlencode-www-form' encodes a form data set (an evaluation
;;; structure whose attribute values are evaluation texts) into a text string
;;; according to the rules for the application/x-www-form-urlencoded content
;;; type:
;;;
;;; 1. Space characters are replaced by `+', and then reserved characters are
;;;    escaped as described in RFC 1738 (URL), section 2.2: Non-alphanumeric
;;;    characters are replaced by `%HH', a percent sign and two hexadecimal
;;;    digits representing the ASCII code of the character. Line breaks are
;;;    represented as "CR LF" pairs (i.e., `%0D%0A').
;;; 2. The name is separated from the value by `=' and name/value pairs are
;;;    separated from each other by `&'.

(defun-simple twrite-urlencoded-text-string (string)
  (loop for i below (text-string-length string)
    for char = (charw string i) do
    (cond ((char=w char #.%space)
       (twrite-char #\+))
      ((wide-character-safe-for-uri-p char)
       (twrite-char char))

      ;; TO DO: This is probably wrong...  Wide characters beyond 0xFF
      ;; shouldn't be here at all.  And maybe bare newlines should be
      ;; converted to CRLF.  Or maybe not?
      ((char=w char #.%line-separator)
       (twrite-percent-encoded-wide-character #.%return)
       (twrite-percent-encoded-wide-character #.%newline))
      (t
       (twrite-percent-encoded-wide-character char)))))

(defun-simple urlencode-www-form (data-set)
  (twith-output-to-text-string
    (loop for first = t then nil
      for (name . value) being each evaluation-structure-pair of data-set do
      (unless first (twrite-char #\&))
      (twrite-urlencoded-text-string (symbol-name-text-string name))
      (twrite-char #\=)
      (twrite-urlencoded-text-string (evaluation-text-value value)))))


(defun twrite-crlf ()
  (twrite-char #.%return)
  (twrite-char #.%newline))


;; TO DO: multipart/form-data




;;;; HTTP date formatting

;;; HTTP uses RFC 1123 for date formats (an update of RFC 822).
;;; http://rfc.net/rfc1123.html
;;; http://www.w3.org/Protocols/rfc822/


;;; The function `twrite-two-digit-fixnum' writes a fixnum to the current
;;; twriting context, with a leading zero if needed.

(defun-void twrite-two-digit-fixnum (n)
  (tformat "~a~a" (if (<f n 10) "0" "") n))


;;; The function `twrite-http-date' writes the current date/time to the current
;;; twriting context in the HTTP-date format.
;;;
;;; 3.3.1: All HTTP date/time stamps MUST be represented in Greenwich Mean Time
;;; (GMT), without exception.  HTTP-date is case sensitive and MUST NOT include
;;; additional LWS beyond that specifically included as SP in the grammar.

(defun-void twrite-http-date ()
  (with-temporary-gensym-float-creation twrite-http-date
    (let* ((local-time-in-seconds (gensym-get-unix-time))
       (adjustment-in-hours
         (if (daylight-saving-time-p-macro)
         (1-f (time-zone-in-hours))
         (time-zone-in-hours)))
       (gmt-time-in-seconds
         (+ local-time-in-seconds (* 60 60 adjustment-in-hours))))
      (multiple-value-bind (second minute hour date month year day)
      (gensym-decode-unix-time gmt-time-in-seconds)
    (tformat "~a, " (select-day-of-week-string day))
    (twrite-two-digit-fixnum date)
    (tformat " ~a ~a " (select-month-string month) year)
    (twrite-two-digit-fixnum hour)
    (tformat ":")
    (twrite-two-digit-fixnum minute)
    (tformat ":")
    (twrite-two-digit-fixnum second)
    (tformat " GMT")))))





;;;; HTTP status codes

;;; The function `reason-phrase-for-http-status-code' returns a constant gensym
;;; string containing the reason phrase recommended by RFC 2616 section 6.1.1
;;; for the provided status code (a fixnum).

(defun-simple reason-phrase-for-http-status-code (code)
  (fixnum-case code
    (100 "Continue")
    (101 "Switching Protocols")
    (200 "OK")
    (201 "Created")
    (202 "Accepted")
    (203 "Non-Authoritative Information")
    (204 "No Content")
    (205 "Reset Content")
    (206 "Partial Content")
    (300 "Multiple Choices")
    (301 "Moved Permanently")
    (302 "Found")
    (303 "See Other")
    (304 "Not Modified")
    (305 "Use Proxy")
    (307 "Temporary Redirect")
    (400 "Bad Request")
    (401 "Unauthorized")
    (402 "Payment Required")
    (403 "Forbidden")
    (404 "Not Found")
    (405 "Method Not Allowed")
    (406 "Not Acceptable")
    (407 "Proxy Authentication Required")
    (408 "Request Time-out")
    (409 "Conflict")
    (410 "Gone")
    (411 "Length Required")
    (412 "Precondition Failed")
    (413 "Request Entity Too Large")
    (414 "Request-URI Too Large")
    (415 "Unsupported Media Type")
    (416 "Requested range not satisfiable")
    (417 "Expectation Failed")
    (500 "Internal Server Error")
    (501 "Not Implemented")
    (502 "Bad Gateway")
    (503 "Service Unavailable")
    (504 "Gateway Time-out")
    (505 "HTTP Version not supported")
    (otherwise "Unknown Status Code")))


;;; g2-check-http-response-status-code(response: structure) = ()
;;;
;;; The system procedure `g2-check-http-response-status-code' examines an HTTP
;;; response structure and signals an error if the status code indicates an HTTP
;;; error.

(def-concept g2-check-http-response-status-code)




;;;; HTTP request/response formatting

;;; The function `format-http-request' pre-processes a HTTP request message
;;; being sent to a given address.  The address is a URI reference structure.
;;; The request is an evaluation structure containing the following optional
;;; attributes:
;;;
;;;   method: symbol (such as GET or POST)
;;;   headers: structure
;;;   entity: text or structure
;;;
;;; Each attribute of the headers structure will be included in the request as
;;; a HTTP header.  If the entity attribute is a structure, it is considered a
;;; form data set, which will be encoded using the
;;; application/x-www-form-urlencoded MIME type; otherwise the entity attribute
;;; is assumed to have already been encoded (into 8-bit characters) and will be
;;; sent as-is as the body of the request (this is only valid if the method is
;;; POST).
;;;
;;; This function returns an evaluation structure containing the following
;;; attributes:
;;;
;;;   scheme: symbol (the symbol HTTP)
;;;   host: text
;;;   port: integer
;;;   message: text

(def-type-parameter http-request-type
    (structure ((method (member get post))
        (headers (structure))
        (entity (or text (structure))))))

(defun format-http-request (address request)
  (check-type-or-stack-error request http-request-type)
  (let ((method (evaluation-structure-slot request 'method
                       (make-evaluation-symbol 'get)))
    (headers? (evaluation-structure-slot request 'headers))
    (entity? (evaluation-structure-slot request 'entity))
    (query? (when (uri-query address)
          (twith-output-to-text-string
            (twrite-percent-encoded-text-string
              (uri-query address)))))
    content-type? message-body?)

    ;; Figure out where to put the entity (if any).
    (case (evaluation-symbol-symbol method)
      (get (when (evaluation-structure-p entity?)
         (reclaim-if-text-string query?)
         (setq query? (urlencode-www-form entity?))))
      (post (cond ((evaluation-structure-p entity?)
           (setq message-body? (urlencode-www-form entity?))
           (setq content-type? "application/x-www-form-urlencoded"))
          (t
           (setq message-body? (twith-output-to-text-string
                     (when entity? (twrite entity?))))))))

    (allocate-evaluation-structure-inline
      'scheme (make-evaluation-symbol (uri-scheme address))
      'host (make-evaluation-text (uri-host address))
      'port (make-evaluation-integer (or (uri-port address) 80))
      'message
      (make-evaluation-text-reclaiming-argument
    (twith-output-to-text-string
      (tformat "~a " method)
      (if (uri-path-is-empty-p address)
          ;; 5.1.2: Note that the absolute path cannot be empty; if none is
          ;; present in the original URI, it MUST be given as "/" (the
          ;; server root).
          (twrite-string "/")
          (twrite-uri-path (uri-path address)))
      (when query?
        (tformat "?~a" query?)
        (reclaim-text-string query?))
      (tformat " HTTP/1.1")
      (twrite-crlf)

      ;; 14.10: HTTP/1.1 applications that do not support persistent
      ;; connections MUST include the "close" connection option in
      ;; every message.
      (tformat "Connection: close")
      (twrite-crlf)

      ;; 14.23: A client MUST include a Host header field in all
      ;; HTTP/1.1 request messages.
      (tformat "Host: ~a" (uri-host address))
      (when (uri-port address) (tformat ":~a" (uri-port address)))
      (twrite-crlf)

      ;; 4.4: For compatibility with HTTP/1.0 applications, HTTP/1.1
      ;; requests containing a message-body MUST include a valid
      ;; Content-Length header field unless the server is known to be
      ;; HTTP/1.1 compliant.
      (when message-body?
        (tformat "Content-Length: ~a" (text-string-length message-body?))
        (twrite-crlf))

      (when content-type?
        (tformat "Content-Type: ~a" content-type?)
        (twrite-crlf))

      (when headers?
        (loop for (name . value) being
          each evaluation-structure-pair of headers? do
          (tformat "~a: ~a" name value)
          (twrite-crlf)))

      (twrite-crlf)

      ;; TO DO: encode message body according to Transfer-Encoding header
      (when message-body?
        (twrite message-body?)
        (reclaim-text-string message-body?)))))))


;;; The system procedure function `g2-format-http-response' converts a HTTP
;;; response from a structure to a text.  The response structure contains the
;;; following optional fields:
;;;
;;;   status-code: integer
;;;   reason-phrase: text
;;;   headers: structure
;;;   entity: text
;;;   user-data: item-or-value
;;;
;;; The status-code attribute defaults to 200 ("OK").  The reason-phrase
;;; attribute defaults to the recommended reason phrase from RFC 2616 for the
;;; given status code.  Each attribute of the headers structure will be included
;;; in the response as a HTTP header.

(def-type-parameter http-response-type
    (structure ((status-code integer)
        (reason-phrase text)
        (headers (structure))
        (entity text)
        (entity-producer (class procedure))
        (user-data item-or-datum))))

;;; Begin of Gensym-364-JIRA-111-RFP-12633-Memory leak in GWEB module fix.
;;; Commented as it has a memory leak
;;; The modified macroexpaned version is used (located just after the commented
;;; original one). The orginal definition is left for the documentation purpose.
#|(defun-for-system-procedure g2-format-http-response ((response structure))
  (declare (values text))
  (check-type-or-stack-error response http-response-type)
  (twith-output-to-text-string
    (let* ((status-code? (evaluation-structure-slot response 'status-code))
       (status-code
         (if status-code? (evaluation-integer-value status-code?) 200))
       (reason-phrase? (evaluation-structure-slot response 'reason-phrase))
       (reason-phrase
         (if reason-phrase?
         (evaluation-text-value reason-phrase?)
         (reason-phrase-for-http-status-code status-code)))
       (headers? (evaluation-structure-slot response 'headers))
       (entity? (evaluation-structure-slot response 'entity)))

      (tformat "HTTP/1.1 ~a ~a" status-code reason-phrase)
      (twrite-crlf)

      ;; 14.10: HTTP/1.1 applications that do not support persistent connections
      ;; MUST include the "close" connection option in every message.
      (tformat "Connection: close")
      (twrite-crlf)

      ;; 14.18: Origin servers MUST include a Date header field in all responses
      (tformat "Date: ")
      (twrite-http-date)
      (twrite-crlf)

      (when headers?
    (loop for (name . value) being
          each evaluation-structure-pair of headers? do
      (tformat "~a: ~a" name value)
      (twrite-crlf)))
      (twrite-crlf)

      (when entity? (twrite entity?)))

    (reclaim-evaluation-structure response)))
|#

;;; Macroexpanded version of G2-FORMAT-HTTP-RESPONSE
;;; For the original one look above.
(DECLARE-SYSTEM-PROCEDURE-FUNCTION G2-FORMAT-HTTP-RESPONSE NIL
                                    ((RESPONSE STRUCTURE)) ((VALUE-1 TEXT)))
 (DEFUN G2-FORMAT-HTTP-RESPONSE (RESPONSE-AS-EVALUATION-VALUE)
        (LET*
         ((RESPONSE (IDENTITY RESPONSE-AS-EVALUATION-VALUE)) (VALUE-1 NIL))
         (MULTIPLE-VALUE-SETQ (VALUE-1)
           (PROGN
            (CHECK-TYPE-OR-STACK-ERROR RESPONSE HTTP-RESPONSE-TYPE)
            (TWITH-OUTPUT-TO-TEXT-STRING
             (LET*
              ((STATUS-CODE? (EVALUATION-STRUCTURE-SLOT RESPONSE 'STATUS-CODE))
               (STATUS-CODE
                (IF STATUS-CODE? (EVALUATION-INTEGER-VALUE STATUS-CODE?) 200))
               (REASON-PHRASE?
                (EVALUATION-STRUCTURE-SLOT RESPONSE 'REASON-PHRASE))
               (REASON-PHRASE
                (IF REASON-PHRASE? (EVALUATION-TEXT-VALUE REASON-PHRASE?)
                    (REASON-PHRASE-FOR-HTTP-STATUS-CODE STATUS-CODE)))
               (HEADERS? (EVALUATION-STRUCTURE-SLOT RESPONSE 'HEADERS))
               (ENTITY? (EVALUATION-STRUCTURE-SLOT RESPONSE 'ENTITY)))
              (TFORMAT "HTTP/1.1 ~a ~a" STATUS-CODE REASON-PHRASE)
              (TWRITE-CRLF) (TFORMAT "Connection: close") (TWRITE-CRLF)
              (TFORMAT "Date: ") (TWRITE-HTTP-DATE) (TWRITE-CRLF)
              (WHEN HEADERS?
                (LOOP FOR (NAME . VALUE) BEING EACH EVALUATION-STRUCTURE-PAIR
                      OF HEADERS? DO (TFORMAT "~a: ~a" NAME VALUE)
                      (TWRITE-CRLF)))
              (TWRITE-CRLF) (WHEN ENTITY? (TWRITE ENTITY?)))
             (RECLAIM-EVALUATION-STRUCTURE RESPONSE))))
         (IDENTITY RESPONSE-AS-EVALUATION-VALUE)
          ;;; Memory leak is caused by creating a copy of value-1 without
          ;;; being reclaimed. Indeed, we don't need a one more copy at all.
          ;;; (VALUES (MAKE-EVALUATION-TEXT VALUE-1))
         (VALUES VALUE-1)))
;;; End of Gensym-364-JIRA-111-RFP-12633-Memory leak in GWEB module fix
;;; by SoftServe

;;;; HTTP request/response parsing

;;; The function `parse-http-request-line' parses the first line (text string)
;;; of a HTTP request message, returning three values: the method (a symbol),
;;; the request-URI (a text string), and the HTTP-version (a text string).

(defun parse-http-request-line (line)
  (let* ((sp1? (position-in-text-string #.%space line))
     (method (text-string-substring line 0 sp1?))
     (sp2? (when sp1?
         (position-in-text-string-tail #.%space line (1+f sp1?))))
     (uri (if sp1?
          (text-string-substring line (1+f sp1?) sp2?)
          (copy-text-string "")))
     (version (if sp2?
              (text-string-substring line (1+f sp2?) nil)
              (copy-text-string ""))))
    (upcase-text-string-in-place method)
    (values (intern-text-string method) uri version)))


;;; The function `parse-http-status-line' parses the first line (text string) of
;;; a HTTP response message, returning three values: the HTTP-version (a text
;;; string), the status-code (a three-digit fixnum integer, or -1 if this can't
;;; be parsed), and the reason-phrase (a text string).

(defun parse-http-status-line (line)
  (let* ((sp1? (position-in-text-string #.%space line))
     (version (text-string-substring line 0 sp1?))
     (sp2? (when sp1?
         (position-in-text-string-tail #.%space line (1+f sp1?))))
     (status-code
       (or (when sp1?
         (read-positive-fixnum-from-string
           line (1+f sp1?) (or sp2? (text-string-length line))))
           -1))
     (reason-phrase
       (if sp2?
           (text-string-substring line (1+f sp2?) nil)
           (copy-text-string ""))))
    (values version status-code reason-phrase)))



;;; The function `parse-http-message-header' parses a text string header line
;;; (name and value) onto a reversed eval-property-list of headers already
;;; parsed, which is returned.  If the header line is a continuation, it is
;;; concatenated onto the value of the previous header and the list is returned.
;;; Each header name is a symbol and each header value is an evaluation text.

(defun parse-http-message-header (line headers)
  (let ((first-char (charw line 0)))
    (when (or (char=w first-char #.%space)
          (char=w first-char #.%tab))
      ;; A line beginning with linear white space is a continuation of the
      ;; previous field value.  Replace the LWS with a single space character.
      (when headers
    ;; TO DO: error if headers is empty
    (let ((left (car headers))
          (right (text-string-trim '(#.%space #.%tab) line)))
      (setf (car headers)
        (make-evaluation-text-reclaiming-argument
          (tformat-text-string "~a ~a" left right)))
      (reclaim-evaluation-text left)
      (reclaim-text-string right)))
      (return-from parse-http-message-header headers)))

  (let ((separator (position-in-text-string #.%\: line)))
    (unless separator
      ;; TO DO: this is an error!
      (return-from parse-http-message-header headers))

    (let ((field-name (text-string-substring line 0 separator))
      (field-value (text-string-substring line (1+f separator) nil)))
      (upcase-text-string-in-place field-name)
      (nconc
    (eval-list
      (make-evaluation-text-reclaiming-argument
        (prog1 (text-string-trim '(#.%space #.%tab) field-value)
          (reclaim-text-string field-value)))
      (intern-text-string field-name))
    headers))))



;;; The function `parse-http-message-headers' takes an evaluation sequence of
;;; HTTP message header lines (evaluation texts) and parses them into an
;;; evaluation structure.  Each header field value is an evaluation text.

(defun parse-http-message-headers (header-lines)
  (loop for i from 0 below (evaluation-sequence-length header-lines)
    for line = (evaluation-sequence-aref header-lines i)
    for headers = (parse-http-message-header line headers)
    finally (return (allocate-evaluation-structure (nreverse headers)))))



;;; The function `http-message-length' determines the transfer-length of a HTTP
;;; message given its headers as an evaluation structure, according to RFC 2616
;;; section 4.4.  A return value of -1 indicates that the message body will be
;;; terminated by closing the connection.

(def-concept transfer-length)
(defun http-message-length (headers)
  ;; TO DO: check Transfer-Encoding header
  (let ((length-text? (evaluation-structure-slot headers 'Content-Length)))
    (or (when length-text?
      (let ((length (evaluation-text-value length-text?)))
        ;; TO DO: error if Content-Length header is malformed
        (read-positive-fixnum-from-string
          length 0 (text-string-length length))))
    -1)))



;;; The system procedure function `g2-parse-http-request' is used by
;;; the system procedure `g2-serve-http-connection' to parse the start-line and
;;; header-lines of a HTTP request message.  It returns a request structure,
;;; which has the following attributes:
;;;
;;;   method: symbol
;;;   request-uri: text
;;;   http-version: text
;;;   path: sequence of texts
;;;   query: text or structure (optional)
;;;   headers: structure
;;;   transfer-length: integer
;;;
;;; The path is a sequence of path segments in the request-uri.  Since the
;;; request-uri is not allowed to be a relative path, the path sequence begins
;;; with the first segment after the leading slash.  If there is no path
;;; (i.e. the request-uri is an absolute URI with no slashes after the host)
;;; then the path sequence is empty.  If the path is just "/", then the path
;;; sequence contains one empty text.
;;;
;;; [TO DO: query]

;; TO DO: signal parse errors, catch them and return 400 Bad Request.
;; TO DO: check version, maybe return 505 HTTP Version Not Supported.

(defun-for-system-procedure g2-parse-http-request
    ((start-line text) (header-lines sequence))
  (declare (values structure))
  (multiple-value-bind (method request-uri http-version)
      (parse-http-request-line start-line)
    (let ((uri (parse-uri request-uri))
      (headers (parse-http-message-headers header-lines)))
      (reclaim-evaluation-sequence header-lines)
      (allocate-evaluation-structure
    (nconc
      (eval-list
        'method
        (make-evaluation-symbol method)
        'request-uri
        (make-evaluation-text-reclaiming-argument request-uri)
        'http-version
        ;; TO DO: parse the HTTP version into major and minor
        (make-evaluation-text-reclaiming-argument http-version)
        'path
        (allocate-evaluation-sequence
          (loop for segment in (cdr (uri-path uri))
            collect (make-evaluation-text segment) using eval-cons)))
      (prog1 (when (uri-query uri)
           (eval-list
             'query
             ;; TO DO: parse urlencoded query
             (make-evaluation-text (uri-query uri))))
        (reclaim-uri-reference uri))
      (eval-list
        'headers
        headers
        'transfer-length
        (make-evaluation-integer (http-message-length headers))))))))



;;; The system procedure function `g2-parse-http-response' is used by
;;; the system procedure `g2-send-web-request' to parse the start-line and
;;; header-lines of a HTTP response message.  It returns a response structure,
;;; which has the following attributes:
;;;
;;;   http-version: text (e.g. "HTTP/1.1")
;;;   status-code: integer
;;;   reason-phrase: text
;;;   headers: structure
;;;   transfer-length: integer

(defun-for-system-procedure g2-parse-http-response
    ((start-line text) (header-lines sequence))
  (declare (values structure))
  (multiple-value-bind (version code reason)
      (parse-http-status-line start-line)
    (let ((headers (parse-http-message-headers header-lines)))
      (reclaim-evaluation-sequence header-lines)
      (allocate-evaluation-structure-inline
    'http-version
    ;; TO DO: parse the HTTP version into major and minor
    (make-evaluation-text-reclaiming-argument version)
    'status-code
    (make-evaluation-integer code)
    'reason-phrase
    (make-evaluation-text-reclaiming-argument reason)
    'headers
    headers
    'transfer-length
    (make-evaluation-integer (http-message-length headers))))))





;;; The function `read-positive-hexadecimal-fixnum-from-string' reads a
;;; hexadecimal number from a text string (between indices start and end) and
;;; returns two values, the number (or nil if the number is too large for a
;;; fixnum) and the index of the first character after the value.

;; TO DO: merge this with read-positive-fixnum-from-string, or at least move
;; this to UTILITIES3.

(defconstant most-positive-fixnum-floor-16 (floorf most-positive-fixnum 16))

(defun read-positive-hexadecimal-fixnum-from-string (string start end)
  (loop with num = 0
    for i from start below end
    for digit = (digit-char-pw (charw string i) 16)
    while digit
    when (>f num most-positive-fixnum-floor-16)
      return (values nil i)
    do (setq num (+f (*f num 16) digit))
    finally (return (values num i))))


;;; g2-read-http-entity-body(http-message: structure) = (text)
;;;
;;; The system procedure `g2-read-http-entity-body' reads the entity-body of an
;;; HTTP message from an http-message structure returned by
;;; `g2-send-web-request'.  If the message has no body, an empty text is
;;; returned.  In either case, after this system procedure returns, the HTTP
;;; connection will have been closed.

(def-concept g2-read-http-entity-body)


;;; The system procedure function `g2-parse-http-chunk-header' is used by
;;; `g2-read-http-entity-body' to parse the chunk header of a chunk from a
;;; Chunked-Body, i.e. the message-body of an HTTP message whose
;;; transfer-codings includes "chunked".  The chunk header (an evaluation text)
;;; consists of the chunk-size in hexadecimal and an optional chunk-extension
;;; prefixed by a semicolon, as defined by RFC 2616:
;;;
;;; http://www.w3.org/Protocols/rfc2616/rfc2616-sec3.html#sec3.6.1
;;;
;;; This function returns two values, the chunk-size as an integer and a
;;; structure containing the extension names and values.

;; Currently the chunk extension is ignored and an empty structure is always
;; returned.
;; TO DO: implement chunk-extension parsing

(defun-for-system-procedure g2-parse-http-chunk-header ((header text))
  (declare (values integer structure))
  (let ((len (text-string-length header)))
    (multiple-value-bind (size i)
    (read-positive-hexadecimal-fixnum-from-string header 0 len)
      (unless size
    (stack-error
      cached-top-of-stack
      "HTTP chunk size is too large in header: ~a" header))
      (unless (or (=f i len) (and (>f i 0) (char=w (charw header i) #.%\;)))
    (stack-error
      cached-top-of-stack
      "Failed to parse HTTP chunk header: ~a" header))
      (values size (allocate-evaluation-structure nil)))))





;;;; HTTP server class


;;; The class `http-server'.  Instances of this class can be passed to the
;;; system procedures `g2-http-listen' and `g2-shutdown-http-server'.

(def-class (http-server object)

  ;; The slot `http-server-port' holds the current TCP port number that the
  ;; server is listening on, or NIL if it is not currently listening.  This slot
  ;; is read-only.
  (http-server-port nil (type http-server-port) not-user-editable do-not-save)

  ;; The slot `http-server-dispatch' holds a symbol naming a G2 procedure.  This
  ;; procedure should have the following signature:
  ;;
  ;;   dispatch(server: class http-server, request: structure) = (structure)
  ;;
  ;; For each HTTP request that is received by `g2-http-listen', this procedure
  ;; is called with the server and a request structure.  The request structure
  ;; has the same attributes as the structure returned by the system procedure
  ;; function `g2-parse-http-request', plus optionally an additional
  ;; "entity" text attribute.  The dispatch procedure should return a response
  ;; structure suitable for passing to the system procedure function
  ;; `g2-format-http-response'.  After the response headers are written to the
  ;; HTTP connection, if the response structure includes an "entity-producer"
  ;; attribute, its value is repeatedly called with the response structure, and
  ;; each return value (a sequence) is written to the HTTP connection (with
  ;; g2-tcp-write-bytes).  An empty sequence signals the end of the entity.
  ;;
  ;; The user may change this slot while a server is running-- each incoming
  ;; request goes to the current dispatch procedure.  If this slot is NIL, or
  ;; does not name an existing procedure, all requests will receive a generic
  ;; "404 not found" response.
  (http-server-dispatch nil (type procedure-name?))

  ;; The slot `http-server-listener' holds the TCP listener socket object, so
  ;; that it can be closed by `g2-shutdown-http-server'.  This slot is not user
  ;; visible.
  (http-server-listener nil not-user-editable do-not-save)

  ;; The slot `http-server-invocation' holds the procedure invocation for the
  ;; g2-http-listen procedure, so that it can be aborted by
  ;; `g2-shutdown-http-server'.  This slot is not user visible.
  (http-server-invocation nil not-user-editable do-not-save)

  )



;;; The text representation of the slot type `http-server-port' is either the
;;; symbol NONE or a positive integer.

(def-grammar-category http-server-port ()
  ('none nil)
  (positive-integer))

(def-slot-value-writer http-server-port (value)
  (twrite (or value 'none)))

;;; The evaluation-value representation of the slot-type `http-server-port' is
;;; either no value or an evaluation integer.

(define-category-evaluator-interface (http-server-port :access read)
    (or (no-item) integer)
  ((get-form (slot-value))
   (when slot-value (make-evaluation-integer slot-value))))



;;; The function `notify-http-servers-of-g2-reset' is called whenever the system
;;; is reset.  It clears the transient slots on all http-server instances.

(defun-void notify-http-servers-of-g2-reset ()
  (loop for server being each class-instance of 'http-server do
    (change-slot-value server 'http-server-port nil)
    (change-slot-value server 'http-server-listener nil)
    (change-slot-value server 'http-server-invocation nil)))




;;;; HTTP server system procedures


;;; g2-start-http-server(server: class http-server, port: integer) = ()
;;;
;;; The system procedure `g2-start-http-server' starts a task that listens on
;;; the given TCP port number for HTTP 1.1 requests and passes them to the
;;; server's dispatch procedure.  The http-server-port attribute is set to the
;;; port number.  If the server is already currently listening, it is shut down
;;; first.  The listener task can be terminated using the system procedure
;;; `g2-shutdown-http-server'.

(def-concept g2-start-http-server)



;;; g2-http-listen(server: class http-server, port: integer) = ()
;;;
;;; The system procedure `g2-http-listen' is an auxiliary procedure that is run
;;; asynchronously by `g2-start-http-server' with the "start" action.  The cap
;;; takes care of making the listener socket, and also passes in the current
;;; procedure invocation.  It then goes into a loop, calling
;;; `g2-serve-http-connection' for each connection.

(defun-for-system-procedure g2-http-listen ((server item) (port integer)
                        (socket item) (invocation item))
  (declare (values))
  (change-slot-value server 'http-server-port port)
  (change-slot-value server 'http-server-listener socket)
  (change-slot-value server 'http-server-invocation invocation))
    


;;; g2-serve-http-connection(server: class http-server,
;;;                          connection: item-or-value) = ()
;;;
;;; The system procedure `g2-serve-http-connection' is an auxiliary procedure
;;; called by `g2-http-listen' for each connection that is returned by
;;; `g2-tcp-accept' on the server's listener socket.  It makes system calls to
;;; `g2-parse-http-request' and `g2-format-http-response', described
;;; above.  In between it calls the server's dispatch procedure (and the
;;; response entity-producer, if any), catching any errors and turning them into
;;; a 500 Internal Server Error response.  If the server dispatch procedure does
;;; not exist, a 404 Not Found response is sent.

(def-concept g2-serve-http-connection)



;;; g2-shutdown-http-server(server: class http-server) = ()
;;;
;;; The system procedure `g2-shutdown-http-server' stops the listener task of an
;;; HTTP server.  The http-server-port attribute is set to NONE.  This does
;;; nothing if the server is not currently listening.

;; The system procedure cap gets the listener socket and procedure invocation
;; from this system call and then takes care of aborting the invocation and
;; closing the socket.

(defun-for-system-procedure g2-shutdown-http-server ((server item))
  (declare (values item item))
  (change-slot-value server 'http-server-port nil)
  (values (http-server-listener server)
      (http-server-invocation server)))
  






;;;; Web client system pocedures

;;; g2-send-web-request(URL: text, request: structure) = (structure)
;;;
;;; The system procedure `g2-send-web-request' sends a request to a Web
;;; server at the given URL, returning the response when it arrives.  The form
;;; of the request structure and the returned response structure depend on the
;;; URL scheme.  Currently, only HTTP URLs are supported.  See the documentation
;;; for the functions `format-http-request' and `g2-parse-http-response',
;;; respectively.  In addition, if the HTTP response has an entity (i.e. if the
;;; message has a body), then the response structure includes a CONNECTION
;;; attribute which is a g2-socket instance.  The caller is responsible for
;;; closing this connection (with the g2-tcp-close system procedure).
;;;


(def-concept g2-send-web-request)


;;; The system procedure function `g2-format-web-request' preprocesses a
;;; Web request message structure by converting it to text according to the URL
;;; scheme.  The returned structure has the following attributes:
;;;
;;;   scheme: symbol
;;;   host: text
;;;   port: integer
;;;   message: text

(defun-allowing-unwind-for-system-procedure g2-format-web-request
    ((url text) (request structure))
  (declare (values structure))
  (let ((address (parse-uri url)))
    (unwind-protect
     (case (uri-scheme address)
       (http (format-http-request address request))
       ;; ...other schemes go here, e.g. https, ftp, mailto, file?

       ((nil) (stack-error cached-top-of-stack "URL has no scheme: ~a" url))
       (t (stack-error cached-top-of-stack "Unknown URL scheme: ~a"
               (uri-scheme address))))
      (reclaim-uri-reference address)
      (reclaim-evaluation-structure request))))





;;;; XML evaluation values

;;; An `XML element evaluation value' is an evaluation structure representing an
;;; XML element.  It has the following attributes:
;;;
;;;   tag-name: text
;;;   attributes: structure
;;;   children: sequence
;;;
;;; The `tag-name' attribute is required, while the others are optional.  The
;;; attribute values of the `attributes' structure are evaluation texts, and
;;; their names use the standard correspondence between XML names and G2
;;; symbols, e.g. "fooBar" <=> FOO-BAR.  See the DOM module for details.  Each
;;; element of the `children' sequence is either an XML element evaluation value
;;; or an evaluation text (representing XML text content).  (This union of types
;;; is also known as an `XML evaluation value' or `XML value'.)  For example,
;;; the following XML element corresponds to the following XML element value:
;;;
;;;   <elt attrName='attrValue'>
;;;     <child>text1</child>
;;;     text2
;;;   </elt>
;;;
;;;   structure(tag-name: "elt", attributes: structure(attr-name: "attrValue")
;;;     children: sequence(structure(tag-name: "child",
;;;                                  children: sequence("text1")),
;;;                        "text2"))

;; TO DO: This is analogous to DOM level 1.  It would be nicer to have DOM level
;; 2 (e.g. namespaces), not to mention a real DOM with objects & methods.

;; TO DO: convert to Xexpr (using eval-conses) for internal use

(def-concept xml-element-evaluation-value)
(def-concept xml-evaluation-value)
(def-concept xml-value)


;;; The function `make-xml-element-evaluation-value' returns a new XML element
;;; evaluation value given its tag name (evaluation text), attributes (eval-cons
;;; plist of symbols and evaluation texts), and children (eval-cons list of XML
;;; evaluation values).  All three arguments will be owned by the new value.

(defun-simple make-xml-element-evaluation-value (tag-name ns-prefix ns-uri attributes children)
  (allocate-evaluation-structure
    (nconc
      (eval-list 'tag-name tag-name)
	  (when ns-prefix 
		(eval-list 'ns-prefix ns-prefix))
	  (when ns-uri 
		(eval-list 'ns-uri ns-uri))
      (when attributes
		(eval-list 'attributes (allocate-evaluation-structure attributes)))
	  (when children
		(eval-list 'children (allocate-evaluation-sequence children))))))


;;; The loop path `xml-element-evaluation-value-child' allows the loop clause
;;; `for x being each xml-element-evaulation-value-child of v' where v is an XML
;;; element evaluation value and x will be bound to each child in order.

(define-loop-path xml-element-evaluation-value-child
    xml-element-evaluation-value-child-path (of))

(defun-for-macro xml-element-evaluation-value-child-path
    (path-name var data-type? prep-phrases inclusive-p preps data)
  (declare (ignore path-name data-type? inclusive-p preps data))
  (let ((value (loop-gentemp 'value-))
    (children (loop-gentemp 'children-))
    (index (loop-gentemp 'index-))
    (len (loop-gentemp 'len-)))
    `(;init-bindings
      ((,var nil)
       (,value ,(second (assq 'of prep-phrases)))
       (,children nil)
       (,index nil)
       (,len nil))
      ;prologue-forms
      ((setq ,children (xml-element-evaluation-value-children ,value))
       (setq ,index 0)
       (setq ,len (if ,children (evaluation-sequence-length ,children) 0)))
      ;pre-step-tests
      nil
      ;steppings
      nil
      ;post-step-tests
      (>=f ,index ,len)
      ;post-step-settings
      (,var (evaluation-sequence-aref ,children ,index)
       ,index (1+f ,index))
      )))


(defun-simple xml-evaluation-value-p (value)
  (or (evaluation-text-p value)
      (xml-element-evaluation-value-p value)))

(defun-simple evaluation-sequence-of-xml-evaluation-values-p (seq)
  (and (evaluation-sequence-p seq)
       (loop for x being each evaluation-sequence-element of seq
         always (xml-evaluation-value-p x))))

(defun-simple xml-element-evaluation-value-p (value)
  (and (evaluation-structure-p value)
   (evaluation-text-p (xml-element-evaluation-value-name value))	   
   (let ((prefix (xml-element-evaluation-value-ns-prefix value)))
	(or (not prefix) (evaluation-text-p prefix)))
   (let ((uri (xml-element-evaluation-value-ns-uri value)))
	(or (not uri) (evaluation-text-p uri)))	   
   (let ((attrs (xml-element-evaluation-value-attributes value)))
	(or (not attrs) (xml-attributes-evaluation-value-p attrs)))		
   (let ((children (xml-element-evaluation-value-children value)))
	(or (not children) 
           (evaluation-sequence-of-xml-evaluation-values-p children)))))

(defun-simple xml-attributes-evaluation-value-p (attrs)
  (and (evaluation-structure-p attrs)
       (loop for (name . value) being each evaluation-structure-pair of attrs
         always (evaluation-text-p value))))

(defun-simple evaluation-sequence-of-xml-element-evaluation-values-p (seq)
  (and (evaluation-sequence-p seq)
       (loop for x being each evaluation-sequence-element of seq
         always (xml-element-evaluation-value-p x))))

;;; The function `xml-evaluation-value-is-element-p' determines whether a value
;;; that is known to be an XML evaluation value is an XML element evaluation
;;; value.  (This is more efficient than `xml-element-evaluation-value-p', which
;;; does a full tree traversal.)

(defun-simple xml-evaluation-value-is-element-p (value)
  (evaluation-structure-p value))


;;; The function `xml-element-evaluation-value-name' returns the tag name of an
;;; XML element evaluation value.

(defun-simple xml-element-evaluation-value-name (value)
  (evaluation-structure-slot value 'tag-name))

(defun-simple xml-element-evaluation-value-ns-prefix (value)
  (evaluation-structure-slot value 'ns-prefix))

(defun-simple xml-element-evaluation-value-ns-uri (value)
  (evaluation-structure-slot value 'ns-uri))
  
;;; The function `xml-element-evaluation-value-attributes' returns the
;;; attributes structure of an XML element evaluation value, or NIL if it has
;;; none.

(defun-simple xml-element-evaluation-value-attributes (value)
  (evaluation-structure-slot value 'attributes))

;;; The function `xml-element-evaluation-value-children' returns the children
;;; sequence of an XML element evaluation value, or NIL if it has none.

(defun-simple xml-element-evaluation-value-children (value)
  (evaluation-structure-slot value 'children))


;;; The function `xml-evaluation-value-get-content' returns a new evaluation
;;; text that is the text content of an XML evaluation value.  If the value is
;;; itself a text node, then a copy of it is returned.  If the value is an
;;; element, the text content of its children is concatenated and returned.

(defun-simple xml-evaluation-value-get-content (value)
  (if (evaluation-text-p value)
      (copy-evaluation-text value)
      (loop with text = #w""
        for child being each xml-element-evaluation-value-child of value
        do (setq text (concatenate-text-strings
                text (xml-evaluation-value-get-content child)))
        finally (return (make-evaluation-text-reclaiming-argument text)))))


(defun-simple xml-node-qname (node)
  (multiple-value-bind (local-name prefix ns-uri) (xml-node-name node)
    (reclaim-if-text-string ns-uri)
    (twith-output-to-text-string
      (when prefix
		(twrite-string prefix)
		(twrite-char #\:)
		(reclaim-text-string prefix))
		  (twrite-string local-name)
		  (reclaim-text-string local-name))))

(defun-simple make-xml-element-evaluation-value-from-xml-element (element)
  (multiple-value-bind (local-name prefix ns-uri) (xml-node-name element)
	(make-xml-element-evaluation-value
		(make-evaluation-text-reclaiming-argument local-name)
		(make-evaluation-text-reclaiming-argument prefix)
		(make-evaluation-text-reclaiming-argument ns-uri)
		(loop for attr being each xml-node of (xml-node-attributes element)
		  nconc (eval-list
				  (make-evaluation-symbol
					(convert-xml-name-to-symbol-and-reclaim
					  (xml-node-qname attr)))          
				  (make-evaluation-text-reclaiming-argument
					(xml-node-get-content attr))))
		(loop for child being each xml-node of (xml-node-child-nodes element)
		  collect (make-xml-evaluation-value-from-xml-node child)
			using eval-cons))))

(defun-simple make-xml-evaluation-value-from-xml-node (node)
  (let ((type-symbol (xml-node-type-symbol node)))
    (case type-symbol
      (xml-element-node
       (make-xml-element-evaluation-value-from-xml-element node))
      (xml-text-node
       (make-evaluation-text-reclaiming-argument (xml-node-get-content node)))
      (t
       ;; unimplemented-- use the type symbol itself as a warning
       type-symbol))))


(defun-simple xml-node-new-child-from-xml-element-evaluation-value  (node element)
	(let* ((prefix? (xml-element-evaluation-value-ns-prefix element))
		  (attrs (xml-element-evaluation-value-attributes element))
		  (local-name (xml-element-evaluation-value-name element))
		  (child (xml-node-new-child node local-name)))
	  ;(reclaim-if-text-string local-name)
	  (when attrs
		(loop for (name-symbol . value) being
			  each evaluation-structure-pair of attrs do
		  (let ((name (convert-symbol-to-xml-name 
                            (evaluation-symbol-symbol name-symbol))))
			(cond  ((text-string= name #w"xmlns")
			   (xml-element-new-namespace child value))
			  ((text-string= name #w"xmlns:" :end1 6)
			   (let ((prefix (text-string-substring name 6 nil)))
				 (xml-element-new-namespace child value prefix)
				 (reclaim-text-string prefix)))
			  (t
			   (xml-element-set-attribute child name value)))
			(reclaim-text-string name))))
	  (xml-node-set-namespace
		child (xml-node-lookup-namespace child prefix?))
	  ;(reclaim-if-text-string prefix?)
	  (loop for x being each xml-element-evaluation-value-child of element do
		(if (evaluation-text-p x)
			(xml-node-add-content child (evaluation-text-value x))
			(xml-node-new-child-from-xml-element-evaluation-value child x)))
	  child))

(defun-simple make-xml-document-from-xml-element-evaluation-value (value)
  (let ((document (xml-create-document)))
    (xml-node-new-child-from-xml-element-evaluation-value document value)
    document))

(defun-simple make-xml-document-from-xml-element-evaluation-value-and-reclaim
    (value)
  (prog1 (make-xml-document-from-xml-element-evaluation-value value)
    (reclaim-evaluation-value value)))


;;;; SOAP messages

(defparameter soap-xml-namespace-uri
  ;; #w"http://www.w3.org/2003/05/soap-envelope" ; SOAP 1.2
  #w"http://schemas.xmlsoap.org/soap/envelope/") ; SOAP 1.1
(defparameter soap-xml-namespace-prefix
  #w"soap")

(defparameter soap12-xml-namespace-uri
  #w"http://www.w3.org/2003/05/soap-envelope") ; SOAP 1.2
(defparameter soap12-xml-namespace-prefix
  #w"soap12")

(defparameter xsi-xml-namespace-uri
  #w"http://www.w3.org/2001/XMLSchema-instance")
(defparameter xsi-xml-namespace-prefix
  #w"xsi")

(defparameter xsd-xml-namespace-uri
  #w"http://www.w3.org/2001/XMLSchema")
(defparameter xsd-xml-namespace-prefix
  #w"xsd")

;;; A SOAP message is an XML document.

;;; namespaces: evaluation sequence (alist) or nil
;;; header-entries: evaluation sequence or nil
;;; body-entries: evaluation sequence

(defun-simple make-soap-message (namespaces header-entries body-entries)
  (make-xml-document-from-xml-element-evaluation-value-and-reclaim
    (make-xml-element-evaluation-value
      (make-evaluation-text #w"Envelope") 						;tag-name
      (make-evaluation-text soap-xml-namespace-prefix)       					;ns-prefix
      (make-evaluation-text soap-xml-namespace-uri)   			;ns-uri
	  (nconc
		(eval-list 'xmlns\:soap   (make-evaluation-text soap-xml-namespace-uri))
        (eval-list 'xmlns\:soap12 (make-evaluation-text soap12-xml-namespace-uri))
        (eval-list 'xmlns\:xsd    (make-evaluation-text xsd-xml-namespace-uri))
        (eval-list 'xmlns\:xsi    (make-evaluation-text xsi-xml-namespace-uri))
		(when namespaces
		  (loop for (prefix . uri) being each evaluation-structure-pair of namespaces
		    nconc (eval-list (make-evaluation-symbol prefix)  (make-evaluation-text uri)))))
      (nconc
		(when header-entries
		  (eval-list
			(make-xml-element-evaluation-value
			  (make-evaluation-text #w"Header") 				;tag-name
			  (make-evaluation-text soap-xml-namespace-prefix)   				;ns-prefix
			  (make-evaluation-text soap-xml-namespace-uri)   	;ns-uri
			  nil
			  (loop for entry being
				each evaluation-sequence-element of header-entries
				collect (copy-evaluation-value entry) using eval-cons))))
		(eval-list
		  (make-xml-element-evaluation-value
			(make-evaluation-text #w"Body")
			(make-evaluation-text soap-xml-namespace-prefix)
			(make-evaluation-text soap-xml-namespace-uri)   	;ns-uri
			nil
			(loop for entry being
			  each evaluation-sequence-element of body-entries
			  collect (copy-evaluation-value entry) using eval-cons)))))))

(defun-simple soap-message-get-envelope (message)
  (xml-node-get-child-by-name message #w"Envelope" soap-xml-namespace-uri))

(defun-simple soap-message-get-header (message)
  (xml-node-get-child-by-name
    (soap-message-get-envelope message) #w"Header" soap-xml-namespace-uri))

(defun-simple soap-message-get-body (message)
  (xml-node-get-child-by-name
    (soap-message-get-envelope message) #w"Body" soap-xml-namespace-uri))

;;; soap 1.2	
(defun-simple soap12-message-get-envelope (message)
  (xml-node-get-child-by-name message #w"Envelope" soap12-xml-namespace-uri))

(defun-simple soap12-message-get-header (message)
  (xml-node-get-child-by-name
    (soap-message-get-envelope message) #w"Header" soap12-xml-namespace-uri))

(defun-simple soap12-message-get-body (message)
  (xml-node-get-child-by-name
    (soap-message-get-envelope message) #w"Body" soap12-xml-namespace-uri))

(defun soap-message-evaluation-structure-p (struct)
  (and (evaluation-structure-p struct)
       (let ((namespaces
           (evaluation-structure-slot struct 'namespaces))
         (header-entries
           (evaluation-structure-slot struct 'header-entries))
         (body-entries
           (evaluation-structure-slot struct 'body-entries)))
     (and (or (not namespaces)
          (xml-attributes-evaluation-value-p namespaces))
          (or (not header-entries)
          (evaluation-sequence-of-xml-element-evaluation-values-p
            header-entries))
          (evaluation-sequence-of-xml-element-evaluation-values-p
        body-entries)))))

(defun make-soap-message-from-evaluation-structure (struct)
			(make-soap-message
				(evaluation-structure-slot struct 'namespaces)
				(evaluation-structure-slot struct 'header-entries)
    (evaluation-structure-slot struct 'body-entries)))


(defun make-evaluation-structure-from-soap-message (message)
  (let* ((soap12? 
           (xml-node-namespace-uri-equals-p 
		     (xml-document-root-element message) 
			 soap12-xml-namespace-uri))
         (header 
		   (if soap12? 
		      (soap12-message-get-header message) 
			  (soap-message-get-header message)))
		 (header-entries
		   (when header
			 (loop for entry being each xml-element
			   of (xml-node-child-nodes header)
			   collect (make-xml-element-evaluation-value-from-xml-element
					 entry)
				 using eval-cons)))
		 (namespace-list 
		   (xml-element-get-namespace-list message (xml-document-root-element message)))
		 (namespaces 
		   (loop for i from 0 below (xml-namespace-list-length namespace-list)
  		     nconc (let ((ns-entry (xml-namespace-list-item namespace-list i))) 
			         (eval-list (convert-xml-name-to-symbol-and-reclaim  
					              (tformat-text-string "xmlns\:~a" (xml-namespace-get-prefix ns-entry)))
				                (make-evaluation-text  (xml-namespace-get-uri ns-entry))))))
		 (message-body 
		   (if soap12? 
		      (soap12-message-get-body message) 
			  (soap-message-get-body message)))
			  
		 (body-entries
		   (loop for entry being each xml-element
			 of (xml-node-child-nodes message-body)
			 collect (make-xml-element-evaluation-value-from-xml-element
				   entry)
			   using eval-cons)))

    (allocate-evaluation-structure
      (nconc 
	     (when namespaces
           (eval-list 'namespaces
              (allocate-evaluation-structure namespaces)))
	     (when header-entries
           (eval-list 'header-entries
              (allocate-evaluation-sequence header-entries)))
         (eval-list 'body-entries
            (allocate-evaluation-sequence body-entries))))))
    



;;;; SOAP client system procedures


;;; g2-send-soap-request(URL: text, request: structure) = (structure)
;;;
;;; The system procedure `g2-send-soap-request' sends a SOAP 1.1 request to
;;; a SOAP receiver at the given URL, returning the SOAP response when it
;;; arrives.  The request structure must have the attribute "body-entries", a
;;; sequence containing XML values (see above).
;;;
;;; The request structure may also have the following optional attributes:
;;;
;;;   action: text
;;;   namespaces: structure of prefix/URI attributes [TO DO: not implemented]
;;;   header-entries: sequence of XML values
;;;
;;; The action attribute is the SOAPAction URI, indicating the intent of the
;;; request; this is only used for HTTP.

(def-concept g2-send-soap-request)

(def-type-parameter soap-request-type
    (structure ((action text)
        (namespaces (structure))
        (header-entries (sequence))
        (body-entries (sequence)))
           body-entries))
(def-type-parameter soap-response-type
    (structure ((namespaces (structure))
        (header-entries (sequence))
        (body-entries (sequence)))
           body-entries))
;; TO DO: xml-value type


;;; The system procedure function `g2-make-web-request-from-soap-message'
;;; converts a SOAP 1.1 request message into a Web request.

(defun-for-system-procedure g2-make-web-request-from-soap-message
    ((message structure))
  (declare (values structure))
  (check-type-or-stack-error message soap-request-type)
  ;; TO DO: merge these two type checks
  (unless (soap-message-evaluation-structure-p message)
    (stack-error
      cached-top-of-stack
      "Not a well-formed SOAP message structure: ~NV" message))
  (let ((action? (evaluation-structure-slot message 'action)))
    (prog1 (allocate-evaluation-structure-inline
         'method (make-evaluation-symbol 'post)
         'headers
         (allocate-evaluation-structure-inline
           'content-type
           (make-evaluation-text #w"text/xml; charset=utf-8")
           'soapaction
           (if action?
           ;; add double-quotes:
           (make-evaluation-text-reclaiming-argument
             (tformat-text-string "~s" action?))
           (make-evaluation-text #w"")))
         'entity
         (make-evaluation-text-reclaiming-argument
           (reclaiming-xml-structures
         (xml-write-text-string
           (make-soap-message-from-evaluation-structure message)))))
      (reclaim-evaluation-structure message))))


;;; The system procedure function `g2-make-soap-message-from-web-response'
;;; converts a Web response message into a SOAP 1.1 response.

(defun-for-system-procedure g2-make-soap-message-from-web-response
    ((response structure))
  (declare (values structure))
  (fixnum-case (evaluation-structure-slot response 'status-code)
    ((200 500) ;OK or SOAP fault
     ;; TO DO: these status codes are HTTP-specific, should be generalized?
     (let ((entity? (evaluation-structure-slot response 'entity)))
       (unless entity?
     (stack-error cached-top-of-stack "SOAP response contains no entity."))
       (reclaiming-xml-structures
     (let ((message (xml-read-string (evaluation-text-value entity?))))
       (unless message
         (write-stack-error cached-top-of-stack
           (tformat "Failed to parse SOAP response message:~%")
           (loop for error in (xml-get-errors) do (twrite-string error))))
       (prog1 (make-evaluation-structure-from-soap-message message)
         (reclaim-evaluation-structure response))))))
    (-1
      (stack-error cached-top-of-stack "SOAP response is empty or malformed."))
    (otherwise
      (stack-error cached-top-of-stack "Web error in SOAP response: ~a ~a"
           (evaluation-structure-slot response 'status-code)
           (evaluation-structure-slot response 'reason-phrase)))))



;;;; SOAP server system procedures

;;; g2-handle-http-request-as-soap
;;; (server: class http-server, http-request: structure,
;;;  soap-dispatch: class procedure) = (structure)
;;;
;;; The system procedure `g2-handle-http-request-as-soap' converts a HTTP
;;; request message received by a HTTP server into a SOAP request, passes it to
;;; the soap-dispatch procedure, and converts the resulting SOAP response
;;; message into a HTTP response.

(def-concept g2-handle-http-request-as-soap)
;; TO DO: catch an error, make a SOAP fault



;;; The system procedure function `g2-make-soap-message-from-http-request'
;;; converts a HTTP request message into a SOAP 1.1 request.

(defun-for-system-procedure g2-make-soap-message-from-http-request
    ((request structure))
  (declare (values structure))
  (let* ((entity? (evaluation-structure-slot request 'entity))
     (headers (evaluation-structure-slot request 'headers))
     (action? (evaluation-structure-slot headers 'soapaction)))
    (unless entity?
      (stack-error cached-top-of-stack "SOAP request contains no entity."))
    (reclaiming-xml-structures
      (let ((msg (xml-read-string (evaluation-text-value entity?))))
    (unless msg
      (write-stack-error cached-top-of-stack
        (tformat "Failed to parse SOAP request message:~%")
        (loop for error in (xml-get-errors) do (twrite-string error))))
    (let ((msg-struct (make-evaluation-structure-from-soap-message msg)))
      (when action?
        (setf (evaluation-structure-slot msg-struct 'action)
          (copy-evaluation-text action?)))
      (reclaim-evaluation-structure request)
      msg-struct)))))


;;; The system procedure function `g2-make-http-response-from-soap-message'
;;; converts a SOAP 1.1 response message into a HTTP response.

(defun-for-system-procedure g2-make-http-response-from-soap-message
    ((msg-struct structure))
  (declare (values structure))
  (check-type-or-stack-error msg-struct soap-response-type)
  ;; TO DO: merge these two type checks
  (unless (soap-message-evaluation-structure-p msg-struct)
    (stack-error
      cached-top-of-stack
      "Not a well-formed SOAP message structure: ~NV" msg-struct))
  (reclaiming-xml-structures
    (let* ((msg (make-soap-message-from-evaluation-structure msg-struct))
       (fault-p (loop for entry being each xml-element of
              (xml-node-child-nodes (soap-message-get-body msg))
              thereis (xml-node-name-equals-p
                    entry #w"Fault" soap-xml-namespace-uri))))
      (prog1 (allocate-evaluation-structure
           (nconc
			 (when fault-p
			   ;; 6.2 SOAP HTTP Response
			   ;; In case of a SOAP error while processing the request, the
			   ;; SOAP HTTP server MUST issue an HTTP 500 "Internal Server
			   ;; Error" response and include a SOAP message in the response
			   ;; containing a SOAP Fault element indicating the SOAP
			   ;; processing error.
			   (eval-list 'status-code (make-evaluation-integer 500)))
			 (eval-list
			   'headers
			   (allocate-evaluation-structure-inline
				 'content-type
				 (make-evaluation-text #w"text/xml; charset=utf-8"))
			   'entity
			   (make-evaluation-text-reclaiming-argument
				 (xml-write-text-string msg)))))
		(reclaim-evaluation-structure msg-struct)))))




;;;; Web service description classes

;;; A Web service description has a set of interfaces, bindings, and services.
;;;
;;; An interface has a set of interface operations.  An interface operation has
;;; a list of interface message references.  Interface message references have a
;;; direction (in or out) and an element local-name and namespace-URI.
;;;
;;; A binding associates a set of binding operations with an interface.  Each
;;; binding operation associates protocol-specific information (such as a SOAP
;;; action URI or HTTP method) with an interface operation of the associated
;;; interface.  A binding can also associate protocol-specific information with
;;; an interface as a whole.
;;;
;;; A service has a set of endpoints.  An endpoint associates an address (URL)
;;; with a binding.
;;;
;;; Note that this module uses the terminology of WSDL 2.0.  In WSDL 1.1
;;; terminology, an endpoint is a port and an interface is a portType.  WSDL 1.1
;;; messages don't exist in WSDL 2.0-- an interface refers to schema elements
;;; directly through its interface message references.


;;; Names of the various components of a Web service description do not have to
;;; be globally unique: service names, binding names, and interface names all
;;; have their own partitions, while endpoint names and operation names only
;;; have to be unique within their service or interface, respectively.

;; TO DO: maybe get rid of frame note about duplicate names?
;; TO DO: name directories, e.g. for prompting in the editor



;;; The class `web-service-object' is the abstract base class for all Web
;;; service description classes.

(def-class (web-service-object object not-user-instantiable)
  )


;;; The class `web-service-interface'.  Each instance is an abstract
;;; specification of a set of operations provided by a service.  It has a
;;; subworkspace with web-service-interface-operation instances.  It lives on
;;; the subworkspace of a web-service-description instance.

(def-class (web-service-interface web-service-object)
  (web-service-interface-name nil (type xml-ncname))
  )


;;; The function `get-instance-with-slot-value-if-any' returns the first frame
;;; of class `class' whose slot named `name' has the value `value'.  (Do not
;;; call this with a slot that does not exist on `class', or else G2 will
;;; abort!)

(defun-simple get-instance-with-slot-value-if-any (class name value)
  (loop for item being each class-instance of class
    when (slot-value-equal-p (get-slot-value item name) value)
      return item))

;;; The function `get-instance-with-slot-value-on-subworkspace-if-any' returns
;;; the first frame of class `class' whose slot named `name' has the value
;;; `value' on a subworkspace of `block'.

(defun-simple get-instance-with-slot-value-on-subworkspace-if-any
    (class name value block)
  (loop named outer for workspace in (subworkspaces block) do
     (loop for item being each subblock of workspace
       when (and (frame-of-class-p item class)
             (slot-value-equal-p (get-slot-value item name) value))
         do (return-from outer item))))


;;; The function `web-service-interface-operation' returns the interface
;;; operation of `interface' named `op-name', or NIL if there is no such
;;; interface operation.

(defun-simple web-service-interface-operation (interface operation-name)
  (get-instance-with-slot-value-on-subworkspace-if-any
    'web-service-interface-operation 'web-service-interface-operation-name
    operation-name interface))


;;; The class `web-service-interface-operation'.  Each instance is an abstract
;;; spefication of an operation provided by a service.  It lives on the
;;; subworkspace of a web-service-interface instance.

(def-class (web-service-interface-operation web-service-object)
  (web-service-interface-operation-name nil (type xml-ncname))
  (web-service-input-message
    nil (type web-service-interface-message-reference))
  (web-service-output-message
    nil (type web-service-interface-message-reference))
  ;; TO DO: fault references, message exchange pattern, style
  )


;;; The slot type `web-service-interface-message-reference' refers to an XML
;;; Schema element type.  It is a list containing the element's local name and
;;; optionally its namespace URI.

;; TO DO: category evaluator

(def-grammar-category web-service-interface-message-reference ()
  (xml-ncname (1))
  ((xml-ncname uri) (1 2)))

;; TO DO: make this an actual token from the tokenizer?
(def-grammar-category xml-ncname () (whole-string))

(def-slot-value-writer xml-ncname (name)
  (when name (tformat "~s" name)))

(def-slot-value-writer web-service-interface-message-reference (msg-ref)
  (when msg-ref
    (gensym-dstruct-bind ((name ns?) msg-ref)
      (tformat "~s" name)
      (when ns? (tformat " ~s" ns?)))))



;;; The class `web-service-binding' is the abstract base class for specific
;;; protocol binding extensions (such as HTTP and SOAP).  Each instance
;;; specifies an interface and protocol-specific details for each of its
;;; operations.  It has a subworkspace with web-service-binding-operation
;;; instances.  It lives on the subworkspace of a web-service-description
;;; instance.

(def-class (web-service-binding web-service-object not-user-instantiable)
  (web-service-binding-name nil (type xml-ncname))
  ;; The slot `web-service-interface' holds a text string naming an existing
  ;; interface.  TO DO: can we use a relation for this?
  (web-service-interface nil (type web-service-interface-name))
  )

(def-grammar-category web-service-interface-name () (xml-ncname))

(def-slot-value-writer web-service-interface-name (value)
  (when value (tformat "~s" value)))


;;; The function `web-service-binding-interface' returns the interface of
;;; `binding' or NIL if it does not specify any interface or if the interface
;;; does not exist.

;; TO DO: only look in the current description subworkspace, and its import
;; objects?

(defun web-service-binding-interface (binding)
  (get-instance-with-slot-value-if-any
    'web-service-interface 'web-service-interface-name
    (web-service-interface binding)))


;;; The class `web-service-binding-operation' is the abstract base class for
;;; protocol-specific details for an operation.  Each instance lives on the
;;; subworkspace of a web-service-binding instance.  Its name should be the same
;;; as the name of an operation of the binding's interface.

(def-class (web-service-binding-operation web-service-object)
  (web-service-binding-operation-name nil (type xml-ncname))
  ;; TO DO: message and fault references
  )


;;; The function `web-service-binding-operation' returns the binding
;;; operation of `binding' named `operation-name', or NIL if there is no such
;;; binding operation.

(defun web-service-binding-operation (binding operation-name)
  (get-instance-with-slot-value-on-subworkspace-if-any
    'web-service-binding-operation 'web-service-binding-operation-name
    operation-name binding))


;;; The class `web-service-http-binding' is a binding class for Web services
;;; that use "plain" HTTP (as opposed to SOAP over HTTP).
;;;
;;; WSDL 2.0 Part 2 Section 6
;;; WSDL 1.1 Section 4

(def-class (web-service-http-binding web-service-binding)
  ;; The slot `web-service-http-method' is the HTTP method (a symbol) that is
  ;; used by all operations of the interface.  Currently only GET and POST are
  ;; supported.  TO DO: PUT and DELETE
  (web-service-http-method GET (type http-method))
  ;; TO DO: query parameter separator default
  )

(def-grammar-category http-method ()
  ('get)
  ('post))

(def-slot-value-writer http-method (value)
  (tformat "~a" value))


;;; The class `web-service-http-operation'.  Each instance contains
;;; HTTP-specific details for an operation.  It lives on the subworkspace of a
;;; web-service-http-binding instance.

(def-class (web-service-http-operation web-service-binding-operation)
  ;; The slot `web-service-http-operation-location' is a relative URL (text
  ;; string), which will be combined with the address of the endpoint (an
  ;; absolute URL) to form the specific URL of the HTTP operation.
  (web-service-http-operation-location nil (type uri))
  ;; TO DO: method, serializations, query parameter separator
  )


;;; The class `web-service-soap-binding' is a binding class for Web services
;;; that use SOAP.
;;;
;;; WSDL 2.0 Part 2 Section 5
;;; WSDL 1.1 Section 3

(def-class (web-service-soap-binding web-service-binding)
  ;; TO DO: soap mep default
  )


;;; The class `web-service-soap-operation'.  Each instance contains
;;; SOAP-specific details for an operation.  It lives on the subworkspace of a
;;; web-service-soap-binding instance.

(def-class (web-service-soap-operation web-service-binding-operation)
  ;; The slot `web-service-soap-operation-action' is an absolute URI (text
  ;; string), which will be used as the SOAP Action for the SOAP operation.
  (web-service-soap-operation-action nil (type uri))
  ;; TO DO: soap mep
  )
  

;;; The class `web-service'.  Each instance is a specification of a particular
;;; remote service.  It has a subworkspace with web-service-endpoint instances.
;;; It lives on the subworkspace of a web-service-description instance.

(def-class (web-service web-service-object)
  (web-service-name nil (type xml-ncname))
  ;; TO DO: interface
  )


;;; The class `web-service-endpoint'.  Each instance associates an address with
;;; a binding.  It lives on the subworkspace of a web-service instance.

(def-class (web-service-endpoint web-service-object)
  (web-service-endpoint-name nil (type xml-ncname))
  (web-service-endpoint-binding nil (type web-service-binding-name))
  (web-service-endpoint-address nil (type uri))
  )

(def-grammar-category web-service-binding-name () (unreserved-symbol))

(def-slot-value-writer web-service-binding-name (value)
  (when value (tformat "~a" value)))


;;; The class `web-service-description'.  An instance corresponds to a WSDL
;;; document and has a subworkspace containing the Web service components
;;; (interfaces, bindings, and services) defined by the document.

(def-class (web-service-description web-service-object)
  (web-service-description-name nil (type xml-ncname))
  ;; The slot `web-service-xml-namespace' is the target XML namespace URI for
  ;; all top-level components of the description.
  (web-service-xml-namespace nil (type uri))
  )




;;; A `Web service endpoint reference' is an evaluation structure containing
;;; the following attributes:
;;;
;;;  * service-namespace: text
;;;  * service-name: text
;;;  * endpoint-name: text

;; TO DO: support wsdl-location (URL) -- resolve it in the sys-proc cap
;; TO DO: support matching the endpoint by interface, or by operation and
;; message type

(def-concept web-service-endpoint-reference)
(def-concept endpoint-reference)


;;; The function `get-endpoint-from-web-service-endpoint-reference' returns a
;;; web-service-endpoint instance, or NIL if none can be determined.

(defun-simple get-endpoint-from-web-service-endpoint-reference (ref)
  (let ((service (get-service-from-web-service-endpoint-reference ref))
    (endpoint-name (evaluation-structure-slot ref 'endpoint-name)))
    (when (and service endpoint-name)
      (get-instance-with-slot-value-on-subworkspace-if-any
    'web-service-endpoint 'web-service-endpoint-name
    endpoint-name service))))

;;; The function `get-service-from-web-service-endpoint-reference' returns a
;;; web-service instance, or NIL if none can be determined.

(defun-simple get-service-from-web-service-endpoint-reference (ref)
  (let ((service-name (evaluation-structure-slot ref 'service-name))
    (service-namespace (evaluation-structure-slot ref 'service-namespace)))
    (when service-name
      (loop for desc being each class-instance of 'web-service-description
        when (slot-value-equal-p
           (web-service-xml-namespace desc) service-namespace)
          do (let ((service
             (get-instance-with-slot-value-on-subworkspace-if-any
               'web-service 'web-service-name service-name desc)))
           (when service
             (return service)))))))




;;;; Web service messages

;;; A Web service message is an evaluation structure.  Each structure attribute
;;; is a message part, which has a name and a value.  The value of a message
;;; part attribute is either an XML evaluation value (text or element) or an
;;; evaluation sequence of XML evaluation values.

(def-concept web-service-message)

(defun-simple web-service-message-p (value)
  (and (evaluation-structure-p value)
       (loop for (name . value) being each evaluation-structure-pair of value
         always (web-service-message-part-value-p value))))

(defun-simple web-service-message-part-value-p (value)
  (or (xml-evaluation-value-p value)
      (evaluation-sequence-of-xml-evaluation-values-p value)))


;;; The function `make-xml-element-evaluation-value-from-web-service-message'
;;; serializes a Web service message as an XML element evaluation value, using
;;; an interface message reference to supply the element name and default
;;; namespace (if any).  Each message part becomes a child element of the
;;; serialized message element.  Its tag name is the part name (using the
;;; standard hyphen-replacement algorithm to convert symbols to XML names).  If
;;; the part value is a single XML evaluation value, that becomes its single
;;; child (either a text node or an element).  If the part value is an
;;; evaluation sequence of XML evaluation values, those values become its
;;; children.

(defun-simple make-xml-element-evaluation-value-from-web-service-message
    (message msg-ref ns-prefix)
  (gensym-dstruct-bind ((name ns-uri) msg-ref)
		(make-xml-element-evaluation-value
		  (make-evaluation-text name)
          (make-evaluation-text (if ns-prefix ns-prefix #w"tns"))
		  (make-evaluation-text ns-uri)
          (eval-list
             (if ns-prefix
                (convert-xml-name-to-symbol 
                  (tformat-text-string "xmlns\:~a" ns-prefix))
                'xmlns)
             (make-evaluation-text ns-uri))
		  (loop for (name . value) being each evaluation-structure-pair of message
			collect
			(make-xml-element-evaluation-value-from-web-service-message-part
			  name value ns-prefix ns-uri) using eval-cons))))

(defun-simple make-xml-element-evaluation-value-from-web-service-message-part
    (name value ns-prefix ns-uri)
  (let* ((xml-qname (convert-symbol-to-xml-name name)))
	  (multiple-value-bind (local-name prefix) (xml-qname-expand xml-qname)
        (when ns-prefix (reclaim-if-text-string prefix))
		(make-xml-element-evaluation-value
			(make-evaluation-text-reclaiming-argument local-name)
            (if ns-prefix 
              (make-evaluation-text ns-prefix)
			  (make-evaluation-text-reclaiming-argument prefix))
			(if ns-uri (make-evaluation-text ns-uri) nil)
			nil
			(if (xml-evaluation-value-p value) 
			  (eval-list (copy-evaluation-value value))
			  (loop for value being each evaluation-sequence-element of value
				  collect (copy-evaluation-value value) using eval-cons))))))


;;; The function `make-urlencoded-http-entity-from-web-service-message'
;;; serializes a Web service message as a structure suitable for the entity
;;; attribute of the request structure given to format-http-request, which will
;;; be serialized to text with content-type "application/x-www-form-urlencoded".
;;; The part names are converted from symbols to XML names using the standard
;;; hyphen-replacement algorithm, and then the names are converted to uppercase
;;; symbols (since query parameter names are case-insensitive).  The message
;;; parts must all be evaluation texts.
;;;
;;; WSDL 2.0 Part 2, Section 6.7.2.2.1 Construction of the query string

(defun-simple make-urlencoded-http-entity-from-web-service-message (message)
  (allocate-evaluation-structure
    (loop for (name . value) being each evaluation-structure-pair of message
      collect (let ((field-name (convert-symbol-to-xml-name name)))
            (upcase-text-string-in-place field-name)
            (intern-text-string field-name))
        using eval-cons
      collect (copy-evaluation-text value)
        using eval-cons)))


;;; The function `make-web-service-message-from-xml-element-evaluation-value'
;;; deserializes a Web service message from an XML element evaluation value.
;;; The message parts are constructed from its child elements.  All non-element
;;; children are ignored.

(defun-simple make-web-service-message-from-xml-element-evaluation-value (value)
  (allocate-evaluation-structure
    (loop for child being each xml-element-evaluation-value-child of value
      when (xml-evaluation-value-is-element-p child) nconc
        (make-web-service-message-part-from-xml-element-evaluation-value
          child))))

;;; The function
;;; `make-web-service-message-part-from-xml-element-evaluation-value' returns an
;;; eval-list with two elements, a part name and a part value, deserialized from
;;; an XML element evaluation value.  The part name is the element tag name,
;;; converted to a symbol using the standard hyphen-replacement algorithm.  If
;;; the element has no children, the part value is an empty text.  If the
;;; element has exactly one child, the part value is that child.  If the element
;;; has two or more children, the part value is an evaluation sequence of the
;;; children.

(defun-simple make-web-service-message-part-from-xml-element-evaluation-value
    (value)
  (let ((children
		  (loop for child being each
			xml-element-evaluation-value-child of value
			collect (copy-evaluation-value child) using eval-cons)))
    (eval-list
      (convert-xml-name-to-symbol (xml-element-evaluation-value-name value))
      (cond ((null children)
         (make-evaluation-text #w""))
        ((null (cdr children))
         (prog1 (car children)
           (reclaim-eval-list children)))
        (t
         (allocate-evaluation-sequence children))))))


;;; The function `make-web-service-message-from-xml-http-entity' deserializes a
;;; Web service message from an evaluation text that was an HTTP entity with
;;; serialization format application/xml.  The message has a single part,
;;; constructed from the root element of the entity document.  A stack error is
;;; raised if there are any deserialization errors.

(defun-simple make-web-service-message-from-xml-http-entity (entity)
  (let ((xml-value
      (reclaiming-xml-structures
        (make-xml-element-evaluation-value-from-xml-element
          (xml-document-root-element
        (xml-read-string-or-stack-error
          (evaluation-text-value entity)))))))
    (prog1 (allocate-evaluation-structure
         (make-web-service-message-part-from-xml-element-evaluation-value
           xml-value))
      (reclaim-evaluation-value xml-value))))



;;;; Web service client system procedures


;;; g2-invoke-web-service-operation
;;; (endpoint-reference: structure, operation-name: text,
;;;  input-message: structure) = (structure)
;;;
;;; The system procedure `g2-invoke-web-service-operation' invokes an operation
;;; on a remote Web service given a Web service endpoint reference and operation
;;; name.  The return value is the output message.  The input and output
;;; messages are Web service message structures (see above).  A stack error is
;;; raised if an endpoint cannot be determined from the endpoint reference, if
;;; the input message is not well-formed, or if an error occurs while
;;; communicating with the Web service.

;;; The procedure cap is split into two system calls:
;;; `g2-make-web-service-operation-invocation' and
;;; `g2-get-message-from-web-service-operation-response'.  In between it calls
;;; the appropriate system procedure to actually send the request message, such
;;; as `g2-send-web-request' or `g2-send-soap-request' (depending on the Web
;;; service binding).

(def-concept g2-invoke-web-service-operation)



;;; The system procedure function `g2-make-web-service-operation-invocation'
;;; returns an invocation structure containing the information needed to send a
;;; request message corresponding to a given Web service operation.  The
;;; returned structure contains the following attributes:
;;;
;;;   sys-proc-name: a symbol, the name of a system procedure to call
;;;   URL: a text, the location of the Web service provider agent
;;;   request: a structure, the request message to be sent

;; TO DO: allow operation item to be supplied directly instead of referred to by
;; name

(defun-for-system-procedure g2-make-web-service-operation-invocation
    ((endpoint-reference structure)
     (operation-name text)
     (input-message structure))
  (declare (values structure))
  (unless (web-service-message-p input-message)
    (stack-error
      cached-top-of-stack
      ;; TO DO: more specific error message
      "Input message ~NV is malformed." input-message))
  (let ((endpoint (get-endpoint-from-web-service-endpoint-reference
            endpoint-reference)))
    (unless endpoint
      (stack-error
		cached-top-of-stack
		"An endpoint cannot be determined from the endpoint reference ~NV."
		endpoint-reference))
    (let* ((binding-name (web-service-endpoint-binding endpoint))
       (binding (get-instance-with-slot-value-if-any
              ;; TO DO: only look on the subworkspace of the description
              'web-service-binding 'web-service-binding-name
              binding-name))
       (address (web-service-endpoint-address endpoint)))
      (unless binding-name
		(stack-error
		  cached-top-of-stack
		  "Endpoint ~NF has no binding."
		  endpoint))
      (unless binding
		(stack-error
		  cached-top-of-stack
		  "The binding ~a of endpoint ~NF does not exist."
		  binding-name endpoint))
      (unless address
		(stack-error
		  cached-top-of-stack
		  "Endpoint ~NF has no address."
		  endpoint))
      ;; TO DO: type-check input-message using XML Schema
      (prog1 (frame-class-case binding
           ;; TO DO: can we use a method here?
           (web-service-http-binding
			 (make-http-web-service-operation-invocation
			   binding operation-name address input-message))
           (web-service-soap-binding
			 (make-soap-web-service-operation-invocation
			   binding operation-name address input-message))
           (t
			 (stack-error
			   cached-top-of-stack
			   "Binding ~NF is of unknown type ~NF."
			   binding (class binding))))
		(reclaim-evaluation-structure input-message)))))


;;; The function `make-http-web-service-operation-invocation' uses an HTTP Web
;;; service binding to construct an operation invocation structure suitable for
;;; calling g2-send-web-request.  A stack error is raised if the input message
;;; parts are not all evaluation texts or if the binding has no named operation.
;;; The serialization format is assumed to be application/x-www-form-urlencoded.

(defun make-http-web-service-operation-invocation
    (binding operation-name address input-message)
  (loop for (name . value) being each evaluation-structure-pair of input-message
    unless (evaluation-text-p value)
      do (stack-error
           cached-top-of-stack
           "Input message part ~a is not a text: ~NV" name value))
  (let ((method (web-service-http-method binding))
    (operation (web-service-binding-operation binding operation-name)))
    (unless operation
      (stack-error
    cached-top-of-stack
    "Binding ~NF has no operation ~a." binding operation-name))
    (let ((location? (web-service-http-operation-location operation)))
      (allocate-evaluation-structure-inline
		'sys-proc-name (make-evaluation-symbol 'g2-send-web-request)
		'URL (make-evaluation-text-reclaiming-argument
			   (if location?
			   ;; TO DO: this should use URI resolution rather than simple
			   ;; concatenation.
			   ;;
			   ;; TO DO: and eventually, this should do pattern substitution
			   ;; of curly braces inside the location string.
			   ;;
			   ;; WSDL 2.0 Part 2 Section 6.7
			   ;; WSDL 1.1 Section 4.7
			   (concatenate-text-strings address location?)
			   (copy-text-string address)))
		'request
		(allocate-evaluation-structure-inline
		  'method (make-evaluation-symbol method)
		  'entity (make-urlencoded-http-entity-from-web-service-message
				input-message))))))


;;; The function `make-soap-web-service-operation-invocation' uses a SOAP Web
;;; service binding to construct an operation invocation structure suitable for
;;; calling g2-send-soap-request.  A stack error is raised if the binding has no
;;; named operation, if the interface named by the binding does not exist, or if
;;; the interface has no named operation.

(defun make-soap-web-service-operation-invocation
    (binding operation-name address input-message)
  (multiple-value-bind (local-operation-name prefix)
      (xml-qname-expand (copy-text-string operation-name))
    (let ((operation (web-service-binding-operation binding local-operation-name))
          (interface (web-service-binding-interface binding)))
      (unless operation
        (ui-stack-error "Binding ~NF has no operation ~a."
                        binding local-operation-name))
      (unless interface
        (ui-stack-error "Interface ~a of binding ~NF does not exist."
                        (web-service-interface binding) binding))
      (let* ((interface-operation
              (web-service-interface-operation interface local-operation-name))
             (action? (web-service-soap-operation-action operation))
             (ns-prefix (if prefix
                            (tformat-text-string "~a" prefix)
                          (tformat-text-string "tns")))
             (msg-ref (web-service-input-message interface-operation)))
        (unless interface-operation
          (ui-stack-error "Interface ~NF has no operation ~a."
                          interface local-operation-name))
        (gensym-dstruct-bind ((input-message-name ns-uri) msg-ref)
          input-message-name ; can't use declare to ignore
          (allocate-evaluation-structure-inline
            'sys-proc-name (make-evaluation-symbol 'g2-send-soap-request)
            'URL (make-evaluation-text address)
            'request
            (allocate-evaluation-structure
              (nconc
                (when action?
                  (eval-list 'action (make-evaluation-text action?)))
                (eval-list
                  'namespaces
                  (allocate-evaluation-structure-inline
                    (make-evaluation-symbol 
                      (convert-xml-name-to-symbol-and-reclaim
                        (tformat-text-string "xmlns\:~a" ns-prefix)))
                    (make-evaluation-text ns-uri)))
                (eval-list
                  'body-entries
                  (allocate-evaluation-sequence
                    (eval-list
                     (make-xml-element-evaluation-value-from-web-service-message
                       input-message
                       (web-service-input-message interface-operation) prefix))))))))))))


;;; The system procedure function
;;; `g2-get-message-from-web-service-operation-response' retrieves the output
;;; message from the response structure returned from invoking a Web service
;;; operation.

;; TO DO: faults

(defun-for-system-procedure g2-get-message-from-web-service-operation-response
    ((invocation structure) (response structure))
  (declare (values structure))
  (prog1 (case (evaluation-symbol-symbol
         (evaluation-structure-slot invocation 'sys-proc-name))
       (g2-send-web-request
        (get-message-from-http-web-service-operation-response response))
       (g2-send-soap-request
        (get-message-from-soap-web-service-operation-response response)))
    (reclaim-evaluation-structure invocation)
    (reclaim-evaluation-structure response)))


;;; The function `get-message-from-http-web-service-operation-response' converts
;;; the entity of an HTTP response structure to a Web service message.  The
;;; entity is assumed to consist of an XML document whose root element is an XML
;;; serialization of a single message part.  A stack error is raised if there
;;; are any deserialization errors.

(defun get-message-from-http-web-service-operation-response (response)
  ;; TO DO: check status, content-type
  ;; TO DO: check that the message name and namespace match the interface
  ;; output message reference
  (make-web-service-message-from-xml-http-entity
    (evaluation-structure-slot response 'entity)))


;;; The function `get-message-from-soap-web-service-operation-response' extracts
;;; the first body entry from a SOAP response structure and converts its child
;;; elements to a Web service message.
;;;
;;; WSDL 2.0 Part 2 Section 5.3: "This SOAP binding extension only allows one
;;; single element in SOAP body."

(defun get-message-from-soap-web-service-operation-response (response)
  ;; TO DO: check for soap fault
  ;; TO DO: copy namespace declarations from the envelope to the payload
  ;; TO DO: check that the message name and namespace match the interface
  ;; output message reference
  (make-web-service-message-from-xml-element-evaluation-value
    (evaluation-sequence-aref
      (evaluation-structure-slot response 'body-entries) 0)))




;;;; Importing from a WSDL document

;;; Names in a WSDL document are converted to symbols using the standard
;;; hyphen-replacement mapping (convert-xml-name-to-symbol in dom.lisp).
;;;
;;; Currently namespace names and prefixes in a WSDL document are ignored-- it
;;; is assumed that all local-names are unique in their appropriate partition.

;; TO DO: deal with namespaces!



;;; WSDL 1.1 namespace URIs:

(defconstant wsdl-xml-namespace-uri
  #w"http://schemas.xmlsoap.org/wsdl/")
(defconstant wsdl-soap-xml-namespace-uri
  #w"http://schemas.xmlsoap.org/wsdl/soap/")
(defconstant wsdl-soap12-xml-namespace-uri
  #w"http://schemas.xmlsoap.org/wsdl/soap12/")
(defconstant wsdl-http-xml-namespace-uri
  #w"http://schemas.xmlsoap.org/wsdl/http/")



;;; The function `add-items-to-web-service-subworkspace' adds a subworkspace to
;;; a Web service object, adds a list of items to it, and reclaims the list.

(defun add-items-to-web-service-subworkspace (items ws-object)
  (let ((subworkspace (make-workspace 'kb-workspace)))
    (add-subworkspace subworkspace ws-object)
    (loop for item in items and y downfrom 0 by 100 do
      (transfer-item item subworkspace 0 y)))
  (reclaim-gensym-list items))


    
;;; The function `import-web-service-message' finds a <message> child element of
;;; a <description> by name.

(defun import-web-service-message (description name)
  (loop for message being each xml-element of (xml-node-child-nodes description)
    when (xml-node-name-equals-p
           message #w"message" wsdl-xml-namespace-uri)
      do (let ((msg-name (xml-element-get-attribute message "name")))
           (when (prog1 (equalw msg-name name)
               (reclaim-text-string msg-name))
         (return message)))))


;;; The function `import-web-service-interface-message-reference' returns the
;;; element name and namespace of a message reference element.  In WSDL 1.1,
;;; there is an extra level of indirection between a message reference and the
;;; element it refers to, namely the message type declaration, so we have to use
;;; some heuristics to figure out the element we want.  There are two typical
;;; cases (corresponding to the definitions of "document-literal" and
;;; "rpc-literal" in the WS-I Basic Profile):

;;; 1. For an interface intended to be used with a "document style" binding, the
;;;    message type has a single part, which has an element attribute.  In this
;;;    case, we return the name and namespace of the attribute value (a QName).
;;; 2. For an interface intended to be used with a "rpc style" binding, the
;;;    message type has zero or more parts, each of which has a type attribute.
;;;    In this case, we return the name and namespace of the message.
;;;
;;; Note that in either case, we only look at the first message part.

(defun import-web-service-interface-message-reference (element)
  (multiple-value-bind (msg-name prefix msg-ns)
      (xml-element-get-attribute-qname element "message")
    (reclaim-if-text-string prefix)
    ;; TO DO: check that ns-uri = target namespace!
    (when msg-name
      (let* ((operation (xml-node-parent-node element))
         (interface (xml-node-parent-node operation))
         (description (xml-node-parent-node interface))
         (message (import-web-service-message description msg-name))
         (first-part (xml-node-get-child-by-name
               message #w"part" wsdl-xml-namespace-uri)))
    (if first-part
        (multiple-value-bind (elt-name prefix elt-ns)
        (xml-element-get-attribute-qname first-part "element")
          (reclaim-if-text-string prefix)
          (if elt-name
          (progn
            (reclaim-text-string msg-name)
            (values elt-name (xml-namespace-get-uri elt-ns)))
          (values msg-name (xml-namespace-get-uri msg-ns))))
        (values msg-name (xml-namespace-get-uri msg-ns)))))))


;;; The function `import-web-service-interface-operation' makes a Web service
;;; interface operation from an <operation> element.

(defun import-web-service-interface-operation (element)
  (let ((operation (make-entity 'web-service-interface-operation)))
    (set-frame-name-from-xml-element operation element)
    (change-slot-value operation 'web-service-interface-operation-name
               (xml-element-get-attribute element "name"))
    (loop for child being each xml-element of (xml-node-child-nodes element) do
      (let ((input-p
          (xml-node-name-equals-p child #w"input" wsdl-xml-namespace-uri))
        (output-p
          (xml-node-name-equals-p child #w"output" wsdl-xml-namespace-uri)))
    (when (or input-p output-p)
      (multiple-value-bind (name ns)
          (import-web-service-interface-message-reference child)
        (when name
          (change-slot-value
        operation (if input-p
                  'web-service-input-message
                  'web-service-output-message)
        (if ns
            (slot-value-list name ns)
            (slot-value-list name)))))))
      ;; TO DO: fault message references
      )
    operation))


;;; The function `import-web-service-interface' makes a Web service interface
;;; from an <interface> element.

(defun import-web-service-interface (element)
  (let ((interface (make-entity 'web-service-interface)))
    (set-frame-name-from-xml-element interface element)
    (change-slot-value interface 'web-service-interface-name
               (xml-element-get-attribute element "name"))
    (loop for child being each xml-element of (xml-node-child-nodes element)
      when (xml-node-name-equals-p
         child #w"operation" wsdl-xml-namespace-uri)
        collect (import-web-service-interface-operation child)
          into operations using gensym-cons
        finally (add-items-to-web-service-subworkspace
              operations interface))
    interface))


;;; The function `import-web-service-binding-type' returns a symbol (such as
;;; SOAP or HTTP) specifying the type of a <binding> element.
;; TO DO: use a struct instead of a symbol, use struct-methods instead of a
;; bunch of case statements.

(defun import-web-service-binding-type (element)
  (cond ((xml-node-get-child-by-name
       element #w"binding" wsdl-soap-xml-namespace-uri)
     'soap)
	 ((xml-node-get-child-by-name
       element #w"binding" wsdl-soap12-xml-namespace-uri)
     'soap12)    
	 ((xml-node-get-child-by-name
       element #w"binding" wsdl-http-xml-namespace-uri)
     'http)))


;;; The function `import-web-service-soap-operation' makes a binding operation
;;; from a <soap:operation> element.

(defun import-web-service-soap-operation (element)
  (let ((operation (make-entity 'web-service-soap-operation)))
    (change-slot-value
      operation 'web-service-soap-operation-action
      (xml-element-get-attribute element "soapAction"))
    operation))
	

;;; The function `import-web-service-http-operation' makes a binding operation
;;; from a <http:operation> element.

(defun import-web-service-http-operation (element)
  (let ((operation (make-entity 'web-service-http-operation)))
    (change-slot-value
      operation 'web-service-http-operation-location
      (xml-element-get-attribute element "location"))
    operation))
;; TO DO: error if verb is GET and input is not http:urlEncoded
;; TO DO: error if verb is POST and input is not x-www-form-urlencoded
;; TO DO: error if output is not mime:mimeXml
;; TO DO: support http:urlReplacement


;;; The function `import-web-service-binding-operation' makes a Web service
;;; binding operation from an <operation> element.  The `type' argument is a
;;; symbol specifying the type of the binding.

(defun import-web-service-binding-operation (element type)
  (let* ((operation-element
       (xml-node-get-child-by-name
         element #w"operation"
         (case type
           (soap wsdl-soap-xml-namespace-uri)
           (soap12 wsdl-soap12-xml-namespace-uri)
           (http wsdl-http-xml-namespace-uri))))
     (operation
       (case type
         (soap (import-web-service-soap-operation operation-element))
         (soap12 (import-web-service-soap-operation operation-element))
         (http (import-web-service-http-operation operation-element)))))
    (set-frame-name-from-xml-element operation element)
    (change-slot-value operation 'web-service-binding-operation-name
               (xml-element-get-attribute element "name"))
    ;; TO DO: messages
    operation))


;;; The function `import-web-service-soap-binding-attributes' sets
;;; protocol-specific attributes for a Web service SOAP binding from a <binding>
;;; element.

(defun import-web-service-soap-binding-attributes (binding element)
  (declare (ignore binding))
  (let ((element (xml-node-get-child-by-name
           element #w"binding" wsdl-soap-xml-namespace-uri)))
    (declare (ignore element))
    ;; TO DO: error if transport is not HTTP
    ;; TO DO: error if style is document and there are multiple message parts
    ))


		;;; The function `import-web-service-soap-binding-attributes' sets
		;;; protocol-specific attributes for a Web service SOAP binding from a <binding>
		;;; element.

(defun import-web-service-soap12-binding-attributes (binding element)
  (declare (ignore binding))
  (let ((element (xml-node-get-child-by-name
           element #w"binding" wsdl-soap12-xml-namespace-uri)))
    (declare (ignore element))
    ;; TO DO: error if transport is not HTTP
    ;; TO DO: error if style is document and there are multiple message parts
    ))

	
;;; The function `import-web-service-http-binding-attributes' sets
;;; protocol-specific attributes for a Web service HTTP binding from a <binding>
;;; element.

(defun import-web-service-http-binding-attributes (binding element)
  (let* ((element (xml-node-get-child-by-name
            element #w"binding" wsdl-http-xml-namespace-uri))
     (method (xml-element-get-attribute element "verb")))
    (when method
      (upcase-text-string-in-place method)
      (change-slot-value binding 'web-service-http-method
             (intern-text-string method)))))


;;; The function `import-web-service-binding' makes a Web service binding from a
;;; <binding> element.

(defun import-web-service-binding (element)
  (let ((type (import-web-service-binding-type element)))
    (when type
      (let ((binding (make-entity (case type
                    (soap 'web-service-soap-binding)
                    (soap12 'web-service-soap-binding)
                    (http 'web-service-http-binding)))))
    (set-frame-name-from-xml-element binding element)
    (change-slot-value binding 'web-service-binding-name
               (xml-element-get-attribute element "name"))
    (multiple-value-bind (interface-name prefix ns)
        (xml-element-get-attribute-qname element "type")
      (declare (ignore ns))
      (reclaim-if-text-string prefix)
      ;; TO DO: check ns-uri = target namespace!
      (change-slot-value binding 'web-service-interface interface-name))
    (loop for child being each xml-element of (xml-node-child-nodes element)
          when (xml-node-name-equals-p
             child #w"operation" wsdl-xml-namespace-uri)
        collect (import-web-service-binding-operation child type)
          into operations using gensym-cons
          finally (add-items-to-web-service-subworkspace
            operations binding))
    (case type
      (soap (import-web-service-soap-binding-attributes binding element))
      (soap12 (import-web-service-soap12-binding-attributes binding element))
      (http (import-web-service-http-binding-attributes binding element)))
    binding))))


;;; The function `import-web-service-endpoint' makes a Web service endpoint from
;;; a <port> element.

(defun import-web-service-endpoint (element)
  (let ((endpoint (make-entity 'web-service-endpoint)))
    (set-frame-name-from-xml-element endpoint element)
    (change-slot-value endpoint 'web-service-endpoint-name
               (xml-element-get-attribute element "name"))
    (multiple-value-bind (binding-name prefix ns)
    (xml-element-get-attribute-qname element "binding")
      (declare (ignore ns))
      (reclaim-if-text-string prefix)
      ;; TO DO: check ns-uri = target namespace!
      (change-slot-value endpoint 'web-service-endpoint-binding binding-name))
    (let ((address-element
        (or (xml-node-get-child-by-name
          element #w"address" wsdl-soap-xml-namespace-uri)
		(xml-node-get-child-by-name
          element #w"address" wsdl-soap12-xml-namespace-uri)  
        (xml-node-get-child-by-name
          element #w"address" wsdl-http-xml-namespace-uri))))
      (when address-element
    (change-slot-value
      endpoint 'web-service-endpoint-address
      (xml-element-get-attribute address-element "location"))))
    endpoint))


;;; The function `import-web-service' makes a Web service from a <service>
;;; element.

(defun import-web-service (element)
  (let ((service (make-entity 'web-service)))
    (set-frame-name-from-xml-element service element)
    (change-slot-value service 'web-service-name
               (xml-element-get-attribute element "name"))
    (loop for child being each xml-element of (xml-node-child-nodes element)
      when (xml-node-name-equals-p child #w"port" wsdl-xml-namespace-uri)
        collect (import-web-service-endpoint child)
          into endpoints using gensym-cons
        finally (add-items-to-web-service-subworkspace endpoints service))
    service))



;;; The function `import-web-service-description-child' makes an item
;;; from a top-level child element of a WSDL document.

(defun import-web-service-description-child (element)
  (xml-node-name-symbol-case element
    (wsdl-xml-namespace-uri
      (documentation
    (make-free-text-box-with-text
      (convert-text-string-to-text
        (xml-node-get-content element))))
      (import
    ;; TO DO
    )
      (types
    ;; TO DO
    )
      (message
    ;; TO DO
    )
      (port-type
    (import-web-service-interface element))
      (binding
    (import-web-service-binding element))
      (service
    (import-web-service element))
      (t
    ;; TO DO
    ))
    (t
      ;; TO DO
      )))


;;; The function `import-web-service-description' makes a Web service
;;; description from a <definitions> element.

(defun import-web-service-description (element)
  (let ((description (make-entity 'web-service-description)))
    (set-frame-name-from-xml-element description element)
    (change-slot-value description 'web-service-description-name
               (xml-element-get-attribute element "name"))
    (change-slot-value description 'web-service-xml-namespace
               (xml-element-get-attribute element "targetNamespace"))
    (loop for child being each xml-element of (xml-node-child-nodes element)
      for item = (import-web-service-description-child child)
      when item collect item into items using gensym-cons
      finally (add-items-to-web-service-subworkspace items description))
    description))


;;; The function `import-web-service-description-from-document' makes a Web
;;; service description from a WSDL 1.1 document.

(defun import-web-service-description-from-document (document)
  (let ((root (xml-document-root-element document)))
    (when root
      (xml-node-name-symbol-case root
        (wsdl-xml-namespace-uri
      (definitions
        (import-web-service-description root)))))))




;;; g2-import-web-service-description(URL: text)
;;;   = (class web-service-description)
;;;
;;; The system procedure `g2-import-web-service-description'
;;; creates a Web service description according to a WSDL document located on
;;; the Web at the given URL.  Interfaces, bindings, and services are placed on
;;; the subworkspace of the description.

;; This is implemented entirely at the KB level.

(def-concept g2-import-web-service-description)



;;; g2-import-web-service-description-from-xml-text(document: text)
;;;   = (class web-service-description)
;;;
;;; The system procedure `g2-import-web-service-description-from-xml-text'
;;; creates a Web service description according to a WSDL document (the text
;;; argument).  Interfaces, bindings, and services are placed on the
;;; subworkspace of the description.

(defun-for-system-procedure g2-import-web-service-description-from-xml-text
    ((document-text text))
  (declare (values item))
  (reclaiming-xml-structures
    (let* ((document (xml-read-string document-text))
       (errors (xml-get-errors)))
      (unless document
    (write-stack-error cached-top-of-stack
      (loop for error in errors do (twrite-string error))
      (reclaim-gensym-tree-with-text-strings errors)))
      (when errors
    (with-user-notification ()
      (loop for error in errors do (twrite-string error))
      (reclaim-gensym-tree-with-text-strings errors)))
      (let ((description (import-web-service-description-from-document
               document)))
    (unless description
      (stack-error cached-top-of-stack "Invalid WSDL."))
    (set-transient-and-propagate description nil)
    (funcall-method 'activate-if-possible-and-propagate description)
    description))))
