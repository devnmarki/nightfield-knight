#include "column.hpp"

namespace ui
{
	Column::Column(const ColumnProps& props)
		: WidgetBase{ props }
	{
        float totalWidth = 0;
        float maxHeight = 0;

        for (size_t i = 0; i < props.children.size(); i++)
        {
            auto& child = props.children[i];
            totalWidth += child->getWidth();
            maxHeight = std::max(maxHeight, static_cast<float>(child->getHeight()));
            if (i < props.children.size() - 1) 
                totalWidth += props.gap;
        }

        float currentX = props.position.x;
        for (auto& child : props.children)
        {
            child->setPosition(glm::vec2(currentX, props.position.y));
            currentX += child->getWidth() + props.gap;
        }

        _box = make_widget<Box>(BoxProps{
            .position = props.position,
            .width = static_cast<int>(totalWidth),
            .height = static_cast<int>(maxHeight),
            .style = BoxStyle{
                .backgroundColor = props.style.backgroundColor,
            }
            });

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