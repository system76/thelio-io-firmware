#ifndef BATTERY_H
#define BATTERY_H

struct Battery {
    uint8_t address;
};

struct Battery battery_new(uint8_t address);

uint8_t battery_mode(struct Battery * battery, uint16_t * value);
uint8_t battery_temp(struct Battery * battery, uint16_t * value);
uint8_t battery_voltage(struct Battery * battery, uint16_t * value);
uint8_t battery_current(struct Battery * battery, uint16_t * value);
uint8_t battery_avg_current(struct Battery * battery, uint16_t * value);
uint8_t battery_charge(struct Battery * battery, uint16_t * value);
uint8_t battery_abs_charge(struct Battery * battery, uint16_t * value);
uint8_t battery_capacity(struct Battery * battery, uint16_t * value);
uint8_t battery_full_capacity(struct Battery * battery, uint16_t * value);
uint8_t battery_status(struct Battery * battery, uint16_t * value);
uint8_t battery_cycle_count(struct Battery * battery, uint16_t * value);
uint8_t battery_design_capacity(struct Battery * battery, uint16_t * value);
uint8_t battery_design_voltage(struct Battery * battery, uint16_t * value);
uint8_t battery_date(struct Battery * battery, uint16_t * value);
uint8_t battery_serial(struct Battery * battery, uint16_t * value);
uint8_t battery_oem(struct Battery * battery, uint8_t * buf, int len);
uint8_t battery_model(struct Battery * battery, uint8_t * buf, int len);
uint8_t battery_technology(struct Battery * battery, uint8_t * buf, int len);

#endif // BATTERY_H
