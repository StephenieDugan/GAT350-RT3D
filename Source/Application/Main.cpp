#include "World01.h"
#include "World02.h"
#include "World03.h"
#include "World04.h"
#include "World05.h"
#include "Core/Core.h"
#include "Framework/Framework.h"
#include "Renderer/Renderer.h"

#include <iostream>
#include "Core/StringUtils.h"


using namespace std;

int main(int argc, char* argv[])
{
	INFO_LOG("Initialize Engine...")
	std::string input = "Hello Party People";

	// Test Upper
	std::string upper = Twili::StringUtils::ToUpper(input);
	std::cout << "ToUpper: " << upper << std::endl;

	// TestLower
	std::string lower = Twili::StringUtils::ToLower(input);
	std::cout << "ToLower: " << lower << std::endl;

	// Test IsEqualIgnoreCase
	std::string str1 = "Hello";
	std::string str2 = "HELLO";
	bool isEqual = Twili::StringUtils::IsEqualIgnoreCase(str1, str2);
	std::cout << "IsEqualIgnoreCase: " << isEqual << std::endl;

	// Test Unique
	std::string Str1 = Twili::StringUtils::CreateUnique(input);
	std::string Str2 = Twili::StringUtils::CreateUnique(input);
	std::cout << "Unique Strings: " << Str1 << ",\n " << Str2 << std::endl;

	//Twili::MemoryTracker::Initialize();
	Twili::seedRandom((unsigned int)time(nullptr));
	Twili::setFilePath("assets");

	ENGINE.Initialize();
	
	auto world = make_unique<Twili::World05>();
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
