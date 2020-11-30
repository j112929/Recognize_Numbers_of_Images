#include <algorithm>
#include <iostream>

/*
//
// Created by 吉卓林 on 2020/10/7.
//
//#include <stdio.h>
#include "test.h"
//#include <string.h>
#include <string>
#include "derived.cpp"

using namespace std;
int main(){
//    test test;
//    string *s = string("1");
//    test.find_or_throw(s);
    derived d;
    derived *p = &d;
    p->run();
}
*/

template<class T>
class shared_ptr {
    T *p_;
    int *count_;
public:
    shared_ptr()
            : p_(NULL), count_(NULL) {
    }

    ~shared_ptr() {
        if (count_ != NULL) {
            --*count_;
            if (*count_ == 0) {
                delete p_;
                delete count_;
            }
        }
    }

    explicit shared_ptr(T *p) {
        try {
            count_ = new int(1); // initialize the count to 1
            p_ = p;
        }
        catch (...) {
            delete p;
            throw;
        }
    }

    shared_ptr(const shared_ptr<T> &sp)
            : p_(sp.p_), count_(sp.count_) {
        ++*count_;
    }

    shared_ptr<T> &operator=(shared_ptr<T> sp) {
        swap(sp);
        return *this;
    }

    void swap(shared_ptr<T> &sp) {
        std::swap(p_, sp.p_);
        std::swap(count_, sp.count_);
    }

    T *operator->() const {
        assert(p_ != NULL);
        return p_;
    }
}; // class shared_ptr<T>

struct B;

struct A {
    shared_ptr<B> b_of_A;

    A() {
        std::cout << "ctor of A" << std::endl;
    }

    ~A() {
        std::cout << "dtor of A" << std::endl;
    }
}; // struct A

struct B {
    shared_ptr<A> a_of_B;

    B() {
        std::cout << "ctor of B" << std::endl;
    }

    ~B() {
        std::cout << "dtor of B" << std::endl;
    }
}; // struct B

void test1() {
    std::cout << "======== test1 ========" << std::endl;

    shared_ptr<A> pa(new A);
    shared_ptr<B> pb(new B);

    pa->b_of_A = pb;
    pb->a_of_B = pa;
}

void test2() {
    std::cout << "======== test2 ========" << std::endl;

    shared_ptr<A> pa(new A);
    shared_ptr<B> pb(new B);

    pa->b_of_A = pb;
}

void test3() {
    std::cout << "======== test3 ========" << std::endl;

    shared_ptr<A> pa(new A);
    shared_ptr<B> pb(new B);

    pb->a_of_B = pa;
}

void test4() {
    std::cout << "======== test4 ========" << std::endl;

    shared_ptr<A> pa(new A);
    shared_ptr<B> pb(new B);
}

int main() {
    /*try {
        derived d(true, true);
    }
    catch (std::exception &e) {
        std::cout << e.what() << std::endl;
    }*/
//    derived d;
//    base *p = &d;
//    p->run();
//    base b;
//    std::string &a = b.get_hello();
//    std::string s = std::to_string(&a);
//    printf("----%s\n", std::string(&a));
    test1();
    test2();
    test3();
    test4();
    return 0;
}
