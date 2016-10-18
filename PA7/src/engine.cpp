#include "engine.h"

Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
}

Engine::Engine(string name)
{
  m_WINDOW_NAME = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH = 0;
  m_FULLSCREEN = true;
}

Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize(char * configFile)
{
  // Start a window
  m_window = new Window();

  if(!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics();
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT, configFile))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }
  // No errors
  return true;
}



void Engine::Run()
{
  m_running = true;
  int code = 0;


  while(m_running)
  {
    // Update the DT
    m_DT = getDT();

    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
      Keyboard(code);
    }

    // Render All Graphics
    m_graphics->Update(m_DT, code);
    m_graphics->Render();

    // Swap to the Window
    m_window->Swap();
  }
}

void Engine::Keyboard( int &code )
{
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }
  else if (m_event.type == SDL_KEYDOWN)
  {
    // handle key down events here
    switch(m_event.key.keysym.sym)
    {
      case SDLK_ESCAPE:
      m_running = false;
      break;

      case SDLK_q: // Default view
      code = 0;
      break;
      case SDLK_w: // Look at Sun
      code = 1;
      break;
      case SDLK_e: // Mercury
      code = 2;
      break;
      case SDLK_r: // Venus
      code = 3;
      break;
      case SDLK_t: // Earth
      code = 4;
      break;
      case SDLK_y: // Mars
      code = 5;
      break;
      case SDLK_u: // Jupiter
      code = 6;
      break;
      case SDLK_i: // Saturn
      code = 7;
      break;
      case SDLK_o: // Uranus
      code = 8;
      break;
      case SDLK_p: // Neptune
      code = 9;
      break;
      case SDLK_a: // Pluto
      code = 10;
      break;


    }

  }
}

unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}
