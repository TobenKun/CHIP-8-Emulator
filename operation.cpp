#include <cstdint>
#include <iostream>
#include "Chip8.hpp"

void Chip8::OP_00E0()
{
	memset(video, 0, sizeof(video));
	if (debugMode) std::cout << ": Clears the screen" << std::endl;
}

void Chip8::OP_00EE()
{
	sp--;
	pc = stack[sp];
	if (debugMode) std::cout << ": Returns from a subroutine" << std::endl;
}

void Chip8::OP_1nnn()
{
	uint16_t address = opcode & 0xFFFu;
	pc = address;
	if (debugMode)
		std::cout << ": Jumps to address " << std::hex << address << std::endl;
}

void Chip8::OP_2nnn()
{
	uint16_t address = opcode & 0xFFFu;

	stack[sp] = pc;
	sp++;
	pc = address;
	if (debugMode)
		std::cout << ": Calls subroutine at " << std::hex << address
				  << std::endl;
}

void Chip8::OP_3xkk()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;
	uint8_t byte = opcode & 0xFFu;

	if (registers[Vx] == byte)
	{
		pc += 2;
		if (debugMode) std::cout << ": Skip the next instruction" << std::endl;
	}
	else if (debugMode)
		std::cout << ": not skipped" << std::endl;
}

void Chip8::OP_4xkk()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;
	uint8_t byte = opcode & 0xFFu;

	if (registers[Vx] != byte)
	{
		pc += 2;
		if (debugMode) std::cout << ": Skip the next instruction" << std::endl;
	}
	else if (debugMode)
		std::cout << ": not skipped" << std::endl;
}

void Chip8::OP_5xy0()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;
	uint8_t Vy = (opcode & 0xF0u) >> 0x4u;

	if (registers[Vx] == registers[Vy])
	{
		pc += 2;
		if (debugMode) std::cout << ": Skip the next instruction" << std::endl;
	}
	else if (debugMode)
		std::cout << ": not skipped" << std::endl;
}

void Chip8::OP_6xkk()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;
	uint8_t byte = opcode & 0xFFu;

	registers[Vx] = byte;
	if (debugMode)
		std::cout << ": Set register[" << std::hex << Vx << "] to " << std::hex
				  << byte << std::endl;
}

void Chip8::OP_7xkk()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;
	uint8_t byte = opcode & 0xFFu;

	registers[Vx] += byte;
	if (debugMode)
		std::cout << "Adds " << std::hex << byte << " to register[" << std::hex
				  << Vx << "]" << std::endl;
}

void Chip8::OP_8xy0()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;
	uint8_t Vy = (opcode & 0xF0u) >> 0x4u;

	registers[Vx] = registers[Vy];
	if (debugMode)
		std::cout << ": Set register[" << std::hex << Vx << "] to " << std::hex
				  << registers[Vy] << std::endl;
}

void Chip8::OP_8xy1()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;
	uint8_t Vy = (opcode & 0xF0u) >> 0x4u;

	registers[Vx] |= registers[Vy];
}

void Chip8::OP_8xy2()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;
	uint8_t Vy = (opcode & 0xF0u) >> 0x4u;

	registers[Vx] &= registers[Vy];
}

void Chip8::OP_8xy3()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;
	uint8_t Vy = (opcode & 0xF0u) >> 0x4u;

	registers[Vx] ^= registers[Vy];
}

void Chip8::OP_8xy4()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;
	uint8_t Vy = (opcode & 0xF0u) >> 0x4u;

	uint16_t sum = registers[Vx] + registers[Vy];
	uint8_t	 carry = (sum > 0xFFu) ? 1 : 0;

	registers[Vx] = sum & 0xFFu;
	registers[0xFu] = carry;
}

void Chip8::OP_8xy5()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;
	uint8_t Vy = (opcode & 0xF0u) >> 0x4u;

	uint16_t result = registers[Vx] - registers[Vy];
	uint8_t	 carry = (registers[Vx] >= registers[Vy]) ? 1 : 0;

	registers[Vx] = result & 0xFFu;
	registers[0xFu] = carry;
}

void Chip8::OP_8xy6()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;

	uint8_t carry = (registers[Vx] & 0x1u);
	registers[Vx] >>= 0x1u;
	registers[0xFu] = carry;
}

void Chip8::OP_8xy7()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;
	uint8_t Vy = (opcode & 0xF0u) >> 0x4u;

	uint16_t result = registers[Vy] - registers[Vx];
	uint8_t	 carry = (registers[Vy] >= registers[Vx]) ? 1 : 0;
	registers[Vx] = result & 0xFF;

	registers[0xFu] = carry;
}

