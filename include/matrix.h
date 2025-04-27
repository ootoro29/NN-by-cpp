#ifndef Matrix_Class
#define Matrix_Class

#include <iostream>
#include <vector>
#include <array>
#include <random>
#include <math.h>
using namespace std;

class Matrix{
    public:
        Matrix(int row,int column);
        Matrix(const Matrix& c);
        Matrix(initializer_list<double> A);
        Matrix(initializer_list<vector<double>> A);
        void resize();
        bool is_squared();
        void initialize();
        void show();
        void show_info();
        void swap_elems(int i1, int j1,int i2, int j2);
        void swap_rows(int i, int j);
        void set(int i, int j, double value);
        double get(int i, int j);
        int get_row();
        int get_column();
        void random();
    private:
        int column = 30,row = 30; 
        double* val;
    public:
        Matrix& operator =(Matrix& m);
        Matrix& operator =(const Matrix& m);
        Matrix operator +(Matrix m);
        Matrix operator !();
        Matrix operator&();
        Matrix operator -(Matrix m);
        Matrix operator *(Matrix m);
        Matrix operator *(double c);
        Matrix &operator =(initializer_list<double> A);
        Matrix &operator =(double* A);
        double* operator [](int index);
        double operator ()(int c,int r);
};
void preview_Ax_is_B(Matrix A, Matrix B);
Matrix gauss_method(Matrix A, Matrix B);
Matrix LU(Matrix A);
void LU(Matrix A,Matrix* outL,Matrix* outU);
Matrix LU_Crout(Matrix A);
Matrix Polynomial_Least_Squares(int d,Matrix Data);
Matrix Polynomial_Least_Squares(vector<int> d,Matrix Data);
Matrix identity(int n);
Matrix identity(Matrix x);


#endif //Matrix_Class