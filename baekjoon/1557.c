#include <stdio.h>
#include <stdbool.h>

bool mark[1000001] = {false};
long long num[1000001] = {0};

int main(void) 
{
	long long i, j, count=0, min, max, div;
	int cnt_num =0; 

	scanf("%lld %lld", &min, &max);

    	for(i=2; i*i<=max; i++) {        
        	num[i] = i*i;
        	cnt_num++;
    	}

 	for(i=2; i<cnt_num+2; i++){
        	div = min;                
        	if(div % num[i] != 0){               
            		div = (min/num[i] + 1) * num[i]; 
        	}
 
        	for(j = div; j <=max; j += num[i]){
            		if(!mark[j-min]){
                		mark[j-min] = true;
                		count++;
            		}
        	}
	}
 
	printf("%lld", max-min-count+1);
	return 0;
}