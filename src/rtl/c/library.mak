
#############################################################################
#
#   Include file for Chestnut Run-Time Library Makefile
#   Produced automatically by running 
#     % write-make <this-file-name>
#
#   Copyright (c) 1990-1992 Chestnut Software, Inc.  All Rights Reserved.
#   Use of this file is subject to the terms of a license from
#   Chestnut Software, Inc.  Please refer to the License for details.
#
############################################################################
# Notes:
#
# ALL dependencies on .h files are specified for every .c
# The files composed in several separate lists for portability reasons
#
#############################################################################


# Runtime   files

LIBOBJECTS1  = \
$(libbin)/acons.o\
$(libbin)/adjoin.o\
$(libbin)/adjsblp.o\
$(libbin)/adjstrry.o\
$(libbin)/admnsns.o\
$(libbin)/advncpcg.o\
$(libbin)/allcmmg.o\
$(libbin)/alphchrp.o\
$(libbin)/alpnmrcp.o\
$(libbin)/amjndx.o\
$(libbin)/anbndsp.o\
$(libbin)/append.o\
$(libbin)/append2.o\
$(libbin)/apply.o\
$(libbin)/apply1.o\
$(libbin)/apply2.o\
$(libbin)/apply3.o\
$(libbin)/aref.o\
$(libbin)/aref0.o\
$(libbin)/aref1.o\
$(libbin)/aref2.o\
$(libbin)/aref3.o\
$(libbin)/aref4.o\
$(libbin)/aref5.o\
$(libbin)/aref6.o\
$(libbin)/aref7.o

# Runtime   files

LIBOBJECTS2  = \
$(libbin)/armmrlmt.o\
$(libbin)/armmrysd.o\
$(libbin)/arrayp.o\
$(libbin)/arrdmnsn.o\
$(libbin)/arrttlsz.o\
$(libbin)/arryrnk.o\
$(libbin)/artrgtsz.o\
$(libbin)/asllpnp.o\
$(libbin)/asscifnt.o\
$(libbin)/assoc.o\
$(libbin)/assoc_eq.o\
$(libbin)/assoc_if.o\
$(libbin)/assoceql.o\
$(libbin)/assocqul.o\
$(libbin)/assq.o\
$(libbin)/atom.o\
$(libbin)/avncmbl.o\
$(libbin)/bgintim.o\
$(libbin)/bignump.o\
$(libbin)/bitp.o\
$(libbin)/bitvctrp.o\
$(libbin)/bothcsep.o\
$(libbin)/boundp.o\
$(libbin)/butlast.o\
$(libbin)/caaaar.o\
$(libbin)/caaadr.o

# Runtime   files

LIBOBJECTS3  = \
$(libbin)/caaar.o\
$(libbin)/caadar.o\
$(libbin)/caaddr.o\
$(libbin)/caadr.o\
$(libbin)/caar.o\
$(libbin)/cadaar.o\
$(libbin)/cadadr.o\
$(libbin)/cadar.o\
$(libbin)/caddar.o\
$(libbin)/cadddr.o\
$(libbin)/caddr.o\
$(libbin)/cadr.o\
$(libbin)/car.o\
$(libbin)/ccl.o\
$(libbin)/cdaaar.o\
$(libbin)/cdaadr.o\
$(libbin)/cdaar.o\
$(libbin)/cdadar.o\
$(libbin)/cdaddr.o\
$(libbin)/cdadr.o\
$(libbin)/cdar.o\
$(libbin)/cdbltdbl.o\
$(libbin)/cddaar.o\
$(libbin)/cddadr.o\
$(libbin)/cddar.o\
$(libbin)/cdddar.o

# Runtime   files

LIBOBJECTS4  = \
$(libbin)/cddddr.o\
$(libbin)/cdddr.o\
$(libbin)/cddr.o\
$(libbin)/cdr.o\
$(libbin)/char_bit.o\
$(libbin)/char_eq.o\
$(libbin)/char_eqn.o\
$(libbin)/char_eqr.o\
$(libbin)/char_ge.o\
$(libbin)/char_gen.o\
$(libbin)/char_ger.o\
$(libbin)/char_gt.o\
$(libbin)/char_gtn.o\
$(libbin)/char_gtr.o\
$(libbin)/char_int.o\
$(libbin)/char_le.o\
$(libbin)/char_len.o\
$(libbin)/char_ler.o\
$(libbin)/char_lt.o\
$(libbin)/char_ltn.o\
$(libbin)/char_ltr.o\
$(libbin)/char_ne.o\
$(libbin)/char_nen.o\
$(libbin)/char_ner.o\
$(libbin)/charbits.o\
$(libbin)/charcode.o

# Runtime   files

LIBOBJECTS5  = \
$(libbin)/charfont.o\
$(libbin)/charname.o\
$(libbin)/chrcter.o\
$(libbin)/chrcterp.o\
$(libbin)/chrdwncs.o\
$(libbin)/chrequl.o\
$(libbin)/chrequln.o\
$(libbin)/chrequlr.o\
$(libbin)/chrgrtrp.o\
$(libbin)/chrlessp.o\
$(libbin)/chrlsspn.o\
$(libbin)/chrlsspr.o\
$(libbin)/chrmmbr.o\
$(libbin)/chrntqln.o\
$(libbin)/chrntqlr.o\
$(libbin)/chrntqul.o\
$(libbin)/chrupcse.o\
$(libbin)/cllc.o\
$(libbin)/clrinput.o\
$(libbin)/clrutput.o\
$(libbin)/cmplmnnl.o\
$(libbin)/cmplncnp.o\
$(libbin)/cnnlnncn.o\
$(libbin)/cnsnlfls.o\
$(libbin)/cnsnlndl.o\
$(libbin)/cnsnlr.o

# Runtime   files

LIBOBJECTS6  = \
$(libbin)/cobjectp.o\
$(libbin)/codechar.o\
$(libbin)/coerce.o\
$(libbin)/commonp.o\
$(libbin)/complexp.o\
$(libbin)/conctnt.o\
$(libbin)/consp.o\
$(libbin)/copy_seq.o\
$(libbin)/copylist.o\
$(libbin)/copytree.o\
$(libbin)/count.o\
$(libbin)/count_if.o\
$(libbin)/cp_alist.o\
$(libbin)/cpfptr.o\
$(libbin)/cpysymbl.o\
$(libbin)/crgrtrpn.o\
$(libbin)/crgrtrpr.o\
$(libbin)/crngrrp.o\
$(libbin)/crngrrpn.o\
$(libbin)/crngrrpr.o\
$(libbin)/crnlsspn.o\
$(libbin)/crnlsspr.o\
$(libbin)/crntlssp.o\
$(libbin)/csnpsrm.o\
$(libbin)/cspsrm.o\
$(libbin)/cswrsrm.o

# Runtime   files

LIBOBJECTS7  = \
$(libbin)/cuntifnt.o\
$(libbin)/dbltntgr.o\
$(libbin)/dcdnvslm.o\
$(libbin)/dcnmsng.o\
$(libbin)/defftp.o\
$(libbin)/deleteeq.o\
$(libbin)/deleteif.o\
$(libbin)/delq.o\
$(libbin)/describe.o\
$(libbin)/dgtchrp.o\
$(libbin)/digitchr.o\
$(libbin)/dirctory.o\
$(libbin)/dldplcs.o\
$(libbin)/dltfil.o\
$(libbin)/dltifnot.o\
$(libbin)/dltql.o\
$(libbin)/dltqul.o\
$(libbin)/doaref1.o\
$(libbin)/dormovif.o\
$(libbin)/dostfrf.o\
$(libbin)/drmfrrr.o\
$(libbin)/eighth.o\
$(libbin)/encnvslm.o\
$(libbin)/endp.o\
$(libbin)/engnmsng.o\
$(libbin)/eq.o

# Runtime   files

LIBOBJECTS8  = \
$(libbin)/eql.o\
$(libbin)/equal.o\
$(libbin)/equalp.o\
$(libbin)/faref.o\
$(libbin)/fifth.o\
$(libbin)/fill.o\
$(libbin)/fillngth.o\
$(libbin)/filuthor.o\
$(libbin)/find.o\
$(libbin)/find_if.o\
$(libbin)/findifnt.o\
$(libbin)/first.o\
$(libbin)/fixnump.o\
$(libbin)/flatsize.o\
$(libbin)/fllpntr.o\
$(libbin)/flnmsrng.o\
$(libbin)/floatp.o\
$(libbin)/flpstn.o\
$(libbin)/flwrtdt.o\
$(libbin)/fnllmbl.o\
$(libbin)/fnshtm.o\
$(libbin)/fnshtpt.o\
$(libbin)/forptrp.o\
$(libbin)/forptrtp.o\
$(libbin)/fortype.o\
$(libbin)/fortypep.o

# Runtime   files

LIBOBJECTS9  = \
$(libbin)/forval.o\
$(libbin)/fourth.o\
$(libbin)/fpaddr.o\
$(libbin)/fptype.o\
$(libbin)/frcutput.o\
$(libbin)/frfptr.o\
$(libbin)/frshlin.o\
$(libbin)/fsizeof.o\
$(libbin)/fstrval.o\
$(libbin)/ftmod.o\
$(libbin)/ftname.o\
$(libbin)/ftrem.o\
$(libbin)/ftsize.o\
$(libbin)/ftypep.o\
$(libbin)/funcall.o\
$(libbin)/funcall3.o\
$(libbin)/functinp.o\
$(libbin)/gensym.o\
$(libbin)/gentemp.o\
$(libbin)/get.o\
$(libbin)/getf.o\
$(libbin)/gnrnlrlm.o\
$(libbin)/gnrnlrnm.o\
$(libbin)/gnvrslm.o\
$(libbin)/grpccrp.o\
$(libbin)/gtdcddtm.o

# Runtime   files

LIBOBJECTS10  = \
$(libbin)/gtprprts.o\
$(libbin)/hsnmsrng.o\
$(libbin)/ichrnme.o\
$(libbin)/identity.o\
$(libbin)/igglg.o\
$(libbin)/ilzxlbl.o\
$(libbin)/immedite.o\
$(libbin)/ingrlng.o\
$(libbin)/inlzllbl.o\
$(libbin)/inlzmbl.o\
$(libbin)/inlzpckg.o\
$(libbin)/innlmkp.o\
$(libbin)/inspect.o\
$(libbin)/int_char.o\
$(libbin)/integerp.o\
$(libbin)/intrsctn.o\
$(libbin)/invldmd.o\
$(libbin)/invlncnn.o\
$(libbin)/ismblnm.o\
$(libbin)/isngsng.o\
$(libbin)/isngsngn.o\
$(libbin)/keywordp.o\
$(libbin)/last.o\
$(libbin)/ldelete.o\
$(libbin)/ldiff.o\
$(libbin)/lgclpnmp.o\
$(libbin)/list.o

# Runtime   files

LIBOBJECTS11  = \
$(libbin)/listp.o\
$(libbin)/listrvrs.o\
$(libbin)/liststar.o\
$(libbin)/listvlus.o\
$(libbin)/llisten.o\
$(libbin)/lmlmnn.o\
$(libbin)/lmlmnnvn.o\
$(libbin)/load.o\
$(libbin)/load_run.o\
$(libbin)/lopen.o\
$(libbin)/lowrcsp.o\
$(libbin)/lremove.o\
$(libbin)/lsleep.o\
$(libbin)/lstlngth.o\
$(libbin)/lstnrvrs.o\
$(libbin)/lunion.o\
$(libbin)/m_nthcdr.o\
$(libbin)/makechar.o\
$(libbin)/makelist.o\
$(libbin)/map.o\
$(libbin)/map_into.o\
$(libbin)/mcfptr.o\
$(libbin)/mchintyp.o\
$(libbin)/mchnvrsn.o\
$(libbin)/mcnnstnc.o\
$(libbin)/mdcmbnn.o

# Runtime   files

LIBOBJECTS12  = \
$(libbin)/member.o\
$(libbin)/membereq.o\
$(libbin)/memberif.o\
$(libbin)/memberse.o\
$(libbin)/memq.o\
$(libbin)/merge.o\
$(libbin)/mismatch.o\
$(libbin)/mkarrlt.o\
$(libbin)/mkcomplx.o\
$(libbin)/mkfptr.o\
$(libbin)/mkfptri.o\
$(libbin)/mkpthnm.o\
$(libbin)/mkscnsnc.o\
$(libbin)/mksqunc.o\
$(libbin)/mksymbol.o\
$(libbin)/mkunbund.o\
$(libbin)/mkvctor.o\
$(libbin)/mkvlucll.o\
$(libbin)/mlplvlln.o\
$(libbin)/mmbrifnt.o\
$(libbin)/mmbrodd.o\
$(libbin)/mmbrql.o\
$(libbin)/mmbrqul.o\
$(libbin)/mrgptnms.o\
$(libbin)/mspcmccc.o\
$(libbin)/mvsn.o\
$(libbin)/namechar.o

# Runtime   files

LIBOBJECTS13  = \
$(libbin)/nbutlast.o\
$(libbin)/nconc.o\
$(libbin)/nconc2.o\
$(libbin)/ncons.o\
$(libbin)/ncons1.o\
$(libbin)/ninth.o\
$(libbin)/nmstring.o\
$(libbin)/nntrsctn.o\
$(libbin)/not.o\
$(libbin)/nreconc.o\
$(libbin)/nreverse.o\
$(libbin)/nsbsfn.o\
$(libbin)/nsbstfnt.o\
$(libbin)/nsbsttt.o\
$(libbin)/nsbstttf.o\
$(libbin)/nsdffrnc.o\
$(libbin)/nsngcplz.o\
$(libbin)/nsngdncs.o\
$(libbin)/nsrngpcs.o\
$(libbin)/nsublis.o\
$(libbin)/nsubst.o\
$(libbin)/nsubstif.o\
$(libbin)/nsxclsvr.o\
$(libbin)/nth.o\
$(libbin)/nthcdr.o\
$(libbin)/null.o

# Runtime   files

LIBOBJECTS14  = \
$(libbin)/numberp.o\
$(libbin)/nunion.o\
$(libbin)/objccdbl.o\
$(libbin)/packagep.o\
$(libbin)/pairlis.o\
$(libbin)/pathname.o\
$(libbin)/pctpintr.o\
$(libbin)/peekchar.o\
$(libbin)/pnmdrcr.o\
$(libbin)/position.o\
$(libbin)/pprint.o\
$(libbin)/prin1.o\
$(libbin)/princ.o\
$(libbin)/print.o\
$(libbin)/prmpfrvl.o\
$(libbin)/prn1srng.o\
$(libbin)/prncsrng.o\
$(libbin)/probfil.o\
$(libbin)/proclaim.o\
$(libbin)/progv_do.o\
$(libbin)/prsintgr.o\
$(libbin)/psitinif.o\
$(libbin)/psnmsng.o\
$(libbin)/pstnfnt.o\
$(libbin)/pthnmdvc.o\
$(libbin)/pthnmep.o

# Runtime   files

