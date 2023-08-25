//
//  main.cpp
//  FunctionPractice
//
//  Created by Tailang  Cao on 8/25/23.
//

#include <iostream>

float hypo_length (float s_1, float s_2) {
     float hypo = std::sqrt(s_1*s_1 + s_2*s_2);
    return hypo;
}

int main() {
    float side_1, side_2;
    std::cout << "Please enter the two right-andgle side length of a triangle: \n";
    std::cin >> side_1 >> side_2;

    std::cout << "The length of the hypotenuse is: ";
    std::cout << hypo_length (side_1 , side_2) << "\n";

    return 0;
}


//#include <iostream>
//
//double x_velo (double speed, double angle){
//    double x = speed*cos(angle);
//    return x;
//}
//
//double y_velo (double speed, double angle){
//    double y = speed*sin(angle);
//    return y;
//}
//
//int main() {
//    double speed_enter, angle_enter, x, y;
//    std::cout << "Please enter the speed you are going: \n";
//    std::cin >> speed_enter;
//    std::cout << "Please enter the angle you are going: \n";
//    std::cin >> angle_enter;
//
//    x = x_velo(speed_enter, angle_enter);
//    y = y_velo(speed_enter, angle_enter);
//
//    std::cout << "The x velocity is: " << x << "\n";
//    std::cout << "The y velocity is: " << y << "\n";
//
//    return 0;
//}




//#include <ctime>
//#include <iostream>
//
//int main()
//{
//    std::time_t result = std::time(nullptr);
//    std::cout << std::asctime(std::localtime(&result))
//              << result << " seconds since the Epoch\n";
//}
// The function being called is nullptr



//#include <iostream>
//
//float hypo_length (float s_1, float s_2) {
//     float hypo = std::sqrt(s_1*s_1 + s_2*s_2);
//    return hypo;
//}
//
//int main(){
//    float side_1, side_2;
//    side_1 = 5; side_2 = 4;
//    std::cout << hypo_length (side_1 , side_2) << "\n";
//
//    return 0;
//}


//#include <iostream>
//
//
//bool isCapitalized (std::string word){
//
//    return (isupper(word[0]) != 0);
//}
//
//
//std::string boolToString (bool isCapitalize){
//    if (isCapitalize){
//        return "True";
//    }
//    else{
//        return "False";
//    }
//}
//
//
//int main(){
//    std::string word;
//    std::cout << "Enter something: \n";
//    std::cin >> word;
//    std::cout << boolToString(isCapitalized(word)) << "\n";
//
//    return 0;
//}



#include <iostream>

bool isPrime (int num){
    std::cout << "Enter a number: \n";
    std::cin >> num;
    
    for (int i = 2; i <= num/2; i +=1) {
        if (num % i == 0){
            return false;
            }
        }
    
    return true;
    
    

    
}
