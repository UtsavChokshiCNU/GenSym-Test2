****************************************
****** How to Promote a Product ********
****************************************
       -- revised 11/17/1999 

--------
Overview
--------
This document describes how to promote products for shipping and internal
use.  There are sections below that contain step-by-step instructions on
how to promote and remove products.

* Your product must have a registered name before it can be promoted.
  You can register the name through Order Services.
* You must log onto a Solaris machine under the ab account to promote or
  remove a product.
* Promote your products using the tool /gensym/tools/promote-product
    - With no arguments, promote-product shows usage and examples.
    - The tool promotes EVERYTHING in the source directory and its
      subdirectories, so be careful that the contents are correct.
    - You must promote to iship before you promote to eship.  Once you
      have promoted to eship, you should remove the iship promotion.
    - When you promote to iship, you should give a version number
      that includes an encoded year and date to indicate when the
      product was built (not promoted).  E.g., 50r3-BD08 is version
      50r3 built on April 8th, 1999. The date has form YMDD, where
           Y is B for 1999, C for 2000, ...
           M is A for January, B for February ...
           DD is always two digits.
    - When you promote to eship, you should drop the encoded date.
      Subsequent promotions of patches should retain the encoded date.
    - After promoting to eship, you should contact Order Services to
      have your product placed on media, or you should contact the
      Gensym webmaster to have your product placed in the HelpLink
      ftp area.
* Manage your disk space!
    -  Run the tool /gensym/tools/remove-product to remove a product that
       you have previously promoted.  With no arguments, it shows usage.
    -  Remove unused iship promotions ASAP.
    -  Ask Order Services to archive and remove eship promotions that are
       no longer needed. 
 
-------
Details
-------
These instructions pertain to promoting Unix and NT products.  VMS products are
promoted with a different set of tools.  (See 0193-vms-promotion.txt in the
trail or g2dev website.)  There are sections below that contain step-by-step
instructions for promoting and removing products.

product names
+++++++++++++
Before a product can be promoted or shipped, its name must be registered in
the products database.  Order Services can register your product name for
you.  Names are kept short (under 8 characters) to accommodate restrictions
on filenames on cdrom.  For example, tw is Telewindows, axl is ActiveXLink,
etc.  You should choose a name and use it consistently.  If you try to
promote an unregistered product, you'll get an error message.

When Order Services registers your product, it is registered as either
a platform-dependent or platform-independent product.  Once registered,
you must promote your product appropriately (see the section below
on platform dependent vs. platform independent products).

iship vs. eship
+++++++++++++++
i means internal, e means external.  Products are first promoted to iship,
where they can be used and tested in-house.  When they have been judged ready
for customers, they are promoted to eship, where they can be put on media or
made available through ftp.  From a unix machine, /gensym/ut is the path to
eship promotions, while /gensym/ut/dev is the path to iship promotions.

WARNING: You should never directly add or delete files found down these paths.
They are organized by complex symbolic links that mere humans should not alter.

Order Services can produce media only from eship with their standard tools.
Putting iship products on media is non-standard, requires handwork, and should
be avoided.

Versions promoted to iship should have a standard date suffix (see the
Appendix on version numbering).  This is needed because there may be many
promotions of the same version to iship.  The date suffix allows internal
users (QA, application developers, etc.) to easily distinguish the versions.

When a product has been sufficiently tested and deemed ready for customers,
promote it from iship to eship.  At this point, drop the date suffix.  For
example, g2-50r4-BK05 in iship is promoted to g2-50r4 in eship.  If
subsequent re-releases of a product version are needed, they should be
provided as patches, and the release number should retain the date suffix in
eship (e.g., if g2-50r4 is later patched, it might be promoted to
g2-50r4-CB12 in eship).

platform dependent vs. platform independent
+++++++++++++++++++++++++++++++++++++++++++
The tools allow you to promote both platform-dependent and platform-
independent products.  You choose whether the product is platform-
independent (e.g., kbs that can be loaded on any platform) or platform-
dependent (e.g., a set of executables that run only on the Intel NT platform).

