

#include <stdio.h>
#include <iostream>

/*class BinaryTree{
private:
    elemofTree head; 
public:
BinaryTree(int value){
    head.value = value;
    head.right = NULL;
    head.left = NULL;
 }
/* BinaryTree::BinaryTree(Fractional& headValue){
   head = headValue;  
}*/

/* int push(int value){

    elemofTree *newElem = new elemofTree;
    (*newElem).value = value;
    (*newElem).left = NULL;
    (*newElem).right = NULL;
    
    if ((*newElem).value > head.value)    
        head.right = newElem;
    else
        head.left = newElem;
     return newElem;
    }*/
    
//     elemofTree *first(int value){
//         elemofTree *newElem = new elemofTree;
//         newElem->value = value;
//         newElem->left = NULL;
//         newElem->right = NULL;
//         return elemofTree;

//     }



int tabs = 1;

// Определение узла для дерева
struct elemofTree {
    int value; 
    elemofTree* left;
    elemofTree* right;
};
class BinaryTree{
private:

// Функция создания нового узла 
elemofTree* GetNewElem(int value) {
    elemofTree* newElem = new elemofTree();//выделяем память под указатель на структуру
    (*newElem).value = value;//разыменовываем указатель и получаем доступ к полю нач.значения
    newElem->left = NULL;
    newElem->right = NULL;
    return newElem;
}
// Чтобы вставить данные, возвращаем адрес корневого узла
elemofTree* push(elemofTree* root,int value) {
    if(root == NULL) { //-если корень пуст
        root = GetNewElem(value);// кладем новое значение
// если данные для вставки меньше, вставляем в левое поддерево
    }else if(value <= root->value) {
        root->left = push(root->left,value);
    }
    //  вставить в правое поддерево.
    else {
        root->right = push(root->right,value);
    }
    return root;
}

// Для поиска элемента возвращает true, если элемент найден
bool Search(elemofTree* root,int value) {
    if(root == NULL){
        return false;
    }
    else if(root->value == value) {
        return true;
    }
    else if(value <= root->value) {
        return Search(root->left,value);
    }
    else {
        return Search(root->right,value);
    }
}
//Функция вывода дерева
void print(elemofTree *newElem){
 if (!newElem) 
    return; //Если ветки не существует - выходим. Выводить нечего
 
 //Иначе увеличим счетчик рекурсивно вызванных процедур
 tabs++;  
 print(newElem->left); //Выведем ветку и ее подветки слева
    for (int i = 0; i < tabs; i++)
        std::cout << " "; //Потом отступы
        std::cout << newElem->value << std::endl;
        print(newElem->right);//И ветки, что справа

 
 tabs--; //После уменьшим кол-во отступов
 return;
}

int main(){
    elemofTree* root = NULL; 

    //std::cin >> root->value;
    

    root = push(root,25); 
    root = push(root,20);
    root = push(root,22);
    root = push(root,30);
    root = push(root,-1);
    root = push(root,-2);
    root = push(root,20);
          
    int number;
    std::cout<<"Enter number be searched\n";
    std::cin>>number;
    //If number is found, print "FOUND"
    if(Search(root,number) == true){
        std::cout<<"Found\n";
    }else{ 
        std::cout<<"Not Found\n";
    }
    print (root);
return 0;
}

 