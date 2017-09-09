#include <stdio.h>
#include "rt-suite.hpp"
#include "g2fasth.hpp"
#include "test_agent.hpp"

#include "libgsi.hpp"
#include "gsi_misc.h"

using namespace g2::fasth;

#define STORE_SIZE               5
#define MAX_STORE_INDEX          STORE_SIZE - 1

gsi_item *item_or_value_store;
long      store_index = 0;
gsi_item *error_object_ptr;

void init()
{
    item_or_value_store = gsi_make_items(STORE_SIZE);
    store_index = 0;
}

void shutdown()
{
    for (store_index=0;store_index<STORE_SIZE;store_index++)
        gsirtl_free_i_or_v_contents(item_or_value_store[store_index]);
    gsi_reclaim_items(item_or_value_store);
}

void rpc_add_float(gsi_item rpc_args[],gsi_int count,call_identifier_type call_index)
{
    double a,b,c;
    a = gsi_flt_of(rpc_args[0]);
    b = gsi_flt_of(rpc_args[1]);
    c = a + b;
    gsi_set_flt(rpc_args[0], c);
    gsi_rpc_return_values(rpc_args, 1, call_index, current_context);
}

void rpc_text(gsi_item rpc_args[],gsi_int count,call_identifier_type call_index)
{
#if defined(GSI_USE_WIDE_STRING_API)
    gsi_set_str(rpc_args[0], L"RPC text value");
#else
    gsi_set_str(rpc_args[0], "RPC text value");
#endif
    gsi_rpc_return_values(rpc_args, 1, call_index, current_context);
}

void rpc_error_mode(gsi_item rpc_args[],gsi_int count,call_identifier_type call_index)
{
    int mode = gsi_log_of(rpc_args[0]);
    g2::fasth::libgsi::getInstance().error_mode(mode > 0);
}

void rpc_action(gsi_item rpc_args[],gsi_int count,call_identifier_type call_index)
{
    g2::fasth::libgsi& gsiobj = g2::fasth::libgsi::getInstance();
    gsi_item* arguments = gsi_make_items(1);
    gsi_set_str(arguments[0], "Synchronous call from G2FASTH");
    
    gsiobj.start_remote("G2-REMOTE", arguments);
    gsi_reclaim_items(arguments);
}

void rpc_asynch(gsi_item rpc_args[],gsi_int count,call_identifier_type call_index)
{
    g2::fasth::libgsi& gsiobj = g2::fasth::libgsi::getInstance();
    gsi_item* arguments = gsi_make_items(1);
    gsi_set_str(arguments[0], "Test");
    
    gsiobj.call_remote("G2-ASYNCH", arguments);
    gsi_reclaim_items(arguments);
}

void exit_thread(void*p)
{
    if (nullptr == p) return;
    int* sleep_sec = (int*)p;
    printf("Exit thread: program will exit in %d sec...\n", *sleep_sec);
    tthread::this_thread::sleep_for(tthread::chrono::milliseconds(*sleep_sec*1000));
    exit(0);
}
void rpc_exit(gsi_item rpc_args[],gsi_int count,call_identifier_type call_index)
{
    puts("rpc_exit()");
    int* sleep_sec = new int;
    *sleep_sec = 1;
    new tthread::thread(exit_thread, sleep_sec);
}

void rpc_test(gsi_item rpc_args[],gsi_int count,call_identifier_type call_index)
{
    std::string test_code(str_of(rpc_args[0]));

    printf("rpc_test(%s)\n", test_code.c_str());

    RegTestSuite rts(test_code);

    rts.execute();

    std::string result = rts.get_results()[0].outcome() == test_outcome::pass ? "pass" : "fail";

    gsi_set_str(rpc_args[0], (char*)result.c_str());
    gsi_rpc_return_values(rpc_args, 1, call_index, current_context);
}

