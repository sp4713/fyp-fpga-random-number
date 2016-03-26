Main idea of Vivado HLS is to accelerate the process of transforming algorithm in C or C++ to Xilinx FPGAs

Code written in C/C++ or SystemC -> Vivado HLS -> VHDL/Verilog IP + Testbenches
- Extract data path and control unit based on the code

C/C++ LIMITATIONS
- no dynamic memory allocation
- no STD; FILE-I/O, not system calls
- no recursive functions

Generated code is not the most readable
Sometimes you want something smaller than CTRL_UNIT + DATAPATH
Sometimes you want more control on the generated code
