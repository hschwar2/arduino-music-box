//------------ PINS -----------------
const int kBlueButtonPin = A5;
const int kYellowButtonPin = A4;
const int kRedButtonPin = A3;
const int kGreenButtonPin = A2;


const int kBlueLEDPin = 6;
const int kYellowLEDPin = 7;
const int kRedLEDPin = 8;
const int kGreenLEDPin = 9;


const int kBuzzerPotPin = A0;
const int kButtonPressedPin = 2;


const int krgbRedPin = 11;
const int krgbBluePin = 13;
const int krgbGreenPin = 12;


volatile bool buttonStatusTrue = false;
volatile int whichButtonPressed = -1; //1  = blue, 2 = yellow, 3 = red, 4 = green (-1 is invalid)


//structs - these were not covered in class, but after research it was decided that these would be best
//to store a frequency and associated color
struct Note {
  int freq;
  int r;
  int g;
  int b;


};
// to store the note and associated duration of note
struct MelodyStep{
  Note note;
  int duration;


};


//FREQUENCY TO NOTE TRANSLATION
// Note frequencies (Hz) with associated colors- full chromatic scale
// index 0 = frequency, index 1 = r, index 2 = g, index 3 = b
const Note kNoteRest = {0, 0, 0, 0};
const Note kNoteC4   = {262, 255, 0, 0};     // Red
const Note kNoteCS4  = {277, 150, 20, 0};    // Dark Red
const Note kNoteD4   = {294, 255, 128, 0};   // Orange
const Note kNoteDS4  = {311, 150, 100, 0};   // Gold
const Note kNoteE4   = {330, 255, 255, 0};   // Bright Yellow
const Note kNoteF4   = {349, 0, 255, 0};     // Green
const Note kNoteFS4  = {370, 0, 150, 70};    // Pine Green
const Note kNoteG4   = {392, 0, 255, 255};   // Cyan
const Note kNoteGS4  = {415, 0, 100, 200};   // Medium Blue
const Note kNoteGSharp4 = {415, 0, 100, 200};// (Match GS4)
const Note kNoteA4   = {440, 0, 0, 255};     // Royal Blue
const Note kNoteAS4  = {466, 100, 0, 200};   // Deep Purple
const Note kNoteB4   = {494, 255, 0, 255};   // Magenta
const Note kNoteC5   = {523, 255, 100, 100}; // Coral/Salmon
const Note kNoteCS5  = {554, 200, 50, 100};  
const Note kNoteD5   = {587, 255, 200, 100}; // Peach
const Note kNoteDS5  = {622, 119, 255, 53};  // Neon Green
const Note kNoteE5   = {659, 255, 255, 150}; // Pale Yellow
const Note kNoteF5   = {698, 150, 255, 255}; // Pale Blue
const Note kNoteFS5  = {740, 0, 180, 120};   // Seafoam Green
const Note kNoteG5   = {784, 180, 150, 255}; // Lavender
const Note kNoteGS5  = {831, 208, 188, 255}; // Periwinkle
const Note kNoteA5   = {880, 195, 255, 188}; // Mint Green
const Note kNoteAS5  = {932, 29, 71, 24};    // Forest Green
const Note kNoteB5   = {988, 145, 255, 253}; // Aquamarine
const Note kNoteC6   = {1047, 233, 255, 169}; // Lime Green
const Note kNoteD6   = {1175, 145, 3, 87};    // Maroon
const Note kNoteE6   = {1319, 180, 126, 240}; // Violet
const Note kNoteF6   = {1397, 255, 100, 0};   // Orange
const Note kNoteG6   = {1568, 255, 243, 0};   // Gold


// SONGS - melody struct array of notes and associated frequencies
// Harry Potter Theme (Hedwig's Theme)
MelodyStep kMelodyHarryPotter[] = {
  {kNoteB4, 400}, {kNoteE5, 600}, {kNoteG5, 200}, {kNoteFS5, 400}, {kNoteE5, 800},
  {kNoteB5, 400}, {kNoteA5, 1200},
  {kNoteFS5, 1200},
  {kNoteE5, 600}, {kNoteG5, 200}, {kNoteFS5, 400}, {kNoteDS5, 800},
  {kNoteF5, 400}, {kNoteB4, 1600}}; // 14 long


