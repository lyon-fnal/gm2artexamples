# !!! Note the list of FCL files. If you make a new FCL file in this directory,
#     you must add it to this list. If you don't, it will be ignored.
#

# !!! Add new fcl files to the bottom of this list
set( fcl_files
        messageservice.fcl
        minimalMessageService.fcl
        hello1.fcl
        hello2.fcl
        makeDatum.fcl
        readDatum.fcl
)

# install all *.fcl files in this directory
# Let's automatically find all of the fcl files in this directory
install( FILES ${fcl_files}
         DESTINATION ${product}/${version}/${PROJECT_NAME}/fcl )

# Also, copy the fcl files to the build area
foreach(aFile ${fcl_files})
  get_filename_component( basename ${aFile} NAME )
  configure_file( ${aFile} ${CMAKE_BINARY_DIR}/fcl/${basename} COPYONLY )
endforeach(aFile)
