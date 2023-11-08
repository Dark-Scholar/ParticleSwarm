#ifndef SCREEN_H
#define SCREEN_H

#include <cstring>

#include <SDL.h>

namespace vtech {
	class Screen {
		public:
			const static int SCREEN_WIDTH = 800;
			const static int SCREEN_HEIGHT = 600;

		private:
			SDL_Window *window;
			SDL_Renderer *renderer;
			SDL_Texture *texture;
			Uint32 *buffer;

		public:
			// iniitalization list
			Screen();
			virtual ~Screen();

			bool init();
			bool processEvents();
			void update();
			void setPixel(
				int x,
				int y,
				Uint8 r,
				Uint8 g,
				Uint8 b
			);
			void close();
			void clear();
	};
};

#endif