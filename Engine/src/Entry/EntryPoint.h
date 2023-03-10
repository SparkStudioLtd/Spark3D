#include "CoreFramework.h"

bool running = true;

ApplicationSpecification getSpec() {
	ApplicationSpecification app;

	app.Name = "Spark Demo";
	app.Width = 1920;
	app.Height = 1080;

	return app;
}

int main() {
	//while (running) {
		Spark* spark = new Spark();
		Spark::CreateCore();
		ApplicationSpecification spec = getSpec();
		Spark::RegisterApplicationSpecification(spec);
		Spark::EnterLoop();
		Spark::Shutdown();
	//}
	std::cout << "Hello, World!" << std::endl;
	return 0;
}