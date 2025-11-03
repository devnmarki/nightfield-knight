#ifndef BOX_HPP
#define BOX_HPP

#include "ui/widget.hpp"

namespace ui
{
	struct BoxStyle
	{
		int width = 10;
		int height = 10;
		glm::u8vec4 backgroundColor = glm::u8vec4(0.0f);
	};

	struct BoxProps : public WidgetProps
	{
		glm::vec2 position = glm::vec2(0.0f);
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