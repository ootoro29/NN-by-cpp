#ifndef Function_Class
#define Function_Class
#include "matrix.h"

class Function{
    public:    
        virtual Matrix f(Matrix x);
        virtual Matrix df(Matrix x);
};

class LossFunction{
    public:    
        virtual double f(Matrix x, Matrix y);
        virtual Matrix df(Matrix x, Matrix y);
};


#endif //Function_Class