#include <Vector2.h>
#include <iostream>
#include <libMath.h>

int main(int argc, char* argv[])
{
	Vector2 a = Vector2(10.f, 5.f);
	Vector2 b = Vector2(3.f, -3.f);

	Vector2 c = a + b;
	
	std::cout << "Vector2 a: " << a.x << "x " << a.y << "y " << std::endl;
	std::cout << "Vector2 b: " << b.x << "x " << b.y << "y " << std::endl;
	std::cout << "Vector2 c = a + b " << std::endl;
	std::cout << "Vector2 c: " << c.x << "x " << c.y << "y " << std::endl;

	Matrix4 A = Matrix4(1.f, 0.707f, 0.3, 0.f,
						3.f, 2.f, 0.5f, 12.f,
						2.3f, 4.3f, 0.5f, 0.f,
						1.2f, 4.3f, 0.3f, 1.f);
	Matrix4 B = A.Inverse();
	Matrix4 C = A * B;
	Matrix4 D = B * A;

	std::cout << "Matrix A: " << std::endl << A;
	std::cout << "Matrix B: " << std::endl << B;
	std::cout << "Matrix C: " << std::endl << C;
	std::cout << "Matrix D: " << std::endl << D;


	return 0;
}