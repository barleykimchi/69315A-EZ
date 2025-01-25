#include "main.h"

/////
// For installation, upgrading, documentations, and tutorials, check out our website!
// https://ez-robotics.github.io/EZ-Template/
/////

// These are out of 127
int DRIVE_SPEED = 70;
const int TURN_SPEED = 90;
const int SWING_SPEED = 110;

// Constants
void default_constants() {
  // P, I, D, and Start I
  chassis.pid_drive_constants_set(20.0, 0.0, 100.0);         // Fwd/rev constants
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
  chassis.pid_turn_set(180, TURN_SPEED, ez::clockwise);
  chassis.pid_wait();
}

void blueSAWP(){ // Blue SAWP
  DRIVE_SPEED = 110; 

  // Drive and turn to alliance stake
  chassis.pid_drive_set(-7_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(-90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-7_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Score preload
  intake.move(127);
  pros::delay(500);
  intake.move(0);

  // Back up
  chassis.pid_drive_set(2_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Turn to mogo
  chassis.pid_turn_set(130_deg, TURN_SPEED);
  chassis.pid_wait();

  // Drive to and hold mogo
  extendMogo();
  chassis.pid_drive_set(-38_in, DRIVE_SPEED);
  chassis.pid_wait_until(-13_in);
  chassis.pid_speed_max_set(60);
  chassis.pid_wait();
  pros::delay(200);
  retractMogo();

  // Turn to 1-stack
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  // Drive to and collect first ring
  intake.move(127);
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
  intake.move(0);

  // Drive to and touch ladder
  chassis.pid_drive_set(34_in, DRIVE_SPEED);
  chassis.pid_wait_until(20_in);
  chassis.pid_speed_max_set(30);
  chassis.pid_wait();
}

void redSAWP(){ // Red SAWP
  DRIVE_SPEED = 110; 

  // Drive and turn to alliance stake
  chassis.pid_drive_set(-7_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  chassis.pid_drive_set(-7_in, DRIVE_SPEED);
  chassis.pid_wait();

  // Score preload
  intake.move(127);
  pros::delay(500);
  intake.move(0);

  // Back up
  chassis.pid_drive_set(2_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Turn to mogo
  chassis.pid_turn_set(-130_deg, TURN_SPEED);
  chassis.pid_wait();

  // Drive to and hold mogo
  extendMogo();
  chassis.pid_drive_set(-38_in, DRIVE_SPEED);
  chassis.pid_wait_until(-13_in);
  chassis.pid_speed_max_set(60);
  chassis.pid_wait();
  pros::delay(200);
  retractMogo();

  // Turn to 1-stack
  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait_quick_chain();

  // Drive to and collect first ring
  intake.move(127);
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
  chassis.pid_drive_set(14_in, 40);
  chassis.pid_wait();
  pros::delay(500);

  // Back up
  chassis.pid_drive_set(-10_in, DRIVE_SPEED);
  chassis.pid_wait_quick_chain();

  // Turn towards ladder
  chassis.pid_turn_set(162_deg, TURN_SPEED);
  chassis.pid_wait_until(160_deg);
  intake.move(0);

  // Drive to and touch ladder
  chassis.pid_drive_set(34_in, DRIVE_SPEED);
  chassis.pid_wait_until(20_in);
  chassis.pid_speed_max_set(30);
  chassis.pid_wait();

  ladybrown_Left.move(-127);
  ladybrown_Right.move(127);

  pros::delay(500);

  ladybrown_Left.move(0);
  ladybrown_Right.move(0);
}

void skills(){

  // Score preload
  intake.move(127);
  pros::delay(500);
  intake.move(0);

  // Drive to position for mogo
  chassis.pid_drive_set(6_in, DRIVE_SPEED);
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
  intake.move(127);
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
// Drive Example
///
void drive_example() {
  // The first parameter is target inches
  // The second parameter is max speed the robot will drive at
  // The third parameter is a boolean (true or false) for enabling/disabling a slew at the start of drive motions
  // for slew, only enable it when the drive distance is greater than the slew distance + a few inches

  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-12_in, DRIVE_SPEED);
  chassis.pid_wait();
}

///
// Turn Example
///
void turn_example() {
  // The first parameter is the target in degrees
  // The second parameter is max speed the robot will drive at

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();
}

///
// Combining Turn + Drive
///
void drive_and_turn() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(-45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
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

///
// Auto that tests everything
///
void combining_movements() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  chassis.pid_turn_set(45_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_swing_set(ez::RIGHT_SWING, -45_deg, SWING_SPEED, 45);
  chassis.pid_wait();

  chassis.pid_turn_set(0_deg, TURN_SPEED);
  chassis.pid_wait();

  chassis.pid_drive_set(-24_in, DRIVE_SPEED, true);
  chassis.pid_wait();
}

///
// Interference example
///
void tug(int attempts) {
  for (int i = 0; i < attempts - 1; i++) {
    // Attempt to drive backward
    printf("i - %i", i);
    chassis.pid_drive_set(-12_in, 127);
    chassis.pid_wait();

    // If failsafed...
    if (chassis.interfered) {
      chassis.drive_sensor_reset();
      chassis.pid_drive_set(-2_in, 20);
      pros::delay(1000);
    }
    // If the robot successfully drove back, return
    else {
      return;
    }
  }
}

// If there is no interference, the robot will drive forward and turn 90 degrees.
// If interfered, the robot will drive forward and then attempt to drive backward.
void interfered_example() {
  chassis.pid_drive_set(24_in, DRIVE_SPEED, true);
  chassis.pid_wait();

  if (chassis.interfered) {
    tug(3);
    return;
  }

  chassis.pid_turn_set(90_deg, TURN_SPEED);
  chassis.pid_wait();
}
