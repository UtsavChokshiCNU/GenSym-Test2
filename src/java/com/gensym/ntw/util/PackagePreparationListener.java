package com.gensym.ntw.util;

import java.util.EventListener;

public interface PackagePreparationListener extends java.util.EventListener
{

  /**
   * Called when the connection enters package preparation mode.
   */
  public void enterPackagePreparationMode(PackagePreparationEvent evt);

  /**
   * Called when the connection leaves package preparation mode.
   */
  public void leavePackagePreparationMode(PackagePreparationEvent evt);

  /**
   * Called when the connection enters simulate proprietary mode.
   */
  public void enterSimulateProprietaryMode(PackagePreparationEvent evt);

  /**
   * Called when the connection leaves simulate proprietary mode.
   */
  public void leaveSimulateProprietaryMode(PackagePreparationEvent evt);

  
}

