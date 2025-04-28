# Some solutions to errors encountered:
- SPI port requires shielded wires
- R1 and R2 should both be shorted in AS5047P-TS_EK_AB
- JP1 should be switched to 3v3
- both 5V and 3.3V pins on the encoder should be connected to 3.3V on the ODrive
- odrv0.axis0.encoder.config.use_index should be set to False (For absolute encoder, like AS5047P in this case, there is no need to use index)
  
# Some errors to be resolved:
- encoderError.index_not_found_yet
   - AXIS_STATE_ENCODER_INDEX_SEARCH
   - check axis.encoder.index_found
   - startup_encoder_index_search
