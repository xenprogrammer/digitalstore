#include <MultiWidgets/Application.hpp>
#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/ImageWidget.hpp>
#include <Nimble/Random.hpp>
#include <MultiWidgets/TimerOperator.hpp>
#include <MultiWidgets/Animators.hpp>
#include <MultiWidgets/MessageSendOperator.hpp>



namespace customProjects
{
	class drawnArrow : public MultiWidgets::Widget
	{
		public:
			MultiWidgets::WidgetPtr parentWidget;	
			drawnArrow(MultiWidgets::WidgetPtr, MultiWidgets::WidgetPtr);
			virtual void eventProcess(const QByteArray & messageId, Radiant::BinaryData & data) OVERRIDE;
			void renderBackground(Luminous::RenderContext &r) const OVERRIDE;
			Nimble::Vector2f basePoint;
			Nimble::Vector2f targetPoint;
			void setBasePoint(Nimble::Vector2f);
			void setTargetPoint(Nimble::Vector2f);
			bool renderingEnabled;
			void setRendering(bool);
			MultiWidgets::WidgetPtr centralBubble;

			void setValues(float, float, Nimble::Vector2f, Nimble::Vector2f);

			Nimble::Vector2f getEquatedPoint(Nimble::Vector2f, Nimble::Vector2f, float);
			double getDistance(Nimble::Vector2f, Nimble::Vector2f);

			float arrowDistance;
			float totalDistance1;
			Nimble::Vector2f arrowStartPoint1;
			Nimble::Vector2f arrowEndPoint1;
	};
}