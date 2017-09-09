: clean-staging.bat
: AUTHOR: SJW
: CREATED: 4/26/99 

: USAGE:
: DESCRIPTION:   

: REMOVE OLD DIRECTORIES
: INTELNT
rd /S/Q %SRCBOX%\javalink\javalink-intelnt-staging
rd /S/Q %SRCBOX%\sequoia\sequoia-intelnt-staging\java
: SPARCSOL
rd /S/Q %SRCBOX%\javalink\javalink-sparcsol-staging
rd /S/Q %SRCBOX%\sequoia\sequoia-sparcsol-staging

: CREATE NEW DIRECTORIES
: INTELNT
mkdir %SRCBOX%\javalink
mkdir %SRCBOX%\javalink\javalink-intelnt-staging
mkdir %SRCBOX%\javalink\javalink-intelnt-staging\bin
mkdir %SRCBOX%\javalink\javalink-intelnt-staging\classes
mkdir %SRCBOX%\javalink\javalink-intelnt-staging\classes\jars
mkdir %SRCBOX%\javalink\javalink-intelnt-staging\docs
mkdir %SRCBOX%\javalink\javalink-intelnt-staging\docs\api
mkdir %SRCBOX%\javalink\javalink-intelnt-staging\docs\guides
mkdir %SRCBOX%\javalink\javalink-intelnt-staging\kbs
mkdir %SRCBOX%\sequoia
mkdir %SRCBOX%\sequoia\sequoia-intelnt-staging 
mkdir %SRCBOX%\sequoia\sequoia-intelnt-staging\java
mkdir %SRCBOX%\sequoia\sequoia-intelnt-staging\java\bin 
mkdir %SRCBOX%\sequoia\sequoia-intelnt-staging\java\classes
mkdir %SRCBOX%\sequoia\sequoia-intelnt-staging\java\classes\jars 
mkdir %SRCBOX%\sequoia\sequoia-intelnt-staging\java\classes\activex
mkdir %SRCBOX%\sequoia\sequoia-intelnt-staging\java\docs 
mkdir %SRCBOX%\sequoia\sequoia-intelnt-staging\java\docs\api 
mkdir %SRCBOX%\sequoia\sequoia-intelnt-staging\java\docs\guides 
mkdir %SRCBOX%\sequoia\sequoia-intelnt-staging\java\kbs 
: SPARCSOL
mkdir %SRCBOX%\javalink\javalink-sparcsol-staging 
mkdir %SRCBOX%\javalink\javalink-sparcsol-staging\bin 
mkdir %SRCBOX%\javalink\javalink-sparcsol-staging\classes
mkdir %SRCBOX%\javalink\javalink-sparcsol-staging\classes\jars 
mkdir %SRCBOX%\javalink\javalink-sparcsol-staging\docs 
mkdir %SRCBOX%\javalink\javalink-sparcsol-staging\docs\api 
mkdir %SRCBOX%\javalink\javalink-sparcsol-staging\docs\guides 
mkdir %SRCBOX%\javalink\javalink-sparcsol-staging\kbs 
mkdir %SRCBOX%\sequoia\sequoia-sparcsol-staging\bin  
mkdir %SRCBOX%\sequoia\sequoia-sparcsol-staging\classes 
mkdir %SRCBOX%\sequoia\sequoia-sparcsol-staging\classes\jars  
mkdir %SRCBOX%\sequoia\sequoia-sparcsol-staging\docs
mkdir %SRCBOX%\sequoia\sequoia-sparcsol-staging\docs\api  
mkdir %SRCBOX%\sequoia\sequoia-sparcsol-staging\docs\guides  
mkdir %SRCBOX%\sequoia\sequoia-sparcsol-staging\kbs  

