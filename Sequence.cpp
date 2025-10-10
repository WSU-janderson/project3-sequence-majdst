#include "Sequence.h"
#include <stdexcept>
#include <ostream>
#include <iostream>

using std::size_t;
using std::string;
using std::runtime_error;
using std:: out_of_range;


//given index-->find the raw pointer to the node
SequenceNode* Sequence::nodeAt(size_t idx) const {
    if (idx >= size_) {
        throw out_of_range("index out of range");
    }

    SequenceNode* current = head_; //start at the head

    //walking forward
    for (size_t i = 0; i < idx; i++) {

        current = current ->next;
    }
    return current;
}

// Creates a sequence of sz items
Sequence::Sequence(size_t sz):head_(nullptr), tail_(nullptr), size_(0) {

    for (size_t i = 0; i < sz; i++){push_back("");} //empty string-->new element
}

//memory cleaning
Sequence::~Sequence(){clear();}
//create a deep copy-->
/*
 * remember: this part create a deep copy, if I just copy the head/tail--> they will
 * point to the same memory as others-->if other delete, list will break.
 */
Sequence::Sequence(const Sequence& other) : head_(nullptr), tail_(nullptr), size_(0) {

    SequenceNode* current = other.head_;
    while (current != nullptr) {
        push_back(current->item);
        current = current->next;
    }
}
//deep copy -->rhs
Sequence& Sequence::operator = (const Sequence& rhs) {
    if (this== &rhs){return *this;}

    //destroy current content
    clear();

    // build new content via deep copy
    SequenceNode* current = rhs.head_;

    while (current != nullptr) {
        push_back(current->item);
        current = current->next;
    }

    return *this;
}

//memory release by delete item
void Sequence::clear() {
    SequenceNode* current = head_;

    while (current != nullptr) {
        //delete current before storing next

        SequenceNode* next_node = current->next;
        delete current;
        current = next_node;
    }

    head_ = nullptr;
    tail_ = nullptr;
    size_ = 0;
}

// At index-->access or modify
string& Sequence::operator[](size_t position) {
    return nodeAt(position)->item;
}

//first element check
string Sequence::front() const {
    if (empty()) {
        throw runtime_error("Front Empty");
    }else{return head_->item;}
}
//last element
string Sequence::back() const {
    if (empty()) {
        throw runtime_error("Back empty");
    }else{tail_->item;}
}

bool Sequence::empty() const{return size_ == 0;}
size_t Sequence::size() const{return size_;}

// append item to sequence
void Sequence::push_back(string item) {
    SequenceNode* n = new SequenceNode(item);

    if (empty()) {
        head_ = tail_ = n;
    }else {
        n->before = tail_; //new node-->current tail
        tail_->next=n;
        tail_=n; //update tail
    }
    size_++;
}