LIBOBJECTS15  = \
$(libbin)/pthnmhst.o\
$(libbin)/pthnmnm.o\
$(libbin)/pthnmtyp.o\
$(libbin)/ptnmvrsn.o\
$(libbin)/rassoc.o\
$(libbin)/rassocif.o\
$(libbin)/ratiop.o\
$(libbin)/rdcrnng.o\
$(libbin)/rdrmsrng.o\
$(libbin)/readbyte.o\
$(libbin)/readchar.o\
$(libbin)/readline.o\
$(libbin)/realp.o\
$(libbin)/reduce.o\
$(libbin)/remprop.o\
$(libbin)/replace.o\
$(libbin)/rest.o\
$(libbin)/reverse.o\
$(libbin)/revppend.o\
$(libbin)/rmvdplcs.o\
$(libbin)/rnmfil.o\
$(libbin)/room.o\
$(libbin)/rplaca.o\
$(libbin)/rplacd.o\
$(libbin)/rsscifnt.o\
$(libbin)/rtionlp.o

# Runtime   files

LIBOBJECTS16  = \
$(libbin)/rwmjrrf.o\
$(libbin)/s_fill_n.o\
$(libbin)/s_find_n.o\
$(libbin)/s_load_n.o\
$(libbin)/sadjoinn.o\
$(libbin)/sassocn.o\
$(libbin)/sbgnmdg.o\
$(libbin)/sbnrsls.o\
$(libbin)/sbsfn.o\
$(libbin)/sbstttf.o\
$(libbin)/scgnrlrr.o\
$(libbin)/schar.o\
$(libbin)/schrrlop.o\
$(libbin)/schrrlpn.o\
$(libbin)/scngvbgn.o\
$(libbin)/scnswtgc.o\
$(libbin)/scntfntn.o\
$(libbin)/scountn.o\
$(libbin)/scpvbgnm.o\
$(libbin)/scuntifn.o\
$(libbin)/sdeleten.o\
$(libbin)/sdjstrrn.o\
$(libbin)/sdltfntn.o\
$(libbin)/sdltif.o\
$(libbin)/sdltifn.o\
$(libbin)/sdmsngn.o

# Runtime   files

LIBOBJECTS17  = \
$(libbin)/search.o\
$(libbin)/second.o\
$(libbin)/set.o\
$(libbin)/set_char.o\
$(libbin)/set_cxr.o\
$(libbin)/set_get.o\
$(libbin)/set_getf.o\
$(libbin)/set_nth.o\
$(libbin)/set_rest.o\
$(libbin)/setaref0.o\
$(libbin)/setaref1.o\
$(libbin)/setaref2.o\
$(libbin)/setaref3.o\
$(libbin)/setaref4.o\
$(libbin)/setaref5.o\
$(libbin)/setaref6.o\
$(libbin)/setaref7.o\
$(libbin)/setf_bit.o\
$(libbin)/setfaref.o\
$(libbin)/setfifth.o\
$(libbin)/setfirst.o\
$(libbin)/setfsbit.o\
$(libbin)/setninth.o\
$(libbin)/setpckge.o\
$(libbin)/setschar.o\
$(libbin)/setsixth.o

# Runtime   files

LIBOBJECTS18  = \
$(libbin)/setsvref.o\
$(libbin)/settenth.o\
$(libbin)/setthird.o\
$(libbin)/seventh.o\
$(libbin)/sfaref.o\
$(libbin)/sffllpnr.o\
$(libbin)/sfindifn.o\
$(libbin)/sfllfntn.o\
$(libbin)/sfllpnr.o\
$(libbin)/sfndfntn.o\
$(libbin)/sforval.o\
$(libbin)/sfpaddr.o\
$(libbin)/sfptype.o\
$(libbin)/sfstrval.o\
$(libbin)/sfwrvrsn.o\
$(libbin)/sgvvbnng.o\
$(libbin)/shrtstnm.o\
$(libbin)/si_throw.o\
$(libbin)/sinpckgn.o\
$(libbin)/sixth.o\
$(libbin)/skwrdrgp.o\
$(libbin)/slclosen.o\
$(libbin)/slodrunn.o\
$(libbin)/slopenn.o\
$(libbin)/slplcsn.o\
$(libbin)/slunionn.o

# Runtime   files

LIBOBJECTS19  = \
$(libbin)/slwriten.o\
$(libbin)/smblfncn.o\
$(libbin)/smblplst.o\
$(libbin)/smblvllp.o\
$(libbin)/smembern.o\
$(libbin)/smergen.o\
$(libbin)/smjndxx.o\
$(libbin)/smkerryn.o\
$(libbin)/smklistn.o\
$(libbin)/smkpckgn.o\
$(libbin)/smkptnmn.o\
$(libbin)/smkrstrg.o\
$(libbin)/smkscrr.o\
$(libbin)/smksqncn.o\
$(libbin)/smksrngn.o\
$(libbin)/smkstbln.o\
$(libbin)/smmbrfnn.o\
$(libbin)/smmbrifn.o\
$(libbin)/smplbvcp.o\
$(libbin)/smplrryp.o\
$(libbin)/smplsngp.o\
$(libbin)/smplvcrp.o\
$(libbin)/smsmtchn.o\
$(libbin)/smvfncll.o\
$(libbin)/smvplcsn.o\
$(libbin)/snbnnjmp.o

# Runtime   files

LIBOBJECTS20  = \
$(libbin)/snddbjcp.o\
$(libbin)/sndrdcrp.o\
$(libbin)/sngcplzn.o\
$(libbin)/snglpn.o\
$(libbin)/sngnlpn.o\
$(libbin)/sngppnd2.o\
$(libbin)/sngppndn.o\
$(libbin)/snngclzn.o\
$(libbin)/snngncn.o\
$(libbin)/snngpcn.o\
$(libbin)/snnlncll.o\
$(libbin)/snnrscnn.o\
$(libbin)/snpngng.o\
$(libbin)/snpngngs.o\
$(libbin)/snrscnn.o\
$(libbin)/snsbsfn.o\
$(libbin)/snsbsfnn.o\
$(libbin)/snsbsn.o\
$(libbin)/snsbstfn.o\
$(libbin)/snsdrncn.o\
$(libbin)/snslngnn.o\
$(libbin)/snsqncfn.o\
$(libbin)/snsublsn.o\
$(libbin)/snsubstn.o\
$(libbin)/sntmisc.o\
$(libbin)/snunionn.o

# Runtime   files

LIBOBJECTS21  = \
$(libbin)/snxclvn.o\
$(libbin)/some.o\
$(libbin)/sort.o\
$(libbin)/spgvbnng.o\
$(libbin)/spnmngn.o\
$(libbin)/sprsngrn.o\
$(libbin)/spsitinn.o\
$(libbin)/spsnfnn.o\
$(libbin)/spstnfn.o\
$(libbin)/squncp.o\
$(libbin)/srassocn.o\
$(libbin)/srcrbjcp.o\
$(libbin)/sreducen.o\
$(libbin)/sremoven.o\
$(libbin)/sreplcen.o\
$(libbin)/srethrow.o\
$(libbin)/srmovifn.o\
$(libbin)/srmvfntn.o\
$(libbin)/srngcplz.o\
$(libbin)/srngdncs.o\
$(libbin)/srngppnd.o\
$(libbin)/srrcnns.o\
$(libbin)/srsscfnn.o\
$(libbin)/srsscifn.o\
$(libbin)/srstrvls.o\
$(libbin)/srwmjrrf.o

# Runtime   files

LIBOBJECTS22  = \
$(libbin)/ssbsfn.o\
$(libbin)/ssbsfnn.o\
$(libbin)/ssbstttn.o\
$(libbin)/ssdrncn.o\
$(libbin)/ssearchn.o\
$(libbin)/ssffncn.o\
$(libbin)/ssmblncn.o\
$(libbin)/ssmblpls.o\
$(libbin)/ssnggpn.o\
$(libbin)/ssngncsn.o\
$(libbin)/ssngngpn.o\
$(libbin)/ssngnqln.o\
$(libbin)/ssngpcsn.o\
$(libbin)/ssrnggn.o\
$(libbin)/ssrngln.o\
$(libbin)/ssrngqln.o\
$(libbin)/ssrnpqr.o\
$(libbin)/ssscfntn.o\
$(libbin)/sssmblld.o\
$(libbin)/sssocifn.o\
$(libbin)/sstrmgtc.o\
$(libbin)/sstrnggn.o\
$(libbin)/sstrngln.o\
$(libbin)/sstrngnn.o\
$(libbin)/sstrngqn.o\
$(libbin)/ssublisn.o

# Runtime   files

LIBOBJECTS23  = \
$(libbin)/ssubstfn.o\
$(libbin)/ssubstn.o\
$(libbin)/ssubstpn.o\
$(libbin)/ssvmrvls.o\
$(libbin)/ssvvlus.o\
$(libbin)/ssxclsvn.o\
$(libbin)/statclst.o\
$(libbin)/statlsts.o\
$(libbin)/statobjp.o\
$(libbin)/stdffrnc.o\
$(libbin)/stfaref.o\
$(libbin)/stffnctn.o\
$(libbin)/stfourth.o\
$(libbin)/stighth.o\
$(libbin)/streamp.o\
$(libbin)/string.o\
$(libbin)/stringp.o\
$(libbin)/strngcrp.o\
$(libbin)/strngpcs.o\
$(libbin)/strquln.o\
$(libbin)/stscond.o\
$(libbin)/stsubsq.o\
$(libbin)/stsubsq1.o\
$(libbin)/stsubsq2.o\
$(libbin)/stsvnth.o\
$(libbin)/sttcrr.o\
$(libbin)/sttcbtrr.o\
$(libbin)/sttccrrr.o

# Runtime   files

LIBOBJECTS24  = \
$(libbin)/sttcflot.o\
$(libbin)/sttcpckg.o\
$(libbin)/sttcrto.o\
$(libbin)/sttcsmbl.o\
$(libbin)/stxclsvr.o\
$(libbin)/sublis.o\
$(libbin)/subseq.o\
$(libbin)/subsetp.o\
$(libbin)/subst.o\
$(libbin)/subst_if.o\
$(libbin)/substfnt.o\
$(libbin)/substtut.o\
$(libbin)/subtypep.o\
$(libbin)/svref.o\
$(libbin)/swrsrngn.o\
$(libbin)/swrtlnn.o\
$(libbin)/swrtstng.o\
$(libbin)/symblvlu.o\
$(libbin)/symbolnm.o\
$(libbin)/symbolp.o\
$(libbin)/tailp.o\
$(libbin)/tenth.o\
$(libbin)/terpri.o\
$(libbin)/tfaref.o\
$(libbin)/third.o\
$(libbin)/tlllcbl.o

# Runtime   files

LIBOBJECTS25  = \
$(libbin)/treeequl.o\
$(libbin)/ttlmmrsd.o\
$(libbin)/type_of.o\
$(libbin)/typep.o\
$(libbin)/unquetag.o\
$(libbin)/unredchr.o\
$(libbin)/upprcsp.o\
$(libbin)/upstpckg.o\
$(libbin)/usmdpnm.o\
$(libbin)/values.o\
$(libbin)/vcrpsxnd.o\
$(libbin)/vctorpop.o\
$(libbin)/vctrpush.o\
$(libbin)/vector.o\
$(libbin)/vectorp.o\
$(libbin)/vluslist.o\
$(libbin)/writbyt.o\
$(libbin)/writechr.o\
$(libbin)/writlin.o\
$(libbin)/wrtstrng.o\
$(libbin)/wtspccrp.o\
$(libbin)/xor.o\
$(libbin)/y_or_n_p.o\
$(libbin)/yesnoaux.o\
$(libbin)/yesornop.o\
$(libbin)/yornpn.o

# Runtime   files

LIBOBJECTS26  = \
$(libbin)/ysornopn.o

# 
# a separate goal to add files to archive 
# provided for each group for better portability concerns
# 
libgoal1 : $(LIBOBJECTS1) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal2 : $(LIBOBJECTS2) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal3 : $(LIBOBJECTS3) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal4 : $(LIBOBJECTS4) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal5 : $(LIBOBJECTS5) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal6 : $(LIBOBJECTS6) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal7 : $(LIBOBJECTS7) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal8 : $(LIBOBJECTS8) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal9 : $(LIBOBJECTS9) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal10 : $(LIBOBJECTS10) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal11 : $(LIBOBJECTS11) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal12 : $(LIBOBJECTS12) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal13 : $(LIBOBJECTS13) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal14 : $(LIBOBJECTS14) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal15 : $(LIBOBJECTS15) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal16 : $(LIBOBJECTS16) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal17 : $(LIBOBJECTS17) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal18 : $(LIBOBJECTS18) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal19 : $(LIBOBJECTS19) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal20 : $(LIBOBJECTS20) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal21 : $(LIBOBJECTS21) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal22 : $(LIBOBJECTS22) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal23 : $(LIBOBJECTS23) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal24 : $(LIBOBJECTS24) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal25 : $(LIBOBJECTS25) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal26 : $(LIBOBJECTS26) 
	$(CLINK) $(LIBPLACE)/$(library).a $?

libgoal_end : 

LIBGOALS = \
libgoal1 \
libgoal2 \
libgoal3 \
libgoal4 \
libgoal5 \
libgoal6 \
libgoal7 \
libgoal8 \
libgoal9 \
libgoal10 \
libgoal11 \
libgoal12 \
libgoal13 \
libgoal14 \
libgoal15 \
libgoal16 \
libgoal17 \
libgoal18 \
libgoal19 \
libgoal20 \
libgoal21 \
libgoal22 \
libgoal23 \
libgoal24 \
libgoal25 \
libgoal26 \
libgoal_end

#if make complains: delete LIBOBJECTS and use file small.mak instead of Makefile: 
LIBOBJECTS= \
$(LIBOBJECTS1) \
$(LIBOBJECTS2) \
$(LIBOBJECTS3) \
$(LIBOBJECTS4) \
$(LIBOBJECTS5) \
$(LIBOBJECTS6) \
$(LIBOBJECTS7) \
$(LIBOBJECTS8) \
$(LIBOBJECTS9) \
$(LIBOBJECTS10) \
$(LIBOBJECTS11) \
$(LIBOBJECTS12) \
$(LIBOBJECTS13) \
$(LIBOBJECTS14) \
$(LIBOBJECTS15) \
$(LIBOBJECTS16) \
$(LIBOBJECTS17) \
$(LIBOBJECTS18) \
$(LIBOBJECTS19) \
$(LIBOBJECTS20) \
$(LIBOBJECTS21) \
$(LIBOBJECTS22) \
$(LIBOBJECTS23) \
$(LIBOBJECTS24) \
$(LIBOBJECTS25) \
$(LIBOBJECTS26) \


## library compilation targets


$(libbin)/acons.o : $(LIBDIR)/acons.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/acons.o $(LIBDIR)/acons.c 


$(libbin)/adjoin.o : $(LIBDIR)/adjoin.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/adjoin.o $(LIBDIR)/adjoin.c 


$(libbin)/adjsblp.o : $(LIBDIR)/adjsblp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/adjsblp.o $(LIBDIR)/adjsblp.c 


$(libbin)/adjstrry.o : $(LIBDIR)/adjstrry.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/adjstrry.o $(LIBDIR)/adjstrry.c 


$(libbin)/admnsns.o : $(LIBDIR)/admnsns.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/admnsns.o $(LIBDIR)/admnsns.c 


$(libbin)/advncpcg.o : $(LIBDIR)/advncpcg.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/advncpcg.o $(LIBDIR)/advncpcg.c 


