#ifndef INC_GSI_CALLBACKS_H
#define INC_GSI_CALLBACKS_H

#include <gsi_main.h>

extern "C" {
/**
* Specify a default port number that a G2 Gateway process using TCP/IP can listen
* on for connections from a G2 process.
*/
gsi_int gsi_get_tcp_port();
/**
* Perform G2 Gateway-related operations that need to be performed only once
* during the lifetime of the bridge process.
*/
void gsi_set_up();
/**
* Called by G2 Gateway when a connected G2 process resumes its current KB.
*/
void gsi_resume_context();
/**
* Called when G2 registers an item with G2 Gateway.
*/
void gsi_receive_registration(gsi_registration registration);
/**
* Initialize a connection between a GSI interface in G2 and G2 Gateway, or reject the connection.
*/
gsi_int gsi_initialize_context(char* remote_process_init_string, gsi_int length);
/**
* Shut down a context and perform operations necessary to shut down the external
* system and clean up the bridge process
*/
void gsi_shutdown_context();
/**
* Seek data or perform other user-specified actions, repeatedly.
*/
void gsi_g2_poll();
/**
* Called when G2 executes one or more set actions on a data served GSI variable.
*/
void gsi_set_data(gsi_registered_item* registered_item_array, gsi_int count);
/**
* Respond to a request from G2 for a value for a data-served GSI variable.
*/
void gsi_get_data(gsi_registered_item* registered_item_array, gsi_int count);
/**
* Deregister a single registered variable.
*/
void gsi_receive_deregistrations(gsi_registered_item* registered_item_array, gsi_int count);
/**
* Receive a message from G2, sent as a result of a G2 inform action on a GSI message server.
*/
void gsi_receive_message(char* message, gsi_int length);
/**
* Called by G2 Gateway whenever any G2 process that is connected to this G2
* Gateway process pauses its current knowledge base (KB).
*/
void gsi_pause_context();
}
#endif // !INC_GSI_CALLBACKS_H
