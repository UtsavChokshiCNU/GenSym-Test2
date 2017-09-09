echo "QC Charter control (from jed)"
java -mx80 com.gensym.com.BeanXporter -progid CCOCX.CCOCXCtrl.1  -package com.gensym.com.beans -jar .\charter.jar
javac TestCharter.java