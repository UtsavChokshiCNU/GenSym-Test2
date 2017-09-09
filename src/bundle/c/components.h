/* This contains entries needed for associating keys with the
 * parsed entries from a family file.  Both key.h and
 * family-descriptor.h must be included first to get the
 * necessary definitions.
 */

typedef struct component_selection {
    int selected;
    COMPONENT *component;
} COMPONENT_SELECTION;

typedef struct licensed_components {
    FAMILY_DESCRIPTOR *family;
    BUNDLE *bundle;
    COMPONENT_SELECTION components[NUMBER_OF_COMPONENTS];
} LICENSED_COMPONENTS;
