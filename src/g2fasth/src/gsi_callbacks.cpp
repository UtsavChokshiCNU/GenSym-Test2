#include "libgsi.hpp"

/// GSI callbacks stubs

/**
* Specify a default port number that a G2 Gateway process using TCP/IP can listen
* on for connections from a G2 process.
*/
gsi_int gsi_get_tcp_port()
{
    return g2::fasth::libgsi::getInstance().gsi_get_tcp_port_();
}

/**
* Perform G2 Gateway-related operations that need to be performed only once
* during the lifetime of the bridge process.
*/
void gsi_set_up()
{
    g2::fasth::libgsi::getInstance().gsi_set_up_();
}

/**
* Called by G2 Gateway when a connected G2 process resumes its current KB.
*/
void gsi_resume_context()
{
    g2::fasth::libgsi::getInstance().gsi_resume_context_();
}

/**
* Called when G2 registers an item with G2 Gateway.
*/
void gsi_receive_registration(gsi_registration registration)
{
    g2::fasth::libgsi::getInstance().gsi_receive_registration_(registration);
}

/**
* Initialize a connection between a GSI interface in G2 and G2 Gateway, or reject the connection.
*/
gsi_int gsi_initialize_context(char* remote_process_init_string, gsi_int length)
{
    return g2::fasth::libgsi::getInstance().gsi_initialize_context_(remote_process_init_string, length);
}

/**
* Shut down a context and perform operations necessary to shut down the external
* system and clean up the bridge process
*/
void gsi_shutdown_context()
{
    g2::fasth::libgsi::getInstance().gsi_shutdown_context_();
}

/**
* Seek data or perform other user-specified actions, repeatedly.
*/
void gsi_g2_poll()
{
    g2::fasth::libgsi::getInstance().gsi_g2_poll_();
}

/**
* Called when G2 executes one or more set actions on a data served GSI variable.
*/
void gsi_set_data(gsi_registered_item* registered_item_array, gsi_int count)
{
    g2::fasth::libgsi::getInstance().gsi_set_data_(registered_item_array, count);
}

/**
* Respond to a request from G2 for a value for a data-served GSI variable.
*/
void gsi_get_data(gsi_registered_item* registered_item_array, gsi_int count)
{
    g2::fasth::libgsi::getInstance().gsi_get_data_(registered_item_array, count);
}

/**
* Deregister a single registered variable.
*/
void gsi_receive_deregistrations(gsi_registered_item* registered_item_array, gsi_int count)
{
    g2::fasth::libgsi::getInstance().gsi_receive_deregistrations_(registered_item_array, count);
}

/**
* Receive a message from G2, sent as a result of a G2 inform action on a GSI message server.
*/
void gsi_receive_message(char* message, gsi_int length)
{
    g2::fasth::libgsi::getInstance().gsi_receive_message_(message, length);
}

/**
* Called by G2 Gateway whenever any G2 process that is connected to this G2
* Gateway process pauses its current knowledge base (KB).
*/
void gsi_pause_context()
{
    g2::fasth::libgsi::getInstance().gsi_pause_context_();
}