// Imperial March
MelodyStep kMelodyImperialMarch[]= {
  {kNoteA4, 500}, {kNoteA4, 500}, {kNoteA4, 500}, {kNoteF4, 350}, {kNoteC5, 150},
  {kNoteA4, 500}, {kNoteF4, 350}, {kNoteC5, 150}, {kNoteA4, 650},
  {kNoteE5, 500}, {kNoteE5, 500}, {kNoteE5, 500}, {kNoteF5, 350}, {kNoteC5, 150},
  {kNoteGSharp4, 500}, {kNoteF4, 350}, {kNoteC5, 150}, {kNoteA4, 650}}; //18 long


// The Godfather Love Theme
MelodyStep kMelodyTheGodfather[] = {
  {kNoteE4, 375}, {kNoteA4, 375}, {kNoteC5, 375}, //1
  {kNoteB4, 375}, {kNoteA4, 375}, {kNoteC5, 375}, {kNoteA4, 375}, {kNoteB4, 375}, {kNoteA4, 375}, {kNoteF4, 375}, {kNoteG4, 375},
  {kNoteE4, 1500}, {kNoteE4, 375}, {kNoteA4, 375}, {kNoteC5, 375},
  {kNoteB4, 375}, {kNoteA4, 375}, {kNoteC5, 375}, {kNoteA4, 375}, {kNoteC5, 375}, {kNoteA4, 375}, {kNoteE4, 375}, {kNoteDS4, 375},
  {kNoteD4, 1500}, {kNoteD4, 375}, {kNoteF4, 375} // Ends at note 26
};


// Never Gonna Give You Up
MelodyStep kMelodyNeverGonnaGiveYouUp[] = {
  {kNoteD5, 789}, {kNoteE5, 789}, {kNoteA4, 526},
  {kNoteE5, 789}, {kNoteFS5, 789}, {kNoteA5, 131}, {kNoteG5, 131}, {kNoteFS5, 263},
  {kNoteD5, 789}, {kNoteE5, 789}, {kNoteA4, 1052},
  {kNoteA4, 131}, {kNoteA4, 131}, {kNoteB4, 131}, {kNoteD5, 263}, {kNoteD5, 131},
  {kNoteD5, 789}, {kNoteE5, 789}, {kNoteA4, 526},
  {kNoteE5, 789}, {kNoteFS5, 789}, {kNoteA5, 131}, {kNoteG5, 131}, {kNoteFS5, 263},
  {kNoteD5, 789}, {kNoteE5, 789}, {kNoteA4, 1052},
  {kNoteA4, 131}, {kNoteA4, 131}, {kNoteB4, 131} // Ends at note 30
};


MelodyStep kMelodyMario[] = {
  {kNoteE5, 125}, {kNoteE5, 125}, {kNoteRest, 125}, {kNoteE5, 125}, {kNoteRest, 125}, {kNoteC5, 125}, {kNoteE5, 125}, {kNoteRest, 125},
  {kNoteG5, 125}, {kNoteRest, 375}, {kNoteG4, 125}, {kNoteRest, 375},
  {kNoteC5, 250}, {kNoteG4, 250}, {kNoteE4, 250}, {kNoteA4, 250}, {kNoteB4, 250}, {kNoteAS4, 125}, {kNoteA4, 250},
  {kNoteG4, 150}, {kNoteE5, 150}, {kNoteG5, 150}, {kNoteA5, 250}, {kNoteF5, 125}, {kNoteG5, 125},
  {kNoteE5, 250}, {kNoteC5, 125}, {kNoteD5, 125}, {kNoteB4, 250}
}; // 29 steps


MelodyStep kMelodyStarWarsTheme[] = {
  {kNoteG4, 500}, {kNoteD5, 500}, {kNoteC5, 150}, {kNoteB4, 150}, {kNoteA4, 150}, {kNoteG5, 500}, {kNoteD5, 250},
  {kNoteC5, 150}, {kNoteB4, 150}, {kNoteA4, 150}, {kNoteG5, 500}, {kNoteD5, 250}, {kNoteC5, 150}, {kNoteB4, 150}, {kNoteC5, 150},
  {kNoteA4, 500}, {kNoteG4, 500}, {kNoteD5, 500}, {kNoteC5, 150}, {kNoteB4, 150}, {kNoteA4, 150}, {kNoteG5, 500}, {kNoteD5, 250},
  {kNoteC5, 150}, {kNoteB4, 150}, {kNoteA4, 150}, {kNoteG5, 500}
}; // 27 steps


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("Serial Monitor Initialized");


  pinMode(kBlueLEDPin, OUTPUT);
  pinMode(kYellowLEDPin, OUTPUT);
  pinMode(kRedLEDPin, OUTPUT);
  pinMode(kGreenLEDPin, OUTPUT);


  pinMode(krgbRedPin, OUTPUT);
  pinMode(krgbBluePin, OUTPUT);
  pinMode(krgbGreenPin, OUTPUT);


  attachInterrupt(digitalPinToInterrupt(kButtonPressedPin), buttonPressed, RISING);


}


