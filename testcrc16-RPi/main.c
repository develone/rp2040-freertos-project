#include <stdio.h>
int main() {
unsigned char message[9] = {0xd3, 0x01, 0x00,0xd3, 0x01, 0x00,0xd3, 0x01, 0x10};
short unsigned int crc;
printf("Hello, world!\n");
crc = crc16_ccitt(message, 9);
printf("0x%x\n",crc);
}


