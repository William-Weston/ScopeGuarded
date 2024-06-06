# =====================================
# Preamble
# =====================================

cmake_minimum_required( VERSION 3.29 )

project( ScopeGuarded
         VERSION      0.01
         DESCRIPTION  "Implementation of ScopeGuard and associated macros"
         LANGUAGES    CXX 
)

if ( PROJECT_IS_TOP_LEVEL )
   enable_testing()
   include( CTest )
endif()

# =====================================
# Project Wide Setup
# =====================================

set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )
set( CMAKE_CXX_EXTENSIONS NO )

list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake )

# =====================================
# Externally Provided Content
# =====================================

include( dependencies.cmake )


# =====================================
# Main Targets Built By This Project
# =====================================

add_subdirectory( src )