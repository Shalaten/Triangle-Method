#include "Edge.h"

Edge::Edge(int firstPoint = 0, int secondPoint = 0, double weight = 0) {
	this->firstPoint = firstPoint;
	this->secondPoint = secondPoint;
	this->weight = weight;
}

int Edge::GetFirstPoint()
{
	return firstPoint;
}

int Edge::GetSecondPoint()
{
	return secondPoint;
}

double Edge::GetWeight()
{
	return weight;
}

void Edge::SetFirstPoint(int firstPoint)
{
	this->firstPoint = firstPoint;
}

void Edge::SetSecondPoint(int secondPoint)
{
	this->secondPoint = secondPoint;
}

void Edge::SetWeight(double weight)
{
	this->weight = weight;
}
