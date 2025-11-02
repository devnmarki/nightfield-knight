#include "renderer.hpp"

namespace base
{
	void Renderer::draw(std::shared_ptr<Texture> texture, const glm::vec2& position, SDL_Rect* src, glm::vec2 scale, bool flip, uint8_t alpha, Camera* camera)
	{
        if (texture == nullptr) return;

        glm::vec2 screenPos = position;
        glm::vec2 finalScale = scale;
        if (camera != nullptr)
        {
            screenPos = camera->worldToScreen(position);
            finalScale = scale * camera->getZoom();
        }

        SDL_FRect dst = {
            .x = screenPos.x,
            .y = screenPos.y,
            .w = static_cast<float>(texture->getWidth()) * finalScale.x,
            .h = static_cast<float>(texture->getHeight()) * finalScale.y
        };

        if (src != nullptr)
        {
            dst.w = src->w * finalScale.x;
            dst.h = src->h * finalScale.y;
        }

        SDL_RendererFlip rFlip = flip ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;

        SDL_SetTextureAlphaMod(texture->getHandle(), alpha);
        SDL_RenderCopyExF(Window::getInstance().getRenderer(), texture->getHandle(), src, &dst, 0.0, nullptr, rFlip);
    }

    void Renderer::draw(Sprite& sprite, const glm::vec2& position, glm::vec2 scale, bool flip, Camera* camera)
    {
        draw(sprite.texture, position, &sprite.source, scale, flip, sprite.alpha, camera);
    }

    void Renderer::draw(Sprite& sprite, const glm::vec2& position, float scale, bool flip, Camera* camera)
    {
        draw(sprite.texture, position, &sprite.source, glm::vec2(scale), flip, sprite.alpha, camera);
    }
}