#include "main.h"

// Motor Groups
pros::MotorGroup intake ({19, -20}, pros::v5::MotorGears::blue);       
pros::Motor ladybrown_Left (17, pros::v5::MotorGears::green);
pros::Motor ladybrown_Right (18, pros::v5::MotorGears::green);

// Pneumatics
pros::adi::Pneumatics mogoL ('A', false);
pros::adi::Pneumatics mogoR ('B', false);
pros::adi::Pneumatics colorSort ('C', false);
ez::Piston doinker('D', false); // Used EZ Template piston commands
ez::Piston hang('H', false);

// Sensors
pros::v5::Imu imu(16);
pros::v5::Optical optical(6);

void setIntake(int intakePower){                                                   
      intake.move(intakePower);
}

// Chassis constructor
ez::Drive chassis(
    // Drive motors, the first motor is used for sensing!
    {-9, -10},    // Left Chassis Ports (negative port will reverse it!)
    {8, 7},       // Right Chassis Ports (negative port will reverse it!)
    16,           // IMU Port
    3.25,         // Wheel Diameter
    600);         // Wheel RPM

// All other competition modes are blocked by initialize; it is recommended
// to keep execution time for this mode under a few seconds.
void initialize() {

  pros::delay(500);  // Stop the user from doing anything while legacy ports configure

  // Configure your chassis controls
  chassis.opcontrol_curve_buttons_toggle(true);  // Enables modifying the controller curve with buttons on the joysticks
  chassis.opcontrol_drive_activebrake_set(2);    // Sets the active brake kP. We recommend ~2.  0 will disable.
  default_constants();                           // Set the drive to constants from autons.cpp

  ladybrown_Left.tare_position();
  ladybrown_Right.tare_position();

  // These are already defaulted to these buttons, but you can change the left/right curve buttons here!
  // chassis.opcontrol_curve_buttons_left_set(pros::E_CONTROLLER_DIGITAL_LEFT, pros::E_CONTROLLER_DIGITAL_RIGHT);
  // chassis.opcontrol_curve_buttons_right_set(pros::E_CONTROLLER_DIGITAL_Y, pros::E_CONTROLLER_DIGITAL_A);

  // Autonomous Selector using LLEMU
  ez::as::auton_selector.autons_add({
    Auton("AWP RED", newAWP_RED),
    Auton("AWP BLUE", newAWP_BLUE), 
    Auton("Blue Right Auton NO WALL STAKE", br_NOWS),
    Auton("Blue Left Auton NO WALL STAKE", bl_NOWS),
    Auton("Red Right Auton NO WALL STAKE", rr_NOWS),
    Auton("Red Left Auton NO WALL STAKE", rl_NOWS),
    Auton("Skills", skills),
    Auton("EMERGENCY AUTON", EMERGENCY_AUTON),
    Auton("REd stake", red_stake),
    Auton("blue stake", blue_stake)
  });

  // Initialize chassis and auton selector
  imu.reset();
  chassis.initialize();
  ez::as::initialize();
  master.rumble(".");
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {

  // put in while true loop?
  mogoR.extend();
  mogoL.extend();
}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
  // . . .
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
  
  chassis.pid_targets_reset();                   // Resets PID targets to 0
  chassis.drive_imu_reset();                     // Reset IMU to 0
  chassis.drive_sensor_reset();                  // Reset drive sensors to 0
  chassis.drive_brake_set(MOTOR_BRAKE_HOLD);     // Set motors to hold.  This helps autonomous consistency

  ez::as::auton_selector.selected_auton_call();  // Calls selected auton from autonomous selector
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */

void opcontrol() {
  // This is preference to what you like to drive on
  pros::motor_brake_mode_e_t driver_preference_brake = MOTOR_BRAKE_HOLD;
  chassis.drive_brake_set(driver_preference_brake);

  while (true) {
    // PID Tuner
    // After you find values that you're happy with, you'll have to set them in auton.cpp
    if (!pros::competition::is_connected()) {
      // Enable / Disable PID Tuner
      //  When enabled:
      //  * use A and Y to increment / decrement the constants
      //  * use the arrow keys to navigate the constants
      if (master.get_digital(DIGITAL_X))
        chassis.pid_tuner_toggle();

      // Trigger the selected autonomous routine
      if (master.get_digital(DIGITAL_B)) {
        autonomous();
        pros::delay(1000);
        chassis.drive_brake_set(driver_preference_brake);
      }

      chassis.pid_tuner_iterate();  // Allow PID Tuner to iterate
    }

    chassis.opcontrol_arcade_standard(ez::SPLIT);   // Standard split arcade

    // Set up OP controls for INTAKE                                                                // COMMENT BACK IN
    if (master.get_digital(DIGITAL_R1)){
        setIntake(115);
    } else if (master.get_digital(DIGITAL_R2)){
        setIntake(-115);
    } else {
        setIntake(0);
    }

    // Set up OP controls for MOGO MECH
    if (master.get_digital(DIGITAL_L1)){
        mogoL.extend();
        mogoR.extend();
    } else if (master.get_digital(DIGITAL_L2)){
        mogoL.retract();
        mogoR.retract();
    }

    // // Set up OP controls for LADYBROWN
    if (master.get_digital(DIGITAL_DOWN)){
      ladybrown_Left.move(-80);
      ladybrown_Right.move(80);
    } else if (master.get_digital(DIGITAL_UP)){
      if(ladybrown_Left.get_position() >= 1550){
        ladybrown_Left.move(0);
        ladybrown_Right.move(0);
        ladybrown_Left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        ladybrown_Right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
      } else {
          ladybrown_Left.move(80);
          ladybrown_Right.move(-80);
      }
    } else if (master.get_digital(DIGITAL_RIGHT)){
            ladybrown_Right.move_absolute(-350, 127);
            ladybrown_Left.move_absolute(350, 127);
    } else {
      ladybrown_Left.move(0);
      ladybrown_Right.move(0);
      ladybrown_Left.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
      ladybrown_Right.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
    }

    // Set up OP controls for DOINKER
    doinker.button_toggle(master.get_digital(DIGITAL_A));
    pros::delay(10);

    // Set up OP controls for HANG
    hang.button_toggle(master.get_digital(DIGITAL_X));
    pros::delay(10);

    // Set up OP controls for COLOR SORT
    if(master.get_digital(DIGITAL_Y)){
      colorSort.extend();
      pros::delay(500);
      colorSort.retract();
    }

    pros::delay(ez::util::DELAY_TIME);  // This is used for timer calculations!  Keep this ez::util::DELAY_TIME
  }
}