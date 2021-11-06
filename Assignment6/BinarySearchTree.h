// Assignment #6
// Name: Helin Wang
// ASU Email Address: hwang438@asu.edu
/* Description: This is a programming assignment.You will develop a binary search tree with some of its operations.
You need to implement a data structure to represent a node.Each node represents a Cluband should have data fields containing a club nameand a university name. (its key will be a combination of its club nameand university name),
its parent node called "parent", its left child node called "left", and its right child node called "right". Using the nodes above, you need to implement a binary search tree using their keys.
When you compare two nodes, compare their university names first in alphabetical order(each character's ASCII number, you can use compare( ) function for the strings). If their university names are the same, then compare their club names.
Your binary search tree needs to have operations "inorderTreeWalk", "preorderTreeWalk", and "postorderTreeWalk"
that will print all node keys in a certain order(see the lecture notes / textbook.)
Your binary search tree needs to have operations "treeInsert", "rightRotate", "leftRotate", "treeSearch", "treeMinimum", "treeMaximum", "treeSuccessor", and "treePredecessor".
(see the lecture notes / textbook for those operations.)
BinarySeachTree class should have a constructor that initializes its root to be NULL, and a destructor that will delete all nodes in the treeand perform garbage collections.The destructor should also print “The number of nodes deleted : X” where X is the number of nodes deletedand it should be called when a user chooses to exit the program.
You should implement a driver class with a main method which takes the following commands(A, B, C, D, E, F, G, H, I, J, K, Q) from the keyboard :*/

#include <iostream> //to use cout
#include <string> //to use strings
#include <cstdlib> //to use atoi

using namespace std;

//Club represents some club information
class Club
 {
  private: 
    string clubName;
    string universityName;
    Club * left, * right, * parent;


  public:
    //The following two functions are constructors
    Club()
     { 
      clubName = "?";
      universityName = "?";
      parent = NULL;
      left = NULL;
      right = NULL;
     }


    Club(string clubName1, string universityName1)
     {
      clubName = clubName1;
      universityName = universityName1;
     
      parent = NULL;
      left = NULL;
      right = NULL;
     }

    //The following functions are accessor functions
    Club * getLeft()
     {
      return left;
     }

    Club * getRight()
     {
      return right;
     }

    Club * getParent()
     {
      return parent;
     }
     
    string getClubName()
     {
         return clubName;
     }
     string getUniversityName()
     {
         return universityName;
     }
     

    //The following functions are mutator functions
    void setLeft(Club * other)
     {
       left = other;
     }

    void setRight(Club * other)
     {
       right = other;
     }

    void setParent(Club * other)
     {
       parent = other;
     }

    //The print method prints the clubName and universityName
    void print()
     {
         cout << "Club Name: " << clubName << endl;
         cout << "University Name: " << universityName << endl << endl;
     }

   //you can add more functions

    int compare(Club* club)
    {
       return (this->getUniversityName() + this->getClubName())
            .compare(club->getUniversityName() + club->getClubName());
    }
 };

//class BinarySearchTree will contains clubs
class BinarySearchTree
 {
  private:
     Club * root;
     int size;

  public:
     BinarySearchTree();
     ~BinarySearchTree();
     int postOrderTreeDelete(Club *);
     bool isEmpty();
     void inOrderTreePrint();
     void preOrderTreePrint();
     void postOrderTreePrint();
     void inOrderTreeWalk(Club *);
     void preOrderTreeWalk(Club *);
     void postOrderTreeWalk(Club *);
     Club * treeSearchNode(Club *, string, string);
     Club * treeSearch(string, string);
     Club * treeMinimum();
     Club * treeMaximum();
     Club * treeMinimumNode(Club *);
     Club * treeMaximumNode(Club *);
     Club * treeSuccessor(string,string);
     Club * treePredecessor(string,string);
     bool treeInsert(string,string);
     bool rightRotate(string, string);
     bool leftRotate(string, string);
 };

//The constructor initialize the root to be NULL
BinarySearchTree::BinarySearchTree()
 {
  root = NULL;
  size = 0;
 }

//The descurtor should delete all nodes in the tree 
//and perform garbage collections starting from leaves (bottom-up order). 
//The destructor should also print “The number of nodes deleted: X” 
//where X is the number of nodes deleted
BinarySearchTree::~BinarySearchTree()
 {
   //TO BE COMPLETED
    cout << postOrderTreeDelete(root)<<endl;
 }

