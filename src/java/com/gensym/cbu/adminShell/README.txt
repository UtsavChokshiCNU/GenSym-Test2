How to launch a Denali client (specifically OpEx) from a browser.
=================================================================

1. Start rmiregistry in a Command Shell.  
   > rmiregistry

2. Bring up Denali server (in another Command Shell).
   > runelectronics  (or equivalent)

3. Bring up a fresh browser.  I use Netscape.  (Craig wonders if it
   will actually work in Internet Explorer.)  

   A.  This is assuming that you have a Plug-in installed that is at
       least version 1.2.
   B.  If you are building your own HTML (rather than using the
       ShellLauncher.html that I provide in this directory) you will
       need to run it through the HTML Converter program, which comes
       with the plug-in.

4. Load the "ShellLauncher.html".  This should work (hopefully).


How to launch a browser that has embedded Denali elements in it.
================================================================

1. Do all of the stuff for the guy above.

2. Load the "ShelletteLauncher.html". 
   You will see two different applets extracting values from the same
   server.  Oooooo.