;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module KB-LOAD1: Loading, Merging, Knowlege Bases

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Lowell B. Hawkinson, Michael Levin, Mark H. David





(declare-forward-references-to-module kb-save2  
  empty-kb-p
  ;; undo-kb-state-changes
  ;; note-as-frame-with-kb-state-changes
  (autostart-after-doing-init-file? variable)
  (autostart-reason-in-init-file? variable)
  (doing-g2-init-file-p variable)
  (automatically-resolve-conflicts-by-default variable)
  (update-before-loading-by-default variable))

(declare-forward-references-to-module g2-foreign
  connect-to-foreign-image
  disconnect-from-foreign-image
  disconnect-from-all-foreign-images
  connect-to-external-foreign-image
  disconnect-from-external-foreign-image
  twrite-foreign-image-connection-spec
  connection-specification-to-foreign-image-function
  external-foreign-image-disconnection-spec-p
  pathname-of-a-connected-foreign-image-p)

(declare-forward-references
  (save-kb function kb-save3)
  (enter-dialog function controls)
  (on/off-switch-on-p function controls)
  (change-on/off-switch function controls)
  (make-button function controls)
  (embedded-rule?-function function controls)
  (load-attribute-file function attributes)
  (write-g2-stats-header function g2-meters)
  (*current-computation-frame* variable comp-utils)
  (current-computation-component-particulars variable comp-utils)
  (rule-byte-code-body-function function rules)
  (put-rule-byte-code-body function rules)
  (make-or-reformat-ruling-for-meter function displays)
  (snapshot-memory-levels function mem-sysproc)
  (get-cvs-editors function kb-save3)
  (directory-contains-pathname-p function kb-save3)
  (reclaim-cvs-editors function kb-save3)
  (do-scc-command function kb-save3)
  (source-code-control-support-enabled-p variable kb-save3))

(declare-forward-reference schedule-task-to-invoke-existential-rules function)
(declare-forward-reference get-current-workstation-or-ui-client-interface-if-any function)
(declare-forward-reference g2gl-variable-compilation-p function) ; g2-bpel


(def-substitute-for-old-class credits-workspace temporary-workspace)
						; 24 Oct 87



;;; `Break-if-name-inconsistency?' ...

(def-system-variable break-if-name-inconsistency? kb-load1 nil)


;;; `new-saved-kb-format-p' is true when loading/merging kbs with the new
;;; non-recursive kb-frame writing as of G2 3.0 and >.

(defvar new-saved-kb-format-p)

(defvar kb-uses-crlf-p)

