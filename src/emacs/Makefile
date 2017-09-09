EMACS=xemacs

# use "make compile" to regenerate /home/development/emacs byte compiled files,
# after doing cvs update in that directory as user ab.  Not sure what "comp" is

compile:
	$(EMACS) -batch -l gensym-make.el

comp:
	$(EMACS) -batch -f batch-byte-compile *.el

tags:
	etags *.el emacs-link/*/*.el

clean:
	/bin/rm -f *.elc
