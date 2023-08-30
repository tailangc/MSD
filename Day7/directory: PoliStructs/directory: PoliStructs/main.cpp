//
//  main.cpp
//  directory: PoliStructs
//
//  Created by Tailang  Cao on 8/29/23.
//

#include <iostream>
#include "Polistructs_function.hpp"


void ErrorExit(std::string message){
  std::cerr << "Failed test: " << message << std::endl;
  exit(1);
}


int main() {
     
    
    
    std::vector<politician> allPoliticians;
    politician A, B, C, D;
    A.name = "AA";
    A.party_affiliation = "Javacans";
    A.is_federal = true;
    B.name = "BB";
    B.party_affiliation = "Cplusers";
    B.is_federal = true;
    C.name = "CC";
    C.party_affiliation = "Cplusers";
    C.is_federal = false;
    D.name = "DD";
    D.party_affiliation = "Javacans";
    D.is_federal = true;
    
    allPoliticians = {A, B, C, D};
    
    std::vector<politician> JavacansGroup = Javacans(allPoliticians);
    std::vector<politician> fedC_Group = federalCplusers(allPoliticians);
    
    for (politician javapo : JavacansGroup){
        if ((javapo.name != "AA" && javapo.name != "DD") || javapo.name == "BB" || javapo.name == "CC"){
            ErrorExit( "incorrect Javacans member" );
        }
    }
    
    for (politician fedCpo : fedC_Group){
        if (fedCpo.name != "BB" || fedCpo.name == "AA" || fedCpo.name == "CC" || fedCpo.name == "DD"){
            ErrorExit("incorrect Federal Cplusers Group");
        }
    }
    std::cout << "your function is correct.\n";
//    assert()

    return 0;
}
