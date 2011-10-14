# You do not have to change anything here
# !!! But note, if you add a new fcl file in this directory, you will need to zap your
# build area (gm2d zapBuild) and redo cmake ../src

# install all *.fcl files in this directory
# Let's automatically find all of the fcl files in this directory
file(GLOB fcl_files *.fcl)
install( FILES ${fcl_files}
         DESTINATION ${product}/${version}/${PROJECT_NAME}/fcl )

# Also, copy the fcl files to the build area
foreach(aFile ${fcl_files})
  get_filename_component( basename ${aFile} NAME )
  configure_file( ${aFile} ${CMAKE_BINARY_DIR}/fcl/${basename} COPYONLY )
endforeach(aFile)
