This is a C++ real time flight 3D simulator.

# Overview
This project, consists of a live 3D simulation of a flight using real-time data fetched from the OpenSky REST API. It determines the position of the aircraft in relation to the globe by using the latitude and longitude fetched from the API. it also determines the direction of the plane by calculating the vector of two consecutive positions.  
Specifications
The application is developed using the c++ based Ogre3D rendering engine. the minimum required version is c++1, boost library 1.67 and Ogre 1.11.3.

## How it looks like

![](flight-simultation.gif) 

# Requirements

1) Input from user should be an icao24 plane identifier.
	If no data is available for the entered icao24, then the user can choose to select a random flight.

2) The simulation should display the correct model of the plane, as well as the air company.
3) The screen should show the correct part of the world over which the plane is currently flying.
4) The current time of the day should be honoured by setting the correct lightening of the scene (day/night).

# Implementation  

## C++ Version 
The minimum version required to build this project is c++14.

## RestAPI 
The API used to retrieve the real-live data is open-sky

## Multithreading 
Multithreading is used to fetch the current coordinates of a plane and also keep the simulation smooth
and interruptable.

# Milestones
## Realistic simulation 
Achieving a realistic simulation by rendering the real model of the plane with the company’s logo and country’s flag on it, and setting the plane in the real geographical and directional properties of the flight.
## Time Optimisation 
Make the simulation as quick and fluid as possible by decreasing the time interval between two api calls to fetch data, and in case no new data is fetched, then try to predict the next position of the aircraft by using the previous data.
