//
//  Polistructs_function.hpp
//  directory: PoliStructs
//
//  Created by Tailang  Cao on 8/29/23.
//
#include <iostream>
#ifndef Polistructs_function_hpp
#define Polistructs_function_hpp

#include <stdio.h>


struct politician{std::string name; std::string party_affiliation; bool is_federal;};

std::vector<politician> Javacans (std::vector<politician> allPoliticians);

std::vector<politician> federalCplusers (std::vector<politician> allPoliticians);



#endif /* Polistructs_function_hpp */






