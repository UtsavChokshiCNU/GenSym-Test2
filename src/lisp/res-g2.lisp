;; -*- Mode: Lisp; Package: AB; Base: 10; Syntax: Common-Lisp -*-
(in-package "AB")


;;;; Module RES-G2 (Resources for G2 Side Code)

;;; Copyright (c) 1986 - 2017 Gensym Corporation.
;;; All Rights Reserved.

;;; Joseph Devlin




;;; The slot-value-compiler for resource definitions has the responsibility
;;; to see that all expression found in a resource definition get evaluated,
;;; that values are substituted for numeric constants, etc.  This implies that
;;; the user should recompile all of their resource whenever there is a version
;;; change to the set of windows include files that are understood/simulated
;;; by the resource compiler.  Of course, such a change will only come
;;; around with each version of Telewindows.

(def-slot-value-compiler resource-definition (parse-result
						  resource-definition)
  (declare (ignore resource-definition))
  parse-result)

;; add a sanity check for the controls -- do they actually exist?
;; better to find out now than later...
;; jtidwell 5/29/96

;;; Note on parsed format of resource definitions

;;; There are no dotted lists in the input the slot value compiler for resource
;;; definition.  So the recursion in `evaluate-resource-defintion' is over
;;; nested proper lists rather than cons trees.  

(defun evaluate-resource-definition (exp)
  (cond
    ((consp exp)
     (case (car exp)
       (dialog-integer-expression )
       (otherwise
	(phrase-cons
	  (car exp)
	  (loop for sub in (cdr exp)
		collect (evaluate-resource-definition exp)
		using phrase-cons)))))
    (t
     exp)))

(add-grammar-rules
  
  '((resource-definition resource-statement-list)
    ;; Outer Grammar
    (resource-statement-list resource-statement
     (1))
    (resource-statement-list
     (resource-statement resource-statement-list)
     (1 . 2))

    ;; Resource Statement Types
    (resource-statement accelerators-resource-statement)
    (resource-statement bitmap-resource-statement)
    (resource-statement cursor-resource-statement)
    (resource-statement dialog-resource-statement)
    (resource-statement dialogex-resource-statement)
    (resource-statement font-resource-statement)
    (resource-statement language-resource-statement)
    (resource-statement menu-resource-statement)
    (resource-statement popup-resource-statement)
    (resource-statement stringtable-resource-statement)
    ;; temporary hack  - jtidwell 5/13/96
    ;; the five canonical resource structures:
    (resource-statement twdialog-resource-statement)
    (resource-statement twtabbeddialog-resource-statement)
    (resource-statement twframe-resource-statement)
    (resource-statement twmenu-resource-statement)
    (resource-statement twstatusbar-resource-statement)
    ;; (resource-statement tw-resource-statement)

    ;; Common Definitions
    (resource-name integer)
    (resource-name hex-integer-or-any-symbol)
    (resource-filename whole-string)
    (resource-boolean 'false)
    (resource-boolean 'true)
    (resource-boolean positive-integer
     1)
    (optional-control-name control-name)
    (optional-control-name
     ('\( control-name '\))
     2)
    (control-name 'idok)
    (control-name 'idcancel)
    (control-name 'idapply)
    (control-name 'idc_static)
    (control-name integer)
    (control-name hex-integer-or-any-symbol)
    (control-name unreserved-symbol)
    (hex-integer-or-any-symbol unreserved-symbol
     (hex-integer-or-symbol 1) control-name-hex-transform-or-symbol)

    ;; Common Substatements
    (optional-statement-list optional-statement (1))
    (optional-statement-list
     (optional-statement optional-statement-list)
     (1 . 2))
    (optional-statement characteristics-optional-statement)
    (optional-statement language-statement)
    (optional-statement version-optional-statement)
    (load-mem-options-2
     (load-attribute memory-attribute-list)
     (1 2))
    (load-mem-options-2
     memory-attribute-list
     (nil 1))
    (load-mem-options-2
     load-attribute
     (1 nil))
    (load-attribute 'preload)
    (load-attribute 'loadoncall)
    (memory-attribute-list
     memory-attribute
     (1))
    (memory-attribute-list
     (memory-attribute memory-attribute-list)
     (1 . 2))
    (memory-attribute 'fixed)
    (memory-attribute 'moveable)
    (memory-attribute 'discardable)
    (memory-attribute 'pure)
    (memory-attribute 'impure)

    (characteristics-optional-statement
     ('characteristics integer)
     (characteristics 2))
    (version-optional-statement
     ('version integer)
     (version 2))
    
    ;; Accelerators Definitions
    (accelerators-resource-statement
     (resource-name 'accelerators optional-statement-list
      'begin accelerator-resource-entry-list 'end)
     (win32 accelerators 1 ((@ 3) contents 5)))
    (accelerators-resource-statement
     (resource-name 'accelerators
      'begin accelerator-resource-entry-list 'end)
     (win32 accelerators 1 (contents 4)))
    (accelerator-resource-entry-list accelerator-resource-entry
     (1))
    (accelerator-resource-entry-list
     (accelerator-resource-entry accelerator-resource-entry-list)
     (1 . 2))
    (accelerator-resource-entry
     (accelerator-event '\, resource-name '\, accelerator-type-and-options)
     (win32 accel-event 3 (event 1 options 5)))
    (accelerator-resource-entry
     (accelerator-event '\, resource-name )
     (win32 accel-event 3 (event 1)))
    (accelerator-event whole-string)
    (accelerator-event positive-integer)
    (accelerator-type-and-options accelerator-type-or-option
     (1))
    (accelerator-type-and-options
     (accelerator-type-or-option '\, accelerator-type-and-options)
     (1 . 3))
    (accelerator-type-or-option 'control)
    (accelerator-type-or-option 'shift)
    (accelerator-type-or-option 'alt)
    (accelerator-type-or-option 'virtkey)
    (accelerator-type-or-option 'ascii)
    (accelerator-type-or-option 'noinvert)

    ;; Font Resources (not statements)
    (font-resource-statement
     (resource-name 'font resource-filename)
     (win32 font 1 (filename 3)))
    (font-resource-statement
     (resource-name 'font load-mem-options-2 resource-filename)
     (win32 font 1 (loadmem 3 filename 4)))
    
    ;; Menu Definitions
    (menu-resource-statement
     (resource-name 'menu load-mem-options-2
      menu-resource-statement-tail)
     (win32 menu 1 (loadmem 3 . 4)))
    (menu-resource-statement
     (resource-name 'menu
      menu-resource-statement-tail)
     (win32 menu 1 (3)))
    (menu-resource-statement-tail
     (optional-statement-list 'begin menu-item-list 'end)
     ((@ 1) contents 3))
    (menu-resource-statement-tail
     ('begin menu-item-list 'end)
     (contents 2))
    (menu-item-list
     menu-item
     (1))
    (menu-item-list
     (menu-item menu-item-list)
     (1 . 2))
    (menu-item
     ('menuitem 'separator)
     (win32 separator nil (nil)))
    (menu-item
     ('menuitem whole-string '\, control-name)
     (win32 menu-entry 4 (text 2)))
    (menu-item
     ('menuitem whole-string '\, control-name '\, menuitem-option-list)
     (win32 menu-entry 4 (text 2 options 6)))
    (menu-item popup-resource-statement)
    (menuitem-option-list menuitem-option (1))
    (menuitem-option-list
     (menuitem-option  '\, menuitem-option-list)
     (1 . 3))
    (menuitem-option 'checked)
    (menuitem-option 'grayed)
    (menuitem-option 'help)
    (menuitem-option 'inactive)
    (menuitem-option 'menubarbreak)
    (menuitem-option 'menubreak)

    ;; Popup Menu
    (popup-resource-statement
     ('popup whole-string menuitem-option-list
      'begin menu-item-list 'end)
     (win32 popup nil (text 2 options 3 contents 5)))
    (popup-resource-statement
     ('popup whole-string
      'begin menu-item-list 'end)
     (win32 popup nil (text 2 contents 4)))

    ;; Bitmap Resource
    (bitmap-resource-statement
     (resource-name 'bitmap resource-filename)
     (win32 bitmap 1 (filename 3)))
    (bitmap-resource-statement
     (resource-name 'bitmap load-mem-options-2 resource-filename)
     (win32 bitmap 1 (loadmem 3 filename 4)))

    ;; Cursor Resource
    (cursor-resource-statement
     (resource-name 'cursor resource-filename)
     (win32 cursor 1 (filename 3)))
    (cursor-resource-statement
     (resource-name 'cursor load-mem-options-2 resource-filename)
     (win32 cursor 1 (loadmem 3 filename 4)))
    
    ;; Dialog Resource
    (dialog-resource-statement
     (resource-name 'dialog
      integer '\, integer '\, positive-integer '\, positive-integer
      dialog-resource-statement-tail)
     (win32 dialog 1 (x 3 y 5 width 7 height 9 . 10)))
    (dialog-resource-statement
     (resource-name 'dialog load-mem-options-2
      integer '\, integer '\, positive-integer '\, positive-integer
      dialog-resource-statement-tail)
     (win32 dialog 1 (x 4 y 6 width 8 height 10 loadmem 3 . 11)))
    (dialog-resource-statement-tail
     (optional-dialog-statement-list
      'begin control-statement-list 'end)
     ((@ 1) contents 3))
    (dialog-resource-statement-tail
     ('begin control-statement-list 'end)
     (contents 2))
    (optional-dialog-statement-list
     optional-dialog-statement
     1)
    (optional-dialog-statement-list
     (optional-dialog-statement optional-dialog-statement-list)
     ((@ 1) . 2))
    (optional-dialog-statement optional-statement)
    (optional-dialog-statement caption-statement)
    (optional-dialog-statement class-statement)
    (optional-dialog-statement language-statement)
    (optional-dialog-statement style-statement)
    (optional-dialog-statement exstyle-statement)
    (optional-dialog-statement font-statement)
    (caption-statement
     ('caption  whole-string)
     (caption 2))
    (class-statement
     ('class whole-string)
     (class 2))
    (class-statement
     ('class positive-integer)
     (class 2))
    (language-statement
     ('language positive-integer positive-integer)
     (language (primary 2 secondary 3)))
    (exstyle-statement
     ('exstyle positive-integer)
     (exstyle 2))
    (exstyle-statement
     ('exstyle exstyle-spec)
     (exstyle 2))
    (exstyle-spec exstyle-spec-entry (1))
    (exstyle-spec
     (exstyle-spec-entry '\| exstyle-spec)
     (1 . 3))
    (exstyle-spec-entry 'ws_ex_dlgmodalframe)
    (exstyle-spec-entry 'ws_ex_leftscrollbar)
    (exstyle-spec-entry 'ws_ex_appwindow)
    (font-statement
     ('font positive-integer '\, whole-string)
     (font (pointsize 2 typeface 4)))
    (style-statement
     ('style dialog-style-list)
     (style 2))
    (dialog-style-list dialog-style-factor (1))
    (dialog-style-list
     (dialog-style-factor '\| dialog-style-list)
     (1 . 3))
    (dialog-style-factor dialog-style-entry)
    (dialog-style-factor
     ('not dialog-style-entry)
     (not 2))
    (dialog-style-entry hex-integer)
    (dialog-style-entry positive-integer)
    (dialog-style-entry 'ds_localedit)
    (dialog-style-entry 'ds_modalframe)
    (dialog-style-entry 'ds_noidlemsg)
    (dialog-style-entry 'ws_border)
    (dialog-style-entry 'ws_caption)
    (dialog-style-entry 'ws_child)
    (dialog-style-entry 'ws_childwindow)
    (dialog-style-entry 'ws_clipchildren)
    (dialog-style-entry 'ws_clipsiblings)
    (dialog-style-entry 'ws_disabled)
    (dialog-style-entry 'ws_dlgframe)
    (dialog-style-entry 'ws_group)
    (dialog-style-entry 'ws_hscroll)
    (dialog-style-entry 'ws_iconic)
    (dialog-style-entry 'ws_maximize)
    (dialog-style-entry 'ws_maximizebox)
    (dialog-style-entry 'ws_minimize)
    (dialog-style-entry 'ws_minimizebox)
    (dialog-style-entry 'ws_overlapped)
    (dialog-style-entry 'ws_overlappedwindow)
    (dialog-style-entry 'ws_popup)
    (dialog-style-entry 'ws_popupwindow)
    (dialog-style-entry 'ws_sizebox)
    (dialog-style-entry 'ws_sysmenu)
    (dialog-style-entry 'ws_tabstop)
    (dialog-style-entry 'ws_thickframe)
    (dialog-style-entry 'ws_visible)
    (dialog-style-entry 'ws_vscroll)

    ;; Extended Dialogs
    (dialogex-resource-statement
     (resource-name 'dialogex
      integer '\, integer '\, positive-integer '\, positive-integer
      dialogex-resource-statement-tail)
     (win32 dialog 1 (x 3 y 5 width 7 height 9 . 10)))
    (dialogex-resource-statement
     (resource-name 'dialogex load-mem-options-2
      integer '\, integer '\, positive-integer '\, positive-integer
      dialogex-resource-statement-tail)
     (win32 dialog 1 (x 4 y 6 width 8 height 10 loadmem 3 . 11)))
    (dialogex-resource-statement
     (resource-name 'dialogex
      integer '\, integer '\, positive-integer '\, positive-integer
      '\, dialog-integer-expression
      dialogex-resource-statement-tail)
     (win32 dialog 1 (x 3 y 5 width 7 height 9 help-id 11 . 12)))
    (dialogex-resource-statement
     (resource-name 'dialogex load-mem-options-2
      integer '\, integer '\, positive-integer '\, positive-integer
      '\, dialog-integer-expression
      dialogex-resource-statement-tail)
     (win32 dialog 1 (x 4 y 6 width 8 height 10 loadmem 3 help-id 12 . 13)))
    (dialogex-resource-statement-tail
     (optional-dialogex-statement-list
      'begin dialogex-control-statement-list 'end)
     ((@ 1) contents 3))
    (dialogex-resource-statement-tail
     ('begin dialogex-control-statement-list 'end)
     (contents 2))
    (optional-dialogex-statement-list
     optional-dialogex-statement
     (1))
    (optional-dialogex-statement-list
     (optional-dialogex-statement optional-dialogex-statement-list)
     (1 . 2))
    ;; The following should have a transform defined
    ;; to test whether the unique-expression is an integer-expresion
    ;; using a very limited set of operators
    ;;
    ;; why is all this necessary for a help-id?  -jtidwell 5/17/96
    (dialog-integer-expression dialog-bitwise-expression)
    (dialog-bitwise-expression
     (dialog-bitwise-expression dialog-bitwise-op dialog-additive-expression)
     (2 1 3))
    (dialog-bitwise-expression dialog-additive-expression)
    (dialog-bitwise-op '\& bitwise-and)
    (dialog-bitwise-op '\| bitwise-or)
    (dialog-additive-expression
     (dialog-additive-expression dialog-additive-op dialog-term)
     (2 1 3))
    (dialog-additive-expression dialog-term)
    (dialog-additive-op '\+ add)
    (dialog-additive-op '\- subtract)
    (dialog-term
     ('\~ dialog-factor)
     (not 2))
    (dialog-term dialog-factor)
    (dialog-factor
     ('\( dialog-bitwise-expression '\))
     2)
    (dialog-factor integer)
    (optional-dialogex-statement optional-statement)
    (optional-dialogex-statement caption-statement)
    (optional-dialogex-statement class-statement)
    (optional-dialogex-statement style-statement)
    (optional-dialogex-statement exstyle-statement)
    (optional-dialogex-statement dialogex-font-statement)
    (optional-dialogex-statement dialogex-menu-statement)
    (dialogex-font-statement
     ('font positive-integer '\, whole-string)
     (font (pointsize 2 typeface 4)))
    (dialogex-font-statement
     ('font positive-integer '\, whole-string
      '\, positive-integer)
     (font (pointsize 2 typeface 4 weight 6)))
    (dialogex-font-statement
     ('font positive-integer '\, whole-string
      '\, positive-integer
      '\, resource-boolean)
     (font (pointsize 2 typeface 4 weight 6 italic 8)))
    (dialogex-menu-statement
     ('menu resource-name)
     (menu 2))
    (dialogex-control-statement-list dialogex-control-statement (1))
    (dialogex-control-statement-list
     (dialogex-control-statement dialogex-control-statement-list)
     (1 . 2))
    (dialogex-control-statement extended-generic-control-statement)
    (dialogex-control-statement extended-static-control-statement)
    (dialogex-control-statement extended-button-control-statement)
    (dialogex-control-statement extended-edit-control-statement)
    (extended-generic-control-statement
     ('control whole-string '\, optional-control-name
      '\, generic-control-class-name '\, generic-control-style-spec
      dialogex-control-common)
     (win32 extended-control 4 (class 6 text 2 style 8 . 9)))
    (extended-static-control-statement
     (static-control-class-name whole-string '\, optional-control-name
      dialogex-control-common)
     (win32 extended-static 4 (class 1 text 2 . 5)))
    (extended-button-control-statement
     (button-control-class-name whole-string '\, optional-control-name
      dialogex-control-common)
     (win32 extended-button 4 (class 1 text 2 . 5)))
    (extended-edit-control-statement
     (edit-control-class-name optional-control-name
      dialogex-control-common)
     (win32 extended-edit 2 (class 1 . 3)))

    (dialogex-control-common
     (dialog-integer-expression '\, dialog-integer-expression
      '\, dialog-integer-expression '\, dialog-integer-expression
      '\, exstyle-spec '\, dialog-integer-expression
      'begin dialogex-control-data-spec 'end)
     (x 1 y 3 width 5 height 7 exstyle 9 help-id 11 control-data 12))
    (dialogex-control-common
     (dialog-integer-expression '\, dialog-integer-expression
      '\, dialog-integer-expression '\, dialog-integer-expression
      '\, exstyle-spec '\, dialog-integer-expression)
     (x 1 y 3 width 5 height 7 exstyle 9 help-id 11))
    (dialogex-control-common
     (dialog-integer-expression '\, dialog-integer-expression
      '\, dialog-integer-expression '\, dialog-integer-expression
      '\, exstyle-spec)
     (x 1 y 3 width 5 height 7 exstyle 9))
    (dialogex-control-common
     (dialog-integer-expression '\, dialog-integer-expression
      '\, dialog-integer-expression '\, dialog-integer-expression)
     (x 1 y 3 width 5 height 7))
    (dialogex-control-data-spec dialogex-control-data-element (1))
    (dialogex-control-data-spec
     (dialogex-control-data-element '\, dialogex-control-data-spec)
     (1 . 3))
    (dialogex-control-data-element positive-integer) ; wrong, or not general enough
    
    (generic-control-style-spec generic-control-style-factor (1))
    (generic-control-style-spec
     (generic-control-style-factor '\| generic-control-style-spec)
     (1 . 3))
    (generic-control-style-factor generic-control-style)
    (generic-control-style-factor
     ('not generic-control-style)
     (not 2))
    (generic-control-style button-style)
    (generic-control-style combobox-style)
    (generic-control-style edit-style)
    (generic-control-style listbox-style)
    (generic-control-style scroll-bar-style)
    (generic-control-style static-style)
    (generic-control-style dialog-style-entry)
    (generic-control-class-name 'button)
    (generic-control-class-name 'static)
    (generic-control-class-name 'edit)
    (generic-control-class-name 'listbox)
    (generic-control-class-name 'scrollbar)
    (generic-control-class-name 'combobox)
    (generic-control-class-name whole-string)
    (static-control-class-name 'ltext)
    (static-control-class-name 'rtext)
    (static-control-class-name 'ctext)
    (button-control-class-name 'auto3state)
    (button-control-class-name 'autocheckbox)
    (button-control-class-name 'autoradiobutton)
    (button-control-class-name 'checkbox)
    (button-control-class-name 'pushbox)
    (button-control-class-name 'pushbutton)
    (button-control-class-name 'radiobutton)
    (button-control-class-name 'state3)
    (button-control-class-name 'userbutton)
    (edit-control-class-name 'edittext)
    (edit-control-class-name 'bedit)
    (edit-control-class-name 'hedit)
    (edit-control-class-name 'edit)

    ;; Controls
    (control-statement-list control-statement (1))
    (control-statement-list
     (control-statement control-statement-list)
     (1 . 2))
    (control-statement auto3state-statement)
    (control-statement autocheckbox-statement)
    (control-statement autoradiobutton-statement)
    (control-statement checkbox-statement)
    (control-statement combobox-statement)
    (control-statement defpushbutton-statement)
    (control-statement edittext-statement)
    (control-statement general-control-statement)
    (control-statement groupbox-statement)
    (control-statement listbox-statement)
    (control-statement ctext-statement)
    (control-statement ltext-statement)
    (control-statement rtext-statement)
    (control-statement pushbutton-statement)
    (control-statement pushbox-statement)
    (control-statement radiobutton-statement)
    (control-statement state3-statement)

    ;; (combobox [Text???] id x,y, w, h, [style [, extended-style ]])
    (combobox-statement generated-combobox-statement)
    (combobox-statement documented-combobox)
    (generated-combobox-statement
     ('combobox whole-string '\, control-name control-statement-tail)
     (win32 combobox 4 (text 2 . 5)))
    (generated-combobox-statement
     ('combobox control-name control-statement-tail)
     (win32 combobox 2 3))
    ;; x y w h style exstyle
    (control-statement-tail
     ('\, integer '\, integer
      '\, positive-integer '\, positive-integer)
     (x 2 y 4 width 6 height 8))
    (control-statement-tail
     ('\, integer '\, integer
      '\, positive-integer '\, positive-integer
      '\, control-style-spec)
     (x 2 y 4 width 6 height 8 style 10))
    (control-statement-tail
     ('\, integer '\, integer
      '\, positive-integer '\, positive-integer
      '\, control-style-spec
      '\, control-extended-style-spec)
     (x 2 y 4 width 6 height 8 style 10 extended-style 12))
    (combobox-style-spec combobox-style-factor (1))
    (combobox-style-spec
     (combobox-style-factor '\| combobox-style-spec)
     (1 . 3))
    (combobox-style-factor combobox-style)
    (combobox-style-factor
     ('not combobox-style)
     (not 2))
    (combobox-style 'ws_tabstop)
    (combobox-style 'ws_group)
    (combobox-style 'ws_vscroll)
    (combobox-style 'ws_disabled)
    (combobox-style 'cbs_simple)
    (combobox-style 'cbs_dropdown)
    (combobox-style 'cbs_dropdownlist)
    (combobox-style 'cbs_autohscroll)
    (combobox-style 'cbs_disablenoscroll)
    (combobox-style 'cbs_hasstrings)
    (combobox-style 'cbs_nointegralheight)
    (combobox-style 'cbs_oemconvert)
    (combobox-style 'cbs_ownerdrawfixed)
    (combobox-style 'cbs_ownerdrawvariable)
    (combobox-style 'cbs_sort)
    (combobox-style 'cbs_uppercase)
    (combobox-style 'cbs_lowercase)

    ;; (listbox text id ...)
    (listbox-statement generated-listbox-statement)
    (listbox-statement documented-listbox)
    (generated-listbox-statement
     ('listbox whole-string '\, control-name control-statement-tail)
     (win32 listbox 4 (text 2 . 5))) ;; pbk ask joe about this comment 
    ;; the nil is for the fictitious "text" field, cf. combobox
    (generated-listbox-statement
     ('listbox control-name control-statement-tail)
     (win32 listbox 2 3))

    
    ;; (control text, id, class, style, x, y, w, h, [,extended-style])
    (general-control-statement
     ('control whole-string '\, control-name ;positive-integer 
      '\, control-class '\, control-style-spec '\, integer
      '\, integer '\, positive-integer '\, positive-integer)
     (win32 control 4 (class 6 text 2 x 10 y 12 width 14 height 16
		      style 8)))
    (general-control-statement
     ('control whole-string '\, control-name ;positive-integer
      '\, control-class '\, control-style-spec '\, positive-integer
      '\, positive-integer '\, positive-integer '\, positive-integer
      '\, control-extended-style-spec)
     (win32 control 4 (class 6 text 2 x 10 y 12 width 14 height 16
		      style 8 exstyle 18)))
    (control-class whole-string
     (control-class 1) check-and-downcase-class-name-transform) ; pbk
    (control-class positive-integer)
    (control-style-spec control-style-factor (1))
    (control-style-spec
     (control-style-factor '\| control-style-spec)
     (1 . 3))
    (control-style-factor control-style)
    (control-style-factor
     ('not control-style)
     (not 2))
    (control-style button-style)
    (control-style combobox-style)
    (control-style edit-style)
    (control-style listbox-style)
    (control-style scroll-bar-style)
    (control-style static-style)
    (control-style child-window-style)

    (child-window-style 'ws_child)    ; vkp 12/26/95 hack
    (child-window-style 'ws_visible)
    (child-window-style 'ws_border)
    
    (button-style 'bs_3state)
    (button-style 'bs_auto3state)
    (button-style 'bs_autocheckbox)
    (button-style 'bs_autoradiobutton)
    (button-style 'bs_checkbox)
    (button-style 'bs_defpushbutton)
    (button-style 'bs_groupbox)
    (button-style 'bs_lefttext)
    (button-style 'bs_ownerdraw)
    (button-style 'bs_pushbutton)
    (button-style 'bs_radiobutton)
    (button-style 'bs_userbutton)
    (button-style 'bs_text)
    ;(button-style 'bs_icon)
    ;(button-style 'bs_bitmap)
    (button-style 'bs_left)
    (button-style 'bs_right)
    (button-style 'bs_center)
    (button-style 'bs_top)
    (button-style 'bs_bottom)
    (button-style 'bs_vcenter)
    (button-style 'bs_pushlike)
    (button-style 'bs_multiline)
    (button-style 'bs_notify)
    (button-style 'bs_flat)
    (button-style 'bs_rightbutton)
    
    (edit-style 'es_left)
    (edit-style 'es_center)
    (edit-style 'es_right)
    (edit-style 'es_lowercase)
    (edit-style 'es_uppercase)
    (edit-style 'es_password)
    (edit-style 'es_multiline)
    (edit-style 'es_autovscroll)
    (edit-style 'es_autohscroll)
    (edit-style 'es_nohidesel)
    (edit-style 'es_oemconvert)
    (edit-style 'es_readonly)
    (edit-style 'es_wantreturn)
    (edit-style 'es_number)

    (listbox-style 'lbs_standard)
    (listbox-style 'lbs_disablenoscroll)
    (listbox-style 'lbs_extendedsel)
    (listbox-style 'lbs_hasstrings)
    (listbox-style 'lbs_notify)
    (listbox-style 'lbs_multiplesel)
    (listbox-style 'lbs_multicolumn)
    (listbox-style 'lbs_nointegralheight)
    (listbox-style 'lbs_sort)
    (listbox-style 'lbs_noredraw)
    (listbox-style 'lbs_ownerdrawfixed)
    (listbox-style 'lbs_ownerdrawvariable)
    (listbox-style 'lbs_usetabstops)
    (listbox-style 'lbs_wantkeyboardinput)
    (listbox-style 'lbs_nodata)
    (listbox-style 'lbs_nosel)

    (scroll-bar-style 'sbs_vert)
    (scroll-bar-style 'sbs_rightalign)
    (scroll-bar-style 'sbs_leftalign)
    (scroll-bar-style 'sbs_horz)
    (scroll-bar-style 'sbs_topalign)
    (scroll-bar-style 'sbs_bottomalign)
    (scroll-bar-style 'sbs_sizebox)
    (scroll-bar-style 'sizeboxtopleftalign)
    (scroll-bar-style 'sizeboxbottomrightalign)

    (static-style 'ss_left)
    (static-style 'ss_center)
    (static-style 'ss_right)
    (static-style 'ss_leftnowordwrap)
    (static-style 'ss_simple)
    (static-style 'ss_noprefix)
    (static-style 'ss_icon)
    ;(static-style 'ss_bitmap)
    (static-style 'ss_blackrect)
    (static-style 'ss_whiterect)
    (static-style 'ss_grayrect)
    (static-style 'ss_blackframe)
    (static-style 'ss_grayframe)
    (static-style 'ss_whiteframe)
    (static-style 'ss_useritem)
    (static-style 'ss_ownerdraw)
    (static-style 'ss_enhmetafile)
    (static-style 'ss_etchedhorz)
    (static-style 'ss_etchedvert)
    (static-style 'ss_etchedframe)
    (static-style 'ss_typemask)
    (static-style 'ss_notify)
    (static-style 'ss_centerimage)
    (static-style 'ss_rightjust)
    (static-style 'ss_realsizeimage)
    (static-style 'ss_sunken)

    ;; Text Controls
    (ctext-statement
     ('ctext whole-string '\, optional-control-name control-statement-tail)
     (win32 ctext 4 (text 2 . 5)))
    (ltext-statement
     ('ltext whole-string '\, optional-control-name control-statement-tail)
     (win32 ltext 4 (text 2 . 5)))
    (rtext-statement
     ('rtext whole-string '\, optional-control-name control-statement-tail)
     (win32 rtext 4 (text 2 . 5)))

    ;; Pushbutton Controls
   
    (auto3state-statement
     ('auto3state whole-string '\, control-name control-statement-tail)
     (win32 auto3state 4 (text 2 . 5)))
    (autocheckbox-statement
     ('autocheckbox whole-string '\, control-name control-statement-tail)
     (win32 autocheckbox 4 (text 2 . 5)))
    (autoradiobutton-statement
     ('autoradiobutton whole-string '\, control-name control-statement-tail)
     (win32 autoradiobutton 4 (text 2 . 5)))
    (checkbox-statement
     ('checkbox whole-string '\, control-name control-statement-tail)
     (win32 checkbox 4 (text 2 . 5)))
    (defpushbutton-statement
	('defpushbutton whole-string '\, control-name control-statement-tail)
	(win32 defpushbutton 4 (text 2 . 5)))
    (edittext-statement
     ('edittext whole-string '\, control-name control-statement-tail)
     (win32 edittext 4 (text 2 . 5)))
    (edittext-statement
     ('edittext control-name control-statement-tail)
     (win32 edittext 2 3))
    (groupbox-statement
     ('groupbox whole-string '\, control-name control-statement-tail)
     (win32 groupbox 4 (text 2 . 5)))
    (pushbutton-statement
      ('pushbutton whole-string '\, control-name control-statement-tail)
      (win32 pushbutton 4 (text 2 . 5)))
    (pushbox-statement
     ('pushbox whole-string '\, control-name control-statement-tail)
     (win32 pushbox 4 (text 2 . 5)))
    (radiobutton-statement
     ('radiobutton whole-string '\, control-name control-statement-tail)
     (win32 radiobutton 4 (text 2 . 5)))
    (state3-statement
     ('state3 whole-string '\, control-name control-statement-tail)
     (win32 state3 4 (text 2 . 5)))

    ;; Language Definition
    (language-resource-statement
     ('language positive-integer positive-integer)
     (win32 language nil (primary 2 secondary 3))) ; the nil is a dummy for id
    
    ;; Stringtable Resource Statement
    (stringtable-resource-statement
     ('stringtable load-mem-options-2 stringtable-tail)
     (win32 stringtable nil (loadmem 2 . 3)))
    (stringtable-resource-statement
     ('stringtable stringtable-tail)
     (win32 stringtable nil (2)))
    (stringtable-tail
     (optional-statement-list 'begin stringtable-entry-list 'end)
     ((@ 1) contents 3))
    (stringtable-tail
     ('begin stringtable-entry-list 'end)
     (contents 2))
    (stringtable-entry-list stringtable-entry (1))
    (stringtable-entry-list
     (stringtable-entry stringtable-entry-list)
     (1 . 2))
    (stringtable-entry
     (resource-name whole-string))
    
    
    ;; TW-resource  -jtidwell 5/13/96
    ;; twdialog
    (twdialog-resource-statement
     (resource-name 'tw-dialog
      integer '\, integer '\, positive-integer '\, positive-integer
      twdialog-statement-tail)
     (tw tw-dialog 1 (x 3 y 5 width 7 height 9 . 10)))
    (twdialog-resource-statement
     (resource-name 'tw-dialog load-mem-options-2
      integer '\, integer '\, positive-integer '\, positive-integer
      twdialog-statement-tail)
     (tw tw-dialog 1 (x 4 y 6 width 8 height 10 loadmem 3 . 11)))
    
    (twtabbeddialog-resource-statement
     (resource-name 'tw-tabbed-dialog
      integer '\, integer '\, positive-integer '\, positive-integer
      twtabbeddialog-statement-tail)
     (tw tw-tabbed-dialog 1 (x 3 y 5 width 7 height 9 . 10)))
    (twtabbeddialog-resource-statement
     (resource-name 'tw-tabbed-dialog load-mem-options-2
      integer '\, integer '\, positive-integer '\, positive-integer
      twtabbeddialog-statement-tail)
     (tw tw-tabbed-dialog 1 (x 4 y 6 width 8 height 10 loadmem 3 . 11)))
        
    (twframe-resource-statement
     (resource-name 'tw-frame
      integer '\, integer '\, positive-integer '\, positive-integer
      twframe-statement-tail)
     (tw tw-frame 1 (x 3 y 5 width 7 height 9 . 10)))
    
    (twmenu-resource-statement
     (resource-name 'tw-menu load-mem-options-2
      twmenu-statement-tail)
     (tw tw-menu 1 (loadmem 3 . 4)))
    (twmenu-resource-statement
     (resource-name 'tw-menu
      twmenu-statement-tail)
     (tw tw-menu 1 3))
    
    (twstatusbar-resource-statement
     (resource-name 'tw-status-bar
      integer '\, integer '\, positive-integer '\, positive-integer
      twstatusbar-statement-tail)
     (tw tw-status-bar 1 (x 3 y 5 width 7 height 9 . 10)))
    

    ;; statement tails
    (twdialog-statement-tail
     (optional-twdialog-statement-list
      'begin twcontrol-statement-list 'end)   ;; control list
     ((@ 1) contents 3))
    (twdialog-statement-tail
     ('begin twcontrol-statement-list 'end)
     (contents 2))
    
    (twtabbeddialog-statement-tail
     (optional-twdialog-statement-list
      'begin twtabpage-statement-list 'end)   ;; tabpage list
     ((@ 1) contents 3))
    (twtabbeddialog-statement-tail
     ('begin twtabpage-statement-list 'end)
     (contents 2))
    
    (twframe-statement-tail
     (optional-twdialog-statement-list
      'begin twview-statement-list 'end)  ;; view list
     ((@ 1) contents 3))
    (twframe-statement-tail
     ('begin twview-statement-list 'end)
     (contents 2))
    
    (twmenu-statement-tail
     (optional-twresource-statement-list
      'begin twmenu-item-list 'end)         ;; menu-item list
     ((@ 1) contents 3))
    (twmenu-statement-tail
     ('begin twmenu-item-list 'end)
     (contents 2))
    
    (twstatusbar-statement-tail
     (optional-twresource-statement-list
      'begin twsegment-statement-list 'end)  ;; segment list
     ((@ 1) contents 3))
    (twstatusbar-statement-tail
     ('begin twsegment-statement-list 'end)
     (contents 2))

    (optional-twresource-statement-list optional-statement)
    (optional-twresource-statement-list optional-twresource-statement)
    (optional-twresource-statement-list
     (optional-twresource-statement optional-twresource-statement-list)
     ((@ 1) . 2))
    (optional-twresource-statement-list
     (optional-statement optional-twresource-statement-list)
     ((@ 1) . 2))
    (optional-twresource-statement
     ('subclass class)
     (subclass 2))   ;; needs defining
    (optional-twresource-statement
     ('attributes attribute-list)
     (attributes 2))
    (attribute-list attribute-pair)
    (attribute-list
     (attribute-pair '\, attribute-list)
     ((@ 1) . 3))
    (attribute-pair
     (attribute-name '\= attribute-value)
     (1 3))
    (attribute-value
     ('\( attribute-value-sublist '\))
     2)
    (attribute-value-sublist attribute-value (1))
    (attribute-value-sublist
     (attribute-value '\, attribute-value-sublist)
     (1 . 3))
    (attribute-value whole-string)
    (attribute-value unreserved-symbol)
    (attribute-value number)
    (attribute-value 'true)
    (attribute-value 'false)
    (attribute-value 'yes)
    (attribute-value 'no)
    (attribute-value 'none)
    
    (optional-twdialog-statement-list
     optional-dialog-statement
     1)
    (optional-twdialog-statement-list
     optional-twresource-statement
     1)
    (optional-twdialog-statement-list
     (optional-twresource-statement optional-twdialog-statement-list)
     ((@ 1) . 2))
    (optional-twdialog-statement-list
     (optional-dialog-statement optional-twdialog-statement-list)
     ((@ 1) . 2))

    ;; tw-resource control, etc. statement lists
    ;; note:  twcontrol-statement-lists can include both controls and views
    ;;  (as of 7/3/96)  - jtidwell
    (twcontrol-statement-list twcontrol-statement (1))
    (twcontrol-statement-list twformview-statement-for-dialog (1))
    (twcontrol-statement-list
     (twcontrol-statement twcontrol-statement-list)
     (1 . 2))
    (twcontrol-statement-list
     (twformview-statement-for-dialog twcontrol-statement-list)
     (1 . 2))
    (twcontrol-statement
     (class whole-string '\, control-name
       control-statement-tail '\, attribute-list)
     (tw 1 4 (text 2 attributes 7 . 5)))
    (twcontrol-statement
     (class whole-string '\, control-name
       control-statement-tail)
      (tw 1 4 (text 2 . 5)))
    (twcontrol-statement
     (class control-name
       control-statement-tail '\, attribute-list)
     (tw 1 2 (attributes 5 . 3)))
    (twcontrol-statement
     (class control-name
       control-statement-tail)
      (tw 1 2 3))
    (twformview-statement-for-dialog
     (class resource-name control-statement-tail '\, attribute-list
      'begin twcontrol-statement-list 'end)
     (tw 1 2 (attributes 5 contents 7 . 3)))
    (twformview-statement-for-dialog
     (class resource-name control-statement-tail
      'begin twcontrol-statement-list 'end)
     (tw 1 2 (contents 5 . 3)))

    (twview-statement-list twview-statement (1))
    (twview-statement-list
     (twview-statement twview-statement-list)
     (1 . 2))
    (twview-statement twformview-statement)
    (twview-statement twsplitter-statement)
    (twview-statement twotherview-statement)
    (twformview-statement
     (class resource-name '\, attribute-list
      'begin twcontrol-statement-list 'end)
     (tw 1 2 (attributes 4 contents 6)))
    (twformview-statement
     (class resource-name
      'begin twcontrol-statement-list 'end)
     (tw 1 2 (contents 4)))
    (twsplitter-statement
     (class resource-name '\, attribute-list
      'begin twview-statement-list 'end)
     (tw 1 2 (attributes 4 contents 6)))
    (twsplitter-statement
     (class resource-name
      'begin twview-statement-list 'end)
     (tw 1 2 (contents 4)))
    (twotherview-statement
     (class resource-name '\, attribute-list)
     (tw 1 2 (attributes 4)))
    (twotherview-statement
     (class resource-name)
     (tw 1 2 (nil)))


    (twtabpage-statement-list twtabpage-statement(1))
    (twtabpage-statement-list twcontrol-statement(1))
    (twtabpage-statement-list
     (twtabpage-statement twtabpage-statement-list)
     (1 . 2))    
    (twtabpage-statement-list
     (twcontrol-statement twtabpage-statement-list)
     (1 . 2))
    (twtabpage-statement
     ('tabpage resource-name)
     (tw tw-tabpage 2 (nil)))    ;; needs defining
    (twtabpage-statement
     ('tabs integer '\, integer)
     (tw tw-tabs nil (x 2 y 4)))    ;; needs defining
    
    (twmenu-item-list twmenu-item (1))
    (twmenu-item-list
     (twmenu-item twmenu-item-list)
     (1 . 2))
    (twmenu-item
     ('menuitem 'separator)
     (tw separator nil (nil)))
    (twmenu-item
     ('menuitem whole-string '\, control-name)
     (tw menu-entry 4 (text 2)))
    (twmenu-item
     ('menuitem whole-string '\, control-name '\, twmenu-item-option-list)
     (tw menu-entry 4 (text 2 . 6)))
    (twmenu-item-option-list menuitem-option-list
     (options 1))
    (twmenu-item-option-list handler-pair)
    (twmenu-item-option-list
     (menuitem-option-list '\, handler-pair)
     (options 1 . 3))
    (handler-pair
     ('handler '\= unreserved-symbol)
     (handler 3))

    
    (twmenu-item twpopup-resource-statement)
    (twpopup-resource-statement
     ('popup whole-string '\, resource-name '\, menuitem-option-list
      'begin twmenu-item-list 'end)
     (tw popup 4 (text 2 options 6 contents 8)))
    (twpopup-resource-statement
     ('popup whole-string '\, resource-name
      'begin twmenu-item-list 'end)
     (tw popup 4 (text 2 options nil contents 6)))
#|
    ;; if we ever decide to use subclasses of tw-popup-menu...
    (twpopup-resource-statement
     (class whole-string '\, resource-name '\,
      menuitem-option-list '\, attr-statement-list
      'begin twmenu-item-list 'end)
     (popup 2 6 10))
    (twpopup-resource-statement
     (class whole-string '\, resource-name attr-statement-list
      'begin twmenu-item-list 'end)
     (popup 2 nil 7))
    (twpopup-resource-statement
     (class whole-string '\, resource-name menuitem-option-list
      'begin twmenu-item-list 'end)
     (popup 2 5 7))
    (twpopup-resource-statement
     (class whole-string '\, resource-name
      'begin twmenu-item-list 'end)
     (popup 2 nil 6))
|#
    
    (twsegment-statement-list twsegment-statement (1))
    (twsegment-statement-list
     (twsegment-statement twsegment-statement-list)
     (1 . 2))
    (twsegment-statement
     ('segment whole-string '\, resource-name '\, integer '\, positive-integer
      optional-twresource-statement-list)
     (tw segment 4 (text 2 x 6 width 8 . 9)))
    (twsegment-statement
     ('segment whole-string '\, resource-name '\, integer '\, positive-integer)
     (tw segment 4 (text 2 x 6 width 8)))

    ;; end tw-resource stuff


    ))

(defun control-name-hex-transform-or-symbol (thing)
  (let* ((sym (cadr thing))
	 (pname (symbol-name-text-string sym))
	 (len (lengthw pname)))
    (cond
      ((memq sym '(idok idcancel idapply idc_static))
       bad-phrase)
      ((and (>f len 2)
	    (char=w #.%\0 (charw pname 0))
	    (or (char=w #.%\x (charw pname 1))
		(char=w #.%\X (charw pname 1)))
	    (loop for i from 2 below len
		  as ch = (charw pname i)
		  always (digit-char-pw ch 16)))
       (loop with res = 0
	     for i from 2 below len
	     as ch = (char-upcasew (charw pname i))
	     as digit-value = (if (digit-char-pw ch)
				  (-f (char-codew ch)
				      #.(char-codew #.%\0))
				  (-f (char-codew ch)
				      #.(-f (char-codew #.%\A) 10)))
	     do (setf res (logior digit-value (ashf res 4)))
	     finally (return res)))
      (t ;(format t "pbk: hex-badphrase, ergo just a symbol.~%")
	 sym))))

(declare-grammar-transform-can-return-bad-phrase control-name-hex-transform-or-symbol)

(defparameter legit-win32-class-listing
  '(#.(stringw "button")
    #.(stringw "combobox")
    #.(stringw "listbox")
    #.(stringw "static")
    #.(stringw "edit")))

(defun-simple legit-win32-class-p (class-name) 
  (loop for legit-class in legit-win32-class-listing
	thereis (string-equalw legit-class class-name)))

(defun check-and-downcase-class-name-transform (thing)
  (let ((class-name (second thing)))
    (cond ((legit-win32-class-p class-name)
	   (copy-text-string-with-case-conversion class-name :none))
	  (t bad-phrase))))

(declare-grammar-transform-can-return-bad-phrase check-and-downcase-class-name-transform)

;;; The class `resource' is being remove in favor 