void loop() {
  delay(100);


  if(buttonStatusTrue){
    //making false so it resets after
      buttonStatusTrue = false;  


    //pulling all LEDS low
      pullAllLedsLow();


    //finding which button was pressed
    // finding which button was pressed: 1 = blue; 2 = yellow; 3 = red; 4 = green
    // calls functions associated with button press (setting led to high and playing song   associated with button)


    switch(whichButtonPressed){
      case 1:
        digitalWrite(kBlueLEDPin, HIGH);
        playMelody(kMelodyStarWarsTheme, 27);
        delay(50);
      break;


      case 2:
        digitalWrite(kYellowLEDPin, HIGH);
        playMelody(kMelodyMario, 29);
        delay(50);
      break;


      case 3:
        digitalWrite(kRedLEDPin, HIGH);
        playMelody(kMelodyTheGodfather, 26);
        delay(50);
      break;


      case 4:
        digitalWrite(kGreenLEDPin, HIGH);
        playMelody(kMelodyNeverGonnaGiveYouUp, 30);
        delay(50);


      case -1:
        Serial.println("no button found :(");
      break;


      default:
        Serial.println("How did you get here?");
      break;
    }


  }
}


/*This function will analog read each color button to see which one was pressed, returning the int associated with that color. If none were pressed, returning -1*/
int pollButtonPressed(){
  if(analogRead(kBlueButtonPin) > 500){
    return 1;
  }
  else if (analogRead(kYellowButtonPin) > 500){
    return 2;
  }
  else if(analogRead(kRedButtonPin) > 500){
    return 3;
  }
  else if(analogRead(kGreenButtonPin) > 500){
    return 4;
  }
  else
    return -1;


}
/*This function pulls all of the leds to low as a reset, so none are bright at the same time*/
void pullAllLedsLow(){
  digitalWrite(kBlueLEDPin, LOW);
  digitalWrite(kYellowLEDPin, LOW);
  digitalWrite(kRedLEDPin, LOW);
  digitalWrite(kGreenLEDPin, LOW);


}
/*This function will set the volatile boolean buttonStatusTrue to true and poll which button was pressed, changing the volatile int whichButtonPressed*/
void buttonPressed(){
  buttonStatusTrue = true;
  whichButtonPressed = pollButtonPressed();


}
/*This function will run through the melody step arrays and run the song passed through as an argument. If the button is pressed, it breaks out of the for loop and stops playing the current song.*/
void playMelody(MelodyStep melody[], int lengthSong) {
    for (int i = 0; i < lengthSong; i++) {
      if(buttonStatusTrue){
        break;
      }
      //getting current note and duration
        Note currentNote = melody[i].note;
        int duration = melody[i].duration;
        //displaying rgb color to the led
          writeColor(currentNote.r, currentNote.g, currentNote.b);


        //playing melody
        if (currentNote.freq == kNoteRest.freq) {
            noTone(kBuzzerPotPin);
            delay(duration);
        } else {
            tone(kBuzzerPotPin, currentNote.freq, duration);
            delay(duration + 20);
        }
    }
    noTone(kBuzzerPotPin);
}


// RGB LED functions
void writeColor(int redPWM, int greenPWM, int bluePWM){
  //polling brightness of rgb led
    int voltage = analogRead(kBuzzerPotPin);
    float pwmVal = map(voltage, 0, 1023, 0, 255);
    float percentPWM = 1-pwmVal/255.;


  //Serial.println(percentPwm);
    Serial.println(percentPWM);


//writing to pins
  analogWrite(krgbRedPin, redPWM*percentPWM);
  analogWrite(krgbBluePin, bluePWM*percentPWM);
  analogWrite(krgbGreenPin, greenPWM*percentPWM);
}
