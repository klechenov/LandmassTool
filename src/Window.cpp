#pragma once
#include <Window.h>

#include <QScrollBar>


Window::Window()
	: m_Layout(this), m_View(&m_Scene)
{
	m_Layout.addWidget(&m_View);
	m_View.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_View.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_View.setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	m_View.horizontalScrollBar()->blockSignals(true);
	m_View.verticalScrollBar()->blockSignals(true);
	m_Scene.setItemIndexMethod(QGraphicsScene::ItemIndexMethod::BspTreeIndex);
	m_Scene.setSceneRect(0, 0, 2000, 2000);
}