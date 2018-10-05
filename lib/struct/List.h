#ifndef CLANGPOOL_LINKEDLIST_H
#define CLANGPOOL_LINKEDLIST_H

#define __MAX_KEY_LENGTH 2048


struct Link {
    struct Link* next;
    char* key;
    int value;
};


struct LinkLibrary {
    struct Link* (* new)(char* key, int);
};


struct LinkedListLibrary {
    struct Link* (* new)(int*, int);
    struct Link* (* insertFirst)(struct Link*, int);
    struct Link* (* insertAt)(struct Link*, int, int);
    struct Link* (* add)(struct Link*, char*, int);
    struct Link* (* freeFirst)(struct Link*);
    struct Link* (* freeAt)(struct Link*, int);
    struct Link* (* pop)(struct Link*);
    struct Link* (* free)(struct Link*);
    int (* length)(struct Link*);
    int (* contains)(struct Link*, int);
    struct Link* (* getAt)(struct Link*, int);
    struct Link* (* get)(struct Link*, char*);
    struct Link* (* remove)(struct Link*, char*);
    struct Link* (* invert)(struct Link*);
    struct Link* (* merge)(struct Link*, struct Link*);
    void (* display)(struct Link*);
};


extern const struct LinkLibrary Link;

extern const struct LinkedListLibrary List;

#endif //CLANGPOOL_LINKEDLIST_H
