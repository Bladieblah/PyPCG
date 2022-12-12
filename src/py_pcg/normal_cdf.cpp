#include <math.h>

#include "normal_cdf.hpp"

#define UNIFORM_LOW 0.02425
#define UNIFORM_HIGH 0.97575

/*
 * Ruan, H., Huang, X., Fu, H., & Yang, G. (2014). 
 * A fully pipelined probability density function engine 
 * for Gaussian Copula model. 
 * Tsinghua Science and Technology, 19(2), 194-202.
 */

double inverse_normal_cdf(double uniform) {
	double q, r;

	if (uniform <= 0) {
		return -HUGE_VAL;
	}
	else if (uniform < UNIFORM_LOW) {
		q = sqrt(-2 * log(uniform));
		return (((((c[0] * q + c[1]) * q + c[2]) * q + c[3]) * q + c[4]) * q + c[5]) /
			((((d[0] * q + d[1]) * q + d[2]) * q + d[3]) * q + 1);
	}
	else if (uniform <= UNIFORM_HIGH) {
        q = uniform - 0.5;
        r = q * q;
        
        return (((((a[0] * r + a[1]) * r + a[2]) * r + a[3]) * r + a[4]) * r + a[5]) * q /
            (((((b[0] * r + b[1]) * r + b[2]) * r + b[3]) * r + b[4]) * r + 1);
	}
	else if (uniform < 1) {
		q  = sqrt(-2 * log(1 - uniform));

		return -(((((c[0] * q + c[1]) * q + c[2]) * q + c[3]) * q + c[4]) * q + c[5]) /
			((((d[0] * q + d[1]) * q + d[2]) * q + d[3]) * q + 1);
	}
	else {
		return HUGE_VAL;
	}
}