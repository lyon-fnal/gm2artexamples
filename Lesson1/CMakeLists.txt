# This CMakeLists.txt file handles ART modules. Note that 
# there are no header files here (ART modules do not have headers)

# Use the @simple_plugin@ macro to tell CMake how to build the modules. You need 
# a call for every module in the directory that you want to build. The syntax is,
# <pre>simple_plugin( moduleName "module" dependentLibrary )</pre> The arguments are:
# * @moduleName@ is the name of your module (without the @_module@)
# * @"module"@ is a literal to identify your library as a module
# * @dependentLibrary@ (optional) is either a particular library that your module depends on or a list of libraries
# See below for examples

art_make( LIBRARIES "gm2artexamples_DataObjects")

# Two simple ART modules
#simple_plugin(HelloWorld1 "module")
#simple_plugin(HelloWorld2 "module")

# Two more ART modules that depend on the classes from the @DataObjects@ directory 
# (e.g. the @MyLittleDatum@ class). Note that the dependent library for @MyLittleDatum@ 
# needs to be given (see the @CMakeLists.txt@ file in @DataObjects@ for the library name)
#simple_plugin(ProduceMyLittleDatum "module" "gm2artexamples_dataobjects")
#simple_plugin(MyDatumReader "module" "gm2artexamples_dataobjects")