$(libbin)/allcmmg.o : $(LIBDIR)/allcmmg.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/allcmmg.o $(LIBDIR)/allcmmg.c 


$(libbin)/alphchrp.o : $(LIBDIR)/alphchrp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/alphchrp.o $(LIBDIR)/alphchrp.c 


$(libbin)/alpnmrcp.o : $(LIBDIR)/alpnmrcp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/alpnmrcp.o $(LIBDIR)/alpnmrcp.c 


$(libbin)/amjndx.o : $(LIBDIR)/amjndx.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/amjndx.o $(LIBDIR)/amjndx.c 


$(libbin)/anbndsp.o : $(LIBDIR)/anbndsp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/anbndsp.o $(LIBDIR)/anbndsp.c 


$(libbin)/append.o : $(LIBDIR)/append.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/append.o $(LIBDIR)/append.c 


$(libbin)/append2.o : $(LIBDIR)/append2.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/append2.o $(LIBDIR)/append2.c 


$(libbin)/apply.o : $(LIBDIR)/apply.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/apply.o $(LIBDIR)/apply.c 


$(libbin)/apply1.o : $(LIBDIR)/apply1.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/apply1.o $(LIBDIR)/apply1.c 


$(libbin)/apply2.o : $(LIBDIR)/apply2.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/apply2.o $(LIBDIR)/apply2.c 


$(libbin)/apply3.o : $(LIBDIR)/apply3.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/apply3.o $(LIBDIR)/apply3.c 


$(libbin)/aref.o : $(LIBDIR)/aref.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/aref.o $(LIBDIR)/aref.c 


$(libbin)/aref0.o : $(LIBDIR)/aref0.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/aref0.o $(LIBDIR)/aref0.c 


$(libbin)/aref1.o : $(LIBDIR)/aref1.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/aref1.o $(LIBDIR)/aref1.c 


$(libbin)/aref2.o : $(LIBDIR)/aref2.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/aref2.o $(LIBDIR)/aref2.c 


$(libbin)/aref3.o : $(LIBDIR)/aref3.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/aref3.o $(LIBDIR)/aref3.c 


$(libbin)/aref4.o : $(LIBDIR)/aref4.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/aref4.o $(LIBDIR)/aref4.c 


$(libbin)/aref5.o : $(LIBDIR)/aref5.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/aref5.o $(LIBDIR)/aref5.c 


$(libbin)/aref6.o : $(LIBDIR)/aref6.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/aref6.o $(LIBDIR)/aref6.c 


$(libbin)/aref7.o : $(LIBDIR)/aref7.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/aref7.o $(LIBDIR)/aref7.c 


$(libbin)/armmrlmt.o : $(LIBDIR)/armmrlmt.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/armmrlmt.o $(LIBDIR)/armmrlmt.c 


$(libbin)/armmrysd.o : $(LIBDIR)/armmrysd.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/armmrysd.o $(LIBDIR)/armmrysd.c 


$(libbin)/arrayp.o : $(LIBDIR)/arrayp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/arrayp.o $(LIBDIR)/arrayp.c 


$(libbin)/arrdmnsn.o : $(LIBDIR)/arrdmnsn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/arrdmnsn.o $(LIBDIR)/arrdmnsn.c 


$(libbin)/arrttlsz.o : $(LIBDIR)/arrttlsz.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/arrttlsz.o $(LIBDIR)/arrttlsz.c 


$(libbin)/arryrnk.o : $(LIBDIR)/arryrnk.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/arryrnk.o $(LIBDIR)/arryrnk.c 


$(libbin)/artrgtsz.o : $(LIBDIR)/artrgtsz.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/artrgtsz.o $(LIBDIR)/artrgtsz.c 


$(libbin)/asllpnp.o : $(LIBDIR)/asllpnp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/asllpnp.o $(LIBDIR)/asllpnp.c 


$(libbin)/asscifnt.o : $(LIBDIR)/asscifnt.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/asscifnt.o $(LIBDIR)/asscifnt.c 


$(libbin)/assoc.o : $(LIBDIR)/assoc.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/assoc.o $(LIBDIR)/assoc.c 


$(libbin)/assoc_eq.o : $(LIBDIR)/assoc_eq.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/assoc_eq.o $(LIBDIR)/assoc_eq.c 


$(libbin)/assoc_if.o : $(LIBDIR)/assoc_if.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/assoc_if.o $(LIBDIR)/assoc_if.c 


$(libbin)/assoceql.o : $(LIBDIR)/assoceql.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/assoceql.o $(LIBDIR)/assoceql.c 


$(libbin)/assocqul.o : $(LIBDIR)/assocqul.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/assocqul.o $(LIBDIR)/assocqul.c 


$(libbin)/assq.o : $(LIBDIR)/assq.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/assq.o $(LIBDIR)/assq.c 


$(libbin)/atom.o : $(LIBDIR)/atom.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/atom.o $(LIBDIR)/atom.c 


$(libbin)/avncmbl.o : $(LIBDIR)/avncmbl.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/avncmbl.o $(LIBDIR)/avncmbl.c 


$(libbin)/bgintim.o : $(LIBDIR)/bgintim.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/bgintim.o $(LIBDIR)/bgintim.c 


