//
//  main.cpp
//  learn_opengl
//
//  Created by Felix Ji on 1/5/23.
//


#include <iostream>
#include "lesson_01_window.hpp"
#include "lesson_02_triangle.hpp"
#include "lesson_03_rectangle.hpp"

int main(void) {
    bool quit = false;
    while (!quit) {
        int number = -1;
        std::cout << "Enter lesson number:, quit with 0" << std::endl;
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
            case 3:
                Lesson03::entry();
                break;
        }
    }

}
