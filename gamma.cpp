#include "gamma.h"


void Gamma::initialize(double a, double b){
	assert((a>0)&&(b>0));
    beta = b;
    if(a<1){
        alpha = 1.0+a;
        p = a;
    }
    else p = 1;
	dd = a-(1/3.0);
	cc = (1.0/3.0)/sqrt(dd);
}

double Gamma::rand_gamma(xorshift64& rand){
	double d, x, v, u;
    for(;;){
        do{
            x = rand_normal(rand, 0.0, 1);
            v = 1.0 + cc * x;
        }
        while(v <= 0);
        v = v*v*v;
        u = rand.get_double52();
        if(u < 1 - 0.0331 *x*x*x*x)
            break;
        if(log(u) < 0.5 * x * x + dd * (1 - v + log(v)))
            break;
    }
    d = 1/beta * dd * v;
    if(p >= 1)
        return d;
    else{
        u = rand.get_double52();
        return d * pow(u,1.0/alpha);
    }
}
