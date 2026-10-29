#include <iostream>
#include <string>
class SavingsAccount {
    std::string accountNumber;
    double balance;
    double transactions[10]{};
    int count = 0;
    int next = 0; // circular insertion index
public:
    SavingsAccount(const std::string& number, double opening) : accountNumber(number), balance(opening) {}
    void deposit(double amount);
    bool withdraw(double amount);
    void miniStatement() const;
};
void SavingsAccount::deposit(double amount) {
    if (amount <= 0) return;
    balance += amount;
    transactions[next] = amount;
    next = (next + 1) % 10;
    if (count < 10) ++count;
}
bool SavingsAccount::withdraw(double amount) {
    if (amount <= 0 || amount > balance) return false;
    balance -= amount;
    transactions[next] = -amount;
    next = (next + 1) % 10;
    if (count < 10) ++count;
    return true;
}
void SavingsAccount::miniStatement() const {
    std::cout << "Account: " << accountNumber << "\nBalance: " << balance << "\nRecent transactions (oldest to newest):\n";
    int start = (count == 10) ? next : 0;
    for (int i = 0; i < count; ++i) std::cout << transactions[(start + i) % 10] << '\n';
}
int main() {
    SavingsAccount a("SA-1042", 1000);
    a.deposit(200); a.withdraw(50); a.deposit(75); a.withdraw(20);
    a.miniStatement();
}