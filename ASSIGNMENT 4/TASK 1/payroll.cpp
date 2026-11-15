#include <iostream>
#include <memory>
#include <string>
#include <vector>
using namespace std;

class Staff {
protected:
    string name;
    int id;
    double basic;
public:
    Staff(string n, int i, double b) : name(std::move(n)), id(i), basic(b) {}
    virtual double pay() const = 0;
    virtual void show() const {
        cout << name << " (" << id << "): " << pay() << '\n';
    }
    virtual ~Staff() = default;
};
class Professor : public Staff {
    double research;
public:
    Professor(string n, int i, double b, double r)
        : Staff(std::move(n), i, b), research(r) {}
    double pay() const override { return basic * 1.42 + research; }
};
class LabAssistant : public Staff {
public:
    LabAssistant(string n, int i, double b) : Staff(std::move(n), i, b) {}
    double pay() const override { return basic * 1.42; }
};
class GuestFaculty : public Staff {
    double hours, rate;
public:
    GuestFaculty(string n, int i, double h, double r)
        : Staff(std::move(n), i, 0), hours(h), rate(r) {}
    double pay() const override { return hours * rate; }
};
int main() {
    vector<unique_ptr<Staff>> staff;
    staff.push_back(make_unique<Professor>("Anita", 101, 50000, 5000));
    staff.push_back(make_unique<LabAssistant>("Bala", 102, 30000));
    staff.push_back(make_unique<GuestFaculty>("Charan", 103, 20, 800));
    for (const auto& person : staff) person->show();
}