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
//delete last item
void Sequence::pop_back() {
    if (empty()) {throw runtime_error("Empty->pop_back()");}
    SequenceNode* to_delete = tail_;

    if (size_ == 1) {
        //become --> empty list
        head_ = tail_ = nullptr;
    } else {
        //like python, new is the node before old one
        tail_ = tail_ ->before;
        tail_->next = nullptr;
    }
    delete to_delete; //manually deleting and making memory free
    --size_;
    /*
     * Memory leak: node is removed from linked list, but its memory block
     * remains reserved and unusable
     */
}
//Insert new at position
void Sequence::insert(size_t position, string item) {
    if (position > size_){throw out_of_range("Error-out of range");}

    if (position == size_) {
        push_back(item);
        return;
    }
    //new node
    SequenceNode* n = new SequenceNode(item);
    //inserting new node as head
    if (position == 0) {
        n->next = head_;
        head_->before = n;
        head_ = n;
    }else {
        //insert in the middle

        SequenceNode* after = nodeAt(position);
        SequenceNode* before = after->before; //this node -->new node

        //link
        n->next = after;
        n->before = before;

        //reroute
        before->next = n;
        after->before = n;
    }

    size_++;


}

//remove items
void Sequence::erase(size_t position) {

    SequenceNode* to_delete = nodeAt(position);

    //head adjust-->head delete
    if (to_delete == head_) {head_ = to_delete->next;}
    //tail adjust-->tail delete
    if (to_delete == tail_){tail_ = to_delete->before;}

    //connecting after delete --> before --> next
    if (to_delete->before){to_delete->before->next = to_delete->next;}
    //connecting after delete --> next -->before
    if (to_delete->next){to_delete->next->before = to_delete->before;}

    delete to_delete;
    size_--;
}

void Sequence::erase(size_t position, size_t count) {

    //boundary checking
    if (position >= size_ || count == 0 || position + count > size_) {
        throw out_of_range("Error--> Erase (location-count)");
    }

    //head finder point to delete
    SequenceNode* start_node = nodeAt(position);
    SequenceNode* end_node = start_node;

    //tail finder point to delete
    for (size_t i = 1; i < count; i++){end_node = end_node->next;}

    SequenceNode* before_start = start_node->before;
    SequenceNode* after_end = end_node->next;

    //connecting the nodes
    if (before_start) {
        before_start -> next = after_end;
    }else {
        head_ = after_end; // this point --> start
    }

    if (after_end) {
        after_end->before = before_start;
    }else {
        tail_ = before_start; // this point --> end
    }

    // manually deleting all the nodes as requested

    SequenceNode* current = start_node;
    for (size_t i = 0; i<count; i++) {
        SequenceNode* next_to_delete = current->next;
        delete current;
        current = next_to_delete;
    }

    size_ -= count;
}
/*
 * https://youtube.com/shorts/dfyM-yRTAZY?si=b8nFoXlH5d7hvV3S
 * https://youtube.com/shorts/fyLKvGt0ZrM?si=8KTVXvis77roIcoN
 */



