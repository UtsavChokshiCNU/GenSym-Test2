#define GSI_USE_REFERENCES                    11

GSI_API_EXTERN void      gsi_set_local_home
        GSI_API_PROTO(( gsi_item local_home ));
GSI_API_EXTERN gsi_item  gsi_context_remote_home
        GSI_API_PROTO(( gsi_int context ));

GSI_API_EXTERN gsi_int  gsi_item_reference_flag
        GSI_API_PROTO(( gsi_item item ));
GSI_API_EXTERN void     gsi_set_item_reference_flag
        GSI_API_PROTO(( gsi_item item, gsi_int reference_flag ));

#define gsi_item_name_is_identifying_flag gsi_item_name_is_ident_flag
#define gsi_set_item_name_is_identifying_flag gsi_set_item_name_is_ident_flag
GSI_API_EXTERN gsi_int  gsi_item_name_is_identifying_flag
        GSI_API_PROTO(( gsi_item item ));
GSI_API_EXTERN void     gsi_set_item_name_is_identifying_flag
        GSI_API_PROTO(( gsi_item item, gsi_int reference_flag ));

#define gsi_item_class_is_identifying_flag gsi_item_class_is_ident_flag
//#define gsi_set_item_class_is_identifying_flag gsi_set_item_class_is_ident_flag
GSI_API_EXTERN gsi_int  gsi_item_class_is_identifying_flag
        GSI_API_PROTO(( gsi_item item ));
GSI_API_EXTERN void     gsi_set_item_class_is_identifying_flag
        GSI_API_PROTO(( gsi_item item, gsi_int reference_flag ));

GSI_API_EXTERN gsi_int    gsi_attr_is_identifying
        GSI_API_PROTO(( gsi_attr attribute ));
GSI_API_EXTERN void       gsi_set_attr_is_identifying
        GSI_API_PROTO(( gsi_attr attribute, gsi_int new_value ));