$(libbin)/bignump.o : $(LIBDIR)/bignump.c $(LIBHEADERS) \
                $(RUNTIME.H) $(TRIVIALP.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/bignump.o $(LIBDIR)/bignump.c 


$(libbin)/bitp.o : $(LIBDIR)/bitp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(TRIVIALP.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/bitp.o $(LIBDIR)/bitp.c 


$(libbin)/bitvctrp.o : $(LIBDIR)/bitvctrp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/bitvctrp.o $(LIBDIR)/bitvctrp.c 


$(libbin)/bothcsep.o : $(LIBDIR)/bothcsep.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/bothcsep.o $(LIBDIR)/bothcsep.c 


$(libbin)/boundp.o : $(LIBDIR)/boundp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/boundp.o $(LIBDIR)/boundp.c 


$(libbin)/butlast.o : $(LIBDIR)/butlast.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/butlast.o $(LIBDIR)/butlast.c 


$(libbin)/caaaar.o : $(LIBDIR)/caaaar.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/caaaar.o $(LIBDIR)/caaaar.c 


$(libbin)/caaadr.o : $(LIBDIR)/caaadr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/caaadr.o $(LIBDIR)/caaadr.c 


$(libbin)/caaar.o : $(LIBDIR)/caaar.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/caaar.o $(LIBDIR)/caaar.c 


$(libbin)/caadar.o : $(LIBDIR)/caadar.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/caadar.o $(LIBDIR)/caadar.c 


$(libbin)/caaddr.o : $(LIBDIR)/caaddr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/caaddr.o $(LIBDIR)/caaddr.c 


$(libbin)/caadr.o : $(LIBDIR)/caadr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/caadr.o $(LIBDIR)/caadr.c 


$(libbin)/caar.o : $(LIBDIR)/caar.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/caar.o $(LIBDIR)/caar.c 


$(libbin)/cadaar.o : $(LIBDIR)/cadaar.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cadaar.o $(LIBDIR)/cadaar.c 


$(libbin)/cadadr.o : $(LIBDIR)/cadadr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cadadr.o $(LIBDIR)/cadadr.c 


$(libbin)/cadar.o : $(LIBDIR)/cadar.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cadar.o $(LIBDIR)/cadar.c 


$(libbin)/caddar.o : $(LIBDIR)/caddar.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/caddar.o $(LIBDIR)/caddar.c 


$(libbin)/cadddr.o : $(LIBDIR)/cadddr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cadddr.o $(LIBDIR)/cadddr.c 


$(libbin)/caddr.o : $(LIBDIR)/caddr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/caddr.o $(LIBDIR)/caddr.c 


$(libbin)/cadr.o : $(LIBDIR)/cadr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cadr.o $(LIBDIR)/cadr.c 


$(libbin)/car.o : $(LIBDIR)/car.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/car.o $(LIBDIR)/car.c 


$(libbin)/ccl.o : $(LIBDIR)/ccl.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ccl.o $(LIBDIR)/ccl.c 


$(libbin)/cdaaar.o : $(LIBDIR)/cdaaar.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cdaaar.o $(LIBDIR)/cdaaar.c 


$(libbin)/cdaadr.o : $(LIBDIR)/cdaadr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cdaadr.o $(LIBDIR)/cdaadr.c 


$(libbin)/cdaar.o : $(LIBDIR)/cdaar.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cdaar.o $(LIBDIR)/cdaar.c 


$(libbin)/cdadar.o : $(LIBDIR)/cdadar.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cdadar.o $(LIBDIR)/cdadar.c 


$(libbin)/cdaddr.o : $(LIBDIR)/cdaddr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cdaddr.o $(LIBDIR)/cdaddr.c 


$(libbin)/cdadr.o : $(LIBDIR)/cdadr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cdadr.o $(LIBDIR)/cdadr.c 


$(libbin)/cdar.o : $(LIBDIR)/cdar.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cdar.o $(LIBDIR)/cdar.c 


$(libbin)/cdbltdbl.o : $(LIBDIR)/cdbltdbl.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cdbltdbl.o $(LIBDIR)/cdbltdbl.c 


$(libbin)/cddaar.o : $(LIBDIR)/cddaar.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cddaar.o $(LIBDIR)/cddaar.c 


$(libbin)/cddadr.o : $(LIBDIR)/cddadr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cddadr.o $(LIBDIR)/cddadr.c 


$(libbin)/cddar.o : $(LIBDIR)/cddar.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cddar.o $(LIBDIR)/cddar.c 


$(libbin)/cdddar.o : $(LIBDIR)/cdddar.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cdddar.o $(LIBDIR)/cdddar.c 


$(libbin)/cddddr.o : $(LIBDIR)/cddddr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cddddr.o $(LIBDIR)/cddddr.c 


$(libbin)/cdddr.o : $(LIBDIR)/cdddr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cdddr.o $(LIBDIR)/cdddr.c 


$(libbin)/cddr.o : $(LIBDIR)/cddr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cddr.o $(LIBDIR)/cddr.c 


$(libbin)/cdr.o : $(LIBDIR)/cdr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cdr.o $(LIBDIR)/cdr.c 


$(libbin)/char_bit.o : $(LIBDIR)/char_bit.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_bit.o $(LIBDIR)/char_bit.c 


$(libbin)/char_eq.o : $(LIBDIR)/char_eq.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_eq.o $(LIBDIR)/char_eq.c 


$(libbin)/char_eqn.o : $(LIBDIR)/char_eqn.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_eqn.o $(LIBDIR)/char_eqn.c 


$(libbin)/char_eqr.o : $(LIBDIR)/char_eqr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_eqr.o $(LIBDIR)/char_eqr.c 


$(libbin)/char_ge.o : $(LIBDIR)/char_ge.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_ge.o $(LIBDIR)/char_ge.c 


$(libbin)/char_gen.o : $(LIBDIR)/char_gen.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_gen.o $(LIBDIR)/char_gen.c 


$(libbin)/char_ger.o : $(LIBDIR)/char_ger.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_ger.o $(LIBDIR)/char_ger.c 


$(libbin)/char_gt.o : $(LIBDIR)/char_gt.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_gt.o $(LIBDIR)/char_gt.c 


$(libbin)/char_gtn.o : $(LIBDIR)/char_gtn.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_gtn.o $(LIBDIR)/char_gtn.c 


$(libbin)/char_gtr.o : $(LIBDIR)/char_gtr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_gtr.o $(LIBDIR)/char_gtr.c 


$(libbin)/char_int.o : $(LIBDIR)/char_int.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_int.o $(LIBDIR)/char_int.c 


$(libbin)/char_le.o : $(LIBDIR)/char_le.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_le.o $(LIBDIR)/char_le.c 


$(libbin)/char_len.o : $(LIBDIR)/char_len.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_len.o $(LIBDIR)/char_len.c 


$(libbin)/char_ler.o : $(LIBDIR)/char_ler.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_ler.o $(LIBDIR)/char_ler.c 


$(libbin)/char_lt.o : $(LIBDIR)/char_lt.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_lt.o $(LIBDIR)/char_lt.c 


$(libbin)/char_ltn.o : $(LIBDIR)/char_ltn.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_ltn.o $(LIBDIR)/char_ltn.c 


$(libbin)/char_ltr.o : $(LIBDIR)/char_ltr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_ltr.o $(LIBDIR)/char_ltr.c 


$(libbin)/char_ne.o : $(LIBDIR)/char_ne.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_ne.o $(LIBDIR)/char_ne.c 


$(libbin)/char_nen.o : $(LIBDIR)/char_nen.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_nen.o $(LIBDIR)/char_nen.c 


$(libbin)/char_ner.o : $(LIBDIR)/char_ner.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/char_ner.o $(LIBDIR)/char_ner.c 


$(libbin)/charbits.o : $(LIBDIR)/charbits.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/charbits.o $(LIBDIR)/charbits.c 


$(libbin)/charcode.o : $(LIBDIR)/charcode.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/charcode.o $(LIBDIR)/charcode.c 


$(libbin)/charfont.o : $(LIBDIR)/charfont.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/charfont.o $(LIBDIR)/charfont.c 


$(libbin)/charname.o : $(LIBDIR)/charname.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/charname.o $(LIBDIR)/charname.c 


$(libbin)/chrcter.o : $(LIBDIR)/chrcter.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/chrcter.o $(LIBDIR)/chrcter.c 


$(libbin)/chrcterp.o : $(LIBDIR)/chrcterp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/chrcterp.o $(LIBDIR)/chrcterp.c 


$(libbin)/chrdwncs.o : $(LIBDIR)/chrdwncs.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/chrdwncs.o $(LIBDIR)/chrdwncs.c 


$(libbin)/chrequl.o : $(LIBDIR)/chrequl.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/chrequl.o $(LIBDIR)/chrequl.c 


$(libbin)/chrequln.o : $(LIBDIR)/chrequln.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/chrequln.o $(LIBDIR)/chrequln.c 


$(libbin)/chrequlr.o : $(LIBDIR)/chrequlr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/chrequlr.o $(LIBDIR)/chrequlr.c 


$(libbin)/chrgrtrp.o : $(LIBDIR)/chrgrtrp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/chrgrtrp.o $(LIBDIR)/chrgrtrp.c 


$(libbin)/chrlessp.o : $(LIBDIR)/chrlessp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/chrlessp.o $(LIBDIR)/chrlessp.c 


$(libbin)/chrlsspn.o : $(LIBDIR)/chrlsspn.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/chrlsspn.o $(LIBDIR)/chrlsspn.c 


$(libbin)/chrlsspr.o : $(LIBDIR)/chrlsspr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/chrlsspr.o $(LIBDIR)/chrlsspr.c 


$(libbin)/chrmmbr.o : $(LIBDIR)/chrmmbr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/chrmmbr.o $(LIBDIR)/chrmmbr.c 


$(libbin)/chrntqln.o : $(LIBDIR)/chrntqln.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/chrntqln.o $(LIBDIR)/chrntqln.c 


$(libbin)/chrntqlr.o : $(LIBDIR)/chrntqlr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/chrntqlr.o $(LIBDIR)/chrntqlr.c 


$(libbin)/chrntqul.o : $(LIBDIR)/chrntqul.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/chrntqul.o $(LIBDIR)/chrntqul.c 


$(libbin)/chrupcse.o : $(LIBDIR)/chrupcse.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/chrupcse.o $(LIBDIR)/chrupcse.c 


$(libbin)/cllc.o : $(LIBDIR)/cllc.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cllc.o $(LIBDIR)/cllc.c 


$(libbin)/clrinput.o : $(LIBDIR)/clrinput.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/clrinput.o $(LIBDIR)/clrinput.c 


$(libbin)/clrutput.o : $(LIBDIR)/clrutput.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/clrutput.o $(LIBDIR)/clrutput.c 


$(libbin)/cmplmnnl.o : $(LIBDIR)/cmplmnnl.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cmplmnnl.o $(LIBDIR)/cmplmnnl.c 


$(libbin)/cmplncnp.o : $(LIBDIR)/cmplncnp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cmplncnp.o $(LIBDIR)/cmplncnp.c 


$(libbin)/cnnlnncn.o : $(LIBDIR)/cnnlnncn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cnnlnncn.o $(LIBDIR)/cnnlnncn.c 


$(libbin)/cnsnlfls.o : $(LIBDIR)/cnsnlfls.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cnsnlfls.o $(LIBDIR)/cnsnlfls.c 


$(libbin)/cnsnlndl.o : $(LIBDIR)/cnsnlndl.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cnsnlndl.o $(LIBDIR)/cnsnlndl.c 


$(libbin)/cnsnlr.o : $(LIBDIR)/cnsnlr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cnsnlr.o $(LIBDIR)/cnsnlr.c 


$(libbin)/cobjectp.o : $(LIBDIR)/cobjectp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(TRIVIALP.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cobjectp.o $(LIBDIR)/cobjectp.c 


$(libbin)/codechar.o : $(LIBDIR)/codechar.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/codechar.o $(LIBDIR)/codechar.c 


$(libbin)/coerce.o : $(LIBDIR)/coerce.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/coerce.o $(LIBDIR)/coerce.c 


$(libbin)/commonp.o : $(LIBDIR)/commonp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/commonp.o $(LIBDIR)/commonp.c 


$(libbin)/complexp.o : $(LIBDIR)/complexp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/complexp.o $(LIBDIR)/complexp.c 


$(libbin)/conctnt.o : $(LIBDIR)/conctnt.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CONCATNT.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/conctnt.o $(LIBDIR)/conctnt.c 


$(libbin)/consp.o : $(LIBDIR)/consp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/consp.o $(LIBDIR)/consp.c 


$(libbin)/copy_seq.o : $(LIBDIR)/copy_seq.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/copy_seq.o $(LIBDIR)/copy_seq.c 


$(libbin)/copylist.o : $(LIBDIR)/copylist.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/copylist.o $(LIBDIR)/copylist.c 


$(libbin)/copytree.o : $(LIBDIR)/copytree.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/copytree.o $(LIBDIR)/copytree.c 


$(libbin)/count.o : $(LIBDIR)/count.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/count.o $(LIBDIR)/count.c 


$(libbin)/count_if.o : $(LIBDIR)/count_if.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/count_if.o $(LIBDIR)/count_if.c 


$(libbin)/cp_alist.o : $(LIBDIR)/cp_alist.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cp_alist.o $(LIBDIR)/cp_alist.c 


$(libbin)/cpfptr.o : $(LIBDIR)/cpfptr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cpfptr.o $(LIBDIR)/cpfptr.c 


$(libbin)/cpysymbl.o : $(LIBDIR)/cpysymbl.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cpysymbl.o $(LIBDIR)/cpysymbl.c 


$(libbin)/crgrtrpn.o : $(LIBDIR)/crgrtrpn.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/crgrtrpn.o $(LIBDIR)/crgrtrpn.c 


$(libbin)/crgrtrpr.o : $(LIBDIR)/crgrtrpr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/crgrtrpr.o $(LIBDIR)/crgrtrpr.c 


$(libbin)/crngrrp.o : $(LIBDIR)/crngrrp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/crngrrp.o $(LIBDIR)/crngrrp.c 


$(libbin)/crngrrpn.o : $(LIBDIR)/crngrrpn.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/crngrrpn.o $(LIBDIR)/crngrrpn.c 


$(libbin)/crngrrpr.o : $(LIBDIR)/crngrrpr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/crngrrpr.o $(LIBDIR)/crngrrpr.c 


$(libbin)/crnlsspn.o : $(LIBDIR)/crnlsspn.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/crnlsspn.o $(LIBDIR)/crnlsspn.c 


$(libbin)/crnlsspr.o : $(LIBDIR)/crnlsspr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/crnlsspr.o $(LIBDIR)/crnlsspr.c 


$(libbin)/crntlssp.o : $(LIBDIR)/crntlssp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/crntlssp.o $(LIBDIR)/crntlssp.c 


$(libbin)/csnpsrm.o : $(LIBDIR)/csnpsrm.c $(LIBHEADERS) \
                $(RUNTIME.H) $(STRMINIT.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/csnpsrm.o $(LIBDIR)/csnpsrm.c 


$(libbin)/cspsrm.o : $(LIBDIR)/cspsrm.c $(LIBHEADERS) \
                $(RUNTIME.H) $(STRMINIT.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cspsrm.o $(LIBDIR)/cspsrm.c 


$(libbin)/cswrsrm.o : $(LIBDIR)/cswrsrm.c $(LIBHEADERS) \
                $(RUNTIME.H) $(STRMINIT.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cswrsrm.o $(LIBDIR)/cswrsrm.c 


$(libbin)/cuntifnt.o : $(LIBDIR)/cuntifnt.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/cuntifnt.o $(LIBDIR)/cuntifnt.c 


$(libbin)/dbltntgr.o : $(LIBDIR)/dbltntgr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/dbltntgr.o $(LIBDIR)/dbltntgr.c 


$(libbin)/dcdnvslm.o : $(LIBDIR)/dcdnvslm.c $(LIBHEADERS) \
                $(RUNTIME.H) $(UTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/dcdnvslm.o $(LIBDIR)/dcdnvslm.c 


$(libbin)/dcnmsng.o : $(LIBDIR)/dcnmsng.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/dcnmsng.o $(LIBDIR)/dcnmsng.c 


$(libbin)/defftp.o : $(LIBDIR)/defftp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/defftp.o $(LIBDIR)/defftp.c 


$(libbin)/deleteeq.o : $(LIBDIR)/deleteeq.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SEQMODI.H) $(DEL-EQ.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/deleteeq.o $(LIBDIR)/deleteeq.c 


$(libbin)/deleteif.o : $(LIBDIR)/deleteif.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SEQMODI.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/deleteif.o $(LIBDIR)/deleteif.c 


$(libbin)/delq.o : $(LIBDIR)/delq.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/delq.o $(LIBDIR)/delq.c 


$(libbin)/describe.o : $(LIBDIR)/describe.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/describe.o $(LIBDIR)/describe.c 


$(libbin)/dgtchrp.o : $(LIBDIR)/dgtchrp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/dgtchrp.o $(LIBDIR)/dgtchrp.c 


$(libbin)/digitchr.o : $(LIBDIR)/digitchr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/digitchr.o $(LIBDIR)/digitchr.c 


$(libbin)/dirctory.o : $(LIBDIR)/dirctory.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/dirctory.o $(LIBDIR)/dirctory.c 


$(libbin)/dldplcs.o : $(LIBDIR)/dldplcs.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SEQMODI.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/dldplcs.o $(LIBDIR)/dldplcs.c 


$(libbin)/dltfil.o : $(LIBDIR)/dltfil.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/dltfil.o $(LIBDIR)/dltfil.c 


$(libbin)/dltifnot.o : $(LIBDIR)/dltifnot.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SEQMODI.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/dltifnot.o $(LIBDIR)/dltifnot.c 


$(libbin)/dltql.o : $(LIBDIR)/dltql.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SEQMODI.H) $(DEL-EQ.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/dltql.o $(LIBDIR)/dltql.c 


$(libbin)/dltqul.o : $(LIBDIR)/dltqul.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SEQMODI.H) $(DEL-EQ.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/dltqul.o $(LIBDIR)/dltqul.c 


$(libbin)/doaref1.o : $(LIBDIR)/doaref1.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/doaref1.o $(LIBDIR)/doaref1.c 


$(libbin)/dormovif.o : $(LIBDIR)/dormovif.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SEQMODI.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/dormovif.o $(LIBDIR)/dormovif.c 


$(libbin)/dostfrf.o : $(LIBDIR)/dostfrf.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/dostfrf.o $(LIBDIR)/dostfrf.c 


$(libbin)/drmfrrr.o : $(LIBDIR)/drmfrrr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/drmfrrr.o $(LIBDIR)/drmfrrr.c 


$(libbin)/eighth.o : $(LIBDIR)/eighth.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/eighth.o $(LIBDIR)/eighth.c 


$(libbin)/encnvslm.o : $(LIBDIR)/encnvslm.c $(LIBHEADERS) \
                $(RUNTIME.H) $(UTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/encnvslm.o $(LIBDIR)/encnvslm.c 


$(libbin)/endp.o : $(LIBDIR)/endp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/endp.o $(LIBDIR)/endp.c 


$(libbin)/engnmsng.o : $(LIBDIR)/engnmsng.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/engnmsng.o $(LIBDIR)/engnmsng.c 


$(libbin)/eq.o : $(LIBDIR)/eq.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/eq.o $(LIBDIR)/eq.c 


$(libbin)/eql.o : $(LIBDIR)/eql.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/eql.o $(LIBDIR)/eql.c 


$(libbin)/equal.o : $(LIBDIR)/equal.c $(LIBHEADERS) \
                $(RUNTIME.H) $(EQUAL.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/equal.o $(LIBDIR)/equal.c 


$(libbin)/equalp.o : $(LIBDIR)/equalp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(EQUAL.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/equalp.o $(LIBDIR)/equalp.c 


$(libbin)/faref.o : $(LIBDIR)/faref.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/faref.o $(LIBDIR)/faref.c 


$(libbin)/fifth.o : $(LIBDIR)/fifth.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/fifth.o $(LIBDIR)/fifth.c 


$(libbin)/fill.o : $(LIBDIR)/fill.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SEQMODI.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/fill.o $(LIBDIR)/fill.c 


$(libbin)/fillngth.o : $(LIBDIR)/fillngth.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/fillngth.o $(LIBDIR)/fillngth.c 


$(libbin)/filuthor.o : $(LIBDIR)/filuthor.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/filuthor.o $(LIBDIR)/filuthor.c 


$(libbin)/find.o : $(LIBDIR)/find.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/find.o $(LIBDIR)/find.c 


$(libbin)/find_if.o : $(LIBDIR)/find_if.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/find_if.o $(LIBDIR)/find_if.c 


$(libbin)/findifnt.o : $(LIBDIR)/findifnt.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/findifnt.o $(LIBDIR)/findifnt.c 


$(libbin)/first.o : $(LIBDIR)/first.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/first.o $(LIBDIR)/first.c 


$(libbin)/fixnump.o : $(LIBDIR)/fixnump.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/fixnump.o $(LIBDIR)/fixnump.c 


$(libbin)/flatsize.o : $(LIBDIR)/flatsize.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/flatsize.o $(LIBDIR)/flatsize.c 


$(libbin)/fllpntr.o : $(LIBDIR)/fllpntr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/fllpntr.o $(LIBDIR)/fllpntr.c 


$(libbin)/flnmsrng.o : $(LIBDIR)/flnmsrng.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/flnmsrng.o $(LIBDIR)/flnmsrng.c 


$(libbin)/floatp.o : $(LIBDIR)/floatp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/floatp.o $(LIBDIR)/floatp.c 


$(libbin)/flpstn.o : $(LIBDIR)/flpstn.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/flpstn.o $(LIBDIR)/flpstn.c 


$(libbin)/flwrtdt.o : $(LIBDIR)/flwrtdt.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/flwrtdt.o $(LIBDIR)/flwrtdt.c 


$(libbin)/fnllmbl.o : $(LIBDIR)/fnllmbl.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/fnllmbl.o $(LIBDIR)/fnllmbl.c 


$(libbin)/fnshtm.o : $(LIBDIR)/fnshtm.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/fnshtm.o $(LIBDIR)/fnshtm.c 


$(libbin)/fnshtpt.o : $(LIBDIR)/fnshtpt.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/fnshtpt.o $(LIBDIR)/fnshtpt.c 


$(libbin)/forptrp.o : $(LIBDIR)/forptrp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/forptrp.o $(LIBDIR)/forptrp.c 


$(libbin)/forptrtp.o : $(LIBDIR)/forptrtp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/forptrtp.o $(LIBDIR)/forptrtp.c 


$(libbin)/fortype.o : $(LIBDIR)/fortype.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/fortype.o $(LIBDIR)/fortype.c 


$(libbin)/fortypep.o : $(LIBDIR)/fortypep.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/fortypep.o $(LIBDIR)/fortypep.c 


$(libbin)/forval.o : $(LIBDIR)/forval.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/forval.o $(LIBDIR)/forval.c 


$(libbin)/fourth.o : $(LIBDIR)/fourth.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/fourth.o $(LIBDIR)/fourth.c 


$(libbin)/fpaddr.o : $(LIBDIR)/fpaddr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/fpaddr.o $(LIBDIR)/fpaddr.c 


$(libbin)/fptype.o : $(LIBDIR)/fptype.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/fptype.o $(LIBDIR)/fptype.c 


$(libbin)/frcutput.o : $(LIBDIR)/frcutput.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/frcutput.o $(LIBDIR)/frcutput.c 


$(libbin)/frfptr.o : $(LIBDIR)/frfptr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/frfptr.o $(LIBDIR)/frfptr.c 


$(libbin)/frshlin.o : $(LIBDIR)/frshlin.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/frshlin.o $(LIBDIR)/frshlin.c 


$(libbin)/fsizeof.o : $(LIBDIR)/fsizeof.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/fsizeof.o $(LIBDIR)/fsizeof.c 


$(libbin)/fstrval.o : $(LIBDIR)/fstrval.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/fstrval.o $(LIBDIR)/fstrval.c 


$(libbin)/ftmod.o : $(LIBDIR)/ftmod.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ftmod.o $(LIBDIR)/ftmod.c 


$(libbin)/ftname.o : $(LIBDIR)/ftname.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ftname.o $(LIBDIR)/ftname.c 


$(libbin)/ftrem.o : $(LIBDIR)/ftrem.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ftrem.o $(LIBDIR)/ftrem.c 


$(libbin)/ftsize.o : $(LIBDIR)/ftsize.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ftsize.o $(LIBDIR)/ftsize.c 


$(libbin)/ftypep.o : $(LIBDIR)/ftypep.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ftypep.o $(LIBDIR)/ftypep.c 


$(libbin)/funcall.o : $(LIBDIR)/funcall.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/funcall.o $(LIBDIR)/funcall.c 


$(libbin)/funcall3.o : $(LIBDIR)/funcall3.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/funcall3.o $(LIBDIR)/funcall3.c 


$(libbin)/functinp.o : $(LIBDIR)/functinp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/functinp.o $(LIBDIR)/functinp.c 


$(libbin)/gensym.o : $(LIBDIR)/gensym.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/gensym.o $(LIBDIR)/gensym.c 


$(libbin)/gentemp.o : $(LIBDIR)/gentemp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/gentemp.o $(LIBDIR)/gentemp.c 


$(libbin)/get.o : $(LIBDIR)/get.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/get.o $(LIBDIR)/get.c 


$(libbin)/getf.o : $(LIBDIR)/getf.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/getf.o $(LIBDIR)/getf.c 


$(libbin)/gnrnlrlm.o : $(LIBDIR)/gnrnlrlm.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/gnrnlrlm.o $(LIBDIR)/gnrnlrlm.c 


$(libbin)/gnrnlrnm.o : $(LIBDIR)/gnrnlrnm.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/gnrnlrnm.o $(LIBDIR)/gnrnlrnm.c 


$(libbin)/gnvrslm.o : $(LIBDIR)/gnvrslm.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/gnvrslm.o $(LIBDIR)/gnvrslm.c 


$(libbin)/grpccrp.o : $(LIBDIR)/grpccrp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/grpccrp.o $(LIBDIR)/grpccrp.c 


$(libbin)/gtdcddtm.o : $(LIBDIR)/gtdcddtm.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/gtdcddtm.o $(LIBDIR)/gtdcddtm.c 


$(libbin)/gtprprts.o : $(LIBDIR)/gtprprts.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/gtprprts.o $(LIBDIR)/gtprprts.c 


$(libbin)/hsnmsrng.o : $(LIBDIR)/hsnmsrng.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/hsnmsrng.o $(LIBDIR)/hsnmsrng.c 


$(libbin)/ichrnme.o : $(LIBDIR)/ichrnme.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ichrnme.o $(LIBDIR)/ichrnme.c 


$(libbin)/identity.o : $(LIBDIR)/identity.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/identity.o $(LIBDIR)/identity.c 


$(libbin)/igglg.o : $(LIBDIR)/igglg.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/igglg.o $(LIBDIR)/igglg.c 


$(libbin)/ilzxlbl.o : $(LIBDIR)/ilzxlbl.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ilzxlbl.o $(LIBDIR)/ilzxlbl.c 


$(libbin)/immedite.o : $(LIBDIR)/immedite.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/immedite.o $(LIBDIR)/immedite.c 


$(libbin)/ingrlng.o : $(LIBDIR)/ingrlng.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ingrlng.o $(LIBDIR)/ingrlng.c 


$(libbin)/inlzllbl.o : $(LIBDIR)/inlzllbl.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/inlzllbl.o $(LIBDIR)/inlzllbl.c 


$(libbin)/inlzmbl.o : $(LIBDIR)/inlzmbl.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/inlzmbl.o $(LIBDIR)/inlzmbl.c 


$(libbin)/inlzpckg.o : $(LIBDIR)/inlzpckg.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/inlzpckg.o $(LIBDIR)/inlzpckg.c 


$(libbin)/innlmkp.o : $(LIBDIR)/innlmkp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/innlmkp.o $(LIBDIR)/innlmkp.c 


$(libbin)/inspect.o : $(LIBDIR)/inspect.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/inspect.o $(LIBDIR)/inspect.c 


$(libbin)/int_char.o : $(LIBDIR)/int_char.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/int_char.o $(LIBDIR)/int_char.c 


$(libbin)/integerp.o : $(LIBDIR)/integerp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/integerp.o $(LIBDIR)/integerp.c 


$(libbin)/intrsctn.o : $(LIBDIR)/intrsctn.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/intrsctn.o $(LIBDIR)/intrsctn.c 


$(libbin)/invldmd.o : $(LIBDIR)/invldmd.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/invldmd.o $(LIBDIR)/invldmd.c 


$(libbin)/invlncnn.o : $(LIBDIR)/invlncnn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/invlncnn.o $(LIBDIR)/invlncnn.c 


$(libbin)/ismblnm.o : $(LIBDIR)/ismblnm.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ismblnm.o $(LIBDIR)/ismblnm.c 


$(libbin)/isngsng.o : $(LIBDIR)/isngsng.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/isngsng.o $(LIBDIR)/isngsng.c 


$(libbin)/isngsngn.o : $(LIBDIR)/isngsngn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/isngsngn.o $(LIBDIR)/isngsngn.c 


$(libbin)/keywordp.o : $(LIBDIR)/keywordp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/keywordp.o $(LIBDIR)/keywordp.c 


$(libbin)/last.o : $(LIBDIR)/last.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/last.o $(LIBDIR)/last.c 


$(libbin)/ldelete.o : $(LIBDIR)/ldelete.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SEQMODI.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ldelete.o $(LIBDIR)/ldelete.c 


$(libbin)/ldiff.o : $(LIBDIR)/ldiff.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ldiff.o $(LIBDIR)/ldiff.c 


$(libbin)/lgclpnmp.o : $(LIBDIR)/lgclpnmp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/lgclpnmp.o $(LIBDIR)/lgclpnmp.c 


$(libbin)/list.o : $(LIBDIR)/list.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/list.o $(LIBDIR)/list.c 


$(libbin)/listp.o : $(LIBDIR)/listp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/listp.o $(LIBDIR)/listp.c 


$(libbin)/listrvrs.o : $(LIBDIR)/listrvrs.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/listrvrs.o $(LIBDIR)/listrvrs.c 


$(libbin)/liststar.o : $(LIBDIR)/liststar.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/liststar.o $(LIBDIR)/liststar.c 


$(libbin)/listvlus.o : $(LIBDIR)/listvlus.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/listvlus.o $(LIBDIR)/listvlus.c 


$(libbin)/llisten.o : $(LIBDIR)/llisten.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/llisten.o $(LIBDIR)/llisten.c 


$(libbin)/lmlmnn.o : $(LIBDIR)/lmlmnn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/lmlmnn.o $(LIBDIR)/lmlmnn.c 


$(libbin)/lmlmnnvn.o : $(LIBDIR)/lmlmnnvn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/lmlmnnvn.o $(LIBDIR)/lmlmnnvn.c 


$(libbin)/load.o : $(LIBDIR)/load.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/load.o $(LIBDIR)/load.c 


$(libbin)/load_run.o : $(LIBDIR)/load_run.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/load_run.o $(LIBDIR)/load_run.c 


$(libbin)/lopen.o : $(LIBDIR)/lopen.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/lopen.o $(LIBDIR)/lopen.c 


$(libbin)/lowrcsp.o : $(LIBDIR)/lowrcsp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/lowrcsp.o $(LIBDIR)/lowrcsp.c 


$(libbin)/lremove.o : $(LIBDIR)/lremove.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SEQMODI.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/lremove.o $(LIBDIR)/lremove.c 


$(libbin)/lsleep.o : $(LIBDIR)/lsleep.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/lsleep.o $(LIBDIR)/lsleep.c 


$(libbin)/lstlngth.o : $(LIBDIR)/lstlngth.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/lstlngth.o $(LIBDIR)/lstlngth.c 


$(libbin)/lstnrvrs.o : $(LIBDIR)/lstnrvrs.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/lstnrvrs.o $(LIBDIR)/lstnrvrs.c 


$(libbin)/lunion.o : $(LIBDIR)/lunion.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/lunion.o $(LIBDIR)/lunion.c 


$(libbin)/m_nthcdr.o : $(LIBDIR)/m_nthcdr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/m_nthcdr.o $(LIBDIR)/m_nthcdr.c 


$(libbin)/makechar.o : $(LIBDIR)/makechar.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/makechar.o $(LIBDIR)/makechar.c 


$(libbin)/makelist.o : $(LIBDIR)/makelist.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/makelist.o $(LIBDIR)/makelist.c 


$(libbin)/map.o : $(LIBDIR)/map.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/map.o $(LIBDIR)/map.c 


$(libbin)/map_into.o : $(LIBDIR)/map_into.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/map_into.o $(LIBDIR)/map_into.c 


$(libbin)/mcfptr.o : $(LIBDIR)/mcfptr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mcfptr.o $(LIBDIR)/mcfptr.c 


$(libbin)/mchintyp.o : $(LIBDIR)/mchintyp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mchintyp.o $(LIBDIR)/mchintyp.c 


$(libbin)/mchnvrsn.o : $(LIBDIR)/mchnvrsn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mchnvrsn.o $(LIBDIR)/mchnvrsn.c 


$(libbin)/mcnnstnc.o : $(LIBDIR)/mcnnstnc.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mcnnstnc.o $(LIBDIR)/mcnnstnc.c 


$(libbin)/mdcmbnn.o : $(LIBDIR)/mdcmbnn.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mdcmbnn.o $(LIBDIR)/mdcmbnn.c 


$(libbin)/member.o : $(LIBDIR)/member.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/member.o $(LIBDIR)/member.c 


$(libbin)/membereq.o : $(LIBDIR)/membereq.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/membereq.o $(LIBDIR)/membereq.c 


$(libbin)/memberif.o : $(LIBDIR)/memberif.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/memberif.o $(LIBDIR)/memberif.c 


$(libbin)/memberse.o : $(LIBDIR)/memberse.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/memberse.o $(LIBDIR)/memberse.c 


$(libbin)/memq.o : $(LIBDIR)/memq.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/memq.o $(LIBDIR)/memq.c 


$(libbin)/merge.o : $(LIBDIR)/merge.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/merge.o $(LIBDIR)/merge.c 


$(libbin)/mismatch.o : $(LIBDIR)/mismatch.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mismatch.o $(LIBDIR)/mismatch.c 


$(libbin)/mkarrlt.o : $(LIBDIR)/mkarrlt.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mkarrlt.o $(LIBDIR)/mkarrlt.c 


$(libbin)/mkcomplx.o : $(LIBDIR)/mkcomplx.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mkcomplx.o $(LIBDIR)/mkcomplx.c 


$(libbin)/mkfptr.o : $(LIBDIR)/mkfptr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mkfptr.o $(LIBDIR)/mkfptr.c 


$(libbin)/mkfptri.o : $(LIBDIR)/mkfptri.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mkfptri.o $(LIBDIR)/mkfptri.c 


$(libbin)/mkpthnm.o : $(LIBDIR)/mkpthnm.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mkpthnm.o $(LIBDIR)/mkpthnm.c 


$(libbin)/mkscnsnc.o : $(LIBDIR)/mkscnsnc.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mkscnsnc.o $(LIBDIR)/mkscnsnc.c 


$(libbin)/mksqunc.o : $(LIBDIR)/mksqunc.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mksqunc.o $(LIBDIR)/mksqunc.c 


$(libbin)/mksymbol.o : $(LIBDIR)/mksymbol.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mksymbol.o $(LIBDIR)/mksymbol.c 


$(libbin)/mkunbund.o : $(LIBDIR)/mkunbund.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mkunbund.o $(LIBDIR)/mkunbund.c 


$(libbin)/mkvctor.o : $(LIBDIR)/mkvctor.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mkvctor.o $(LIBDIR)/mkvctor.c 


$(libbin)/mkvlucll.o : $(LIBDIR)/mkvlucll.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mkvlucll.o $(LIBDIR)/mkvlucll.c 


$(libbin)/mlplvlln.o : $(LIBDIR)/mlplvlln.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mlplvlln.o $(LIBDIR)/mlplvlln.c 


$(libbin)/mmbrifnt.o : $(LIBDIR)/mmbrifnt.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mmbrifnt.o $(LIBDIR)/mmbrifnt.c 


$(libbin)/mmbrodd.o : $(LIBDIR)/mmbrodd.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mmbrodd.o $(LIBDIR)/mmbrodd.c 


$(libbin)/mmbrql.o : $(LIBDIR)/mmbrql.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mmbrql.o $(LIBDIR)/mmbrql.c 


$(libbin)/mmbrqul.o : $(LIBDIR)/mmbrqul.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mmbrqul.o $(LIBDIR)/mmbrqul.c 


$(libbin)/mrgptnms.o : $(LIBDIR)/mrgptnms.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mrgptnms.o $(LIBDIR)/mrgptnms.c 


$(libbin)/mspcmccc.o : $(LIBDIR)/mspcmccc.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mspcmccc.o $(LIBDIR)/mspcmccc.c 


$(libbin)/mvsn.o : $(LIBDIR)/mvsn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/mvsn.o $(LIBDIR)/mvsn.c 


$(libbin)/namechar.o : $(LIBDIR)/namechar.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/namechar.o $(LIBDIR)/namechar.c 


$(libbin)/nbutlast.o : $(LIBDIR)/nbutlast.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nbutlast.o $(LIBDIR)/nbutlast.c 


$(libbin)/nconc.o : $(LIBDIR)/nconc.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nconc.o $(LIBDIR)/nconc.c 


$(libbin)/nconc2.o : $(LIBDIR)/nconc2.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nconc2.o $(LIBDIR)/nconc2.c 


$(libbin)/ncons.o : $(LIBDIR)/ncons.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ncons.o $(LIBDIR)/ncons.c 


$(libbin)/ncons1.o : $(LIBDIR)/ncons1.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ncons1.o $(LIBDIR)/ncons1.c 


$(libbin)/ninth.o : $(LIBDIR)/ninth.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ninth.o $(LIBDIR)/ninth.c 


$(libbin)/nmstring.o : $(LIBDIR)/nmstring.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nmstring.o $(LIBDIR)/nmstring.c 


$(libbin)/nntrsctn.o : $(LIBDIR)/nntrsctn.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nntrsctn.o $(LIBDIR)/nntrsctn.c 


$(libbin)/not.o : $(LIBDIR)/not.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/not.o $(LIBDIR)/not.c 


$(libbin)/nreconc.o : $(LIBDIR)/nreconc.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nreconc.o $(LIBDIR)/nreconc.c 


$(libbin)/nreverse.o : $(LIBDIR)/nreverse.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nreverse.o $(LIBDIR)/nreverse.c 


$(libbin)/nsbsfn.o : $(LIBDIR)/nsbsfn.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SEQMODI.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nsbsfn.o $(LIBDIR)/nsbsfn.c 


$(libbin)/nsbstfnt.o : $(LIBDIR)/nsbstfnt.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nsbstfnt.o $(LIBDIR)/nsbstfnt.c 


$(libbin)/nsbsttt.o : $(LIBDIR)/nsbsttt.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SEQMODI.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nsbsttt.o $(LIBDIR)/nsbsttt.c 


$(libbin)/nsbstttf.o : $(LIBDIR)/nsbstttf.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SEQMODI.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nsbstttf.o $(LIBDIR)/nsbstttf.c 


$(libbin)/nsdffrnc.o : $(LIBDIR)/nsdffrnc.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nsdffrnc.o $(LIBDIR)/nsdffrnc.c 


$(libbin)/nsngcplz.o : $(LIBDIR)/nsngcplz.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nsngcplz.o $(LIBDIR)/nsngcplz.c 


$(libbin)/nsngdncs.o : $(LIBDIR)/nsngdncs.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nsngdncs.o $(LIBDIR)/nsngdncs.c 


$(libbin)/nsrngpcs.o : $(LIBDIR)/nsrngpcs.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nsrngpcs.o $(LIBDIR)/nsrngpcs.c 


$(libbin)/nsublis.o : $(LIBDIR)/nsublis.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nsublis.o $(LIBDIR)/nsublis.c 


$(libbin)/nsubst.o : $(LIBDIR)/nsubst.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nsubst.o $(LIBDIR)/nsubst.c 


$(libbin)/nsubstif.o : $(LIBDIR)/nsubstif.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nsubstif.o $(LIBDIR)/nsubstif.c 


$(libbin)/nsxclsvr.o : $(LIBDIR)/nsxclsvr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nsxclsvr.o $(LIBDIR)/nsxclsvr.c 


$(libbin)/nth.o : $(LIBDIR)/nth.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nth.o $(LIBDIR)/nth.c 


$(libbin)/nthcdr.o : $(LIBDIR)/nthcdr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nthcdr.o $(LIBDIR)/nthcdr.c 


$(libbin)/null.o : $(LIBDIR)/null.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/null.o $(LIBDIR)/null.c 


$(libbin)/numberp.o : $(LIBDIR)/numberp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/numberp.o $(LIBDIR)/numberp.c 


$(libbin)/nunion.o : $(LIBDIR)/nunion.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/nunion.o $(LIBDIR)/nunion.c 


$(libbin)/objccdbl.o : $(LIBDIR)/objccdbl.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/objccdbl.o $(LIBDIR)/objccdbl.c 


$(libbin)/packagep.o : $(LIBDIR)/packagep.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/packagep.o $(LIBDIR)/packagep.c 


$(libbin)/pairlis.o : $(LIBDIR)/pairlis.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/pairlis.o $(LIBDIR)/pairlis.c 


$(libbin)/pathname.o : $(LIBDIR)/pathname.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) $(STRMINIT.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/pathname.o $(LIBDIR)/pathname.c 


$(libbin)/pctpintr.o : $(LIBDIR)/pctpintr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/pctpintr.o $(LIBDIR)/pctpintr.c 


$(libbin)/peekchar.o : $(LIBDIR)/peekchar.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/peekchar.o $(LIBDIR)/peekchar.c 


$(libbin)/pnmdrcr.o : $(LIBDIR)/pnmdrcr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/pnmdrcr.o $(LIBDIR)/pnmdrcr.c 


$(libbin)/position.o : $(LIBDIR)/position.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/position.o $(LIBDIR)/position.c 


$(libbin)/pprint.o : $(LIBDIR)/pprint.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/pprint.o $(LIBDIR)/pprint.c 


$(libbin)/prin1.o : $(LIBDIR)/prin1.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/prin1.o $(LIBDIR)/prin1.c 


$(libbin)/princ.o : $(LIBDIR)/princ.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/princ.o $(LIBDIR)/princ.c 


$(libbin)/print.o : $(LIBDIR)/print.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/print.o $(LIBDIR)/print.c 


$(libbin)/prmpfrvl.o : $(LIBDIR)/prmpfrvl.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/prmpfrvl.o $(LIBDIR)/prmpfrvl.c 


$(libbin)/prn1srng.o : $(LIBDIR)/prn1srng.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/prn1srng.o $(LIBDIR)/prn1srng.c 


$(libbin)/prncsrng.o : $(LIBDIR)/prncsrng.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/prncsrng.o $(LIBDIR)/prncsrng.c 


$(libbin)/probfil.o : $(LIBDIR)/probfil.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/probfil.o $(LIBDIR)/probfil.c 


$(libbin)/proclaim.o : $(LIBDIR)/proclaim.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/proclaim.o $(LIBDIR)/proclaim.c 


$(libbin)/progv_do.o : $(LIBDIR)/progv_do.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/progv_do.o $(LIBDIR)/progv_do.c 


$(libbin)/prsintgr.o : $(LIBDIR)/prsintgr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/prsintgr.o $(LIBDIR)/prsintgr.c 


$(libbin)/psitinif.o : $(LIBDIR)/psitinif.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/psitinif.o $(LIBDIR)/psitinif.c 


$(libbin)/psnmsng.o : $(LIBDIR)/psnmsng.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/psnmsng.o $(LIBDIR)/psnmsng.c 


$(libbin)/pstnfnt.o : $(LIBDIR)/pstnfnt.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/pstnfnt.o $(LIBDIR)/pstnfnt.c 


$(libbin)/pthnmdvc.o : $(LIBDIR)/pthnmdvc.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/pthnmdvc.o $(LIBDIR)/pthnmdvc.c 


$(libbin)/pthnmep.o : $(LIBDIR)/pthnmep.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/pthnmep.o $(LIBDIR)/pthnmep.c 


$(libbin)/pthnmhst.o : $(LIBDIR)/pthnmhst.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/pthnmhst.o $(LIBDIR)/pthnmhst.c 


$(libbin)/pthnmnm.o : $(LIBDIR)/pthnmnm.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/pthnmnm.o $(LIBDIR)/pthnmnm.c 


$(libbin)/pthnmtyp.o : $(LIBDIR)/pthnmtyp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/pthnmtyp.o $(LIBDIR)/pthnmtyp.c 


$(libbin)/ptnmvrsn.o : $(LIBDIR)/ptnmvrsn.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ptnmvrsn.o $(LIBDIR)/ptnmvrsn.c 


$(libbin)/rassoc.o : $(LIBDIR)/rassoc.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/rassoc.o $(LIBDIR)/rassoc.c 


$(libbin)/rassocif.o : $(LIBDIR)/rassocif.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/rassocif.o $(LIBDIR)/rassocif.c 


$(libbin)/ratiop.o : $(LIBDIR)/ratiop.c $(LIBHEADERS) \
                $(RUNTIME.H) $(TRIVIALP.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ratiop.o $(LIBDIR)/ratiop.c 


$(libbin)/rdcrnng.o : $(LIBDIR)/rdcrnng.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/rdcrnng.o $(LIBDIR)/rdcrnng.c 


$(libbin)/rdrmsrng.o : $(LIBDIR)/rdrmsrng.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/rdrmsrng.o $(LIBDIR)/rdrmsrng.c 


$(libbin)/readbyte.o : $(LIBDIR)/readbyte.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/readbyte.o $(LIBDIR)/readbyte.c 


$(libbin)/readchar.o : $(LIBDIR)/readchar.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/readchar.o $(LIBDIR)/readchar.c 


$(libbin)/readline.o : $(LIBDIR)/readline.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/readline.o $(LIBDIR)/readline.c 


$(libbin)/realp.o : $(LIBDIR)/realp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(TRIVIALP.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/realp.o $(LIBDIR)/realp.c 


$(libbin)/reduce.o : $(LIBDIR)/reduce.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/reduce.o $(LIBDIR)/reduce.c 


$(libbin)/remprop.o : $(LIBDIR)/remprop.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/remprop.o $(LIBDIR)/remprop.c 


$(libbin)/replace.o : $(LIBDIR)/replace.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SEQMODI.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/replace.o $(LIBDIR)/replace.c 


$(libbin)/rest.o : $(LIBDIR)/rest.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/rest.o $(LIBDIR)/rest.c 


$(libbin)/reverse.o : $(LIBDIR)/reverse.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/reverse.o $(LIBDIR)/reverse.c 


$(libbin)/revppend.o : $(LIBDIR)/revppend.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/revppend.o $(LIBDIR)/revppend.c 


$(libbin)/rmvdplcs.o : $(LIBDIR)/rmvdplcs.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SEQMODI.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/rmvdplcs.o $(LIBDIR)/rmvdplcs.c 


$(libbin)/rnmfil.o : $(LIBDIR)/rnmfil.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/rnmfil.o $(LIBDIR)/rnmfil.c 


$(libbin)/room.o : $(LIBDIR)/room.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/room.o $(LIBDIR)/room.c 


$(libbin)/rplaca.o : $(LIBDIR)/rplaca.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/rplaca.o $(LIBDIR)/rplaca.c 


$(libbin)/rplacd.o : $(LIBDIR)/rplacd.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/rplacd.o $(LIBDIR)/rplacd.c 


$(libbin)/rsscifnt.o : $(LIBDIR)/rsscifnt.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/rsscifnt.o $(LIBDIR)/rsscifnt.c 


$(libbin)/rtionlp.o : $(LIBDIR)/rtionlp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/rtionlp.o $(LIBDIR)/rtionlp.c 


$(libbin)/rwmjrrf.o : $(LIBDIR)/rwmjrrf.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/rwmjrrf.o $(LIBDIR)/rwmjrrf.c 


$(libbin)/s_fill_n.o : $(LIBDIR)/s_fill_n.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/s_fill_n.o $(LIBDIR)/s_fill_n.c 


$(libbin)/s_find_n.o : $(LIBDIR)/s_find_n.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/s_find_n.o $(LIBDIR)/s_find_n.c 


$(libbin)/s_load_n.o : $(LIBDIR)/s_load_n.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/s_load_n.o $(LIBDIR)/s_load_n.c 


$(libbin)/sadjoinn.o : $(LIBDIR)/sadjoinn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sadjoinn.o $(LIBDIR)/sadjoinn.c 


$(libbin)/sassocn.o : $(LIBDIR)/sassocn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sassocn.o $(LIBDIR)/sassocn.c 


$(libbin)/sbgnmdg.o : $(LIBDIR)/sbgnmdg.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sbgnmdg.o $(LIBDIR)/sbgnmdg.c 


$(libbin)/sbnrsls.o : $(LIBDIR)/sbnrsls.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sbnrsls.o $(LIBDIR)/sbnrsls.c 


$(libbin)/sbsfn.o : $(LIBDIR)/sbsfn.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SEQMODI.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sbsfn.o $(LIBDIR)/sbsfn.c 


$(libbin)/sbstttf.o : $(LIBDIR)/sbstttf.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SEQMODI.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sbstttf.o $(LIBDIR)/sbstttf.c 


$(libbin)/scgnrlrr.o : $(LIBDIR)/scgnrlrr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(STAT_ARR.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/scgnrlrr.o $(LIBDIR)/scgnrlrr.c 


$(libbin)/schar.o : $(LIBDIR)/schar.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/schar.o $(LIBDIR)/schar.c 


$(libbin)/schrrlop.o : $(LIBDIR)/schrrlop.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/schrrlop.o $(LIBDIR)/schrrlop.c 


$(libbin)/schrrlpn.o : $(LIBDIR)/schrrlpn.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/schrrlpn.o $(LIBDIR)/schrrlpn.c 


$(libbin)/scngvbgn.o : $(LIBDIR)/scngvbgn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/scngvbgn.o $(LIBDIR)/scngvbgn.c 


$(libbin)/scnswtgc.o : $(LIBDIR)/scnswtgc.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/scnswtgc.o $(LIBDIR)/scnswtgc.c 


$(libbin)/scntfntn.o : $(LIBDIR)/scntfntn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/scntfntn.o $(LIBDIR)/scntfntn.c 


$(libbin)/scountn.o : $(LIBDIR)/scountn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/scountn.o $(LIBDIR)/scountn.c 


$(libbin)/scpvbgnm.o : $(LIBDIR)/scpvbgnm.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/scpvbgnm.o $(LIBDIR)/scpvbgnm.c 


$(libbin)/scuntifn.o : $(LIBDIR)/scuntifn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/scuntifn.o $(LIBDIR)/scuntifn.c 


$(libbin)/sdeleten.o : $(LIBDIR)/sdeleten.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sdeleten.o $(LIBDIR)/sdeleten.c 


$(libbin)/sdjstrrn.o : $(LIBDIR)/sdjstrrn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sdjstrrn.o $(LIBDIR)/sdjstrrn.c 


$(libbin)/sdltfntn.o : $(LIBDIR)/sdltfntn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sdltfntn.o $(LIBDIR)/sdltfntn.c 


$(libbin)/sdltif.o : $(LIBDIR)/sdltif.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SEQMODI.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sdltif.o $(LIBDIR)/sdltif.c 


$(libbin)/sdltifn.o : $(LIBDIR)/sdltifn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sdltifn.o $(LIBDIR)/sdltifn.c 


$(libbin)/sdmsngn.o : $(LIBDIR)/sdmsngn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sdmsngn.o $(LIBDIR)/sdmsngn.c 


$(libbin)/search.o : $(LIBDIR)/search.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/search.o $(LIBDIR)/search.c 


$(libbin)/second.o : $(LIBDIR)/second.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/second.o $(LIBDIR)/second.c 


$(libbin)/set.o : $(LIBDIR)/set.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/set.o $(LIBDIR)/set.c 


$(libbin)/set_char.o : $(LIBDIR)/set_char.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/set_char.o $(LIBDIR)/set_char.c 


$(libbin)/set_cxr.o : $(LIBDIR)/set_cxr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DEFSET.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/set_cxr.o $(LIBDIR)/set_cxr.c 


$(libbin)/set_get.o : $(LIBDIR)/set_get.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/set_get.o $(LIBDIR)/set_get.c 


$(libbin)/set_getf.o : $(LIBDIR)/set_getf.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/set_getf.o $(LIBDIR)/set_getf.c 


$(libbin)/set_nth.o : $(LIBDIR)/set_nth.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/set_nth.o $(LIBDIR)/set_nth.c 


$(libbin)/set_rest.o : $(LIBDIR)/set_rest.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/set_rest.o $(LIBDIR)/set_rest.c 


$(libbin)/setaref0.o : $(LIBDIR)/setaref0.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/setaref0.o $(LIBDIR)/setaref0.c 


$(libbin)/setaref1.o : $(LIBDIR)/setaref1.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/setaref1.o $(LIBDIR)/setaref1.c 


$(libbin)/setaref2.o : $(LIBDIR)/setaref2.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/setaref2.o $(LIBDIR)/setaref2.c 


$(libbin)/setaref3.o : $(LIBDIR)/setaref3.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/setaref3.o $(LIBDIR)/setaref3.c 


$(libbin)/setaref4.o : $(LIBDIR)/setaref4.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/setaref4.o $(LIBDIR)/setaref4.c 


$(libbin)/setaref5.o : $(LIBDIR)/setaref5.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/setaref5.o $(LIBDIR)/setaref5.c 


$(libbin)/setaref6.o : $(LIBDIR)/setaref6.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/setaref6.o $(LIBDIR)/setaref6.c 


$(libbin)/setaref7.o : $(LIBDIR)/setaref7.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/setaref7.o $(LIBDIR)/setaref7.c 


$(libbin)/setf_bit.o : $(LIBDIR)/setf_bit.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/setf_bit.o $(LIBDIR)/setf_bit.c 


$(libbin)/setfaref.o : $(LIBDIR)/setfaref.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/setfaref.o $(LIBDIR)/setfaref.c 


$(libbin)/setfifth.o : $(LIBDIR)/setfifth.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/setfifth.o $(LIBDIR)/setfifth.c 


$(libbin)/setfirst.o : $(LIBDIR)/setfirst.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/setfirst.o $(LIBDIR)/setfirst.c 


$(libbin)/setfsbit.o : $(LIBDIR)/setfsbit.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/setfsbit.o $(LIBDIR)/setfsbit.c 


$(libbin)/setninth.o : $(LIBDIR)/setninth.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/setninth.o $(LIBDIR)/setninth.c 


$(libbin)/setpckge.o : $(LIBDIR)/setpckge.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/setpckge.o $(LIBDIR)/setpckge.c 


$(libbin)/setschar.o : $(LIBDIR)/setschar.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/setschar.o $(LIBDIR)/setschar.c 


$(libbin)/setsixth.o : $(LIBDIR)/setsixth.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/setsixth.o $(LIBDIR)/setsixth.c 


$(libbin)/setsvref.o : $(LIBDIR)/setsvref.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/setsvref.o $(LIBDIR)/setsvref.c 


$(libbin)/settenth.o : $(LIBDIR)/settenth.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/settenth.o $(LIBDIR)/settenth.c 


$(libbin)/setthird.o : $(LIBDIR)/setthird.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/setthird.o $(LIBDIR)/setthird.c 


$(libbin)/seventh.o : $(LIBDIR)/seventh.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/seventh.o $(LIBDIR)/seventh.c 


$(libbin)/sfaref.o : $(LIBDIR)/sfaref.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sfaref.o $(LIBDIR)/sfaref.c 


$(libbin)/sffllpnr.o : $(LIBDIR)/sffllpnr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sffllpnr.o $(LIBDIR)/sffllpnr.c 


$(libbin)/sfindifn.o : $(LIBDIR)/sfindifn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sfindifn.o $(LIBDIR)/sfindifn.c 


$(libbin)/sfllfntn.o : $(LIBDIR)/sfllfntn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sfllfntn.o $(LIBDIR)/sfllfntn.c 


$(libbin)/sfllpnr.o : $(LIBDIR)/sfllpnr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sfllpnr.o $(LIBDIR)/sfllpnr.c 


$(libbin)/sfndfntn.o : $(LIBDIR)/sfndfntn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sfndfntn.o $(LIBDIR)/sfndfntn.c 


$(libbin)/sforval.o : $(LIBDIR)/sforval.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sforval.o $(LIBDIR)/sforval.c 


$(libbin)/sfpaddr.o : $(LIBDIR)/sfpaddr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sfpaddr.o $(LIBDIR)/sfpaddr.c 


$(libbin)/sfptype.o : $(LIBDIR)/sfptype.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sfptype.o $(LIBDIR)/sfptype.c 


$(libbin)/sfstrval.o : $(LIBDIR)/sfstrval.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sfstrval.o $(LIBDIR)/sfstrval.c 


$(libbin)/sfwrvrsn.o : $(LIBDIR)/sfwrvrsn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sfwrvrsn.o $(LIBDIR)/sfwrvrsn.c 


$(libbin)/sgvvbnng.o : $(LIBDIR)/sgvvbnng.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sgvvbnng.o $(LIBDIR)/sgvvbnng.c 


$(libbin)/shrtstnm.o : $(LIBDIR)/shrtstnm.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/shrtstnm.o $(LIBDIR)/shrtstnm.c 


$(libbin)/si_throw.o : $(LIBDIR)/si_throw.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/si_throw.o $(LIBDIR)/si_throw.c 


$(libbin)/sinpckgn.o : $(LIBDIR)/sinpckgn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sinpckgn.o $(LIBDIR)/sinpckgn.c 


$(libbin)/sixth.o : $(LIBDIR)/sixth.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sixth.o $(LIBDIR)/sixth.c 


$(libbin)/skwrdrgp.o : $(LIBDIR)/skwrdrgp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/skwrdrgp.o $(LIBDIR)/skwrdrgp.c 


$(libbin)/slclosen.o : $(LIBDIR)/slclosen.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/slclosen.o $(LIBDIR)/slclosen.c 


$(libbin)/slodrunn.o : $(LIBDIR)/slodrunn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/slodrunn.o $(LIBDIR)/slodrunn.c 


$(libbin)/slopenn.o : $(LIBDIR)/slopenn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/slopenn.o $(LIBDIR)/slopenn.c 


$(libbin)/slplcsn.o : $(LIBDIR)/slplcsn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/slplcsn.o $(LIBDIR)/slplcsn.c 


$(libbin)/slunionn.o : $(LIBDIR)/slunionn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/slunionn.o $(LIBDIR)/slunionn.c 


$(libbin)/slwriten.o : $(LIBDIR)/slwriten.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/slwriten.o $(LIBDIR)/slwriten.c 


$(libbin)/smblfncn.o : $(LIBDIR)/smblfncn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smblfncn.o $(LIBDIR)/smblfncn.c 


$(libbin)/smblplst.o : $(LIBDIR)/smblplst.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smblplst.o $(LIBDIR)/smblplst.c 


$(libbin)/smblvllp.o : $(LIBDIR)/smblvllp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smblvllp.o $(LIBDIR)/smblvllp.c 


$(libbin)/smembern.o : $(LIBDIR)/smembern.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smembern.o $(LIBDIR)/smembern.c 


$(libbin)/smergen.o : $(LIBDIR)/smergen.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smergen.o $(LIBDIR)/smergen.c 


$(libbin)/smjndxx.o : $(LIBDIR)/smjndxx.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smjndxx.o $(LIBDIR)/smjndxx.c 


$(libbin)/smkerryn.o : $(LIBDIR)/smkerryn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smkerryn.o $(LIBDIR)/smkerryn.c 


$(libbin)/smklistn.o : $(LIBDIR)/smklistn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smklistn.o $(LIBDIR)/smklistn.c 


$(libbin)/smkpckgn.o : $(LIBDIR)/smkpckgn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smkpckgn.o $(LIBDIR)/smkpckgn.c 


$(libbin)/smkptnmn.o : $(LIBDIR)/smkptnmn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smkptnmn.o $(LIBDIR)/smkptnmn.c 


$(libbin)/smkrstrg.o : $(LIBDIR)/smkrstrg.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smkrstrg.o $(LIBDIR)/smkrstrg.c 


$(libbin)/smkscrr.o : $(LIBDIR)/smkscrr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smkscrr.o $(LIBDIR)/smkscrr.c 


$(libbin)/smksqncn.o : $(LIBDIR)/smksqncn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smksqncn.o $(LIBDIR)/smksqncn.c 


$(libbin)/smksrngn.o : $(LIBDIR)/smksrngn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smksrngn.o $(LIBDIR)/smksrngn.c 


$(libbin)/smkstbln.o : $(LIBDIR)/smkstbln.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smkstbln.o $(LIBDIR)/smkstbln.c 


$(libbin)/smmbrfnn.o : $(LIBDIR)/smmbrfnn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smmbrfnn.o $(LIBDIR)/smmbrfnn.c 


$(libbin)/smmbrifn.o : $(LIBDIR)/smmbrifn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smmbrifn.o $(LIBDIR)/smmbrifn.c 


$(libbin)/smplbvcp.o : $(LIBDIR)/smplbvcp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smplbvcp.o $(LIBDIR)/smplbvcp.c 


$(libbin)/smplrryp.o : $(LIBDIR)/smplrryp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(TRIVIALP.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smplrryp.o $(LIBDIR)/smplrryp.c 


$(libbin)/smplsngp.o : $(LIBDIR)/smplsngp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smplsngp.o $(LIBDIR)/smplsngp.c 


$(libbin)/smplvcrp.o : $(LIBDIR)/smplvcrp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smplvcrp.o $(LIBDIR)/smplvcrp.c 


$(libbin)/smsmtchn.o : $(LIBDIR)/smsmtchn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smsmtchn.o $(LIBDIR)/smsmtchn.c 


$(libbin)/smvfncll.o : $(LIBDIR)/smvfncll.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smvfncll.o $(LIBDIR)/smvfncll.c 


$(libbin)/smvplcsn.o : $(LIBDIR)/smvplcsn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/smvplcsn.o $(LIBDIR)/smvplcsn.c 


$(libbin)/snbnnjmp.o : $(LIBDIR)/snbnnjmp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snbnnjmp.o $(LIBDIR)/snbnnjmp.c 


$(libbin)/snddbjcp.o : $(LIBDIR)/snddbjcp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(TRIVIALP.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snddbjcp.o $(LIBDIR)/snddbjcp.c 


$(libbin)/sndrdcrp.o : $(LIBDIR)/sndrdcrp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sndrdcrp.o $(LIBDIR)/sndrdcrp.c 


$(libbin)/sngcplzn.o : $(LIBDIR)/sngcplzn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sngcplzn.o $(LIBDIR)/sngcplzn.c 


$(libbin)/snglpn.o : $(LIBDIR)/snglpn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snglpn.o $(LIBDIR)/snglpn.c 


$(libbin)/sngnlpn.o : $(LIBDIR)/sngnlpn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sngnlpn.o $(LIBDIR)/sngnlpn.c 


$(libbin)/sngppnd2.o : $(LIBDIR)/sngppnd2.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sngppnd2.o $(LIBDIR)/sngppnd2.c 


$(libbin)/sngppndn.o : $(LIBDIR)/sngppndn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sngppndn.o $(LIBDIR)/sngppndn.c 


$(libbin)/snngclzn.o : $(LIBDIR)/snngclzn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snngclzn.o $(LIBDIR)/snngclzn.c 


$(libbin)/snngncn.o : $(LIBDIR)/snngncn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snngncn.o $(LIBDIR)/snngncn.c 


$(libbin)/snngpcn.o : $(LIBDIR)/snngpcn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snngpcn.o $(LIBDIR)/snngpcn.c 


$(libbin)/snnlncll.o : $(LIBDIR)/snnlncll.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FUNCALL.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snnlncll.o $(LIBDIR)/snnlncll.c 


$(libbin)/snnrscnn.o : $(LIBDIR)/snnrscnn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snnrscnn.o $(LIBDIR)/snnrscnn.c 


$(libbin)/snpngng.o : $(LIBDIR)/snpngng.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SVARGS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snpngng.o $(LIBDIR)/snpngng.c 


$(libbin)/snpngngs.o : $(LIBDIR)/snpngngs.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SVARGS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snpngngs.o $(LIBDIR)/snpngngs.c 


$(libbin)/snrscnn.o : $(LIBDIR)/snrscnn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snrscnn.o $(LIBDIR)/snrscnn.c 


$(libbin)/snsbsfn.o : $(LIBDIR)/snsbsfn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snsbsfn.o $(LIBDIR)/snsbsfn.c 


$(libbin)/snsbsfnn.o : $(LIBDIR)/snsbsfnn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snsbsfnn.o $(LIBDIR)/snsbsfnn.c 


$(libbin)/snsbsn.o : $(LIBDIR)/snsbsn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snsbsn.o $(LIBDIR)/snsbsn.c 


$(libbin)/snsbstfn.o : $(LIBDIR)/snsbstfn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snsbstfn.o $(LIBDIR)/snsbstfn.c 


$(libbin)/snsdrncn.o : $(LIBDIR)/snsdrncn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snsdrncn.o $(LIBDIR)/snsdrncn.c 


$(libbin)/snslngnn.o : $(LIBDIR)/snslngnn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snslngnn.o $(LIBDIR)/snslngnn.c 


$(libbin)/snsqncfn.o : $(LIBDIR)/snsqncfn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snsqncfn.o $(LIBDIR)/snsqncfn.c 


$(libbin)/snsublsn.o : $(LIBDIR)/snsublsn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snsublsn.o $(LIBDIR)/snsublsn.c 


$(libbin)/snsubstn.o : $(LIBDIR)/snsubstn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snsubstn.o $(LIBDIR)/snsubstn.c 


$(libbin)/sntmisc.o : $(LIBDIR)/sntmisc.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sntmisc.o $(LIBDIR)/sntmisc.c 


$(libbin)/snunionn.o : $(LIBDIR)/snunionn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snunionn.o $(LIBDIR)/snunionn.c 


$(libbin)/snxclvn.o : $(LIBDIR)/snxclvn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/snxclvn.o $(LIBDIR)/snxclvn.c 


$(libbin)/some.o : $(LIBDIR)/some.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SOME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/some.o $(LIBDIR)/some.c 


$(libbin)/sort.o : $(LIBDIR)/sort.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sort.o $(LIBDIR)/sort.c 


$(libbin)/spgvbnng.o : $(LIBDIR)/spgvbnng.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/spgvbnng.o $(LIBDIR)/spgvbnng.c 


$(libbin)/spnmngn.o : $(LIBDIR)/spnmngn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/spnmngn.o $(LIBDIR)/spnmngn.c 


$(libbin)/sprsngrn.o : $(LIBDIR)/sprsngrn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sprsngrn.o $(LIBDIR)/sprsngrn.c 


$(libbin)/spsitinn.o : $(LIBDIR)/spsitinn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/spsitinn.o $(LIBDIR)/spsitinn.c 


$(libbin)/spsnfnn.o : $(LIBDIR)/spsnfnn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/spsnfnn.o $(LIBDIR)/spsnfnn.c 


$(libbin)/spstnfn.o : $(LIBDIR)/spstnfn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/spstnfn.o $(LIBDIR)/spstnfn.c 


$(libbin)/squncp.o : $(LIBDIR)/squncp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(TRIVIALP.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/squncp.o $(LIBDIR)/squncp.c 


$(libbin)/srassocn.o : $(LIBDIR)/srassocn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/srassocn.o $(LIBDIR)/srassocn.c 


$(libbin)/srcrbjcp.o : $(LIBDIR)/srcrbjcp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(TRIVIALP.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/srcrbjcp.o $(LIBDIR)/srcrbjcp.c 


$(libbin)/sreducen.o : $(LIBDIR)/sreducen.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sreducen.o $(LIBDIR)/sreducen.c 


$(libbin)/sremoven.o : $(LIBDIR)/sremoven.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sremoven.o $(LIBDIR)/sremoven.c 


$(libbin)/sreplcen.o : $(LIBDIR)/sreplcen.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sreplcen.o $(LIBDIR)/sreplcen.c 


$(libbin)/srethrow.o : $(LIBDIR)/srethrow.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/srethrow.o $(LIBDIR)/srethrow.c 


$(libbin)/srmovifn.o : $(LIBDIR)/srmovifn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/srmovifn.o $(LIBDIR)/srmovifn.c 


$(libbin)/srmvfntn.o : $(LIBDIR)/srmvfntn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/srmvfntn.o $(LIBDIR)/srmvfntn.c 


$(libbin)/srngcplz.o : $(LIBDIR)/srngcplz.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/srngcplz.o $(LIBDIR)/srngcplz.c 


$(libbin)/srngdncs.o : $(LIBDIR)/srngdncs.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/srngdncs.o $(LIBDIR)/srngdncs.c 


$(libbin)/srngppnd.o : $(LIBDIR)/srngppnd.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/srngppnd.o $(LIBDIR)/srngppnd.c 


$(libbin)/srrcnns.o : $(LIBDIR)/srrcnns.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/srrcnns.o $(LIBDIR)/srrcnns.c 


$(libbin)/srsscfnn.o : $(LIBDIR)/srsscfnn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/srsscfnn.o $(LIBDIR)/srsscfnn.c 


$(libbin)/srsscifn.o : $(LIBDIR)/srsscifn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/srsscifn.o $(LIBDIR)/srsscifn.c 


$(libbin)/srstrvls.o : $(LIBDIR)/srstrvls.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/srstrvls.o $(LIBDIR)/srstrvls.c 


$(libbin)/srwmjrrf.o : $(LIBDIR)/srwmjrrf.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/srwmjrrf.o $(LIBDIR)/srwmjrrf.c 


$(libbin)/ssbsfn.o : $(LIBDIR)/ssbsfn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssbsfn.o $(LIBDIR)/ssbsfn.c 


$(libbin)/ssbsfnn.o : $(LIBDIR)/ssbsfnn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssbsfnn.o $(LIBDIR)/ssbsfnn.c 


$(libbin)/ssbstttn.o : $(LIBDIR)/ssbstttn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssbstttn.o $(LIBDIR)/ssbstttn.c 


$(libbin)/ssdrncn.o : $(LIBDIR)/ssdrncn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssdrncn.o $(LIBDIR)/ssdrncn.c 


$(libbin)/ssearchn.o : $(LIBDIR)/ssearchn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssearchn.o $(LIBDIR)/ssearchn.c 


$(libbin)/ssffncn.o : $(LIBDIR)/ssffncn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssffncn.o $(LIBDIR)/ssffncn.c 


$(libbin)/ssmblncn.o : $(LIBDIR)/ssmblncn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssmblncn.o $(LIBDIR)/ssmblncn.c 


$(libbin)/ssmblpls.o : $(LIBDIR)/ssmblpls.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssmblpls.o $(LIBDIR)/ssmblpls.c 


$(libbin)/ssnggpn.o : $(LIBDIR)/ssnggpn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssnggpn.o $(LIBDIR)/ssnggpn.c 


$(libbin)/ssngncsn.o : $(LIBDIR)/ssngncsn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssngncsn.o $(LIBDIR)/ssngncsn.c 


$(libbin)/ssngngpn.o : $(LIBDIR)/ssngngpn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssngngpn.o $(LIBDIR)/ssngngpn.c 


$(libbin)/ssngnqln.o : $(LIBDIR)/ssngnqln.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssngnqln.o $(LIBDIR)/ssngnqln.c 


$(libbin)/ssngpcsn.o : $(LIBDIR)/ssngpcsn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssngpcsn.o $(LIBDIR)/ssngpcsn.c 


$(libbin)/ssrnggn.o : $(LIBDIR)/ssrnggn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssrnggn.o $(LIBDIR)/ssrnggn.c 


$(libbin)/ssrngln.o : $(LIBDIR)/ssrngln.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssrngln.o $(LIBDIR)/ssrngln.c 


$(libbin)/ssrngqln.o : $(LIBDIR)/ssrngqln.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssrngqln.o $(LIBDIR)/ssrngqln.c 


$(libbin)/ssrnpqr.o : $(LIBDIR)/ssrnpqr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SVARGS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssrnpqr.o $(LIBDIR)/ssrnpqr.c 


$(libbin)/ssscfntn.o : $(LIBDIR)/ssscfntn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssscfntn.o $(LIBDIR)/ssscfntn.c 


$(libbin)/sssmblld.o : $(LIBDIR)/sssmblld.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sssmblld.o $(LIBDIR)/sssmblld.c 


$(libbin)/sssocifn.o : $(LIBDIR)/sssocifn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sssocifn.o $(LIBDIR)/sssocifn.c 


$(libbin)/sstrmgtc.o : $(LIBDIR)/sstrmgtc.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sstrmgtc.o $(LIBDIR)/sstrmgtc.c 


$(libbin)/sstrnggn.o : $(LIBDIR)/sstrnggn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sstrnggn.o $(LIBDIR)/sstrnggn.c 


$(libbin)/sstrngln.o : $(LIBDIR)/sstrngln.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sstrngln.o $(LIBDIR)/sstrngln.c 


$(libbin)/sstrngnn.o : $(LIBDIR)/sstrngnn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sstrngnn.o $(LIBDIR)/sstrngnn.c 


$(libbin)/sstrngqn.o : $(LIBDIR)/sstrngqn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sstrngqn.o $(LIBDIR)/sstrngqn.c 


$(libbin)/ssublisn.o : $(LIBDIR)/ssublisn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssublisn.o $(LIBDIR)/ssublisn.c 


$(libbin)/ssubstfn.o : $(LIBDIR)/ssubstfn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssubstfn.o $(LIBDIR)/ssubstfn.c 


$(libbin)/ssubstn.o : $(LIBDIR)/ssubstn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssubstn.o $(LIBDIR)/ssubstn.c 


$(libbin)/ssubstpn.o : $(LIBDIR)/ssubstpn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssubstpn.o $(LIBDIR)/ssubstpn.c 


$(libbin)/ssvmrvls.o : $(LIBDIR)/ssvmrvls.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssvmrvls.o $(LIBDIR)/ssvmrvls.c 


$(libbin)/ssvvlus.o : $(LIBDIR)/ssvvlus.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssvvlus.o $(LIBDIR)/ssvvlus.c 


$(libbin)/ssxclsvn.o : $(LIBDIR)/ssxclsvn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ssxclsvn.o $(LIBDIR)/ssxclsvn.c 


$(libbin)/statclst.o : $(LIBDIR)/statclst.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/statclst.o $(LIBDIR)/statclst.c 


$(libbin)/statlsts.o : $(LIBDIR)/statlsts.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/statlsts.o $(LIBDIR)/statlsts.c 


$(libbin)/statobjp.o : $(LIBDIR)/statobjp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/statobjp.o $(LIBDIR)/statobjp.c 


$(libbin)/stdffrnc.o : $(LIBDIR)/stdffrnc.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/stdffrnc.o $(LIBDIR)/stdffrnc.c 


$(libbin)/stfaref.o : $(LIBDIR)/stfaref.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/stfaref.o $(LIBDIR)/stfaref.c 


$(libbin)/stffnctn.o : $(LIBDIR)/stffnctn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/stffnctn.o $(LIBDIR)/stffnctn.c 


$(libbin)/stfourth.o : $(LIBDIR)/stfourth.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/stfourth.o $(LIBDIR)/stfourth.c 


$(libbin)/stighth.o : $(LIBDIR)/stighth.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/stighth.o $(LIBDIR)/stighth.c 


$(libbin)/streamp.o : $(LIBDIR)/streamp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/streamp.o $(LIBDIR)/streamp.c 


$(libbin)/string.o : $(LIBDIR)/string.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/string.o $(LIBDIR)/string.c 


$(libbin)/stringp.o : $(LIBDIR)/stringp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/stringp.o $(LIBDIR)/stringp.c 


$(libbin)/strngcrp.o : $(LIBDIR)/strngcrp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/strngcrp.o $(LIBDIR)/strngcrp.c 


$(libbin)/strngpcs.o : $(LIBDIR)/strngpcs.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/strngpcs.o $(LIBDIR)/strngpcs.c 


$(libbin)/strquln.o : $(LIBDIR)/strquln.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/strquln.o $(LIBDIR)/strquln.c 


$(libbin)/stscond.o : $(LIBDIR)/stscond.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/stscond.o $(LIBDIR)/stscond.c 


$(libbin)/stsubsq.o : $(LIBDIR)/stsubsq.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/stsubsq.o $(LIBDIR)/stsubsq.c 


$(libbin)/stsubsq1.o : $(LIBDIR)/stsubsq1.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/stsubsq1.o $(LIBDIR)/stsubsq1.c 


$(libbin)/stsubsq2.o : $(LIBDIR)/stsubsq2.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/stsubsq2.o $(LIBDIR)/stsubsq2.c 


$(libbin)/stsvnth.o : $(LIBDIR)/stsvnth.c $(LIBHEADERS) \
                $(RUNTIME.H) $(DUMMY.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/stsvnth.o $(LIBDIR)/stsvnth.c 


$(libbin)/sttcrr.o : $(LIBDIR)/sttcrr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(STAT_ARR.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sttcrr.o $(LIBDIR)/sttcrr.c 


$(libbin)/sttcbtrr.o : $(LIBDIR)/sttcbtrr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(STAT_ARR.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sttcbtrr.o $(LIBDIR)/sttcbtrr.c 


$(libbin)/sttccrrr.o : $(LIBDIR)/sttccrrr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(STAT_ARR.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sttccrrr.o $(LIBDIR)/sttccrrr.c 


$(libbin)/sttcflot.o : $(LIBDIR)/sttcflot.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sttcflot.o $(LIBDIR)/sttcflot.c 


$(libbin)/sttcpckg.o : $(LIBDIR)/sttcpckg.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sttcpckg.o $(LIBDIR)/sttcpckg.c 


$(libbin)/sttcrto.o : $(LIBDIR)/sttcrto.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sttcrto.o $(LIBDIR)/sttcrto.c 


$(libbin)/sttcsmbl.o : $(LIBDIR)/sttcsmbl.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sttcsmbl.o $(LIBDIR)/sttcsmbl.c 


$(libbin)/stxclsvr.o : $(LIBDIR)/stxclsvr.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/stxclsvr.o $(LIBDIR)/stxclsvr.c 


$(libbin)/sublis.o : $(LIBDIR)/sublis.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/sublis.o $(LIBDIR)/sublis.c 


$(libbin)/subseq.o : $(LIBDIR)/subseq.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/subseq.o $(LIBDIR)/subseq.c 


$(libbin)/subsetp.o : $(LIBDIR)/subsetp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/subsetp.o $(LIBDIR)/subsetp.c 


$(libbin)/subst.o : $(LIBDIR)/subst.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/subst.o $(LIBDIR)/subst.c 


$(libbin)/subst_if.o : $(LIBDIR)/subst_if.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/subst_if.o $(LIBDIR)/subst_if.c 


$(libbin)/substfnt.o : $(LIBDIR)/substfnt.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/substfnt.o $(LIBDIR)/substfnt.c 


$(libbin)/substtut.o : $(LIBDIR)/substtut.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SEQMODI.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/substtut.o $(LIBDIR)/substtut.c 


$(libbin)/subtypep.o : $(LIBDIR)/subtypep.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SUBTYPEP.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/subtypep.o $(LIBDIR)/subtypep.c 


$(libbin)/svref.o : $(LIBDIR)/svref.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/svref.o $(LIBDIR)/svref.c 


$(libbin)/swrsrngn.o : $(LIBDIR)/swrsrngn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/swrsrngn.o $(LIBDIR)/swrsrngn.c 


$(libbin)/swrtlnn.o : $(LIBDIR)/swrtlnn.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/swrtlnn.o $(LIBDIR)/swrtlnn.c 


$(libbin)/swrtstng.o : $(LIBDIR)/swrtstng.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/swrtstng.o $(LIBDIR)/swrtstng.c 


$(libbin)/symblvlu.o : $(LIBDIR)/symblvlu.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/symblvlu.o $(LIBDIR)/symblvlu.c 


$(libbin)/symbolnm.o : $(LIBDIR)/symbolnm.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/symbolnm.o $(LIBDIR)/symbolnm.c 


$(libbin)/symbolp.o : $(LIBDIR)/symbolp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/symbolp.o $(LIBDIR)/symbolp.c 


$(libbin)/tailp.o : $(LIBDIR)/tailp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/tailp.o $(LIBDIR)/tailp.c 


$(libbin)/tenth.o : $(LIBDIR)/tenth.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/tenth.o $(LIBDIR)/tenth.c 


$(libbin)/terpri.o : $(LIBDIR)/terpri.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/terpri.o $(LIBDIR)/terpri.c 


$(libbin)/tfaref.o : $(LIBDIR)/tfaref.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/tfaref.o $(LIBDIR)/tfaref.c 


$(libbin)/third.o : $(LIBDIR)/third.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/third.o $(LIBDIR)/third.c 


$(libbin)/tlllcbl.o : $(LIBDIR)/tlllcbl.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/tlllcbl.o $(LIBDIR)/tlllcbl.c 


$(libbin)/treeequl.o : $(LIBDIR)/treeequl.c $(LIBHEADERS) \
                $(RUNTIME.H) $(LISTS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/treeequl.o $(LIBDIR)/treeequl.c 


$(libbin)/ttlmmrsd.o : $(LIBDIR)/ttlmmrsd.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ttlmmrsd.o $(LIBDIR)/ttlmmrsd.c 


$(libbin)/type_of.o : $(LIBDIR)/type_of.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/type_of.o $(LIBDIR)/type_of.c 


$(libbin)/typep.o : $(LIBDIR)/typep.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/typep.o $(LIBDIR)/typep.c 


$(libbin)/unquetag.o : $(LIBDIR)/unquetag.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/unquetag.o $(LIBDIR)/unquetag.c 


$(libbin)/unredchr.o : $(LIBDIR)/unredchr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/unredchr.o $(LIBDIR)/unredchr.c 


$(libbin)/upprcsp.o : $(LIBDIR)/upprcsp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/upprcsp.o $(LIBDIR)/upprcsp.c 


$(libbin)/upstpckg.o : $(LIBDIR)/upstpckg.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/upstpckg.o $(LIBDIR)/upstpckg.c 


$(libbin)/usmdpnm.o : $(LIBDIR)/usmdpnm.c $(LIBHEADERS) \
                $(RUNTIME.H) $(FILESYS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/usmdpnm.o $(LIBDIR)/usmdpnm.c 


$(libbin)/values.o : $(LIBDIR)/values.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/values.o $(LIBDIR)/values.c 


$(libbin)/vcrpsxnd.o : $(LIBDIR)/vcrpsxnd.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/vcrpsxnd.o $(LIBDIR)/vcrpsxnd.c 


$(libbin)/vctorpop.o : $(LIBDIR)/vctorpop.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/vctorpop.o $(LIBDIR)/vctorpop.c 


$(libbin)/vctrpush.o : $(LIBDIR)/vctrpush.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/vctrpush.o $(LIBDIR)/vctrpush.c 


$(libbin)/vector.o : $(LIBDIR)/vector.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/vector.o $(LIBDIR)/vector.c 


$(libbin)/vectorp.o : $(LIBDIR)/vectorp.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/vectorp.o $(LIBDIR)/vectorp.c 


$(libbin)/vluslist.o : $(LIBDIR)/vluslist.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/vluslist.o $(LIBDIR)/vluslist.c 


$(libbin)/writbyt.o : $(LIBDIR)/writbyt.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/writbyt.o $(LIBDIR)/writbyt.c 


$(libbin)/writechr.o : $(LIBDIR)/writechr.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/writechr.o $(LIBDIR)/writechr.c 


$(libbin)/writlin.o : $(LIBDIR)/writlin.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/writlin.o $(LIBDIR)/writlin.c 


$(libbin)/wrtstrng.o : $(LIBDIR)/wrtstrng.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/wrtstrng.o $(LIBDIR)/wrtstrng.c 


$(libbin)/wtspccrp.o : $(LIBDIR)/wtspccrp.c $(LIBHEADERS) \
                $(RUNTIME.H) $(CHARS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/wtspccrp.o $(LIBDIR)/wtspccrp.c 


$(libbin)/xor.o : $(LIBDIR)/xor.c $(LIBHEADERS) \
                $(RUNTIME.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/xor.o $(LIBDIR)/xor.c 


$(libbin)/y_or_n_p.o : $(LIBDIR)/y_or_n_p.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SVARGS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/y_or_n_p.o $(LIBDIR)/y_or_n_p.c 


$(libbin)/yesnoaux.o : $(LIBDIR)/yesnoaux.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SVARGS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/yesnoaux.o $(LIBDIR)/yesnoaux.c 


$(libbin)/yesornop.o : $(LIBDIR)/yesornop.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SVARGS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/yesornop.o $(LIBDIR)/yesornop.c 


$(libbin)/yornpn.o : $(LIBDIR)/yornpn.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SVARGS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/yornpn.o $(LIBDIR)/yornpn.c 


$(libbin)/ysornopn.o : $(LIBDIR)/ysornopn.c $(LIBHEADERS) \
                $(RUNTIME.H) $(SVARGS.H) 
	$(LIBCCOMPILE) $(OUTCFLAG)$(libbin)/ysornopn.o $(LIBDIR)/ysornopn.c 


# end 

