#include <MultiWidgets/Application.hpp>
#include <MultiWidgets/Widget.hpp>
#include <MultiWidgets/ImageWidget.hpp>
#include <Nimble/Random.hpp>
#include <MultiWidgets/TimerOperator.hpp>
#include <MultiWidgets/Animators.hpp>
#include <MultiWidgets/MessageSendOperator.hpp>
#include "imageDisplayer.hpp"


namespace customProjects
{
	class animatedArrow : public MultiWidgets::Widget
	{
		public:
			MultiWidgets::WidgetPtr parentWidget;
			MultiWidgets::WidgetPtr firstBuble;
			MultiWidgets::WidgetPtr movingBuble;
			QString imagePath;
			QString myName;
			float targetDistance;
			float targetDuration;		
			int arrowCount;
			float prevArrowLoc;
			float targetX;
			float targetY;
			bool isArrowReached;	
			int maxArrowsCount;
			int spacingArrows;
			int myRadians;
			Nimble::Vector2 lastArrowEndLoc;			
			animatedArrow(MultiWidgets::WidgetPtr, MultiWidgets::WidgetPtr, QString, float, float, int);
			void setMyName(QString _name);
			QString getMyName();
			void displayArrows();
			bool checkChildLocation(float, float);
			void removeExtraArrows(float x);
			void removeAllArrows();
			void displayArrowsOnDistance(float dist, float lastX);
			void displayArrowsOnDistanceUpdate(float dist, Nimble::Vector2f _startLoc);
			double getDistance(Nimble::Vector2f point1, Nimble::Vector2f point2);
			void enableWidget(imageDisplayer &);			
			virtual void eventProcess(const QByteArray & messageId, Radiant::BinaryData & data) OVERRIDE;
	};
}