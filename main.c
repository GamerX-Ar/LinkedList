#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef int T;

typedef struct dl_item_t dl_item_t;
typedef struct list_t list_t;

struct dl_item_t {
    T _value;
    dl_item_t *_prev;
    dl_item_t *_next;
};

struct list_t {
    dl_item_t *_item;
    void (*add)(const T, const unsigned short, list_t * const);
    void (*del)(const unsigned short, list_t * const);
    T (*at)(const unsigned short, list_t * const);
    bool (*is_empty)(list_t * const);
    unsigned short (*length)(list_t * const);
    void (*destroy)(list_t * const);
};

void destroy(list_t * const this) {
    for(; this->_item != NULL; this->_item = this->_item->_next) {
        free(this->_item);
    }
}

void add(const T value, const unsigned short index, list_t * const this) {
    dl_item_t *it = this->_item;
    unsigned short it_pos = 0;

    for (it_pos = 0; it_pos < index && it->_next; ++it_pos) {
        it = it->_next;
    }

    dl_item_t *list_item = malloc(sizeof(dl_item_t));
    list_item->_value = value;
    list_item->_prev = index > it_pos ? it : it ? it->_prev : NULL;
    list_item->_next = index > it_pos ? it ? it->_next : NULL : it;

    if ( it ) {
        if (index > it_pos) {
            it->_next = list_item;
        } else {
            it->_prev = list_item;
        }
    }

    if ( !list_item->_prev ) { this->_item = list_item; }
}

void del(const unsigned short index, list_t * const this) {

}

T at(const unsigned short index, list_t * const this) {
    return 0;
}

bool is_empty(list_t * const this) {
    return 0;
}

unsigned short length(list_t * const this) {
    return 0;
}

void init_dlist(list_t *list) {
    list->_item = NULL;
    list->add = &add;
    list->del = &del;
    list->at = &at;
    list->is_empty = &is_empty;
    list->length = &length;
    list->destroy = &destroy;
}

int main() {
    list_t list;

    init_dlist(&list);

    list.add(1, 0, &list);
    list.add(2, 0, &list);

    list.destroy(&list);

    return 0;
}
