
;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")

;;;; Module SYSTEMS

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Mark H. David, Jim Allard, and Ong, Peng Tsin


;;;; Master Module Enumeration

#-translator
(eval-when (:compile-toplevel :load-toplevel :execute)
  (pushnew :java-export-facilities *features*)
  #+development ; TODO: why it's development only?
  (pushnew :clear-text *features*)
  ;; re-worked UC14 (hashed relation instances)
  (pushnew :relation-instances-v2 *features*)
  (pushnew :relation-instances-v2.1 *features*) ; can switch to 2.0
  (pushnew :connections-v2 *features*)
  (pushnew :subblocks-v2 *features*) ; in DRAW and FRAMES3
  #+SymScale
  (pushnew :skip-list *features*)
  #+SymScale
  (pushnew :Lockfree-Deque *features*)
  #+SymScale
  (pushnew :Lockfree-List *features*))

;; What's :java-export-facilities? See the def-feature in FEATURES for info on
;; why this is here!  (MHD 3/6/03)

;;; `Def-all-system-modules' provides the full set of modules in their canonical
;;; ordering.  No system can include modules not enumerated in this list.  No
;;; system can order modules in a manner inconsistent with this list.  No module
;;; can configure it's module in a manner inconsistent with the alist given
;;; here.

(def-all-system-modules
  (|123|)                        ; A tool for loading and translating Lisp systems.
  (load)
  (bootstrap)
  (systems)
  (portable-threads)
  (delta)
  (features) ; g2-config need it. -- Chun Tian (binghe), 2010/8/13
  (g2-config)
  (g2-patches)
  (tw-patches)
  (gsi-patches)
  ;;(gsi-user)                                ; Lisp notes on how to make bridges, but not part of GSI per se
  ;;(gsi-leak)                                ; Lisp GSI leak tools, but not part of GSI per se
  (ctest-patches)
  (loop)
  (glbasics)
  (gldebug)
  (lisp-server)

  (numbers)   ; LS only -- binghe, 2010/8/27
  (integrals) ; LS only -- binghe, 2010/8/27
  (license)
  (os-foreign)
  (basics)
  (os-time)
  (os-settings)
  (os-memory)
  (primitives)                                ; primitives/characters order swapped -- characters
  (characters)                                ; needs character-case macro (MHD 3/13/95)
  (jismap)                                ; JIS X 0208 / Unicode Mappings
  (ksmap2)                                ; KS C 5601 / Unicode Mappings (Unicode 2.0)
  (gbmap)                                ; GB 2312-80 / Unicode Mappings
  (gbmapr)                                ; -- reverse mappings broken out in sep. mod.

  (characters2)
  
  (keyboards)
  (keydefs)
  (utilities0)
  
  (utilities1)
  (utilities2)
  (letters)
  (unicode)
  
  (iso2022)
  (transcode)
  (iso8859)
  (alphabet)
  (token)
  (utilities3)
  (utilities4)
  (test-framework)
  (times)
  (f-keys)
  (os-error)
  (platforms)
  (launch)
  (pathnames)
  (file-parse)
  (streams)
  (postscript)
  (schedule)
  (clocks)
  (networks)
  (ctest)
  (int0)
  (int1)
  (neterror)
  (netevent)
  (int2)
  (int3a)
  (int3b)
  (int4)
  (gsi-common)
  (windows1)
  (windows2)
  (windows3)
  (windows3a)
  (windows4)
  (images)
  (mice)
  (fonts)
  (icons)
  (hb72)
  (hm14)
  (hm18)
  (hm24)
  (slavic14)
  (slavic18)
  (slavic24)
  (hebrew14)
  (hebrew18)
  (hebrew24)
  (thai14)
  (thai18)
  (thai24)
  (site)
  (doc)
  (parse)
  (parse2)
  (frames1)
  (types)
  (frames2)
  (slots)
  (frames2a)
  (frames2b)
  (frames3)
  (frames4)
  (frames5)
  (panes)
  (draw)
  (entities)
  (places)
  (view-def)
  (modules)
  (debug)
  (ps-header)
  (printing)
  (connect1)
  (connect2)
  (connect3)
  (connect3a)
  (connect4)
  (connect5)
  #+mtg2 (factions)
  (definitions)
  (relations)
  (formats)
  (sequences1)
  (sequences2)
  (sequences3)
  (boxes)
  (language)
  (tables)
  (telestubs)
  (dialogs)
  (native-tw)
  (workstation)
  (books)
  (menus)
  (new-menus)
  (facilities)
  (kfep1)
  (kfep2)
  (kfep3)
  (hfep1)
  (hfep2)
  (edit1)
  (edit2)
  (rings)
  (moves)
  (run)
  (kb-merge)
  (kb-load1)
  (kb-load2)
  (kb-save1)
  (kb-save2)
  (kb-save3)
  (kb-save4)
  (warmboot)
  (font-files)
  (telewindows)
  (check-kbs)

  (comp-utils)
  (compile1)
  (compile2)
  (sets)
  (lists)
  (arrays)
  (hash-tables)
  (priority-queues)
  (variables)
  (histories)
  (roles)
  (eval)
  (rules)
  (new-rules)
  (chaining)
  (functions)
  (cells)
  (proc-gram)
  (rpc-common1)
  (rpc-common2)
  (rpc-common3)
  (gsi)
  (gsi-rpc1)
  (gsi-rpc2)

  (proc-utils)
  (proc-comp)
  (proc-debug)

  (change-log)
  (file-sysproc)
  (mem-sysproc)
  (g2-rpc1)
  (g2-rpc2)
  (g2-rpc3)
  (explain)
  (parts)
  (displays)
  (graphs1)
  (graphs2)
  (graph-util)
  (graph-def)
  (graphs)
  (charts1)
  (new-tables)
  (install)
  (filters)
  (activate)
  (attr-export)
  (cycles)
  (simulate1)
  (simulate2)
  (simulate3)
  (simulate5)
  (lexer)
  (sax)
  (dom)
  (conclude)
  (grammar0)
  (grammar1)
  (grammar1a)
  (grammar2)
  (grammar3)
  (grammar4)
  (grammar4a)
  (grammar5)
  (grammar6a)
  (grammar6b)
  (grammar6c)
  (grammar7)
  (stack-utils)
  (stack-inst)
  (stack-comp)
  (stack-eval1)
  (stack-eval2)
  (stack-acts)
  (stack-kern)
  #+mtg2 (thread-pond)
  (proc-inst)
  (proc-inst2)
  (queries)
  (g2-foreign)
  (gfi-stubs)
  (attributes)
  (gfi)
  (g2-gsi)
  (gspan)
  (g2ds)
  (g2ds-nupec)
  (views)
  (controls)
  (commands0)
  (commands1)
  (commands2)
  (view-msg1)
  (view-g2)
  (media)
  (traversals)
  (teleserver)
  (icons1)
  (icons2)
  (icons3)
  (icons4)
  (icons5)

  (interop) ; [tam.srogatch][2010-10-26]: DLL interoperability
  (continentalextension) ;[tam.mokaddims][2nd January 2011]: added to test new kb extension
  (smartsignalextension)
  (mqttclient)
  (socket1)
  (socket2)
  (web-services)
  (g2-bpel)

  (player)
  (rg-report)
  (g2-meters)

  ;; WebLink stuff
  (gwutil-1)
  (buffer)
  (gthread)
  (htmlgen)
  (bridge)
  (web)
  (server)   ;; too generically named; refers only to WebLink
  (web-gsi)

  ;; V5 stuff - not well sorted out yet
  (resources)
  #+res-g2-facilities
  (res-g2)
  (events)       ;; temporary measure to use boot-module 12/30/95 - Que?
  (events-g2)
  #+java-export-facilities
  (java1)
  #+java-export-facilities
  (java2)
  #+java-export-facilities
  (java3)
  (sysicons)
  (checkmemory)  ;; There are inconsistencies in how this is included!!!
  (translate)
  (test-eq-hash-table)
  #+mtg2 (test-thread-pond)
  #+mtg2 (test-factions)
  (g2-final))



;;;; Telewindows



;;; The Telewindows system at present consists of an initial subsequence of the
;;; G2 system modules.

(declare-system (telewindows

                  products-uninterested-in-this-system (gsi)

                  alias
                     tw

                  nicknames
                     (tw)

                  systems-to-share-binary-files-with
                     (AB Gensym-Site)

                  #-no-macros
                  boot-files
                     #-no-macros
                     ((123 :local-file-type
                           #.(bootstrap-information-lisp-source-file-type)
                           :master-file-type #.master-lisp-source-file-type
                           :updates-file-type-symbol lisp))

                  #-no-macros
                  system-lisp-binary-files
                     #-no-macros
                     (
                      )

                  system-c-files                ; needed in dst for loading
                     ((twmain :overriding-include-test (or chestnut chestnut-3) ;Chestnut3.1 - was :chestnut
                              :local-directory-namestring
                              ;; This introduces a spurious diff when we translate in
                              ;; different sandboxes.  Can we get rid of it?  - jv, 11/15/99
                              "system-c-local-directory-namestring"))


                  #-no-macros
                  distribution-c-files
                     #-no-macros
                     ()

                  #-no-macros
                  h-files
                     #-no-macros
                     (
                      )

                  #-no-macros
                  text-files
                     #-no-macros
                     (
                      (original-tw :default-file-type "ok")
                      (tw :default-file-type "ok")
                      (tw-chestnut :default-file-type "ok"
                                   :local-pathname-name "gensym-tw"
                                   :master-pathname-name "tw"
                                   :overriding-include-test (or chestnut chestnut-3) ;Chestnut3.1 - was :chestnut
                                   :local-directory-namestring
                                   #.(get 'ab::telewindows 'local-chestnut-dst-misc-directory))
                      (twjapanese-chestnut :default-file-type "ok"
                                   :local-pathname-name "gensym-twj"
                                   :master-pathname-name "twj"
                                   :overriding-include-test (or chestnut chestnut-3) ;Chestnut3.1 - was :chestnut
                                   :local-directory-namestring
                                   #.(get 'ab::telewindows 'local-chestnut-dst-misc-directory))
                      (original-tw-chestnut :default-file-type "ok"
                                   :local-pathname-name "tw"
                                   :master-pathname-name "original-tw"
                                   :overriding-include-test (or chestnut chestnut-3) ;Chestnut3.1 - was :chestnut
                                   :local-directory-namestring
                                   #.(get 'ab::telewindows 'local-chestnut-dst-misc-directory)))

                  #-no-macros
                  kb-files
                     #-no-macros
                     ()

                  #-no-macros
                  kl-files
                     #-no-macros
                     ())

  #-no-macros
  (load :include-test-for-load nil)
  (bootstrap :include-test-for-load (not :do-not-load-bootstrap)
             :lisp-compile-function compile-bootstrap-and-reboot-all-modules
             :lisp-update-function update-bootstrap-and-reupdate-all-modules)
  systems
  delta

  (features :overriding-include-test development)  
  g2-config
  tw-patches
  loop                                                ; Load this first to set *features*
  glbasics
  (gldebug :overriding-include-test development)            ; Low-level debugging for G2 and TW.
  os-foreign
  basics                                        ; uses csleep.c, cprimitives.c
  os-time                                       ;extracted from BASICS (jh, 2/2/92)
  os-settings                                   ;extracted from BASICS (jh, 2/2/92)
  os-memory                                     ;extracted from BASICS (jh, 2/2/92)
  primitives                                        ; uses g2pointers.c
  characters
  jismap
  ksmap2
  gbmap
  gbmapr
  characters2
  
  keyboards                                        ; Requires def-global-property in primitives.
  keydefs
  utilities0
  utilities1
  utilities2
  letters
  unicode
  iso2022
  transcode
  iso8859
  utilities3
  times
  f-keys
  os-error
  platforms
  launch                                        ; split from platforms by paf! 9jan94
  pathnames
  file-parse
  streams

  schedule
  clocks

  networks

  int0          ;; jh, 12/29/94.
  int1
  neterror
  netevent
  int2
  int3a
  int3b
  int4

  windows1
  windows2
  windows3
  windows3a
  windows4
  images                                                    ; Bitmaps and Pixmaps. -fmw, 12/21/93


  fonts
  ;; pbk removed icons from Telewindows (4/19/96)
  ;; The following fonts are licenced by Gensym from Adobe Systems, Inc.
  HB72
  HM14
  HM18
  HM24
  SLAVIC14
  SLAVIC18
  SLAVIC24
  HEBREW14
  HEBREW18
  HEBREW24
  THAI14
  THAI18
  THAI24

  sequences1
  telestubs
  dialogs
  native-tw
  rings
  font-files                                        ; (MHD 4/11/91)

  telewindows
  (checkmemory :overriding-include-test development)
  translate
  )







;;;; GSI Extension in Lisp

;; old notes (circa 1989).

;;; The system `gsi' (formerly `gsi-extension' alias gsix) is for GSI extension
;;; code written in Lisp.  This will be the GSI external server for the Lisp
;;; machines, and could optionally be used as a portable implementation for
;;; other architectures as well (someday).

