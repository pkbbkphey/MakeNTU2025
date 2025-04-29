# saving configuration:
```
odrv0.axis0.requested_state = AXIS_STATE_IDLE
odrv0.save_configuration()
odrv0.reboot()
```

# debug:
```
dump_errors(odrv0)
odrv0.clear_errors()
```

# 常用狀態：
```
odrv0.axis0.requested_state = AXIS_STATE_IDLE
odrv0.axis0.requested_state = AXIS_STATE_CLOSED_LOOP_CONTROL
```

# 控制方式：
### 位置：
```
odrv0.axis0.controller.config.control_mode = CONTROL_MODE_POSITION_CONTROL
odrv0.axis0.controller.input_pos = 0          // 指定位置，單位round
```

### 速度：
```
odrv0.axis0.controller.config.control_mode = CONTROL_MODE_VELOCITY_CONTROL
odrv0.axis0.controller.input_vel = 0          // 指定轉速，單位rps
```

### 啟動程序：
```
odrv0.axis0.config.startup_motor_calibration = False            // 重新接UVW線才要重新執行
  - odrv0.axis0.motor.config.pre_calibrated = True              // 常態設定(不要動)
  - odrv0.axis0.requested_state = AXIS_STATE_MOTOR_CALIBRATION  // 校正方式

odrv0.axis0.config.startup_encoder_index_search = False         // 絕對編碼器不須要index

odrv0.axis0.config.startup_encoder_offset_calibration = True    // 重新安裝編碼器才需要執行
  - odrv0.axis0.encoder.config.pre_calibrated = True            // 常態設定(不要動)
  - odrv0.axis0.requested_state = AXIS_STATE_ENCODER_OFFSET_CALIBRATION  // 校正方式

odrv0.axis0.config.startup_closed_loop_control = True
```

# axis0:
### 安全：
```
odrv0.axis0.motor.config.current_lim = 10
odrv0.axis0.controller.config.vel_limit = 2          // velocity limit, rps
odrv0.axis0.motor.config.calibration_current = 10    // 靜止時的電流
```

### 煞車電阻：
```
odrv0.config.brake_resistance = 2              // Ohm
odrv0.config.enable_brake_resistor = True      // 要接上煞車電阻！
```

### 馬達：
```
odrv0.axis0.motor.config.pole_pairs = 20                       // 40 magnets => pole pair = 20
odrv0.axis0.motor.config.torque_constant = 0.048647            // 8.27 / motor KV, motor KV = 170
odrv0.axis0.motor.config.motor_type = MOTOR_TYPE_HIGH_CURRENT
```

### 編碼器：
```
odrv0.axis0.encoder.config.abs_spi_cs_gpio_pin = 5            // 5 to 8 recommended
odrv0.axis0.encoder.config.mode = ENCODER_MODE_SPI_ABS_CUI    // or ENCODER_MODE_SPI_ABS_AMS
odrv0.axis0.encoder.config.cpr = 2**14
odrv0.axis0.encoder.config.use_index = False                  // For absolute encoder, like AS5047P in this case, there is no need to use index
odrv0.axis0.config.startup_encoder_index_search = True
```

### Tuning:
[Tuning method](https://docs.odriverobotics.com/v/0.5.6/control.html#control-doc)
#### Original:
```
odrv0.axis0.controller.config.pos_gain = 20.0
odrv0.axis0.controller.config.vel_gain = 0.1666666716337204
odrv0.axis0.controller.config.vel_integrator_gain = 0.3333333432674408
```
#### Tuned for 9020 BLDC motor @Vin = 15V:
```
odrv0.axis0.controller.config.pos_gain = 150
odrv0.axis0.controller.config.vel_gain = 0.24
odrv0.axis0.controller.config.vel_integrator_gain = 1    // 0.5 * bandwidth * vel_gain, bandwidth = 1/100ms
```

# 通訊(UART)
[UART](https://docs.odriverobotics.com/v/0.5.6/uart.html)
```
odrv0.config.uart_a_baudrate = 115200
odrv0.config.enable_uart_a = True
odrv0.config.uart0_protocol = STREAM_PROTOCOL_TYPE_ASCII_AND_STDOUT
```

# Some config to be explored:
```
//odrv0.axis0.motor.config.resistance_calib_max_voltage = 4
//odrv0.axis0.motor.config.requested_current_range = 25
//odrv0.axis0.motor.config.current_control_bandwidth = 100
```

