/* The installer version is stored in the key, the family
 * file, and the installer.  These assure compatibility.
 *
 * NOTE: this will be changed occasionally when it is
 * desired or necessary to invalidate previous versions
 * of codes.  For software revisions, and for appearances
 * to customers, we will use BUNDLE_INSTALLER_VERSION, q.v.
 * in BUNDLE_INSTALLER_VERSION. (For the FCS of G2, NOLS,
 * and Netsleuth, we displayed this (as 1.0) in the Unix
 * installer, but it was the same anyhow.  With 1.0r1, we
 * are leaving this a 10, so we don't invalidate old
 * codes. -mhd, 10/25/00
 */
#define INSTALLER_VERSION 11  /*  Prints as X.Y */

/* Platform codes.  These have form <platform-name>_CODE,
 * where platform-name is all lowercase. The count is
 * zero-based and contiguous to facilitate treating these
 * as bits in an array.
 */
#define INTELNT_CODE  0
#define SPARCSOL_CODE 1
#define RS6000_CODE   2
#define HPUX_CODE     3
#define LINUX_CODE    4
#define ALPHAOSF_CODE 5
#define LINUX64_CODE  6
#define HPIA64_CODE   7
#define WIN64_CODE    8

/* Error codes for errors that the user might see.
 * They are divided into categories for troubleshooting.
 * They should not be published directly to customers, since that could
 * help hackers to break our encoding scheme.
 */
#define FILE_ERROR 0x100
#define BAD_LICENSE_KEY 0x200
#define INCONSISTENCY_WITH_KEY 0x400
#define FAMILY_FILE_ERROR 0x500
#define INSTALLATION_ERROR 0x600
#define SYSTEM_ERROR 0x700

#define EARLY_EOF        (FILE_ERROR | 0x01)
#define BAD_MAGIC_NUMBER (FILE_ERROR | 0x02)

#define FAMILY_FILE_OPEN        (FILE_ERROR | 0x21)
#define FAMILY_FILE_INTEGRITY   (FILE_ERROR | 0x22)
#define FAMILY_FILE_TOO_LONG    (FILE_ERROR | 0x23)
#define FAMILY_FILE_PARSE_ERROR (FILE_ERROR | 0x24)

#define TAR_FILE_OPEN (FILE_ERROR | 0x24)
#define GSM_FILE_TAR_READ (FILE_ERROR | 0x25)

#define TAR_PIPE_WRITE (FILE_ERROR | 0x26)

#define EARLY_GSM_EOF (FILE_ERROR | 0x31)

#define NO_TAR_EXECUTABLE_FOUND (FILE_ERROR | 0x47)

#define KEY_NULL_STRING       (BAD_LICENSE_KEY | 0x01)
#define KEY_STRING_TOO_LONG   (BAD_LICENSE_KEY | 0x02)
#define KEY_TOO_MANY_DIGITS   (BAD_LICENSE_KEY | 0x03)
#define KEY_TOO_FEW_DIGITS    (BAD_LICENSE_KEY | 0x04)
#define KEY_ILLEGAL_CHARACTER (BAD_LICENSE_KEY | 0x05)
#define KEY_INVALID_ALPHANUM  (BAD_LICENSE_KEY | 0x06)
#define KEY_BAD_CHECKSUM      (BAD_LICENSE_KEY | 0x07)

#define KEY_TO_FAMILY_ID_MISMATCH        (BAD_LICENSE_KEY | 0x11)
#define KEY_TO_FAMILY_INSTALLER_MISMATCH (BAD_LICENSE_KEY | 0x12)

#define KEY_HEADER_INSTALLER_MISMATCH (INCONSISTENCY_WITH_KEY | 0x01)
#define KEY_HEADER_FAMILY_MISMATCH    (INCONSISTENCY_WITH_KEY | 0x02)
#define KEY_HEADER_SYSTEM_MISMATCH    (INCONSISTENCY_WITH_KEY | 0x03)

#define BUNDLE_NOT_IN_FAMILY       (FAMILY_FILE_ERROR | 0x01)
#define BAD_COMPONENT_INDEX_FOUND  (FAMILY_FILE_ERROR | 0x02)
#define TAR_ARGS_EXCEEDED          (FAMILY_FILE_ERROR | 0x03)

#define FILE_RENAMING_ERROR       (INSTALLATION_ERROR | 0x01)

#define WAITPID_FAILURE (SYSTEM_ERROR | 0x01)
#define SPAWN_ERROR     (SYSTEM_ERROR | 0x02)

#define LINE_TOO_LONG -1

#define SUCCESS 0
#define FAILURE 1
