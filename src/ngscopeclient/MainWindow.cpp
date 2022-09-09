/***********************************************************************************************************************
*                                                                                                                      *
* glscopeclient                                                                                                        *
*                                                                                                                      *
* Copyright (c) 2012-2022 Andrew D. Zonenberg                                                                          *
* All rights reserved.                                                                                                 *
*                                                                                                                      *
* Redistribution and use in source and binary forms, with or without modification, are permitted provided that the     *
* following conditions are met:                                                                                        *
*                                                                                                                      *
*    * Redistributions of source code must retain the above copyright notice, this list of conditions, and the         *
*      following disclaimer.                                                                                           *
*                                                                                                                      *
*    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the       *
*      following disclaimer in the documentation and/or other materials provided with the distribution.                *
*                                                                                                                      *
*    * Neither the name of the author nor the names of any contributors may be used to endorse or promote products     *
*      derived from this software without specific prior written permission.                                           *
*                                                                                                                      *
* THIS SOFTWARE IS PROVIDED BY THE AUTHORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED   *
* TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL *
* THE AUTHORS BE HELD LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES        *
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR       *
* BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT *
* (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE       *
* POSSIBILITY OF SUCH DAMAGE.                                                                                          *
*                                                                                                                      *
***********************************************************************************************************************/

/**
	@file
	@author Andrew D. Zonenberg
	@brief Implementation of MainWindow
 */
#include "ngscopeclient.h"
#include "MainWindow.h"

#include "AddScopeDialog.h"

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Construction / destruction

MainWindow::MainWindow(vk::raii::Queue& queue)
	: VulkanWindow("ngscopeclient", queue)
	, m_showDemo(true)
{
}

MainWindow::~MainWindow()
{
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Rendering

void MainWindow::DoRender(vk::raii::CommandBuffer& /*cmdBuf*/)
{

}

void MainWindow::RenderUI()
{
	//Menu for main window
	MainMenu();

	//DEBUG: draw the demo window
	ImGui::ShowDemoWindow(&m_showDemo);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// GUI handlers

void MainWindow::MainMenu()
{
	if(ImGui::BeginMainMenuBar())
	{
		FileMenu();
		AddMenu();
		HelpMenu();
		ImGui::EndMainMenuBar();
	}

	//Dialog boxes
	set< shared_ptr<Dialog> > dlgsToClose;
	for(auto& dlg : m_dialogs)
	{
		if(!dlg->Render())
			dlgsToClose.emplace(dlg);
	}
	for(auto& dlg : dlgsToClose)
		m_dialogs.erase(dlg);
}

void MainWindow::FileMenu()
{
	if(ImGui::BeginMenu("File"))
	{
		ImGui::EndMenu();
	}
}

void MainWindow::AddMenu()
{
	if(ImGui::BeginMenu("Add"))
	{
		if(ImGui::BeginMenu("Oscilloscope"))
		{
			if(ImGui::MenuItem("Connect..."))
				m_dialogs.emplace(make_shared<AddScopeDialog>());

			ImGui::EndMenu();
		}

		ImGui::EndMenu();
	}
}

void MainWindow::HelpMenu()
{
	if(ImGui::BeginMenu("Help"))
	{
		ImGui::EndMenu();
	}
}
