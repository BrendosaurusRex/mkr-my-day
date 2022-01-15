// MKR-My-Day! Rebel against Cancel Culture!

#include <SD.h>
#include <SPI.h>
#include <AudioZero.h>

const char filename[] = "JPIPER~1.WAV";

File waveFile;

void setup() {

  Serial.begin(9600);
  while (!Serial);
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(3000);
  digitalWrite(LED_BUILTIN, LOW);

  Serial.print("Initializing SD card...");
  if (!SD.begin()) {
    Serial.println("initialization failed!");
    while(1);
  }
  Serial.println("initialization done.");

  /* SPI.setClockDivider(4); */

  waveFile = SD.open(filename);
  if (!waveFile) {
    Serial.println("wave file is invalid!");
    while(1); // do nothing
  }
  Serial.print("Loaded file: ");
  Serial.println(filename);

  AudioZero.begin(2*44100);
  Serial.println("Starting playback");
  AudioZero.play(waveFile);
  delay(5000);
  Serial.println("Playback stopped");
} // setup()

void loop() {

  Serial.println("Starting playback");
  AudioZero.play(waveFile);
  delay(5000);
  Serial.println("Playback stopped");

}

