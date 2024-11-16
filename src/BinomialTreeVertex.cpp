#include "C:\Users\McKing.DESKTOP-4Q7G3QP\Documents\GitHub\3A Marseille\Binomial-Pricing-Model\include\BinomialTreeVertex.h"

BinomialTreeVertex::BinomialTreeVertex(
    float spot, float up, float down, int step, int index, 
    std::shared_ptr<BinomialTreeVertex> prev_vertex
) : spot(spot), up(up), down(down), step(step), index(index), prev_vertex(prev_vertex), 
    value(0.0f), delta(0.0f) {}
