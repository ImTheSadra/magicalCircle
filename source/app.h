#include <SDL2/SDL.h>
#include "circle.h"

class App{
private:
    SDL_Window* window;
    SDL_Renderer* renderer;
    
    bool running = true;

    const int width = 800;
    const int height = 600;

    void update(){
        SDL_Event event;
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){this->running = false;}
        }
    };

    vector<Circle> objects;

    void draw(){
        SDL_SetRenderDrawColor(this->renderer, 51, 51, 51, 100);
        SDL_RenderClear(this->renderer);

        for(int i = 0; i < this->objects.size(); i++){
            this->objects.at(i).draw(this->renderer);
        }

        SDL_RenderPresent(this->renderer);
    };
public:
    App(){
        this->window = SDL_CreateWindow(
            "wow",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            this->width, this->height, 
            SDL_WINDOW_SHOWN
        );
        this->renderer = SDL_CreateRenderer(this->window, -1, 0);

        for(int i = 0; i < 10; i++){
            int color[3];
            srand(time(NULL));
            PerlinNoise::seed_type seed = (rand()/RAND_MAX)*7000;
            PerlinNoise noise {seed};

            for(int c = 0; c < 3; c++){
                color[c] = noise.octave2D_01(i*0.1, c*(1/30), 20)*255;
            }
            srand(time(NULL));
            this->objects.push_back(Circle(this->width, this->height, ((rand()/RAND_MAX)*7000)+i, color));
        }
    };
    void run(){
        while(this->running){
            int start = SDL_GetTicks();
            this->update();
            this->draw();
            int end = SDL_GetTicks();
            SDL_Delay((end-start)/10);
        }
    };
};