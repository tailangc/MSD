//
//  main.cpp
//  ForLoopPractice
//
//  Created by Tailang  Cao on 8/23/23.
//

//#include <iostream>
//using namespace std;
//int main() {
//    int num = 1;
//    while(num <= 10){
//        cout << num << ",";
//        num += 1;
//    }
//    cout << "\n";
//
//
//    for(int nums = 1; nums <= 10; nums += 1){
//        cout << nums << ",";
//    }
//    cout << "\n";
//    return 0;
//}


//#include <iostream>
//using namespace std;
//int main() {
//
//    int num_A; int num_B; int mid;
//    cout << "Please enter two numbers: \n";
//    cin >> num_A >> num_B;
//
//    if(num_A >= num_B){
//        num_A = num_A; num_B = num_B;
//    }
//    else{
//        mid = num_A;
//        num_A = num_B;
//        num_B = mid;
//    }
//
//    for(int num_P = num_B; num_P <= num_A; num_P += 1){
//        cout << num_P << " ";
//    }
//
//    cout << "\n";
//    return 0;
//
//}
//
//
//
//
//#include <iostream>
//using namespace std;
//int main() {
//
//
//    cout << "Print the odd numbers between 1-20. \n";                   //Title
//
//    int num = 1;          //Come up with this idea first
//    while (num <= 20){
//        if(num % 2 == 1){
//            cout << num << " ";
//        }
//        num += 1;
//    }
//    cout << "\n";
//
//    for (int nums = 1; nums <= 20; nums += 2){
//        cout << nums << " ";
//    }
//    cout << "\n";
//    return 0;
//}




//#include <iostream>
//using namespace std;
//int main() {
//    cout << "Sum of positive numbers \n";                   //Title
//    int num = 0; int sum = 0;
//    while(num >= 0){
//        cout << "Enter a number: \n";
//        cin >> num;
//        sum = sum + num;
//    }
//    sum = sum - num;
//    cout << "The sum of the positive numbers is: " << sum << "\n";
//
//    return 0;
//}


//#include <iostream>
//using namespace std;
//int main() {
//    cout << "Multiplication Table \n";                 //Title
//    int y = 1;
//
//    while(y <= 5){                                  //loop for y
//        int x = 1;
//        cout << y << "x" << "*";
//        while(x <= 5){                              //loop for x
//            if(x == 5 && x*y >= 10){                //End of the line for 2 digit numbers
//                cout << x*y << "\n";
//                x += 1;
//            }
//            else if(x == 5){                        //End of the line for 1 digit numbers
//                cout << " " << x*y << "\n";
//                x += 1;
//            }
//            else if(x < 5 && x*y >= 10){            //Other 2 digit numbers
//                cout << x*y << " ";
//                x += 1;
//            }
//            else if(x < 5){                         //Other 1 digit numbers
//                cout << " " << x*y << " ";
//                x += 1;
//            }
//        }
//        y += 1;
//    }
//
//
//    return 0;
//}
