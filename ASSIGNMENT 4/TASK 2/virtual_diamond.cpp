#include <iostream>
using namespace std;
struct Person {
    Person() { cout << "Person "; }
    virtual ~Person() = default;
};
struct Student : virtual Person {
    Student() { cout << "Student "; }
};
struct Staff : virtual Person {
    Staff() { cout << "Staff "; }
};
struct TeachingAssistant : Student, Staff {
    TeachingAssistant() { cout << "TA "; }
};
int main() {
    TeachingAssistant ta;
    cout << '\n';
}