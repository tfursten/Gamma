# Gamma
Gamma rejection sampling from [Marsaglia and Tsang 2000](http://delivery.acm.org/10.1145/360000/358414/p363-marsaglia.pdf?ip=149.169.219.168&id=358414&acc=ACTIVE%20SERVICE&key=B63ACEF81C6334F5%2EBD7B0059B564CDBA%2E4D4702B0C3E38B35%2E4D4702B0C3E38B35&CFID=617740920&CFTOKEN=73882148&__acm__=1422565045_2c273a62b5e5db6113168b5247aaaa8f)


An algorithm for generating a gamma variables X~Gamma(a,b) for a>=1.  
1. Set-up d = a -1/3 and c = 1/sqrt(9d).  
2. Generate: v = (1+c*x)^3, drawing x from a standard normal. Repeat if v <= 0 [rare].  
3. Generate uniform U.    
4. If U < 1-0.0331*x^4 return d*v.  
5. if log(U) < 0.5*x^2+d*(1-v+log(v)) return d*v.  
6. Go to step 2.  

Uniform random variables are generated using Xorshift64.h  
Normal random variables are generated using the Ziggurat Algorithm ([Marsaglia and Tsang 2000](http://www.jstatsoft.org/v05/i08/paper)) in rnormal.h. 

###Testing
This implementation of the Marsaglia and Tsang method for generating Gamma distributed random numbers runs faster than the GSL implementation using their fastest random number generator (taus) but does not work for very low values of $\alpha$ (<0.5). Below is a QQ-Plot of 1.0x10^7 random values from each implementation.
![Alt text](https://github.com/tfursten/Gamma/blob/master/img/qqplot.png?raw=true =10x10)
