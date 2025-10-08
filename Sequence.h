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
    //Rule of Three--> ensure object created, copied and destroyed
    //no memory leak
    explicit Sequence(std::size_t size=0); //create

    Sequence(const Sequence& other); //copy

    ~Sequence(); //delete

    Sequence& operator = (const Sequence& rhs); //right hand side copy

    // giving access to element in linked list

    std::string& operator[](std::size_t position); //access to item(index)

    std::string front() const; //checking sequence-->if front empty-->exception

    std::string back() const; //checking sequence-->if back empty-->exception

    //Adding & Removing

    void push_back(std::string item); //append to sequence

    void pop_back(); //delete last item

    /*
     * the main difference between linked list and array--> shift right
     */

    void insert(std::size_t position, std::string item); //insert to position

    void erase(std::size_t position); //remove items at position

    void erase(std::size_t position, std::size_t count); //remove the count item

    // for releasing memory
    void clear();
    //checking if the sequence is empty or have elements
    void empty() const;
    // overall size of the sequence
    std::size_t size() const;
/*
 * In here, we should have access to private part, friend gives access to that part.
 */
    friend std::ostream& operator<<(std::ostream& os, const Sequence& s);



};