(eval-when (#-translating :compile-toplevel :load-toplevel :execute)
(defun-for-macro clear-text-kb-format-p-variable ()
  'plist-has-been-checked-p)

(defun-for-macro enable-loading-clear-text-kbs-p-variable ()
  'need-to-check-plist-p)

(defun-for-macro enable-loading-in-clear-text-function ()
  'do-plist-checking)
)

(defmacro clear-text-kb-format-p ()
  (clear-text-kb-format-p-variable))

(defmacro enable-loading-clear-text-kbs-p ()
  (enable-loading-clear-text-kbs-p-variable))

(defvar #.(clear-text-kb-format-p-variable))

#+(and development clear-text)
(def-feature :clear-text-loading-is-initially-enabled)

#+(and development clear-text)
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :clear-text-loading-is-initially-enabled *features*))

(def-system-variable #.(enable-loading-clear-text-kbs-p-variable) kb-load1
  #+clear-text-loading-is-initially-enabled t
  #-clear-text-loading-is-initially-enabled nil)

;See also enable-saving-in-clear-text
(defun-for-system-procedure #.(enable-loading-in-clear-text-function) ()
  (setq #.(enable-loading-clear-text-kbs-p-variable) t)
  (copy-evaluation-truth-value evaluation-true-value))

(defun file-types-for-module ()
  (if (enable-loading-clear-text-kbs-p)
      '(#w"xml" #w"kl" #w"kb")
      '(#w"kl" #w"kb")))

;;; A `basis-kb' (viewed as a file) is the saved kb from which it may be
;;; possible to reconstruct a KB (in RAM) by means of backups and/or journals. A
;;; KB file which can serve as a basis KB must be of version 3.0 or >, must not
;;; have been saved as a module, and must have a string as a value for the
;;; property KB-NAME in its initial-plist.
;;;
;;; Within a modularized application that is consistently modularized, each
;;; individual module may potentially be a basis KB, but only when it is the
;;; installed, top-level module.  Only the basis KB that is installed, i.e., the
;;; top-level module can be the basis KB.  Moreover, during the loading process
;;; itself, each module may well have been the basis KB, however transiently,
;;; since modules are merged from bottom to top, and each successive module may
;;; take over the mantel having the "installed" system tables.

;;; `Complete-kb-name?' is a piece of text that identifies the current kb in a
;;; manner unlikely to be duplicated anywhere in the world. It is set as
;;; follows.
;;; 
;;;   (1) initially, and upon clearing a KB to "new-kb";
;;;   
;;;   (2) after suncessfully reading a 3.0 or > KB that has kb-name on its
;;;   initial-plist (and is not a module), to that string;
;;;
;;;   (3) if no such string, or the read failed, or after a merge, to NIL;
;;;
;;;   (4) Before saving a complete KB, to a string created at that time which
;;;   contains the following components:
;;;
;;;      (a) pathname-name;
;;;      (b) the machine-id;
;;;      (c) the date and time to the
;;;          second in readable form.
;;;          (There is no encrypting
;;;          of the initial plist.)
;;;
;;;   
;;; This value is written to the initial-plist. The effect of this is to
;;; identify the KB in RAM with its basis-kb when if that is possible.  "new-kb"
;;; means that an empty Kb may be used as the basis. NIL means that there is no
;;; basis. The presence of a basis does not necessarily mean that continuity of
;;; changes starting with the basis can be established. That additional fact is
;;; carried as the value of all-permanently-changed-things-are-marked.

(def-system-variable complete-kb-name? kb-load1 nil nil nil reclaim-if-text-string-function)






;;;; Saved KB Formats



;;; A `saved kb' is a text file that should contain only standard Common Lisp
;;; characters (the 95 simple characters plus a newline character) plus possibly a
;;; linefeed character.  In most cases, the text file will be coded in ASCII, where
;;; the newline and linefeed characters are represented as 13 and 10 (decimal),
;;; respectively.

;;; Format of a saved kb:
;;;
;;; Old format:
;;;
;;;    K plist
;;;    {system-frame}
;;;    {class-definition}
;;;    {kb-workspace}
;;;    E plist kb-object-count element-count checksum
;;;
;;; New format:  (3.0+ KBs)

;;;
;;;    J plist
;;;    *1
;;;    {ghost-definition}
;;;    *2
;;;    {format-frame}
;;;    {computation-style}
;;;    {system-frame}
;;;    {class-definition}
;;;    The KB workspace hierarchy
;;;    E plist kb-object-count element-count checksum
;;;
;;; New format:  (4.0+ KBs)
;;;
;;;    J plist
;;;    *1
;;;    {ghost-definition}
;;;    *2
;;;    {system-frame}
;;;    {class-definition}
;;;    The KB workspace hierarchy
;;;    E plist kb-object-count element-count checksum
;;;
;;; NOTE: in 4.0 (and also prior to 3.0), only format frames referenced by other
;;; frame saved are stored in the KB.  In 4.0, frames of certain classes are
;;; exempt from the rule that they are never to be written in the recursive
;;; descent of writing another frame.  The constraint we obey now is that no
;;; frames that could have savable pointers to other frames are written out
;;; within the recursive descent of writing another frame.  Note that format
;;; frames and computation styles may not now have within them savable pointers
;;; to other frames, and therefore qualify.  Note that dependent frames were
;;; always written out within other frames, but they could not have multiple
;;; pointers to themselves.  (ADD COMPUTATION-STYLE!!)
;;;
;;; NOTE: the letters *, 1 and 2, and the single capital letters (K, E, and J)
;;; mean characters, possibly preceeded by "spaces", as defined below.
;;;    
;;; NOTE: For 4.0 this has been compatibly extended by allowing spaces (as
;;; defined below to appear before or after any of the above elements.  This
;;; is intended to allow comments, particularly those that a source code
;;; control system could utilize at the head of the file.
;;;
;;; [TO BE DONE SOON:]
;;; NOTE: For 4.0, all spaces before the initial J character are saved for each
;;; module, and then saved back out.  [What to do with TAB or other non-gensym
;;; characters?!  Should this be saved per module?  Should this be editable
;;; from inside the KB?!]
;;; 
;;; NOTE: At present, 4.0 KBs are not stable unless the frame serial numbers of
;;; frames do not change.  Under a few sets of common circumstances, this is
;;; true now, but in general, the frame serial numbers are not stable.  We don't
;;; yet have a solution. (MHD 10/4/93)

;;; In the old format, a reference to any frame not yet written causes it to be
;;; written lexically within the writing of another frame if necessary.  In the
;;; new format, this is not so. For example, writing format frames, system
;;; frames, and definitions does not cause the writing of any further frames.
;;; The KB workspace herarchy is a forest whose roots are top level KB
;;; workspaces. Each tree is traversed in a depth-first manner by the recursive
;;; function traverse-frame-for-saving. --- In the new, new format (4.0), this
;;; is relaxed back somewhat to the old way in the case of format frames.  They
;;; are now again written lexically within the writing of another frame.  By the
;;; way, even in 3.0 instances of the class dependent-frame were also written
;;; in this way.  They, however, can not have multiple references.




;;; Not included in saved kbs are:
;;;
;;;    non-kb workspaces (e.g., temporary workspaces), except for those that
;;;    occur as or in saved slot values;
;;;
;;;    format frames, except for those that occur as or in saved slot values;
;;;
;;;    frames that have their do-not-save-in-kb frame flag or their transient
;;;    frame flag set, except for those that occur as or in saved slot values;
;;;
;;;    frames that are not reachable via kb-workspaces that are savable
;;;    with the exception of system-tables and definitions.
;;;
;;;    non-savable kb-workspaces
;;;
;;;    orphan class definitions (see below);
;;;
;;; An `orphan class definition' is one that (1) has no superblock, (2) is not
;;; instantiated, and (3) has a name of the form JUNCTION-BLOCK-FOR-x where
;;; x is the name of a defined class.

;;; In knowledge bases for which (class-definitions-ordered-p) is true, class
;;; definitions may be assumed to be so ordered that a class definition follows
;;; the class definition, if any, of its superior class, if any.

;;; Because superblock and subworkspaces links are not followed when saving a kb
;;; (they are reconstructed from subblock links and parent-of-subworkspace? links,
;;; respectively), there is no way that an instance of a class could be read from
;;; a kb before the definition of its class is installed. NO LONGRER VALID REASON!!!

;;; The plist after J or K should include the following properties (though old kbs
;;; need contain no more than the timestamp property):
;;;
;;;     system-version
;;;
;;;     timestamp
;;;
;;;     kb-flags
;;;
;;;     kb-name -- the kb name when the kb was last saved
;;;
;;;	current-frame-serial-number -- a positive integer which is greater than
;;;				    the frame-serial-number of any frame that
;;;				    follows.


;;; The plist after E should include the following properties (though the
;;; numeric-symbols property is optional):
;;;
;;;     detail-pane-description -- see the definition of make-pane-description below
;;;
;;;     numeric-symbols -- syntactically anomalous G2 symbols of type NUMERIC

;; Make use of the kb-name property when the kb is read!
 


;;; Formats of different types of "elements" in a saved kb:
;;;
;;;  earlier kb object    kb-object-index space    the space provides separation as needed
;;;  earlier kb object    kb-object-index
;;;  (These are not used for frames or connections in 3.0 and later.)
;;;
;;;  Formats used in 3.0 for references to frames:
;;;
;;;  (first) forward reference to frame, i.e., when it preceeds the frame itself
;;;  
;;;  				G frame-serial-number class
;;;
;;;                             NB: See the discussion below under "Problems
;;;                             with the G element."
;;;  				
;;;  other references to frames
;;;  				H frame-serial-number
;;;
;;;  reference to a connection structure:
;;;  				I frame-serial-number
;;;  				
;;;  frame-serial-number        positive integer
;;;
;;;  class			symbol
;;;
;;;  slot value cons      L element {element} R
;;;  slot value cons      L element {element} . element
;;;
;;;  Note that LR will cause a bombout. Use N for nil.  Note that, as of 4.0,
;;;  but not earlier, space elements may appear before of after the elements of
;;;  the list (or tree).
;;;
;;;  symbol (in lisp or ab package)
;;;                       count ' character-sequence
;;;  keyword              count : character-sequence
;;;  Unindexed symbol: 	  count ` character-sequence (pkg AB or LISP)
;;; 			  count , character-sequence (keyword pkg)
;;; 			  An unindexed symbol for which type-of-syntactic-anomaly
;;; 			  is 'numeric is preceeded by $.
;;;  string               count S character-sequence
;;;
;;;
;;;  
;;;  
;;;
;;;  frame (in pre-3.0)   F class
;;;                         author-or-authors time-of-last-edit?
;;;                         {slot-name value-element}
;;;                         [left-edge top-edge right-edge bottom-edge 
;;;                         {subblock}]
;;;                       !
;;;                         
;;;                       The edges and subblocks were provided whenever
;;;                       frame was a block.  The author-or-authors and
;;;                       time-or-last-edit? were always nil, as there
;;;                       was never a full implementation of this slot,
;;;                       so they never got set in practice.
;;;
;;;  frame  (in 3.0+)     F frame-serial-number class
;;;                         {slot-denotation value-element}
;;;                         [<runtime data>]
;;;                       !
;;;
;;;                       Slot-denotation is new for 4.0, replacing slot-name.
;;;                       It is either a slot-name (a symbol), which makes it
;;;                       compatible with old KBs, or a list of the form
;;;
;;;                          (CLASS-QUALIFIED-NAME class-qualifier slot-name)
;;;                          
;;;
;;;                       The <runtime data> is optionally present, as indicated
;;;                       by the brackets ([]).  The runtime-data format is
;;;                       provided below.  Runtime data is provided only if
;;;                       saving a snapshot KB, and then only if frame has
;;;                       runtime data to save.  (In 4.0, it may even then not
;;;                       be written: sometimes runtime data is not written
;;;                       immediately, but is deferred until later in the KB as
;;;                       a "frame modification"; see below.)
;;;
;;; frame modification    Same as above (frame)

(def-concept frame-modification)

;;;                       In 4.0, an F element can be either a completely new
;;;                       frame, or a `frame modification', which can be thought
;;;                       of as a combination of a frame element and frame
;;;                       reference element.  It refers to an existing frame
;;;                       instance, but gives additional or overriding slot
;;;                       values, or additional or overriding runtime data.
;;; 
;;;                       A frame modification element cannot be distinguished
;;;                       from a frame (block) element, except by virtue of
;;;                       the fact that it repeats a previously encountered
;;;                       
;;;                          F <frame serial number> <class>
;;;
;;;                       sequence.
;;;
;;;                       At present, this feature is only used to defer writing
;;;                       the runtime data (when snapshotting) in definitions,
;;;                       i.e., their relations, until after every definition
;;;                       has been written.
;;;
;;;                       (Note that the <class> is not strictly needed, but it
;;;                       seems a nice bit of redundancy, since it comes at such
;;;                       a low cost: a few bytes of space for the index to the
;;;                       symbol, and the cost of looking up the symbol in the
;;;                       hashtable. I believe ML had earlier planned to omit
;;;                       the class, and some of his notes scattered about
;;;                       reflect this.  Review!  (MHD 1/24/93))
;;;
;;;  dependent frame      Y class {slot-name value-element} !
;;;
;;;                       These are only written in the new format (3.0+),
;;;                       since they didn't even exist prior to 3.0.
;;;                       
;;;                       Dependent frames are never top level
;;;                       elements of a KB; you can only get to them via
;;;                       non-dependent frames.
;;;
;;;  connection           C frame-serial-number (new format only)
;;;			    connection-frame-or-class
;;;                         input-end-object output-end-object
;;;                         input-end-position output-end-position
;;;                         delta-or-deltas connection-not-directed?
;;;                         connection-attributes-plist
;;;                         
;;;  simple vector        count V {element}  ; NOT PRESENTLY ALLOWED
;;;					     ;   (AND SEE BELOW)
;; ML: See what below?!  managed array W? (MHD 10/12/93)
;;
;;;  managed float array  count O {element}
;;;
;;;                       where each element is the content of
;;;                       a float (P) element, q.v. below
;;;
;;;
;;;  managed array        count W {element}
;;;
;;;  positive integer     absolute-value +
;;;  negative integer     absolute-value -
;;
;;;  nil                  N               alternative form
;;;  t                    T               alternative form
;;;  integer zero         Z               alternative form
;;;  no value             X
;;
;;;  positive/negative    significand P exponent	; old format only
;;;    slot value float   significand M exponent	; old format only

;;;  any float		  P left-half right-half	; new format only 
;;;  			     where left-half and right-half are
;;;  			     written in binary word format.
;;;  small whole number floats
;;;  			  M positive or negative integer
;;;  			  (Float must have an integer value and be smaller
;;;  			  in magnitude than a bignum on any platform)

;;; truth-value           U float [-1.0 +1.0]            ; not implemented in 3.0
;;;                                                      ; implemented in 4.0+ (MHD 10/27/93)
;;;                       This is actually a truth-value evaluation
;;;                       value.

;;; binary word		  5 characters with ascii codes from 33 to 126.
;;;			  The 32 bits of the word are divided 13+19.
;;;			  Each of these is written in radix 94, using
;;;			  (ascii code - 33) as the weight of a character.
;;;		          They take exactly 2 and 3 digits respectively.
;;;
;;;                       NOTE: this is not a KB element.  It just is
;;;                       read in the context of reading a byte code
;;;                       body, which is a KB element; see below.

;;; byte-code-body        B byte-code-body-length
;;;                         n binary words where n
;;;                           = (ceiling byte-code-body-length 4)
;;;                         (length byte-code-body-constant-vector)
;;;                         {kb-element}
;;;                         byte-code-body-environment-description (a
;;;                           kb-element)
;;;                         The three lengths are positive integers.

;;; timestamp             & 10 chars as in float format, but no #\P, or
;;;                       delta as fixnum digits (
;;;                       - delta as fixnum digits )
;;;                       A timestamp specifies an absolute time in GMT to
;;;                       any desired accuracy within the limitations of an
;;;                       IEEE 64 bit float. It follows the UNIX convention
;;;                       by specifying the elapsed seconds since Jan 1, 1970
;;;                       GMT. The & convention specifies a 64 bit float as
;;;                       specified above. The ( and ) formats specify a
;;;                       positive or negative increment respectively to the
;;;                       value of the last timestamp. This convention will be
;;;                       used other than for the first timestamp in a KB whenever
;;;                       the time difference from the last timestamp is integral
;;;                       and not very large.

;;; runtime-data          [ {runtime-data-component} !
;;;                         Runtime data is found only in frames, and only as
;;;                         the last thing in a frame before the final !. Each
;;;                         type runtime data begins with a capital letter that
;;;                         identifies it, and is self delimiting. These do not
;;;                         conflict with the use of capital letters heading
;;;                         kb elements in general, because of the special context
;;;                         within runtime-data. The ! above is the normal one for
;;;                         ending a frame. The types of runtime-data are:
;;;                           V  variable-current-status
;;;                           P  parameter-current-status
;;;                           H  variable-or-parameter-history
;;;                               (obsolete in 4.0, except for early
;;;                               4.0 Alpha releases)
;;;                           J  variable-simulation-history
;;;                               (obsolete in 4.0, except for early
;;;                               4.0 Alpha releases)
;;;                           C  trend-chart history
;;;                               (obsolete in 4.0; appeared only briefly
;;;                               in early 4.0 Alpha releases)
;;;                           B  history buffer and its location
;;;                               (only in 4.0+ KBs; replaces H, J, and G)
;;;                           S  simulation-status-of-variable
;;;                           L  list-contents
;;;                           A  vector-contents
;;;                           R  relation-instances
;;;                           K  kb-workspace is active
;;;                           O  hash-table contents (added by SoftServe)

;;; variable-current-status
;;;                       V current-value collection-time expiration
;;;                         current-value is a kb-element
;;;                         collection-time is N(il) or a timestamp
;;;                         expiration is N(il), a timestamp, X which 
;;;                         represents 'never, or G which represents
;;;                         *some-time-ago* 

;;; parameter-current-status 
;;;                       P current-value collection-time

;;; variable-or-parameter-history
;;;                       H buffer-length {value collection-time}
;;;                         where buffer-length is the number of pairs that
;;;                         follow, value is a float, fixnum, symbol, string, or
;;;                         X (meaning no-simulation-value), and collection-time
;;;                         is a timestamp.
;;;                         
;;; variable-simulation-history
;;;                       J buffer-length {value collection-time}
;;;                         (See variable-or-parameter-history)
;;;
;;; history-buffer-and-its-location
;;;                       B history-buffer-information history-location-information
;;;
;;;                       (A detailed description of
;;;                       history-buffer-information and
;;;                       history-location-information, which are structured
;;;                       lists, can be found in module HISTORIES.)

;;; simulation-status-of-variable-or-parameter
;;;                       S simulation-value (a KB element or X for no-simulation-value)  
;;;
;;; relation-instances    R relation-instances (slot value as an element)

;;; vector-contents       A length {element}
;; HUH?  A is documented below as "readable element" (used only in old KBs)
;; and further below as "positive exponent"! ML?  (MHD 10/1/93)

;;; list-contents         L length {element}
;; HUH?!  L is already defined for lists differently above!  ML? (MHD 10/1/93)

;;; elements of vectors and lists are items, numbers, strings, symbols and
;;; logical values. This is currently the only place where logical values are
;;; used, since integers are used when they occur in variables and parameters.
;;; But here, there is no per-item typing information, so the elements must be
;;; typed.


;;; deletion message      D frame-serial-number (top level only) 


;;; readable element      A readable-representation space ; USED ONLY IN OLD KBS


;;; Format of an index or count:
;;;
;;;    a radix-32 representation of a non-negative fixnum, using lower-case letters

;;; Format of an absolute value or significand:
;;;
;;;    a radix-32 representation of a non-negative integer (fixnum or bignum),
;;;      using lower-case letters

;;; Format of a character-sequence:
;;;
;;;    {character}, except that
;;;       (a) \\ represents \, provided (character-sequences-breakable-in-kb-p)
;;;             is true but (three-escape-characters-p) is not;
;;;       (b) subsequences of the form \ non-simple-character {character} \ are
;;;             ignored (and not included in the count);
;;;       (c) there should be no newline or linefeed characters; and
;;;       (d) if the the last character is a \, an extra \ is added at the end
;;;             (but not included in the count)

;;; Format of a character:
;;;
;;;    a simple character (a standard Common Lisp character object)

;;; Format of a class or slot-name:
;;;
;;;    symbol element

;;; Format of an edge or exponent:
;;;
;;;    format of an integer

;;; Formats for a space:
;;;
;;;    #\space, #\newline, or #\linefeed
;;;
;;;    ; {non-newline-character} #\newline
;;;
;;; Note that ; ... #\newline is intended to be used for writing for comments.
;;; Note that #\newline means any linebreak character: they may vary from
;;; platform to platform.  The operation newline-character-p should be utilized
;;; to abstract away from this subtlety.
;;; 
;;; Wherever an element can begin, there can be spaces preceding it.

;; -- That's now always true; prior to 4.0, it was not always true for some non-
;; top-level elements, e.g., L (List) elements.  (MHD 9/30/93)


;;; Format for a breakpoint/space:  (breakpoint in development only)
;;;
;;;    ;^ {non-newline-character} #\newline
;;;
;;; Note that breakpoints are ordinarily never written into KBs.  They are
;;; ignored in production version of G2.  They are intended to be used when
;;; debugging KBs by inserting them between elements, resulting in a call
;;; to the Lisp break function.
;;;
;;; Breakpoints are semantically equivalent to spaces.


;;; A `kb object index' is the index, by order of appearance in a saved kb, of
;;; an earlier symbol, frame, block, or connection, where 0 is the index of the
;;; first such kb object. (In 2.0, used only for symbols.)

;;; In frames or blocks, slot initializations are included only for slots that
;;; (a) have non-default values and (b) have either a type feature and no
;;; do-not-save feature or a save feature and no type feature, except that (a)
;;; doesn't apply in the case of format or, prior to 4.0, system frames.  As
;;; of 4.0, system frames no longer get non-default values saved.

;;; A readable element will always, at present, have a readable representation
;;; of a non-integer number.  When such a readable representation is in
;;; floating-point format but has an e or E or no exponent marker, it will be
;;; read as a gensym-float number.

;;; In some Common Lisp implementations, #\linefeed may be the same as
;;; #\newline.

;;; Summary of uppercase letters, and nonletters, in use. Please keep up to
;;; date.
;;; 
;;;  	A	positive exponent
;;;     B	byte-code-body
;;;     C	connection structure or frame (I think only structure! ML) 
;;;     D       block or connection has been deleted
;;;     E	preceeds second plist
;;;     F	frame
;;;     G	frame reference, first one if it preceeds frame itself (new format)
;;;     H	frame reference, other references (new format)
;;;     I	connection, all references in new format
;;;     J	preceeds first p-list, new format
;;;     K	preceeds first p-list, old format		
;;;     L	list
;;;     M	negative exponent (old format); short form slot value float (new format)
;;;     N	NIL
;;;     O       managed float array (new 4.0 format)
;;;     P	positive exponent (old format); long form for slot value (new format)
;;;     Q       history buffer
;;;     R       end of list 
;;;     S	string
;;;     T	true
;;;     U       truth value
;;;     V	vector
;;;     W	managed array
;;;     X	no value (i.e., the value of no-value)
;;;	Y       dependent frame
;;;	Z	zero
;;;
;;;     *       marker to delineate portions of a saved KB. Followed by a single
;;;             character.  (These portions may not overlap.) 
;;;             *1 marks the beginning of ghost definitions (*1 in 3.0)
;;;             *2 marks the end of ghost definitions (*2 in 3.0)
;;;
;;;     -       positive integer (postfix)
;;;     +       negative integer (postfix)
;;;
;;;     #       no value in the simulator (i.e., the value of
;;;               simulation-no-value; this is new for 4.0)
;;;
;;;     !       marks the end of entire reading of a frame, including a series of
;;;             saved slots and possibly runtime data.
;;;
;;;     [ 	runtime data (See above)
;;;     %       component/part
;;;     ~       a frame denotation (either a uuid text-string or a name symbol)
;;;     ^       old long value (added by SoftServe), new for G2 2011
;;;     ?       new long value (Chun Tian (binghe)), new for G2 2015

;;; Problems with the G element.
;;;
;;; The presence of frames that are forward-reference (G) elements presents a
;;; special problem for code that may be executed while loading, e.g., frame and
;;; slot initialization code.  What gets stored into a part of the KB that was
;;; read in as a reference (G) element is a frame that has not yet had its slots
;;; initialized and/or restored from the KB.  It may be assumed that the frame
;;; will have this process performed prior to ending the loading process, during
;;; the reading in of other frames, in particular those that contain pointers to
;;; the forwardly referenced frame, slots may not obey their usual constraints
;;; as to data type.  For example, the simulation-details slot of a variable is
;;; normally either NIL or an instance of a simulation-subtable frame.  However,
;;; after such a variable is created as a forward-reference element, but before
;;; it has been restored from the KB via read-frame-from-kb, the
;;; simulation-subtable slot will contain its slot init form, which in some
;;; cases may be a cons of the form (:FUNCALL ...), thus violating the usual
;;; data type assumptions.  Therefore, code which may operate on this slot
;;; _during the loading process_ must deal with the possibility of this slot
;;; having a value that would normally not be legal (a cons).  E.g., in this
;;; example, either
;;;
;;;    (framep simulation-details)
;;;
;;; or
;;;
;;;    (and simulation-details (not (consp simulation-details)))
;;;
;;; would be required to determine if simulation-details was a frame or not.
;;; I.e., a simple nil-check on simulation-details is not adequate for such
;;; code.  The fact that such forwardly referenced frames are obscure and occur
;;; only rarely makes it that much more difficult to test; however, it cannot be
;;; predicted when they will occur.  The saving software is free to write them
;;; out at any time.  The higher level software cannot prevent their existence,
;;; and therefore must be prepared for their presence, rare as such cases may
;;; be.




;; Consider not allowing an absolute value to be a bignum.

;; Consider not including the right and bottom edges for entities, since these
;; can be easily computed during loading.  This would even allow icons to be
;; changed in size, provided port positions and workspace boundaries can be (and
;; are) suitably adjusted.

;; Consider allowing symbols in packages other than lisp, ab, and keyword.

;; Consider having ignorable character subsequences be of the form
;; \ ! non-simple-character {character} \, for greater robustness than depending
;; on a #\newline or #\linefeed to continue to follow the initial \.

;; Consider reinstating the simple vector type of element, by fixing comments
;; above and code in read-element-for-kb (to use recycled structures) and
;; write-element-for-kb (to write vector structures).

;; Consider making the format for connections more flexible.  As it now stands,
;; if a change is required, the connection-not-directed? component would be a
;; good candidate for generalization.  Also, consider handling connections a bit
;; more efficiently, by taking advantage of what is known about possible values
;; for its various slots.

;; Consider assigning better key letters for symbols.

;; Consider using upper-case characters for radix-32 integer representations and
;; having format indicators be lower-case, since that would be a bit more
;; efficient in Common Lisp.

;; Consider allowing characters as elements.

;; Consider changing "char" to "character" in this file.










;;;; Finding Differences in Frames



;;; `Find-differences-in-frames-if-any' is nil if frame-1 and frame-2 are of the
;;; same class and if all savable slots in frame-1 and frame-2 have equal
;;; values, except possibly for the values of slots listed in the code below.
;;; Otherwise, if just-see-if-there-are-any?  is true, it returns t; otherwise,
;;; it returns a slot value list of either CLASS or denotations of savable
;;; slots, the values of which are not equal in frame-1 and frame-2.
;;;
;;; Note that the in just-see-if-there-are-any? = nil case, the result is a
;;; fresh slot value list either a symbol or a slot value list of symbols.  In
;;; general, a slot value true, or, most simply, a slot value.

(defun find-differences-in-frames-if-any
    (frame-1 frame-2
	     &optional just-see-if-there-are-any? compatible-definition-classes?)
  
  (if (and (not (eq (class frame-1) (class frame-2)))
	   (not compatible-definition-classes?))
      (if just-see-if-there-are-any?
	  t
	  (slot-value-list 'class))
      (loop as slot-description
	       in (slot-descriptions (class-description-slot frame-1))
	    when (and (not (memq-p-macro
			     (pretty-slot-name slot-description)
			     '(frame-flags ; ok forever?
			       frame-status-and-notes
			       frame-author-or-authors ; etc??
			       frame-change-log
			       change-log-information
			       frame-representations
			       name-or-names-for-frame
			       name-of-defined-class
			       icon-attributes-plist
			       user-overridable-system-slots
			       subworkspaces
			       slot-group-for-block?
			       indexed-attributes-for-definition
			       junction-block-class-for-connection
			       include-in-menus?
			       instantiate?
			       uuid
			       ;; Relation-instances is an internal slot.
			       ;; It should not cause irreconcilable conflicts.
			       relation-instances
			       icon-background-images
			       ))) ; See note
		      ;; Instances of user-defined definitions may have user-
		      ;; defined attributes which do not contribute to the
		      ;; inheritance of the classes being defined.  They should
		      ;; not cause class conflicts.
		      (not (user-defined-slot-description-p slot-description))
		      (let ((slot-value-1  
			      (get-slot-description-value-macro frame-1 slot-description))
			    (slot-value-2
			      (get-slot-description-value-macro frame-2 slot-description)))
			(and (not (eq slot-value-1 slot-value-2))
			     (slot-description-is-of-savable-slot-p slot-description)
			     (not (slot-value-equal-p
				    slot-value-1 slot-value-2)))))
	      if just-see-if-there-are-any?
		return t
	      else collect
		(denote-slot-using-slot-value-conses
		  slot-description
		    (class-description-slot frame-1))
		       using slot-value-cons)))

;; Note: the just-see-if-there-are-any? was just added today.  Old callers used
;; to cons up and delete the list just to see if there were differences, which
;; was a waste. (MHD 10/3/91)

;; Adding indexed-attributes-for-definition to the list of exceptions serves two
;; purposes: (1) it prevents merge conflicts from arising because of differences
;; in indexing, presumably because this is a transparent efficiency issue, and
;; (2) it saves us from having to have complicated code that recognizes that
;; a difference in indexed-attributes-for-definition means a difference in
;; attribute-descriptions-for-class.  
;; IS THIS RIGHT? (MHD 7/25/91)

;; This is used, at present, for two purposes: (1) determining whether or not two
;; format frames are equivalent; and (2) determining whether or not two object
;; definitions are equivalent and, if not, which of their slots differ.

;; This is defined in a very ad hoc fashion, and should be better engineered!!!









;;;; Series of Values



;;; A `series of values' is a data-abstracted structure that holds a series of values.
;;; This structure is currently implemented as a slot value list of subseries-of-value
;;; vectors, vector-pool-allocated vectors of length 64.  (Note that a series of values
;;; implemented as a list of vectors cannot be saved out in a KB file.)

(def-vector-pool subseries-of-values 64)

;; Consider having a specialized subtype of these with :element-type gensym-float.

;; Consider making these longer, of length 128, say.



;;; `Convert-list-to-series-of-values' ...

(defun convert-list-to-series-of-values (list)
  (loop while list
	collect
	  (loop with subseries-of-values = (make-subseries-of-values)
		as i from 0 below (length subseries-of-values)
		do (setf (aref-subseries-of-values subseries-of-values i)
			 (pop list))		; changes arg
		while list
		finally (return subseries-of-values))
	  using slot-value-cons))



;;; `Convert-series-of-values-to-list' ...

(defun convert-series-of-values-to-list (series-of-values length &optional (copy-values? nil))
  (loop for subseries-of-values in series-of-values
	nconc
	  (loop for i from 0 below (length subseries-of-values)
		while (>=f (decff length) 0)	; changes arg
		collect
		(if copy-values?
		  (copy-for-slot-value (aref-subseries-of-values subseries-of-values i))
		  (aref-subseries-of-values subseries-of-values i))
		  using slot-value-cons)))

(defun reclaim-subseries-of-values-and-values (subseries-of-values)
  (loop for i from 0 below (array-total-size subseries-of-values)
	for value = (aref subseries-of-values i)
	do
    (when value
      (reclaim-slot-value value)
      (setf (aref subseries-of-values i) nil)))
  (reclaim-subseries-of-values subseries-of-values))

(defun reclaim-series-of-values-and-values (series-of-values)
  (loop for subseries-of-values in series-of-values
	do (reclaim-subseries-of-values-and-values
	     subseries-of-values))
  ;; Reclaim values, especially numbers, if possible!
  (reclaim-slot-value-list series-of-values))

;;; `Reclaim-series-of-values' reclaims series-of-values.

(defun reclaim-series-of-values (series-of-values)
  (loop for subseries-of-values in series-of-values
	;; Reclaim values, especially numbers, if possible!
	do (reclaim-subseries-of-values subseries-of-values))
  (reclaim-slot-value-list series-of-values))



;;; `Get-value-from-series-of-values' get the ith value (a number or nil) in
;;; series-of-values, where 0 is the index for the first such value.

(def-substitution-macro get-value-from-series-of-values (series-of-values i)
  (aref-subseries-of-values (nth (ash i -6) series-of-values) (logand i 63)))

;; Consider defining this as a macro in such a way that setf will work with it.






;;;; Collecting Updates to Sensor Attributes



(defvar collecting-updates-to-sensor-attributes-p nil)
(defvar collected-updates-to-sensor-attributes nil)

(defun handle-collected-updates-to-sensor-attributes ()
  (loop for (sensor gsi-interface-frame real-attribute-name-list)
	    in collected-updates-to-sensor-attributes
	do
    (handle-update-to-located-sensor-attribute
      sensor
      (car real-attribute-name-list) ; ignored
      gsi-interface-frame)))

(defmacro collecting-updates-to-sensor-attributes (&body forms)
  `(let ((collecting-updates-to-sensor-attributes-p t)
	 (collected-updates-to-sensor-attributes nil))
     (prog1 (progn ,@forms)
       (handle-collected-updates-to-sensor-attributes))))




;;;; Cloning Frames



;;; `Clone-frame' ...  Blocks-in-bounding-box?  is used for cloning a group of
;;; connected blocks.

;;; A block returned by clone-frame (and its subblocks) may be assumed to have
;;; the same edge positions as the original block (and its subblocks).  Note
;;; this behavior is different from that of make-frame, which creates blocks
;;; which may be assumed to be at position (0,0).
;;;
;;; When a workspace is cloned, it has its module assignment cloned.  This is
;;; straightforward in the case of cloning a top-level workspace.  However, in
;;; the case of cloning a subworkspace, special code is needed to arrange for
;;; this, since module information is only stored in top-level workspaces.  Note
;;; that cloning a subworkspace (except in the case of a recursive call) at
;;; present always results in a new top-level workspace.  [Note: this feature is
;;; new for 4.0, but has been requested by certain users, particularly Mark
;;; Kramer, with reports that this is a frequent cause of losing modularity.  It
;;; seems that making this change has slight potential to cause KBs to work
;;; differently, but is worth the risk as a cleanup and an ease-of-use
;;; enhancement. (MHD 11/22/94)]
;;;
;;; In the case of cloning a non-workspace item, no module information is kept.
;;; During the period in which such a clone is in limbo, i.e., not attached to
;;; any workspace, it will appear to be not assigned to any module.

;;; Slots that have the feature DO-NOT-CLONE are not copied, with the exception
;;; of the name-or-names-for-frame slot if it has the feature
;;; LOCAL-NAME-OR-NAMES.  Notable examples of slots with the DO-NOT-CLONE
;;; feature include the slots named frame-status-and-notes,
;;; name-or-names-for-frame (but with the LOCAL-NAME-OR-NAMES feature for
;;; G2GL-variable), name-of-defined-class, parent-frame, table-rows,
;;; column-edges, and row-edges.  Of these example slots, parent-frame,
;;; table-rows, column-edges, and row-edges have logic elsewhere for their
;;; "parents" to immediately fill in the proper values.  The other slots simply
;;; feel it would be inappropriate to clone them.  These issues are mostly
;;; discussed in detail elsewhere.
;;;
;;; Slots that have the feature do-not-save are generally not copied, unless
;;; they're one of the special slots that the code knows about; see the case
;;; statement in code for details.

;;; Note that this function binds *current-computation-frame* and current-
;;; computation-component-particulars to NIL within its body.  Many of the slot
;;; putters here can establish frame notes, and these expect to be in the NULL
;;; global environment when invoked.  This rebinding here is sad, but per my
;;; conversation with Ben and a bug involving the putters in action-buttons, at
;;; the moment this is the way to go.  Happy New Year.  -jra 12/31/91

(defvar superior-frame-being-cloned?)

;; Made superior-frame-being-cloned? a special variable so copy-frame
;; methods have some way of finding a superblock other than adding more
;; special cases to clone-frame.  When the value of superior-frame-being-cloned
;; is non-nil it is bound to the NEW frame that will be the superblock
;; of some yet-to-be-cloned dependent frames or sub-structures.  JED 12/15/93

;;; IMPORTANT: if there are significant changes to how slots are cloned or
;;; initialized, please review the function g2-attributes-and-classes-to-clone.
;;; Corresponding changes may also need to be made there.  - cpm, 11/17/96

(defun clone-frame
    (old-frame &optional (blocks-in-bounding-box? nil) superior-frame-being-cloned?)
  (collecting-updates-to-sensor-attributes
    (let* ((*current-computation-frame* nil)
	   (current-computation-component-particulars nil)
	   (class-description (class-description-slot old-frame))
	   (new-frame
	     (let ((new-frame
		     (make-frame-without-computed-initializations
		       class-description nil nil)))
	       (schedule-task-to-invoke-existential-rules new-frame 'is-created)
	       (frame-class-case new-frame
		 (kb-workspace
		   (when (null superior-frame-being-cloned?)
		     (initialize-slot-value
		       new-frame 'module-this-is-part-of?
		       (get-module-block-is-in old-frame))))
		 (entity 
		   (initialize-slot-value
		     new-frame 'icon-attributes-plist
		     (copy-for-slot-value (icon-attributes-plist old-frame))))
		 (table
		   (copy-table old-frame new-frame superior-frame-being-cloned?)))
	       new-frame))
	   (superior-frame-being-cloned? new-frame)
	   (ellipses-added-p nil))

      (loop as slot-description
	       in (slot-descriptions class-description)
	    as slot-name
	       = (pretty-slot-name slot-description)
	    as do-not-clone?
	       = (and (feature-assq
			'do-not-clone (slot-features slot-description))
		      ;; exception: esp. needed for G2GL/G2-BPEL (MHD 3/22/05)
		      (or (not (eq slot-name 'name-or-names-for-frame))
			  (not
			    (feature-assq
			      'local-name-or-names
			      (slot-features slot-description)))))
	    as slot-init-form = (slot-init-form slot-description)
	    as old-slot-value
	       = (get-slot-description-value-macro old-frame slot-description)
	    unless (or (eq old-slot-value slot-init-form)
		       do-not-clone?)
	      do (case slot-name
		   (slot-group-for-block?
		    (clone-slot-group-for-block?
		      old-slot-value old-frame new-frame blocks-in-bounding-box?))
		   ((box-translation-and-text simulation-formulas?)
		    ;; generalize for all/other text slots?!
		    (setq ellipses-added-p
			  (clone-text-slot-value new-frame slot-description old-slot-value)))

		   ;; eliminate this kludge in favor of handling this in a method
		   ;; where needed (old graphs and readout tables)!  (MHD 4/15/94)
		   (frame-representations	; only handles "self-representing" tables
		    (loop for representation-frame in old-slot-value
			  when (eq representation-frame old-frame)
			    collect new-frame using slot-value-cons))
		   ((column-of-args column-of-values)
		    (clone-series-of-values
		      new-frame slot-description old-slot-value old-frame))
		   ((embedded-rule? embedded-rule-in-user-menu-choice?)
					; Clone now if do-not-initialize-
					; specializations-for-frame is T?  -
					; cpm, 11/17/96
		    (clone-embedded-rule new-frame slot-description old-slot-value))
		   (list-of-plots
		    (initialize-slot-description-value
		      new-frame slot-description
		      (loop for plot in old-slot-value
			    collect (clone-frame plot) using slot-value-cons)))
		   (subworkspaces
					; Clone now if do-not-initialize-
					; specializations-for-frame is T?  -
					; cpm, 11/17/96
		    (add-subworkspace
		      (clone-frame
			(car old-slot-value)
			nil
			old-frame)	; added. (MHD 8/20/96)
		      new-frame))
		   (t         ;; This AND form includes user-defined slot-descriptions.
		    (when (or (and (slot-description-is-of-savable-slot-p slot-description)
				   (not (eq slot-name 'icon-attributes-plist))) ; done earlier
 			      ;; some slots that aren't savable but must be cloned:
 			      (eq slot-name 'frame-flags)
			      (savable-connection-attribute-p slot-name))
		      (block simple-clone-slot-value
			(let ((new-slot-value
				(cond
				  ;; a compound slot value
				  ((compound-slot-descriptor slot-name)
				   (clone-compound-slot-value
				     old-slot-value new-frame slot-name))
				  ;; a simple slot value
				  ((or (not (framep old-slot-value))
				       (of-class-p old-slot-value 'dependent-frame))
				   (copy-for-slot-value old-slot-value))
				  ;; a format frame
				  ((format-frame-p old-slot-value)
				   old-slot-value)
				  ;; already filled in.
				  ((framep (get-slot-description-value-macro
					     new-frame slot-description))
				   (return-from simple-clone-slot-value nil))
				  (t
				   (clone-frame old-slot-value nil new-frame))
				  )))
			  (initialize-slot-description-value
			    new-frame slot-description new-slot-value)))))))

      ;; This was never called before -- previously, slots that needed evaluation
      ;; but had do-not-clone in their features would have been initialized to
      ;; garbage (i.e., whatever was in the allocated frame vector); now they'll
      ;; be funcalled.  (It turns out that the only instance of such a slot
      ;; has been up till now the frame-status-and-notes slot, which leave this
      ;; function potentially pointing to garbage, but, in practice, pointing
      ;; to nil (by luck).  (MHD 7/5/94)
      
      ;; This form creates subframes for attributes when the slot-value is eq
      ;; to the slot-init-form (both are the same (:funcall <function> <class>)
      ;; form.  When invoking-g2-methods? is t, allocate frame will have
      ;; initialized the slots of user-defined slot-descriptions with such forms
      ;; to nil.  (ghw 6/21/96)
      (initialize-slots-of-frame-needing-evaluation new-frame)

      ;; Update the status of newly cloned, embedded-rules, if they are not OK.
      ;; This is needed because consistency-analysis may not always be able to
      ;; regenerate this status (e.g., with compiler errors).  (Note that the
      ;; frame-status of items are not automatically cloned.)  This is not done
      ;; for (non-embedded) rules and procedures because the clones of these items
      ;; are always made incomplete.  - cpm, jra 8/2/95
      (frame-class-case new-frame
	((generic-action-button user-menu-choice)
	 (let ((new-embedded-rule?
		 (if (frame-of-class-p new-frame 'generic-action-button)
		     (embedded-rule?-function new-frame)
		     (embedded-rule-in-user-menu-choice? new-frame)))
	       (old-embedded-rule?
		 (if (frame-of-class-p old-frame 'generic-action-button)
		     (embedded-rule?-function old-frame)
		     (embedded-rule-in-user-menu-choice? old-frame))))
	   (when (and new-embedded-rule? old-embedded-rule?)
	     ;; Make the clone of a BAD or INCOMPLETE embbedded-rule INCOMPLETE.
	     (update-frame-status
	       new-embedded-rule?
	       (if (frame-status old-embedded-rule?)
		   'incomplete
		   nil)
	       t))))
	(t
	  (when ellipses-added-p
	    (update-frame-status new-frame 'incomplete nil))))

      ;; The initialize method is not called when creating frames via
      ;; make-frame-without-computing-slot-initializations, which is what
      ;; clone-frame uses; so, we need to just call it here:  (MHD 7/5/94)
      (cond ((block-p new-frame)
	     (with-immutable-consistency-analysis (new-frame)
	       ;; Call the system methods
	       (initialize-frame new-frame))
	     ;; Call the g2 methods unless blocks-in-bounding-box? or
	     ;; superior-frame-being-cloned? are true.  See make-frame
	     ;; comments.  (ghw 6/21/96)
	     (assert-consistency-analysis-if-allowed new-frame))
	    (t
	     (initialize-frame new-frame)))

      (when (block-p new-frame)
	(when (frame-of-class-p new-frame 'meter)
	  (make-or-reformat-ruling-for-meter nil new-frame))
	
	;; If new-frame has frame-representations -- presumably attribute
	;; displays -- update the slot's representation(s) therein
	;; Note that this must be done after the initialize method has been
	;; called because the slots may not have their final value until
	;; then. (MHD 10/25/91)
	(update-representations new-frame)
	(update-attribute-tables new-frame nil nil)) ; to delete obsolete slots
      new-frame)))

;; NOTE: this previously called the initialize-frame method directly, rather
;; than calling initialize-frame, i.e., without binding
;; current-block-of-dependent-frame and other important variables (in the "frame
;; initialization" context)! (MHD 7/5/94)

;; The special case for list-of-plots could be removed if a copy method for plots
;; (which are now dependent frames) were implemented!

;; Note that cloning blocks with connections seriously lost when code was added to shift the
;; block to (0,0) at the end just before returning the new frame.  I did not figure out quite
;; why.  Note that cloning connections indirectly recursively calls clone-frame (without the
;; third arg!).  This should be checked out further.  I did check that no callers expect
;; the cloned frame to be at (0,0), and then documented the new behavior. (MHD 9/23/88)

;; Code this more abstractly!  In particular, have a def-slot-value-cloner!

;; This should have some protection against infinite recursion!

;; Consider speeding up the class tests.

;; We could be clever and make "self-connections" clone as such here, but why bother since
;; later we will be doing that as part of a more general "group cloning" function.

;; Think about frame status.



;;; `Clone-text-slot-value' sets the designated slot in new-frame to a modified
;;; copy of old-text-slot-value, which should either be nil or a
;;; box-translation-and-text type value, i.e.,
;;;
;;;    (translation . text)
;;;
;;; If the translation (the car of text-slot-value) is not no-value, this copies
;;; the translation as no-value, and inserts ellipsis dots at the end of the
;;; copy of the text.

(defun clone-text-slot-value (new-frame slot-description old-text-slot-value)
  (let ((include-ellipsis?
	 (and old-text-slot-value
	      (not (no-value-p (car old-text-slot-value))))))
    (initialize-slot-description-value
      new-frame slot-description
      (when old-text-slot-value
	(slot-value-cons
	 (if include-ellipsis?
	     no-value
	     (copy-for-slot-value (car old-text-slot-value)))
	 (nconc (copy-text (cdr old-text-slot-value))
		(when include-ellipsis?
		  (slot-value-list
		   (copy-text-string ellipsis-text-string)))))))     
     include-ellipsis?))

;; Consider not including the ellipsis if this is a subframe of some higher
;; frame.  That shouldn't be very hard to arrange to determine.  However, a
;; problem with doing this is that there are parallel slots that are set by the
;; compiler in many cases, e.g., byte-code-body.




;;; `Clone-series-of-values' ...

(defun clone-series-of-values (new-frame slot-description old-slot-value old-frame)
  (let ((slot-value-list
	  (convert-series-of-values-to-list
	    old-slot-value
	    (get-slot-value
	      old-frame 'number-of-rows-in-table)
	    t)))
    (initialize-slot-description-value new-frame slot-description slot-value-list)))

;;  Original comment: "KLUDGE for series-of-values!" -- LH




;;; The function `clone-embedded-rule' copies the embedded rule, if any, in an
;;; action button's embedded-rule? slot or in a user menu choice's
;;; embedded-rule-in-user-menu-choice? slot.  The copy is set into the same slot
;;; in new-frame.  This leaves the newly created rule in the slot embedded-rule?
;;; (or embedded-rule-in-user-menu-choice?)  containing a
;;; box-translation-and-text whose car is (no-value); that must be checked for,
;;; and fixed up in, the initialize method for action-button and
;;; user-menu-choice.  The parallel slots box-translation-and-text and
;;; rule-byte-code-body are also copied and set into the cloned rule, which makes
;;; it complete.

(defun clone-embedded-rule (new-frame slot-description old-slot-value)
  (let ((embedded-rule?
	  (if old-slot-value (clone-frame old-slot-value nil new-frame))))
    (initialize-slot-description-value
      new-frame slot-description embedded-rule?)
    (when embedded-rule?
      
      ;; At this point, the newly created rule in the slot embedded-rule?  (or
      ;; embedded-rule-in-user-menu-choice?) contains a car which is (no-value).
      ;; This must be replaced. The translation used in the following compile is
      ;; extracted from the rule embedded in the old button frame. Compile the
      ;; rule.

      ;; Copy the byte-code-body before the box-translation.  Required by
      ;; box-transalation-and-text putter.
      (put-rule-byte-code-body
	embedded-rule?
	(copy-for-slot-value
	  (rule-byte-code-body-function old-slot-value))
	nil)
      (put-box-translation-and-text
	embedded-rule?
	(copy-for-slot-value (box-translation-and-text old-slot-value))
	nil)

      ;; Do chaining links need to be resolved?  Can action-buttons
      ;; or user-menu-choices have links (i.e., be forward or
      ;; backward chained to)?  No, at least we don't think so.  -
      ;; cpm, jra 6/10/92
      #+development
      (when (get-slot-value old-slot-value 'rule-chaining-links)
	(error "Cannot clone buttons or menus with chaining links.")))))



;;; Clone Handler for Slot Groups

(defun clone-slot-group-for-block? 
       (slot-group-for-block? old-frame new-frame blocks-in-bounding-box?)
  (when slot-group-for-block?
    (clone-icon-slot-group 
      slot-group-for-block? old-frame new-frame blocks-in-bounding-box?)))

;; Note that superblock? is not cloned.

(defun clone-icon-slot-group 
       (slot-group-for-block? old-frame new-frame blocks-in-bounding-box?)
  (clone-edges-of-block old-frame new-frame)
  (clone-subblocks-of-block slot-group-for-block? old-frame new-frame)
  (clone-connections-of-block 
    slot-group-for-block? old-frame new-frame blocks-in-bounding-box?))

(defun clone-edges-of-block (old-frame new-frame)
  (change-edges-of-block new-frame
			 (left-edge-of-block old-frame)
			 (top-edge-of-block old-frame)
			 (right-edge-of-block old-frame)
			 (bottom-edge-of-block old-frame)))

(defun clone-subblocks-of-block (slot-group-for-block? old-frame new-frame)
  (let ((old-value (subblocks-internal slot-group-for-block?)))
    (unless (table-p old-frame)			; table subblocks are cloned by copy-table
      (if (workspace-p old-frame)
	  (setf (workspace-margin new-frame)	; vector slot -- we set this here in
		(workspace-margin old-frame)))	;   anticipation of its being looked at
						;   by the calls to add-to-workspace that
						;   happen during the following call.
						;   (MHD 1/17/92)
      (loop with reversed-list-of-cloned-subblocks
	      = (loop with workspace-case? = (workspace-p old-frame)
		      with cloned-block = nil
		      with result = nil		; "reverse-list-using-gensym-conses"
		      with blocks-in-bounding-box?
		         = #-subblocks-v2 old-value
			   #+subblocks-v2 (copy-subblocks-using-slot-value-conses old-value)
		      with plist-of-blocks-and-corresponding-clones = nil		      
		      for subblock being each subblock of old-frame
		      unless (and
			       (frame-of-class-p subblock 'name-box)
			       (not (frame-of-class-p old-frame 'method))
			       ;; the following exempts, e.g., g2gl-variable instances:
			       (not (feature-assq
				      'local-name-or-names
				      (slot-features
					(get-slot-description
					  'name-or-names-for-frame
					  (slot-descriptions
					    (class-description-slot
					      old-frame)))))))
			do (setq cloned-block
				 (clone-frame subblock blocks-in-bounding-box? new-frame))
			   (setq result		; list reversing happens here
				 (gensym-cons cloned-block result))
			   (when workspace-case?	; also make a plist in this case
			     (setq plist-of-blocks-and-corresponding-clones
				   (gensym-cons
				     subblock
				     (gensym-cons
				       cloned-block
				       plist-of-blocks-and-corresponding-clones))))
		      finally
			#+subblocks-v2
			(reclaim-slot-value-list blocks-in-bounding-box?)
			(when workspace-case?
			  (loop for (block cloned-block) 
				    on plist-of-blocks-and-corresponding-clones 
				    by #'cddr
				when (connections block)
				do
			    (clone-connections-for-block
			      block cloned-block
			      plist-of-blocks-and-corresponding-clones))
			  (reclaim-gensym-list
			    plist-of-blocks-and-corresponding-clones))
			(return result))
	    for cloned-subblock in reversed-list-of-cloned-subblocks
	    do (add-to-block
		 cloned-subblock new-frame
		 (left-edge-of-block cloned-subblock)
		 (top-edge-of-block cloned-subblock))
	    finally
	      (reclaim-gensym-list reversed-list-of-cloned-subblocks)))))

(defun clone-connections-of-block 
       (slot-group-for-block? old-frame new-frame blocks-in-bounding-box?)
  (when-let (old-value (connections-internal slot-group-for-block?))
    (clone-connections-slot
      old-value old-frame new-frame blocks-in-bounding-box?)))







;;;; File Error Handling



;;; `Handling-file-errors' ... This should be wrapped around major file operations.
;;; If a file error occurs, nil is returned.

;;; The catches level 3 Aborts.

;;; This should catch "everything", including explicit aborts, aborts from error
;;; traps, etc.  

(defmacro handling-file-errors (&body body)
  ;; Lucid has to be switched by version.  Some Lucids store the error string as
  ;; the second element of the info, some store it as the third, and some hide it
  ;; inside a condition-like object.  Note also that lucid::with-error-trapping
  ;; leaks, whether it traps an error or not.  It creates an enclosing cons to
  ;; hold multiple values when no error is signalled, and it conses and creates
  ;; error strings when an error is signalled.  This is moot, since
  ;; handling-file-errors is typically used around calls to directory, which
  ;; leaks anyway.  Once we have a stable, non-consing conditions system, this
  ;; should all be abstracted to the Common Lisp level or implemented as an
  ;; extension of g2-streams.  (jh, 5/23/90)

  ;; Added compile-time switching to eliminate error-handling from Chestnut
  ;; images.  This is a precursor to adding our own signal catchers.  Note that we
  ;; cannot use a #+chestnut-trans read-macro directly for this, since Chestnut
  ;; images are built from within Lucid.  jh per jra & blm, 3/18/91.

  #+lucid
  (if (eval-feature :chestnut-trans)
      `(progn ,@body)
      `(catch 'exit-error
	 (multiple-value-bind 
	   (returned-value-or-error-information error-p)
	     (lucid::with-error-trapping 
	       (catch-abort (3) 
		 ,@body))
	   (cond ((null error-p)
		  (first returned-value-or-error-information))
		 (t (notify-user
		      "File system error.  Error string was: ~S"
		      (let ((info 
			      (second 
				returned-value-or-error-information)))
			(if (text-string-p info)
			    info
			    "Unspecified file system problem"
			    )))
		    (throw 'exit-error nil))))))

  #-lucid
  `(catch-abort (3)
     . ,body))

;; Extend this and clean it up per the new Common Lisp Error Handling system! 

;; Probably in a non-development system (only?) this should intercept more
;; error conditions than it does now!

;; Extended handling-file-errors to cover Lucid, since Lucid/VMS bombs when given
;; non-existent directory names, instead of returning nil as mandated by CLtL/2e,
;; p 663.  (jh, 5/23/90)






;; The following stream operations are here because they use the macro
;; handling-file-errors.  Maybe, handling-file-errors and these operations
;; should be moved to streams!!  19mar90, cpm.


;;; The function `parse-namestring-handling-file-errors' is a simplified
;;; parse-namestring wrapped with handling-file-errors error-catching.  If an
;;; error occurs, nil is returned and an error is displayed.  Otherwise, a
;;; pathname is returned.

;(defun-allowing-unwind parse-namestring-handling-file-errors
;       (thing)
;  (handling-file-errors
;    (parse-namestring thing)))



;;; The function `make-pathname-handling-file-errors' is a simplified
;;; make-pathname wrapped with handling-file-errors error-catching.  If an error
;;; occurs, nil is returned and an error is displayed.  Otherwise, a pathname is
;;; returned.

;(defun-allowing-unwind make-pathname-handling-file-errors
;       (&key defaults name type)
;  (handling-file-errors
;    (make-pathname
;      :name name
;      :type type
;      :defaults defaults)))



;;; The function `g2-stream-open-for-output-handling-file-errors' is a call to
;;; g2-stream-open-for-output wrapped with handling-file-errors error-catching.
;;; If an error occurs, nil is returned and this either sets the g2-stream-error-
;;; flag or if the error was caught by the handling-file-errors wrapper, an error
;;; is displayed.  If the stream was opened successfully, a g2-stream is returned.

(defun-allowing-unwind g2-stream-open-for-output-handling-file-errors (namestring)
  (handling-file-errors
    (g2-stream-open-for-output namestring)))


;;; The function `g2-stream-open-for-appending-handling-file-errors' is a call to
;;; g2-stream-open-for-appending wrapped with handling-file-errors error-catching.
;;; If an error occurs, nil is returned and either sets the g2-stream-error-flag
;;; or if the error was caught be the handling-file-errors wrapper, an error is
;;; displayed.  If the stream was opened successfully, a g2-stream is returned.

(defun-allowing-unwind g2-stream-open-for-appending-handling-file-errors
       (namestring create-if-does-not-exist?)
  (handling-file-errors
    (g2-stream-open-for-appending namestring create-if-does-not-exist?)))







;;;; Handling Knowledge Base Loading and Saving Commands 


(def-system-variable do-g2-init-file? run t)

(def-system-variable current-kb-pathname? kb-load1 nil nil nil reclaim-gensym-pathname)

(def-system-variable attempting-save-via-system-procedure? kb-load1 nil)

(def-system-variable g2-window-for-save-via-system-procedure? kb-load1 nil)

;;; `default-kb-pathname?' is used by function `make-default-pathname'.
(def-system-variable default-kb-pathname? kb-load1 nil nil nil reclaim-gensym-pathname)

(defun-void reclaim-recent-loaded-kbs (list)
  (when list
    (loop for pathname in list
	  do (reclaim-gensym-pathname pathname))
    (reclaim-gensym-list list)))

;;; `recent-loaded-kbs' is a gensym-list of recent kbs in current G2.
;;; the kb pathname is stored by ascending order of loaded time.
(def-system-variable recent-loaded-kbs kb-load1 nil nil nil reclaim-recent-loaded-kbs)

(defconstant +max-cached-recent-loaded-kbs+ 10)

(defun-void add-recent-loaded-kb (pathname)
  (when pathname
    ;; remove `pathname' from `recent-loaded-kbs' if it existed in `recent-loaded-kbs'.
    ;; this will keep the proper loaded order of `recent-loaded-kbs'.
    (loop with namestring = (gensym-namestring pathname)
	  for trailing-pointer = nil then leading-pointer
	  for leading-pointer = recent-loaded-kbs then (cdr-of-cons leading-pointer)
	  until (null leading-pointer)
	  for cached-pathname = (car leading-pointer)
	  for cached-namestring = (gensym-namestring cached-pathname)
	  for equal-p = (if (or (eq local-file-system 'win32)
				(eq local-file-system 'dos))
			  (text-string-equal+ cached-namestring namestring)
			  (text-string= cached-namestring namestring))
	  do (reclaim-text-string cached-namestring)
	     (when equal-p
	       (reclaim-gensym-pathname cached-pathname)
	       (cond (trailing-pointer
		      (setf (cdr trailing-pointer) (cdr leading-pointer)))
		     (t
		      (setf recent-loaded-kbs (cdr recent-loaded-kbs))))
	       (reclaim-gensym-cons leading-pointer)
	       (loop-finish))
	  finally (reclaim-text-string namestring))

    ;; remove oldest one from `recent-loaded-kbs' if the cached size exceed allowed maximum size.
    (when (>=f (length recent-loaded-kbs) +max-cached-recent-loaded-kbs+)
      (let ((p recent-loaded-kbs))
	(setf recent-loaded-kbs (cdr recent-loaded-kbs))
	(reclaim-gensym-pathname (car p))
	(reclaim-gensym-cons p)))

    ;; add `pathname' to end of `recent-loaded-kbs'.
    (setf recent-loaded-kbs
	  (nconc recent-loaded-kbs (gensym-list (copy-gensym-pathname pathname))))))

(defun get-recent-loaded-kb (name)
  (and name
       (loop for pathname in recent-loaded-kbs
	     for namestring = (gensym-namestring pathname)
	     for match-p = (text-string= name namestring)
	     do (reclaim-text-string namestring)
		(if match-p
		  (return pathname)))))


(def-grammar-category command ()
  (file-command)
  (query-command))

#+(and development clear-text)
(def-feature :clear-text-saving-is-initially-enabled)

#+(and development clear-text)
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :clear-text-saving-is-initially-enabled *features*))

#+(and development clear-text)
(def-feature :compiled-code-saving-is-initially-enabled)

#+development
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :compiled-code-saving-is-initially-enabled *features*))

(def-grammar-category file-command ()
  ((load-or-merge-kb file-loading-spec) (1 2 nil))
  ((load-or-merge-kb file-loading-spec '\, kb-load-or-merge-options) (1 2 4))
  ((merge-kb file-loading-spec '\, kb-merge-options) (1 2 4))

  ((save-or-back-up-kb file-saving-spec))
  #+compiled-code-saving-is-initially-enabled
  ((save-or-back-up-kb file-saving-spec emitting-c-code))

  ((save-module file-saving-spec))
  ((save-module file-saving-spec including-all-required-modules))
  #+clear-text
  ((save-module file-saving-spec including-all-required-modules using-clear-text))
  #+clear-text
  ((save-module file-saving-spec using-clear-text))
  #+clear-text
  ((save-module file-saving-spec using-clear-text including-all-required-modules))

  #+scc-grammar-is-initially-present
  ((save-module file-saving-spec including-all-required-modules using-clear-text commit-after-saving))
  #+scc-grammar-is-initially-present
  ((save-module file-saving-spec including-all-required-modules commit-after-saving))
  #+scc-grammar-is-initially-present
  ((save-module file-saving-spec including-all-required-modules commit-after-saving using-clear-text))
  #+scc-grammar-is-initially-present
  ((save-module file-saving-spec using-clear-text including-all-required-modules commit-after-saving))
  #+scc-grammar-is-initially-present
  ((save-module file-saving-spec using-clear-text commit-after-saving))
  #+scc-grammar-is-initially-present
  ((save-module file-saving-spec using-clear-text commit-after-saving including-all-required-modules))
  #+scc-grammar-is-initially-present
  ((save-module file-saving-spec commit-after-saving))
  #+scc-grammar-is-initially-present
  ((save-module file-saving-spec commit-after-saving including-all-required-modules))
  #+scc-grammar-is-initially-present
  ((save-module file-saving-spec commit-after-saving including-all-required-modules using-clear-text))
  #+scc-grammar-is-initially-present
  ((save-module file-saving-spec commit-after-saving using-clear-text))
  #+scc-grammar-is-initially-present
  ((save-module file-saving-spec commit-after-saving using-clear-text including-all-required-modules))
  #+compiled-code-saving-is-initially-enabled
  ((save-module file-saving-spec emitting-c-code))
  #+compiled-code-saving-is-initially-enabled
  ((save-module file-saving-spec emitting-c-code including-all-required-modules))
  #+compiled-code-saving-is-initially-enabled
  ((save-module file-saving-spec including-all-required-modules emitting-c-code))

  ((save-module-into directory-saving-spec))
  ((save-module-into directory-saving-spec including-all-required-modules))
  #+clear-text
  ((save-module-into directory-saving-spec including-all-required-modules using-clear-text))
  #+clear-text
  ((save-module-into directory-saving-spec using-clear-text))
  #+clear-text
  ((save-module-into directory-saving-spec using-clear-text including-all-required-modules))
  #+compiled-code-saving-is-initially-enabled
  ((save-module-into directory-saving-spec emitting-c-code))
  #+compiled-code-saving-is-initially-enabled
  ((save-module-into directory-saving-spec emitting-c-code including-all-required-modules))
  #+compiled-code-saving-is-initially-enabled
  ((save-module-into directory-saving-spec including-all-required-modules emitting-c-code))

  ((write-g2-stats file-name))
  ((write-g2-stats default-file-name))
  ((write-g2-stats 'g2-stats.text))
  ((write-g2-stats default-file-name file-name) (1 3 2))
  (custom-software-file-command)
  #+scc-grammar-is-initially-present
  (source-code-control-file-command))

(defvar clear-text-grammar-rules-added-p
  #+clear-text-saving-is-initially-enabled t
  #-clear-text-saving-is-initially-enabled nil)

(eval-when (#-translating :compile-toplevel :load-toplevel :execute)
(defun-for-macro enable-saving-in-clear-text-function ()
  'do-plist-checking-again)
)

;See also enable-loading-in-clear-text
(defun-for-system-procedure #.(enable-saving-in-clear-text-function) ()
  (unless clear-text-grammar-rules-added-p
    (setq clear-text-grammar-rules-added-p t)
    (with-permanent-gensym-float-creation
      (add-grammar-rules
	'((save-module-option using-clear-text)
	  (save-module-option commit-after-saving)))))
  (copy-evaluation-truth-value evaluation-true-value))

(defvar compiled-code-grammar-rules-added-p
  #+compiled-code-saving-is-initially-enabled t
  #-compiled-code-saving-is-initially-enabled nil)

(eval-when (#-translating :compile-toplevel :load-toplevel :execute)
(defun-for-macro enable-saving-compiled-code-function ()
  'es-c-c)
)

(defun-for-system-procedure #.(enable-saving-compiled-code-function) ()
  (unless compiled-code-grammar-rules-added-p
    (setq compiled-code-grammar-rules-added-p t)
    (with-permanent-gensym-float-creation
      (add-grammar-rules
	'((save-module-option emitting-c-code)))))
  (copy-evaluation-truth-value evaluation-true-value))

(def-grammar-category including-all-required-modules ()
  (('\, 'including 'all 'required 'modules) including-all-required-modules))

(def-grammar-category commit-after-saving ()
  (('\, 'commit 'after 'saving 'with 'log 'message whole-string) (commit-after-saving 8)))

(def-grammar-category emitting-c-code ()
  (('\, 'emitting 'code) emitting-c-code))

(def-grammar-category using-clear-text ()
  (('\, 'using 'clear 'text) using-clear-text))

(add-grammar-rules
  '((init-file-command file-command)
    (init-file-command ('start 'g2) start-g2)


    ;; The KB Loading/Merging cases:
    ;; 
    ;; 1. LOAD | MERGE
    ;; 2. pathname
    ;;    | PER-DIRECTORY-MENU
    ;;    | (default-pathname pathname)
    ;;    | (default-pathname PER-DIRECTORY-MENU)
    ;; 3. list-of-load-or-merge-options

    ;;    Note that list-of-load-or-merge-options is turned into a plist
    ;;    by the compiler for use in execute-file-command.  The
    ;;    appropriate tags in list-of-load-or-merge-options include
    ;;    RESOLVE-CONFLICTS-AUTOMATICALLY, REFORMAT-AS-APPROPRIATE,
    ;;    START-AFTERWARDS, NEVER-START-AFTERWARDS, WARMBOOT-AFTERWARDS,
    ;;    and (in the merge case only) INSTALL-SYSTEM-TABLES.  The
    ;;    resultant plist contains the indicators
    ;;    RESOLVE-CONFLICTS-AUTOMATICALLY, REFORMAT-AS-APPROPRIATE,
    ;;    INSTALL-SYSTEM-TABLES, and WHAT-TO-DO-AFTER-LOADING-KB.  The
    ;;    first three indicators give boolean values; the final
    ;;    indicator is one of NIL, START-AFTERWARDS, NEVER-START-AFTERWARDS,
    ;;    WARMBOOT-AFTERWARDS, WARMBOOT-AFTERWARDS-WITH-CATCH-UP.

    
    ;; Values for the WHAT-TO-DO-AFTER-LOADING-KB indicator:
    ;; 
    ;;   NIL => for kb w/runtime data: discard runtime data & then, for
    ;;     any kb: defer to init file or table
    ;;     
    ;;   START-AFTERWARDS => for kb w/runtime data: discard runtime data
    ;;   
    ;;   NEVER-START-AFTERWARDS => for kb w/runtime data: discard runtime
    ;;    data & then, for any kb: override init file or table
    ;;
    ;;   WARMBOOT-AFTERWARDS => for kb without runtime data: error;
    ;;    otherwise, restore runtime data & start
    ;;
    ;;   WARMBOOT-AFTERWARDS-WITH-CATCH-UP => for kb without runtime data: error;
    ;;    otherwise, restore runtime data & start with current time set to the
    ;;    snapshot current time and the scheduler-mode changed to "as fast as
    ;;    possible".


    (file-loading-spec file-saving-spec)
    (file-loading-spec per-directory-menu)
    (file-loading-spec (default-file-name per-directory-menu))

    (file-saving-spec file-name)
    (file-saving-spec default-file-name)
    (file-saving-spec (default-file-name file-name))

    (directory-saving-spec directory-name)
    (directory-saving-spec default-directory-name)

    (kb-load-or-merge-option ('automatically 'resolving 'conflicts) resolve-conflicts-automatically)
    (kb-load-or-merge-option ('manually 'resolving 'conflicts) resolve-conflicts-manually)
    (kb-load-or-merge-option ('bringing 'formats 'up-to-date) reformat-as-appropriate)
    #+scc-grammar-is-initially-present
    (kb-load-or-merge-option ('update 'from 'source 'code 'control 'before 'loading) update-before-loading)
    #+scc-grammar-is-initially-present
    (kb-load-or-merge-option ('do 'not 'update 'from 'source 'code 'control 'before 'loading) do-not-update-before-loading)
    (kb-load-or-merge-option do-after-loading-kb)

    (kb-merge-option kb-load-or-merge-option)
    (kb-merge-option ('installing 'system 'tables) install-system-tables)
    
    (do-after-loading-kb ('starting 'afterwards) start-afterwards)    
    (do-after-loading-kb ('not 'starting 'afterwards) never-start-afterwards)
    (do-after-loading-kb ('warmbooting 'afterwards) warmboot-afterwards)

    (do-after-loading-kb
      ('warmbooting 'afterwards 'and 'running 'from 'snapshot 'time 'as 'fast 'as 'possible)
      warmboot-afterwards-with-catch-up)

    (save-module ('save 'module module-name 'as)
      (save-module 3))
    (save-module ('save 'top-level 'module 'as)
      (save-module |g2-internal-top-level|))

    (save-module-into ('save 'module module-name 'into)
      (save-module-into 3))
    (save-module-into ('save 'top-level 'module 'into)
      (save-module-into |g2-internal-top-level|))

    (write-g2-stats ('write 'g2 'stats 'as) write-g2-stats)

    (load-or-merge-kb ('load 'kb) load)
    (load-or-merge-kb ('merge 'kb) merge)
    (merge-kb ('merge 'kb) merge)

    (save-or-back-up-kb ('save 'current 'kb 'as) kb-save)

    (custom-software-file-command (load-custom-software-file file-loading-spec))

    ;; jh, 2/9/92.  Added the following phrase as defensive programming,
    ;; in case the process-killing machinery or pathname matching fails.
    (custom-software-file-command ('disconnect 'from 'all 'foreign 'images)
				  (disconnect-from-all-foreign-images))

    (load-custom-software-file ('connect 'to 'foreign 'image) 
			       connect-to-foreign-image)

    (custom-software-file-command
     ('connect 'to 'external 'foreign 'image 'at foreign-image-connection-spec)
      (connect-to-external-foreign-image 7))
    (foreign-image-connection-spec
     ('tcp-ip 'host whole-string 'port-number integer)
     (tcp-ip 3 5))
    
    (load-custom-software-file ('disconnect 'from 'foreign 'image) 
			       disconnect-from-foreign-image)

    (custom-software-file-command
     ('disconnect 'from 'external 'foreign 'image 'at
      foreign-image-connection-spec)
     (disconnect-from-external-foreign-image 7))

    (load-custom-software-file ('load 'attribute 'file) load-attribute-file)

    (per-directory-menu ('per 'directory 'menu) per-directory-menu)

    (default-file-name ('\( file-name 'by 'default '\)) 2)
    (default-directory-name ('\( directory-name 'by 'default '\)) 2)

    (file-name symbol)			; order matters here bug?! (MHD 4/17/94)
    (file-name whole-string)))

(defvar source-code-control-grammar-is-present-p
  #+scc-grammar-is-initially-present t
  #-scc-grammar-is-initially-present nil)

(defun add-source-code-control-grammar ()
  (unless source-code-control-grammar-is-present-p
    (setq source-code-control-grammar-is-present-p t)
    (with-permanent-gensym-float-creation
      (add-grammar-rules
       '((file-command
	  (save-module file-saving-spec including-all-required-modules using-clear-text commit-after-saving))
	 (file-command
	  (save-module file-saving-spec including-all-required-modules commit-after-saving))
	 (file-command
	  (save-module file-saving-spec including-all-required-modules commit-after-saving using-clear-text))
	 (file-command
	  (save-module file-saving-spec using-clear-text including-all-required-modules commit-after-saving))
	 (file-command
	  (save-module file-saving-spec using-clear-text commit-after-saving))
	 (file-command
	  (save-module file-saving-spec using-clear-text commit-after-saving including-all-required-modules))
	 (file-command
	  (save-module file-saving-spec commit-after-saving))
	 (file-command
	  (save-module file-saving-spec commit-after-saving including-all-required-modules))
	 (file-command
	  (save-module file-saving-spec commit-after-saving including-all-required-modules using-clear-text))
	 (file-command
	  (save-module file-saving-spec commit-after-saving using-clear-text))
	 (file-command
	  (save-module file-saving-spec commit-after-saving using-clear-text including-all-required-modules))
	 (file-command
	  (source-code-control-file-command))

	 (kb-load-or-merge-option
	  ('update 'from 'source 'code 'control 'before 'loading) update-before-loading)
	 (kb-load-or-merge-option
	  ('do 'not 'update 'from 'source 'code 'control 'before 'loading) do-not-update-before-loading))))
    t))

(def-grammar-category source-code-control-file-command ()
  ((source-code-control-prefix 'update file-saving-spec) (scc-update 3))
  ((source-code-control-prefix 'edit file-saving-spec) (scc-edit 3))
  ((source-code-control-prefix 'unedit file-saving-spec) (scc-unedit 3))
  ((source-code-control-prefix 'commit file-saving-spec 'with 'log 'message whole-string) (scc-commit 3 7))
  ((source-code-control-prefix 'revert file-saving-spec) (scc-revert 3)))

(def-grammar-category source-code-control-prefix ()
  (('source 'code 'control)))

(add-grammar-rules-for-list
  'kb-load-or-merge-options 'kb-load-or-merge-option '\,)

(add-grammar-rules-for-list
  'kb-merge-options 'kb-merge-option '\,)

;; Consider moving these grammar rules to module GRAMMAR2.



;;; Generic File Pathname Grammar

(add-grammar-rules
  '((generic-file-pathname generic-file-pathname-element)
    (generic-file-pathname (generic-file-pathname-element generic-file-pathname))
    
    (generic-file-pathname-element file-name)
    (generic-file-pathname-element directory-name)
    (generic-file-pathname-element file-name-punctuation-mark) ; grammar below
    
    (directory-name symbol)		; name directories
    (directory-name whole-string)	; same def. file-name, which is above
					; order matters here bug?! (MHD 4/17/94)
    ))

(def-registered-directory-of-names directory-name) ; need explained in PARSE
(def-registered-directory-of-names file-name)


;;; `File name punctuation marks' are the following symbols:
;;;
;;;    / : $ ; < > [ ] * ? \ ~
;;;    
;;; The grammar category `file-name-punctuation-marks' specifies each of these.
;;;
;;; The variables `file-name-punctuation-list' is a standin for, and subset of,
;;; punctuation-alist.  This is used as the value for the
;;; punctuation-alist-subset-override? slot of the edit state structure used
;;; when parsing file names in the KB-load dialog.

(defparameter file-name-punctuation-alist
  '((#.%\/ \/)
    (#.%\: \:)
    (#.%\$ \$)
    (#.%\; \;)
    (#.%\< \<)
    (#.%\> \>)
    (#.%\[ \[)
    (#.%\] \])
    ;; Following are Gensym wildcard characters
    (#.%\* \*)
    (#.%\? \?)				; why was this \*?! (MHD 2/20/96)
    (#.%\{ #w"{")		; why was this a string?! "{"
    (#.%\} #w"}")		; ditto. "}" (MHD 2/20/96) -- ans: to avoid @{ @} in menu!
    ;; jh, 8/23/94.  Backslash is also a Gensym wildcard character, but cannot
    ;; be used on NT machines because the backslash is also the directory
    ;; component delimiter there.    
    ;; jh, 10/7/94.  Experimental replacement of backslash with shriek, for a
    ;; single escape character every file system can live with.
    (#.%\! \!)

    ;; New: previously complex gensym characters: (MHD 2/20/96)
    (#.%\\ |~\\|)				; remember: symbol print names are in UTF-G!
    (#.%\~ |~~|)
    ))


;; OBS:  (MHD 2/20/96)

;(defvar file-name-complex-character-punctuation-alist
;  '((#\~
;     . ((#\\ |~\\|)
;	(#\~ |~~|)))))

(defvar file-punctuation-mark-grammar-rules
  (nconc
    (loop for (nil symbol) in file-name-punctuation-alist
	  collect `(file-name-punctuation-mark ',symbol))
    ;; OBS:  (MHD 2/20/96)
;    (loop for (nil . alist) in file-name-complex-character-punctuation-alist
;	  nconc
;	  (loop for (nil symbol) in alist
;		collect `(file-name-punctuation-mark ',symbol)))
    `((file-name-punctuation-mark number))
    ))

(add-grammar-rules file-punctuation-mark-grammar-rules)


;;; `Token-menu-class-per-category-overrides' is copied to make up the value for
;;; the token-menu-class-per-category-overrides? slot of the edit-state
;;; structure when in a file command editing context, i.e., editing the category
;;; generic-file-pathname.  The function
;;; `get-token-menu-class-per-category-overrides-for-file-command' returns this
;;; as a freshly conses tree of gensym conses, which is what the editor wants
;;; in that slot.

(defparameter token-menu-class-per-category-overrides
  '((:all-token . pathname-component-token-menu) ; overkill, but ok, and the other
					;   ones don't work as of this
					;   time.  (MHD 4/17/94)
    (file-name . pathname-component-token-menu)
    (directory-name . pathname-component-token-menu)
    (file-name-punctuation-mark . pathname-component-token-menu)))

(defun get-token-menu-class-per-category-overrides-for-file-command ()
  (copy-tree-using-gensym-conses token-menu-class-per-category-overrides))





(def-slot-value-compiler file-command (file-command-parse)
  (compile-init-file-or-file-command file-command-parse nil))

;; bah & jh, 12/3/91.  It is possible for the user to type in an invalid file name
;; and get the previous default in a per-directory menu.  Added a
;; slot-value-compiler for the file-command class to handle this.  This
;; slot-value-compiler is a good place to put other such checks.



(def-slot-value-compiler init-file-command (file-command-parse)
  (compile-init-file-or-file-command file-command-parse t))

;; jh & mhd, 6/9/92.  Abstracted check-file-command-for-slot and
;; transform-load-or-merge-options-if-appropriate so we can have a slot-value
;; compiler for the init-file-command-category.  This informs the user in the
;; logbook when there are problems parsing a command in the G2 init file.



;;; Compile-init-file-or-file-command ...  if init-file-case?  is true, and
;;; there is a failure to compile, this notifies the user of any failure to
;;; compile; otherwise, if there is a failure to compile, this returns
;;; bad-phrase with the failure string as its second value.  For non-failing
;;; cases, this works the same way no matter what the value of init-file-case?.

(defun compile-init-file-or-file-command (file-command-parse init-file-case?)
  (if (eq file-command-parse 'start-g2)
      file-command-parse
      (let* ((command-symbol
	       (if (consp (first file-command-parse))
		   (car (first file-command-parse))
		   (first file-command-parse)))
	     (load-or-merge-case-p
	       (memq command-symbol '(load merge)))
	     (failed-to-compile-and-why? 
	       (check-file-command-for-slot
		 file-command-parse
		 load-or-merge-case-p)))
	(cond
	  (failed-to-compile-and-why?
	   (cond
	     (init-file-case?
	      (notify-user "~a" failed-to-compile-and-why?)
	      (reclaim-text-string failed-to-compile-and-why?)
	      bad-phrase)
	     (t
	      (values bad-phrase failed-to-compile-and-why?))))
	  (t (transform-load-or-merge-options-if-appropriate
	       file-command-parse
	       command-symbol
	       load-or-merge-case-p)
	     file-command-parse)))))







;;; The following all have as their result a wide string containing the error
;;; message text.

;;; `Error-file-name-cannot-be-parsed' is called when file-name, a wide string,
;;; cannot be parsed and turned into a gensym pathname.  The result is a wide
;;; string containing the error message text.

;;; `Get-error-string-for-illegal-wildcards-in-filename' is called when
;;; file-name, a wide string, contains wildcards, illegally, and so cannot
;;; interpreted as denoting a single file.  

;;; `Get-error-string-for-bad-starting-afterwards-option' is called when
;;; `starting afterwards' is a selected option, and the argument options
;;; contains an option not permitted in combination with it.

;;; `Get-error-string-for-bad-warmbooting-afterwards-option' is called when
;;; `warmbooting afterwards' is a selected option, and the argument options
;;; contains an option not permitted in combination with it.

(defun get-error-string-for-file-name-cannot-be-parsed (file-name)
  (tformat-text-string
    "The default file name ~s cannot be parsed on this platform."
    file-name))

;;; `get-error-string-for-illegal-wildcards-in-filename'
;;; tells the user not to use certain characters. See
;;; wild-regular-expression-string-p for exactly what
;;; characters are not allowed.

(defun get-error-string-for-illegal-wildcards-in-filename (file-name)
  (tformat-text-string
    "The file name ~s contains an illegal wildcard."
    file-name))

(defun get-error-string-for-bad-starting-afterwards-option (options)
  (tformat-text-string
    "The KB-loading option `~a' is not consistent with `starting afterwards'"
    (if (memq 'never-start-afterwards options)
	"not starting afterwards" "warmbooting afterwards")))

(defun get-error-string-for-bad-warmbooting-afterwards-option (options)
  (tformat-text-string
    "The KB-loading option `~a' is not consistent with `warmbooting afterwards'"
    (if (memq 'never-start-afterwards options)
	"not starting afterwards" "starting afterwards")))



;;; Check-file-command-for-slot is a subfunction of compile-init-file-or-
;;; file-command; its result is nil, indicating success, or a new wide string
;;; indicating and explaining the reason for failure.  Such a string is to be
;;; reclaimed by the caller.

(defun-allowing-unwind check-file-command-for-slot
    (file-command-parse load-or-merge-case-p)
  (protected-let*
      ((filename-spec (second file-command-parse)) ; note 1
       (per-directory-p
	 (eq (if (consp filename-spec) (second filename-spec) filename-spec)
	     'per-directory-menu))
       (default-file-name?
	 (if (consp filename-spec) (first filename-spec)))
       (default-file-name-as-ascii-string? ; actually Unicode...!
	   default-file-name?)
       (pathname-from-default-file-name?
	 (if default-file-name-as-ascii-string?
	     (gensym-pathname default-file-name-as-ascii-string?))
	 (reclaim-gensym-pathname pathname-from-default-file-name?))
       (namestring?
	 (if (not per-directory-p)
	     (if (consp filename-spec) (second filename-spec) filename-spec)))
       (namestring-as-ascii-string?	; actually Unicode...!
	 namestring?)
       (options
	 (if load-or-merge-case-p (third file-command-parse))))
    (cond
      ;; Check the parsability of the default pathname in a per-directory
      ;; context -- it does not probe for files in the file system at present.
      ((and per-directory-p default-file-name?
	    (null pathname-from-default-file-name?))
       (get-error-string-for-file-name-cannot-be-parsed default-file-name?))
      ;; jh, 10/7/92.  The following form checks that a wildcarded default
      ;; pathname does not occur outside a "per directory" context.
      ((and (not per-directory-p) namestring-as-ascii-string?
	    (gensym-wild-pathname-p namestring-as-ascii-string?))
       (get-error-string-for-illegal-wildcards-in-filename namestring?))
      ;; This form enforces mutual exclusivity between the do-after-loading
      ;; options.  -- Added.  (MHD/JH 4/6/92)
      (load-or-merge-case-p
       (or (when (memq 'start-afterwards options)
	     (when (or (memq 'never-start-afterwards options)
		       (memq 'warmboot-afterwards options)
		       (memq 'warmboot-afterwards-with-catch-up options))
	       (get-error-string-for-bad-starting-afterwards-option options)))
	   (when (or (memq 'warmboot-afterwards options)
		     (memq 'warmboot-afterwards-with-catch-up options))
	     (when (or (memq 'never-start-afterwards options)
		       (memq 'start-afterwards options))
	       (get-error-string-for-bad-warmbooting-afterwards-option options))))))))


;; Note 1: the second element of file-command-parse can be:
;;      pathname
;;    | PER-DIRECTORY-MENU
;;    | (default-pathname pathname)
;;    | (default-pathname PER-DIRECTORY-MENU)




;;; Transform-load-or-merge-options-if-appropriate, for the load-or-merge case,
;;; replaces load-or-merge-options with load-or-merge-options-plist, if appropriate.
;;; Note that load-or-merge-options always begins with the symbol |,|, an artifact of
;;; the list grammar, which is dropped during the following transformation.  For the
;;; save case, this form just transforms the one save option,
;;; INCLUDING-ALL-REQUIRED-MODULES, into option-plist.

(defun-void transform-load-or-merge-options-if-appropriate 
    (file-command-parse command-symbol load-or-merge-case-p)
  (cond
    (load-or-merge-case-p
     (let ((load-or-merge-options (third file-command-parse))
	   (load-or-merge-options-plist nil))
       (loop for indicator
		 in '(install-system-tables
		      reformat-as-appropriate
		      resolve-conflicts-automatically
		      update-before-loading)
	     when (memq indicator load-or-merge-options)
	       do (setq load-or-merge-options-plist
			(phrase-cons
			  indicator
			  (phrase-cons
			    't
			    load-or-merge-options-plist))))
       (loop for (indicator option)
		 in '((resolve-conflicts-automatically resolve-conflicts-manually)
		      (update-before-loading do-not-update-before-loading))
	     when (memq option load-or-merge-options)
	       do (setq load-or-merge-options-plist
			(phrase-cons
			  indicator
			  (phrase-cons
			    'nil
			    load-or-merge-options-plist))))
       (let ((what-to-do-after-loading-kb?
	       (if (memq 'warmboot-afterwards load-or-merge-options)
		   'warmboot-afterwards
		   (if (memq 'warmboot-afterwards-with-catch-up
			     load-or-merge-options)
		       'warmboot-afterwards-with-catch-up
		       (if (memq 'never-start-afterwards load-or-merge-options)
			   'never-start-afterwards
			   (if (memq 'start-afterwards load-or-merge-options)
			       'start-afterwards))))))
	 (if what-to-do-after-loading-kb?
	     (setq load-or-merge-options-plist
		   (phrase-cons
		     'what-to-do-after-loading-kb
		     (phrase-cons
		       what-to-do-after-loading-kb?
		       load-or-merge-options-plist)))))
       (setf (third file-command-parse)
	     load-or-merge-options-plist)))
    ((memq command-symbol '(kb-save save save-module save-module-into))
     (let ((tail (cddr file-command-parse)))
       (setf (cddr file-command-parse)
	     (phrase-list
	       (nconc (when (memq 'including-all-required-modules tail)
			(phrase-list 'including-all-required-modules t))
		      (when (memq 'using-clear-text tail)
			(phrase-list 'using-clear-text t))
		      (let ((log (loop for e in tail
				       when (and (consp e) (eq (car e) 'commit-after-saving))
					 return (cadr e))))
			(when log
			  (phrase-list 'commit-after-saving log)))
		      (when (memq 'emitting-c-code tail)
			(phrase-list 'emitting-c-code t)))))))))




;;; `Current-attribute-file-pathname?' ...

(def-system-variable current-attribute-file-pathname? kb-load1 nil)


;;; `Current-statistics-file-pathname?' ...

(def-system-variable current-statistics-file-pathname? kb-load1 nil)


;;; `Current-foreign-image-pathname?' ...

(def-system-variable current-foreign-image-pathname? kb-load1 nil) ;jh, 6/18/91.


;; ... see also current-kb-pathname?!



;;; 'Make-default-pathname' ...

;;; A `symbolic file type' is a symbol.  Currently, it can only be either
;;; ATTRIBUTE, STATISTICS, FOREIGN-IMAGE, or KB (or nil, which is
;;; equivalent to KB).

;;; A `file type' is a string for use, e.g., as a :type argument to
;;; make-pathname.

(defun make-default-pathname (symbolic-file-type?)
  (case symbolic-file-type?
    (attribute     current-attribute-file-pathname?)
    (statistics    current-statistics-file-pathname?)
    (foreign-image current-foreign-image-pathname?)
    (t (or default-kb-pathname? current-kb-pathname?))))



;;; `Make-default-file-type' ... returns a sharable string or nil.

;; jh, 9/3/91.  Changed make-default-file-type to return nil when we are getting
;; the file type of a foreign image in UNIX.  This is because there is a
;; difference between the empty string and nil there.  The empty string means that
;; there is an extension, so the delimiting dot should be supplied (as in
;; "/usr/jh/hello.") .  Nil, on the other hand, means that there is no extension
;; and the delimiter should not be supplied (as in "/usr/jh/hello").  The latter
;; looks better as a default foreign image, which is an executable UNIX file and
;; traditionally has no extension.

(defun make-default-file-type (symbolic-file-type?)
  (case symbolic-file-type?
    (xml #w"xml")
    (foreign-image #w"fgn")
    ((attribute statistics) #w"text")
    (log #w"log") ;jh, 11/12/91.
    (t #w"kb")))

;; jh, 1/29/92.  Changed make-default-file-type to return a file type of "fgn" for
;; foreign images.  It is next to impossible to adhere to the UNIX tradition of
;; executables without file types.  There is no way to distinguish foreign images
;; from other images in the same directory unless we impose this convention on
;; users.  As well, we cannot merge pathnames with
;; process-specific-system-pathname properly unless the foreign image has a
;; non-nil file-type.  This is because gensym-merge-pathnames isn't flexible
;; enough to tell the difference between a file type of nil that we don't want the
;; defaults to overwrite (as is the case here) and one that we do (the usual
;; case).


;;; `Get-current-user-name' ... returns either the user name from the OS as
;;; an interned lisp symbol, or the symbol USER.  The second value, made-up?,
;;; is true iff the symbol USER had to be returned because the OS's user name
;;; could not be obtained.

;; Get-current-user-name should be moved to PRIMITIVES as soon as it won't perturb
;; things.  jh, 1/11/91.

(defun get-current-user-name ()
  (let* ((foreign-user-name? (foreign-get-user-name)))
    (if foreign-user-name?
	(if (>f (text-string-length foreign-user-name?) 0)
	    (intern-text-string foreign-user-name?)
	    (progn
	      (reclaim-text-string foreign-user-name?)
	      (values 'user t)))
	(values 'user t))))





;;; `Handle-file-command' ... Symbolic-file-type? (optional) is passed on to
;;; make-default-pathname to produce the default pathname the user sees.

(defun-allowing-unwind handle-file-command
    (command-verb &optional symbolic-file-type? inconsistent-so-save-all? module-case?)
  (protected-let*
      ((for-save-p (and (char=w (charw command-verb 0) #.%\S)
			(char=w (charw command-verb 1) #.%\a)
			(char=w (charw command-verb 2) #.%\v)
			(char=w (charw command-verb 3) #.%\e)))
       (pathname-for-file-command
	 (get-pathname-for-file-command
	   symbolic-file-type?
	   inconsistent-so-save-all? module-case?
	   (or inconsistent-so-save-all? ; xml-prohibited-p
	       (and for-save-p (not module-case?))))
	 (reclaim-gensym-pathname pathname-for-file-command))
       (xml-pathname-p
	 (string-equalw #w"xml" (gensym-pathname-type pathname-for-file-command)))
       (namestring-for-file-command
	 (gensym-namestring pathname-for-file-command)
	 (reclaim-text-string namestring-for-file-command))
       (user-readable-namestring-for-file-command
	 namestring-for-file-command)
       (file-command-initial-text-line
	 (tformat-text-string
	   (if (and for-save-p xml-pathname-p module-case?)
	       "~a (~s by default), using clear text"
	       "~a (~s by default)")
	   command-verb user-readable-namestring-for-file-command)))
    (handle-command 'file-command file-command-initial-text-line)))



;;; `Get-pathname-for-file-command' ...

(defun-allowing-unwind get-pathname-for-file-command
    (symbolic-file-type? inconsistent-so-save-all? module-case? xml-prohibited?)
  (protected-let*
      ((pathname-for-file-command-1
	 (get-or-make-default-kb-pathname symbolic-file-type? xml-prohibited?)
	 (reclaim-gensym-pathname pathname-for-file-command-1))
       (base-name-pathname ; note 1
	 (gensym-pathname-name pathname-for-file-command-1))
       (base-name-string
	 (if (text-string-p base-name-pathname)
	     base-name-pathname
	     #w""))
       (base-name-string-prefix
	 (text-string-substring
	   base-name-string
	   0
	   (minf (text-string-length base-name-string) 4))
	 (reclaim-text-string base-name-string-prefix))
       (all-type-base-name-string-p
	 (string-equalw base-name-string-prefix #w"all-"))
       (derived-name-string
	 ;; get the file name for the module:
	 (cond
	   ;; if saving an inconsistent attempt a modularity ...
	   (inconsistent-so-save-all?
	    (if all-type-base-name-string-p
		(copy-text-string base-name-string)
		(tformat-text-string "ALL-~a" base-name-string)))
	   ;; if not saving a module at all ...
	   ((not (and module-case? (top-level-kb-module? module-information)))
	    (copy-text-string base-name-string))
	   ;; now we know we're saving a module; if there's an explicit save
	   ;; pathname in the installed module-information system table ...
	   ((kb-module-file-name? module-information)	; a string or symbol?
	    (copy-text-string
	      (stringw (kb-module-file-name? module-information))))
	   (t
	    (let*
		((module (top-level-kb-module? module-information))
		 (pathname? (get-true-pathname-of-module-if-any module))
		 (namestring-copy?
		   (and pathname?
			(let ((pathname-name
				(gensym-pathname-name pathname?)))
			  (if (text-string-p pathname-name)
			      (copy-text-string pathname-name)
			      (make-wide-string 0))))))
	      (if namestring-copy?		; see note. (MHD 12/12/94)
		  ;; if this module has been loaded from file ...
		  namestring-copy?
		  ;; otherwise, use the module name as the file name
		  (copy-symbol-name module nil)))))
	 (reclaim-text-string derived-name-string)))
    (gensym-merge-pathnames
      derived-name-string
      pathname-for-file-command-1)))

;; Note: to fix a complaint (HQ-106377) that if you load a KB whose file name is
;; foo, but it is actually module bar, it prompts you to save as "...bar.kb", we
;; will make use of a record we keep of which files were loaded for which modules
;; defaulting the name to the name of the file loaded for the module being saved,
;; if any.  See ML's comments in the bug. (MHD 12/12/94, and 3/22/95)

;; Note 1: sometimes a pathname can be :wild, but apparently nothing else weird.
;; See def-namestring-generator and def-filename-parser. 





;;; `Get-or-make-default-kb-pathname' returns the default pathname to supply to
;;; the load-kb and save-kb commands, as a gensym-pathname structure.
;;;
;;; The pathname name component is guaranteed to be non-nil; it must filled in
;;; with a non-empty string.
;;;
;;; Symbolic-file-type?, in nil or unspecified, becomes KB.

(defun-allowing-unwind get-or-make-default-kb-pathname (&optional symbolic-file-type? xml-prohibited?)
  (protected-let 
      ((user-name-as-file-name
	 (tformat-text-string "~a" (get-current-user-name))
	 (reclaim-text-string user-name-as-file-name))
       (current-default-pathname?
	 (make-default-pathname symbolic-file-type?))
       (returned-pathname 
	 (cond
	   (current-default-pathname?
	    (gensym-make-pathname
	      :defaults current-default-pathname?
	      :type (let ((type (gensym-pathname-type current-default-pathname?)))
		      (if (and (text-string-p type)
			       (string-equalw type #w"xml")
			       xml-prohibited?)
			  #w"kb"
			  (if (eq symbolic-file-type? 'xml)
			      #w"xml"
			      type)))
	      :version :newest))
	   (current-kb-pathname?
	    (gensym-make-pathname
	      :defaults current-kb-pathname?
	      :type (make-default-file-type symbolic-file-type?)
	      :version :newest))
	   ;; Boondoggle: allow an alternate default pathname for load-kb.
	   #+(and lucid development)
	   ((lcl:environment-variable "DEFAULT_KB_PATHNAME")	    
	    (gensym-pathname (lcl:environment-variable "DEFAULT_KB_PATHNAME")))
	   (t	    
	    (gensym-make-pathname ;copies its args
	      :name user-name-as-file-name
	      :type (make-default-file-type symbolic-file-type?)
	      :version :newest
	      :defaults process-specific-system-pathname)))))
    ;; guarantee at least a name; here, it can be nil either rarely or not at
    ;; all [document exactly when some day!]:
    (when (null (gensym-pathname-name returned-pathname))
      (setq returned-pathname
	    (prog1 (gensym-make-pathname
		     :name user-name-as-file-name
		     :defaults returned-pathname)
	      (reclaim-gensym-pathname returned-pathname))))
    returned-pathname))
















;; Move elsewhere?! (MHD 2/19/92)



(def-class (file-command command)
  (box-translation-and-text
    nil (type file-command text)))





;;;; New Handling of File Commands



;;; The class `kb-load-file-command' ...
;;;
;;; The box-translation-and-text slot of a file command corresponds to the edit
;;; box in which the file name is typed in.  Its grammar category is
;;; generic-file-pathname.
;;;
;;; Its editing is very non-standard, although it is hoped that it will feel
;;; natural to the user. Parsing is done not only by the editor, but also by the
;;; pathname parser, and a little bit by hand.  In addition, we employ custom
;;; menus that insert in their own way, custom punctuation alists, custom name
;;; directories managed online while parsing, and display custom blocks, namely
;;; several check boxes and a table displaying this item.
;;;
;;; The table is displayed right under the edit box, and shows the only two
;;; user-visible slots, `current-directory-contents-statistics?' and
;;; `current-directory-namestring-for-file-command?', which are displayed without
;;; their names.
;;;
;;; The display usually looks has this format:
;;; 
;;;   line 1: directory pathname
;;;   line 2: number of directories & files
;;;   
;;; Example:
;;;   /tmp_mnt/home/mhd
;;;   20 Directories, 137 Files
;;;
;;; This information is usually in synch with the slot
;;; `gensym-pathnames-under-current-directory?', which stores a path list of
;;; gensym pathnames, needing custom reclaimer.  When the later slot is not yet
;;; filled in, the former slot should be nil.  In that state, the writer for
;;; the former slot writes
;;;
;;;   (contents unknown)
;;;
;;; When the directory is being searched, the value of the former slot should
;;; be 0, and in that case, the writer writes
;;;
;;;   (contents unknown; obtaining directory ...)
;;;
;;; When the directory search completes, it fills the former slot with a
;;; slot-value list of the form
;;;
;;;   (<number-of-directories> <number-of-files>)
;;;
;;; as well as filling the later slot with the directory.  The filler, in
;;; addition, maintains two name directories: file-name and directory-name.
;;;
;;; ...

(def-class (kb-load-file-command file-command)
  (box-translation-and-text nil (type generic-file-pathname text))

  (current-directory-namestring-as-text-string-for-file-command? ; a text string, converted from
    nil (type file-command-directory-namestring-as-text-string?) ;   ASCII (or, some day, the encoding
    not-user-editable)			          ;   used by the file system)
  (current-directory-namestring-for-file-command?
    nil)				; same, raw-string version of the above
  
  (current-namestring-as-text-string-for-file-command? nil) ; same, but the whole namestring,
					;   as a legal text string
  
  (current-directory-contents-statistics? ; nil for none; 0 for searching; or a list,
    nil (type directory-contents-statistics?) ; (<number-of-directories> <number-of-files>)
    not-user-editable)

  ;; phase in!!
  (gensym-pathnames-under-current-directory? nil)

  (file-command-directory-search-cache? nil) ; don't save, don't show

  
  (load-command-file-types ("{kK}{bBlL}")) ; :WILD ok; make changeable later!

  (merging-kb-is-the-default? nil)

  (retain-current-directory-menus-p nil))

;; jh, 4/18/95.  Added the retain-current-directory-menus-p slot to the class
;; kb-load-file-command.  The intent is that the file and directory prompts
;; disappear unless the user chose to load the KB, meaning that the user
;; probably wants to retain those prompts by default.

(def-slot-value-reclaimer file-command-directory-search-cache?
    (directory-search-cache?)
  (when directory-search-cache?
    (reclaim-directory-search-cache directory-search-cache?)))

(def-slot-value-reclaimer gensym-pathnames-under-current-directory?
    (gensym-pathname-list)
  (reclaim-path-list-of-gensym-pathnames gensym-pathname-list))


;;; The class method add-items-to-edit-workspace is defined now for
;;; subclasses of kb-load-file-command (later, other frames?!).
;;;
;;; Refresh-case? is used when the items have been added already, but
;;; some have been deleted.  It is up to the application to decide
;;; how to interret refresh-case?, i.e., how to decide what does
;;; or doesn't need to be added.

(def-class-method add-items-to-edit-workspace
    (kb-load-file-command edit-workspace edit-box refresh-case?)
  ;; If it's the refresh case, shift the items we're maintaining
  ;; on the workspace, if necessary.  Otherwise, put up the
  ;; items: the table representing the file command, and the
  ;; check boxes.
  (cond
    (refresh-case?
     (move-file-command-items-if-necessary
       kb-load-file-command edit-workspace edit-box))
    (t
     (make-load-command-items-and-add-to-workspace
       kb-load-file-command edit-workspace edit-box))))

;; Consider having two separate menus for the directories and the files.  The
;; "../" (up-one) directory would presumably then always be in the directory
;; menu.  Ultimately, separate scroll boxes for files, directories, and drives
;; the ability to delete files and create directories



;;; `Move-file-command-items-if-necessary' is used to move the group of items
;;; associated with file-command on an edit workspace to a new position, if they
;;; are not at the "right" position, i.e., due to expansion of the edit box.
;;;
;;; Here, they want to be aligned with the left edge of the text box, and a few
;;; units (10) below it.

(defun move-file-command-items-if-necessary
    (file-command workspace edit-box)  
  (loop with left-edge = (left-edge-of-block edit-box)
	with top-edge = (+w (bottom-edge-of-block edit-box) 10)
	for subblock being each subblock of workspace
	when (and (frame-of-class-p subblock 'table)
		  (memq subblock
			(frame-representations file-command)))
	  return
	  (let ((delta-y
		 (-w top-edge (top-edge-of-block subblock)))
		(delta-x
		 (-w left-edge (left-edge-of-block subblock))))
	    (unless (and (=w delta-y 0) (=w delta-x 0))
	      (move-block subblock delta-x delta-y)
	      (loop for subblock being each subblock of workspace
		    when (frame-of-class-p subblock 'check-box)
		      do (move-block subblock delta-x delta-y))))))

(defun-allowing-unwind do-pathname-component-conversion
    (original-pathname merged-pathname? cursor-should-retreat-p)
  (when merged-pathname?
            
    ;; jh, 8/31/94.  Well, the replace-empty-components merge-pathnames rule bit
    ;; us here.  The intent of this rule was to prevent bad pathname merging in
    ;; VMS when the device component was actually a logical name that expanded
    ;; into a partial directory.  But at this point in the code, we have
    ;; inherited the device name from a previous filename supplied by the user
    ;; to the KB-loading editor.  And we know this device is in concord with the
    ;; directory, since we are checking each directory component as the user
    ;; types it in.  So we merge the device component by hand here.
    (when (eq local-file-system 'vms)
      (unless (gensym-pathname-device merged-pathname?)
	(setf (gensym-pathname-device merged-pathname?)
	      (copy-pathname-contents
		(gensym-pathname-device original-pathname)))))
    
    (protected-let*
	((new-namestring-text
	   (gensym-namestring merged-pathname?)
	   (reclaim-text-string new-namestring-text))
	 (new-namestring
	   (copy-text-string new-namestring-text)
	   (reclaim-text-string new-namestring))
	 (text-tail (text-being-edited current-edit-state))
	 (line-index 1)
	 (character-index 0))
      (multiple-value-bind (line-index-at-end character-index-at-end)
	  (find-end-of-text text-tail line-index)
	(insert-text-string-in-text-being-edited
	  new-namestring nil nil
	  line-index character-index text-tail
	  line-index-at-end character-index-at-end)
	;; Place cursor just before closing right-bracket or just after end
	;; of filename.
	(when cursor-should-retreat-p
	  (move-or-delete-from-cursor nil t nil))
	(return-from do-pathname-component-conversion t))))
  (return-from do-pathname-component-conversion nil))

(defun-void clear-load-command-directory-information (kb-load-file-command)
  (reclaim-path-list-of-gensym-pathnames
    (gensym-pathnames-under-current-directory? kb-load-file-command))
  (setf (gensym-pathnames-under-current-directory? kb-load-file-command)
	nil)
  (change-slot-value
    kb-load-file-command
    'current-directory-contents-statistics?
    nil)
  (clear-file-and-directory-name-directories kb-load-file-command))

;;; The function `do-pathname-component-conversion-if-necessary' returns non-nil
;;; if conversion was done, nil otherwise.

(defun-allowing-unwind do-pathname-component-conversion-if-necessary
    (text-tail? text-string-to-insert?)
  (cond
    ((and text-tail? text-string-to-insert?)
     (protected-let*
	 ((vms-directory-filenames-can-dangle-p t)
	  (pathname-text
	    (convert-text-to-text-string
	      (text-being-edited current-edit-state))
	    (reclaim-text-string pathname-text))
	  (pathname-ascii		; ref. to ASCII is obsolete! (MHD 2/22/96)
	    (copy-text-string pathname-text)
	    (reclaim-text-string pathname-ascii))
	  (ascii-to-insert
	    (copy-text-string text-string-to-insert?)
	    (reclaim-text-string ascii-to-insert))
	  (merged-pathname?
	    (gensym-merge-pathnames ascii-to-insert pathname-ascii)
	    (reclaim-gensym-pathname merged-pathname?))
	  (kb-load-file-command (frame-being-edited? current-edit-state)))

       (when merged-pathname?
	 (setq merged-pathname?
	       (resolve-directory/file-ambiguities-in-kb-load-file-command
		 kb-load-file-command
		 merged-pathname?)))
       
       (clear-load-command-directory-information kb-load-file-command)
      
       (cond
	 ((or (eq local-file-system 'vms)
	      (gensym-wild-pathname-p pathname-ascii))
	  (protected-let ((original-pathname?
			    (gensym-pathname pathname-ascii)
			    (reclaim-gensym-pathname original-pathname?)))
	    (if original-pathname?
		(do-pathname-component-conversion
		    original-pathname?
		  merged-pathname?
		  t ;cursor-should-retreat-p
		  )
		nil)))
	 ((g2-stream-directory-p pathname-ascii)
	  (let ((directory-pathname?
		  (gensym-file-as-directory pathname-ascii)))
	    (if directory-pathname?
		(do-pathname-component-conversion
		  directory-pathname?
		  merged-pathname?
		  nil ;cursor-should-retreat-p
		  )
		nil)))
	 (t nil))))
    (t nil)))


;;; `Move-block' ...

(defun move-block (block delta-x delta-y)
  (erase-images-of-block block nil)
  (shift-block block delta-x delta-y)
  (enlarge-workspace-for-block-rectangle-if-necessary block nil)
  (draw-images-of-block block nil))

;; Obviously a function that should have been written long ago, and doesn't
;; belong here...




(defun make-load-command-items-and-add-to-workspace
    (file-command workspace edit-box)
  (let* ((left-edge (left-edge-of-block edit-box))
	 (top-edge (+w (bottom-edge-of-block edit-box) 10))
	 (current-directory-information-text-table
	   (make-attributes-table
	     file-command
	     'file-command-info-table-format
	     nil
	     (choose-font-format-per-fonts-table
	       'file-command-attribute-value-format
	       'font-for-editing)
	     nil
	     '(current-directory-contents-statistics?
	       current-directory-namestring-as-text-string-for-file-command?)
	     nil
	     '(current-directory-contents-statistics?
	       current-directory-namestring-as-text-string-for-file-command?))))
    (add-to-workspace
      current-directory-information-text-table workspace
      left-edge top-edge t t)
    (setf (token-menu-class-per-category-overrides? current-edit-state)
	  (get-token-menu-class-per-category-overrides-for-file-command))
    (setf (extra-space-to-leave-below-edit-box? current-edit-state)
	  (height-of-block
	    current-directory-information-text-table))
    (setq top-edge
	  (+w (bottom-edge-of-block current-directory-information-text-table)
	      10))
    ;; maybe these belong elsewhere:
    (setf (maximum-number-of-names-for-a-menu-override?
	    current-edit-state)
	  100000)			; i.e., unlimited
    (setf (punctuation-alist-subset-override? current-edit-state)
	  file-name-punctuation-alist)
;    (setf (complex-character-punctuation-alist-subset-override?
;	    current-edit-state)
;	  file-name-complex-character-punctuation-alist)
    (loop with column-top-edge = top-edge
	  with column-right-edge-so-far = left-edge
	  for column from 0 to 1
	  do
      (loop for row
		in '(("start afterwards"
		      starting-afterwards

		      "never start afterwards"
		      not-starting-afterwards)

		     ("warmboot afterwards"
		      warmbooting-afterwards

		      "warmboot afterwards with catch-up feature"
		      warmbooting-afterwards-with-catch-up)
		     
		     ("merge in this KB"
		      merge-kb

		      "merge in this KB and install its system tables"
		      merge-kb-and-install-system-tables)

		     ("bring formats up-to-date"
		      bring-formats-up-to-date
		      
		      "automatically resolve conflicts"
		      automatically-resolving-conflicts)

		     ("update from source code control before loading"
		      update-before-loading))
	    ;; first three above are mutually exclusive, i.e., should
	    ;; be radio buttons, sort of (with one more button saying
	    ;; "nothing afterwards" which is on by default); plus, we're
	    ;; missing the warmboot catchup mode; plus the merge case
	    ;; should eventually be merged in here.  (MHD 7/9/93)
	    for (label name) = (nthcdr (+f column column) row)
	    as check-box
	       = (unless (or (null label)
			     (and (eq name 'update-before-loading)
				  (not source-code-control-support-enabled-p)))
		   (make-button 'check-box (copy-text-string label) name t nil nil t))
	    do (when check-box
		 (case name
		   (merge-kb
		    (if (merging-kb-is-the-default? file-command)
			(change-on/off-switch check-box t)))
		   (automatically-resolving-conflicts
		    (if automatically-resolve-conflicts-by-default
			(change-on/off-switch check-box t)))
		   (update-before-loading
		    (if update-before-loading-by-default
			(change-on/off-switch check-box t)))
		   ;; others?
		   )
		 (add-to-workspace
		  check-box workspace left-edge top-edge t nil)
		 (multiple-value-bind
		     (left-edge top-edge right-edge bottom-edge)
		     (determine-extreme-edges-of-block check-box)
		   (declare (ignore left-edge top-edge))
		   (setf (extra-space-to-leave-below-edit-box?
			  current-edit-state)
			 (maxw
			  (extra-space-to-leave-below-edit-box?
			   current-edit-state)
			  (-w (+w bottom-edge 10)
			      (bottom-edge-of-block edit-box))))
		   (unless (eq name 'update-before-loading)
		     (setq column-right-edge-so-far
			   (maxw column-right-edge-so-far
				 right-edge))))
		 (setq top-edge
		       (+w (bottom-edge-of-block check-box) 10))))
      (setf left-edge
	    (+w column-right-edge-so-far 10))
      (setq top-edge column-top-edge))))



;;; The function `resolve-directory/file-ambiguities-in-kb-load-file-command'
;;; takes two arguments: a kb-load-file-command and a gensym-pathname giving the
;;; current default directory visible to the user.  It modifies the following
;;; slots in the kb-load-file-command:

;;;   current-directory-namestring-for-file-command?
;;;   current-directory-namestring-as-text-string-for-file-command?
;;;   current-namestring-as-text-string-for-file-command?

;;; This function returns the gensym-pathname used to modify the slots in the
;;; kb-load-file-command.  This function acquires ownership of the
;;; gensym-pathname argument, in the sense that the original gensym-pathname
;;; argument is reclaimed if a new gensym-pathname had to be created,

(defun-simple resolve-directory/file-ambiguities-in-kb-load-file-command
    (kb-load-file-command gensym-pathname)
  (let ((namestring-as-text-string
	  (gensym-namestring-as-text-string gensym-pathname))
	(wild-pathname-p (gensym-wild-pathname-p gensym-pathname)))
    
    ;; If there is a name component, but it's for a directory, just change the
    ;; pathname over so the name component looks like the last subdirectory,
    ;; rather than a file name.  (If this were not done, the probe-file below
    ;; would succeed, at least on UNIX, for a directory, and then we'd pass
    ;; along a request to load the KB from a "file" that was really a directory,
    ;; and things would break....)
    (unless wild-pathname-p
      (when (and (gensym-pathname-name gensym-pathname)
		 (current-namestring-as-text-string-for-file-command?
		   kb-load-file-command)
		 (if (eq (gensym-pathname-file-system gensym-pathname)
			 'unix)
		     ;; The following call to gensym-probe-file can only be
		     ;; used on UNIX since e.g. on NT directories are not
		     ;; files in the same way they are on UNIX, and so
		     ;; gensym-probe-file might return NIL on NT where it
		     ;; would return non-NIL on UNIX. - jpg quoting yduj 10/11/00
		     (let ((truename?
			     ;; Call to gensym-probe-file added so that e.g.
			     ;; Load KB ~/kbs  gets ~-expanded. - jpg 9/29/00
			     (gensym-probe-file gensym-pathname))
			   temporary-namestring)
		       (when truename?
			 (setq temporary-namestring 
			       (gensym-namestring truename?))
			 (reclaim-gensym-pathname truename?)
			 (prog1
			     (g2-stream-directory-p temporary-namestring)
			   (reclaim-text-string temporary-namestring))))
		     (let ((temporary-namestring 
			     (gensym-namestring gensym-pathname)))
		       (prog1
			   (g2-stream-directory-p temporary-namestring)
			 (reclaim-text-string temporary-namestring)))))
	(setq gensym-pathname
	      (prog1 (or (gensym-file-as-directory gensym-pathname)
			 (make-empty-gensym-pathname))
		(reclaim-gensym-pathname gensym-pathname)))
	(setq namestring-as-text-string
	      (prog1 (gensym-namestring-as-text-string gensym-pathname)
		(reclaim-text-string namestring-as-text-string)))))
    
    (change-slot-value
      kb-load-file-command
      'current-directory-namestring-for-file-command?
      (gensym-directory-and-above-namestring gensym-pathname))
    (change-slot-value
      kb-load-file-command
      'current-directory-namestring-as-text-string-for-file-command?
      (if wild-pathname-p
	  (gensym-namestring-as-text-string gensym-pathname)
	  (gensym-directory-and-above-namestring-as-text-string
	    gensym-pathname)))
    (change-slot-value
      kb-load-file-command
      'current-namestring-as-text-string-for-file-command?
      namestring-as-text-string)
    gensym-pathname))

;;; The `handle-end-operation method for kb-load-file-command' ...

(def-class-method handle-end-operation
    (kb-load-file-command workstation-context)
  (let* ((edit-state (specific-structure-for-workstation-context workstation-context))
	 (edit-text-as-string
	   (convert-text-to-text-string (text-being-edited edit-state)))
	 (edit-text-as-token?
	   (read-from-text-string edit-text-as-string))
	 (dwimified-edit-text-as-string
	   (if (text-string-p edit-text-as-token?)
	       edit-text-as-token?
	       (copy-text-string edit-text-as-string)))
	 (filename-text-string
	   (text-string-trim '(#.%Space #.%Newline) dwimified-edit-text-as-string))
	 (vms-directory-filenames-can-dangle-p t)
	 (gensym-pathname?
	   (gensym-merge-pathnames
	     filename-text-string
	     (current-directory-namestring-for-file-command?
	       kb-load-file-command)))
	 (probed-pathname? nil))
    (reclaim-text-string edit-text-as-string)
    ;; If gensym-pathname? is nil, ascii-filename is reclaimed in the
    ;; cond-clause in this function below.
    (reclaim-text-string filename-text-string)
    (when (not (text-string-p edit-text-as-token?))
      (reclaim-text-string dwimified-edit-text-as-string))

    (let ((possibly-new-gensym-pathname
	    (resolve-directory/file-ambiguities-in-kb-load-file-command
	      kb-load-file-command
	      gensym-pathname?)))
      ;; When we created a new pathname (because we detected that the name of a
      ;; file actually named a directory) ...
      (unless (eq gensym-pathname? possibly-new-gensym-pathname)
	(setq gensym-pathname? possibly-new-gensym-pathname)
	;; jh, 4/19/95.  In UNIX and NT, might have to add a trailing slash so
	;; subsequent insertions work right.  In VMS, might have to add a
	;; closing square bracket and position the insertion cursor
	;; appropriately.
	(let ((new-namestring
		(current-namestring-as-text-string-for-file-command?
		  kb-load-file-command))
	      (text-tail (text-being-edited current-edit-state))
	      (line-index 1)
	      (character-index 0))
	  (multiple-value-bind (line-index-at-end character-index-at-end)
	      (find-end-of-text text-tail line-index)
	    (insert-text-string-in-text-being-edited
	      new-namestring nil nil
	      line-index character-index text-tail
	      line-index-at-end character-index-at-end)
	    (when (eq local-file-system 'vms)
	      (move-or-delete-from-cursor nil t nil))))))
    
    ;; Need to call this to get screen update to happen before diving into a
    ;; directory search.
    (force-process-drawing)
    
    (cond
      ((and gensym-pathname?
	    (or (gensym-wild-pathname-p gensym-pathname?)
		(null (gensym-pathname-name gensym-pathname?))))  ; assumed to be valid
       ;; Change these first to provide immediate feedback to user:
       (change-slot-value
	 kb-load-file-command 'current-directory-contents-statistics?
	 0)

       ;; Need to call this to get screen update to happen before diving into a
       ;; directory search.
       (force-process-drawing)
       
       (funcall-method-if-any
	 'add-items-to-edit-workspace
	 kb-load-file-command
	 (edit-workspace current-edit-state)
	 (edit-box current-edit-state)
	 t)
       (set-up-load-command-directory-information
	 kb-load-file-command gensym-pathname?)
       (reclaim-gensym-pathname gensym-pathname?)
       t) ;t to remain in editor
      ((and gensym-pathname?
	    (null (setq probed-pathname?
			(gensym-probe-file gensym-pathname?)))) ; true for directories, too
       (display-editor-notification
	   "Cannot find ~s"
	 (current-namestring-as-text-string-for-file-command? kb-load-file-command))
       :display-notification) ;to remain in editor (after notification)
      (gensym-pathname?
       (when (gensym-pathname-p probed-pathname?)
	 (reclaim-gensym-pathname probed-pathname?))
       (setf (retain-current-directory-menus-p kb-load-file-command) t)
       ;; Following form deletes the kb-load-file-command frame by unwinding a
       ;; workstation context.
       (load-or-merge-kb-from-file-command
	 gensym-pathname? (edit-workspace current-edit-state)))
      (t ;gensym-merge-pathnames couldn't parse -- returned nil
       (when (gensym-pathname-p probed-pathname?)
	 (reclaim-gensym-pathname probed-pathname?))
       (display-editor-notification
	   "~s is not a file or directory name"
	 filename-text-string)
       (reclaim-text-string filename-text-string)
       :display-notification)))) ;to remain in editor (after notification)

(def-class-method cleanup (kb-load-file-command)
  (funcall-superior-method kb-load-file-command)
  (unless (retain-current-directory-menus-p kb-load-file-command)
    (clear-load-command-directory-information kb-load-file-command)))



(defun load-or-merge-kb-from-file-command (gensym-pathname edit-workspace)
  (multiple-value-bind
      (bring-formats-up-to-date? warmboot-case? auto-merge-case?
				 install-system-tables-if-merge-case?
				 what-to-do-after-loading-kb? merge-kb?
				 update-before-loading?)
      (get-button-settings-for-file-command #'get-file-command-check-box-value edit-workspace)
    (abort-current-workstation-context 'editing) ; gets rid of editor -- note
					;   that this is not necessary.  It may
					;   be convenient to allow repeated
					;   merge (or other) operations;
					;   consider this later!
    (load-or-merge-kb-if-ok
      gensym-pathname			; pathname
      (if merge-kb?			; load-case?
	  nil
	  (if (empty-kb-p) t 'replace))
      bring-formats-up-to-date?	; bring-formats-up-to-date?
      warmboot-case?			; warmboot-case?
      auto-merge-case?		; auto-merge-case?
      install-system-tables-if-merge-case? ; install-system-tables-if-merge-case?
      what-to-do-after-loading-kb?
      update-before-loading?)))



(defun get-file-command-check-box-value (edit-workspace button-name)
  (loop for subblock being each subblock of edit-workspace
	when (and (frame-of-class-p subblock 'check-box)
		  (eq (get-primary-name-for-frame-if-any subblock) button-name))
	  return (on/off-switch-on-p subblock)))
  

(defun get-button-settings-for-file-command (getter arg)
  (let* ((bring-formats-up-to-date?
	   (funcall getter
	     arg 'bring-formats-up-to-date))
	 (auto-merge-case?
	   (funcall getter
	     arg 'automatically-resolving-conflicts))
	 (warmboot-case?
	   (if (funcall getter
		 arg 'warmbooting-afterwards)
	       'warmboot-afterwards
	       (if (funcall getter
		     arg
		     'warmbooting-afterwards-with-catch-up)
		   'warmboot-afterwards-with-catch-up)))
	 (what-to-do-after-loading-kb?
	   (cond
	     (warmboot-case? warmboot-case?)
	     ((funcall getter
		arg 'starting-afterwards)
	      'start-afterwards)
	     ((funcall getter
		arg 'not-starting-afterwards)
	      'never-start-afterwards)))
	 (merge-kb-and-install-system-tables?
	   (funcall getter
	     arg 'merge-kb-and-install-system-tables))
	 (merge-kb?
	   (or merge-kb-and-install-system-tables?
	       (funcall getter arg 'merge-kb)))
	 (update-before-loading?
	   (and source-code-control-support-enabled-p
		(funcall getter
		  arg 'update-before-loading))))
    (values
      bring-formats-up-to-date?
      warmboot-case?
      auto-merge-case?
      merge-kb-and-install-system-tables?
      what-to-do-after-loading-kb?
      merge-kb?
      update-before-loading?)))  


(defun make-and-set-up-kb-load-file-command (merge-case?)
  (let* ((kb-load-file-command (make-text-box 'kb-load-file-command))
	 (default-pathname (get-or-make-default-kb-pathname)))
    (when (box-translation-and-text kb-load-file-command)
      (reclaim-slot-value (box-translation-and-text kb-load-file-command)))

    (setf (box-translation-and-text kb-load-file-command)
	  (slot-value-cons
	    no-value
	    (if (null current-kb-pathname?)
		(slot-value-list
		  (make-lost-spaces-text-element 0)
		  (gensym-directory-and-above-namestring-as-text-string
		    default-pathname))
		(nconc 
		  (if (not (gensym-pathname-name
			     default-pathname)) ; ends with name?
		      (slot-value-list (make-lost-spaces-text-element 0)))
		  (slot-value-list
		    (gensym-namestring-as-text-string default-pathname))))))

    (set-up-load-command-directory-information
      kb-load-file-command
      default-pathname; (get-or-make-default-kb-pathname)
      t
      merge-case?)
    (reclaim-gensym-pathname default-pathname)
    kb-load-file-command))




	 
     
	  


(defun-allowing-unwind set-up-load-command-directory-information
    (kb-load-file-command gensym-pathname
     &optional dont-search-directory? merge-case?)
  (with-file-system-directory-search-cache
      (:wildcard-string "*"
       :initial-cache-contents
         (file-command-directory-search-cache? kb-load-file-command))
    (setf (current-directory-namestring-for-file-command? kb-load-file-command)
	  (gensym-directory-and-above-namestring gensym-pathname))
    (setf (current-directory-namestring-as-text-string-for-file-command? kb-load-file-command)
	  (if (gensym-wild-pathname-p gensym-pathname)
	      (gensym-namestring-as-text-string gensym-pathname)
	      (gensym-directory-and-above-namestring-as-text-string gensym-pathname)))
    (setf (current-namestring-as-text-string-for-file-command? kb-load-file-command)
	  (gensym-namestring-as-text-string gensym-pathname))
    (setf (merging-kb-is-the-default? kb-load-file-command) merge-case?)
    (unless dont-search-directory?
      (reclaim-path-list-of-gensym-pathnames
	(gensym-pathnames-under-current-directory? kb-load-file-command))
      (setf (gensym-pathnames-under-current-directory? kb-load-file-command)
	    (get-load-command-directory
	      kb-load-file-command
	      (and (gensym-wild-pathname-p gensym-pathname)
		   (copy-gensym-pathname gensym-pathname))))
      (set-up-current-directory-information-text-based-on-other-slots
	kb-load-file-command)
      (set-up-file-and-directory-name-directories kb-load-file-command)
      (setf (file-command-directory-search-cache? kb-load-file-command)
	    (seize-file-system-directory-search-cache)))))

(defun namestring-is-xml-file-p (text-string)
  (let ((length-4 (-f (lengthw text-string) 4)))
    (prog1 (and (<= 1 length-4)
		(text-string-search #w".xml" text-string length-4 nil)) ; case insensitive
      (reclaim-text-string text-string))))

(defun get-load-command-directory (load-command user-supplied-wild-pathname?)
  (let ((current-directory-namestring
	  (current-directory-namestring-for-file-command? load-command)))
    (if user-supplied-wild-pathname?
	(gensym-directory-using-cache user-supplied-wild-pathname? t)
	(loop with match-regular-expression-for-g2-stream-directory-hook
		= (when (enable-loading-clear-text-kbs-p)
		    'namestring-is-xml-file-p)
	      for file-type in (load-command-file-types load-command)
	      as wild-gensym-pathname
	      = (gensym-make-pathname
		  :defaults
		  current-directory-namestring
		  :name :wild
		  :type file-type)
	      as first-time? = t then nil
	      nconc
	      (gensym-directory-using-cache
		wild-gensym-pathname
		first-time?)))))

  
(def-system-variable all-file-namestrings-in-directory-of-names kb-load1
  nil)				; a slot value list

(def-system-variable all-directory-namestrings-in-directory-of-names kb-load1
    nil)				; a slot value list

(def-system-variable defaults-namestring-for-directory-of-names? kb-load1
    nil) 				; a slot value

(defun-void clear-file-and-directory-name-directories (file-command)
  (loop for namestring in all-file-namestrings-in-directory-of-names
	do (delete-from-directory-of-names namestring 'file-name))
  (loop for namestring in all-directory-namestrings-in-directory-of-names
	do (delete-from-directory-of-names namestring 'directory-name))
  (setq all-directory-namestrings-in-directory-of-names
	(prog1 nil
	  (reclaim-slot-value
	    all-directory-namestrings-in-directory-of-names)))
  (setq all-file-namestrings-in-directory-of-names
	(prog1 nil
	  (reclaim-slot-value
	    all-file-namestrings-in-directory-of-names)))
  (let ((current-directory-namestring?
	  (current-directory-namestring-for-file-command? file-command)))
    (when current-directory-namestring?
      (setq defaults-namestring-for-directory-of-names?
	    (prog1 
		(copy-text-string current-directory-namestring?)
	      (reclaim-slot-value
		defaults-namestring-for-directory-of-names?))))))

(defun set-up-file-and-directory-name-directories (file-command)
  (clear-file-and-directory-name-directories file-command)
  (update-name-directories-per-file-command file-command))

(defun update-name-directories-per-file-command (file-command)
  (loop for gensym-pathname
	    in (gensym-pathnames-under-current-directory? file-command)
	as enough-namestring-as-text-string
	= (gensym-enough-namestring-as-text-string
	    gensym-pathname
	    (current-directory-namestring-for-file-command? file-command))
	as directory-p = (null (gensym-pathname-name gensym-pathname))
	do (cond
	     ((string=w enough-namestring-as-text-string #w"")
	      (reclaim-text-string enough-namestring-as-text-string))
	     (t
	      (let ((nicer-enough-namestring-as-text-string
		      (tformat-text-string
			"~a~a"
			enough-namestring-as-text-string
			(if directory-p
			    #w""
			    #w" ")))) ; add extra space after file names
		(reclaim-text-string enough-namestring-as-text-string)			 
		(add-to-directory-of-names
		  nicer-enough-namestring-as-text-string		; string owned by directory
		  (if directory-p 'directory-name 'file-name))
		(cond
		  (directory-p
		   (slot-value-push
		     nicer-enough-namestring-as-text-string
		     all-directory-namestrings-in-directory-of-names))
		  (t
		   (slot-value-push
		     nicer-enough-namestring-as-text-string
		     all-file-namestrings-in-directory-of-names))))))))

;; An alternative to having a "nicer" namestring with an extra space for
;; file names, but not for directories, would be to have a new kind of token
;; menu type that only added space at the end, but that would be work, and it
;; would have to be a per-category token type, and they really aren't yet
;; working. (MHD 4/17/94)

;; Have a "complete-file-pathname" category, which would insert itself by
;; replacing the entire text, with an extra space at the end, and would get
;; added to it all the directories you've gone to so far, and maybe some initial
;; default ones.  To do this, per-category menus are needed.  (MHD 4/17/94)

  
;; Phase in! =>
(def-slot-value-writer file-command-directory-namestring-as-text-string? (value)
  (if (null value)
      (tformat "(directory unknown)")
      (tformat "~a" value)))


;; Phase in! =>
(def-slot-value-writer directory-contents-statistics? (value)
  (cond
    ((or (null value) (eql value 0))
     (tformat
       "(contents unknown~a)"
       (if (eql value 0)
	   #w"; obtaining directory ..."
	   #w"")))
    ((consp value)
     (let ((number-of-directories (first value))
	   (number-of-files (second value)))
       (tformat
	 "~d Director~a, ~d File~a"
	 number-of-directories
	 (if (=f number-of-directories 1) #w"y" #w"ies")
	 number-of-files
	 (if (=f number-of-files 1) #w"" #w"s"))))))


(defun set-up-current-directory-information-text-based-on-other-slots
  (kb-load-file-command)
  (loop for gensym-pathname
	    in (gensym-pathnames-under-current-directory? kb-load-file-command)
	as directory-p = (null (gensym-pathname-name gensym-pathname))
	count directory-p into number-of-directories
	count (not directory-p) into number-of-files
	finally
	  (change-slot-value
	    kb-load-file-command 'current-directory-contents-statistics?
	    (slot-value-list number-of-directories number-of-files))))


;; NEW FILE DIALOG STUFF ENDS HERE. (MHD 8/18/93)


(def-class (init-file-command command)
  (box-translation-and-text
    nil (type init-file-command text)))



;;; `Execute-command' ...

(def-class-method execute-command (file-command)
  (execute-file-command file-command))

(def-class-method execute-command (init-file-command)
  (case (car (box-translation-and-text init-file-command))
    (start-g2					; will be tested
     nil)					;   in do-init-file
						;   and performed there
    (t	  
     (execute-file-command init-file-command))))






;;; `Execute-file-command' ...


;; jh, 11/12/91.  Abstracted make-first-time-default-pathname since it is also
;; used in the set-default-directory system procedure in FILE-IO.
;; Make-first-time-default-pathname needs to reclaim user-name but not the result
;; of make-default-file-type, which contains cached strings.  Note that
;; get-current-user-name interns a symbol and so won't leak unless the G2 user is
;; doing something very bizarre with the USER environment variable.

(defun-allowing-unwind make-first-time-default-pathname (symbolic-file-type)
  (protected-let 
      ((user-name
	 (tformat-text-string 
	   "~a" 
	   (get-current-user-name))
	 (reclaim-text-string user-name)))
    (gensym-make-pathname
      :name     user-name
      :type     (make-default-file-type symbolic-file-type)
      :version  :newest
      :defaults process-specific-system-pathname)))



;;; `Probe-for-kb-named-by-text-string' takes a gensym text string, merges it
;;; with the current default pathname, and probes for it.  If it finds it, it
;;; returns a new gensym pathname to be owned by the caller.  Otherwise, it
;;; returns nil.
;;;
;;; `Probe-for-kb-pathname' does the same but requires a "convertible thing",
;;; i.e., a namestring (i.e., in the character set of the file system, not
;;; a text string in the gensym character set) or a gensym pathname.
;;;
;;; These functions do all of the appropriate merging and probing to find the
;;; file that is to be loaded.  These are meant to be a superset of the kinds of
;;; merging that may happen in the course of a hand-loading of a KB file, i.e.,
;;; that done by the dialog manager and by read-kb and functions in between.
;;;
;;; These are suitable for calling by system procedures, which cannot have
;;; intervening dialogs or interaction with the user.
;;; 
;;; [However, at present, it does not handle modules!  Thus, it will not
;;; validate the availability of required modules to all levels.  That is a
;;; desireable feature, but it will require a fair amount (~ 1 day) of
;;; reengineering not practical at this time. (MHD 6/6/95)]

(defun-allowing-unwind probe-for-kb-named-by-text-string (text-string)
  (protected-let*
      ((namestring
	 (copy-text-string text-string)
	 (reclaim-text-string namestring)))
    (probe-for-kb-pathname namestring)))

(defun-allowing-unwind probe-for-kb-pathname (convertible-thing)
  (with-protected-pathname-conversion
      ((convertible-thing mergeable-pathname))
    ;;mergeable-pathname might be NIL if it couldn't be parsed -- return NIL
    (when mergeable-pathname
      (protected-let*
	  ((mergeable-pathname-with-home	; in-place modification of arg
	     (maybe-supply-home-to-possible-unix-pathname mergeable-pathname))
	   (default-pathname
	       (get-or-make-default-kb-pathname)
	       (reclaim-gensym-pathname default-pathname))
	   (merge-series
	     (gensym-list
	       mergeable-pathname-with-home
	       default-pathname)
	     (reclaim-gensym-list merge-series))
	   (merged-pathname
	     (merge-series-of-pathnames merge-series))
	   (less-case-sensitive-pathname
	     (or (get-less-case-sensitive-gensym-pathname-if-any merged-pathname)
		 merged-pathname)
	     (reclaim-gensym-pathname less-case-sensitive-pathname)))
	(gensym-probe-file less-case-sensitive-pathname)))))



(defun-allowing-unwind maybe-modify-confirmation-query-and-default-pathname
    (default-pathname default-namestring-for-user confirmation-query)
  (let ((maximum-length?
	  (gensym-maximum-file-name-length default-pathname))
	(file-type? (gensym-pathname-type default-pathname))
	(trimmed-file-type-p nil))
    (when (and (text-string-p file-type?)
	       (eqlw (charw file-type? (1-f (lengthw file-type?))) #.%Space))
      (let* ((trimmed-file-type
	       (text-string-right-trim #w" " file-type?))
	     (default-pathname-with-trimmed-type
	       (gensym-make-pathname
		 :type trimmed-file-type
		 :defaults default-pathname)))
	(reclaim-gensym-pathname default-pathname)
	(setq default-pathname default-pathname-with-trimmed-type)
	(setq trimmed-file-type-p t)))
    (cond
      (maximum-length?
       (protected-let* 
	   ((file-namestring ;base name + type + version
	      (gensym-file-namestring default-pathname)
	      (reclaim-text-string file-namestring))
	    (file-namestring-length
	      (text-string-length file-namestring))
	    (file-namestring-for-user
	      (copy-text-string file-namestring)
	      (reclaim-text-string file-namestring-for-user)))
	 (if (>f file-namestring-length maximum-length?)
	     (protected-let*
	        ((file-base-namestring
		  (gensym-pathname-name default-pathname))
		 (file-base-namestring-length
		  (text-string-length file-base-namestring))
		 (truncated-base-namestring
		  (text-string-substring
		   file-base-namestring
		   0
		   (-f maximum-length?
		       (-f file-namestring-length file-base-namestring-length)))
		  (reclaim-text-string truncated-base-namestring))
		 (truncated-default-pathname
		  (gensym-make-pathname
		   :name truncated-base-namestring
		   :defaults default-pathname))
		 (truncated-namestring-for-user
		  (gensym-namestring-as-text-string
		    truncated-default-pathname)))
	      (reclaim-gensym-pathname default-pathname)
	      (reclaim-text-string default-namestring-for-user)
	      (reclaim-text-string confirmation-query)
	      (values (tformat-text-string
		       "The filename ~s is too long ~
                        to store in the file system.  Save KB as ~s?"
		       file-namestring-for-user
		       truncated-namestring-for-user)
		      truncated-namestring-for-user
		      truncated-default-pathname))
	     (values confirmation-query
		     default-namestring-for-user
		     default-pathname))))
      (trimmed-file-type-p
       (let* ((file-namestring-for-user (gensym-namestring default-pathname))
	      (new-confirmation-query
		(tformat-text-string
		  "The filename ~s contains trailing spaces.  ~
                   G2 will be unable to locate this file.  ~
                   Save KB as ~s instead?"
		  default-namestring-for-user
		  file-namestring-for-user)))
	 (reclaim-text-string default-namestring-for-user)
	 (reclaim-text-string confirmation-query)
	 (values new-confirmation-query
		 file-namestring-for-user
		 default-pathname)))
      (t (values confirmation-query
		 default-namestring-for-user
		 default-pathname)))))

(defun symbolic-file-type-for-file-command? (command-symbol)
  (case command-symbol
    ((connect-to-foreign-image disconnect-from-foreign-image)
     'foreign-image)
    (load-attribute-file 'attribute)
    (write-g2-stats 'statistics)
    (t nil)))

(defun-allowing-unwind execute-file-command (file-command)
  (let* ((command-translation
	   (copy-for-slot-value
	     (first (box-translation-and-text file-command))))
	 
	 (command-symbol
	   (if (consp (first command-translation))
	       ;; then: ((save-module module)
	       ;;           <file-name, etc.> [<including, etc.>]
	       ;;           )
	       (car (first command-translation))
	       ;; else: (<command> <file-name, etc.>)
	       (first command-translation)))
	 (scc-command-p
	  (memq command-symbol '(scc-update scc-edit scc-unedit scc-revert scc-commit)))
	 (options-plist				; for load, save, or merge
	  (unless scc-command-p
	    (and (consp (third command-translation))
		 (third command-translation))))
	 (module-to-save?
	   (if (memq command-symbol '(save-module save-module-into))
	       (second (first command-translation))))
	 (include-required-modules?		; only for save-module case
	   (if module-to-save?
	       (getf options-plist
		     'including-all-required-modules)))
	 (only-changed-modules?
	   (if module-to-save?
	       (getf options-plist
		     'save-only-changed-modules)))
	 (log-message-for-commit-after-saving?
	   (copy-if-text-string
	    (if scc-command-p
		(and (eq command-symbol 'scc-commit)
		     (third command-translation))
		(getf options-plist 'commit-after-saving))))
	 (emit-c-code?		; only for save case
	   (and (getf options-plist 'emitting-c-code) t))
	 (default-file-name?
	   (if (consp (second command-translation))
	       (first (second command-translation))))
	 (file-or-directory-name?
	   (if (consp (second command-translation))
	       (unless (eq (second (second command-translation))
			   'per-directory-menu)
		 (second (second command-translation)))
	       (unless (eq (second command-translation)
			   'per-directory-menu)
		 (second command-translation))))
	 (per-directory-menu-if-loading?
	   (if (consp (second command-translation))
	       (eq (second (second command-translation))
		   'per-directory-menu)
	       (eq (second command-translation)
		   'per-directory-menu)))
	 (resolve-conflicts-automatically?
	   (getf options-plist 'resolve-conflicts-automatically 'default))
	 (reformat-as-appropriate-if-load-or-merge-case?
	   (getf options-plist 'reformat-as-appropriate))
	 (install-system-tables-if-merge-case?
	   (getf options-plist 'install-system-tables))
	 (what-to-do-after-loading-kb?
	   (getf options-plist 'what-to-do-after-loading-kb))
	 (use-clear-text?
	   (getf options-plist 'using-clear-text))
	 (update-before-loading?
	   (getf options-plist 'update-before-loading 'default))	 
	 (symbolic-file-type?
	   (symbolic-file-type-for-file-command? command-symbol))
	 (command-default-namestring?
	   (if default-file-name?
	       (if (symbolp default-file-name?)
		   (gensym-namestring default-file-name?)
		   (copy-text-string default-file-name?))
	       nil))
	 (command-default-pathname?
	   (if command-default-namestring?
	       (prog1
		 (gensym-pathname command-default-namestring?)
		 (reclaim-text-string command-default-namestring?))
	       nil))
	 (current-default-pathname? 
	   (make-default-pathname symbolic-file-type?))
	 (default-pathname?			;guaranteed to be a gensym-pathname
	   (or command-default-pathname?
	       current-default-pathname?
	       (make-first-time-default-pathname symbolic-file-type?)))
	 
	 ;; Make-default-pathname never creates a new gensym-pathname, but always
	 ;; returns the previous gensym-pathname used for the specific file
	 ;; operation -- loading, saving, foreign loading, etc.  (Perhaps it
	 ;; should be renamed to impart this fact.) Thus we don't want to reclaim
	 ;; default-pathname?  if it was obtained from make-default-pathname, but
	 ;; we do if we got it anywhere else.
	 
	 (default-pathname-is-reclaimable-p
	   (or command-default-pathname?
	       (null current-default-pathname?)))
	 (load-case?
	   ;; jh, 6/18/91.  Added foreign image clauses.  See FOREIGN.
	   (case command-symbol
	     (load (if (empty-kb-p) t 'replace))
	     (connect-to-foreign-image      'connect-to-foreign-image)     
	     (disconnect-from-foreign-image 'disconnect-from-foreign-image)
	     (otherwise nil)))
	 (external-foreign-image-connection-spec?
	   (and (memq command-symbol
		      '(connect-to-external-foreign-image
			disconnect-from-external-foreign-image))
		(let* ((connection-spec-slot-value
			 (second command-translation))
		       (transport-type
			 (first connection-spec-slot-value))
		       (host-name-slot-value
			 (second connection-spec-slot-value))
		       (host-name
			 (if (text-string-p host-name-slot-value)
			     (copy-text-string host-name-slot-value)
			     host-name-slot-value))
		       (port-number-or-name-slot-value
			 (third connection-spec-slot-value))
		       (port-number-or-name
			 (if (text-string-p port-number-or-name-slot-value)
			     (copy-text-string
			       port-number-or-name-slot-value)
			     port-number-or-name-slot-value)))
		  (icp-list transport-type
			    host-name
			    port-number-or-name)))))
    (finish-executing-file-command
     command-symbol
     module-to-save?
     include-required-modules?
     emit-c-code?
     file-or-directory-name?
     use-clear-text?
     log-message-for-commit-after-saving?
     per-directory-menu-if-loading?
     resolve-conflicts-automatically?
     reformat-as-appropriate-if-load-or-merge-case?
     install-system-tables-if-merge-case?
     what-to-do-after-loading-kb?
     symbolic-file-type?
     current-default-pathname?
     default-pathname?
     default-pathname-is-reclaimable-p
     load-case?
     external-foreign-image-connection-spec?
     update-before-loading?
     only-changed-modules?)
    (reclaim-slot-value command-translation)))





;;; `Finish-executing-file-command' ...

;;; Command-symbol may any one of the following:
;;;
;;;    LOAD
;;;    MERGE
;;;    
;;;    KB-SAVE
;;;    BACKUP
;;;    KB-SAVE-WITH-RUNTIME-DATA
;;;    RUNTIME-DATA-ONLY
;;;    SAVE-MODULE
;;;    
;;;    LOAD-ATTRIBUTE-FILE
;;;    
;;;    CONNECT-TO-FOREIGN-IMAGE
;;;    
;;;    DISCONNECT-FROM-FOREIGN-IMAGE
;;;    
;;;    DISCONNECT-FROM-ALL-FOREIGN-IMAGES
;;;    
;;;    CONNECT-TO-EXTERNAL-FOREIGN-IMAGE
;;;
;;;    DISCONNECT-FROM-EXTERNAL-FOREIGN-IMAGE
;;;    
;;;    WRITE-G2-STATS

;;; Module-to-save?, if non-nil, should be a symbol, the name of a module to
;;; save.  If so, this first checks if that module exists.  If not, this reports
;;; the problem to the user and does nothing.  Otherwise, this calls
;;; save-module-of-kb.  Module-to-save?  is only relevant when command-symbol is
;;; KB-SAVE.
;;;
;;; Include-required-modules?, if non-nil, is only relevant when module-to-save?
;;; is supplied non-nil.  It is passed along to save-module-of-kb as the parameter
;;; include-required-modules?.  See save-module-of-kb for its documentation.

;;; File-name? is the name of the file to operate on.  If may only be nil if
;;; per-directory-menu-if-loading? is true.

;;; Load-case? ... may be nil, T, or REPLACE.  It should be REPLACE when this
;;; is a typical Load KB, and there is a another KB already that this is replacing.
;;; T or REPLACE means to replace the system tables.  REPLACE means to query the
;;; user to make sure they don't mind replacing the current KB.  NIL means that
;;; this is a typical Merge KB.  (But see also install-system-tables-if-merge-case?)

;;; ... [Finish Documenting!]

(defun finish-executing-file-command 
    (command-symbol
      module-to-save?
      include-required-modules?
      emit-c-code?
      file-or-directory-name?
      use-clear-text?
      log-message-for-commit-after-saving?
      per-directory-menu-if-loading?
      resolve-conflicts-automatically?
      reformat-as-appropriate-if-load-or-merge-case?
      install-system-tables-if-merge-case?
      what-to-do-after-loading-kb?
      symbolic-file-type?
      current-default-pathname?		; Must be a gensym-pathname or NIL.
      default-pathname?
      default-pathname-is-reclaimable-p
      load-case?
      external-foreign-image-connection-spec?
      update-before-loading?
      only-changed-modules?)
  (when doing-g2-init-file-p
    ;; jh per mhd, 8/14/91.  If the user ends up declining a per-directory
    ;; choice offered by the G2 Init file, we don't want to want to keep the
    ;; start/don't start choice, since the KB won't run as planned anyway.
    (unless (eq autostart-after-doing-init-file? 'never-autostart)
      (cond ((eq what-to-do-after-loading-kb?
		 'start-afterwards)
	     (setq autostart-after-doing-init-file? 'autostart))
	    ((eq what-to-do-after-loading-kb?
		 'never-start-afterwards)
	     (setq autostart-after-doing-init-file? 'do-not-autostart)))
      (when (member
	      what-to-do-after-loading-kb?
	      '(start-afterwards never-start-afterwards))
	(setq autostart-reason-in-init-file?
	      (case command-symbol
		(merge 'merge-in-init-file)
		(otherwise 'load-in-init-file))))))

  (cond
    (per-directory-menu-if-loading?
     (post-directory-menu
       default-pathname? load-case?
       reformat-as-appropriate-if-load-or-merge-case?
       symbolic-file-type?
       (or (eq what-to-do-after-loading-kb? 'warmboot-afterwards)
	   (eq what-to-do-after-loading-kb?
	       'warmboot-afterwards-with-catch-up))
       resolve-conflicts-automatically?
       what-to-do-after-loading-kb?
       (eq command-symbol 'disconnect-from-foreign-image)
       install-system-tables-if-merge-case?
       update-before-loading?)
     (when default-pathname-is-reclaimable-p
       (reclaim-gensym-pathname default-pathname?)))
    (t 
     (let* ((name-from-command		; can't be nil when per-directory-menu-...?
	      file-or-directory-name?)		;   is nil, which it's now known to be.
	    (symbolic-filename-p
	      (symbolp name-from-command))
	    (mergeable-namestring
	      (copy-text-string
		(if symbolic-filename-p
		    (symbol-name-text-string name-from-command)
		    name-from-command)))
	    (new-default-pathname-1
	      (prog1 (maybe-supply-home-to-possible-unix-pathname
		       (gensym-merge-pathnames
			 (if symbolic-filename-p
			     (nstring-downcasew mergeable-namestring)
			     mergeable-namestring)
			 default-pathname?))
		(reclaim-text-string mergeable-namestring)
		(when default-pathname-is-reclaimable-p
		  (reclaim-gensym-pathname default-pathname?))))
	    (new-default-pathname
	      (let* ((old-pathname new-default-pathname-1)
		     (old-pathname-type (gensym-pathname-type old-pathname)))
		(cond ((and (memq command-symbol '(backup kb-save-with-runtime-data
						   runtime-data-only))
			    (text-string-p old-pathname-type)
			    (string-equalw old-pathname-type #w"xml"))
		       (prog1 (gensym-make-pathname :type #w"kb"
						    :defaults old-pathname)
			 (reclaim-gensym-pathname old-pathname)))
		      ;; forcely change file type to XML for clear text saving.
		      ((and use-clear-text?
			    (text-string-p old-pathname-type)
			    (string-equalw old-pathname-type #w"kb"))
		       (prog1 (gensym-make-pathname :type #w"xml"
						    :defaults old-pathname)
			 (reclaim-gensym-pathname old-pathname)))
		      (t
		       new-default-pathname-1))))
	    (default-namestring-for-user
	      (gensym-namestring-as-text-string new-default-pathname)))

       (setq default-pathname? new-default-pathname)

       (if (null default-pathname?)
	   (notify-user
	     "~S is not a valid file name!"
	     file-or-directory-name?)

	   ;; At this point default-pathname?  is guaranteed to be a reclaimable
	   ;; gensym-pathname structure.  All intermediate structures have been
	   ;; reclaimed.  Any file command handler must either reclaim it or
	   ;; pass it to store-current-pathname, which reclaims the previous
	   ;; default pathname if present.

	   (case command-symbol
	     ((load merge)
	      (load-or-merge-kb-if-ok
		default-pathname? load-case?
		reformat-as-appropriate-if-load-or-merge-case?
		(or (eq what-to-do-after-loading-kb? 'warmboot-afterwards)
		    (eq what-to-do-after-loading-kb?
			'warmboot-afterwards-with-catch-up))
		resolve-conflicts-automatically?
		install-system-tables-if-merge-case?
		what-to-do-after-loading-kb?
		update-before-loading?))
	     ((kb-save backup kb-save-with-runtime-data runtime-data-only
		       save-module save-module-into)
	      (let ((same-pathname?
		      ;; The test used to be the generic gensym-pathnames-equal-p,
		      ;; but that failed when one pathname version was :newest and
		      ;; the other was empty, as often happens with the complicated
		      ;; defaulting here.  See further notes in PATHNAMES under
		      ;; gensym-pathnames-equal-enough-p.  jh, 3/6/91.
		      (gensym-pathnames-equal-enough-p 
			default-pathname? 
			current-default-pathname?)))
		(cond 
		  ((or same-pathname?
		       attempting-save-via-system-procedure?
		       do-g2-init-file?
		       ;; makes code below obsolete!
		       (memq command-symbol '(save-module save-module-into)))
		   ;; Don't require confirmation if the KB is being samed with the
		   ;; same (i.e., the default) pathname, or if the save is being
		   ;; done via a system procedure, or if the save is being done
		   ;; from a G2 init file.
		   (cond
		     ((memq command-symbol '(save-module save-module-into))
		      ;; Find out the real top-level module
		      (when (eq module-to-save? '|g2-internal-top-level|)
			(setq module-to-save? (top-level-kb-module? module-information)))
		      (cond
			((not (module-exists-p module-to-save?))
			 (notify-user
			   "The module ~a does not exist and so cannot be saved.  ~
                              NOTHING WAS SAVED!!"
			   module-to-save?))
			(t
			 (when use-clear-text?
			   (let ((old-pathname default-pathname?))
			     (setq default-pathname? (gensym-make-pathname
						       :type #w"xml"
						       :defaults default-pathname?))
			     (reclaim-gensym-pathname old-pathname)))
			 (save-module-of-kb
			   default-pathname? module-to-save?
			   include-required-modules?
			   use-clear-text?
			   emit-c-code?
			   log-message-for-commit-after-saving?
			   only-changed-modules?)
			 ;; For this call to reclaim-gensym-pathname and the
			 ;; next call six lines down, save-kb copies the
			 ;; default-pathname? but does not reclaim it.  The
			 ;; reclaiming is left to the caller.  (ghw 2/6/96)
			 (reclaim-gensym-pathname default-pathname?))))
		     ((memq command-symbol '(kb-save backup kb-save-with-runtime-data
						     runtime-data-only))
		      ;; (these are all the remaining possibilities)
		      (save-kb default-pathname? command-symbol emit-c-code? log-message-for-commit-after-saving?)
		      (reclaim-gensym-pathname default-pathname?))))
		  
		  (t
		   (let ((confirmation-query
			   (tformat-text-string
			     "Save KB as ~s?" default-namestring-for-user)))

		     ;; jh, 10/20/91.  If we are on a file system that limits
		     ;; filename length, form a filename whose base name is
		     ;; truncated but whose extension and version remain intact,
		     ;; so that later uses of "per directory menu" will work
		     ;; properly.  Note that the following assumes that the file
		     ;; system of default-pathname?  is the local file system.
		     ;; If we ever do remote file access, we will have to
		     ;; generalize this, perhaps by including a machine
		     ;; specification in the gensym-pathname structure or
		     ;; perhaps by making G2 "preflight" each machine to see if
		     ;; it actually truncates filenames.
		     (multiple-value-setq (confirmation-query
					    default-namestring-for-user
					    default-pathname?)
		       (maybe-modify-confirmation-query-and-default-pathname
			 default-pathname? 
			 default-namestring-for-user
			 confirmation-query))

		     (enter-dialog
		       confirmation-query
		       nil nil
		       'save-kb
		       (slot-value-list default-pathname? command-symbol emit-c-code?)
		       ;; jh, 10/20/91.  We were leaking default-pathname?  when
		       ;; the user chose "Cancel" from the the "Save KB as"
		       ;; dialog.  See above comment in this function about why
		       ;; we sometimes don't want to reclaim default-pathname?.
		       'reclaim-gensym-pathname
		       (slot-value-list default-pathname?)
		       
		       ;; UNKLUDGE!! (MHD 10/29/89)
		       (NTH-VALUE 0 (GET-POSITION-OF-MOUSE))
		       (NTH-VALUE 1 (GET-POSITION-OF-MOUSE))))))))
	     (load-attribute-file
	      (load-custom-software-file-if-ok
		default-pathname? symbolic-file-type?))

	     (connect-to-foreign-image
	      (connect-to-foreign-image default-pathname?))
	     (disconnect-from-foreign-image
	      (disconnect-from-foreign-image default-pathname?))
	     (disconnect-from-all-foreign-images
	      (disconnect-from-all-foreign-images))
	     
	     (connect-to-external-foreign-image
	      (connect-to-external-foreign-image
		external-foreign-image-connection-spec?))
	     (disconnect-from-external-foreign-image
	      (disconnect-from-external-foreign-image
		external-foreign-image-connection-spec?))

	     ((scc-update scc-edit scc-unedit scc-revert)
	      (do-scc-command command-symbol default-pathname?))
	     (scc-commit
	      (do-scc-command command-symbol default-pathname? log-message-for-commit-after-saving?))

	     (write-g2-stats
	      (write-g2-stats default-pathname?))))
       (reclaim-text-string default-namestring-for-user)))))

;; Modified execute-file-command to accommodate the new reclaimable
;; gensym-pathnames.  jh, 1/11/91.

;; Using a symbol-name as a filename is a bad idea, because the user types in
;; lowercase and would be suprised when the Lisp reader converts this to
;; uppercase.  This we convert to lowercase any filename which came from a symbol
;; in execute-file-command.  jh per mhd, 1/23/91.
;;
;; -- same convention adapted for file names that are symbols in
;; module-information tables.  (MHD 9/8/94)

;; jh, 10/21/91.  Modified execute-file-command to check for platform-specific
;; limits on filename length and notify the user on the "Save KB as" dialog box.




;;; `warmbooting?' is bound true throughout the entire process of warmbooting.

(def-system-variable warmbooting? kb-load1 nil)


;;; `warmbooting-with-catch-up?' is bound true when the user warmbooting in
;;; "catch up" mode.  The current time will be set to the current time of the
;;; snapshot.

(def-system-variable warmbooting-with-catch-up? kb-load1 nil)


;;; Get-less-case-sensitive-gensym-pathname-if-any ... returns nil OR recycles
;;; gensym-pathname and returns a "less case sensitive" gensym pathname, whose
;;; namestring is the same as gensym-pathname's except for alphabetic case
;;; differences, but matches, in alphabetic case, some actual disk file,
;;; whereas gensym-pathname might not have.

;;; In order to work, this must probe the directory implied by gensym-pathname,
;;; which can take some time, but usually is quite fast, especially on unix file
;;; systems.  So, if this returns non-nil, it returns a truename.  However, note
;;; that it is not guaranteed to do a probe-file, so that must be done in
;;; addition when a null value is returned in order check if the gensym-pathname
;;; really exists.

;;; When the pathname is from a non-unix file system, such as VMS or Lispm, this
;;; always returns nil.

(defun get-less-case-sensitive-gensym-pathname-if-any (gensym-pathname)
  (when (eq (gensym-pathname-file-system gensym-pathname) 'unix)
    (let* ((truename? (gensym-probe-file gensym-pathname))
	   (resulting-new-pathname? nil))
      (cond
	(truename? (reclaim-gensym-pathname truename?))
	(t
	 (let* ((directory?
		  (let ((directory-pathname
			  (gensym-make-pathname
			    :name :wild 
			    :type :wild 
			    :version :newest
			    :defaults gensym-pathname)))
		    (prog1
			(gensym-directory directory-pathname)	 
		      (reclaim-gensym-pathname directory-pathname)))))		  
	   (when directory?
	     (setq resulting-new-pathname?
		   (get-less-case-sensitive-gensym-pathname-given-directory
		     gensym-pathname
		     directory?))
	     (loop for p in directory?
		   do (reclaim-gensym-pathname p))
	     (reclaim-path-list directory?)))))
      resulting-new-pathname?)))

;; The purpose of this is to make case-sensitive file systems less of a
;; pain.  This is rather inefficient, but not noticably because UNIX
;; file access is so fast.  Note that this kind of case conversion is
;; not something performed at the gensym-pathname level, since the UNIX
;; file system does distinguish cases.  It is simply a convenience for
;; the user not to have to type in an uppercase file name.  We should
;; consider documenting this behavior for the user somewhere.  jh,
;; 12/12/90.

;; This body of this function used to be part of the body of read-kb.
;; (MHD 7/31/91)

;; jh, 10/4/91.  Fixed this not to happen on VMS systems, which are not case
;; sensitive.  Moved from KB-LOAD2.




;;; The function `abandon-load-or-merge-kb-if-ok' is called by
;;; load-or-merge-kb-if-ok when G2 cannot locate a file corresponding to the
;;; pathname supplied by the user.  If the directory component of the user
;;; pathname represents an actual directory, this function modifies
;;; default-kb-pathname?  to contain the new directory.  This behavior is
;;; friendlier to the user.  This function is reponsible for reclaiming its
;;; pathname argument.  It can do so either by reclaiming it directly (if it did
;;; not represent an actual directory) or by making it the value of
;;; current-kb-pathname?.  In the latter case, the next call to
;;; store-current-pathname will reclaim this pathname.

;; jh, 10/2/92.  (Ideally we would like to offer directory components in the
;; grammar menus for the file command, but that is a more ambitious project.)
;; Note that if current-kb-pathname?  is nil (meaning that no KB has yet been
;; loaded), we absorb the entire pathname supplied by the user.  Given these
;; circumstances, this is the best we can do.

(defun-allowing-unwind abandon-load-or-merge-kb-if-ok
		       (gensym-pathname namestring-for-pathname)
  ;; Change the KB-loading default if appropriate.
  (let ((valid-directory-pathname-p
	 (with-suppressed-pathname-components 
	   gensym-pathname 
	   (gensym-pathname-name 
	    gensym-pathname-type 
	    gensym-pathname-version)
	   (protected-let* 
	      ((directory-pathname
		(or (gensym-directory-as-file gensym-pathname)
		    (make-empty-gensym-pathname))
		(reclaim-gensym-pathname directory-pathname))
	       (directory-namestring
		(gensym-namestring directory-pathname)
		(reclaim-text-string directory-namestring)))
	    (and (g2-stream-directory-p directory-namestring)
		 gensym-pathname ;gets reclaimed or cached below
		 t)))))
    (cond ((and current-kb-pathname? valid-directory-pathname-p)
	   (store-current-pathname 
	     current-kb-pathname?
	     (gensym-merge-pathnames
	       (gensym-pathname-name current-kb-pathname?)
	       gensym-pathname))
	   (add-recent-loaded-kb current-kb-pathname?)
	   (reclaim-gensym-pathname gensym-pathname))
	  (valid-directory-pathname-p
	   ;; Don't reclaim pathname; cache instead.
	   (store-current-pathname current-kb-pathname? gensym-pathname)
	   (add-recent-loaded-kb current-kb-pathname?))
	  (t (reclaim-gensym-pathname gensym-pathname))))
  ;; Notify the user that the file couldn't be located.
  (if (g2-stream-error-flag-set-p)
      (protected-let
	((error-string-for-user
	   (import-text-string
	     (g2-stream-error-string)
	     'G2-STREAM-ERROR-STRING)
	   (reclaim-text-string error-string-for-user)))
	;; jh, 1/31/92.  Only print out error message if there was an
	;; error.
	(notify-user 
	  "G2 could not find the file ~s:  ~a."
	  namestring-for-pathname
	  error-string-for-user))
      (notify-user 
	"G2 could not find the file ~s."
	namestring-for-pathname)))


;;; `Load-or-merge-kb-if-ok' ... Its first argument, gensym-pathname, must be a
;;; gensym-pathname structure, which is to be reclaimed or incorporated by this
;;; function.

(defun-allowing-unwind load-or-merge-kb-if-ok 
    (gensym-pathname
      load-case?				
      bring-formats-up-to-date?
      warmboot-case?
      &optional
      auto-merge-case?
      install-system-tables-if-merge-case?
      what-to-do-after-loading-kb?
      update-before-loading?)
  (declare (ignore warmboot-case?))		; arg no longer needed -- given
  (protected-let*				;  by what-to-do-after-loading-kb?
      ((truename?				;  -- clean up later! (MHD 6/9/92)
	 (or (get-less-case-sensitive-gensym-pathname-if-any gensym-pathname)
	     (gensym-probe-file gensym-pathname))
	 )
       (namestring-for-pathname
	 (gensym-namestring (or truename? gensym-pathname))
	 (reclaim-text-string namestring-for-pathname)))
    
    (unless truename?
      (abandon-load-or-merge-kb-if-ok 
	(copy-gensym-pathname gensym-pathname)
	namestring-for-pathname)
      (return-from load-or-merge-kb-if-ok))

    ;; We reclaim pathname here because it never becomes the default.  The
    ;; reclaimation happens whether or not we are on a Lispm.
    (reclaim-gensym-pathname gensym-pathname)
    (with-module-related-frame-note-updates-supressed
      (prog1
	  (read-kb-or-group-thereof
	    truename?		
	    load-case?
	    (or load-case?
		install-system-tables-if-merge-case?) 
	    bring-formats-up-to-date?
	    auto-merge-case?
	    what-to-do-after-loading-kb?
	    update-before-loading?
	    (get-current-workstation-or-ui-client-interface-if-any))
	(reclaim-gensym-pathname truename?)))))


;; Have a system table parameter that causes the current kb to be preserved
;; until the new one is safely in (revising the calls to read-kb appropriately)!

;; jh, 10/6/91.  Added call to get-less-case-sensitive-gensym-pathname-if-any in
;; load-or-merge-kb-if-ok, to make the character case of the filename less of an
;; issue there.

;; Added gensym-pathname-lessp which does the work that file-name-lessp used to.
;; jh, 12/15/90.

(defun gensym-pathname-lessp (gensym-pathname1 gensym-pathname2)
  (string-lesspw
    (gensym-pathname-name gensym-pathname1)
    (gensym-pathname-name gensym-pathname2)))





;;; `Post-directory-menu' ...

;; Finally, did so.  Modified post-directory-menu to accommodate new reclaimable
;; gensym-pathnames.  jh, 1/11/91

(defun-allowing-unwind get-directory-for-kb-file-type
  (default-pathname? directory-pathname &optional include-ok-file-type? include-subdirectories?)
  (declare (ignore include-ok-file-type?))
  (if (and default-pathname?
	   (gensym-wild-pathname-p default-pathname?))
      (sort-list
	(gensym-directory default-pathname? nil)
	#'gensym-pathname-lessp nil)
      (let* ((match-regular-expression-for-g2-stream-directory-hook
	       (when (enable-loading-clear-text-kbs-p)
		 'namestring-is-xml-file-p))
	     (name-pathname
	       (gensym-make-pathname
		 :name :wild
		 :type #w"{kK}{bBlL}" ; Gensym regexp syntax
		 :version :newest
		 :defaults 
		 default-pathname?))
	     (wild-directory-pathname
	       (prog1 (gensym-merge-pathnames name-pathname directory-pathname)
		      (reclaim-gensym-pathname name-pathname))))
	(prog1 (sort-list (nconc
			    (gensym-directory wild-directory-pathname nil)
			    (if include-subdirectories?
				(gensym-subdirectories wild-directory-pathname nil)))
			  #'gensym-pathname-lessp nil)
	       (reclaim-gensym-pathname wild-directory-pathname)))))

;; jh, 4/23/93.  Modified get-directory-for-kb-file-type to call
;; gensym-directory once instead of as much as four times.  We used to have to
;; make several calls because we couldn't trust the wildcard mechanisms on our
;; various platforms.  But now we can take advantage of the fact that we do
;; platform-independent regular expression matching inside G2 (see STREAMS).
;; When gensym-directory is called with a pathname that contains one of our
;; regular expression metacharacters, it obtains the entire directory from the
;; operating system and then applies regular expression matching to this list.
;; This will be a win on all platforms, but especially on the development
;; Lispms.






(defun-allowing-unwind get-directory-for-non-kb-file-type 
		       (default-pathname? 
			symbolic-file-type?
			load-case?
			directory-pathname)
  (let* ((pathname-with-type
	   (let ((type-file-name-pathname
		   (if (gensym-wild-pathname-p default-pathname?)
		       (copy-gensym-pathname default-pathname?)
		       (gensym-make-pathname
			 :name :wild
			 :type 
			 (or (gensym-pathname-type default-pathname?)
			     (make-default-file-type symbolic-file-type?))
			 :defaults default-pathname?))))
	     (prog1
	       (gensym-merge-pathnames
		 type-file-name-pathname
		 directory-pathname)
	       (reclaim-gensym-pathname type-file-name-pathname)))))
    (cond 
      ((eq symbolic-file-type? 'foreign-image)
       ;; jh, 10/6/94.  Added the following form to cause gensym-directory to
       ;; include specific version numbers on VMS.  Unless the argument to
       ;; gensym-directory has a non-nil gensym-pathname-version component, this
       ;; function will not supply specific version numbers there.  Without this
       ;; form, directory filtering for connected foreign images failed the
       ;; gensym-pathnames-equal-enough-p comparison in
       ;; pathname-of-a-connected-foreign-image-p, because the pathname
       ;; associated with each foreign image is stored as a truename (i.e., one
       ;; with specific version numbers).
       (setf (gensym-pathname-version pathname-with-type) :newest)
       (let ((unfiltered-directory
	       (sort-list
		 (prog1
		     (gensym-directory pathname-with-type nil)
		   (reclaim-gensym-pathname pathname-with-type))
		 'gensym-pathname-lessp nil))
	     (filtered-directory nil))
	 (loop for directory-item in unfiltered-directory 
	       do (cond
		    ((eq load-case? 'connect-to-foreign-image) 
		     (if (pathname-of-a-connected-foreign-image-p
			   directory-item)
			 (reclaim-gensym-pathname directory-item)
			 (path-push directory-item filtered-directory)))
		    ((eq load-case? 'disconnect-from-foreign-image) 
		     (if (pathname-of-a-connected-foreign-image-p
			   directory-item)
			 (path-push directory-item filtered-directory)
			 (reclaim-gensym-pathname directory-item))))
	   finally (reclaim-path-list unfiltered-directory)
		   (return (nreverse filtered-directory)))))
      (t (let ((unfiltered-directory
		 (sort-list
		   (prog1
		       (gensym-directory pathname-with-type nil)
		     (reclaim-gensym-pathname pathname-with-type))
		   'gensym-pathname-lessp nil)))
	   unfiltered-directory)))))


;; jh, 3/30/92.  Changed the per-directory menu search for foreign images to be
;; more useful.  If the G2 user is disconnecting from a foreign image,
;; per-directory now only lists names of connected images and if the G2 user is
;; connecting to a foreign image, per-directory menu confines its choices to
;; pathnames whose images aren't already connected.  After this fix, using the
;; image-building MASTER.KB will be easier.  As well, this indirectly addresses
;; some as yet undiagnosed problems some users are having when they disconnect from
;; foreign images.

;; jh, 10/7/92.  Modified get-directory-for-kb-file-type and
;; get-directory-for-non-kb-file-type to use wildcards in pathnames.  The first
;; pass is to have these functions disregard the standard file types (.KB and
;; the like) whenever the default pathname contains a wildcard.  This will
;; permit G2 users to load files with non-standard file types per directory
;; menu.




(defun-allowing-unwind post-directory-menu
    (default-pathname? load-case?
	bring-formats-up-to-date? symbolic-file-type? warmboot-case?
	auto-merge-case?
	what-to-do-after-loading-kb?
	disconnect-from-external-foreign-image-p
	install-system-tables-if-merge-case?
	update-before-loading?)
  (handling-gensym-file-errors
    (protected-let*
        ((directory-pathname 
	   (gensym-make-pathname
	     :name     :wild
	     ;; type will always be specified below
	     :version  :newest
	     :defaults default-pathname?)
	   (reclaim-gensym-pathname directory-pathname))
	 (menu-was-posted?				    ; If posted, it reclaims some things for us.
	   nil)
	 (directory-namestring 
	   (if (and default-pathname? 
		    (gensym-wild-pathname-p default-pathname?))
	       (gensym-namestring default-pathname?)
	       (gensym-device-and-directory-namestring directory-pathname))
	   (unless menu-was-posted?
	     (reclaim-text-string directory-namestring)))
	 (directory-namestring-for-notify-user
	   directory-namestring)
	 (file-type-for-notify-user
	   (case symbolic-file-type?
	     (foreign-image "foreign image")
	     (attribute 'attribute)
	     (otherwise "KB and KL")))

	 (title
	   (tformat-text-string "~a Files on \"~a\""
				file-type-for-notify-user
				directory-namestring-for-notify-user)
	   (unless menu-was-posted?
	     (reclaim-text-string title)))

	 (parameters
	   (slot-value-list directory-pathname default-pathname?
			    symbolic-file-type?
			    load-case?)
	   (reclaim-slot-value-list parameters))
	 (menu-name
	   (if disconnect-from-external-foreign-image-p
	       'pathnames-in-directory
	       'foreign-images)))
      
      (notify-user "Looking for ~a files in ~s"
		   file-type-for-notify-user
		   directory-namestring-for-notify-user)
      (gensym-assert (text-string-p (make-default-file-type symbolic-file-type?)))

      (let ((menu?
	      (make-menu-named menu-name		    ; This can throw on file-system errors.
			       :parameters parameters
			       :title title)))
	
	(cond ((null menu?)
	       (notify-user "There are no ~a files in ~s" 
			    (if (equal file-type-for-notify-user "KB and KL")
				"KB or KL"
				file-type-for-notify-user)
			    directory-namestring-for-notify-user))
	      (t
	       (let ((choice-function-arguments
		       (slot-value-list			    ; MENUS will reclaim the spine of this list
			 load-case? 
			 (copy-gensym-pathname default-pathname?)
			 directory-namestring		    ; reclaimed in handle-choice-for-directory-menu
			 bring-formats-up-to-date?
			 symbolic-file-type?		    ; always a constant string
			 warmboot-case?
			 auto-merge-case?
			 what-to-do-after-loading-kb?
			 install-system-tables-if-merge-case?
			 update-before-loading?)))

		 (post-menu menu?
			    :choice-function #'handle-choice-for-directory-menu
			    :choice-function-arguments choice-function-arguments
			    :no-choice-function #'handle-choice-for-directory-menu)
		 
		 (setq menu-was-posted? t))))))))

;; jh, 1/7/92.  Modernized post-directory-menu to use protected-let*.




;;; The function `compute-directory-menu-items' returns a list of menu items,
;;; one for each file in the directory matching the given file type, etc.

(defun compute-directory-menu-items
    (directory-pathname default-pathname? symbolic-file-type? load-case?)
  (let* ((pathnames
	   (if (memq symbolic-file-type? '(kb nil))		  		  
	       (get-directory-for-kb-file-type
		 default-pathname? 
		 directory-pathname)		  
	       (get-directory-for-non-kb-file-type
		 default-pathname? 
		 symbolic-file-type?
		 load-case?
		 directory-pathname)))
	 (ascii-pathnames
	   (loop for pathname in pathnames
		 as file-namestring = (gensym-file-namestring pathname)
		 as ascii-filename = (copy-text-string
				       file-namestring)
		 collect ascii-filename using slot-value-cons
		 do (reclaim-text-string file-namestring)
		    (reclaim-gensym-pathname pathname))))

    (reclaim-slot-value-list pathnames)

    (when (eq load-case? 'disconnect-from-foreign-image)
      (setq ascii-pathnames
	    (nconc
	      ascii-pathnames
	      (loop for image-info
			in all-external-foreign-function-images?
		    collect
		    (twith-output-to-text-string
		      (twrite-foreign-image-connection-spec
			(connection-specification-to-foreign-image-function
			  image-info)))
		      using slot-value-cons))))

    ascii-pathnames))
    



;;; The defmenu `external-foreign-function-images' is a menu of all the
;;; (connected?) external foreign function images.

(defmenu external-foreign-function-images ()
  (loop for image-info in all-external-foreign-function-images?
	collect
	(twith-output-to-text-string
	  (twrite-foreign-image-connection-spec
	    (connection-specification-to-foreign-image-function
	      image-info)))
	  using slot-value-cons))


;;; The defmenu `pathnames-in-directory' is a menu of filenames in a directory

(defmenu (pathnames-in-directory
	   :parameters (directory-pathname default-pathname?
					   symbolic-file-type?
					   load-case?))
    ()
  (compute-directory-menu-items
    directory-pathname default-pathname? symbolic-file-type? load-case?))



;;; The defmenu `foreign-images' is the menu for connect/disconnect foreign
;;; image.

(defmenu (foreign-images
	   :parameters (directory-pathname default-pathname?
					   symbolic-file-type?
					   load-case?))
    ()
  (include pathnames-in-directory)
  (include external-foreign-function-images ()))

;; The () above means to pass no parameters to the included menu.




;;; The function `handle-choice-for-directory-menu' is called after choosing a
;;; pathname in the menu posted by per-directory-menu

(defun-allowing-unwind handle-choice-for-directory-menu
    (choice-menu 
      menu-item
      choice 
      load-case?
      default-pathname
      directory-namestring
      bring-formats-up-to-date?
      symbolic-file-type?
      warmboot-case?
      auto-merge-case?
      what-to-do-after-loading-kb?
      install-system-tables-if-merge-case?
      update-before-loading?)
  (declare (ignore menu-item))
  (cond ((null choice)				; menu dismissed instead of chosen from
	 ;; When we are executing an init file, a dismissed menu invalidates any
	 ;; subsequent start-after-load command.  The rationale is that the KB
	 ;; will not run as planned anyway, since the user has rejected a part of
	 ;; the application.  jh per mhd, 8/14/91.
	 (when doing-g2-init-file-p
	   (setq autostart-after-doing-init-file? 'never-autostart))
	 (reclaim-text-string directory-namestring)
	 (reclaim-gensym-pathname default-pathname)
	 (delete-menu choice-menu))
	((and (eq load-case? 'disconnect-from-foreign-image)
	      (external-foreign-image-disconnection-spec-p choice))
	 (protected-let*
	     ((command-frame
		(make-command-frame 'init-file-command)
		(delete-frame command-frame))
	      (text-to-parse
		;; I removed (convert-raw-text-string-to-unformatted-text)
		;; surrounding this, replacing it convert-text-string-to-text.
		;; It made no sense -- choice here is already a legal gensym
		;; text string in gensym character set (or it is assumed to be,
		;; at least, by calls below).  (MHD 12/8/94)
		(convert-text-string-to-text
		  (twith-output-to-text-string
		    (tformat "disconnect from external foreign image at ")
		    (tformat "~a" choice)))))
	   ;; Re-parse the connection-spec from menu choice.
	   (when (parse-text-for-slot
		   text-to-parse
		   command-frame
		   (get-slot-description-of-frame
		     'box-translation-and-text
		     command-frame
		     nil))
	     (delete-menu choice-menu)
	     (disconnect-from-external-foreign-image
	       (second (car (box-translation-and-text command-frame)))))
	   (reclaim-text-string directory-namestring)
	   (reclaim-gensym-pathname default-pathname)))
	(t (protected-let* 
	       ;; Must be done before deleting menu.
	       ;; See above for similar code.
	       ((namestring-for-choice
		  (copy-text-string
		    (if (symbolp choice)
			(symbol-name-text-string choice)
			choice))
		  (reclaim-text-string namestring-for-choice))
		(pathname-for-merge
		  (gensym-merge-pathnames
		    directory-namestring
		    default-pathname)
		  (reclaim-gensym-pathname pathname-for-merge))
		;; Re-assemble the entire pathname from menu choice.
		(pathname 
		  (gensym-merge-pathnames 
		    namestring-for-choice
		    pathname-for-merge)
		  (reclaim-gensym-pathname pathname)))
	     ;; The convention is to delete the menu before loading or merging,
	     ;; where it might or might not get done.
	     (delete-menu choice-menu)
	     (case symbolic-file-type?
	       (attribute
		(load-custom-software-file-if-ok 
		  (copy-gensym-pathname pathname)
		  symbolic-file-type?))
	       (foreign-image
		(case load-case?
		  (connect-to-foreign-image
		   (connect-to-foreign-image
		     (copy-gensym-pathname pathname)))
		  (disconnect-from-foreign-image
		   (disconnect-from-foreign-image 
		     (copy-gensym-pathname pathname)))
		  #+development
		  (otherwise (error "Unknown foreign image command ~a"
				    load-case?))))
	       
	       (otherwise
		(load-or-merge-kb-if-ok
		  (copy-gensym-pathname pathname)
		  load-case? 
		  bring-formats-up-to-date?
		  warmboot-case?
		  auto-merge-case?
		  install-system-tables-if-merge-case?
		  what-to-do-after-loading-kb?
		  update-before-loading?)))
	     (reclaim-text-string directory-namestring)
	     (reclaim-gensym-pathname default-pathname)))))

;; Modified handle-choice for directory menu to accommodate the new reclaimable
;; gensym-pathnames.  Note that this function is now called with nil when
;; dismissed, so it can do some reclamation.  jh, 1/11/91.





;;; `Make-kb-name' converts the name component of gensym-pathname to a text
;;; string, where any lower-case characters have been converted to upper-case,
;;; and any non-gensym characters have been converted to gensym characters, if
;;; possible, or else dropped.

(defun make-kb-name (gensym-pathname)
  (let ((temporary-text-string
	  (gensym-pathname-name gensym-pathname)))
    (copy-text-string-with-case-conversion
      (if (text-string-p temporary-text-string)
	  temporary-text-string
	  #w"")
      :all)))

;; Actually, at present, this assumes that file names are always just ASCII, so
;; only ASCII=>Gensym conversion takes place.  Later, hopefully the type of
;; character encoding can be stored in the pathname.
  
;; This is called only within FILES. An examination of its use shows that any
;; value except nil would be satisfactory. ML 4/2/91





;;;; Formats for File Commands



;;; The table format `file-command-info-table-format' is used for the attribute
;;; table displaying the current directory and some status info in the file
;;; command dialog.
;;;
;;; Its format makes the table aspects completely transparent -- no borders,
;;; column boundaries, row boundaries, or background colors are visible.
;;;
;;; Off of this format hangs a spot generator method that simply generates the
;;; workspace spot, i.e., so that clicks appear to go past the table to the
;;; workspace.

(def-table-format file-command-info-table-format
  table-line-color? nil
  table-background-color? nil

  table-left-border-width 0
  table-top-border-width 0
  table-right-border-width 0
  table-bottom-border-width 0
  table-border-color? nil

  table-row-boundary-width 0
  table-row-boundary-color? nil

  table-column-boundary-width 0
  table-column-boundary-color? nil)

(def-table-format-spot-generator file-command-info-table-format
    (table mouse-pointer)
  (generate-output-only-table-spot table mouse-pointer (make-output-only-table-spot)))




;;; The format `file-command-attribute-value-format', and its size variations
;;; for small and extra-large, are used for the cells displayed in the
;;; information table in file dialog.
;;; 
;;; They are based to some extent on the default attribute-value format.
;;; However, each has at least 1000 as its minimum-format-width-for-text-cell
;;; attribute to ensure that they rarely require formatting into more than one
;;; line.  They also have margins (top, left, right, and bottom) squeezed rather
;;; tightly, roughly by 50%, mostly to conserve horizontal space.
;;;
;;; Introduced for 4.0.
;;;
;;; These will never be saved in a KB, since they are only used on edit
;;; workspaces, temporary workspaces.

(def-text-cell-format file-command-attribute-value-format
  text-cell-lines-justified? nil
  text-cell-left-margin 4
  text-cell-top-margin 2
  text-cell-right-margin 4
  text-cell-bottom-margin 2
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 20
  text-cell-font-map (hm18)			;was recently swiss20
  text-cell-line-height 20
  text-cell-baseline-position 16
  text-cell-line-spacing 3
  default-word-spacing #.(convert-to-text-width 4) ; was 6 (MHD 2/20/94)
  minimum-format-width-for-text-cell 1250)

(def-text-cell-format file-command-small-attribute-value-format
  text-cell-lines-justified? nil
  text-cell-left-margin 4
  text-cell-top-margin 2
  text-cell-right-margin 4
  text-cell-bottom-margin 2
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 8
  text-cell-font-map (hm14)
  text-cell-line-height 18
  text-cell-baseline-position 14
  text-cell-line-spacing 3
  default-word-spacing #.(convert-to-text-width 4)
  minimum-format-width-for-text-cell 1000)

(setf (corresponding-small-font-format-name
	'file-command-attribute-value-format)
      'file-command-small-attribute-value-format)


(def-text-cell-format file-command-extra-large-attribute-value-format
  text-cell-lines-justified? nil
  text-cell-left-margin 5
  text-cell-top-margin 2
  text-cell-right-margin 5
  text-cell-bottom-margin 2
  text-cell-paragraph-indentation 0
  text-cell-turnover-line-indentation 14
  text-cell-font-map (hm24)
  text-cell-line-height 26
  text-cell-baseline-position 21
  text-cell-line-spacing 3
  default-word-spacing #.(convert-any-number-to-text-width-at-compile-time 8.75) ; 5/8 en
  minimum-word-spacing #.(convert-to-text-width 7)	          ; 1/2 en
  maximum-word-spacing #.(convert-to-text-width 21)	          ; 3/2 en
  minimum-format-width-for-text-cell 1500)

(setf (corresponding-extra-large-font-format-name
	'file-command-attribute-value-format)
      'file-command-extra-large-attribute-value-format)








;;;; Loading Custom Software Files



;;; `Load-custom-software-file-if-ok' ...  Gensym-pathname-to-load must
;;; be a gensym pathname (structure).

;;; In the case where this calls load-attributes-file, this will only
;;; print a notify-user message ("Done loading ...") when T is returned
;;; from load-attribute-file.  When nil is returned, it is assumed that
;;; load-attributes-file prints a relevant notify-user message explaining
;;; any problems.

;;; This function does not return any useful values.

(defun-allowing-unwind load-custom-software-file-if-ok 
		       (gensym-pathname-to-load symbolic-file-type?)
  (handling-gensym-file-errors
    (let ((truename? (gensym-probe-file gensym-pathname-to-load)))
      (if truename?
	  (let ((namestring-for-truename (gensym-namestring truename?))
		(success? t))       
	    (notify-user
	      "Loading ~a file \"~a\""
	      symbolic-file-type? namestring-for-truename)
	    (case symbolic-file-type?
	      (attribute
	       (setq success? (load-attribute-file gensym-pathname-to-load))))
	    (case symbolic-file-type?
	      (attribute 
	       (store-current-pathname
		 current-attribute-file-pathname? gensym-pathname-to-load)))	    
	    (when success?
	      (notify-user
		"Done loading ~a file \"~a\"."
		symbolic-file-type? namestring-for-truename))	 
	    (reclaim-gensym-pathname truename?)
	    (reclaim-text-string namestring-for-truename))
	  (let ((namestring-for-attempted-pathname
		  (gensym-namestring gensym-pathname-to-load)))
	    (notify-user
	      "~s does not exist."
	      namestring-for-attempted-pathname)
	    (reclaim-text-string namestring-for-attempted-pathname))))))

;; Maybe current-attribute-file-pathname?, etc., should be cleared (to
;; nil) upon a clear-kb.

;; Load-custom-software-file-if-ok leaks (!) unavoidably, since it calls
;; implementation-dependent load functions.  The best we can do is
;; prevent any leaks due to dropped pathnames.

;; Modified load-custom-software-file-if-ok to accomidate the new reclaimable
;; gensym-pathnames.  jh, 1/11/91.








;;; `System-statistics-writers' ... A `statistics writer' is a function which
;;; receives a g2-stream argument and which does output to that stream
;;; describing various aspects of the current state of the system.  To register
;;; a statistics writer, push its name on this list.  The function for writing a
;;; header and a good number of the statistics writing functions are defined in
;;; the module G2-METERS.

(defvar system-statistics-writers nil)




;;; `Write-g2-stats' ... opens pathname for output to a g2 stream and funcalls
;;; each statistics writer with that g2 stream.  On exit, the file is closed.
;;; File errors, if any, might prevent this whole enterprise from succeeding,
;;; in which case they will be caught and reported to the user here.  This
;;; function returns no useful values.

;; Modified write-g2-stats to accommodate the new reclaimable gensym-pathnames.
;; Now it will not cons at all while measuring memory.  jh, 1/11/91.

(defun-allowing-unwind write-g2-stats (pathname)
  (handling-gensym-file-errors
    (protected-let* ((namestring 
		       (gensym-namestring pathname)
		       (reclaim-text-string namestring))
		     (namestring-for-user
		       (copy-text-string namestring)
		       (reclaim-text-string namestring-for-user)))
      (g2-stream-with-open-stream
          (open-g2-stream? namestring
	   :direction :output)
	(cond (open-g2-stream?
	       (notify-user
		 "Writing G2 statistics file ~a ..."
		 namestring-for-user)
	       (write-g2-stats-header open-g2-stream?)
	       (loop for statistics-writer in system-statistics-writers
		     do
		     (g2-stream-terpri open-g2-stream?)
		     (funcall statistics-writer open-g2-stream?))
	       (notify-user "G2 statistics file completed.")
	       (store-current-pathname 
		 current-statistics-file-pathname? 
		 pathname))
	      (t (protected-let ((error-string-for-user
				   (import-text-string
				     (g2-stream-error-string)
				     'G2-STREAM-ERROR-STRING)
				   (reclaim-text-string error-string-for-user)))
		   (notify-user
		     "Unable to open G2 statistics file ~s, ~a."
		     namestring-for-user
		     error-string-for-user)))))))
  (snapshot-memory-levels))




#+development
(defun-for-system-procedure g2-write-stats-to-tmp-file ()
  (write-g2-stats
    (gensym-make-pathname
      :directory #w"/tmp"
      :name (tformat-text-string "g2-stats-~A.txt"
				 (mod (get-universal-time) 100000)))))


(defun-for-system-procedure g2-write-stats (filename)
  (write-g2-stats filename))




;;;; KB Flags




;;; `Kb-flags' and `kb-flags-for-saving' are integers, which are incremented
;;; each time an incompatible revision to G2 or to the format of saved kbs is
;;; introduced.  KB-flags is the highest value we accept on reading.
;;; Kb-flags-for-saving is the value we emit on saving.  (See below for why
;;; these might be different.)  (Initially, kb-flags had the values 1, 3, 7, 15,
;;; and 31.  Following 31, it will be incremented by 1 each time.)  It is always
;;; bound to the latest kb format revision number, except during loading or
;;; merging of saved kbs, where it is bound to the revision number as of the
;;; time of the saving of that kb (kept as the `kb flags' property on the "K
;;; plist").  Note that kb-flags may have an old value not just during the
;;; reading of saved kbs, but also during certain deferred or cleanup actions
;;; related thereto.

;;; Each time KB-Flags is incremented a new macro is introduced at the tail of
;;; this section.  The documentation of this series of macros provides some
;;; chronology for the evolution of KB format.  In addition, a corresponding
;;; post loading function is often implemented and placed at the tail of the
;;; section "G2 Post Loading Functions" of KB-LOAD2.

;;; During development of the release of 6.0, kb-flags has gone ahead, up to
;;; 273, but we don't want it to go so high up.  We want to be able to read KBs
;;; saved in that version.  We want to save with a lower value, 270. So we've
;;; now got a new parameter, `kb-flags-for-saving', which will henceforth be
;;; used as the value of KB-FLAGS to save in the KB, whereas kb-flags (and
;;; kb-flags-of-software) will be used as value to compare to when reading the
;;; KB.

;;; The rule for incrementing these two variables is that whenever either
;;; kb-flags of kb-flags-for-saving are incremented, they should both generally
;;; be made one higher than kb-flags.  Otherwise, it will have no effect in that
;;; G2's may still load the KBs with the increased kb-flag value, which is
;;; usually undesireable.  In some cases, however, during development, these can
;;; get separated, especially when a kb-flag increase is "backed out".  Such
;;; cases are generally rare.

;;; We want to make sure: G2 2015 Standard could be used for saving KBs with flag
;;; 281, which is readable by previous G2 versions up to 8.3r1. However, all KBs
;;; saved by G2 ENT/SymScale with flag 282 is readable by all versions of G2 2015.
;;; -- Chun Tian (binghe), 23 Aug 2015

(defvar kb-flags 282)
(defvar kb-flags-for-saving #-SymScale 281 #+SymScale 282)

;; CHANGE KB-FLAGS WHEN YOU ADD A NEW FLAG!!!
;; NOTE: DO NOT USE KB FLAG 253!
;; NOTE: do not use kb flag 271, 272, 273.  Next increase, increment
;;   both of the above variables to 274.  (MHD 4/2/00)
;; Done. -fmw, 1/24/03


;;; `Kb-flags-of-software' is never rebound and maybe used to find the top level
;;; binding of kb-flags at any time.

(defparameter kb-flags-of-software kb-flags)

;; Rename this "kb-format-revision-number"!  (This entails a bit of code in
;; read-kb.)

;; Aside from renaming, the code should be cleaned up by examining all
;; references (including those in macros) to kb-flags, and distinguishing the
;; ones that refer to the software version from those that refer to the kb.
;; There may be some that refer to either, depending on bound context, I'm not
;; sure.  There are too many local and bound variables containing "kb-flags" as
;; a substring of the name.  I do not want to this now, because although clumsy,
;; the present software does not have bugs.  ML, 11/21/91.  (release time)




(defmacro at-or-beyond-kb-format-revision-number-p (kb-format-revision-number)
  `(>=f kb-flags ,kb-format-revision-number))

(defmacro beyond-kb-format-revision-number-p (kb-format-revision-number)
  `(>f kb-flags ,kb-format-revision-number))

(defmacro before-kb-format-revision-number-p (kb-format-revision-number)
  `(<f kb-flags ,kb-format-revision-number))



;;; `Character-sequences-breakable-in-kb-p' is true when \ characters can be used
;;; to break character sequences; see above.  In general, when this kb flag is on,
;;; the length of lines in saved kbs may be assumed to be limited (to about 80
;;; characters).

(defmacro character-sequences-breakable-in-kb-p ()
  `(at-or-beyond-kb-format-revision-number-p 1))




;;; `Class-definitions-ordered-p' is true when class definitions may be assumed
;;; to be so ordered that a class definition follows the class definition, if
;;; any, of its superior class, if any.  In this case, it may also be assumed
;;; that class definitions do not have saved values for name-or-names-for-frame
;;; slots.

(defmacro class-definitions-ordered-p ()
  `(at-or-beyond-kb-format-revision-number-p 3))




;;; `Invocable-rule-flags-ok-p' is true when the invocable-via-forward-
;;; chaining and invocable-via-backward-chaining frame flags of rules accurately
;;; reflect whether or not forward chaining or backward chaining may invoke a
;;; particular rule.  If this predicate is not true, then the slot putting
;;; method for the box-translation-and-text slot of rules needs to update these
;;; flags according to whether the rule is a when, whenever, or other kind of
;;; rule.  Added by jra, 8/6/88 to convert up to version 1.1.

(defmacro invocable-rule-flags-ok-p ()
  `(at-or-beyond-kb-format-revision-number-p 7))




;;; `Compatibility-of-default-settings-for-variables-p' ...

(defmacro compatibility-of-default-settings-for-variables-p ()
  `(at-or-beyond-kb-format-revision-number-p 15))

;; This should be documented!  (And it should have been named better.)




;;; `Frame-representations-for-embedded-rules-ok-p' is true when "invalid frame
;;; representation pointer in embedded rules bug, 1/26/89" has been fixed up.
;;; (See comments below for further information).

(defmacro frame-representations-for-embedded-rules-ok-p ()
  `(at-or-beyond-kb-format-revision-number-p 31))




;;; `Three-escape-characters-p' is true when @, ~, and \ may all occur as escape
;;; characters, which is the case as of 5/17/89

(defmacro three-escape-characters-p ()
  `(at-or-beyond-kb-format-revision-number-p 32))




;;; `Subworkspaces-no-longer-inherit-names-p' ...  Subworkspaces no longer may
;;; have the name of their superior items.  This flag is for conversion of old
;;; kbs. The name which is identical is being removed.  This could not be done
;;; readily by slot-putters because of the lack of reliable order dependencies
;;; when loading. ML.

(defmacro subworkspaces-no-longer-inherit-names-p ()
  `(at-or-beyond-kb-format-revision-number-p 33))




;;; `Old-graphs-are-now-in-stack-of-subblocks-p' ...

(defmacro old-graphs-are-now-in-stack-of-subblocks-p ()
  `(at-or-beyond-kb-format-revision-number-p 34))




;;; `Simulation-category-correct-p' ...

(defmacro simulation-category-correct-p ()
  `(at-or-beyond-kb-format-revision-number-p 36))




;;; `Old-rules-correct-p' ...

(defmacro old-rules-correct-p ()
  `(at-or-beyond-kb-format-revision-number-p 37))




;;; `Graphs-opaque-p' ...

(defmacro graphs-opaque-p ()
  `(at-or-beyond-kb-format-revision-number-p 38))




;;; `All-rule-boxes-have-text-box-format' is true now that all instances of rule
;;; or its subclasses conform to the constraint that they have a non-nil text-box-
;;; format slot, even if they are "embedded".  Embedded rules in action buttons and
;;; user menu choices violated this constraint until now. (MHD 10/17/89)

(defmacro all-rule-boxes-have-text-box-format ()
  `(at-or-beyond-kb-format-revision-number-p 39))

(defmacro capabilities-are-ok-p ()
  `(at-or-beyond-kb-format-revision-number-p 40))




;; December 11, 1989

(defmacro no-unimplemented-superiors-p ()
  `(at-or-beyond-kb-format-revision-number-p 41))




;;; `Allow-format-frame-color-discrepancies-p' is true for kbs made after now,
;;; now that it is no longer necessary to bring colors up-to-date in order to
;;; have the defaults that allow color changes to work.

(defmacro allow-format-frame-color-discrepancies-p ()
  `(at-or-beyond-kb-format-revision-number-p 100))    ; (MHD 4/2/90)

;; ML wanted this number to be 100.




;; From now on, please date these. ML.



(defmacro connection-attributes-saved-p ()
  `(at-or-beyond-kb-format-revision-number-p 101))

;; This is needed to allow addition of the saved slot connection-attributes-plist
;; to the connection structure.  - AGH, 9/27/90




;;; Kb-security-implemented must go into effect at the same time that kbs are
;;; saved in a normalized state. (See SEQUENCES, for normalize-kb.)

(defmacro kb-security-implemented-p ()
  `(at-or-beyond-kb-format-revision-number-p 102))

;; 200 no longer used (was previously used for 
;; simulation-formulas-format-updated-for-3-0-p).



;; We are now maintining three distinct versions of G2. It is important that
;; kb-flags be kept in sequential order as encountered from any KB. Therefore:

;; (1) Flags that are going into 3.0 only and not retrofitted should start with
;; number 200.
;; (2) Flags going into 2.1 should start with 101, and should immediately be
;; carried forward into 3.0. 
;; (3) If any new flags are needed in 2.0, this will be a problem, because
;; flag 101 has been assigned to 2.1 and 3.0, and is not going into 2.0. If
;; anyone feels that a KB flag needs to go into 2.0, please see me first.

;; ML, Oct 22, 1990



;;; Done while removing two obsolete frame flags involved with
;;; maintaining G2 1.0 rule compatibility which was abandoned with 2.0.

(defmacro no-more-old-rules ()
  `(at-or-beyond-kb-format-revision-number-p 201))

;; Used by put-frame-flags in FRAMES2

#+unused
(defun no-more-old-rules-function ()
  (no-more-old-rules))

(defmacro redundant-simulation-formulas-notes-removed-p ()
  `(at-or-beyond-kb-format-revision-number-p 202))

(defmacro frame-flags-revised ()
  `(at-or-beyond-kb-format-revision-number-p 204))

(defun frame-flags-revised-function ()
  (frame-flags-revised))		;; used in FRAMES3


(defmacro permanent-blocks-marked ()
  `(at-or-beyond-kb-format-revision-number-p 205))



;; 206 no longer used (was previously used for 
;; generic-simulation-formulas-format-updated-for-3-0-p).




;; Needs a bit more work! (MHD 3/25/91)
;; ;;; `Allow-format-frame-maximum-width-discrepancies-p' is true for kbs
;; ;;; made after now, now that it is no longer necessary to bring the
;; ;;; maximum-format-width-for-text-cell slot up-to-date in order
;; ;;; to have the defaults that allow changing the "minimum width" to work.
;; 
;; (defmacro allow-format-frame-maximum-width-discrepancies-p ()
;;   `(at-or-beyond-kb-format-revision-number-p 205))    ; (MHD 3/25/91)




;;; Kb-flags at or above 207 have procedure code bodies saved with the compiled
;;; procedure.  

;;; The compile has changed so KB's at or after 208 have accurately saved
;;; procedure code bodies.  cpm, 7/24/91. 

;;; Now, it's 209, since the Inform and change-system-attribute action emitters,
;;; and the coerce-matching-element-type instruction have changed.  cpm, 8/6/91

;;; Note that this macro is no longer used, and its effect has been subsumed
;;; within stack-evaluator-3.0-beta-compilations-saved-p.  -jra 9/16/91

;(defmacro procedure-3.0-code-bodies-saved-p ()
;  `(at-or-beyond-kb-format-revision-number-p 209))




;;; Kb-flags incremented to 210 to substitute class saving-parameters
;;; for journal-and-backup-parameters - AGH, 8/19/91.


;;; Kb-flags incremented to 211 to mark the beginning of the saving of stack
;;; evaluator compilations for all items.  -jra 8/25/91

;; Note that this macro is no longer used.  -jra 9/16/91

;(defmacro stack-evaluator-3.0-beta-compilations-saved-p ()
;  `(at-or-beyond-kb-format-revision-number-p 211))


(defmacro permanent-blocks-really-marked-p  ()
  `(at-or-beyond-kb-format-revision-number-p 212))




;;; Kb-flags incremented to 213 to mark the beginning of compilation saving
;;; after a number of stack compiler bugs have been fixed.  -jra 9/16/91

;;; Fixed more bugs and changed how error messages for name and role failure get
;;; generated.  Bumped the number up to 214.  -jra 10/10/91

;;; Changed has a value to accept no-item and fixed unknowns returned in
;;; rule-let evaluations.  Bumping the number to 215 to force recompiles just
;;; before shipping Alpha releases.  -jra 10/14/91

(defmacro bug-fixed-3.0-beta-compilations-saved-p ()
  `(at-or-beyond-kb-format-revision-number-p 215))

;; This macro is obsolete, given bug-fixed-value-of-compilations-saved-p.  -jra
;; 11/19/91




(defun connections-for-class-slot-correct-format-p ()
  (at-or-beyond-kb-format-revision-number-p 216))

;; The slot putter for connections-for-class?  checks this and updates the format
;; to include the connection style indicator (the sixth element of the stubs
;; spec).  This must be done in the slot putter, rather than in a post-loading
;; function, since merge conflict checks are made at the end of read-frame-for-kb
;; (after the slot putter, but before any post-loading functions are run.  This
;; has to be a function since it is forward referenced.




;;; Today I changed procedures to make the class-of-procedure-invocation slot
;;; available.  Those procedures saved out before this time will have procedure
;;; invocations created by default.  The default after this will to not create
;;; procedure invocations.  -jra 11/9/91

(defmacro class-of-procedure-invocation-available-p ()
  `(at-or-beyond-kb-format-revision-number-p 217))




;;; Today Chris and I fixed bugs in the value of, the current value of, collect
;;; data, and coerce to datum which force recompilations.  -jra & cpm 11/19/91

;(defmacro bug-fixed-value-of-compilations-saved-p ()
;  `(at-or-beyond-kb-format-revision-number-p 218))


(defmacro new-tampering-algorithm-p ()
  `(at-or-beyond-kb-format-revision-number-p 219))

;;; Kb-flags advanced to 220 by ML on 12/11/91 for compatibility reasons. But a
;;; new test predicate is not needed. Reason: adding a savable slot
;;; mother-class-of-class (now known as foundation-class-of-class) to
;;; definitions.

;;; Today, we shifted the evaluator instruction numbers and need to force
;;; recompiles.  - cpm & jra, 12/13/91

;(defmacro base-evaluator-at-150-p ()
;  `(at-or-beyond-kb-format-revision-number-p 221))


(defmacro all-connections-have-frames-if-necessary ()
  `(at-or-beyond-kb-format-revision-number-p 222))

;;; Kb-flags advanced to 222 by ML on 12/16/91 for compatibility reasons. But a
;;; new test predicate is not needed. Reason: Saving foundation-class-list
;;; (previously known as mother-class-list) in KBs.

;;; Kb-flags advanced to 223 by AGH on 1/7/92.




;;; Kb-flags advanced to 224 to force recompilations of user kb expressions.
;;; Many bugs in rules, unknown expressions, and source node tree compilations
;;; have been made.  -jra & cpm 2/1/92

;;; Kb-flags advanced to 225 to force recompilations of user kb expressions.
;;; Changes made to var spot formats, function compilations when no-item is
;;; allowed, and context switching for cells and formulas.  -jra & cpm 2/5/92

;;; Kb-flags advanced to 226 to force recompilations of user kb expressions.
;;; Changes made to readouts, special-form nodes (value, current-value,
;;; simulated-value), and there-exists-literal and undeclared local names in
;;; procedures.  - cpm, 2/12/92

;;; Kb-flags advanced to 227 to force a recompile of user kb's.  A change was
;;; made to the emitter for maximum and minimum aggregator expressions.  - cpm,
;;; & jra 2/24/92.

;;; KB-flags advanced to 228 to force a recompile of user kb's to propagate a
;;; rule compiler fix which affects nested every forms around an action.

;;; KB-flags advanced to 229 to force a recompile of user kb's to propagate a
;;; rule compiler fix affecting nested function calls, collection-time,
;;; expiration-time, and relation forward chaining.  -jra 4/6/92

(defmacro version-3-0-beta-rev-2-recompiled-p ()
  `(at-or-beyond-kb-format-revision-number-p 229))


;;; Icon-editor-fixed-p tests kb-flags for a KB that should have had object
;;; definitions all checked to ensure that the icon-description-for-class?
;;; slot has had its filled polygons fixed so that points are stored in
;;; clockwise (normalized) order.  Failure to do this resulted in diffferences
;;; when subsequently edited, since the compiler for this slot did normalize
;;; the order.

;;; Icon-editor-fixed-p-function is a functional version of this macro.

(defmacro icon-editor-fixed-p ()
  `(at-or-beyond-kb-format-revision-number-p 230))


(defun icon-editor-fixed-p-function ()
  (icon-editor-fixed-p))

;; Icon-editor-fixed-p-function is only called by install-class-definition,
;; a forward reference, from KB-MERGE.  (MHD 4/21/92)

;;; 231 marks the version where we changed the names of the `text-size' feature
;;; of parts to be consistent with text-size names used elsewhere in g2.

(defmacro standardized-part-text-sizes-p ()
  `(at-or-beyond-kb-format-revision-number-p 231))




;;; Kb-flags bumped up to 232 to force a recompile of KBs.  This propagates
;;; several fixes in the compile including the new begin-activity instruction
;;; for better error messages.  The last fix to the compiler included here is a
;;; fix to the case-dispatch instruction to deal with integer ranges whose base
;;; was outside of a two byte positive integer.  -jra 6/14/92

(defmacro case-dispatch-range-fixed-p ()
  `(at-or-beyond-kb-format-revision-number-p 232))




;;; Kb-flags upped to 233 to mark a point past the fixing of the frame notes on
;;; procedure-invocation component particulars problem.  This macro is used by
;;; the eliminate-procedure-invocation-frame-notes post loading function to
;;; determine if a cleanup of inappropriate frame notes is required.

(defmacro procedure-invocation-frame-notes-fixed-p ()
  `(at-or-beyond-kb-format-revision-number-p 233))



;;; Kb-flags upped to 234 after at the time the frame flag
;;; table-may-not-be-wysiwyg added to tables.  Older tables will be treated as
;;; if they have this flag true.  The flag may be set true by update-text-cell.
;;; It is always left nil after the creation of or reformatting of a table.

;;; The predicate for this flag is table-wysiwyg-p-flag-in-this-kb.

(defmacro table-wysiwyg-p-flag-in-this-kb ()
  `(at-or-beyond-kb-format-revision-number-p 234))


;;; Kb-flags upped to 235 after the fix to code in FACILITIES not to offer the
;;; menu choice add-optional-subtable for the g2-user-mode slot of of g2-window
;;; instances.  Prior to this, users could legally add subtables here (in 3.0,
;;; although it might have been accompanied by a bombout writing ths slot in a
;;; table for the instance) and even numbers, strings, and truth values (in 2.0
;;; and 2.1).  Now, the post-loading function
;;; fix-possible-non-symbols-in-g2-user-mode eliminates any trace of any such
;;; instances that survived in KBs.

;;; The predicate for this flag is possible-non-symbols-in-g2-user-mode-fixed-p.

(defmacro possible-non-symbols-in-g2-user-mode-fixed-p ()
  `(at-or-beyond-kb-format-revision-number-p 235))

;; Added today in rev. 3.1. (MHD 12/28/92)

;; 236 was skipped at some point? - ben  7/6/93
;; 237 was used by mistake. - ben 7/6/93
;; -- So, that means: use 238, right? (--Right. KB-FLAGS was 237.  Now it's
;; 238.) (MHD 9/29/93)




;;; The KB flag `stable-non-human-readable-kbs?' is true when writing all 4.0+
;;; KBs.  It should only be false when reading pre-4.0 KBs.  When this is true,
;;; KBs are written in "stable" fashion.  That is, the encryption state is reset
;;; to a known, stable state at the beginning of reading or writing every
;;; string.  (There is one other thing being done to make KBs look more stable
;;; to a line-by-line diffs-like analyzer: writing a newline after each major
;;; "section" of the KB, and after each slot of a frame.  But this is being done
;;; unconditionally, since it does not introduce any incompatibilities in the
;;; reading direction.)  

(defmacro stable-non-human-readable-kbs? ()
  `(at-or-beyond-kb-format-revision-number-p 238))

;; Added today.  Along with the commit to 4.0.  (MHD 9/29/93)



;;; The function `loading-version-3-or-earlier-kb-p' is true when loading a KB
;;; created in a 3.0 or earlier version of G2.

(defun loading-version-3-or-earlier-kb-p ()
  (not (stable-non-human-readable-kbs?)))



;;; The KB flag `capabilities-are-obsolete-p' is true in 4.0+ G2.  In read-
;;; frame-for-kb, this kb flag is checked and the capabilities attached to
;;; pre 4.0 kbs are either added to the direct-superiors-of-class slot or
;;; the instance-configuration slot of the class definition.

(defmacro capabilities-are-obsolete-p ()
  `(at-or-beyond-kb-format-revision-number-p 239))




;;; The KB flag `no-blinking-areas-in-icon-descriptions-p' is true in 4.0+ G2.
;;; All ancient "blinking area" specs have been removed now from
;;; icon-description line drawing descriptions.  They were last seen in the
;;; Gensym demo KB pulp-and-paper as of 7/5/88.  Conceivably, one could load
;;; such an old KB.  
;;;
;;; Now, we've been taking them out of user icon line drawing directives
;;; for some time, but it's time to definitively mark this cleanup.  As we
;;; add new line drawing directives, these obsolete elements will become
;;; less easy, or impossible, to detect.
;;;
;;; See the cleanup in fix-icon-descriptions-after-reading-1 for further
;;; details.

(defmacro no-blinking-areas-in-icon-descriptions-p ()
  `(at-or-beyond-kb-format-revision-number-p 240))




;;; The KB flag `saving-subsecond-histories-p' is true in 4.0+ G2.  When loading
;;; a KB saved from software in which subsecond histories were saved, i.e., in
;;; snapshots, the new format for histories is used.  This format takes
;;; advantage of the fact that managed float arrays can now be saved as a
;;; built-in KB element.  The readers of the old format must be used when this
;;; is false.

(defmacro saving-subsecond-histories-p ()
  `(at-or-beyond-kb-format-revision-number-p 241))




;;; The KB flag `simulation-no-value-can-be-written-p' is true in 4.0+ G2.  When
;;; loading a KB saved from software in which this flag is true, the value of
;;; simulation-no-value is written as the new simulation-no-value (#) element.
;;; In older KBs, such values were converted via special code into the no-value
;;; (X) element.  The conversion will still have to be done for such old KBs.
;;; 
;;; Note that all of the cases in which no-value elements were written instead
;;; of no-simulation-value elements occured only in saved runtime data.
;;; Therefore, support for such occurances can be dropped when we stop
;;; supporting the loading of snapshots saved in this way, i.e., 3.0 KB
;;; snapshots.

(defmacro simulation-no-value-can-be-written-p ()
  `(at-or-beyond-kb-format-revision-number-p 242))




;;; The KB flag `kb-restrictions-reclassified-as-kb-configuration-p' is true in
;;; 4.0+ G2.  When loading a KB saved from software in which this flag is true,
;;; there are never any instances of the class kb-restrictions, which is never
;;; instantiated any more.  When a KB is read in that was saved before this
;;; version of the software, any instance of kb-restrictions is immediately
;;; classified as an instance of kb-configuration, an equivalent class with
;;; the newer, preferred name.
;;;
;;; The constant `kb-format-revision-for-kb-restrictions-reclassification' is
;;; bound to the particular kb-format revision number, i.e., this particular
;;; version of kb-flags corresponding to this particular feature.  This is to be
;;; used for the def-substitute-for-old-class form, which is found in module
;;; FILTERS.

(defconstant kb-format-revision-for-kb-restrictions-reclassification 243)

(defmacro kb-restrictions-reclassified-as-kb-configuration-p ()
  `(at-or-beyond-kb-format-revision-number-p
     kb-format-revision-for-kb-restrictions-reclassification))




;;; The KB flag `workspace-background-images-are-centered-p' is true in 4.0 KBs
;;; saved after 9/16/94 or so.  Previously, the x,y coordinates given in the
;;; background-images slot of a workspace positioned the upper-left corner of
;;; the image. They now position the center of the image.

(defun workspace-background-images-are-centered-p ()
  (at-or-beyond-kb-format-revision-number-p 244))




;;; The kb flag `specific-procedure-method-simplified-to-method-p' is true in
;;; 4.0 KBs saved after 12/12/94 when we changed the class name
;;; specific-procedure-method to method and procedure-method to
;;; method-declaration.  -jra 12/12/94

(defconstant kb-flag-when-specific-procedure-method-died 245)

(defmacro specific-procedure-method-simplified-to-method-p ()
  `(at-or-beyond-kb-format-revision-number-p
     kb-flag-when-specific-procedure-method-died))




;;; The kb flag `reinstated-meter-g2-region-memory-size-p' is true in 4.0 Beta
;;; Rev. 20 kbs and later, after the ambiguous meaning of
;;; g2-region-memory-available in g2-meter-name was resolved by reintroducing
;;; the function g2-mem

(defmacro reinstated-meter-g2-region-memory-size-p ()
  `(at-or-beyond-kb-format-revision-number-p 246))




;;; The kb flag `insert-action-duplicate-element-fix-in-kb-p' is true in 4.0 Beta
;;; Rev. 24 kbs and later, and indicates that the insert action will, by default,
;;; signal errors for duplicate elements, when duplicates are not allowed.

;;; KB's created before this version will not use the insert action duplicate
;;; element bug fix.  This is needed for KB's, such as GDA and GUIDE.

(defmacro insert-action-duplicate-element-fix-in-kb-p ()
  `(at-or-beyond-kb-format-revision-number-p 247))





;;; The kb flag `bad-4-0-beta-magnifications-in-text-boxes-removed-p' is true
;;; after 4.0 Beta Phase II (after 4.0b33).  Some bad magnification were put in
;;; due to a bug in the new system procedure for magnifying text.  This gets
;;; checked for and fixed up if necessary upon reading when this flag is false.

(defmacro bad-4-0-beta-magnifications-in-text-boxes-removed-p ()
  `(at-or-beyond-kb-format-revision-number-p 248))

(defun bad-4-0-beta-magnifications-in-text-boxes-removed-p-function ()
  (bad-4-0-beta-magnifications-in-text-boxes-removed-p))
  

;;; the kb flag `new-get-connection-vertex-behavior-p' causes
;;; g2-get-connection-vertices to be disciplined about the number of extra
;;; connections that it adds to the list

(defmacro new-get-connection-vertex-behavior-p ()
  `(at-or-beyond-kb-format-revision-number-p 249))




;;; The kb flag `new-item-configuration-key-binding-grammar-p' is true when the
;;; KB was saved with the new item config grammar for key bindings ("typing"
;;; vs. "pressing", etc).  If false, then attribute displays showing the item
;;; configuration are updated by a post-loading function.

(defmacro new-item-configuration-key-binding-grammar-p ()
  `(at-or-beyond-kb-format-revision-number-p 250))




;;; The kb flag `strict-prohibition-of-connections-on-frames-in-attributes-p'
;;; states that as of now we will strictly prohibit connections/stubs from being
;;; placed upon objects in attributes.  This is not part of G2's current model
;;; of what a kb is; such stubs can confuse code that traverses the KB.

(defmacro strict-prohibition-of-connections-on-frames-in-attributes-p ()
  `(at-or-beyond-kb-format-revision-number-p 251))


;;; The kb flag `all-icons-are-polychrome-p' states that as of now we have
;;; all polychrome icons in saved KBs.

(defmacro all-icons-are-polychrome-p ()
  `(at-or-beyond-kb-format-revision-number-p 252))




;;; The KB flag `new-grammar-for-class-specific-attributes-p' is true in 4.0+.

(defmacro new-grammar-for-class-specific-attributes-p ()
  `(at-or-beyond-kb-format-revision-number-p 253))

;; NOTE: DO NOT USE KB FLAG 253!
;; 
;; Note that we have withdrawn KB flag 253.  This was added inbetween Rev. 0 and
;; Rev. 1, and it was later decided that it was unacceptible to disallow
;; backward compatibility from Rev. 1 to Rev. 0.  So, we have moved kb-flags
;; backwards to 252, and changed the the function read-initial-plist-from-kb to
;; fix up the plist so that it can never contain the flags number 253.  If it
;; does, that function will decrement the number back to 252.  The predicate
;; new-grammar-for-class-specific-attributes-p will be left referencing 253, so
;; it will continually perform the update it does for all rev. 0 and rev. 1 KBs.
;; This is harmless, though a little slow.  Hopefully we can avoid another awful
;; kludge like this one in the future by only updating the kb-flags when we are
;; absolutely forced to.  The next value should be 254.  -jra 8/15/95


;;; The KB flag `vectorized-procedure-environments-attributes-p' marks a change
;;; from list to vector storage in code body argument-list-description,
;;; returned-values-description and byte-code-body-environment-descriptions see
;;; convert-frame-internals-to-vectors-as-necessary.

(defmacro vectorized-procedure-environments-attributes-p ()
  `(at-or-beyond-kb-format-revision-number-p 254))




;;; The KB flag `fixup-attribute-configuration-error-p' is used to limit the
;;; kbs that fix-up-configuration-attribute-error is called for.  Since 254
;;; is the first kb-flag in G2 5.0, this flag can be used to exempt 5.0 kbs
;;; from the fixup.

(defmacro fixup-attribute-configuration-error-p ()
  `(before-kb-format-revision-number-p 254))




;;; The KB flag `two-code-body-on-error-p' indicates that on-error statements
;;; will now emit two code bodies rather than three.  This requires a
;;; complete recompile because it changes the way in which run-time errors
;;; are handled.

(defmacro two-code-body-on-error-p ()
  `(at-or-beyond-kb-format-revision-number-p 255))




;;; The KB flag `struct-renamed-to-structure-p' indicates that on-error
;;; statements will now emit two code bodies rather than three.  This requires a
;;; complete recompile because it changes the way in which run-time errors are
;;; handled.

(defmacro struct-renamed-to-structure-p ()
  `(at-or-beyond-kb-format-revision-number-p 256))




;;; `possible-icon-variables-alist-p' indicates that a kb may have been
;;; created with a g2 that used alists for icon-variables.
;;; This version of g2 was never shipped, although gensym employees may
;;; have created invalid kbs.

(defmacro possible-icon-variables-alist-p ()
  `(not (at-or-beyond-kb-format-revision-number-p 258)))


(defmacro use-kind-for-remote-procedure-declaration-argument-passing-style-p ()
  `(at-or-beyond-kb-format-revision-number-p 259))


;;; `methodized-actions-part-one-p' is the flag indicates that
;;;  the KB has been created with a KB which has been recompiled for
;;;  methodized actions.  A recompile is required because actions will
;;;  now compile down to call instructions.

(defmacro methodized-actions-part-one-p ()
  `(at-or-beyond-kb-format-revision-number-p 259))


;;; `methodized-actions-part-two-p' is a second flag indicating that
;;; the KB has been created with a KB which has been recompiled for
;;; methodized actions.  This second flag was needed so that KBs will
;;; get several fixes, including the g2-clone procedure.

(defmacro methodized-actions-part-two-p ()
  `(at-or-beyond-kb-format-revision-number-p 260))


;;; `remove-methodized-actions-p'

(defmacro remove-methodized-actions-p ()
  `(at-or-beyond-kb-format-revision-number-p 261))


;;; The macro `old-format-for-default-overrides-p' is used to determine
;;; if a KB was created before a change in the format of the default-overrides
;;; slot on definitions for 5.0r0.

(defmacro old-format-for-default-overrides-p ()
  `(before-kb-format-revision-number-p 262))

(defun old-format-for-default-overrides-p-function ()
  (old-format-for-default-overrides-p))




;;; The macro `contains-move-from-surrounding-local-var-p' is used to determine
;;; whether or not this KB could have compilations containing the new
;;; stack-instruction move-from-surrounding-local-var.  (Note that this macro is
;;; never used, but is here as part of the mantra of things-to-do when upping
;;; the kb-flags to prevent backwards loading of KBs.)  -jallard 6/16/97

(defmacro contains-move-from-surrounding-local-var-p ()
  `(at-or-beyond-kb-format-revision-number-p 263))




;;; The macro `everything-on-a-workspace-is-an-item-p' can be  used to determine
;;; whether or not this KB can contain instances of new system classes defined
;;; to support the Nevada project; for example, table-item.

(defmacro everything-on-a-workspace-is-an-item-p ()
  `(at-or-beyond-kb-format-revision-number-p 264))




;;; `needs-author-or-authors-fixup-p' determines whether this KB
;;; might contain extra, unnecessary entries (repeated edits by a single author
;;; need cleanups).

(defmacro needs-author-or-authors-fixup-p ()
  `(or (=f kb-flags 262)
       (=f kb-flags 263)))

;;; `newer-than-author-or-authors-bug-p' 

(defmacro newer-than-author-or-authors-bug-p ()
  `(>=f kb-flags-of-software 264))



;;; The macro `rewritten-procedure-inlining-p' determines whether or not this KB
;;; was saved after the October '97 rewrite of inlining.  All inlining before
;;; this point will be made incomplete and we'll force a recompile on it.  Also,
;;; all cached parses for inlined procedures are being dropped at this point.
;;; In the future when grammer changes are made, new kb-flag revisions will be
;;; needed to force dropping the cacached parse results.

(defmacro rewritten-procedure-inlining-p ()
  `(at-or-beyond-kb-format-revision-number-p 265))


;;; KB-flags 266 is uuids for every item.  Note that this is the first feature
;;; that is unique to 6.x KBs, so it can be used to implement the predicate that
;;; follows, to identify a 5.x KB by its absence.

(defmacro evaluation-aggregates-contain-frame-serial-numbers ()
  `(before-kb-format-revision-number-p 266))



;;; The function `loading-version-5-or-earlier-kb-p' is true when loading a KB
;;; created in a 5.x or earlier version of G2, which is based on whether
;;; kb-flags being >= 266.

(defun loading-version-5-or-earlier-kb-p ()
  (not (at-or-beyond-kb-format-revision-number-p 266)))





(defmacro instruction-argument-counts-not-on-stack-p ()
  `(at-or-beyond-kb-format-revision-number-p 267))

(defmacro does-not-need-null-author-fixup-p ()
  `(at-or-beyond-kb-format-revision-number-p 268))

(defmacro need-to-normalize-message-properties-p ()
  `(before-kb-format-revision-number-p 269))

(defun-simple need-to-normalize-message-properties-p-function ()
  (need-to-normalize-message-properties-p))

(defconstant g2-version-6-general-kb-flags 270)

(defmacro workspace-edges-are-normalized-p ()
  `(at-or-beyond-kb-format-revision-number-p g2-version-6-general-kb-flags))

(defmacro digital-clocks-are-fixed-p ()
  `(at-or-beyond-kb-format-revision-number-p g2-version-6-general-kb-flags))




;;; `Tabular-functions-of-1-arg-sorted-by-Unicodes-p' should have gone in
;;; as part of 5.0r0 which is when the change actually happened. This is
;;; part of the fix for HQ-3315043, which wasn't unearthed until a
;;; Japanese user upgraded from 4x to 5x. Tabular functions over strings
;;; used to be sorted on the basis of their escape sequences when
;;; Japanese (etc.) was used in 4.x and before. As a result they are
;;; in the wrong order when imported into 5.x (6x) and have to be
;;; resorted as soon as the kb is loaded.  ddm 1/25/00

(defmacro tabular-functions-of-1-arg-sorted-by-Unicodes-p ()
  `(at-or-beyond-kb-format-revision-number-p g2-version-6-general-kb-flags))


;;; `Item-reference-parameters-in-v6-prerelease-p' is a flag that's true up
;;; until the prerelease of 6.0 of around mid-February 2000.  During the
;;; prerelease until this time, item-reference-parameters was a system table
;;; with one attribute (show-uuids-in-attribute-tables) exposed to users.
;;; After this time, the class is obsolete and has "block" as its substitute,
;;; but its slots live on in miscellaneous-parameters.

(defmacro item-reference-parameters-in-v6-prerelease-p ()
  `(at-or-beyond-kb-format-revision-number-p g2-version-6-general-kb-flags))


(defmacro fixed-representations-of-default-overrides-p ()
  `(beyond-kb-format-revision-number-p g2-version-6-general-kb-flags))

;;; The constant `last-kb-flags-saved-with-item-reference-parameters' is bound
;;; to 272, which is the highest version of kb-flags that may have been saved

(defconstant last-kb-flags-saved-with-item-reference-parameters 272)


;;; The defconstant `g2-version-7-beta-0-kb-flags' is the kb-flags for KBs saved
;;; in 7.0 beta rev 0.  KBs saved in alpha versions of 7.0 have kb-flags of 270,
;;; the same as 6.x KBs.

(defconstant g2-version-7-beta-0-kb-flags 274)

;;; The defconstant `g2-version-8-beta-0-kb-flags' is the kb-flags for KBs
;;; saved in 8.0 beta rev 0.  KBs saved in alpha versions of 8.0 have kb-flags
;;; of 274, the same as 7.x KBs.  NOTE, in some pre-release versions of G2
;;; 8.0b0, the kb-flags had not been bumped up yet. It is being bumped up on
;;; 5/21/2004.

(defconstant g2-version-8-beta-0-kb-flags 275)


;;; The defconstant `g2-version-8-1-alpha-0-kb-flags' is the kb-flags for KBs
;;; saved in 8.1 Alpha rev 0.  -jv, 1/20/05

(defconstant g2-version-8-1-alpha-0-kb-flags 276)


;;; The defconstant `g2-version-8-1-beta-0-kb-flags' is the kb-flags for KBs
;;; saved in 8.1 Beta Rev 0.  Note that this was set after the addition of the
;;; G2-BPEL/G2GL facility, and so includes all those new classes. -mhd, 3/9/05

(defconstant g2-version-8-1-beta-0-kb-flags 277)


;;; The defconstant `g2-version-81r0-kb-flags' is the kb-flags for KBs saved in
;;; 8.1 Rev 0. -mhd, 4/24/05

(defconstant g2-version-81r0-kb-flags 278)

;;; The defconstant `g2-version-82r0-kb-flags' is the kb-flags for KBs saved in
;;; 8.2 Rev 0. New slot in logbook-parameters, etc. -fmw, 11/3/05

(defconstant g2-version-82r0-kb-flags 279)

;;; The defconstant `g2-version-8-3-alpha-0-kb-flags' is the kb-flags for KBs
;;; saved in 8.3 Alpha Rev 0. New classes for sockets and web services.  No
;;; particular need to check this value, just refuse to load kbs in older G2.
;;; yduJ, 8/18/06

(defconstant g2-version-8-3-alpha-0-kb-flags 280)

;;; The defconstant `g2-version-2011-kb-flags' is the kb-flags for KBs saved
;;; between 8.3r1 (see r68228) to 2011.

(defconstant g2-version-2011-kb-flags 281)

;;; The defconstant `g2-version-2015-kb-flags' is the kb-flags for KBs saved in
;;; G2 2015 beta (since January 2015). New KB instruction `compare-and-swap', etc.
;;; -- Chun Tian (binghe),  Jan 18, 2015.

(defconstant g2-version-2015-beta-kb-flags 282)

(defmacro compare-and-swap-as-kb-instruction-p ()
  `(at-or-beyond-kb-format-revision-number-p g2-version-2015-beta-kb-flags))

;; CHANGE THE DEFPARAMETER KB-FLAGS WHEN YOU ADD TO THIS!!!









;;; `Kb-flags-from-last-kb-read' is bound around the execution of post-
;;; loading functions to the value that kb-flags had been bound to
;;; during the read, i.e., the value of kb-flags at the time the kb was saved.

(defvar kb-flags-from-last-kb-read)



;;; `System-version-from-last-kb-read' is bound around the execution of post-
;;; loading functions to the value that system-version-from-kb-being-read had
;;; been bound to during the read, i.e., the value of current-system-version at
;;; the time the kb was saved.

(defvar system-version-from-last-kb-read)


;;; The variables `system-revision-from-last-kb-read' and
;;; `system-quality-from-last-kb-read' are the cached result of calling
;;; get-quality-and-revision-of-system-version on
;;; system-version-from-last-kb-read, since computing them is expensive.

(defvar system-revision-from-last-kb-read)
(defvar system-quality-from-last-kb-read)

(defun count-and-fix-invalid-items () 
  (let ((cnt 0)) 
    (loop for instance being each class-instance of 'object do 
      (when (and (not (permanent-block-p instance))
                 (not (transient-p instance))
                 ;; GENSYMCID-716 G2 graphics issues after KB clear / reload.
                 (not (g2gl-variable-compilation-p instance)))
        (incff cnt) 
        (set-transient instance) 
        (format T "Fixed the invalid frame number ~A~%" cnt))) 
    cnt))