#|

(def-class (resource (item entity) define-predicate)
  
  ;; initialize method now deals with initial setup -- this slot's init form
  ;; will now be nil, and inherited. (MHD 7/18/94)
;  (frame-status-and-notes
;    (:funcall slot-value-cons-function incomplete nil))
  
  (frame-author-or-authors
    nil (type authors-with-time-of-last-edit?))
  (frame-change-log nil (type frame-change-log))
  (name-or-names-for-frame
    nil system (type nil) save)
  (icon-description
    (:funcall-at-load-time
      create-icon-description
      60 60
      ((polychrome (g2-icon-background . light-gray)
		   (g2-icon-light-shading . smoke)
		   (g2-icon-dark-shading . dark-gray)
		   (icon-color . foreground)
		   (g2-icon-specialty-region-1 . black)
		   (g2-icon-specialty-region-2 . gray))
       g2-icon-background
       (solid-rectangle (0 0) (50 50))
       g2-icon-light-shading
       (filled-polygon ((0 0) (50 0) (47 3) (3 3) (3 47) (0 50))
		       ((0 0) (50 0) (47 3)) ((3 3) (3 47) (0 50))
		       ((0 0) (47 3) (3 3)) ((3 3) (0 50) (0 0)))
       g2-icon-dark-shading
       (filled-polygon ((47 3) (50 0) (50 50) (0 50) (3 47) (47 47))
		       ((47 3) (50 0) (50 50))
		       ((50 50) (0 50) (3 47))
		       ((47 47) (47 3) (50 50))
		       ((50 50) (3 47) (47 47)))
       (lines (10 40) (10 10) (40 10))
       icon-color
       (outline (0 0) (0 50) (50 50) (50 0))
       (lines (44 5) (5 5) (5 45))
       g2-icon-light-shading
       (lines (5 45) (44 45) (44 5)))))
  (resource-definition
    nil (type resource-definition text) vector-slot
    system save do-not-identify-in-attribute-tables
    do-not-clone)
  (resource-are-obsolete-please-convert-me
    nil
    (type free text))
  (resource-compilation
    nil vector-slot system)
  )

