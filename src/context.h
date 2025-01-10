#include <string>
#include <glfw/glfw3.h>

namespace CGL {

class Context {
public:
	Context();
	~Context();

	void update();
	bool alive();

	int width() const;
	int height() const;

	void init();

	GLFWwindow* getWindow() const;

private:
	GLFWwindow* m_window = nullptr;
	int m_width = 800, m_height = 600;
	std::string m_title = "Test Project";
	bool m_alive = false;
};
};