#ifndef SERIAL_BUFFER_H_MARK
#define SERIAL_BUFFER_H_MARK 1

class SerialBuffer
{
public:
  SerialBuffer();

  int count() const;
  int free() const;
  int get();
  void put(unsigned char c);
  unsigned char &operator[](int index);

private:
  unsigned char in;
  unsigned char out;
  unsigned char buf[256];
};

#endif
