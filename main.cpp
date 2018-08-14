//
//  main.cpp
//  simulationValuingCallsPuts
//
//  Created by Colin Chen on 13/02/2018.
//  Copyright © 2018 Colin Chen. All rights reserved.
//

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <limits>
#include "mtrand.h"
using namespace std;
double calculateCallExerciseValue(double spot, double strike){
    double exerciseValue;
    if(spot>strike){
        exerciseValue = spot - strike;
    }
    else{
        exerciseValue=0;
    }
    return exerciseValue;
}
double calculatePutExerciseValue(double spot, double strike){
    double exerciseValue;
    if(spot<strike){
        exerciseValue = strike - spot;
    }
    else{
        exerciseValue=0;
    }
    return exerciseValue;
}
double generateGaussianNoise(double mu, double sigma)
{
    const double epsilon = 1e-10;
    const double two_pi = 2.0*3.14159265358979323846;
    
    static double z0, z1;
    static bool generate;
    static MTRand drand;
    
    generate = !generate;
    
    if (!generate)
        return z1 * sigma + mu;
    
    double u1, u2;
    do
    {
        u1 = drand() ;
        u2 = drand() ;
    }
    while ( u1 <= epsilon );
    
    z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
    z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
    return z0 * sigma + mu;
}
int main() {
    double dt = 0.25;
    double drift = 0.02;
    double vol = 0.15;
    double u=drift*dt;
    double sigma=vol*sqrt(dt);
    double sumR,S1,call,put,ri,sumS=0,sumCall=0,sumPut=0;
    for(int j=0;j<100000;j++){
        sumR=0;
        for(int i=0;i<4;i++){
            double x = generateGaussianNoise(0, 1);
            ri=(u-0.5*sigma*sigma)+sigma*x;
            sumR=sumR+ri;
        }
        S1=100*exp(sumR);
        sumS=sumS+S1;
        call=calculateCallExerciseValue(S1, 100);
        sumCall=sumCall+call;
        put=calculatePutExerciseValue(S1, 100);
        sumPut=sumPut+put;
        if((j==99||j==999)||(j==9999||j==99999)){
            cout<<"The average stock price is "<<sumS/(j+1)<<" the call price: "<<sumCall/(j+1)<<" the put price: "<<sumPut/(j+1)<<endl;
        }
    }
    return 0;
}
