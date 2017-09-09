/*
 *  Copyright (C) 1986-2017 Gensym Corporation.
 *  All Rights Reserved.
 *
 *      PlanetImpl.java
 *
 *   Description: Generated Interface file. Do not edit!
 *
 *        Author: Gensym Corp.
 *
 *       Version: 5.1 Rev. 0 (H15)
 *
 *          Date: Tue Dec 01 18:08:57 EST 1998
 *
 */


package com.gensym.demos.democlasses;

import com.gensym.classes.*;
import com.gensym.util.Structure;
import com.gensym.util.Sequence;
import com.gensym.util.Symbol;
import com.gensym.util.symbol.SystemAttributeSymbols;
import com.gensym.jgi.*;
import com.gensym.classes.Object;

public class PlanetImpl extends com.gensym.classes.ObjectImpl implements Planet {


  static final long serialVersionUID = 2L;
  private static final Symbol IS_INHABITED_ = Symbol.intern ("IS-INHABITED");
  private static final Symbol NUMBER_OF_MOONS_ = Symbol.intern ("NUMBER-OF-MOONS");
  private static final Symbol MOONS_ = Symbol.intern ("MOONS");
  private static final Symbol DISTANCE_FROM_THE_SUN_ = Symbol.intern ("DISTANCE-FROM-THE-SUN");
  private static final Symbol TEMPERATURE_ = Symbol.intern ("TEMPERATURE");
  private static final Symbol TEMPERATURE_THRESHOLD_ = Symbol.intern ("TEMPERATURE-THRESHOLD");
  private static final Symbol ATMOSPHERIC_PRESSURE_ = Symbol.intern ("ATMOSPHERIC-PRESSURE");
  private static final Symbol ORBITAL_VELOCITY_ = Symbol.intern ("ORBITAL-VELOCITY");
  private static final Symbol HAS_RINGS_ = Symbol.intern ("HAS-RINGS");
  private static final Symbol DISCOVERER_ = Symbol.intern ("DISCOVERER");

  /* Generated constructors */

  public PlanetImpl() {
    super();
  }

  public PlanetImpl(G2Access context, int handle, Structure attributes) {
    super (context, handle, attributes);
  }


