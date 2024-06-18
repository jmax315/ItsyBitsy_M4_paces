#ifndef SERIAL_PUMP_H_MARK
#define SERIAL_PUMP_H_MARK

#include <Arduino.h>
#include <sam.h>

class SerialBuffer;

class SerialPump
{
public:
    SerialPump(Stream &port, SerialBuffer *input, SerialBuffer *output, Sercom *sercom_p = 0);
    void run();

    void disable_on_write_complete(void);

  private:
    Stream &port;
    Sercom *sercom;
    bool m_disable_on_write_finished;
    SerialBuffer *in;
    SerialBuffer *out;
};

#endif
