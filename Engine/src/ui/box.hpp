#ifndef BOX_HPP
#define BOX_HPP

#include "ui/widget.hpp"
#include "scene/scene_manager.hpp"

namespace ui
{
	struct BoxStyle
	{
		glm::u8vec4 backgroundColor = glm::u8vec4(0.0f);
	};

	struct BoxProps : public WidgetProps
	{
		glm::vec2 position = glm::vec2(0.0f);
		int width = 0;
		int height = 0;
		std::shared_ptr<IWidget> child = nullptr;
		BoxStyle style = {};
	};

	class Box : public WidgetBase<BoxProps>
	{
	public:
		Box(const BoxProps& props);

		void update() override;
		void render() override;

	private:
		SDL_Rect _rect;
	};
}

#endif