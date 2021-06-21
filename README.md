# Vex-Robotics-Compeition-Tipping-Point-2021-2022
## Team Low Voltage's robot code, using PROS for V5
## Current To-do
- Implement Slew Rate, as a background task (RTOS)
- Add functions for ring intake, goal grabber and lift
- Add win point auto

## Make & Uploading the code
The main commands to be used are:
```prosv5 make``` and ```prosv5 upload```.

Additionally, to force a clean compile, use: ```prosv5 make all```

The *make* command is to compile the code, then it should be uploaded to the bot via brain-usb-connection.

The V5 can store more than 1 program, in order to specify where to upload add the following after *upload*, ```--slot[1-8]```

Further commands are found at [The PROS V5 Documentation](https://pros.cs.purdue.edu/v5/index.html)
