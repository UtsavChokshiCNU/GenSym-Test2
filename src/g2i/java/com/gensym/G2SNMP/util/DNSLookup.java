/*
 * DNSLookup.java
 *
 * Created on October 31, 2000, 12:17 PM
 */

package com.gensym.G2SNMP.util;

import java.io.*;
import java.nio.charset.Charset;
import java.util.HashMap;



/**
 *
 * @author  hstreete
 * @version 
 */
public class DNSLookup {
    private static final HashMap ADDRESS_INDEX = new HashMap( 1023 );
    private static final HashMap NAME_INDEX = new HashMap( 1023 );
    private static boolean hasReadXrefFile = false;
    private static final byte minByte = -128;
    
    private static final Object ADDRESS_MONITOR = new Object();
    private static final Object NAME_MONITOR = new Object();

    private static class LazyDNSLookupHolder {
    	private static final DNSLookup INSTANCE = new DNSLookup();   	
    }
    /** Creates new DNSLookup */
    private DNSLookup() 
    {
    }
    
    public static DNSLookup getInstance()
    {
        return LazyDNSLookupHolder.INSTANCE;
    }
    
    /** Read an nslookup file to initialize. **/
    
    public void readXrefFile( String xrefFileName )
    {
        if ( hasReadXrefFile == false )
        {
            System.out.println( "Reading cross-reference information from file: " 
                                + xrefFileName );
            File inputFile = new File( xrefFileName );
            FileInputStream fileStream = null;

            try
            {
            	fileStream = new FileInputStream(inputFile);
                BufferedReader inputBuffer = new BufferedReader(new InputStreamReader(fileStream, Charset.defaultCharset()));
                StreamTokenizer tokenizer = new StreamTokenizer( inputBuffer );            
                tokenizer.resetSyntax();
                tokenizer.wordChars( 0x21, 0x7e );
                tokenizer.whitespaceChars( 0x00, 0x20 );

                String hostName = "";
                String hostAddress = "";
                int tokenCount = 0;
                int token = 0;

                while ( token != StreamTokenizer.TT_EOF )
                {
                    try
                    {
                        switch ( tokenCount )
                        {
                            case 0:     // First token is hostname.
                                token = tokenizer.nextToken();
                                System.out.println( "Read hostname token: " + tokenizer.toString() );                        
                                hostName = tokenizer.toString();
                                tokenCount++;
                                break;
                            case 1:     // Second token is type--ignored.
                                token = tokenizer.nextToken();
                                System.out.println( "Read type token: " + tokenizer.toString() );                         
                                tokenCount++;
                                break;
                            case 2:     // Third token is IP address.
                                token = tokenizer.nextToken();
                                System.out.println( "Read address token: " + tokenizer.toString() );                         
                                hostAddress = tokenizer.toString();                       
                                synchronized (NAME_MONITOR) 
                                {
                                  NAME_INDEX.put(hostName, hostAddress);
                                }
                                synchronized (ADDRESS_MONITOR) 
                                {
                                  ADDRESS_INDEX.put(hostAddress, hostName);
                                }
                          tokenCount = 0;  
                                break;
                            default:
                                break;
                        }
                    }
                    catch ( IOException IOX1 )
                    {
                        System.err.println( "Encountered I/O exception." );
                    }
                }          
            }
            catch ( FileNotFoundException FNFX1 )
            {
                System.err.println( "File not found: " + inputFile );
            } finally {
            	if(fileStream != null){
            		try{
            			fileStream.close();
            		}catch(IOException ex) {}
            	}
            }
            
            hasReadXrefFile = true;
            synchronized (ADDRESS_MONITOR) 
            {
              System.out.println( "Read " + ADDRESS_INDEX.entrySet().size() + " address index elements." );
            }
            synchronized (NAME_MONITOR) 
            {
              System.out.println( "Read " + NAME_INDEX.entrySet().size() + " host name index elements." );
            }
        }
        else
        {
            System.err.println( "Error: Cross-reference file has already been read." );
        }
    }
    
    public static String getName( String anIPAddress )
    {
      synchronized (ADDRESS_MONITOR) 
      {
        if ( ADDRESS_INDEX.containsKey( anIPAddress ) )
            return (String)ADDRESS_INDEX.get( anIPAddress );
        else
            return null;
      }
    }
    
    public static String getAddress( String aHostName )
    {
      synchronized (NAME_MONITOR) 
      {
        if ( NAME_INDEX.containsKey( aHostName ) )
            return (String)NAME_INDEX.get( aHostName );
        else
            return null;
      }
    }
    
    public static String inetAddrToString( byte rawAddress[] )
    {
        int intValue;
        String addrString = "";
        
        for ( int i = 0; i < 4; i++ )
        {
            intValue = 128 + (int)( rawAddress[i] ^ minByte );
            addrString += String.valueOf( intValue );
            if ( i < 3 )
                addrString += ".";
        }
        return addrString;
    }
}