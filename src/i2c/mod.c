#include <avr/io.h>
#include "../cpu.h"
#include "mod.h"

void i2c_init() {
	TWAR = 0;
	TWBR = (uint8_t)(((F_CPU / F_SCL) - 16 ) / 2);
	TWCR = 0;
}
