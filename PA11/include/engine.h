#ifndef ENGINE_H
#define ENGINE_H

#include "window.h"
#include "graphics.h"
#include <sys/time.h>
#include <assert.h>

class Engine
{
  public:
    Engine(std::string name, int width, int height);
    Engine(std::string name);
    ~Engine();
    bool Initialize();
    void Run();
    void Keyboard(bool codes[]);
    unsigned int getDT();
    long long GetCurrentTimeMillis();

  private:
    // Window related variables
    Window *m_window;
    std::string m_WINDOW_NAME;
    int m_WINDOW_WIDTH;
    int m_WINDOW_HEIGHT;
    bool m_FULLSCREEN;
    SDL_Event m_event;

    //time
    unsigned int m_DT;
    long long m_currentTimeMillis;

    // Graphics
    Graphics *m_graphics;
    bool m_running;
    bool codes[15] = {false};
};

#endif // ENGINE_H
