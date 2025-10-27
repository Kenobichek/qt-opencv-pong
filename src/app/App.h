#pragma once

class App {
	public:
		virtual ~App() = default;
		virtual int exec() = 0;
};