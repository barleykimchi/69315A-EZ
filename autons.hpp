#pragma once

#include "EZ-Template/drive/drive.hpp"
#include "EZ-Template/piston.hpp"
#include "pros/adi.hpp"

// Motors used in autons
extern Drive chassis;
extern pros::v5::MotorGroup intake;
extern pros::v5::Motor ladybrown_Left;
extern pros::v5::Motor ladybrown_Right;

// Pistons used in autons
extern pros::adi::Pneumatics mogoL;
extern pros::adi::Pneumatics mogoR;
extern pros::adi::Pneumatics colorSort;
extern ez::Piston doinker;
extern ez::Piston hang;

// Sensors used in autons
extern pros::v5::Imu imu;
extern pros::v5::Optical optical;

// Functions used in autons
void extendMogo();
void retractMogo();
void default_constants();

// Autons used in matches
void br_NOWS();
void rr_NOWS();
void bl_NOWS();
void rl_NOWS();
void EMERGENCY_AUTON();
void color_sort_test();
void spitRED_task();
void spitBLUE_task();
void skills();

void blue_stake();
void red_stake();

// Example autons from EZ Template
// void motion_chaining();
// void combining_movements();
// void interfered_example();

void newAWP_RED();
void newAWP_BLUE();