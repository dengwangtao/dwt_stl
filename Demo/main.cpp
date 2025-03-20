#include "vector.h"
#include "util.h"
#include "astring.h"
#include "map.h"
#include "common.h"

s32 main()
{
    {
        print("Test: print raw array");
        s32 v[3] = {1, 2, 3};

        for (auto& x : v)
        {
            print("x = ", x);
        }

        print(v);
    }

    {
        print("Test: print vector");
        dwt_stl::vector<s32> v;
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
        print("Test: print vector<pair>");
        dwt_stl::vector<dwt_stl::pair<s32, dwt_stl::pair<double, dwt_stl::string>>> v;
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
        print("Test: print vector<pair<pair>>");
        dwt_stl::vector<dwt_stl::pair<s32, dwt_stl::pair<double, const char*>>> v;
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
        print("Test: print map 01");
        dwt_stl::map<s32, dwt_stl::string> mp;
        mp[1] = "hello";
        mp[2] = "world";
        mp[3] = "!";

        for (auto& x : mp)
        {
            print("val = ", x);
        }

        print(mp);
    }

    {
        print("Test: print map 02");
        dwt_stl::map<s32, dwt_stl::map<dwt_stl::string, double>> mp;
        mp[1]["hello"] = 1.2;
        mp[1]["world"] = 2.3;
        mp[2]["hello"] = 3.4;
        mp[2]["world"] = 4.5;
        mp[3]["hello"] = 5.6;
        mp[3]["world"] = 6.7;

        for (auto& x : mp)
        {
            print("val = ", x);
        }

        print(mp);
    }

    {
        print("Test: sort");
        dwt_stl::vector<s32> v {1, 7, 3, 4, 5, 6, 2, 9, 0, 8};
        dwt_stl::sort(v.begin(), v.end());
        print(v);
    }

    {
        print("Test: make_heap");
        dwt_stl::vector<s32> v {1, 7, 3, 4, 5, 6, 2, 9, 0, 8};
        dwt_stl::make_heap(v.begin(), v.end());
        print(v);
    }

    {
        print("Test: sort_heap");
        dwt_stl::vector<s32> v {1, 7, 3, 4, 5, 6, 2, 9, 0, 8};
        dwt_stl::make_heap(v.begin(), v.end());
        dwt_stl::sort_heap(v.begin(), v.end());
        print(v);
    }
    return 0;
}