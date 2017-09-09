/* gram1.c
 * Input file:  grammar1.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gram1.h"


static Object Qtext;               /* text */

/* FILTER-OUT-THE-TEXT-OF-AS-A-SPECIAL-CASE */
Object filter_out_the_text_of_as_a_special_case(form)
    Object form;
{
    Object role, role_is_simple_qm, simple_role;

    x_note_fn_call(194,0);
    role = role_of_designation(form);
    role_is_simple_qm = simple_role_p(role);
    simple_role = role_is_simple_qm ? role : simple_role_of_role(role);
    if (EQ(simple_role,Qtext))
	return VALUES_1(Bad_phrase);
    else
	return VALUES_1(form);
}

static Object Qicon_color;         /* icon-color */

static Object Qstripe_color;       /* stripe-color */

/* FILTER-OUT-REGION-ICON-COLOR */
Object filter_out_region_icon_color(form)
    Object form;
{
    Object role, role_is_simple_qm, local_name_qm;

    x_note_fn_call(194,1);
    role = role_of_designation(form);
    role_is_simple_qm = simple_role_p(role);
    local_name_qm =  !TRUEP(role_is_simple_qm) ? 
	    get_explicitly_specified_local_name_of_role_if_any(role) : Qnil;
    if (EQ(local_name_qm,Qicon_color) || EQ(local_name_qm,Qstripe_color))
	return VALUES_1(Bad_phrase);
    else
	return VALUES_1(form);
}

/* FILTER-OUT-THE-TEXT-OF-AND-REGION-ICON-COLOR */
Object filter_out_the_text_of_and_region_icon_color(form)
    Object form;
{
    Object role, role_is_simple_qm, simple_role, local_name_qm;

    x_note_fn_call(194,2);
    role = role_of_designation(form);
    role_is_simple_qm = simple_role_p(role);
    simple_role = role_is_simple_qm ? role : simple_role_of_role(role);
    local_name_qm =  !TRUEP(role_is_simple_qm) ? 
	    get_explicitly_specified_local_name_of_role_if_any(role) : Qnil;
    if (EQ(simple_role,Qtext) || EQ(local_name_qm,Qicon_color) || 
	    EQ(local_name_qm,Qstripe_color))
	return VALUES_1(Bad_phrase);
    else
	return VALUES_1(form);
}

