

## GPU

### SIMT

Single Instruction, Multiple Threads

- 一个 PC，控制多个执行流同时执行
- 逻辑线程可以更多
执行流有独立的寄存器
- x, y, z 三个寄存器用于标记“线程号”，决定线程执行的动作

SIMD

Single Instruction, Multiple Data

Tensor 指令（Tensor Core）：混合精度 A x B + C
单条指令完成 4x4x4 个乘法运算
