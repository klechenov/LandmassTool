#pragma once
#include <Figure.h>

#include <QCursor>
#include <QGraphicsSceneMouseEvent>

static constexpr qreal WIDTH = 80;

Figure::Figure()
    : m_Brush(Qt::BrushStyle::NoBrush),
      m_Pen(m_Brush, WIDTH, Qt::PenStyle::SolidLine, Qt::PenCapStyle::RoundCap, Qt::PenJoinStyle::RoundJoin)
{
    m_Pen.setColor(QColor(Qt::GlobalColor::black));
    m_Stroker.setWidth(WIDTH);
}

void Figure::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
    setPos(mapToScene(event->pos() - m_StartMouseCoords));
}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	m_StartMouseCoords = event->pos();
	setCursor(QCursor(Qt::ClosedHandCursor));

    Q_UNUSED(event);
}

void Figure::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
    setCursor(QCursor(Qt::ArrowCursor));
    
    Q_UNUSED(event);
}

void Figure::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{	
    painter->setPen(m_Pen);
    painter->setBrush(m_Brush);

	painter->drawPath(path());

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QPainterPath Figure::shape() const
{
	return m_Stroker.createStroke(path());
}
