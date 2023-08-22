//
//  main.cpp
//  Average
//
//  Created by Tailang  Cao on 8/22/23.
//

#include <iostream>
using namespace std;
int main() {
    // insert code here...
    float score_1; float score_2; float score_3; float score_4; float score_5;
    float score_average;
    
    cout << "Enter 5 assignment scores: \n";
    cin >> score_1 >> score_2 >> score_3 >> score_4 >> score_5;
    
    score_average = (score_1 + score_2 + score_3 + score_4 + score_5)/5;
    cout << "Average:" << score_average << "\n";
    
    return 0;
}
