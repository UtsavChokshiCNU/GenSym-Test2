/* wrapper.h
 *
 * Copyright (C) 1991 Chestnut Software, Inc.  All Rights Reserved.
 *
 *
 *
 * The definition of the WRAPPER_OF macro is closely tied to the data structure
 * and tag definitions specified in object.h.
 */

/* SI_WRAPPER_OF(object)
 *
 * Returns the class wrapper that best describes object.
 * Evaluates object more than once.
 *
 * Implementation note: This is optimized for the Instance case, only doing
 * the out-of-line function call for non-Instance objects.  This presumes that
 * most places that need the wrapper will be operating on Instance objects.
 * Other cases could be pulled up into the inline code, but there is the
 * possibility that the cost in code space would outway the benefits.
 *
 * Note that the wrapper returned by this function might be "obsolete".
 * Callers of this macro must arrange to deal with this possibility in an
 * appropriate fashion.  See SI_WRAPPER_OBSOLETE_P() and class_of().
 */

#ifdef SI_RUNTIME_INTERNAL

#define SI_WRAPPER_OF(o) \
    (SI_INSTANCEP(o) ? INSTANCE_WRAPPER(o) : SI_wrapper_of(o))

extern Object	SI_wrapper_of();

#endif /* defined(SI_RUNTIME_INTERNAL) */

/* These need to be external so that static initializers work. */
#if SI_OBJECT_INITIALIZERS_WORK
extern SI_Class_wrapper	SI_Function_wrapper;
extern SI_Class_wrapper	SI_Package_wrapper;
#endif

/* These need to be referenced by the corresponding constructors, so need
 * to be external.  Some of them might go away if the corresponding pieces of
 * the runtime are reimplemented using CLOS. */

#ifdef SI_RUNTIME_INTERNAL

extern Object	SI_WRAPPER_cobject;
extern Object	SI_WRAPPER_foreign_pointer;
extern Object	SI_WRAPPER_foreign_type;
extern Object	SI_WRAPPER_primitive_foreign_type;
extern Object	SI_WRAPPER_array_foreign_type;
extern Object	SI_WRAPPER_pointer_foreign_type;
extern Object	SI_WRAPPER_structure_foreign_type;
extern Object	SI_WRAPPER_effective_method;
extern Object	SI_WRAPPER_function;
extern Object	SI_WRAPPER_hash_table;
extern Object	SI_WRAPPER_logical_pathname;
extern Object	SI_WRAPPER_method_combination;
extern Object	SI_WRAPPER_package;
extern Object	SI_WRAPPER_pathname;
extern Object	SI_WRAPPER_random_state;
extern Object	SI_WRAPPER_readtable;

#if SI_SUPPORT_THREAD
extern Object	SI_WRAPPER_atomic_ref;
extern Object	SI_WRAPPER_thread;
extern Object	SI_WRAPPER_lock;
extern Object	SI_WRAPPER_condition_variable
#endif

extern Object	SI_WRAPPER_broadcast_stream;
extern Object	SI_WRAPPER_concatenated_stream;
extern Object	SI_WRAPPER_echo_stream;
extern Object	SI_WRAPPER_file_stream;
extern Object	SI_WRAPPER_string_input_stream;
extern Object	SI_WRAPPER_string_output_stream;
extern Object	SI_WRAPPER_synonym_stream;
extern Object	SI_WRAPPER_two_way_stream;
extern Object	SI_WRAPPER_interaction_stream;

#endif /* defined(SI_RUNTIME_INTERNAL) */
