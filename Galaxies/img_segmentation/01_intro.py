# Standard imports for data science.
import numpy as np
import matplotlib.pyplot as plt

# Example images and datasets.
# A curated set of general purpose and scientific images used in tests, examples, and documentation.
from skimage import data

# Return threshold value based on Otsu's method.
from skimage.filters import threshold_otsu

# This package contains various functions for multidimensional image processing.
from scipy import ndimage as ndi

# Find watershed basins in an image flooded from given markers.
from skimage.segmentation import watershed

# Find peaks in an image as coordinate list.
from skimage.feature import peak_local_max

# The KMeans algorithm clusters data by trying to separate samples in n groups of equal variance, minimizing a criterion known as the inertia or within-cluster sum-of-squares.
from sklearn.cluster import KMeans

# Retrieve a coins image from a data set for testing.
image = data.coins()

# Creates a figure object and a set of subplots
fig, axes = plt.subplots(nrows=1, ncols=2, figsize=(12,5))

ax = axes.ravel()

ax[0].imshow(image, cmap=plt.cm.grey)

