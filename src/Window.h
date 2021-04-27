#pragma once
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QWidget>

#include <Scene.h>

class Window : public QWidget
{
	Q_OBJECT

public:
	
	Window();

private:

	QVBoxLayout m_Layout;
	Scene m_Scene;
	QGraphicsView m_View;

};
