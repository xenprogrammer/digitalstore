
#include <MultiWidgets/Application.hpp>
#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/ImageWidget.hpp>
#include <Nimble/Random.hpp>
#include <MultiWidgets/TimerOperator.hpp>
#include <MultiWidgets/Animators.hpp>
#include <MultiWidgets/MessageSendOperator.hpp>



namespace customProjects
{
	class MenuBubble : public MultiWidgets::ImageWidget
	{
	public:
		MenuBubble(float x, float y);
	};
}