#include "command_handler.h"
#include <stdio.h>
#include "icom_protocol.h"
#include "serial_buffer.h"

CommandHandler::CommandHandler(ICOMProtocol &input, SerialBuffer &debug_buffer)
  : in(input),
    debug(debug_buffer)
{}

void CommandHandler::run()
{
  if ((command_length = in.get_command(command, sizeof(command))) > 0)
    dump_the_command();
}

void CommandHandler::dump_the_command()
{
  static int command_number= 1;
  char wkbuf[512], *wbp= wkbuf;

  // format up a debug message
  wbp += sprintf(wbp, "got command (%d):", command_number++);
  for (int i= 0; i < command_length; i++)
    wbp += sprintf(wbp, " 0x%02x", command[i]);
  wbp += sprintf(wbp, "\n");

  // and send it.
  for (char *outp= wkbuf; outp < wbp; outp++)
    debug.put(*outp);
}