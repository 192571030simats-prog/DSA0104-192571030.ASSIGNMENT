#include <iostream>
#include <string>

class Event {
    std::string name;
    int rows, seatsPerRow;
    char** seats;
    int booked = 0;
public:
    Event(const std::string& eventName, int r, int s)
        : name(eventName), rows(r > 0 ? r : 0), seatsPerRow(s > 0 ? s : 0), seats(nullptr) {
        if (rows > 0 && seatsPerRow > 0) {
            seats = new char*[rows];
            int made = 0;
            try {
                for (; made < rows; ++made) seats[made] = new char[seatsPerRow]{};
            } catch (...) {
                while (made > 0) delete[] seats[--made];
                delete[] seats; throw;
            }
        }
        std::cout << "Constructed " << name << " (" << rows << 'x' << seatsPerRow << ")\n";
    }
    ~Event() {
        if (seats) {
            for (int r = 0; r < rows; ++r) delete[] seats[r];
            delete[] seats;
        }
        std::cout << "Destroyed " << name << "; booked seats=" << booked << '\n';
    }
    bool book(int r, int s) {
        if (r < 0 || r >= rows || s < 0 || s >= seatsPerRow || seats[r][s]) return false;
        seats[r][s] = 1; ++booked; return true;
    }
    bool cancel(int r, int s) {
        if (r < 0 || r >= rows || s < 0 || s >= seatsPerRow || !seats[r][s]) return false;
        seats[r][s] = 0; --booked; return true;
    }
};

int main() {
    std::cout << "-- stack object --\n";
    Event morning("MorningShow", 2, 3); morning.book(0, 1); morning.cancel(0, 1); morning.book(1, 2);
    std::cout << "-- block object --\n";
    { Event afternoon("AfternoonShow", 1, 2); afternoon.book(0, 0); }
    std::cout << "-- heap object --\n";
    Event* evening = new Event("EveningShow", 2, 2); evening->book(1, 1); delete evening;
    std::cout << "-- zero rows --\n";
    Event empty("NoSeats", 0, 10);
    std::cout << "Seat map payload examples (char bytes): "
              << 10*20 << ", " << 100*200 << ", " << 1000*2000 << '\n';
}
