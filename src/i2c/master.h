// Based on https://github.com/g4lvanix/I2C-master-lib

uint8_t i2c_recv(uint8_t address, uint8_t* data, uint16_t length);
uint8_t i2c_send(uint8_t address, uint8_t* data, uint16_t length);

uint8_t i2c_get(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);
uint8_t i2c_set(uint8_t devaddr, uint8_t regaddr, uint8_t* data, uint16_t length);