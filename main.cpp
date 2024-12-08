#include <chrono>
#include <iostream>
#include "Chip8.hpp"
#include "Platform.hpp"

int main(int ac, char** av)
{
	if (ac != 4)
	{
		std::cerr << "Usage: " << av[0] << " <Scale> <Delay> <ROM>\n";
		std::exit(1);
	}

	int			videoScale = std::stoi(av[1]);
	int			cycleDelay = std::stoi(av[2]);
	char const* romFilename = av[3];

	Platform platform("CHIP-8 Emulator", VIDEO_WIDTH * videoScale,
					  VIDEO_HEIGHT * videoScale, VIDEO_WIDTH, VIDEO_HEIGHT);

	Chip8 chip8;
	chip8.LoadROM(romFilename);

	int videoPitch = sizeof(chip8.video[0]) * VIDEO_WIDTH;

	auto lastCycleTime = std::chrono::high_resolution_clock::now();
	bool quit = false;

	chip8.debugMode = false;

	while (!quit)
	{
		quit = platform.ProcessInput(chip8.keypad);

		auto  currentTime = std::chrono::high_resolution_clock::now();
		float dt =
			std::chrono::duration<float, std::chrono::milliseconds::period>(
				currentTime - lastCycleTime)
				.count();

		if (!chip8.debugMode &&
			dt > cycleDelay)
		{
			lastCycleTime = currentTime;

			chip8.Cycle();

			if (chip8.drawFlag)
			{
				platform.Update(chip8.video, videoPitch);
				chip8.drawFlag = false;
			}
		}
		else if (chip8.debugMode == true && chip8.keypad[16])
		{
			chip8.Cycle();
			platform.Update((chip8.video), videoPitch);
			// chip8.printRegisters();
		}
	}

	return (0);
}
