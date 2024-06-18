#include "serial_pump.h"
#include <HardwareSerial.h>
#include <sam.h>
#include "serial_buffer.h"


SerialPump::SerialPump(Stream &serial_port, SerialBuffer *input, SerialBuffer *output, Sercom *sercom_p)
  : port(serial_port),
    sercom(sercom_p),
    m_disable_on_write_finished(false),
    in(input),
    out(output)
{}

void SerialPump::run()
{
  if (in)
    while (port.available() > 0 && in->free() > 0)
      in->put(port.read());
  else
    while (port.available() > 0)
      port.read();

  if (!out)
    return;

  if (sercom && out->count())
    sercom->USART.CTRLB.reg |= SERCOM_USART_CTRLB_TXEN; 

  while (port.availableForWrite() > 0 && out->count() > 0)
    port.write(out->get());

  if (m_disable_on_write_finished  && out->count() == 0
      && sercom
      && sercom->USART.INTFLAG.bit.TXC
      && sercom->USART.INTFLAG.bit.DRE) {
    sercom->USART.CTRLB.reg &= ~SERCOM_USART_CTRLB_TXEN; 
  }
}   

void SerialPump::disable_on_write_complete()
{
  m_disable_on_write_finished = true;
}