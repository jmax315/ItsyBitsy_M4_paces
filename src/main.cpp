#include <Arduino.h>
#include <sam.h>

#include "serial_buffer.h"
#include "icom_protocol.h"
#include "serial_pump.h"
#include "timer.h"
#include "command_handler.h"


void send_dummy_command(void);

SerialBuffer in, out, debug;

ICOMProtocol icom_layer(in, out);
SerialPump icom_serial_pump(Serial1, &in, &out, SERCOM3);
SerialPump debug_serial_pump(Serial, &in, &debug);
Timer dummy_command_timer(500, &send_dummy_command);
CommandHandler command_dumper(icom_layer, debug);


void setup() {
  pinMode(PIN_SERIAL1_TX, OUTPUT);
  digitalWrite(PIN_SERIAL1_TX, HIGH);

  Serial.begin(115200);
  Serial1.begin(9600);

  icom_serial_pump.disable_on_write_complete();
}

void loop() {
  icom_serial_pump.run();
  debug_serial_pump.run();
  dummy_command_timer.run();
  command_dumper.run();
}

void send_dummy_command(void)
{
  static unsigned char dummy_command[]= {0xfe, 0xfe, 0xfe, 0xfe, 0x01, 0x02, 0x03, 0xfd, 0xfe, 0xfe};

  icom_layer.send_command(dummy_command, sizeof(dummy_command));
}