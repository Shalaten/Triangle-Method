#pragma once

class Vertice {
public:
	Vertice(int verticeNumber);

	double GetLostWeight();
	void SetLostWeight(double lostWeight);

	int GetVerticeNumber();

	int GetFirstMinVertice();
	void SetFirstMinVertice(int firstMinVertice);
	int GetSecondMinVertice();
	void SetSecondMinVertice(int secondMinVertice);

	double GetFirstMinVerticeWeight();
	void SetFirstMinVerticeWeight(double firstMinVerticeWeight);
	double GetSecondMinVerticeWeight();
	void SetSecondMinVerticeWeight(double secondMinVerticeWeight);
private:
	int verticeNumber;
	int firstMinVertice, secondMinVertice;
	double firstMinVerticeWeight, secondMinVerticeWeight;
	double lostWeight;
	bool state;
};