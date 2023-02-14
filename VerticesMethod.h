#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <ctime>
#include "Edge.h"
#include "Vertice.h"

class VerticesMethod {
public:
	VerticesMethod(int pointsAmount);
	// ABILITIES
	void FindWay();
	void BroodForceMethod();
	// GET SET 
	int GetPointsAmounts();
	std::vector<std::vector<Edge>> GetEdges();
	// ANOTHER
	void PrintEdgeMatrix();
	void PrintBroodForceMethodWay();
private:
	int pointsAmount;
	std::vector<std::vector<Edge>> edges;
	std::vector<int> shortWay;
	double minWeight;
	
	void GenerateEdgeMatrix();
	void BroodForceMethodRecursion(std::vector<int> wayM, int counterM, double sumWeightM, int lastPoint, std::vector<bool> checkedPointsM);
	bool IsEquals(int oneNumber, int twoNumber);
	bool IsMore(int oneNumber, int twoNumber);
	enum class EdgeState {
		RIGHT,
		NEUTRAL,
		WRONG
	};
	void TriangleRecursion(std::vector<Edge>& minWayR, double minWayWeightR, int rightVerticesAmountR, std::vector<bool>& verticesStatesR);

};