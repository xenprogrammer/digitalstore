#include "drawnArrow.hpp"

namespace customProjects
{
	drawnArrow::drawnArrow(MultiWidgets::WidgetPtr _parentWidget, MultiWidgets::WidgetPtr _centralBubble) :Widget()
	{
		setBackgroundColor(1.0, 1.0, 0.0, 1.0);
		parentWidget = _parentWidget;
		parentWidget->addChild(this);
		centralBubble = _centralBubble;
		renderingEnabled = false;

		basePoint = Nimble::Vector2f(0, 0);
		targetPoint = Nimble::Vector2f(0, 0);

		Radiant::BinaryData d;
		addOperator(std::make_shared<MultiWidgets::MessageSendOperator>(0.01f, "positionMe", d, false));
	}

	void drawnArrow::setRendering(bool _renderingState)
	{
		renderingEnabled = _renderingState;
	}
	
	void drawnArrow::renderBackground(Luminous::RenderContext & r) const
	{
		Radiant::info("renderBackground " + (QString::number(basePoint.x)).toUtf8());
		if (renderingEnabled)
		{
			Luminous::Style s;
			s.setStrokeColor(Radiant::Color(1, 0, 0, 1));
			s.setStrokeWidth(1);

			float deltaX;
			float deltaY;
			deltaX = 15;
			deltaY = 15;

			Nimble::Vector2f basePoint1;
			Nimble::Vector2f targetPoint1;

			basePoint1 = basePoint;
			targetPoint1 = Nimble::Vector2f(basePoint.x - deltaX, basePoint.y - deltaY);
			r.drawLine(basePoint1, targetPoint1, s);
			
			basePoint1 = targetPoint1;
			targetPoint1 = Nimble::Vector2f(basePoint.x, basePoint.y - deltaY);
			r.drawLine(basePoint1, targetPoint1, s);

			basePoint1 = targetPoint1;
			targetPoint1 = Nimble::Vector2f(basePoint.x + deltaX, basePoint.y);
			r.drawLine(basePoint1, targetPoint1, s);

			basePoint1 = targetPoint1;
			targetPoint1 = Nimble::Vector2f(basePoint.x, basePoint.y + deltaY);
			r.drawLine(basePoint1, targetPoint1, s);

			basePoint1 = targetPoint1;
			targetPoint1 = Nimble::Vector2f(basePoint.x - deltaX, basePoint.y + deltaY);
			r.drawLine(basePoint1, targetPoint1, s);

			basePoint1 = targetPoint1;
			targetPoint1 = basePoint;
			r.drawLine(basePoint1, targetPoint1, s);

			for (int i = 0; ; ++i)
			{
				Radiant::info("i = " + (QString::number(i)).toUtf8());
				float equatedDistance;
				equatedDistance = (i * arrowDistance);

				float distanceRatio;
				distanceRatio = equatedDistance / totalDistance1;
				if (distanceRatio < 1)
				{
					setBasePoint(getEquatedPoint(arrowStartPoint1, arrowEndPoint1, equatedDistance));
				}
				else
				{
					break;
				}
			}
		}
	}
	
	void drawnArrow::setBasePoint(Nimble::Vector2f _basePoint)
	{
		//basePoint = _basePoint;
		basePoint = mapFromParent(_basePoint);
		Radiant::info("renderBackground _basePoint x = " + (QString::number(_basePoint.x)).toUtf8());
	}

	void drawnArrow::setTargetPoint(Nimble::Vector2f _targetPoint)
	{
		//targetPoint = _targetPoint;
		//targetPoint = mapFromParent(_targetPoint);
	}

	void drawnArrow::setValues(float _arrowDistance, float _totalDistance1, Nimble::Vector2f _arrowStartPoint1, Nimble::Vector2f _arrowEndPoint1)
	{
		arrowDistance = _arrowDistance;
		totalDistance1 = _totalDistance1;
		arrowStartPoint1 = _arrowStartPoint1;
		arrowEndPoint1 = _arrowEndPoint1;
	}

	void drawnArrow::eventProcess(const QByteArray & messageId, Radiant::BinaryData & data)
	{
		if (messageId == "positionMe")
		{
			Nimble::Vector2f centerLocation = Nimble::Vector2f(centralBubble->x() + centralBubble->width()/2, centralBubble->y() + centralBubble->height() / 2);
			setCenterLocation(centerLocation);
		}
	}
	Nimble::Vector2f drawnArrow::getEquatedPoint(Nimble::Vector2f _arrowStartPoint, Nimble::Vector2f _arrowEndPoint, float _dist)
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

	double drawnArrow::getDistance(Nimble::Vector2f point1, Nimble::Vector2f point2) {
		float diffx = point2.x - point1.x;// x2 - x1;
		float diffy = point2.y - point1.y;//y2 - y1;
		return (double)sqrt(diffx*diffx + diffy*diffy);
	}
}
