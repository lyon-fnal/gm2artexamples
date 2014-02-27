# Remember that every directory that has something to build or copy to the build area needs a @CMakeLists.txt@ file
# and must also appear as a @add_subdirectory@ call in the &l=CMakeLists.txt& file of the parent directory.

# h3. Main code

# Make a shared library containing the objects for all sources in this directory.
# You don't have to list the sources, the build system will figure it out. 
# The library will be called productName_subDirectoryName. So in this case, it would be
# gm2artexamples_DataObjects.so
art_make()

# Put the headers in the release area too
install_headers()

# If you are following the tutorial, you should look at the &l=DataObjects/MyLittleDatum.hh& file next. 
