#include "Vertice.h"

Vertice::Vertice(int verticeNumber)
{
	this->verticeNumber = verticeNumber;
	firstMinVertice = 0;
	secondMinVertice = 0;
	lostWeight = 0.0;
	firstMinVerticeWeight = 10000.0;
	secondMinVerticeWeight = 10000.0;
	state = false;
}

double Vertice::GetLostWeight()
{
	return lostWeight;
}

void Vertice::SetLostWeight(double lostWeight)
{
	this->lostWeight = lostWeight;
}

int Vertice::GetVerticeNumber()
{
	return verticeNumber;
}

int Vertice::GetFirstMinVertice()
{
	return firstMinVertice;
}

void Vertice::SetFirstMinVertice(int firstMinVertice)
{
	this->firstMinVertice = firstMinVertice;
}

int Vertice::GetSecondMinVertice()
{
	return secondMinVertice;
}

void Vertice::SetSecondMinVertice(int secondMinVertice)
{
	this->secondMinVertice = secondMinVertice;
}

double Vertice::GetFirstMinVerticeWeight()
{
	return firstMinVerticeWeight;
}

void Vertice::SetFirstMinVerticeWeight(double firstMinVerticeWeight)
{
	this->firstMinVerticeWeight = firstMinVerticeWeight;
}
double Vertice::GetSecondMinVerticeWeight()
{
	return secondMinVerticeWeight;
}

void Vertice::SetSecondMinVerticeWeight(double secondMinVerticeWeight)
{
	this->secondMinVerticeWeight = secondMinVerticeWeight;
}
