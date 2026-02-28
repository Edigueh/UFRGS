from marvin.tools import Maps

import matplotlib.pyplot as plt

maps = Maps(plateifu='8485-1901')

# Hydrogen flux map (H-alpha)
ha = maps.emline_gflux_ha_6564
ha.plot()

plt.show()
