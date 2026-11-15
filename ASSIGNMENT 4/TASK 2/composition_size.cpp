#include <iostream>
#include <string>
using namespace std;
struct Person { string name; int id{}; };
struct Student : virtual Person { string programme; };
struct Staff : virtual Person { string department; };
struct TeachingAssistant : Student, Staff {};
struct TeachingAssistantComposition { Student student; Staff staff; };
int main() {
    cout << "Virtual inheritance TA size: " << sizeof(TeachingAssistant) << '\n';
    cout << "Composition TA size: " << sizeof(TeachingAssistantComposition) << '\n';
    TeachingAssistant ta;
    ta.name = "Kavya";
    cout << "Shared virtual-base name: " << ta.name << '\n';
    TeachingAssistantComposition composed;
    composed.student.name = "Student identity";
    composed.staff.name = "Staff identity";
    cout << composed.student.name << " / " << composed.staff.name << '\n';
}