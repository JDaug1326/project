import os
import h5py
import numpy as np

filename = r'weights100000.h5'
f = h5py.File(filename)

for layer, g in f.items():
    for name, d in g.items():
        for k, v in d.items():
            print(k, v)
            print(' {} has a shape of {}'.format(k, np.array(d.get(k)).shape))
            print(" {} and has weights of {}".format(k, np.array(v)))
            print(str(k))