void Chip8::OP_8xyE()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;

	uint8_t carry = (registers[Vx] & 0x80u) >> 0x7u;
	registers[Vx] <<= 0x1u;
	registers[0xFu] = carry;
}

void Chip8::OP_9xy0()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;
	uint8_t Vy = (opcode & 0xF0u) >> 0x4u;

	if (registers[Vx] != registers[Vy]) pc += 2;
}

void Chip8::OP_Annn()
{
	uint16_t address = (opcode & 0xFFFu);
	index = address;
}

void Chip8::OP_Bnnn()
{
	uint16_t address = (opcode & 0xFFFu);

	pc = (address + registers[0x0]) & 0xFFF;
}

void Chip8::OP_Cxkk()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;
	uint8_t byte = opcode & 0xFFu;

	registers[Vx] = randByte(randGen) & byte;
}

void Chip8::OP_Dxyn()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;
	uint8_t Vy = (opcode & 0xF0u) >> 0x4u;
	uint8_t height = opcode & 0xFu;

	registers[0xFu] = 0;

	for (unsigned int row = 0; row < height; ++row)
	{
		uint8_t sprite_byte = memory[index + row];

		for (unsigned int col = 0; col < 8; ++col)
		{
			uint8_t sprite_pixel = sprite_byte & (0x80u >> col);

			uint8_t wrapped_x = (registers[Vx] + col) % VIDEO_WIDTH;
			uint8_t wrapped_y = (registers[Vy] + row) % VIDEO_HEIGHT;

			uint32_t* screen_pixel =
				&video[wrapped_y * VIDEO_WIDTH + wrapped_x];

			if (sprite_pixel)
			{
				if (*screen_pixel == 0xFFFFFFFF)
				{
					registers[0xF] = 1;
				}
				*screen_pixel ^= 0xFFFFFFFF;
			}
		}
	}
}

void Chip8::OP_Ex9E()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;
	uint8_t key_num = registers[Vx];

	if (keypad[key_num]) pc += 2;
}

void Chip8::OP_ExA1()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;
	uint8_t key_num = registers[Vx];

	if (!keypad[key_num]) pc += 2;
}

void Chip8::OP_Fx07()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;

	registers[Vx] = delayTimer;
}

void Chip8::OP_Fx0A()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;

	if (keypad[0])
		registers[Vx] = 0;
	else if (keypad[1])
		registers[Vx] = 1;
	else if (keypad[2])
		registers[Vx] = 2;
	else if (keypad[3])
		registers[Vx] = 3;
	else if (keypad[4])
		registers[Vx] = 4;
	else if (keypad[5])
		registers[Vx] = 5;
	else if (keypad[6])
		registers[Vx] = 6;
	else if (keypad[7])
		registers[Vx] = 7;
	else if (keypad[8])
		registers[Vx] = 8;
	else if (keypad[9])
		registers[Vx] = 9;
	else if (keypad[10])
		registers[Vx] = 10;
	else if (keypad[11])
		registers[Vx] = 11;
	else if (keypad[12])
		registers[Vx] = 12;
	else if (keypad[13])
		registers[Vx] = 13;
	else if (keypad[14])
		registers[Vx] = 14;
	else if (keypad[15])
		registers[Vx] = 15;
	else
		pc -= 2;
}

void Chip8::OP_Fx15()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;

	delayTimer = registers[Vx];
}

void Chip8::OP_Fx18()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;

	soundTimer = registers[Vx];
}

void Chip8::OP_Fx1E()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;

	index += registers[Vx];
	if (index > 0xFFF)
	{
		registers[0xFu] = 1;
		index &= 0xFFF;
	}
	else
		registers[0xFu] = 0;
}

void Chip8::OP_Fx29()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;
	uint8_t digit = registers[Vx];

	index = FONTSET_START_ADDRESS + (5 * digit);
}

void Chip8::OP_Fx33()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;
	uint8_t value = registers[Vx];

	memory[index + 2] = value % 10;
	value /= 10;
	memory[index + 1] = value % 10;
	value /= 10;
	memory[index] = value % 10;
}

void Chip8::OP_Fx55()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;

	for (uint8_t i = 0; i <= Vx; i++)
	{
		memory[index + i] = registers[i];
	}
}

void Chip8::OP_Fx65()
{
	uint8_t Vx = (opcode & 0xF00u) >> 0x8u;

	for (uint8_t i = 0; i <= Vx; i++)
	{
		if (index + i <= 0xFFFu) registers[i] = memory[index + i];
	}
}
