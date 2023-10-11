
![Alt text](images/AD102.png)

## GPU 线程机制

一个GPU中有多个流处理器（Streaming Multiprocesssor，SM），每个SM中有多个 warp，warp是线程簇，每个warp 可以同时并行执行多个线程

GPU 的本质在于并行
CPU 则是尽可能加快指令的运算

## GPU 线程分级

在 AI 计算模式中，不是所有计算都是线程独立的

对一张图片，先用网格 Grip 进行覆盖，切分成多个块 Blocks（相邻 Block 可能会重叠），对每个块独立执行处理。Block 中线程 Threads 通过本地数据共享来计算

Nvidia 的 GPU 中有多个 GPC（Graph Process Cluster）图像处理簇（A100 中有8个）；每个GPC中有多个 TPC（Texture Process Cluster）纹理处理簇；每个 TPC 中有多个 SM；SM中有多个 Block 和 Thread

- GPC（Graph Processing Cluster）：图形处理簇
- TPC（Texture Processing Cluster）：纹理处理簇
- SM（Stream Multiprocessors）：流多处理器

GPC > TPC > SM > CORE（CUDA Tensor core、TR Core）

### SM 流式多处理器

核心组件包括 CUDA 核心、共享内存、寄存器等

- CUDA Core：向量运算单元（FP32-FPU、FP64-DPU、INT32-ALU）
- Tensor Core：张量运算单元（FP16、BF16、INT8、INT4）
- Special Function Units：特殊函数单元SFU（超越函数和数学函数，例如反平方根、正余弦）
- Warp Scheduler：线程束调度器（XX Thread/clock）
- Dispatch Unit：指令分发单元（XX Thread/clock）
- Multi level Catch：多级缓存
- Register File：寄存器堆
- Load/Store：访问存储单元 LD/ST

![](images/Ada%20Streaming%20Multiprocessor.png)

在 CUDA 中的作用：可以并发地执行数百个线程。

一个 block 上线程是放在同一个 SM，SM 的有限 Cache 制约了每个 block 的线程数量

### Warp 线程束

逻辑上，所有 Thread 是并行的，但是，从硬件的角度来说，并不是所有的 Thread 能够在同一时刻执行，这里就需要引入 Warp

通过 Warp 对线程进程锁同步，然后拆解成具体的指令给执行单元去执行

Warp 是 SM 基本执行单元，一个 Warp 包含 32 个并行 Thread，这 32 个 Thread 执行于 SIMT 模式。也就是所有 Thread 以锁同步的方式执行同一条指令，但每个 Thread 会使用各自的 Data 执行指令分支。如果在 Warp 中没有 32 个 Thread 需要工作，那么 War哦 还是作为一个整体运行，但这部分 Thread 是处于非激活状态的

### CUDA

CUDA（Compute Unified Device Architecture）通用并行计算平台和编程模型

是一个并行计算架构和编程模型或者说编程体系

基于 LLVM 构建了 CUDA 编译器，方便开发者使用 C 进程开发。提供了对其他编程语言的支持

CUDA 使软硬件解构，可以独立演进

### 线程层次结构：Kernel

CUDA 引入主机端（host）和设备（device）概念。CUDA程序中既包含 host 程序，又包含 device 程序

相互通信：host和device之间可以进行通信和数据的拷贝

- CUDA 执行流程中最重要的一个过程是调用 CUDA 的 kernel 函数来执行计算，kernel 是 CUDA 中一个重要的概念
- 在 CUDA 程序架构中，Host 代码部分在 CPU 上执行，是普通 C 代码；当遇到数据并行处理的部分，CUDA 就会将程序编译成 GPU 能执行的程序，并传送到 GPU上执行，这个程序在 CUDA 里称作 kernel
- Device 代码部分在 GPU 上执行，此代码部分编写在 kernel 函数中（.cu 文件）。kernel 用 `__global__` 符号声明，在调用时需要使用 `<<<grid, block>>>` 来指定 kernel 要执行

![](images/Thread%20Level.png)

1. 网格 Grid
   - kernel 在 device 上执行时，实际上是启动很多线程，一个kernel所启动的所有线程称为一个网格 Grid
   - 同一个网格上的线程共享相同的全局内存空间
2. 线程块 Block
   - Grid 分为多个 Block，一个 block 里包含很多个线程，block 之间并行执行，并且无法通行，也就没有执行顺序。
   - 每个block 包含共享内存（shared Memory），里面的 Thread 共享这些内存
3. 线程 Thread
   - CUDA 并行程序实际上会被多个 thread 来执行
   - 同一个 block 中 thread 可以同步，也可以通过 Shared Memory 通信

CUDA 跟 NVIDIA 硬件架构的关系

线程块 Block 只在一个 SM 上通过 wrap 进行调度
一旦在 SM 上调起了 block 线程块，就会一直保留到执行完 kernel
SM　可以同时保存多个　Block，快速并行的执行

![Alt text](images/Ada%20GPU%20Architecture.png)