void rpc_declare_variable(gsi_item rpc_args[],gsi_int count,call_identifier_type call_index)
{
    std::string var_name(str_of(rpc_args[0]));
    std::string var_type(str_of(rpc_args[1]));

    printf("rpc_declare_variable(%s:%s)\n", var_name.c_str(), var_type.c_str());

    libgsi& gsi = libgsi::getInstance();

    if (var_type == "integer")
        gsi.declare_g2_variable<int>(var_name);
    else if (var_type == "float")
        gsi.declare_g2_variable<double>(var_name);
    else if (var_type == "logical")
        gsi.declare_g2_variable<bool>(var_name);
    else if (var_type == "string" || var_type == "text")
        gsi.declare_g2_variable<std::string>(var_name);

    gsi_rpc_return_values(NULL, 0, call_index, current_context);
}

void set_variable_value(gsi_item rpc_args[],gsi_int count,call_identifier_type call_index)
{
    std::string name(str_of(rpc_args[0]));
    std::string value(str_of(rpc_args[1]));
    printf("set_variable_value(%s, %s);\n", name.c_str(), value.c_str());

    libgsi::variable_map vars = libgsi::getInstance().get_g2_variables(false);
    if (0 == vars.count(name))
        return;

    switch (vars[name]->reg_type)
    {
    case g2_integer:
        libgsi::getInstance().assign_temp_value<int>(name.c_str(), atoi(value.c_str()));
        break;
    case g2_float:
        libgsi::getInstance().assign_temp_value<double>(name.c_str(), atof(value.c_str()));
        break;
    case g2_string:
        libgsi::getInstance().assign_temp_value<std::string>(name.c_str(), value);
        break;
    case g2_logical:
        libgsi::getInstance().assign_temp_value<bool>(name.c_str(), value=="true");
        break;
    default:
        return;
    }
}

void asynch_receiver(gsi_item rpc_args[], gsi_int count)
{
    char* value = gsi_str_of(rpc_args[0]);
    std::cout << value << std::endl;
}

void rpc_update_vars(gsi_item rpc_args[],gsi_int count,call_identifier_type call_index)
{
    g2::fasth::libgsi& gsiobj = g2::fasth::libgsi::getInstance();
    gsiobj.update_g2_variable("INTEGER-DAT");
    gsiobj.update_g2_variable("FLOAT64-DAT");
}

int int_handler()
{
    static int x = 0;
    return ++x;
}

double float_handler()
{
    static double d = 0.0;
    return d += 3.14;
}

void receive_item_or_value(gsi_item arg_array[],gsi_int count,call_identifier_type call_index)
{
/*
 *  Display the entire contents of the argument to standard out.
 *  Items arguments are displayed recursively attribute by attribute.
 */
    printf("count = %d, store_index = %d\n",count,store_index);
    printf("-------------------------\n");
    printf("  Printing argument\n");
    printf("-------------------------\n");
    gsirtl_display_item_or_value(arg_array[0],STARTING_LEVEL,STANDARD_OUT);
    printf("------------------------- end of argument.\n");

/*
 *  This program keeps a rotating store of STORE_SIZE items.
 *  Copy the argument into the item_or_value_store which is 
 *  an array of gsi_item's.
 */
    gsirtl_copy_item_or_value(arg_array[0],item_or_value_store[store_index]);

/*
 *  Increment the store index (resetting it if it is maxed) and free
 *  memory for displaced items.  Note that the item structure itself
 *  is not reclaimed but any sub parts (values or attributes) which
 *  take up memory are reclaimed.
 */
    if (store_index == MAX_STORE_INDEX)
      store_index = 0;
    else
      store_index++;
    gsirtl_free_i_or_v_contents(item_or_value_store[store_index]);

} /* end receive_item_or_value */


void receive_item_transfer(gsi_item arg_array[],gsi_int count,call_identifier_type call_index)
{
/*
 *  The contract of this function is a simple superset of 
 *  that for receive_item_or_value(), so it is called here.
 */
    receive_item_or_value(arg_array,count,call_index);

/*
 *  This function is called as opposed to started by G2 and as such
 *  must return even if no arguments are returned.
 */
    gsi_rpc_return_values(NULL_PTR,0,call_index,current_context);

} /* end receive_item_transfer */


