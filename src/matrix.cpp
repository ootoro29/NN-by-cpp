#include <iostream>
#include "../include/matrix.h"
#include <vector>
#include <array>
#include <random>
#include <math.h>
using namespace std;

Matrix::Matrix(int row,int column){
    this->row = row;
    this->column = column;
    resize();
}

Matrix::Matrix(const Matrix& c){
    column = c.column;
    row = c.row;
    resize();
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            *(val+i*column+j) = *(c.val+i*column+j);
        }
    }
}

Matrix::Matrix(initializer_list<double> A){
    auto itr = A.begin();
    column = 1;
    row = A.size();
    resize();
    for(int i = 0; i < A.size(); i++){
        *(val+i) = *(itr+i);
    }
}
Matrix::Matrix(initializer_list<vector<double>> A){
    auto itr = A.begin();
    int max_column = 1;
    for(int i = 0; i < A.size(); i++){
        if((*(itr+i)).size() > max_column)max_column = (*(itr+i)).size();
    }
    row = A.size();
    column = max_column;
    resize();
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            *(val+i*column+j) = *((*(itr+i)).begin() + j);
        }
    }
}

void Matrix::resize(){
    val = new double[column*row];
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            *(val + i*column + j) = 0;
        }
    }
}

bool Matrix::is_squared(){
    return row == column;
}

void Matrix::initialize(){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            *(val+i*column+j) = 0;
        }
    }
}

void Matrix::show(){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            printf("%.10lf\t",*(val+i*column+j));
            //cout << *(val+i*column+j) << " ";
        }
        std::cout << endl;
    }
}
void Matrix::show_info(){
    std::cout <<this->get_row() <<","<< this->get_column()<<endl;
}
void Matrix::swap_elems(int i1, int j1,int i2, int j2){
    double tmp = get(i1,j1);
    set(i1,j1,get(i2,j2));
    set(i2,j2,tmp);
    
}
void Matrix::swap_rows(int i, int j){
    for(int k = 0; k < column; k++){
        swap_elems(i,k,j,k);
    }
}

void Matrix::set(int i, int j, double value){
    *(val+i*column+j) = value;
}
double Matrix::get(int i, int j){
    double tmp = *(val+i*column+j);
    return tmp;
}
int Matrix::get_row(){
    return row;
}
int Matrix::get_column(){
    return column;
}
void Matrix::random(){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dist(-1, 1);
    for(int i = 0; i < get_row(); ++i) {
        for(int j = 0; j < get_column(); ++j) {
            set(i,j,dist(gen));
        }
    }
}
Matrix& Matrix::operator =(Matrix& m){
    row = m.row;
    column = m.column;
    resize();
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            *(val+i*column+j) = *(m.val+i*column+j);
        }
    }
    return *this;
}

Matrix& Matrix::operator =(const Matrix& m){
    row = m.row;
    column = m.column;
    resize();
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            *(val+i*column+j) = *(m.val+i*column+j);
        }
    }
    return *this;
}

Matrix Matrix::operator +(Matrix m){
    Matrix ans(row,column);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            ans.set(i,j,m(i,j)+*(val+i*column+j));
        }
    }
    return ans;
}

Matrix Matrix::operator !(){
    Matrix A = *this;
    if(!A.is_squared()){
        cout << "A is not squared matrix" << endl;
        return A;
    }
    int n = A.get_row();
    Matrix E(n,n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(i != j)E.set(i,j,0);
            else E.set(i,j,1);
        }
    }
    for(int k = 0; k < n; k++){
        int pivot = k;
        for(int i = k+1; i < n; i++){
            if(abs(A(i,k)) > abs(A(pivot,k))){
                pivot = i;
            }
        }
        if(A(pivot,k) == 0){
            cout << "Can't solve" << endl;
            return A;
        }
        if(pivot != k){
            A.swap_rows(pivot,k);
            E.swap_rows(pivot,k);
        }
        //前進消去
        for(int i = k + 1; i < n; i++){
            double m = A(i,k)/A(k,k);
            A.set(i,k,0);
            for(int j = k+1; j < n; j++){
                A.set(i,j,A(i,j)-m*A(k,j));
            }
            for(int j = 0; j < n; j++){
                E.set(i,j,E(i,j)-m*E(k,j));
            }
        }
    }

    Matrix X(n,n);
    for(int k = 0; k < n; k++){
        X.set(n-1,k,E(n-1,k)/A(n-1,n-1));
        for(int i = n-2; i >= 0; i--){
            double sum = 0;
            for(int j = i+1; j < n; j++){
                sum += A(i,j)*X(j,k);
            }
            X.set(i,k,(E(i,k) - sum) / A(i,i));
        }
    }
    return X;
}

