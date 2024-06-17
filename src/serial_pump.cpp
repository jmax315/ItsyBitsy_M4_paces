#include "serial_pump.h"
#include <HardwareSerial.h>
#include "serial_buffer.h"


SerialPump::SerialPump(HardwareSerial &serial_port, SerialBuffer &input, SerialBuffer &output)
: port(serial_port),
  in(input),
  out(output)
{}

void SerialPump::run()
{
  while (port.available() > 0 && in.free() > 0)
    in.put(port.read());

  while (port.availableForWrite() > 0 && out.count() > 0)
    port.write(out.get());
}