1. Dependencies:
- Uses Eigen for matrix operations (replacing NumPy)
- Would need a DataFrame-like class implementation (replacing pandas)
- Would need C++ implementations of PCA and OPTICS algorithms
- Would need a plotting library like matplotlib-cpp for visualization

2. Major changes:
- Replaced Python dynamic typing with C++ static typing
- Converted NumPy arrays and Pandas DataFrames to Eigen matrices and custom DataFrame class
- Changed Python list comprehensions to C++ loops
- Replaced Python's object-oriented features with C++ equivalents

3. Implementation notes:
- Some methods are left as placeholders since they would require significant C++ library support
- Statistical functions like Hurst exponent calculation are simplified
- Plotting functions would need to be implemented using a C++ plotting library

4. Missing features that would need to be implemented:
- A proper DataFrame class for data handling
- C++ implementations of statistical tests
- Proper error handling and memory management
- Visualization capabilities
