#include "Sequence.h"
#include <stdexcept>
#include <ostream>
#include <algorithm>

using std::size_t;
using std::string;
using std::runtime_error;
using std:: out_of_range;


//given index-->find the raw pointer to the node
SequenceNode* Sequence::nodeAt(size_t idx) const {
    if (idx >= size_) {
        throw out_of_range("index out of range");
    }
}