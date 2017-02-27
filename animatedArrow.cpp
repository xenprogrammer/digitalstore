#include "animatedArrow.hpp"

namespace customProjects
{
	animatedArrow::animatedArrow(MultiWidgets::WidgetPtr _parentWidget, MultiWidgets::WidgetPtr  _firstBuble, QString _imagePath, float _targetDistance, float _targetDuration, int _maxArrowCount) :Widget()
	{
		isArrowReached = false;
		setBackgroundColor(0.0f, 0.0f, 0.0f, 0.0f);
		parentWidget = _parentWidget;
		firstBuble = _firstBuble;
		movingBuble = _parentWidget;
		imagePath = _imagePath;
		targetDistance = _targetDistance;
		setInputFlags(INPUT_NONE);
		targetX = 0;
		targetY = 0;
		spacingArrows = 21;
		targetDuration = _targetDuration;		
		arrowCount = 0;
		prevArrowLoc = 0;
		maxArrowsCount = _maxArrowCount;
		myRadians = 0;
		lastArrowEndLoc = Nimble::Vector2f(0, 0);	
		parentWidget->addChild(this);

		//Radiant::BinaryData d;
		//addOperator(std::make_shared<MultiWidgets::MessageSendOperator>(0.1f, "generateArrows", d, false));

		//Radiant::BinaryData d;
		//addOperator(std::make_shared<MultiWidgets::MessageSendOperator>(0.1f, "updateArrows", d, false));
		
	}

	void animatedArrow::setMyName(QString _name) {
		setName(_name.toUtf8());
	}

	QString	animatedArrow::getMyName() {
		return name();
	}

	void animatedArrow::displayArrows() {
		for (size_t i = 0; i < maxArrowsCount; i++)
		{
			QString tmpName;
			tmpName = "image_" + QString::number(i);

			auto id = MultiWidgets::create<customProjects::imageDisplayer>(this, imagePath, tmpName, true);
			id->setX(i*spacingArrows);

			printf("\n y loc %f", id->location().y);

	
			id->setVisible(false);			

			if (i == 5) {
				lastArrowEndLoc = Nimble::Vector2(id->location().x, id->location().y + id->height());
			}
			prevArrowLoc = i*spacingArrows;
		}
	}

	bool animatedArrow::checkChildLocation(float x, float y) {
		bool isAllowChild = true;
		for (ChildIterator it = childBegin(); it != childEnd(); ++it)
		{
			MultiWidgets::WidgetPtr w = *it;
	
			if (w->name().contains("madhavi")) {
				
				if (w->location().x == x) {
				//	printf("\n equal");
				//	removeChild(w);
					isAllowChild = false;
				}
				else {
					isAllowChild = true;
				}
			}
		}
		return isAllowChild;
	}

	void animatedArrow::removeExtraArrows(float x) {
		
		for (ChildIterator it = childBegin(); it != childEnd(); ++it)
		{
			MultiWidgets::WidgetPtr w = *it;
			if (w->name().contains("madhavi")) {
				if (w->location().x > x) {
					printf("\n removed");
					removeChild(w);				
				}
				else {
				
				}
			}
		}		
	}

	void animatedArrow::removeAllArrows() {

		
		removeChildren();
		prevArrowLoc = 0;
		/*
		for (ChildIterator it = childBegin(); it != childEnd(); ++it)
		{
			MultiWidgets::WidgetPtr w = *it;
			if (w->name().contains("madhavi")) {
				removeChild(w);
			}
		}
		prevArrowLoc = 0;
		*/
	}



	void animatedArrow::displayArrowsOnDistance(float dist, float lastX) {
		
		//removeAllArrows();

		int count = round(dist / spacingArrows);
		for (size_t i = 0; i < count; i++)
		{
			QString tmpName;
			tmpName = "madhavi";

			auto id = MultiWidgets::create<customProjects::imageDisplayer>(this, imagePath, tmpName, true);
			id->setX(prevArrowLoc);
			id->setVisible(true);

			lastArrowEndLoc = Nimble::Vector2(id->location().x, id->location().y + id->height());

			prevArrowLoc = i*spacingArrows;
		}
	}

	void animatedArrow::displayArrowsOnDistanceUpdate(float dist, Nimble::Vector2f _startLoc) {

		Nimble::Vector2f stLoc = _startLoc;
		int count = round(dist / spacingArrows);
		for (size_t i = 0; i < count; i++)
		{			
			auto id = MultiWidgets::create<MultiWidgets::ImageWidget>(parentWidget);
			if (id->load("ArrowR.png")) {
				id->setName("madhavi");
				id->setX(stLoc.x);
				id->setY(stLoc.y);
				id->setVisible(true);
			}
			stLoc.x += spacingArrows;

			if (i == count - 1) {
				lastArrowEndLoc = id->location();
			}
		}
	}

	double animatedArrow::getDistance(Nimble::Vector2f point1, Nimble::Vector2f point2) {
		float diffx = point2.x - point1.x;
		float diffy = point2.y - point1.y;
		return sqrt((double)diffx*diffx + diffy*diffy);
	}

	void animatedArrow::eventProcess(const QByteArray & messageId, Radiant::BinaryData & data)
	{
		//if (messageId == "generateArrows")
		//{
		//	for (auto ci = this->childBegin(); ci != this->childEnd(); ++ci) {
		//		MultiWidgets::WidgetPtr w = (*ci);
		//		if (w.dynamic_pointer_cast<customProjects::imageDisplayer>() != nullptr) {
		//			if (w.dynamic_pointer_cast<customProjects::imageDisplayer>()->imageName == "image_" + QString::number(arrowCount)) {
		//				w.dynamic_pointer_cast<customProjects::imageDisplayer>()->setVisible(true);
		//				if (arrowCount == 5) {							
		//					targetX = w->x();
		//					targetY = w->y();
		//					isArrowReached = true;
		//				}
		//			}
		//		}
		//	}
		//	++arrowCount;
		//}
	}

	void animatedArrow::enableWidget(imageDisplayer &_id)
	{
		imageDisplayer *id;
		id = &_id;
		QString i;
		i = id->getImageName();
		Radiant::info("\nenableWidget " + i.toUtf8());
	}
}
