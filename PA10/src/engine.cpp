#include "engine.h"

Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME = name;
  m_WINDOW_WIDTH = width;
  m_WINDOW_HEIGHT = height;
  m_FULLSCREEN = false;
  m_DT = 0;
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

    m_graphics->Update(m_DT, codes);
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
    // handle key down events here
    if (m_event.key.keysym.sym == SDLK_ESCAPE)
    {
      m_running = false;
    }
    if(m_event.key.keysym.sym == SDLK_w)
    {
      codes[0] = true;
    }
    if(m_event.key.keysym.sym == SDLK_a)
    {
      codes[1] = true;
    }
    if(m_event.key.keysym.sym == SDLK_s)
    {
      codes[2] = true;
    }
    if(m_event.key.keysym.sym == SDLK_d)
    {
      codes[3] = true;
    }
    if(m_event.key.keysym.sym == SDLK_SPACE)
    {
      codes[4] = true;
    }
    if(m_event.key.keysym.sym == SDLK_r)
    {
      codes[5] = true;
    }
    if(m_event.key.keysym.sym == SDLK_p)
    {
      codes[6] = !codes[6];
      if(codes[6])
      {
        if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT, false))
        {
          printf("The graphics failed to initialize.\n");
        }
      }

      else
      {
        if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT, true))
        {
          printf("The graphics failed to initialize.\n");
        }
      }
    }
    if(m_event.key.keysym.sym == SDLK_z) // left paddle
    {
      codes[7] = true;

    }
    if(m_event.key.keysym.sym == SDLK_SLASH) // right paddle
    {
      codes[8] = true;

    }

  }

}

unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis = (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  //std::cout<< "time: "<< m_currentTimeMillis<< "\n";
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}
