// gsi_tests.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"

#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>


#include <stdio.h>


#include "Int64SupportTest.h"


extern "C" Object gsi_version_consistency_check();
extern "C" Object g2rtl_gsi_initialize_region_increments();
extern "C" Object g2int_init_top_level();
extern "C" Object g2int_userinit();
extern "C" Object launch_gsi();
extern "C" Object gsi_init_standard_callbacks();


#define g2rtl_string string
#define g2rtl_get get




int main(int argc, char* argv[])
{
	//GSI initialization 
	gsi_version_consistency_check();
    g2rtl_gsi_initialize_region_increments();
    g2int_init_top_level();
    g2int_userinit();
    launch_gsi();
    gsi_init_standard_callbacks();

	CPPUNIT_NS::TextUi::TestRunner runner;
    runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
    
    bool result = runner.run();

    // Comment/Uncomment next line to hide/view results because console window is closed
    getchar();

    return result ? 0 : -1;
}

//GSI callbacks stubs

gsi_int gsi_get_tcp_port()
{
    return 22040;
}

void gsi_set_up() {

}

void gsi_resume_context()
{

}

void gsi_receive_registration(gsi_registration registration) {

}

gsi_int gsi_initialize_context(char* remote_process_init_string, gsi_int length) {
  return GSI_ACCEPT; 
}
   
 
void gsi_shutdown_context()
{

}

void gsi_g2_poll() {

}

void gsi_set_data(gsi_registered_item* registered_item_array, gsi_int count) {

}

void gsi_get_data(gsi_registered_item* registered_item_array, gsi_int count) {

}

void gsi_receive_deregistrations(gsi_registered_item* registered_item_array, gsi_int count)
{}


void gsi_receive_message(char* message, gsi_int length)
{}

void gsi_pause_context()
{

}