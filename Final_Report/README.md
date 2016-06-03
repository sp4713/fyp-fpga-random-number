##Introduction
  - What are RNGs, state that they're empirically tested using batteries of tests
  - Brief overview of why there are currently problems for hardware RNG testing
- Project Scope
  - State context: RNGs for MC simulations
  - Goal 1: User-specified RNGs tested up to 2^44 samples at one sample/clock cycle
    - Most importantly, system should be useful (tests should be parameterisable, 
  - Goal 2: outperform software test suites in terms of throughput / max sample size
    - For maximum efficiency, HW/SW split should be well-reasoned
  - Questions addressed in project:
    - How to communicate test success/failure to the user?
    - What types of RNGs to facilitate in test suite?
    - How to optimise system throughput to one sample per clock cycle?
    - How to parallelise multiple RNG tests under consideration?
    - How to facilitate the processing of trillions of samples?
    - How to design the system's split into hardware and software portions?
    - How to interact with the test suite?
- Target Platform
  - Overview of PS/PL split of board, software suite, why not Verilog/VHDL
- Report Structure
##Background
- Related Work (restate existence of current test suites and theory books)
- Project Motivation
  - MC simulations & RNGs in FPGAs
  - Need or higher throughput RNGs
  - Need or higher throughput test suites
- RNG types under consideration
  - State different RNGs exist for different application areas
  - Pseudo & Deterministic, Uniform, 32-bit Unsigned Integer
- Statistical Testing of RNGs
  - How to assess statistical properties? (split into theoretical and empirical, explain empirical)
  - Interpreting Empirical Test Results
    - brief overview of test statistic conversion to a p-value
    - explain what is p-value
- Empirical Statistical Test Algorithm
  - Explain that 32 bits are analysed for every sample and each test compares theoretical vs observed distributions
  - Chi-Squared Test (formula, required parameters)
  - Computing p-values from this test (formulae)
- Empirical Tests under Consideration (put this section in design specifications? put disregarded tests in appendix?)
  - Selection Criteria (light resource footprint such that it's parallelisable, one sample/cycle, meets timing constraints)
  - Frequency Test (explain underlying algorithm, then how to get p-value parameters)
  - Serial 2-tuple Test (same)
  - Serial 3-tuple Test (same, and state how this only works for 2^38 samples)
- RNGs under consideration
  - Explain how different (quality) RNGs required to show different permutations of tests failing
  - Simple Counter (fastest and lightest footprint)
  - RANDU (too slow but for demonstration purposes)
- PS/PL interconnect
  - Explanation of AXI4 and 32-bit truncation
- Section for workflow diagram?

##(TBD) Design Specification (aka Requirements Capture) TBD
- investigation of expected use and a brief more detailed than the specification is constructed
- outlining project objectives
- Produce set of strict technical specifications that the final product must follow

- (TBD) Top Level Specifications
  - Types of RNGs under consideration
  - Input parameters user should supply
  - Output information system should supply

- Low Level Specification - Describe Work Flow Diagram
  - How user provides custom RNG (mention how RNG needs to be fast too)
  - How to compile the design from user perspective (how it was designed to keep laborious tasks at minimum)
  - How to start/stop simulation
  - codes should be correct and reasonable
  - outline of expected use and a brief more detailed than the specification is constructed

##Top Level Abstract Design
- To be designed, system needs to be: Synthesisable, implementable, HW/SW Interfaceable
- Outline Design Flow Diagram (in this section?)
- The different stages of compilation required by the user (and which help files are provided)
- Keep section a lot more brief than low level abstract design

##Low Level Abstract Design (longest section?)
- Step-by-step bottom-up description of implementation in Vivado HLS, then Vivado IP Integrator, then Xilinx SDK

##Simulation and Testing (TBD)
- Describe toolchain used (mainly Vivado HLS custom testbenches and testbenches in Xilinx SDK)
- Describe test flow (with nice diagram)

##Implementation (put it here?)
- Discuss problems faced and their overcomings here or somewhere else?
- Describe block design of Zynq processor with HLS components (and interconnects)
- Describe how almost exclusively LUTs are used instead of slower memory

##Evaluation (which areas to examine?)
- Hardware Resources used
- Performance (just simply state that all works fast and well?)

##Future Work and Conclusion

##Appendix
- Put disregarded tests here?
- Which codes to put here?
- 
