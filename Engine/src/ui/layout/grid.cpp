#include "grid.hpp"

namespace ui
{
	Grid::Grid(const GridProps& props)
		: WidgetBase{ props }
	{
		float totalWidth = 0;
		float totalHeight = 0;

		for (int row = 0; row < props.rows; row++)
		{
			std::vector<std::shared_ptr<IWidget>> columnChildren;

			for (int col = 0; col < props.columns; col++)
			{
				int childIndex = row * props.columns + col;
				if (childIndex < props.children.size())
				{
					if (props.children[childIndex]->getWidth() == 0)
						props.children[childIndex]->setWidth(props.cellWidth);
					if (props.children[childIndex]->getHeight() == 0)
						props.children[childIndex]->setHeight(props.cellHeight);

					columnChildren.push_back(props.children[childIndex]);
				}
			}

			std::shared_ptr<Column> column = make_widget<Column>(
				ColumnProps{
					.position = glm::vec2(props.position.x, props.position.y + (row * (props.cellHeight + props.gap))),
					.gap = props.gap,
					.children = columnChildren
				}
			);

			_rows.push_back(column);

			if (row == 0)
				totalWidth = static_cast<float>(column->getWidth());
			totalHeight += column->getHeight() + props.gap;
		}

		_props.width = static_cast<int>(totalWidth);
		_props.height = static_cast<int>(totalHeight - props.gap);
	}

	void Grid::update()
	{
		for (auto& row : _rows)
			row->update();
	}

	void Grid::render()
	{
		for (auto& row : _rows)
			row->render();
	}
}