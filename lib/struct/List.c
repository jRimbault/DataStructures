#include <memory.h>
#include <stdio.h>
#include <string.h>

#include "List.h"


#define __MAX_KEY_LENGTH 2048

struct Node
{
    char* key;
    int value;
    struct Node* next;
};

struct List
{
    struct Node* first;
    struct Node* last;
    struct Node* current;
    size_t length;
};


struct Node* newNode(char* key, int value)
{
    struct Node* n = malloc(sizeof(struct Node));
    n->key = strdup(key);
    n->value = value;
    n->next = NULL;
    return n;
}


void* node_free(struct Node* node)
{
    free(node->key);
    free(node);
    return NULL;
}


int node_get_value(struct Node* node)
{
    if (!node) {
        return 0;
    }
    return node->value;
}


char* node_get_key(struct Node* node)
{
    if (!node) {
        return NULL;
    }
    return node->key;
}


char* node_to_chars(struct Node* node)
{
    if (!node) { return NULL; }
    char* str = calloc(__MAX_KEY_LENGTH, sizeof(char));
    sprintf(str, "{%s: %d}", node->key, node->value);
    return str;
}


struct List* list_new()
{
    struct List* list = malloc(sizeof(struct List));
    list->first = NULL;
    list->last = NULL;
    list->length = 0;
    return list;
}


void* list_free(struct List* list)
{
    if (!list) {
        return NULL;
    }
    if (!list->first) {
        free(list);
        return NULL;
    }
    struct Node* head = list->first;
    while (head) {
        struct Node* tmp = head;
        head = head->next;
        node_free(tmp);
    }
    free(list);
    return NULL;
}


size_t list_length(struct List* list)
{
    if (!list) { return 0; }
    return list->length;
}


size_t list_add_node(struct List* list, struct Node* node)
{
    if (!list) {
        return 0;
    }
    list->length += 1;
    if (!list->first) {
        list->first = node;
        list->last = node;
    } else {
        list->last->next = node;
        list->last = node;
    }
    return list->length;
}


struct Node* node_get_node_by_key(struct List* list, char* key)
{
    if (!list || !list->first) {
        return NULL;
    }
    struct Node* head = list->first;
    while (head) {
        if (0 == strncmp(head->key, key, __MAX_KEY_LENGTH)) {
            return head;
        }
        head = head->next;
    }
    return NULL;
}


size_t list_remove_by_key(struct List* list, char* key)
{
    if (!list || !list->first) { return 0; }

    struct Node* head = list->first->next;

    if (0 == strncmp(list->first->key, key, __MAX_KEY_LENGTH)) {
        node_free(list->first);
        list->first = head;
        list->length -= 1;
        return list->length;
    }

    struct Node* prev = list->first;
    while (head) {
        if (0 == strncmp(head->key, key, __MAX_KEY_LENGTH)) {
            prev->next = head->next;
            node_free(head);
            list->length -= 1;
            break;
        }
        prev = head;
        head = head->next;
    }
    return list->length;
}


bool list_contains(struct List* list, char* key)
{
    if (!list || !list->first) { return false; }

    struct Node* head = list->first;

    if (0 == strncmp(head->key, key, __MAX_KEY_LENGTH)) {
        return true;
    }

    while (head) {
        if (0 == strncmp(head->key, key, __MAX_KEY_LENGTH)) {
            return true;
        }
        head = head->next;
    }
    return false;
}


void list_invert(struct List* list)
{
    if (!list || !list->first) { return; }
    struct Node* head = list->first;
    struct Node* prev = NULL;
    struct Node* next = NULL;

    while (head) {
        next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
}


struct Node* _list_merge(struct Node* a, struct Node* b)
{
    if (!a) { return b; }
    if (!b) { return a; }
    struct Node* ret = NULL;

    if (a->value <= b->value) {
        ret = a;
        ret->next = _list_merge(a->next, b);
    } else {
        ret = b;
        ret->next = _list_merge(a, b->next);
    }

    return ret;
}


struct List* list_merge(struct List* l1, struct List* l2)
{
    if (!l1) { return l2; }
    if (!l2) { return l1; }
    struct List* list = list_new();
    list->first = _list_merge(l1->first, l2->first);
    return list;
}


struct Node* list_iterator(struct List* list, size_t index)
{
    if (!list) { return NULL; }
    if (index >= list->length) { return NULL; }
    struct Node* head = list->first;
    for (size_t i = 0; i < index; i += 1) {
        head = head->next;
    }
    return head;
}


char* list_to_chars(struct List* list)
{
    if (!list || !list->first) { return NULL; }
    char* str = calloc(list->length * __MAX_KEY_LENGTH, sizeof(char));
    sprintf(str, " {length: %zu}", list->length);
    struct Node* head = list->first;
    while (head) {
        char* node = node_to_chars(head);
        sprintf(str + strnlen(str, __MAX_KEY_LENGTH), " %s", node);
        free(node);
        head = head->next;
    }
    return str;
}


const struct NodeLibrary Node = {
    .new = newNode,
    .free = node_free,
    .value = node_get_value,
    .key = node_get_key,
    .toString = node_to_chars,
};

const struct ListLibrary List = {
    .new = list_new,
    .free = list_free,
    .length = list_length,
    .add = list_add_node,
    .get = node_get_node_by_key,
    .remove = list_remove_by_key,
    .contains = list_contains,
    .invert = list_invert,
    .merge = list_merge,
    .iter = list_iterator,
    .toString = list_to_chars,
};
