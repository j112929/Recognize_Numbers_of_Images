//
// Created by 吉卓林 on 2020/11/17.
//

#ifndef MY449_A_H
#define MY449_A_H


class A {


      int member;
    ~A();
public:
//    A() {
//
//    }

//    ~A();
};
void some_function() {
    A a; // line 1
    A b = a; // line 2
    b = a; // line 3
}

#endif //MY449_A_H
