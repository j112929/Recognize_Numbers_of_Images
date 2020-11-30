//
// Created by 吉卓林 on 2020/10/7.
//

#ifndef MY449_BASE_H
#define MY449_BASE_H

#include <stdio.h>
#include <iostream>

class base {
protected:
//    virtual void step_one() { std::cout << "base::step_one()" << std::endl; }

//    virtual void step_two() { std::cout << "base::step_two()" << std::endl; }

public:
    base(bool th) {
        std::cout << "ctor of base" << std::endl;
        if (th) {
            throw std::runtime_error("throw from ctor of base");
        } }
    ~base() {
        std::cout << "dtor of base" << std::endl;
    }
    /*void run() {
        std::cout << "enter base::run" << std::endl;

        step_one();

        step_two();

        std::cout << "exit base::run" << std::endl;
    }*/
//    std::string &get_hello() ;

};

#endif //MY449_BASE_H
