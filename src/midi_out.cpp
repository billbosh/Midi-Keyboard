#include "midi_out.hpp"

libremidi::midi_out setup_midi_out() { 
   // Display all available midi busses
   libremidi::observer obs;
   std::cout << "\nPlease choose one of the following busses you would like the "
                "send MIDI messages to: "
             << std::endl;
   for (int i = 0; const libremidi::input_port &port : obs.get_input_ports()) {
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
