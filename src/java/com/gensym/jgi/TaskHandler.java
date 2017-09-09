package com.gensym.jgi;

/**
 * A TaskHandler is responsible for handling the execution of tasks
 */
public interface TaskHandler 
{

  /**
   * Start a task for a given owner object. 
   * @param task The task to start in another Thread.
   * @param owner An object responsible for the task.
   * @param runInQueuedThreadRequest A request to queue tasks for this target.
   * @return True if the task was handled, false if not.
   */
  public boolean start(Runnable task,
		       Object owner,
		       boolean runInQueuedThreadRequest);

}
