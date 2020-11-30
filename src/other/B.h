//
// Created by 吉卓林 on 2020/11/17.
//

#ifndef MY449_B_H
#define MY449_B_H


class B {
    B &operator=(const B &);
};
class A
{
    B member;
};
void some_function() {
    A a; // line 1
    A b = a; // line 2
    b = a; // line 3
}

#endif //MY449_B_H
