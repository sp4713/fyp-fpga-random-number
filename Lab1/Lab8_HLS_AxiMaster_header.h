// Size limit
// Maximum AXI4 full burst length is 256 bytes

//#define MAX_TRANSFER_SIZE = 268435456
#define MAX_TRANSFER_SIZE = 200000 //200kb
const int max_depth = MAX_TRANSFER_SIZE;

int setMem(unsigned char value, volatile unsigned char *addr, int size);