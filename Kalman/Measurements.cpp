#include "Measurements.h"


Measurements::Measurements(std::vector<float> content) {
    if (size(content) != FIELD_LENGTH) {
        std::cout << "Incorrect size of fields!" << std::endl;
    }
    stamp = content[1];

    acc_x = content[2];
    acc_y = content[3];
    acc_z = content[4];

    yaw = content[5];
    pitch = content[6];
    roll = content[7];

    mag_x = content[8];
    mag_y = content[9];
    mag_z = content[10];

    temperature = content[11];

    water = (content[12] == 1.0) ? true : false;

    lat = content[13];
    lon = content[14];

};