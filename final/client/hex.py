import serial

with serial.Serial('/dev/avr-nano') as ser:
    while True:
        data = [ser.read() for x in range(2)]
        print("Y: 0x{:X}".format((data[0] << 8) | data[1]))

