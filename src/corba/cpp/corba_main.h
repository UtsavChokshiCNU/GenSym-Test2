#ifndef CORBAMAIN_H
#define CORBAMAIN_H
#include <setjmp.h>
#include <time.h>
#include "gsi_main_cpp.h"
#include "g2string.h"
#include "G2ContainerClass.h"
#include "G2CorbaContainer.h"
#include "connections.h"

/**************/
/* Header file containing class and strucure definitions */
/**************/

/* Prototypes/Forward Declarations */

// RPC Functions from G2
void g2orb_send_req(void *, gsi_item [], gsi_int, void * );
void g2orb_reg_obj(void *, gsi_item [], gsi_int, void * );
void rpc_req_recv(void *, gsi_item [], gsi_int, void * );
void g2orb_dereg_obj(void *, gsi_item [], gsi_int, void * );
void g2orb_reg_proxy(void *, gsi_item [], gsi_int, void * );
void g2orb_dereg_proxy(void *, gsi_item [], gsi_int, void * );
void g2orb_download_ir(void *, gsi_item [], gsi_int, void * );
void g2idl_compile_idl(void *, gsi_item [], gsi_int, void * );
void g2orb_reg_g2(void *, gsi_item args[], gsi_int count, void *);
void g2orb_object_to_string(void *, gsi_item args[], gsi_int count, void *);
void g2orb_decode_user_ref(void *, gsi_item args[], gsi_int count, void *);
void g2orb_ping_rpc(void *, gsi_item args[], gsi_int count, void *);


void g2idl_pre_scan_file(void *, gsi_item args[], gsi_int count, void *);



// RPC receiver functions
void rpc_get_recv(void *, gsi_item arguments[], gsi_int count, void *);
void rpc_loc_recv(void *, gsi_item args[], gsi_int count, void *);

// other functions

void init_orb(char *name);
void service_orb(void);
void service_requests(void);
void g2orb_return_symbol_error(char *, void *, gsi_int);
gsi_item get_attr_by_name(gsi_item ptr, char *name);
G2IRObject *get_ir_object(G2OrbContext *cObj, char *ID);
void create_listener(unsigned port_number);
void main_loop(void);
void request_failed(G2CRequest *rObj, char *code);
socket_data *create_connection(char *system_name, unsigned port_number);
void request_sent(G2CRequest *rObj);
void got_request_reply(G2CRequest *rObj, iiop *iiopObj,
					   unsigned char reply_status);
void got_server_request(iiop *iiopObj, unsigned long requestid, 
						unsigned char resp_expected, 
						char *objectkey, char *opname, 
						char *principal, socket_data *sdata);
unsigned char build_NVList_from_gsi(G2OrbContainer &arglist,
						G2Interface *iObj, G2Operation *oObj, 
						G2OrbContext *cObj, gsi_item *Args,
						int direction);
unsigned char build_Any_from_gsi(gsi_item gsiItem, gsi_item *args, 
								 int &argIndex,
								 G2OrbContext *cObj,
								 G2OrbContainer &arglist,
								 int direction,
								 G2String *true_type = NULL);
int decode_request_body(G2OrbContainer &arglist, iiop *iiopObj, int context_number);
void encode_mesg_header(iiop *ptr, int mesg_type, int flag);
void update_mesg_header_size(iiop *ptr);
void  process_iiop_message(void *iiopmesg, unsigned long mesg_len, unsigned char little_endian, 
						   unsigned char mesg_type, socket_data *sdata);
int string2objref(char *objref, G2String& Host, unsigned& port_number, G2OctSeq& object_key);
void objref2string_encodeprofile(iiop &profile, char *host, unsigned port_number, 
								 G2OctSeq& obj_key,int flag);
void convert_to_g2_symbol_string(char *);
int check_type_for_complex(gsi_item parm, G2OrbContext *cObj);
void deep_reclaim_items(gsi_item *ptr, int n);
G2Operation *got_server_find_operation(char *opname, G2Interface *iObj, G2OrbContext *cObj);
int decodeobjref(char *objref, G2String& iiop_host, 
				 unsigned& iiop_port, G2OctSeq& objkey);
int objref2binior(char *objref, iiop& binior);
int binior2objref(iiop& ior, int context, G2String& decodedIOR);
int binior2objrefEx(iiop& ior, int context, G2String& decodedIOR,
                    char **pp_iiop_host, unsigned *p_iiop_port,
                    unsigned char **pp_object_key, int *p_object_key_len,
                    char **pp_object_kind);
void g2orb_return_symbol_string_error(char *code, char *mesg, void *call_index, gsi_int context_number);
void g2orb_simplify_idl_kind(char* p_dest, char* p_src);
void genbinior(iiop& ior, char *kind, char *host, unsigned port_number, G2OctSeq& obj_key, char *g2host, 
				unsigned g2port, unsigned g2profilever);
void timeout_serv_req(void);
void timeout_client_req(void);
int do_decode_objref(iiop *objref, iiop *ptr, int flag);
void call_locator(iiop *iiopObj, unsigned long requestid,
				  unsigned char resp_expected,
				  char *objectkey, char *opname,
				  char *principal, socket_data *sdata) ;
void loc_reject_request(G2LRequest *lObj, char *reason);
void g2orb_return_server_mesg_excep(socket_data *sdata, unsigned long reqnum,
									 char *exception, gsi_int minor, gsi_int comp_status);
void got_locate_request(char *objectkey, unsigned long requstid, socket_data *sdata);
unsigned long get_request_id(void);
void got_locate_request_reply(G2CRequest *rObj, iiop *iiopObj, unsigned char reply_status);
int got_forward_reply(G2OrbContext *cObj, G2CRequest *rObj, iiop *iiopObj);
void main_control( gsi_item file_names, gsi_item * );
void dispatch_error(char *filename, int line_number, char *mesg);
void purge_objects(G2OrbContext *cObj);
void getIOR_G2SO( char  *g2orb_objname, G2SRequest *srObj, G2Interface *iObj, 
                  G2Operation *oObj, G2OrbContext *cObj );


// global data

extern  G2OrbContainer ContextObjs; // Set of context objects
extern  G2OrbContainer RequestObjs; // Set of Request objects
extern  G2OrbContainer ServReqObjs; // Set of server request objects
extern 	G2OrbContainer Sockets;  // Set of socket search objects
extern	G2OrbContainer Objects;  // Set of server objects
extern	G2OrbContainer SocketMaps;  // Set of socket map objects
extern	G2OrbContainer LocateReqObjs; // Collection of locate request objects
extern  NoHashContainer PurgeObjects; // Objects pending purge
extern  G2String hostname;
extern  unsigned hostport;
extern unsigned long idle_timeout;
extern unsigned long connect_timeout;
extern unsigned long client_timeout;
extern unsigned long server_timeout;

extern int debug_mode;

extern jmp_buf error_marker;
extern G2String error_message;

extern unsigned char relations_flag;
extern int decoding_context;
extern int g2item_level_deep;
extern bool decode_top_level;

#define GSI_NULL_RELATION_TAG 5000

extern time_t	g_current_time;   // updated once per run loop


#endif

