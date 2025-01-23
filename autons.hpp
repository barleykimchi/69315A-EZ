#pragma once

void default_constants();

void blueSAWP();
void redSAWP();
void skills();
void turnTest();
void colorSort();

extern pros::adi::Pneumatics mogoL;
extern pros::adi::Pneumatics mogoR;

extern pros::Motor intake;
extern pros::Motor ladybrown_Left;
extern pros::Motor ladybrown_Right;

extern pros::v5::Optical optical;

void extendMogo();
void retractMogo();
