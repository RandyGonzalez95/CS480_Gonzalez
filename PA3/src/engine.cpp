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
  if(!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  // No errors
  return true;
}

void Engine::InitCodes( bool * code )
{
  int index = 0;

  // initialize array of booleans to 0
  for(index = 0; index<10; index++)
  {
    code[index] = false;
  }
}

void Engine::Run()
{
  m_running = true;
  bool *code = new bool[10]; // creates array of booleans to check spin, orbit, rotate codes

  // initialize all bools to false
  InitCodes(code);

  while(m_running)
  {
    // Update the DT
    m_DT = getDT();

    // Check the keyboard input
    while(SDL_PollEvent(&m_event) != 0)
    {
      Keyboard(code);
    }

    // Update and render the graphics
    m_graphics->Update(m_DT, code);
    m_graphics->Render();

    // Swap to the Window
    m_window->Swap();
  }
}

void Engine::Keyboard( bool *code )
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
    else if(m_event.key.keysym.sym == SDLK_q)  // Default key
    {
       // code 0
       code[0] = !code[0];

    }
    else if(m_event.key.keysym.sym == SDLK_w) // Reverse key
    {
      // code 1
      code[1] = !code[1];
    }
   else if(m_event.key.keysym.sym == SDLK_e) // Stop spin
    {
      // code 2
      code[2] = !code[2];

    }
   else if(m_event.key.keysym.sym == SDLK_r) // Pause cube
    {
      // code 3
      code[3] = !code[3];


    }
   else if(m_event.key.keysym.sym == SDLK_t) // Pause orbit
    {
      // code 4
      code[4] = !code[4];
    }

   // Moon Keys

  else if(m_event.key.keysym.sym == SDLK_a)  // Default key
    {


    }
    else if(m_event.key.keysym.sym == SDLK_s) // Reverse key
    {


    }
   else if(m_event.key.keysym.sym == SDLK_d) // Stop spin
    {


    }
   else if(m_event.key.keysym.sym == SDLK_f) // Pause cube
    {

    }
   else if(m_event.key.keysym.sym == SDLK_g) // Pause orbit
    {

    }



  }
  else if(m_event.type == SDL_MOUSEBUTTONDOWN)
  {
    if(m_event.button.button == SDL_BUTTON_LEFT)
    {
      code[1] = !code[1];
    }
    if(m_event.button.button == SDL_BUTTON_RIGHT)
    {
      code[2] = !code[2];
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
