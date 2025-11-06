## AURA GNaCC for USLI 2026
Guidance, Navigation, and Control computer for NASA USLI 2026 competition

### To Do list
- [X]  Collect Sensor reports 
- [x]  Log data 
- [x]  Flight State Machine
- [x]  Serial print for all error statements 
- [ ]  Sensor Fusion 
- [ ]  State Estimaiton -- Unscented Kalman filter
- [ ]  Frame rate manager
- [ ]  Sensor calibration at start up

## Log Manger
- [ ] Event logging
- [ ] check SD card handling
- [x] csv header 1st row
- [x] handle files already on SD
- [ ] check cyclic flash logger
- [ ] tune logging interval and max flash logs
- [ ] writing to sd after landing??
- [x] auto log stop after X time from landing

## Flight state machine 
- [ ] fix conditionals
- [ ] low pass fitler for sensor reports
- [ ] call log methods at events
