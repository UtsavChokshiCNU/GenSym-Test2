;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module CONNECT4

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Andreas Hofmann



(declare-forward-reference 
  decache-roles-for-entities-related-to-this-connection function)

(declare-forward-reference add-or-delete-subworkspace-connection-post function)


(declare-forward-reference loading-kb-p variable)

(declare-forward-reference decache-roles-for-connection-post function)

(declare-forward-reference transfer-blocks-with-their-external-connections function)

(declare-forward-reference disable-stack-error variable)


;;;; Subworkspace Cloning



;;; `Clone-connections-for-block' must be called when cloning a workspace
;;; subblock with connections, in order to clone the connectivity between block
;;; and other blocks in plist-of-blocks-and-corresponding-clones.
;;; plist-of-blocks-and-corresponding-clones is a plist of blocks, all of
;;; which are workspace subblocks, and corresponding clones in need of having
;;; their connections cloned.  (If (connections block) is nil, the call to this
;;; may be omitted as an optimization.)

;;; This does not return any value; it just has the side effect of cloning the
;;; connections of block.

#-connections-v2
(defun clone-connections-for-block 
       (block cloned-block plist-of-blocks-and-corresponding-clones)
  (loop for rest-of-block-connections
	    on (connections block)
	as next-block-connection-or-port-name
	   = (car rest-of-block-connections)
	for rest-of-cloned-block-connections
	    on (connections cloned-block)
	when (and (not (symbolp next-block-connection-or-port-name))
		  ;; NOTE: the goal here is to find those internal connections, we test on
		  ;; output end of block, then see if the input end is also in the cloned
		  ;; blocks.
		  (eq (output-end-object next-block-connection-or-port-name)
		      block))
	do
    (let* ((block-at-other-end
	    (input-end-object next-block-connection-or-port-name))
	   (cloned-block-at-other-end
	    (getfq plist-of-blocks-and-corresponding-clones
		   block-at-other-end)))
      (when cloned-block-at-other-end
	;; if block-at-other-end is in objects-to-clone (connection is not external)
	(cond
	  ((neq block block-at-other-end)
	   ;; If connection does not loop back to same block
	   (loop for connection in (connections block-at-other-end)
		 for cloned-connection-stub
		     in (connections cloned-block-at-other-end)
		 ;; NOTE: here the LOOP assumes that `block-at-other-end' and
		 ;; `cloned-block-at-other-end' have the same connection orders.
		 when (eq connection next-block-connection-or-port-name)
		 do
	     ;; Correct cloned connection is cloned-connection-stub.
	     ;; Tie this to cloned block.  Rest-of-cloned-block-connections
	     ;; has a nil place holder as its first element which must now
	     ;; be replaced by the cloned connection.
	     (make-cloned-connection-stub-be-copy-of-connection
	       rest-of-cloned-block-connections cloned-connection-stub
	       connection cloned-block cloned-block-at-other-end)))
	  (t ; if connection does loop back to same block
	   (loop for connection in (cdr rest-of-block-connections)
		 for cloned-connection-stub in (cdr rest-of-cloned-block-connections)
		 when (eq connection next-block-connection-or-port-name)
		 do
	     (let ((extra-stub ; to be replaced by cloned-connection-stub
		    (car rest-of-cloned-block-connections)))
	       (make-cloned-connection-stub-be-copy-of-connection
		 rest-of-cloned-block-connections cloned-connection-stub
		 connection cloned-block cloned-block-at-other-end)
	       (delete-connection extra-stub)))))))))

;; This is only called from clone-subblocks-of-block (module KB-LOAD1) at present.
;; (MHD 7/8/92)

;;; the helper macro `connection-item-equal' is used to compare two connection-item in
;;; which their connection names can match with each other.

#+connections-v2
(def-substitution-macro connection-item-input-equal (c1 c2)
  (equal (connection-item-input-names c1)
	 (connection-item-input-names c2)))

#+connections-v2
(def-substitution-macro connection-item-output-equal (c1 c2)
  (equal (connection-item-output-names c1)
	 (connection-item-output-names c2)))

#+connections-v2
(def-substitution-macro input-end-position-eq (connection-1 connection-2)
  (=f (input-end-position connection-1)
      (input-end-position connection-2)))

#+connections-v2
(def-substitution-macro output-end-position-eq (connection-1 connection-2)
  (=f (output-end-position connection-1)
      (output-end-position connection-2)))

