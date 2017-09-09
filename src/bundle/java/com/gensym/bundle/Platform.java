/*
 *   Copyright (C) 1986-2017 Gensym Corporation. All Rights Reserved.
 *
 * 	 Platform.java
 *
 * @author David McDonald
 * @version 0.1 initiated 8/25/00
 */

public class Platform {

    private String name;
    public void setName(String n) { name = n; }
    public String getName() { return name; }

    private int id;
    public void setId(int i) { id = i; }
    public int getId() { return id; }

    public Platform (String name, int id) {
	this.name = name;
	this.id = id;
    }

}
