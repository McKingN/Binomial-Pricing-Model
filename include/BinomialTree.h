#ifndef BINOMIAL_TREE_H
#define BINOMIAL_TREE_H

#include "BinomialTreeVertex.h"
#include <map>
#include <tuple>
#include <string>
#include <vector>

// BinomialTree.h

class BinomialTree {
private:
    std::map<std::tuple<int, int>, std::shared_ptr<BinomialTreeVertex>> tree;
    std::string optionType;
    float strike, spot, interestRate, timePeriod, variationPercentage;
    int numberOfPeriods;

    std::pair<float, float> europeanOptionPricingBinomialOnePeriodModel(std::shared_ptr<BinomialTreeVertex> vertex);

public:
    BinomialTree(
        const std::string& optionType,
        float strike,
        float spot,
        float interestRate,
        float timePeriod,
        float variationPercentage,
        int numberOfPeriods
    );

    void buildTree();
    void pricer();
    void drawTree(const std::string& output_file);

    // Corrected Getter for the tree - no need for BinomialTree:: here
    std::map<std::tuple<int, int>, std::shared_ptr<BinomialTreeVertex>>& getTree();
};

#endif // BINOMIAL_TREE_H