add_library(demangle
    lib/Demangle.cpp
    lib/ItaniumDemangle.cpp
    lib/MicrosoftDemangle.cpp
    lib/MicrosoftDemangleNodes.cpp)
    
target_include_directories(demangle
    PUBLIC
        include)