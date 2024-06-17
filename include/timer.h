#ifndef TIMER_H_MARK
#define TIMER_H_MARK 1

class Timer
{
public:
    Timer(int interval, void (*callback)(void));

    void run();

private:
  unsigned m_interval;
  void (*m_callback)(void);
  unsigned long m_last_callback_time;
};

#endif
