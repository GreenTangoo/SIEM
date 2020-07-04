TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    aggregator/aggregation_module/ApacheAggregation/apache_aggr.cpp \
    aggregator/aggregation_module/CustomAggregation/custom_aggregator.cpp \
    aggregator/aggregation_module/FilesManipulation/files_manipulation_aggr.cpp \
    aggregator/aggregation_module/IptablesAggregation/iptables_aggr.cpp \
    aggregator/aggregation_module/ProcessesManipulation/processes_manupulation_aggr.cpp \
    aggregator/aggregation_module/SystemAuthorizationAggregation/system_auth_aggr.cpp \
    aggregator/aggregation_module/aggregation_initializer.cpp \
    aggregator/aggregation_module/aggregator_interface/aggr_interface_implementation.cpp \
    aggregator/parser_json/json.cpp \
    aggregator/parser_txt/parser.cpp \
    config_descriptor.cpp \
    correlation_module/AccessManagment/account_access/user_login_symptoms.cpp \
    correlation_module/AccessManagment/account_access/valid_accounts.cpp \
    correlation_module/CustomCorrelation/custom_correlator.cpp \
    correlation_module/graph.cpp \
    correlation_module/recognition_categories_main.cpp \
    correlation_module/sub_graph.cpp \
    error_handler_module/handler.cpp \
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
    correlation_module/all_categories.cpp \

HEADERS += \
    aggregator/aggregation_module/ApacheAggregation/apache_aggr.hpp \
    aggregator/aggregation_module/CustomAggregation/custom_aggregator.hpp \
    aggregator/aggregation_module/FilesManipulation/files_manipulation_aggr.hpp \
    aggregator/aggregation_module/IptablesAggregation/iptables_aggr.hpp \
    aggregator/aggregation_module/ProcessesManipulation/processes_manupulation_aggr.hpp \
    aggregator/aggregation_module/SystemAuthorizationAggregation/system_auth_aggr.hpp \
    aggregator/aggregation_module/aggregation_initializer.hpp \
    aggregator/aggregation_module/aggregator_interface/aggr_interface_implementation.hpp \
    aggregator/aggregation_module/aggregator_interface/main_aggr_interface.hpp \
    aggregator/aggregation_module/all_aggregations.hpp \
    aggregator/parser_json/json.hpp \
    aggregator/parser_txt/parser.hpp \
    config_descriptor.hpp \
    correlation_module/AccessManagment/account_access/user_login_symptoms.hpp \
    correlation_module/AccessManagment/account_access/valid_accounts.hpp \
    correlation_module/CustomCorrelation/custom_correlator.hpp \
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
    error_handler_module/handler.hpp \
    logfile_defines.hpp \
    prediction_module/predictor.hpp \
    aggregator/time_class/parse_time.hpp \
    correlation_module/SystemManagment/proccess_manipulation/command_line_interface_symptoms.hpp \
    correlation_module/SystemManagment/files_manipulation/account_discovery_symptoms.hpp \
    correlation_module/SystemManagment/proccess_manipulation/system_network_conf_discovery_symptoms.hpp \
    correlation_module/SystemManagment/proccess_manipulation/system_network_conn_discovery_symptoms.hpp \
    correlation_module/SystemManagment/proccess_manipulation/data_compressed_symptoms.hpp \
