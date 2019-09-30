#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	window = NULL;
	screen_surface = NULL;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;

	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		Uint32 flags = SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN;

		//Use OpenGL 2.1
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

		if(WIN_FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		if(WIN_RESIZABLE == true)
		{
			flags |= SDL_WINDOW_RESIZABLE;
		}

		if(WIN_BORDERLESS == true)
		{
			flags |= SDL_WINDOW_BORDERLESS;
		}

		if(WIN_FULLSCREEN_DESKTOP == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN_DESKTOP;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}
//Setters
void ModuleWindow::SetTitle(const char* title)
{
	SDL_SetWindowTitle(window, title);
}

void ModuleWindow::SetBrightness(float brightness)
{
	SDL_SetWindowBrightness(window, brightness);
}

void ModuleWindow::SetWidth(uint width)
{
	SDL_SetWindowSize(window, width, height);
	this->width = width;

	if (!fullscreen)
		App->renderer3D->OnResize(width, height);
}


void ModuleWindow::SetHeigth(uint height)
{
	SDL_SetWindowSize(window, width, height);
	this->height = height;

	if (!fullscreen)
		App->renderer3D->OnResize(width, height);
}

void ModuleWindow::SetWindowSize(int w, int h)
{
	if (w > 0 && h > 0)
	{
		width = w;
		height = h;
		SDL_SetWindowSize(window, width, height);

		if (!fullscreen)
			App->renderer3D->OnResize(width, height);
	}
}


void ModuleWindow::SetSize(uint size, int& w, int& h)
{
	w = screen_w * size;
	h = screen_h * size;

	this->size = size;

	SDL_SetWindowSize(window, w, h);

	if (!fullscreen)
		App->renderer3D->OnResize(w, h);
}

void ModuleWindow::SetFullscreen(bool fullscreen_)
{
	this->fullscreen = fullscreen_;

	if (fullscreen_)
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	else
		SDL_SetWindowFullscreen(window, 0);
}

void ModuleWindow::SetBorderless(bool borderless_)
{
	if (!(fullscreen && fullscreen_desktop))
	{
		this->borderless = borderless_;

		if (borderless_)
			SDL_SetWindowBordered(window, SDL_FALSE);
		else
			SDL_SetWindowBordered(window, SDL_TRUE);
	}
}

void ModuleWindow::SetFullScreenDesktop(bool fd)
{
	this->fullscreen_desktop = fd;

	if (fullscreen_desktop)
		SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
	else 
		SDL_SetWindowFullscreen(window, 0);
}

void ModuleWindow::SetResizable(bool resize)
{
	this->resizable = resize;

	//if (resizable && !fullscreen)
	//	SDL_SetWindowResizable(window, SDL_TRUE);
	//else
	//	SDL_SetWindowResizable(window, SDL_FALSE);
}

//Getters
float ModuleWindow::GetBrightness() const
{
	return SDL_GetWindowBrightness(window);
}

uint ModuleWindow::GetSize() const
{
	return size;
}

void ModuleWindow::GetWindowSize(int & width, int & height)
{
	SDL_GetWindowSize(window, &width, &height);
}

uint ModuleWindow::GetWidth() const
{
	return width;
}

uint ModuleWindow::GetHeight() const
{
	return height;
}


bool ModuleWindow::GetFullscreenWindow() const
{
	return fullscreen;
}

bool ModuleWindow::GetBorderlessWindow() const
{
	return borderless;
}


bool ModuleWindow::GetFullDesktopWindow() const
{
	return fullscreen_desktop;
}
