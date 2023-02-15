#include "VerticesMethod.h"

int main(int argc, char* argv[]) {
	setlocale(LC_ALL, "ru");

	VerticesMethod verticesMethod(8);

	
	std::cout << std::endl;
	verticesMethod.PrintBroodForceMethodWay();


	std::cout << std::endl;

	return 0;
}