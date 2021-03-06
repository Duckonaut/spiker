#include <common/io.h>
#include <common/rand.h>
#include <common/util.h>
#include <kernel/graphics.h>
#include <kernel/interrupts.h>
#include <kernel/mmio.h>
#include <kernel/timer.h>
#include <stddef.h>
#include <stdint.h>

const uint32_t UART0_BASE = 0x20201000;
const uint32_t UART0_IMSC = (UART0_BASE + 0x38);

uint32_t arm4_cpsrget()
{
    uint32_t r;
    
    asm("mrs %[ps], cpsr" : [ps]"=r" (r));
    return r;
}

void arm4_cpsrset(uint32_t r)
{
    asm("msr cpsr, %[ps]" : : [ps]"r" (r));
}

uint32_t arm_fpscrget() {
	uint32_t r;
    asm("fmrx %[ps], fpscr" : [ps]"=r" (r));
    return r;
}

void arm_fpscrset(uint32_t r) {
    asm("fmxr fpscr, %[ps]" : : [ps]"r" (r));
}

void kernel_main(uint32_t r0, uint32_t r1, uint32_t atags)
{
	(void)r0;
	(void)r1;
	(void)atags;

	while (graphics(320, 240))
		;

	//printf(itoa(arm4_cpsrget(), 2));
	printf("\n");

	printf(INTERRUPTS_ENABLED() ? "YES\n" : "NO\n");	

	interrupts_init();

	printf(btoa(arm4_cpsrget()));
	printf("\n");
	//timer_init();
	//timer_set(3000);
	printf(INTERRUPTS_ENABLED() ? "YES\n" : "NO\n");

	arm4_cpsrset(arm4_cpsrget() | (1 << 9) | (1 << 8) | (1 << 7) | (1 << 6));

	printf(btoa(arm4_cpsrget()));
	printf("\n");

	//do {
	//	uint32_t dummy;
	//	asm volatile("fmrx %[dummy],fpexc\n\t"
    //                 "orr %[dummy],%[dummer],#0x40000000\n\t"
	//				 "fmxr fpexc ,%[dummer]\n\t" : [dummy]"=r" (dummy) : [dummer]"r" (dummy));
	//} while (0);

	//printf(itoa(arm_fpscrget(), 2));
	//printf("\n");

	//arm_fpscrset(arm_fpscrget() & ~(1 << 10));

	//printf(itoa(arm_fpscrget(), 2));
	printf("\n\n");

	pixel_t black = {0, 0, 0};

	uint32_t x = 0;

    printf("Hello, world!\n");

    printf("Hello, %dst world!\n", 1);

    printf("Hello, %dnd world!\n", 2);

    printf("Hello, %xth world!\n", 1436);

    printf("Hello, %s!\n", "world");

    printf("%[_:_]HI\n");
    printf("%[FF000000:_]HI\n");
    printf("%[_:FFFFFF00]HI\n");
    printf("%[00FF0000:0000FF00]HI\n");
    printf("%[_:_]HI\n");
    printf("%[FFFFFF00:00000000]HI\n");
    printf("%[FFFFFF0000000000]HI\n");
    printf("%[]HI\n");
    printf("%[:::]HI\n");
    printf("%[xyz]HI\n");
    printf("%[XXXXXXXX:FFFFFFFF]HI\n");
	
	uint32_t gpio_enable_output = 0x00040000;
	uint32_t gpio_comm_16 = 0x00010000;
	uint32_t delay_num = 0x003F0000;

	mmio_write(GPIO + 4, gpio_enable_output);

	while (1) {
		mmio_write(GPIO + 40, gpio_comm_16);

		delay(100000);

		mmio_write(GPIO + 28, gpio_comm_16);

		delay(100000);
	}
}
