#include "column.hpp"

namespace ui
{
	Column::Column(const ColumnProps& props)
		: WidgetBase{ props }
	{
		_box = make_widget<Box>(BoxProps{
			.position = props.position,
			.width = props.width,
			.height = props.height,
			.style = BoxStyle{
				.backgroundColor = props.style.backgroundColor,
			}
		});

		for (size_t i = 0; i < props.children.size(); i++)
		{
			auto& child = props.children[i];

			glm::vec2 startPos = child->getPosition() + props.position;
			float nextX = startPos.x + (i * (child->getWidth() + props.gap));
			child->setPosition(glm::vec2(startPos.x + nextX, startPos.y));

			_box->getProps().width += child->getWidth() + props.gap;
			_box->getProps().height += child->getHeight();
		}

		_props.width = _box->getProps().width;
		_props.height = _box->getProps().height;
	}

	void Column::update()
	{
		for (std::shared_ptr<IWidget>& child : _props.children)
		{
			child->update();
		}
	}	

	void Column::render()
	{
		if (_box != nullptr)
			_box->render();

		for (std::shared_ptr<IWidget>& child : _props.children)
		{
			child->render();
		}
	}
}