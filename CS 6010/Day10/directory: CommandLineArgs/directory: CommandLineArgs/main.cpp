//
//  main.cpp
//  directory: CommandLineArgs
//
//  Created by Tailang  Cao on 9/1/23.
//

#include <iostream>

int main(int argc, const char * argv[]) {
    for (int i = 0; i < argc; i++){
        std::cout << i << argv[i] << "\n";
    }
    return 0;
}
