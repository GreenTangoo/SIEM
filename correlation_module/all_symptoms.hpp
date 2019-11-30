#ifndef ALL_SYMPTOMS_HPP
#define ALL_SYMPTOMS_HPP


#include "recognition_categories_main.h"

#include "NetworkManagment/discovery/port_scanning_symptoms.hpp"
#include "NetworkManagment/discovery/directory_discovery_symptoms.hpp"


#include "AccessManagment/account_access/user_login_symptoms.hpp"
#include "AccessManagment/account_access/login_root_symptoms.hpp"

#include "SystemManagment/files_manipulation/action_files_symptoms.hpp"
#include "SystemManagment/proccess_manipulation/action_proccess_symptoms.hpp"

using namespace symptoms::discovery;
using namespace symptoms::account_access;
using namespace symptoms::files_manipulation;
using namespace symptoms::proccess_manipulation;

#endif
