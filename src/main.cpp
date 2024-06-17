#include <Arduino.h>

#include "serial_buffer.h"
#include "icom_protocol.h"
#include "serial_pump.h"
#include "timer.h"


void send_dummy_command(void);
void process_the_command(unsigned char *command, int command_length);

SerialBuffer in, out, debug;

ICOMProtocol icom_layer(in, out);
SerialPump icom_serial_pump(Serial1, &in, &out);
SerialPump debug_serial_pump(Serial, &in, &debug);
Timer dummy_command_timer(500, &send_dummy_command);

void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);
}

void loop() {
  int command_length;
  unsigned char command_buffer[32];

  icom_serial_pump.run();
  debug_serial_pump.run();
  dummy_command_timer.run();

  if ((command_length = icom_layer.get_command(command_buffer, sizeof(command_buffer))) > 0)
    process_the_command(command_buffer, command_length);
}



void send_dummy_command(void)
{
  static unsigned char dummy_command[]= {0xfe, 0xfe, 0xfe, 0xfe, 0x01, 0x02, 0x03, 0xfd, 0xfe, 0xfe};

  icom_layer.send_command(dummy_command, sizeof(dummy_command));
}


void process_the_command(unsigned char *command, int command_length)
{
  static int command_number= 1;
  char wkbuf[512], *wbp= wkbuf;

  // format up a debug message
  wbp += sprintf(wbp, "got command (%d):", command_number++);
  while (command_length-- > 0)
    wbp += sprintf(wbp, " 0x%02x", *command++);
  wbp += sprintf(wbp, "\n");

  // and send it.
  for (char *outp= wkbuf; outp < wbp; outp++)
    debug.put(*outp);
}
