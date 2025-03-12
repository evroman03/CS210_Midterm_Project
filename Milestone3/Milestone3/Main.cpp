#include <iostream>
#include "BST.h"
#include "SchoolData.h"
#include "string"

int main() 
{
    BinarySearchTree<SchoolData> schoolTree;

    SchoolData newSchool("A_Green Valley High", "123 Main St", "Green Valley", "StateX", "CountyY");
    SchoolData newSchool2("D_Green Valley High", "123 Main St", "Green Valley", "StateX", "CountyY");
    SchoolData newSchool3("C_Green Valley High", "123 Main St", "Green Valley", "StateX", "CountyY");

    //// Insert into the tree
    schoolTree.bstInsert(newSchool);
    schoolTree.bstInsert(newSchool2);
    schoolTree.bstInsert(newSchool3);

    schoolTree.bstInorder();

    return 0;
}