When you promote a platform-dependent product, it is found down the
/gensym/ut path only on the platform for which it was promoted.  When
you promote a platform-independent product, it is found down the
/gensym/ut path on all platforms.

special symbolic links
++++++++++++++++++++++
When you promote a product to iship (/gensym/ut/dev...), a special
symbolic link, called <product>-latest, is created to point to the most
recent product promotion.  For example, when g2-51r4-BK05 is promoted
the g2-latest link also points to the same location.  This is a convenience.

One common point of confusion is that the <product>-latest link does not
necessarily point to the latest version; it merely points to the most recent
promotion.  For example, if g2-60b0-BK01 was promoted last week and
g2-51r4-BK05 was promoted this week, g2-latest points to g2-51r4-BK05, even
though g2-60b0-BK01 is a later version of the product.  In general, one
should not rely on the <product>-latest link.

++ eship <product>-test and <product>-shipping links ++
There are two special links that you can set in the eship directory.  You can
set the <product>-shipping link to point to the shipping version of your
product, and you can set the <product>-test link to point to the version that
you'd like in-house users to test with.  To set these links, use the program
   /gensym/tools/set-ut-links
See the comments in the file for more information.

In general, the /gensym/ut and /gensym/ut/dev directories are merely
containers of complex symbolic links.  You should never try to alter these
directly.

product production
++++++++++++++++++
Product production refers to "producing" media to make products available
to customers.  It also refers to making products available through ftp.

Media is produced by Order Services.  For products to be put on media,
they must first be promoted to eship.  When you would like a product
to be put on media and shipped, give Order Services the relevant information
about which version, platform, and medium is required, and they'll take
care of the details.

If you wish to make a product available through HelpLink ftp, you must
also first promote to eship.  Inform the Gensym Webmaster about which
product, version, and platforms are needed, and he or she will take
care of the details.

disk-space management
+++++++++++++++++++++
There is no automatic cleanup of obsolete promotions.  Like a rowboat
in the rain, if it is not bailed out it will eventually fill up.

++ iship ++
You are responsible for removing your own iship promotions.  Typically there
is no need to keep more than one recent version around.  Use
/gensym/tools/remove-product to remove an iship promotion.  See the section
below that has step-by-step instructions on how to remove a product
promotion.

++ eship ++
Products are promoted to eship are generally shipped to customers.  For this
reason, it is important that we always have an available copy.  When a
product promotion in eship is no longer needed, you should inform Order
Services.  They will make a tape or cd archive of the product and then remove
it.  If you later need it, they will restore it for you.

the obsolete promotion system
+++++++++++++++++++++++++++++
Before the promote-product script was introduced, there were separate scripts
for independent and dependent promotion called promote-package and
promote-dependent-package.  These were more complex to use because they
required you to create an inventory file before promoting.  Also, they stored
files in an easily corrupted form.  promote-product and remove-product are
now the standard way of handling product promotions.


---------------------------------------------------
Promoting a Product to iship (for Internal Release)
  - Step by Step Instructions
---------------------------------------------------
++++
Note: In the following, % is the Unix prompt character.  Do not type it.
++++

1. Prepare your files in a directory that is accessible though the automounter.
   (/vmsdisc can only be used only if there are no subdirectories).

2. Double check that the files in the directory and subdirectories are exactly
   what the customer should receive; i.e., no garbage and no omissions.  What
   you see is what they get.

3. Determine the iship id (version and build date) for your product.  You'll
   need this for promoting.  For example, if you're promoting version
   5.1 Rev 3 built on May 8, 1999, the id is 51r3-BE08.  See the Appendix
   below on version numbers and dates.

4. Log into the machine "franklin" as the user "ab" (ask the Order Services
   manager for password).

5. Change directories to the directory where promotion tools are stored.

     % cd /gensym/tools

