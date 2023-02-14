#include "Edge.h"

Edge::Edge()
{
	this->firstPoint = 0;
		this->secondPoint = 0;
		this->weight = 0.0;
}

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

void Edge::operator=(const Edge& edge)
{
	this->firstPoint = edge.firstPoint;
	this->secondPoint = edge.secondPoint;
	this->weight = edge.weight;
}
