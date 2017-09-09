package com.gensym.G2SNMP.trapd;

import com.adventnet.snmp.snmp2.SnmpOID;
/**
   Object that represents a trap pattern for traps to be rejected
*/
class TrapPattern {
    public int Generic;
    public int Specific;
    public SnmpOID Enterprise;


    /**
       Returns true if both TrapPatterns have the same Enterprise, Generic and Specific attributes
       @roseuid 3677792A0327
     */
    @Override
    public boolean equals(Object obj) {
        if (Enterprise.toString().equals((((TrapPattern)obj).Enterprise).toString()) &&
            (Generic == ((TrapPattern)obj).Generic)) {
            // Specific is meaningful only if Generic == 6
            if (Generic == 6) {
                return (this.Specific == ((TrapPattern)obj).Specific);
            } else {
                return true;
            }
        } else {
            return false;
        }
    }
    
    @Override
    public int hashCode() {
    	final int prime = 31;
    	int result = 1;
    	result = prime * result + ((this.Enterprise == null) ? 0 : this.Enterprise.toString().hashCode());
    	result = prime * result + this.Generic;
    	return result;

    }

    /**
       @roseuid 3677792A0395
     */
    public TrapPattern(String anEnterprise, int aGeneric, double aSpecific) throws com.gensym.G2SNMP.rpc.TypeConversionException{
        Enterprise = com.gensym.G2SNMP.rpc.TypeConverter.stringToOid(anEnterprise);
        Generic = com.gensym.G2SNMP.rpc.TypeConverter.intToGenericId(aGeneric);
        Specific = com.gensym.G2SNMP.rpc.TypeConverter.doubleToSpecificId(aSpecific);
    }

}