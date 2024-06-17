#include "timer.h"

#include <Arduino.h>


Timer::Timer(int interval, void (*callback)(void))
  : m_interval(interval),
    m_callback(callback),
    m_last_callback_time(0)
{}

void Timer::run()
{
  unsigned long now = millis();

  if (now - m_last_callback_time < m_interval)
    return;

  m_last_callback_time= now;
  m_callback();
}
