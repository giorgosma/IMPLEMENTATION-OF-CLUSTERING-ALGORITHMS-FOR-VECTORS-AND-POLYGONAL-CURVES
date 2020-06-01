# IMPLEMENTATION OF CLUSTERING ALGORITHMS FOR VECTORS AND POLYGONAL CURVES

##Description:
1. Implementation of clustering algorithms for vectors and polygonal curves
    - Vectors metric is L1 (Manhattan)
    - Polygonal curves metric is Dynamic Time Warping (DTW)
2. Implementation of hashing and search algorithms for vectors and polygonal curves
------------------------
##Implementation details:
1. Clustering:
    - Initialization:
        - Random selection of K points / K curves
        - K-means++
    - Assignment:
        - Lloyd's assignment
        - Assignment by Range search with LSH for vectors / curves (custom implementation)
    - Update:
        - Partitioning Around Medoids (PAM) 'a la Lloyds
        - Compute Mean Vector
2. Hashing and Search:
    - Vectors
        - LSH 
        - random projection to Hypercube
    - Curves
        - display curves into L grid curves and convert them to vectors
