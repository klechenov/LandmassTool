#pragma once
#include <QGraphicsScene>
#include <QPainter>
#include <QBrush>
class Scene : public QGraphicsScene
{

	Q_OBJECT

public:

	~Scene();

protected:

	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void keyPressEvent(QKeyEvent* keyEvent) override;

private:

	enum class Modes
	{
		Pen,
		Selector,
		Eraser
	};

	QPointF m_PreviousPosition;
	QGraphicsPathItem* m_DrawningPath = nullptr;
	Modes m_Mode = Modes::Pen;
	bool m_LeftButtonPressed = false;

};