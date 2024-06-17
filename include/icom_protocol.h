#ifndef ICOM_PROTOCOL_H_MARK
#define ICOM_PROTOCOL_H_MARK 1

class SerialBuffer;

class ICOMProtocol {
public:    
    ICOMProtocol(SerialBuffer &input, SerialBuffer &output);

    int get_command(unsigned char *command_buffer, int command_buffer_size);
    void send_command(unsigned char *command_buffer, int command_buffer_size);

    void drop_any_garbage();
    bool we_have_a_complete_command();

private:
    SerialBuffer &in;
    SerialBuffer &out;
};

#endif
