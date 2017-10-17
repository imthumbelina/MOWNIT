#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;
double eps = 1e-6;

float iterate(float r, float x){
    return r*x*(1-x);
}

float iterating(float r, float x, int n){
    for(int i = 0; i <n ;i++){
        x = iterate(r, x);
    }
    return x;
}

float iterating_zero(float r, float x, int n, ofstream  & popfile){

    float x0 = x;
    bool died = false;
    for(int i = 0; i< n && !died; i++){
        x = iterate(r, x);
        if(abs(x) < eps){
            cout<<"Population died in " << i << "generation"<<endl;
            popfile << x0 <<"," << i <<endl;
            died = true;
        }
    }
    if(!died){
        cout<<"Population have not died"<<endl;
    }
    return x;
}

double iterate_double(double r, double x){
    return r*x*(1-x);
}

double iterating_double(double r, double x, int n){
    for(int i = 0; i <n ;i++){
        x = iterate_double(r, x);
    }
    return x;
}


int main() {

    ofstream csvfile, doublefile, populationfile;

    csvfile.open("diagram.csv");
    doublefile.open("doublefile.csv");
    populationfile.open("population.csv");

    csvfile << endl;
    doublefile <<endl;

    //zadanie 4.1

    for(float i = 0; i< 4 ; i+= 0.01 ){
        float h = iterating(i, 0.01, 1000);
        for(int j = 0; j< 100 ; j++){
            h = iterate(i, h);
        }
    }

    //zadanie 4.2

    for(float i = 3.75; i<= 3.8 ; i+= 0.0001 ){
        float h = iterating(i, 0.5, 1000);
        for(int j = 0; j< 100 ; j++){
            csvfile << h << ",";
            csvfile << i <<endl;
            h = iterate(i, h);
        }
    }

    for(double i = 3.75; i<= 3.8 ; i+= 0.0001 ){
        double h = iterating_double(i, 0.5, 1000);
        for(int j = 0; j< 100 ; j++){
            doublefile << h << ",";
            doublefile << i <<endl;
            h = iterate_double(i, h);
        }
    }

    //zadanie 4.3

    for(float i = 0; i < 1 ; i+=0.001) {
        iterating_zero(4, i, 1000000,populationfile);
    }



}