;;; Note that if we are #+gsi-web, "gsi" is actually WebLink.

(declare-system (gsi
                  #+gsi-web alias #+gsi-web gw
                  system-is-windowless-p t)
  #-no-macros
  (load :include-test-for-load nil)
  (bootstrap :include-test-for-load (not :do-not-load-bootstrap)
             :lisp-compile-function compile-bootstrap-and-reboot-all-modules
             :lisp-update-function update-bootstrap-and-reupdate-all-modules)
  systems
  delta

  (features :overriding-include-test development)
  g2-config
  gsi-patches
  loop                                                ; Load this first to set *features*
  glbasics      ; break into two modules to shrink GSI!!!
  (gldebug :overriding-include-test development)            ; Low-level debugging for G2 and TW.
  os-foreign
  basics                                        ; uses csleep.c, cprimitives.c
  os-time       ; 1 reference: c-native-clock-ticks-per-second
  os-settings
  os-memory     ; break up?
  primitives                                        ; uses g2pointers.c
  characters    ; break up?
  jismap
  ksmap2
  gbmap
  gbmapr
  characters2
  
  utilities0
  utilities1
  utilities2
  letters
  unicode
  iso2022
  transcode
  iso8859
  utilities3
  times
  os-error
  launch      ; a subset of the former platforms which I used to include
  pathnames
  #+gsi-web file-parse
  #+gsi-web streams

  schedule
  clocks

  networks
  int1
  neterror
  netevent
  int2
  int3a
  int3b
  int4
  gsi-common
  rpc-common1
  rpc-common2
  rpc-common3
  gsi
  gsi-rpc1
  gsi-rpc2
  #+gsi-web socket1
  #+gsi-web gwutil-1
  #+gsi-web buffer
  #+gsi-web gthread
  #+gsi-web htmlgen
  #+gsi-web bridge
  #+gsi-web web
  #+gsi-web server
  #+gsi-web web-gsi

  translate)

