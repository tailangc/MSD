//
//  main.cpp
//  GiveChange
//
//  Created by Tailang  Cao on 8/22/23.
//

#include <iostream>
using namespace std;
int main() {
    // insert code here...
    int price_in_cents;
    int paid_in_cents;
    int change;
    int quarters;
    int dimes;
    int nickles;
    int pennies;
    int change_remain;
    
    cout << "Enter item price in cents: \n";
    cin >> price_in_cents;
    
    cout << "\n Enter amount paid in cents: \n";
    cin >> paid_in_cents;
    
    change = paid_in_cents - price_in_cents;
    quarters = change / 25;
    change_remain = change - quarters * 25;
    dimes = change_remain / 10;
    change_remain = change_remain - dimes * 10;
    nickles = change_remain / 5;
    change_remain = change_remain - nickles * 5;
    pennies = change_remain;
    
    cout << "Change = " << change << "cents \n";
    cout << "Quarters: " << quarters << "\n";
    cout << "Dimes: " << dimes << "\n";
    cout << "Nickles: " << nickles << "\n";
    cout << "Pennies: " << pennies << "\n\n";
    
    return 0;
}
