//
// Created by 吉卓林 on 2020/10/7.
//

#include "base.h"
#include "member.h"

/*class derived : public base {
protected:
    void step_one() {std::cout << "derived::step_one" << std::endl;}
    void step_two() {std::cout << "derived::step_two" << std::endl;}
public:
    void run() {
        std::cout << "enter derived::run" << std::endl;
        step_one();
        step_two();
        std::cout << "exit derived::run" << std::endl;
    }
};*/
class derived : public base {
    member m_;
public:
    derived(bool base_th, bool member_th)
            : base(base_th), m_(member_th) {
        std::cout << "ctor of derived" << std::endl;
    }
    ~derived() {
        std::cout << "dtor of derived" << std::endl;
    }
};