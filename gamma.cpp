#include <iostream>
#include <fstream>
#include "xorshift64.h"
#include "rnormal.h"
#include <fstream>
#include <assert.h>

using namespace std;

inline int wrap_around(int x, int w) {
    return ((x%w)+w)%w;
}

inline int xy2i(int x, int y, int mx, int my) {
    assert(0 <= x && x < mx);
    assert(0 <= y && y < my);
    return x*my+y;
}

int absorbing(int x, int y, int maxX, int maxY)
{
    if (x >= 0 && x < maxX && y >= 0 && y < maxY)
        return xy2i(x,y,maxX,maxY);
    return -1;
}

int periodic(int x, int y, int maxX, int maxY)
{
    int newX = wrap_around(x,maxX);
    int newY = wrap_around(y,maxY);
    return xy2i(newX,newY,maxX,maxY);
}

int disperse_cont(xorshift64& rand, int x, int y, double d, int mx, int my)
{
    double a = rand.get_double52() * 2.0 * M_PI;
    double newX = floor(d*cos(a)+x+0.5);
    double newY = floor(d*sin(a)+y+0.5);
    int i = periodic(newX,newY,mx,my);
    return i;

}


double gamma_bigA(xorshift64& rand, double a, double b, double dd, double cc)
{
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
    //cout << d*b << endl;
    return d/b;
}

double gamma_smallA(xorshift64& rand, double a, double b, double L, double w, double r){
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
}


int main(){
    xorshift64 myrand;
    double sigma = .5;
    double scale = 1/0.5;
    //double alpha = 1;
    double alpha = scale * sigma * sigma;
    //double alpha = (sigma*sigma)/(scale);
    cout << "Alpha: " << alpha << endl;
    assert(alpha>0);
    double sum = 0.0;
    int it = 10000000;
    vector<double> var(it);
    //if(alpha>=1){
    double dd = alpha-(1/3.0);
    double cc = 1/sqrt(9*dd);
    //cout << "BIG ALPHA" << endl;
    for(int i = 0; i<it; i++){
        double d = gamma_bigA(myrand, alpha, scale, dd, cc);
        sum += d;
        var[i] = d;
    }
    //}
    /*
    else{
        double L = 1/alpha;
        double w = alpha/exp(1-alpha);
        double r = 1/(1+w);
        cout << "SMALL ALPHA" << endl;
        for(int i = 0; i<it; i++){
            double d = gamma_smallA(myrand, alpha, scale, L, w, r);
            sum += d;
            var[i] = d;
        }
    }
    */
    double variance;
    double mean = sum/double(it);
    for(int i = 0; i<it; i++){
        variance += (var[i]-mean)*2;
    }
    cout << "Mean: " << mean << endl;
    cout << "Variance: " << variance << endl;
    return 0;
}
