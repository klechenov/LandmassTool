#pragma once

#include <QGraphicsPathItem>
#include <QObject>
#include <QPainter>

class Figure : public QObject, public QGraphicsPathItem
{
	Q_OBJECT

public:

	Figure();

private:

	QPointF m_StartMouseCoords;
	QPainterPathStroker m_Stroker;
	QBrush m_Brush;
	QPen m_Pen;

	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
	QPainterPath shape() const override;

};