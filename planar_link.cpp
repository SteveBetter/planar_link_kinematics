#include "planar_link.hpp"
#include <cmath>

#define pi 3.14159265

int deg2rad(double * const rad_ptr, const double deg)
{
    *rad_ptr = deg / 180.0 * pi;

    return 0;
}

int rad2deg(double * const deg_ptr, const double rad)
{
    *deg_ptr = rad / pi * 180.0;

    return 0;
}

int two_link_kin(double * const x_ptr, double * const y_ptr, \
                const double sita1, const double sita2, \
                const double L1, const double L2, const ENUM_UNIT unit)
{
    double sita1_rad, sita2_rad = 0.0;
    if ( unit == DEG) {
        deg2rad(&sita1_rad, sita1);
        deg2rad(&sita2_rad, sita2);
    } else {
        sita1_rad = sita1;
        sita2_rad = sita2;
    }

    *x_ptr = L1 * cos(sita1_rad) + L2 * cos(sita1_rad + sita2_rad);
    *y_ptr = L1 * sin(sita1_rad) + L2 * sin(sita1_rad + sita2_rad);

    return 0;
}

int two_link_ik(double * const sita1_ptr, double * const sita2_ptr, \
                double * const sita1_2_ptr, double * const sita2_2_ptr, \
                const double x, const double y, \
                const double L1, const double L2, const ENUM_UNIT unit)
{
    double sita1_rad, sita2_rad, sita1_2_rad, sita2_2_rad = 0.0;
    double epsilon = 1e-10;
    sita2_rad = acos(((x*x + y*y) - (L1*L1 + L2*L2)) / (2.0 * L1 * L2) - epsilon);

    double beta_rad = atan2(y, x);
    double phi_rad = acos((x*x + y*y + L1*L1 -  L2*L2) / ( 2.0 * L1 * sqrt(x*x + y*y) )  - epsilon);

    if ( unit == DEG ) {
        rad2deg(sita1_ptr, beta_rad - phi_rad);
        rad2deg(sita2_ptr, sita2_rad);
        rad2deg(sita1_2_ptr, beta_rad + phi_rad);
        rad2deg(sita2_2_ptr, -sita2_rad);
    } else {
        *sita1_ptr = beta_rad - phi_rad;
        *sita2_ptr = sita2_rad;
        *sita1_2_ptr = beta_rad + phi_rad;
        *sita2_2_ptr = -sita2_rad;
    }

    return 0;
}

int three_link_kin(double * const x_ptr, double * const y_ptr, double * const alpha_ptr, \
                    const double sita1, const double sita2, const double sita3, \
                    const double L1, const double L2, const double L3, const ENUM_UNIT unit)
{
    double sita1_rad, sita2_rad, sita3_rad, alpha_rad = 0.0;
    if ( unit == DEG) {
        deg2rad(&sita1_rad, sita1);
        deg2rad(&sita2_rad, sita2);
        deg2rad(&sita3_rad, sita3);
    } else {
        sita1_rad = sita1;
        sita2_rad = sita2;
        sita3_rad = sita3;
    }

    *x_ptr = L1 * cos(sita1_rad) + L2 * cos(sita1_rad + sita2_rad) + L3 * cos(sita1_rad + sita2_rad + sita3_rad) ;
    *y_ptr = L1 * sin(sita1_rad) + L2 * sin(sita1_rad + sita2_rad) + L3 * sin(sita1_rad + sita2_rad + sita3_rad) ;
    alpha_rad = sita1_rad + sita2_rad + sita3_rad;

    if (unit == DEG) {
        rad2deg(alpha_ptr, alpha_rad);
    } else {
        *alpha_ptr = alpha_rad;
    }

    return 0;
}

int three_link_ik(double *sita1_ptr, double *sita2_ptr, double *sita3_ptr, \
                double *sita1_2_ptr, double *sita2_2_ptr, double *sita3_2_ptr, \
                const double x, const double y, const double alpha, \
                const double L1, const double L2, const double L3, ENUM_UNIT unit)
{
    double alpha_rad = 0.0;
    if (unit == DEG) {
        deg2rad(&alpha_rad, alpha);
    } else {
        alpha_rad = alpha;
    }

    double x_tmp = x - L3 * cos(alpha_rad);
    double y_tmp = y - L3 * sin(alpha_rad);

    double sita1_rad, sita2_rad, sita1_2_rad, sita2_2_rad = 0.0;
    two_link_ik(&sita1_rad, &sita2_rad, \
                &sita1_2_rad, &sita2_2_rad, \
                x_tmp, y_tmp, \
                L1, L2, RAD);

    double sita3_rad, sita3_2_rad = 0.0;
    sita3_rad = alpha_rad - sita1_rad - sita2_rad;
    sita3_2_rad = alpha_rad - sita1_2_rad - sita2_2_rad;

    if (unit == DEG) {
        rad2deg(sita1_ptr, sita1_rad);
        rad2deg(sita2_ptr, sita2_rad);
        rad2deg(sita3_ptr, sita3_rad);
        rad2deg(sita1_2_ptr, sita1_2_rad);
        rad2deg(sita2_2_ptr, sita2_2_rad);
        rad2deg(sita3_2_ptr, sita3_2_rad);
    } else {
        *sita1_ptr = sita1_rad;
        *sita2_ptr = sita2_rad;
        *sita3_ptr = sita3_rad;
        *sita1_2_ptr = sita1_2_rad;
        *sita2_2_ptr = sita2_2_rad;
        *sita3_2_ptr = sita3_2_rad;
    }

    return 0;
}
