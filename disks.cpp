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

bool Point::operator<(const Point &rhs) const {
    if (x < rhs.x)
        return true;
    if (rhs.x < x)
        return false;

    return y < rhs.y;
}

bool Point::operator>(const Point &rhs) const {
    return rhs < *this;
}

bool Point::operator<=(const Point &rhs) const {
    return !(rhs < *this);
}

bool Point::operator>=(const Point &rhs) const {
    return !(*this < rhs);
}

static double isLeft(Point P0, Point P1, Point P2) {
    return (P1.x - P0.x) * (P2.y - P0.y) - (P2.x - P0.x) * (P1.y - P0.y);
}

// Melkman's algorithm: O(n) at simple polygonal cases, O(n log(h)) otherwise
// Reference: https://maxgoldste.in/melkman/
deque<Point> getConvexHull(deque<Point>& points) {
    deque<Point> result;
    //if (points.size() < 3)
    //    return points;

    if (isLeft(points[0], points[1], points[2]) > 0) {
        // Right
        result.emplace_back(points[0]);
        result.emplace_back(points[1]);
    } else {
        // Left
        result.emplace_back(points[1]);
        result.emplace_back(points[0]);
    }

    result.emplace_back(points[2]);
    result.emplace_front(points[2]);

    //if (points.size() == 3) return points;

    for (int i = 3; i < points.size(); i++) {
        int s = result.size();
        while (isLeft(points[i], result[0], result[1]) > 0 &&
               isLeft(result[s - 2], result[s - 1], points[i]) > 0) {
            i++;
            if (i > points.size() - 1)
                return result;
        }

        while (isLeft(result[s - 2], result[s - 1], points[i]) <= 0) {
            result.pop_back();
            s = result.size();
        }
        result.emplace_back(points[i]);

        while (isLeft(points[i], result[0], result[1]) <= 0)
            result.pop_front();
        result.emplace_front(points[i]);
    }

    return result;
}

// Monotone Chain algorithm: O(n log(n)).
// Notice, the Melkman's algorithm is still better at the worst case.
// Reference: https://upload.wikimedia.org/wikipedia/commons/9/9a/Animation_depicting_the_Monotone_algorithm.gif
std::vector<Point> getConvexHull(std::vector<Point>& points) {
    int n = points.size();
    int k = 0;

    std::vector<Point> H(2*n);
    std::sort(points.begin(), points.end());

    // Lower hull
    for (int i = 0; i < n; ++i)
    {
        while(k >= 2 && isLeft(H[k-2], H[k-1], points[i]) <= 0)
            k--;

        H[k++] = points[i];
    }


    // Upper hull
    for (int i = n-2, t = k+1; i >= 0; i--) {
        while (k >= t && isLeft(H[k-2], H[k-1], points[i]) <= 0)
            k--;

        H[k++] = points[i];
    }

    H.resize(k);
    return H;
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