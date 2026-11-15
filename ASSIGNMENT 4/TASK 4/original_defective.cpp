#include <iostream>
using namespace std;
class Account {
public:
    double rate() const { return 3.5; }
    ~Account() { cout << "Account destructor\n"; }
};
class SeniorAccount : public Account {
    double* history = new double[100];
public:
    double rate() const { return 4.0; }
    ~SeniorAccount() {
        delete[] history;
        cout << "SeniorAccount destructor; history released\n";
    }
};
int main() {
    Account* accounts[2] = {new Account, new SeniorAccount};
    for (Account* a : accounts) cout << a->rate() << '\n';
    for (Account* a : accounts) delete a; // Undefined behavior: non-virtual base destructor.
    Account sliced = SeniorAccount();
    cout << sliced.rate() << '\n';
}