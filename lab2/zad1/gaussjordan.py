import numpy as np

def gauss_jordan(a,x):

    n = a.shape[0]
    print("Array before pivoting")
    print(a)

    for i in range(n):
        for k  in range(i+1,n):
            if(a[i][i]<a[k][i]):
                for j in range(n+1):
                    tmp = a[i][j];
                    a[i][j]=a[k][j];
                    a[k][j]=tmp;

    print("Array after pivoting")
    print(a)

    for i in range(n-1):
        for k in range(i+1,n):
            t = a[k][i]/a[i][i];
            for j in range(n+1):
                a[k][j] = a[k][j] - t*a[i][j];

    print("Array after gaussian elimination")
    print(a)



    for i in range(n-1,0,-1):
        for k in range(i-1,-1,-1):
            t = a[k][i]/a[i][i];
            for j in range(n+1):
                a[k][j] = a[k][j] - t*a[i][j];

    print("Array after gaussian elimination up")
    print(a)

    for s in range(n):
        for j in range(n,-1,-1):
            a[s][j] = a[s][j]/a[s][s];
        x[s] = a[s][n]

    print(x)
    return

a= np.array([[0.,2.,1.,-8.],[1.,-2.,-3.,0.],[-1.,1.,2.,3.]]);
x=np.array([0.,0.,0.]);
gauss_jordan(a,x)

n=10
b= np.random.rand(n,n+1);
y= np.zeros(n);

gauss_jordan(b,y)
