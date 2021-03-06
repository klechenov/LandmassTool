#pragma once
#include <Scene.h>
#include <Figure.h>

#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QPainterPath>

Scene::~Scene()
{
	for (QGraphicsItem* item : items(Qt::SortOrder::AscendingOrder))
	{
		delete item;
	}
}

void Scene::keyPressEvent(QKeyEvent* keyEvent)
{
	if (!m_LeftButtonPressed)
	{
		switch (keyEvent->key())
		{
		case Qt::Key::Key_1:
			m_Mode = Modes::Pen;
			break;
		case Qt::Key::Key_2:
			m_Mode = Modes::Selector;
			break;
		case Qt::Key::Key_3:
			m_Mode = Modes::Eraser;
			break;
		}
	}
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->button() != Qt::MouseButton::LeftButton)
	{
		return;
	}

	m_LeftButtonPressed = true;

	if (m_Mode == Modes::Pen || m_Mode == Modes::Eraser)
	{
		m_CurrentUsedFigure = new Figure(this);
		QPainterPath path;
		path.moveTo(event->scenePos());
		m_CurrentUsedFigure->setPath(path);

		addItem(m_CurrentUsedFigure);
	}
	else if(m_Mode == Modes::Selector)
	{
		QGraphicsScene::mousePressEvent(event);
	}

	update();
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	if (!m_LeftButtonPressed)
	{
		return;
	}
	m_MouseMoved = true;

	if ((m_Mode == Modes::Pen || m_Mode == Modes::Eraser) && m_CurrentUsedFigure)
	{
		m_CurrentUsedFigure->SetFigureType(FigureType::Line);
		QPainterPath path = m_CurrentUsedFigure->path();
		path.lineTo(event->scenePos());
		m_CurrentUsedFigure->setPath(path);
	}
	else if (m_Mode == Modes::Selector)
	{
		QGraphicsScene::mouseMoveEvent(event);
	}

	update();
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->button() != Qt::MouseButton::LeftButton)
	{
		return;
	}

	if ((m_Mode == Modes::Pen || m_Mode == Modes::Eraser) && m_CurrentUsedFigure)
	{
		if (!m_MouseMoved)
		{
			m_CurrentUsedFigure->SetFigureType(FigureType::Ellipse);
			QPainterPath path = m_CurrentUsedFigure->path();
			path.addEllipse(event->scenePos(), WIDTH / 2, WIDTH / 2);
			m_CurrentUsedFigure->setPath(path);
		}
	}
	else if (m_Mode == Modes::Selector)
	{
		QGraphicsScene::mouseReleaseEvent(event);
	}

	if (m_CurrentUsedFigure)
	{
		CollisionResponce(m_CurrentUsedFigure);
		if (m_Mode == Modes::Eraser)
		{
			removeItem(m_CurrentUsedFigure);
		}
	}


	m_CurrentUsedFigure = nullptr;
	m_LeftButtonPressed = false;
	m_MouseMoved = false;

	update();
}

void Scene::CollisionResponce(Figure* figure)
{
	QList<QGraphicsItem*> collidedItems = collidingItems(figure);
	
	for (QGraphicsItem* item : collidedItems)
	{
		Figure* pathItem = dynamic_cast<Figure*>(item);
		if (pathItem)
		{
			if (m_Mode == Modes::Pen || m_Mode == Modes::Selector)
			{
				MergeFigures(pathItem, figure);
			}
			else if (m_Mode == Modes::Eraser)
			{
				EraseFigure(pathItem, figure);
			}
		}
	}
}

void Scene::MergeFigures(Figure* figure, Figure* addedFigure)
{
	/*QPainterPath figurePath = figure->path();
	const QPainterPath intersected = figure->path().intersected(addedFigure->path());
	QPainterPath newPath = addedFigure->path() - intersected;
	if (!newPath.isEmpty())
	{
		figurePath.addPath(newPath);
		figure->setPath(figurePath);
	}
	removeItem(addedFigure);*/

	QPainterPath path = figure->path();
	QPainterPath addedPath = addedFigure->path();
	path.addPath(addedPath);
	figure->setPath(path);
	removeItem(addedFigure);
}

void Scene::EraseFigure(Figure* figure, Figure* eraser)
{
	QPainterPath newpath;
	newpath = figure->path() - eraser->shape();
	if (newpath.isEmpty())
	{
		removeItem(figure);
	}
	else
	{
		figure->setPath(newpath);
	}
}
