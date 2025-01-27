# esp32-game-audio-player
An ESP32 Arduino library for playing audio samples. Intended for use in games to trigger sound effects.

This is a thin wrapper for pschatzmann's excellent [arduino-audio-tools](https://github.com/pschatzmann/arduino-audio-tools) and related, specifically targetting the [Waveshare WM8960 Audio Board](https://www.waveshare.com/wiki/WM8960_Audio_Board)

# Example usage

```C++

#include "ESP32GameAudioPlayer.h"

enum SoundEffects {
    Blam,
    Kapow,
    Ping,
    Pong,
}

GameAudioPlayer gap = new GameAudioPlayer({
    {SoundEffects::Blam, "/blam.wav", GAP_WAV, 44000},
    {SoundEffect::Kapow, "/kapow.mp3", GAP_MP3, 22000},
});   

gap.addSound(SoundEffect::Ping, "/ping.wav", GAP_WAV, 22000);
gap.addSound(SoundEffect::Pong, "/pong.wav", GAP_WAV, 22000);

gap.initialise(GAP_I2S);

gap.trigger(SoundEffects::Blam);

```