void receive_and_return_copy(gsi_item arg_array[],gsi_int count,call_identifier_type call_index)
{
    gsi_int   duplicate_index;
/*
 *  The contract of this function is a simple superset of 
 *  that for receive_item_or_value(), so it is called here.
 */
    receive_item_or_value(arg_array,count,call_index);

/*
 *  Return the copy to G2.  Note, that receive_item_or_value()
 *  increments the store index so we have to look back one to
 *  get at the duplicate that was generated by the function.
 */
    if (store_index == 0)
      duplicate_index = MAX_STORE_INDEX;
    else
      duplicate_index = store_index - 1;
    printf("\n------>\n"); 
    gsi_rpc_return_values(&item_or_value_store[duplicate_index],1,call_index,current_context);
    printf("   <\n");
} /* end receive_and_return_copy */


void receive_request_for_copy(gsi_item arg_array[],gsi_int count,call_identifier_type call_index)
{
    long      i;
    char     *search_name = sym_of(arg_array[0]);
    char     *iv_name;
    gsi_item  item_or_value;

/*
 *  This function, searches the item_or_value_store 
 *  for an item given the item's name.
 */
    for (i=0; i<=MAX_STORE_INDEX; i++) {
      item_or_value = item_or_value_store[i];
      iv_name = name_of(item_or_value);
      if (strcmp(iv_name,search_name) == 0) {
	gsi_rpc_return_values(&item_or_value,1,call_index,current_context);
	return; }
    } /* end for */

    gsi_rpc_return_values(error_object_ptr,1,call_index,current_context);

} /* receive_request_for_copy */


void prepare_test_3226();
void prepare_test_3227();
void prepare_test_3228();
void prepare_test_3229();
void prepare_test_3230();
void prepare_test_4161_4164(bool);

