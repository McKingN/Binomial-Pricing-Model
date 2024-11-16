#include "../include/BinomialTree.h"
#include <iostream>
#include <memory>
#include <cmath>
#include <C:\Program Files\Graphviz\include\graphviz\gvc.h>

BinomialTree::BinomialTree(
    const std::string& optionType,
    float strike,
    float spot,
    float interestRate,
    float timePeriod,
    float variationPercentage,
    int numberOfPeriods
) : optionType(optionType), strike(strike), spot(spot), interestRate(interestRate),
    timePeriod(timePeriod), variationPercentage(variationPercentage), numberOfPeriods(numberOfPeriods) {}

void BinomialTree::buildTree() {
    // Create the root vertex
    auto firstVertex = std::make_shared<BinomialTreeVertex>(
        spot, spot * (1 + variationPercentage), spot * (1 - variationPercentage), 0, 0
    );
    tree[{0, 1}] = firstVertex;

    // Build the rest of the tree
    for (int i = 0; i < numberOfPeriods; ++i) {
        for (int j = 1; j <= std::pow(2, i); ++j) {
            auto current_vertex = tree[{i, j}];
            if (!current_vertex) continue;

            float up = current_vertex->spot * (1 + variationPercentage);
            float down = current_vertex->spot * (1 - variationPercentage);

            auto vertex_up = std::make_shared<BinomialTreeVertex>(
                up, up * (1 + variationPercentage), up * (1 - variationPercentage), i + 1, 2 * j - 1, current_vertex
            );
            auto vertex_down = std::make_shared<BinomialTreeVertex>(
                down, down * (1 + variationPercentage), down * (1 - variationPercentage), i + 1, 2 * j, current_vertex
            );

            tree[{i + 1, 2 * j - 1}] = vertex_up;
            tree[{i + 1, 2 * j}] = vertex_down;

            current_vertex->vertex_up = vertex_up;
            current_vertex->vertex_down = vertex_down;
        }
    }
}

std::pair<float, float> BinomialTree::europeanOptionPricingBinomialOnePeriodModel(std::shared_ptr<BinomialTreeVertex> vertex) {
    float spot = vertex->spot;
    float spotUp = vertex->vertex_up->spot;
    float spotDown = vertex->vertex_down->spot;
    float interestRate = this->interestRate;
    float timePeriode = this->timePeriod;
    float strike = this->strike;
    float valueUp = vertex->vertex_up->value;
    float valueDown = vertex->vertex_down->value;

    // Compute delta and value using the binomial formula
    float delta = (valueUp - valueDown) / (spotUp - spotDown);
    float value = (spot * delta) + ((valueDown - delta * spotDown) / std::pow(1 + interestRate, timePeriode));

    return {delta, value};
}

void BinomialTree::pricer() {
    // Set the value of the option at the leaves (final step of the tree)
    for (int index = 1; index <= std::pow(2, numberOfPeriods); ++index) {
        auto vertex = tree[{numberOfPeriods, index}];
        if (!vertex) {
            std::cout << "Vertex not found for (step, index): (" << numberOfPeriods << ", " << index << ")\n";
            continue;
        }
        if (optionType == "call") {
            vertex->value = std::max(vertex->spot - strike, 0.0f);
        } else if (optionType == "put") {
            vertex->value = std::max(strike - vertex->spot, 0.0f);
        }
        tree[{numberOfPeriods, index}] = vertex;
    }

    // Backward pricing of the option
    for (int step = numberOfPeriods - 1; step >= 0; --step) {
        for (int index = 1; index <= std::pow(2, step); ++index) {
            auto vertex = tree[{step, index}];
            if (!vertex) continue;
            auto [delta, value] = europeanOptionPricingBinomialOnePeriodModel(vertex);
            vertex->delta = delta;
            vertex->value = value;
        }
    }
}

// Getter method for the tree
// BinomialTree.cpp

std::map<std::tuple<int, int>, std::shared_ptr<BinomialTreeVertex>>& BinomialTree::getTree() {
    return tree;
}





