//
//  main.cpp
//  learn_opengl
//
//  Created by Felix Ji on 1/5/23.
//


#include <iostream>
#include "lesson_01.hpp"
#include "lesson_02.hpp"

int main(void) {
    int number;
    bool quit = false;
    
    while (!quit) {
        std::cout << "Enter lesson number [1-2]:, quit with 0" << std::endl;
        std::cin >> number;
        switch (number) {
            case 0:
                quit = true;
                break;
            case 1:
                Lesson01::entry();
                break;
            case 2:
                Lesson02::entry();
                break;
        }
    }

}
