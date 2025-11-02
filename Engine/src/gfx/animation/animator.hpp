#ifndef ANIMATOR_HPP
#define ANIMATOR_HPP

#include <unordered_map>
#include <vector>
#include <memory>
#include <fstream>

#include <nlohmann/json.hpp>

#include "gfx/animation/animation.hpp"
#include "asset_manager.hpp"
#include "gfx/renderer.hpp"
#include "scene/scene_manager.hpp"

using json = nlohmann::json;

namespace base
{
	class Animator
	{
	public:
		Animator() = default;

		void loadAnimations(const std::string& filePath);

		void playAnimation(const std::string& id);
		void renderCurrentAnimation(const glm::vec2& position = glm::vec2(0.0f), const glm::vec2& scale = glm::vec2(1.0f));

		Animation* getCurrentAnimation();

	private:
		std::unordered_map<std::string, Animation> _animations;
		Animation* _currentAnimation = nullptr;
	};
}

#endif