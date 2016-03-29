# fyp-fpga-random-number
The aim of this project is to develop an FPGA accelerated system for
testing random number generators, which is able to test for statistical
defects over trillions of random samples. It will require some understanding
of basic stats, but is mainly about building the hardware and software
to actually do the job.

Random numbers are at the heart of many types of Monte-Carlo simulations,
such as financial modelling and physics simulations. In practise we
use deterministic random number generators which algorithmically
emulate randomness using software or digital logic, and we care about two
main quality metrics:
- distribution: does the random number generator follow the
  distribution (uniform, Gaussian, exponential, ...) it is supposed to?
- independence: is each sample statistically independent of all previous samples?
These questions become particularly important when using clusters
containing modern hardware such as GPUs or FPGAs, as we need to
ensure the distrubution and independence hold over quadrillions of samples.

There are a number of software tools for testing distribution and independence,
but these are too slow, so the aim of this project is to move much of the
calculation into an FPGA. The types of statistical tests used are comparatively
simple (e.g. histograms and auto-correlation), but the difficult part is processing
one random sample per cycle at a high clock rate. Expected outcomes are:

- A system (both software and hardware) for performing basic statistical tests at very high speeds.
- The ability to configure the random number generator and distribution being tested.
- Demonstration of useful tests performed on 10^12 or more samples.

More advanced students will be expect to increase parallelism and performance, and
to add more sophisticated tests. RNG quality for massively parallel
systems is of research importance, so a good project could result
in a research paper.

Skills needed are a good understanding of digital logic, some knowledge of
Verilog/VHDL is useful, though it can also be performance in HLS (C-like
code). No particular mathematical knowledge is needed beyond basic stats.
