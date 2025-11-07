#include "row.hpp"

namespace ui
{
	Row::Row(const RowProps& props)
        : WidgetBase{ props }
	{
        float maxWidth = 0;
        float totalHeight = 0;

        for (size_t i = 0; i < props.children.size(); i++)
        {
            auto& child = props.children[i];
            maxWidth = std::max(maxWidth, static_cast<float>(child->getWidth()));
            totalHeight += child->getHeight();
            if (i < props.children.size() - 1)
                totalHeight += props.gap;
        }

        float currentY = props.position.y;
        for (auto& child : props.children)
        {
            child->setPosition(glm::vec2(props.position.x, currentY));
            currentY += child->getHeight() + props.gap;
        }

        _box = make_widget<Box>(BoxProps{
            .position = props.position,
            .width = static_cast<int>(maxWidth),
            .height = static_cast<int>(totalHeight),
            .style = BoxStyle{
                .backgroundColor = props.style.backgroundColor,
            }
            });

        _props.width = _box->getProps().width;
        _props.height = _box->getProps().height;
	}

	void Row::update()
	{
		for (std::shared_ptr<IWidget>& child : _props.children)
		{
			child->update();
		}
	}

	void Row::render()
	{
		if (_box != nullptr)
			_box->render();

		for (std::shared_ptr<IWidget>& child : _props.children)
		{
			child->render();
		}
	}
}