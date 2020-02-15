import serial

resolution = 0.0625
checksum_factor = 140

def raw_to_celsius(raw):
    return raw * resolution

def checksum(byte, checksum):
    return checksum == byte ^ checksum_factor

with serial.Serial('/dev/ttyACM0') as ser:
    while True:
        upper = ord(ser.read())
        lower = ord(ser.read())
        check = ord(ser.read())

        if checksum(lower, check):
            print("upper:     {:08b}".format(upper))
            print("lower:     {:08b}".format(lower))

            # We send 2 bytes per measurement
            raw = (upper << 8) | lower
            print("total: {:016b}\n".format(raw))
            print("{0:.4f} *C".format(raw_to_celsius(raw)))
        else:
            # Discard one byte (might need to take 2 cycles to get correct orientation
            ser.read()
