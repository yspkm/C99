#include <stdio.h> 
#include <string.h> // strlen
#include <stdlib.h>  // atoi

#define MAX_LEN 50
#define TRUE 0x1
#define FALSE 0x0 

int main(void) { 
    int i, ans, is_minus, temp, temp_idx;
    char expr[MAX_LEN + 1], temp_expr[MAX_LEN + 1];

    scanf("%s", expr);
    is_minus = FALSE;
    ans = 0;
    temp_idx = 0;
    temp_expr[0] = '\0';
    for(i=0;i<=strlen(expr);i++) { 
        if(!expr[i] || expr[i]=='+' || expr[i]=='-') { 
            if (is_minus) { 
                temp = atoi(temp_expr);
                ans -= temp; 
            } else { 
                temp = atoi(temp_expr);
                ans += temp; 
            } 
            temp_expr[0]='\0'; 
            temp_idx = 0;
            if(expr[i]=='-') { 
                is_minus = TRUE; 
            } 
        } else { 
            temp_expr[temp_idx++] = expr[i]; 
            temp_expr[temp_idx] = '\0';
        } 
    } 
    printf("%d\n", ans);
    return 0;
}