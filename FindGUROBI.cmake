# FindGUROBI.cmake - Find the GUROBI libraries

if(GUROBI_INCLUDE_DIR)
  set(GUROBI_FIND_QUIETLY TRUE)
endif()

# Find the GUROBI include directory
find_path(GUROBI_INCLUDE_DIR
  NAMES gurobi_c.h
  HINTS ${GUROBI_DIR} $ENV{GUROBI_HOME}
  PATH_SUFFIXES include)

# Find the GUROBI library (C library)
find_library(GUROBI_LIBRARY
  NAMES gurobi gurobi120 gurobi110 gurobi100
  HINTS ${GUROBI_DIR} $ENV{GUROBI_HOME}
  PATH_SUFFIXES lib)

# Find the GUROBI C++ library
if(MSVC)
  # On Windows with MSVC
  find_library(GUROBI_CXX_LIBRARY
    NAMES gurobi_c++md2017 gurobi_c++md2019
    HINTS ${GUROBI_DIR} $ENV{GUROBI_HOME}
    PATH_SUFFIXES lib)
else()
  # On Linux/macOS
  find_library(GUROBI_CXX_LIBRARY
    NAMES gurobi_c++
    HINTS ${GUROBI_DIR} $ENV{GUROBI_HOME}
    PATH_SUFFIXES lib)
endif()

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GUROBI DEFAULT_MSG
  GUROBI_LIBRARY GUROBI_CXX_LIBRARY GUROBI_INCLUDE_DIR)

mark_as_advanced(GUROBI_LIBRARY GUROBI_CXX_LIBRARY GUROBI_INCLUDE_DIR)
