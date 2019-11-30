#ifndef DOWNLOAD_FILES_SYMPTOMS_HPP
#define DOWNLOAD_FILES_SYMPTOMS_HPP

#include <string>
#include <algorithm>
#include <map>

#include "../../symptoms_interface/symp_implementation.hpp"
#include "../../../aggregator/parser_json/json.hpp"

namespace symptoms
{
    namespace files_manipulation
    {
        class ActionFilesSymptoms : public Symptom_impl
        {
        private:
            jsoner::json_parser parser;
            std::string json_filename;
        public:
            ActionFilesSymptoms(std::string filename);
            ActionFilesSymptoms(const ActionFilesSymptoms &other) = default;
            ActionFilesSymptoms(ActionFilesSymptoms &&other) = default;
            ~ActionFilesSymptoms();
            bool checkSymptoms();
        };
    }
}

#endif
