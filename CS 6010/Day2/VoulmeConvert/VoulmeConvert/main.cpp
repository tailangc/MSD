//
//  main.cpp
//  VoulmeConvert
//
//  Created by Tailang  Cao on 8/22/23.
//

#include <iostream>
using namespace std;
int main() {
    // insert code here...
    double volume_in_ounces;
    cout << "Enter volume in ounces: \n" ;
    cin >> volume_in_ounces;
    cout << "\n";
    
    double cups; double pints; double gallons; double liters; double cubic_inches;
    
    cups = volume_in_ounces / 8;
    pints = volume_in_ounces / 16;
    gallons = volume_in_ounces / 128;
    liters =  volume_in_ounces * 0.0296;
    cubic_inches = volume_in_ounces * 1.8;
    
    cout << "Ounces: " << volume_in_ounces << "\n";
    cout << "Cups: " << cups << "\n";
    cout << "Pints: " << pints << "\n";
    cout << "Gallons: " << gallons << "\n";
    cout << "Liters: " << liters << "\n";
    cout << "Cubic Inches: " << cubic_inches << "\n\n";
    
    return 0;

}