;;;
;;; The connections-v2 version of `clone-connections-for-block':
;;;
;;;       +---+                         +---+
;;;   +-->| B | block-at-other-end  +-->| B'| cloned-block-at-other-end
;;;   |   +---+                     |   +---+
;;;   |                             | cloned-connection-stub
;;;   |                             |
;;;   | block-connection            +--<* loose-end1
;;;   |
;;;   |          +---+              +-->* loose-end2
;;;   |       +->| B"|              |
;;;   |      /   +---+              | cloned-block-connection
;;; +-+-+   /                     +-+-+
;;; | H +--+  block               | H'| cloned-block
;;; +---+                         +---+
;;;
;;; The goal is to find out the correct `cloned-block-connection' & `cloned-connection-stub'
;;; in the connection hash table of `cloned-block' & `cloned-block-at-other-end', and then
;;; connect `cloned-block' with `cloned-block-at-other-end' by reusing `cloned-connection-stub'
;;; and deleting the following three left things:
;;;
;;;  1. loose-end1
;;;  2. loose-end2
;;;  3. cloned-block-connection
;;;
;;; It's important that the newly made connection looks exactly the same as the original
;;; connection: both connection positions and connection port names are the same:
;;;
;;; (input-end-position) *--------------------------> (output-end-position)
;;;
;;; -- Chun Tian (binghe), May 2016.

