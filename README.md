# A Scalable Multi-Path Microarchitecture for Efficient GPU Control Flow

GPUs use **SIMT** (single-instruction, multiple-thread) to execute the same instructions in several threads. GPGPU-Sim uses **SIMT stack** to simulate SIMT. SIMT stack is a single-path stack execution model. Its serialization of divergent control flow paths reduces **thread-level parallelism**. **MP IPDOM** enables **multi-path execution** with support for an arbitrary number of divergence splits while maintaining reconvergence at the IPDOM. 

We implemented the MP IPDOM in this project based on the [original paper](https://people.ece.ubc.ca/~aamodt/publications/papers/eltantawy.hpca2014.pdf) and [this post](https://www.zhihu.com/question/612490213) using [GPGPU-SIM](https://github.com/gpgpu-sim/gpgpu-sim_distribution). We added an additional structure, **simt_reconvergence_table**, to record the reconvergence items and modified the code to support **parallel warp execution**. The split warp in MP IPDOM could run parallel. Since the original scoreboard only recorded the register usage per-warp instead of per-split warp, we modified the **scoreboard** to track register usage in each split warp.

# Building

Following the official [GPGPU-SIM document](https://github.com/gpgpu-sim/gpgpu-sim_distribution).

