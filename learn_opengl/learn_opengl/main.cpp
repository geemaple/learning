//
//  main.cpp
//  learn_opengl
//
//  Created by Felix Ji on 1/5/23.
//


#include <iostream>
#include "lesson_01.hpp"

int main(void) {
    
    int number = 0;
    std::cout << "Enter lesson number: ";
    std::cin >> number;
    
    switch (number) {
        case 1:
            lenson_01_entry();
            break;
        default:
            break;
    }
}
