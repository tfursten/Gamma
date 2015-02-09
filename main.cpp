#include <iostream>
#include <fstream>
#include <gsl/gsl_randist.h>
#include "xorshift64.h"
#include "gamma.h"

using namespace std;

int main(){
    xorshift64 myrand;
    ofstream myfile;
    Gamma gam;
    myfile.open("test.txt");
    myfile << "myGamma\tGSLGamma" << endl;
    double beta = 1/3.0; //theta
    //set alpha so that the second moment of the
    //distribution is equivalent to 2sigma^2
    double sigma = 4;
    double alpha = (sigma*sigma*beta);
    cout << "Alpha: " << alpha << endl;
    assert(alpha>=0.5);
    gam.initialize(alpha, beta);
    for(int i = 0; i<it; i++){
        double d = gam.rand_gamma(myrand);
        myfile<<d<<endl;
        sum += d;
        var[i] = d;
    }
    double mean = sum/double(it);
    cout << "Mean: " << mean << endl;
    return 0;
}


int gslgamma(double alpha, double beta, int it){
    gsl_rng * myrand = gsl_rng_alloc(gsl_rng_taus);
    double sum = 0;
    for(int i = 0; i<it; i++){
        double x = gsl_ran_gamma(myrand,alpha,beta);
        sum += x;
        }
    cout << sum/double(it) << endl;
    return 0;
}
int mygamma(double alpha, double beta, int it){
    xorshift64 myrand;
    Gamma g;
    g.initialize(alpha,beta);
    double sum = 0;
    for(int i = 0; i<it; i++){
        double d = g.rand_gamma(myrand);
        sum += d;
        }
    cout << sum/double(it) << endl;
    return 0;
}

void time_test(double alpha, double beta, int it){
    gslgamma(alpha, 1/beta, it);
    //mygamma(alpha, beta, it);
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
