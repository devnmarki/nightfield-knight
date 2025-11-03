#ifndef COLUMN_HPP
#define COLUMN_HPP

#include <vector>

#include "ui/widget.hpp"
#include "ui/box.hpp"

namespace ui
{
	struct ColumnStyle
	{
		glm::u8vec4 backgroundColor = glm::u8vec4(0.0f);
	};

	struct ColumnProps : WidgetProps
	{
		glm::vec2 position = glm::vec2(0.0f);
		int width = 0;
		int height = 0;
		int gap = 0;
		ColumnStyle style = {};
		std::vector<std::shared_ptr<IWidget>> children; 
	};

	class Column : public WidgetBase<ColumnProps>
	{
	public:
		Column(const ColumnProps& props = {});

		void update() override;
		void render() override;

	private:
		std::shared_ptr<Box> _box;
	};
}

#endif