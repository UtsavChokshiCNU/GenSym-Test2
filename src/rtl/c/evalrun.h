

/* Every interpreted function has its lambda-definition stored
 * as FIRST element of its ENVIRONMENT
 *
 * Current representation:
 * (number-of-arguments list-of-arguments.forms)
 *
 */


#define FORMARGS() \
    (CAR(CDR(CAR(SI_FUNCTION_ENV(SI_Called_function)))))

#define NARGS() \
    (CAR((CAR(SI_FUNCTION_ENV(SI_Called_function)))))

#define FORMS() \
    (CDR(CDR(CAR(SI_FUNCTION_ENV(SI_Called_function)))))

#define INIT_EVALRUN() \
    ((void)(initialized_p ? \
     (void) TRUE : \
     (initialized_p = TRUE, SI_INIT_evalrun())))

#define ENSURE_STACK(n)
