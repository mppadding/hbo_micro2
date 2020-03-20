import serial, time

checksum_factor = 69
# Scale: 
#   -  250°/s => 131
#   -  500°/s =>  65.5
#   - 1000°/s =>  32.8
#   - 2000°/s =>  16.4
scale = 131

def checksum(byte, checksum):
    return checksum == byte ^ checksum_factor

def to_neg(value, bits=16):
    return value - ((value << 1) & (1 << bits))

angle = 0

with serial.Serial('/dev/avr-nano') as ser:
    ser.baudrate = 115200
    while True:
        start = time.time()

        upper = ord(ser.read())
        lower = ord(ser.read())
        check = ord(ser.read())

        end = time.time()

        # print("Time: {}".format(end - start))

        if checksum(lower, check):
            raw = (upper << 8) | 0x00
            converted = to_neg(raw)
            angle += (converted / scale) * (end - start)

            print("upper:             {:08b}".format(upper))
            print("lower:             {:08b}".format(lower))
            print("total:     {:016b}".format(raw))
            print("neg:     {}".format(converted))
            print("angle: {}".format(angle))
        else:
            # Discard one byte, might take 2 cycles to realign
            ser.read()
            print("Discarded one byte")
