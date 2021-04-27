#pragma once
#include <Figure.h>

#include <QCursor>
#include <QPainter>
#include <QBrush>

void Figure::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    setPos(mapToScene(event->pos() - m_StartMouseCoords));
}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if (path().contains(event->pos()))
    {
		m_StartMouseCoords = event->pos();
		setCursor(QCursor(Qt::ClosedHandCursor));
    }

    Q_UNUSED(event);
}

void Figure::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    setCursor(QCursor(Qt::ArrowCursor));
    
    Q_UNUSED(event);
}

void Figure::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{	
    QBrush brush(Qt::BrushStyle::NoBrush);
    QPen pen(brush, 80, Qt::PenStyle::SolidLine, Qt::PenCapStyle::RoundCap, Qt::PenJoinStyle::RoundJoin);
    pen.setColor(QColor(Qt::GlobalColor::black));

    painter->setPen(pen);
    painter->setBrush(brush);

	painter->drawPath(path());

    Q_UNUSED(option);
    Q_UNUSED(widget);
}
