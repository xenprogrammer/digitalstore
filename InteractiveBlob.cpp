#include <MultiWidgets/StayInsideParentOperator.hpp>
#include "InteractiveBlob.hpp"
#include "animatedArrow.hpp"
#include "drawnArrow.hpp"


#define PI 3.14

namespace customProjects
{
	InteractiveBlob::InteractiveBlob(MultiWidgets::WidgetPtr _parent, MultiWidgets::WidgetPtr _centralBubble, int _myIndex, int _totalCount, int _radius, MultiWidgets::WidgetPtr _linkedArrow)
	{
		setBackgroundColor(0.0, 0.0, 1.0, 1.0);
		centralBubble = _centralBubble;
		myIndex = _myIndex;
		totalCount = _totalCount;
		radius = _radius;
		linkedArrow = _linkedArrow;
		myEquatedAngle = 2 * PI * myIndex / totalCount;
		isMouseDown = false;
		parent = _parent;
		_parent->addChild(this);
		previousDistance = -100;
		Nimble::Vector2f startPoint = Nimble::Vector2(centralBubble->x() + (centralBubble->width() / 2), centralBubble->y() + (centralBubble->height() / 2));
		setCenterLocation(startPoint);
		addOperator(std::make_shared<MultiWidgets::StayInsideParentOperator>());
		Nimble::Vector2f basePoint = getRotatedPoint(startPoint, radius, myEquatedAngle);
		tweenToLocation(basePoint, 1.5);
		//Radiant::BinaryData d;
		//addOperator(std::make_shared<MultiWidgets::MessageSendOperator>(6.5f, "startFollowingBubble", d, true));
		eventAddListener("finger-down", [=]
		{
			isMouseDown = true;
		});

		eventAddListener("finger-up", [=]
		{
			isMouseDown = false;
		});
		//setCenterLocation(Nimble::Vector2(0,0));
		//setCenterLocation(getRotatedPoint(centerPoint, radius, myAngle));
		/*
		centerPoint = Nimble::Vector2f(centralBubble->x() - (centralBubble->width() / 2), centralBubble->y() - (centralBubble->height() / 2));
		myIndex = _myIndex;
		totalCount = _totalCount;
		radius = _radius;
		isMouseDown = false;

		masterCount = 0;

		QString path = QString::number(myIndex) + ".png";
		if (load(path))
		{
			myEquatedAngle = 2 * PI * myIndex / totalCount;
			//setX(this->location().x - (width() / 2));
			//setY(this->location().y - (height() / 2));
			//setX(centerPoint.x + radius * cos(myEquatedAngle));
			//setY(centerPoint.y + radius * sin(myEquatedAngle));
			tweenToBaseLocation(centerPoint.x + radius * cos(myEquatedAngle), centerPoint.y + radius * sin(myEquatedAngle), centerPoint);

			//Radiant::BinaryData d;
			//addOperator(std::make_shared<MultiWidgets::MessageSendOperator>(5.0f, "triggerTrail", d, true));

			eventAddListener("finger-down", [=]
			{
				isMouseDown = true;
			});

			eventAddListener("finger-up", [=]
			{
				isMouseDown = false;
			});
		}
		*/
	}

	void InteractiveBlob::tweenToLocation(Nimble::Vector2f targetLocation, float _duration)
	{
		Nimble::Vector2f currentLocation = Nimble::Vector2f(x()+width()/2,y()+height()/2);
		auto anim = std::make_shared < MultiWidgets::AnimatorCenterLocation>();
		anim->bouncyAnimation(_duration, currentLocation, targetLocation);
		addOperator(anim);
		anim->eventAddListener("finished", [=] 
		{
			Radiant::BinaryData d;
			addOperator(std::make_shared<MultiWidgets::MessageSendOperator>(0.05f, "positionRelativeToBubble1", d, false));

			Nimble::Vector2f basePoint = Nimble::Vector2f(centralBubble->x() + (centralBubble->width() / 2), centralBubble->y() + (centralBubble->height() / 2));
			linkedArrow.dynamic_pointer_cast<customProjects::drawnArrow>()->setBasePoint(basePoint);

			Nimble::Vector2f targetPoint = Nimble::Vector2f(location().x, location().y);
			linkedArrow.dynamic_pointer_cast<customProjects::drawnArrow>()->setTargetPoint(targetPoint);

			linkedArrow.dynamic_pointer_cast<customProjects::drawnArrow>()->setRendering(true);
		});
	}

