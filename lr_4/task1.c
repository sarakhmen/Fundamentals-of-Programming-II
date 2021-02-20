#include <stdio.h>
#include <stdlib.h>

int custom_rand(int a, int b){
    int ret_val = 0;
    for(int i = a; i<b; ++i){
        if(rand() % i == 0)
            ret_val = i;
    }
    return ret_val;
}

int main(void){
    int val,
        sum = 0,
        lower_bound = 1,
        upper_bound = 100;
    printf("Randomize 100 numbers in the range %d to %d:\n", lower_bound, upper_bound);
    for(int i = 0; i < 100; ++i){
        printf("%d ", val = custom_rand(lower_bound, upper_bound));
        sum += val;
    }
    printf("\nAverage value after 100 attempts = %f", (double)sum/100);
	return 0;
}
