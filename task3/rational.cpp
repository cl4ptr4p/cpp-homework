//
// Created by Andrey on 08.04.2016.
//

#include "rational.h"

rational::rational(int arg){
    num = arg;
    denom = 1;
}

rational :: rational(int first, int second){
    num = first;
    denom = second;
    simplify(num, denom);
}

int rational::getDenom()const{
    return denom;
}

int rational::getNum()const{
    return num;
}

int rational::gcd(int a, int b){
    int t;
    while(b){
        a %= b;
        t = a;
        a = b;
        b = t;
    }
    return a;
}

void rational::simplify(int &a, int &b){
    int tmp = gcd(a, b);
    while(tmp != 1) {
        a /= tmp;
        b /= tmp;
        tmp = gcd(a, b);
    }
    return;
}

rational rational::operator+(rational const &a)const{
    int fir = a.num * denom + num * a.denom;
    int sec = denom * a.denom;
    simplify(fir, sec);
    return rational(fir, sec);
}

rational rational::operator-(rational const &a) const {
    int fir = - a.num * denom + num * a.denom;
    int sec = denom * a.denom;
    simplify(fir, sec);
    return rational(fir, sec);
}

rational rational::operator*(rational const &a) const {
    int fir = a.num * num;
    int sec = denom * a.denom;
    simplify(fir, sec);
    return rational(fir, sec);
}

rational rational::operator/(rational const &a) const {
    int fir = num * a.denom ;
    int sec = denom * a.num;
    simplify(fir, sec);
    return rational(fir, sec);
}
