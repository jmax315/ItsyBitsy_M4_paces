#ifndef COMMAND_HANDLER_H_MARK
#define COMMAND_HANDLER_H_MARK 1

class ICOMProtocol;
class SerialBuffer;

class CommandHandler
 {
public:
  CommandHandler(ICOMProtocol &in, SerialBuffer &debug_buffer);

  void run(void);

private:
  void dump_the_command();


  ICOMProtocol &in;
  int command_length;
  unsigned char command[32];
  SerialBuffer &debug;
};

#endif
