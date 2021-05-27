#include <Arduino.h>
// This is a test example for SystemMisc
#include <stevesch-SystemMisc.h>

using stevesch::CycleCounter;
using stevesch::Interval;

CycleCounter fpsCounter;

constexpr long kInterval1_microseconds = 1000 * 1000; // 1 sec.
Interval interval1(kInterval1_microseconds);

constexpr long kInterval2_microseconds = 1000 * 5000; // 5 sec.
Interval interval2(kInterval2_microseconds);

inline long timeFn() { return micros(); }
long microsLastLoop = 0;

void setup()
{
  Serial.begin(115200);
  while (!Serial);
  Serial.println("Setup initializing...");

  // place setup code here

  Serial.println("Setup complete.");
}

void loop()
{
  long microsNow = timeFn();
  long dtMicros = microsNow - microsLastLoop;
  microsLastLoop = microsNow;
  int n;

  float dtSeconds = 1.0e-6f * dtMicros;
  fpsCounter.record(dtSeconds);

  n = interval1.update(dtMicros);
  if (n)
  {
    // n will be 1 unless our loop time exceeded our
    // interval time.
    static int loopCount1 = 0;
    loopCount1 += n;
    Serial.printf("interval1 expired times so far: %d\n", loopCount1);
  }

  n = interval2.update(dtMicros);
  if (n)
  {
    // n will be 1 unless our loop time exceeded our
    // interval time.
    static int loopCount2 = 0;
    loopCount2 += n;
    Serial.printf("interval2 expired times so far: %d\n", loopCount2);

    // print cycle counter stats:
    float fps = (fpsCounter.mAverageDt > 0.0f) ? (1.0f / fpsCounter.mAverageDt) : 0.0f;
    Serial.printf("fps: %5.1f  dt av: %4.1fms  dt min: %4.1fms  max: %4.1fms  loops: %d\n",
      fps,
      fpsCounter.mAverageDt * 1000.0f,
      fpsCounter.mDtMin * 1000.0f,
      fpsCounter.mDtMax * 1000.0f,
      fpsCounter.mCount);
    // reset min/max/average/count:
    fpsCounter.reset();
  }

  // just add some delay to simulate some processing
  delay(2);

  // some time-consuming computation to artificially lower the fps randomly
  int imax = rand() % 1000;
  for (int i=0; i < imax; ++i)
  {
    volatile float y = sinf(0.1f * i);
    y = y;
  }
}
