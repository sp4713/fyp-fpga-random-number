##Introduction
  - What are RNGs, state that they're tested in batteries of tests
  - Currently, test suites are software, problems with hardware RNG testing
  - State problem: Analysis of FPGA-accelerated custom RNGs for use in computer simulations
- Project Scope
  - Goal: User-specified RNGs tested up to 2^44 samples at one sample/clock cycle
  - Easy to set up, thought-out hw/sw split, 

##Background


##Design Specification (aka Requirements Capture)
- investigation of expected use and a brief more detailed than the specification is constructed
- outlining project objectives
- Produce set of strict technical specifications that the final product must follow

- Top Level Specifcations
  - Types of RNGs under consideration
  - Input parameters user should supply
  - Output information system should supply
- Low Level Specification - Describe Work Flow Diagram
  - How user provides custom RNG (mention how RNG needs to be fast too)
  - How to compile the design from user perspective (how it was designed to keep laborious tasks at minimum)
  - How to start/stop simulation

##Top Level Specification
- Synthesisable
- Implementable
- HW/SW Interfaceable

##Low Level Specification
- codes should be correct and reasonable
- outline of expected use and a brief more detailed than the specification is constructed

##Top Level Abstract Design
###Vivado HLS
###Vivado IP Integrator
###Xilinx SDK

##Top Level Abstract Design
- Outline Design Flow Diagram
- The different stages of compilation required by the user (and 
- Keep section a lot more brief than low level abstract design

##Low Level Abstract Design
- Vivado HLS
- Vivado IP Integrator
- Xilinx SDK
- 
##Simulation and Testing

##Implementation

##Evaluation

##Conclusion
