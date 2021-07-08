#include "binary_tree.h"
#include "stack.h"
#include <stdlib.h>
#include <stdio.h>

/* FYI, predefined macro and data types are as below.  */
/*
typedef char DATA_TYPE;

typedef struct _bTreeNode
{
    DATA_TYPE item;
    struct _bTreeNode * left_child;
    struct _bTreeNode * right_child;
} BTreeNode;
*/

BTreeNode* CreateNode(DATA_TYPE item)
{
    BTreeNode* node;
    /* write your own code here. */
    node = (BTreeNode*) malloc(sizeof(BTreeNode));
    node->item = item;
    node->right_child = NULL;
    node->left_child = NULL;

    return node;
}

void DestroyNode(BTreeNode* node)
{
    /* write your own code here. */
    if (node)
        free(node);
}

void CreateLeftSubtree(BTreeNode* root, BTreeNode* left)
{
    /* write your own code here. */
    if (root->left_child || !root)
        exit(1);
    root->left_child = left;
}

void CreateRightSubtree(BTreeNode* root, BTreeNode* right)
{
    /* write your own code here. */
    if (root->right_child || !root)
        exit(1);
    root->right_child = right;
}

void Inorder(BTreeNode* root)
{
    /* write your own code here. */

    if (root) {
        Inorder(root->left_child);
        printf("%c", root->item);
        Inorder(root->right_child);
    }
}

void Preorder(BTreeNode* root) 
{
    /* write your own code here. */
    if (root) {
        printf("%c", root->item);
        Preorder(root->left_child);
        Preorder(root->right_child);
    }
}

void Postorder(BTreeNode* root)
{
    /* write your own code here. */
    if (root) {
        Postorder(root->left_child);
        Postorder(root->right_child);
        printf("%c", root->item);
    }
}

int CalculateExpTree(BTreeNode* root)
{
    int ret;
    /* write your own code here. */
    int lopd, ropd;
    if (root == NULL) return 0;
    if (root->left_child == NULL && root->right_child == NULL) return root->item - '0';
    
    lopd = CalculateExpTree(root->left_child);
    ropd = CalculateExpTree(root->right_child);

    switch (root->item) {
        case '+': ret = lopd + ropd; break;
        case '-': ret = lopd - ropd; break;
        case '*': ret = lopd * ropd; break;
        case '/': ret = lopd / ropd; break;
        case '%': ret = lopd % ropd; break;
        case '@': ret = lopd << ropd; break;
        case '#': ret = lopd >> ropd; break;
    }

    return ret;
}

BTreeNode* MakeExpTree(char* exp, int len)
{
    BTreeNode* ret;
    /* write your own code here. */
    Stack opt_stack;
    BTreeNode *root, *lc, *rc;
    Stack* osptr = &opt_stack;
    InitStack(osptr);

    for (int i = 0; i< len; i++) {
        if ('0' <= exp[i] && exp[i] <= '9')
            root = CreateNode(exp[i]);
        else {
            rc = PeekNode(osptr); Pop(osptr);
            lc = PeekNode(osptr); Pop(osptr);

            root = CreateNode(exp[i]);
            CreateLeftSubtree(root, lc);
            CreateRightSubtree(root, rc);
        }
        PushNode(&opt_stack, root);
    }
    ret = PeekNode(&opt_stack);
    return ret;
}

void DestroyExpTree(BTreeNode* root)
{
    //이 함수는 반드시 사용 후에 caller함수위치에서의 root 포인터를 NULL로 초기화해줘야 합니다. 
    //root_ptr->root->left
    //              ->right
    //예를들어 traversal함수로 테스트하기 위해서 초기화가 필요합니다. 
    //그러나 prototype자체가 그냥 포인터이므로 해당위치를 초기화할 수 없습니다. 
    /* write your own code here. */
    if (root != NULL) {
        DestroyExpTree(root->left_child);
        DestroyExpTree(root->right_child);
        DestroyNode(root);
    }
}
//DO NOT define main function 