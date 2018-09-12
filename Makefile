DEVICE?=atmega32u4
#DEVICE?=atmega2560
#DEVICE?=atmega1280

include mk/$(DEVICE).mk

BUILD=build/$(DEVICE)
CFLAGS=-Os -fstack-usage -Wall -Wl,--gc-sections -Wl,-u,vfprintf -lprintf_flt -D __DEVICE__=$(DEVICE) -mmcu=$(DEVICE)

.PHONY: all clean console icsp stack upload

all: $(BUILD)/main.hex

clean:
	rm -rf $(BUILD)

console:
	sudo tio $(PORT) -b $(CONSOLE_BAUD)

icsp: $(BUILD)/main.hex
	sudo avrdude -v -v -p $(DEVICE) -c usbasp -U flash:w:$<:i

icsp_fuse:
	sudo avrdude -v -v -p $(DEVICE) -c usbasp -U efuse:w:0xCB:m -U hfuse:w:0xD8:m -U lfuse:w:0xFF:m

stack: $(BUILD)/main.elf
	sort -k2 -n $$(find $(BUILD) -name *.su)

upload: $(BUILD)/main.hex
	sudo avrdude -v -v -p $(DEVICE) -c $(PROGRAMMER) -P $(PORT) -b $(PROGRAMMER_BAUD) -D -U flash:w:$<:i

$(BUILD)/%.o: src/%.c src/*.h src/*/*.h
	mkdir -p $(@D)
	avr-gcc $(CFLAGS) $< -c -o $@

$(BUILD)/libUSBtoSerial.a: usb/*.c usb/*.h usb/Config/*.h
	mkdir -p $(@D)
	make -C usb lib
	cp usb/libUSBtoSerial.a $@

OBJS=\
	$(BUILD)/cmd/thelio.o \
	$(BUILD)/config.o \
	$(BUILD)/debounce.o \
	$(BUILD)/device.o \
	$(BUILD)/pin.o \
	$(BUILD)/stdio.o \
	$(BUILD)/tach.o \
	$(BUILD)/time.o \
	$(BUILD)/timer.o \
	$(BUILD)/transition.o \
	$(BUILD)/uart.o \
	$(BUILD)/main.o \
	$(BUILD)/libUSBtoSerial.a

#\
	$(BUILD)/cmd/mod.o \
	$(BUILD)/cmd/console.o \
	$(BUILD)/cmd/battery.o \
	$(BUILD)/cmd/driver.o \
	$(BUILD)/cmd/echo.o \
	$(BUILD)/cmd/eeprom.o \
	$(BUILD)/cmd/exit.o \
	$(BUILD)/cmd/help.o \
	$(BUILD)/cmd/i2c.o \
	$(BUILD)/cmd/i2c_slave.o \
	$(BUILD)/cmd/keyboard.o \
	$(BUILD)/cmd/pin.o \
	$(BUILD)/cmd/pwm.o \
	$(BUILD)/cmd/sleep.o \
	$(BUILD)/cmd/time.o \
	$(BUILD)/i2c/mod.o \
	$(BUILD)/i2c/master.o \
	$(BUILD)/i2c/slave.o \
	$(BUILD)/keyboard/mod.o \
	$(BUILD)/keyboard/map.o \
	$(BUILD)/keyboard/pins.o \
	$(BUILD)/battery.o \
	$(BUILD)/readline.o \
	$(BUILD)/tokenize.o \

$(BUILD)/main.elf: $(OBJS)
	mkdir -p $(@D)
	avr-gcc $(CFLAGS) $^ -o $@


$(BUILD)/main.hex: $(BUILD)/main.elf
	mkdir -p $(@D)
	avr-objcopy -j .text -j .data -O ihex $< $@
