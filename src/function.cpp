#include "../include/function.h"
#include "../include/matrix.h"

Matrix Function::f(Matrix x){
    return x;
}

Matrix Function::df(Matrix x){
    return x;
}

double LossFunction::f(Matrix x, Matrix y){
    return 0;
}

Matrix LossFunction::df(Matrix x, Matrix y){
    return x - y;
}