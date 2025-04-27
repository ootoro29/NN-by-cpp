#include "../include/neural.h"
#include "../include/matrix.h"
#include "../include/layer.h"
#include "functions.cpp"
using namespace std;

Neural::Neural(initializer_list<int> size){
    if(size.size() <= 2){
        std::cout << "サイズが不正です"  << endl;
        return;
    };
    vector<int> length(size.size());
    for(int i = 0 ; i < size.size(); i++){
        length[i] = *(size.begin() + i);
    }
    this->Layers.push_back(Layer(length[0]+1, length[1], new Relu()));
    for(int i = 1; i < length.size()-2; i++){
        this->Layers.push_back(Layer(length[i]+1, length[i+1], new Relu()));
    }
    this->Layers.push_back(Layer(length[length.size()-2]+1, length[length.size()-1], new Identity()));
    this->Loss = new MSE();
}

Matrix Neural::predict(Matrix in){
    Matrix out(in);
    for(int i = 0; i < this->Layers.size(); i++){
        out = (this->Layers[i]).forward(out);
    }
    return out;
}

void Neural::fix(Matrix in, Matrix ans){
    Matrix P = this->predict(in);
    Matrix dC_da = this->Loss->df(P, ans);
    Matrix *D = new Matrix(this->Layers[this->Layers.size()-1].loss(dC_da));
    for(int i = this->Layers.size()-2; i >= 0; i--){        
        D = new Matrix(this->Layers[i].backward(*D, this->Layers[i+1].get_weight()));
    }
    double A = this->accuracy(in,ans);
    for(int i = 0; i < this->Layers.size(); i++){
        this->Layers[i].fix();
    }
    double B = this->accuracy(in,ans);
}

void Neural::show(){
    for(int i = 0; i < this->Layers.size(); i++){
        Layers[i].get_weight().show();
    }
}

double Neural::accuracy(Matrix in,Matrix ans){
    Matrix out = this->predict(in);
    return this->Loss->f(out, ans);
}