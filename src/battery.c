#include <stdio.h>
#include <string.h>
#include "cpu.h"
#include <util/delay.h>
#include "battery.h"
#include "i2c/master.h"
#include "i2c/slave.h"

uint8_t i2c_get_16(uint8_t chip, uint8_t command, uint16_t * value) {
    uint8_t status = i2c_get(chip, command, (uint8_t *)value, 2);
    if (status != 0) {
        return status;
    }

    return 0;
}

struct Battery battery_new(uint8_t address) {
    struct Battery battery = {
        .address = address
    };

    return battery;
}

uint8_t battery_mode(struct Battery * battery, uint16_t * value) {
    return i2c_get_16(battery->address, 0x03, value);
}

uint8_t battery_temp(struct Battery * battery, uint16_t * value) {
    return i2c_get_16(battery->address, 0x08, value);
}

uint8_t battery_voltage(struct Battery * battery, uint16_t * value) {
    return i2c_get_16(battery->address, 0x09, value);
}

uint8_t battery_current(struct Battery * battery, uint16_t * value) {
    return i2c_get_16(battery->address, 0x0A, value);
}

uint8_t battery_avg_current(struct Battery * battery, uint16_t * value) {
    return i2c_get_16(battery->address, 0x0B, value);
}

uint8_t battery_charge(struct Battery * battery, uint16_t * value) {
    return i2c_get_16(battery->address, 0x0D, value);
}

uint8_t battery_abs_charge(struct Battery * battery, uint16_t * value) {
    return i2c_get_16(battery->address, 0x0E, value);
}

uint8_t battery_capacity(struct Battery * battery, uint16_t * value) {
    return i2c_get_16(battery->address, 0x0F, value);
}

uint8_t battery_full_capacity(struct Battery * battery, uint16_t * value) {
    return i2c_get_16(battery->address, 0x10, value);
}

uint8_t battery_status(struct Battery * battery, uint16_t * value) {
    return i2c_get_16(battery->address, 0x16, value);
}

uint8_t battery_cycle_count(struct Battery * battery, uint16_t * value) {
    return i2c_get_16(battery->address, 0x17, value);
}

uint8_t battery_design_capacity(struct Battery * battery, uint16_t * value) {
    return i2c_get_16(battery->address, 0x18, value);
}

uint8_t battery_design_voltage(struct Battery * battery, uint16_t * value) {
    return i2c_get_16(battery->address, 0x19, value);
}

uint8_t battery_date(struct Battery * battery, uint16_t * value) {
    return i2c_get_16(battery->address, 0x1B, value);
}

uint8_t battery_serial(struct Battery * battery, uint16_t * value) {
    return i2c_get_16(battery->address, 0x1C, value);
}

uint8_t battery_oem(struct Battery * battery, uint8_t * buf, int len) {
    if (len < 1) {
        printf("%d < 1\n", len);
        return 1;
    }

    uint8_t status = i2c_get(battery->address, 0x20, buf, 1);
    if (status != 0) {
        return status;
    }

    if (buf[0] >= len) {
        printf("%u >= %d\n", buf[0], len);
        return 2;
    }

    _delay_ms(1);

    return i2c_get(battery->address, 0x20, buf, buf[0] + 1);
}

uint8_t battery_model(struct Battery * battery, uint8_t * buf, int len) {
    if (len < 1) {
        printf("%d < 1\n", len);
        return 1;
    }

    uint8_t status = i2c_get(battery->address, 0x21, buf, 1);
    if (status != 0) {
        return status;
    }

    if (buf[0] >= len) {
        printf("%u >= %d\n", buf[0], len);
        return 2;
    }

    _delay_ms(1);

    return i2c_get(battery->address, 0x21, buf, buf[0] + 1);
}

uint8_t battery_technology(struct Battery * battery, uint8_t * buf, int len) {
    if (len < 1) {
        printf("%d < 1\n", len);
        return 1;
    }

    uint8_t status = i2c_get(battery->address, 0x22, buf, 1);
    if (status != 0) {
        return status;
    }

    if (buf[0] >= len) {
        printf("%u >= %d\n", buf[0], len);
        return 2;
    }

    _delay_ms(1);

    return i2c_get(battery->address, 0x22, buf, buf[0] + 1);
}
