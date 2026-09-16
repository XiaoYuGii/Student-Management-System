#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "student.h"
#include <iostream>
#include <iomanip>
#include <stdexcept>

struct Node {
    Student data;
    Node*   next;

    explicit Node(const Student& s) : data(s), next(nullptr) {}
};

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    void    insertBack(const Student& s);
    bool    update(int id, const Student& s);
    bool    remove(int id);
    Node*   search(int id)  const;
    Node*   searchByName(const std::string& n) const;

    void    display()       const;
    bool    isEmpty()       const;
    int     size()          const;
    bool    idExists(int id) const;
    int     nextAutoId()    const;

    Node*   head()          const { return head_; }

private:
    Node* head_;
    int   size_;

    Node* findPrev(int id) const;

    void printLine() const;
};

inline LinkedList::LinkedList() : head_(nullptr), size_(0) {}

inline LinkedList::~LinkedList() {
    Node* cur = head_;
    while (cur) {
        Node* tmp = cur->next;
        delete cur;
        cur = tmp;
    }
}

inline void LinkedList::insertBack(const Student& s) {
    Node* newNode = new Node(s);
    if (!head_) {
        head_ = newNode;
    } else {
        Node* cur = head_;
        while (cur->next) cur = cur->next;
        cur->next = newNode;
    }
    ++size_;
}

inline bool LinkedList::update(int id, const Student& s) {
    Node* cur = search(id);
    if (!cur) return false;
    cur->data = s;
    return true;
}

inline bool LinkedList::remove(int id) {
    if (!head_) return false;

    if (head_->data.id == id) {
        Node* tmp = head_;
        head_ = head_->next;
        delete tmp;
        --size_;
        return true;
    }

    Node* prev = findPrev(id);
    if (!prev) return false;

    Node* target = prev->next;
    prev->next   = target->next;
    delete target;
    --size_;
    return true;
}

inline Node* LinkedList::search(int id) const {
    Node* cur = head_;
    while (cur) {
        if (cur->data.id == id) return cur;
        cur = cur->next;
    }
    return nullptr;
}

inline Node* LinkedList::searchByName(const std::string& name) const {
    Node* cur = head_;
    while (cur) {
        if (cur->data.name == name) return cur;
        cur = cur->next;
    }
    return nullptr;
}

inline bool LinkedList::isEmpty() const { return size_ == 0; }
inline int  LinkedList::size()    const { return size_; }

inline bool LinkedList::idExists(int id) const {
    return search(id) != nullptr;
}

inline int LinkedList::nextAutoId() const {
    int maxId = 0;
    Node* cur = head_;
    while (cur) {
        if (cur->data.id > maxId) maxId = cur->data.id;
        cur = cur->next;
    }
    return maxId + 1;
}

inline Node* LinkedList::findPrev(int id) const {
    Node* cur = head_;
    while (cur && cur->next) {
        if (cur->next->data.id == id) return cur;
        cur = cur->next;
    }
    return nullptr;
}

inline void LinkedList::printLine() const {
    std::cout << std::string(75, '-') << "\n";
}

inline void LinkedList::display() const {
    if (isEmpty()) {
        std::cout << "  [No records found]\n";
        return;
    }
    printLine();
    std::cout << std::left
              << std::setw(6)  << "ID"
              << std::setw(22) << "Name"
              << std::setw(10) << "Gender"
              << std::setw(6)  << "Age"
              << std::setw(7)  << "GPA"
              << std::setw(20) << "Major"
              << "\n";
    printLine();
    Node* cur = head_;
    while (cur) {
        const Student& s = cur->data;
        std::cout << std::left
                  << std::setw(6)  << s.id
                  << std::setw(22) << s.name
                  << std::setw(10) << s.gender
                  << std::setw(6)  << s.age
                  << std::setw(7)  << std::fixed << std::setprecision(2) << s.gpa
                  << std::setw(20) << s.major
                  << "\n";
        cur = cur->next;
    }
    printLine();
    std::cout << "  Total records: " << size_ << "\n\n";
}

#endif