  /**
   * Generated Property Setter for attribute -- IS-INHABITED
   * @param isInhabited new value to conclude for IS-INHABITED
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setIsInhabited(boolean isInhabited) throws G2AccessException {
    setAttributeValue (IS_INHABITED_, new Boolean (isInhabited));
  }

  /**
   * Generated Property Getter for attribute -- IS-INHABITED
   * @return the value of the IS-INHABITED attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getIsInhabited() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (IS_INHABITED_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- NUMBER-OF-MOONS
   * @param numberOfMoons new value to conclude for NUMBER-OF-MOONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setNumberOfMoons(int numberOfMoons) throws G2AccessException {
    setAttributeValue (NUMBER_OF_MOONS_, new Integer (numberOfMoons));
  }

  /**
   * Generated Property Getter for attribute -- NUMBER-OF-MOONS
   * @return the value of the NUMBER-OF-MOONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public int getNumberOfMoons() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (NUMBER_OF_MOONS_);
    return ((Integer)retnValue).intValue ();
  }

  /**
   * Generated Property Setter for attribute -- MOONS
   * @param moons new value to conclude for MOONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setMoons(com.gensym.classes.ItemArray moons) throws G2AccessException {
    setAttributeValue (MOONS_, moons);
  }

  /**
   * Generated Property Getter for attribute -- MOONS
   * @return the value of the MOONS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.classes.ItemArray getMoons() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (MOONS_);
    return (com.gensym.classes.ItemArray)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DISTANCE-FROM-THE-SUN
   * @param distanceFromTheSun new value to conclude for DISTANCE-FROM-THE-SUN
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDistanceFromTheSun(java.lang.Number distanceFromTheSun) throws G2AccessException {
    setAttributeValue (DISTANCE_FROM_THE_SUN_, distanceFromTheSun);
  }

  /**
   * Generated Property Getter for attribute -- DISTANCE-FROM-THE-SUN
   * @return the value of the DISTANCE-FROM-THE-SUN attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Number getDistanceFromTheSun() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (DISTANCE_FROM_THE_SUN_);
    return (java.lang.Number)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TEMPERATURE
   * @param temperature new value to conclude for TEMPERATURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTemperature(java.lang.Number temperature) throws G2AccessException {
    setAttributeValue (TEMPERATURE_, temperature);
  }

  /**
   * Generated Property Getter for attribute -- TEMPERATURE
   * @return the value of the TEMPERATURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Number getTemperature() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (TEMPERATURE_);
    return (java.lang.Number)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- TEMPERATURE-THRESHOLD
   * @param temperatureThreshold new value to conclude for TEMPERATURE-THRESHOLD
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setTemperatureThreshold(java.lang.Number temperatureThreshold) throws G2AccessException {
    setAttributeValue (TEMPERATURE_THRESHOLD_, temperatureThreshold);
  }

  /**
   * Generated Property Getter for attribute -- TEMPERATURE-THRESHOLD
   * @return the value of the TEMPERATURE-THRESHOLD attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Number getTemperatureThreshold() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (TEMPERATURE_THRESHOLD_);
    return (java.lang.Number)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ATMOSPHERIC-PRESSURE
   * @param atmosphericPressure new value to conclude for ATMOSPHERIC-PRESSURE
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAtmosphericPressure(java.lang.Number atmosphericPressure) throws G2AccessException {
    setAttributeValue (ATMOSPHERIC_PRESSURE_, atmosphericPressure);
  }

  /**
   * Generated Property Getter for attribute -- ATMOSPHERIC-PRESSURE
   * @return the value of the ATMOSPHERIC-PRESSURE attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Number getAtmosphericPressure() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (ATMOSPHERIC_PRESSURE_);
    return (java.lang.Number)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ORBITAL-VELOCITY
   * @param orbitalVelocity new value to conclude for ORBITAL-VELOCITY
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setOrbitalVelocity(java.lang.Number orbitalVelocity) throws G2AccessException {
    setAttributeValue (ORBITAL_VELOCITY_, orbitalVelocity);
  }

  /**
   * Generated Property Getter for attribute -- ORBITAL-VELOCITY
   * @return the value of the ORBITAL-VELOCITY attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Number getOrbitalVelocity() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (ORBITAL_VELOCITY_);
    return (java.lang.Number)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- HAS-RINGS
   * @param hasRings new value to conclude for HAS-RINGS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setHasRings(boolean hasRings) throws G2AccessException {
    setAttributeValue (HAS_RINGS_, new Boolean (hasRings));
  }

  /**
   * Generated Property Getter for attribute -- HAS-RINGS
   * @return the value of the HAS-RINGS attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public boolean getHasRings() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (HAS_RINGS_);
    return ((Boolean)retnValue).booleanValue ();
  }

  /**
   * Generated Property Setter for attribute -- DISCOVERER
   * @param discoverer new value to conclude for DISCOVERER
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDiscoverer(com.gensym.demos.democlasses.DiscovererInformation discoverer) throws G2AccessException {
    setAttributeValue (DISCOVERER_, discoverer);
  }

  /**
   * Generated Property Getter for attribute -- DISCOVERER
   * @return the value of the DISCOVERER attribute of this item
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.demos.democlasses.DiscovererInformation getDiscoverer() throws G2AccessException {
    java.lang.Object retnValue = getAttributeValue (DISCOVERER_);
    return (com.gensym.demos.democlasses.DiscovererInformation)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- AUTHORS
   * @param authors new value to conclude for AUTHORS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAuthorsForClass(com.gensym.util.Structure authors) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.AUTHORS_, authors);
  }

  /**
   * Generated Property Getter for attribute -- AUTHORS
   * @return the value of the AUTHORS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Structure getAuthorsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.AUTHORS_);
    return (com.gensym.util.Structure)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CHANGE-LOG
   * @return the value of the CHANGE-LOG attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getChangeLogForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CHANGE_LOG_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CLASS-NAME
   * @param className new value to conclude for CLASS-NAME
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setClassNameForClass(com.gensym.util.Symbol className) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.CLASS_NAME_, className);
  }

  /**
   * Generated Property Getter for attribute -- CLASS-NAME
   * @return the value of the CLASS-NAME attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Symbol getClassNameForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_NAME_);
    return (com.gensym.util.Symbol)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- CLASS-SPECIFIC-ATTRIBUTES
   * @param classSpecificAttributes new value to conclude for CLASS-SPECIFIC-ATTRIBUTES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setClassSpecificAttributesForClass(com.gensym.util.Sequence classSpecificAttributes) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.CLASS_SPECIFIC_ATTRIBUTES_, classSpecificAttributes);
  }

  /**
   * Generated Property Getter for attribute -- CLASS-SPECIFIC-ATTRIBUTES
   * @return the value of the CLASS-SPECIFIC-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getClassSpecificAttributesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_SPECIFIC_ATTRIBUTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CLASS-RESTRICTIONS
   * @return the value of the CLASS-RESTRICTIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getClassRestrictionsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_RESTRICTIONS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- INSTANCE-CONFIGURATION
   * @param instanceConfiguration new value to conclude for INSTANCE-CONFIGURATION
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setInstanceConfigurationForClass(com.gensym.util.Sequence instanceConfiguration) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.INSTANCE_CONFIGURATION_, instanceConfiguration);
  }

  /**
   * Generated Property Getter for attribute -- INSTANCE-CONFIGURATION
   * @return the value of the INSTANCE-CONFIGURATION attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getInstanceConfigurationForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INSTANCE_CONFIGURATION_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CLASS-INHERITANCE-PATH
   * @return the value of the CLASS-INHERITANCE-PATH attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getClassInheritancePathForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CLASS_INHERITANCE_PATH_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- INHERITED-ATTRIBUTES
   * @return the value of the INHERITED-ATTRIBUTES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getInheritedAttributesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.INHERITED_ATTRIBUTES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- SUPERIOR-CLASS
   * @return the value of the SUPERIOR-CLASS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getSuperiorClassForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.SUPERIOR_CLASS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CAPABILITIES-AND-RESTRICTIONS
   * @return the value of the CAPABILITIES-AND-RESTRICTIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getCapabilitiesAndRestrictionsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CAPABILITIES_AND_RESTRICTIONS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTES-SPECIFIC-TO-CLASS
   * @return the value of the ATTRIBUTES-SPECIFIC-TO-CLASS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getAttributesSpecificToClassForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTES_SPECIFIC_TO_CLASS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- MENU-OPTION
   * @return the value of the MENU-OPTION attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getMenuOptionForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.MENU_OPTION_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- DIRECT-SUPERIOR-CLASSES
   * @param directSuperiorClasses new value to conclude for DIRECT-SUPERIOR-CLASSES
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setDirectSuperiorClassesForClass(com.gensym.util.Sequence directSuperiorClasses) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.DIRECT_SUPERIOR_CLASSES_, directSuperiorClasses);
  }

  /**
   * Generated Property Getter for attribute -- DIRECT-SUPERIOR-CLASSES
   * @return the value of the DIRECT-SUPERIOR-CLASSES attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getDirectSuperiorClassesForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.DIRECT_SUPERIOR_CLASSES_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- CHANGE
   * @return the value of the CHANGE attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getChangeForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.CHANGE_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ATTRIBUTE-INITIALIZATIONS
   * @param attributeInitializations new value to conclude for ATTRIBUTE-INITIALIZATIONS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAttributeInitializationsForClass(com.gensym.util.Sequence attributeInitializations) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_INITIALIZATIONS_, attributeInitializations);
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-INITIALIZATIONS
   * @return the value of the ATTRIBUTE-INITIALIZATIONS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public com.gensym.util.Sequence getAttributeInitializationsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_INITIALIZATIONS_);
    return (com.gensym.util.Sequence)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- ATTRIBUTE-DISPLAYS
   * @param attributeDisplays new value to conclude for ATTRIBUTE-DISPLAYS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setAttributeDisplaysForClass(java.lang.Object attributeDisplays) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_DISPLAYS_, attributeDisplays);
  }

  /**
   * Generated Property Getter for attribute -- ATTRIBUTE-DISPLAYS
   * @return the value of the ATTRIBUTE-DISPLAYS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getAttributeDisplaysForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.ATTRIBUTE_DISPLAYS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Setter for attribute -- STUBS
   * @param stubs new value to conclude for STUBS
   * @exception G2AccessException if there are any communication problems
   *              or the value does not match with the type specification
   */
  @Override
  public void setStubsForClass(java.lang.Object stubs) throws G2AccessException {
    setStaticAttributeValue (SystemAttributeSymbols.STUBS_, stubs);
  }

