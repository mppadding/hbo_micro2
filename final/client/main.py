import serial

def raw_to_volt(raw):
    return raw * (5 / 4096)

with serial.Serial('/dev/ttyACM0') as ser:
    while True:
        upper = ord(ser.read())

        # Make sure we start with upper and not lower.
        if upper & (1 << 7):
            # Remove the start indicator
            upper &= 0x7F;
            lower = ord(ser.read())

            print("upper:     {:08b}".format(upper))
            print("lower:     {:08b}".format(lower))

            # We send 2 bytes per measurement
            raw = (upper << 8) | lower
            print("total: {:012b}\n".format(raw))
            print("{0:.2f} volts".format(raw_to_volt(raw)))

