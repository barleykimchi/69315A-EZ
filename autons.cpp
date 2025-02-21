#include "main.h"

// Speeds (Out of 127)
int DRIVE_SPEED = 110;
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;

// Color Sensor Values
const int red = 15;
const int blue = 210;

// Constants
void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(20.00, 0.0, 100.0);         // Fwd/rev constants
  chassis.pid_heading_constants_set(11.0, 0.0, 20.0);        // Holds the robot straight while going forward
  chassis.pid_turn_constants_set(3.0, 0.05, 20.0, 15.0);     // Turn in place constants
  chassis.pid_swing_constants_set(6.0, 0.0, 65.0);           // Swing constants

  // Exit conditions
  chassis.pid_turn_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_swing_exit_condition_set(90_ms, 3_deg, 250_ms, 7_deg, 500_ms, 500_ms);
  chassis.pid_drive_exit_condition_set(90_ms, 1_in, 250_ms, 3_in, 500_ms, 500_ms);

  chassis.pid_turn_chain_constant_set(3_deg);
  chassis.pid_swing_chain_constant_set(5_deg);
  chassis.pid_drive_chain_constant_set(3_in);

  // Slew constants
  chassis.slew_turn_constants_set(3_deg, 70);
  chassis.slew_drive_constants_set(3_in, 70);
  chassis.slew_swing_constants_set(3_in, 80);

  chassis.pid_angle_behavior_set(ez::shortest);  // Changes the default behavior to the shortest path 
}

void turnTest(){

  chassis.pid_swing_set(ez::RIGHT_SWING, -290_deg, 50, 5);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::RIGHT_SWING, -330_deg, 50, 5);
  chassis.pid_wait();
}

