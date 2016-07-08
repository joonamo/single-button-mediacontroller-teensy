#include <Bounce.h>
Bounce button0 = Bounce(0, 10);
elapsedMillis timer;
int waitingForDouble = 0;

void setup() {
  Serial.begin(38400);
  pinMode(0, INPUT_PULLUP);
  pinMode(13, OUTPUT);
  timer = 0;

  // Flash the light for a bit
  for (int i = 3; i > 0; --i)
  {
    delay(50);
    digitalWrite(13, HIGH);
    delay(50);
    digitalWrite(13, LOW);  
  }
}

void loop() {
  button0.update();
  if (button0.fallingEdge())
  {
    if (waitingForDouble == 1)
    {
      // Second tap, reset timer
      timer = 0;
      waitingForDouble = 2;
    } 
    else if (waitingForDouble == 2)
    {
      waitingForDouble = 0;
      // Triple tap, fire instantly
      Keyboard.set_media(KEY_MEDIA_PREV_TRACK);
      Keyboard.send_now();
      Keyboard.set_media(0);
      Keyboard.send_now();
    } else {
      // First tap, start timer
      timer = 0;
      waitingForDouble = 1;
    }
  }
  if (waitingForDouble && timer > 250)
  {
    // Timeout
    if (waitingForDouble == 2) 
    {
      // Double tap
      Keyboard.set_media(KEY_MEDIA_NEXT_TRACK);
      Keyboard.send_now();
      Keyboard.set_media(0);
      Keyboard.send_now();  
    }
    else if (digitalRead(0)) 
    {
      // Button is up -> Single tap
      Keyboard.set_media(KEY_MEDIA_PLAY_PAUSE);
      Keyboard.send_now();
      Keyboard.set_media(0);
      Keyboard.send_now();
    } 
    else 
    {
      // Long press
      Keyboard.set_media(KEY_MEDIA_STOP);
      Keyboard.send_now();
      Keyboard.set_media(0);
      Keyboard.send_now();
    }
    waitingForDouble = 0;
  }
}