Matrix Matrix::operator&(){
    Matrix A(column,row);
    for(int i = 0; i < column; i++){
        for(int j = 0; j < row; j++){
            A.set(i,j,get(j,i));
        }
    }
    return A;
}

Matrix Matrix::operator -(Matrix m){
    Matrix ans(row,column);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            ans.set(i,j,*(val+i*column+j)-m(i,j));
        }
    }
    return ans;
}
Matrix Matrix::operator *(Matrix m){
    if(column != m.row)cout << "error" << endl;
    Matrix ans(row,m.column);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < m.column; j++){
            double sum = 0;
            for(int k = 0; k < column; k++){
                sum += (get(i,k))*m(k,j);
            }
            ans.set(i,j,sum);
        }
    }
    return ans;
}
Matrix Matrix::operator *(double c){
    Matrix ans(row,column);
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            ans.set(i,j,c*get(i,j));   
        }
    }
    return ans;
}
Matrix &Matrix::operator =(initializer_list<double> A){
    auto itr = A.begin();
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            *(val+i*column+j) = *(itr+i*column+j);
        }
    }
    return *this;
}
Matrix &Matrix::operator =(double* A){
    for(int i = 0; i < row; i++){
        for(int j = 0; j < column; j++){
            *(val+i*column+j) = *(A+i*column+j);
        }
    }
    return *this;
}

double* Matrix::operator [](int index){
    return (val+index);
}
double Matrix::operator ()(int c,int r){
    double data = get(c,r);
    return data;
}

void preview_Ax_is_B(Matrix A, Matrix B){
    cout << "========================================================================================"<<endl;
    for(int i = 0; i < A.get_row(); i++){
        for(int j = 0; j < A.get_column(); j++){
            printf("%lf\t",A.get(i,j));    
        }
        printf("|\t%lf",B.get(i,0));
        cout << endl;
    }
    cout << "========================================================================================"<<endl;
}


Matrix gauss_method(Matrix A, Matrix B){
    if(!A.is_squared()){
        cout << "A is not squared matrix" << endl;
        return A;
    }
    int n = A.get_row();
    for(int k = 0; k < n; k++){
        int pivot = k;
        for(int i = k+1; i < n; i++){
            if(abs(A(i,k)) > abs(A(pivot,k))){
                pivot = i;
            }
        }
        if(A(pivot,k) == 0){
            cout << "Can't solve" << endl;
            return A;
        }
        if(pivot != k){
            A.swap_rows(pivot,k);
            B.swap_rows(pivot,k);

            preview_Ax_is_B(A,B);
        }
        //前進消去
        for(int i = k + 1; i < n; i++){
            double m = A(i,k)/A(k,k);
            A.set(i,k,0);
            for(int j = k+1; j < n; j++){
                A.set(i,j,A(i,j)-m*A(k,j));
            }
            B.set(i,0,B(i,0)-m*B(k,0));

            preview_Ax_is_B(A,B);
        }
    }

    //後退代入
    Matrix X(n,1);
    X.set(n-1,0,B(n-1,0)/A(n-1,n-1));
    for(int i = n-2; i >= 0; i--){
        double sum = 0;
        for(int j = i+1; j < n; j++){
            sum += A(i,j)*X(j,0);
        }
        X.set(i,0,(B(i,0) - sum) / A(i,i));
    }
    return X;
}

