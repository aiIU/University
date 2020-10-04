
#ifndef HEAD_H
#define HEAD_H

class Fractional{

public:    

   Fractional(); // конструктор по умолчанию  
   Fractional(int initNumerator, int initDenominator); //конструктор с параметрами
   Fractional(const Fractional& src);//конструктор копирования
   Fractional(int initValue);///конструктор с параметрами

    
    const Fractional simplify();

    // Перегрузка оператора 

    const Fractional operator+(const Fractional& right);
    const Fractional operator +(const int& right);

    friend Fractional operator+(int left, const Fractional& right);

    
    const Fractional operator -(const Fractional& right);
    const Fractional operator -(const int& right);
    
    friend Fractional operator-(int left, const Fractional& right);


    const Fractional operator *(const Fractional& right);
    const Fractional operator *(const int& right);
    
    const Fractional operator /(const Fractional& right);
    const Fractional operator /(const int& right);

    const Fractional operator ++(); 
    const Fractional operator --();

    const Fractional operator ++(int );
    const Fractional operator --(int initValue);

    const Fractional operator +=(const Fractional& right);          
    const Fractional operator -=(const Fractional& right);
    operator double();

    bool operator ==(const Fractional& right);
    bool operator !=(const Fractional& right);
    bool operator >(const Fractional& right)const;
    bool operator <(const Fractional& right)const;


    friend std::ostream& operator<<(std::ostream& os, const Fractional& fr);
    
private:
    int numerator;
    int denominator;
 };

#endif






























 