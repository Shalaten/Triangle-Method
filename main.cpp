#include "VerticesMethod.h"

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru");

	VerticesMethod verticesMethod(5);

	//verticesMethod.PrintEdgeMatrix();
	std::cout << std::endl;
	verticesMethod.PrintBroodForceMethodWay();

	return 0;
}