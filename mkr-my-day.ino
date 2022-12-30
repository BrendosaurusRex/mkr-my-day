#include <SD.h>
#include <ArduinoSound.h>

#define PLAY_BUTTON_PIN 7
#define VOLUME_PIN      A1

const char filename[] = "16jpiper.wav";

SDWaveFile waveFile;

void setup() {

    pinMode(PLAY_BUTTON_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(PLAY_BUTTON_PIN), PlayButtonInterrupt, FALLING);

    pinMode(VOLUME_PIN, INPUT);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, HIGH);

    Serial.begin(9600);
    delay(1000);
    Serial.print("Initializing SD card...");
    if (!SD.begin()) { Serial.println("Initialization failed!"); while(1); }
    // TODO: output SD files available
    Serial.println("Available files: ");

    Serial.println("Initialization done.");

    waveFile = SDWaveFile(filename);
    if (!waveFile) { Serial.println("Wave file is invalid!"); while(1); }
    Serial.print("Loaded file: ");
    Serial.println(filename);

    Serial.print("Bits per sample = ");
    Serial.println(waveFile.bitsPerSample());

    long channels = waveFile.channels();
    Serial.print("Channels = ");
    Serial.println(channels);

    long sampleRate = waveFile.sampleRate();
    Serial.print("Sample rate = ");
    Serial.print(sampleRate);
    Serial.println(" Hz");

    long duration = waveFile.duration();
    Serial.print("Duration = ");
    Serial.print(duration);
    Serial.println(" seconds");

    float volumeLevel = getVolumeLevel(VOLUME_PIN);
    AudioOutI2S.volume(volumeLevel);

    // check if the I2S output can play the wave file
    if (!AudioOutI2S.canPlay(waveFile)) { Serial.println("unable to play wave file using I2S!"); while (1); }

    Serial.println("===");
    Serial.println("Setup done!\n===");
    delay(500);
    digitalWrite(LED_BUILTIN, LOW);
} // setup()

void loop() {
    while(1);
} // loop()

void PlayButtonInterrupt() {
    noInterrupts();
    Serial.println(">>>");
    AudioOutI2S.volume(getVolumeLevel(VOLUME_PIN));
    Serial.println("Starting playback from Interrupt!");
    digitalWrite(LED_BUILTIN, HIGH);
    AudioOutI2S.play(waveFile);
    Serial.println("Finished playback from Interrupt!");
    Serial.println("###");
    digitalWrite(LED_BUILTIN, LOW);
    interrupts();
} // PlayButtonInterrupt()

float getVolumeLevel(int volumePin) {
    float volumePercent = (float) analogRead(volumePin) / 10.23;
    Serial.print("Volume = ");
    Serial.print(volumePercent);
    Serial.println("%");
    return volumePercent;
} // getVolumeLevel()

