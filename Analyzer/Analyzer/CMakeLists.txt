cmake_minimum_required(VERSION 3.15)
project(SyntaxAnalyzer)

set(CMAKE_CXX_STANDARD 17)

add_library(analyzer_lib            Analyzer/Analyzer.h Analyzer/Analyzer.cpp)
add_library(generator_lib           StringGenerator/StringGenerator.h StringGenerator/StringGenerator.cpp)
add_library(object_lib              StringGenerator/Object/Object.h StringGenerator/Object/Object.cpp)

add_library(Distance_lib            StringGenerator/Object/Distance/Distance.h StringGenerator/Object/Distance/Distance.cpp)
add_library(Geo_lib                 StringGenerator/Object/Geo/geo.h StringGenerator/Object/Geo/geo.cpp)
add_library(Height_lib              StringGenerator/Object/Height/Height.h StringGenerator/Object/Height/Height.cpp)
add_library(Latitude_lib            StringGenerator/Object/Latitude/Latitude.h StringGenerator/Object/Latitude/Latitude.cpp)
add_library(Longitude_lib           StringGenerator/Object/Longitude/Longitude.h StringGenerator/Object/Longitude/Longitude.cpp)

add_library(RegExAnalyzer_lib       RegExAnalyzer/RegExAnalyzer.h RegExAnalyzer/RegExAnalyzer.cpp)
add_library(AutomataAnalyzer_sm_lib AutomataAnalyzer/_sm/AutomataAnalyzer_sm.h AutomataAnalyzer/_sm/AutomataAnalyzer_sm.cpp)
add_library(AutomataAnalyzer_lib    AutomataAnalyzer/AutomataAnalyzer.h AutomataAnalyzer/AutomataAnalyzer.cpp)
add_library(FlexAnalyzer_lib        FlexAnalyzer/FlexAnalyzer.h FlexAnalyzer/FlexAnalyzer.cpp)

target_link_libraries(AutomataAnalyzer_lib AutomataAnalyzer_sm_lib)
target_link_libraries(AutomataAnalyzer_sm_lib AutomataAnalyzer_lib)

target_link_libraries(RegExAnalyzer_lib analyzer_lib)
target_link_libraries(AutomataAnalyzer_lib analyzer_lib)
target_link_libraries(FlexAnalyzer_lib analyzer_lib)

add_executable(SyntaxAnalyzer main/main.cpp AutomataAnalyzer/_sm/statemap.h)

target_link_libraries(SyntaxAnalyzer
        analyzer_lib
        generator_lib
        object_lib
        Distance_lib
        Geo_lib
        Height_lib
        Latitude_lib
        Longitude_lib
        RegExAnalyzer_lib
        AutomataAnalyzer_sm_lib
        AutomataAnalyzer_lib
        FlexAnalyzer_lib
      )