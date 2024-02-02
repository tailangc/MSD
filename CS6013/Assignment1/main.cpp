#include <iostream>
#include <sys/time.h>


extern "C" {

void sayHello();
int myPuts( const char* s, int len );
timeval myGTOD();

}

int main () {


    sayHello();
    myPuts("Hello!", 6);
    std::cout<< "\n";

    timeval current = myGTOD();
    std::cout<< "Seconds: " << current.tv_sec << "\n";
    std::cout<< "Microseconds: " << current.tv_usec << "\n";

    timeval currentTime;

    //Calling built in to compare
    gettimeofday(&currentTime, nullptr);
    std::cout << "Seconds: " << currentTime.tv_sec << "\n";
    std::cout << "Microseconds: " << currentTime.tv_usec << "\n";

    return 0;
}
