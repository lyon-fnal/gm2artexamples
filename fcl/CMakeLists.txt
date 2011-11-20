# This CMakeLists.txt file handles the fcl configuration files. 
# All that it really does is copy them to the build and release areas
# (but that's important!). 

# Note: *IMPORTANT* The list of FCL files to handle is below. You *must* put a new
# file in this list. If you don't, it will not appear in the build area
# nor in the release area. 
set( fcl_files
        messageservice.fcl
        minimalMessageService.fcl
        hello1.fcl
        hello2.fcl
        makeDatum.fcl
        readDatum.fcl
        makeHits.fcl
        readHits.fcl
)

# Install the files in the list to the release area
install( FILES ${fcl_files}
         DESTINATION ${product}/${version}/${PROJECT_NAME}/fcl )

# Also, copy the fcl files to the build area
foreach(aFile ${fcl_files})
  get_filename_component( basename ${aFile} NAME )
  configure_file( ${aFile} ${CMAKE_BINARY_DIR}/fcl/${basename} COPYONLY )
endforeach(aFile)
