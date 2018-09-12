#include <stdio.h>
#include <string.h>
#include "../cpu.h"
#include <util/delay.h>
#include "mod.h"
#include "../battery.h"
#include "../i2c/master.h"
#include "../i2c/slave.h"

void cmd_battery_help_inner();

int cmd_battery_help(struct Battery * battery, int argc, char ** argv) {
    cmd_battery_help_inner();
    return 0;
}

int cmd_battery_mode(struct Battery * battery, int argc, char ** argv) {
    uint16_t value;
    uint8_t status = battery_mode(battery, &value);
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    printf("%X", value);
    if (value & (1 << 0)) {
        printf(" INTERNAL_CHARGE_CONTROLLER");
    }
    if (value & (1 << 1)) {
        printf(" PRIMARY_BATTERY_SUPPORT");
    }
    if (value & (1 << 7)) {
        printf(" CONDITION_FLAG");
    }
    if (value & (1 << 8)) {
        printf(" CHARGE_CONTROLLER_ENABLED");
    }
    if (value & (1 << 9)) {
        printf(" PRIMARY_BATTERY");
    }
    if (value & (1 << 13)) {
        printf(" ALARM_MODE");
    }
    if (value & (1 << 14)) {
        printf(" CHARGER_MODE");
    }
    if (value & (1 << 15)) {
        printf(" CAPACITY_MODE");
    }
    printf("\n");

    return 0;
}

int cmd_battery_temp(struct Battery * battery, int argc, char ** argv) {
    uint16_t value;
    uint8_t status = battery_temp(battery, &value);
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    printf("%f C\n", ((double)value)/10.0 - 273.15);

    return 0;
}

int cmd_battery_voltage(struct Battery * battery, int argc, char ** argv) {
    uint16_t value;
    uint8_t status = battery_voltage(battery, &value);
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    printf("%f V\n", ((double)value)/1000.0);

    return 0;
}

int cmd_battery_current(struct Battery * battery, int argc, char ** argv) {
    uint16_t value;
    uint8_t status = battery_current(battery, &value);
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    printf("%f A\n", ((double)((int16_t)value))/1000.0);

    return 0;
}

int cmd_battery_avg_current(struct Battery * battery, int argc, char ** argv) {
    uint16_t value;
    uint8_t status = battery_avg_current(battery, &value);
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    printf("%f A\n", ((double)((int16_t)value))/1000.0);

    return 0;
}

int cmd_battery_charge(struct Battery * battery, int argc, char ** argv) {
    uint16_t value;
    uint8_t status = battery_charge(battery, &value);
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    printf("%u %%\n", value);

    return 0;
}

int cmd_battery_abs_charge(struct Battery * battery, int argc, char ** argv) {
    uint16_t value;
    uint8_t status = battery_abs_charge(battery, &value);
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    printf("%u %%\n", value);

    return 0;
}

int cmd_battery_capacity(struct Battery * battery, int argc, char ** argv) {
    uint16_t mode;
    uint8_t status = battery_mode(battery, &mode);
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    _delay_ms(1);

    uint16_t value;
    status = battery_capacity(battery, &value);
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    if (mode & (1 << 15)) {
        printf("%f WH\n", ((double)((int16_t)value))/10000.0);
    } else {
        printf("%f AH\n", ((double)((int16_t)value))/1000.0);
    }

    return 0;
}

int cmd_battery_full_capacity(struct Battery * battery, int argc, char ** argv) {
    uint16_t mode;
    uint8_t status = battery_mode(battery, &mode);
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    _delay_ms(1);

    uint16_t value;
    status = battery_full_capacity(battery, &value);
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    if (mode & (1 << 15)) {
        printf("%f WH\n", ((double)((int16_t)value))/10000.0);
    } else {
        printf("%f AH\n", ((double)((int16_t)value))/1000.0);
    }

    return 0;
}

int cmd_battery_status(struct Battery * battery, int argc, char ** argv) {
    uint16_t value;
    uint8_t status = battery_status(battery, &value);
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    printf("%X", value);
    if (value & 0xf) {
        printf(" ERROR:0x%X", value & 0xf);
    }
    if (value & (1 << 4)) {
        printf(" FULLY_DISCHARGED");
    }
    if (value & (1 << 5)) {
        printf(" FULLY_CHARGED");
    }
    if (value & (1 << 6)) {
        printf(" DISCHARGING");
    }
    if (value & (1 << 7)) {
        printf(" INITIALIZED");
    }
    if (value & (1 << 8)) {
        printf(" REMAINING_TIME_ALARM");
    }
    if (value & (1 << 9)) {
        printf(" REMAINING_CAPACITY_ALARM");
    }
    if (value & (1 << 11)) {
        printf(" TERMINATE_DISCHARGE_ALARM");
    }
    if (value & (1 << 12)) {
        printf(" OVER_TEMP_ALARM");
    }
    if (value & (1 << 14)) {
        printf(" TERMINATE_CHARGE_ALARM");
    }
    if (value & (1 << 15)) {
        printf(" OVER_CHARGED_ALARM");
    }
    printf("\n");

    return 0;
}

int cmd_battery_cycle_count(struct Battery * battery, int argc, char ** argv) {
    uint16_t value;
    uint8_t status = battery_cycle_count(battery, &value);
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    printf("%u\n", value);

    return 0;
}

