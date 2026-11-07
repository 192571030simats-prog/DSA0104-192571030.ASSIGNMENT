#include <iostream>
#include <stdexcept>
#include <string>

class Book {
    std::string title;
    std::string author;
    int copies;
    static int checkedCopies(int n) {
        if (n < 0) throw std::invalid_argument("number of copies cannot be negative");
        return n;
    }
public:
    Book() : Book("Untitled", "Unknown", 0) {}
    explicit Book(const std::string& t) : Book(t, "Unknown", 1) {}
    Book(const std::string& t, const std::string& a, int n)
        : title(t), author(a), copies(checkedCopies(n)) {}
    void print() const {
        std::cout << "Title: " << title << " | Author: " << author
                  << " | Copies: " << copies << '\n';
    }
};

// Demonstrates why declaration order matters: first is initialized before second.
struct OrderDemo {
    int first;
    int second;
    OrderDemo() : second(20), first(10) {}
};

int main() {
    try {
        Book empty;
        Book donated("The Selfish Gene");
        Book full("The Gene", "Siddhartha Mukherjee", 4);
        std::cout << "Default constructor: "; empty.print();
        std::cout << "Title-only constructor: "; donated.print();
        std::cout << "Parameterized constructor: "; full.print();
        OrderDemo order;
        std::cout << "Declaration-order demo: " << order.first << ' ' << order.second << '\n';
        try { Book invalid("Invalid", "Test", -2); (void)invalid; }
        catch (const std::invalid_argument& e) { std::cout << "Negative copies rejected: " << e.what() << '\n'; }
    } catch (const std::exception& e) { std::cerr << "Error: " << e.what() << '\n'; return 1; }
}
