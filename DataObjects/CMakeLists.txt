## Make a shared library containing the objects for all sources in this directory.
## The library name should being with the package name.
## You will have to use this library name in the directory with the modules.

cet_make( LIBRARY_NAME gm2artexamples_dataobjects )

## Put the headers in the release area too

install_headers()