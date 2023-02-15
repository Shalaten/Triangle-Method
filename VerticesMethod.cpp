#include "VerticesMethod.h"
#include <string>
#define DEBUG3
//#define DEBUG

VerticesMethod::VerticesMethod(int pointsAmount)
{
	srand(time(NULL));
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
	std::vector<Edge> minWayTrue;
	minWayTrue.reserve(pointsAmount);
	double minWayWeightTrue = 0.0;

	for (int oneV = 0; oneV < pointsAmount; ++oneV) {
		for (int twoV = 0; twoV < pointsAmount; ++twoV) {
			if (!IsEquals(oneV, twoV)) {
				for (int threeV = 0; threeV < pointsAmount; ++threeV) {
					if (!IsEquals(oneV, threeV) && !IsEquals(twoV, threeV)) {
						// Создание списка рёбер 
						std::vector<Edge> minWay;
						minWay.reserve(pointsAmount);
						// Добавление в список три первые ребра
						minWay.push_back(Edge(oneV, twoV, edges[oneV][twoV].GetWeight()));
						minWay.push_back(Edge(twoV, threeV, edges[twoV][threeV].GetWeight()));
						minWay.push_back(Edge(threeV, oneV, edges[threeV][oneV].GetWeight()));
						// Количество использованых вершин
						int rightVerticesAmount = 3;
						//  Список рёбер которые были использованы
						std::vector<bool> verticesStates(pointsAmount, false);
						verticesStates[oneV] = true;
						verticesStates[twoV] = true;
						verticesStates[threeV] = true;
						// Минимальный вес пути
						double minWayWeight = edges[oneV][twoV].GetWeight() + edges[twoV][threeV].GetWeight() + edges[threeV][oneV].GetWeight();
						// Создаём рекурсию поиска новых рёбер
						while (rightVerticesAmount != pointsAmount) {
							double newVerticeWeightSum = 0.0;
							int newVertice = 0;
							Edge selectedEdge;
							int selectedEdgeNumber = 0;
							for (int j = 0; j < minWay.size(); ++j) {
								double startWeightsSum = minWayWeight - minWay[j].GetWeight();
								double potentialWeightSum = 0.0;
								int potentialNewVertice = 0;
								Edge potentialSelectedEdge = minWay[j];
								int potentialSelectedEdgeNumber = j;
								for (int i = 0; i < pointsAmount; ++i) {
									if (!verticesStates[i]) {
										double findWeightSum = edges[minWay[j].GetFirstPoint()][i].GetWeight() + edges[minWay[j].GetSecondPoint()][i].GetWeight() + startWeightsSum;
										if (potentialWeightSum == 0) {
											potentialWeightSum = findWeightSum;
											potentialNewVertice = i;
										}
										else if (findWeightSum < potentialWeightSum) {
											potentialWeightSum = findWeightSum;
											potentialNewVertice = i;
										}
									}
								}
								if (newVerticeWeightSum == 0) {
									newVerticeWeightSum = potentialWeightSum;
									newVertice = potentialNewVertice;
									selectedEdge = potentialSelectedEdge;
									selectedEdgeNumber = potentialSelectedEdgeNumber;
								}
								else if (newVerticeWeightSum > potentialWeightSum) {
									newVerticeWeightSum = potentialWeightSum;
									newVertice = potentialNewVertice;
									selectedEdge = potentialSelectedEdge;
									selectedEdgeNumber = potentialSelectedEdgeNumber;
								}
							}
							// Осталось удалить старое ребро, добавить два новых и опять вызвать TriangleRecursion передав в неё все нужные параметры
							minWayWeight -= selectedEdge.GetWeight();
							rightVerticesAmount--;
							std::vector<Edge>::iterator itMinWay = minWay.begin();
							minWay.erase(itMinWay + selectedEdgeNumber);
							minWay.push_back(Edge(selectedEdge.GetFirstPoint(), newVertice, edges[selectedEdge.GetFirstPoint()][newVertice].GetWeight()));
							minWayWeight += edges[selectedEdge.GetFirstPoint()][newVertice].GetWeight();
							rightVerticesAmount++;
							minWay.push_back(Edge(selectedEdge.GetSecondPoint(), newVertice, edges[selectedEdge.GetSecondPoint()][newVertice].GetWeight()));
							minWayWeight += edges[selectedEdge.GetSecondPoint()][newVertice].GetWeight();
							rightVerticesAmount++;

							verticesStates[newVertice] = true;
						}
						/////////////////////////////////////////////////
						if (minWayWeightTrue == 0) {
							minWayWeightTrue = minWayWeight;
							minWayTrue = minWay;
						}
						else if (minWayWeightTrue > minWayWeight) {
							minWayWeightTrue = minWayWeight;
							minWayTrue = minWay;
						}
					}
				}
			}
		}
	}

	std::cout << "Triangle Method" << std::endl;
	for (auto weightS : minWayTrue) {
		std::cout << weightS.GetFirstPoint() << " - " << weightS.GetSecondPoint() << "\t";
	}
	std::cout << minWayWeightTrue << std::endl;
#endif
#ifdef DEBUG
#pragma region MyRegion
	// Создание списка рёбер 
	std::vector<Edge> minWay;
	minWay.reserve(pointsAmount);
	// Добавление в список три первые ребра
	minWay.push_back(Edge(0, 1, edges[0][1].GetWeight()));
	minWay.push_back(Edge(1, 2, edges[1][2].GetWeight()));
	minWay.push_back(Edge(2, 0, edges[2][0].GetWeight()));
	// Количество использованых вершин
	int rightVerticesAmount = 3;
	//  Список рёбер которые были использованы
	std::vector<bool> verticesStates(pointsAmount, false);
	verticesStates[0] = true;
	verticesStates[1] = true;
	verticesStates[2] = true;
	// Минимальный вес пути
	double minWayWeight = edges[0][1].GetWeight() + edges[1][2].GetWeight() + edges[2][0].GetWeight();
	// Создаём рекурсию поиска новых рёбер
	while (rightVerticesAmount != pointsAmount) {
		double newVerticeWeightSum = 0.0;
		int newVertice = 0;
		Edge selectedEdge;
		int selectedEdgeNumber = 0;
		for (int j = 0; j < minWay.size(); ++j) {
			double startWeightsSum = minWayWeight - minWay[j].GetWeight();
			double potentialWeightSum = 0.0;
			int potentialNewVertice = 0;
			Edge potentialSelectedEdge = minWay[j];
			int potentialSelectedEdgeNumber = j;
			for (int i = 0; i < pointsAmount; ++i) {
				if (!verticesStates[i]) {
					double findWeightSum = edges[minWay[j].GetFirstPoint()][i].GetWeight() + edges[minWay[j].GetSecondPoint()][i].GetWeight() + startWeightsSum;
					if (potentialWeightSum == 0) {
						potentialWeightSum = findWeightSum;
						potentialNewVertice = i;
					}
					else if (findWeightSum < potentialWeightSum) {
						potentialWeightSum = findWeightSum;
						potentialNewVertice = i;
					}
				}
			}
			if (newVerticeWeightSum == 0) {
				newVerticeWeightSum = potentialWeightSum;
				newVertice = potentialNewVertice;
				selectedEdge = potentialSelectedEdge;
				selectedEdgeNumber = potentialSelectedEdgeNumber;
			}
			else if (newVerticeWeightSum > potentialWeightSum) {
				newVerticeWeightSum = potentialWeightSum;
				newVertice = potentialNewVertice;
				selectedEdge = potentialSelectedEdge;
				selectedEdgeNumber = potentialSelectedEdgeNumber;
			}
		}
		// Осталось удалить старое ребро, добавить два новых и опять вызвать TriangleRecursion передав в неё все нужные параметры
		minWayWeight -= selectedEdge.GetWeight();
		rightVerticesAmount--;
		std::vector<Edge>::iterator itMinWay = minWay.begin();
		minWay.erase(itMinWay + selectedEdgeNumber);
		minWay.push_back(Edge(selectedEdge.GetFirstPoint(), newVertice, edges[selectedEdge.GetFirstPoint()][newVertice].GetWeight()));
		minWayWeight += edges[selectedEdge.GetFirstPoint()][newVertice].GetWeight();
		rightVerticesAmount++;
		minWay.push_back(Edge(selectedEdge.GetSecondPoint(), newVertice, edges[selectedEdge.GetSecondPoint()][newVertice].GetWeight()));
		minWayWeight += edges[selectedEdge.GetSecondPoint()][newVertice].GetWeight();
		rightVerticesAmount++;

		verticesStates[newVertice] = true;
	}
#pragma endregion



	for (auto weightS : minWay) {
		std::cout << weightS.GetFirstPoint() << " - " << weightS.GetSecondPoint() << "\t";
	}
	std::cout << minWayWeight << std::endl;
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

void VerticesMethod::TriangleRecursion(std::vector<Edge>& minWayR, double minWayWeightR, int rightVerticesAmountR, std::vector<bool>& verticesStatesR)
{
	if (rightVerticesAmountR != pointsAmount) {
		double oneCheckWeightSum = 0.0;
		int oneNewVertice = 0;
		Edge oneOldEdge;
		int oneNumberOldEdge = 0;
		for (int j = 0; j < minWayR.size(); ++j) {
			double startWeightsSum = minWayWeightR - minWayR[j].GetWeight();
			double twoCheckWeightSum = 0.0;
			int twoNewVertice = 0;
			Edge twoOldEdge = minWayR[j];
			int twoNumberOldEdge = j;
			for (int i = 0; i < pointsAmount; ++i) {
				if (!verticesStatesR[i]) {
					double findWeightSum = edges[minWayR[j].GetFirstPoint()][i].GetWeight() + edges[minWayR[j].GetSecondPoint()][i].GetWeight() + startWeightsSum;
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
		minWayWeightR -= oneOldEdge.GetWeight();
		rightVerticesAmountR--;
		std::vector<Edge>::iterator itMinWay = minWayR.begin();
		minWayR.erase(itMinWay + oneNumberOldEdge - 1);
		minWayR.push_back(Edge(oneOldEdge.GetFirstPoint(), oneNewVertice, edges[oneOldEdge.GetFirstPoint()][oneNewVertice].GetWeight()));
		minWayWeightR += edges[oneOldEdge.GetFirstPoint()][oneNewVertice].GetWeight();
		rightVerticesAmountR++;
		minWayR.push_back(Edge(oneOldEdge.GetSecondPoint(), oneNewVertice, edges[oneOldEdge.GetSecondPoint()][oneNewVertice].GetWeight()));
		minWayWeightR += edges[oneOldEdge.GetSecondPoint()][oneNewVertice].GetWeight();
		rightVerticesAmountR++;

		verticesStatesR[oneNewVertice] = true;
		
		TriangleRecursion(minWayR, minWayWeightR, rightVerticesAmountR, verticesStatesR);
	}
}
