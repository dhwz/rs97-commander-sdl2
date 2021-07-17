#include <iostream>
#include "window.h"
#include "def.h"
#include "sdlutils.h"
#include "sdl_event_to_string.h"

#include <fstream>
#include <algorithm>

#define KEYHOLD_TIMER_FIRST   6
#define KEYHOLD_TIMER         2


extern SDL_Surface *ScreenSurface;

CWindow::CWindow(void):
    m_timer(0),
    m_lastPressed(SDLK_0),
    m_retVal(0)
{
    // Add window to the lists for render
    Globals::g_windows.push_back(this);
}

CWindow::~CWindow(void)
{
    // Remove last window
    Globals::g_windows.pop_back();
}

const int CWindow::execute(void)
{
std::string input_up_btn;
std::string input_down_btn;
std::string input_left_btn;
std::string input_right_btn;
std::string input_a_btn;
std::string input_b_btn;
std::string input_x_btn;
std::string input_y_btn;
std::string input_l_btn;
std::string input_r_btn;
std::string input_select_btn;
std::string input_start_btn;


 std::string gamepad = SDL_JoystickNameForIndex(0);
    
    //from: https://www.walletfox.com/course/parseconfigfile.php
    // std::ifstream is RAII, i.e. no need to call close
    std::ifstream cFile ("/tmp/joypads/"+gamepad+".cfg");
    if (cFile.is_open())
    {
     // std::cout << "Using: " << "/tmp/joypads/" << gamepad << ".cfg" << '\n';
        std::string line;
        while(getline(cFile, line)){
            line.erase(std::remove_if(line.begin(), line.end(), isspace),
                                 line.end());
            if(line[0] == '#' || line.empty())
                continue;
            auto delimiterPos = line.find("=");
            auto name = line.substr(0, delimiterPos);
            auto value = line.substr(delimiterPos + 1);
            value.erase(std::remove(value.begin(),value.end(),'\"'),value.end());
          //  std::cout << name << " " << value << '\n';
          
           if  (name.find("input_up_btn") != std::string::npos)
           input_up_btn = value;
                     
           if  (name.find("input_down_btn") != std::string::npos)
           input_down_btn = value;
                     
           if  (name.find("input_left_btn") != std::string::npos)
           input_left_btn = value;
                     
           if  (name.find("input_right_btn") != std::string::npos)
           input_right_btn = value;
          
           if  (name.find("input_a_btn") != std::string::npos)
           input_a_btn = value;
          
           if  (name.find("input_b_btn") != std::string::npos)
           input_b_btn = value;
          
           if  (name.find("input_x_btn") != std::string::npos) 
           input_x_btn = value;
          
           if  (name.find("input_y_btn") != std::string::npos) 
           input_y_btn = value;
          
           if  (name.find("input_l_btn") != std::string::npos) 
           input_l_btn = value;
          
           if  (name.find("input_r_btn") != std::string::npos) 
           input_r_btn = value;
          
           if  (name.find("input_select_btn") != std::string::npos) 
           input_select_btn = value;
          
           if  (name.find("input_start_btn") != std::string::npos) 
           input_start_btn = value;
        }
        
    }
    else {
        printf("Name: %s\n", "Couldn't open /tmp/joypads/"+gamepad+".cfg config file for reading.");
    }
    
    m_retVal = 0;
    Uint32 l_time(0);
    SDL_Event l_event;
    bool l_loop(true);
    bool l_render(true);
    // Main loop
    while (l_loop)
    {
        l_time = SDL_GetTicks();
        // Handle key press
        while (SDL_PollEvent(&l_event))
        {
            if (l_event.type == SDL_KEYDOWN)
            {
                l_render = this->keyPress(l_event);
                if (m_retVal)
                    l_loop = false;
            }
            else if (l_event.type == SDL_QUIT) 
            {
                return m_retVal;
            }
            else if(l_event.type == SDL_JOYBUTTONDOWN || l_event.type == SDL_JOYHATMOTION)
            {
               SDL_Event key_event;
 
     std::string button = sdlEventToString(l_event);
         
       if (button.find("hat=0 value=1") != std::string::npos) { 
           key_event.key.keysym.sym = MYKEY_UP;
//           std::cout << "You pressed up! " << '\n';
       } else if (button.find("button="+input_up_btn+" s") != std::string::npos) { 
           key_event.key.keysym.sym = MYKEY_UP;
//           std::cout << "You pressed up! " << '\n';
       } else if (button.find("hat=0 value=4") != std::string::npos) { 
           key_event.key.keysym.sym = MYKEY_DOWN;
//           std::cout << "You pressed down! " << '\n';
       } else if (button.find("button="+input_down_btn+" s") != std::string::npos) { 
           key_event.key.keysym.sym = MYKEY_DOWN;
//           std::cout << "You pressed down! " << '\n';
       } else if (button.find("hat=0 value=8") != std::string::npos) { 
           key_event.key.keysym.sym = MYKEY_LEFT;
//           std::cout << "You pressed left! " << '\n';
       } else if (button.find("button="+input_left_btn+" s") != std::string::npos) { 
           key_event.key.keysym.sym = MYKEY_LEFT;
//           std::cout << "You pressed left! " << '\n';
       } else if (button.find("hat=0 value=2") != std::string::npos) { 
           key_event.key.keysym.sym = MYKEY_RIGHT;
//           std::cout << "You pressed right! " << '\n';
       } else if (button.find("button="+input_right_btn+" s") != std::string::npos) { 
           key_event.key.keysym.sym = MYKEY_RIGHT;
//           std::cout << "You pressed right! " << '\n';
       } else if (button.find("button="+input_a_btn+" s") != std::string::npos) { 
           key_event.key.keysym.sym = MYKEY_OPEN;
//           std::cout << "You pressed a! " << '\n';
       } else if (button.find("button="+input_b_btn+" s") != std::string::npos) { 
           key_event.key.keysym.sym = MYKEY_PARENT;
//           std::cout << "You pressed b! " << '\n';
       } else if (button.find("button="+input_x_btn+" s") != std::string::npos) { 
           key_event.key.keysym.sym = MYKEY_OPERATION;
//           std::cout << "You pressed x! " << '\n';
       } else if (button.find("button="+input_y_btn+" s") != std::string::npos) { 
           key_event.key.keysym.sym = MYKEY_SYSTEM;
//           std::cout << "You pressed y! " << '\n';
       } else if (button.find("button="+input_l_btn+" s") != std::string::npos) { 
           key_event.key.keysym.sym = MYKEY_PAGEUP;
//           std::cout << "You pressed l! " << '\n';
       }else if (button.find("button="+input_r_btn+" s") != std::string::npos) { 
           key_event.key.keysym.sym = MYKEY_PAGEDOWN;
//           std::cout << "You pressed r! " << '\n';
       }else if (button.find("button="+input_select_btn+" s") != std::string::npos) { 
           key_event.key.keysym.sym = MYKEY_SELECT;
//           std::cout << "You pressed select! " << '\n';
       }else if (button.find("button="+input_start_btn+" s") != std::string::npos) { 
           key_event.key.keysym.sym = MYKEY_TRANSFER;
//           std::cout << "You pressed start! " << '\n';
       } else { 
           break; // Break out of loop to prevent undefined buttons from triggering a key_event
//           std::cout << "I don't know what you pressed! " << '\n';
//           std::cout << button << '\n';
       }
         
         if (button.find("hat=0 value=0") != std::string::npos) { 
         //std::cout << "preventing a double input" << '\n';
         } else {
                l_render = this->keyPress(key_event);
                if (m_retVal)
                    l_loop = false;
        }
           }
        }
        // Handle key hold
        if (l_loop)
            l_render = this->keyHold() || l_render;
        // Render if necessary
        if (l_render && l_loop)
        {
            SDL_utils::renderAll();
            // Flip twice to avoid graphical glitch on Dingoo
            //SDL_Flip(Globals::g_screen);
            //SDL_Flip(Globals::g_screen);
            // SDL_Flip(ScreenSurface);
            SDL_UpdateWindowSurface(Globals::g_sdlwindow);
            SDL_UpdateWindowSurface(Globals::g_sdlwindow);

            l_render = false;
            INHIBIT(std::cout << "Render time: " << SDL_GetTicks() - l_time << "ms"<< std::endl;)
        }
        // Cap the framerate
        l_time = MS_PER_FRAME - (SDL_GetTicks() - l_time);
        if (l_time <= MS_PER_FRAME) SDL_Delay(l_time);
    }
    return m_retVal;
}

const bool CWindow::keyPress(const SDL_Event &p_event)
{
    // Reset timer if running
    if (m_timer)
        m_timer = 0;
    m_lastPressed = p_event.key.keysym.sym;
    return false;
}

const bool CWindow::keyHold(void)
{
    // Default behavior
    return false;
}

const bool CWindow::tick(const Uint8 p_held)
{
    bool l_ret(false);
    if (p_held)
    {
        if (m_timer)
        {
            --m_timer;
            if (!m_timer)
            {
                // Trigger!
                l_ret = true;
                // Timer continues
                m_timer = KEYHOLD_TIMER;
            }
        }
        else
        {
            // Start timer
            m_timer = KEYHOLD_TIMER_FIRST;
        }
    }
    else
    {
        // Stop timer if running
        if (m_timer)
            m_timer = 0;
    }
    return l_ret;
}

const int CWindow::getReturnValue(void) const
{
    return m_retVal;
}

bool CWindow::isFullScreen(void) const
{
    // Default behavior
    return false;
}
