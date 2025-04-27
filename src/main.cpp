#include "../include/neural.h"
#include "../include/matrix.h"
#include "../include/function.h"
#include "../include/layer.h"
using namespace std;

int main(){
    Neural NN({4, 9, 2});
    //XORさせるやつ
    //vector<Matrix> X = {{0,0},{0,1},{1,0},{1,1}};
    //vector<Matrix> Y = {{0},{1},{1},{0}};

    //ChatGPTに生成させたデータ
    vector<Matrix> X = {
        {{0}, {0}, {0}, {0}},
        {{1}, {2}, {-1}, {0}},
        {{-3}, {0}, {1}, {2}},
        {{5}, {5}, {5}, {5}},
        {{-2}, {-1}, {-3}, {0}},
        {{3}, {0}, {0}, {1}},
        {{2}, {2}, {-2}, {2}},
        {{-1}, {1}, {-1}, {1}},
        {{4}, {1}, {0}, {-2}},
        {{-5}, {-5}, {-5}, {-5}},
        {{1}, {-2}, {3}, {0}},
        {{0}, {3}, {1}, {-1}},
        {{-2}, {2}, {2}, {-2}},
        {{3}, {3}, {-3}, {-3}},
        {{-1}, {0}, {2}, {5}},
        {{5}, {-2}, {-2}, {1}},
        {{0}, {-3}, {4}, {2}},
        {{2}, {2}, {2}, {2}},
        {{-3}, {-1}, {0}, {1}},
        {{1}, {4}, {-1}, {-4}}
    };
    
    vector<Matrix> Y = {
        {{0}, {0}},    // 0000 -> (0,0)
        {{1}, {0}},    // small positive values
        {{0}, {1}},    // some negative + positive
        {{2}, {2}},    // all large positive
        {{-1}, {0}},   // mostly negative
        {{1}, {1}},    // moderate positives
        {{2}, {0}},    // mix with negatives
        {{0}, {0}},    // alternating smalls
        {{2}, {-1}},   // larger mixed
        {{-2}, {-2}},  // all large negatives
        {{1}, {1}},    // weird pattern
        {{0}, {2}},    // some higher outputs
        {{1}, {-1}},   // mixed
        {{0}, {0}},    // cancels out
        {{1}, {2}},    // positive trend
        {{2}, {0}},    // dominant positive
        {{0}, {1}},    // more positive
        {{2}, {2}},    // all same positive
        {{-1}, {1}},   // negative to positive
        {{1}, {-2}}    // positive to negative
    };
    
    cout << "学習前---------------" << endl;
    for(int i = 0; i < X.size(); i++){
        X[i].show();
        NN.predict(X[i]).show();
        cout << "---------------" << endl;
    }
    for(int j = 0; j < 5000; j++){
        for(int i = 0; i < X.size(); i++){
            NN.fix(X[i], Y[i]);
        }
    }
    cout << "学習後---------------" << endl;
    for(int i = 0; i < X.size(); i++){
        X[i].show();
        NN.predict(X[i]).show();
        cout << "---------------" << endl;
    }
    return 0;
}

//g++ main.cpp neural.cpp layer.cpp matrix.cpp function.cpp functions.cpp -o main