

%% vehicle parameters (move to other file)

EFFECTIVE_ROLLING_RADIUS_OF_TIRES_M = 0.23323;  % should be 0.18 eventually but this value is getting overridden each run.

tire_radius = [EFFECTIVE_ROLLING_RADIUS_OF_TIRES_M, EFFECTIVE_ROLLING_RADIUS_OF_TIRES_M];
Vehicle.Chassis.TireA1.tire_radius = struct('Value', EFFECTIVE_ROLLING_RADIUS_OF_TIRES_M);
Vehicle.Chassis.TireA2.tire_radius = struct('Value', EFFECTIVE_ROLLING_RADIUS_OF_TIRES_M);


MAXIMUM_TORQUE_FROM_MOTOR_Nm = 250;
MAXIMUM_NEGATIVE_TORQUE_FROM_MOTOR_Nm = -250;


% lowest can't be 0, highest can't be ... TODO!
APPS_1_UPPER_VOLTAGE = 4.0;
APPS_1_LOWER_VOLTAGE = 0.5;
APPS_2_UPPER_VOLTAGE = 4.5;
APPS_2_LOWER_VOLTAGE = 1.0;


%% sensors
% the number of signals emitted by speed sensor per each revolution of a wheel
SPEED_SENSOR_SIGNALS_PER_REV = 10;





%% battery pack
MAXIMUM_CONTINUOUS_CURRENT_DRAW_A = 200;
MAXIMUM_CONTINUOUS_CURRENT_CHARGE_A = 100;  % the amount of current that can be used to charge the battery pack



%% control system parameters
TARGET_SLIP_RATIO = 0.10;  % during launch control, this slip ratio will be targeted.