int cmd_battery_design_capacity(struct Battery * battery, int argc, char ** argv) {
    uint16_t mode;
    uint8_t status = battery_mode(battery, &mode);
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    _delay_ms(1);

    uint16_t value;
    status = battery_design_capacity(battery, &value);
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    if (mode & (1 << 15)) {
        printf("%f WH\n", ((double)((int16_t)value))/10000.0);
    } else {
        printf("%f AH\n", ((double)((int16_t)value))/1000.0);
    }

    return 0;
}

int cmd_battery_design_voltage(struct Battery * battery, int argc, char ** argv) {
    uint16_t value;
    uint8_t status = battery_design_voltage(battery, &value);
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    printf("%f V\n", ((double)value)/1000.0);

    return 0;
}

int cmd_battery_date(struct Battery * battery, int argc, char ** argv) {
    uint16_t value;
    uint8_t status = battery_date(battery, &value);
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    unsigned int year = value/512 + 1980;
    unsigned int month = (value % 512)/32;
    unsigned int day = (value % 32);
    printf("%u-%u-%u\n", year, month, day);

    return 0;
}

int cmd_battery_serial(struct Battery * battery, int argc, char ** argv) {
    uint16_t value;
    uint8_t status = battery_serial(battery, &value);
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    printf("%u\n", value);

    return 0;
}

int cmd_battery_oem(struct Battery * battery, int argc, char ** argv) {
    uint8_t buf[33] = { 0 };
    uint8_t status = battery_oem(battery, buf, sizeof(buf));
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    int i;
    for(i = 1; i <= buf[0] && i < sizeof(buf); i++) {
        printf("%c", buf[i]);
    }
    printf("\n");

    return 0;
}

int cmd_battery_model(struct Battery * battery, int argc, char ** argv) {
    uint8_t buf[33] = { 0 };
    uint8_t status = battery_model(battery, buf, sizeof(buf));
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    int i;
    for(i = 1; i <= buf[0] && i < sizeof(buf); i++) {
        printf("%c", buf[i]);
    }
    printf("\n");

    return 0;
}

int cmd_battery_technology(struct Battery * battery, int argc, char ** argv) {
    uint8_t buf[33] = { 0 };
    uint8_t status = battery_technology(battery, buf, sizeof(buf));
    if(status != 0) {
        printf("error %d\n", status);
        return 1;
    }

    int i;
    for(i = 1; i <= buf[0] && i < sizeof(buf); i++) {
        printf("%c", buf[i]);
    }
    printf("\n");

    return 0;
}

int cmd_battery_dump(struct Battery * battery, int argc, char ** argv);

#undef BATTERY_CMD
#define BATTERY_CMD(N) { #N, cmd_battery_ ## N },

struct battery_command {
    char * name;
    int (*func)(struct Battery * battery, int argc, char ** argv);
};

struct battery_command battery_commands[] = {
    BATTERY_CMD(help)
    BATTERY_CMD(dump)
    BATTERY_CMD(mode)
    BATTERY_CMD(temp)
    BATTERY_CMD(voltage)
    BATTERY_CMD(current)
    BATTERY_CMD(avg_current)
    BATTERY_CMD(charge)
    BATTERY_CMD(abs_charge)
    BATTERY_CMD(capacity)
    BATTERY_CMD(full_capacity)
    BATTERY_CMD(status)
    BATTERY_CMD(cycle_count)
    BATTERY_CMD(design_capacity)
    BATTERY_CMD(design_voltage)
    BATTERY_CMD(date)
    BATTERY_CMD(serial)
    BATTERY_CMD(oem)
    BATTERY_CMD(model)
    BATTERY_CMD(technology)
    { NULL, NULL }
};

int cmd_battery_dump(struct Battery * battery, int argc, char ** argv) {
    int i;
    int dump = 0;
    for (i = 0; ; i++) {
        char * name = battery_commands[i].name;
        if (name == NULL) {
            break;
        }
        if (dump) {
            printf("%s: ", battery_commands[i].name);
            int status = battery_commands[i].func(battery, argc, argv);
            if(status != 0) {
                return status;
            }
        }
        if (strcmp(name, "dump") == 0) {
            dump = 1;
        }
    }
    return 0;
}

void cmd_battery_help_inner() {
    printf("battery\n");
    int i;
    for (i = 0; ; i++) {
        char * name = battery_commands[i].name;
        if(name == NULL) {
            break;
        }
        printf("    %s\n", battery_commands[i].name);
    }
}

int cmd_battery(int argc, char ** argv) {
    if (argc > 1) {
        //TODO: Pass battery as argument
        struct Battery battery = battery_new(0x0B);

        int i;
        for (i = 0; ; i++) {
            char * name = battery_commands[i].name;
            if(name == NULL) {
                printf("unknown battery command: '%s'\n", argv[1]);
                cmd_battery_help_inner();
                return 1;
            }
            if (strcmp(argv[1], name) == 0) {
                return battery_commands[i].func(&battery, argc - 1, &argv[1]);
            }
        }
    } else {
        printf("no argument provided\n");
        cmd_battery_help_inner();
        return 1;
    }

    return 0;
}
