#include <iostream>
#include <string>
using namespace std;
class Address {
    string city; int pin;
public:
    Address(string c, int p) : city(std::move(c)), pin(p) {
        cout << "Address constructed ";
    }
    ~Address() { cout << "Address destroyed "; }
};
class Person {
protected:
    string name; int age;
    Address home;
public:
    Person(string n, int a, string city, int pin)
        : name(std::move(n)), age(a), home(std::move(city), pin) {
        cout << "Person constructed ";
    }
    virtual ~Person() { cout << "Person destroyed "; }
};
class Student : public Person {
    long long regNo;
public:
    Student(string n, int a, long long r, string c, int p)
        : Person(std::move(n), a, std::move(c), p), regNo(r) {
        cout << "Student constructed ";
    }
    ~Student() override { cout << "Student destroyed "; }
};
class Staff : public Person {
    double salary;
public:
    Staff(string n, int a, double s, string c, int p)
        : Person(std::move(n), a, std::move(c), p), salary(s) {
        cout << "Staff constructed ";
    }
    ~Staff() override { cout << "Staff destroyed "; }
};
struct VirtualPerson { VirtualPerson(){ cout << "VirtualPerson "; } };
struct VStudent : virtual VirtualPerson { VStudent(){ cout << "VStudent "; } };
struct VStaff : virtual VirtualPerson { VStaff(){ cout << "VStaff "; } };
struct TA : VStudent, VStaff { TA(){ cout << "TA "; } };
int main() {
    { Student s("Kavya", 19, 192311001, "Salem", 636001); cout << "| "; }
    cout << '\n';
    { Staff t("Ravi", 40, 50000, "Chennai", 600001); cout << "| "; }
    cout << '\n';
    { TA ta; cout << "| "; }
    cout << '\n';
}