#include "vector.h"
#include "util.h"
#include "astring.h"

int main()
{
    {
        dwt_stl::vector<int> v;
        v.push_back(1);
        v.push_back(2);
        v.push_back(3);

        for (auto& x : v)
        {
            print("x = ", x);
        }

        print(v);
    }

    {
        dwt_stl::vector<dwt_stl::pair<int, double>> v;
        v.emplace_back(1, 1.2);
        v.emplace_back(2, 3.4);
        v.emplace_back(3, 5.6);

        for (auto& x : v)
        {
            print("val = ", x);
        }

        print(v);
    }
    return 0;
}