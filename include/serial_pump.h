#ifndef SERIAL_PUMP_H_MARK
#define SERIAL_PUMP_H_MARK

class Stream;
class SerialBuffer;

class SerialPump
{
public:
    SerialPump(Stream &port, SerialBuffer *input, SerialBuffer *output);

    void run();

  private:
    Stream &port;
    SerialBuffer *in;
    SerialBuffer *out;
};

#endif
