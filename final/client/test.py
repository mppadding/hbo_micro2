import serial, time, math

checksum_factor = 69

def checksum(byte, checksum):
    return checksum == byte ^ checksum_factor

def to_neg(value, bits=16):
    return value - ((value << 1) & (1 << bits))

with serial.Serial('/dev/avr-nano') as ser:
    ser.baudrate = 115200
    while True:
        data = [ord(ser.read()) for x in range(6)]
        check = ord(ser.read())

        # print("Time: {}".format(end - start))

        if checksum(data[5], check):
            x = to_neg((data[0] << 8) | data[1])
            y = to_neg((data[2] << 8) | data[3])
            z = to_neg((data[4] << 8) | data[5])

            print("Angle X: {}".format(x))
            print("Angle Y: {}".format(y))
            print("Angle Z: {}".format(z))
            print()
        else:
            # Discard one byte, might take a couple of cycles to realign
            ser.read()
            print("Discarded one byte")
