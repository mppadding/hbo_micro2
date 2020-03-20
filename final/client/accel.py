import serial, time, math

checksum_factor = 69
scale = 16384

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
            x = to_neg((data[0] << 8) | data[1]) / scale
            y = to_neg((data[2] << 8) | data[3]) / scale
            z = to_neg((data[4] << 8) | data[5]) / scale
            sqx = x*x
            sqy = y*y
            sqz = z*z

            Ax = math.atan2(x, math.sqrt(sqy + sqz)) * (180/math.pi)
            Ay = math.atan2(y, math.sqrt(sqx + sqz)) * (180/math.pi)

            print("Angle X: {}".format(Ax))
            print("Angle Y: {}".format(Ay))
            print()
        else:
            # Discard one byte, might take a couple of cycles to realign
            ser.read()
            print("Discarded one byte")
