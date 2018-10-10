#ifndef _PLANAR_LINK_HPP_
#define _PLANAR_LINK_HPP_

typedef enum UNIT{
    RAD,
    DEG
} ENUM_UNIT;

int two_link_kin(double * const x_ptr, double * const y_ptr, \
                const double sita1, const double sita2, \
                const double L1, const double L2, const ENUM_UNIT unit = RAD);

int two_link_ik(double * const sita1_ptr, double * const sita2_ptr, \
                double * const sita1_2_ptr, double * const sita2_2_ptr, \
                const double x, const double y, \
                const double L1, const double L2, const ENUM_UNIT unit = RAD);

int three_link_kin(double * const x_ptr, double * const y_ptr, double * const alpha_ptr, \
                    const double sita1, const double sita2, const double sita3, \
                    const double L1, const double L2, const double L3, const ENUM_UNIT unit = RAD);

int three_link_ik(double *sita1_ptr, double *sita2_ptr, double *sita3_ptr, \
                double *sita1_2_ptr, double *sita2_2_ptr, double *sita3_2_ptr, \
                const double x, const double y, const double alpha, \
                const double L1, const double L2, const double L3, ENUM_UNIT unit = RAD);

#endif // _PLANAR_LINK_HPP_