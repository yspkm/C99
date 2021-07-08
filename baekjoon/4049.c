#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MATLEN 500
#define DIVLEN 25 

typedef int Data;
typedef struct _Node
{
    int item;
    struct _Node *next;
} Node;
typedef struct _List
{
    Node *head;
    int len;
} List;
void initList(List **lptrptr);
void addNode(List *lptr, Data item);
void printAllNode(List *lptr);

typedef struct _Matrix {
    int matrix[MATLEN][MATLEN];
    int r;
    int c;
} Matrix;
typedef struct _Divisors {
    int divs[DIVLEN];
    int len;
} Divisors;


bool isEnd(Matrix *mat);
int getRes(Matrix *mat, Divisors *row_div, Divisors *col_div);
void getDivisor(Divisors *divs, int num);
void getAllDivisor(Matrix *mat, Divisors *row_div, Divisors *col_div);
bool isScalMul(Matrix* mat, int row, int col, int curh, int curw);
bool isProduct(Matrix* mat, int row, int col);

Divisors g_div;

int getGcd(int a, int b){
    if(b == 0){
        return a;
    }else{
        return getGcd(b, a%b);
    }
}

int main(void)
{
    Matrix mat;
    Divisors row_div, col_div;
    List* res; initList(&res);

    while (!isEnd(&mat)) {
        addNode(res, getRes(&mat, &row_div, &col_div));
    }
    printAllNode(res);

    return 0;
}

bool isEnd(Matrix *mat)
{
    bool ret = false;
    scanf("%d %d", &mat->r, &mat->c);
    if (mat->r == 0 && mat->c == 0) {
        ret = true;
    }
    else {
        int i, j;
        for (i = 0; i < mat->r; i++) {
            for (j = 0; j < mat->c; j++) {
                scanf("%d", &(mat->matrix[i][j]));
            }
        }
    }
    return ret;
}

int getRes(Matrix *mat, Divisors *row_div, Divisors *col_div)
{
    int i, j, row, col, ret = 0;
    getAllDivisor(mat, row_div, col_div);

    for (i = 0; i < row_div->len; i++) {
        for (j = 0; j < col_div->len; j++) {
            if((i == 0 && j == 0) || (i == row_div->len-1 && j == col_div->len-1)) { //same tensor
                continue;
            }
            row = row_div->divs[i];
            col = col_div->divs[j];
            if (isProduct(mat, row, col)) {
                ret++;
            }
        }
    }
    int temp = mat->matrix[0][0];
    for (i = 0; i < mat->r; i++) {
        for (j = 0; j < mat->c; j++) {
            if (temp != mat->matrix[i][j])
                break;
        }
    }
    if (i == mat->r && j == mat->c) {
        getDivisor(&g_div, temp); 
        ret *= g_div.len;
    }

    return ret;
}

void getDivisor(Divisors *divs, int num) 
{
    int i, idx=0;
    divs->len = 0;
    for (i = 1; i <= num; i++){
        if (num % i == 0) {
            divs->divs[idx++] = i;
            divs->len++;
        }
    }
}

void getAllDivisor(Matrix *mat, Divisors *row_div, Divisors *col_div)
{
    getDivisor(row_div, mat->r);
    getDivisor(col_div, mat->c);
}

bool isProduct(Matrix* mat, int row, int col)
{
    bool ret = true;
    int curh, curw, h = mat->r / row, w = mat->c / col;
    for (curh = 0; curh < h; curh++) {
        for (curw = 0; curw < w; curw++) {
            if (curh == 0 && curw == 0)
                continue; //first element
            if (!isScalMul(mat, row, col, curh, curw)) { 
                return false;
            }
        }
    }
    return ret;
}

bool isScalMul(Matrix *mat, int row, int col, int curh, int curw)
{
    bool ret = true;
    int rb = row * curh, cb = col * curw, i, j, gcd, num, den, new_num, new_den;
    if (mat->matrix[0][0] > mat->matrix[rb][cb]) {
        gcd = getGcd(mat->matrix[0][0], mat->matrix[rb][cb]);
        num = mat->matrix[0][0] / gcd;
        den = mat->matrix[rb][cb] / gcd;
        for (i = 0; i < row; i++) {
            for (j=0; j <col; j++) {
                if (!mat->matrix[i][j] && !mat->matrix[rb+i][cb+j]) continue;
                if (!mat->matrix[i][j] || !mat->matrix[rb+i][cb+j]){
                    return false;
                }
                gcd = getGcd(mat->matrix[i][j], mat->matrix[rb+i][cb+j]);
                new_num = mat->matrix[i][j] / gcd;
                new_den = mat->matrix[rb+i][cb+j] / gcd;
                if (num != new_num || den != new_den) {
                    return false;
                }
            }
        }
    } else if (mat->matrix[0][0] < mat->matrix[rb][cb]) {
        gcd = getGcd(mat->matrix[rb][cb], mat->matrix[0][0]);
        num = mat->matrix[rb][cb] / gcd;
        den = mat->matrix[0][0] / gcd;
        for (i = 0; i < row; i++) {
            for (j=0; j <col; j++) {
                if (!mat->matrix[i][j] && !mat->matrix[rb+i][cb+j]) continue;
                if (!mat->matrix[i][j] || !mat->matrix[rb+i][cb+j]){
                    return false;
                }
                gcd = getGcd(mat->matrix[rb+i][cb+j], mat->matrix[i][j]);
                new_num = mat->matrix[rb+i][cb+j] / gcd;
                new_den = mat->matrix[i][j] / gcd;
                if (num != new_num || den != new_den) {
                    return false;
                }
            }
        }
    } else {
        for (i = 0; i < row; i++) {
            for (j = 0; j < col; j++) {
                if (mat->matrix[i][j] != mat->matrix[rb+i][cb+j]) {
                    return false;
                }
            }
        }
    }

    return ret;
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
    Node *cur = lptr->head->next;
    for (; cur;) 
    {
        printf("%d\n", cur->item);
        cur = cur->next;
    }
}

void initList(List **lptrptr)
{
    *lptrptr = (List *)malloc(sizeof(List));
    (*lptrptr)->head = (Node*) malloc(sizeof(Node));
    (*lptrptr)->head->next = NULL;
    (*lptrptr)->len = 0;
}