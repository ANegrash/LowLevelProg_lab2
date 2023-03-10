#ifndef CALC_REQUEST_TREE_H
#define CALC_REQUEST_TREE_H

#include <stdbool.h>
#include "stdlib.h"
#include "array_list.h"

typedef enum request_type {
    UNDEFINED,
    REQUEST_OPEN,
    REQUEST_CREATE,
    REQUEST_CLOSE,
    REQUEST_ADD_SCHEMA,
    REQUEST_DELETE_SCHEMA,
    REQUEST_ADD_NODE,
    REQUEST_SELECT
} request_type;

typedef enum attr_type {
    ATTR_TYPE_INTEGER = 0,
    ATTR_TYPE_BOOLEAN,
    ATTR_TYPE_FLOAT,
    ATTR_TYPE_STRING,
    ATTR_TYPE_REFERENCE
} attr_type;

typedef struct file_work_struct {
    char *filename;
} file_work_struct;

typedef struct attribute_declaration {
    char *attr_name;
    attr_type type;
    char *schema_ref_name;
} attribute_declaration;

typedef struct add_schema_struct {
    char *schema_name;
    arraylist *attribute_declarations;
} add_schema_struct;

typedef struct delete_schema_struct {
    char *schema_name;
} delete_schema_struct;

union value {
    int integer_value;
    bool bool_value;
    char* string_value;
    float float_value;
};

typedef struct attr_value {
    char *attr_name;
    attr_type type;
    union value value;
} attr_value;

typedef struct add_node_struct {
    char* schema_name;
    arraylist *attribute_values;
} add_node_struct;

typedef enum select_option {
    OPTION_EQUAL,
    OPTION_GREATER,
    OPTION_GREATER_EQUAL,
    OPTION_LESS,
    OPTION_LESS_EQUAL,
    OPTION_NOT_EQUAL,
    OPTION_LIKE
} select_option;

typedef struct select_condition {
    char *attr_name;
    select_option option;
    attr_type type;
    union value value;
} select_condition;

typedef enum statement_type {
    SELECT_CONDITION,
    OUT,
    DELETE
} statement_type;

typedef struct statement {
    statement_type type;
    union {
        arraylist *conditions;
        char *attr_name;
    };
} statement;

typedef struct request_tree {
    request_type type;
    char* schema_name;
    union {
        file_work_struct file_work;
        add_schema_struct add_schema;
        delete_schema_struct delete_schema;
        add_node_struct add_node;
        arraylist *statements;
    };
} request_tree;

void print_request_tree(request_tree tree);

size_t get_tree_size(request_tree tree);

request_tree get_request_tree();

#endif //CALC_REQUEST_TREE_H
