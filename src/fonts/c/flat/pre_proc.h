/* kanji code preprocessor */
/* JIS and EUC filter functions */
FUNCTION ufix16 JIS2SJ PROTO((PROTO_DECL2 ufix16 code));
FUNCTION ufix16 EUC2JIS PROTO((PROTO_DECL2 ufix16 code));
FUNCTION ufix16 EUC2SJ PROTO((PROTO_DECL2 ufix16 code));

/* kanji font manager */
FUNCTION int kj_set_font_mapping PROTO ((PROTO_DECL2 ufix8 index, char* font_name));
FUNCTION int kj_read_font_mapping PROTO ((PROTO_DECL2 char *filename));
FUNCTION int kj_SJ_font_manager PROTO ((PROTO_DECL2 ufix8 sj_lead_byte, char* font_name, int *count));
FUNCTION int kj_SJ2_font_manager PROTO ((PROTO_DECL2 ufix16 code, char* font_name, int *count));
FUNCTION int kj_set_kanji_specs PROTO ((PROTO_DECL2 ufix16 flags,real *matrix));