|#

;;; Delete me before beta of 5.0

(def-substitute-for-old-class resource tw-resource 257)

(def-slot-value-reclaimer resource-compilation (list-of-compiled-resources resource)
  (declare (ignore resource))
  (loop for compiled-resource-tail on list-of-compiled-resources
	do
    (reclaim-compiled-resource (car-of-cons compiled-resource-tail)))
  (reclaim-slot-value-list list-of-compiled-resources))

(def-slot-putter resource-definition (resource
					compiled-resource-definition
					initializing-p)
  (declare (ignore initializing-p))
  (setf (resource-definition resource) compiled-resource-definition)
  (change-slot-value resource
		     'resource-compilation
		     (make-compiled-resources 
		       (car compiled-resource-definition))))

;; derived from winnt.h in the Microshortz #include files

(defmacro make-wind32-language-id (primary secondary)
  `(logiorf ,primary (ashf ,secondary 10)))

(defun make-compiled-resources (resource-definition)
  (loop with most-recent-language = 0 ; per win32 decree
	with compiled-resources = nil
        for resource-spec in resource-definition
	as (native-p type id type-specific-data) = resource-spec
	as compiled-resource
	   = (and (not (or (eq type 'stringtable)  ; note A
			   (eq type 'language)))   
		  (make-compiled-resource
		    (if (eq native-p 'win32) t nil)
		    type id most-recent-language))
	do
    (when compiled-resource
      (slot-value-push compiled-resource compiled-resources))
    (ecase type
      
      (accelerators
       ;; where in the structure should the accel contents go? !!
       ;; this is my best guess  -jtidwell 6/4/96
       (setf (compiled-resource-properties compiled-resource)
	     (slot-value-list
	       :contents (copy-for-slot-value
			   (parsed-resource-contents resource-spec))))
       (add-optional-statements-to-compiled-resource
	 compiled-resource resource-spec))
       ;; add accelerator-table
      
      ((bitmap cursor font)
       (add-load-mem-options-to-compiled-resource
	 compiled-resource (parsed-resource-property resource-spec 'loadmem))
       (setf (compiled-resource-properties compiled-resource)
	     (slot-value-list
	       :filename
	       (copy-tree-for-compiled-resource
		 (parsed-resource-property resource-spec 'filename)))))

      ;; any kind of dialog, plus some other things
      ((dialog dialogex tw-dialog tw-tabbed-dialog tw-frame tw-status-bar)
       (add-load-mem-options-to-compiled-resource
	 compiled-resource
	 (parsed-resource-property resource-spec 'loadmem))
       (setf (compiled-resource-properties compiled-resource)
	     (slot-value-list
	       :contents (copy-for-slot-value
			   (parsed-resource-contents resource-spec))
	       :help-id (parsed-resource-property resource-spec 'help-id)))
       (add-coordinates-to-compiled-resource
	 compiled-resource
	 (parsed-resource-property resource-spec 'x)
	 (parsed-resource-property resource-spec 'y)
	 (parsed-resource-property resource-spec 'width)
	 (parsed-resource-property resource-spec 'height))
       (add-optional-statements-to-compiled-resource
	 compiled-resource resource-spec))

      (language-statement
       (setf most-recent-language
	     (make-wind32-language-id
	       (parsed-resource-property resource-spec 'primary)
	       (parsed-resource-property resource-spec 'secondary))))

      ((menu tw-menu)
       (add-load-mem-options-to-compiled-resource
	 compiled-resource
	 (parsed-resource-property resource-spec 'loadmem))
       (setf (compiled-resource-properties compiled-resource)
	     (slot-value-list
	       :contents (copy-for-slot-value
			     (parsed-resource-contents resource-spec))))
       (add-optional-statements-to-compiled-resource
	 compiled-resource resource-spec))
	 
      (stringtable
       (let ((string-specs (parsed-resource-contents resource-spec)))
	 (loop for (resource-name string) in string-specs
	       as compiled-resource = (make-compiled-resource
					'win32 'string resource-name most-recent-language)
	       do
	   (slot-value-push compiled-resource compiled-resources)
	   (setf (compiled-resource-properties compiled-resource)
		 (slot-value-list
		   :text (copy-text-string string)))
	   (add-load-mem-options-to-compiled-resource
	     compiled-resource
	     (parsed-resource-property resource-spec 'loadmem))
	   (add-optional-statements-to-compiled-resource
	     compiled-resource resource-spec)))))

	finally
	  (return compiled-resources)))

;; Note A: languages and string tables are not really resources in the sense
;; that they can be found and instantiated at run time.  Languages affect
;; the interpretation of other resourcs.  Stringtables are sets of resources
;; that are used individually at run-time and have unique ids.  Their grouping
;; in RC files is for convenience and perhaps to aid their memory management in
;; Windows.


(defun copy-tree-for-compiled-resource (tree)
  (copy-for-slot-value tree))

#+obsolete
(defun copy-tree-for-compiled-resource (tree)
  (format t "tree=~s~%" tree)
  (cond
    ((or (symbolp tree)
	 (fixnump tree))
     tree)
    ((managed-float-p tree)
     (copy-managed-float tree))
    ((consp tree)
     (gensym-cons
       (copy-tree-for-compiled-resource (car-of-cons tree))
       (copy-tree-for-compiled-resource (cdr-of-cons tree))))
    ((text-string-p tree)
     (copy-text-string tree))
    (t
     (error "unexpected element in compiled-resource tree"))))
	   
(defun add-load-mem-options-to-compiled-resource (compiled-resource load-mem-options)
  (setf (compiled-resource-load-option compiled-resource) (car load-mem-options)
	(compiled-resource-memory-options compiled-resource)
	(copy-list-using-slot-value-conses (cadr load-mem-options))))

(defun add-coordinates-to-compiled-resource (compiled-resource x y w h)
  (setf (compiled-resource-properties compiled-resource)
	(nconc (slot-value-list :x x :y y :width w :height h)
	       (compiled-resource-properties compiled-resource))))

(defun add-optional-statements-to-compiled-resource (compiled-resource resource-spec)
  (let ((caption (parsed-resource-property resource-spec 'caption))
	(characteristics (parsed-resource-property resource-spec 'characteristics))
	(class (parsed-resource-property resource-spec 'class))
	(font (parsed-resource-property resource-spec 'font))
	(language (parsed-resource-property resource-spec 'language))
	(style (parsed-resource-property resource-spec 'style))
	;; (exstyle (parsed-resource-property resource-spec 'exstyle))
	;; (version (parsed-resource-property resource-spec 'version))
	(subclass (parsed-resource-property resource-spec 'subclass))
	(attributes (parsed-resource-property resource-spec 'attributes))
	)
    (if caption
	(nconc (compiled-resource-properties compiled-resource)
	       (slot-value-list
		 :caption (copy-text-string caption))))
    (if characteristics
	(nconc (compiled-resource-properties compiled-resource)
	       (slot-value-list
		 :characteristics (copy-for-slot-value characteristics))))
    (if class
	(nconc (compiled-resource-properties compiled-resource)
	       (slot-value-list
		 :class (copy-for-slot-value class))))
    (if font
	(nconc (compiled-resource-properties compiled-resource)
	       (slot-value-list
		 :font (copy-for-slot-value font))))
    (if language
       (setf (compiled-resource-language compiled-resource)
	     (make-wind32-language-id language (cadr language))))
    (if style
	(nconc (compiled-resource-properties compiled-resource)
	       (slot-value-list
		 :style	(copy-for-slot-value style))))
    (if subclass
	(nconc (compiled-resource-properties compiled-resource)
	       (slot-value-list
		 :subclass (copy-for-slot-value subclass))))
    (if attributes
	(nconc (compiled-resource-properties compiled-resource)
	       (slot-value-list
		 :attributes (copy-for-slot-value attributes))))
    ))
      

(defun-for-system-procedure g2-new-resource (workspace g2-window)
  (let ((image-plane (map-to-image-plane-or-stack-error
		       workspace g2-window))
	;; guarded by previous form
	(workstation (workstation-for-g2-window? g2-window)))
    (for-workstation (workstation)
      (manifest-item-creation
	(make-entity 'tw-resource)
	image-plane
	(x-in-window-for-image-plane
	  (item-x-position workspace) image-plane)
	(y-in-window-for-image-plane
	  (item-y-position workspace) image-plane)))))

