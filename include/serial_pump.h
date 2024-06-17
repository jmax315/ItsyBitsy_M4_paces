#ifndef SERIAL_PUMP_H_MARK
#define SERIAL_PUMP_H_MARK

class HardwareSerial;
class SerialBuffer;

class SerialPump
{
public:
    SerialPump(HardwareSerial &port, SerialBuffer &input, SerialBuffer &output);

    void run();

  private:
    HardwareSerial &port;
    SerialBuffer &in;
    SerialBuffer &out;
};

#endif
