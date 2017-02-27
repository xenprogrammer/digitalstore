#include <MultiWidgets/Application.hpp>
#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/ImageWidget.hpp>
#include <Nimble/Random.hpp>
#include <MultiWidgets/TimerOperator.hpp>
#include <MultiWidgets/Animators.hpp>
#include <MultiWidgets/MessageSendOperator.hpp>

namespace customProjects
{
	class RelativeMotion : public MultiWidgets::Widget
	{
	public:
		RelativeMotion();
		int totalCount;
		
		Nimble::Vector2f targetPoint;
		Nimble::Vector2f targetPoint1;
		float rotationAngle;
		Nimble::Vector2f getRotatedPoint(Nimble::Vector2f , float , float );
		MultiWidgets::WidgetPtr getChildByName(QString);
		MultiWidgets::WidgetPtr getChildInBaseWidgetByType(MultiWidgets::WidgetPtr, QString);

		void eventProcess(const QByteArray & messageId, Radiant::BinaryData & data);
		//void renderBackground(Luminous::RenderContext &r) const OVERRIDE;
	};
}