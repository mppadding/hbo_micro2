import serial, time
with serial.Serial('/dev/avr-nano') as ser:
    ser.baudrate = 115200
    while True:
        c = ser.read()
        if ord(c) < 128:
            print(c.decode('ascii'), end="")
