#include <iostream>
#include <maps>
#include <vector>
#include <set>
#include <queue>

int main(int argc, char const* argv[])
{

    return 0;
}

void sumTree(node *n,int level, int *evenSum, int *oddSum){

    if(n == NULL)
        return;
    if(level%2 == 0)
        *evenSum += n.val;
    else
        *oddSum += n.val;

    sumTree(n->left,level+1,evenSum,oddSum);
    sumTree(n->right,level+1,evenSum,oddSum);

}

int calcDiff(node * root){

    int level = 1;
    int evenSum = 0;
    int oddSum = 0;

    sumTree(root,level,&evenSum, &oddSum);
    return (oddSum - evenSum);

}


