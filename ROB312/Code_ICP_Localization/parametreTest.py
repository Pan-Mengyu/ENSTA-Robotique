import numpy as np
import matplotlib.pyplot as plt
import math
import time

import readDatasets as datasets
import icp

# Reading some data
scanList = datasets.read_u2is(56)
scanOriginal = scanList[55]
scanTruePose = np.array([0.3620, 0.0143, 0.0483])  # Manual estimation for scan 55 of u2is dataset

# Initialise error log
nb_test = 96
poseError = np.zeros((3, nb_test))
global MinDistance


for a in range(5, nb_test):

    icp.setValue(a * 0.01)

    for b in range(10):
        time_start = time.process_time()
        idref = np.random.randint(50)
        refscan = scanList[idref]
        # Generate random displacement and applies it to the second scan
        randT = np.random.rand(2, 1) - 0.5
        randR = 0.6*np.random.rand(1, 1) - 0.3
        R = np.array([[math.cos(randR), -math.sin(randR)], [math.sin(randR), math.cos(randR)]])
        scan = datasets.transform_scan(scanOriginal, R, randT)

        R, t, error = icp.icp(refscan, scan, 200, 1e-7)
        scan = datasets.transform_scan(scan, R, t)
        poseError[:, a] = np.transpose(scan["pose"] - scanTruePose)
    time_elapsed = time.process_time() - time_start
    tErrors = np.sqrt(np.square(poseError[0, :]) + np.square(poseError[1, :]))
    oErrors = np.sqrt(np.square(poseError[2, :]))
    print("Index:{:e}".format(a * 0.01))
    print("Mean (var) translation error : {:e} ({:e})".format(np.mean(tErrors), np.var(tErrors)))
    print("Mean (var) rotation error : {:e} ({:e})".format(np.mean(oErrors), np.var(oErrors)))
    print("Mean computation time : {:f}".format(time_elapsed/nb_test))