package com.gensym.cbu.experimental.mibbrowser;

public class ModuleIdentity
{
  String lastUpdated = new String();
  String organization = new String();
  String contactInfo = new String();
  String description = new String();

  public ModuleIdentity ()
    {
    }

  public void setLastUpdated(String s)
    {
      lastUpdated = s;
    }

  public String getLastUpdated()
    {
      return lastUpdated;
    }

  public void setOrganization (String s)
    {
       organization = s;
    }

  public String getOrganization()
    {
      return organization;
    }

  public void setContactInfo (String s)
    {
       contactInfo = s;
    }

  public String getContactInfo()
    {
      return contactInfo;
    }

  public void setDescription (String s)
    {
       description = s;
    }

  public String getDescription()
    {
      return description;
    }
}
