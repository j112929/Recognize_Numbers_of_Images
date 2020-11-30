//
// Created by 吉卓林 on 2020/10/7.
//

#ifndef MY449_COLLECTION_H
#define MY449_COLLECTION_H

#include <stdio.h>
#include <vector>
class collection {
};

class my_array :public collection {
    std::vector<int> vec_;
};

void test() {
    collection *p = new my_array;
    delete p;
}

#endif //MY449_COLLECTION_H
