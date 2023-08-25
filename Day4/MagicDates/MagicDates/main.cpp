//
//  main.cpp
//  MagicDates
//
//  Created by Tailang  Cao on 8/24/23.
//

#include <iostream>

int main() {
    std::string date, month, day;
    int last_two_digits, month_num, day_num;

    std::cout << "Please enter a date: \n";
    std::cin >> date;

    if(date[1] == '/'){                  // turn all kinds of date into mm/dd/yyyy format
        date = "0" + date;
        if(date[4] == '/'){
            date = date.substr(0,3) + "0" + date.substr(3,6);
        }
    }
    
    if(date[4] == '/'){
        date = date.substr(0,3) + "0" + date.substr(3,6);
        if(date[1] == '/'){
            date = "0" + date;
        }
    }

    if(std::stoi(date.substr(0,2)) < 1 || std::stoi(date.substr(0,2)) >12 ||std::stoi(date.substr(3,2)) <1 || std::stoi(date.substr(3,2)) > 31 || std::stoi(date.substr(6,4)) < 1000 || std::stoi(date.substr(6,4)) > 9999){

        std::cout << "Invalid date.\n";


    }



    month_num = std::stoi(date.substr(0,2));
    day_num = std::stoi(date.substr(3,2));
    last_two_digits = std::stoi(date.substr(8,2));

    if(last_two_digits == day_num * month_num){
        std::cout << date << " IS a magic date";
    }

    else{
        std::cout << date << " is NOT a magic date";
    }

    return 0;
}





