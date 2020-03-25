using System;
using System.IO.Ports;

namespace net {
    class Program {
        static SerialPort _serialPort;
        static bool _stream = false;

        static void Main(string[] args) {
            if(args.Length > 0)
                if(args[0] == "stream")
                    _stream = true;
                else if(args[0] == "help" || args[0] == "--help") {
                    Console.WriteLine("Invoke program without arguments for `update` mode.\nOr invoke with `stream` for stream mode.");
                    return;
                }
                else
                    Console.WriteLine("Warning: Invalid argument `" + args[0] + "`. Defaulting to update mode");

            _serialPort = new SerialPort();

            _serialPort.PortName = "/dev/avr-uno";
            _serialPort.BaudRate = 115200;
            _serialPort.Open();
            Read();
        }

        /***
         * CRC calculating according to crc_ibutton in <util/crc16.h>
         * Calculates an 8 bit CRC with the polynomial of 0x8C
         */
        public static byte CalculateCRC(byte crc, byte data) {
            crc ^= data;

            for(int i = 0; i < 8; i++) {
                if((crc & 0x01) != 0)
                    crc = Convert.ToByte((crc >> 1) ^ 0x8C);
                else
                    crc >>= 1;
            }

            return crc;
        }

        public static void Read() {
            while (true) {
                // Check if packet received
                if(_serialPort.BytesToRead < 3)
                    continue;

                try {
                    byte[] buffer = new byte[3];
                    _serialPort.Read(buffer, 0, 3);

                    // Convert byte to sbyte
                    sbyte x = unchecked((sbyte)buffer[0]);
                    sbyte y = unchecked((sbyte)buffer[1]);

                    if(!_stream)
                        Console.Write("\r                  ");

                    // Check if CRC matches
                    if(buffer[2] == CalculateCRC(CalculateCRC(0x00, buffer[0]), buffer[1])) {
                        if(_stream)
                            Console.WriteLine("X: " + x.ToString() + ", Y: " + y.ToString());
                        else
                            Console.Write("\rX: " + x.ToString() + ", Y: " + y.ToString());
                    } else {
                        // CRC does not match, read a byte to skip it.
                        _serialPort.ReadByte();
                        if(_stream)
                            Console.WriteLine("Discarded one byte");
                        else
                            Console.Write("\rDiscarded one byte");
                    }
                }
                catch (TimeoutException) { }
            }
        }

    }
}
