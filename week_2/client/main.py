import serial

def raw_to_volt(raw):
    return raw * (5 / 1024)

with serial.Serial('/dev/ttyACM0') as ser:
    while True:
        # This is due to us only sending 8 bits (lowest 2 bits of adc are not important here)
        raw = (ord(ser.read()) << 2) + 0b11

        print("{0:.2f} volts".format(raw_to_volt(raw)))

