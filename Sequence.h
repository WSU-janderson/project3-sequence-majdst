#include <cstddef>
#include <iosfwd>
#include <string>
#include <exception>

class SequenceNode {

public: //made it public to give access
    std::string item;
    //double linked list
    SequenceNode* next = nullptr; // next node pleaseee
    SequenceNode* before = nullptr; // before node pleasee

    SequenceNode() = default;

    SequenceNode(const std::string& val):item(val){}

};

//next class--> sequence class
class Sequence {
private:
    // first node pointer
    SequenceNode* head_ = nullptr;
    //last node pointer
    SequenceNode* tail_ = nullptr;
    // initialize the number of elements
    std::size_t size = 0;

    /*
     *This is a helper function to prevent to repeat the for loop everytime we are
     *looking for node
     */
    SequenceNode* nodeAt(std:: size_t idx) const;

public:
    
};