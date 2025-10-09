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
Sequence::Sequence(const Sequence& other) : head_(0), tail_(0), size_(0) {

    SequenceNode* current = other.head_;
    while (current != nullptr) {
        push_back(current->item);
        current = current->next;
    }
}
