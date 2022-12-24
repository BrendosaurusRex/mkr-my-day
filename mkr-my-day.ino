#include <SD.h>
#include <ArduinoSound.h>

const char filename[] = "tone440.wav";

SDWaveFile waveFile;

void setup() {

    Serial.begin(9600);
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

    waveFile = SDWaveFile(filename);
    if (!waveFile) {
        Serial.println("Wave file is invalid!");
        while(1);
    }
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

    // adjust the playback volume
    AudioOutI2S.volume(5);

    // check if the I2S output can play the wave file
    if (!AudioOutI2S.canPlay(waveFile)) {
        Serial.println("unable to play wave file using I2S!");
        while (1);
    }

    // start playback
    Serial.println("Starting playback");
    AudioOutI2S.play(waveFile);
    if (AudioOutI2S.isPlaying()) { digitalWrite(LED_BUILTIN, HIGH); }
    AudioOutI2S.stop();
    Serial.println("Finished playback");
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);

} // setup()

void loop() {
    Serial.println("Starting playback");
    AudioOutI2S.play(waveFile);
    if (AudioOutI2S.isPlaying()) { digitalWrite(LED_BUILTIN, HIGH); }
    Serial.println("Finished playback");
    digitalWrite(LED_BUILTIN, LOW);
    delay(1000);

} // loop()

