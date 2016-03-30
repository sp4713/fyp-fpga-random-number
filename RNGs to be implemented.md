- return 4
- RANDU https://en.wikipedia.org/wiki/RANDU
    V_{j+1} = 65539*V_jmod2^31
http://crypto.stackexchange.com/questions/32620/how-to-design-a-deliberately-weak-prng-for-experimentation
https://www.phy.duke.edu/~rgb/General/dieharder/dieharder.html#list
https://en.m.wikipedia.org/wiki/Mersenne_Twister
https://en.wikipedia.org/wiki/Diehard_tests

#Statistical Tests
    1. General Test Procedures for Studying Random Data
        A. Chi-Square test
        B. K-S tests
            - If the K-S test usually passes, there is strong evidence that the transformation from uniform to nonuniform random values was implemented correctly.
            - If the K-S test fails, examining the values of x that determines K+ and K- can help developers locate the bug in the RNG
            
    2. Empirical Tests
    3. Theoretical Tests
    4. Spectral Test
