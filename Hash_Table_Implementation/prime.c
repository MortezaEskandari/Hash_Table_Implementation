#include <math.h>

#include "prime.h"


/* Checks if passed in int is a prime number
 * @param const int x: the int we are checking if it's prime or not
 * Returns:
 *  1    - prime
 *  0    - not prime
 *  -1   - undefined (i.e. x < 2)
 */
int is_prime(const int x){

    if(x < 2) {
        return -1;
    }
    else if(x < 4){
        return 1;
    }
    else if((x % 2) == 0){
        return 0;
    }
    else{
        for(int i = 3; i <= floor(sqrt((double) x)); i += 2){
            if((x % i) == 0){
                return 0;
            }
        }
    }
    return 1;
}

/*
 * Returns the next prime after x, or x if x is prime
 */
int next_prime(int x){
    while(is_prime(x) != 1){
        x++;
    }
    return x;
}
