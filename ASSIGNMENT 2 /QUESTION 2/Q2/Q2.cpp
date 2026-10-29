#include <iostream>
int& highest(int marks[], int n) {
    int best = 0;
    for (int i = 1; i < n; ++i) if (marks[i] > marks[best]) best = i;
    return marks[best];
}
// Intentionally unsafe demonstration is omitted from execution: returning a reference
// to a local variable would create a dangling reference and undefined behaviour.
int main() {
    int marks[] = {76, 91, 84, 88, 91};
    std::cout << "Highest before moderation: " << highest(marks, 5) << '\n';
    highest(marks, 5) += 2;
    std::cout << "Highest after moderation: " << highest(marks, 5) << '\n';
    std::cout << "Array after moderation: ";
    for (int x : marks) std::cout << x << ' ';
    std::cout << '\n';
}