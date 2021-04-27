#pragma once
#include <Scene.h>
#include <Figure.h>

#include <QGraphicsPathItem>
#include <QGraphicsSceneMouseEvent>
#include <QPainterPath>
#include <QKeyEvent>

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
	if (event->button() == Qt::MouseButton::LeftButton)
	{
		m_LeftButtonPressed = true;
	}

	if (m_Mode == Modes::Pen)
	{
		m_DrawningPath = new Figure();
		m_PreviousPosition = event->scenePos();
		QPainterPath path;
		path.moveTo(m_PreviousPosition);
		m_DrawningPath->setPath(path);

		addItem(m_DrawningPath);
	}
	else if(m_Mode == Modes::Selector)
	{
		QGraphicsScene::mousePressEvent(event);
	}

	update();
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent* event)
{
	if (m_Mode == Modes::Pen && m_DrawningPath)
	{
		QPainterPath path = m_DrawningPath->path();
		m_PreviousPosition = event->scenePos();
		path.lineTo(m_PreviousPosition);
		m_DrawningPath->setPath(path);
	}
	else if (m_Mode == Modes::Selector)
	{
		QGraphicsScene::mousePressEvent(event);
	}

	update();
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent* event)
{
	if (event->button() == Qt::MouseButton::LeftButton)
	{
		m_LeftButtonPressed = false;
	}

	if (m_Mode == Modes::Pen)
	{
		m_DrawningPath = nullptr;
	}
	else if (m_Mode == Modes::Selector)
	{
		QGraphicsScene::mousePressEvent(event);
	}

	update();
}