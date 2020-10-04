
#include <stdio.h>
#include <iostream>

#include "fraction.h"
#include "tree.hpp"

using namespace std;


template <class T>
void print(Tree<T> &tree){
	Node<Fractional> *temp_ptr;
	for (int i = 0; i < tree.size(); ++i){
		temp_ptr = tree.get(i);
		if (temp_ptr) {
			cout << *(temp_ptr->data()) << endl;
		}
	}

}

int main(){
  
    Fractional frac1(1,4);
    Fractional frac2(1,4);
    Fractional frac3(2);
    Fractional frac4(2,3);
    Fractional frac5(1,3);
  

    Fractional sum = frac1 + frac2;
    Fractional sum1 = frac1 + frac3;
    Fractional sum2 = frac3 + frac2;
    cout<<"Addition operation:"<< endl;
    cout<< frac1 << " + " << frac2 <<" = "<< sum<< endl;

    cout<< frac1 << " + " << frac3 <<" = "<< sum1<<endl;

    cout<< frac3 << " + " << frac2 <<" = "<< sum2<<endl;


    Fractional sub = frac2 - frac1;
    Fractional sub1 = frac1 - frac3;
    Fractional sub2 = frac3 - frac2;
    cout<<"Subtraction operation:"<<endl;
    cout<< frac2 << " - " << frac1 <<" = "<< sub<<endl;

    cout<< frac1 << " - " << frac3 <<" = "<< sub1<<endl;

    cout<< frac3 << " - " << frac2 <<" = "<< sub2<<endl;


    Fractional mult = frac2 * frac1;
    Fractional mult1 = frac1 * frac3;
    Fractional mult2 = frac3 * frac2;
    cout<<"Multiplication operation:"<<endl;
    cout<< frac2 << " * " << frac1 <<" = "<< mult <<endl;

    cout<< frac1 << " * " << frac3 <<" = "<< mult1<<endl;

    cout<< frac3 << " * " << frac2 <<" = "<< mult2<<endl;


    Fractional div = frac2 / frac1;
    Fractional div1 = frac1 / frac3;
    Fractional div2 = frac3 / frac2;
    cout<<"Division operation:"<<endl;
    cout<< frac2 << " / " << frac1 <<" = "<< div <<endl;

    cout<< frac1 << " / " << frac3 <<" = "<< div1<<endl;

    cout<< frac3 << " / " << frac2 <<" = "<< div2<<endl;


    cout << "Decrement operation:" << endl;
    cout << "--" << frac4;
    Fractional inc = --frac4;
    cout<< " = " << inc <<endl;

    cout << "Increment operation:" << endl;
    cout << "++" << frac4;
    Fractional dec = ++frac4;
    cout<< " = " << dec <<endl;

    cout << "Postfix Increment operation:" << endl;
    cout << frac4 << "--";
    Fractional dec1 = frac4--;
    cout << " = " << dec1 <<endl;
    cout<<"recall "<< frac4-- << endl;   


    cout << "Postfix Increment operation:" << endl;
    cout << frac1 << "++";
    Fractional dec2 = frac1++;
    cout << " = " << dec2 << endl;
    cout<<"recall "<< frac1++ << endl;   



    cout << "Comparison operation:" << endl;
    cout.setf(ios::boolalpha);
    bool x = frac1 != frac2;
    cout << frac1 << "!=" << frac2 << " - " << x << endl;

    bool y = frac3 == frac2;
    cout << frac3 << "==" << frac2 << " - " << y << endl;

    bool z = frac3 > frac2;
    cout << frac3 << ">" << frac2 << " - " << z << endl;

    bool k = frac3 < frac2;
    cout << frac3 << "<" << frac2 << " - " << k << endl;

    double num = (double)frac5;
    cout<< "double num:" << num << endl;


    Fractional frac6(1,2);//0.5
    Fractional frac7(1,4);//0.25
    Fractional frac8(1,5);//0.2
    Fractional frac9(1,1);//1

	Tree<Fractional>tree;
	tree.add(frac6);
    tree.add(frac7);
    tree.add(frac8);
    tree.add(frac9);
    print(tree);
    cout << "\n";
    
    tree.remove(frac8);
	print(tree);
    
    

	// tree.remove();
	// print(tree);

    return 0;
}

