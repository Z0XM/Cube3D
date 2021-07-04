#include "CubeRenderer.hpp"

int main()
{
	CubeRenderer cube;
	while (cube.isRunning())
	{
		cube.update();
		cube.render();
	}
}