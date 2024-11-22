#include <SFML/Graphics.hpp>
#include <libremidi/libremidi.hpp>
#include <iostream>
#include <unordered_map>

libremidi::midi_out setup_midi_out() {
    // Display all available midi busses
    libremidi::observer obs;
    std::cout << "\nPlease choose one of the following busses you would like the send MIDI messages to: " << std::endl;
    for (int i = 0; const libremidi::input_port& port : obs.get_input_ports()){
        std::cout << i << ": " << port.port_name << std::endl;
        ++i;
    }

    // Get input for desired bus
    std::cout << "Enter bus index: " << std::endl;
    int bus_choice = 0;
    std::cin >> bus_choice;

    // Create midi output object for the selected bus
    libremidi::midi_out midi;
    midi.open_port(obs.get_output_ports()[bus_choice]);

    return midi;
}

int main()
{
    auto window = sf::RenderWindow({100u, 100u}, "CMake SFML Project");
    window.setFramerateLimit(44100);
    window.setKeyRepeatEnabled(false);

    int octave = 0;
    const std::unordered_map<sf::Keyboard::Scancode, int> key_map {
        {sf::Keyboard::Scancode::A , 60},
        {sf::Keyboard::Scancode::W, 61},
        {sf::Keyboard::Scancode::S, 62},
        {sf::Keyboard::Scancode::E, 63},
        {sf::Keyboard::Scancode::D, 64},
        {sf::Keyboard::Scancode::F, 65},
        {sf::Keyboard::Scancode::T, 66},
        {sf::Keyboard::Scancode::G, 67},
        {sf::Keyboard::Scancode::Y, 68},
        {sf::Keyboard::Scancode::H, 69},
        {sf::Keyboard::Scancode::U, 70},
        {sf::Keyboard::Scancode::J, 71},
        {sf::Keyboard::Scancode::K, 72},
        {sf::Keyboard::Scancode::O, 73},
        {sf::Keyboard::Scancode::L, 74},
        {sf::Keyboard::Scancode::P, 75},
        {sf::Keyboard::Scancode::Semicolon, 76}
    };

    libremidi::midi_out midi = setup_midi_out();

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                // if key_map key pressed
                if (key_map.contains(event.key.scancode)) {
                    midi.send_message(
                        0x90,
                        key_map.at(event.key.scancode) + 12 * octave,
                        127);
                }
                // if octave up key pressed
                else if (event.key.scancode == sf::Keyboard::Scancode::X && octave < 4) {
                    // turn off all currently playing notes
                    for (const auto& [key, value] : key_map) {
                        midi.send_message(
                            0x80,
                            value + 12 * octave,
                            127);
                    }
                    ++octave;
                }
                // if octave down key pressed
                else if (event.key.scancode == sf::Keyboard::Scancode::Z && octave > -5) {
                    // turn off all currently playing notes
                    for (const auto& [key, value] : key_map) {
                        midi.send_message(
                            0x80,
                            value + 12 * octave,
                            127);
                    }
                    --octave;
                }
            }
            else if (event.type == sf::Event::KeyReleased) {
                // if key_map key released
                if (key_map.contains(event.key.scancode)) {
                    midi.send_message(
                        0x80,
                        key_map.at(event.key.scancode) + 12 * octave,
                        127);
                }
            }
        }
        window.clear();
        window.display();
    }
}
