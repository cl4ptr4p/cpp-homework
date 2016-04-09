//
// Created by Andrey on 08.04.2016.
//

#ifndef TASK3_RATIONAL_RATIONAL_H
#define TASK3_RATIONAL_RATIONAL_H

#endif //TASK3_RATIONAL_RATIONAL_H


#pragma once

class rational {
public:
    rational(int);
    rational(int, int);
    int getNum() const;
    int getDenom() const;
    rational operator+(rational const &a) const;
    rational operator-(rational const &a) const;
    rational operator*(rational const &a) const;
    rational operator/(rational const &a) const;
private:
    int num, denom;
    static int gcd(int, int);
    static void simplify(int&, int&);
};
