//Arduino Leonardo midi servocontroller for animatronic workshop
//servos on pins 2-7. 8-13 for various digital outs.
//by Thomas Rutgers (2021) - Techlab / St Joost School of Art & Design - ts.rutgers [at] avans.nl

#include <Servo.h>
#include "MIDIUSB.h"
Servo servo2, servo3, servo4, servo5, servo6, servo7;

void setup() {

  servo2.attach(2);
  servo3.attach(3);
  servo4.attach(4);
  servo5.attach(5);
  servo6.attach(6);
  servo7.attach(7);
  for (int n = 8; n <= 13; n++) {
    pinMode(n, OUTPUT);
  }
}

void controlChange(byte channel, byte control, byte value) {
  midiEventPacket_t event = {0x0B, 0xB0 | channel, control, value};
  MidiUSB.sendMIDI(event);
}

void loop() {

  //read midi
  midiEventPacket_t rx;
  rx = MidiUSB.read();
  if (rx.header == 0x0B) { // control change
    if (rx.byte2 == 2) {
      servo2.write(map(rx.byte3, 0, 127, 180, 0));
    }
    if (rx.byte3 == 3) {
      servo3.write(map(rx.byte3, 0, 127, 180, 0));
    }
    if (rx.byte4 == 4) {
      servo4.write(map(rx.byte3, 0, 127, 180, 0));
    }
    if (rx.byte5 == 5) {
      servo5.write(map(rx.byte3, 0, 127, 180, 0));
    }
    if (rx.byte6 == 6) {
      servo6.write(map(rx.byte3, 0, 127, 180, 0));
    }
    if (rx.byte7 == 7) {
      servo7.write(map(rx.byte3, 0, 127, 180, 0));
    }
    if (rx.byte2 >= 8 && rx.byte2 <= 13) {
      else {
        digitalWrite(rx.byte2, rx.byte3);
      }
    }
  }


}