#+connections-v2
(defun clone-connections-for-block (block cloned-block plist-of-blocks-and-corresponding-clones
				    &aux
				    (connection-table (connections block))
				    (cloned-connection-table (connections cloned-block)))
  (loop for block-connection being each output-connection of block
	for block-connection-item = (get-connection-item block-connection connection-table)
	for block-at-other-end = (get-block-at-other-end-of-connection block-connection block)
	for cloned-block-at-other-end = (getfq plist-of-blocks-and-corresponding-clones
					       block-at-other-end)
	when cloned-block-at-other-end
	do
    ;; GENSYMCID-1660: Regression test MAKE-SUBWORKSPACE failed after CRT workarounds
    ;;
    ;; Previously, the double For-clauses of connections in above LOOP is not reliable: because in
    ;; hash-table, no orders are guaranteed. Thus we must make another search to find out
    ;; the correct `cloned-block-connection'. -- Chun Tian (binghe), Feb 2016.
    (let* ((cloned-block-connection
	    (loop for cloned-connection being each output-connection of cloned-block
		  for cloned-connection-item
		    = (get-connection-item cloned-connection cloned-connection-table)
		  when (and (not (connection-item-output-marked? cloned-connection-item))
			    (connection-item-output-equal cloned-connection-item
							  block-connection-item)
			    ;; GENSYMCID-1771: Color changing by cloning in G2-2015.5
			    ;;
			    ;; Note: just comparing connection names are not enough for choosing
			    ;; the correct corresponding connections. When there's no connection
			    ;; names at all, the positions of two connections must be compared.
			    ;; -- Chun Tian (binghe), May 2016.

                            ;; This is still an unreliable way to identify the connection. connection can have no name, 
                            ;; position can coincide but this would be not the connection intended.
			    (input-end-position-eq cloned-connection block-connection))
		  do
	      (return cloned-connection)))
	   (connection-table-at-other-end
	    (connections block-at-other-end))
	   (connection-item-at-other-end
	    (get-connection-item block-connection connection-table-at-other-end))
	   (cloned-connection-table-at-other-end
	    (connections cloned-block-at-other-end))
	   (cloned-connection-stub
	    (loop for cloned-connection being each input-connection of cloned-block-at-other-end
		  for cloned-connection-item
		    = (get-connection-item cloned-connection cloned-connection-table-at-other-end)
		  when (and (not (connection-item-input-marked? cloned-connection-item))
			    (connection-item-input-equal cloned-connection-item
							 connection-item-at-other-end)
			    (output-end-position-eq cloned-connection block-connection))
		  do
	      (setf (connection-item-input-marked? cloned-connection-item) t)
	      (return cloned-connection))))
      ;; Note: in rare cases one of cloned-block-connection & cloned-connection-stub
      ;; is nil and the connection clone process cannot continue. We need to know why.
      ;; -- Chun Tian (binghe), Feb 2016.
      ;;
      ;; GENSYMCID-1676: Disconnection by cloning in G2-2015.3
      ;;
      ;; Updates: the above issue should be fixed now, by fixing the initializations of slots
      ;; `connection-item-output-marked?' and `connection-item-input-marked?' in connect1.lisp.
      ;; However, it's safe to keep the `assert' and `when' protects. --binghe, Mar 2016
      (assert-for-development
	(and cloned-block-connection cloned-connection-stub))
      ;; Correct cloned connection is cloned-connection-stub.
      ;; Tie this to cloned block.
      (make-cloned-connection-stub-be-copy-of-connection
       cloned-block-connection
       cloned-connection-stub
       block-connection
       cloned-block
       cloned-block-at-other-end)
       ; we done with this connection - let's prevent it from being re-processed 
      (let ((cloned-connection-stub-connection-item
             (get-connection-item cloned-connection-stub cloned-connection-table)))
        (setf (connection-item-output-marked? cloned-connection-stub-connection-item) t)))))

;;; NOTE: in connections v1, for those internal connections in the block group, the
;;; connection is not actually cloned, instead only the connection names and a NIL
;;; will be put into the connection list. Later, in `clone-connections-for-block',
;;; those NIL connections will be then replaced with connection structures, by
;;; `make-cloned-connection-stub-be-copy-of-connection':
;;;
;;; +---+           +---+
;;; | A +---------->| B | (original connection)
;;; +---+           +---+
;;; +---+           +---+
;;; | A'+-->L       | B'| (clone-connections-slot, L = loose-end)
;;; +---+           +---+
;;; +---+           +---+
;;; | A'+---------->| B'| (clone-connections-for-block, a loose-end is deleted)
;;; +---+           +---+
;;;
;;; -- Chun Tian (binghe), Aug 2015.

#-connections-v2
(defun clone-connections-slot
       (old-slot-value old-frame new-frame blocks-in-bounding-box?)
  (loop with previous-connection? = nil
	for connection-or-port-name in old-slot-value
	collect
	  (if (symbolp connection-or-port-name)
	      connection-or-port-name
	      (let* ((input-end-object
		       (input-end-object connection-or-port-name))
		     (new-connection?
		       (if (or (eq old-frame input-end-object)
			       (not (memq input-end-object
					  blocks-in-bounding-box?)))
			   (clone-stub-for-connection
			     previous-connection? ; what's the purpose?
			     connection-or-port-name
			     old-frame
			     new-frame))))
		(setq previous-connection? connection-or-port-name)
		new-connection?)) ; could be NIL here
	  into new-connections using slot-value-cons
	finally
	  (setf (connections new-frame) new-connections)
	  (loop for connection being each connection of new-frame
		do (determine-subworkspace-connection-posts-for-object
		     connection new-frame))))

;;; NOTE (continued): however above idea won't work for the connections v2,
;;; because all connections must be stored as connection/connection-item pairs, and
;;; there's no way to have NIL connections for later modification. This is the last
;;; outstanding bug found in #+connections-v2.
;;;
;;; As a solution, we're going to clone all internal connections twice: one as input
;;; connections, one as output connections, and both of them have loose-ends. Then,
;;; in `clone-connections-for-block', we need to delete more things: two loose-ends,
;;; one extra stub connection:
;;;
;;; +---+           +---+
;;; | A +---------->| B | (original connection)
;;; +---+           +---+
;;; +---+           +---+
;;; | A'+==>L   L~~>| B'| (clone-connections-slot, L = loose-end)
;;; +---+           +---+
;;; +---+           +---+
;;; | A'+~~~~~~~~~~>| B'| (clone-connections-for-block, two loose-ends and
;;; +---+           +---+  one extra connection are deleted)
;;; Here A' is cloned-block, B' is cloned-block-at-other-end 
;;; Also the picture does not take into account the self-connected block

#+connections-v2
(defun clone-connections-slot
       (old-slot-value old-frame new-frame blocks-in-bounding-box?)
  (declare (ignore blocks-in-bounding-box?))
  (loop with new-connection-table = (make-connection-item-table)
	for (connection . connection-item) being each binary-tree-entry-cons
					   of old-slot-value
	for new-connection
	    = (clone-stub-for-connection nil connection old-frame new-frame)
	for new-connection-item = (make-connection-item new-connection)
	do
    ;; 1. insert into the binary tree
    (setf (get-connection-item new-connection new-connection-table)
	  new-connection-item)
    ;; 2. now handle connection names
    (cond
      ((connection-item-duplicated? connection-item)
       (let* ((extra-connection
	       ;; By putting `connection' in place of `previous-connection?',
	       ;; we want to create an input connection here.
	       (clone-stub-for-connection connection connection old-frame new-frame))
	      (extra-connection-item
	       (make-connection-item extra-connection)))
	 ;; insert the extra connection
	 (setf (get-connection-item extra-connection new-connection-table)
	       extra-connection-item)
	 ;; in case connection item is duplicated, the first connection (new)
	 ;; shares the output names, the second connection (extra) shares
	 ;; the input names.
	 (setf (connection-item-output-names new-connection-item)
	       (copy-list-using-slot-value-conses
		 (connection-item-output-names connection-item)))
	 (setf (connection-item-input-names extra-connection-item)
	       (copy-list-using-slot-value-conses
		 (connection-item-input-names connection-item)))))
      (t
       ;; in case connection item is not duplicated, only one of
       ;; input/output names is non-nil, and we don't care which, just copy
       ;; them all into new-connection-item.
       (setf (connection-item-output-names new-connection-item)
	     (copy-list-using-slot-value-conses
	       (connection-item-output-names connection-item)))
       (setf (connection-item-input-names new-connection-item)
	     (copy-list-using-slot-value-conses
	       (connection-item-input-names connection-item)))))
	finally
	  (setf (connections new-frame) new-connection-table)
	  ;;
	  ;; GENSYMCID-1779: GDA propagation of values issue
	  ;;
	  ;; NOTE: in connections-v1 version of this function, there was a LOOP
	  ;; here for subworkspace connection posts detection of all output
	  ;; connections of the newly created frame. In another words, the
	  ;; `input-end-object` of these output connections, if it has a
	  ;; subworkspace, this information will be stored into the connection
	  ;; object. However, since some of these output connections (if they're
	  ;; internal connections in the bounding box) will be later deleted in
	  ;; step 3 of `make-cloned-connection-stub-be-copy-of-connection', it's
	  ;; not correct to do such detections here any more. Instead, we have
	  ;; moved the `input-end subworkspace connection posts detection` into
	  ;; `make-cloned-connection-stub-be-copy-of-connection', together with
	  ;; `output-end subworkspace connection posts detection'.
	  ;;
	  ;; -- Chun Tian (binghe), Jun 2016.
	  (return nil)))

#-connections-v2
(defun make-cloned-connection-stub-be-copy-of-connection
    (rest-of-cloned-block-connections
     cloned-connection-stub
     connection
     cloned-block
     cloned-block-at-other-end)
  ;; replace NIL with the connection, see NOTE of `clone-connections-slot'.
  (setf (car rest-of-cloned-block-connections)
	cloned-connection-stub)
  ;; copy delta-or-deltas
  (setf (delta-or-deltas cloned-connection-stub)
	(copy-list-using-connection-conses
	  (delta-or-deltas connection)))
  (let ((output-loose-end
	  (output-end-object cloned-connection-stub))
	(input-loose-end
	  (input-end-object cloned-connection-stub)))
    (cond
      ;; NOTE: here, the first branch should never be true for undirected
      ;; connections, because the way make-stub working is to use output
      ;; loose-end for the loose-end. Therefore, the wrong tested block
      ;; `cloned-block' was never found by previous developers. It should
      ;; be `cloned-block-at-other-end'. -- Chun Tian (binghe), Aug 2015
      ((eq output-loose-end
	   cloned-block-at-other-end) ; old: cloned-block
       (delete-connection-in-block
	 input-loose-end cloned-connection-stub nil)
       (delete-frame input-loose-end)  ; delete loose end
       (setf (input-end-object cloned-connection-stub)
	     cloned-block))
      (t
       (delete-connection-in-block
	 output-loose-end cloned-connection-stub nil)
       (delete-frame output-loose-end) ; delete loose end
       (setf (output-end-object cloned-connection-stub)
	     cloned-block)))
    (setf (input-end-position cloned-connection-stub)
	  (input-end-position connection))
    (setf (output-end-position cloned-connection-stub)
	  (output-end-position connection))
    ;; NOTE: input-end subworkspace connection posts were detected earlier
    ;; in `clone-connections-slot'. -- Chun Tian (binghe), Jun 2016.
    (determine-subworkspace-connection-posts-for-object
      cloned-connection-stub (output-end-object cloned-connection-stub))))

;;; +---+                      +---+                           +---+
;;; | B | block-at-other-end   | B'| cloned-block-at-other-end | B'|
;;; +---+                      +---+                           +---+
;;;   ^                          ^ <-- cloned-connection-stub -->^
;;;   |   connection             |                               |
;;;   |                          * loose-end1 (x)                |
;;;   |                                                          |
;;;   |                          * loose-end2 (x)                |
;;;   |                          ^                               |
;;;   |                          | cloned-block-connection (x)   |
;;; +-+-+                      +-+-+                           +-+-+
;;; | H | block                | H'|       cloned-block        | H'|
;;; +---+                      +---+                           +---+
;;;  (0)                        (1)                             (2)
;;;
;;; the goal is to deleted those with (x) and go from (1) to (2). --binghe, Aug 2015.

#+connections-v2
(defun make-cloned-connection-stub-be-copy-of-connection
    (cloned-block-connection
     cloned-connection-stub
     connection
     cloned-block
     cloned-block-at-other-end)
  (let* ((same-cloned-block?
	  (eq cloned-block cloned-block-at-other-end))
	 (cloned-block-connection-table
	  (connections cloned-block))
	 (cloned-block-connection-item
	  (get-connection-item cloned-block-connection
			       cloned-block-connection-table)))

    ;; 1. delete cloned-block-connection from cloned-block
    (setf (get-connection-item cloned-block-connection
			       cloned-block-connection-table)
	  nil)
    (delete-connection-item cloned-block-connection
			    cloned-block-connection-table)

    ;; 2. connect cloned-block with cloned-block-at-other-end
    (cond (same-cloned-block?
	   ;; a) in case of same cloned block, copy connection output names
	   ;; from `cloned-block-connection' into cloned-connection-stub.
	   (let ((cloned-connection-stub-item
		  (get-connection-item cloned-connection-stub
				       cloned-block-connection-table)))
	     (setf (connection-item-output-names cloned-connection-stub-item)
		   (connection-item-output-names cloned-block-connection-item))
	     ;; reclaim cloned-block-connection-item
	     (reclaim-connection-item cloned-block-connection-item)
	     ;; mark the connection item as duplicated (input + output)
	     (assert-for-development
	       (not (connection-item-duplicated? cloned-connection-stub-item)))
	     (setf (connection-item-duplicated? cloned-connection-stub-item) t)))
	  (t
	   ;; b) in normal case, re-use the cloned-block-connection-item structure
	   ;; with valid port names.
	   (setf (connection-item-connection cloned-block-connection-item)
		 cloned-connection-stub)
	   (setf (get-connection-item cloned-connection-stub
				      cloned-block-connection-table)
		 cloned-block-connection-item))))

  ;; 3. delete `cloned-block-connection' with its loose-end, preserving the other end
  (delete-connection cloned-block-connection
		     nil ; remove-subworkspace-connection-posts-if-appropriate?
		     cloned-block) ; preserved-loose-end?

  ;; 4. copy delta-or-deltas from the original connection
  (setf (delta-or-deltas cloned-connection-stub)
	(copy-list-using-connection-conses
	  (delta-or-deltas connection)))

  ;; 5. delete left loose ends.
  (let ((output-loose-end
	  (output-end-object cloned-connection-stub))
	(input-loose-end
	  (input-end-object cloned-connection-stub)))
    (cond
      ;; NOTE: see comments in the #-connections-v2 version.
      ((eq output-loose-end cloned-block-at-other-end)
       (delete-connection-in-block
	 input-loose-end cloned-connection-stub nil)
       (delete-frame input-loose-end)  ; delete loose end
       (setf (input-end-object cloned-connection-stub)
	     cloned-block))
      ;; NOTE: actually it never reaches here.
      ((eq input-loose-end cloned-block-at-other-end)
       (delete-connection-in-block
	 output-loose-end cloned-connection-stub nil)
       (delete-frame output-loose-end) ; delete loose end
       (setf (output-end-object cloned-connection-stub)
	     cloned-block))
      (t
       #+development
       (error "impossible case")))

    ;; 6. copy input/output end positions from original connection (useless)
    (setf (input-end-position cloned-connection-stub)
	  (input-end-position connection))
    (setf (output-end-position cloned-connection-stub)
	  (output-end-position connection))
    ;; 7. determine subworkspace CPs
    (determine-subworkspace-connection-posts-for-object
      cloned-connection-stub (output-end-object cloned-connection-stub))
    ;;
    ;; GENSYMCID-1779: GDA propagation of values issue
    ;;
    ;; Previously, input-end subworkspace connection ports were detected in
    ;; `clone-connections-slot', but the connections holding the information
    ;; will be later deleted in current function, resulting into the issue.
    ;; A better and symmetric solution is to move the detection here, together
    ;; with output-end subworkspace connection posts detection.
    ;;
    ;; -- Chun Tian (binghe), Jun 2016.
    (determine-subworkspace-connection-posts-for-object
      cloned-connection-stub (input-end-object cloned-connection-stub))))

