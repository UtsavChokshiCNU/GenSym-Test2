/* Returned by GetNextComponentIndex at last component. */
#define NO_MORE_COMPONENTS -1

#define DIGITS_IN_KEY 25
#define DIGITS_PLUS_FILLER_IN_KEY 35
#define DATA_DIGITS_IN_KEY (DIGITS_IN_KEY - 1)
#define NUMBER_OF_WORDS 4

#define NUMBER_OF_COMPONENT_NIBBLES 15

/* The maximum number of components is 60. Index range is 0 to 59. */
#define NUMBER_OF_BASE_COMPONENTS (NUMBER_OF_COMPONENT_NIBBLES*NUMBER_OF_WORDS)
#define NUMBER_OF_COMPONENTS NUMBER_OF_BASE_COMPONENTS+8

typedef struct license_key {
    unsigned int installer_version;
    unsigned int family_id;
    unsigned int bundle_id;
    unsigned int system_id;
    unsigned char components[NUMBER_OF_COMPONENTS]; /* 1 if licensed else 0.*/
} LICENSE_KEY;

/* The following is static to guarantee only one instance per inclusion.
 * It maps the values from 0 thru 31 to randomized characters; i.e.,
 * each character represents a 5-bit value.
 */
static char chartrans[] = {
    'c','g','6','f','h','t','i','3',
    'j','z','r','8','k','7','n','y',
    'm','a','9','p','x','5','q','e',
    '2','b','s','u','d','v','w','4'
};

#ifdef __cplusplus
extern "C" int key_to_keystruct(char *key, LICENSE_KEY *kstruct);
#else 
extern int key_to_keystruct(char *key, LICENSE_KEY *kstruct);
#endif
