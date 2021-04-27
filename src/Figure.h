#pragma once
#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsPathItem>

class Figure : public QObject, public QGraphicsPathItem
{
	Q_OBJECT

private:

	QPointF m_StartMouseCoords;

	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;

};