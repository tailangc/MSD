//
//  main.cpp
//  RoadTripCalculator
//
//  Created by Tailang  Cao on 8/22/23.
//

#include <iostream>
using namespace std;
int main() {
    // insert code here...
    float driving_distance;
    float miles_per_gallon;
    float dollars_per_gallon;
    
    cout << "Enter the driving distance:" << "\n";
    cin >> driving_distance;
    cout << "Enter the miles per gallon:" << "\n";
    cin >> miles_per_gallon;
    cout << "Enter the dollars per gallon" << "\n";
    cin >> dollars_per_gallon;
    
    float number_of_gallons = driving_distance/miles_per_gallon;
    float cost = number_of_gallons*dollars_per_gallon;
    
    cout << "the cost of your road trip will be: $" << cost << "\n\n" ;
    
    return 0;
}