int BinarySearchTree::postOrderTreeDelete(Club* clublist) {
    if (clublist != NULL) {
        int sum = postOrderTreeDelete(clublist->getLeft());
        sum += postOrderTreeDelete(clublist->getRight());
        delete clublist;
        return (sum + 1);//delete the binary tree by using postorder recusivlly, each time delete a node, add 1 to the sum
    }
    return 0;
}

//Checks if the tree is empty
bool BinarySearchTree::isEmpty()
 {
   if (root == NULL)
    return true;
   else
    return false; 
 }

//prints all nodes using in-order
void BinarySearchTree::inOrderTreePrint()
 {
  if (isEmpty())
    cout << "tree is empty" << endl;
  else
   {
    cout << "\n";
    inOrderTreeWalk(root);
    cout << "\n";
   }
 }

//prints all nodes using pre-order
void BinarySearchTree::preOrderTreePrint()
 {
  if (isEmpty())
    cout << "tree is empty" << endl;
  else
   {
    cout << "\n";
    preOrderTreeWalk(root);
    cout << "\n";
   }
 }

//prints all nodes using post-order
void BinarySearchTree::postOrderTreePrint()
 {
  if (isEmpty())
    cout << "tree is empty" << endl;
  else
   {
    cout << "\n";
    postOrderTreeWalk(root);
    cout << "\n";
   }
 }

///COMPLETE THE REQUIRED FUNCTIONS

bool BinarySearchTree::treeInsert(string club, string univ) {
    Club* newclub = new Club(club, univ);
    Club* pointer = this->root;
    Club* prev = this->root; //create a new club and record user input
    while (pointer != NULL) //search the binary tree until found the correct position,
        //if element greater than node go right other wise go left
    {
        if (pointer->compare(newclub) == 0) {
            return false;
        }
        else if (pointer->compare(newclub) < 0) {
            prev = pointer;
            pointer = pointer->getRight();
        }
        else {
            prev = pointer;
            pointer = pointer->getLeft();
        }
    }
    if (this->root == NULL) { //if binary tree is empty, then we add the newclub into the first node
        this->root = newclub;
    }
    else {
        if (prev->compare(newclub) < 0) {
            prev->setRight(newclub);
            newclub->setParent(prev);
            size++;
        } //else if the parent is smaller than newclub add to the left node and assign the memory addres for newclub
        else {
            prev->setLeft(newclub);
            newclub->setParent(prev);
            size++;
        }//other wise add to the right node
    }
    return true;
 }

void BinarySearchTree::inOrderTreeWalk(Club* clublist){
    if (clublist != NULL) {
        inOrderTreeWalk(clublist->getLeft());
        clublist->print();
        inOrderTreeWalk(clublist->getRight()); //recursion print the tree if it has left node until found the null node, 
        //after that print all left and parent node search if it has right node, print the right node
    }
}

void BinarySearchTree::preOrderTreeWalk(Club* clublist) {
    if (clublist != NULL) {
        clublist->print();
        preOrderTreeWalk(clublist->getLeft());
        preOrderTreeWalk(clublist->getRight()); //recursion print the parent node, and recusivelly seach the left node then print them out, 
        //otherwise print the right node
    }
}

void BinarySearchTree::postOrderTreeWalk(Club* clublist) {
    if (clublist != NULL) {
        postOrderTreeWalk(clublist->getLeft());
        postOrderTreeWalk(clublist->getRight());
        clublist->print();//recursion print the left node until found the null, then recusivelly seach the right node then print them out, 
        //finally print the parent node
    }
}

Club* BinarySearchTree::treeSearch(string club, string univ) {
    return treeSearchNode(root, club, univ);  //call tree seach node and search for the element in the tree 
}

Club* BinarySearchTree::treeSearchNode(Club* clublist, string club, string univ) {
    if (clublist != NULL) {
        Club* newclub = new Club(club, univ); //create the newclub for user input
        if (clublist->compare(newclub) == 0) {
            return clublist; //found the location where is the club located
        } 
        else if (clublist->compare(newclub) < 0) {
            return treeSearchNode(clublist->getRight(), club, univ);
        } //if the user input greater than the clublist go right, otherwise go left
        else {
            return treeSearchNode(clublist->getLeft(), club, univ);
        }
    }
    return NULL;
}

Club* BinarySearchTree::treeMinimum() {
    Club* pointer = this->root;
    while (pointer != NULL && pointer->getLeft() != NULL) {
        pointer = pointer->getLeft();//keep tracking to the most left node which is the smallest node
    }
    return pointer;
}

