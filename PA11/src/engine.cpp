#include "engine.h"

Engine::Engine(std::string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
  m_DT = 0;
}

Engine::Engine(std::string name)
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

bool Engine::Initialize()
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

  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT, false))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  else
  {
    if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT, true))
    {
      printf("The graphics failed to initialize.\n");
      return false;
    }
  }

  return true;
}

void Engine::Run()
{
  m_running = true;

  while(m_running)
  {
    // Update the DT
    m_DT = getDT();

    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
      Keyboard(codes);
    }

    // Update Graphics
    m_graphics->Update(m_DT, codes);

    // Update Render
    m_graphics->Render();

    // Swap to the Window
    m_window->Swap();
  }
}

void Engine::Keyboard(bool codes[])
{
  if(m_event.type == SDL_QUIT)
  {
    m_running = false;
  }

  else if (m_event.type == SDL_KEYDOWN)
  {
    switch(m_event.key.keysym.sym)
    {
      case SDLK_ESCAPE: // Quit Program
        m_running = false;
        break;

      case SDLK_q: // Move Camera X Up
        codes[0] = true;
        break;

      case SDLK_w: // Move Camera Y Up
        codes[1] = true;
        break;

      case SDLK_e: // Move Camera Z Up
        codes[2] = true;
        break;

      case SDLK_r: // Move Camera X Down
        codes[3] = true;
        break;

      case SDLK_t: // Move Camera Y Down
        codes[4] = true;
        break;

      case SDLK_y: // Move Camera Z Down
        codes[5] = true;
        break;

      case SDLK_SPACE: // Shoot Cue Ball
        codes[6] = true;
        break;

      case SDLK_o: // Reset Game
        codes[7] = true;
        break;

      case SDLK_LEFT: // Move pool stick left
        codes[8] = true;
        break;

      case SDLK_RIGHT: // Move pool stick right
        codes[9] = true;
        break;

      case SDLK_a: // Decrease Ambient List
        codes[10] = true;
        break;

      case SDLK_s: // Increase Ambient List
        codes[11] = true;
        break;

      case SDLK_d: // Decrease Specular Light
        codes[12] = true;
        break;

      case SDLK_f: // Increase Specular Light
        codes[13] = true;
        break;

      case SDLK_u: // Reset Camera View
        codes[14] = true;
        break;

      case SDLK_p:
        codes[15] = !codes[15];

        // Vertex Lighting
        if(codes[15])
        {
          if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT, false))
          {
            printf("The graphics failed to initialize.\n");
          }

        }

        // Fragment Lighting
        else if(!codes[15])
        {
          if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT, true))
          {
            printf("The graphics failed to initialize.\n");
          }

        }
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
