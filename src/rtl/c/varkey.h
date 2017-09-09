
/* Support for vararg keyword functions */

/* Note: delete and remove are called ldelete and lremove */

#undef adjoin
#undef adjust_array
#undef assoc
#undef assoc_if
#undef assoc_if_not
#undef lclose
#undef count
#undef count_if
#undef count_if_not
#undef ldelete
#undef delete_duplicates
#undef delete_if
#undef delete_if_not
#undef fill
#undef find
#undef find_if
#undef find_if_not
#undef free_malloced_array_internal
#undef intersection
#undef load_run
#undef make_array
#undef make_hash_table
#undef make_list
#undef make_malloced_array
#undef make_malloced_string
#undef make_package
#undef make_pathname
#undef make_sequence
#undef make_string
#undef member
#undef member_if
#undef member_if_not
#undef merge
#undef mismatch
#undef nintersection
#undef nset_difference
#undef nset_exclusive_or
#undef nstring_capitalize
#undef nstring_downcase
#undef nstring_upcase
#undef nsublis
#undef nsubst
#undef nsubst_if
#undef nsubst_if_not
#undef nsubstitute
#undef nsubstitute_if
#undef nsubstitute_if_not
#undef nunion
#undef lopen
#undef parse_integer
#undef parse_namestring
#undef position
#undef position_if
#undef position_if_not
#undef rassoc
#undef rassoc_if
#undef rassoc_if_not
#undef read_from_string
#undef reduce
#undef lremove
#undef remove_duplicates
#undef remove_if
#undef remove_if_not
#undef replace
#undef search
#undef set_difference
#undef set_exclusive_or
#undef sort
#undef stable_sort
#undef string_capitalize
#undef string_downcase
#undef string_equal
#undef string_greaterp
#undef string_lessp
#undef string_not_equal
#undef string_not_greaterp
#undef string_not_lessp
#undef string_upcase
#undef string_ne
#undef string_lt
#undef string_le
#undef string_eq
#undef string_gt
#undef string_ge
#undef sublis
#undef subsetp
#undef subst
#undef subst_if
#undef subst_if_not
#undef substitute
#undef substitute_if
#undef substitute_if_not
#undef tree_equal
#undef lunion
#undef lwrite
#undef write_line
#undef write_string
#undef write_to_string

#ifdef SI_VARIADIC_KEYWORD_FUNCTIONS

#define adjoin	                SI_adjoin_n
#define adjust_array		SI_adjust_array_n
#define assoc			SI_assoc_n
#define assoc_if		SI_assoc_if_n
#define assoc_if_not		SI_assoc_if_not_n
#define lclose			SI_lclose_n
#define count			SI_count_n
#define count_if		SI_count_if_n
#define count_if_not		SI_count_if_not_n
#define ldelete		 	SI_delete_n
#define delete_duplicates 	SI_delete_duplicates_n
#define delete_if		SI_delete_if_n
#define delete_if_not		SI_delete_if_not_n
#define fill			SI_fill_n
#define find			SI_find_n
#define find_if			SI_find_if_n
#define find_if_not		SI_find_if_not_n
#define free_malloced_array_internal     SI_free_malloced_array_internal
#define intersection		SI_intersection_n
#define load_run                SI_load_run_n
#define make_array		SI_make_array_n
#define make_hash_table		SI_make_hash_table_n
#define make_list		SI_make_list_n
#define make_malloced_array     SI_make_malloced_array
#define make_malloced_string    SI_make_malloced_string
#define make_package		SI_make_package_n
#define make_pathname		SI_make_pathname_n
#define make_sequence		SI_make_sequence_n
#define make_string		SI_make_string_n
#define member			SI_member_n
#define member_if		SI_member_if_n
#define member_if_not		SI_member_if_not_n
#define merge			SI_merge_n
#define mismatch		SI_mismatch_n
#define nintersection		SI_nintersection_n
#define nset_difference		SI_nset_difference_n
#define nset_exclusive_or	SI_nset_exclusive_or_n
#define nstring_capitalize	SI_nstring_capitalize_n
#define nstring_downcase	SI_nstring_downcase_n
#define nstring_upcase		SI_nstring_upcase_n
#define nsublis			SI_nsublis_n
#define nsubst			SI_nsubst_n
#define nsubst_if		SI_nsubst_if_n
#define nsubst_if_not		SI_nsubst_if_not_n
#define nsubstitute		SI_nsubstitute_n
#define nsubstitute_if		SI_nsubstitute_if_n
#define nsubstitute_if_not	SI_nsubstitute_if_not_n
#define nunion			SI_nunion_n
#define lopen			SI_lopen_n
#define parse_integer		SI_parse_integer_n
#define parse_namestring	SI_parse_namestring_n
#define position		SI_position_n
#define position_if		SI_position_if_n
#define position_if_not		SI_position_if_not_n
#define rassoc			SI_rassoc_n
#define rassoc_if		SI_rassoc_if_n
#define rassoc_if_not		SI_rassoc_if_not_n
#define read_from_string	SI_read_from_string_n
#define reduce			SI_reduce_n
#define lremove			SI_remove_n
#define remove_duplicates	SI_remove_duplicates_n
#define remove_if		SI_remove_if_n
#define remove_if_not		SI_remove_if_not_n
#define replace			SI_replace_n
#define search			SI_search_n
#define set_difference		SI_set_difference_n
#define set_exclusive_or	SI_set_exclusive_or_n
#define sort			SI_sort_n
#define stable_sort		SI_stable_sort_n
#define string_capitalize	SI_string_capitalize_n
#define string_downcase		SI_string_downcase_n
#define string_equal		SI_string_equal_n
#define string_greaterp		SI_string_greaterp_n
#define string_lessp		SI_string_lessp_n
#define string_not_equal	SI_string_not_equal_n
#define string_not_greaterp	SI_string_not_greaterp_n
#define string_not_lessp	SI_string_not_lessp_n
#define string_upcase		SI_string_upcase_n
#define string_ne		SI_string_ne_n
#define string_lt		SI_string_lt_n
#define string_le		SI_string_le_n
#define string_eq		SI_string_eq_n
#define string_gt		SI_string_gt_n
#define string_ge		SI_string_ge_n
#define sublis			SI_sublis_n
#define subsetp			SI_subsetp_n
#define subst			SI_subst_n
#define subst_if		SI_subst_if_n
#define subst_if_not		SI_subst_if_not_n
#define substitute		SI_substitute_n
#define substitute_if		SI_substitute_if_n
#define substitute_if_not	SI_substitute_if_not_n
#define tree_equal		SI_tree_equal_n
#define lunion			SI_lunion_n
#define lwrite			SI_lwrite_n
#define write_line		SI_write_line_n
#define write_string		SI_write_string_n
#define write_to_string		SI_write_to_string_n

