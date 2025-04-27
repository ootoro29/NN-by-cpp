#include <math.h>
#include "../include/matrix.h"
#include "../include/function.h"

class Identity:public Function{ // 恒等関数
    Matrix f(Matrix x){
        return x;
    }
    Matrix df(Matrix x){
        Matrix dfx(x.get_row(),x.get_row());
        for(int i = 0; i < x.get_row(); i++){
            dfx.set(i, i, 1);
        }
        return dfx;
    }
};

class Sigmoid:public Function{ // 恒等関数
    Matrix f(Matrix x){
        Matrix fx(x.get_row(),1);
        for(int i = 0; i < x.get_row(); i++){
            fx.set(i, 0, 1/(1 + exp(-x[i][0])));
        }
        return fx;
    }
    Matrix df(Matrix x){
        Matrix dfx(x.get_row(),x.get_row());
        Matrix F = identity(this->f(x));
        dfx = (identity(x.get_row()) - F) * (F);
        return dfx;
    }
};

class Relu:public Function{ // 恒等関数
    Matrix f(Matrix x){
        Matrix fx(x.get_row(),1);
        for(int i = 0; i < x.get_row(); i++){
            fx.set(i, 0, (x.get(i,0) > 0)?x.get(i,0):0);
        }
        return fx;
    }
    Matrix df(Matrix x){
        Matrix dfx(x.get_row(),x.get_row());
        for(int i = 0; i < x.get_row(); i++){
            dfx.set(i, i, (x.get(i,0) > 0)?1:0);
        }
        return dfx;
    }
};

class MSE:public LossFunction{
    double f(Matrix x, Matrix y){
        return (((&(x-y))*(x-y))*(1.0/x.get_row())).get(0,0) / (2*x.get_row());
    }
    Matrix df(Matrix x, Matrix y){
        return (x-y)*(1.0/x.get_row());
    }
};
