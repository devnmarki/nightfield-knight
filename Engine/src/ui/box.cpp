#include "box.hpp"

namespace ui
{
	Box::Box(const BoxProps& props)
		: WidgetBase{ props }
	{
		_rect = SDL_Rect{
			.x = static_cast<int>(props.position.x),
			.y = static_cast<int>(props.position.y),
			.w = props.width,
			.h = props.height
		};

		if (props.child == nullptr) return;
	
		if (auto* child = dynamic_cast<Box*>(props.child.get()))
		{
			child->_props.position += props.position;
		} 
	}

	void Box::update()
	{
		_rect.x = static_cast<int>(_props.position.x);
		_rect.y = static_cast<int>(_props.position.y);
		_rect.w = _props.width;
		_rect.h = _props.height;

		if (_props.child != nullptr)
			_props.child->update();
	}

	void Box::render()
	{
		if (_props.width == 0 || _props.height == 0)
			return;

		base::Renderer::fillRect(&_rect, _props.style.backgroundColor);

		if (_props.child != nullptr)
			_props.child->render();
	}
}