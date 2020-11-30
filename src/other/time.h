//
// Created by 吉卓林 on 2020/10/7.
//

#ifndef MY449_TIME_H
#define MY449_TIME_H

class time {
    int hour, min, sec;
public:
    bool set(int h, int m, int s);

    int get_hour() const;

    int get_min() const;

    int get_sec() const;
};

#endif //MY449_TIME_H
