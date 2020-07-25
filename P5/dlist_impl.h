//
// Created by Administrator on 2020/7/22/022.
//

#ifndef P5_DLIST_IMPL_H
#define P5_DLIST_IMPL_H

#include "dlist.h"
#include <iostream>

using namespace std;

template<class T>
bool Dlist<T>::isEmpty() const {
    return first == nullptr && last == nullptr;
    //TODO: ATTENTION: actually if it is empty; !!! first & last= nullptr !!!
}

template<class T>
void Dlist<T>::insertFront(T *op) {
    node *new_node;
    new_node = new node;
    new_node->op = op;
    new_node->prev = nullptr;
    if (isEmpty()) {
        new_node->next = nullptr;
        first = new_node;
        last = new_node;
    } else {
        first->prev = new_node;
        new_node->next = first;
        first = new_node;
    }
}

template<class T>
void Dlist<T>::insertBack(T *op) {
    node *new_node;
    new_node = new node;
    new_node->op = op;
    new_node->next = nullptr;
    if (isEmpty()) {
        new_node->prev = nullptr;
        first = new_node;
        last = new_node;
    } else {
        last->next = new_node;
        new_node->prev = last;
        last = new_node;
    }
}


template<class T>
T *Dlist<T>::removeFront() {
    if (first == nullptr) {
        emptyList a;
        throw a;
    } else {
        node *medium = first;
        first = first->next;
        if (first != nullptr) {
            first->prev = nullptr;
        } else {
            last = nullptr;
        }
        T *result = medium->op;
        delete medium;//TODO:check if medium is deleted, result will be deleted as well?
        return result;
    }
}

template<class T>
T *Dlist<T>::removeBack() {
    if (last == nullptr) {
        emptyList a;
        throw a;
    } else {
        node *medium = last;
        last = last->prev;
        if (last != nullptr) {
            last->next = nullptr;
        } else {
            first = nullptr;
        }
        T *result = medium->op;
        delete medium;//TODO:check if medium is deleted, result will be deleted as well?
        return result;
    }
}

template<class T>
T *Dlist<T>::remove(bool (*cmp)(const T *, const T *), T *ref) {
    node *itr = first;
    while (itr) {
        if (cmp(itr->op, ref)) {
            node *previous_node = itr->prev;
            node *next_node = itr->next;
            previous_node->next = next_node;
            next_node->prev = previous_node;
            T *result = itr->op;
            delete itr;//TODO:check if itr is deleted, result will be deleted as well?
            return result;
        } else {
            itr = itr->next;
        }
    }
    return nullptr;
}

template<class T>
void Dlist<T>::copyAll(const Dlist<T> &l) {
    removeAll();
    node *itr = l.first;
    if (itr) {
        node *itr_this, *medium;
        int i = 0;
        while (itr) {
            itr_this = new node;
            T *new_op = new T;
            *new_op = *(itr->op);
            itr_this->op = new_op;
            if (i > 0) {
                itr_this->prev = medium;
                medium->next = itr_this;
            }
            medium = itr_this;
            itr = itr->next;
            if (i == 0) {
                first = itr_this;
                first->prev = nullptr;
            }
            i++;
        }
        last = itr_this;
        last->next = nullptr;
    } else {
        first = nullptr;
        last = nullptr;
    }
}

template<class T>
void Dlist<T>::removeAll() {
    if (first != nullptr) {
        node *itr = first, *medium;
        while (itr) {
            medium = itr->next;
            delete itr->op;
            delete itr;
            itr = medium;
        }
    }
    first = nullptr;
    last = nullptr;
}

template<class T>
Dlist<T>::Dlist():first(nullptr), last(nullptr) {

}

template<class T>
Dlist<T>::Dlist(const Dlist<T> &l) {
    copyAll(l);
}

template<class T>
Dlist<T> &Dlist<T>::operator=(const Dlist<T> &l) {
    copyAll(l);
    return *this;
}

template<class T>
Dlist<T>::~Dlist<T>() {
    removeAll();
}


#endif //P5_DLIST_IMPL_H
