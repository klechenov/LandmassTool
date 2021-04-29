#pragma once
#include <Scene.h>

#include <QGraphicsPathItem>
#include <QObject>
#include <QPainter>

static constexpr qreal WIDTH = 80;

enum class FigureType
{
	Ellipse,
	Line
};

class Figure final : public QObject, public QGraphicsPathItem
{
	Q_OBJECT

public:

	Figure(Scene* scene);

	inline bool IsEmpty() const { return path().isEmpty(); };
	void SetFigureType(FigureType type);
	QPainterPath shape() const override;
	
private:

	QPointF m_PreviousCoords;
	QPainterPathStroker m_Stroker;
	QBrush m_Brush;
	QPen m_Pen;
	Scene* m_Scene = nullptr;
	FigureType m_Type = FigureType::Ellipse;

	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override {};
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
	void SetEllipseDrawSetting();
	void SetLineDrawSetting();
};