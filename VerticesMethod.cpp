#include "VerticesMethod.h"
#include <string>
#define DEBUG3

VerticesMethod::VerticesMethod(int pointsAmount)
{
	//srand(time(NULL));
	this->pointsAmount = pointsAmount;
	minWeight = 10000000.0;
	GenerateEdgeMatrix();
	PrintEdgeMatrix();
	FindWay();
	BroodForceMethod();
}

void VerticesMethod::FindWay()
{
#ifdef DEBUG3
	// Создание списка рёбер 
	std::vector<Edge> way;
	way.reserve(pointsAmount);
	// Добавление в список три первые ребра
	way.push_back(Edge(0, 1, edges[0][1].GetWeight()));
	way.push_back(Edge(1, 2, edges[1][2].GetWeight()));
	way.push_back(Edge(2, 0, edges[2][0].GetWeight()));
	int rightVerticesAmount = 3;
	std::vector<bool> verticesStates(pointsAmount, false);
	verticesStates[0] = true;
	verticesStates[1] = true;
	verticesStates[2] = true;
	// Минимальный путь
	std::vector<Edge> minWay;
	double minWayWeight = 0.0;
	// Создаём рекурсию поиска новых рёбер
	TriangleRecursion(way, minWayWeight, rightVerticesAmount, verticesStates);
	std::cout << minWay[0].GetWeight() << std::endl;
#endif
}

void VerticesMethod::BroodForceMethod()
{
	for (int i = 0; i < pointsAmount; ++i) {
		int counter = 0;
		double sumWeight = 0;
		std::vector<int> way;
		way.push_back(i);
		std::vector<bool> checkedPoints;
		checkedPoints.resize(pointsAmount);
		checkedPoints[i] = true;
		BroodForceMethodRecursion(way, counter, sumWeight, i, checkedPoints);
	}
}

int VerticesMethod::GetPointsAmounts()
{
	return pointsAmount;
}

std::vector<std::vector<Edge>> VerticesMethod::GetEdges()
{
	return edges;
}

void VerticesMethod::PrintEdgeMatrix()
{
	for (int i = 0; i < pointsAmount; ++i) {
		for (int j = 0; j < pointsAmount; ++j) {
			std::cout << edges[i][j].GetWeight()<< "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void VerticesMethod::PrintBroodForceMethodWay()
{
	for (auto point : shortWay) {
		std::cout << point << "\t";
	}
	std::cout << "Weight - " << minWeight << std::endl;
}

void VerticesMethod::GenerateEdgeMatrix()
{
	edges.reserve(pointsAmount);
	for (int i = 0; i < pointsAmount; ++i) {
		std::vector<Edge> insideEdgeVector;
		insideEdgeVector.reserve(pointsAmount);
		for (int j = 0; j < pointsAmount; j++) {
			if (!IsEquals(i, j)) {
				double weight = rand() / 10.0;
				if (!IsMore(i, j)) {
					insideEdgeVector.push_back(Edge(i, j, weight));
				} 
				else {
					insideEdgeVector.push_back(Edge(j, i, edges[j][i].GetWeight()));
				}
			}
			else
			{
				insideEdgeVector.push_back(Edge(i, j, 0.0));
			}
		}
		edges.push_back(insideEdgeVector);
	}
}

void VerticesMethod::BroodForceMethodRecursion(std::vector<int> wayM, int counterM, double sumWeightM, int lastPoint, std::vector<bool> checkedPointsM)
{
	for (int i = 0; i < pointsAmount; i++) {
		int counter = counterM + 1;
		double sumWeight = sumWeightM;
		std::vector<int> way = wayM;
		std::vector<bool> checkedPoints = checkedPointsM;
		if (edges[lastPoint][i].GetWeight() != 0) {
			if (counter < pointsAmount - 1 && !checkedPoints[i]) {
				sumWeight += edges[lastPoint][i].GetWeight();
				way.push_back(i);
				checkedPoints[i] = true;
				BroodForceMethodRecursion(way, counter, sumWeight, i, checkedPoints);
			}
			else if (counter == pointsAmount - 1 && !checkedPoints[i]) {
				sumWeight += edges[i][lastPoint].GetWeight();
				sumWeight += edges[way[0]][i].GetWeight();
				way.push_back(i);
				if (sumWeight < minWeight) {
					shortWay = way;
					minWeight = sumWeight;
				}
			}
		}
	}
}

bool VerticesMethod::IsEquals(int oneNumber, int twoNumber)
{
	return oneNumber == twoNumber ? true : false;
}

bool VerticesMethod::IsMore(int oneNumber, int twoNumber)
{
	return oneNumber > twoNumber ? true : false;
}

void VerticesMethod::TriangleRecursion(std::vector<Edge>& minWay, double minWayWeight, int rightVerticesAmount, std::vector<bool>& verticesStates)
{
	if (rightVerticesAmount != pointsAmount) {
		double oneCheckWeightSum = 0.0;
		int oneNewVertice = 0;
		Edge oneOldEdge;
		int oneNumberOldEdge = 0;
		for (int j = 0; j < minWay.size(); ++j) {
			double startWeightsSum = minWayWeight - minWay[j].GetWeight();
			double twoCheckWeightSum = 0.0;
			int twoNewVertice = 0;
			Edge twoOldEdge = minWay[j];
			int twoNumberOldEdge = j;
			for (int i = 0; i < pointsAmount; ++i) {
				if (!verticesStates[i]) {
					double findWeightSum = edges[minWay[j].GetFirstPoint()][i].GetWeight() + edges[minWay[j].GetSecondPoint()][i].GetWeight() + startWeightsSum;
					if (twoCheckWeightSum == 0) {
						twoCheckWeightSum = findWeightSum;
						twoNewVertice = i;
					}
					else if (findWeightSum < twoCheckWeightSum) {
						twoCheckWeightSum = findWeightSum;
						twoNewVertice = i;
					}
				}
			}
			if (oneCheckWeightSum == 0) {
				oneCheckWeightSum = twoCheckWeightSum;
				oneNewVertice = twoNewVertice;
				oneOldEdge = twoOldEdge;
				oneNumberOldEdge = twoNumberOldEdge;
			}
			else if (oneCheckWeightSum > twoCheckWeightSum) {
				oneCheckWeightSum = twoCheckWeightSum;
				oneNewVertice = twoNewVertice;
				oneOldEdge = twoOldEdge;
				oneNumberOldEdge = twoNumberOldEdge;
			}
		}
		// Осталось удалить старое ребро, добавить два новых и опять вызвать TriangleRecursion передав в неё все нужные параметры
		minWayWeight -= oneOldEdge.GetWeight();
		rightVerticesAmount--;
		std::vector<Edge>::iterator itMinWay = minWay.begin();
		minWay.erase(itMinWay + oneNumberOldEdge - 1);
		minWay.push_back(Edge(oneOldEdge.GetFirstPoint(), oneNewVertice, edges[oneOldEdge.GetFirstPoint()][oneNewVertice].GetWeight()));
		minWayWeight += edges[oneOldEdge.GetFirstPoint()][oneNewVertice].GetWeight();
		rightVerticesAmount++;
		minWay.push_back(Edge(oneOldEdge.GetSecondPoint(), oneNewVertice, edges[oneOldEdge.GetSecondPoint()][oneNewVertice].GetWeight()));
		minWayWeight += edges[oneOldEdge.GetSecondPoint()][oneNewVertice].GetWeight();
		rightVerticesAmount++;

		verticesStates[oneNewVertice] = true;
		
		TriangleRecursion(minWay, minWayWeight, rightVerticesAmount, verticesStates);
	}
}
