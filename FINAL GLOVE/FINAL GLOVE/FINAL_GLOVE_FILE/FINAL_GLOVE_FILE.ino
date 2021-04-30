//sensor stuffs
int pointerSensorPin = A0;  //pointer finger
int middleSensorPin = A1;   //middle finger
int ringSensorPin = A2;     //ring finger
int pinkieSensorPin = A3;   //pinkie finger
int thumbSensorPin = A4;    //thumb

//booleans
bool thumbDown = false;
bool basslineMuted = false;
bool melodyMuted = false;
bool harmonyMuted = false;
bool chordsMuted = false;
bool intervalLeapsMuted = false;
bool weirdThingMuted = false;
bool drumSampleMuted = false;
bool dampened = false;
bool detuned = false;
bool allMuted = false;

//toggle stuffs
bool pointerSensorState = HIGH;
bool middleSensorState = HIGH;
bool ringSensorState = HIGH;
bool pinkieSensorState = HIGH;
bool thumbSensorState = HIGH;

bool prevPointerSensorState = HIGH;
bool prevMiddleSensorState = HIGH;
bool prevRingSensorState = HIGH;
bool prevPinkieSensorState = HIGH;
bool prevThumbSensorState = HIGH;

bool pointerOn = false;
bool middleOn = false;
bool ringOn = false;
bool pinkieOn = false;

//TEST VARS
bool muted;

//SETUP
void setup() {
  Serial.begin(9600);
  pinMode(pointerSensorPin, INPUT); //set pointer sensor pin as input
}

//LOOP
void loop() {
  //read sensor pins
  pointerSensorState  = digitalRead(pointerSensorPin);
  middleSensorState   = digitalRead(middleSensorPin);
  ringSensorState     = digitalRead(ringSensorPin);
  pinkieSensorState   = digitalRead(pinkieSensorPin);
  thumbSensorState    = digitalRead(thumbSensorPin);

  //call muting functions
  muteBassline();       //1
  muteMelody();         //1, 3, 4
  muteHarmony();        //1, 2
  muteChords();         //1, 2, 3
  muteIntervalLeaps();  //1, 2, 4
  muteDrumSample();     //1, 4
  muteWeirdThing();     //4

  //dampen function
  dampen();             //3, 4
  detune();             //2, 3, 4

  //mute everything
  muteAll();            //no fingers up
  
  //test function
  //  muteTest();

  //call finger toggle functions
  fingerToggles();

  //reset prevStates
  prevPointerSensorState = pointerSensorState;
  prevMiddleSensorState  = middleSensorState;
  prevRingSensorState    = ringSensorState;
  prevPinkieSensorState  = pinkieSensorState;
  prevThumbSensorState   = thumbSensorState;
}

void muteBassline() { //FINGER 1 UP
  if (!pointerOn && middleOn && ringOn && pinkieOn) {          //if the magnet in fingers 2, 3, and 4 are toggled...
    //        Serial.println("bassline ready");
    if (toggledOn(thumbSensorState, prevThumbSensorState)) {   //AND the thumb is toggled
      basslineMuted = !basslineMuted;                           //switch the boolean
      Serial.print("bassline ");
      Serial.println(basslineMuted);

      if (basslineMuted == true) {                             //if one boolean is true do this
        usbMIDI.sendControlChange(1, 0, 1); //(command, value, channel)
      }
      else {                                                  //if the other boolean is true, do this
        usbMIDI.sendControlChange(1, 127, 1); //(command, value, channel)
        //      Serial.println("bassline unmuted");
      }
    }
  }
}

void muteHarmony() { //FINGER 1, 2 UP
  if (!pointerOn && !middleOn && ringOn && pinkieOn) {          //if the magnet in fingers 3 and 4 are toggled...
    //    Serial.println("harmony ready");
    if (toggledOn(thumbSensorState, prevThumbSensorState)) {   //AND the thumb is toggled
      harmonyMuted = !harmonyMuted;                               //switch the boolean
      Serial.print("harmony ");  
      Serial.println(harmonyMuted);

      if (harmonyMuted == true) {                               //if one boolean is true do this
        usbMIDI.sendControlChange(2, 0, 1); //(command, value, channel)
      }
      else {                                                  //if the other boolean is true, do this
        usbMIDI.sendControlChange(2, 127, 1); //(command, value, channel)
        //      Serial.println("harmony unmuted");
      }
    }
  }
}

