package com.trilogy.gensym.xml.elements;

/**
 * @author rvasyl
 *
 */
public class Shortcut {

    private String shortcutName;
    private String folderName;
    private String subfolderName;
    private String subsubfolderName;
    private String appDisplayName;
    private String appDirectory;
    private String targetName;
    private String parameters;
    private String iconFile;
    private float  iconIndex;
    private String runStyle;

    /**
     * Content of 'shortcut' tag in XML file.
     * 
     * @param shortcutName
     * @param folderName
     * @param subfolderMame
     * @param subsubfolderName
     * @param appDisplayName
     * @param appDirectory
     * @param targetName
     * @param parameters
     * @param iconFile
     * @param iconIndex
     * @param runStyle
     */
    public Shortcut (String shortcutName, String folderName, String subfolderMame, String subsubfolderName, 
            String appDisplayName, String appDirectory, String targetName, String parameters,
            String iconFile, float iconIndex, String runStyle) {
        this.shortcutName = shortcutName;
        this.folderName = folderName;
        this.subfolderName = subfolderMame;
        this.subsubfolderName = subsubfolderName;
        this.appDisplayName = appDisplayName;
        this.appDirectory = appDirectory;
        this.targetName = targetName;
        this.parameters = parameters;
        this.iconFile = iconFile;
        this.iconIndex = iconIndex;
        this.runStyle = runStyle;
    }

    public String getShortcutName() {
        return shortcutName;
    }

    public String getFolderName() {
        return folderName;
    }

    public String getSubfolderName() {
        return subfolderName;
    }

    public String getSubsubfolderName() {
        return subsubfolderName;
    }

    public String getAppDisplayName() {
        return appDisplayName;
    }

    public String getAppDirectory() {
        return appDirectory;
    }

    public String getTargetName() {
        return targetName;
    }

    public String getParameters() {
        return parameters;
    }

    public String getIconFile() {
        return iconFile;
    }

    public float getIconIndex() {
        return iconIndex;
    }

    public String getRunStyle() {
        return runStyle;
    }
}
