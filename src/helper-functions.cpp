#include "vex.h"
#include "robot-config.h"

using namespace vex;

////////
// HELPER FUNCTION FOR AUTONOMOUS ROLLER FUNCTION TO CHECK IF HUE IS IN COLOR RANGE
////////
bool isColor(vex::color desiredColor, float hueNum) {
  // if the desired color is blue...
  if (desiredColor == blue) 
  {
    // if the hue is within the range of values to be considered "blue"..
    if (hueNum > blueMIN && hueNum < blueMAX) 
    {
      // detected color is blue.
      return true;
    }
  }
  else if (desiredColor == red) 
  {
    // if the hue is within the range of values to be considered "red"...
    if (hueNum > redMIN && hueNum < redMAX) 
    {
      // detected color is red.
      return true;
    }
  }


  // no conditions were fulfilled (detected color does not match desired color)
  return false; 
}

////////
// HELPER FUNCTION FOR DETERMINING IF A DISK IS IN THE INTAKE
///////
bool diskInIntake() {
  float dist = SonarSensor.distance(distanceUnits::cm); // store the detected distance

  // if the disk is detected in the intake...
  if (dist <= diskBoundMAX && dist >= diskBoundMIN) 
  {
    // disk is in intake
    return true;
  }

  // otherwise, disk is not in the intake
  return false;
}