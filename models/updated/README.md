# VCU-25 Firmware Model

## Working with this project

1. Open Vehicle_Controller_Model.prj
2. Run vehicle_specs.m
3. Open sm_car.slx
4. Run simulations


## Directories

**/resources/project**
- this stored everything related to the project
- this doesn't need to be touched
- all the project settings are encoded in files in this directory

**/work**
- the working directory
- this doesn't need to be touched
- this dir isn't tracked in the git repo

**Scripts_Data**
- this is where all the 



## Changing Vehicle Parameters

Vehicle Parameters are stored in the `Vehicle` structure in MATLAB

To change the parameters of the Vehicle, modify `Scripts_Data/Vehicle_data_dwishbone.m` and then run it.

DO NOT MODIFY `Vehicle` IN THE WORKSPACE. All changes could get reset when various events occur.

### Vehicle Parameters Test Data

This structure is created when ...
- not when the Simulink model is loaded
- not when a different map is selected

It is created when
- the `Scripts_Data/Vehicle_data_dwishbone.m` is run
- The startup file is run (this runs this ^^ file)

It is changed when ..
- a different map is selected



## Changing Map Parameters

