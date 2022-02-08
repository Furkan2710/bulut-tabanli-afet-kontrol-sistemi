#include "lsm6dsm.h"
#include "deneyap.h"
LSM6DSM IMU; 
void setup() {
 Serial.begin(115200);                         // Seri haberlesme baslatildi
 IMU.begin();                                  // IMU ayarlari konfigure edildi
}
void loop() {
  if (IMU.readFloatAccelX()<0.10 & IMU.readFloatAccelX()>-0.10)
  {
    Serial.println("Hers sey yolunda :)");
  }
  else if (IMU.readFloatAccelX()>0.10)
  {
    Serial.println("Bir seyler ters :/");
  }
  
  else if (IMU.readFloatAccelX()<-0.10)
  {
    Serial.println("Bir seyler ters :/");
  }
}
