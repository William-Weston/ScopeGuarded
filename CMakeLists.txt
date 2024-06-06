# =====================================
# Preamble
# =====================================

cmake_minimum_required( VERSION 3.29 )

project( ScopeGuard
   VERSION      0.01
   DESCRIPTION  "Implementation of ScopeGuard and associated macros"
   LANGUAGES    CXX 
)

# =====================================
# Project Wide Setup
# =====================================

set( CMAKE_CXX_STANDARD 23 )
set( CMAKE_CXX_STANDARD_REQUIRED YES )
set( CMAKE_CXX_EXTENSIONS NO )


# =====================================
# Main Targets Built By This Project
# =====================================

add_subdirectory( src )