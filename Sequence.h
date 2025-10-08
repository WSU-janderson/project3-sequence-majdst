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