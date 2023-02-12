#include "VerticesMethod.h"
#include <string>
//#define DEBUG 
//#define DEBUG2
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
	// Матрица состояний рёбер
	std::vector<std::vector<EdgeState>> stateOfEdges;
	stateOfEdges.reserve(pointsAmount);
	for (int i = 0; i < pointsAmount; ++i) {
		std::vector<EdgeState> insideVector;
		insideVector.resize(pointsAmount, EdgeState::NEUTRAL);
		stateOfEdges.push_back(insideVector);
	}
	// Удаление самовходящих рёбер
	for (int i = 0; i < pointsAmount; ++i) {
		stateOfEdges[i][i] = EdgeState::WRONG;
	}
	// Поиск треугольника с минимальным весом
	std::vector<int> triangle(4);
	double triangleWeight = 0.0;
	for (int one = 0; one < pointsAmount; ++one) {
		for (int two = 0; two < pointsAmount; ++two) {
			if (!IsEquals(one, two)) {
				for (int three = 0; three < pointsAmount; ++three) {
					if (!IsEquals(three, one) && !IsEquals(three, two)) {
						double sumOfWeights = edges[one][two].GetWeight() + edges[two][three].GetWeight() + edges[three][one].GetWeight();
						if (triangleWeight == 0 || triangleWeight > sumOfWeights) {
							triangleWeight = sumOfWeights;
							triangle[0] = one;
							triangle[1] = two;
							triangle[2] = three;
							triangle[3] = one;
							/*triangle[0].SetFirstPoint(one);
							triangle[0].SetSecondPoint(two);
							triangle[0].SetWeight(edges[one][two].GetWeight());
							triangle[1].SetFirstPoint(two);
							triangle[1].SetSecondPoint(three);
							triangle[1].SetWeight(edges[two][three].GetWeight());
							triangle[2].SetFirstPoint(three);
							triangle[2].SetSecondPoint(one);
							triangle[2].SetWeight(edges[three][one].GetWeight());*/
						}
					}
				}
			}
		}
	}
	///////////////////////////////
	std::cout << "One - " << triangle[0] << "\t" << "Two - " << triangle[1] << "\t" << "Three - " << triangle[2] << "\t" << "Weight - " << triangleWeight << std::endl;
	///////////////////////////////
	for (int one = 0, two = 1; one < 3; ++one, ++two) {
		std::vector<Edge> way;
		double wayWeight = triangleWeight;
		// Создание массива состояний вершин
		std::vector<bool> verticesState(pointsAmount, false);
		// Количество правильных вершин
		int rightVerticesAmount = 0;
		way.reserve(pointsAmount);
		// Add two start edges
		for (int oneT = 0, twoT = 1; oneT < 3; ++oneT, ++twoT) {
			if (!IsEquals(oneT, one)) {
				way.push_back(Edge(triangle[oneT], triangle[twoT], edges[triangle[oneT]][triangle[twoT]].GetWeight()));
			}
			verticesState[triangle[oneT]] = true;
			rightVerticesAmount++;
		}
		///////////////////////////
		for (auto edge : way) {
			std::cout << edge.GetFirstPoint() << " - " << edge.GetSecondPoint() << " = " << edge.GetWeight() << "\t";
		}
		std::cout << std::endl;
		///////////////////////////
		// Поиск новой правильной вершины

		triangleRecursion(triangle[one], triangle[two], verticesState, rightVerticesAmount, way);
	}

#endif

