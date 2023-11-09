#include "Screen.h"

namespace vtech {
	Screen::Screen(): window(NULL), renderer(NULL), texture(NULL), buffer1(NULL), buffer2(NULL) {}

	Screen::~Screen() {
		close();
	}

	bool Screen::init() {
		if (SDL_Init(SDL_INIT_VIDEO) < 0) {
			return false;
		}

		window = SDL_CreateWindow(
			"Particle Swarm",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN
		);

		if (window == NULL) {
			SDL_Quit();
			return false;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
		texture = SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC,
			SCREEN_WIDTH,
			SCREEN_HEIGHT
		);

		if (renderer == NULL) {
			SDL_DestroyWindow(window);
			SDL_Quit();
			return false;
		}

		if (texture == NULL) {
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			return false;
		}

		// Create a piece of memory to hold information on all pixels.
		// For each pixel we have 4bytes (RGBA) each consisting of 8bits
		// 4 * 8 = 32
		// So we need 32 bits of data (the equivalent of an int on most systems)
		buffer1 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];
		buffer2 = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];


		// Calculate the total number of bytes for the buffer
		size_t bufferSizeInBytes = SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32);
		memset(buffer1, 0, bufferSizeInBytes);
		memset(buffer2, 0, bufferSizeInBytes);

		for (int i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++) {
			buffer1[i] = 0x00000000;
		}

		return true;
	}

	void Screen::update() {
		// Pitch is the amount of memory allocated to a single row of pixels
		SDL_UpdateTexture(texture, NULL, buffer1, SCREEN_WIDTH*sizeof(Uint32));
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);
	}

	void Screen::setPixel(int x, int y, Uint8 r, Uint8 g, Uint8 b) {
		Uint32 color = 0;

		if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT) return;

		color += r;
		color <<= 8;
		color += g;
		color <<= 8;
		color += b;
		color <<= 8;
		color += 0xFF; // Alpha

		buffer1[(y * SCREEN_WIDTH) + x] = color;
	}

	void Screen::close() {
		if (buffer1 != nullptr) {
			delete[] buffer1;
			buffer1 = nullptr;
		}

		if (buffer2 != nullptr) {
			delete[] buffer2;
			buffer2 = nullptr;
		}

		if (texture != nullptr) {
			SDL_DestroyTexture(texture);
			texture = nullptr;
		}

		if (renderer != nullptr) {
			SDL_DestroyRenderer(renderer);
			renderer = nullptr;
		}

		if (window != nullptr) {
				SDL_DestroyWindow(window);
				window = nullptr;
		}
		SDL_Quit();
	}

	bool Screen::processEvents() {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				return false;
			}
		}
		return true;
	};

	void Screen::boxBlur() {
		// Swap buffers, pixel info stored in 2
		// we draw from buffer 1.
		Uint32 *temp = buffer1;
		buffer1 = buffer2;
		buffer2 = temp;

		const int rowLimit = SCREEN_HEIGHT - 1;
		const int colLimit = SCREEN_WIDTH - 1;

		for (int y = 0; y < SCREEN_HEIGHT; y++) {
			for (int x = 0; x < SCREEN_WIDTH; x++) {
				/*
				 * 0 0 0
				 * 0 1 0
				 * 0 0 0
				 *
				 * We have an identified pixel which is surrounded by 8 other
				 * pixels. We need to get the pixel values of all these surrounding
				 * pixels and divide by 9 to create an average of our pixel colour
				 * throughout the surrounding pixels.
				 *
				 * We do this by adding up the RGB values in each of our 9 pixels,
				 * divide the result by 9, then store the results back into the pixel
				 * we are setting. This causes the central pixel to become an average
				 * of the colours of the surrounding pixels creating a blur effect.
				 */
				int redTotal = 0;
				int greenTotal = 0;
				int blueTotal = 0;

				for (int row = -1; row <= 1; row++) {
					for (int col = -1; col <= 1; col++) {
						int currentX = x + col;
						int currentY = y + row;

						if (currentX >= 0 && currentX < colLimit && currentY >= 0 && currentY < rowLimit) {
							Uint32 color = buffer2[currentY * SCREEN_WIDTH + currentX];

              // Use bit masks to extract color components
							Uint8 red = (color >> 24) & 0xFF;
							Uint8 green = (color >> 16) & 0xFF;
							Uint8 blue = (color >> 8) & 0xFF;

							redTotal += red;
							greenTotal += green;
							blueTotal += blue;
						}
					}
				}
				Uint8 red = redTotal / 9;
				Uint8 green = greenTotal / 9;
				Uint8 blue = blueTotal / 9;

				setPixel(x, y, red, green, blue);
			}
		}
	}
};