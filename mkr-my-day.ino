// MKR-My-Day! Rebel against Cancel Culture!

#include <SD.h>
#include <AudioZero.h>

const char filename[] = "jpiper~1.wav";
const int  sampleRate = 2*44100;

File waveFile;

void setup() {

  Serial.begin(9600);
  // while (!Serial);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(3000);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.print("Initializing SD card...");
  if (!SD.begin()) {
    Serial.println("Initialization failed!");
    while(1);
  }
  Serial.println("Initialization done.");

  waveFile = SD.open(filename);
  if (!waveFile) {
    Serial.println("Wave file is invalid!");
    while(1); // do nothing
  }
  Serial.print("Loaded file: ");
  Serial.println(filename);

  AudioZero.begin(sampleRate);
  Serial.println("Starting playback");
  AudioZero.play(waveFile);
  AudioZero.end();
  Serial.println("Playback stopped");

} // setup()

void loop() {
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1000);
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);

} // loop()

