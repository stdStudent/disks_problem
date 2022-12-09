#include "disks.h"

ostream& operator<<(ostream& os, const Point& p)
{
    os << '(' << p.x << ", " << p.y << ')';
    return os ;
}

bool Point::operator==(const Point &rhs) const {
    return x == rhs.x &&
           y == rhs.y;
}

bool Point::operator!=(const Point &rhs) const {
    return !(rhs == *this);
}

static double isLeft(Point P0, Point P1, Point P2) {
    return (P1.x - P0.x) * (P2.y - P0.y) - (P2.x - P0.x) * (P1.y - P0.y);
}

// O(n) at simple polygonal cases, O(n log(h)) otherwise
// Reference: https://maxgoldste.in/melkman/
deque<Point> getConvexHull(deque<Point>& points) {
    deque<Point> dequeue;
    //if (points.size() < 3)
    //    return points;

    if (isLeft(points[0], points[1], points[2]) > 0) {
        // Right
        dequeue.emplace_back(points[0]);
        dequeue.emplace_back(points[1]);
    } else {
        // Left
        dequeue.emplace_back(points[1]);
        dequeue.emplace_back(points[0]);
    }

    dequeue.emplace_back(points[2]);
    dequeue.emplace_front(points[2]);

    //if (points.size() == 3) return points;

    for (int i = 3; i < points.size(); i++) {
        int s = dequeue.size();
        while (isLeft(points[i], dequeue[0], dequeue[1]) > 0 &&
               isLeft(dequeue[s - 2], dequeue[s - 1], points[i]) > 0) {
            i++;
            if (i > points.size() - 1)
                return dequeue;
        }

        while (isLeft(dequeue[s - 2], dequeue[s - 1], points[i]) <= 0) {
            dequeue.pop_back();
            s = dequeue.size();
        }

        dequeue.emplace_back(points[i]);
        while (isLeft(points[i], dequeue[0], dequeue[1]) <= 0)
            dequeue.pop_front();
        dequeue.emplace_front(points[i]);
    }

    return dequeue;
}

// TODO: target complexity: O(r*n) min, O(r*n log(h)) max, r -> h/2
size_t countDisks(deque<Point>& set) {
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

//template<typename return_value, typename parameterT>
//size_t count_disks(func<return_value, parameterT> f, parameterT& set) {
//    size_t count = 0;
//
//    while (set.size() > 2) {
//        auto exclude = f(set);
//
//        for (auto& elem : exclude)
//            erase(set, elem);
//
//        ++count;
//    }
//
//    return count;
//}