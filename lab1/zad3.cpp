#include <iostream>
#include <fstream>
#include <time.h>
#include <cmath>
#include <iomanip>

using namespace std;


double riemann_func_double(double s, int N){
    double sum = 0.0;

    for(int k = 1; k <= N; k++){
        sum += 1/pow(k,s);
    }

    return sum;
}

float riemann_func(float s, int N){
    float sum = 0.0;

    for(int k = 1; k <= N; k++){
        sum += 1/pow(k,s);
    }

    return sum;
}

float riemann_func_bcwrds_float(float s, int N){
    float sum =0.0;

    for(int k= N;k>=1;k--){
        sum+=1/pow(k,s);
    }

    return sum;
}

double riemann_func_bcwrds_double(double s, int N){
    double sum =0.0;

    for(int k= N;k>=1;k--){
        sum+=1/pow(k,s);
    }

    return sum;
}

float dirichlet_func(float s, int N){
    float sum = 0.0;

    for(int k = 1; k <= N; k++){
        sum += pow(-1.0, k-1)*1/pow(k,s);
    }

    return sum;
}

double dirichlet_func_double(double s, int N){
    double sum = 0.0;

    for(int k = 1; k <= N; k++){
        sum += pow(-1.0, k-1)*1/pow(k,s);
    }

    return sum;
}

float dirichlet_func_bcwrds(float s, int N){
    float sum = 0.0;

    for(int k = N; k >=1; k--){
        sum += pow(-1.0, k-1)*1/pow(k,s);
    }

    return sum;
}

double dirichlet_func_bcwrds_double(double s, int N){
    float sum = 0.0;

    for(int k = N; k >=1; k--){
        sum += pow(-1.0, k-1)*1/pow(k,s);
    }

    return sum;
}

int main(){

float s [] = {2,3.6667,5,7.2,10};
int n [] = {50,100,200,500,1000};
double s2[] = {2,3.6667,5,7.2,10};
int n2[] = {50,100,200,500,1000};

for(int i=0;i<5;i++){
    for(int j=0;j<5;j++){
        cout<<"||Values "<<s[i] <<":" <<n[j]<<"||"<<endl;
        cout<<"Riemman function float  "<<setprecision(15)<< riemann_func(s[i],n[j])<<endl;
        cout<<"Riemman function double" << riemann_func_double(s2[i],n2[j])<<endl;
        cout<<"Riemman function backwards float " << riemann_func_bcwrds_float(s[i],n[j])<<endl;
        cout<<"Riemman function backwards double " << riemann_func_bcwrds_double(s2[i],n2[j])<<endl;
        cout<<endl;


        cout<<"Dirichlet function float " << dirichlet_func(s[i],n[j])<<endl;
        cout<<"Dirichlet function double" << dirichlet_func_double(s2[i],n2[j])<<endl;
        cout<<"dirichlet function backwards float" <<dirichlet_func_bcwrds(s[i],n[j])<<endl;
        cout<<"dirichlet function backwards float" <<dirichlet_func_bcwrds_double(s2[i],n2[j])<<endl;
        cout<<endl;
    }
}

}
