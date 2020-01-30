#include <QApplication>

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <vector>
#include <thread>

#include "correlation_module/graph.h"
#include "correlation_module/sub_graph.h"
#include "prediction_module/predictor.hpp"
#include "aggregator/time_class/parse_time.hpp"
#include "gui_module/mainapplicationwindow.h"

using namespace topology;

void displayPrediction(const analysis::prediction &obj, std::ofstream &fout)
{
    std::vector<std::pair<std::string, std::vector<std::string>>> returned_pred = obj.getPredictionSymptoms();

    for(size_t i(0); i < returned_pred.size(); i++)
    {
        fout << "Attack vector name: " << returned_pred[i].first << "\n";
        for(size_t j(0); j < returned_pred[i].second.size(); j++)
            fout << "    Possible later symptoms: " << returned_pred[i].second[j] << "\n";
    }
}

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    /*app.setStyleSheet("QLabel {"
                      "border-style: solid;"
                      "border-width: 1px;"
                      "border-color: black; "
                      "}");*/
    MainApplicationWindow *window = new MainApplicationWindow();
    window->setFixedSize(800,600);
    window->show();

    std::ofstream fout;
    fout.open("result.txt", std::ios_base::out);
    if(fout.is_open() == false)
        return -1;



    topology::graph graph_obj;
    graph_obj.initializeRecognitionMethods();
    graph_obj.fillGraph();

    std::list<sub_graph> return_vec = graph_obj.getAllSubGraphs();

    for(std::list<sub_graph>::iterator it = return_vec.begin(); it != return_vec.end(); it++)
    {
        analysis::prediction prediction_obj(*it);
        displayPrediction(prediction_obj, fout);

        fout << "One sub graph" << "\n";
        std::vector<symptom_info> symptoms = it->getSymptomInfo();

        for(size_t i(0); i < symptoms.size(); i++)
        {
            fout << "  One symptom" << "\n";
            fout << "      Time: " << symptoms[i].time.getStrTime() << "\n";
            fout << "      Category: " << category::category_resolver::getInstance().getCategoryName(symptoms[i].symp_type) << "\n";

            for(size_t j(0); j < symptoms[i].info.size(); j++)
                fout << "      Information: " << symptoms[i].info[j].first << "\n";
        }
        fout << "\n";
    }

    return app.exec();
}

