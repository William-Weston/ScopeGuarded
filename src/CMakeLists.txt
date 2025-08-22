#=============================
# Define Targets
#=============================

add_library( ScopeGuarded INTERFACE )
add_library( ScopeGuarded::ScopeGuarded ALIAS ScopeGuarded )

set( ScopeGuarded_Public_Headers
   ${CMAKE_CURRENT_SOURCE_DIR}/include/ScopeGuarded/ScopeGuarded.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/ScopeGuarded/details/ScopeGuard.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/ScopeGuarded/details/UncaughtExceptionCounter.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/include/ScopeGuarded/details/ScopeGuardExceptional.hpp
)


target_sources( ScopeGuarded
   INTERFACE
      FILE_SET  HEADERS
      BASE_DIRS include
      FILES     ${ScopeGuarded_Public_Headers}
)

target_compile_features( ScopeGuarded
   INTERFACE
      cxx_std_17
)


#=============================
# Testing
#=============================

add_executable( ScopeGuarded_Tests )

target_sources( ScopeGuarded_Tests 
   PRIVATE
     src/ScopeGuard.t.cpp
)

target_link_libraries( ScopeGuarded_Tests
   PRIVATE
      ScopeGuarded::ScopeGuarded
      Catch2::Catch2
      Catch2::Catch2WithMain
)


include( Catch )
catch_discover_tests( ScopeGuarded_Tests )

#=============================
# Packaging
#=============================

if ( PROJECT_IS_TOP_LEVEL )

   include( GNUInstallDirs )

   install(
      TARGETS   ScopeGuarded
      EXPORT    ScopeGuarded-Export

      FILE_SET  HEADERS
                DESTINATION   ${CMAKE_INSTALL_INCLUDEDIR}
      
      INCLUDES  DESTINATION   ${CMAKE_INSTALL_INCLUDEDIR}
   )

   set( CONFIG_FILES_DEST "share/ScopeGuarded/cmake" )

   install(
      EXPORT       ScopeGuarded-Export
      FILE         ScopeGuardedConfig.cmake
      NAMESPACE    "ScopeGuarded::"
      DESTINATION  ${CONFIG_FILES_DEST}
   )  

   include( CMakePackageConfigHelpers )

   write_basic_package_version_file( "ScopeGuardedConfigVersion.cmake" 
      VERSION            ${PROJECT_VERSION}
      COMPATIBILITY      SameMajorVersion
      ARCH_INDEPENDENT
   )

   install(
      FILES
         "${PROJECT_BINARY_DIR}/ScopeGuardedConfigVersion.cmake"
      DESTINATION
         "${CONFIG_FILES_DEST}"
   )

endif()