#ifdef DEBUG
	std::vector<Vertice> vertices;
	vertices.reserve(pointsAmount);
	for (int i = 0; i < pointsAmount; ++i) {
		vertices.push_back(Vertice(i));
	}

	for (int i = 0; i < pointsAmount; ++i) {
		double edgesSum = 0.0;
		for (int j = 0; j < pointsAmount; ++j) {
			if (edges[i][j].GetWeight() < vertices[i].GetFirstMinVerticeWeight() && !IsEquals(i, j)) {
				if (vertices[i].GetFirstMinVerticeWeight() < vertices[i].GetSecondMinVerticeWeight()) {
					vertices[i].SetSecondMinVerticeWeight(vertices[i].GetFirstMinVerticeWeight());
					vertices[i].SetSecondMinVertice(vertices[i].GetFirstMinVertice());
				}
				vertices[i].SetFirstMinVerticeWeight(edges[i][j].GetWeight());
				vertices[i].SetFirstMinVertice(j);
			}
			else if (edges[i][j].GetWeight() < vertices[i].GetSecondMinVerticeWeight() && !IsEquals(i, j)) {
				if (vertices[i].GetSecondMinVerticeWeight() < vertices[i].GetFirstMinVerticeWeight()) {
					vertices[i].SetFirstMinVerticeWeight(vertices[i].GetSecondMinVerticeWeight());
					vertices[i].SetFirstMinVertice(vertices[i].GetSecondMinVertice());
				}
				vertices[i].SetSecondMinVerticeWeight(edges[i][j].GetWeight());
				vertices[i].SetSecondMinVertice(j);
			}
			edgesSum += edges[i][j].GetWeight();
		}
		vertices[i].SetLostWeight(edgesSum + edges[vertices[i].GetSecondMinVertice()][vertices[i].GetFirstMinVertice()].GetWeight() - ((vertices[i].GetSecondMinVerticeWeight() + vertices[i].GetFirstMinVerticeWeight()) * 2));
	}
		for (int v = 0; v < pointsAmount; ++v) {

			std::vector<std::vector<EdgeState>> stateOfEdges;
			stateOfEdges.reserve(pointsAmount);
			for (int i = 0; i < pointsAmount; ++i) {
				std::vector<EdgeState> insideVector;
				insideVector.resize(pointsAmount, EdgeState::NEUTRAL);
				stateOfEdges.push_back(insideVector);
			}

			int firstRightVertice = v;

			// Этап заполнения таблицы состояний рёбер и состояний рёбер после нахождения первой правильной вершины
			for (int i = 0; i < pointsAmount; ++i) {
				stateOfEdges[i][i] = EdgeState::WRONG;
			}
			for (int i = 0; i < pointsAmount; ++i) {
				if (vertices[firstRightVertice].GetFirstMinVertice() != i && vertices[firstRightVertice].GetSecondMinVertice() != i) {
					stateOfEdges[firstRightVertice][i] = EdgeState::WRONG;
					stateOfEdges[i][firstRightVertice] = EdgeState::WRONG;
				}
				else {
					stateOfEdges[firstRightVertice][i] = EdgeState::RIGHT;
					stateOfEdges[i][firstRightVertice] = EdgeState::RIGHT;
				}
			}
			stateOfEdges[vertices[firstRightVertice].GetFirstMinVertice()][vertices[firstRightVertice].GetSecondMinVertice()] = EdgeState::WRONG;
			stateOfEdges[vertices[firstRightVertice].GetSecondMinVertice()][vertices[firstRightVertice].GetFirstMinVertice()] = EdgeState::WRONG;


			// Этап поиска всех оставшихся правильных рёбер
			int oneVertice = vertices[firstRightVertice].GetFirstMinVertice();
			int twoVertice = vertices[firstRightVertice].GetSecondMinVertice();
			std::cout << "               ЭТАП   -    " << v << std::endl;
			std::cout << "firstRightVertice - " << firstRightVertice << std::endl;
			std::cout << "oneVertice - " << oneVertice << "\t" << "twoVertice - " << twoVertice << std::endl;
			for (int i = 0; i < pointsAmount - 3; ++i) {
				double oneWeightSum = 0.0;
				int oneMinVertice = 0;
				double oneMinWeight = 100000.0;
				for (int j = 0; j < pointsAmount; ++j) {
					if (stateOfEdges[oneVertice][j] == EdgeState::NEUTRAL) {
						oneWeightSum += edges[oneVertice][j].GetWeight();
						if (edges[oneVertice][j].GetWeight() < oneMinWeight) {
							oneMinVertice = j;
							oneMinWeight = edges[oneVertice][j].GetWeight();
						}
					}
				}
				oneWeightSum -= oneMinWeight * 2;
				//--------------------------------------------------------------
				double twoWeightSum = 0.0;
				int twoMinVertice = 0;
				double twoMinWeight = 100000.0;
				for (int j = 0; j < pointsAmount; ++j) {
					if (stateOfEdges[twoVertice][j] == EdgeState::NEUTRAL) {
						twoWeightSum += edges[twoVertice][j].GetWeight();
						if (edges[twoVertice][j].GetWeight() < twoMinWeight) {
							twoMinVertice = j;
							twoMinWeight = edges[twoVertice][j].GetWeight();
						}
					}
				}
				twoWeightSum -= twoMinWeight * 2;



				////////////////////////////////////////////////////////////////


				// Этап преобразования ненужных NEUTRAL зарядов в WRONG заряды
				if (oneWeightSum > twoWeightSum) {
					stateOfEdges[oneVertice][oneMinVertice] = EdgeState::RIGHT;
					stateOfEdges[oneMinVertice][oneVertice] = EdgeState::RIGHT;
					for (int j = 0; j < pointsAmount; ++j) {
						if (stateOfEdges[oneVertice][j] == EdgeState::NEUTRAL) {
							stateOfEdges[oneVertice][j] = EdgeState::WRONG;
							stateOfEdges[j][oneVertice] = EdgeState::WRONG;
						}
					}
					oneVertice = oneMinVertice;
				}
				else {
					stateOfEdges[twoVertice][twoMinVertice] = EdgeState::RIGHT;
					stateOfEdges[twoMinVertice][twoVertice] = EdgeState::RIGHT;
					for (int j = 0; j < pointsAmount; ++j) {
						if (stateOfEdges[twoVertice][j] == EdgeState::NEUTRAL) {
							stateOfEdges[twoVertice][j] = EdgeState::WRONG;
							stateOfEdges[j][twoVertice] = EdgeState::WRONG;
						}
					}
					twoVertice = twoMinVertice;
				}
				stateOfEdges[oneVertice][twoVertice] = EdgeState::WRONG;
				stateOfEdges[twoVertice][oneVertice] = EdgeState::WRONG;
			}
			stateOfEdges[oneVertice][twoVertice] = EdgeState::RIGHT;
			stateOfEdges[twoVertice][oneVertice] = EdgeState::RIGHT;


			double sum = 0.0;
			for (int i = 0; i < pointsAmount; ++i) {
				for (int j = i + 1; j < pointsAmount; ++j) {
					if (stateOfEdges[i][j] == EdgeState::RIGHT) {
						sum += edges[i][j].GetWeight();
						std::cout << i << " - " << j << "\t";
					}
				}
			}
			std::cout << "WEIGHT - " << sum << std::endl;
		}
	
