#pragma once
#include<SDL2/SDL.h>
#include<SDL2/SDL_image.h>

class messageType{ //contains a textbox and a button to send the message
    public:
    private:
};

class messageBox{ //contains the sent messages frm you and users with name, timestamp and the message
    public:
        messageBox(string person, string timestamp, string message);
    private:
};

class statusBar{ //shows all the users active on a port( assume an array of active users given to you in an array, i.e: char users[][] = {"person1", "person2", ...})
    public:
    private:
};