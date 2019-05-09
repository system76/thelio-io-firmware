# USB Protocol

The Thelio Io module uses USB CDC ACM in order to communicate with the host.
This is an easy protocol to handle on both the host and device side, and is
used for devices such as GPS and OBDII. Normal AT commands are ignored, ERROR
is returned. Instead, a custom set of commands is used tailored to the
application.

The Thelio Io device can be found with an ID of 7676:7676, to be allocated
later. Opening this device and setting it up with a frequency of 1 MHz will
allow you to start sending commands. Other frequencies may be possible, but
the design should utilize 1 MHz if possible.

Commands are 15 bytes in length, and have the format: `IoCCCCDDDDDDDD\r`. Here,
the `Io` indicates a literal two-byte ASCII `Io` marker, similar to `AT` in AT
commands. `CCCC` indicates a four-byte ASCII command, which may be a hex string,
and `DDDDDDDD` indicates an eight-byte ASCII data value, which may also be a
hex string. The data value is interpreted based on the command, and may contain
subcommands or multiple values. It may also be truncated.

Upon receiving a command, the embedded controller will instantly execute the
command and will print output, followed by either `\r\nOK\r\n` or
`\r\nERROR\r\n`, similar to `AT` command output. The host should wait for one of
these return codes before issuing another command.

Device identifiers must be known by the enumerator, using the USB ID. Attempting
to read the tachometer setting is an easy way to check for a device being
present. In the default device, the following device identifiers are available:

- `CPUF` - CPU fan
- `INTF` - intake fan
- `EXHF` - exhaust fan
- `POWB` - power button

# Examples

## Tachometer

`IoTACHCPUF\r`

Command: `TACH`
Data: `CPUF`
Return: `\r\n07D0\r\n\r\nOK\r\n`

Get the tachometer of device `CPUF`. This will return the tachometer reading
in hex, in this case, it is `2000`, followed by `OK`.

If the device is not found, `ERROR` will be returned.

## Duty cycle (Get)

`IoDUTYCPUF\r`

Command: `DUTY`
Data: `CPUF`
Return: `\r\n1388\r\n\r\nOK\r\n`

Get the duty of device `CPUF`. This will return the current duty cycle, in this
case, `5000`, which is 50%, followed by `OK`. This value may still be
transitioning due to a previous duty cycle set command.

If the device is not found, `ERROR` will be returned.

## Duty cycle (Set)

`IoDUTYCPUF2710\r`

Command: `DUTY`
Data: `CPUF2710`
Return: `\r\nOK\r\n`

Set the duty of device `CPUF` to `10000`, which is 100%. The data must be a hex
encoded value from `0000` to `2710`.

If the device is not found, or the value is above `2710` in hex, `ERROR` will be
returned.


## Suspend State (Get)

`IoSUSP\r`

Command: `SUSP`
Data: ``
Return: `\r\n0001\r\n\r\nOK\r\n`

Get the suspend state of the device. This will return a hex encoded suspend
state. Currently the only values supported are `0000` and `0001`.

Errors should not occur, but must be handled in case of a firmware modification.

## Power State (Set)

`IoSUSP0001\r`

Command: `SUSP`
Data: `0001`
Return: `\r\nOK\r\n`

Set the suspend state of the device. The data must be a hex encoded value.
Currently the only values supported are `0000` and `0001`.

If the value is above `0001` in hex, `ERROR` will be returned.


## Revision (Get)

`IoREVISION\r`

Command: `REVISION`
Data: ``
Return: `\r\n1.0.0\r\n\r\nOK\r\n`

Get the revision of the device. This will return a string, created by the command
`git describe --tags --dirty`. This command is 8 characters long to prevent the
incorrect use of a set command.

Errors should not occur, but must be handled in case of a firmware modification.
