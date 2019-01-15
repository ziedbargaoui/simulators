This is a C++ real time flight 3D simulator.

= REQUIREMENTS =

1) Input from user should be an icao24 plane identifier.
	If no data is available for the entered icao24, then the user can choose to select a random flight.

2) The simulation should display the correct model of the plane, as well as the air company.
3) The screen should show the correct part of the world over which the plane is currently flying.
4) The current time of the day should be honoured by setting the correct lightening of the scene (day/night).

** IMPLEMENTATION **

*** C++ Version ***
The minimum version required to build this project is c++14.

*** RestAPI ***
The API used to retrieve the real-live data is open-sky

*** Multithreading ***
Multithreading is used to fetch the current coordinates of a plane and also keep the simulation smooth
and interruptable.
