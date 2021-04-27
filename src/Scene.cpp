#pragma once
#include <Scene.h>

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

	if (m_Mode == Modes::Pen)
	{
		m_DrawningPath = new Figure();
		QPainterPath path;
		path.moveTo(event->scenePos());
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
	if (!m_LeftButtonPressed)
	{
		return;
	}
	m_MouseMoved = true;

	if (m_Mode == Modes::Pen && m_DrawningPath)
	{
		m_DrawningPath->SetLineDrawSetting();
		QPainterPath path = m_DrawningPath->path();
		path.lineTo(event->scenePos());
		m_DrawningPath->setPath(path);
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

	if (m_Mode == Modes::Pen && m_DrawningPath)
	{
		if (!m_MouseMoved)
		{
			m_DrawningPath->SetEllipseDrawSetting();
			QPainterPath path = m_DrawningPath->path();
			path.addEllipse(event->scenePos(), WIDTH / 2, WIDTH / 2);
			m_DrawningPath->setPath(path);			
		}

		m_DrawningPath = nullptr;
	}
	else if (m_Mode == Modes::Selector)
	{
		QGraphicsScene::mouseReleaseEvent(event);
	}

	m_LeftButtonPressed = false;
	m_MouseMoved = false;

	update();
}