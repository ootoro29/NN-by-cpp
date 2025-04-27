#ifndef Layer_Class
#define Layer_Class

#include "matrix.h"
#include "function.h"

class Layer{
    private:
        int in_dim;
        int out_dim;
        Matrix *W;
        Matrix *dC_dz;
        Matrix *IN;
        Matrix *z;
        Function *activation_function;
        
    public:
        Layer(int in_dim, int out_dim, Function *activation_function);
        Matrix forward(Matrix x);
        Matrix backward(Matrix dC_dZ, Matrix W);
        Matrix loss(Matrix dC_da);
        Matrix get_weight();
        void fix();
};

#endif //Layer_Class