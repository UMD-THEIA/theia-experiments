#ifndef STARFIELDPROCESSORVARIABLES_HPP
#define STARFIELDPROCESSORVARIABLES_HPP



#include <iostream>
#include <cmath>
#include "../variable_config.hpp"

using namespace std;


class StarfieldProcessorVariables {
public:

    // timesurface parameters
    float tau;
    float phi;
    int R;
    int L;

    // timesurface matrices
    float t[1280][720] = {0};
    float s[ROI][ROI] = {0};

    // internal processing utilities
    int ROI_sum = 0;
    float ROI_elements[ROI][ROI] = {0};
    float x_ind[ROI] = {0};
    float y_ind[ROI] = {0};
    int current_x_ind = 0;
    int current_y_ind = 0;


    StarfieldProcessorVariables() {

        tau = tau_in;
        phi = phi_in;
        R = R_in;
        L = L_in;

    };

    void initSPV() {

        for (int i = 0; i < 1280; i++)
            for (int j = 0; j < 720; j++)
                t[i][j] = -std::numeric_limits<double>::infinity();

        for (int i = 0; i < ROI; i++)
            for (int j = 0; j < ROI; j++)
                s[i][j] = -std::numeric_limits<double>::infinity();

        for (int i = 0; i < ROI; i++)
            for (int j = 0; j < ROI; j++)
                ROI_elements[i][j] = -std::numeric_limits<double>::infinity();

    };

    void set_ROI(float xi, float yi) {

        int x_min = xi - R;
        int x_max = xi + R;
        int y_min = yi - R;
        int y_max = yi + R;

        for (int i = 0; i < ROI; i++) {

            x_ind[i] = x_min + i;
            y_ind[i] = y_min + i;

        }

        for (int i = 0; i < ROI; i++)
            for (int j = 0; j < ROI; j++) {

                current_x_ind = x_ind[i];
                current_y_ind = y_ind[j];

                if (current_x_ind >= 0 && current_x_ind < 1280 && current_y_ind >= 0 && current_x_ind < 720) {

                    ROI_elements[i][j] = t[current_x_ind][current_y_ind];

                };
            }

    };

    void update_ROI(float eventTime) {

        // try and vectorize this if possible (and if faster)
        // there are also probably a ton of duplicate calculations going on here from events with the same timestamp?
        for (int i = 0; i < ROI; i++)
            for (int j = 0; j < ROI; j++)
                s[i][j] = exp( (ROI_elements[i][j] - eventTime) / tau );

    };

    bool surface_activation_test(){

        for (int i = 0; i < ROI; i++)
            for (int j = 0; j < ROI; j++)
                if (s[i][j] > phi)
                    ROI_sum += 1;
        
        if (ROI_sum > L)
            return true;
        else
            return false;

    };
    
    void reset_dynamic_variables() {

        ROI_sum = 0;

        for (int i = 0; i < ROI; i++)
            for (int j = 0; j < ROI; j++)
                s[i][j] = -std::numeric_limits<double>::infinity();

        for (int i = 0; i < ROI; i++)
            for (int j = 0; j < ROI; j++)
                ROI_elements[i][j] = -std::numeric_limits<double>::infinity();

    };

};



#endif