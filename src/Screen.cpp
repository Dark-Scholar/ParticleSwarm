#include "Screen.h"

namespace vtech {
	Screen::Screen(): window(NULL), renderer(NULL), texture(NULL), buffer(NULL) {}

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
		buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT];


		// Calculate the total number of bytes for the buffer
		size_t bufferSizeInBytes = SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32);
		memset(buffer, 0, bufferSizeInBytes);

		for (int i = 0; i < SCREEN_WIDTH*SCREEN_HEIGHT; i++) {
			buffer[i] = 0x00000000;
		}

		return true;
	}

	void Screen::update() {
		// Pitch is the amount of memory allocated to a single row of pixels
		SDL_UpdateTexture(texture, NULL, buffer, SCREEN_WIDTH*sizeof(Uint32));
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

		buffer[(y * SCREEN_WIDTH) + x] = color;
	}

	void Screen::close() {
		if (buffer != nullptr) {
			delete[] buffer;
			buffer = nullptr;
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
};