	void InteractiveBlob::removeAllArrows1()
	{
		/*
		while (getClipNum())
		{
			for (ChildIterator it = arrow->childBegin(); it != arrow->childEnd(); ++it)
			{
				MultiWidgets::WidgetPtr w = *it;



				if (w->name().contains("madhavi")) {

					printf("\n name =");
					printf(w->name());
					arrow->removeChild(w);
				}

			}
		}
		*/
	}

	Nimble::Vector2f InteractiveBlob::getRotatedPoint(Nimble::Vector2f _point, float _radius, float _angle)
	{
		float xC;
		xC = _point.x + _radius * cos(_angle);
		float yC;
		yC = _point.y + _radius * sin(_angle);
		Nimble::Vector2 tmpPoint = Nimble::Vector2f(xC, yC);
		return tmpPoint;
	}

	void InteractiveBlob::updateArrows()
	{
		/*
		arrowStartPoint = mapFromParent(Nimble::Vector2f(centralBubble->location().x, centralBubble->location().y));
		arrowEndPoint = mapFromParent(Nimble::Vector2f(this->location().x, this->location().y));


		double totalDistance;
		totalDistance = getDistance(arrowStartPoint, arrowEndPoint);

		Nimble::Vector2f arrowStartPoint1;
		Nimble::Vector2f arrowEndPoint1;

		arrowStartPoint1 = getEquatedPoint(arrowStartPoint, arrowEndPoint, centralBubble->width() / 2);
		arrowEndPoint1 = getEquatedPoint(arrowStartPoint, arrowEndPoint, totalDistance - 15);
		totalDistance = getDistance(arrowStartPoint1, arrowEndPoint1);

		arrow.dynamic_pointer_cast<customProjects::animatedArrow>()->displayArrowsOnDistance(totalDistance, 0);
		//arrow.dynamic_pointer_cast<customProjects::animatedArrow>()->displayArrowsOnDistanceUpdate(totalDistance, arrowStartPoint1);

		for (int i = 0; ; ++i)
		{
		float distanceRatio;
		distanceRatio = (i * arrowDistance) / totalDistance;
		if (distanceRatio < 1)
		{
		var del : Number;
		del = 1 - distanceRatio;

		var pointX : Number;
		pointX = Number(del * arrowStartPoint1.x) + Number(distanceRatio * arrowEndPoint1.x);

		var pointY : Number;
		pointY = Number(del * arrowStartPoint1.y) + Number(distanceRatio * arrowEndPoint1.y);

		var myArrow : mcArrow;
		myArrow = new mcArrow();
		addChild(myArrow);
		myArrow.x = pointX;
		myArrow.y = pointY;
		myArrow.rotation = myDegrees + 180;
		}
		else
		{
		break;
		}
		}

		float angle = myRadians+PI;
		arrow->setRotation(angle);
		prevDistance = totalDistance;

		*/
	}

	double InteractiveBlob::getDistance(Nimble::Vector2f point1, Nimble::Vector2f point2) {
		float diffx = point2.x - point1.x;// x2 - x1;
		float diffy = point2.y - point1.y;//y2 - y1;
		return (double) sqrt(diffx*diffx + diffy*diffy);
	}

	Nimble::Vector2f InteractiveBlob::getEquatedPoint(Nimble::Vector2f _arrowStartPoint, Nimble::Vector2f _arrowEndPoint, float _dist)
	{
		Nimble::Vector2f arrowStartPoint;
		Nimble::Vector2f arrowEndPoint;

		arrowStartPoint = Nimble::Vector2f(_arrowStartPoint.x, _arrowStartPoint.y);
		arrowEndPoint = Nimble::Vector2f(_arrowEndPoint.x, _arrowEndPoint.y);

		double totalDistance;
		totalDistance = getDistance(arrowStartPoint, arrowEndPoint);

		float distanceRatio;
		distanceRatio = _dist / totalDistance;

		float del;
		del = 1 - distanceRatio;

		float pointX;
		pointX = (del * arrowStartPoint.x) + (distanceRatio * arrowEndPoint.x);

		float pointY;
		pointY = (del * arrowStartPoint.y) + (distanceRatio * arrowEndPoint.y);

		return Nimble::Vector2f(pointX, pointY);
	}
	
