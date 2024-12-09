#include "main.h"

// Speed Constants (Out of 127)
const int DRIVE_SPEED = 127;
const int MOGO_DRIVE_SPEED = 60;
const int TURN_SPEED = 100;
const int SWING_SPEED = 50;

// Constants
void default_constants() {
  chassis.pid_heading_constants_set(3, 0, 20);
  chassis.pid_drive_constants_set(20, 0, 165); 
  chassis.pid_turn_constants_set(3, 0, 22);

  chassis.pid_turn_exit_condition_set(50_ms, 3_deg, 250_ms, 3_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(80_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);

  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  chassis.slew_drive_constants_set(7_in, 80);

  chassis.pid_swing_constants_set(6, 0, 65);
  chassis.pid_swing_exit_condition_set(80_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
}

void extendMogo(){
  mogoL.set_value(true);
  mogoR.set_value(true); 
}

void retractMogo(){
  mogoL.set_value(false);
  mogoR.set_value(false);
}

void spitRED_task() {
    while (true) {
        if (optical.get_hue() < 20) {
            colorSort.extend();
            pros::delay(500);
        } else {
            colorSort.retract();
        }
        pros::delay(10);
    }
}

void spitBLUE_task() {
    while (true) {
        if (optical.get_hue() > 200) {
            colorSort.extend();
            pros::delay(500);
        } else {
            colorSort.retract();
        }
        pros::delay(10);
    }
}

void newAWP_RED(){                                                               // Done

  pros::Task color_sort(spitBLUE_task);

  // Score Preload on Alliance Stake
  chassis.pid_drive_set(10_in, DRIVE_SPEED);
  chassis.pid_wait_until(7_in);

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait_until(70_deg);

  chassis.pid_drive_set(8_in, DRIVE_SPEED);
  pros::delay(300);
  intake.move(127);
  chassis.pid_wait();

  pros::delay(300);
  intake.move(0);

  // Moving towards 1st mogo

  chassis.pid_drive_set(-6_in, DRIVE_SPEED);
  chassis.pid_wait_until(-4_in);

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(1.5_in, DRIVE_SPEED);
  chassis.pid_wait_until(1_in);
  extendMogo();

  chassis.pid_turn_set(-125_deg, TURN_SPEED);
  chassis.pid_wait();

// Drive forward and slow down to get Mogo
  chassis.pid_drive_set(20_in, DRIVE_SPEED);
  chassis.pid_wait_until(19_in);
  chassis.pid_drive_set(40_in, MOGO_DRIVE_SPEED);
  chassis.pid_wait_until(35_in);

  retractMogo();

  chassis.pid_drive_set(7_in, DRIVE_SPEED);
  chassis.pid_wait_until(6_in);

  chassis.pid_turn_set(-20_deg, TURN_SPEED);
  chassis.pid_wait_until(-19_deg);

// make a while true w a bool i can set
bool intake_status = true;

if(intake_status == true){
  intake.move(127);
} else if (intake_status == false){
  intake.move(0);
}

  chassis.pid_drive_set(-18_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(80_deg, TURN_SPEED);
  chassis.pid_wait_until(69_deg);

  chassis.pid_drive_set(-14_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(10_in, DRIVE_SPEED);
  chassis.pid_wait_until(9_in);

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait_until(179_deg);

  chassis.pid_drive_set(-35_in, DRIVE_SPEED);
  chassis.pid_wait();

  intake_status == false;

  ladybrown_Left.move(50);
  ladybrown_Right.move(-50);

  pros::delay(500);

  ladybrown_Left.move(0);
  ladybrown_Right.move(0);

  color_sort.remove();
}

void newAWP_BLUE(){                                                               // Done

  pros::Task color_sort(spitRED_task);

  // Score Preload on Alliance Stake
  chassis.pid_drive_set(10_in, DRIVE_SPEED);
  chassis.pid_wait_until(7_in);

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait_until(-70_deg);

  chassis.pid_drive_set(8_in, DRIVE_SPEED);
  pros::delay(300);
  intake.move(127);
  chassis.pid_wait();

  pros::delay(300);
  intake.move(0);

  // Moving towards 1st mogo

  chassis.pid_drive_set(-6_in, DRIVE_SPEED);
  chassis.pid_wait_until(-4_in);

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(1.5_in, DRIVE_SPEED);
  chassis.pid_wait_until(1_in);
  extendMogo();

  chassis.pid_turn_set(125_deg, TURN_SPEED);
  chassis.pid_wait();

  // Drive forward and slow down to get Mogo
  chassis.pid_drive_set(20_in, DRIVE_SPEED);
  chassis.pid_wait_until(19_in);
  chassis.pid_drive_set(40_in, MOGO_DRIVE_SPEED);
  chassis.pid_wait_until(35_in);

  retractMogo();

  chassis.pid_drive_set(7_in, DRIVE_SPEED);
  chassis.pid_wait_until(6_in);

  chassis.pid_turn_set(20_deg, TURN_SPEED);
  chassis.pid_wait_until(19_deg);

// make a while true w a bool i can set
bool intake_status = true;

if(intake_status == true){
  intake.move(127);
} else if (intake_status == false){
  intake.move(0);
}

  chassis.pid_drive_set(-18_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-80_deg, TURN_SPEED);
  chassis.pid_wait_until(-69_deg);

  chassis.pid_drive_set(-14_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(10_in, DRIVE_SPEED);
  chassis.pid_wait_until(9_in);

  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait_until(179_deg);

  chassis.pid_drive_set(-35_in, DRIVE_SPEED);
  chassis.pid_wait();

  intake_status == false;

  ladybrown_Left.move(50);
  ladybrown_Right.move(-50);

  pros::delay(500);

  ladybrown_Left.move(0);
  ladybrown_Right.move(0);

  color_sort.remove();
}

// Blue Right Auton (No Wall Stake)
// 4 blue rings on 1 goal, touch ladder
void br_NOWS() {

  pros::Task color_sort(spitRED_task);

  // Drive to mogo
  extendMogo();
  pros::delay(300);

  chassis.pid_drive_set(35_in, MOGO_DRIVE_SPEED);
  chassis.pid_wait();

  // Clamp mogo
  retractMogo();
  pros::delay(300);

  // Back up to secure mogo
  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(5_in, DRIVE_SPEED);
  chassis.pid_wait_until(4_in);

  // Turn towards second ring
  chassis.pid_turn_set(-115_deg, TURN_SPEED);

  intake.move(127);
  pros::delay(1000);

  chassis.pid_wait_until(-110_deg);

  // Drive towards second ring
  chassis.pid_drive_set(-28_in, DRIVE_SPEED);
  intake.move(127);
  chassis.pid_wait_until(-25_in);

  // Turn towards third ring
  imu.reset();
  chassis.pid_turn_set(120_deg, TURN_SPEED);
  intake.move(127);
  chassis.pid_wait();

  chassis.pid_drive_set(-7_in, DRIVE_SPEED);
  intake.move(127);
  chassis.pid_wait();

  // Turn towards fourth ring
  imu.reset();
  chassis.pid_turn_set(-110_deg, TURN_SPEED);
  intake.move(127);
  chassis.pid_wait();

  chassis.pid_drive_set(-6_in, DRIVE_SPEED);
  intake.move(127);
  chassis.pid_wait();
  
  // Turn towards ladder
  imu.reset();
  chassis.pid_turn_set(-135_deg, TURN_SPEED);
  intake.move(127);
  chassis.pid_wait();

  // Drive to ladder
  chassis.pid_drive_set(-40_in, DRIVE_SPEED);
  intake.move(127);
  pros::delay(300);
  intake.move(0);
  chassis.pid_wait_until(-35_in);

  // Touch ladder
  // ladybrown.move(60);
  // pros::delay(500);
  // ladybrown.move(0);
  // ladybrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  color_sort.remove();
  
}

// Red Left Auton (No Wall Stake)
// 4 red rings on 1 goal, touch ladder
void bl_NOWS(){                                                                 // Done

  pros::Task color_sort(spitRED_task);

  extendMogo();

  chassis.pid_drive_set(20_in, DRIVE_SPEED);
  chassis.pid_wait_until(19_in);
  
  chassis.pid_drive_set(25_in, MOGO_DRIVE_SPEED);
  chassis.pid_wait_until(15_in);

  retractMogo();

  chassis.pid_turn_set(65_deg, TURN_SPEED);
  chassis.pid_wait_until(60_deg);

  bool intake_status = true;

  if(intake_status == true){
    intake.move(127);
  } else if (intake_status == false){
    intake.move(0);
  }

  chassis.pid_drive_set(-35_in, DRIVE_SPEED);
  chassis.pid_wait_until(-30_in);

  chassis.pid_turn_set(-125_deg, TURN_SPEED);
  chassis.pid_wait_until(-120_deg);

    intake_status = false;

  chassis.pid_drive_set(-50_in, DRIVE_SPEED);
  chassis.pid_wait_until(-45_in);

  ladybrown_Left.move(50);
  ladybrown_Right.move(-50);

  pros::delay(500);

  ladybrown_Left.move(0);
  ladybrown_Right.move(0);

  color_sort.remove();
}

void rr_NOWS(){

  pros::Task color_sort(spitRED_task);

  extendMogo();

  chassis.pid_drive_set(20_in, DRIVE_SPEED);
  chassis.pid_wait_until(19_in);
  
  chassis.pid_drive_set(30_in, MOGO_DRIVE_SPEED);
  chassis.pid_wait_until(15_in);

  retractMogo();

  pros::delay(1000);

  chassis.pid_turn_set(-65_deg, TURN_SPEED);
  chassis.pid_wait_until(-60_deg);

  bool intake_status = true;

  if(intake_status == true){
    intake.move(127);
  } else if (intake_status == false){
    intake.move(0);
  }

  chassis.pid_drive_set(-35_in, DRIVE_SPEED);
  chassis.pid_wait_until(-30_in);

  // chassis.pid_turn_set(125_deg, TURN_SPEED);
  // chassis.pid_wait_until(120_deg);

  //   intake_status = false;

  // chassis.pid_drive_set(-50_in, DRIVE_SPEED);
  // chassis.pid_wait_until(-45_in);

  // ladybrown_Left.move(50);
  // ladybrown_Right.move(-50);

  // pros::delay(500);

  // ladybrown_Left.move(0);
  // ladybrown_Right.move(0);

  color_sort.remove();
}

void rl_NOWS(){

  pros::Task color_sort(spitBLUE_task);

  // Drive to mogo
  extendMogo();
  pros::delay(300);

  chassis.pid_drive_set(35_in, MOGO_DRIVE_SPEED);
  chassis.pid_wait();

  // Clamp mogo
  retractMogo();
  pros::delay(300);

  // Back up to secure mogo
  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(5_in, DRIVE_SPEED);
  chassis.pid_wait_until(4_in);

  // Turn towards second ring
  chassis.pid_turn_set(115_deg, TURN_SPEED);

  intake.move(127);
  pros::delay(1000);

  chassis.pid_wait_until(110_deg);

  // Drive towards second ring
  chassis.pid_drive_set(-25_in, DRIVE_SPEED);
  intake.move(127);
  chassis.pid_wait();

  // // Turn towards third ring
  chassis.pid_turn_set(91_deg, TURN_SPEED);
  intake.move(127);
  chassis.pid_wait_until(90_deg);

  chassis.pid_drive_set(-7_in, DRIVE_SPEED);
  intake.move(127);
  chassis.pid_wait();

  // // Turn towards fourth ring
  // imu.reset();
  // chassis.pid_turn_set(-110_deg, TURN_SPEED);
  // intake.move(127);
  // chassis.pid_wait();

  // chassis.pid_drive_set(-6_in, DRIVE_SPEED);
  // intake.move(127);
  // chassis.pid_wait();
  
  // // Turn towards ladder
  // imu.reset();
  // chassis.pid_turn_set(-135_deg, TURN_SPEED);
  // intake.move(127);
  // chassis.pid_wait();

  // // Drive to ladder
  // chassis.pid_drive_set(-40_in, DRIVE_SPEED);
  // intake.move(127);
  // pros::delay(300);
  // intake.move(0);
  // chassis.pid_wait_until(-35_in);

  // Touch ladder
  // ladybrown.move(60);
  // pros::delay(500);
  // ladybrown.move(0);
  // ladybrown.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);

  color_sort.remove();

}

void red_stake(){

  chassis.pid_drive_set(10_in, DRIVE_SPEED);
  chassis.pid_wait_until(7_in);

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait_until(70_deg);

  chassis.pid_drive_set(8_in, DRIVE_SPEED);
  pros::delay(300);
  intake.move(127);
  chassis.pid_wait();

  pros::delay(300);
  intake.move(0);
}

void blue_stake(){

  chassis.pid_drive_set(10_in, DRIVE_SPEED);
  chassis.pid_wait_until(7_in);

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait_until(-70_deg);

  chassis.pid_drive_set(8_in, DRIVE_SPEED);
  pros::delay(300);
  intake.move(127);
  chassis.pid_wait();

  pros::delay(300);
  intake.move(0);
}


void EMERGENCY_AUTON(){

  // Drive to mogo
  extendMogo();
  pros::delay(300);

  chassis.pid_drive_set(35_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Clamp mogo
  retractMogo();
  pros::delay(300);

  // Back up to secure mogo
  chassis.pid_drive_set(-10_in, 127);
  chassis.pid_wait();

  chassis.pid_drive_set(5_in, 127);
  chassis.pid_wait();

  intake.move(127);
  pros::delay(3000);

}

void skills(){
  intake.move(127);
  pros::delay(1000);
  intake.move(0);

  chassis.pid_drive_set(-15_in, DRIVE_SPEED);
  chassis.pid_wait_until(-13_in);

  extendMogo();

  chassis.pid_turn_set(85_deg, TURN_SPEED);
  chassis.pid_wait_until(84_deg);

  chassis.pid_drive_set(25_in, DRIVE_SPEED);
  chassis.pid_wait_until(20_in);

  retractMogo();

  chassis.pid_turn_set(70_deg, TURN_SPEED);
  chassis.pid_wait_until(69_deg);

  chassis.pid_drive_set(55_in, DRIVE_SPEED);
  chassis.pid_wait();

  extendMogo();

  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait();
}

// Testing Autons
void color_sort_test(){

pros::Task color_sort(spitBLUE_task);

  intake.move(127);
  pros::delay(5000);
  intake.move(0);
  pros::delay(1000);

  intake.move(127);
  pros::delay(5000);
  intake.move(0);
  pros::delay(1000);

  intake.move(127);
  pros::delay(5000);
  intake.move(0);
  pros::delay(1000);

  color_sort.remove();
}

///
// Interference example
///
// void tug(int attempts) {
//   for (int i = 0; i < attempts - 1; i++) {
//     // Attempt to drive backward
//     printf("i - %i", i);
//     chassis.pid_drive_set(-12_in, 127);
//     chassis.pid_wait();

//     // If failsafed...
//     if (chassis.interfered) {
//       chassis.drive_sensor_reset();
//       chassis.pid_drive_set(-2_in, 20);
//       pros::delay(1000);
//     }
//     // If the robot successfully drove back, return
//     else {
//       return;
//     }
//   }
// }

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
// void interfered_example() {
//   chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
//   chassis.pid_wait();

//   if (chassis.interfered) {
//     tug(3);
//     return;
//   }

//   chassis.pid_turn_set(90_deg, TURN_SPEED);
//   chassis.pid_wait();
// }