#pragma once
#include <Figure.h>

#include <QGraphicsScene>

class Scene final : public QGraphicsScene
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

	Figure* m_DrawningPath = nullptr;
	Modes m_Mode = Modes::Pen;
	bool m_LeftButtonPressed = false;
	bool m_MouseMoved = false;

};