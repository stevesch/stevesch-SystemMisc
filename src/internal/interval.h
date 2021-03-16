#ifndef STEVESCH_SYSTEMMISC_INTERNAL_INTERVANL_H_
#define STEVESCH_SYSTEMMISC_INTERNAL_INTERVANL_H_
#include <stevesch-SystemMisc.h>
#include <stevesch-MathBase.h>

namespace stevesch {

struct Interval
{
  long mPeriod;
  long mAccum;

  Interval(long period) : mPeriod(period), mAccum(0) {}
  void reset() { mAccum = 0; }
  int update(long dt) {
    mAccum += dt;
    const long period = mPeriod;
    if (mAccum < period) {
      return 0;
    }
    long accum0 = mAccum;
    mAccum = accum0 % period;
    int n = accum0 / period;
    return n;
  }

  long remain() const { return mPeriod - mAccum; }
};

}
#endif
