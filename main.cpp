#include <iostream>
#include <vector>

#include "disks.h"

using namespace std;

template<typename T>
static void print(deque<T> const& v)
{
    for (auto i: v)
        std::cout << i << endl;

    std::cout << std::endl;
}

int main() {
    deque<Point> set{ {0, 3}, {2, 2}, {1, 1}, {2, 1}, {3, 4},
                       {3, 0}, {0, 0}, {3, 3}, {1, 1}, {4,3} };

    print(getConvexHull(set));
    cout << countDisks(set) << endl;

//    auto CH_func = func<deque<Point>, deque<Point>&>(getConvexHull);
//    cout << count_disks(CH_func, set) << endl;

    return 0;
}
