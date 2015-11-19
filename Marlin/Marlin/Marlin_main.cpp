
//===========================================================================
//=============================private variables=============================
//===========================================================================

static float destination[NUM_AXIS] = {  0.0, 0.0, 0.0, 0.0};

void process_commands()
{
  
  if(code_seen('G'))
  {
    switch((int)code_value())
    {
    
    case 28: //G28 Home all Axis one at a time
     
      enable_endstops(true);
      
      #if Z_HOME_DIR > 0                      // If homing away from BED do Z first
      if((home_all_axis) || (code_seen(axis_codes[Z_AXIS]))) {
        HOMEAXIS(Z);
      }
      #endif
      
      #ifdef QUICK_HOME
      if((home_all_axis)||( code_seen(axis_codes[X_AXIS]) && code_seen(axis_codes[Y_AXIS])) )  //first diagonal move
      {
        current_position[X_AXIS] = 0;current_position[Y_AXIS] = 0;  

        plan_set_position(current_position[X_AXIS], current_position[Y_AXIS], current_position[Z_AXIS], current_position[E_AXIS]); 
        destination[X_AXIS] = 1.5 * X_MAX_LENGTH * X_HOME_DIR;destination[Y_AXIS] = 1.5 * Y_MAX_LENGTH * Y_HOME_DIR;  
        feedrate = homing_feedrate[X_AXIS]; 
        if(homing_feedrate[Y_AXIS]<feedrate)
          feedrate =homing_feedrate[Y_AXIS]; 
        plan_buffer_line(destination[X_AXIS], destination[Y_AXIS], destination[Z_AXIS], destination[E_AXIS], feedrate/60, active_extruder);
        st_synchronize();
    
        axis_is_at_home(X_AXIS);
        axis_is_at_home(Y_AXIS);
        plan_set_position(current_position[X_AXIS], current_position[Y_AXIS], current_position[Z_AXIS], current_position[E_AXIS]);
        destination[X_AXIS] = current_position[X_AXIS];
        destination[Y_AXIS] = current_position[Y_AXIS];
        plan_buffer_line(destination[X_AXIS], destination[Y_AXIS], destination[Z_AXIS], destination[E_AXIS], feedrate/60, active_extruder);
        feedrate = 0.0;
        st_synchronize();
        endstops_hit_on_purpose();
      }
      #endif
   
      #if Z_HOME_DIR < 0                      // If homing towards BED do Z last
      if((home_all_axis) || (code_seen(axis_codes[Z_AXIS]))) {
        HOMEAXIS(Z);
      }
      #endif

      plan_set_position(current_position[X_AXIS], current_position[Y_AXIS], current_position[Z_AXIS], current_position[E_AXIS]);
      
      #ifdef ENDSTOPS_ONLY_FOR_HOMING
        enable_endstops(false);
      #endif
  }
}
}
void prepare_move()
{
  clamp_to_software_endstops(destination);

  previous_millis_cmd = millis(); 
  // Do not use feedmultiply for E or Z only moves
  if( (current_position[X_AXIS] == destination [X_AXIS]) && (current_position[Y_AXIS] == destination [Y_AXIS])) {
      plan_buffer_line(destination[X_AXIS], destination[Y_AXIS], destination[Z_AXIS], destination[E_AXIS], feedrate/60, active_extruder);
  }
  else {
    plan_buffer_line(destination[X_AXIS], destination[Y_AXIS], destination[Z_AXIS], destination[E_AXIS], feedrate*feedmultiply/60/100.0, active_extruder);
  }
  for(int8_t i=0; i < NUM_AXIS; i++) {
    current_position[i] = destination[i];
  }
}