	void InteractiveBlob::removeAllArrows()
	{
		/*
		while (getClipNum())
		{
			for (ChildIterator it = arrow->childBegin(); it != arrow->childEnd(); ++it)
			{
				MultiWidgets::WidgetPtr w = *it;
			
				if (w->name().contains("madhavi")) {

					printf("\n name =");
					printf(w->name());
					arrow->removeChild(w);
				}
				
			}
		}
	*/
	}
	
	int InteractiveBlob::getClipNum()
	{
		/*
		int count;
		count = 0;

		for (ChildIterator it = arrow->childBegin(); it != arrow->childEnd(); ++it)
		{
			MultiWidgets::WidgetPtr w = *it;
			if (w->name().contains("madhavi"))
			{
				++count;
			}
		}
		return count;
		*/
		return 0;
	}

	void InteractiveBlob::updateArrows1()
	{/*
	 Nimble::Vector2f arrowStartPoint;
	 Nimble::Vector2f arrowEndPoint;
	 Nimble::Vector2f centerPoint;

	 float arrowDistance;
	 arrowDistance = 10.0f;

	 arrowStartPoint = Nimble::Vector2f(centralBubble->x() + (centralBubble->width() / 2), centralBubble->y() + (centralBubble->height() / 2));
	 arrowEndPoint = Nimble::Vector2f(x() - width() / 2, y() + height() / 2);

	 double totalDistance;
	 totalDistance = getDistance(arrowStartPoint, arrowEndPoint);

	 Nimble::Vector2f arrowStartPoint1;
	 Nimble::Vector2f arrowEndPoint1;
	 arrowStartPoint1 = getEquatedPoint(arrowStartPoint, arrowEndPoint, centralBubble->width() / 2);
	 arrowEndPoint1 = getEquatedPoint(arrowStartPoint, arrowEndPoint, totalDistance - (width() / 2));
	 double totalDistance1;
	 totalDistance1 = getDistance(arrowStartPoint1, arrowEndPoint1);

	 if (previousDistance == -100)
	 {
	 for (int i = 0; ; ++i)
	 {
	 float equatedDistance;
	 equatedDistance = (i * arrowDistance);

	 float distanceRatio;
	 distanceRatio = equatedDistance / totalDistance1;
	 if (distanceRatio < 1)
	 {
	 Nimble::Vector2f arrowTempPoint;
	 arrowTempPoint = getEquatedPoint(arrowStartPoint1, arrowEndPoint1, equatedDistance);
	 auto arrow = MultiWidgets::create<customProjects::imageDisplayer>(this, "ArrowR.png", "arrow_", true);
	 arrow->setMyLocation(arrowTempPoint);
	 }
	 else
	 {
	 break;
	 }
	 }
	 previousDistance = totalDistance;
	 }
	 else if (previousDistance == totalDistance)
	 {
	 // do not do anything
	 }
	 else if (previousDistance < totalDistance)
	 {
	 // add arrows

	 for (int i = 0; ; ++i)
	 {
	 float equatedDistance;
	 equatedDistance = (i * arrowDistance);

	 float distanceRatio;
	 distanceRatio = equatedDistance / totalDistance1;
	 if (distanceRatio < 1)
	 {
	 Nimble::Vector2f arrowTempPoint;
	 arrowTempPoint = getEquatedPoint(arrowStartPoint1, arrowEndPoint1, equatedDistance);
	 auto arrow = MultiWidgets::create<customProjects::imageDisplayer>(parent, "ArrowR.png", "arrow_", true);
	 arrow->setMyLocation(arrowTempPoint);
	 }
	 else
	 {
	 break;
	 }
	 }
	 previousDistance = totalDistance;
	 }
	 else if (previousDistance > totalDistance)
	 {
	 // remove arrows
	 for (int i = 0; ; ++i)
	 {
	 float equatedDistance;
	 equatedDistance = (i * arrowDistance);

	 float distanceRatio;
	 distanceRatio = equatedDistance / totalDistance1;
	 if (distanceRatio < 1)
	 {
	 Nimble::Vector2f arrowTempPoint;
	 arrowTempPoint = getEquatedPoint(arrowStartPoint1, arrowEndPoint1, equatedDistance);
	 auto arrow = MultiWidgets::create<customProjects::imageDisplayer>(this, "ArrowR.png", "arrow_", true);
	 arrow->setMyLocation(arrowTempPoint);
	 }
	 else
	 {
	 break;
	 }
	 }
	 previousDistance = totalDistance;
	 }
	 */
	}

