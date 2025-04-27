#ifndef Neural_Class
#define Neural_Class
#include <vector>
#include "function.h"
#include "matrix.h"
#include "layer.h"
using namespace std;

class Neural{
    private:
        vector<Layer> Layers;
        LossFunction *Loss;
    
    public:
        Neural(initializer_list<int> size);
        Matrix predict(Matrix in);
        double accuracy(Matrix in,Matrix ans);
        void fix(Matrix in, Matrix ans);
        void show();
};

#endif //Neural_Class