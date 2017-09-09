echo "WorldView for Developers 2.1 from http://www.intervista.com/download/index.html"
echo "Requires the file D:\rucube.wrl"
java -mx80 com.gensym.com.BeanXporter -progid WORLDVIEW.WorldViewCtrl.1  -package com.gensym.com.beans -jar .\worldview.jar
javac TestWorldView.java