#else

#define adjoin g2rtl_adjoin
#define adjust_array g2rtl_adjust_array
#define assoc g2rtl_assoc
#define assoc_if g2rtl_assoc_if
#define assoc_if_not g2rtl_assoc_if_not
#define lclose g2rtl_lclose
#define count g2rtl_count
#define count_if g2rtl_count_if
#define count_if_not g2rtl_count_if_not
#define ldelete g2rtl_ldelete
#define delete_duplicates g2rtl_delete_duplicates
#define delete_if g2rtl_delete_if
#define delete_if_not g2rtl_delete_if_not
#define fill g2rtl_fill
#define find g2rtl_find
#define find_if g2rtl_find_if
#define find_if_not g2rtl_find_if_not
#define free_malloced_array_internal g2rtl_free_malloced_array_internal
#define intersection g2rtl_intersection
#define load_run g2rtl_load_run
#define make_array g2rtl_make_array
#define make_hash_table g2rtl_make_hash_table
#define make_list g2rtl_make_list
#define make_malloced_array g2rtl_make_malloced_array
#define make_malloced_string g2rtl_make_malloced_string
#define make_package g2rtl_make_package
#define make_pathname g2rtl_make_pathname
#define make_sequence g2rtl_make_sequence
#define make_string g2rtl_make_string
#define member g2rtl_member
#define member_if g2rtl_member_if
#define member_if_not g2rtl_member_if_not
#define merge g2rtl_merge
#define mismatch g2rtl_mismatch
#define nintersection g2rtl_nintersection
#define nset_difference g2rtl_nset_difference
#define nset_exclusive_or g2rtl_nset_exclusive_or
#define nstring_capitalize g2rtl_nstring_capitalize
#define nstring_downcase g2rtl_nstring_downcase
#define nstring_upcase g2rtl_nstring_upcase
#define nsublis g2rtl_nsublis
#define nsubst g2rtl_nsubst
#define nsubst_if g2rtl_nsubst_if
#define nsubst_if_not g2rtl_nsubst_if_not
#define nsubstitute g2rtl_nsubstitute
#define nsubstitute_if g2rtl_nsubstitute_if
#define nsubstitute_if_not g2rtl_nsubstitute_if_not
#define nunion g2rtl_nunion
#define lopen g2rtl_lopen
#define parse_integer g2rtl_parse_integer
#define parse_namestring g2rtl_parse_namestring
#define position g2rtl_position
#define position_if g2rtl_position_if
#define position_if_not g2rtl_position_if_not
#define rassoc g2rtl_rassoc
#define rassoc_if g2rtl_rassoc_if
#define rassoc_if_not g2rtl_rassoc_if_not
#define read_from_string g2rtl_read_from_string
#define reduce g2rtl_reduce
#define lremove g2rtl_lremove
#define remove_duplicates g2rtl_remove_duplicates
#define remove_if g2rtl_remove_if
#define remove_if_not g2rtl_remove_if_not
#define replace g2rtl_replace
#define search g2rtl_search
#define set_difference g2rtl_set_difference
#define set_exclusive_or g2rtl_set_exclusive_or
#define sort g2rtl_sort
#define stable_sort g2rtl_stable_sort
#define string_capitalize g2rtl_string_capitalize
#define string_downcase g2rtl_string_downcase
#define string_equal g2rtl_string_equal
#define string_greaterp g2rtl_string_greaterp
#define string_lessp g2rtl_string_lessp
#define string_not_equal g2rtl_string_not_equal
#define string_not_greaterp g2rtl_string_not_greaterp
#define string_not_lessp g2rtl_string_not_lessp
#define string_upcase g2rtl_string_upcase
#define string_ne g2rtl_string_ne
#define string_lt g2rtl_string_lt
#define string_le g2rtl_string_le
#define string_eq g2rtl_string_eq
#define string_gt g2rtl_string_gt
#define string_ge g2rtl_string_ge
#define sublis g2rtl_sublis
#define subsetp g2rtl_subsetp
#define subst g2rtl_subst
#define subst_if g2rtl_subst_if
#define subst_if_not g2rtl_subst_if_not
#define substitute g2rtl_substitute
#define substitute_if g2rtl_substitute_if
#define substitute_if_not g2rtl_substitute_if_not
#define tree_equal g2rtl_tree_equal
#define lunion g2rtl_lunion
#define lwrite g2rtl_lwrite
#define write_line g2rtl_write_line
#define write_string g2rtl_write_string
#define write_to_string g2rtl_write_to_string

#endif

