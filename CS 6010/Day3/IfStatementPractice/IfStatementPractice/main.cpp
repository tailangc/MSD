//
//  main.cpp
//  IfStatementPractice
//
//  Created by Tailang  Cao on 8/22/23.
//


//
//#include <iostream>
//using namespace std;
//int main() {
//    int age;
//    cout << "Please enter your age: \n";
//    cin >> age;
//
//    if(age < 18){
//        cout << "You are underaged for voting and senate.\n";
//    }
//    else if(age >= 18 && age < 30){
//        cout << "You are old enough for vote but not for senate.\n";
//    }
//    else if(age >= 30){
//        cout << "You are old enough for vote and senate.\n";
//    }
//
//    if(age >= 80){
//        cout << "You are part of the greatest generation.\n";
//    }
//    else if(age >= 60 && age < 80){
//        cout << "You are part of the baby bloomers.\n";
//    }
//    else if(age >= 40 && age < 60){
//        cout << "You are aort of the generation X.\n";
//    }
//    else if(age >= 20 && age < 40){
//        cout << "You are part if the millennials.\n";
//    }
//    else{
//        cout << "You are part of the iKid.\n";
//    }
//    return 0;
//}







#include <iostream>
using namespace std;
int main(){
    string is_weekday; string is_holiday; string have_children;

    cout << "Do you have young children? (Type Y for yes and N for no.) \n";
    cin >> have_children;
    if (have_children == "Y")
    {
        cout << "Wake UP!! \n";
    }
    else{
        cout << "Is today a weekday? (Type Y for yes and N for no.) \n";
        cin >> is_weekday;
        if(is_weekday == "N"){
            cout << "You can have a sleep. \n";
        }
        else
        {
            cout << "Is today a holiday? (Type Y for yes and N for no.) \n";
            cin >> is_holiday;
            if (is_holiday == "N")
            {
                cout << "Wake UP!!\n";
            }
            else{
                cout << "You can have a sleep.\n";
            }
        }
    }
    return 0;
    }
