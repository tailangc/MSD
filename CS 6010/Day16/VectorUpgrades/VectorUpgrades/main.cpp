//
//  main.cpp
//  VectorUpgrades
//
//  Created by Tailang  Cao on 9/13/23.
//

#include <iostream>
#include"helper.hpp"
int main(int argc, const char * argv[]) {
//    myVector v1 = {1,2,3};
//    myVector v2 = {4,5,6};
//    myVector v1 (10);
//    myVector v2 (10);
//
//    for(int i = 1; i < 4; i++){
//        v1.pushBack(i);
//    }
//    for(int i = 3; i < 6; i++){
//        v2.pushBack(i);
//    }
//
//    v1[2] = 4;
//    std::cout << v1[2] << std::endl;
//
//    const int a = v1[2];
//    std::cout << a << std::endl;
//
//    for(int i = 0; i < v1.getSize() ; i++){
//        std::cout << v1.get(i);
//    }
    
    myVector<char> v3 (10);
    myVector<char> v4 (10);
    
    v3.pushBack(12);
    v3.pushBack(12);
    v3[1] = 10;
    v4.pushBack(12);
    v4.pushBack(12);
    v4.pushBack(13);
    // "<<"
    //std::cout << v3
    if(v3[1] == 10){
        std::cout << "the = and [] works!" << std::endl;
    }
    if(v3==v4){
        std::cout << "v3==v4 is true" << std::endl;
    }
    else{
        std::cout << "v3==v4 is false" << std::endl;
    }

    if(v3<v4){
        std::cout << "v3<v4 is true" << std::endl;
    }
    else{
        std::cout << "v3<v4 is false" << std::endl;
    }
    
    if(v3<=v4){
        std::cout << "v3<=v4 is true" << std::endl;
    }
    else{
        std::cout << "v3<=v4 is false" << std::endl;
    }
    
    if(v3>v4){
        std::cout << "v3>4 is true" << std::endl;
    }
    else{
        std::cout << "v3>4 is false" << std::endl;
    }
    
    if(v3>=v4){
        std::cout << "v3>=v4 is true" << std::endl;
    }
    else{
        std::cout << "v3>=v4 is false" << std::endl;
    }
    
    


myVector<double> v5(10);
myVector<double> v6(10);

const double db1 = 0.123;
const double db2 = 0.456;

v5.pushBack(db1);
v6.pushBack(db2);

// "<<"
//std::cout << v3
//if(v5 == v6){
//    std::cout << "the = and [] works!" << std::endl;
//}
if(v5==v6){
    std::cout << "v5==v6 is falsee" << std::endl;
}
else{
    std::cout << "v5==v6 is true" << std::endl;
}

if(v5<v6){
    std::cout << "v5<v6 is true" << std::endl;
}
else{
    std::cout << "v5<v6 is false" << std::endl;
}

if(v5<=v6){
    std::cout << "v5<=v6 is true" << std::endl;
}
else{
    std::cout << "v5<=v6 is false" << std::endl;
}

if(v5>v6){
    std::cout << "v5>6 is true" << std::endl;
}
else{
    std::cout << "v5>6 is false" << std::endl;
}

if(v5>=v6){
    std::cout << "v5>=v6 is true" << std::endl;
}
else{
    std::cout << "v5>=v6 is false" << std::endl;
}

return 0;
}
