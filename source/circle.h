#include "noise/noise.h"
#include <vector>
#include <math.h>
#include <random>
#include <time.h>
#include <SDL2/SDL.h>
#include <iostream>

using namespace std;
using namespace siv;

class Circle{
public:
    vector<int> raduis;
    int w, h;
    double step, rScale;
    double rSpeed = 0.1;
    PerlinNoise noise;
    int r, g, b;
    Circle(int width, int height, PerlinNoise::seed_type seed, int color[3]){
        this->noise.reseed(seed);
        for(int i = 0; i < 350; i++){
            int r = 200-(noise.octave1D_01(i*0.01, 100)*100);
            this->raduis.push_back(r);
        }
        this->w = width; this->h = height;
        this->r = color[0];
        this->g = 0;
        this->b = color[2];
    }

    void draw(SDL_Renderer* renderer){
        this->step += 0.01;
        int lx, ly;
        SDL_SetRenderDrawColor(renderer, this->r, this->g, this->b, 255);
        for(int i = 0; i < this->raduis.size(); i++){
            int ra = this->raduis.at(i)-this->rScale;
            double angle = i+this->step;
            double angle_ = angle*(M_PI / 180);
            
            int x = (this->w/2)-cos(angle_)*ra;
            int y = (this->h/2)-sin(angle_)*ra;

            if (i == 0){
                int ara = (this->raduis.at(this->raduis.size()-1))-this->rScale;
                double aangle = this->raduis.size()-1+this->step;
                double aangle_ = aangle*(M_PI / 180);
                
                int ax = (this->w/2)-cos(aangle_)*ara;
                int ay = (this->h/2)-sin(aangle_)*ara;

                SDL_RenderDrawLine(renderer, x, y, ax, ay);
            } else if (i == this->raduis.size()-1) {
                int ara = this->raduis.at(0)-this->rScale;
                double aangle = this->step;
                double aangle_ = aangle*(M_PI / 180);
                
                int ax = (this->w/2)-cos(aangle_)*ara;
                int ay = (this->h/2)-sin(aangle_)*ara;

                SDL_RenderDrawLine(renderer, x, y, ax, ay);
            } else {
                SDL_RenderDrawLine(renderer, x, y, lx, ly);
            }
            lx = x; ly = y;
        }
        // if (this->rScale < 0 || this->rScale > 400){
        //     this->rSpeed = -this->rSpeed;
        // }
        // this->rScale += this->rSpeed;
        double t = this->noise.octave1D_01(this->step*0.01, 50);
        this->rScale = t*800;
    }
};