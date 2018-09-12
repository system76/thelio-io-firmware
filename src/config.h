#ifndef CONFIG_H
#define CONFIG_H

#define CFG_16(N, V)
#define CFG_32(N, V)

#define CFGS \
    /* Fan frequency in Hz */ \
    CFG_32(fan_frequency, 25000) \
    /* Fan transition speed in us */ \
    CFG_32(fan_transition, 1000) \
    /* Fan duty default in 0..10000 */ \
    CFG_16(fan_duty, 5000) \
    /* LED frequency in Hz */ \
    CFG_32(led_frequency, 125000) \
    /* LED transition speed in us */ \
    CFG_32(led_transition, 200000) \
    /* LED suspend transition speed in us */ \
    CFG_32(suspend_transition, 6000000) \
    /* Off setting of power LED in 0..10000 */ \
    /* 79, 157, and 235 are valid low settings */ \
    CFG_16(powerbtn_off, 235) \
    /* Max suspend setting of power LED in 0..10000 */ \
    CFG_16(powerbtn_suspend, 2500) \
    /* On setting of power LED in 0..10000 */ \
    CFG_16(powerbtn_on, 3500) \
    /* Pressed setting of power LED in 0..10000 */ \
    CFG_16(powerbtn_pressed, 10000)

#undef CFG_16
#define CFG_16(N, V) uint16_t N;

#undef CFG_32
#define CFG_32(N, V) uint32_t N;

struct Config {
    CFGS
};

struct Config config_new();

void config_load(struct Config * config);
void config_save(struct Config * config);

#endif // CONFIG_H
