#include "midi_out.hpp"
#include "midi.hpp"
#include "arpeggiator.hpp"
#include <SFML/Graphics.hpp>
#include <libremidi/libremidi.hpp>
#include <unordered_map>

int main() {
  auto window = sf::RenderWindow({100u, 100u}, "Midi Keyboard");
  window.setFramerateLimit(44100);
  window.setKeyRepeatEnabled(false);

  int octave = 0;
  bool arpeggiate_on = false;
  const std::unordered_map<sf::Keyboard::Scancode, int> key_map{
      {sf::Keyboard::Scancode::A, 60},        {sf::Keyboard::Scancode::W, 61},
      {sf::Keyboard::Scancode::S, 62},        {sf::Keyboard::Scancode::E, 63},
      {sf::Keyboard::Scancode::D, 64},        {sf::Keyboard::Scancode::F, 65},
      {sf::Keyboard::Scancode::T, 66},        {sf::Keyboard::Scancode::G, 67},
      {sf::Keyboard::Scancode::Y, 68},        {sf::Keyboard::Scancode::H, 69},
      {sf::Keyboard::Scancode::U, 70},        {sf::Keyboard::Scancode::J, 71},
      {sf::Keyboard::Scancode::K, 72},        {sf::Keyboard::Scancode::O, 73},
      {sf::Keyboard::Scancode::L, 74},        {sf::Keyboard::Scancode::P, 75},
      {sf::Keyboard::Scancode::Semicolon, 76}};

  libremidi::midi_out midi = setup_midi_out();

  while (window.isOpen()) {
    for (auto event = sf::Event(); window.pollEvent(event);) {
      if (event.type == sf::Event::Closed) {
        current_octave_notes_off(midi, key_map, octave);
        window.close();
      }
      if (arpeggiate_on) {
        arp_loop(midi, key_map, octave, event, arpeggiate_on);
      } else {
        midi_loop(midi, key_map, octave, event, arpeggiate_on);
      }
    }
    /*window.clear();*/
    /*window.display();*/
  }
}
