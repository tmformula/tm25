


% the number of signals emitted by speed sensor per each revolution of a wheel
SPEED_SENSOR_SIGNALS_PER_REV = 10;



TARGET_SLIP_RATIO = 0.10;  % when slip ratio is higher than this, it'll be brought down.


EFFECTIVE_ROLLING_RADIUS_OF_TIRES_M = 0.23323;  % should be 0.18 eventually but this value is getting overridden each run.

tire_radius = [EFFECTIVE_ROLLING_RADIUS_OF_TIRES_M, EFFECTIVE_ROLLING_RADIUS_OF_TIRES_M];
Vehicle.Chassis.TireA1.tire_radius = struct('Value', EFFECTIVE_ROLLING_RADIUS_OF_TIRES_M);
Vehicle.Chassis.TireA2.tire_radius = struct('Value', EFFECTIVE_ROLLING_RADIUS_OF_TIRES_M);