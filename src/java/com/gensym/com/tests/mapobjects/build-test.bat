echo "ESRI MapObjects ActiveX library from http://www.esri.com"
echo "Requires sample data to be set up"
java -mx80 com.gensym.com.BeanXporter -progid MapObjects.Map.1 -package com.gensym.com.beans -jar .\mapobjects.jar
javac TestMapObjects.java