#include <iostream>
#include <fstream>
#include "xorshift64.h"
#include "rnormal.h"
#include <fstream>
#include <assert.h>

using namespace std;

double gamma(xorshift64& rand, double a, double b, double dd, double cc){
//Marsalgia2000
    double d;
    for(;;){
        double x = rand_normal(rand,0.0,1);
        double u = rand.get_double52();
        double v = pow(1+cc*x,3);
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
    return d/b;
}




int main(){
    xorshift64 myrand;
    myrand.seed(46546546001);
    double scale = 1/3.0; //theta
    double sigma = 4;
    double alpha = (sigma*sigma*scale);
    cout << "Alpha: " << alpha << endl;
    assert(alpha>=1);
    double sum = 0.0;
    int it = 10000000;
    vector<double> var(it);
    double dd = alpha-(1/3.0);
    double cc = 1/sqrt(9*dd);
    for(int i = 0; i<it; i++){
        double d = gamma(myrand, alpha, scale, dd, cc);
        sum += d;
        var[i] = d;
    }

    double variance;
    double mean = sum/double(it);
    for(int i = 0; i<it; i++){
        variance += (var[i]-mean)*2;
    }
    cout << "Mean: " << mean << endl;
    cout << "Variance: " << variance << endl;
    return 0;
}

/*double gamma_smallA(xorshift64& rand, double a, double b, double L, double w, double r){
    //Martin2013
    double d;
    for(;;){
        double u = rand.get_double52();
        //double c = 1/tgamma(param2+1);
        double z,n;
        if(u<=r){
            z = -log(u/r);
            //z = rand_exp(1.0)-param5;
        }
        else{
            //z = log(u)/param3;
            z = -rand_exp(rand, L);
        }
        if(z>=0)
            n = exp(-z);
        else
            n = w*L*exp(L*z);
        if((exp(-z-exp(z/a)))/n > u){
            d = -z/a;
            break;
        }
    }
    d = exp(d);
    //cout << d << endl;
    return d;
}*/