6.  If you forget how to use the promote-product script, type it
    without arguments for help and examples. I.e., type
        % promote-product

 a. For a machine-independent product, use a command like the following:
        % promote-product -i gda /home/gdadev/current 21r0-BD17
    and replace
      -- "gda" with your registered product name
      -- "/home/gdadev/current" with the full path to the directory
         whose contents you wish to promote
      -- "21r0-BD17" with the iship id for your promotion

 b. For a machine-dependent product, use a command line like the following:
        % promote-product -i setcim rs6000 /home/paf/setcim/dist 20r3-BG09
    and replace
      -- "setcim" with your registered product name
      -- "rs6000" with the target platform for your product's executables
      -- "/home/paf/setcim/dist" with the full path to the directory
         whose contents you wish to promote
      -- "20r3-BG09" with the iship id for your promotion

7. Examine the output of your promote-product script.  There should be a number
   of messages beginning with "LOG:" which tell you about the steps that
   promote-product went through.  Verify that none of them start with "ERROR:".
   Also, promote-product will attempt to determine that the source of the
   promotion and the destination are identical, so verify that the "diff"
   command did not produce any unwanted output (which would indicate differences
   between the source and destination, which would in turn indicate a problem
   with the computer or network.)  If there are problems, take appropriate
   action to repair either your promote-product command, or get help repairing
   the computers.

You're done!

---------------------------------------------------
Promoting a Product to eship (for External Release)
  - Step by Step Instructions
---------------------------------------------------
++++
Note: In the following, % is the Unix prompt character.  Do not type it.
++++

1. Determine the iship id of your promoted product. (Remember that
   a product must be promoted to iship before it can be promoted to eship).
   E.g., the iship id might be 21r0-BD17.

2. Use the iship id to determine the eship id.  For the first release
   simply drop the date suffix.  For a patch release, the eship id is
   the same as the iship id.  For example, for a new release, if the
   iship id is 21r0-BD17, then the eship id is 21r0

3. Log into the machine "franklin" as the user "ab" (ask the Order Services
   manager for password).

4. Change directories to the directory where promotion tools are stored.

      % cd /gensym/tools

5.  If you forget how to use the promote-product script, type it
    without arguments for help and examples. I.e., type
        % promote-product

 a. For a machine-independent product, use a command like the following:
        % promote-product -e gda 21r0-BD17 21r0
    and replace
      -- "gda" with your registered product name
      -- "21r0-BD17" with the iship id that you're promoting
      -- "21r0" with the eship id to be used.

 b. For a machine-dependent product, use a command line like the following:
        % promote-product -e setcim rs6000 20r3-BG09 20r3
    and replace
      -- "setcim" with your registered product name
      -- "rs6000" with the target platform that you're promoting
      -- "20r3-BG09" with the iship id that you're promoting
      -- "20r3" with the eship id to be used.

6. Remove the iship promotion, assuming that no one is currently using it.
    (See the next section on Removing Promoted Products).

7. See warning above in iship promotions about examining the output of the
   promote-product script.

You're done!  Go to your release party!

---------------------------------------------------
Removing Promoted Products
  - Step by Step Instructions
---------------------------------------------------
++++
Note: In the following, % is the Unix prompt character.  Do not type it.
++++

+++ iship versions:  It is your responsibility to remove these.  If you
  don't, they will occupy disk space that other products need.  Follow the
  steps below to remove your product promotions. 

+++ eship versions:  Do not remove these yourself.  Ask Order Services to
  remove them.  They will first create an archive version that you can
  later have restored.

1. Log into the machine "franklin" as the user "ab" (ask the Order Services
   manager for password).

2. Change directories to the directory where utilities for tape making (and
   other stuff) are stored.

        % cd /gensym/tools