;;;; Subworkspace Connection Posts

;;; Subworkspace connection posts are an extension of the connection posts
;;; facility.  If the superior-connection slot of a connection post which is on a
;;; subworkspace of some item designates a connection of that item, the connection
;;; post is considered a subworkspace connection post for that connection.  The
;;; connection post is considered "connected" to the connection in the sense that
;;; the connection role servers will serve the connection post from the connection
;;; and vice-versa.  This allows for graphically building sub-assemblies of items
;;; on their subworkspaces which, when cloned, continue to observe the intended
;;; connectivity.

;;; Pointers are set up between connection posts and superior connections at
;;; installation time to facilitate role service.  The pointers are kept in the
;;; superior-connection-cache slot of connection posts and in the
;;; connection-attributes-plist of connections.  The
;;; search-for-directly-connected-entities mechanism in role uses
;;; search-for-subworkspace-connection-posts and connection-post-search-2 which
;;; utililize these pointers.

;;; Handle-connection-post-addition-or-removal-as-subblock is called by
;;; install-connection-posts-after-loading-1, transfer-block-with-no-connections,
;;; and transfer-grouped-blocks-with-their-external-connections to update the
;;; pointers when a connection post is loaded in or transferred.  Thus,
;;; handle-connection-post-addition-or-removal-as-subblock begins with a
;;; connection post and sets up pointers to corresponding connections.

