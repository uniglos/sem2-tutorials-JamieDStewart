#include <Vector2.h>
#include <iostream>

int main(int argc, char* argv[])
{
	Vector2 a = Vector2(10.f, 5.f);
	Vector2 b = Vector2(3.f, -3.f);

	Vector2 c = a + b;

	std::cout << "Vector2 a: " << a.x << "x " << a.y << "y " << std::endl;
	std::cout << "Vector2 b: " << b.x << "x " << b.y << "y " << std::endl;
	std::cout << "Vector2 c = a + b " << std::endl;
	std::cout << "Vector2 c: " << c.x << "x " << c.y << "y " << std::endl;

	return 0;
}