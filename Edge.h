#pragma once

class Edge {
public:
	Edge();
	Edge(int firstPoint, int secondPoint, double weight);
	int GetFirstPoint();
	int GetSecondPoint();
	double GetWeight();
	void SetFirstPoint(int firstPoint);
	void SetSecondPoint(int secondPoint);
	void SetWeight(double weight);

	void operator = (const Edge& edge);
private:
	int firstPoint, secondPoint;
	double weight;
};
