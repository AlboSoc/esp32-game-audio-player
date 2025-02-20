#include <iostream>
#include <string>
#include <unordered_map>

#include "AudioTools/CoreAudio/AudioStreams.h"
#include "AudioTools/CoreAudio/AudioI2S/I2SStream.h"
#include "mtb_wm8960.h" // https://github.com/pschatzmann/arduino-wm8960
#include "AudioID.h"
#include "AudioTools/AudioLibs/WM8960Stream.h"

struct AudioFile {
    std::string filePath;
    int sampleRate;
    std::string codec;
};

template <typename T>
class ESP32GameAudioPlayer {
public:
    void addSound(T id, const std::string& path, int rate, const std::string& codec) {
        audioFiles[id] = {path, rate, codec};
    }

    const AudioFile& getAudioFile(T id) const {
        return audioFiles.at(id);
    }

    void play(T id) {
        if (!hasBegun) {
            std::cout << "ESP32GameAudioPlayer has not begun, so not playing.\n";
            return;
        }
        const auto& audioFile = getAudioFile(id);
        std::cout << "Playing: " << audioFile.filePath 
                  << " at " << audioFile.sampleRate << " Hz using " << audioFile.codec << " codec.\n";
    }

    void begin() {
        if (hasBegun) {
            return;
        }
        hasBegun = true;
        std::cout << "ESP32GameAudioPlayer has begun.\n";
    }

    void end() {
        if (!hasBegun) {
            return;
        }
        hasBegun = false;
        std::cout << "ESP32GameAudioPlayer has ended.\n";
    }

    // Arduino Setup
    void setup(void) {  
        // // Open Serial 
        // Serial.begin(115200);
        // while(!Serial);
        // AudioLogger::instance().begin(Serial, AudioLogger::Warning);

        // // setup wire on pins 19 and 21
        // Wire.begin(19, 21);
        // Wire.setClock(1000);

        // // start I2S
        // Serial.println("starting I2S...");
        // auto config = out.defaultConfig(TX_MODE);
        // config.sample_rate = sample_rate; 
        // config.channels = channels;
        // config.bits_per_sample = 16;
        // config.wire = &Wire;
        // // config.features =  WM8960_FEATURE_HEADPHONE;
        // // config.features =  WM8960_FEATURE_SPEAKER;
        // // use default i2s pins 
        // //config.pin_bck = 14;
        // //config.pin_ws = 15;
        // //config.pin_data = 22;
        // // custom I2S output pins
        // config.pin_bck = 27;
        // config.pin_ws = 26;
        // config.pin_data = 25;  

        // if (!out.begin(config)){
        //     stop();
        // }

        // // Setup sine wave
        // sineWave.begin(channels, sample_rate, N_B4);

        // Serial.println("setting volume:");
        // // config.features =  WM8960_FEATURE_SPEAKER;  // runtime changing of this seems to work, so long as both the headphone and speaker were enabled initially.
        // // out.setVolumeOut(0);
        // // config.features =  WM8960_FEATURE_HEADPHONE;  // runtime changing of this seems to work, so long as both the headphone and speaker were enabled initially.
        // // out.setVolumeOut(1.0);  // To loud!  2W out of built-in speakers
        // out.setVolumeOut(0.5);  // That's better. 1W out of built-in speakers


        // Serial.println("started...");
    }


private:
    std::unordered_map<T, AudioFile> audioFiles;
    bool hasBegun = false;

    uint16_t sample_rate=44100;
    uint8_t channels = 2;                                      // The stream will have 2 channels 
    SineWaveGenerator<int16_t> sineWave(32000);                // subclass of SoundGenerator with max amplitude of 32000
    GeneratedSoundStream<int16_t> sound(sineWave);             // Stream generated from sine wave
    WM8960Stream out; 
    StreamCopy copier(out, sound);                             // copies sound into i2s


};
