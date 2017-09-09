package com.gensym.nols.main;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.Serializable;
import java.text.SimpleDateFormat;
import java.util.Vector;


/**
 * Application settings controller
 *
 */
public class NolSettings implements Serializable {

	private static final long serialVersionUID = 7160626611145043805L;
	private static volatile NolSettings instance;
	private static final String FILE_NAME =  "settings.nol";
	// Windows-specific folder
	private static final File FOLDER = new File(System.getenv("APPDATA") + File.separator + "nolstudio");
	
	private Vector<String> customDateTimeFormatsVector;
	private Vector<String> customTimeFormatsVector;
	private Vector<String> customDateFormatsVector;
	private SimpleDateFormat dateFormat;
	private SimpleDateFormat timeFormat;

	private NolSettings() {
		customTimeFormatsVector = new Vector<String>();
		customDateFormatsVector = new Vector<String>();
		customDateTimeFormatsVector = new Vector<String>();
	}

	public static NolSettings getSettings() {
		if (instance == null) {
			synchronized (NolSettings.class) {
				if (instance == null) {
					instance = load();
				}
			}
		}
		return instance;
	}

	/**
	 * Save settings in file
	 */
	public static void save() {
		ObjectOutputStream oos = null;
		FileOutputStream fos = null;
		try {
			if (!FOLDER.exists()){
				FOLDER.mkdir();
			}
			fos = new FileOutputStream(new File(FOLDER, FILE_NAME), true);
			oos = new ObjectOutputStream(fos);
			oos.writeObject(instance);
		} catch (IOException e) {
			e.printStackTrace();
		} finally {
			try {
				if (fos != null) {
					fos.close();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
			try {
				if (oos != null) {
					oos.close();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

	}

	private static NolSettings load() {
		NolSettings instance = new NolSettings();
		ObjectInputStream ois = null;
		FileInputStream fis = null;
		try {
			if (FOLDER.exists()){
				fis = new FileInputStream(new File(FOLDER, FILE_NAME));
				ois = new ObjectInputStream(fis);
				instance = (NolSettings) ois.readObject();
			}
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		} finally {
			try {
				if (fis != null) {
					fis.close();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
			try {
				if (ois != null) {
					ois.close();
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
		}

		return instance;
	}

	public Vector<String> getCustomDateTimeFormatsVector() {
		return customDateTimeFormatsVector;
	}

	public void setCustomDateTimeFormatsVector(Vector<String> customDateTimeFormatsVector) {
		this.customDateTimeFormatsVector = customDateTimeFormatsVector;
	}

	public Vector<String> getCustomTimeFormatsVector() {
		return customTimeFormatsVector;
	}

	public void setCustomTimeFormatsVector(Vector<String> customTimeFormatsVector) {
		this.customTimeFormatsVector = customTimeFormatsVector;
	}

	public Vector<String> getCustomDateFormatsVector() {
		return customDateFormatsVector;
	}

	public void setCustomDateFormatsVector(Vector<String> customDateFormatsVector) {
		this.customDateFormatsVector = customDateFormatsVector;
	}

	public SimpleDateFormat getTimeFormat() {
		return timeFormat;
	}

	public void setTimeFormat(SimpleDateFormat timeFormat) {
		this.timeFormat = timeFormat;
	}

	public SimpleDateFormat getDateFormat() {
		return dateFormat;
	}

	public void setDateFormat(SimpleDateFormat dateFormat) {
		this.dateFormat = dateFormat;
	}

}
