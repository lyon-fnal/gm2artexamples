# This CMakeLists.txt file handles ART modules. Note that 
# there are no header files here (ART modules do not have headers)

# Use the @art_make@ macro to tell CMake how to build the modules. These modules depend on the data products defined in their shared object. Use the @LIBRARIES@ option to specify that dependence.

art_make( LIBRARIES "gm2artexamples_DataObjects")