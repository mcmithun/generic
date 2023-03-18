/* testing class for quick sorts
 * Used in realtime with cutom types
 * By: Mithun C
 */

#ifndef TESTMANUERS_H
#define TESTMANUERS_H
#include <iostream>
#include <ostream>
#include <vector>

class TestManuers
{
    int uid;
    int start;
    int end;
public:
    TestManuers(int _uid, int _start, int _end): uid(_uid), start(_start), end(_end) {}

    // Overload comparison operators, currently uid is only checked
    // Near future tuple shall be used, to incorporate the comparision
    // along with start and end, unfortunately after c++17 comparison operators
    // for tuple goes deprecated :( .
    bool operator>(const TestManuers &rhs){
        return (this->uid > rhs.uid);
    }

    bool operator>=(const TestManuers &rhs){
        return (this->uid >= rhs.uid);
    }

    bool operator<(const TestManuers &rhs){
        return (this->uid < rhs.uid);
    }

    bool operator<=(const TestManuers &rhs){
        return (this->uid <= rhs.uid);
    }

    bool operator==(const TestManuers &rhs){
        return (this->uid == rhs.uid);
    }

    bool operator!=(const TestManuers &rhs){
        return (this->uid != rhs.uid);
    }

    friend std::ostream& operator<<(std::ostream& stream, const std::vector<TestManuers> &arr){
        for(auto elm: arr){
            stream << "["<<elm.uid << ", "<<elm.start<<", " <<elm.end<< "] ";
        }
        return stream;
    }
};

#endif // TESTMANUERS_H
