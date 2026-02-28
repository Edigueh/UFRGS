from marvin.tools import Maps

# Do not forget to add this, as marvin plots uses matplotlib behind.
import matplotlib.pyplot as plt

maps = Maps(plateifu='8485-1901')

# Hydrogen flux map (H-alpha)
ha = maps.emline_gflux_ha_6564
ha.plot()

plt.show()
