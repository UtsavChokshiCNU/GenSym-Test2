package com.gensym.jgi;

import java.lang.reflect.Method;

/**
 * Class to hold LocalRPC declarations
 */
class LocalRPCDeclaration {
    Object target = null;
    Method target_method = null;
    String target_method_name = null;
    boolean run_in_queued_thread = true;
    boolean run_outside_gsi_thread = true;
    boolean force_return_value = false;

    LocalRPCDeclaration( Object target, 
			 Method method,
			 String target_method_name,
			 boolean run_in_queued_thread,
			 boolean run_outside_gsi_thread,
			 boolean force_return_value) {
      this.target = target;
      this.target_method = method;
      this.target_method_name = target_method_name;
      this.run_in_queued_thread = run_in_queued_thread;
      this.run_outside_gsi_thread = run_outside_gsi_thread;
      this.force_return_value = force_return_value;
    }

  @Override
  public String toString () {
    return super.toString() + "{target=" + target +
      ",target_method=" + target_method +
      ",target_method_name=" + target_method_name +
      ",QdThread=" + run_in_queued_thread +
      ",OutsideGSI=" + run_outside_gsi_thread +
      ",ForceRetn=" + force_return_value + "}";
  }
}
