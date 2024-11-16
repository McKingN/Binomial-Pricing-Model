#ifndef BINOMIAL_TREE_VERTEX_H
#define BINOMIAL_TREE_VERTEX_H

#include <memory>

class BinomialTreeVertex {
public:
    float spot;
    float up;
    float down;
    int step;
    int index;
    float value;
    float delta;

    std::shared_ptr<BinomialTreeVertex> prev_vertex;
    std::shared_ptr<BinomialTreeVertex> vertex_up;
    std::shared_ptr<BinomialTreeVertex> vertex_down;

    BinomialTreeVertex(
        float spot,
        float up,
        float down,
        int step,
        int index,
        std::shared_ptr<BinomialTreeVertex> prev_vertex = nullptr
    );
};

#endif // BINOMIAL_TREE_VERTEX_H
