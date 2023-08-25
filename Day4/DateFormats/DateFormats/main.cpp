//
//  main.cpp
//  DateFormats
//
//  Created by Tailang  Cao on 8/24/23.
//

#include <iostream>

int main() {
    
    std::string USdate, SENdate, month, day;
    std::cout << "Please enter a date: \n";
    std::cin >> USdate;
    
    if(USdate[1] == '/'){                    // turn all kinds of date into mm/dd/yyyy format
        USdate = "0" + USdate;
        if(USdate[4] == '/'){
            USdate = USdate.substr(0,3) + "0" + USdate.substr(3,6);
        }
    }
    
    if(USdate[4] == '/'){
        USdate = USdate.substr(0,3) + "0" + USdate.substr(3,6);
        if(USdate[1] == '/'){
            USdate = "0" + USdate;
        }
    }
    
    if(std::stoi(USdate.substr(0,2)) < 1 || std::stoi(USdate.substr(0,2)) >12 ||std::stoi(USdate.substr(3,2)) <1 || std::stoi(USdate.substr(3,2)) > 31 || std::stoi(USdate.substr(6,4)) < 1000 || std::stoi(USdate.substr(6,4)) > 9999){
        
        std::cout << "Invalid date.\n";
        
        return 0;
    
    }
    
    if(USdate.substr(0,2) == "01"){
        month = "Janurary";
    }
    if(USdate.substr(0,2) == "02"){
        month = "February";
    }
    if(USdate.substr(0,2) == "03"){
        month = "March";
    }
    if(USdate.substr(0,2) == "04"){
        month = "April";
    }
    if(USdate.substr(0,2) == "05"){
        month = "May";
    }
    if(USdate.substr(0,2) == "06"){
        month = "June";
    }
    if(USdate.substr(0,2) == "07"){
        month = "July";
    }
    if(USdate.substr(0,2) == "08"){
        month = "August";
    }
    if(USdate.substr(0,2) == "09"){
        month = "September";
    }
    if(USdate.substr(0,2) == "10"){
        month = "October";
    }
    if(USdate.substr(0,2) == "11"){
        month = "November";
    }
    if(USdate.substr(0,2) == "12"){
        month = "December";
    }
    
    if(std::stoi(USdate.substr(3,2)) < 10){               //Make sure the day is in dd format.
        day = USdate.substr(4,1);
    }
    else{
        day = USdate.substr(3,2);
    }
    
    std::cout << month << " " << day << "," << USdate.substr(6,4) << "\n";
    
    
    // 01/02/1999
    return 0;
}