;;; Determine-subworkspace-connection-posts is called by add-stub,
;;; replace-connection-in-block, and add-connection-in-block to update pointers
;;; when a connection is added to a block.  It is also called by
;;; clone-connections-slot, and make-cloned-connection-stub-be-copy-of-connection
;;; to update the pointers when the connections are cloned.  It is also called by
;;; change-portname-given-stub-designation, and move-stub-given-stub-designation
;;; when connection positions and portnames are changed via the change option in
;;; class definitions.  Finally, it is called by add-subworkspace when a
;;; subworkspace is added to a block.  Thus,
;;; determine-subworkspace-connection-posts begins with connections and sets up
;;; pointers to corresponding connection posts.

;;; Flush-subworkspace-connection-posts-for-object removes the pointers set up by
;;; determine-subworkspace-connection-posts.  It is called by
;;; replace-connection-in-block, delete-connection-in-block,
;;; reclaim-connection-and-delta-or-deltas,
;;; change-portname-given-stub-designation, and move-stub-given-stub-designation.

;;; Add-subworkspace-connection-post-to-connection and
;;; remove-subworkspace-connection-post-from-connection are primitives called by
;;; the above functions for establishing or removing the pointers.



(declare-forward-reference get-connection-given-stub-designation function)

(def-slot-putter superior-connection 
		 (connection-post superior-connection-designation initializing?)
  (if loading-kb-p
      (setf (superior-connection connection-post) superior-connection-designation)
      (let* ((old-translation?
	       (unless 
		 initializing?
		 (superior-connection connection-post)))
	     (superblock? (superblock? connection-post))
	     (superior-block?
	       (when (and superblock?
			  (kb-workspace-p superblock?))
		 (parent-of-subworkspace? superblock?)))
	     (old-designated-connection? 
	       (when superior-block?
		 (get-connection-given-stub-designation 
		   superior-block? old-translation?)))
	     (new-designated-connection? 
	       (when superior-block?
		 (get-connection-given-stub-designation 
		   superior-block? superior-connection-designation))))
	(when old-designated-connection?
	  (remove-subworkspace-connection-post-from-connection
	    old-designated-connection? connection-post
	    (eq (input-end-object old-designated-connection?) superior-block?)
	    nil))
	(setf (superior-connection connection-post) superior-connection-designation)
	(when new-designated-connection?
	  (add-subworkspace-connection-post-to-connection
	    new-designated-connection? connection-post
	    (eq (input-end-object new-designated-connection?) superior-block?)))
	superior-connection-designation)))

