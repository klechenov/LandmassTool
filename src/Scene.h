#pragma once
#include <QGraphicsScene>

class Figure;

class Scene final : public QGraphicsScene
{

	Q_OBJECT

public:

	~Scene();

	inline void SetCurrentUsedFigure(Figure* figure) { m_CurrentUsedFigure = figure; };

protected:

	virtual void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
	virtual void keyPressEvent(QKeyEvent* keyEvent) override;

private:

	void CollisionResponce(Figure* figure);
	void MergeFigures(Figure* figure, Figure* addedFigure);
	void EraseFigure(Figure* figure, Figure* eraser);

	enum class Modes
	{
		Pen,
		Selector,
		Eraser
	};

	Figure* m_CurrentUsedFigure = nullptr;
	Modes m_Mode = Modes::Pen;
	bool m_LeftButtonPressed = false;
	bool m_MouseMoved = false;

};