3. If you forget how to use the remove-product script, type it without
   arguments for help and examples.  I.e., type
        % remove-product

 a. To remove a machine-independent product, use a command like the following:
        % remove-product -i gda 21r0-BD17
    and replace
      -- "gda" with your registered product name
      -- "21r0-BD17" with the id of the product that you're removing.
    Note that -i indicates iship.

 b. To remove a machine-dependent product for ALL platforms, use a command
    like the following:
        % remove-product -i setcim 20r3-BG09
    and replace
      -- "setcim" with your registered product name
      -- "21r0-BD17" with the id of the product that you're removing.
    Be careful, because this removes it for ALL platforms.  If you want
    to remove it for only specific platforms, see c.

 c. To remove a machine-dependent product for specific platforms, use a
    command like the following:
        % remove-product -i setcim 20r3-BG09 intelnt rs6000
    and replace
      -- "setcim" with your registered product name
      -- "21r0-BD17" with the id of the product that you're removing
      -- "intelnt rs6000" with a list of one or more platforms.
    Note that -i indicates iship.

The product has now been deleted.

-------------------------------------
Appendix - Version and Date Numbering
-------------------------------------

Gensym has chosen a standard release and revision number format for all its
products.  This format is required by the tape making software, gives Gensym 
a consistent face to customers, and makes life easier for nearly everyone.

The release number shown in your product and supporting documentation should
have the following format.

  <major-#>.<minor-#> Alpha Rev.|Beta Rev.|Rev. <revision-number>

For promoting, the promoted name uses consistent abbreviation, as follows.

  <major-#><minor-#><the letter a, b, or r><revision-number>[-<date>]

+++ major-#: The major release number for a product starts at 1 and is
incremented when major new functionality is added or the product is
drastically changed.

+++ minor-#: The minor number starts at 0 (zero) and is incremented for a
release with significant new functionality that does not qualify as
a major release.

+++ revision-number:  This starts at 0 (zero) and is incremented for each
general release to customers.  It is reset to 0 each time the release
type advances, from alpha to beta to final (see next section).  New
revisions typically contain bug fixes or minor additions to functionality.
Revision numbers may increase beyond 9 (e.g., 50r10 comes after 50r9),
but revision numbers beyond 9 are discouraged.  Revision-numbers are not
changed for patches released to specific customers; instead, patch
releases are differentiated by a date suffix.

+++ release type: (Alpha Rev., Beta Rev., or final Rev.).  These
are abbreviated by a, b, and r in the promotion name. A product is
designated as Alpha before functionality is complete and the reliability
is unproved.  A product progresses to Beta when it contains all features
planned for a release, has passed a QA cycle, and is being given to users
for outside testing in anticipation of the final release.  When the decision
is made to move into the final release of the product, then Alpha or Beta
designations are dropped. Revision numbers restart at 0 after each
change in release type.

+++ date suffix:  A date is suffixed to the version when either
(i) the product is promoted to iship or (ii) a patch version is promoted
from iship to eship.  The date should designate when the build date,
not the promotion date (which can always be obtained as the directory
creation date).  The date has form YMDD, where
    Y is B for 1999, C for 2000, D for 2001 ...
    M is A for January, B for February
       (A Jan, B Feb, C March, D Apr, E May, F June
        G July, H Aug, I Sept, J Oct, K Nov, L Dec)
    DD is always two digits.
It is very useful to put this same date format into your software so
that internal and external users can determine which build they are
using.  The date is encoded so that customers won't worry needlessly
if they don't have the latest build.

Examples of version numbers
+++++++++++++++++++++++++++

The following are examples of release numbers and their abbreviations.  These
numbers appear in ascending order for a product.

In iship:
  Version 2.1 Beta Rev. 0     21b0-BC06  (built March 6, 1999)
  Version 3.0 Rev. 4          30r4-CF21  (built June 21, 2000)

In eship:
  Version 1.0 Alpha Rev. 2    10a2
  Version 2.1 Beta Rev. 0     21b0
  Version 2.1 Rev. 11         21r11
  Version 3.0 Beta Rev. 1     30b1
  Version 3.0 Rev. 4          30r4

