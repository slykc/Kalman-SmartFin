#include "Measurements.h"


Measurements::Measurements(std::vector<float> content) {
if (size(content) != FIELD_LENGTH) {
    std::cout << "Incorrect size of fields!" << std::endl;
}

acc_x = content[0];
acc_y = content[1];
acc_z = content[2];

yaw = content[3];
pitch = content[4];
roll = content[5];

mag_x = content[6];
mag_y = content[7];
mag_z = content[8];

temperature = content[9];

stamp = content[10];
    };