//
//  main.cpp
//  learn_assembly
//
//  Created by Felix on 2024/5/23.
//

#include <iostream>

extern "C" int asm_main();

int main(int argc, const char * argv[]) {
    // insert code here...
    int ret_status;
    ret_status = asm_main();
    std::cout << "Return status: " << ret_status << std::endl;
    return ret_status;
}
