// Because I'm too lazy to write my own bounce code today
#include <Bounce.h>

// Left side Bumper Button
int pinPushButtonLeft1 = 6;
Bounce pushButtonLeft1 = Bounce(pinPushButtonLeft1, 10);
int pinPushButtonLeft2 = 8;
Bounce pushButtonLeft2 = Bounce(pinPushButtonLeft2, 10);

// Right side bumper button
int pinPushButtonRight1 = 9;
Bounce pushButtonRight1 = Bounce(pinPushButtonRight1, 10);
int pinPushButtonRight2 = 10;
Bounce pushButtonRight2 = Bounce(pinPushButtonRight2, 10);

// Ball plunger button either a physical spring loaded 
// device as on most older tables or a button as on pinbox
int pinPushButtonPlunger = 4;
Bounce pushButtonPlunger = Bounce(pinPushButtonPlunger, 10);

// Game start button almost always found on the left front 
// side of a pinball cabinet, used to start game play
int pinPushButtonStart = 12;
Bounce pushButtonStart = Bounce(pinPushButtonStart, 10);

// Tracks USB keyboard modifiers between loops
int lastModifiers = 0;
int currentModifiers = 0;

/**
 * Let's get the pinbox going! Open up the button ports! Get
 * the LED Blinker port ready to fire!
 */
void setup()
{
  pinMode(pinPushButtonLeft1, INPUT_PULLUP);
  pinMode(pinPushButtonLeft2, INPUT_PULLUP);
  pinMode(pinPushButtonRight1, INPUT_PULLUP);
  pinMode(pinPushButtonRight2, INPUT_PULLUP);
  pinMode(pinPushButtonPlunger, INPUT_PULLUP);
  pinMode(pinPushButtonStart, INPUT_PULLUP);
  
  Keyboard.begin();
}

/**
 * During each update we'll check for changes in the state of
 * each of our buttons.  In the case of the shift keys we will
 * manage what is being pressed using set_modifier bit flags.  
 * In the case of the keys, we'll map the rising and falling 
 * edges of the button signals directly to 'key up' and 'key down'
 * by setting specific keycodes
 * 
 * With button polling complete, we'll then use Leonardo's built-in
 * USB Keyboard functionality to send it back to the USB bus
 */
void loop()
{
  // Poll the left bumper button and set the bitflag to ON during
  // a falling edge and back to OFF on rising edges
  if (pushButtonLeft1.update()) {
    if(pushButtonLeft1.fallingEdge()) {
      Keyboard.press(KEY_LEFT_SHIFT);
    }
    else {
      Keyboard.release(KEY_LEFT_SHIFT);
    }
    
  }
  
  // Now do the same to the right bumper button and set the correct bits
  // of current modifiers for this side
  if (pushButtonRight1.update()) {
    if(pushButtonRight1.fallingEdge()) {
      Keyboard.press(KEY_RIGHT_SHIFT);   
    }
    else {
      Keyboard.release(KEY_RIGHT_SHIFT);
    }
  }
  
  // Poll the ball plunger button and set key #1 to space bar on falling
  // edges.  Reset key #1 to unset when a rising edge occurs
  if (pushButtonPlunger.update()) {
    if(pushButtonPlunger.fallingEdge()) {
      Keyboard.release(' ');
    }
    else {
      Keyboard.press(' ');
    }
  }
  
  // Poll the game start button in the same way and set or unset the
  // enter key across the USB
  if (pushButtonStart.update()) {
    if(pushButtonStart.fallingEdge()) {
      Keyboard.press(KEY_RETURN);
    }
    else {
      Keyboard.release(KEY_RETURN);
    }
  }
}