Club* BinarySearchTree::treeMaximum() {
    Club* pointer = this->root;
    while (pointer != NULL && pointer->getRight() != NULL) {
        pointer = pointer->getRight(); //keep tracking to the most right node which is the greatest node
    }
    return pointer;
}

Club* BinarySearchTree::treePredecessor(string club, string univ) {
    Club* pointer = treeSearch(club, univ);
    if (pointer == NULL) {
        return NULL;
    }//if pointer is empty return NULL
    if (pointer->getLeft() != NULL) {
            return treeMaximumNode(pointer->getLeft());
    } //If its left subtree is not null
    ////Then predecessor will be the right most
    //    //child of left subtree or left child itself.
    else {
        Club* parent = pointer->getParent(); //if the pointer is the last node without left child
        while (parent != NULL && parent->getRight() != pointer) {
            pointer = parent;
            parent = pointer->getParent();
        }//tracking back to the parent node and keep pointer as the left node of parent
        return parent;//return parent when found out the pointer's parent at the root or itself on the right node of parent
    }
    


}

Club* BinarySearchTree::treeMaximumNode(Club* pointer) {
    if (pointer == NULL) {
        return NULL;
    }
    while (pointer->getRight() != NULL) {
        pointer = pointer->getRight(); //keep tracking to the most right node which is the greatest node
    }
    return pointer;
}

Club* BinarySearchTree::treeSuccessor(string club, string univ) {
    Club* pointer = treeSearch(club, univ);

    if (pointer == NULL) {
        return NULL;
    } //if pointer is empty return NULL
    if (pointer->getRight() != NULL) {
           return treeMinimumNode(pointer->getRight());
    }
    //If its right subtree is not null
    //The successor will be the left most child
    //of right subtree or right child itself.
    else {
        Club* parent = pointer->getParent(); //if the pointer is the last node without right child
        while (parent != NULL && parent->getLeft() != pointer) {
            pointer = parent;
            parent = pointer->getParent();//tracking back to the parent node and keep pointer as the right node of parent
        }
        return parent;//return parent when found out the pointer's parent at the root or itself on the left node of parent
    }

}

Club* BinarySearchTree::treeMinimumNode(Club* pointer) {
    if (pointer == NULL) {
        return NULL;
    }
    while (pointer->getLeft() != NULL) {
        pointer = pointer->getLeft(); //keep tracking to the most left node which is the smallest node
    }
    return pointer;
}

bool BinarySearchTree::leftRotate(string club, string univ) {
    Club* x = this->treeSearch(club, univ); // get the node of given club and university
    if (x == NULL) {
        return false;
    }
    Club* y = x->getRight();//set y as x right child
    if (y == NULL) {
        return false;
    }
    x->setRight(y->getLeft());//set x's righ child as y's left child
    if (y->getLeft() != NULL) {
        y->getLeft()->setParent(x);//if y's left child is not null, then set the right child as x's parent
    }

    y->setParent(x->getParent());//exchange parent of x and y
    if (x->getParent() == NULL) {//if x is a root set y as a root node
        root = y;
    }
    else {
        if (x == (x->getParent())->getLeft()) {
            (x->getParent())->setLeft(y);//set x as brother (parent's left child) node
        }
        else {
            (x->getParent())->setRight(y);//set x as brother (parent's right child) node
        }
    }

    y->setLeft(x);//set the y's left childen to the x node
    x->setParent(y);
    return true;
}
bool BinarySearchTree::rightRotate(string club, string univ) {
    Club* x = this->treeSearch(club, univ); //get the node of given club and university
    if (x == NULL) {
        return false;
    }
    Club* y = x->getLeft(); //set y as x left child
    if (y == NULL) {
        return false;
    }

    x->setLeft(y->getRight()); //set x's left child as y's right child
    if (y->getRight() != NULL) {
        y->getRight()->setParent(x);
    } //if y's right child is not null, then set the right child as x's parent

    y->setParent(x->getParent()); //exchange parent of x and y
    if (x->getParent() == NULL) {
        root = y;
    }//if x is a root set y as a root node
    else {
        if (x == (x->getParent())->getLeft()) {
            (x->getParent())->setLeft(y);
        }//set x as brother (parent's left child) node
        else {
            (x->getParent())->setRight(y);
        }//set x as brother (parent's right child) node
    }

    y->setRight(x); //set the y's right childen to the x node
    x->setParent(y);
    return true;
}
