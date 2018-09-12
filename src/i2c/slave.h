// Based on https://github.com/thegouger/avr-i2c-slave

void i2c_slave_init(uint8_t address, void (*new_cb)(), void (*recv_cb)(uint8_t), uint8_t (*send_cb)());
void i2c_slave_stop();
