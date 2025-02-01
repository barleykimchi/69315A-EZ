#pragma once

void default_constants();

// Color sorter variables declarations
extern bool sorterEnabled;
extern int targetHue;

// Controller auton selector variable declarations
extern int currAuton;
extern const int NUM_AUTONS;
extern string allAutons[]; 

// Pneumatic declarations
extern pros::adi::Pneumatics mogoL;
extern pros::adi::Pneumatics mogoR;

// Motor declarations
extern pros::Motor intake;
extern pros::Motor ladybrown_Left;
extern pros::Motor ladybrown_Right;

// Sensor declarations
extern pros::v5::Optical optical;

// Movement function declarations
void extendMogo();
void retractMogo();

// Autonomous programs
void blueSAWP();
void redSAWP();
void skills();
void turnTest();
