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


void* freeNode(struct Node* node)
{
    free(node->key);
    free(node);
    return NULL;
}


int nodeValue(struct Node* node)
{
    if (!node) {
        return 0;
    }
    return node->value;
}


char* nodeKey(struct Node* node)
{
    if (!node) {
        return NULL;
    }
    return node->key;
}


char* nodeToString(struct Node* node)
{
    if (!node) { return NULL; }
    char* str = calloc(__MAX_KEY_LENGTH, sizeof(char));
    sprintf(str, "{%s: %d}", node->key, node->value);
    return str;
}


struct List* newList()
{
    struct List* list = malloc(sizeof(struct List));
    list->first = NULL;
    list->length = 0;
    return list;
}


void* freeList(struct List* list)
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
        freeNode(tmp);
    }
    free(list);
    return NULL;
}


size_t listLength(struct List* list)
{
    if (!list) { return 0; }
    return list->length;
}


size_t addToList(struct List* list, struct Node* node)
{
    if (!list) {
        return 0;
    }
    list->length += 1;
    if (!list->first) {
        list->first = node;
        return list->length;
    }
    struct Node* head = list->first;
    while (head->next) {
        head = head->next;
    }
    head->next = node;
    return list->length;
}


struct Node* getNodeFromList(struct List* list, char* key)
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


size_t removeFromList(struct List* list, char* key)
{
    if (!list || !list->first) { return 0; }

    struct Node* head = list->first->next;

    if (0 == strncmp(list->first->key, key, __MAX_KEY_LENGTH)) {
        freeNode(list->first);
        list->first = head;
        list->length -= 1;
        return list->length;
    }

    struct Node* prev = list->first;
    while (head) {
        if (0 == strncmp(head->key, key, __MAX_KEY_LENGTH)) {
            prev->next = head->next;
            freeNode(head);
            list->length -= 1;
            break;
        }
        prev = head;
        head = head->next;
    }
    return list->length;
}


bool listContains(struct List* list, char* key)
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


void invertList(struct List* list)
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


struct Node* _mergeLists(struct Node* a, struct Node* b)
{
    if (!a) { return b; }
    if (!b) { return a; }
    struct Node* ret = NULL;

    if (a->value <= b->value) {
        ret = a;
        ret->next = _mergeLists(a->next, b);
    } else {
        ret = b;
        ret->next = _mergeLists(a, b->next);
    }

    return ret;
}


struct List* mergeLists(struct List* l1, struct List* l2)
{
    if (!l1) { return l2; }
    if (!l2) { return l1; }
    struct List* list = newList();
    list->first = _mergeLists(l1->first, l2->first);
    return list;
}


struct Node* iterateOverList(struct List* list, size_t index)
{
    if (!list) { return NULL; }
    struct Node* head = list->first;
    for (size_t i = 0; head != NULL && i < list->length; i += 1) {
        if (index == i) { break; }
        head = head->next;
    }
    return head;
}


char* listToString(struct List* list)
{
    if (!list || !list->first) { return NULL; }
    char* str = calloc(list->length * __MAX_KEY_LENGTH, sizeof(char));
    sprintf(str, " {length: %zu}", list->length);
    struct Node* head = list->first;
    while (head) {
        char* node = nodeToString(head);
        sprintf(str + strnlen(str, __MAX_KEY_LENGTH), " %s", node);
        free(node);
        head = head->next;
    }
    return str;
}


const struct NodeLibrary Node = {
    .new = newNode,
    .free = freeNode,
    .value = nodeValue,
    .key = nodeKey,
    .toString = nodeToString,
};

const struct ListLibrary List = {
    .new = newList,
    .free = freeList,
    .length = listLength,
    .add = addToList,
    .get = getNodeFromList,
    .remove = removeFromList,
    .contains = listContains,
    .invert = invertList,
    .merge = mergeLists,
    .iter = iterateOverList,
    .toString = listToString,
};
