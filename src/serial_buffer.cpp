#include "serial_buffer.h"

SerialBuffer::SerialBuffer()
  : in(0),
    out(0)
{}

int SerialBuffer::count() const
{
  return (in - out) & 0xff;
}

int SerialBuffer::free() const
{
  return sizeof(buf) - count() - 1;
}

int SerialBuffer::get()
{
  if (count() < 1)
     return -1;
  return buf[out++];
}

void SerialBuffer::put(unsigned char c)
{
  if (free() > 0)
    buf[in++] = c;
}

unsigned char &SerialBuffer::operator[](int index)
{
  return buf[(out + index) & 0xff];
}
