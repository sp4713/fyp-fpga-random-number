# fyp-fpga-random-number
Motivation
==========
- make use of fast generation of numbers on FPGA
- no way of testing these fast streams in software
    -  testing RNGs designed for hardware

Milestones
- Skills/knowledge                 (3 weeks)
    - what is meant by RNG
        - have there been any crises because of bad RNG? why do we care?
        - explain non-trivial problems, why was it hard?
    - What can Vivado HLS do? (c)
        - Main idea of Vivado HLS is to accelerate the process of transforming algorithm in C or C++ to Xilinx FPGAs
        - Code written in C/C++ or SystemC -> Vivado HLS -> VHDL/Verilog IP + Testbenches
        - Extract data path and control unit based on the code
    - What can Vivado HLS not do? (✓)
            - C/C++ LIMITATIONS
                - no dynamic memory allocation
                - no STD; FILE-I/O, not system calls
                - no recursive functions
                - Generated code is not the most readable
                - Sometimes you want something smaller than CTRL_UNIT + DATAPATH
                - Sometimes you want more control on the generated code
    - How to run Vivado HLS programs on FPGA? (how does interfacing work)
    - some top-level design (block design, how connect with each other, interface with outside world) -> to be included in interim report

- Planning                (X weeks)
    - which statistical tests to implement
    - performance metrics to be hit
    - evaluating criteria to be met
    - some top-level design (block design, how connect with each other, interface with outside world) -> to be included in interim report
    
- Implementation minimum                (X weeks)
    - Low risk, critical (minimum) parts first
      - Evaluate minimum parts against above metrics

- Implementation advanced                (2 weeks)
    - To be determined/revisted
      - Evaluate minimum parts against above metrics
    
- Full evaluation                (2 weeks)

- Report writing                (2 weeks)
