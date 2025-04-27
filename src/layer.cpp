#include "../include/layer.h"
#include "../include/function.h"
#include "../include/matrix.h"

Layer::Layer(int in_dim, int out_dim, Function *activation_function){
    this->W = new Matrix(out_dim, in_dim); //デフォルトコンストラクタを作ってないからポインタにして逃げてる
    this->activation_function = activation_function;
    this->W->random();
}

Matrix Layer::forward(Matrix x){
    Matrix X(x.get_row()+1,1);
    for(int i = 0; i < x.get_row(); i++){
        X.set(i, 0, x.get(i,0));
    }
    X.set(x.get_row(), 0, 1);
    this->IN = new Matrix(X);
    this->z = new Matrix(*(this->W) * X);
    Matrix OUT(this->activation_function->f(*z));
    return  OUT;
}

Matrix Layer::backward(Matrix dC_dZ, Matrix W){// Wは前の層の重み配列
    Matrix da_dz(this->activation_function->df(*z));
    Matrix dZ_da(&(W));
    this->dC_dz = new Matrix(da_dz * dZ_da * dC_dZ);
    return *this->dC_dz;
}

void Layer::fix(){
    Matrix X((*(this->dC_dz)) * (&*(this->IN)));
    Matrix fixedW(*(this->W) - (X*0.01));
    for(int i = 0; i < this->W->get_row(); i++){
        for(int j = 0; j < this->W->get_column(); j++){
            this->W->set(i,j,fixedW.get(i,j));
        }
    }
}

Matrix Layer::loss(Matrix dC_da){
    Matrix da_dz(this->activation_function->df(*z));
    this->dC_dz = new Matrix(da_dz*dC_da);
    return *(new Matrix(*(this->dC_dz)));
}
Matrix Layer::get_weight(){ // dZ_daはbの要素が要らない
    Matrix w(this->W->get_row(),this->W->get_column()-1);
    for(int i = 0; i < this->W->get_row(); i++){
        for(int j = 0; j < this->W->get_column()-1; j++){
            w.set(i,j,this->W->get(i,j));
        }
    }
    return w;
}