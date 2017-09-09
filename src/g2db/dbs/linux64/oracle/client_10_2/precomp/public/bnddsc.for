C     
C**   BNDDSC : Bind Var Descriptor.
C
C     BNDN         Nr of elements in Descriptor arrays (e.g., 20 in
C                  following examples). BNDN determines the maximum
C                  nr of Column-Names that can be DESCRIBE'd.
C
C     BNDF         Nr of Bind Variables found by Oracle during
C                  DESCRIBE BIND VARIABLES FOR BND. On return from the
C                  DESCRIBE, if BNDF is .LT. 0, then there were too
C                  many Bind-Vars (i.e., in these examples, if a
C                  DESCRIBE BIND VARIABLES were performed for a SQL stmt
C                  with .GT. 20 Bind-Vars, then the PCC would return
C                  BNDF equal to minus the actual nr of Bind-Vars.
C                  This option is used in languages like C or Pascal to
C                  allow the user to dynamically re-allocate a larger
C                  area to receive the Bind Variable info.
C
C     BNDS(20)     Arr of ptrs to Bind Variable Names. BNDS(i)
C                  is a ptr to a user-allocated buffer. See BNDSB(),
C                  below. Must be initialized by the pgmr. Although
C                  Fortran does not support the notion of "pointers",
C                  the utility subroutine, SQLADR(), can be used to
C                  initialize BNDS().
C
C     BNDSB(30,20) Bind Variable Name Buffer. Contains the name of each
C                  Bind Var in the SQL stmt.
C
C                  On a DESCRIBE BIND VARIABLE call, the PCC will stuff
C                  the name of each Bind Var into the buffer indicated
C                  by BNDS(). See above. In these examples, we assume
C                  that the pgmr has initialized each BNDS() entry via:
C
C                      CALL SQLADR ( BNDSB(1,I), BNDS(I) )
C
C                  This will store the addr of the Bind Var Name Buffer
C                  (for each Bind Var) in its corresponding BNDS()
C                  entry.
C
C                  For example, given:
C
C                    SELECT TNAME,TABTYPE
C                      FROM TAB
C                      WHERE TNAME = :TN AND TABTYPE = :TT
C
C                  (an admittedly nonsense SQL stmt, but ok for my
C                  purpose). After the DESCRIBE BIND (assuming BNDS has
C                  been properly initialized), BNDSB(1:2,1) would contain
C                  the string 'TN'; and BNDSB(1:2,2) would contain the
C                  string 'TT'.
C
C     BNDM(20)     Arr of max lengths of BNDS(20) Name-Buffer (i.e.,
C                  30. See BNDSB(30,20), above). Note that each Name-
C                  Buffer entry can have a different length. This option
C                  is really designed for languages like C or Pascal
C                  where storage can be dynamically allocated.
C
C     BNDC(20)     Current lengths of Name-Buffers. I.e., this array
C                  contains the length of each Bind Var Name returned
C                  in BNDS(20)/BNDSB(30,20). For example, using the
C                  above example, BNDC(1) would be 2 (length of string
C                  'TN'); and BNDC(2) would be 2 (length of string
C                  'TT').
C
C     BNDV(20)     Arr of ptrs to Bind Var Values. This arr is used
C                  during OPEN..USING DESCRIPTOR processing.
C                  The user pgm should initialize this array to con-
C                  tain addrs to Bind Var Value Buffer area. See BNDVB,
C                  below. On a OPEN..USING, the PCC will execute the
C                  SQL stmt using the Bind Var Values specified via
C                  BNDV/BNDVB.
C
C     BNDVB(80,20) Bind Var Value Buffer. Used during OPEN..USING
C                  processing. The pgmr (i.e., you) should set appro-
C                  priate values for each Bind Variable by storing
C                  the appropriate value in the appropriate BNDVB
C                  entry for this Bind Variable.
C
C                  In these examples, we assume the pgmr has initial-
C                  ized BNDV() via:
C
C                      CALL SQLADR ( BNDVB(1,I), BNDV(I) )
C
C                  For example, given that we have the following SQL
C                  stmt:
C
C                      SELECT *
C                        FROM TAB
C                        WHERE TNAME = :TN AND TABTYPE = :TT
C
C                  after the DESCRIBE BIND VARIABLES stmt, and before
C                  the OPEN..USING stmt, you should store the values
C                  you wish :TN and :TT to have in BNDVB(1:80,1) and
C                  BNDVB(1:80,2), respectively (you also must store
C                  the appropriate lengths of these strings in BNDL.
C                  See below).
C
C                  For example, if you store 'EMP' into BNDVB(1:3,1),
C                  and 'TABLE' into BNDVB(1:5,2); then upon executing
C                  the OPEN..USING, the query:
C
C                      SELECT *
C                        FROM TAB
C                        WHERE TNAME = 'EMP' AND TABTYPE = 'TABLE'
C
C                  will be executed.
C
C     BNDL(20)     Arr of lengths of Bind Var Value buffers. The
C                  pgmr specifies the size of each BNDV(I)/BNDVB(1:80,I)
C                  entry via BNDL(I). For example, if you want a Bind
C                  Var value to be 3 chars wide (as for, :TN = 'EMP',
C                  in our example), set BNDL(I) entry to 3. Note that,
C                  although each BNDVB entry can contain a max of 80
C                  chars, the corresponding BNDL entry will determine
C                  the actual length honored by Oracle. Note also
C                  that each returned Bind Var Value in BNDVB can
C                  have a different length. This feature is intended
C                  primarily for languages like C or Pascal where
C                  storage can be allocated dynamically.
C
C     BNDT(20)     Data Type of Bind Variable. Pgmr should set this
C                  array to the desired datatype for each Bind Var.
C                  Some Oracle datatypes are:
C
C                    01  =  Varying length char string. Nr of chars
C                           is determined by BNDL.
C                    03  =  Binary Integer. Byte-width is determined
C                           by BNDL.
C                    04  =  Binary Floating Pt. Byte-width is deter-
C                           mined by BNDL.
C
C                  See Chap 5, DATA TYPE DEFINITIONS in the HLI Ref
C                  Manual for more details. If the pgmr coerces the
C                  datatype of Bind V Var by storing an appropriate
C                  value in the BNDT entry for the Bind Var, then
C                  Oracle will perform the necessary conversion at
C                  OPEN..USING.
C
C     BNDI(20)     Arr of ptrs to Indicator Variables for BNDV/BNDVB
C                  See BNDIV(20), below.
C
C     BNDIV(20)    Array of Indicator Variables for BNDV/BNDVB. On an
C                  OPEN..USING, the value of BNDIV entries will deter-
C                  mine whether or not this Bind Var is NULL. Set
C                  BNDIV(I) to -1 to indicate that the I'th Bind Var's
C                  value is NULL; else .GE. 0 to indicate that BNDVB
C                  contains a value-to-be-used.
C
C                  We assume that BNDI(I) has been initialized via:
C
C                      CALL SQLADR ( BNDIV(I), BNDI(I) )
C
C                  Note that this is intended for languages that sup-
C                  port pointer vars and dynamic memory.
C
C     BNDX(20)     Ptr to Indicator Var Name Buffer. See BNDXB, below.
C
C     BNDXB(30,20) Indicator Var Name Buffer. After a DESCRIBE BIND
C                  VARIABLES, BNDXB will contain the names of all
C                  Indicator Variables specified in the SQL stmt. For
C                  example, given:
C
C                      SELECT *
C                        FROM EMP
C                        WHERE MGR = :MGRVAR:MGRIND
C
C                  BNDXB(1:6,1) would contain 'MGRIND', the name of
C                  the 1st (and only) Indicator Variable.
C
C     BNDY(20)     Max len of Indicator Variable Name Buffer. Set by
C                  the pgmr to tell Oracle the size of the BNDXB
C                  buffer to receive an Indicator Var Name. In our
C                  examples, this is equal to 30 (See BNDXB(30,20),
C                  above). Note that each Indicator Variable can have
C                  it's own length. This is intended for languages
C                  like C which support dynamic memory allocation.
C
C     BNDZ(20)     Cur len of Indicator Variable Name Buffer. After
C                  a DESCRIBE, will contain the nr of chars in each
C                  Indicator Var Name. Using our above example for
C                  BNDXB(1:6,1) = 'MGRIND', BNDZ(1) would be 6.
C
C
C     Notes:
C
C       -- See also SELDSC.FOR to compare Select List Descriptor.
C
C       -- The name of a Descriptor is specified on the appropriate
C          SQL stmt (for example, DESCRIBE BIND VARIABLES INTO BND --
C          'BND' is the name of the Descriptor).
C
C          The PCC will reference the various arrays that comprise
C          this Descriptor by appending the appropriate N, F, S, M,
C          C, L, etc., suffix char (e.g., BNDN, BNDF, BNDS(), BNDM(),
C          and so on). Therefore, on Fortrans that only support 6 char
C          variable names, a Descriptor name can be .LE. 5 chars in
C          length.
C
C       -- There is nothing magic about the names or lens of the
C          BNDSB(), BNDVB(), BNDXB(), and BNDIV() arrays. Oracle
C          "finds" these buffers via the corresponding BNDS(), BNDV(),
C          etc., arrays; and their lengths are specified via the
C          BNDM(), BNDL(), etc., arrays. I have chosen the above
C          names and lengths arbitrarily. In fact, you could even
C          have a C or Pascal or Assembler routine do dynamic alloca-
C          tion for you, if you wish; thus passing the address of the
C          dynamically allocated memory back to the appropriate
C          BNDS(), BNDV(), etc., array.
C
C       -- If you are setting up your own Descriptor (i.e., not using
C          this one), you should be careful to use the correct Fortran
C          types for the various Descriptor arrays. Oracle expects
C          these arrays to have the physical structure dictated below.
C
C          For example, the BNDS() and BNDV() arrays will contain an
C          addr. Therefore, they must be declared to be the size of an
C          addr on the machine you intend to run on (i.e., INTEGER *4
C          on the VAX).
C
C       -- The utility subroutine, SQLADR, can be used to determine
C          the addr of a Fortran data item. For example:
C
C              CALL SQLADR ( VAR, ADDR )
C
C          will store the addr of VAR into ADDR. Typically, this is
C          used to initialize the BNDS(), BNDV(), etc., arrays.
C

      INTEGER      BNDN
      INTEGER      BNDF
      INTEGER *4   BNDS(20)
      INTEGER *2   BNDM(20)
      INTEGER *2   BNDC(20)
      INTEGER *4   BNDL(20)
      INTEGER *2   BNDT(20)
      INTEGER *4   BNDV(20)
      INTEGER *4   BNDI(20)
      INTEGER *4   BNDX(20)
      INTEGER *2   BNDY(20)
      INTEGER *2   BNDZ(20)
 
      LOGICAL *1   BNDSB(30,20)
      LOGICAL *1   BNDVB(80,20)
      LOGICAL *1   BNDXB(30,20)

      INTEGER *2   BNDIV(20)

      COMMON /BNDDSC/ BNDN, BNDF,
     1                BNDS, BNDM, BNDC, BNDL, BNDT, BNDV,
     2                BNDI, BNDX, BNDY, BNDZ,
     3                BNDSB, BNDVB, BNDXB, BNDIV
