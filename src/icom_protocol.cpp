#include "icom_protocol.h"
#include "serial_buffer.h"

ICOMProtocol::ICOMProtocol(SerialBuffer &input_buffer, SerialBuffer &output_buffer)
  : in(input_buffer),
    out(output_buffer)
{}

 int ICOMProtocol::get_command(unsigned char *command_buffer, int command_buffer_size)
{
    drop_any_garbage();
    if (!we_have_a_complete_command())
      return 0;


    in.get();
    in.get();

    int command_size= 0;
    while (command_size < command_buffer_size && in[0] != 0xfd && in[0] != 0xfe) {
      *command_buffer++ = in.get();
      command_size++;
    }
    in.get();

    return command_size;
}

void ICOMProtocol::send_command(unsigned char *command_buffer, int command_buffer_size)
{
  while (command_buffer_size-- > 0)
    out.put(*command_buffer++);
}

void ICOMProtocol::drop_any_garbage()
{
  for (;;)
  {
    if (in.count() <= 0)
      return;

    if (in.count() == 1 && in[0] == 0xfe)
      return;

    if (in.count() == 2 && in[0] == 0xfe && in[1] == 0xfe)
      return;

    if (in.count() >= 3 && in[0] == 0xfe && in[1] == 0xfe && in[2] != 0xfe)
      return;

    in.get();
  }
}

bool ICOMProtocol::we_have_a_complete_command()
{
  if (in.count() < 3) // need two header bytes, a trailer byte, and at least one payload byte.
    return false;

  if (in[0] != 0xfe || in[1] != 0xfe)
    return false;

  for (int i=2; i < in.count(); i++)
    if (in[i] == 0xfd || in[i] == 0xfe)
      return true;
  
  return false;
}