/* QUOTED-SYMBOL-PHRASE-P */
Object quoted_symbol_phrase_p(phrase)
    Object phrase;
{
    Object temp;
    char temp_1;

    x_note_fn_call(194,3);
    if (CONSP(phrase) && EQ(M_CAR(phrase),Qquote)) {
	temp = M_CDR(phrase);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = M_CDR(phrase);
	temp_1 =  !TRUEP(CDR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = M_CAR(M_CDR(phrase));
	temp = SYMBOLP(temp) ? T : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* REJECT-IF-SEQUENCE-CONSTANT */
Object reject_if_sequence_constant(function_and_args)
    Object function_and_args;
{
    Object arg, ab_loop_list_;
    char temp;

    x_note_fn_call(194,4);
    if (EQ(M_CAR(function_and_args),Qsequence)) {
	arg = Nil;
	ab_loop_list_ = CDR(function_and_args);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	arg = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !(quoted_symbol_phrase_p(arg) || phrase_for_constant_p(arg))) {
	    temp = TRUEP(Nil);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = TRUEP(T);
	goto end_1;
	temp = TRUEP(Qnil);
      end_1:;
    }
    else
	temp = TRUEP(Nil);
    return VALUES_1(temp ? Bad_phrase : function_and_args);
}

static Object Qevaluated_structure;  /* evaluated-structure */

/* REJECT-IF-STRUCTURE-CONSTANT */
Object reject_if_structure_constant(function_and_args)
    Object function_and_args;
{
    Object indicator_arg_phrase, value_arg_phrase, ab_loop_list_, temp;
    char temp_1;

    x_note_fn_call(194,5);
    if (EQ(M_CAR(function_and_args),Qevaluated_structure)) {
	indicator_arg_phrase = Nil;
	value_arg_phrase = Nil;
	ab_loop_list_ = CDR(function_and_args);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
      next_loop:
	indicator_arg_phrase = CAR(ab_loop_list_);
	temp = CDR(ab_loop_list_);
	value_arg_phrase = CAR(temp);
	if ( !(quoted_symbol_phrase_p(value_arg_phrase) || 
		phrase_for_constant_p(value_arg_phrase))) {
	    temp_1 = TRUEP(Nil);
	    goto end_1;
	}
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	goto next_loop;
      end_loop:
	temp_1 = TRUEP(T);
	goto end_1;
	temp_1 = TRUEP(Qnil);
      end_1:;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return VALUES_1(Bad_phrase);
    else
	return VALUES_1(function_and_args);
}

static Object list_constant;       /* # */

/* TRANSPOSE-SUM */
Object transpose_sum(phrase)
    Object phrase;
{
    Object third_1;

    x_note_fn_call(194,6);
    third_1 = THIRD(phrase);
    if (CONSP(third_1) && memq_function(CAR(third_1),list_constant))
	return transpose_sum_1(FIRST(phrase),SECOND(phrase),third_1);
    else
	return VALUES_1(phrase);
}

static Object QPLUS_PLUS_PLUS;     /* |+plus+| */

/* TRANSPOSE-SUM-1 */
Object transpose_sum_1(op,construct,destruct)
    Object op, construct, destruct;
{
    x_note_fn_call(194,7);
    if (ATOM(destruct) ||  !TRUEP(memq_function(FIRST(destruct),
	    list_constant)))
	return phrase_list_3(op,construct,destruct);
    else
	return transpose_sum_1(EQ(FIRST(destruct),QPLUS_PLUS_PLUS) ? Qplus 
		: Qminus,phrase_list_3(op,construct,SECOND(destruct)),
		THIRD(destruct));
}

static Object list_constant_1;     /* # */

/* TRANSPOSE-TERM */
Object transpose_term(phrase)
    Object phrase;
{
    Object third_1;

    x_note_fn_call(194,8);
    third_1 = THIRD(phrase);
    if (CONSP(third_1) && memq_function(CAR(third_1),list_constant_1))
	return transpose_term_1(FIRST(phrase),SECOND(phrase),third_1);
    else
	return VALUES_1(phrase);
}

static Object QTIMES;              /* |*times*| */

/* TRANSPOSE-TERM-1 */
Object transpose_term_1(op,construct,destruct)
    Object op, construct, destruct;
{
    x_note_fn_call(194,9);
    if (ATOM(destruct) ||  !TRUEP(memq_function(FIRST(destruct),
	    list_constant_1)))
	return phrase_list_3(op,construct,destruct);
    else
	return transpose_term_1(EQ(FIRST(destruct),QTIMES) ? Qstar : 
		Qslash,phrase_list_3(op,construct,SECOND(destruct)),
		THIRD(destruct));
}

void grammar1_INIT()
{
    Object temp;
    Object Qtranspose_term, QSL_SLASH_SL, AB_package, Qtranspose_sum, Q_MINUS_;
    Object Qreject_if_structure_constant, Qreject_if_sequence_constant;
    Object string_constant_138, string_constant_137, string_constant_136;
    Object string_constant_135, string_constant_134, string_constant_133;
    Object string_constant_132, string_constant_131, string_constant_130;
    Object string_constant_129, string_constant_128, string_constant_127;
    Object string_constant_126, string_constant_125, string_constant_124;
    Object string_constant_123, string_constant_122, string_constant_121;
    Object string_constant_120, string_constant_119, string_constant_118;
    Object string_constant_117, string_constant_116, string_constant_115;
    Object string_constant_114, string_constant_113, string_constant_112;
    Object string_constant_111, string_constant_110, string_constant_109;
    Object string_constant_108, string_constant_107, string_constant_106;
    Object string_constant_105, string_constant_104, string_constant_103;
    Object string_constant_102, string_constant_101, string_constant_100;
    Object string_constant_99, string_constant_98, string_constant_97;
    Object string_constant_96, string_constant_95, string_constant_94;
    Object string_constant_93, string_constant_92, string_constant_91;
    Object string_constant_90, string_constant_89, string_constant_88;
    Object string_constant_87, string_constant_86, string_constant_85;
    Object string_constant_84, string_constant_83, string_constant_82;
    Object string_constant_81, string_constant_80, string_constant_79;
    Object string_constant_78, string_constant_77, string_constant_76;
    Object string_constant_75, string_constant_74, string_constant_73;
    Object string_constant_72, string_constant_71, string_constant_70;
    Object string_constant_69, string_constant_68, string_constant_67;
    Object string_constant_66, string_constant_65, string_constant_64;
    Object string_constant_63, string_constant_62, string_constant_61;
    Object string_constant_60, string_constant_59, string_constant_58;
    Object string_constant_57, string_constant_56, string_constant_55;
    Object string_constant_54, string_constant_53, string_constant_52;
    Object string_constant_51, string_constant_50, string_constant_49;
    Object string_constant_48, string_constant_47, string_constant_46;
    Object string_constant_45, string_constant_44, string_constant_43;
    Object string_constant_42, string_constant_41, string_constant_40;
    Object string_constant_39, string_constant_38, string_constant_37;
    Object string_constant_36, string_constant_35, string_constant_34;
    Object string_constant_33, string_constant_32, string_constant_31;
    Object string_constant_30, string_constant_29, string_constant_28;
    Object string_constant_27, string_constant_26, string_constant_25;
    Object string_constant_24, string_constant_23, string_constant_22;
    Object string_constant_21, string_constant_20, string_constant_19;
    Object string_constant_18, string_constant_17, string_constant_16;
    Object string_constant_15, string_constant_14, string_constant_13;
    Object string_constant_12, string_constant_11, string_constant_10;
    Object string_constant_9, string_constant_8, string_constant_7;
    Object string_constant_6, string_constant_5, string_constant_4;
    Object string_constant_3, string_constant_2, string_constant_1;
    Object Qrestrict_if_not_slot_edit_feature, Qfilter_out_region_icon_color;
    Object Qfilter_out_the_text_of_and_region_icon_color;
    Object Qfilter_out_the_text_of_as_a_special_case, Qnumber_of_datapoints;
    Object Qcheck_number_of_args, string_constant;
    Object Qconvert_class_qualified_list_to_keyword_symbol;

    x_note_fn_call(194,10);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qconvert_class_qualified_list_to_keyword_symbol = 
	    STATIC_SYMBOL("CONVERT-CLASS-QUALIFIED-LIST-TO-KEYWORD-SYMBOL",
	    AB_package);
    string_constant = 
	    STATIC_STRING("1p1o830Ty1n83-Gy1m9k83=my83*my1n830=yln9l1m830Ty83-2y1m837Sy830Ty1m837Sy1m9k83Zy1o83BFy1n83-Gy1m9k83=my83-6ny1n830=yln9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qconvert_class_qualified_list_to_keyword_symbol);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant));
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qfilter_out_the_text_of_as_a_special_case = 
	    STATIC_SYMBOL("FILTER-OUT-THE-TEXT-OF-AS-A-SPECIAL-CASE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfilter_out_the_text_of_as_a_special_case,
	    STATIC_FUNCTION(filter_out_the_text_of_as_a_special_case,NIL,
	    FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qfilter_out_the_text_of_as_a_special_case);
    Qicon_color = STATIC_SYMBOL("ICON-COLOR",AB_package);
    Qstripe_color = STATIC_SYMBOL("STRIPE-COLOR",AB_package);
    Qfilter_out_region_icon_color = 
	    STATIC_SYMBOL("FILTER-OUT-REGION-ICON-COLOR",AB_package);
    SET_SYMBOL_FUNCTION(Qfilter_out_region_icon_color,
	    STATIC_FUNCTION(filter_out_region_icon_color,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qfilter_out_region_icon_color);
    Qfilter_out_the_text_of_and_region_icon_color = 
	    STATIC_SYMBOL("FILTER-OUT-THE-TEXT-OF-AND-REGION-ICON-COLOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfilter_out_the_text_of_and_region_icon_color,
	    STATIC_FUNCTION(filter_out_the_text_of_and_region_icon_color,
	    NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qfilter_out_the_text_of_and_region_icon_color);
    Qtranspose_sum = STATIC_SYMBOL("TRANSPOSE-SUM",AB_package);
    Qtranspose_term = STATIC_SYMBOL("TRANSPOSE-TERM",AB_package);
    Qcheck_number_of_args = STATIC_SYMBOL("CHECK-NUMBER-OF-ARGS",AB_package);
    Qreject_if_sequence_constant = 
	    STATIC_SYMBOL("REJECT-IF-SEQUENCE-CONSTANT",AB_package);
    Qreject_if_structure_constant = 
	    STATIC_SYMBOL("REJECT-IF-STRUCTURE-CONSTANT",AB_package);
    Qnumber_of_datapoints = STATIC_SYMBOL("NUMBER-OF-DATAPOINTS",AB_package);
    Qrestrict_if_not_slot_edit_feature = 
	    STATIC_SYMBOL("RESTRICT-IF-NOT-SLOT-EDIT-FEATURE",AB_package);
    string_constant_1 = 
	    STATIC_STRING("130Hy1m83=py83-E5y1m83=xy83-tVy1m836Ey83-oUy1m83-E5y83-qpy1m83-tVy83-tZy1m83-oUy83-oYy1o83-E5y1n83-qpy1m9k9l83-pvy1n9lln9m1o83-t");
    string_constant_2 = 
	    STATIC_STRING("Vy1n83-tZy1m9k9l83-tWy1n9lln9m1o83-oUy1n83-oYy1m9k9l83-oVy1n9lln9m1o83-E5y1n83-qpy1m9k9n83-pvy1n9nln9m1o83-tVy1n83-tZy1m9k9n83-t");
    string_constant_3 = 
	    STATIC_STRING("Wy1n9nln9m1o83-oUy1n83-oYy1m9k9n83-oVy1n9nln9m1m83-pvy83-qny1m83-tWy83-tXy1m83-oVy83-oWy1n83-pvy1n83-qny1m9k9l83-pvy1n83f1yln1n8");
    string_constant_4 = 
	    STATIC_STRING("3-tWy1n83-tXy1m9k9l83-tWy1n83f1yln1n83-oVy1n83-oWy1m9k9l83-oVy1n83f1yln1n83-pvy1n83-qny1m9k9n83-pvy1n83f2yln1n83-tWy1n83-tXy1m9k");
    string_constant_5 = 
	    STATIC_STRING("9n83-tWy1n83f2yln1n83-oVy1n83-oWy1m9k9n83-oVy1n83f2yln1m83-qpy83-qny1m83-tZy83-tXy1m83-oYy83-oWy1m83-qpy83-o*y1m83-tZy83-tTy1m83");
    string_constant_6 = 
	    STATIC_STRING("-oYy83-oRy1n83-o*y1m1m9k9l83-qnym1n83-tTy1m1m9k9l83-tXym1n83-oRy1m1m9k9l83-oWym1n83-o*y1m1m9k9n83-qny1m9nm1n83-tTy1m1m9k9n83-tXy");
    string_constant_7 = 
	    STATIC_STRING("1m9nm1n83-oRy1m1m9k9n83-oWy1m9nm1m83-qny83-T9y1m83-tXy83-tKy1m83-oWy83-oGy1o83-qny1n83-T9y1m9k9o83-qoy1n9oln9p1o83-tXy1n83-tKy1m");
    string_constant_8 = 
	    STATIC_STRING("9k9o83-tYy1n9oln9p1o83-oWy1n83-oGy1m9k9o83-oXy1n9oln9p1o83-qny1n83-T9y1m9k9q83-qoy1n9qln9p1o83-tXy1n83-tKy1m9k9q83-tYy1n9qln9p1o");
    string_constant_9 = 
	    STATIC_STRING("83-oWy1n83-oGy1m9k9q83-oXy1n9qln9p1m83-qoy83-T9y1m83-tYy83-tKy1m83-oXy83-oGy1n83-qoy1n83-T9y1m9k9o83-qoy1n83f0yln1n83-tYy1n83-tK");
    string_constant_10 = 
	    STATIC_STRING("y1m9k9o83-tYy1n83f0yln1n83-oXy1n83-oGy1m9k9o83-oXy1n83f0yln1n83-qoy1n83-T9y1m9k9q83-qoy1n83f3yln1n83-tYy1n83-tKy1m9k9q83-tYy1n83");
    string_constant_11 = 
	    STATIC_STRING("f3yln1n83-oXy1n83-oGy1m9k9q83-oXy1n83f3yln1m83-T9y83LCy1m83-tKy83oIy1m83-oGy83nBy1n83-T9y1n83LCy1m9k83f*y83LCy1n83f*yln1n83-tKy1");
    string_constant_12 = 
	    STATIC_STRING("n83oIy1m9k83f*y83oIy1n83f*yln1n83-oGy1n83nBy1m9k83f*y83nBy1n83f*yln1m83LCy833*y1m83oIy830By1m83nBy83F2y1m83LCy83sJy1m83oIy83sJy1");
    string_constant_13 = 
	    STATIC_STRING("m83nBy83sJy1n83LCy1n1m9k83-9y83gFy1m9k83-Aym1n83oIy1n1m9k83-9y83-Fcy1m9k83-Aym1n83nBy1n1m9k83-9y83-Cwy1m9k83-Aym1p83LCy1n832ay1m");
    string_constant_14 = 
	    STATIC_STRING("9k83-9y83Ecy1ll9r9s1p83oIy1n832ay1m9k83-9y83Ecy1ll9r9s1p83nBy1n832ay1m9k83-9y83Ecy1ll9r9s1p83LCy1m832ay836ay2llm9r9s1p83oIy1m832");
    string_constant_15 = 
	    STATIC_STRING("ay83oHy2llm9r9s1p83nBy1m832ay83-Cvy2llm9r9s1o83LCy1n1m9k8s1m9k83-9y83Ecy1l83hBy9t1o83oIy1n1m9k8s1m9k83-9y83Ecy1l83hBy9t1o83nBy1n");
    string_constant_16 = 
	    STATIC_STRING("1m9k8s1m9k83-9y83Ecy1l83hBy9t1o83LCy1m1m9k8s83-Dwy2l83hBym9t1o83oIy1m1m9k8s83-Dwy2l83hBym9t1o83nBy1m1m9k8s83-Dwy2l83hBym9t1n83LC");
    string_constant_17 = 
	    STATIC_STRING("y1n1m9k9u1m9k831Sy1m9k831Ay1l83BTy1n83oIy1n1m9k9u1m9k831Sy1m9k831Ay1l83BTy1n83nBy1n1m9k9u1m9k831Sy1m9k831Ay1l83BTy1n83LCy1o1m9k9");
    string_constant_18 = 
	    STATIC_STRING("u1m9k831Sy1m9k83Yey1m9k831Ay1l83gRy1n83oIy1o1m9k9u1m9k831Sy1m9k83Yey1m9k831Ay1l83gRy1n83nBy1o1m9k9u1m9k831Sy1m9k83Yey1m9k831Ay1l");
    string_constant_19 = 
	    STATIC_STRING("83gRy1n83LCy1o1m9k9u1m9k831Sy1m9k83nay1m9k831Ay1l83gTy1n83oIy1o1m9k9u1m9k831Sy1m9k83nay1m9k831Ay1l83gTy1n83nBy1o1m9k9u1m9k831Sy1");
    string_constant_20 = 
	    STATIC_STRING("m9k83nay1m9k831Ay1l83gTy1n83LCy1p1m9k9u1m9k831Sy1m9k83nay1m9k83Yey1m9k831Ay1l83gSy1n83oIy1p1m9k9u1m9k831Sy1m9k83nay1m9k83Yey1m9k");
    string_constant_21 = 
	    STATIC_STRING("831Ay1l83gSy1n83nBy1p1m9k9u1m9k831Sy1m9k83nay1m9k83Yey1m9k831Ay1l83gSy1n83LCy1o1m9k9u1m9k831Sy1m9k8l1m9k831Ay1l83gVy1n83oIy1o1m9");
    string_constant_22 = 
	    STATIC_STRING("k9u1m9k831Sy1m9k8l1m9k831Ay1l83gVy1n83nBy1o1m9k9u1m9k831Sy1m9k8l1m9k831Ay1l83gVy1n83LCy1p1m9k9u1m9k831Sy1m9k8l1m9k83Yey1m9k831Ay");
    string_constant_23 = 
	    STATIC_STRING("1l83gUy1n83oIy1p1m9k9u1m9k831Sy1m9k8l1m9k83Yey1m9k831Ay1l83gUy1n83nBy1p1m9k9u1m9k831Sy1m9k8l1m9k83Yey1m9k831Ay1l83gUy1n83LCy1n1m");
    string_constant_24 = 
	    STATIC_STRING("9k9u1m9k831Sy1m9k836Vy1m836Vy1l83BTy1n83oIy1n1m9k9u1m9k831Sy1m9k836Vy1m836Vy1l83BTy1n83nBy1n1m9k9u1m9k831Sy1m9k836Vy1m836Vy1l83B");
    string_constant_25 = 
	    STATIC_STRING("Ty1n83LCy1n1m9k9u1m9k831Sy1m9k83E+y1m83E+y1l83BTy1n83oIy1n1m9k9u1m9k831Sy1m9k83E+y1m83E+y1l83BTy1n83nBy1n1m9k9u1m9k831Sy1m9k83E+");
    string_constant_26 = 
	    STATIC_STRING("y1m83E+y1l83BTy1n83LCy1q1m9k9u1m9k831Sy1m9k833+y1m9k83-Ty1m9k9u1m9k83E+y1m83gay1l83BTy1n83oIy1q1m9k9u1m9k831Sy1m9k833+y1m9k83-Ty");
    string_constant_27 = 
	    STATIC_STRING("1m9k9u1m9k83E+y1m83gay1l83BTy1n83nBy1q1m9k9u1m9k831Sy1m9k833+y1m9k83-Ty1m9k9u1m9k83E+y1m83gay1l83BTy1n83LCy1q1m9k9u1m9k831Sy1m9k");
    string_constant_28 = 
	    STATIC_STRING("833+y1m9k83-Ty1m9k9u1m9k83Fty1m83gby1l83BTy1n83oIy1q1m9k9u1m9k831Sy1m9k833+y1m9k83-Ty1m9k9u1m9k83Fty1m83gby1l83BTy1n83nBy1q1m9k9");
    string_constant_29 = 
	    STATIC_STRING("u1m9k831Sy1m9k833+y1m9k83-Ty1m9k9u1m9k83Fty1m83gby1l83BTy1n83LCy1n1m9k9u1m9k831Sy1m9k833Oy1m833Oy1l83BTy1n83oIy1n1m9k9u1m9k831Sy");
    string_constant_30 = 
	    STATIC_STRING("1m9k833Oy1m833Oy1l83BTy1n83nBy1n1m9k9u1m9k831Sy1m9k833Oy1m833Oy1l83BTy1n83LCy1n1m9k9u1m9k831Sy1m9k833Ty1m833Ty1l83BTy1n83oIy1n1m");
    string_constant_31 = 
	    STATIC_STRING("9k9u1m9k831Sy1m9k833Ty1m833Ty1l83BTy1n83nBy1n1m9k9u1m9k831Sy1m9k833Ty1m833Ty1l83BTy1n83LCy1n1m9k9u1m9k831Sy1m9k9v1m9v1l83BTy1n83");
    string_constant_32 = 
	    STATIC_STRING("oIy1n1m9k9u1m9k831Sy1m9k9v1m9v1l83BTy1n83nBy1n1m9k9u1m9k831Sy1m9k9v1m9v1l83BTy1n83LCy1s1m9k9u1m9k9w1m9k83-Ty1m9k9u1m9k83C4y83C-y");
    string_constant_33 = 
	    STATIC_STRING("1m9k83*ly836ay2l83LZys1n83oIy1s1m9k9u1m9k9w1m9k83-Ty1m9k9u1m9k83C4y83C-y1m9k83*ly83oHy2l83LZys1n83nBy1s1m9k9u1m9k9w1m9k83-Ty1m9k");
    string_constant_34 = 
	    STATIC_STRING("9u1m9k83C4y83C-y1m9k83*ly83-Cvy2l83LZys1n83LCy1t1m9k9u1m9k83-=oy1m9k83*ly1m9k83-Ty833*y1m9k83*5y1m9k83-Ty83f7y1m9k83pey1n83-Zeyp");
    string_constant_35 = 
	    STATIC_STRING("s1n83oIy1t1m9k9u1m9k83-=oy1m9k83*ly1m9k83-Ty830By1m9k83*5y1m9k83-Ty83-Fay1m9k83pey1n83-Zeyps1n83nBy1t1m9k9u1m9k83-=oy1m9k83*ly1m");
    string_constant_36 = 
	    STATIC_STRING("9k83-Ty83F2y1m9k83*5y1m9k83-Ty83-Cuy1m9k83pey1n83-Zeyps1n83LCy1s1m9k9u1m9k83*ly1m9k83-Ty833*y1m9k83*5y1m9k83-Ty83f7y1m9k83pey1n8");
    string_constant_37 = 
	    STATIC_STRING("3-*Nyor1n83oIy1s1m9k9u1m9k83*ly1m9k83-Ty830By1m9k83*5y1m9k83-Ty83-Fay1m9k83pey1n83-*Nyor1n83nBy1s1m9k9u1m9k83*ly1m9k83-Ty83F2y1m");
    string_constant_38 = 
	    STATIC_STRING("9k83*5y1m9k83-Ty83-Cuy1m9k83pey1n83-*Nyor1n83LCy1t1m9k9u1m9k83*ly1m9k83-Ty833*y1m9k83*5y1m9k83-Ty83lly83gYy1m9k83pey1n83-GSyor1n");
    string_constant_39 = 
	    STATIC_STRING("83oIy1t1m9k9u1m9k83*ly1m9k83-Ty830By1m9k83*5y1m9k83-Ty83lly83gYy1m9k83pey1n83-GSyor1n83nBy1t1m9k9u1m9k83*ly1m9k83-Ty83F2y1m9k83*");
    string_constant_40 = 
	    STATIC_STRING("5y1m9k83-Ty83lly83gYy1m9k83pey1n83-GSyor1n83LCy1u1m9k9u1m9k83g2y1m9k831Ay1m9k83-Ty833*y1m9k83*5y1m9k83-Ty83lly83gYy1m9k83pey1n83");
    string_constant_41 = 
	    STATIC_STRING("-Muyps1n83oIy1u1m9k9u1m9k83g2y1m9k831Ay1m9k83-Ty830By1m9k83*5y1m9k83-Ty83lly83gYy1m9k83pey1n83-Muyps1n83nBy1u1m9k9u1m9k83g2y1m9k");
    string_constant_42 = 
	    STATIC_STRING("831Ay1m9k83-Ty83F2y1m9k83*5y1m9k83-Ty83lly83gYy1m9k83pey1n83-Muyps1n83LCy1t1m9k9u1m9k83kgy1m9k83*ly1m9k83-Ty833*y1m9k83-Rty1m9k9");
    string_constant_43 = 
	    STATIC_STRING("u1m9k9x83-1sy1n83-6Vypt1n83oIy1t1m9k9u1m9k83kgy1m9k83*ly1m9k83-Ty830By1m9k83-Rty1m9k9u1m9k9x83-Fgy1n83-6Vypt1n83nBy1t1m9k9u1m9k8");
    string_constant_44 = 
	    STATIC_STRING("3kgy1m9k83*ly1m9k83-Ty83F2y1m9k83-Rty1m9k9u1m9k9x83-Cxy1n83-6Vypt1n83LCy1x1m9k9u1m9k83kgy1m9k83*ly1m9k83-Ty833*y1m9k83-Rty1m9k9u");
    string_constant_45 = 
	    STATIC_STRING("83f7y1m9k83-SZy1m9k83=Fy1m9k9u1m9k83g2y1m9k831Ay1o83-6Vyps83=Oy1n83oIy1x1m9k9u1m9k83kgy1m9k83*ly1m9k83-Ty830By1m9k83-Rty1m9k9u83");
    string_constant_46 = 
	    STATIC_STRING("-Fay1m9k83-SZy1m9k83=Fy1m9k9u1m9k83g2y1m9k831Ay1o83-6Vyps83=Oy1n83nBy1x1m9k9u1m9k83kgy1m9k83*ly1m9k83-Ty83F2y1m9k83-Rty1m9k9u83-");
    string_constant_47 = 
	    STATIC_STRING("Cuy1m9k83-SZy1m9k83=Fy1m9k9u1m9k83g2y1m9k831Ay1o83-6Vyps83=Oy1n83LCy1v1m9k9u1m9k83kgy1m9k83*ly1m9k83-Ty833*y1m9k837my83f7y1m9k83");
    string_constant_48 = 
	    STATIC_STRING("pey1m9k83-ty83f7y1m9k83pey1o83-6Vypru1n83oIy1v1m9k9u1m9k83kgy1m9k83*ly1m9k83-Ty830By1m9k837my83-Fay1m9k83pey1m9k83-ty83-Fay1m9k8");
    string_constant_49 = 
	    STATIC_STRING("3pey1o83-6Vypru1n83nBy1v1m9k9u1m9k83kgy1m9k83*ly1m9k83-Ty83F2y1m9k837my83-Cuy1m9k83pey1m9k83-ty83-Cuy1m9k83pey1o83-6Vypru1n83LCy");
    string_constant_50 = 
	    STATIC_STRING("1t1m9k9u1m9k83Dmy1m9k83*ly1m9k83-Ty833*y1m9k83-Rty1m9k9u1m9k9x83-1sy1n83-6oypt1n83oIy1t1m9k9u1m9k83Dmy1m9k83*ly1m9k83-Ty830By1m9");
    string_constant_51 = 
	    STATIC_STRING("k83-Rty1m9k9u1m9k9x83-Fgy1n83-6oypt1n83nBy1t1m9k9u1m9k83Dmy1m9k83*ly1m9k83-Ty83F2y1m9k83-Rty1m9k9u1m9k9x83-Cxy1n83-6oypt1n83LCy1");
    string_constant_52 = 
	    STATIC_STRING("x1m9k9u1m9k83Dmy1m9k83*ly1m9k83-Ty833*y1m9k83-Rty1m9k9u83f7y1m9k83-SZy1m9k83=Fy1m9k9u1m9k83g2y1m9k831Ay1o83-6oyps83=Oy1n83oIy1x1");
    string_constant_53 = 
	    STATIC_STRING("m9k9u1m9k83Dmy1m9k83*ly1m9k83-Ty830By1m9k83-Rty1m9k9u83-Fay1m9k83-SZy1m9k83=Fy1m9k9u1m9k83g2y1m9k831Ay1o83-6oyps83=Oy1n83nBy1x1m");
    string_constant_54 = 
	    STATIC_STRING("9k9u1m9k83Dmy1m9k83*ly1m9k83-Ty83F2y1m9k83-Rty1m9k9u83-Cuy1m9k83-SZy1m9k83=Fy1m9k9u1m9k83g2y1m9k831Ay1o83-6oyps83=Oy1n83LCy1v1m9");
    string_constant_55 = 
	    STATIC_STRING("k9u1m9k83Dmy1m9k83*ly1m9k83-Ty833*y1m9k837my83f7y1m9k83pey1m9k83-ty83f7y1m9k83pey1o83-6oypru1n83oIy1v1m9k9u1m9k83Dmy1m9k83*ly1m9");
    string_constant_56 = 
	    STATIC_STRING("k83-Ty830By1m9k837my83-Fay1m9k83pey1m9k83-ty83-Fay1m9k83pey1o83-6oypru1n83nBy1v1m9k9u1m9k83Dmy1m9k83*ly1m9k83-Ty83F2y1m9k837my83");
    string_constant_57 = 
	    STATIC_STRING("-Cuy1m9k83pey1m9k83-ty83-Cuy1m9k83pey1o83-6oypru1n83LCy1t1m9k9u1m9k83fKy1m9k83*ly1m9k83-Ty833*y1m9k83-Rty1m9k9u1m9k9x83-1sy1n83-");
    string_constant_58 = 
	    STATIC_STRING("KJypt1n83oIy1t1m9k9u1m9k83fKy1m9k83*ly1m9k83-Ty830By1m9k83-Rty1m9k9u1m9k9x83-Fgy1n83-KJypt1n83nBy1t1m9k9u1m9k83fKy1m9k83*ly1m9k8");
    string_constant_59 = 
	    STATIC_STRING("3-Ty83F2y1m9k83-Rty1m9k9u1m9k9x83-Cxy1n83-KJypt1n83LCy1x1m9k9u1m9k83fKy1m9k83*ly1m9k83-Ty833*y1m9k83-Rty1m9k9u83f7y1m9k83-SZy1m9");
    string_constant_60 = 
	    STATIC_STRING("k83=Fy1m9k9u1m9k83g2y1m9k831Ay1o83-KJyps83=Oy1n83oIy1x1m9k9u1m9k83fKy1m9k83*ly1m9k83-Ty830By1m9k83-Rty1m9k9u83-Fay1m9k83-SZy1m9k");
    string_constant_61 = 
	    STATIC_STRING("83=Fy1m9k9u1m9k83g2y1m9k831Ay1o83-KJyps83=Oy1n83nBy1x1m9k9u1m9k83fKy1m9k83*ly1m9k83-Ty83F2y1m9k83-Rty1m9k9u83-Cuy1m9k83-SZy1m9k8");
    string_constant_62 = 
	    STATIC_STRING("3=Fy1m9k9u1m9k83g2y1m9k831Ay1o83-KJyps83=Oy1n83LCy1v1m9k9u1m9k83fKy1m9k83*ly1m9k83-Ty833*y1m9k837my83f7y1m9k83pey1m9k83-ty83f7y1");
    string_constant_63 = 
	    STATIC_STRING("m9k83pey1o83-KJypru1n83oIy1v1m9k9u1m9k83fKy1m9k83*ly1m9k83-Ty830By1m9k837my83-Fay1m9k83pey1m9k83-ty83-Fay1m9k83pey1o83-KJypru1n8");
    string_constant_64 = 
	    STATIC_STRING("3nBy1v1m9k9u1m9k83fKy1m9k83*ly1m9k83-Ty83F2y1m9k837my83-Cuy1m9k83pey1m9k83-ty83-Cuy1m9k83pey1o83-KJypru1n83LCy1v1m9k9u1m9k83-E5y");
    string_constant_65 = 
	    STATIC_STRING("1m9k83-Ty1m9k9u1m9k9y1m9k83-Ty833*y1m9k83-Rty1m9k9u1m9k9x83-1sy1n83-pwyrv1n83oIy1v1m9k9u1m9k83-E5y1m9k83-Ty1m9k9u1m9k9y1m9k83-Ty");
    string_constant_66 = 
	    STATIC_STRING("830By1m9k83-Rty1m9k9u1m9k9x83-Fgy1n83-pwyrv1n83nBy1v1m9k9u1m9k83-E5y1m9k83-Ty1m9k9u1m9k9y1m9k83-Ty83F2y1m9k83-Rty1m9k9u1m9k9x83-");
    string_constant_67 = 
	    STATIC_STRING("Cxy1n83-pwyrv1n83LCy1z1m9k9u1m9k83-E5y1m9k83-Ty1m9k9u1m9k9y1m9k83-Ty833*y1m9k83-Rty1m9k9u83f7y1m9k83-SZy1m9k83=Fy1m9k9u1m9k83g2y");
    string_constant_68 = 
	    STATIC_STRING("1m9k831Ay1o83-pwyru83=Oy1n83oIy1z1m9k9u1m9k83-E5y1m9k83-Ty1m9k9u1m9k9y1m9k83-Ty830By1m9k83-Rty1m9k9u83-Fay1m9k83-SZy1m9k83=Fy1m9");
    string_constant_69 = 
	    STATIC_STRING("k9u1m9k83g2y1m9k831Ay1o83-pwyru83=Oy1n83nBy1z1m9k9u1m9k83-E5y1m9k83-Ty1m9k9u1m9k9y1m9k83-Ty83F2y1m9k83-Rty1m9k9u83-Cuy1m9k83-SZy");
    string_constant_70 = 
	    STATIC_STRING("1m9k83=Fy1m9k9u1m9k83g2y1m9k831Ay1o83-pwyru83=Oy1n83LCy1x1m9k9u1m9k83-E5y1m9k83-Ty1m9k9u1m9k9y1m9k83-Ty833*y1m9k837my83f7y1m9k83");
    string_constant_71 = 
	    STATIC_STRING("pey1m9k83-ty83f7y1m9k83pey1o83-pwyrtw1n83oIy1x1m9k9u1m9k83-E5y1m9k83-Ty1m9k9u1m9k9y1m9k83-Ty830By1m9k837my83-Fay1m9k83pey1m9k83-");
    string_constant_72 = 
	    STATIC_STRING("ty83-Fay1m9k83pey1o83-pwyrtw1n83nBy1x1m9k9u1m9k83-E5y1m9k83-Ty1m9k9u1m9k9y1m9k83-Ty83F2y1m9k837my83-Cuy1m9k83pey1m9k83-ty83-Cuy1");
    string_constant_73 = 
	    STATIC_STRING("m9k83pey1o83-pwyrtw1n83LCy1t1m9k9u1m9k837Ry1m9k83-R3y1m9k83-Ty833*y1m9k83-Rty1m9k9u1m9k9x83-1sy1n83-p9ypt1n83oIy1t1m9k9u1m9k837R");
    string_constant_74 = 
	    STATIC_STRING("y1m9k83-R3y1m9k83-Ty830By1m9k83-Rty1m9k9u1m9k9x83-Fgy1n83-p9ypt1n83nBy1t1m9k9u1m9k837Ry1m9k83-R3y1m9k83-Ty83F2y1m9k83-Rty1m9k9u1");
    string_constant_75 = 
	    STATIC_STRING("m9k9x83-Cxy1n83-p9ypt1n83LCy1x1m9k9u1m9k837Ry1m9k83-R3y1m9k83-Ty833*y1m9k83-Rty1m9k9u83f7y1m9k83-SZy1m9k83=Fy1m9k9u1m9k83g2y1m9k");
    string_constant_76 = 
	    STATIC_STRING("831Ay1o83-p9yps83=Oy1n83oIy1x1m9k9u1m9k837Ry1m9k83-R3y1m9k83-Ty830By1m9k83-Rty1m9k9u83-Fay1m9k83-SZy1m9k83=Fy1m9k9u1m9k83g2y1m9k");
    string_constant_77 = 
	    STATIC_STRING("831Ay1o83-p9yps83=Oy1n83nBy1x1m9k9u1m9k837Ry1m9k83-R3y1m9k83-Ty83F2y1m9k83-Rty1m9k9u83-Cuy1m9k83-SZy1m9k83=Fy1m9k9u1m9k83g2y1m9k");
    string_constant_78 = 
	    STATIC_STRING("831Ay1o83-p9yps83=Oy1n83LCy1v1m9k9u1m9k837Ry1m9k83-R3y1m9k83-Ty833*y1m9k837my83f7y1m9k83pey1m9k83-ty83f7y1m9k83pey1o83-p9ypru1n8");
    string_constant_79 = 
	    STATIC_STRING("3oIy1v1m9k9u1m9k837Ry1m9k83-R3y1m9k83-Ty830By1m9k837my83-Fay1m9k83pey1m9k83-ty83-Fay1m9k83pey1o83-p9ypru1n83nBy1v1m9k9u1m9k837Ry");
    string_constant_80 = 
	    STATIC_STRING("1m9k83-R3y1m9k83-Ty83F2y1m9k837my83-Cuy1m9k83pey1m9k83-ty83-Cuy1m9k83pey1o83-p9ypru1n83LCy1w1m9k9u1m9k83-k-y1m9k83-Ty1m9k83=cy1m");
    string_constant_81 = 
	    STATIC_STRING("9k83Xly83-D1y1m9k83-Ty833*y1m9k83-Rty1m9k9u1m9k9x83-1sy1o83-k*ys1m9kqw1n83oIy1w1m9k9u1m9k83-k-y1m9k83-Ty1m9k83=cy1m9k83Xly83-D1y");
    string_constant_82 = 
	    STATIC_STRING("1m9k83-Ty830By1m9k83-Rty1m9k9u1m9k9x83-Fgy1o83-k*ys1m9kqw1n83nBy1w1m9k9u1m9k83-k-y1m9k83-Ty1m9k83=cy1m9k83Xly83-D1y1m9k83-Ty83F2");
    string_constant_83 = 
	    STATIC_STRING("y1m9k83-Rty1m9k9u1m9k9x83-Cxy1o83-k*ys1m9kqw1n83LCy13Cy1m9k9u1m9k83-k-y1m9k83-Ty1m9k83=cy1m9k83Xly83-D1y1m9k83-Ty833*y1m9k83-Rty");
    string_constant_84 = 
	    STATIC_STRING("1m9k9u83f7y1m9k83-SZy1m9k83=Fy1m9k9u1m9k83g2y1m9k831Ay1p83-k*ys1m9kqv83=Oy1n83oIy13Cy1m9k9u1m9k83-k-y1m9k83-Ty1m9k83=cy1m9k83Xly");
    string_constant_85 = 
	    STATIC_STRING("83-D1y1m9k83-Ty830By1m9k83-Rty1m9k9u83-Fay1m9k83-SZy1m9k83=Fy1m9k9u1m9k83g2y1m9k831Ay1p83-k*ys1m9kqv83=Oy1n83nBy13Cy1m9k9u1m9k83");
    string_constant_86 = 
	    STATIC_STRING("-k-y1m9k83-Ty1m9k83=cy1m9k83Xly83-D1y1m9k83-Ty83F2y1m9k83-Rty1m9k9u83-Cuy1m9k83-SZy1m9k83=Fy1m9k9u1m9k83g2y1m9k831Ay1p83-k*ys1m9");
    string_constant_87 = 
	    STATIC_STRING("kqv83=Oy1n83LCy1y1m9k9u1m9k83-k-y1m9k83-Ty1m9k83=cy1m9k83Xly83-D1y1m9k83-Ty833*y1m9k837my83f7y1m9k83pey1m9k83-ty83f7y1m9k83pey1p");
    string_constant_88 = 
	    STATIC_STRING("83-k*ys1m9kqux1n83oIy1y1m9k9u1m9k83-k-y1m9k83-Ty1m9k83=cy1m9k83Xly83-D1y1m9k83-Ty830By1m9k837my83-Fay1m9k83pey1m9k83-ty83-Fay1m9");
    string_constant_89 = 
	    STATIC_STRING("k83pey1p83-k*ys1m9kqux1n83nBy1y1m9k9u1m9k83-k-y1m9k83-Ty1m9k83=cy1m9k83Xly83-D1y1m9k83-Ty83F2y1m9k837my83-Cuy1m9k83pey1m9k83-ty8");
    string_constant_90 = 
	    STATIC_STRING("3-Cuy1m9k83pey1p83-k*ys1m9kqux1n83LCy1u1m9k9u1m9k83-ZUy1m9k83*Xy83ldy1m9k83-Ty833*y1m9k83-Rty1m9k9u1m9k9x83-1sy1o83-ZUyq1m9kou1n");
    string_constant_91 = 
	    STATIC_STRING("83oIy1u1m9k9u1m9k83-ZUy1m9k83*Xy83ldy1m9k83-Ty830By1m9k83-Rty1m9k9u1m9k9x83-Fgy1o83-ZUyq1m9kou1n83nBy1u1m9k9u1m9k83-ZUy1m9k83*Xy");
    string_constant_92 = 
	    STATIC_STRING("83ldy1m9k83-Ty83F2y1m9k83-Rty1m9k9u1m9k9x83-Cxy1o83-ZUyq1m9kou1n83LCy1y1m9k9u1m9k83-ZUy1m9k83*Xy83ldy1m9k83-Ty833*y1m9k83-Rty1m9");
    string_constant_93 = 
	    STATIC_STRING("k9u83f7y1m9k83-SZy1m9k83=Fy1m9k9u1m9k83g2y1m9k831Ay1p83-ZUyq1m9kot83=Oy1n83oIy1y1m9k9u1m9k83-ZUy1m9k83*Xy83ldy1m9k83-Ty830By1m9k");
    string_constant_94 = 
	    STATIC_STRING("83-Rty1m9k9u83-Fay1m9k83-SZy1m9k83=Fy1m9k9u1m9k83g2y1m9k831Ay1p83-ZUyq1m9kot83=Oy1n83nBy1y1m9k9u1m9k83-ZUy1m9k83*Xy83ldy1m9k83-T");
    string_constant_95 = 
	    STATIC_STRING("y83F2y1m9k83-Rty1m9k9u83-Cuy1m9k83-SZy1m9k83=Fy1m9k9u1m9k83g2y1m9k831Ay1p83-ZUyq1m9kot83=Oy1n83LCy1w1m9k9u1m9k83-ZUy1m9k83*Xy83l");
    string_constant_96 = 
	    STATIC_STRING("dy1m9k83-Ty833*y1m9k837my83f7y1m9k83pey1m9k83-ty83f7y1m9k83pey1p83-ZUyq1m9kosv1n83oIy1w1m9k9u1m9k83-ZUy1m9k83*Xy83ldy1m9k83-Ty83");
    string_constant_97 = 
	    STATIC_STRING("0By1m9k837my83-Fay1m9k83pey1m9k83-ty83-Fay1m9k83pey1p83-ZUyq1m9kosv1n83nBy1w1m9k9u1m9k83-ZUy1m9k83*Xy83ldy1m9k83-Ty83F2y1m9k837m");
    string_constant_98 = 
	    STATIC_STRING("y83-Cuy1m9k83pey1m9k83-ty83-Cuy1m9k83pey1p83-ZUyq1m9kosv1n83LCy1r1m9k9u1m9k83-Hy1m9k83-Ty1m9k836xy1m9k83ucy1m9k83*Xy833*y1m9zr1n");
    string_constant_99 = 
	    STATIC_STRING("83oIy1r1m9k9u1m9k83-Hy1m9k83-Ty1m9k836xy1m9k83ucy1m9k83*Xy830By1m9zr1n83nBy1r1m9k9u1m9k83-Hy1m9k83-Ty1m9k836xy1m9k83ucy1m9k83*Xy");
    string_constant_100 = 
	    STATIC_STRING("83F2y1m9zr1n83LCy1v1m9k9u1m9k83-Hy1m9k83-Ty1m9k836xy1m9k83ucy1m9k83*Xy833*y1m9k83-Rty1m9k9u1m9k9x83-1sy1n9zrv1n83oIy1v1m9k9u1m9k");
    string_constant_101 = 
	    STATIC_STRING("83-Hy1m9k83-Ty1m9k836xy1m9k83ucy1m9k83*Xy830By1m9k83-Rty1m9k9u1m9k9x83-Fgy1n9zrv1n83nBy1v1m9k9u1m9k83-Hy1m9k83-Ty1m9k836xy1m9k83");
    string_constant_102 = 
	    STATIC_STRING("ucy1m9k83*Xy83F2y1m9k83-Rty1m9k9u1m9k9x83-Cxy1n9zrv1n83LCy1z1m9k9u1m9k83-Hy1m9k83-Ty1m9k836xy1m9k83ucy1m9k83*Xy833*y1m9k83-Rty1m");
    string_constant_103 = 
	    STATIC_STRING("9k9u83f7y1m9k83-SZy1m9k83=Fy1m9k9u1m9k83g2y1m9k831Ay1o9zru83=Oy1n83oIy1z1m9k9u1m9k83-Hy1m9k83-Ty1m9k836xy1m9k83ucy1m9k83*Xy830By");
    string_constant_104 = 
	    STATIC_STRING("1m9k83-Rty1m9k9u83-Fay1m9k83-SZy1m9k83=Fy1m9k9u1m9k83g2y1m9k831Ay1o9zru83=Oy1n83nBy1z1m9k9u1m9k83-Hy1m9k83-Ty1m9k836xy1m9k83ucy1");
    string_constant_105 = 
	    STATIC_STRING("m9k83*Xy83F2y1m9k83-Rty1m9k9u83-Cuy1m9k83-SZy1m9k83=Fy1m9k9u1m9k83g2y1m9k831Ay1o9zru83=Oy1n83LCy1x1m9k9u1m9k83-Hy1m9k83-Ty1m9k83");
    string_constant_106 = 
	    STATIC_STRING("6xy1m9k83ucy1m9k83*Xy833*y1m9k837my83f7y1m9k83pey1m9k83-ty83f7y1m9k83pey1o9zrtw1n83oIy1x1m9k9u1m9k83-Hy1m9k83-Ty1m9k836xy1m9k83u");
    string_constant_107 = 
	    STATIC_STRING("cy1m9k83*Xy830By1m9k837my83-Fay1m9k83pey1m9k83-ty83-Fay1m9k83pey1o9zrtw1n83nBy1x1m9k9u1m9k83-Hy1m9k83-Ty1m9k836xy1m9k83ucy1m9k83");
    string_constant_108 = 
	    STATIC_STRING("*Xy83F2y1m9k837my83-Cuy1m9k83pey1m9k83-ty83-Cuy1m9k83pey1o9zrtw1n83LCy1q1m9k9u1m9k83-Hy1m9k83-Ty1m9k83h2y1m9k83*Xy833*y1m83-V+yq");
    string_constant_109 = 
	    STATIC_STRING("1n83oIy1q1m9k9u1m9k83-Hy1m9k83-Ty1m9k83h2y1m9k83*Xy830By1m83-V+yq1n83nBy1q1m9k9u1m9k83-Hy1m9k83-Ty1m9k83h2y1m9k83*Xy83F2y1m83-V+");
    string_constant_110 = 
	    STATIC_STRING("yq1n83C-y1o1m9k83-TDy1m9k8319y1m9k831by1m9k83=Yyl1m833*y834Hy1m830By834Hy1m83F2y834Hy1m833*y83BFy1m830By83BFy1m83F2y83BFy1n833*y");
    string_constant_111 = 
	    STATIC_STRING("1m83lxy83-Gy1mlm1n830By1m83-Fmy83-Gy1mlm1n83F2y1m83-D+y83-Gy1mlm1m833*y1m1m9k9u83*my1m830By1m1m9k9u83*my1m83F2y1m1m9k9u83*my1n83");
    string_constant_112 = 
	    STATIC_STRING("3*y1n83lxy83Hwy833*y1nlmn1n830By1n83-Fmy83-Fby830By1nlmn1n83F2y1n83-D+y83nAy83F2y1nlmn1o833*y1o1m9k9u83*my1m9k83-Ty833*y1n9umo1l");
    string_constant_113 = 
	    STATIC_STRING("93Cy1o830By1o1m9k9u83*my1m9k83-Ty830By1n9umo1l93Cy1o83F2y1o1m9k9u83*my1m9k83-Ty83F2y1n9umo1l93Cy1o833*y1p1m9k9u83*my83*Zy1m9k83-");
    string_constant_114 = 
	    STATIC_STRING("Ty833*y1n9u2lmnp1l93Dy1o830By1p1m9k9u83*my83*Zy1m9k83-Ty830By1n9u2lmnp1l93Dy1o83F2y1p1m9k9u83*my83*Zy1m9k83-Ty83F2y1n9u2lmnp1l93");
    string_constant_115 = 
	    STATIC_STRING("Dy1n833*y1q1m9k9u83-Gy1m9k83=my83*my1m9k83-Ty833*y1n9u1n830=ymoq1n830By1q1m9k9u83-Gy1m9k83=my83*my1m9k83-Ty830By1n9u1n830=ymoq1n");
    string_constant_116 = 
	    STATIC_STRING("83F2y1q1m9k9u83-Gy1m9k83=my83*my1m9k83-Ty83F2y1n9u1n830=ymoq1n833*y1r1m9k9u83-Gy1m9k83=my83*my83*Zy1m9k83-Ty833*y1n9u2l1n830=ymo");
    string_constant_117 = 
	    STATIC_STRING("pr1n830By1r1m9k9u83-Gy1m9k83=my83*my83*Zy1m9k83-Ty830By1n9u2l1n830=ymopr1n83F2y1r1m9k9u83-Gy1m9k83=my83*my83*Zy1m9k83-Ty83F2y1n9");
    string_constant_118 = 
	    STATIC_STRING("u2l1n830=ymopr1n833*y1v1m9k9u83BEy1m9k8319y1m9k83*Iy1m9k83=ay1m9k83-qy1m9k83-Ty833*y1m9k832dy1m9k83*uy833*y1o9u1m83q3ymsv1n830By");
    string_constant_119 = 
	    STATIC_STRING("1v1m9k9u83BEy1m9k8319y1m9k83*Iy1m9k83=ay1m9k83-qy1m9k83-Ty830By1m9k832dy1m9k83*uy830By1o9u1m83q3ymsv1n83F2y1v1m9k9u83BEy1m9k8319");
    string_constant_120 = 
	    STATIC_STRING("y1m9k83*Iy1m9k83=ay1m9k83-qy1m9k83-Ty83F2y1m9k832dy1m9k83*uy83F2y1o9u1m83q3ymsv1n833*y1w1m9k9u83BEy83*Zy1m9k8319y1m9k83*Iy1m9k83");
    string_constant_121 = 
	    STATIC_STRING("=ay1m9k83-qy1m9k83-Ty833*y1m9k832dy1m9k83*uy833*y1o9u2l1m83q3ymntw1n830By1w1m9k9u83BEy83*Zy1m9k8319y1m9k83*Iy1m9k83=ay1m9k83-qy1");
    string_constant_122 = 
	    STATIC_STRING("m9k83-Ty830By1m9k832dy1m9k83*uy830By1o9u2l1m83q3ymntw1n83F2y1w1m9k9u83BEy83*Zy1m9k8319y1m9k83*Iy1m9k83=ay1m9k83-qy1m9k83-Ty83F2y");
    string_constant_123 = 
	    STATIC_STRING("1m9k832dy1m9k83*uy83F2y1o9u2l1m83q3ymntw1n83LCy1o1m9k9u83--by1m9k83-Ty833*y1n9umo1n83oIy1o1m9k9u83--by1m9k83-Ty830By1n9umo1n83nB");
    string_constant_124 = 
	    STATIC_STRING("y1o1m9k9u83--by1m9k83-Ty83F2y1n9umo1o83LCy1p1m9k9u83--by83*Zy1m9k83-Ty833*y1n9u2lmnp1l93Ey1o83oIy1p1m9k9u83--by83*Zy1m9k83-Ty830");
    string_constant_125 = 
	    STATIC_STRING("By1n9u2lmnp1l93Ey1o83nBy1p1m9k9u83--by83*Zy1m9k83-Ty83F2y1n9u2lmnp1l93Ey1n833*y1r1m9k9u83-Gy1m9k83CWy1m9k9u83*my1m9k83-Ty833*y1n");
    string_constant_126 = 
	    STATIC_STRING("83CVym1nopr1n830By1r1m9k9u83-Gy1m9k83CWy1m9k9u83*my1m9k83-Ty830By1n83CVym1nopr1n83F2y1r1m9k9u83-Gy1m9k83CWy1m9k9u83*my1m9k83-Ty8");
    string_constant_127 = 
	    STATIC_STRING("3F2y1n83CVym1nopr1n833*y1t1m9k9u83-Gy1m9k83CWy1m9k9u83-Gy1m9k83=my83*my1m9k83-Ty833*y1n83CVym1no1n830=yprt1n830By1t1m9k9u83-Gy1m");
    string_constant_128 = 
	    STATIC_STRING("9k83CWy1m9k9u83-Gy1m9k83=my83*my1m9k83-Ty830By1n83CVym1no1n830=yprt1n83F2y1t1m9k9u83-Gy1m9k83CWy1m9k9u83-Gy1m9k83=my83*my1m9k83-");
    string_constant_129 = 
	    STATIC_STRING("Ty83F2y1n83CVym1no1n830=yprt1n833*y1m1m9k837Zy1m9k83*ry1m9u1n834Zy83nty83=uy1n830By1m1m9k837Zy1m9k83*ry1m9u1n834Zy83nty83=uy1n83");
    string_constant_130 = 
	    STATIC_STRING("F2y1m1m9k837Zy1m9k83*ry1m9u1n834Zy83nty83=uy1n833*y1m1m9k837Zy1m9k834ry1m9u1n834Zy83-Evy836Py1n830By1m1m9k837Zy1m9k834ry1m9u1n83");
    string_constant_131 = 
	    STATIC_STRING("4Zy83-Evy836Py1n83F2y1m1m9k837Zy1m9k834ry1m9u1n834Zy83-Evy836Py1o833*y1m1m9k837Zy1m9k832Jy1m9u1n834Zy83-Euy832Jy1n93Fy832Jy83-Eu");
    string_constant_132 = 
	    STATIC_STRING("y1o830By1m1m9k837Zy1m9k832Jy1m9u1n834Zy83-Euy832Jy1n93Fy832Jy83-Euy1o83F2y1m1m9k837Zy1m9k832Jy1m9u1n834Zy83-Euy832Jy1n93Fy832Jy8");
    string_constant_133 = 
	    STATIC_STRING("3-Euy1o833*y1m1m9k837Zy1m9k83=Vy1m9u1n834Zy83-Esy83=Vy1n93Fy83=Vy83-Esy1o830By1m1m9k837Zy1m9k83=Vy1m9u1n834Zy83-Esy83=Vy1n93Fy83");
    string_constant_134 = 
	    STATIC_STRING("=Vy83-Esy1o83F2y1m1m9k837Zy1m9k83=Vy1m9u1n834Zy83-Esy83=Vy1n93Fy83=Vy83-Esy1o833*y1m1m9k837Zy1m9k831jy1m9u1n834Zy83-Ety831jy1n93");
    string_constant_135 = 
	    STATIC_STRING("Fy83=Vy83-Ety1o830By1m1m9k837Zy1m9k831jy1m9u1n834Zy83-Ety831jy1n93Fy83=Vy83-Ety1o83F2y1m1m9k837Zy1m9k831jy1m9u1n834Zy83-Ety831jy");
    string_constant_136 = 
	    STATIC_STRING("1n93Fy83=Vy83-Ety1n833*y1p1m9k9u83UAy83-Yy1m9k83*Xy833*y1n9u1mmnp1n830By1p1m9k9u83UAy83-Yy1m9k83*Xy830By1n9u1mmnp1n83F2y1p1m9k9u");
    string_constant_137 = 
	    STATIC_STRING("83UAy83-Yy1m9k83*Xy83F2y1n9u1mmnp1n833*y1q1m9k9u83UAy83-Yy83*Zy1m9k83*Xy833*y1n9u2l1mmnoq1n830By1q1m9k9u83UAy83-Yy83*Zy1m9k83*Xy");
    string_constant_138 = 
	    STATIC_STRING("830By1n9u2l1mmnoq1n83F2y1q1m9k9u83UAy83-Yy83*Zy1m9k83*Xy83F2y1n9u2l1mmnoq");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qplus);
    push_optimized_constant(Qtranspose_sum);
    push_optimized_constant(Qminus);
    push_optimized_constant(Qstar);
    push_optimized_constant(Qtranspose_term);
    push_optimized_constant(Qslash);
    push_optimized_constant(Qcheck_number_of_args);
    push_optimized_constant(Qreject_if_sequence_constant);
    push_optimized_constant(Qreject_if_structure_constant);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qsecond);
    push_optimized_constant(Qfirst);
    push_optimized_constant(Qlast);
    push_optimized_constant(Qvalues);
    push_optimized_constant(Qnumber_of_datapoints);
    push_optimized_constant(Qfilter_out_the_text_of_as_a_special_case);
    push_optimized_constant(Qfilter_out_the_text_of_and_region_icon_color);
    push_optimized_constant(Qfilter_out_region_icon_color);
    push_optimized_constant(Qrestrict_if_not_slot_edit_feature);
    temp = list(50,string_constant_1,string_constant_2,string_constant_3,
	    string_constant_4,string_constant_5,string_constant_6,
	    string_constant_7,string_constant_8,string_constant_9,
	    string_constant_10,string_constant_11,string_constant_12,
	    string_constant_13,string_constant_14,string_constant_15,
	    string_constant_16,string_constant_17,string_constant_18,
	    string_constant_19,string_constant_20,string_constant_21,
	    string_constant_22,string_constant_23,string_constant_24,
	    string_constant_25,string_constant_26,string_constant_27,
	    string_constant_28,string_constant_29,string_constant_30,
	    string_constant_31,string_constant_32,string_constant_33,
	    string_constant_34,string_constant_35,string_constant_36,
	    string_constant_37,string_constant_38,string_constant_39,
	    string_constant_40,string_constant_41,string_constant_42,
	    string_constant_43,string_constant_44,string_constant_45,
	    string_constant_46,string_constant_47,string_constant_48,
	    string_constant_49,string_constant_50);
    add_grammar_rules_function(regenerate_optimized_constant(nconc2(temp,
	    nconc2(list(50,string_constant_51,string_constant_52,
	    string_constant_53,string_constant_54,string_constant_55,
	    string_constant_56,string_constant_57,string_constant_58,
	    string_constant_59,string_constant_60,string_constant_61,
	    string_constant_62,string_constant_63,string_constant_64,
	    string_constant_65,string_constant_66,string_constant_67,
	    string_constant_68,string_constant_69,string_constant_70,
	    string_constant_71,string_constant_72,string_constant_73,
	    string_constant_74,string_constant_75,string_constant_76,
	    string_constant_77,string_constant_78,string_constant_79,
	    string_constant_80,string_constant_81,string_constant_82,
	    string_constant_83,string_constant_84,string_constant_85,
	    string_constant_86,string_constant_87,string_constant_88,
	    string_constant_89,string_constant_90,string_constant_91,
	    string_constant_92,string_constant_93,string_constant_94,
	    string_constant_95,string_constant_96,string_constant_97,
	    string_constant_98,string_constant_99,string_constant_100),
	    list(38,string_constant_101,string_constant_102,
	    string_constant_103,string_constant_104,string_constant_105,
	    string_constant_106,string_constant_107,string_constant_108,
	    string_constant_109,string_constant_110,string_constant_111,
	    string_constant_112,string_constant_113,string_constant_114,
	    string_constant_115,string_constant_116,string_constant_117,
	    string_constant_118,string_constant_119,string_constant_120,
	    string_constant_121,string_constant_122,string_constant_123,
	    string_constant_124,string_constant_125,string_constant_126,
	    string_constant_127,string_constant_128,string_constant_129,
	    string_constant_130,string_constant_131,string_constant_132,
	    string_constant_133,string_constant_134,string_constant_135,
	    string_constant_136,string_constant_137,string_constant_138)))));
    SET_SYMBOL_FUNCTION(Qreject_if_sequence_constant,
	    STATIC_FUNCTION(reject_if_sequence_constant,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qreject_if_sequence_constant);
    Qevaluated_structure = STATIC_SYMBOL("EVALUATED-STRUCTURE",AB_package);
    SET_SYMBOL_FUNCTION(Qreject_if_structure_constant,
	    STATIC_FUNCTION(reject_if_structure_constant,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qreject_if_structure_constant);
    QPLUS_PLUS_PLUS = STATIC_SYMBOL("+plus+",AB_package);
    Q_MINUS_ = STATIC_SYMBOL("-minus-",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,QPLUS_PLUS_PLUS,Q_MINUS_);
    SET_SYMBOL_FUNCTION(Qtranspose_sum,STATIC_FUNCTION(transpose_sum,NIL,
	    FALSE,1,1));
    QTIMES = STATIC_SYMBOL("*times*",AB_package);
    QSL_SLASH_SL = STATIC_SYMBOL("/slash/",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,QTIMES,QSL_SLASH_SL);
    SET_SYMBOL_FUNCTION(Qtranspose_term,STATIC_FUNCTION(transpose_term,NIL,
	    FALSE,1,1));
}
