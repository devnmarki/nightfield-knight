#ifndef WIDGET_HPP
#define WIDGET_HPP

#include <iostream>
#include <memory>
#include <functional>

#include <SDL.h>
#include <vec2.hpp>
#include <vec4.hpp>

#include "gfx/renderer.hpp"

namespace ui
{
	struct WidgetProps 
	{
		glm::vec2 position = glm::vec2(0.0f);
		int width = 0;
		int height = 0;
	};

	class IWidget
	{
	public:
		virtual ~IWidget() = default;

		virtual void update() = 0;
		virtual void render() = 0;

		virtual glm::vec2& getPosition() = 0;
		virtual void setPosition(const glm::vec2& pos) = 0;
		virtual int getWidth() const = 0;
		virtual int getHeight() const = 0;
	};

	template<typename TProps = WidgetProps>
	class WidgetBase : public IWidget
	{
	public:
		explicit WidgetBase(const TProps& props = {}) : _props(props) {}
		virtual ~WidgetBase() = default;

		glm::vec2& getPosition() override { return _props.position; }
		void setPosition(const glm::vec2& pos) override { _props.position = pos; }
		int getWidth() const override { return _props.width; }
		int getHeight() const override { return _props.height; }

		TProps& getProps() { return _props; }
		const TProps& getProps() const { return _props; }

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