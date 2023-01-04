#include "vertex.h"


Edge::Edge(const Edge& e) : source(e.source), target(e.target), flow(e.flow), capacity(e.capacity) {}

bool Edge::isImprove() {
    if (capacity > 0)
        return true;
    return false;
}
bool Edge::operator!=(const Edge& e)
{
    if (source.id == e.source.id && target.id == e.target.id)
        return false;

    return true;
}

void Edge::operator=(const Edge& e)
{
    if (e.target.id != this->target.id)
    {
        this->source = e.source;
        this->target = e.target;
        this->capacity = e.capacity;
        this->flow = e.flow;
    }

}