int main(int argc, char **argv) {
    g2_options options;
    options.parse_arguments(&argc, argv);
    options.set_signal_handler();

    int port_num = 22060;
    if (argc > 1)
    {
        printf("Arg 1 = %s\n", argv[1]);
        char* a; for (a=argv[1]; *a && *a!='-'; a++); *a = 0;
        int tmp = strtol(argv[1], nullptr, 10);
        if (tmp)
          port_num = tmp;
    }
    int timeout_sec = 60;
    if (argc > 3)
    {
        printf("Arg 3 = %s\n", argv[3]);
        int tmp = strtol(argv[3], nullptr, 10);
        if (tmp)
          timeout_sec = tmp;
    }
    int* sleep_sec = new int;
    *sleep_sec = timeout_sec;
    new tthread::thread(exit_thread, sleep_sec);

    g2::fasth::libgsi& gsiobj = g2::fasth::libgsi::getInstance();
    gsiobj.continuous(true);
    gsiobj.port(port_num);
    
    gsiobj.declare_g2_function("RPC-ADD-FLOAT", rpc_add_float);
    gsiobj.declare_g2_function("RPC-TEXT", rpc_text);
    gsiobj.declare_g2_function("RPC-ERROR-MODE", rpc_error_mode);
    gsiobj.declare_g2_function("RPC-ACTION", rpc_action);
    gsiobj.declare_g2_function("RPC-ASYNCH", rpc_asynch);
    gsiobj.declare_g2_function("RPC-EXIT", rpc_exit);
    gsiobj.declare_g2_function("RPC-UPDATE-VARS", rpc_update_vars);

    if (argc > 2)
    {
        printf("Arg 2 = %s\n", argv[2]);
        std::string test_code = argv[2];

        if (test_code == "3226")
            prepare_test_3226();
        else if (test_code=="3227" || test_code=="3227-2")
            prepare_test_3227();
        else if (test_code == "3228")
            prepare_test_3228();
        else if (test_code == "3229")
            prepare_test_3229();
        else if (test_code == "3230")
            prepare_test_3230();
        else if (test_code=="4161-1" || test_code=="4162-1" || test_code=="4163-1" || test_code=="4164-1")
            prepare_test_4161_4164(false);
        else if (test_code=="4161-2" || test_code=="4162-2" || test_code=="4163-2" || test_code=="4164-2")
            prepare_test_4161_4164(true);
    }
    else
    {
        gsiobj.declare_g2_variable<int>("INTEGER-DAT", int_handler);
        gsiobj.declare_g2_variable<double>("FLOAT64-DAT", float_handler);
    }

    gsiobj.declare_g2_function("RPC-ADD-FLOAT", rpc_add_float);
    gsiobj.declare_g2_function("RPC-TEXT", rpc_text);

    gsiobj.declare_g2_function("RECEIVE-AND-DISPLAY-ITEM", receive_item_or_value);
    gsiobj.declare_g2_function("RECEIVE-AND-RETURN-ITEM-COPY", receive_and_return_copy);
    gsiobj.declare_g2_function("RECEIVE-AND-DISPLAY-TRANSFER", receive_item_transfer);
    gsiobj.declare_g2_function("RECEIVE-REQUEST-ITEM-COPY", receive_request_for_copy);

    gsiobj.declare_g2_function("RPC-EXIT", rpc_exit);
    gsiobj.declare_g2_function("RPC-TEST", rpc_test);
    gsiobj.declare_g2_function("RPC-DECLARE-VARIABLE", rpc_declare_variable);
    gsiobj.declare_g2_function("SET-VARIABLE-VALUE", set_variable_value);
    gsiobj.declare_g2_remotefn("G2-REMOTE", 1, 0);
    gsiobj.declare_g2_remotefn("G2-ASYNCH", 1, 1, asynch_receiver);

    gsiobj.declare_g2_init(init);
    gsiobj.declare_g2_shutdown(shutdown);

    gsiobj.startgsi();
    return 0;
}

void prepare_test_3226()
{
    libgsi& gsi = libgsi::getInstance();

    gsi.declare_g2_variable<int>("INTEGER-DAT");
    gsi.declare_g2_variable<double>("FLOAT64-DAT");
}

void prepare_test_3227()
{
    libgsi& gsi = libgsi::getInstance();

    gsi.dont_ignore_not_declared_variables();

    gsi.declare_g2_variable<int>("INTEGER-DAT");
    //gsi.declare_g2_variable<double>("FLOAT64-DAT"); // uncomment to cause an error
}

void prepare_test_3228()
{
    libgsi& gsi = libgsi::getInstance();

    gsi.ignore_not_declared_variables();

    gsi.declare_g2_variable<int>("INTEGER-DAT");
}

void prepare_test_3229()
{
    libgsi& gsi = libgsi::getInstance();

    gsi.ignore_not_registered_variables();

    gsi.declare_g2_variable<int>("INTEGER-DAT");
    gsi.declare_g2_variable<int>("NOT-REGISTERED");
}

void prepare_test_3230()
{
    libgsi& gsi = libgsi::getInstance();

    gsi.dont_ignore_not_registered_variables();

    gsi.declare_g2_variable<int>("INTEGER-DAT");
    gsi.declare_g2_variable<int>("NOT-REGISTERED");
}

// Base handler class for "TEST-FUNC" function
class TestFuncHandler: public gsi_rpc_handler<TestFuncHandler>
{
public:
    TestFuncHandler()
    {
        // Set TestFuncHandler::generic_handler() as initial RPC handling function
        set_function_name("TEST-FUNC");
    }
    static bool test_mode;
};
bool TestFuncHandler::test_mode = false;