;; Post loading function takes care of installation for loading-kb case.  Slot
;; putter can't be used when loading since connections may not have been read yet.



(defun handle-connection-post-addition-or-removal-as-subblock (item removal?)
  (when (connection-post-p item)
    (handle-connection-post-addition-or-removal-as-subblock-1 item removal?)))

(defun handle-connection-post-addition-or-removal-as-subblock-1 
       (connection-post removal?)
  (let* ((superior-connection-designation
	   (superior-connection connection-post))
	 (superblock? (superblock? connection-post))
	 (superior-block?
	   (when (and superblock?
		      (kb-workspace-p superblock?))
	     (parent-of-subworkspace? superblock?)))
	 (designated-connection? 
	   (when superior-block?
	     (get-connection-given-stub-designation 
	       superior-block? superior-connection-designation))))
    (when designated-connection?
      (if removal?
	  (cond ((eq (input-end-object designated-connection?) 
		     (output-end-object designated-connection?))
		 ;; This checks for the case of a circular connection.
		 ;; In this case we have to remove at both the input-end 
		 ;; and the output-end in this same call.
		 ;; (flush-subworkspace-connection-posts connection nil ...)
		 ;; below is also sort of precedence for this. - jpg 12/28/00
		 (remove-subworkspace-connection-post-from-connection
		   designated-connection? connection-post t nil)
		 (remove-subworkspace-connection-post-from-connection
		   designated-connection? connection-post nil nil))
		(t
		 (remove-subworkspace-connection-post-from-connection
		   designated-connection? connection-post
		   (eq (input-end-object designated-connection?) superior-block?)
		   nil)))
	  (add-subworkspace-connection-post-to-connection
	    designated-connection? connection-post
	    (eq (input-end-object designated-connection?) superior-block?))))))



(defun determine-subworkspace-connection-posts (object)
  (loop for connection being each connection of object
	do (determine-subworkspace-connection-posts-for-object
	     connection object)))

