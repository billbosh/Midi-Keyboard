#pragma once

#include <SFML/Graphics.hpp>
#include <libremidi/libremidi.hpp>
#include <iostream>
#include <unordered_map>

void current_octave_notes_off(
    libremidi::midi_out &midi,
    const std::unordered_map<sf::Keyboard::Scancode, int> &key_map,
    int &octave);

void midi_loop(libremidi::midi_out &midi,
               const std::unordered_map<sf::Keyboard::Scancode, int> &key_map,
               int &octave, sf::Event &event, bool &arpeggiate_on);