  /**
   * Generated Property Getter for attribute -- STUBS
   * @return the value of the STUBS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getStubsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.STUBS_);
    return (java.lang.Object)retnValue;
  }

  /**
   * Generated Property Getter for attribute -- DEFAULT-SETTINGS
   * @return the value of the DEFAULT-SETTINGS attribute of this class
   * @exception G2AccessException if there are any communication problems
   */
  @Override
  public java.lang.Object getDefaultSettingsForClass() throws G2AccessException {
    java.lang.Object retnValue = getStaticAttributeValue (SystemAttributeSymbols.DEFAULT_SETTINGS_);
    return (java.lang.Object)retnValue;
  }

  // Method Name Constants
  private static final Symbol MethodName_CHANGE_TEMPERATURE_SIMULATION_ = Symbol.intern ("CHANGE-TEMPERATURE-SIMULATION");
  private static final Symbol MethodName_MOVE_ = Symbol.intern ("MOVE");
  private static final Symbol MethodName_INITIALIZE_ = Symbol.intern ("INITIALIZE");
  private static final Symbol MethodName_DISPLAY_ALARM_ = Symbol.intern ("DISPLAY-ALARM");
  private static final Symbol MethodName_MOVE_PLANET_ = Symbol.intern ("MOVE-PLANET");
  private static final Symbol MethodName_STOP_PLANET_ = Symbol.intern ("STOP-PLANET");
  private static final Symbol MethodName_CHECK_FOR_ECLIPSE_ = Symbol.intern ("CHECK-FOR-ECLIPSE");
  private static final Symbol MethodName_ADD_MOON_ = Symbol.intern ("ADD-MOON");
  private static final Symbol MethodName_REMOVE_MOON_ = Symbol.intern ("REMOVE-MOON");
  private static final Symbol MethodName_UPDATE_MOONS_ = Symbol.intern ("UPDATE-MOONS");
  private static final Symbol MethodName_MOVE_MOONS_ = Symbol.intern ("MOVE-MOONS");
  private static final Symbol MethodName_MOVE_ALARM_ = Symbol.intern ("MOVE-ALARM");
  private static String NoBodyExceptionString = "This method has no implementation for local access";
  
  
  //Generated Methods 

