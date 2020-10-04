
/*ifndef BinaryTree_H
#define BinaryTree_H*/

#include <stdio.h>
//#include "Fractional.h"

struct elemofTree{ 
    Fractional value; //то что записываем в дерево
    elemofTree *left = NULL; // указатели на новые звенья
    elemofTree *right = NULL;
};

class BinaryTree{
private:
    elemofTree head; //корень
public:
    BinaryTree(int value);

    BinaryTree(Fractional& headValue);
   //void push(Fractional& value);
    ~BinaryTree();
        
    
};
