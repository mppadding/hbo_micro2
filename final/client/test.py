import serial, time, math

def crc_ibutton(crc, data):
    crc ^= data
    for x in range(8):
        if(crc & 0x01):
            crc = (crc >> 1) ^ 0x8C
        else:
            crc >>= 1

    return crc

def to_neg(value, bits=16):
    return value - ((value << 1) & (1 << bits))

with serial.Serial('/dev/avr-uno') as ser:
    ser.baudrate = 115200
    while True:
        data = [ord(ser.read()) for x in range(2)]
        crc = ord(ser.read())

        if crc_ibutton(crc_ibutton(0, data[0]), data[1]) == crc:
            x = to_neg(data[0], bits=8)
            y = to_neg(data[1], bits=8)

            print("Angle X: {}".format(x))
            print("Angle Y: {}".format(y))
            print()
        else:
            # Discard one byte, might take a couple of cycles to realign
            ser.read()
            print("Discarded one byte")
