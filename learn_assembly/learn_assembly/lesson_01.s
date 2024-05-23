//
//  lesson_01.s
//  learn_assembly
//
//  Created by Felix on 2024/5/23.
//

#if defined(__arm64__)
.section __TEXT,__text
.globl _asm_main

_asm_main:
    mov x0, #43    // 将42放入 x0 寄存器，作为返回值
    ret            // 返回
#else
.section __TEXT,__text,regular,pure_instructions
.globl _asm_main

_asm_main:
    movl $40, %eax    # 将42放入eax寄存器，作为返回值
    ret               # 返回
#endif


