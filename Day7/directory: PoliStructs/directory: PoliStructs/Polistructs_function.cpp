//
//  Polistructs_function.cpp
//  directory: PoliStructs
//
//  Created by Tailang  Cao on 8/29/23.
//

#include "Polistructs_function.hpp"
#include <iostream>
std::vector<politician> Javacans (std::vector<politician> allPoliticians){
    std::vector<politician> JavacansGroup;
    for (politician politician : allPoliticians){
        if(politician.party_affiliation == "Javacans"){
            JavacansGroup.push_back(politician);
        }
    }
    return JavacansGroup;
}


std::vector<politician> federalCplusers (std::vector<politician> allPoliticians){
    std::vector<politician> fedC_Group;
    for (politician politician : allPoliticians){
        if(politician.is_federal && politician.party_affiliation == "Cplusers"){
            fedC_Group.push_back(politician);
        }
    }
    return fedC_Group;
}