#endif
#ifdef DEBUG2
	std::vector<std::vector<EdgeState>> stateOfEdges;
	stateOfEdges.reserve(pointsAmount);
	for (int i = 0; i < pointsAmount; ++i) {
		std::vector<EdgeState> insideVector;
		insideVector.resize(pointsAmount, EdgeState::NEUTRAL);
		stateOfEdges.push_back(insideVector);
	}

	std::vector<Vertice> vertices;
	vertices.reserve(pointsAmount);
	for (int i = 0; i < pointsAmount; ++i) {
		vertices.push_back(Vertice(i));
	}

	for (int i = 0; i < pointsAmount; ++i) {
		double edgesSum = 0.0;
		for (int j = 0; j < pointsAmount; ++j) {
			if (edges[i][j].GetWeight() < vertices[i].GetFirstMinVerticeWeight() && !IsEquals(i, j)) {
				if (vertices[i].GetFirstMinVerticeWeight() < vertices[i].GetSecondMinVerticeWeight()) {
					vertices[i].SetSecondMinVerticeWeight(vertices[i].GetFirstMinVerticeWeight());
					vertices[i].SetSecondMinVertice(vertices[i].GetFirstMinVertice());
				}
				vertices[i].SetFirstMinVerticeWeight(edges[i][j].GetWeight());
				vertices[i].SetFirstMinVertice(j);
			}
			else if (edges[i][j].GetWeight() < vertices[i].GetSecondMinVerticeWeight() && !IsEquals(i, j)) {
				if (vertices[i].GetSecondMinVerticeWeight() < vertices[i].GetFirstMinVerticeWeight()) {
					vertices[i].SetFirstMinVerticeWeight(vertices[i].GetSecondMinVerticeWeight());
					vertices[i].SetFirstMinVertice(vertices[i].GetSecondMinVertice());
				}
				vertices[i].SetSecondMinVerticeWeight(edges[i][j].GetWeight());
				vertices[i].SetSecondMinVertice(j);
			}
			edgesSum += edges[i][j].GetWeight();
		}
		vertices[i].SetLostWeight(edgesSum + edges[vertices[i].GetSecondMinVertice()][vertices[i].GetFirstMinVertice()].GetWeight() - ((vertices[i].GetSecondMinVerticeWeight() + vertices[i].GetFirstMinVerticeWeight()) * 2));
	}

	int firstRightVertice = 0;
	double firstRightVerticeLostWeight = 0.0;
	for (int i = 0; i < pointsAmount; ++i) {
		if (vertices[i].GetLostWeight() > firstRightVerticeLostWeight) {
			if ((vertices[vertices[i].GetFirstMinVertice()].GetFirstMinVertice() == vertices[i].GetVerticeNumber()
				|| vertices[vertices[i].GetFirstMinVertice()].GetSecondMinVertice() == vertices[i].GetVerticeNumber())
					&& (vertices[vertices[i].GetSecondMinVertice()].GetFirstMinVertice() == vertices[i].GetVerticeNumber()
						|| vertices[vertices[i].GetSecondMinVertice()].GetSecondMinVertice() == vertices[i].GetVerticeNumber())) {
				firstRightVertice = vertices[i].GetVerticeNumber();
				firstRightVerticeLostWeight = vertices[i].GetLostWeight();
			}
		}
	}

	// Этап заполнения таблицы состояний рёбер и состояний рёбер после нахождения первой правильной вершины
	for (int i = 0; i < pointsAmount; ++i) {
		stateOfEdges[i][i] = EdgeState::WRONG;
	}
	for (int i = 0; i < pointsAmount; ++i) {
		if (vertices[firstRightVertice].GetFirstMinVertice() != i && vertices[firstRightVertice].GetSecondMinVertice() != i) {
			stateOfEdges[firstRightVertice][i] = EdgeState::WRONG;
			stateOfEdges[i][firstRightVertice] = EdgeState::WRONG;
		}
		else {
			stateOfEdges[firstRightVertice][i] = EdgeState::RIGHT;
			stateOfEdges[i][firstRightVertice] = EdgeState::RIGHT;
		}
	}
	stateOfEdges[vertices[firstRightVertice].GetFirstMinVertice()][vertices[firstRightVertice].GetSecondMinVertice()] = EdgeState::WRONG;
	stateOfEdges[vertices[firstRightVertice].GetSecondMinVertice()][vertices[firstRightVertice].GetFirstMinVertice()] = EdgeState::WRONG;


	/////////////////////////////////////////////////////////////////////
	for (int i = 0; i < pointsAmount; ++i) {
		for (int j = 0; j < pointsAmount; ++j) {
			if (stateOfEdges[i][j] == EdgeState::NEUTRAL)
				std::cout << 0 << "\t";
			if (stateOfEdges[i][j] == EdgeState::WRONG)
				std::cout << "-" << "\t";                              // Вывод таблицы  
			if (stateOfEdges[i][j] == EdgeState::RIGHT)
				std::cout << "+" << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	/////////////////////////////////////////////////////////////////////


	std::cout << "firstRightVertice - " << firstRightVertice << std::endl;
	// Этап поиска всех оставшихся правильных рёбер
	int oneVertice = vertices[firstRightVertice].GetFirstMinVertice();
	int twoVertice = vertices[firstRightVertice].GetSecondMinVertice();
	for (int i = 0; i < pointsAmount - 3; ++i) {
		std::cout << std::endl;
		std::cout << "               ЭТАП   -    " << i << std::endl;
		std::cout << "oneMinVertice - " << oneVertice << "\t" << "twoMinVertice - " << twoVertice << std::endl;
		double oneWeightSum = 0.0;
		int oneMinVertice = 0;
		double oneMinWeight = 100000.0;
		for (int j = 0; j < pointsAmount; ++j) {
			if (stateOfEdges[oneVertice][j] == EdgeState::NEUTRAL) {
				oneWeightSum += edges[oneVertice][j].GetWeight();
				if (edges[oneVertice][j].GetWeight() < oneMinWeight) {
					oneMinVertice = j;
					oneMinWeight = edges[oneVertice][j].GetWeight();
				}
			}
		}
		oneWeightSum -= oneMinWeight * 2;
		std::cout << "oneVertice - " << oneMinVertice << "\t";
		//--------------------------------------------------------------
		double twoWeightSum = 0.0;
		int twoMinVertice = 0;
		double twoMinWeight = 100000.0;
		for (int j = 0; j < pointsAmount; ++j) {
			if (stateOfEdges[twoVertice][j] == EdgeState::NEUTRAL) {
				twoWeightSum += edges[twoVertice][j].GetWeight();
				if (edges[twoVertice][j].GetWeight() < twoMinWeight) {
					twoMinVertice = j;
					twoMinWeight = edges[twoVertice][j].GetWeight();
				}
			}
		}
		twoWeightSum -= twoMinWeight * 2;
		std::cout << "twoVertice - " << twoMinVertice << std::endl;
		std::cout << std::endl;



		////////////////////////////////////////////////////////////////


		// Этап преобразования ненужных NEUTRAL зарядов в WRONG заряды
		if (oneWeightSum > twoWeightSum) {
			std::cout << "Откуда - " << oneVertice << "куда - " << oneMinVertice << std::endl;
			std::cout << "oneWeightSum - " << oneWeightSum << "twoWeightSum - " << twoWeightSum << std::endl;
			std::cout << std::endl;
			stateOfEdges[oneVertice][oneMinVertice] = EdgeState::RIGHT;
			stateOfEdges[oneMinVertice][oneVertice] = EdgeState::RIGHT;
			for (int j = 0; j < pointsAmount; ++j) {
				if (stateOfEdges[oneVertice][j] == EdgeState::NEUTRAL) {
					stateOfEdges[oneVertice][j] = EdgeState::WRONG;
					stateOfEdges[j][oneVertice] = EdgeState::WRONG;
				}
			}
			oneVertice = oneMinVertice;
		}
		else {
			std::cout << "Откуда - " << twoVertice << "куда - " << twoMinVertice << std::endl;
			std::cout << "twoWeightSum - " << twoWeightSum << "oneWeightSum - " << oneWeightSum << std::endl;
			std::cout << std::endl;
			stateOfEdges[twoVertice][twoMinVertice] = EdgeState::RIGHT;
			stateOfEdges[twoMinVertice][twoVertice] = EdgeState::RIGHT;
			for (int j = 0; j < pointsAmount; ++j) {
				if (stateOfEdges[twoVertice][j] == EdgeState::NEUTRAL) {
					stateOfEdges[twoVertice][j] = EdgeState::WRONG;
					stateOfEdges[j][twoVertice] = EdgeState::WRONG;
				}
			}
			twoVertice = twoMinVertice;
		}
		stateOfEdges[oneVertice][twoVertice] = EdgeState::WRONG;
		stateOfEdges[twoVertice][oneVertice] = EdgeState::WRONG;
		/////////////////////////////////////////////////////////////////////
		for (int h = 0; h < pointsAmount; ++h) {
			for (int j = 0; j < pointsAmount; ++j) {
				if (stateOfEdges[h][j] == EdgeState::NEUTRAL)
					std::cout << 0 << "\t";
				if (stateOfEdges[h][j] == EdgeState::WRONG)
					std::cout << "-" << "\t";                              // Вывод таблицы
				if (stateOfEdges[h][j] == EdgeState::RIGHT)
					std::cout << "+" << "\t";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
		/////////////////////////////////////////////////////////////////////
	}
	stateOfEdges[oneVertice][twoVertice] = EdgeState::RIGHT;
	stateOfEdges[twoVertice][oneVertice] = EdgeState::RIGHT;


	/////////////////////////////////////////////////////////////////////
	for (int i = 0; i < pointsAmount; ++i) {
		for (int j = 0; j < pointsAmount; ++j) {
			if (stateOfEdges[i][j] == EdgeState::NEUTRAL)
				std::cout << 0 << "\t";
			if (stateOfEdges[i][j] == EdgeState::WRONG)
				std::cout << "-" << "\t";                              // Вывод таблицы
			if (stateOfEdges[i][j] == EdgeState::RIGHT)
				std::cout << "+" << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	/////////////////////////////////////////////////////////////////////

	double sum = 0.0;
	for (int i = 0; i < pointsAmount; ++i) {
		for (int j = i + 1; j < pointsAmount; ++j) {
			if (stateOfEdges[i][j] == EdgeState::RIGHT) {
				sum += edges[i][j].GetWeight();
				std::cout << i << " - " << j << "\t";
			}
		}
	}
	std::cout << "WEIGHT - " << sum << std::endl;
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

void VerticesMethod::triangleRecursion(int firstVertice, int secondVertice, std::vector<bool>& verticesStateR, int& rightVerticesAmountR, std::vector<Edge>& wayR)
{
	if (rightVerticesAmountR != pointsAmount) {
		rightVerticesAmountR++;
		double sum = 0;
		int rightVertice = 0;
		for (int i = 0; i < pointsAmount; ++i) {
			if (!verticesStateR[i]) {
				double twoEdgesSum = edges[firstVertice][i].GetWeight() + edges[secondVertice][i].GetWeight();
				if (sum == 0 || sum > twoEdgesSum) {
					rightVertice = i;
					sum = twoEdgesSum;
				}
			}
		}
		if (edges[firstVertice][rightVertice].GetWeight() < edges[secondVertice][rightVertice].GetWeight()) {
			wayR.push_back(Edge(firstVertice, rightVertice, edges[firstVertice][rightVertice].GetWeight()));
			triangleRecursion(secondVertice, rightVertice, verticesStateR, rightVerticesAmountR, wayR);
		} 
		else {
			wayR.push_back(Edge(secondVertice, rightVertice, edges[secondVertice][rightVertice].GetWeight()));
			triangleRecursion(firstVertice, rightVertice, verticesStateR, rightVerticesAmountR, wayR);
		}
	}
	else {
		wayR.push_back(Edge(firstVertice, secondVertice, edges[firstVertice][secondVertice].GetWeight()));
		std::cout << "------------" << std::endl;
		for (auto edgeS : wayR) {
			std::cout << edgeS.GetFirstPoint() << " - " << edgeS.GetSecondPoint() << "\t";
		}
		std::cout << std::endl;
	}
}
