#include <stdint.h>

inline uint32_t div(uint32_t dividend, uint32_t divisor);

inline uint32_t mod(uint32_t dividend, uint32_t divisor);

char* itoa(int num, int base);

int atoi(char* num);

void memcpy(void* dest, const void* src, int bytes);

void memset(void* dest, uint8_t c, int bytes);

void bzero(void* dest, int bytes);
// Loop <delay> picoseconds
void delay(int32_t count);