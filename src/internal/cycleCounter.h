#ifndef STEVESCH_SYSTEMMISC_INTERNAL_CYCLECOUNTER_H_
#define STEVESCH_SYSTEMMISC_INTERNAL_CYCLECOUNTER_H_
#include <stevesch-SystemMisc.h>
#include <stevesch-MathBase.h>

namespace stevesch {

struct CycleCounter
{
  float mAverageDt = 0.0f;
  float mDtMin = 10.0f;
  float mDtMax = 0.0f;
  int mCount = 0;

  inline void reset()
  {
    mAverageDt = 0.0f;
    mDtMin = 10.0f;
    mDtMax = 0.0f;
    mCount = 0;
  }

  void record(float dt) {
    if (mCount) {
      mDtMin = min(mDtMin, dt);
      mDtMax = max(mDtMax, dt);
      mAverageDt = stevesch::lerpf(mAverageDt, dt, 0.1f);
    } else {
      mDtMin = dt;
      mDtMax = dt;
      mAverageDt = dt;
    }
    ++mCount;
  }
};

}
#endif
