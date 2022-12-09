#ifndef DISKS_DISKS_H
#define DISKS_DISKS_H

#include <vector>
#include <deque>
#include <ostream>
#include <functional>

using namespace std;

class Point {
public:
    int x{}, y{};

    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

    friend ostream& operator<<(ostream& os, const Point& p);

    bool operator==(const Point &rhs) const;

    bool operator!=(const Point &rhs) const;
};

deque<Point> getConvexHull(deque<Point>& points);
size_t countDisks(deque<Point>& set);

//template<typename return_value, typename parameter>
//using func = std::function<return_value(parameter)>;
//
//template<typename return_value, typename parameterT>
//size_t count_disks(func<return_value, parameterT> f, parameterT& set);

#endif //DISKS_DISKS_H
