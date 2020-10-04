
#ifndef FRACTION_H
#define FRACTION_H

#include "head.h"
    //конструктор по умолчанию
    Fractional::Fractional(){
        numerator = 1;
        denominator = 1;
    }
    //конструктор с параметрами (числитель,знаменатель)
    Fractional::Fractional(int initNumerator, int initDenominator){
        numerator = initNumerator;
        if (initDenominator != 0)
            denominator = initDenominator;
        else{
            std::cout << "Неверные входные данные, знаменатель изменен на 1." << std::endl;
            denominator = 1;
        }
    }
    //Конструктор копирования
    Fractional::Fractional (const Fractional& src) {
        numerator = src.numerator;
        denominator = src.denominator;
    }
    //конструктор с параметрами (базовый тип)
    Fractional::Fractional(int initValue){
        numerator = initValue;
        denominator = 1;
    }
    //Функция поиска НОД
    int gcd (int a, int b){ 
         return b ? gcd(b, a % b) : a;
    }
    //Функция для сокращения дроби
    Fractional const Fractional::simplify(){
        //В reduction записывается НОД от итерации, num и  den - промежуточные стадии сокращения,
            //reduction = 1 => сокращать нечего
        int reduction = 0;
        int num = numerator,
            den = denominator;
        while (reduction != 1) {
            reduction = gcd(num, den);
            num /= reduction;
            den /= reduction;
        }
        return Fractional(num, den); 
    }

    //Перегрузка оператора 

    Fractional const Fractional::operator+(const Fractional& right){
        return Fractional(right.denominator*numerator + denominator*right.numerator, 
                                denominator*right.denominator).simplify();
    }
    // base type right+
     Fractional const Fractional::operator +(const int& right) {
        return Fractional(numerator + denominator * right,                                              
                                denominator).simplify();
    }
     // base type left+
    Fractional operator+(int left, const Fractional& right){
    return Fractional(right.numerator + right.denominator * left, 
                                 right.denominator).simplify();
    }
  
    Fractional operator-(int left, const Fractional& right){
    return Fractional(left * right.denominator - right.numerator,
                                 right.denominator).simplify();
    }
    // base type right-
     Fractional const Fractional:: operator -(const Fractional& right){
        return Fractional(right.denominator*numerator - denominator*right.numerator,
                                denominator*right.denominator).simplify();
    }
    // base type left-
     Fractional const Fractional:: operator -(const int& right){
        return Fractional(numerator - denominator *right,
                                denominator).simplify();
    }
    

    Fractional  const Fractional:: operator *(const Fractional& right){
        return Fractional(numerator *right.numerator,
                                denominator*right.denominator).simplify();
    }
    // base type right 
     Fractional const Fractional:: operator *(const int& right){
        return Fractional(numerator * right,
                                denominator).simplify();
    }
    

     Fractional const Fractional:: operator /(const Fractional& right){
        return Fractional(numerator *right.denominator, 
                                denominator*right.numerator).simplify();
    }

    // base type right 
    Fractional const Fractional:: operator /(const int& right){
        return Fractional(numerator *right, 
                                numerator * right).simplify();
    }

    // PREFIX
    Fractional const Fractional::operator ++(){
        this->numerator +=1;
        return *this;
    }

    Fractional const Fractional::operator --(){
        this->numerator -=1;
        return *this;
    }

    // POSTFIX
    Fractional const Fractional::operator ++(int ){
        Fractional temp(*this);
        this->numerator +=1;
        return temp;
    }
    Fractional const Fractional::operator --(int initValue){
        Fractional temp(*this);
        this->numerator -=1;
        return temp;
    }

    Fractional const Fractional::operator +=(const Fractional& right){
        return Fractional(right.denominator*numerator + denominator*right.numerator, 
                                denominator*right.denominator).simplify();
    }

    Fractional const Fractional::operator -=(const Fractional& right){
        return Fractional(right.denominator*numerator - denominator*right.numerator, 
                                denominator*right.denominator).simplify();
    }
    Fractional::operator double(){
        return (double)numerator/(double)denominator;
    }

    /* int operator[](int index) {
        return (index == 0) ? numerator : denominator;
    }
    */

    bool Fractional:: operator ==(const Fractional& right){
        return (this->numerator*right.denominator == right.numerator *denominator && 
                                 this->denominator *right.denominator == right.denominator *denominator);
 
    }

    bool Fractional::operator !=(const Fractional& right){
                return !(this->numerator*right.denominator == right.numerator *denominator && 
                                 this->denominator *right.denominator == right.denominator *denominator);
    }

    bool Fractional::operator >(const Fractional& right)const{
        return (this->numerator*right.denominator > right.numerator *denominator &&
                                 this->denominator *right.denominator == right.denominator *denominator);

    }
    bool Fractional::operator <(const Fractional& right)const{
        return (this->numerator*right.denominator < right.numerator *denominator &&
                                 this->denominator *right.denominator == right.denominator *denominator);
    }

    std::ostream& operator<<(std::ostream& os, const Fractional& fr) {
        os << fr.numerator << "/" << fr.denominator;
        return os;
    }

    
#endif