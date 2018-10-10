#include "planar_link.hpp"
#include <cmath>
#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{
    double sita1, sita2, sita3 = 0.0;
    double x, y, alpha = 0.0;
    double sita1_tmp, sita2_tmp, sita3_tmp = 0.0;
    double sita1_2_tmp, sita2_2_tmp, sita3_2_tmp = 0.0;
    const double L1 = 100.0;
    const double L2 = 80.0;
    const double L3 = 50.0;

    const double epsilon = 0.001;

    fstream fs("./test.txt", ios::out);

    for (sita1 = 0.0; sita1 < 90.0; sita1++) {
        for (sita2 = 0.0; sita2 > -180.0; sita2--) {
            two_link_kin(&x, &y, \
                        sita1, sita2, \
                        L1, L2, DEG);
            two_link_ik(&sita1_tmp, &sita2_tmp, \
                        &sita1_2_tmp, &sita2_2_tmp, \
                        x, y, \
                        L1, L2, DEG);

            // cout << "sita1, sita2: "  << sita1 << ", " << sita2 << "; " \
            //         << sita1_tmp << ", " << sita2_tmp  << "; " \
            //         << sita1_2_tmp << ", " << sita2_2_tmp << "; " \
            //         << x << ", " << y << "; " << endl;
            fs << "sita1, sita2: "  << sita1 << ", " << sita2 << "; " \
            << sita1_tmp << ", " << sita2_tmp  << "; " \
            << sita1_2_tmp << ", " << sita2_2_tmp << "; " \
            << x << ", " << y << "; " << endl;

            if (abs(sita1_2_tmp - sita1) >= epsilon || abs(sita2_2_tmp - sita2) >= epsilon ) {
                cout << sita1 << ", " << sita2 << ", " << sita3 << endl;
            }

            if (isnan(sita1_tmp) || isnan(sita2_tmp) || isnan(sita1_2_tmp) || isnan(sita2_2_tmp) ) {
                cout << sita1 << ", " << sita2 << endl;
                return -1;
            }
        }
    }


    for (sita1 = 0.0; sita1 < 90.0; sita1++) {
        for (sita2 = 0.0; sita2 > -180.0; sita2--) {
            for (sita3 = 0.0; sita3 > -180.0; sita3--) {
                three_link_kin(&x, &y, &alpha, \
                                sita1, sita2, sita3, \
                                L1, L2, L3, DEG);
                three_link_ik(&sita1_tmp, &sita2_tmp, &sita3_tmp, \
                            &sita1_2_tmp, &sita2_2_tmp, &sita3_2_tmp, \
                            x, y, alpha, \
                            L1, L2, L3, DEG);

                // cout << "sita1, sita2, sita3: "  << sita1 << ", " << sita2 << ", " << sita3 << "; " \
                //         << sita1_tmp << ", " << sita2_tmp << ", " << sita3_tmp << "; " \
                //         << sita1_2_tmp << ", " << sita2_2_tmp << ", " << sita3_2_tmp << "; " \
                //         << x << ", " << y << ", " << alpha << "; " << endl;
                fs << "sita1, sita2, sita3: "  << sita1 << ", " << sita2 << ", " << sita3 << "; " \
                        << sita1_tmp << ", " << sita2_tmp << ", " << sita3_tmp << "; " \
                        << sita1_2_tmp << ", " << sita2_2_tmp << ", " << sita3_2_tmp << "; " \
                        << x << ", " << y << ", " << alpha << "; " << endl;
                if (abs(sita1_2_tmp - sita1) >= epsilon || abs(sita2_2_tmp - sita2) >= epsilon || abs(sita3_2_tmp - sita3) >= epsilon ) {
                    cout << sita1 << ", " << sita2 << ", " << sita3 << endl;
                }

                if (isnan(sita1_tmp) || isnan(sita2_tmp) || isnan(sita3_tmp) || isnan(sita1_2_tmp) || isnan(sita2_2_tmp) || isnan(sita3_2_tmp)) {
                    cout << sita1 << ", " << sita2 << ", " << sita3 << endl;
                    return -1;
                }                

            }
        }
    }

    fs.close();
    return 0;
}