#include <iostream>
using namespace std;
class Sample {
    int first;
    int second;
public:
    Sample() : second(2), first(1) {}
    void show() const { cout << first << ' ' << second << '\n'; }
};
int main() { Sample s; s.show(); }