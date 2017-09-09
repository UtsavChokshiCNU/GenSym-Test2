package com.gensym.cbu.experimental.mibbrowser;

public class OidEntry implements MibFileObjectTableObject
{
  public String shortName;
  public String shortValue;
  public String definingFile;
  public String oidEntryType;
  public String longName;
  public String longValue;
  public String parentShortName;
  public String parentDefiningFile;

  //MibFileObject Interface
  @Override
  public int getRowCount()
    {
      return 8;
    }

  @Override
  public String getAttribute(int row)
    {
      switch (row) {
      case 0: return "Short Name";
      case 1: return "Short Value";
      case 2: return "Defining File";
      case 3: return "Oid Entry Type";
      case 4: return "Long Name";
      case 5: return "Long Value";
      case 6: return "Parent Short Name";
      case 7: return "Parent Defining File";
      default: return "?";
      }
    }

    @Override
    public String getValue(int row)
    {
      switch (row) {
      case 0: return shortName;
      case 1: return shortValue;
      case 2: return definingFile;
      case 3: return oidEntryType;
      case 4: return longName;
      case 5: return longValue;
      case 6: return parentShortName;
      case 7: return parentDefiningFile;
      default: return "?";
      }
    }
    //end MibFileObject Interface
  
  public OidEntry (String sn, String sv, String df, String psn, String pdf)
    {
      shortName = sn;
      shortValue = sv;
      definingFile =  df;
      parentShortName = psn;
      parentDefiningFile = pdf;
    }

  @Override
  public String toString()
    {
      return shortName;
    }
}
