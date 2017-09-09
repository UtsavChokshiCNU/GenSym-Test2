
package com.gensym.gsi;

public interface ICPTypeTags {

    short GSI_NULL_TYPE_TAG = 0;
    short GSI_INTEGER_TYPE_TAG = 1;
    short GSI_FLOAT_TYPE_TAG = 2;
    short GSI_SYMBOL_TYPE_TAG = 3;
    short GSI_STRING_TYPE_TAG = 4;
    short GSI_LOGICAL_TYPE_TAG = 5;
    short GSI_64BIT_FLOAT_TYPE_TAG = 6;
    short GSI_ITEM_TYPE_TAG = 7;
    short GSI_VALUE_TYPE_TAG = 8;
    short GSI_ITEM_HANDLE_TYPE_TAG = 9;
    short GSI_QUANTITY_TYPE_TAG = 10;
    short GSI_UNSIGNED_SHORT_VECTOR_TYPE_TAG = 11;

    short GSI_INTEGER_ARRAY_TYPE_TAG = 17;
    short GSI_SYMBOL_ARRAY_TYPE_TAG = 19;
    short GSI_STRING_ARRAY_TYPE_TAG = 20;
    short GSI_LOGICAL_ARRAY_TYPE_TAG = 21;
    short GSI_64BIT_FLOAT_ARRAY_TYPE_TAG = 22;
    short GSI_ITEM_ARRAY_TYPE_TAG = 23;
    short GSI_VALUE_ARRAY_TYPE_TAG = 24;
    short GSI_ITEM_OR_VALUE_ARRAY_TYPE_TAG = 25;
    short GSI_QUANTITY_ARRAY_TYPE_TAG = 26;

    short GSI_INTEGER_LIST_TYPE_TAG = 33;
    short GSI_SYMBOL_LIST_TYPE_TAG = 35;
    short GSI_STRING_LIST_TYPE_TAG = 36;
    short GSI_LOGICAL_LIST_TYPE_TAG = 37;
    short GSI_64BIT_FLOAT_LIST_TYPE_TAG = 38;
    short GSI_ITEM_LIST_TYPE_TAG = 39;
    short GSI_VALUE_LIST_TYPE_TAG = 40;
    short GSI_ITEM_OR_VALUE_LIST_TYPE_TAG = 41;
    short GSI_QUANTITY_LIST_TYPE_TAG = 42;

    short GSI_SEQUENCE_TYPE_TAG = 49;
    short GSI_STRUCTURE_TYPE_TAG = 50;
    short GSI_END_TYPE_TAG = 59;
    short GSI_LARGEST_UNARY_TYPE_NUMBER = 11;

    short ICP_CONS_TYPE_TAG = 80;
    short ICP_LIST_TYPE_TAG = 81;
    short ICP_LIST_NIL_TERMINATOR_TYPE_TAG = 82;
    short ICP_LIST_NON_NIL_TERMINATOR_TYPE_TAG = 83;

    short ICP_STANDARD_INDEX_SPACE_TYPE_TAG = 70;
    short ICP_NEW_SYMBOL_TYPE_TAG = 71;
    short ICP_NEW_SYMBOL_EXPANDING_INDEX_SPACE_TYPE_TAG = 72;
    short ICP_TEMPORARY_INDEX_SPACE_TYPE_TAG = 73;
    short RPC_HANDLE_FOR_TEMPORARY_OBJECT_HANDLE_TYPE_TAG = 74;
    short ICP_NEW_KEYWORD_SYMBOL_TYPE_TAG = 75;

    short RPC_UNKNOWN_TYPE_TAG =       0;
    short RPC_OBJECT_TYPE_TAG =        7;
    short RPC_OBJECT_HANDLE_TYPE_TAG = 8;

    short RPC_HANDLE_FOR_SENDING_SIDE_OBJECT_TYPE_TAG = 60;
    short RPC_HANDLE_FOR_RECEIVING_SIDE_OBJECT_HANDLE_TYPE_TAG = 61;
    short RPC_HANDLE_FOR_NEW_SENDING_SIDE_OBJECT_TYPE_TAG = 62;
    short RPC_NEW_ITEM_COPY_WITH_REFERENCE = 63;
    short RPC_EXISTING_ITEM_COPY = 64;
    short RPC_NEW_ITEM_COPY = 65;
    short RPC_NEW_ITEM_COPY_WITH_HANDLE = 66;
    short GSI_TYPED_SEQUENCE_TYPE_TAG = 67;
    short GSI_GENSYM_STRING_TYPE_TAG = 68;
    short GSI_WIDE_STRING_TYPE_TAG = 69;

    short LIST_ELEMENT_NULL_TYPE_TAG = 0;
    short LIST_ELEMENT_INTEGER_TYPE_TAG = 1;
    short LIST_ELEMENT_SYMBOL_TYPE_TAG = 2;
    short LIST_ELEMENT_TEXT_TYPE_TAG = 3;
    short LIST_ELEMENT_LIST_TYPE_TAG = 4;
    short LIST_ELEMENT_CONS_TYPE_TAG = 5;

    short ICP_TREE_INTERNED_LIST_TYPE_TAG = 90;
    short INDEX_SPACE_REMOTE_PROCEDURE_NAME = 91;

}
