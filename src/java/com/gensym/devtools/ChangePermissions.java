/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 *   ChangePermissions.java
 */

//NOTE: I know that com/gensym/devtools is the "wrong directory" for this package.
//      The class file is copied into the appriopriate place in JInstallShield home
//      by the build system

package extensions.permissions;
import java.io.DataInput;

//this import statement will include the InstallShield Java Edition API.
import installshield.jshield.runtime.*;

/**
 * This Extension can be used to set file and directory permissions on a Unix machine.
 * Currently this extension will set the permissions of the bin directory, and any
 * files in the entire installation with a .sh extension to to include execute permission
 * for all.
 */
public class ChangePermissions implements Action {

   private boolean isUnix() {
     String osName = System.getProperty("os.name").toLowerCase();

     return osName.indexOf("windows") == -1 && osName.indexOf("os2") == -1 &&
            osName.indexOf("mac") == -1;
   } 

	public boolean execute(InstallContext ctx) {

		if (isUnix())

			//do a chmod command to change the permissions.
			//In this case we are setting the permissions for the bin directory
			//and all .sh files in the installation to include execute permission
                        // for all
			try
			{
			    Runtime.getRuntime().exec("find " + ctx.getInstallRoot()+"//bin -exec chmod +x {} ;");
			    Runtime.getRuntime().exec("find " + ctx.getInstallRoot()+" -name *.sh -exec chmod +x {} ;");
			}
			catch(Exception e) {e.printStackTrace();}

		return true;
	}

	//There are no uninstallation considerations since we are setting full permissions
	//If you set read only permissions then you would have to reset those permissions
	//to remove the files from the system.
	public boolean undo(InstallContext ctx, DataInput undoLog) {
		return true;
	}

	public void cleanup(InstallContext ctx) {}

	//Set the String to display above the progress bar
	public String describe() {
		return "Updating Permissions";
	}
}

