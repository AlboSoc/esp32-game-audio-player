#include <iostream>
#include <string>
#include <unordered_map>

#include "AudioTools/CoreAudio/AudioStreams.h"
#include "AudioTools/CoreAudio/AudioI2S/I2SStream.h"
#include "mtb_wm8960.h" // https://github.com/pschatzmann/arduino-wm8960
#include "AudioID.h"

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
        const auto& audioFile = getAudioFile(id);
        std::cout << "Playing: " << audioFile.filePath 
                  << " at " << audioFile.sampleRate << " Hz using " << audioFile.codec << " codec.\n";
    }

private:
    std::unordered_map<T, AudioFile> audioFiles;
};
