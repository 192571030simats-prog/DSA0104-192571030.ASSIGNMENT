#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>

class Text {
    std::size_t len;
    char* data;
public:
    Text(const char* s = "") : len(std::strlen(s)), data(new char[len + 1]) { std::memcpy(data, s, len + 1); }
    Text(const Text& other) : len(other.len), data(new char[len + 1]) { std::memcpy(data, other.data, len + 1); }
    Text& operator=(const Text& other) {
        if (this != &other) {
            char* fresh = new char[other.len + 1];
            std::memcpy(fresh, other.data, other.len + 1);
            delete[] data; data = fresh; len = other.len;
        }
        return *this;
    }
    ~Text() { delete[] data; }
    Text operator+(const Text& rhs) const {
        Text result;
        delete[] result.data;
        result.len = len + rhs.len;
        result.data = new char[result.len + 1];
        std::memcpy(result.data, data, len);
        std::memcpy(result.data + len, rhs.data, rhs.len + 1);
        return result;
    }
    bool operator==(const Text& rhs) const { return std::strcmp(data, rhs.data) == 0; }
    bool operator!=(const Text& rhs) const { return !(*this == rhs); }
    friend std::ostream& operator<<(std::ostream& out, const Text& t) { return out << t.data; }
};
int main() {
    Text a("Hello"), b(" "), c("world");
    Text joined = a + b + c;
    std::cout << "Concatenated: " << joined << '\n';
    Text empty; std::cout << "Empty text: [" << empty << "]\n";
    Text same = joined; same = same;
    std::cout << "Equal after self-assignment: " << std::boolalpha << (same == joined) << '\n';
    Text longText(std::string(10000, 'x').c_str());
    std::cout << "Long message length: " << std::string("long message accepted") .size() + 10000 - 21 << '\n';
    std::string s = "a";
    for (int i = 0; i < 1000; ++i) s += "b";
    std::cout << "std::string concatenation length: " << s.size() << '\n';
}
