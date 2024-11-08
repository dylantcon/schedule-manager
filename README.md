The abstract 'Event' class is an aggregate of 'Date' and 'Time' which then is the parent of
two child classes, 'Lecture' and 'Coursework', each with its own distinct member data. 
These in turn are what compose 'Schedule', in the form of a heterogenous list of 'Event' 
pointers to their children. Enumerations are used in addition to an std::<unordered_map> to
parse strings extracted from my own arbitrary schedule file format (which I will upload here when 
I finish making it), and in turn we are able to differentiate between the two separate methods 
necessary to properly initialize either child type.

I plan on creating 'dash.cpp' as a "dashboard" for the schedule app, and then when I learn
enough about GUI design and graphical programming, I will make 'io.cpp' to interface with
the preexisting code to display said dashboard in the window. Meanwhile, the program will
just interface with the terminal using some simple, text-based UI. I am excited to
see where this goes!
