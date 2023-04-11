// #include <boost/log.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>

#include "Measurements.h"
#include "Fusion.h"

#define MEASURE_FREQ 25
#define KALMAN_FREQ 3.125


#define MEAN_GROUP_SIZE 8
#define Buffer std::queue<std::vector<Measurements>>
#define Entry std::vector<Measurements>
class DataManager {
public: 
    DataManager() {
        entryCtr = 0;
        elementCtr = 0;
    };

    void pushNewElement(Measurements element) {
        if (elementCtr == MEAN_GROUP_SIZE - 1) {
            entryCtr++;
            elementCtr = 0;

            Entry temp{element};
            buf.push(temp);
        }
        else {
            buf.back().push_back(element);
        }

        return;
    };

    Entry getEnrty() {
        Entry temp = buf.front();
        buf.pop();
        entryCtr = entryCtr - 1;
        return temp;
    };
    

private:
    Buffer buf;
    int entryCtr;
    int elementCtr;

};


// read measurement from 
std::vector<Measurements> readData(std::string f) {

    std::vector<Measurements> readings;

    std::fstream fin;

    // Open an existing file
    std::fstream file (f, std::ios::in);

    std::vector< std::vector<float>> content;
    std::vector<float> row;
    std::string line, word;

    if (file.is_open())
    {
        // get header line
        getline(file, line);
        // get contents
        while (getline(file, line)){
            row.clear();

            std::stringstream str(line);

            while (std::getline(str, word, ',')) {
                row.push_back(std::stof(word));
            }

            content.push_back(row);
        }
    }
    else {
        // err
        std::cout << "Could not open the file\n";
    }

    for (int i = 0; i < content.size(); i++)
    {
        Measurements temp(content[i]);
        readings.push_back(temp);
    }

    return readings;
}


int main(int argc, char** argv) {

    // read measurements from cvs, file path as an os arguement
    std::string filename = "2023-02-23 Test 1 Cleaned X";
    std::vector<Measurements> readings = readData(filename);
    

    // Kalman Filter
    Fusion kalmanFilter;
    kalmanFilter.begin(MEASURE_FREQ);
    std::vector<float> x_acc_clean;
    std::vector<float> x_acc_dirty;
    float* acc_x_filtered;
    acc_x_filtered = new float;
    float* acc_y_filtered;
    acc_y_filtered = new float;
    float* acc_z_filtered;
    acc_z_filtered = new float;
    for (std::vector<Measurements>::iterator iter = readings.begin();
         iter != readings.end(); iter++) {
            kalmanFilter.update(iter->yaw, iter->pitch, iter->roll, 
                                iter->acc_x, iter->acc_y, iter->acc_z,
                                0, 0, 0);
            
            kalmanFilter.getLinearAcceleration(acc_x_filtered, acc_y_filtered, acc_z_filtered);
            x_acc_clean.push_back(*acc_x_filtered);
            x_acc_dirty.push_back(iter->acc_x);
    }


    std::fstream out_clean;
    out_clean.open("clean_acc_x.txt", std::ios_base::out);

    for (int i = 0; i < x_acc_clean.size(); i++)
    {
        out_clean << x_acc_clean[i] << std::endl;
    }

    out_clean.close();

    std::fstream out_dirty;
    out_dirty.open("dirty_acc_x.txt", std::ios_base::out);

    for (int i = 0; i < x_acc_dirty.size(); i++)
    {
        out_dirty << x_acc_dirty[i] << std::endl;
    }

    out_clean.close();

    return 0;
}

