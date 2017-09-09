/*******************************************************

      Any module that includes this file should 
      include gsi_main.h beforehand.

.........................................................*/

#define STARTING_LEVEL  0
#define STANDARD_OUT    1
#define EMPTY_STRING ""
#define gsirtl_display(x) printf(x)
#define gsirtl_display_1(x,y) printf(x,y)
#define gsirtl_display_2(x,y,z) printf(x,y,z)
#define gsirtl_display_4(x,y1,y2,y3,y4) printf(x,y1,y2,y3,y4)
#define gsirtl_display_6(a,b,c,d,e,f,g) printf(a,b,c,d,e,f,g)
#define gsirtl_indented_display(x) \
            printf("%*s",(int)(level*2),EMPTY_STRING); \
            printf(x); 
#define gsirtl_indented_display_1(x,y) \
            printf("%*s",(int)(level*2),EMPTY_STRING); \
            printf(x,y); 
#define gsirtl_indented_display_2(x,y,z) \
            printf("%*s",(int)(level*2),EMPTY_STRING); \
            printf(x,y,z); 
#define gsirtl_indented_display_6(t,u,v,w,x,y,z) \
            printf("%*s",(int)(level*2),EMPTY_STRING); \
            printf(t,u,v,w,x,y,z); 


#if GSI_USE_PROTOTYPES
#define GSI_MISC_PROTO(args) args
#else
#define GSI_MISC_PROTO(args) ()
#endif

void gsirtl_copy_item_or_value GSI_MISC_PROTO((gsi_item arg, gsi_item duplicate));

void gsirtl_copy_item GSI_MISC_PROTO((gsi_int arg_type, 
				      gsi_item arg, gsi_item duplicate));

void gsirtl_copy_array GSI_MISC_PROTO((gsi_int arg_type, 
				       gsi_item arg, gsi_item duplicate));

void gsirtl_copy_list GSI_MISC_PROTO((gsi_int arg_type,
				      gsi_item arg, gsi_item duplicate));

void gsirtl_copy_simple_value GSI_MISC_PROTO((gsi_int arg_type, 
					      gsi_item arg, gsi_item duplicate));

void gsirtl_copy_sequence GSI_MISC_PROTO((gsi_item arg, gsi_item duplicate));

void gsirtl_copy_structure GSI_MISC_PROTO((gsi_item arg, gsi_item duplicate));

void gsirtl_display_item_or_value GSI_MISC_PROTO((gsi_item arg, gsi_int level, gsi_int display_mod));

void gsirtl_display_item GSI_MISC_PROTO((gsi_int arg_type, 
					 gsi_item arg, gsi_int level, gsi_int display_mode));

void gsirtl_display_array GSI_MISC_PROTO((gsi_int arg_type,
					  gsi_item arg, gsi_int level, gsi_int display_mode));

void gsirtl_display_list GSI_MISC_PROTO((gsi_int arg_type,
					 gsi_item arg, gsi_int level, gsi_int display_mode));

void gsirtl_display_simple_value GSI_MISC_PROTO((gsi_int arg_type,
						 gsi_item arg, gsi_int display_mode));

void gsirtl_display_buffer GSI_MISC_PROTO((char *buffer, long mode));

void gsirtl_free_i_or_v_contents GSI_MISC_PROTO((gsi_item arg));

void gsirtl_free_array_memory GSI_MISC_PROTO((gsi_int arg_type, gsi_item arg));

void gsirtl_free_list_memory GSI_MISC_PROTO((gsi_int arg_type, gsi_item arg));

void gsirtl_free_item_memory GSI_MISC_PROTO((gsi_item arg));

