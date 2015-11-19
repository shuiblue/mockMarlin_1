#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#define STRING_CONFIG_H_AUTHOR "(none, default config)" //Who made the changes.

#ifndef MOTHERBOARD
#define MOTHERBOARD 7
#endif



//===========================================================================
//=============================Thermal Settings  ============================
//===========================================================================

#define TEMP_SENSOR_0 -1

// PID settings:
// Comment the following line to disable PID and enable bang-bang.
#define PIDTEMP
#define PID_MAX 255 // limits current to nozzle; 255=full current

//===========================================================================
//=============================Mechanical Settings===========================
//===========================================================================


// The pullups are needed if you directly connect a mechanical endswitch between the signal and ground pins.
const bool X_ENDSTOPS_INVERTING = true; // set to true to invert the logic of the endstops. 

//#define DISABLE_MAX_ENDS
//automatic expansion
#if defined(ULTIMAKERCONTROLLER) || defined(REPRAP_DISCOUNT_SMART_CONTROLLER)
 #define ULTIPANEL
 #define NEWPANEL
#endif 

// Preheat Constants
#define PLA_PREHEAT_HOTEND_TEMP 180 
#define PLA_PREHEAT_HPB_TEMP 70
#define PLA_PREHEAT_FAN_SPEED 255		// Insert Value between 0 and 255

#define ABS_PREHEAT_HOTEND_TEMP 240
#define ABS_PREHEAT_HPB_TEMP 100
#define ABS_PREHEAT_FAN_SPEED 255		// Insert Value between 0 and 255



#endif //__CONFIGURATION_H