// Real handler class for "TEST-FUNC" function
class RealTestFuncHandler: public TestFuncHandler
{
protected:
    void handler(const g2_arguments& in_args, g2_arguments& out_args) override
    {
        puts(__FUNCTION__);

        // Get function IN arguments
        int N = get_variable_value<int>(in_args[0]);
        std::string str = get_variable_value<std::string>(in_args[1]);

        // Do something
        // Here we just concatenate the second (string) argument N times (where N is the first argument)
        std::string result = "";
        for (int i=0; i<N; i++)
            result = result + str;

        // Put 'result' to OUT arguments
        out_args.resize(1);
        out_args[0] = create_variable<std::string>(result);
    }
    bool filter(const g2_arguments& in_args) override
    {
        // Check N argument
        int N = get_variable_value<int>(in_args[0]);
        if (N < 0)
            return false;
        // Return true in real mode
        return !test_mode;
    }
};

// Mock handler class for "TEST-FUNC" function
class MockTestFuncHandler: public TestFuncHandler
{
protected:
    void handler(const g2_arguments& in_args, g2_arguments& out_args) override
    {
        puts(__FUNCTION__);

        // Get function IN arguments
        int N = get_variable_value<int>(in_args[0]);
        std::string str = get_variable_value<std::string>(in_args[1]);

        // Do something
        // Here we just concatenate the second (string) argument N times (where N is the first argument)
        std::string result = "";
        for (int i=0; i<N; i++)
            result = result + str;
        // And add "MOCK" suffix
        result += "MOCK";

        // Put 'result' to OUT arguments
        out_args.resize(1);
        out_args[0] = create_variable<std::string>(result);
    }
    bool filter(const g2_arguments& in_args) override
    {
        // Check N argument
        int N = get_variable_value<int>(in_args[0]);
        if (N < 0)
            return false;
        // Return true in test(mock) mode
        return test_mode;
    }
};

// Second mock handler class for "TEST-FUNC" function
class SecondMockTestFuncHandler: public TestFuncHandler
{
protected:
    void handler(const g2_arguments& in_args, g2_arguments& out_args) override
    {
        puts(__FUNCTION__);

        // Prepare OUT arguments
        out_args.resize(1);
        out_args[0] = create_variable<std::string>("Number is negative");
    }
    bool filter(const g2_arguments& in_args) override
    {
        // Check N argument
        int N = get_variable_value<int>(in_args[0]);
        return N < 0;
    }
};

// Handler class for "SIMPLE-FUNC" function
class SimpleFuncHandler: public gsi_rpc_handler<SimpleFuncHandler>
{
friend class gsi_rpc_handler<SimpleFuncHandler>;
protected:
    void handler(const g2_arguments& in_args, g2_arguments& out_args) override
    {
        puts(__FUNCTION__);
    }
public:
    SimpleFuncHandler()
    {
        // Set SimpleFuncHandler::generic_handler() as initial RPC handling function
        set_function_name("SIMPLE-FUNC");
    }
};


void prepare_test_4161_4164(bool test_mode)
{
    puts(__FUNCTION__);

    // Real handler
    std::shared_ptr<RealTestFuncHandler> real_handler = std::make_shared<RealTestFuncHandler>();
    // Having a pointer to handler object we can make any configuring with it

    // Mock handler
    std::shared_ptr<MockTestFuncHandler> mock_handler = std::make_shared<MockTestFuncHandler>();
    // Having a pointer to handler object we can make any configuring with it

    // Second mock handler
    std::shared_ptr<SecondMockTestFuncHandler> mock2_handler = std::make_shared<SecondMockTestFuncHandler>();
    // Having a pointer to handler object we can make any configuring with it

    // Add all handlers
    TestFuncHandler::add_handler(real_handler);
    TestFuncHandler::add_handler(mock_handler);
    TestFuncHandler::add_handler(mock2_handler);

    // Real or mock(test) mode
    TestFuncHandler::test_mode = test_mode;

    // Simple function
    SimpleFuncHandler::add_handler(std::make_shared<SimpleFuncHandler>());
}
