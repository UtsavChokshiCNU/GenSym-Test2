
package com.gensym.gsi;

import java.util.*;
import java.lang.reflect.*;
import com.gensym.gsi.messages.*;

public class GSIMessageMap {

    static public Map map = new HashMap();

    static void addMessage(Class mc) {
	try {map.put(mc.getField("messageCode").get(mc.newInstance()),mc);}
	catch (java.lang.Exception e) {}
    }

    static { 
	addMessage(abort_icp_task.class);
	addMessage(acknowledge_deregister_corresponding_icp_object.class);
	addMessage(acknowledge_shutdown.class);
	addMessage(begin_sensor_list.class);
	addMessage(connection_denied.class);
	addMessage(connection_shutdown_imminent.class);
	addMessage(create_item_reference.class);
	addMessage(define_dummy_object.class);
	addMessage(define_gsi_interface.class);
	addMessage(define_gsi_sensor.class);
	addMessage(define_remote_procedure_name.class);
	addMessage(define_resumable_remote_procedure_identifier.class);
	addMessage(define_temporary_index_space.class);
	addMessage(delete_icp_object_for_process.class);
	addMessage(deregister_corresponding_icp_object.class);
	addMessage(deregister_icp_objects.class);
	addMessage(deregister_original_icp_object.class);
	addMessage(end_sensor_list.class);
	addMessage(enlarge_corresponding_icp_object_index_space.class);
	addMessage(get_values_for_sensors_in_list.class);
	addMessage(i_am_alive.class);
	addMessage(initialize_data_server.class);
	addMessage(initialize_gsi_interface.class);
	addMessage(intern.class);
	addMessage(intern_keyword.class);
	addMessage(intern_list.class);
	addMessage(load_sensor_list_element.class);
	addMessage(message_group_id.class);
	addMessage(modify_gsi_sensor_definition.class);
	addMessage(no_license.class);
	addMessage(nop.class);
	addMessage(pause_data_server.class);
	addMessage(receive_gsi_sensor_value_vector.class);
	addMessage(receive_timestamped_gsi_sensor_value_vector.class);
	addMessage(receive_value_for_gsi_sensor.class);
	addMessage(receive_value_for_gsi_sensor_with_timestamp.class);
	addMessage(receive_value_for_ping_request.class);
	addMessage(receive_values_for_gsi_sensors.class);
	addMessage(register_corresponding_icp_object.class);
	addMessage(release_temporary_index_space.class);
	addMessage(reset_data_server.class);
	addMessage(resumable_rpc_call.class);
	addMessage(resumable_rpc_error.class);
	addMessage(resumable_rpc_error_to_caller.class);
	addMessage(resumable_rpc_return_values.class);
	addMessage(resumable_rpc_start.class);
	addMessage(resume_data_server.class);
	addMessage(resume_icp_task.class);
	addMessage(return_initialize_gsi_interface_status.class);
	addMessage(return_peer_version.class);
	addMessage(rpc_acknowledge_abort.class);
	addMessage(rpc_asynchronous_abort.class);
	addMessage(send_data_values_if_any.class);
	addMessage(set_values_for_sensors_in_list.class);
	addMessage(shut_down_data_server.class);
	addMessage(start_data_server.class);
	addMessage(start_icp_task.class);
	addMessage(stop_sending_values_for_sensors_in_list.class);
	addMessage(write_user_message_string.class);
    }
}
