
#include <MultiWidgets/Application.hpp>
#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/ImageWidget.hpp>
#include <Nimble/Random.hpp>
#include <MultiWidgets/TimerOperator.hpp>
#include <MultiWidgets/Animators.hpp>
#include <MultiWidgets/MessageSendOperator.hpp>



namespace customProjects
{
	class InteractiveBlob : public MultiWidgets::Widget
	{
	public:
		//InteractiveBlob(MultiWidgets::WidgetPtr parent, int index, int totalCount, int radius);
		//InteractiveBlob(MultiWidgets::WidgetPtr, MultiWidgets::WidgetPtr, int, int, int);
		InteractiveBlob(MultiWidgets::WidgetPtr, MultiWidgets::WidgetPtr, int, int, int, MultiWidgets::WidgetPtr);
		void eventProcess(const QByteArray & messageId, Radiant::BinaryData & data);
		//void tweenToBaseLocation(float xc, float yc, Nimble::Vector2f centerBLoc);
		void tweenToLocation(Nimble::Vector2f, float);//target location and duration
		void updateArrows();
		void updateArrows1();
		void updateArrows2();
		double getDistance(Nimble::Vector2f point1, Nimble::Vector2f point2);
		Nimble::Vector2f InteractiveBlob::getEquatedPoint(Nimble::Vector2f _arrowStartPoint, Nimble::Vector2f _arrowEndPoint, float _dist);
		void removeAllArrows();
		void removeAllArrows1();
		Nimble::Vector2f getRotatedPoint(Nimble::Vector2f, float, float);//point, radius, angle

		double prevDistance;
		int getClipNum();
		MultiWidgets::WidgetPtr centralBubble;
		MultiWidgets::WidgetPtr arrow;
		MultiWidgets::WidgetPtr parent;
		int myIndex;
		int totalCount;
		int radius;
		MultiWidgets::WidgetPtr linkedArrow;

		float previousDistance;

		int countArrows;
		
		
		float myEquatedAngle;
		bool isMouseDown;

		float Arrowx;
		float Arrowy;

		int masterCount;
	
	};
}
