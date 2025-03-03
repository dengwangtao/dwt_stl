#include "vector.h"
#include "util.h"
#include "astring.h"
#include "map.h"

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
        dwt_stl::vector<dwt_stl::pair<int, dwt_stl::pair<double, dwt_stl::string>>> v;
        v.push_back({1, {2.3, "hello"}});
        v.push_back({2, {4.5, "world"}});
        v.push_back({3, {6.7, "!"}});

        for (auto& x : v)
        {
            print("val = ", x);
        }

        print(v);
    }

    {
        dwt_stl::vector<dwt_stl::pair<int, dwt_stl::pair<double, const char*>>> v;
        v.push_back({1, {2.3, "hello"}});
        v.push_back({2, {4.5, "world"}});
        v.push_back({3, {6.7, "!"}});

        for (auto& x : v)
        {
            print("val = ", x);
        }

        print(v);
    }

    {
        dwt_stl::map<int, dwt_stl::string> mp;
        mp[1] = "hello";
        mp[2] = "world";
        mp[3] = "!";

        for (auto& x : mp)
        {
            print("val = ", x);
        }

        print(mp);
    }
    return 0;
}