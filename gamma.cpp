#include "gamma.h"


void Gamma::initialize(double a, double b){
	beta = b;
	dd = a-(1/3.0);
	cc = 1/sqrt(9*dd);
}

double Gamma::rand_gamma(xorshift64& rand){
	double d;
    for(;;){
        double x = rand_normal(rand,0.0,1);
        double u = rand.get_double52();
        double v = (1+cc*x)*(1+cc*x)*(1+cc*x);
        if(v<=0)
            continue;
        if(u<(1-0.0331*(x*x*x*x))){
            d = dd*v;
            break;
        }
        if(log(u)<0.5*x*x+dd*(1-v+log(v))){
            d = dd*v;
            break;
        }
    }
    return d/beta;
}
