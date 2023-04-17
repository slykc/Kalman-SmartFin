#pragma once
#ifndef __MEASUREMENT_H_
#define __MEASUREMENT_H_
#include <iostream>
#include <vector>

#define FIELD_LENGTH 15

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

    // latitude and longtitude
    float lat, lon;

    // whether water
    bool water;

    // constructor
    Measurements(std::vector<float> content); 
};

#endif