TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    aggregator/parser_json/json.cpp \
    aggregator/parser_txt/parser.cpp \
    correlation_module/AccessManagment/account_access/user_login_symptoms.cpp \
    correlation_module/graph.cpp \
    correlation_module/recognition_categories_main.cpp \
    correlation_module/sub_graph.cpp \
    main.cpp \
    correlation_module/AvailabilityManagment/denial_of_service/dos_wifi_symptoms.cpp \
    correlation_module/NetworkManagment/discovery/directory_discovery_symptoms.cpp \
    correlation_module/NetworkManagment/discovery/port_scanning_symptoms.cpp \
    correlation_module/AccessManagment/account_access/login_root_symptoms.cpp \
    correlation_module/SystemManagment/proccess_manipulation/process_discovery_symptoms.cpp \
    correlation_module/SystemManagment/files_manipulation/data_collection_symptoms.cpp \
    correlation_module/symptoms_interface/symp_implementation.cpp \
    prediction_module/predictor.cpp \
    aggregator/time_class/parse_time.cpp \
    correlation_module/SystemManagment/proccess_manipulation/command_line_interface_symptoms.cpp \
    correlation_module/SystemManagment/files_manipulation/account_discovery_symptoms.cpp \
    correlation_module/SystemManagment/proccess_manipulation/system_network_conf_discovery_symptoms.cpp \
    correlation_module/SystemManagment/proccess_manipulation/system_network_conn_discovery_symptoms.cpp \
    correlation_module/SystemManagment/proccess_manipulation/data_compressed_symptoms.cpp \
    correlation_module/all_categories.cpp

HEADERS += \
    aggregator/parser_json/json.hpp \
    aggregator/parser_txt/parser.hpp \
    correlation_module/AccessManagment/account_access/user_login_symptoms.hpp \
    correlation_module/graph.h \
    correlation_module/recognition_categories_main.h \
    correlation_module/sub_graph.h \
    correlation_module/symptoms_interface/main_symp_interface.hpp \
    correlation_module/recognition_interface.hpp \
    correlation_module/all_symptoms.hpp \
    correlation_module/all_categories.hpp \
    correlation_module/AvailabilityManagment/denial_of_service/dos_wifi_symptoms.hpp \
    correlation_module/NetworkManagment/discovery/directory_discovery_symptoms.hpp \
    correlation_module/NetworkManagment/discovery/port_scanning_symptoms.hpp \
    correlation_module/AccessManagment/account_access/login_root_symptoms.hpp \
    correlation_module/SystemManagment/proccess_manipulation/process_discovery_symptoms.hpp \
    correlation_module/SystemManagment/files_manipulation/data_collection_symptoms.hpp \
    correlation_module/symptoms_interface/symp_implementation.hpp \
    prediction_module/predictor.hpp \
    aggregator/time_class/parse_time.hpp \
    correlation_module/SystemManagment/proccess_manipulation/command_line_interface_symptoms.hpp \
    correlation_module/SystemManagment/files_manipulation/account_discovery_symptoms.hpp \
    correlation_module/SystemManagment/proccess_manipulation/system_network_conf_discovery_symptoms.hpp \
    correlation_module/SystemManagment/proccess_manipulation/system_network_conn_discovery_symptoms.hpp \
    correlation_module/SystemManagment/proccess_manipulation/data_compressed_symptoms.hpp
