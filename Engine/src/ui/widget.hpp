#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <functional>

#include <vec4.hpp>

#include "engine.hpp"

namespace ui
{
	struct WidgetProps 
	{
		glm::vec2 position = glm::vec2(0.0f);
	};

	class IWidget
	{
	public:
		virtual ~IWidget() = default;

		virtual void update() = 0;
		virtual void render() = 0;
	};

	template<typename TProps = WidgetProps>
	class WidgetBase : public IWidget
	{
	public:
		explicit WidgetBase(const TProps& props = {}) : _props(props) {}
		virtual ~WidgetBase() = default;

	protected:
		TProps _props;
	};

	template<typename T, typename... Args>
	inline static std::shared_ptr<T> make_widget(Args&&... args)
	{
		return std::make_shared<T>(std::forward<Args>(args)...);
	}
}

#endif