#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <chrono>

class Time {
    int seconds;
public:
    explicit Time(int s = 0) : seconds(s < 0 ? 0 : s) {}
    Time& operator++() { ++seconds; return *this; }
    Time operator++(int) { Time old(*this); ++seconds; return old; }
    bool operator==(const Time& rhs) const { return seconds == rhs.seconds; }
    bool operator<(const Time& rhs) const { return seconds < rhs.seconds; }
    int value() const { return seconds; }
};
class Playlist {
    std::vector<std::string> tracks;
public:
    Playlist(std::initializer_list<std::string> t) : tracks(t) {}
    std::string& operator[](std::size_t i) { if (i >= tracks.size()) throw std::out_of_range("track index out of range"); return tracks[i]; }
    const std::string& operator[](std::size_t i) const { if (i >= tracks.size()) throw std::out_of_range("track index out of range"); return tracks[i]; }
    std::size_t size() const { return tracks.size(); }
};
int main() {
    Time t(5); Time a = t++; Time b = ++t;
    std::cout << "a=" << a.value() << " b=" << b.value() << " t=" << t.value() << '\n';
    Playlist playlist{"Blue in Green", "So What", "Take Five"};
    std::cout << "Track 1: " << playlist[1] << '\n';
    try { std::cout << playlist[playlist.size()] << '\n'; }
    catch (const std::out_of_range& e) { std::cout << "Range check: " << e.what() << '\n'; }
    // 59:59 + 1 second rolls to 1:00:00 when formatted as hours:minutes:seconds.
    int total = 59 * 60 + 59 + 1;
    std::cout << "Rollover: " << total / 3600 << ':' << (total / 60) % 60 << ':' << total % 60 << '\n';
    constexpr int N = 10000000;
    volatile int sink = 0;
    auto start = std::chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) { Time x(i); ++x; sink = x.value(); }
    auto mid = std::chrono::steady_clock::now();
    for (int i = 0; i < N; ++i) { Time x(i); x++; sink = x.value(); }
    auto end = std::chrono::steady_clock::now();
    std::cout << "10M prefix ns: " << std::chrono::duration_cast<std::chrono::nanoseconds>(mid-start).count() << '\n';
    std::cout << "10M postfix ns: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end-mid).count() << '\n';
    (void)sink;
}
