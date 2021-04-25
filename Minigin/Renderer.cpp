#include "MiniginPCH.h"
#include "Renderer.h"
#include <SDL.h>
#include "SceneManager.h"
#include "Texture2D.h"
#include "imgui.h"
#include "imgui_impl_opengl2.h"
#include "imgui_impl_sdl.h"


void dae::Renderer::Init(SDL_Window * window)
{
	m_Window = window;
	m_Renderer = SDL_CreateRenderer(window, GetOpenGLDriverIndex(), SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (m_Renderer == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateRenderer Error: ") + SDL_GetError());
	}

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(window,SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL2_Init();

}

void dae::Renderer::Render()
{
	SDL_RenderClear(m_Renderer);

	SceneManager::GetInstance().Render();

	
	// Render ImGUI
	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplSDL2_NewFrame(m_Window);
	ImGui::NewFrame();
	if (m_ShowDemo)
		ImGui::ShowDemoWindow(&m_ShowDemo);
	if (m_ShowControls)
		ShowControls();
	ImGui::Render();
	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	
	SDL_RenderPresent(m_Renderer);
}

void dae::Renderer::Destroy()
{
	// Destroy renderwindow
	ImGui_ImplOpenGL2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	if (m_Renderer != nullptr)
	{
		SDL_DestroyRenderer(m_Renderer);
		m_Renderer = nullptr;
	}
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	SDL_QueryTexture(texture.GetSDLTexture(), nullptr, nullptr, &dst.w, &dst.h);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}

void dae::Renderer::RenderTexture(const Texture2D& texture, const float x, const float y, const float width, const float height) const
{
	SDL_Rect dst;
	dst.x = static_cast<int>(x);
	dst.y = static_cast<int>(y);
	dst.w = static_cast<int>(width);
	dst.h = static_cast<int>(height);
	SDL_RenderCopy(GetSDLRenderer(), texture.GetSDLTexture(), nullptr, &dst);
}



int dae::Renderer::GetOpenGLDriverIndex() const
{
	int openglIndex = -1;
	const int driverCount = SDL_GetNumRenderDrivers();
	for(int i{0};i<driverCount;i++)
	{
		SDL_RendererInfo info;
		if (!SDL_GetRenderDriverInfo(i, &info))
			if (!strcmp(info.name, "opengl"))
				openglIndex = i;
	}
	return openglIndex;
}

void dae::Renderer::ShowControls()
{
	ImGui::Begin("Help", &m_ShowControls, ImGuiWindowFlags_MenuBar);



	ImGui::SetWindowSize("Help", {400.f,200.f});
	ImGui::SetWindowPos("Help", {120.f,100.f});
	// Display contents in a scrolling region
	ImGui::TextColored(ImVec4(1, 1, 0, 1), "Controls");
	ImGui::Text("Press -BUTTON A- to kill player1");
	ImGui::Text("Press -BUTTON B- to increase the score of player1");
	ImGui::Text("Press -BUTTON X- to kill player2");
	ImGui::Text("Press -BUTTON Y- to increase the score of player2");
	ImGui::Text("Press -'L'- to toggle the logging of sound");
	ImGui::End();
}
