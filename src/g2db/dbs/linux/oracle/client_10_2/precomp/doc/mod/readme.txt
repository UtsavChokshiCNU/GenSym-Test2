/ 
/ $Header: readme.txt 09-dec-2003.11:34:11 subanerj Exp $ 
/ 
/ Copyright (c) 1994, 1998, 2001, 2002 by Oracle Corporation 
/   NAME
/     readme.txt - SQL*Module general customer information
/
/   DESCRIPTION
/   RETURNS
/   NOTES
/
/   MODIFIED   (MM/DD/YY)
/    subanerj   12/09/03  - update for 10g production 
/    akatti     04/10/03  - changed 9.2.0.0.0 to 10.1.0.1
/    subanerj   01/10/02  - changed 9.0.2.0.0 to 9.2.0.0.0.
/    akatti     07/25/01 -  [1902349]:update for 9.0 release
/    akatti     11/18/98 -  update for 8.1.5 release
/    cracicot   10/10/94 -  add info about new demos
/    cracicot   09/14/94 -  update to 1.1 beta
/    cracicot   03/17/94 -  new version for production
/    cracicot   11/21/93 -  add a few comments
/    cracicot   11/17/93 -  add developers comments for beta release
/    tssmith    11/12/93 -  Add info on running demo programs
/    cracicot   11/11/93 -  Creation


       README FILE FOR PRODUCT: SQL*MODULE 10.1.0.2.0 RELEASE
       =====================================================

       SECTION 1:  WARNING!!!  SPECIAL SITUATION(S) REQUIRING
       IMMEDIATE NOTICE
       ------------------------------------------------------

       1.  store_package=yes

           If you tell SQL*Module to store a package in the
           database, it uses "create or replace", thus any
           package of the same name, already in the database,
           will be overwritten, without warning!



       SECTION 2: VERSION REQUIREMENTS AND DEPENDENCIES
       -------------------------------------------------

       This product requires the following products:

          RDBMS  10.1.0.2.0
          SQLLIB 10.1.0.2.0



       SECTION 3: INFORMATION WHICH DIDN'T MAKE IT INTO THE
       DOCUMENTATION
       ----------------------------------------------------

       We believe the manual "SQL*Module User's Guide and
       Reference" [part #A58231-01] is up to date.

       Please log a bug if you find any inconsistencies
       between actual and documented behavior



       SECTION 4: HOW TO RUN THE DEMOS FOR THIS PRODUCT
       -------------------------------------------------

       Sample Programs
       ===============

       There are three demonstration programs for the supported
       host language (Ada) : DEMOHOST, DEMCALSP and CH1_DRV.

       DEMOHOST
       --------

       The first sample program calls module procedures that
       are defined in the module file DEMOMOD. The exact
       names of these files in the generic distribution are:

       demohost.a -- calls module procedures in demomod.mad

       These names might change from port to port. For
       example, the ADA driver program for DEMOMOD might
       be called demohost.ada, rather than demohost.a.

       Before compiling and running the sample programs, you must
       set up a schema in your Oracle 10.1.0.1.0 database to contain the
       tables that the programs access. There are six SQL scripts
       in your demo directory to set up the schema:

       mktables.sql
       courses.sql
       departmt.sql
       enrolmnt.sql
       instrucs.sql
       students.sql

       Run the MKTABLES script using SQLPLUS.
       MKTABLES calls the other five scripts.

       The sample programs were tested using a schema called
       MODTEST, identified by YES. The schema was created using
       SQLPLUS by doing:

       SQLPLUS> connect system/whatever
       SQLPLUS> grant connect to modtest identified by yes;
       SQLPLUS> grant dba to modtest;

       (The DBA role is not required to run the programs.
       It was used for simplicity in this example.)

       Refer to Chapter 6 of the "SQL*Module User's and Reference
       Guide" for more information about the test programs and
       the test database.

       If you load these tables under a different schema,
       you must change the connecting username and password
       in the call to the "do_connect" procedure in the sample programs.

       (For simplicity, the schema password is hard-coded into the
       source code for the sample programs. Oracle does not
       recommend this as good coding practice.)

       Compile and link the sample programs using the commands
       specific to your operating system and compiler(s) and
       linker. 

       $ modada iname=demomod oname=demomod user=modtest
       $ ada demomods.a
       $ ada demomod.a
       $ ada demohost.a
       $ make ada EXE=demohost
       $ demohost

       In this version of SQL*Module, not all of the functionality
       promised by the college database menu is provided for all
       languages. You might enjoy implementing it yourself, to
       practice using SQL*Module.

       DEMCALSP
       --------

       The second sample program, DEMCALSP, calls a stored
       procedure in the database to compute the grade point average
       for a selected student ID.  (Only students 1000 and 1007
       have actually taken any courses. You can modify the
       ENROLLMENT table to add more, if you'd like.)

       Before calling SQL*Module to create interface procedures
       to call the stored procedure, run the GPAPKG.SQL script
       (using SQLPLUS) to store the PL/SQL procedure in the schema.
       For example:

       SQLPLUS> connect modtest/yes
       SQLPLUS> @gpapkg

       Then compile the DEMCALSP program, using your favorite host
       language compiler. Run SQL*Module to create the interface
       procedures.  An Ada example is shown below.

       $ modada pname=gpa_pkg user=modtest rpc_generate=yes
         oname=gpa_pkg

       Compile the generated file, and link as described for
       DEMOHOST above. (With VAX/OpenVMS Ada, you must compile
       first the generated specification file, GPA_PKG.ORA_DCL,
       then the generated Ada body GPA_PKG.ADA.  You must also
       make sure to compile "logon.ada" into your ACS library.)



       SECTION 5: NOTES
       -----------------

       There are some known minor deficiencies in this release:

       1. PL/SQL does not currently truncate strings when they
          are assigned into host variables which are too small
          to hold them.  Thus, the ANSI SQL behavior provided
          when not calling stored procedures cannot as yet be
          duplicated when in RPC mode.

          Instead, an exception is raised.  There are a few
          other minor discrepancies between PL/SQL behavior and
          embedded SQL standards.  For example, error numbers
          will differ in some cases.

       2. In order for cursors to be closed on commit and rollback,
          as is required by ANSI, the RDBMS initialization parameter
          "serializable" must be set to TRUE.

       3. Cursor variables should not be used when binding=early.

       4. In the SQL*Module programmer's guide document, the
          example code under "Indicator parameters" section in
          chapter 2, should refer to table enrollment instead
          of classes.

       5. In the SQL*Module programmer's guide document, the
          example procedure under PL/SQL section of chapter 3,
          enrollment.idno should be read as enrollment.student_id.



       SECTION 6: OPEN PRIORITY 2 and PRIORITY 3 BUGS
       -----------------------------------------------

       Bug #  Problem Description
       ------ -----------------------------------------------------
       632176 ADA CODE GENERATED SHOULD NOTE LENGTH OF STRING PARAMETERS
       625104 UNABLE TO USE A PLACEHOLDER IN A CURSOR DECLARATION.
       340126 FOR CONNECT STATMENTS, THE LINE NUMBER OF THE STATEMENT IN
              NOT PASSED IN CUD