void blueSAWP(){ // Blue SAWP
  
  sorterEnabled = true;
  targetHue = red;
  jamEnabled = true;

  // Drive and turn to alliance stake
  chassis.pid_drive_set(-7_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-7_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Score preload
  intake.move_voltage(12000);
  pros::delay(500);
  intake.move_voltage(0);

  // Back up
  chassis.pid_drive_set(2_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Turn to mogo
  chassis.pid_turn_set(130_deg, TURN_SPEED);
  chassis.pid_wait();

  // Drive to and hold mogo
  extendMogo();
  chassis.pid_drive_set(-35_in, 100);
  chassis.pid_wait_until(-20_in);
  chassis.pid_speed_max_set(50);
  chassis.pid_wait_quick_chain();
  retractMogo();
  pros::delay(500);

  // Turn to 1-stack
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  // Drive to and collect first ring
  intake.move_voltage(12000);
  chassis.pid_drive_set(17_in, 40);
  chassis.pid_wait();
  
  // Turn to 4-stack
  chassis.pid_turn_set(-95_deg, TURN_SPEED);
  chassis.pid_wait_until(-90_deg);

  // Drive to and collect second ring
  chassis.pid_drive_set(12_in, 40);
  chassis.pid_wait();
  pros::delay(300);

  // Back up
  chassis.pid_drive_set(-5_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Turn to third ring
  chassis.pid_turn_set(-65_deg, TURN_SPEED);
  chassis.pid_wait_until(-60_deg);

  // Drive to and collect third ring
  chassis.pid_drive_set(14_in, 40);
  chassis.pid_wait();
  pros::delay(500);

  // Back up
  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Turn towards ladder
  chassis.pid_turn_set(-182_deg, TURN_SPEED);
  chassis.pid_wait_until(-180_deg);
  intake.move_voltage(0);

  // Drive to and touch ladder
  chassis.pid_drive_set(34_in, DRIVE_SPEED);
  chassis.pid_wait_until(20_in);
  chassis.pid_speed_max_set(30);
  chassis.pid_wait();

  ladybrown_Left.move_absolute(100, 127);
  ladybrown_Right.move_absolute(100, 127);

  pros::delay(500);

  sorterEnabled = false;
  jamEnabled = false;
}

void redSAWP(){ // Red SAWP

  sorterEnabled = true;
  targetHue = blue;
  jamEnabled = true;
  lbTaskEnabled = false;

  // Drive and turn to alliance stake
  chassis.pid_drive_set(-7_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-7_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Score preload
  intake.move_voltage(12000);
  pros::delay(500);
  intake.move_voltage(0);

  // Back up
  chassis.pid_drive_set(2_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Turn to mogo
  chassis.pid_turn_set(-130_deg, TURN_SPEED);
  chassis.pid_wait();

  // Drive to and hold mogo
  extendMogo();
  chassis.pid_drive_set(-35_in, 100);
  chassis.pid_wait_until(-20_in);
  chassis.pid_speed_max_set(50);
  chassis.pid_wait_quick_chain();
  retractMogo();
  pros::delay(500);

  // Turn to 1-stack
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  // Drive to and collect first ring
  intake.move_voltage(12000);
  chassis.pid_drive_set(17_in, 40);
  chassis.pid_wait();
  
  // Turn to 4-stack
  chassis.pid_turn_set(95_deg, TURN_SPEED);
  chassis.pid_wait_until(90_deg);

  // Drive to and collect second ring
  chassis.pid_drive_set(12_in, 40);
  chassis.pid_wait();
  pros::delay(300);

  // Back up
  chassis.pid_drive_set(-5_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Turn to third ring
  chassis.pid_turn_set(65_deg, TURN_SPEED);
  chassis.pid_wait_until(60_deg);

  // Drive to and collect third ring
  chassis.pid_drive_set(13_in, 40);
  chassis.pid_wait();
  pros::delay(500);

  // Back up
  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Turn towards ladder
  chassis.pid_turn_set(162_deg, TURN_SPEED);
  chassis.pid_wait_until(160_deg);
  intake.move_voltage(0);

  // Drive to and touch ladder
  chassis.pid_drive_set(34_in, DRIVE_SPEED);
  chassis.pid_wait_until(20_in);
  chassis.pid_speed_max_set(30);
  chassis.pid_wait();

  ladybrown_Left.move_absolute(100, 127);
  ladybrown_Right.move_absolute(100, 127);

  pros::delay(500);

  sorterEnabled = false;
  jamEnabled = false;
}

void skills(){

  DRIVE_SPEED = 80;

  // Score preload
  intake.move_voltage(12000);
  pros::delay(500);
  intake.move_voltage(0);

  // Drive to position for mogo
  chassis.pid_drive_set(7_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait();

  // Drive to and hold mogo
  extendMogo();
  chassis.pid_drive_set(-25_in, 60);
  chassis.pid_wait_until(-15_in);
  retractMogo();
  pros::delay(500);

  // Turn to 1st ring
  chassis.pid_turn_set(-10_deg, TURN_SPEED);
  chassis.pid_wait();

  // Drive to and collect 1st ring
  intake.move_voltage(12000);
  chassis.pid_drive_set(20_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Turn to 2nd ring
  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  // Drive to and collect 2nd ring
  chassis.pid_drive_set(34_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Turn to 3rd ring
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  // Drive to and collect 3rd ring
  chassis.pid_drive_set(25_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Turn to 4th ring
  chassis.pid_turn_set(180_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  
  // Drive to and collect 4th ring
  chassis.pid_drive_set(50_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Back up
  chassis.pid_drive_set(-15_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Turn to 5th & 6th rings
  chassis.pid_turn_set(-90_deg, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(5_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-180_deg, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Drive to and collect 5th and 6th rings
  chassis.pid_drive_set(30_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Score 5th & 6th rings
  pros::delay(1500);

  // Turn to corner
  chassis.pid_turn_set(295_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  // Drive to corner and deposit mogo
  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  extendMogo();

  // Drive towards center
  chassis.pid_drive_set(25_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Turn towards 2nd mogo
  chassis.pid_turn_set(-270_deg, TURN_SPEED);
  chassis.pid_wait();

  // Other side of field:
  // Drive to and hold 2nd mogo
  chassis.pid_drive_set(-55_in, 60);
  chassis.pid_wait_until(-50_in);
  retractMogo();
  pros::delay(500);

  // Back up
  chassis.pid_drive_set(1_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Turn to 1st ring
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  // Drive to and collect 1st ring
  chassis.pid_drive_set(20_in, DRIVE_SPEED);
  chassis.pid_wait();
  pros::delay(500);

   // Turn to 2nd ring
  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  // Drive to and collect 2nd ring
  chassis.pid_drive_set(36_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Turn to 3rd ring
  chassis.pid_turn_set(-360_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  // Drive to and collect 3rd ring
  chassis.pid_drive_set(25_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Turn to 4th ring
  chassis.pid_turn_set(180_deg, TURN_SPEED, ez::counterclockwise);
  chassis.pid_wait_quick_chain();
  
  // Drive to and collect 4th ring
  chassis.pid_drive_set(50_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Back up
  chassis.pid_drive_set(-15_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Turn to 5th and 6th rings
  chassis.pid_turn_set(90_deg, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(5_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(180_deg, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Drive to and collect 5th and 6th rings
  chassis.pid_drive_set(25_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Wait for rings to score
  pros::delay(1500);

  // Turn to corner
  chassis.pid_turn_set(60_deg, TURN_SPEED);                 // TEST TEST TEST!
  chassis.pid_wait_quick_chain();                             // DOWNLOAD DOWNLOAD DOWNLOAD!

  // Deposit mogo in corner
  chassis.pid_drive_set(-14_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  extendMogo();

  pros::delay(500);

  chassis.pid_drive_set(10_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Wait Until and Changing Max Speed
///
void wait_until_change_speed() {
  // pid_wait_until will wait until the robot gets to a desired position

  // When the robot gets to 6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(24_in, 30, true);
  chassis.pid_wait_until(6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // When the robot gets to -6 inches slowly, the robot will travel the remaining distance at full speed
  chassis.pid_drive_set(-24_in, 30, true);
  chassis.pid_wait_until(-6_in);
  chassis.pid_speed_max_set(DRIVE_SPEED);  // After driving 6 inches at 30 speed, the robot will go the remaining distance at DRIVE_SPEED
  chassis.pid_wait();
}

///
// Swing Example
///
void swing_example() {
  // The first parameter is ez::LEFT_SWING or ez::RIGHT_SWING
  // The second parameter is the target in degrees
  // The third parameter is the speed of the moving side of the drive
  // The fourth parameter is the speed of the still side of the drive, this allows for wider arcs

  chassis.pid_swing_set(ez::LEFT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, 45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::LEFT_SWING, 0_deg, SWING_SPEED, 45);
  chassis.pid_wait();
}

///
// Motion Chaining
///
void motion_chaining() {
  // Motion chaining is where motions all try to blend together instead of individual movements.
  // This works by exiting while the robot is still moving a little bit.
  // To use this, replace pid_wait with pid_wait_quick_chain.
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  // Your final motion should still be a normal pid_wait
  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

void maxPos_Red(){

  targetHue = blue;

  // Drive to and hold mogo
  chassis.pid_drive_set(-20_in, 80);
  chassis.pid_wait_until(-10_in);
  chassis.pid_speed_max_set(60);
  chassis.pid_wait_quick_chain();
  retractMogo();
  pros::delay(300);

  // Turn to rush rings
  chassis.pid_turn_set(158_deg, TURN_SPEED);
  chassis.pid_wait();
  intake.move_voltage(12000);
  // jamEnabled = true;

  // Doinker 1st ring
  chassis.pid_drive_set(18_in, 60);
  chassis.pid_wait();
  doinkerL.set(true);
  pros::delay(500);
  intake.move_voltage(0);

  // Back up
  chassis.pid_drive_set(-5_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(175_deg, TURN_SPEED);
  chassis.pid_wait();

  // Doinker 2nd ring
  chassis.pid_drive_set(12_in, 70);
  chassis.pid_wait();
  doinkerR.set(true);
  pros::delay(500);                             

  // Back up
  chassis.pid_drive_set(-30_in, DRIVE_SPEED);
  chassis.pid_wait();
  doinkerL.set(false);
  doinkerR.set(false);

  // Position for swing 
  intake.move_velocity(12000);
  chassis.pid_turn_set(130_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(3_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Swing and intake 2nd & 3rd rings
  chassis.pid_swing_set(ez::LEFT_SWING, 290_deg, 50, 5);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::LEFT_SWING, 330_deg, 50, 5);
  chassis.pid_wait();
  pros::delay(500);

  // Move to and intake 4th ring
  chassis.pid_turn_set(310_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(20_in, DRIVE_SPEED);
  chassis.pid_wait();
  pros::delay(500);
  
  // Move to corner & clear corner
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(55_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  intake.move_velocity(0);

  doinkerR.set(true);
  pros::delay(300);
  chassis.pid_drive_set(10_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(50_deg, TURN_SPEED);
  chassis.pid_wait();
  doinkerR.set(false);

  // Intake 5th ring
  // chassis.pid_turn_set(0_deg, TURN_SPEED, ez::counterclockwise);
  // chassis.pid_wait_quick_chain();
  // chassis.pid_drive_set(5_in, DRIVE_SPEED);
  // chassis.pid_wait();

  // chassis.pid_wait();
  // pros::delay(300);

  // // Back up
  // chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  // chassis.pid_wait_quick_chain();

  // // Clear corner
  // doinkerR.set(true);
  // pros::delay(300);
  // chassis.pid_drive_set(10_in, DRIVE_SPEED);
  // chassis.pid_wait_quick_chain();
  // chassis.pid_turn_set(50_deg, TURN_SPEED);
  // chassis.pid_wait();
  // doinkerR.set(false);

  pros::delay(500);
  intake.move_velocity(0);
  // jamEnabled = false;

}

// HELP HELP HELP HELP HELP HELP
void maxPos_Blue(){

  targetHue = red;

  // Drive to and hold mogo
  chassis.pid_drive_set(-20_in, 80);
  chassis.pid_wait_until(-10_in);
  chassis.pid_speed_max_set(60);
  chassis.pid_wait_quick_chain();
  retractMogo();
  pros::delay(300);

  // Turn to rush rings
  chassis.pid_turn_set(-160_deg, TURN_SPEED);
  chassis.pid_wait();
  intake.move_voltage(12000);
  // jamEnabled = true;

  // Doinker 1st ring
  chassis.pid_drive_set(20_in, 60);
  chassis.pid_wait();
  doinkerR.set(true);
  pros::delay(500);
  intake.move_voltage(0);

  // Back up
  chassis.pid_drive_set(-5_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_turn_set(-177_deg, TURN_SPEED);
  chassis.pid_wait();

  // Doinker 2nd ring
  chassis.pid_drive_set(12_in, 70);
  chassis.pid_wait();
  doinkerL.set(true);
  pros::delay(500);                             

  // Back up
  chassis.pid_drive_set(-35_in, DRIVE_SPEED);
  chassis.pid_wait();
  doinkerL.set(false);
  doinkerR.set(false);

  // Position for swing 
  intake.move_velocity(12000);
  chassis.pid_turn_set(-130_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(3_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Swing and intake 2nd & 3rd rings
  chassis.pid_swing_set(ez::RIGHT_SWING, -290_deg, 50, 5);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::RIGHT_SWING, -330_deg, 50, 5);
  chassis.pid_wait();
  pros::delay(500);

  // Move to and intake 4th ring
  chassis.pid_turn_set(-310_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(20_in, DRIVE_SPEED);
  chassis.pid_wait();
  pros::delay(500);
  
  // Move to corner
  chassis.pid_turn_set(-350_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(40_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  intake.move_velocity(0);

  // doinkerL.set(true);
  // pros::delay(300);
  // chassis.pid_drive_set(10_in, DRIVE_SPEED);
  // chassis.pid_wait_quick_chain();
  // chassis.pid_turn_set(-310_deg, TURN_SPEED);
  // chassis.pid_wait();
  // doinkerL.set(false);

  // // Intake 5th ring
  // chassis.pid_turn_set(0_deg, TURN_SPEED, ez::counterclockwise);
  // chassis.pid_wait_quick_chain();
  // chassis.pid_drive_set(5_in, DRIVE_SPEED);
  // chassis.pid_wait();

  // chassis.pid_wait();
  // pros::delay(300);

  // // Back up
  // chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  // chassis.pid_wait_quick_chain();

  // // Clear corner
  // doinkerR.set(true);
  // pros::delay(300);
  // chassis.pid_drive_set(10_in, DRIVE_SPEED);
  // chassis.pid_wait_quick_chain();
  // chassis.pid_turn_set(50_deg, TURN_SPEED);
  // chassis.pid_wait();
  // doinkerR.set(false);

  pros::delay(500);
  jamEnabled = false;
}

void maxNeg_Blue(){

  lbTaskEnabled = false;

  targetHue = red;
  // jamEnabled = true;

  // Score alliance stake
  ladybrown_Left.move_absolute(1200, 127);
  ladybrown_Right.move_absolute(1200, 127);
  pros::delay(600);
  lbTaskEnabled = true;

  // Drive to and clamp mogo
  chassis.pid_turn_set(-57_deg, TURN_SPEED, ez::counterclockwise);
  chassis.pid_wait();

  extendMogo();
  chassis.pid_drive_set(-35_in, DRIVE_SPEED);
  chassis.pid_wait_until(-15_in);
  chassis.pid_speed_max_set(60);
  chassis.pid_wait_quick_chain();
  retractMogo();
  pros::delay(300);

  // Drive to and collect 1st & 2nd rings
  chassis.pid_turn_set(150_deg, TURN_SPEED);
  chassis.pid_wait();

  intake.move_voltage(12000);
  chassis.pid_drive_set(10_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_swing_set(ez::LEFT_SWING, 200_deg, 60, 5);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(20_in, 70);
  chassis.pid_wait();
  pros::delay(300);

  chassis.pid_drive_set(-5_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Drive to and intake 3rd ring
  chassis.pid_turn_set(290_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();
  chassis.pid_drive_set(10_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Drive to and score on wall stake
  chassis.pid_turn_set(155_deg, TURN_SPEED, ez::counterclockwise);
  chassis.pid_wait();
  intake.move_velocity(0);
  // Drive to and collect 4th & 5th rings



  pros::delay(500);

}

void maxNeg_Red(){}
