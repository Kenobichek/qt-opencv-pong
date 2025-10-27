#pragma once
#include "App.h"
#include <QApplication>

class QtApp : public App {
	public:
		QtApp(int &argc, char **argv) : app_(argc, argv) {}
		int exec() override { return app_.exec(); }

	private:
		QApplication app_;
};