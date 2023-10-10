

## GPU 线程机制

一个GPU中有多个流处理器（Streaming Multiprocesssor，SM），每个SM中有多个 warp，warp是线程簇，每个warp 可以同时并行执行多个线程

GPU 的本质在于并行
CPU 则是尽可能加快指令的运算

## GPU 线程分级

在 AI 计算模式中，不是所有计算都是线程独立的

对一张图片，先用网格 Grip 进行覆盖，切分成多个块 Blocks（相邻 Block 可能会重叠），对每个块独立执行处理。Block 中线程 Threads 通过本地数据共享来计算