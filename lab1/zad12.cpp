#include <iostream>
#include <fstream>
#include <time.h>
#include <cmath>
#include <iomanip>

using namespace std;

float M = 0.53125;



float recursive_sum(float*array, int N){
    if(N==1) return array[0];
    int mid = N/2;
    int right = N - mid;
    float leftsum = recursive_sum(array, mid);
    float rightsum = recursive_sum(array+mid, right);
    return  leftsum + rightsum;
}

void fill_array(float*array, int N){
    for(int i=0;i<N;i++){
        array[i]=M;
    }
}

void sum_test(float*array, int N){
    float sum = 0.0;
    for(int i=0;i<N;i++){
        sum+=array[i];
    }
}

float kahan_sum(float*array, int N){
    float sum = 0.0;
    float err = 0.0;
    for(int i =0;i<N;i++){
        float y = array[i] - err;
        float temp = sum + y;
        err = (temp - sum) - y;
        sum = temp;
    }

    return sum;
}

int main(){
    int N = 100000000;
    float*array = new float[N];
    ofstream myfile;

    fill_array(array, N);
    myfile.open("m.csv");

    float sum = 0.0;
    float realval = 0.0;
    float rel = 0.0;
    myfile <<endl;



    for(int i=0;i<N;i++){
        sum+=array[i];
        realval = (i+1)*M;
        rel = abs((realval - sum)/realval);

        if(i%2500 == 0){
            myfile << i << "," << rel <<endl;
        }
    }



    float ab = abs(realval - sum);

    cout<<"The non recursive sum is :" <<sum<<endl;
    cout<<"Recursive sum "<<recursive_sum(array, N)<<endl;
    cout<<"Kahan sum is" << kahan_sum(array,N) <<endl;

    cout<<"-----------------------------------------------------------------------------------" << endl;

    cout<<"Non recursive absolute error "<<ab<<endl;
    cout<<"Non recursive relative error "<<rel*100<<"%"<<endl;



    ab = abs(realval - recursive_sum(array, N));
    rel = abs((realval - recursive_sum(array, N))/realval);
    cout<<"Recursive absolute error"<<ab<<endl;
    cout<<"Recursive relative error"<<rel*100<<"%"<<endl;

    ab = realval - kahan_sum(array, N);
    rel = (realval - kahan_sum(array, N))/realval;

    cout<<"Kahan sum absolute error"<<ab<<endl;
    cout<<"Kahan sum relative error"<<rel*100<<"%"<<endl;


    cout<<"---------------------------------------------------------------------------------------" <<endl;


    clock_t begin = clock();
    sum_test(array, N);

    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout<<"The time of non recursive algorithm"<<elapsed_secs<<endl;

    clock_t begin_rec = clock();
    recursive_sum(array, N);
    clock_t end_rec = clock();
    elapsed_secs = double(end_rec - begin_rec) / CLOCKS_PER_SEC;

    cout<<"The time of recursive algorithm"<<elapsed_secs<<endl;

    begin = clock();
    kahan_sum(array, N);
    end = clock();
    elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;

    cout<<"The time of kahan algorithm"<<elapsed_secs<<endl;


}
