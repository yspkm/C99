#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int Data;
typedef struct _Node
{
    int item;
    struct _Node *next;
} Node;
typedef struct _Matrix
{
    Data *matrix;
    int r;
    int c;
} Matrix;
typedef struct _List
{
    Node *head;
    int len;
} List;

bool isEnd(Matrix *mat);
void rmMat(Matrix *mat);
Data getRes(Matrix *mat);

void printMat(Matrix *mat); // for test
List* getPrimeFactor(int num);
void getAllDivisor(List* lptr);

void initList(List **lptrptr);
void addNode(List *lptr, Data item);
void printAllNode(List *lptr);
Data getData(List *lptr, int idx);

int main(void)
{
    Data res;
    List *lptr;
    initList(&lptr);
    Matrix mat;

/*
    while (!isEnd(&mat))
    {
        printMat(&mat);
        addNode(lptr, getRes(&mat));
        rmMat(&mat); //free all memory
    }
    printAllNode(lptr);
    */
    List* fact = getPrimeFactor(777*34*19);
    getAllDivisor(fact);
    printAllNode(fact);

    return 0;
}

bool isEnd(Matrix *mat)
{
    bool ret = false;
    scanf("%d %d", &mat->r, &mat->c);
    if (mat->r == 0 && mat->c == 0)
    {
        ret = true;
    }
    else
    {
        int i, j;
        mat->matrix = (int *)malloc(mat->r * mat->c * sizeof(int));
        for (i = 0; i < mat->r; i++)
        {
            for (j = 0; j < mat->c; j++)
            {
                scanf("%d", &(mat->matrix[j + i * mat->c]));
            }
        }
    }
    return ret;
}

Data getRes(Matrix *mat)
{
    Data ret = 0;
    
    return ret;
}

List* getPrimeFactor(int num)
{
    List* ret; initList(&ret);
    for (int i = 2; i * i <= num; i++) 
    {
        while(num % i == 0)
        {
            num /= i;
            addNode(ret, i);
        }
    }
    if (num != 1)
        addNode(ret, num);
    return ret;
}

void getAllDivisor(List* lptr) 
{
    int len = lptr->len;
    if (len == 2)
        return;
    int i, j;
    Data pf1, pf2;
    for (i = 0; i < len; i++) 
    {
        pf1 = getData(lptr, i);
        for (j = i+1; j < len; j++)
        {
            pf2 = getData(lptr, j);
            addNode(lptr, pf1 * pf2);
        }
    }
}

void rmMat(Matrix *mat)
{
    mat->r = 0;
    mat->c = 0;
    free(mat->matrix);
}

void initList(List **lptrptr)
{
    *lptrptr = (List *)malloc(sizeof(List));
    (*lptrptr)->head = (Node*) malloc(sizeof(Node));
    (*lptrptr)->head->next = NULL;
    (*lptrptr)->len = 0;
}

Data getData(List *lptr, int idx)
{
    if (lptr->len == 0)
        exit(1);
    else
    {
        Node *cur;
        int i;
        for (cur = lptr->head, i = 0; i <= idx; cur = cur->next, i++)
            ;
        return cur->item;
    }
}

void addNode(List *lptr, Data item)
{
    Node *temp;
    if (!lptr->head->next)
    {
        temp = (Node *)malloc(sizeof(Node));
        temp->item = item;
        temp->next = NULL;
        lptr->head->next = temp;
    }
    else
    {
        Node *cur;
        for (cur = lptr->head; cur->next; cur = cur->next)
            ;
        temp = (Node *)malloc(sizeof(Node));
        temp->item = item;
        temp->next = NULL;
        cur->next = temp;
    }
    lptr->len++;
}

void printAllNode(List *lptr)
{
    if (lptr->len == 0)
        exit(1);
    Node *cur = lptr->head;
    for (int i = 0; i < lptr->len; i++)
    {
        cur = cur->next;
        printf("%d\n", cur->item);
    }
}

void printMat(Matrix *mat)
{
    int i, j;
    for (i = 0; i < mat->r; i++)
    {
        for (j = 0; j < mat->c; j++)
            printf("%d ", mat->matrix[j + i * mat->c]);
        printf("\n");
    }
}