// void BinomialTree::drawTree(const std::string& output_file) {
//     // Create Graphviz context for drawing the tree
//     GVC_t* gvc = gvContext();
//     Agraph_t* graph = agopen("binomial_tree", Agdirected, nullptr);

//     // Set graph attributes
//     agattr(graph, AGNODE, "shape", "box");
//     agattr(graph, AGEDGE, "color", "black");

//     for (auto& kv : tree) {
//         int step = std::get<0>(kv.first);
//         int index = std::get<1>(kv.first);
//         auto vertex = kv.second;

//         // Create nodes with label containing vertex data
//         std::string label = "Spot: " + std::to_string(vertex->spot) + "\n";
//         label += "Step: " + std::to_string(step) + "\n";
//         label += "Index: " + std::to_string(index) + "\n";
//         label += "Delta: " + std::to_string(vertex->delta) + "\n";
//         label += "Value: " + std::to_string(vertex->value);

//         Agnode_t* node = agnode(graph, (std::to_string(step) + "_" + std::to_string(index)).c_str(), 1);
//         agset(node, "label", label.c_str());

//         if (vertex->vertex_up) {
//             std::string up_edge = std::to_string(step + 1) + "_" + std::to_string(2 * index - 1);
//             agedge(graph, node, agnode(graph, up_edge.c_str(), 1), 0);
//         }

//         if (vertex->vertex_down) {
//             std::string down_edge = std::to_string(step + 1) + "_" + std::to_string(2 * index);
//             agedge(graph, node, agnode(graph, down_edge.c_str(), 1), 0);
//         }
//     }

//     // Render the graph to a file
//     gvLayout(gvc, graph, "dot");
//     gvRenderFilename(gvc, graph, "pdf", output_file.c_str());

//     // Clean up Graphviz context
//     gvFreeLayout(gvc, graph);
//     agclose(graph);
//     gvFreeContext(gvc);
// }

// void BinomialTree::drawTree(const std::string& output_file) {
//     // Create Graphviz context for drawing the tree
//     GVC_t* gvc = gvContext();
//     Agraph_t* graph = agopen("binomial_tree", Agdirected, nullptr);

//     // Set graph attributes
//     agattr(graph, AGNODE, "shape", "box");
//     agattr(graph, AGEDGE, "color", "black");

//     for (auto& kv : tree) {
//         int step = std::get<0>(kv.first);
//         int index = std::get<1>(kv.first);
//         auto vertex = kv.second;

//         // Create nodes with label containing vertex data
//         std::string label = "Spot: " + std::to_string(vertex->spot) + "\n";
//         label += "Step: " + std::to_string(step) + "\n";
//         label += "Index: " + std::to_string(index) + "\n";
//         label += "Delta: " + std::to_string(vertex->delta) + "\n";
//         label += "Value: " + std::to_string(vertex->value);

//         // Create node using a non-const char*
//         std::string nodeName = std::to_string(step) + "_" + std::to_string(index);
//         Agnode_t* node = agnode(graph, const_cast<char*>(nodeName.c_str()), 1);
//         agset(node, "label", label.c_str());

//         if (vertex->vertex_up) {
//             std::string up_edge = std::to_string(step + 1) + "_" + std::to_string(2 * index - 1);
//             Agnode_t* up_node = agnode(graph, const_cast<char*>(up_edge.c_str()), 1); // Create the "up" node
//             agedge(graph, node, up_node, 1); // Create an edge from current node to "up" node
//         }

//         if (vertex->vertex_down) {
//             std::string down_edge = std::to_string(step + 1) + "_" + std::to_string(2 * index);
//             Agnode_t* down_node = agnode(graph, const_cast<char*>(down_edge.c_str()), 1); // Create the "down" node
//             agedge(graph, node, down_node, 1); // Create an edge from current node to "down" node
//         }
//     }

//     // Render the graph to the output file (assuming you have a render step)
//     gvRenderFilename(gvc, graph, "png", output_file.c_str());
//     gvFreeContext(gvc);
//     agclose(graph);
// }
