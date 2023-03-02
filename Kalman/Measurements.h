#pragma once

#include <iostream>
#include <vector>

#define FIELD_LENGTH 11

struct Measurements {
    // imu data
    float acc_x, acc_y, acc_z;
    float yaw, pitch, roll;

    // timestamp
    float stamp;

    // magnetometer readings
    float mag_x, mag_y, mag_z;

    // temperature
    float temperature;

    // constructor
    Measurements(std::vector<float> content); 
};