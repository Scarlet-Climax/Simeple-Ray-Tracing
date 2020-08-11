#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H
#include <vector>
using namespace std;
#include "hitable.h"

class hitable_list : public hitable {
    vector<hitable*> lst;

   public:
    hitable_list() {}
    hitable_list(vector<hitable*> list) : lst(list) {}
    // void push_back(const hitable& _) { lst.push_back(new hitable(_)); }
    void push_back(hitable* _) { lst.push_back(_); }
    virtual bool hit(const ray& r, float tmin, float tmax, hit_record& rec) const {
        hit_record temp;
        bool hitt = 0;
        double closest = tmax;
        for (auto i : lst)
            if (i->hit(r, tmin, closest, temp)) {
                hitt = 1;
                closest = temp.t;
                rec = temp;
            }
        return hitt;
    }
};

#endif /* HITABLE_LIST_H */
