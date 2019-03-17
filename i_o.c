#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "stonylake/device1.h"

int main(){

    int k = 0;
    k = addOne(k);
    k = addTwo(k);
    printf("k = %d\n", k);
    return 0;
}