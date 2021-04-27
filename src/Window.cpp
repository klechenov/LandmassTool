#pragma once
#include <Window.h>


Window::Window()
	: m_Layout(this), m_View(&m_Scene)
{
	setFixedSize(1280, 720);

	m_Layout.addWidget(&m_View);
	m_View.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_View.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_View.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	m_Scene.setItemIndexMethod(QGraphicsScene::ItemIndexMethod::BspTreeIndex);
	m_Scene.setSceneRect(0, 0, 2000, 2000);

}