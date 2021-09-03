#include <stdio.h>
#include <string.h>

#define MAX_OPT_LEN 6
#define MAX_OUTPUT_LEN 93750 // 3000000 / 32


int main(void)
{
    int set, i, j, m, opd, temp, output_len, last_len;
    unsigned output[MAX_OUTPUT_LEN] = {0};
    char opt_str[MAX_OPT_LEN + 1];

    scanf("%d", &m);
    set = 0x0;
    output_len = 0;
    last_len = 0;
    for (i = 0; i < m; i++) {
        if (last_len == 32) {
            output_len++;
            last_len = 0;
        }
        scanf("%s", opt_str);
        if (!strcmp(opt_str, "add")) {
            scanf("%d", &opd);
            temp = 0x1 << opd;
            set = set | temp;
        } else if (!strcmp(opt_str, "remove")){
            scanf("%d", &opd);
            temp = ~(0x1 << opd);
            set = set & temp;
        } else if (!strcmp(opt_str, "check")) {
            scanf("%d", &opd);
            temp = 0x1 << opd;
            temp = set & temp ? 1 : 0;
            if (temp) {
                output[output_len] |= 0x1 << (32 - (last_len+1));
            }
            last_len++;
        } else if (!strcmp(opt_str, "toggle")) {
            scanf("%d", &opd);
            temp = 0x1 << opd;
            set = set ^ temp;
        } else if (!strcmp(opt_str, "all")) {
            temp = 0x1 << (20+1);
            set = temp - 0x1;
        } else if (!strcmp(opt_str, "empty")) {
            set = 0x0;
        }
    }
    for (i = 0; i < output_len; i++) {
        for (j = 31; j >= 0; j--) {
            printf("%s\n", (output[i] & (0x1 << j)) ? "1" : "0");
        }
    }
    for (j = 31; j >= 32 - last_len; j--) {
        printf("%s\n", (output[i] & (0x1 << j)) ? "1" : "0");
    }
    return 0;
}