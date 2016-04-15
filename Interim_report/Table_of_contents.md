###Introduction
- Explain what RNG is, application areas, statistical quality criteria

####Analysing Random Number Generators (Background)
- Explain empirical methodology
  - More tests passed indicates higher confidence in randomness

####Why test Random Number Sequences? (Background)
- State application areas and theoretical risks posed by bad RNGs
- Case study: Microsoft Excel 2007-2010 RNG update in response to bad publicity

####How analyse Random Number Sequences? (Background)
  - Good RNGs pass Hard tests, Bad RNGs fail Simple tests
    - judging whether RNG passed based on pass/fail results requires human judgment
- Explain meaning of p-value (in chi-squared test?)
- Statistical quality criteria, name TestU01/Diehard

####Why design and analyse RNGs in FPGAs? (Project Motivation)
- High performance computing requires parallel formulation of problems (embarrassingly parallel MC)
- FPGA can be resource-efficient, high-speed generator of RNGs
- Explain that software RNG test throughput limitations motivate FPGA implementation
  - RNG output fed into FPGA MC simulations

###Project Specification
- State that in simulations, fast, resource-efficient generation is desired
- State the client's need for RNGs' output fed into MC simulation

####Simulation Repeatability and Reproducibility
- Explain need for pseudo-random and deterministic RNG
  - Implementation through user-specific seed value / amount of output generated (acknowledged by test bench)

####Target Platform
- Introduce Vivado and Zedboard
  - Motivation: Peripherals, availability to department
  - Dual core ARM Cortex A9MP processor and Programmable Logic
    - Makes prototyping and implementing embedded designs with hardware acceleration easier than FPGA only device
      - Processing system can be used to implement parts of the algorithm which are less suitable or not necessary for hardware acceleration

###Empirical Tests under consideration
####Methodology used - Statistical Hypothesis Testing
####Frequency Test
- Chi-Squared Test
  - Explanation of how it works, mathematical background, (state equation and derive in appendix?)
###

####Minimum RNGs under consideration
- Explain why existing RNG algorithms will be borrowed
Description of basic counters and what features will make them fail certain anticipated tests
- Simple Counter
- RANDU
- Linear Feedback Shift Register

####Advanced RNGs under consideration
- to be revisited

###Appendix
- Derivation of maths (of RNG? of methodology?)
- Gantt Chart
