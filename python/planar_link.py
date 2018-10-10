"""
Three-Link Mechanism:

## kinimatics:
x, y, alpha = three_link_kin(sita1, sita2, sita3, L1, L2, L3, unit = "rad")
or
x, y, alpha = three_link_kin(sita1, sita2, sita3, L1, L2, L3, unit = "deg")

## inverse kinematics:
(sita1, sita2, sita3), (sita1_2, sita2_2, sita3_2) = three_link_ik(x, y, alpha, L1, L2, L3, unit = "rad")
or
(sita1, sita2, sita3), (sita1_2, sita2_2, sita3_2) = three_link_ik(x, y, alpha, L1, L2, L3, unit = "deg")

sita2 is positive, and sita2_2 is negative.

"""

import numpy as np

def two_link_kin(sita1, sita2, L1, L2, unit = "rad"):
    if unit == "deg":
        sita1 = np.deg2rad(sita1)
        sita2 = np.deg2rad(sita2)

    x = L1 * np.cos(sita1) + L2 * np.cos(sita1 + sita2)
    y = L1 * np.sin(sita1) + L2 * np.sin(sita1 + sita2)

    return x, y

def two_link_ik(x, y, L1, L2, unit = "rad"):
    epsilon = 1e-10
    sita2 = np.arccos( ((np.square(x) + np.square(y)) - (np.square(L1) + np.square(L2))) / (2.0 * L1 * L2) - epsilon)
    
    beta = np.arctan2(y, x)
    phi = np.arccos( (np.square(x) + np.square(y) + np.square(L1) - np.square(L2)) / (2.0 * L1 * np.sqrt(np.square(x) + np.square(y))) - epsilon)

    if unit == "deg":
        return (np.rad2deg(beta - phi), np.rad2deg(sita2)), (np.rad2deg(beta + phi), np.rad2deg(-sita2))

    return (beta - phi, sita2), (beta + phi, -sita2)

def three_link_kin(sita1, sita2, sita3, L1, L2, L3, unit = "rad"):
    if unit == "deg":
        sita1 = np.deg2rad(sita1)
        sita2 = np.deg2rad(sita2)
        sita3 = np.deg2rad(sita3)

    x = L1 * np.cos(sita1) + L2 * np.cos(sita1 + sita2) + L3 * np.cos(sita1 + sita2 + sita3)
    y = L1 * np.sin(sita1) + L2 * np.sin(sita1 + sita2) + L3 * np.sin(sita1 + sita2 + sita3)
    alpha = sita1 + sita2 + sita3

    if unit == "deg":
        return x, y, np.rad2deg(alpha)

    return x, y,alpha

def three_link_ik(x, y, alpha, L1, L2, L3, unit = "rad"):
    if unit == "deg":
        alpha = np.deg2rad(alpha)

    x_tmp = x - L3 * np.cos(alpha)
    y_tmp = y - L3 * np.sin(alpha)

    (sita1, sita2), (sita1_2, sita2_2) = two_link_ik(x_tmp, y_tmp, L1, L2, unit = "rad")

    sita3 = alpha - sita1 - sita2
    sita3_2 = alpha - sita1_2 - sita2_2

    if unit == "deg":
        return (np.rad2deg(sita1), np.rad2deg(sita2), np.rad2deg(sita3)), (np.rad2deg(sita1_2), np.rad2deg(sita2_2), np.rad2deg(sita3_2))

    return (sita1, sita2, sita3), (sita1_2, sita2_2, sita3_2)

# L1 = 100.0
# L2 = 50.0
# L3 = 30.0

# def two_link_kin_test():
#     epsilon = 1e-3

#     for sita1 in range(91):
#         for sita2 in range(91):
#             x, y = two_link_kin(sita1, sita2, L1, L2, unit = "deg")
#             #print(sita1, sita2, x, y)
#             (sita1_tmp, sita2_tmp), (sita1_tmp2, sita2_tmp2) = two_link_ik(x, y, L1, L2, unit = "deg")

#             if np.abs(sita1 - sita1_tmp) > epsilon or np.abs(sita2 - sita2_tmp) > epsilon:
#                 print("sita1, sita2: " + str(sita1) + ", " + str(sita2) + "; " + str(sita1_tmp) + ", " + str(sita2_tmp))

# # sita1 = 7.0
# # sita2 = 0.0
# # x, y = two_link_kin(sita1, sita2, L1, L2, unit = "deg")
# # print(((np.square(x) + np.square(y)) - (np.square(L1) + np.square(L2))) / (2.0 * L1 * L2))
# # print((np.square(x) + np.square(y) + np.square(L1) - np.square(L2)) / (2.0 * L1 * np.sqrt(np.square(x) + np.square(y))))

# #two_link_kin_test()

# def three_link_kin_test():
#     epsilon = 1e-3

#     for sita1 in range(91):
#         for sita2 in range(91):
#             for sita3 in range(91):

#                 x, y, alpha = three_link_kin(sita1, sita2, sita3, L1, L2, L3, unit = "deg")
#                 #print(sita1, sita2, x, y)
#                 (sita1_tmp, sita2_tmp, sita3_tmp), (sita1_2_tmp, sita2_2_tmp, sita3_2_tmp) = three_link_ik(x, y, alpha, L1, L2, L3, unit = "deg")

#                 if np.abs(sita1 - sita1_tmp) > epsilon or np.abs(sita2 - sita2_tmp) > epsilon or np.abs(sita3 - sita3_tmp) > epsilon:
#                     print("sita1, sita2, sita3: " + str(sita1) + ", " + str(sita2) + ", " + str(sita3) + "; " + str(sita1_tmp) + ", " + str(sita2_tmp)+ ", " + str(sita3_tmp))


# three_link_kin_test()