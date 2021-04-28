#pragma once
#include <Scene.h>

#include <QGraphicsPathItem>
#include <QObject>
#include <QPainter>

static constexpr qreal WIDTH = 80;

class Figure final : public QObject, public QGraphicsPathItem
{
	Q_OBJECT

public:

	Figure(Scene* scene);

	void SetEllipseDrawSetting();
	void SetLineDrawSetting();

	inline bool IsEmpty() const { return path().isEmpty(); };

private:

	QPointF m_StartMouseCoords;
	QPainterPathStroker m_Stroker;
	QBrush m_Brush;
	QPen m_Pen;
	Scene* m_Scene = nullptr;

	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget = nullptr) override;
	QPainterPath shape() const override;

};