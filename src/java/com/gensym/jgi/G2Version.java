
package com.gensym.jgi;

import java.util.StringTokenizer;
import com.gensym.util.Structure;
import com.gensym.util.Symbol;
import com.gensym.util.NoSuchAttributeException;

/**
 * A class that encapsulates the version for a product (currently
 * G2 and GSI?). It can be used to determine if a particular
 * G2Version matches a minimum version.x
 *
 * @author vkp
 * @version 1.0 2/10/97
 */
public class G2Version {

  private int majorVersion;
  private int minorVersion;
  private String releaseQuality;
  private int releaseQualityID;
  private int revision;
  private String buildID, revString;
  private int dayOfYearApprox;

  /**
   * Private codes for expected tokens in Build Identification string
   */
  private static final int
    VERSION      = 0,
    MAJOR_VERSION= 1,
    MINOR_VERSION= 2,
    REVISION     = 3,
    RELEASE_TYPE = 4,
    NONE         = 5;


  /*
   * Return values from compareTo
   */

  /**
   * Constant for indicating that this G2Version is older
   * than the one being compared to.
   */
  public static final int OLDER = -1;

  /**
   * Constant for indicating that this G2Version the same
   * as the one being compared to.
   */
  public static final int EQUAL = 0;

  /**
   * Constant for indicating that this G2Version is newer
   * than the one being compared to.
   */
  public static final int NEWER = 1;

  /**
   * The release types in decreasing order of stability
   */
  private static final String
    RELEASED  = "Rev",
    BETA      = "Beta",
    ALPHA     = "Alpha",
    PROTOTYPE = "Prototype";

  private static final int
    UNKNOWN_ID   = -1,   // for newly invented levels => cannot be used for comparison
    PROTOTYPE_ID = 0,
    ALPHA_ID     = 1,
    BETA_ID      = 2,
    RELEASED_ID  = 3;

  private static final Symbol
    PROTOTYPE_ = Symbol.intern ("PROTOTYPE"),
    ALPHA_     = Symbol.intern ("ALPHA"),
    BETA_      = Symbol.intern ("BETA"),
    RELEASED_  = Symbol.intern ("RELEASED");


  /**
   * Creates a new G2Version objects from the arguments
   * @param majorVersion the major version number
   * @param minorVersion the minor version number
   * @param releaseQuality the release type
   * @param revision the revision number
   * @param buildID the identification code for the build
   */
  public G2Version (int majorVersion,
		    int minorVersion,
		    String releaseQuality,
		    int revision,
		    String buildID) {
    this.majorVersion = majorVersion;
    this.minorVersion = minorVersion;
    this.releaseQuality = releaseQuality;
    this.revision = revision;
    this.buildID = buildID;
    releaseQualityID = mapQualityToID (releaseQuality);
    fillInDate (buildID);
  }

  private static final Symbol MAJOR_VERSION_NUMBER_ = Symbol.intern ("MAJOR-VERSION-NUMBER");
  private static final Symbol MINOR_VERSION_NUMBER_ = Symbol.intern ("MINOR-VERSION-NUMBER");
  private static final Symbol RELEASE_LEVEL_ = Symbol.intern ("RELEASE-LEVEL");
  private static final Symbol REVISION_ = Symbol.intern ("REVISION");
  private static final Symbol PATCH_NUMBER_ = Symbol.intern ("PATCH-NUMBER");
  private static final Symbol BUILD_IDENTIFICATION_ = Symbol.intern ("BUILD-IDENTIFICATION");


  /**
   * Creates a new G2Version object from the data in the Structure.
   * The structure must contain all the necessary information
   * @param versionStruct
   */
  protected G2Version (Structure versionSruct) {
    Symbol releaseLevel_;
    try {
      majorVersion = 
	((Integer)versionSruct.getAttributeValue(MAJOR_VERSION_NUMBER_)).intValue();
      minorVersion =
	((Integer)versionSruct.getAttributeValue(MINOR_VERSION_NUMBER_)).intValue();
      releaseLevel_ =
	(Symbol)versionSruct.getAttributeValue(RELEASE_LEVEL_);
      revision = 
	((Integer)versionSruct.getAttributeValue(REVISION_)).intValue();
      buildID =
	(String)versionSruct.getAttributeValue(BUILD_IDENTIFICATION_);
    } catch (NoSuchAttributeException e) {
      throw new com.gensym.util.CorruptionException(e);
    }
    releaseQuality = mapQualitySymbolToQuality(releaseLevel_);
    releaseQualityID = mapQualityToID (releaseQuality);
    fillInDate(buildID);
  }


