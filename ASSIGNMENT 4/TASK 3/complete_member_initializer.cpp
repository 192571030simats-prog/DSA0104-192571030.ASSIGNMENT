#include <iostream>
#include <string>
using namespace std;
class Person {
protected:
    string name; int age;
public:
    Person(const string& n, int a) : name(n), age(a) {}
};
class Address {
    string city; int pin;
public:
    Address(const string& c, int p) : city(c), pin(p) {}
    string str() const { return city + "-" + to_string(pin); }
};
class Student : public Person {
    long long regNo;
    Address home;
public:
    Student(const string& n, int a, long long r, const string& city, int pin)
        : Person(n, a), regNo(r), home(city, pin) {}
    void print() const {
        cout << regNo << ' ' << name << " (" << age << ") " << home.str() << '\n';
    }
};
int main() {
    Student s("Kavya", 19, 192311001, "Salem", 636001);
    s.print();
}