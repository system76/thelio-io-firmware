#define CMD(N) N

#define CMDS \
    CMD(battery) \
    CMD(console) \
    CMD(driver) \
    CMD(echo) \
    CMD(eeprom) \
    CMD(exit) \
    CMD(help) \
    CMD(i2c) \
    CMD(i2c_slave) \
    CMD(keyboard) \
    CMD(pin) \
    CMD(pwm) \
    CMD(sleep) \
    CMD(thelio) \
    CMD(time)

struct command {
    char * name;
    int (*func)(int argc, char ** argv);
};

extern struct command commands[];

void run(char * line);