(defun determine-subworkspace-connection-posts-for-object (connection object)
  (when (of-class-p object 'object)
    (loop for subworkspace in (subworkspaces object)
	  do
      (loop for block being each subblock of subworkspace
	    do
	(when (and (connection-post-p block)
		   (eq (get-connection-given-stub-designation 
			 object 
			 (superior-connection block))
		       connection))
	  (add-subworkspace-connection-post-to-connection
	    connection block
	    (eq (input-end-object connection) object)))))))

(defun flush-all-subworkspace-connection-posts-for-object
       (object delete-dangling-connection-posts?)
  (loop for connection being each connection of object
	do (flush-subworkspace-connection-posts-for-object
	     connection object delete-dangling-connection-posts?)))

(defun flush-subworkspace-connection-posts-for-object
       (connection object delete-dangling-connection-posts?)
  (if (eq (input-end-object connection) object)
      (flush-subworkspace-connection-posts connection 'input delete-dangling-connection-posts?)
      (flush-subworkspace-connection-posts connection 'output delete-dangling-connection-posts?)))

(defun flush-subworkspace-connection-posts
       (connection input-or-output? delete-dangling-connection-posts?)
  (cond
    ((eq input-or-output? 'input)
     (flush-subworkspace-connection-post-set
       connection
       (getfq (connection-attributes-plist connection) 
	      'input-end-subworkspace-connection-posts)
       t
       delete-dangling-connection-posts?))
    ((eq input-or-output? 'output)
     (flush-subworkspace-connection-post-set
       connection
       (getfq (connection-attributes-plist connection) 
	      'output-end-subworkspace-connection-posts)
       nil
       delete-dangling-connection-posts?))
    (t
     (flush-subworkspace-connection-post-set
       connection
       (getfq (connection-attributes-plist connection) 
	      'input-end-subworkspace-connection-posts)
       t
       delete-dangling-connection-posts?)
     (flush-subworkspace-connection-post-set
       connection
       (getfq (connection-attributes-plist connection) 
	      'output-end-subworkspace-connection-posts)
       nil
       delete-dangling-connection-posts?))))

(defun flush-subworkspace-connection-post-set 
       (connection connection-post-set input-end? delete-dangling-connection-posts?)
  (let ((copy-of-connection-post-set
	  (copy-list-using-slot-value-conses connection-post-set)))
    (loop for connection-post in copy-of-connection-post-set
	  do (remove-subworkspace-connection-post-from-connection
	       connection connection-post input-end? delete-dangling-connection-posts?))
    (reclaim-slot-value-list copy-of-connection-post-set)))



(defun add-subworkspace-connection-post-to-connection 
       (connection connection-post input-end?)
  (decache-roles-for-connection-post connection-post)
  (add-or-delete-subworkspace-connection-post-from-connection
    connection connection-post input-end? nil nil))

(defun remove-subworkspace-connection-post-from-connection 
       (connection connection-post input-end? delete-dangling-connection-posts?)
  (decache-roles-for-connection-post connection-post)
  (add-or-delete-subworkspace-connection-post-from-connection
    connection connection-post input-end? t delete-dangling-connection-posts?))

(defun delete-subworkspace-connection-post-if-superfluous (connection-post)
  (when (and (superior-connection connection-post)
	     (null (superior-connection-cache connection-post))
	     (null (connections connection-post)))
    (delete-frame connection-post)))

(defun add-or-delete-subworkspace-connection-post-from-connection 
    (connection connection-post input-end? delete-instead? delete-dangling-connection-posts?)
  (decache-roles-for-entities-related-to-this-connection connection)
  (cond
    (input-end?
     (change-connection-attribute
       connection 'input-end-subworkspace-connection-posts
       (add-or-delete-subworkspace-connection-post
	 (copy-list-using-slot-value-conses
	   (getfq (connection-attributes-plist connection) 
		  'input-end-subworkspace-connection-posts))
	 connection-post delete-instead?))
     (change-connection-post-connection-cache
       connection-post connection input-end? delete-instead?))
    (t
     (change-connection-attribute
       connection 'output-end-subworkspace-connection-posts
       (add-or-delete-subworkspace-connection-post
	 (copy-list-using-slot-value-conses
	   (getfq (connection-attributes-plist connection) 
		  'output-end-subworkspace-connection-posts))
	 connection-post delete-instead?))
     (change-connection-post-connection-cache
       connection-post connection input-end? delete-instead?)))
  (when (and delete-instead? delete-dangling-connection-posts?)
    (delete-subworkspace-connection-post-if-superfluous connection-post)))

(defun change-connection-post-connection-cache
       (connection-post connection input-end? delete-instead?)
  (change-slot-value
    connection-post 'superior-connection-cache
    (if delete-instead? 
	nil
	(slot-value-cons
	  (if input-end? 'input 'output)
	  connection))))


(defconstant savable-connection-attributes '(connection-style line-pattern connection-arrows))

(defmacro savable-connection-attribute-p (name)
  (avoiding-variable-capture (name)
    `(or ,@(loop for attr in savable-connection-attributes
		 collect `(eq ,name ',attr)))))

(defun get-savable-connection-attributes-plist (connection-attributes-plist)
  (loop for attribute in savable-connection-attributes
	as value? = (getfq connection-attributes-plist attribute)
	when value?
	  collect attribute using slot-value-cons and
	  collect value? using slot-value-cons))

;; The subworkspace connection attributes are not saved, but rather, are rederived
;; by installation functions.



;;;; Subworkspace Connection Post Capability

;;; Add-subworkspace-connection-posts is called by
;;; go-to-maybe-newly-created-subworkspace when a subworkspace is made for an
;;; object with subworkspace-connection-posts capability.

(defun add-subworkspace-connection-posts (subworkspace object)
  #-connections-v2
  (loop with port-name? = nil
	for port-name-or-connection in (connections object)
	do
    (cond
      ((symbolp port-name-or-connection)
       (when (null port-name?)
	 (setq port-name? port-name-or-connection)))
      (t
       (add-subworkspace-connection-post
	 port-name-or-connection port-name? object subworkspace)
       (setq port-name? nil))))
  #+connections-v2
  (loop with connection-table = (connections object)
	for connection being each connection of object
	for connection-item = (get-connection-item connection connection-table)
	for port-name? = (car (or (connection-item-output-names connection-item)
				  (connection-item-input-names connection-item)))
	do
    (add-subworkspace-connection-post
      connection port-name? object subworkspace)))

(defun add-subworkspace-connection-post (connection port-name? object subworkspace)
  (let* ((original-end-position
	   (if (eq (input-end-object connection) object)
	       (input-end-position connection)
	       (output-end-position connection)))
	 (original-end-position-on-side
	   (get-position-on-side-given-end-position
	     original-end-position))
	 (new-side
	   (get-side-given-end-position original-end-position))
	 (connection-post-position-on-side
	   (scale-subworkspace-connection-post-position
	     subworkspace object
	     original-end-position-on-side
	     new-side))
	 (new-connection-post (make-entity 'connection-post))
	 connection-post-x connection-post-y)
    (multiple-value-setq
      (connection-post-x connection-post-y)
      (connection-post-x-and-y-given-position-and-side
	new-side connection-post-position-on-side subworkspace))
    (let ((disable-stack-error t))
      (transfer-blocks-with-their-external-connections
       new-connection-post subworkspace 
       (-w connection-post-x
	   (halfw (width-of-block subworkspace)))
       (-w (halfw (height-of-block subworkspace))
	   connection-post-y)
       nil))
    (change-slot-value
      new-connection-post 'superior-connection
      (or port-name?
	  (slot-value-list new-side original-end-position-on-side)))))

(defun scale-subworkspace-connection-post-position
       (subworkspace object position-on-object side)
  (with-temporary-gensym-float-creation scale-subworkspace-position
    (round
      (case side
	((left right)
	 (/e (*e (coerce-to-gensym-float position-on-object)
		 (coerce-to-gensym-float
		   (height-of-block subworkspace)))
	     (coerce-to-gensym-float (height-of-block object))))
	(t
	 (/e (*e (coerce-to-gensym-float position-on-object)
		 (coerce-to-gensym-float
		   (width-of-block subworkspace)))
	     (coerce-to-gensym-float (width-of-block object))))))))



(defparameter connection-post-indentation 10)

;; The indentation is currently fixed.  This assumes that the subworkspace created
;; (via go-to-maybe-newly-created-subworkspace) will be large enough to accomodate
;; the indentation.



(defun connection-post-x-and-y-given-position-and-side 
       (side position-on-side subworkspace)
  (let (x y)
    (case side
      (left
       (setq x connection-post-indentation
	     y position-on-side))
      (top
       (setq y connection-post-indentation
	     x position-on-side))
      (right
       (setq x (-w (width-of-block subworkspace) connection-post-indentation)
	     y position-on-side))
      (bottom
       (setq y (-w (height-of-block subworkspace) connection-post-indentation)
	     x position-on-side)))
    (values x y)))





;;;; To Do

;; Make player to test subworkspace connection posts (see below).

;; Allow user to specify kind of subworkspace connection post for class.  Have
;; def-capability automatically include an attribute, and have this attribute
;; defaulted in the object definition.

;; Fix clone bug for tables.

;; When subworkspace connections posts are created, they are not in a straight
;; line.

;; Search-for-subworkspace-connection-posts has no way to return the connection
;; post itself.  This causes designations of connection posts connected on
;; subworkspaces to fail.  I thought I had checks for this.

;; Decache-roles-for-entities-related-to-this-connection should be done by
;; flush and remove functions.



;;;; Testing

;; Test kbs include (in ma:>agh>) connection-post-test.kb, and generator8.kb.
;; Connection-post-test.kb has player stuff in it.


;; To test installation of subworkspace connection posts, monitor the
;; superior-connection-cache slot of a connection post and the
;; connection-attributes-plist of the corresponding connection while doing the
;; following.  In the case of automated testing with the player, rather than
;; monitoring these caches, monitor role service.

;; 1.  Put connection post on subworkspace and edit superior connection slot to
;;     designate superior connection.  Test with changing to none as well.
;;     Designate by portname, and also by location.

;; 2.  Test transferring connection post to and from subworkspace.

;; 3.  Test deleting connection post.

;; 4.  Test adding and breaking connections to superior object.
;;     Join and break connections.  Join dragging either end.
;;     Drag connection into other connection, drag other
;;     connection into it to make junction block.
;;     Test deleting connection by dragging it all the way in
;;     to the object.

;; 5.  Test adding connection via change facility in object definition
;;     (add to object that has subworkspace connection posts which 
;;     designate the connection).  

;; 6.  Test adding transient connection (to object with subworkspace
;;     connection post which designates the connection).

;; 7.  Test cloning an object with connections and corresponding
;;     subworkspace connection posts.

;; 8.  Clone connection post and put on workspace where it does not designate
;;     a connection.  Repeat but putting on workspace where it does
;;     designate a connection.

;; 9.  Test changing portname and location of connections designated
;;     by subworkspace connection posts.

;; 10.  Test cloning an object with several layers of subworkspaces and
;;      subworkspace connection posts (such as a generator in generator8.kb).

;; 11.  Test adding (dragging in a new) connection to object with subworkspace
;;      connection post capability to test automatic creation of subworkspace
;;      connection post.

;; Note that installation of subworkspace connection posts can be tested
;; completely separately from role service (except for role decaching).  Actually,
;; this is not true when doing the testing automatically via the player.


