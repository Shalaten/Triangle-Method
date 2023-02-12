#pragma once

class Edge {
public:
	Edge(int firstPoint, int secondPoint, double weight);
	int GetFirstPoint();
	int GetSecondPoint();
	double GetWeight();
	void SetFirstPoint(int firstPoint);
	void SetSecondPoint(int secondPoint);
	void SetWeight(double weight);
private:
	int firstPoint, secondPoint;
	double weight;
};
