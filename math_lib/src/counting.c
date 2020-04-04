#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint64_t fact(uint32_t n) {
	uint64_t res = 1;
	if(n == 0 || n == 1) {
		return res;
	} else {
		res = n;
		return res*fact(n-1);
	}
}

uint64_t perm(uint32_t n, uint32_t k) {
	if(k > n) {
		printf("k=%u must be not greater than n=%u\n", k,n);
		exit(1);
	} else if(0 == k) {
		return 0;
	} else if(1 == k) {
		return n;
	} else if(n == k) {
		return fact(n);
	} else {
		uint64_t res = 1;
		for(uint32_t i = n; i >(n-k); i--) {
			res *= i;
		}
		return res;
	}
}

uint64_t comb(uint32_t n, uint32_t k) {
	return perm(n,k)/fact(k);
}


#if 0
int main() {
	printf("%lu\n", fact(3));
	printf("%lu\n", perm(20,3));
	printf("%lu\n", comb(20,3));
	return 0;
}
#endif