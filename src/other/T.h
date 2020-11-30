//
// Created by 吉卓林 on 2020/11/17.
//

#ifndef MY449_T_H
#define MY449_T_H


#include <cstddef>

class T {
    T(int i) {

    }

    T create(size_t n);
    bool condition_one(T t);
    bool condition_two(const T &t);
    void modify(T &t);
    T generate(size_t n) {
        T a(1); //line 0
        T b = create(n);//line 1
        while (!condition_one(b))	{	//	line	2
            modify(b);	//	line	3
            if (condition_two(b))	//	line	4
                break;
        }
        return b;
    }
};


#endif //MY449_T_H
