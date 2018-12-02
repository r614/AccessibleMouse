#include <Keyboard.h>
#include <Mouse.h>

void setup(){
  delay(10000);
  Keyboard.begin();
  Mouse.begin();

  toggleSpeech(); 
}

void loop(){
}

void toggleSpeech(){
  Keyboard.press(KEY_LEFT_ALT);
  delay(100);
  Keyboard.press(KEY_LEFT_ALT);
}
