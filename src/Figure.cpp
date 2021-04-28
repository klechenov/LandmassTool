#pragma once
#include <Figure.h>

#include <QCursor>
#include <QGraphicsSceneMouseEvent>

Figure::Figure(Scene* scene)
		: m_Scene(scene)
{
	m_Stroker.setWidth(WIDTH);
	m_Stroker.setCapStyle(Qt::PenCapStyle::RoundCap);
	m_Stroker.setJoinStyle(Qt::PenJoinStyle::RoundJoin);
}

void Figure::SetFigureType(FigureType type)
{
	m_Type = type;
	if (m_Type == FigureType::Ellipse)
	{
		SetEllipseDrawSetting();
	}
	else if (m_Type == FigureType::Line)
	{
		SetLineDrawSetting();
	}
}

void Figure::SetEllipseDrawSetting()
{
	m_Brush.setStyle(Qt::BrushStyle::SolidPattern);
	m_Brush.setColor(QColor(Qt::GlobalColor::black));
	m_Pen.setStyle(Qt::PenStyle::NoPen);
}

void Figure::SetLineDrawSetting()
{
	m_Brush.setStyle(Qt::BrushStyle::NoBrush);
	m_Pen.setBrush(m_Brush);
	m_Pen.setWidth(WIDTH);
	m_Pen.setStyle(Qt::PenStyle::SolidLine);
	m_Pen.setCapStyle(Qt::PenCapStyle::RoundCap);
	m_Pen.setJoinStyle(Qt::PenJoinStyle::RoundJoin);
	m_Pen.setColor(QColor(Qt::GlobalColor::black));
}

void Figure::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	m_Scene->SetCurrentUsedFigure(this);
	m_PreviousCoords = event->pos();
	setCursor(QCursor(Qt::ClosedHandCursor));

	Q_UNUSED(event);
}

void Figure::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	const qreal x = event->pos().x() - m_PreviousCoords.x();
	const qreal y = event->pos().y() - m_PreviousCoords.y();
	QPainterPath painterPath = path();
	painterPath.translate(x, y);
	setPath(painterPath);
	m_PreviousCoords = event->pos();
}

void Figure::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	setCursor(QCursor(Qt::ArrowCursor));
	
	Q_UNUSED(event);
}

void Figure::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget /*= nullptr*/)
{	
	if (IsEmpty())
	{
		return;
	}

	painter->setPen(m_Pen);
	painter->setBrush(m_Brush);

	painter->drawPath(path());

	Q_UNUSED(option);
	Q_UNUSED(widget);
}

QPainterPath Figure::shape() const
{
	if (m_Type == FigureType::Ellipse)
	{
		return path();
	}
	else if (m_Type == FigureType::Line)
	{
		return m_Stroker.createStroke(path());
	}
	
	return QPainterPath();
}