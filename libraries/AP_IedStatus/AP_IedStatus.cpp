/*
 * AP_IedStatus.cpp
 *
 *  Created on: Apr 17, 2020
 *      Author: zwrig_000
 */

#include "AP_IedStatus.h"
#include <GCS_MAVLink/GCS.h>

extern const AP_HAL::HAL& hal;

const AP_Param::GroupInfo AP_IedStatus::var_info[] = {

	// @Param: IED_PIN
	// @DisplayName: Ied Status digital pin.
	// @Description: Input pin for the IED status.
	// @Values: 11:Pixracer,13:Pixhawk ADC4,14:Pixhawk ADC3,15:Pixhawk ADC6/Pixhawk2 ADC,50:PixhawkAUX1,51:PixhawkAUX2,52:PixhawkAUX3,53:PixhawkAUX4,54:PixhawkAUX5,55:PixhawkAUX6,103:Pixhawk SBUS
	// @User: Standard
	AP_GROUPINFO("IED_PIN", 12, AP_IedStatus, _ied_pin,  IED_DEFAULT_PIN),

    AP_GROUPEND
};

// constructor
AP_IedStatus::AP_IedStatus()
{
    AP_Param::setup_object_defaults(this, var_info);
}

// return true if wind vane is enabled
bool AP_IedStatus::enabled() const
{
    return true;
}

// Initialize the Ied Status object and prepare it for use
void AP_IedStatus::init()
{
    /* don't construct twice
    if (_direction_driver != nullptr || _speed_driver != nullptr ) {
        return;
    }*/
    _ied_status = 0.0;

    // ensure we are in input mode
    hal.gpio->pinMode(IED_DEFAULT_PIN, HAL_GPIO_INPUT);

    // enable pullup
    hal.gpio->write(IED_DEFAULT_PIN, 1);
}

// update Ied Status, expected to be called at 20hz
void AP_IedStatus::update()
{
	_ied_status = (unsigned int)hal.gpio->read(IED_DEFAULT_PIN);

	if ((unsigned int)_ied_status == 1 ) {
		gcs().send_text(MAV_SEVERITY_NOTICE, "AN IED HAS BEEN DETECTED!");

	}
}

void AP_IedStatus::send_ied_status(const mavlink_channel_t chan)
{
    // send ied status information
    mavlink_msg_ied_status_send(chan, get_ied_status());
}

