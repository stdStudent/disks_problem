#ifndef DISKS_DISKS_H
#define DISKS_DISKS_H

#include <vector>
#include <deque>
#include <ostream>
#include <algorithm>
#include <functional>

using namespace std;

class Point {
public:
    int x{}, y{};

    Point() {
        this->x = 0;
        this->y = 0;
    }

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    friend ostream& operator<<(ostream& os, const Point& p);
    bool operator==(const Point &rhs) const;
    bool operator!=(const Point &rhs) const;
    bool operator<(const Point &rhs) const;
    bool operator>(const Point &rhs) const;
    bool operator<=(const Point &rhs) const;
    bool operator>=(const Point &rhs) const;
};

deque<Point>       getConvexHull(deque<Point>&       points);
std::vector<Point> getConvexHull(std::vector<Point>& points);

// TODO: target complexity: O(r*n) min, O(r*n log(h)) max, r -> h/2
template <typename T>
size_t countDisks(T& set) {
    size_t count = 0;

    while (set.size() > 2) {
        auto exclude = getConvexHull(set);

        // FIXME: Damn, this ruins everything!
        for (auto& elem : exclude)
            erase(set, elem);

        ++count;
    }

    return count;
}

//template<typename return_value, typename parameter>
//using func = std::function<return_value(parameter)>;
//
//template<typename return_value, typename parameterT>
//size_t count_disks(func<return_value, parameterT> f, parameterT& set);

#endif //DISKS_DISKS_H
