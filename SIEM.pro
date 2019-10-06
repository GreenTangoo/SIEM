TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    aggregator/parser_json/json.cpp \
        main.cpp \
    correlation_module/sypmtoms_namespace/other_symptoms.cpp \
    correlation_module/sypmtoms_namespace/repeater_symptoms.cpp \
    correlation_module/recognition_other_problems.cpp \
    correlation_module/recognition_repeater_problems.cpp \
    aggregator/parser_txt/parser.cpp

HEADERS += \
    aggregator/parser_json/json.hpp \
    correlation_module/sypmtoms_namespace/other_symptoms.hpp \
    correlation_module/sypmtoms_namespace/repeater_symptoms.hpp \
    correlation_module/recognition_interface.hpp \
    aggregator/parser_txt/parser.hpp \
    correlation_module/recognition_other_problems.hpp \
    correlation_module/recognition_repeater_problems.hpp
