#include "box.hpp"

namespace ui
{
	Box::Box(const BoxProps& props)
		: WidgetBase{ props }
	{
		_rect = SDL_Rect{
			.x = static_cast<int>(props.position.x),
			.y = static_cast<int>(props.position.y),
			.w = props.style.width,
			.h = props.style.height
		};

		std::cout << "Box created: x=" << _rect.x << ", y=" << _rect.y
			<< ", w=" << _rect.w << ", h=" << _rect.h << std::endl;
	}

	void Box::update()
	{

	}

	void Box::render()
	{
		if (_props.style.width == 0 || _props.style.height == 0)
			return;

		base::Renderer::fillRect(&_rect, _props.style.backgroundColor);
	}
}