  /**
   * Auto Generated method for G2 Method
   * PLANET::CHANGE-TEMPERATURE-SIMULATION
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS PLANET) = ()
   */
  @Override
  public  void changeTemperatureSimulation() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_CHANGE_TEMPERATURE_SIMULATION_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * PLANET::MOVE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS PLANET) = ()
   */
  @Override
  public  void move() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_MOVE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * PLANET::INITIALIZE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS PLANET) = ()
   */
  @Override
  public  void initialize() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_INITIALIZE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * PLANET::DISPLAY-ALARM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS PLANET,arg1:TEXT) = ()
   */
  @Override
  public  void displayAlarm(java.lang.String arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_DISPLAY_ALARM_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * PLANET::MOVE-PLANET
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS PLANET) = ()
   */
  @Override
  public  void movePlanet() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_MOVE_PLANET_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * PLANET::STOP-PLANET
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS PLANET) = ()
   */
  @Override
  public  void stopPlanet() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_STOP_PLANET_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * PLANET::CHECK-FOR-ECLIPSE
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS PLANET,arg1:CLASS PLANET) = ()
   */
  @Override
  public  void checkForEclipse(com.gensym.demos.democlasses.Planet arg1) throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this,arg1};
      result = (java.lang.Object)callRPC(MethodName_CHECK_FOR_ECLIPSE_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * PLANET::ADD-MOON
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS PLANET) = ()
   */
  @Override
  public  void addMoon() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_ADD_MOON_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * PLANET::REMOVE-MOON
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS PLANET) = ()
   */
  @Override
  public  void removeMoon() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_REMOVE_MOON_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * PLANET::UPDATE-MOONS
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS PLANET) = ()
   */
  @Override
  public  void updateMoons() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_UPDATE_MOONS_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * PLANET::MOVE-MOONS
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS PLANET) = ()
   */
  @Override
  public  void moveMoons() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_MOVE_MOONS_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
  /**
   * Auto Generated method for G2 Method
   * PLANET::MOVE-ALARM
   * @exception G2AccessException if there are any communication problems
   * (this:CLASS PLANET) = ()
   */
  @Override
  public  void moveAlarm() throws G2AccessException
{
    if (isByHandle()) {
      java.lang.Object result;
      java.lang.Object[] args = new java.lang.Object[] {this};
      result = (java.lang.Object)callRPC(MethodName_MOVE_ALARM_, args);
    }
    else {
      // No MethodBody for by-copy exported
      throw new RuntimeException(NoBodyExceptionString);
    }
  }
  
}
