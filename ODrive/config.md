# axis0:
### 安全：
odrv0.axis0.motor.config.current_lim = 10
odrv0.axis0.controller.config.vel_limit = 2
odrv0.axis0.motor.config.calibration_current = 0.1    // 靜止時的電流

### 煞車電阻：
odrv0.config.brake_resistance = 2              // Ohm
odrv0.config.enable_brake_resistor = True      // 要接上煞車電阻！

### 馬達：
odrv0.axis0.motor.config.pole_pairs = 20                       // 40 magnets => pole pair = 20
odrv0.axis0.motor.config.torque_constant = 0.048647            // 8.27 / motor KV, motor KV = 170
odrv0.axis0.motor.config.motor_type = MOTOR_TYPE_HIGH_CURRENT

### 編碼器：


//odrv0.axis0.motor.config.resistance_calib_max_voltage = 4
//odrv0.axis0.motor.config.requested_current_range = 25
//odrv0.axis0.motor.config.current_control_bandwidth = 100


