# UPS CMakeLists.txt file

process_ups_files()

configure_file ( ${gm2artexamples_SOURCE_DIR}/ups/gm2artexamples-config.cmake.in
                 ${gm2artexamples_BINARY_DIR}/ups/gm2artexamples-config.cmake @ONLY )
configure_file ( ${gm2artexamples_SOURCE_DIR}/ups/gm2artexamples-config-version.cmake.in
                 ${gm2artexamples_BINARY_DIR}/ups/gm2artexamples-config-version.cmake @ONLY )

install (FILES ${gm2artexamples_BINARY_DIR}/ups/gm2artexamples-config.cmake
               ${gm2artexamples_BINARY_DIR}/ups/gm2artexamples-config-version.cmake
	 DESTINATION ${flavorqual_dir}/lib/gm2artexamples-${version} )

## Add setup line to source_for_local.sh in local products area (no qualifier needed here)
install(CODE "file(APPEND ${CMAKE_INSTALL_PREFIX}/source_for_local.sh \"\nsetup -j ${product} ${version} -q \\\"${full_qualifier}\\\"\")")
