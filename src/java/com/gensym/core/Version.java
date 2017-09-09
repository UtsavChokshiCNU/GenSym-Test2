
package com.gensym.core;

import java.util.StringTokenizer;

/* Version must be in the format of the version.dat file, as follows:
   I J label K
   where I is major version, J is minor version, K is revision, and 
   label is the type of version, one of the following:
   alpha beta prerelease patch revision (and rev, same as revision).
*/

public final class Version {

  private int buildID;
  private int majorVersion;
  private int minorVersion;
  private int releaseType;
  private int revision;


  /**
   * Quality constants
   */
  public static final int PROTOTYPE  = 0;
  public static final int ALPHA      = 1;
  public static final int BETA       = 2;
  public static final int PRERELEASE = 3;
  public static final int RELEASE    = 4;
  public static final int PATCH      = 5;
  public static final int REVISION   = 6;

  /**
   * Tokenization convenience constants
   */
  private static final int MAX_TOKENS             = 4;
  private static final int MAJOR_VERSION_INDEX    = 0;
  private static final int MINOR_VERSION_INDEX    = 1;
  private static final int RELEASE_TYPE_INDEX     = 2;
  private static final int REVISION_INDEX         = 3;

  private String buildVersion;

  Version (String idString, String versionString) throws MalformedProductInfoException {
    try {
      buildID = Integer.parseInt (idString);
    } catch (NumberFormatException nfe) {
      throw new MalformedProductInfoException ("Error parsing build ID : " + nfe);
    }
    parseBuildVersion (versionString);
  }

  private void parseBuildVersion (String versionString) throws MalformedProductInfoException {
    StringTokenizer tknzr = new StringTokenizer (versionString, " ");
    String[] tokens = new String [MAX_TOKENS];
    int i = 0;
    while (tknzr.hasMoreTokens ()) {
      if (i == MAX_TOKENS)
	throw new MalformedProductInfoException ("Too many tokens in build version : " + versionString);
      tokens[i++] = tknzr.nextToken ();
    }
    String expectedTokenType = "major version";
    try {
      majorVersion = Integer.parseInt (tokens[MAJOR_VERSION_INDEX]);
      expectedTokenType = "minor version";
      minorVersion = Integer.parseInt (tokens[MINOR_VERSION_INDEX]);
      expectedTokenType = "release type";
      determineReleaseType (tokens[RELEASE_TYPE_INDEX]);
      expectedTokenType = "revision";
      revision = Integer.parseInt (tokens[REVISION_INDEX]);
    } catch (NumberFormatException nfe) {
      throw new MalformedProductInfoException ("Error parsing " + expectedTokenType + " : " + nfe);
    }
  }

  private void determineReleaseType (final String releaseTypeString) throws MalformedProductInfoException {
    String releaseTypeValue = DebugUtil.removeCharFromString (releaseTypeString.toLowerCase(), '-');
    if (releaseTypeValue.equals ("prototype"))
      releaseType = PROTOTYPE;
    else if (releaseTypeValue.equals ("alpha"))
      releaseType = ALPHA;
    else if (releaseTypeValue.equals ("beta"))
      releaseType = BETA;
    else if (releaseTypeValue.equals ("prerelease"))
      releaseType = PRERELEASE;
    else if (releaseTypeValue.equals ("release"))
      releaseType = RELEASE;
    else if (releaseTypeValue.equals ("patch"))
      releaseType = PATCH;
    else if (releaseTypeValue.equals ("rev") ||
	      releaseTypeValue.equals ("revision"))
      releaseType = REVISION;
    else
      throw new MalformedProductInfoException (releaseTypeValue + " is not a vaid release type");
  }

  @Override
  public String toString () {
    return Integer.toString (majorVersion) + "." +
      Integer.toString (minorVersion) + " " +
      describeReleaseType () + "Rev. " +
      Integer.toString (revision) + " " +
      describeExtendedReleaseType () +
      "(Build " + buildID + ")";
  }

  private String describeReleaseType () {
    switch (releaseType)
      {
      case PROTOTYPE: return "Prototype ";
      case ALPHA: return "Alpha ";
      case BETA: return "Beta ";
      case PRERELEASE: return "Prerelease ";
      case RELEASE:
      case PATCH:
      case REVISION: return "";
      default: return null;
    }
  }
  
  public String shortVersion () {
    return Integer.toString (majorVersion) + "." +
      Integer.toString (minorVersion) +
      describeReleaseTypeShort () +
      Integer.toString (revision);
  }
  
  /* For short version, a bunch of things are defined to be identical to
     "revision".  This versioning has more flexibility in it than the usual
     standard G2 versioning. */
  private String describeReleaseTypeShort () {
    switch (releaseType)
      {
      case ALPHA:
      case BETA: return "a";
      case PROTOTYPE:
      case PRERELEASE: return "p";
      case RELEASE:
      case PATCH: 
      case REVISION: return "r";
      default: return null;
    }
  }

  private String describeExtendedReleaseType () {
    return (releaseType == PATCH ? "Patch " : "");
  }

  public int getBuildID () {
    return buildID;
  }

  public int getMajorVersion () {
    return majorVersion;
  }

  public int getMinorVersion () {
    return minorVersion;
  }

  public int getReleaseType () {
    return releaseType;
  }

  public String getReleaseDescription () {
    switch (releaseType)
      {
      case PROTOTYPE: return "prototype";
      case ALPHA: return "alpha";
      case BETA: return "beta";
      case PRERELEASE: return "prerelease";
      case RELEASE: return "release";
      case PATCH: return "patch";
      case REVISION: return "revision";
      default: return null;
    }
  }

  public int getRevision () {
    return revision;
  }

  void incrementBuildID () {
    buildID += 1;
  }
}

