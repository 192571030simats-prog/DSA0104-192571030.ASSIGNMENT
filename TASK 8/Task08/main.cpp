#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
int main(){ std::istringstream input("abc\n17\n"); int hour{}; input >> hour; if(input.fail()){ std::cout << "Invalid hour input detected\n"; input.clear(); std::string bad; input >> bad; std::cout << "Discarded invalid token: " << bad << '\n'; input >> hour; } std::cout << "Recovered hour: " << hour << '\n'; std::cout << "Formatted fare: Rs " << std::fixed << std::setprecision(2) << 36.0 << '\n'; }
