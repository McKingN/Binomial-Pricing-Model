#include <iostream>
#include "../include/BinomialTree.h"
#include <vector>
#include <string>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <numeric>
#include "../include/BinomialTreeVertex.h"
#include "BinomialTree.cpp"
#include "BinomialTreeVertex.cpp"

int main() {
    // Initialize the BinomialTree with the desired parameters
    BinomialTree tree(
        "call",          // Option type (call or put)
        10500.0,           // Strike price
        10000.0,           // Spot price
        0.05,             // Interest rate (10%)
        1.0 / 2.0,      // Time period (1 month)
        0.1,            // Volatility (2%)
        2                // Number of periods
    );

    // Build the binomial tree
    tree.buildTree();

    // Price the option
    tree.pricer();

    // Access and display the first vertex informations and btw the price of option
    auto vertex = tree.getTree()[std::make_tuple(0, 1)];
    if (vertex) {
        std::cout << "First vertex spot value: " << vertex->spot << std::endl;
        std::cout << "First vertex value: " << vertex->value << std::endl;
        std::cout << "First vertex delta: " << vertex->delta << std::endl;
    } else {
        std::cout << "Vertex (0, 1) not found in the tree!" << std::endl;
    }

    return 0;
}
