#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>

#include <vec2.hpp>
#include <vec4.hpp>

#include "gfx/texture.hpp"
#include "gfx/sprite.hpp"
#include "core/window.hpp"
#include "scene/camera.hpp"

namespace base
{
	class Renderer
	{
	public:
		static void draw(std::shared_ptr<Texture> texture, const glm::vec2& position, SDL_Rect* src = nullptr, glm::vec2 scale = glm::vec2(1.0f), bool flip = false, uint8_t alpha = 255, Camera* camera = nullptr);
		static void draw(Sprite& sprite, const glm::vec2& position, glm::vec2 scale = glm::vec2(1.0f), bool flip = false, Camera* camera = nullptr);
		static void draw(Sprite& sprite, const glm::vec2& position, float scale = 1.0f, bool flip = false, Camera* camera = nullptr);

		static void fillRect(const SDL_Rect* rect, const glm::u8vec4& color);
	};
}

#endif