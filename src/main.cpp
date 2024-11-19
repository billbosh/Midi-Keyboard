#include <SFML/Graphics.hpp>
#include <cstddef>
#include <unordered_map>

struct midi_message {
    int note;
    int vel;
};

int main()
{
    auto window = sf::RenderWindow({100u, 100u}, "CMake SFML Project");
    window.setFramerateLimit(44100);
    window.setKeyRepeatEnabled(false);
    
    std::unordered_map<char, int> keys = {
        {'a', 64},
        {'s', 65},
        {'d', 66},
        {'f', 67}
    };
    int octave = 0;

    while (window.isOpen())
    {
        for (auto event = sf::Event(); window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.scancode == sf::Keyboard::Scancode::A) {
                    // send midi on message of note: keys['a']
                }
                else if (event.key.scancode == sf::Keyboard::Scancode::S) {
                    // send midi on message of note: keys['s']
                } 
                else if (event.key.scancode == sf::Keyboard::Scancode::D) {
                    // send midi on message of note: keys['d']
                }   
                else if (event.key.scancode == sf::Keyboard::Scancode::F) {
                    // send midi on message of note: keys['f']
                }
            }

            if (event.type == sf::Event::KeyReleased) {
                if (event.key.scancode == sf::Keyboard::Scancode::A) {
                    // send midi off message of note: keys['a']
                }
                else if (event.key.scancode == sf::Keyboard::Scancode::S) {
                    // send midi off message of note: keys['s']
                } 
                else if (event.key.scancode == sf::Keyboard::Scancode::D) {
                    // send midi off message of note: keys['d']
                }   
                else if (event.key.scancode == sf::Keyboard::Scancode::F) {
                    // send midi off message of note: keys['f']
                }
            }     
        }

        window.clear();
        window.display();
    }
}