	void InteractiveBlob::eventProcess(const QByteArray & messageId, Radiant::BinaryData & data)
	{
		float xChange;
		float yChange;
		float xMove;
		float yMove;
		if (messageId == "triggerTrail")
		{
			//Radiant::info("\nTrigger Trail");
			Radiant::BinaryData d;
			addOperator(std::make_shared<MultiWidgets::MessageSendOperator>(1.0f, "positionRelativeToBubble", d, true));
		}
		else if (messageId == "positionRelativeToBubble")
		{
			

			//myRadians = Math.atan2(centralBubble.y - y, centralBubble.x - x);
			//myDegrees = Math.round((myRadians * 180 / Math.PI));
			if (isMouseDown)
			{
			}
			else
			{
				xChange = (centralBubble->x() + radius * cos(myEquatedAngle) - this->location().x);
				yChange = (centralBubble->y() + radius * sin(myEquatedAngle) - this->location().y);
				xMove = (xChange / 20);
				yMove = (yChange / 20);
				this->setX(this->location().x + xMove);
				this->setY(this->location().y + yMove);
			}
			updateArrows1();

			Radiant::BinaryData d;
			addOperator(std::make_shared<MultiWidgets::MessageSendOperator>(0.05f, "positionRelativeToBubble1", d, false));
		}
		else if (messageId == "startFollowingBubble")
		{
			Radiant::BinaryData d;
			addOperator(std::make_shared<MultiWidgets::MessageSendOperator>(0.05f, "positionRelativeToBubble1", d, false));
		}
		else if (messageId == "positionRelativeToBubble1")
		{
			//Radiant::info("\neventProcess " + messageId);
			if (isMouseDown)
			{
			}
			else
			{
				Nimble::Vector2f startPoint = Nimble::Vector2(centralBubble->x() + (centralBubble->width() / 2), centralBubble->y() + (centralBubble->height() / 2));
				Nimble::Vector2f basePoint = getRotatedPoint(startPoint, radius, myEquatedAngle);
				xChange = (basePoint.x - x());
				yChange = (basePoint.y - y());
				xMove = (xChange / 20);
				yMove = (yChange / 20);
				Nimble::Vector2f tempPoint = Nimble::Vector2(basePoint.x + xMove, basePoint.y + yMove);

				if (tempPoint.x >= 0 && tempPoint.x <= parent->width())
				{
					setX(tempPoint.x - width()/2);
				}
				if (tempPoint.y >= 0 && tempPoint.y <= parent->height())
				{
					setY(tempPoint.y - height() / 2);
				}
				updateArrows2();
			}
			//drawing line
			/*
			Nimble::Vector2f basePoint = Nimble::Vector2f(centralBubble->x() + (centralBubble->width() / 2), centralBubble->y() + (centralBubble->height() / 2));
			linkedArrow.dynamic_pointer_cast<customProjects::drawnArrow>()->setBasePoint(basePoint);

			Nimble::Vector2f targetPoint = Nimble::Vector2f(location().x + width() / 2, location().y + height());
			linkedArrow.dynamic_pointer_cast<customProjects::drawnArrow>()->setTargetPoint(targetPoint);
			*/
			//drawing line
		}
	}
	
