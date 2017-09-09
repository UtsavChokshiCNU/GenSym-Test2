C     
C     
C**   SELDSC : Select List Descriptor.
C
C     SELN         Nr of elements in Descriptor arrays (e.g., 20 in
C                  following examples). SELN determines the maximum
C                  nr of Column-Names that can be DESCRIBE'd.
C
C     SELF         Nr of select list items found by Oracle during
C                  DESCRIBE SELECT LIST FOR SEL. On return from the
C                  DESCRIBE, if SELF is .LT. 0, then there were too
C                  many Column-Names (i.e., in these examples, if a
C                  DESCRIBE SELECT LIST were performed for a SQL stmt
C                  with .GT. 20 Column-Names, then the PCC would return
C                  SELF equal to minus the actual nr of Column-Names.
C                  This option is used in languages like C or Pascal to
C                  allow the user to dynamically re-allocate a larger
C                  area to receive the Select List.
C
C     SELS(20)     Arr of ptrs to Select List column names. SELS(i)
C                  is a ptr to a user-allocated buffer. See SELSB(),
C                  below. Must be initialized by the pgmr. Although
C                  Fortran does not support the notion of "pointers",
C                  the utility subroutine, SQLADR(), can be used to
C                  initialize SELS().
C
C     SELSB(30,20) Select List Name Buffer. Contains the name of each
C                  column in the Select List.
C
C                  On a DESCRIBE SELECT LIST call, the PCC will stuff
C                  the name of each column into the buffer indicated
C                  by SELS(). See above. In these examples, we assume
C                  that the pgmr has initialized each SELS() entry via:
C
C                      CALL SQLADR ( SELSB(1,I), SELS(I) )
C
C                  This will store the addr of the Select List Buffer
C                  (for each Select List item) in its corresponding
C                  SELS() entry.
C
C                  For example, given:
C
C                    SELECT TNAME,TABTYPE FROM TAB
C
C                  after the DESCRIBE SELECT LIST, SELS(B(1:5,1) would
C                  contain the string 'TNAME'. SELSB(1:7,2) would con-
C                  tain the string 'TABTYPE'.
C
C     SELM(20)     Arr of max lengths of SELS(20) Name-Buffer (i.e.,
C                  30. See SELSB(30,20), above). Note that each Name-
C                  Buffer entry can have a different length. This option
C                  is really designed for languages like C or Pascal
C                  where storage can be dynamically allocated.
C
C     SELC(20)     Current lengths of Name-Buffers. I.e., this array
C                  contains the length of each column-name returned
C                  in SELS(20)/SELSB(30,20). For example, using the
C                  above example, SELC(1) would be 5 (length of string
C                  'TNAME'); and SELC(2) would be 7 (length of string
C                  'TABTYPE').
C
C     SELV(20)     Arr of ptrs to Column-Values. This arr is used
C                  during FETCH..USING DESCRIPTOR processing.
C                  The user pgm should initialize this array to con-
C                  tain addrs to Column-Value Buffer area. See SELVB,
C                  below. On a FETCH..USING, the PCC will stuff the
C                  Fetch'd cols into the buffer area indicated by SELV.
C
C     SELVB(80,20) Select List Value Buffer. After a FETCH..USING,
C                  contains the value of each column in the fetch'd
C                  row.
C
C                  In these examples, we assume the pgmr has initial-
C                  ized SELV() via:
C
C                      CALL SQLADR ( SELVB(1,I), SELV(I) )
C
C                  For example, given that we have a row in Table TAB:
C
C                      TNAME                          TABTYPE
C                      ------------------------------ -------
C                      MYTABLE                        TABLE
C
C                  Then after the FETCH..USING, SELVB(1:30,1) will
C                  contain 'MYTABLE' (Blank padded on the right out to
C                  width of this column, which is specified via SELL(1).
C                  See below.). Likewise, SELVB(1:30,2) will contain
C                  'TABLE' (again blank padded out to SELL(2)). Note
C                  also, for this example, SELN and SELF will be 2 to
C                  indicate that there are 2 Select List items.
C
C     SELL(20)     Arr of lengths of Select List Value buffers. The
C                  pgmr specifies the size of each SELV(I)/SELVB(1:80,I)
C                  entry via SELL(I). For example, if you want a Select
C                  List value to be padded out to a col-width of 40
C                  chars, set that SELL(I) entry to 40. Note that,
C                  although each SELVB entry can contain a max of 80
C                  chars, the corresponding SELL entry will determine
C                  the actual length honored by Oracle. Note also
C                  that each returned Select List Value in SELVB can
C                  have a different length. This feature is intended
C                  primarily for languages like C or Pascal where
C                  storage can be allocated dynamically.
C
C     SELT(20)     Data Type of Select List item. On return from
C                  DESCRIBE SELECT LIST, SELT(I) will contain the
C                  datatype of Col I. Datatypes returned are:
C
C                    01  =  Varying length char string.
C                    02  =  Internal numeric.
C
C                  Typically, a user will coerce a datatype to a
C                  known (and therefore more useful) type before
C                  issuing the FETCH..USING. Some useful datatypes
C                  are (in addition to the above):
C
C                    03  =  Binary Integer. Byte-width is determined
C                           by SELL.
C                    04  =  Binary Floating Pt. Byte-width is deter-
C                           mined by SELL.
C
C                  See Chap 5, DATA TYPE DEFINITIONS in the HLI Ref
C                  Manual for more details. If the pgmr coerces the
C                  datatype of a Column by storing an appropriate
C                  value in the SELT entry for the column, then Oracle
C                  will perform the necessary conversion at Fetch-
C                  time. If you choose to coerce the datatype of some
C                  Column Value, SELV/SELVB, then be careful to do so
C                  AFTER the DESCRIBE (which will store what Oracle
C                  thinks the datatype of this column is in SELT) and
C                  BEFORE the FETCH (which is when Oracle needs the
C                  info).
C
C     SELI(20)     Arr of ptrs to Indicator Variables for SELV/SELVB
C                  See SELIV(20), below.
C
C     SELIV(20)    Array of Indicator Variables for SELV/SELVB. On a
C                  FETCH..USING, SELIV entries will be set to .LT. 0
C                  if the Fetch'd Column-Value is NULL. Else SELIV
C                  entry will be .GE. 0.
C
C                  We assume that SELI(I) has been initialized via:
C
C                      CALL SQLADR ( SELIV(I), SELI(I) )
C
C                  Note that this is intended for languages that sup-
C                  port pointer vars and dynamic memory.
C
C
C     Notes:
C
C       -- See also BNDDSC.FOR to compare Bind Variables Descriptor.
C
C       -- The name of a Descriptor is specified on the appropriate
C          SQL stmt (for example, DESCRIBE SELECT LIST INTO SEL --
C          'SEL' is the name of the Descriptor).
C
C          The PCC will reference the various arrays that comprise
C          this Descriptor by appending the appropriate N, F, S, M,
C          C, L, etc., suffix char (e.g., SELN, SELF, SELS(), SELM(),
C          and so on). Therefore, on Fortrans that only support 6 char
C          variable names, a Descriptor name can be .LE. 5 chars in
C          length.
C
C       -- There is nothing magic about the names or lens of the
C          SELSB(), SELVB(), and SELIV() arrays. Oracle "finds"
C          these buffers via the corresponding SELS(), SELV(),
C          etc., arrays; and their lengths are specified via the
C          SELM(), SELL(), etc., arrays. I have chosen the above
C          names and lengths arbitrarily. In fact, you could even
C          have a C or Pascal or Assembler routine do dynamic alloca-
C          tion for you, if you wish; thus passing the address of the
C          dynamically allocated memory back to the appropriate
C          SELS(), SELV(), etc., array.
C
C       -- If you are setting up your own Descriptor (i.e., not using
C          this one), you should be careful to use the correct Fortran
C          types for the various Descriptor arrays. Oracle expects
C          these arrays to have the physical structure dictated below.
C
C          For example, the SELS() and SELV() arrays will contain an
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
C          used to initialize the SELS(), SELV(), etc., arrays.
C
C MODIFIED
C     gturk      06/21/95 -  Creation
C   Clare      03/05/86 - Use new DESCRIBE.
C

      INTEGER      SELN
      INTEGER      SELF
      INTEGER *4   SELS(20)
      INTEGER *2   SELM(20)
      INTEGER *2   SELC(20)
      INTEGER *4   SELL(20)
      INTEGER *2   SELT(20)
      INTEGER *2   SELT2(20)
      INTEGER *4   SELV(20)
      INTEGER *4   SELI(20)
 
      LOGICAL *1   SELSB(30,20)
      LOGICAL *1   SELVB(80,20)

      INTEGER *2   SELIV(20)
 
      COMMON /SELDSC/ SELN, SELF,
     1                SELS, SELM, SELC, SELL, SELT, SELT2, SELV,
     2                SELI, SELSB, SELVB, SELIV
