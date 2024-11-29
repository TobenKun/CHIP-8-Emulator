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

	while (!quit)
	{
		quit = platform.ProcessInput(chip8.keypad);

		auto  currentTime = std::chrono::high_resolution_clock::now();
		float dt =
			std::chrono::duration<float, std::chrono::microseconds::period>(
				currentTime - lastCycleTime)
				.count();

		if (dt > cycleDelay)
		{
			lastCycleTime = currentTime;

			chip8.Cycle();

			platform.Update(chip8.video, videoPitch);
		}
	}

	return (0);
}
