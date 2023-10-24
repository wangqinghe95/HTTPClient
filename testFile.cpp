#include "FileOperation.hpp"
#include <iostream>
int main()
{
    FileOperation CFileOpeartion;
    int status = CFileOpeartion.createFile("./test/test/file.txt");

    if(true == status){
        std::cout << "createFile successfully " << std::endl;
    }
    else {
        std::cout << "createFile failure " << std::endl;
    }

    return 0;
}