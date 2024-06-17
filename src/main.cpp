#include <Arduino.h>

#include "serial_buffer.h"
#include "icom_protocol.h"
#include "serial_pump.h"


SerialBuffer in, out, debug;
ICOMProtocol icom_layer(in, out);
SerialPump icom_pump(Serial1, in, out);

bool its_time_to_send()
{
  const unsigned long delay_between_sends_in_ms= 500;
  static unsigned long then= 0;
  unsigned long now = millis();

  if (now - then < delay_between_sends_in_ms)
    return false;
  then= now;
  return true;
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
    if (debug.free() > 0)
      debug.put(*outp);
}


void setup() {
  Serial.begin(115200);
  Serial1.begin(9600);
}

void loop() {
  int command_length;
  unsigned char command_buffer[32];
  unsigned char dummy_command[]= {0xfe, 0xfe, 0xfe, 0xfe, 0x01, 0x02, 0x03, 0xfd, 0xfe, 0xfe};

  icom_pump.run();

  while (Serial.availableForWrite() > 0 && debug.count() > 0)
    Serial.write(debug.get());

  if (its_time_to_send())
    icom_layer.send_command(dummy_command, sizeof(dummy_command));

  if ((command_length = icom_layer.get_command(command_buffer, sizeof(command_buffer))) > 0)
    process_the_command(command_buffer, command_length);
}

// put function definitions here:
