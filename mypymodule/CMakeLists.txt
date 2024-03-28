# Python Extension Module
add_library(mymodule MODULE
    src/mymodule.cpp
)

# Link Python library
# target_link_libraries(mymodule
#     PRIVATE
#     ${PYTHON_LIBRARIES}
# )

# Set Python module suffix for Windows
if(WIN32)
    set_target_properties(mymodule PROPERTIES
        PREFIX ""
        SUFFIX ".pyd"
    )
else()
    # Set Python module suffix for Unix-like systems (e.g., Linux, macOS)
    set_target_properties(mymodule PROPERTIES
        PREFIX ""
        SUFFIX ".so"
    )
endif()

# Move the module to proper location
set_target_properties(mymodule PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
)

# Installation
install(TARGETS mymodule DESTINATION ${PROJECT_SOURCE_DIR}/.venv/lib/site-packages)