(BIND ELT-TYPE
      (ALT FLOAT
	   INTEGER
	   QUANTITY
	   TEXT
	   SYMBOL))

("com.gensym.gcg.TextFieldEditorBuilder" ELT-TYPE)


(OR NO-ITEM
    (BIND ELT-TYPE
	  (ALT FLOAT
	       INTEGER
	       QUANTITY
	       TEXT
	       SYMBOL)))

("com.gensym.gcg.TextFieldEditorBuilder" ELT-TYPE true)


(BIND MEMBER-TYPE 
      (MEMBER (ANY
	       (BIND ELT-TYPE
		     (ALT FLOAT
			  INTEGER
			  QUANTITY
			  TEXT
			  SYMBOL)))))

("com.gensym.gcg.ChoiceEditorBuilder" MEMBER-TYPE ELT-TYPE)


TRUTH-VALUE

("com.gensym.gcg.CheckboxEditorBuilder" )


(BIND ELT-TYPE
      (ALT (EXACTLY VALUE)
	   (EXACTLY ITEM-OR-VALUE)))

("com.gensym.gcg.TextFieldEditorBuilder" ELT-TYPE)


(OR NO-ITEM
    (BIND ELT-TYPE
	  (ALT (EXACTLY VALUE)
	       (EXACTLY ITEM-OR-VALUE))))

("com.gensym.gcg.TextFieldEditorBuilder" ELT-TYPE true)
