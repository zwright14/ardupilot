/*
 * AP_IedStatus.h
 *
 *  Created on: Apr 17, 2020
 *      Author: zwrig_000
 */
#pragma once

#include <AP_Param/AP_Param.h>
#include <AP_AHRS/AP_AHRS.h>
#include <AP_HAL/AP_HAL.h>
#include <GCS_MAVLink/GCS.h>

#define IED_DEFAULT_PIN 54

class AP_IedStatus
{

public:
    AP_IedStatus();

    /* Do not allow copies */
    AP_IedStatus(const AP_IedStatus &other) = delete;
    AP_IedStatus &operator=(const AP_IedStatus&) = delete;

    // return true if wind vane is enabled
    bool enabled() const;

    // Initialize the Wind Vane object and prepare it for use
    void init();

    // update wind vane
    void update();

    // Return ied status
    float get_ied_status() const { return _ied_status; }

    // send mavlink wind message
    void send_ied_status(mavlink_channel_t chan);

    // parameter block
    static const struct AP_Param::GroupInfo var_info[];

private:

    // parameters
    AP_Float _ied_status;                            // the status of the ied
    AP_Int8 _ied_pin;                               // pin to be used for the ied status

    // put enabled vs disabled in one of these

   /* enum IedSystem {
        IED_ENABLED             = 0,
        IED_DISABLED            = 1
    };*/

    static AP_IedStatus *_singleton;
};

namespace AP {
    AP_IedStatus *iedstatus();
};
