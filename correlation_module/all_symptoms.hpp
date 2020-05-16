#ifndef ALL_SYMPTOMS_HPP
#define ALL_SYMPTOMS_HPP


#include "recognition_categories_main.h"

#include "NetworkManagment/discovery/port_scanning_symptoms.hpp"
#include "NetworkManagment/discovery/directory_discovery_symptoms.hpp"


#include "AccessManagment/account_access/user_login_symptoms.hpp"
#include "AccessManagment/account_access/login_root_symptoms.hpp"
#include "AccessManagment/account_access/valid_accounts.hpp"


#include "SystemManagment/files_manipulation/data_collection_symptoms.hpp"
#include "SystemManagment/files_manipulation/account_discovery_symptoms.hpp"
#include "SystemManagment/proccess_manipulation/process_discovery_symptoms.hpp"
#include "SystemManagment/proccess_manipulation/command_line_interface_symptoms.hpp"
#include "SystemManagment/proccess_manipulation/system_network_conf_discovery_symptoms.hpp"
#include "SystemManagment/proccess_manipulation/system_network_conn_discovery_symptoms.hpp"
#include "SystemManagment/proccess_manipulation/data_compressed_symptoms.hpp"

#include "CustomCorrelation/config_descriptor.hpp"
#include "CustomCorrelation/custom_correlator.hpp"

using namespace symptoms_space::discovery;
using namespace symptoms_space::account_access;
using namespace symptoms_space::files_manipulation;
using namespace symptoms_space::proccess_manipulation;
using namespace symptoms_space::custom_correlation;

#endif
