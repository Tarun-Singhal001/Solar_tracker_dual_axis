#include <Servo.h>

Servo servohori; // Horizontal servo (BOTTOM SERVO)
int servoh = 90; // Start servo at 90 degrees (neutral position)
const int servohLimitHigh = 170; // Maximum range of servo (updated)
const int servohLimitLow = 10;   // Minimum range of servo (updated)

Servo servoverti; // Vertical servo (TOP SERVO)
int servov = 90; // Start servo at 90 degrees (neutral position)
const int servovLimitHigh = 170; // Maximum range of servo (updated)
const int servovLimitLow = 10;   // Minimum range of servo (updated)

int ldrtopr = A1; // Top right LDR pin
int ldrbotr = A0; // Bottom right LDR pin
int ldrtopl = A2; // Top left LDR pin
int ldrbotl = A3; // Bottom left LDR pin

void setup() {
  servohori.attach(10); // Horizontal servo connected to pin 10
  servohori.write(servoh);
  
  servoverti.attach(9); // Vertical servo connected to pin 9
  servoverti.write(servov);

  delay(500); // Initial delay
}

void loop() {
  // Read current servo positions
  servoh = servohori.read();
  servov = servoverti.read();
  
  // Read LDR values
  int topl = analogRead(ldrtopl); // Top left LDR
  int topr = analogRead(ldrtopr); // Top right LDR
  int botl = analogRead(ldrbotl); // Bottom left LDR
  int botr = analogRead(ldrbotr); // Bottom right LDR
  
  // Calculate averages
  int avgtop = (topl + topr) / 2; // Average of top LDRs
  int avgbot = (botl + botr) / 2; // Average of bottom LDRs
  int avgleft = (topl + botl) / 2; // Average of left LDRs
  int avgright = (topr + botr) / 2; // Average of right LDRs

  // Vertical servo adjustment
  if (avgtop < avgbot && servov > servovLimitLow) {
    servov--; // Move servo upward
    servoverti.write(servov);
    delay(8);
  } 
  else if (avgbot < avgtop && servov < servovLimitHigh) {
    servov++; // Move servo downward
    servoverti.write(servov);
    delay(8);
  }

  // Horizontal servo adjustment
  if (avgleft > avgright && servoh > servohLimitLow) {
    servoh--; // Move servo left
    servohori.write(servoh);
    delay(8);
  } 
  else if (avgright > avgleft && servoh < servohLimitHigh) {
    servoh++; // Move servo right
    servohori.write(servoh);
    delay(8);
  }

  delay(50); // Main loop delay
}
