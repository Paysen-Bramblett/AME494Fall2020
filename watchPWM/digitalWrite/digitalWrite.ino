#define LILYGO_WATCH_2019_WITH_TOUCH
#include <LilyGoWatch.h>

void setup() {
  pinMode(25, OUTPUT);
  pinMode(26, OUTPUT);
}

void loop() {
  digitalWrite(25, HIGH);
  digitalWrite(26, LOW);
<<<<<<< HEAD
  delay(7);
  digitalWrite(25, LOW);
  digitalWrite(26, HIGH);
  delay(3);
=======
  delay(5000);
  digitalWrite(25, LOW);
  digitalWrite(26, HIGH);
  delay(5000);
>>>>>>> 174f9a6e55527c30416f91caca5709603066cfb0
}
