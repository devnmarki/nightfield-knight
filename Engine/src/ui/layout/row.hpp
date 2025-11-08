#ifndef ROW_HPP
#define ROW_HPP

#include <vector>

#include "ui/widget.hpp"
#include "ui/box.hpp"

namespace ui
{
	struct RowStyle
	{
		glm::u8vec4 backgroundColor = glm::u8vec4(0.0f);
	};

	struct RowProps : WidgetProps
	{
		glm::vec2 position = glm::vec2(0.0f);
		int width = 0;
		int height = 0;
		int gap = 0;
		RowStyle style = {};
		std::vector<std::shared_ptr<IWidget>> children;
	};

	class Row : public WidgetBase<RowProps>
	{
	public:
		Row(const RowProps& props);

		void update() override;
		void render() override;

	private:
		std::shared_ptr<Box> _box;
	};
}

#endif