void muteChords() { //FINGER 1, 2, 3 UP
  if (!pointerOn && !middleOn && !ringOn && pinkieOn) {       //if the magnet in finger 4 is toggled...
    //    Serial.println("chords ready");
    if (toggledOn(thumbSensorState, prevThumbSensorState)) {   //AND the thumb is toggled
      chordsMuted = !chordsMuted;                            //switch the boolean
      Serial.print("chords ");
      Serial.println(chordsMuted);

      if (chordsMuted == true) {                             //if one boolean is true do this
        usbMIDI.sendControlChange(3, 0, 1); //(command, value, channel)
      }
      else {                                                  //if the other boolean is true, do this
        usbMIDI.sendControlChange(3, 127, 1); //(command, value, channel)
        //      Serial.println("chords unmuted");
      }
    }
  }
}

void muteIntervalLeaps() {  //FINGER 1, 2, 4 UP
  if (!pointerOn && !middleOn && ringOn && !pinkieOn) {       //if the magnet in finger 3 is toggled...
    //    Serial.println("interval leaps ready");
    if (toggledOn(thumbSensorState, prevThumbSensorState)) {   //AND the thumb is toggled
      intervalLeapsMuted = !intervalLeapsMuted;                //switch the boolean
      Serial.print("interval leaps ");
      Serial.println(intervalLeapsMuted);

      if (intervalLeapsMuted == true) {                       //if one boolean is true do this
        usbMIDI.sendControlChange(4, 0, 1); //(command, value, channel)
      }
      else {                                                  //if the other boolean is true, do this
        usbMIDI.sendControlChange(4, 127, 1); //(command, value, channel)
        //      Serial.println("interval leaps unmuted");
      }
    }
  }
}


void muteMelody() {  //FINGER 1, 3, 4 UP
  if (!pointerOn && middleOn && !ringOn && !pinkieOn) {       //if the magnet in finger 3 is toggled...
    //    Serial.println("melody ready");
    if (toggledOn(thumbSensorState, prevThumbSensorState)) {   //AND the thumb is toggled
      melodyMuted = !melodyMuted;                //switch the boolean
      Serial.print("melody ");
      Serial.println(melodyMuted);

      if (melodyMuted == true) {                       //if one boolean is true do this
        usbMIDI.sendControlChange(5, 0, 1); //(command, value, channel)
      }
      else {                                                  //if the other boolean is true, do this
        usbMIDI.sendControlChange(5, 127, 1); //(command, value, channel)
        //      Serial.println("melody unmuted");
      }
    }
  }
}

void muteWeirdThing() { //FINGER 4 UP
  if (pointerOn && middleOn && ringOn && !pinkieOn) {         //if the magnet in fingers 1, 2, and 3 are toggled...
    //    Serial.println("weird thing ready");
    if (toggledOn(thumbSensorState, prevThumbSensorState)) {   //AND the thumb is toggled
      weirdThingMuted = !weirdThingMuted;                      //switch the boolean
      Serial.print("weird thing ");
      Serial.println(weirdThingMuted);

      if (weirdThingMuted == true) {                           //if one boolean is true do this
        usbMIDI.sendControlChange(6, 0, 1); //(command, value, channel)
      }
      else {                                                  //if the other boolean is true, do this
        usbMIDI.sendControlChange(6, 127, 1); //(command, value, channel)
        //      Serial.println("weird thing unmuted");
      }
    }
  }
}

void muteDrumSample() { //FINGERS 1, 4 UP
  if (!pointerOn && middleOn && ringOn && !pinkieOn) { //if the magnet in fingers 2 and 3 are toggled...
    //    Serial.println("drum sample ready");
    if (toggledOn(thumbSensorState, prevThumbSensorState)) {   //AND the thumb is toggled
      drumSampleMuted = !drumSampleMuted;                     //switch the boolean
      Serial.print("drum sample ");
      Serial.println(drumSampleMuted);

      if (drumSampleMuted == true) {                          //if one boolean is true do this
        usbMIDI.sendControlChange(7, 0, 1); //(command, value, channel)
      }
      else {                                                  //if the other boolean is true, do this
        usbMIDI.sendControlChange(7, 127, 1); //(command, value, channel)
      }
    }
  }
}

