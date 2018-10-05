#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "List.h"


struct Link* newLink(char* key, int value)
{
    struct Link* n = calloc(1, sizeof(struct Link));
    n->key = strndup(key, __MAX_KEY_LENGTH);
    n->value = value;
    n->next = NULL;
    return n;
}


struct Link* newLinkedList(int* values, int count)
{
    struct Link* link = NULL;
    struct Link* root = NULL;
    struct Link* last = NULL;
    for (int i = 0; i < count; i += 1) {
        if (!link) {
            link = Link.new("", values[i]);
            if (!root) {
                root = link;
            }
            if (last) {
                last->next = link;
            }
        }
        last = link;
        link = link->next;
    }
    return root;
}


struct Link* insertFirst(struct Link* link, int value)
{
    struct Link* new = Link.new("", value);
    new->next = link;
    return new;
}


struct Link* insertAt(struct Link* link, int value, int position)
{
    struct Link* new = Link.new("", value);
    struct Link* root = link;
    struct Link* prev = link;

    for (int i = 0; i < position; i += 1) {
        if (!link->next) break;
        prev = link;
        link = link->next;
    }

    new->next = prev->next;
    prev->next = new;

    return root;
}


void _subInsertLast(struct Link* link, char* key, int value)
{
    if (link->next) {
        _subInsertLast(link->next, key, value);
        return;
    }
    link->next = Link.new(key, value);
}


struct Link* insertLast(struct Link* link, char* key, int value)
{
    if (!link) return Link.new(key, value);
    _subInsertLast(link, key, value);
    return link;
}


struct Link* deleteFirst(struct Link* link)
{
    if (!link) return link;
    struct Link* next = link->next;
    free(link->key);
    free(link);
    return next;
}


struct Link* deleteAt(struct Link* link, int position)
{
    if (position == 0) return List.freeFirst(link);
    struct Link* root = link;
    struct Link* prev = link;

    for (int i = 0; i < position; i += 1) {
        if (!link->next) break;
        prev = link;
        link = link->next;
    }

    prev->next = link->next;
    free(link->key);
    free(link);

    return root;
}


void _subDeleteLast(struct Link* link)
{
    if (link->next->next) {
        _subDeleteLast(link->next);
        return;
    }
    free(link->next->key);
    free(link->next);
    link->next = NULL;
}


struct Link* deleteLast(struct Link* link)
{
    if (link == NULL) return NULL;
    if (link->next == NULL) return NULL;
    _subDeleteLast(link);
    return link;
}


struct Link* deleteList(struct Link* n)
{
    struct Link* tmp;
    while (n) {
        tmp = n;
        n = n->next;
        free(tmp->key);
        free(tmp);
    }
    return NULL;
}


int _subLength(struct Link* link)
{
    if (link->next) {
        return 1 + _subLength(link->next);
    }
    return 1;
}


int listLength(struct Link* link)
{
    if (link == NULL) return 0;
    if (link->next) {
        return 1 + _subLength(link->next);
    }
    return 1;
}


int listContains(struct Link* link, int value)
{
    if (link == NULL) return 0;
    if (link->value == value) return 1;
    return listContains(link->next, value);
}


struct Link* getAt(struct Link* link, int position)
{
    for (int i = 0; i < position && link != NULL; i += 1) {
        link = link->next;
    }
    return link;
}


struct Link* getLink(struct Link* link, char* key)
{
    while (link) {
        if (0 == strncmp(link->key, key, __MAX_KEY_LENGTH)) {
            break;
        }
        link = link->next;
    }
    return link;
}


struct Link* removeLink(struct Link* link, char* key)
{
    if (0 == strncmp(link->key, key, __MAX_KEY_LENGTH)) {
        return deleteFirst(link);
    }
    struct Link* prev = link;
    struct Link* head = link->next;
    while (head) {
        if (0 == strncmp(head->key, key, __MAX_KEY_LENGTH)) {
            prev->next = head->next;
            free(head->key);
            free(head);
            break;
        }
        prev = head;
        head = head->next;
    }
    return link;
}


struct Link* invertList(struct Link* link)
{
    struct Link* current = link;
    struct Link* prev = NULL;
    struct Link* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}


struct Link* mergeLists(struct Link* a, struct Link* b)
{
    struct Link* ret = NULL;
    if (!a) return b;
    if (!b) return a;

    if (a->value <= b->value) {
        ret = a;
        ret->next = mergeLists(a->next, b);
    } else {
        ret = b;
        ret->next = mergeLists(a, b->next);
    }

    return ret;
}


void displayLinkedList(struct Link* n)
{
    if (!n) {
        fprintf(stdout, "\n");
        return;
    }
    fprintf(stdout, " {%s: %d}", n->key, n->value);
    displayLinkedList(n->next);
}


const struct LinkLibrary Link = {
    .new = newLink,
};

const struct LinkedListLibrary List = {
    .new = newLinkedList,
    .insertFirst = insertFirst,
    .insertAt = insertAt,
    .add = insertLast,
    .freeFirst = deleteFirst,
    .freeAt = deleteAt,
    .pop = deleteLast,
    .free = deleteList,
    .length = listLength,
    .contains = listContains,
    .getAt = getAt,
    .get = getLink,
    .remove = removeLink,
    .invert = invertList,
    .merge = mergeLists,
    .display = displayLinkedList,
};
