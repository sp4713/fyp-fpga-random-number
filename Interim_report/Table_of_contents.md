##Introduction
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

##Project Specification
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
- Explain bottleneck issue, slowest test will slow down entire design

####Methodology used - Statistical Hypothesis Testing
- Chi-Squared Test
  - Explanation of how it works, mathematical background (state equation and derivation in appendix?)
- Frequency Test (Basic)
  - Create 32 bit-buckets and check whether each is equiprobably 1 or 0 (i.e. 32 buckets counting occurrences of 1)
- Count the 1s (Intermediate)
  - Count the 1 bits in each of either successive bytes. Convert the counts to "letters", and count the occurrences of five-letter "words"
- Serial Test (Advanced)
  - Each bucket is 00, 01, 10, or 11 - Check equiprobability for each of the 4x32=128 cases (i.e. 4x32=128 buckets counting occurrences of 1 or devise some smarter way)
  - Note that needs to be non-overlapping, otherwise number of points in the cells are not independent, chi-square can't be used
  - Discuss possibility to expand to triple, quadruples, in some efficient way
- Gap Test (Advanced)
  - Count range between two consecutive 1s or 0s in all 32 bits
- Poker Test (Advanced)
  - All different: abcde
  - One pair: aabcd
  - Two pairs: aabbc
  - Three of a kind: aaabc
  - Full house: aaabb
  - Four of a kind: aaaab
  - Poker: aaaaa

####Minimum RNGs under consideration
- Explain why existing RNG algorithms will be borrowed
Description of basic counters and what features will make them fail certain anticipated tests
- Simple Counter
- RANDU
- Linear Feedback Shift Register

####Advanced RNGs under consideration
- to be revisited

##Implementation plan
- Discussion of progress so far, uncertainties at this point in project
- Discussion on antipicated risks (running out of FPGA resources, time, etc.)

##Planning and Evaluation
- State existence of Gantt chart in appendix
- Discussion that RNGs will fall in either almost all pass, almost all fail, or greyzone
- Aim for minimum throughput 2^38 just as TestU01 throughput
  - Then aim higher for 2^44 or 2^48 depending on how much progress has been made at this point (ideally one sample per clock cycle)
  - 10 million samples, 100 million samples/second
- minimum design: frequency test
- advanced design: all 4 mentioned tests in parallel
- describe how evaluation is done through running chunks of data over hours and hours of simulation on FPGA
##Appendix
- Derivation of maths (of RNG? of methodology?)
- Gantt Chart (?)
