#pragma region VEXcode Generated Robot Configuration
#include "vex.h"
using namespace vex;

// -----------------------------------------------------
// Device configuration (as shown in the report)
// If your VEXcode project generates different names/ports,
// replace this section with your project’s auto-generated config.
// -----------------------------------------------------
brain Brain;
inertial BrainInertial = inertial();
optical  Optical6      = optical(PORT6);
motor    Conveyor      = motor(PORT5, true);
motor    SortingArm    = motor(PORT4, false);
motor    Loader        = motor(PORT1, false);
distance Distance2     = distance(PORT2);

void vexcodeInit() {}
#pragma endregion

// =====================================================
// PAUSE / E-STOP TOGGLE SYSTEM
// =====================================================
// - Toggles pause on Brain button press (rising edge)
// - Stops all motors when paused
// - Tracks paused time so time-based cycles remain correct
//
void checkPause(bool &estopPaused,
                bool &lastButtonState,
                timer &cycleTimer,
                double &pausedOffset,
                double &pauseStart,
                bool cycleActive)
{
  // If your Brain button object is named differently, update here:
  bool buttonNow = Brain.buttonCheck.pressing();

  // Rising edge detection
  if (buttonNow && !lastButtonState)
  {
    estopPaused = !estopPaused;

    if (estopPaused)
    {
      Conveyor.stop();
      Loader.stop();
      SortingArm.stop();

      if (cycleActive)
      {
        pauseStart = cycleTimer.value();
      }

      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("E STOP ACTIVATED");
    }
    else
    {
      if (cycleActive)
      {
        double now = cycleTimer.value();
        pausedOffset += (now - pauseStart);
      }
    }
  }

  lastButtonState = buttonNow;
}

// =====================================================
// PAUSE-AWARE WAIT
// =====================================================
void uWait(int ms,
           bool &estopPaused,
           bool &lastButtonState,
           timer &cycleTimer,
           double &pausedOffset,
           double &pauseStart,
           bool cycleActive)
{
  int waited = 0;
  const int step = 10;

  while (waited < ms)
  {
    checkPause(estopPaused, lastButtonState, cycleTimer, pausedOffset, pauseStart, cycleActive);

    if (estopPaused)
    {
      wait(20, msec);
    }
    else
    {
      wait(step, msec);
      waited += step;
    }
  }
}

// =====================================================
// SENSOR + MOTOR INITIALIZATION
// =====================================================
void configureAllSensors(bool &estopPaused,
                         bool &lastButtonState,
                         timer &cycleTimer,
                         double &pausedOffset,
                         double &pauseStart)
{
  BrainInertial.calibrate();
  uWait(2000, estopPaused, lastButtonState, cycleTimer, pausedOffset, pauseStart, false);

  Conveyor.setPosition(0, turns);
  SortingArm.setPosition(0, degrees);
  Loader.setPosition(0, turns);

  Optical6.setLight(ledState::on);

  Brain.Screen.clearScreen();
  Brain.Screen.setFont(mono15);
}

// =====================================================
// CAP LOADED? (distance < 90 mm)
// =====================================================
bool capLoaded()
{
  double distVal = Distance2.objectDistance(mm);
  return distVal < 90.0;
}

// =====================================================
// LOAD CAP INTO CONVEYOR
// =====================================================
void loadCap(bool &estopPaused,
             bool &lastButtonState,
             timer &cycleTimer,
             double &pausedOffset,
             double &pauseStart)
{
  Loader.setVelocity(15, percent);
  Loader.setStopping(brake);
  Loader.setPosition(0, degrees);

  bool loadRunning = true;
  while (loadRunning)
  {
    checkPause(estopPaused, lastButtonState, cycleTimer, pausedOffset, pauseStart, false);

    if (estopPaused)
    {
      wait(20, msec);
    }
    else
    {
      double pos = Loader.position(degrees);
      if (pos > 180)
      {
        loadRunning = false;
      }
      else
      {
        Loader.spin(forward);
      }
    }
  }

  Loader.stop();
}

// =====================================================
// SORT CAP (arm movement)
// material =  1 -> plastic  (move to +10°)
// material = -1 -> metal    (move to -10°)
// Returns direction used so reset can return to 0°
// =====================================================
int sortCap(int material,
            bool &estopPaused,
            bool &lastButtonState,
            timer &cycleTimer,
            double &pausedOffset,
            double &pauseStart)
{
  SortingArm.setVelocity(40, percent);
  SortingArm.setStopping(brake);

  if (material == 1)
  {
    bool sorting = true;
    while (sorting)
    {
      checkPause(estopPaused, lastButtonState, cycleTimer, pausedOffset, pauseStart, false);

      if (estopPaused)
      {
        wait(20, msec);
      }
      else
      {
        double pos = SortingArm.position(degrees);
        if (pos >= 10)
        {
          sorting = false;
        }
        else
        {
          SortingArm.spin(forward);
        }
      }
    }
    SortingArm.stop();
    return 1;
  }

  if (material == -1)
  {
    bool sorting = true;
    while (sorting)
    {
      checkPause(estopPaused, lastButtonState, cycleTimer, pausedOffset, pauseStart, false);

      if (estopPaused)
      {
        wait(20, msec);
      }
      else
      {
        double pos = SortingArm.position(degrees);
        if (pos <= -10)
        {
          sorting = false;
        }
        else
        {
          SortingArm.spin(reverse);
        }
      }
    }
    SortingArm.stop();
    return -1;
  }

  return 0;
}

