#ifndef GRID_HPP
#define GRID_HPP

#include <vector>

#include "ui/widget.hpp"
#include "ui/layout/row.hpp"
#include "ui/layout/column.hpp"

namespace ui
{
	struct GridStyle
	{
		glm::u8vec4 backgroundColor = glm::u8vec4(0.0f, 0.0f, 0.0f, 0.0f);
	};

	struct GridProps : public WidgetProps
	{
		glm::vec2 position = glm::vec2(0.0f, 0.0f);
		int gap = 0;
		int rows = 0;
		int columns = 0;
		int cellWidth = 0;
		int cellHeight = 0;
		GridStyle style = {};
		std::vector<std::shared_ptr<IWidget>> children;
	};

	class Grid : public WidgetBase<GridProps>
	{
	public:
		Grid(const GridProps& props);

		void update() override;
		void render() override;

	private:
		std::vector<std::shared_ptr<Column>> _rows;
	};
}

#endif