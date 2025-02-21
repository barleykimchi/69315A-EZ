#pragma once

void default_constants();

// Color sorter variables declarations
extern bool sorterEnabled;
extern int targetHue;

// Anti-Jam status boolean declaration
extern bool jamEnabled;

// Ladybrown status boolean declaration
extern bool lbTaskEnabled;

// Pneumatic declarations
extern pros::adi::Pneumatics mogoL;
extern pros::adi::Pneumatics mogoR;
extern ez::Piston doinkerL;
extern ez::Piston doinkerR;

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
void turnTest();

void skills();

void blueSAWP();
void redSAWP();

void maxPos_Red();
void maxPos_Blue();

void maxNeg_Red();
void maxNeg_Blue();
