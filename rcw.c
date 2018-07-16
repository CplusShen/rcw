/* 
Date: July 13,2018
Author: cplus.shen@advantech.com.tw
Description: RCW bit decode

Reset Configuration Word (RCW):
       00000000: 0c150010 0e000000 00000000 00000000
       00000010: 11335559 40005012 40025000 c1000000
       00000020: 00000000 00000000 00000000 00238800
       00000030: 20124000 00003101 00000096 00000001
*/

#include <stdio.h>
#include <stdint.h>

#define RCW_BIT_MAX 512
#define RCW_BYTE_MAX (512/8)
#define RCW_DW_MAX (512/8/4)

uint32_t rcw[RCW_DW_MAX] = {
0x0c150010,0x0e000000,0x00000000,0x00000000,
0x11335559,0x40005012,0x40025000,0xc1000000,
0x00000000,0x00000000,0x00000000,0x00238800,
0x20124000,0x00003101,0x00000096,0x00000001,
};

uint8_t rcw_byte[RCW_BYTE_MAX];
uint8_t rcw_bit[RCW_BIT_MAX];
uint8_t rcw_bit_swap[RCW_BIT_MAX];

int main(int argc, char* argv[])
{
    int i;
    int j;

    /* dump rcw */
    for(i=0;i<RCW_DW_MAX;i++) {
        printf("%08x\n",rcw[i]);
    }

    /* double word to bit stream */
    for(i=0;i<RCW_DW_MAX;i++) {
        for (j=0; j<32;j++) {
            rcw_bit[i*32+j] = (rcw[i] >> j) & 0x1;
        }
    }

    /* swap bit stream */
    for(i=0;i<RCW_DW_MAX;i++) {
        for (j=0; j<32;j++) {
            rcw_bit_swap[(i*32)+j] = rcw_bit[(i*32)+(31-j)];
        }
    }

    /* dump rcw bit stream */
    for (i=0; i< RCW_BIT_MAX; i++) {
        printf("rcw_bit[%d] = %d\n",i,(int32_t)rcw_bit_swap[i]);
    }

    return 0;
}