(set-system-version 'gsi-extension (make-system-version 2 0))
(setf (get 'gsi-extension 'fixed-system-key) #\x)





;;;; WebLink

;;; WebLink does not work at all in the main branch.  For the time being, it is
;;; here simply to justify the existence of WebLink specific Lisp files in the
;;; lisp directory.  (It is possible to check files in *only* on a branch, but
;;; I don't want to do that either, because it is a bit complicated and
;;; confusing, and I hope that some day soon, gw *will* work in the main branch.
;;; So, it's better to let the WebLink files sit in the main branch lisp
;;; directory, as long as they don't get in anyone's way.)  -jv, 4/25/03


(declare-system (gw
                  alias weblink
                  nicknames (weblink)
                  system-is-windowless-p t)
  #-no-macros
  (load :include-test-for-load nil)

  (bootstrap :include-test-for-load (not :do-not-load-bootstrap)
             :lisp-compile-function compile-bootstrap-and-reboot-all-modules
             :lisp-update-function update-bootstrap-and-reupdate-all-modules)

  systems
  delta
  gsi-patches
  loop
  glbasics
  (gldebug :overriding-include-test development)
  os-foreign
  basics
  os-time
  os-settings
  os-memory
  primitives
  characters
  jismap
  ksmap2
  gbmap
  gbmapr
  characters2
  utilities0
  utilities1
  utilities2
  letters
  unicode
  iso2022
  transcode
  iso8859
  utilities3
  times
  os-error
  launch

  pathnames
  file-parse
  streams

  schedule
  clocks

  networks
  int1
  neterror
  netevent
  int2
  int3a
  int3b
  int4
  gsi-common
  rpc-common1
  rpc-common2
  rpc-common3
  gsi
  gsi-rpc1
  gsi-rpc2

  gwutil-1
  buffer
  gthread
  htmlgen
  bridge
  web
  server
  web-gsi

  translate
  )



;;;; Gensym (Development-only Site-specific Tools)

#+development
(declare-system (gensym-site                        ; SITE would be better, but
                                                ;   clashes w/built-in
                  products-uninterested-in-this-system (gsi)

                  systems-to-share-binary-files-with
                    (AB Telewindows))
  #-no-macros
  (load :include-test-for-load nil)

  (bootstrap :include-test-for-load (not :do-not-load-bootstrap)
             :lisp-compile-function compile-bootstrap-and-reboot-all-modules
             :lisp-update-function update-bootstrap-and-reupdate-all-modules)
  systems
  delta

  g2-config
  ctest-patches                                ; it can borrow this file from ctest
  loop                                                ; Load this first to set *features*
  glbasics
  (gldebug :overriding-include-test development)
  os-foreign
  basics                                ; uses csleep.c, cprimitives.c
  os-time
  os-settings
  os-memory
  primitives                                ; uses g2pointers.c
  characters
  characters2
  
  keyboards
  keydefs
  utilities0
  utilities1
  utilities2
  letters
  unicode
  transcode
  utilities3
  times
  f-keys                                                    ; This now needs utilities1.
  os-error
  launch
  pathnames
  schedule
  clocks
  networks

  (site :overriding-include-test development))

;;;; G2

;;; The system `ab' (aka `G2') defines the G2 system.

;; G2-specific code is here follows.
;; Note however that there is a lot of code that need not be included in G2's
;; which are released to customers as world saves!  -pto 21dec88

(declare-system (ab
                  alias g2
                  nicknames (g2)
                  system-is-windowless-p nil
                  products-uninterested-in-this-system (gsi)
                  systems-to-share-binary-files-with (Telewindows Gensym-Site GSI))

  #-no-macros
  (load :include-test-for-load nil)
  (bootstrap :include-test-for-load (not :do-not-load-bootstrap)
             :lisp-compile-function compile-bootstrap-and-reboot-all-modules
             :lisp-update-function update-bootstrap-and-reupdate-all-modules)
  systems
  #+(and (or SymScale mtg2) (not chestnut-3))
  portable-threads
  delta
  
  (features :overriding-include-test development)  
  g2-config
  g2-patches

  loop                                                ; Load this first to set *features*
  glbasics
  (gldebug :overriding-include-test development)            ; Low-level debugging for G2 and TW.
  (lisp-server :overriding-include-test development)

  os-foreign
  basics
  os-time
  os-settings
  os-memory
  primitives                                        ; uses g2pointers.c
  characters
  jismap
  ksmap2
  gbmap
  gbmapr

  characters2

  keyboards
  keydefs

  utilities0
  
  utilities1
  utilities2

  letters
  unicode

  iso2022
  transcode
  iso8859

  alphabet
  token

  utilities3
  utilities4                                        ; G2 only, not Telewindows, etc.
  test-framework

  times

  f-keys                                                    ; Key codes. Needs utilities.

  os-error

  platforms      ;; platform windows, local events, workstations, system process, etc.
  launch         ;; process launching - split from platforms 9jan94 paf!
  pathnames
  file-parse
  streams
  postscript     ;; the "SExpr" to postscript translator

  schedule
  clocks

  networks      ;; C interfaces for Networking

  int0          ;; jh, 12/29/94.
  int1          ;; ICP implementation

  neterror
  netevent                                ; new event-based machinery for G2 5.0

  int2
  int3a
  int3b
  int4

  gsi-common
  windows1
  windows2
  windows3
  windows3a
  windows4
  images         ; Bitmaps and Pixmaps. -fmw, 12/21/93

  mice           ;; mouse pointers, spots, and workstation contexts, etc.

  fonts
  icons  ; icon rendering

  ;; The following fonts are licenced by Gensym from Adobe Systems, Inc.
  HB72
  HM14
  HM18
  HM24
  SLAVIC14
  SLAVIC18
  SLAVIC24
  HEBREW14
  HEBREW18
  HEBREW24
  THAI14
  THAI18
  THAI24

  ;; next two for development site only
  (site :overriding-include-test :development
        :optional-module-p t)
  (doc :overriding-include-test :development
       :optional-module-p t)

  parse
  parse2

  frames1
  types
  frames2
  slots
  frames2a
  frames2b
  frames3
  frames4
  frames5

  panes
  draw

  entities
  places
  view-def
  modules


  debug                                                            ; Put before printing.

  ps-header                                                    ; The postscript header for printing
  printing

  connect1
  connect2
  connect3
  connect3a
  connect4
  connect5

  #+mtg2 factions
  
  definitions
  relations

  formats
  sequences1
  sequences2
  sequences3
  boxes
  language
  tables

  telestubs
  dialogs
  native-tw
  workstation

  books
  menus
  new-menus                                        ; UI command facility.  -fmw, 11/4/93
  facilities

  kfep1        ;; KFEP - Kanji Front End Processor
  kfep2
  kfep3

  hfep1        ;; HFEP - Hangul FEP
  hfep2

  edit1
  edit2

  rings
  moves
  run

  kb-merge
  kb-load1
  kb-load2
  kb-save1
  kb-save2
  kb-save3
  kb-save4
  warmboot

  font-files

  (check-kbs :overriding-include-test (not no-macros))

  comp-utils
  compile1
  compile2
  sets
  lists
  arrays
  hash-tables
  priority-queues
  variables
  histories
  roles
  eval
  rules
  new-rules
  chaining
  functions
  cells

  proc-gram
  rpc-common1
  rpc-common2
  rpc-common3
  proc-utils
  proc-comp
  proc-debug

  change-log

  file-sysproc ;was part of FILE-IO (jh, 10/19/93)
  mem-sysproc  ;was part of FILE-IO (jh, 10/19/93)

  g2-rpc1
  g2-rpc2
  g2-rpc3

  explain
  parts
  displays
  graphs1
  graphs2
  graph-util
  graph-def
  graphs
  charts1
  new-tables

  install
  filters
  activate

  attr-export

  cycles

  simulate1
  simulate2
  simulate3
  simulate5

  lexer
  sax
  dom

  conclude
                
  grammar0
  grammar1
  grammar1a
  grammar2
  grammar3
  grammar4
  grammar4a
  grammar5
  grammar6a
  grammar6b
  grammar6c
  grammar7

  stack-utils
  stack-inst
  stack-comp
  stack-eval1
  stack-eval2
  stack-acts
  stack-kern

  #+mtg2 thread-pond
  
  proc-inst
  proc-inst2
  queries

  g2-foreign                                    ;changed name from FOREIGN (jh, 2/2/92)

  GFI-stubs

  attributes                                        ; added. maybe could be moved
                                                ;   earlier. (MHD/CPM 5/5/89)
  (GFI :optional-module-p t)
  (G2-GSI :optional-module-p t)
  (GSPAN :optional-module-p t)

  g2ds
  g2ds-nupec                                    ;split from G2ds (jh, 2/27/92)

  views                                                ; Views and Views API
  controls                                        ; move to a better position!!
                                                ;   (MHD 9/22/88)
  commands0                                        ; UI command support functions, ptype, and menus.
  commands1                                        ; UI commands, part 1.
  commands2                                        ; UI commands, part 2. -fmw, 12/7/93
  view-msg1
  view-g2
  media

  traversals

  teleserver                                        ; add-on telewindows server
                                                ;   functionality

  icons1
  icons2
  icons3
  icons4
  icons5
 
  interop       ;; [tam.srogatch][2010-10-26]: DLL interoperability
  continentalextension 		;;[tam.mokaddims][2nd January 2011]: added to test new kb extensi
  smartsignalextension
  mqttclient
  
  socket1
  socket2
  web-services
  g2-bpel

  player                 ; Keyboard macros and automated testing.
  (rg-report             ; Summary report generator for regression testing logs.
   :overriding-include-test :development)


  g2-meters                                ; g2-meters must be last for
                                        ;   object pool meters to work.
                                        ;   -jra 9/27/88



  resources
  #+res-g2-facilities
  res-g2
  events       ;; temporary measure to use boot-module 12/30/95 - Que?

  events-g2

  #+java-export-facilities
  java1
  #+java-export-facilities
  java2
  #+java-export-facilities
  java3


  sysicons                                ; dwr's new module (tried system-icons, but
                                        ;   I got the complaint that the name was
                                        ;   too long.)
  (checkmemory :overriding-include-test (not :no-macros))
  translate
  test-eq-hash-table
  #+mtg2 test-thread-pond
  #+mtg2 test-factions
  g2-final)







;; The variable `development-world-save-p' allows G2 to distinguish
;; between a development world save, and a development G2 started after
;; loading all the modules.  It is presently just used to decided whether
;; to quit lisp after shutting down G2.  -pto 04aug89

(progn
  (defvar development-world-save-p nil)
  (import-into-user-package 'development-world-save-p))




;;; The function `launch-G2-image' calls launch-system for AB.  This function is
;;; denigrated and should eventually be removed.  It slid into the system during
;;; our initial work with the Chestnut translator.  Launch-system is a better
;;; interface to launching G2, though the only thing that launch-system does is
;;; funcall the launch-function? of the given system.  For G2, the launch
;;; function is currently launch-ab.  Note that the old g2main for Chestnut 1.7
;;; still depends on it for the time being.  -jra 8/18/93

(defun-for-top-level launch-g2-image ()
  (launch-system 'ab))




;;; The function `launch-telewindows-image' calls launch-system for Telewindows.
;;; This function is denigrated and should eventually be removed.  See doc for
;;; launch-g2-image above for more info.  Note that the old twmain for Chestnut
;;; 1.7 still depends on it for the time being.  -jra 8/18/93

(defun-for-top-level launch-telewindows-image ()
  (launch-system 'telewindows))





;;; Save-G2-image ...


(defmacro remove-useless-properties ()
  ;; Get rid of all pointers to Gensym site specific atoms (strings, symbols,
  ;; etc.) here.
  '(progn
     (remprop 'ab :module-pathname-previously-loaded?)
     (remprop 'ab 'all-lisp-source-files)
     (remprop 'ab 'all-lisp-source-file-symbols)

     ;; The following needs to be present
     ;;(remprop 'ab 'lisp-modules-to-be-loaded)

     (remprop 'ab 'local-source-directory)
     (makunbound 'load-pathname)
     (remprop 'ab 'local-development-binary-directory)
     (remprop 'ab 'system-binary-pathname?)
     (remprop 'ab 'local-macro-directory)
     (remprop 'ab 'local-dst-directory)

     ;; Go through the symbol for each file in G2 and remove all the properties
     ;; that are irrelevant for a world save.
     (let (indicator-for-file-class
           property-indicator)
       (dolist (file-class-description alist-of-system-file-class-descriptions)
         (setq indicator-for-file-class
               (fcd-system-property-name file-class-description))
         (dolist (file (get 'ab indicator-for-file-class))
           (dolist (property-description alist-of-file-property-base-defaults)
             (setq property-indicator (first property-description))
             (remprop file property-indicator)))))))




#-translator
(progn
  (defun save-g2-image (&optional image-name?)
    (save-system-image 'g2 image-name?))
  (import-into-user-package 'save-g2-image))

#-translator
(progn
  (defun save-telewindows-image (&optional image-name?)
    (save-system-image 'telewindows image-name?))
  (import-into-user-package 'save-telewindows-image))



;; These functions should get generated by declare-system!! (MHD 10/19/89)

;; Note that there are user package versions of these because they have
;; to be callable from programs that start in the user package (before there
;; even is an AB package), e.g. the 123 file.


;;; Save-system-image ... If no-restart-function? is true, the executable comes
;;; up in a normal Lisp read-eval-print loop, source file info is not gotten rid
;;; of in Lucid, and remove-useless-properties is not called before saving.

;;; This function is only implemented as other than a stub for Lucid platforms.
;;; It is not defined on Lisp machines except in development.


#+(and development (not translator))
(progn
  (defun save-system-image (system image-name? &optional no-restart-function?)
    system image-name?                                ; not used on some platforms

    #+development
    (set (find-symbol "DEVELOPMENT-WORLD-SAVE-P" user-package-in-this-lisp)
         t)

    (unless no-restart-function?
      #+(and lucid (not translator))
      (if (boundp 'lucid::discard-source-file-info)        ; is this ever defined?
          (ab-lisp::funcall 'lucid::discard-source-file-info))
      (remove-useless-properties))

    #+lucid
    (let ((image-name
            (or image-name?
                (case system
                  (telewindows "tw")
                  (t "g2")))))
      (if no-restart-function?
          (lucid::disksave image-name :full-gc t)
          (lucid::disksave
            image-name
            :full-gc t
            :restart-function
            (case system
              (telewindows 'launch-telewindows-image)
              (t 'launch-g2-image))))))
  (import-into-user-package 'save-system-image))


;; Note that before a world save is made, we should clear pointers to site
;; specific objects - especially strings - and then do a GC.  -pto 19dec88










;;;; Licensing Server aka LS

(declare-system (ls
                  alias licensing-server
                  products-uninterested-in-this-system (gsi))
  #-no-macros
  (load :include-test-for-load nil)
  (bootstrap :include-test-for-load (not :do-not-load-bootstrap)
             :lisp-compile-function compile-bootstrap-and-reboot-all-modules
             :lisp-update-function update-bootstrap-and-reupdate-all-modules)
  systems
  portable-threads
  delta
  (features :overriding-include-test development)
  g2-config

  loop
  glbasics
  (gldebug :overriding-include-test development)
  (lisp-server :overriding-include-test development)

  numbers
  ;; check-kbs (needs frames2a)
  integrals

  license)

  ;; Note that this module also loads the secrete code computing modules
  ;; by hand when it loads up.

  ;; products         ;; Note A & B
  ;; licensing-users  ;; Note A & B

;; Note A: This module can be reloaded at runtime, it is a configuration
;; database and when it is reloaded it reconfigures the licensing server.
;; there are commands in the licensing server to reloaded it.

;; Note B: This two module were moved to "lic/server" with the delivered
;; final licensing-server.exe, they're not loadable by systems any more.
;; -- Chun Tian (binghe), 2011/11/18

;;;; Foreign Function Test

(declare-system (ctest
                  alias foreign-function-test
                  products-uninterested-in-this-system (telewindows gsi gw gensym-site ab ls)
                  system-is-windowless-p t)
  #-no-macros
  (load :include-test-for-load nil)
  (bootstrap :include-test-for-load (not :do-not-load-bootstrap)
             :lisp-compile-function compile-bootstrap-and-reboot-all-modules
             :lisp-update-function update-bootstrap-and-reupdate-all-modules)
  systems
  delta
  (features :overriding-include-test development)
  ctest-patches
  loop                                                ; Load this first to set *features*
  glbasics
  (gldebug :overriding-include-test development)
  os-foreign
  basics
  os-time
  os-settings
  os-memory
  primitives
  characters
  characters2
  utilities0
  utilities1
  utilities2
  letters
  unicode
  transcode
  utilities3
  times
  os-error
  launch
  pathnames
  schedule
  clocks
  networks

  ctest)