// =====================================================
// RESET ARM TO 0°
// =====================================================
void resetSortingArm(int direction,
                     bool &estopPaused,
                     bool &lastButtonState,
                     timer &cycleTimer,
                     double &pausedOffset,
                     double &pauseStart)
{
  SortingArm.setVelocity(20, percent);
  SortingArm.setStopping(brake);

  if (direction == 1)
  {
    bool resetting = true;
    while (resetting)
    {
      checkPause(estopPaused, lastButtonState, cycleTimer, pausedOffset, pauseStart, false);

      if (estopPaused)
      {
        wait(20, msec);
      }
      else
      {
        double pos = SortingArm.position(degrees);
        if (pos <= 0)
        {
          resetting = false;
        }
        else
        {
          SortingArm.spin(reverse);
        }
      }
    }
  }
  else if (direction == -1)
  {
    bool resetting = true;
    while (resetting)
    {
      checkPause(estopPaused, lastButtonState, cycleTimer, pausedOffset, pauseStart, false);

      if (estopPaused)
      {
        wait(20, msec);
      }
      else
      {
        double pos = SortingArm.position(degrees);
        if (pos >= 0)
        {
          resetting = false;
        }
        else
        {
          SortingArm.spin(forward);
        }
      }
    }
  }

  SortingArm.stop();
}

// =====================================================
// MAIN PROGRAM
// =====================================================
int main()
{
  vexcodeInit();

  bool estopPaused = false;
  bool lastButtonState = false;

  timer idleTimer;
  timer cycleTimer;

  double pausedOffset = 0.0;
  double pauseStart = 0.0;

  configureAllSensors(estopPaused, lastButtonState, cycleTimer, pausedOffset, pauseStart);

  // Tuned constants (from report code)
  const double CYCLE_TIME = 12.0;
  const int BLACK_THRESHOLD = 15;
  const int PLASTIC_THRESHOLD = 18;
  const int METAL_THRESHOLD = 80;

  bool programRunning = true;

  while (programRunning)
  {
    checkPause(estopPaused, lastButtonState, cycleTimer, pausedOffset, pauseStart, false);

    // Auto shutdown after 30s of no caps
    double idleVal = idleTimer.value();
    if (idleVal >= 30)
    {
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("No caps detected.");
      Brain.Screen.setCursor(2, 1);
      Brain.Screen.print("Shutting down.");
      wait(5, seconds);
      programRunning = false;
      break;
    }

    bool capIsHere = capLoaded();

    if (!capIsHere)
    {
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(1, 1);
      double distNow = Distance2.objectDistance(mm);
      Brain.Screen.print("Distance: %.1f mm", distNow);
      uWait(20, estopPaused, lastButtonState, cycleTimer, pausedOffset, pauseStart, false);
      continue;
    }

    // Cap detected → reset idle timer and run a full cycle
    idleTimer.reset();

    loadCap(estopPaused, lastButtonState, cycleTimer, pausedOffset, pauseStart);

    cycleTimer.reset();
    pausedOffset = 0.0;
    pauseStart = 0.0;

    Conveyor.setVelocity(20, percent);
    Conveyor.setStopping(brake);

    int maxBrightness = 0;
    bool capUnder = false;
    bool sortedAlready = false;
    int direction = 0;

    bool cycleRunning = true;
    while (cycleRunning)
    {
      checkPause(estopPaused, lastButtonState, cycleTimer, pausedOffset, pauseStart, true);

      if (estopPaused)
      {
        wait(20, msec);
        continue;
      }

      double effectiveTime = cycleTimer.value() - pausedOffset;
      if (effectiveTime >= CYCLE_TIME)
      {
        cycleRunning = false;
        break;
      }

      int bNow = Optical6.brightness();

      // Detect cap under sensor window (brightness > black threshold)
      if (bNow > BLACK_THRESHOLD)
      {
        capUnder = true;
        if (bNow > maxBrightness)
        {
          maxBrightness = bNow;
        }
      }

      // When cap has passed (brightness drops back), classify once
      bool leaving = (capUnder == true &&
                      bNow <= BLACK_THRESHOLD &&
                      sortedAlready == false);

      if (leaving)
      {
        int material = 0;
        if (maxBrightness >= METAL_THRESHOLD)
        {
          material = -1;
        }
        else if (maxBrightness >= PLASTIC_THRESHOLD)
        {
          material = 1;
        }

        direction = sortCap(material,
                            estopPaused,
                            lastButtonState,
                            cycleTimer,
                            pausedOffset,
                            pauseStart);

        sortedAlready = true;
      }

      Conveyor.spin(forward);
      uWait(20, estopPaused, lastButtonState, cycleTimer, pausedOffset, pauseStart, true);
    }

    Conveyor.stop();

    resetSortingArm(direction,
                    estopPaused,
                    lastButtonState,
                    cycleTimer,
                    pausedOffset,
                    pauseStart);

    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(1, 1);
    Brain.Screen.print("Peak Bright: %d", maxBrightness);
    Brain.Screen.setCursor(2, 1);
    double dnow = Distance2.objectDistance(mm);
    Brain.Screen.print("Dist: %.1f mm", dnow);

    uWait(200, estopPaused, lastButtonState, cycleTimer, pausedOffset, pauseStart, false);
  }

  Brain.programStop();
  return 0;
}