Matrix LU(Matrix A){
    if(!A.is_squared()){
        cout << "A is not squared matrix" << endl;
        return A;
    }
    int n = A.get_row();
    Matrix L(n,n);
    for(int i = 0; i < n; i++){
        L.set(i,i,1);
    }
    Matrix U = A;
    for(int k = 0; k < n; k++){
        for(int i = k+1; i < n; i++){
            L.set(i,k,U.get(i,k)/U.get(k,k));
            for(int j = k; j < n; j ++){
                U.set(i,j,U.get(i,j)-L.get(i,k)*U.get(k,j));
            }
        }
    }
    cout << "========================================================================================"<<endl;
    L.show();
    cout << "========================================================================================"<<endl;
    cout << "========================================================================================"<<endl;
    U.show();
    cout << "========================================================================================"<<endl;
    return L;
}

void LU(Matrix A,Matrix* outL,Matrix* outU){
    if(!A.is_squared()){
        cout << "A is not squared matrix" << endl;
        return;
    }
    int n = A.get_row();
    Matrix L(n,n);
    for(int i = 0; i < n; i++){
        L.set(i,i,1);
    }
    Matrix U = A;
    for(int k = 0; k < n; k++){
        for(int i = k+1; i < n; i++){
            L.set(i,k,U.get(i,k)/U.get(k,k));
            for(int j = k; j < n; j ++){
                U.set(i,j,U.get(i,j)-L.get(i,k)*U.get(k,j));
            }
        }
    }

    *outL = L;
    *outU = U;
    
}

Matrix LU_Crout(Matrix A){
    if(!A.is_squared()){
        cout << "A is not squared matrix" << endl;
        return A;
    }
    int n = A.get_row();
    Matrix L(n,n);
    Matrix U(n,n);
    for(int i = 0; i < n; i++){
        U.set(i,i,1);
    }
    for(int k = 0; k < n; k++){
        for(int i = k; i < n; i++){
            L.set(i,k,A.get(i,k));
            for(int j = 0; j < k; j ++){
                L.set(i,k,L.get(i,k)-L.get(i,j)*U(j,k));
            }
        }
        for(int j = k+1; j < n; j++){
            U.set(k,j,A.get(k,j));
            for(int i = 0; i < k; i++){
                U.set(k,j,U.get(k,j)-L.get(k,i)*U.get(i,j));
            }
            U.set(k,j,U.get(k,j)/L.get(k,k));
        }
    }
    cout << "========================================================================================"<<endl;
    L.show();
    cout << "========================================================================================"<<endl;
    cout << "========================================================================================"<<endl;
    U.show();
    cout << "========================================================================================"<<endl;
    return L;
}

Matrix Polynomial_Least_Squares(int d,Matrix Data){
    if(Data.get_column() != 2){
        cout << "muri" << endl;
    }
    int n = Data.get_row();
    Matrix X(n,d);
    for(int i = 0; i < d; i++){
        for(int j = 0; j < n; j++){
            X.set(j,i,pow(Data.get(j,0),i));
        }
    }
    Matrix Y(n,1);
    for(int i = 0; i < n; i++){
        Y.set(i,0,Data.get(i,1));
    }
    //(&X*Y).show();
    //((!(&X*X))*(&X*Y)).show();
    Matrix A = (!(&X*X))*(&X*Y);
    return A;
}

Matrix Polynomial_Least_Squares(vector<int> d,Matrix Data){
    if(Data.get_column() != 2){
        cout << "muri" << endl;
    }
    int n = Data.get_row();
    Matrix X(n,d.size());
    for(int i = 0; i < d.size(); i++){
        for(int j = 0; j < n; j++){
            X.set(j,i,pow(Data.get(j,0),d[i]));
        }
    }
    Matrix Y(n,1);
    for(int i = 0; i < n; i++){
        Y.set(i,0,Data.get(i,1));
    }
    Matrix A = (!(&X*X))*(&X*Y);
    return A;
}

Matrix identity(int n){
    Matrix M(n,n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            M.set(i,j,(i==j)?1:0);
        }
    }
    return M;
}

Matrix identity(Matrix x){
    Matrix M(x.get_row(), x.get_row());
    for(int i = 0; i < x.get_row(); i++){
        for(int j = 0; j < x.get_row(); j++){
            M.set(i,j,(i==j)?x.get(i,0):0);
        }
    }
    return M;
}