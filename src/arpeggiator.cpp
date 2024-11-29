#include "arpeggiator.hpp"

void clear_arp_buffer() {}

void arpeggiate(libremidi::midi_out &midi) {}

void arp_loop(libremidi::midi_out &midi,
              const std::unordered_map<sf::Keyboard::Scancode, int> &key_map,
              int &octave, sf::Event &event, bool &arpeggiate_on) {
  if (arpeggiate_on) {
    std::cout << "arpeggiate on" << std::endl;
    if (event.type == sf::Event::KeyPressed) {
      if (event.key.scancode == sf::Keyboard::Scancode::M) {
        arpeggiate_on = !arpeggiate_on;
      }
    }
  } else {
    if (event.type == sf::Event::KeyPressed) {
      // if key_map key pressed
      if (key_map.contains(event.key.scancode)) {
        midi.send_message(0x90, key_map.at(event.key.scancode) + 12 * octave,
                          127);
      }
      // if octave up key pressed
      else if (event.key.scancode == sf::Keyboard::Scancode::X && octave < 4) {
        clear_arp_buffer();
        ++octave;
      }
      // if octave down key pressed
      else if (event.key.scancode == sf::Keyboard::Scancode::Z && octave > -5) {
        clear_arp_buffer();
        --octave;
      } else if (event.key.scancode == sf::Keyboard::Scancode::M) {
        clear_arp_buffer();
        arpeggiate_on = !arpeggiate_on;
        std::cout << "arpeggiate on" << std::endl;
      }
    } else if (event.type == sf::Event::KeyReleased) {
      // if key_map key released
      if (key_map.contains(event.key.scancode)) {
        midi.send_message(0x80, key_map.at(event.key.scancode) + 12 * octave,
                          127);
      }
    }
  }
}