void dampen() {
  if (pointerOn && middleOn && !ringOn && !pinkieOn) {        //if the magnet in fingers 1 and 2 are toggled...
//    Serial.println("dampen ready");
    if (toggledOn(thumbSensorState, prevThumbSensorState)) {   //AND the thumb is toggled
      dampened = !dampened;                                    //switch the boolean
      Serial.print("dampened ");
      Serial.println(dampened);

      if (dampened == true) {                                  //if one boolean is true do this
        usbMIDI.sendControlChange(8, 0, 1); //(command, value, channel)
      }
      else {                                                  //if the other boolean is true, do this
        usbMIDI.sendControlChange(8, 127, 1); //(command, value, channel)
      }
    }
  }
}

void detune() {
  if (pointerOn && !middleOn && !ringOn && !pinkieOn) {        //if the magnet in fingers 1 are toggled...
//    Serial.println("detune ready");
    if (toggledOn(thumbSensorState, prevThumbSensorState)) {   //AND the thumb is toggled
      detuned = !detuned;                                    //switch the boolean
      Serial.print("detune ");
      Serial.println(detuned);

      if (detuned == true) {                                  //if one boolean is true do this
        usbMIDI.sendControlChange(9, 0, 1); //(command, value, channel)
      }
      else {                                                  //if the other boolean is true, do this
        usbMIDI.sendControlChange(9, 127, 1); //(command, value, channel)
      }
    }
  }
}

void muteAll(){
  if (pointerOn && middleOn && ringOn && pinkieOn) {          //if the magnet in fingers 1, 2, 3, and 4 are toggled...
//    Serial.println("mute all ready");
    if (toggledOn(thumbSensorState, prevThumbSensorState)) {   //AND the thumb is toggled
      allMuted = !allMuted;                                    //switch the boolean
      Serial.print("mute all ");
      Serial.println(allMuted);

      if (allMuted == true) {                                  //if one boolean is true do this
        usbMIDI.sendControlChange(10, 0, 1); //(command, value, channel)
      }
      else {                                                  //if the other boolean is true, do this
        usbMIDI.sendControlChange(10, 127, 1); //(command, value, channel)
      }
    }
  }
}

//THIS IS ONLY A TEST
void muteTest() {

  if (pointerOn && !middleOn && !ringOn && !pinkieOn) {
    muted = !muted;
    if (muted) {
      usbMIDI.sendControlChange(1, 0, 1);
    }
    else {
      usbMIDI.sendControlChange(1, 127, 1);
    }
  }
}
//END OF TEST

//TOGGLE FINGER FUNCTIONS
void fingerToggles() {
  pointerToggled();
  middleToggled();
  ringToggled();
  pinkieToggled();
}

void pointerToggled() {
  if (toggledOn(pointerSensorState, prevPointerSensorState)) { //if pointer finger is lowered
    //    Serial.println("pointer toggled on");
    pointerOn = true;
  }
  if (toggledOff(pointerSensorState, prevPointerSensorState)) { //if pointer finger is raised
    //    Serial.println("pointer toggled off");
    pointerOn = false;
  }
}

void middleToggled() {
  if (toggledOn(middleSensorState, prevMiddleSensorState)) { //if middle finger is lowered
    //    Serial.println("middle toggled on");
    middleOn = true;
  }
  if (toggledOff(middleSensorState, prevMiddleSensorState)) { //if middle finger is raised
    //    Serial.println("middle toggled off");
    middleOn = false;
  }
}

void ringToggled() {
  if (toggledOn(ringSensorState, prevRingSensorState)) { //if ring finger is lowered
    //    Serial.println("ring toggled on");
    ringOn = true;
  }
  if (toggledOff(ringSensorState, prevRingSensorState)) { //if ring finger is raised
    //    Serial.println("ring toggled off");
    ringOn = false;
  }
}

void pinkieToggled() {
  if (toggledOn(pinkieSensorState, prevPinkieSensorState)) { //if pinkie finger is lowered
    //    Serial.println("pinkie toggled on");
    pinkieOn = true;
  }
  if (toggledOff(pinkieSensorState, prevPinkieSensorState)) { //if pinkie finger is raised
    //    Serial.println("pinkie toggled off");
    pinkieOn = false;
  }
}

//Functions to designate the moment when the magnet touches the sensor or is pulled away
bool toggledOn(int aSensorState, int aPrevSensorState) {  //if finger is lowered (magnet away)
  if (aSensorState == HIGH && aPrevSensorState == LOW) {
    return (true);
  } else {
    return (false);
  }
}

bool toggledOff(int aSensorState, int aPrevSensorState) {  //if finger is raised (magnet touching)
  if (aSensorState == LOW && aPrevSensorState == HIGH) {
    return (true);
  } else {
    return (false);
  }
}
