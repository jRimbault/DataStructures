#ifndef UNITTESTINGC_TYPELESSLIST_H
#define UNITTESTINGC_TYPELESSLIST_H

#include <stdlib.h>
#include <stdbool.h>


struct Node;

struct List;

struct NodeLibrary
{
    struct Node* (* new)(char* key, void* value);
    void* (* free)(struct Node* node);
    void* (* value)(struct Node* node);
    char* (* toString)(struct Node* node);
};

struct ListLibrary
{
    struct List* (* new)();
    void* (* free)(struct List* list);
    size_t (* length)(struct List* list);
    size_t (* add)(struct List* list, struct Node* node);
    size_t (* remove)(struct List* list, char* key);
    struct Node* (* get)(struct List* list, char* key);
    bool (* contains)(struct List* list, char* key);
    void (* invert)(struct List* list);
    struct List* (* merge)(struct List* l1, struct List* l2);
    struct Node* (* iter)(struct List* list, size_t index);
    char* (* toString)(struct List* list);
};

extern const struct NodeLibrary Node;
extern const struct ListLibrary List;

#endif //UNITTESTINGC_TYPELESSLIST_H
