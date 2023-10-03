#include "World01.h"
#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

using namespace std;

int main(int argc, char* argv[])
{
	INFO_LOG("Initialize Engine...")

	Twili::MemoryTracker::Initialize();
	Twili::seedRandom((unsigned int)time(nullptr));
	Twili::setFilePath("assets");

	ENGINE.Initialize();

	auto world = make_unique<Twili::World01>();
	world->Initialize();

	// main loop
	bool quit = false;
	while (!quit)
	{
		// update
		ENGINE.Update();
		quit = ENGINE.IsQuit();

		world->Update(ENGINE.GetTime().GetDeltaTime());

		// draw
		world->Draw(*ENGINE.GetSystem<Twili::Renderer>());
	}

	world->Shutdown();
	ENGINE.Shutdown();

	return 0;
}