  /**
   * Creates a new G2Version object from a build
   * identification string from G2. The String must be
   * formatted properly or else a RuntimeException will
   * be thrown.
   * @param buildIdentificationString the identification string for a G2
   */
  public G2Version (String buildIdentificationString) {
    StringTokenizer tknzr = new StringTokenizer (buildIdentificationString, " .");
    String token = null;
    int expectedToken = VERSION;
    while (tknzr.hasMoreTokens ()) {
      token = tknzr.nextToken ();
      switch (expectedToken)
	{
	case VERSION:
	  if (!(token.equals ("Version")))
	    throw new IllegalArgumentException ("Version expected. Got <" + token + ">");
	  expectedToken = MAJOR_VERSION;
	  break;
	case MAJOR_VERSION:
	  majorVersion = Integer.parseInt (token);
	  expectedToken = MINOR_VERSION;
	  break;
	case MINOR_VERSION:
	  minorVersion = Integer.parseInt (token);
	  expectedToken = RELEASE_TYPE;
	  break;
	case REVISION:
	  revString = token;
	  while (!Character.isDigit (token.charAt (token.length() - 1))) // Can be "1b" etc.
	    token = token.substring (0, token.length () - 1);            // Remove all trailing chars.
	  revision = Integer.parseInt (token);
	  expectedToken = NONE;
	  break;
	case RELEASE_TYPE:
	  releaseQuality = token;
	  releaseQualityID = mapQualityToID (releaseQuality);
	  expectedToken = REVISION;
	  break;
	default:
	}
    }
    if (token.length () != 3 && token.length () != 4)
      throw new IllegalArgumentException ("Illegal build ID String <" + token + ">");
    buildID = token;
    fillInDate (buildID);
  }

  /**
   * Returns a description of this G2Version
   * @return a String description of this object
   */
  @Override
  public String toString () {
    return "G2Version [MAJOR = " + majorVersion + ":" +
           "MINOR = " + minorVersion + ":" +
           "TYPE  = " + releaseQuality + ":" +
           "REVISION = " + revString + ":" +
           "ID    = " + buildID + " DOY = " + dayOfYearApprox + "]";
  }

  /**
   * Compares against another G2Version object.
   * @param version the G2Version to compare to
   * @return an integer indicating if the version represented by this
   *   object is older than, the same as, or newer than the argument.
   * @see com.gensym.jgi.G2Version#OLDER
   * @see com.gensym.jgi.G2Version#EQUAL
   * @see com.gensym.jgi.G2Version#NEWER
   */
  public int compareTo (G2Version version) {
    if (majorVersion > version.majorVersion)
      return NEWER;
    else if (majorVersion < version.majorVersion)
      return OLDER;

    if (minorVersion > version.minorVersion)
      return NEWER;
    else if (minorVersion < version.minorVersion)
      return OLDER;

    if (releaseQualityID == UNKNOWN_ID ||
	version.releaseQualityID == UNKNOWN_ID)
      throw new IllegalArgumentException ("Illegal Quality String <" + releaseQuality +  ">");
    if (releaseQualityID > version.releaseQualityID)
      return NEWER;
    else if (releaseQualityID < version.releaseQualityID)
      return OLDER;

    if (revision > version.revision)
      return NEWER;
    else if (revision < version.revision)
      return OLDER;

    if (dayOfYearApprox > version.dayOfYearApprox)
      return NEWER;
    else if (dayOfYearApprox < version.dayOfYearApprox)
      return OLDER;

    return EQUAL;
  }

  /**
   * Check if this object represents the same version
   * as the G2Version passed in.
   * @return true if the two versions are the same, false otherwise.
   */
  @Override
  public boolean equals (Object otherVersion) {
	if(otherVersion == null || !G2Version.class.equals(otherVersion.getClass())){
		return false;
	}
	
    return (compareTo ((G2Version)otherVersion) == EQUAL);
  }
  
  @Override
  public int hashCode(){
	final int prime = 31;
  	int result = 1;
  	result = prime * result + this.majorVersion;
  	result = prime * result + this.minorVersion;
  	result = prime * result + this.releaseQualityID;
  	result = prime * result + this.revision;
  	result = prime * result + this.dayOfYearApprox;
  	return result;  
  }

  private int mapQualityToID (String releaseQuality) {
    if (releaseQuality.equals (RELEASED))
      return RELEASED_ID;
    else if (releaseQuality.equals (BETA))
      return BETA_ID;
    else if (releaseQuality.equals (ALPHA))
      return ALPHA_ID;
    else if (releaseQuality.equals (PROTOTYPE))
      return PROTOTYPE_ID;
    else
      return UNKNOWN_ID;
  }


  private String mapQualitySymbolToQuality (Symbol qualitySymbol_) {
    if (qualitySymbol_.equals(PROTOTYPE_))
      return PROTOTYPE;
    else if (qualitySymbol_.equals(ALPHA_))
      return ALPHA;
    else if (qualitySymbol_.equals(BETA_))
      return BETA;
    else if (qualitySymbol_.equals(RELEASED_))
      return RELEASED;
    else
      return qualitySymbol_.getPrintValue();
  }


  private void fillInDate (String buildID) {
    int monthIndex = 0;
    int yearNumber = 0; // = 1998
    char firstChar = buildID.charAt (0);
    if (Character.isDigit (firstChar)) {
      if (firstChar != '8')
	System.err.println ("Possible error in build-id <" + buildID + ">");
      yearNumber = firstChar - '0' - 8;
      monthIndex = 1;
    } else if (buildID.length () == 4) {
      yearNumber = firstChar - 'A';
      monthIndex = 1;
    } // else no year. Assume 0
    char month = buildID.charAt (monthIndex);
    int monthNumber = month - 'A';
    int date = Integer.parseInt (buildID.substring (monthIndex + 1));
    dayOfYearApprox = yearNumber*366 + monthNumber*31 + date;
  }

  public int getMajorVersion () {
    return majorVersion;
  }

  public int getMinorVersion () {
    return minorVersion;
  }

  public String getReleaseQuality () {
    return releaseQuality;
  }

  public int getRevision () {
    return revision;
  }

  // public char? getPatchVersion

  public String getBuildID () {
    return buildID;
  }

}
