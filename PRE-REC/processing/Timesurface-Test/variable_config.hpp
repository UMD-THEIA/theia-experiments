#ifndef VARIABLE_CONFIG_HPP
#define VARIABLE_CONFIG_HPP



using namespace std;

// timesurface parameters
inline constexpr float tau_in = 0.8;
inline constexpr float phi_in = 0.15;
inline constexpr int R_in = 15;
inline constexpr int L_in = 6;
inline constexpr int ROI = 2*R_in + 1;
// 'inline' prevents compiler multiple definition errors
// 'constexpr' allows use to define array dimensions



#endif