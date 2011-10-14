## This directory has Art modules (which do not have headers)
## For each module in this directory, you need a line like the below

## Here are the two simple art modules
simple_plugin(HelloWorld1 "module")
simple_plugin(HelloWorld2 "module")

## Here are the two art modules that involve the classes from the DataObjects 
## directory. Note that the library name (see the CMakeLists.txt file in DataObjects) 
## must be given here to link against that library.
simple_plugin(ProduceMyLittleDatum "module" "gm2artexamples_dataobjects")
simple_plugin(MyDatumReader "module" "gm2artexamples_dataobjects")
