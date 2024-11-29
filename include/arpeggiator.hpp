#pragma once

#include <SFML/Graphics.hpp>
#include <libremidi/libremidi.hpp>
#include <iostream>
#include <unordered_map>

void arpeggiate(libremidi::midi_out &midi);

void arp_loop(libremidi::midi_out &midi,
              const std::unordered_map<sf::Keyboard::Scancode, int> &key_map,
              int &octave, sf::Event &event, bool &arpeggiate_on);
