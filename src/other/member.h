//
// Created by 吉卓林 on 2020/11/17.
//

#ifndef MY449_MEMBER_H
#define MY449_MEMBER_H

#include <stdio.h>
#include <iostream>

class member {
public:
    member(bool th) {
        std::cout << "ctor of member" << std::endl;
        if (th) {
            throw std::runtime_error("throw from ctor of member");
        } }
    ~member() {
        std::cout << "dtor of member" << std::endl;
    }
};


#endif //MY449_MEMBER_H
