TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    aggregator/parser_json/json.cpp \
    aggregator/parser_txt/parser.cpp \
    correlation_module/denial_of_service/dos_wifi/dos_wifi_symptoms.cpp \
    correlation_module/discovery/directory_discovery/directory_discovery_symptoms.cpp \
    correlation_module/discovery/port_scanning/port_scanning_symptoms.cpp \
    main.cpp \
    correlation_module/discovery/discovery_main.cpp

HEADERS += \
    aggregator/parser_json/json.hpp \
    aggregator/parser_txt/parser.hpp \
    correlation_module/symptoms_interface/main_symp_interface.hpp \
    correlation_module/denial_of_service/dos_wifi/dos_wifi_symptoms.hpp \
    correlation_module/denial_of_service/denial_of_service_interface.hpp \
    correlation_module/discovery/directory_discovery/directory_discovery_symptoms.hpp \
    correlation_module/discovery/port_scanning/port_scanning_symptoms.hpp \
    correlation_module/discovery/discovery_main.hpp \
    correlation_module/recognition_interface.hpp \
    correlation_module/all_symptoms.hpp