	void InteractiveBlob::updateArrows2()
	{
		Nimble::Vector2f arrowStartPoint;
		Nimble::Vector2f arrowEndPoint;
		Nimble::Vector2f centerPoint;

		float arrowDistance;
		arrowDistance = 10.0f;

		arrowStartPoint = Nimble::Vector2f(centralBubble->x() + (centralBubble->width() / 2), centralBubble->y() + (centralBubble->height() / 2));
		arrowEndPoint = Nimble::Vector2f(x() + width() / 2, y() + height() / 2);

		double totalDistance;
		totalDistance = getDistance(arrowStartPoint, arrowEndPoint);

		Nimble::Vector2f arrowStartPoint1;
		Nimble::Vector2f arrowEndPoint1;
		arrowStartPoint1 = getEquatedPoint(arrowStartPoint, arrowEndPoint, centralBubble->width() / 2);
		arrowEndPoint1 = getEquatedPoint(arrowStartPoint, arrowEndPoint, totalDistance - (width() / 2));
		double totalDistance1;
		totalDistance1 = getDistance(arrowStartPoint1, arrowEndPoint1);

		if (previousDistance == -100)
		{
			Radiant::info("Start of the subroutine");
			for (int i = 0; ; ++i)
			{
				Radiant::info("i = " + (QString::number(i)).toUtf8());
				float equatedDistance;
				equatedDistance = (i * arrowDistance);

				float distanceRatio;
				distanceRatio = equatedDistance / totalDistance1;
				if (distanceRatio < 1)
				{
					Nimble::Vector2f arrowTempPoint;
					arrowTempPoint = getEquatedPoint(arrowStartPoint1, arrowEndPoint1, equatedDistance);
					//auto arrow = MultiWidgets::create<customProjects::imageDisplayer>(this, "ArrowR.png", "arrow_", true);
					//auto arrow = MultiWidgets::create<MultiWidgets::Widget>();
					//addChild(arrow);
					//arrow->setCenterLocation(mapFromParent(arrowTempPoint));
					linkedArrow.dynamic_pointer_cast<customProjects::drawnArrow>()->setBasePoint(arrowTempPoint);
				}
				else
				{
					break;
				}
			}
			previousDistance = totalDistance;
		}
		else if (previousDistance == totalDistance)
		{
			Radiant::info("previousDistance == totalDistance");
			// do not do anything
		}
		else if (previousDistance < totalDistance)
		{
			Radiant::info("previousDistance < totalDistance");
			// add arrows

			for (int i = 0; ; ++i)
			{
				Radiant::info("i = " + (QString::number(i)).toUtf8());
				float equatedDistance;
				equatedDistance = (i * arrowDistance);

				float distanceRatio;
				distanceRatio = equatedDistance / totalDistance1;
				if (distanceRatio < 1)
				{
					
					Nimble::Vector2f arrowTempPoint;
					arrowTempPoint = getEquatedPoint(arrowStartPoint1, arrowEndPoint1, equatedDistance);
					/*
					//auto arrow = MultiWidgets::create<customProjects::imageDisplayer>(this, "ArrowR.png", "arrow_", true);
					auto arrow = MultiWidgets::create<MultiWidgets::Widget>();
					arrow->setName("arrow");
					arrow->setSize(5, 5);
					arrow->setBackgroundColor(1.0, 1.0, 0.0, 1.0);
					addChild(arrow);
					arrow->setCenterLocation(mapFromParent(arrowTempPoint));
					*/
					linkedArrow.dynamic_pointer_cast<customProjects::drawnArrow>()->setBasePoint(arrowTempPoint);
				}
				else
				{
					break;
				}
			}
			previousDistance = totalDistance;
		}
		else if (previousDistance > totalDistance)
		{
			Radiant::info("previousDistance > totalDistance");
			// remove arrows
			for (int i = 0; ; ++i)
			{
				Radiant::info("i = " + (QString::number(i)).toUtf8());
				float equatedDistance;
				equatedDistance = (i * arrowDistance);

				float distanceRatio;
				distanceRatio = equatedDistance / totalDistance1;
				if (distanceRatio < 1)
				{
					Nimble::Vector2f arrowTempPoint;
					arrowTempPoint = getEquatedPoint(arrowStartPoint1, arrowEndPoint1, equatedDistance);
					/*
					//auto arrow = MultiWidgets::create<customProjects::imageDisplayer>(this, "ArrowR.png", "arrow_", true);
					auto arrow = MultiWidgets::create<MultiWidgets::Widget>();
					arrow->setName("arrow");
					arrow->setSize(5, 5);
					arrow->setBackgroundColor(1.0, 1.0, 0.0, 1.0);
					addChild(arrow);
					arrow->setCenterLocation(mapFromParent(arrowTempPoint));
					*/
					linkedArrow.dynamic_pointer_cast<customProjects::drawnArrow>()->setBasePoint(arrowTempPoint);
				}
				else
				{
					break;
				}
			}
			previousDistance = totalDistance;
		}
	}
}
