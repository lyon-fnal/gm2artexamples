# This CMakeLists.txt file handles the fcl configuration files. 
# All that it really does is copy them to the build and release areas
# (but that's important!). 

file( GLOB fcl_files "*.fcl" )

# Install the files in the list to the release area
install( FILES ${fcl_files}
         DESTINATION ${product}/${version}/fcl )

# Also, copy the fcl files to the build area
foreach(aFile ${fcl_files})
  get_filename_component( basename ${aFile} NAME )
  configure_file( ${aFile} ${CMAKE_BINARY_DIR}/${product}/fcl/${basename} COPYONLY )
endforeach(aFile)
