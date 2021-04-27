#pragma once
#include <Scene.h>

#include <QGraphicsView>
#include <QVBoxLayout>
#include <QWidget>

class Window final : public QWidget
{
	Q_OBJECT

public:
	
	Window();

private:

	QVBoxLayout m_Layout;
	Scene m_Scene;
	QGraphicsView m_View;

};
