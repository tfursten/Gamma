#include <iostream>
#include <fstream>
#include <gsl/gsl_randist.h>
#include "xorshift64.h"
#include "gamma.h"

using namespace std;


int gslgamma(double alpha, double beta, int it){
    gsl_rng * myrand = gsl_rng_alloc(gsl_rng_taus);
    for(int i = 0; i<it; i++){
        double x = gsl_ran_gamma(myrand,alpha,beta);
    }
    return 0;


}
int mygamma(double alpha, double beta, int it){
    xorshift64 myrand;
    Gamma g;
    g.initialize(alpha,beta);
    for(int i = 0; i<it; i++){
        double d = g.rand_gamma(myrand);
        }
    return 0;
}

int main(){
    xorshift64 myrand;
    myrand.seed(98756651651);
    ofstream myfile;
    Gamma gam;
    gsl_rng * myrand2 = gsl_rng_alloc(gsl_rng_taus);
    myfile.open("./Notebook/test05.txt");
    myfile << "myGamma\tGSLGamma" << endl;
    double alpha = 0.5;
    double beta = 0.612;
    int it = 100000;
    gam.initialize(alpha, beta);

    //gslgamma(alpha,beta,it);
    //mygamma(alpha,beta,it);
    for(int i = 0; i<it; i++){
        double d1 = gam.rand_gamma(myrand);
        double d2 = gsl_ran_gamma(myrand2,alpha,1/beta);
        myfile<<d1<<"\t"<<d2<<endl;
    }

    return 0;
}





