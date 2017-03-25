#include<SDL.h>
#include<SDL_image.h>
#include<iostream>
#include<vector>
#include<fstream>

using namespace std;

SDL_Window* window;
SDL_Renderer* renderer;
SDL_Event Event;
SDL_Texture *background,*character,*Logo,*enemy,*colis,*vganador;
SDL_Rect rect_background,rect_character,rect_Logo,rect_enemy,rect_colis,rect_vganador;

//abeja_1
vector<SDL_Texture*> abej_texture;
SDL_Rect rect_abej;
int current_abej = 0;

//abeja_2
vector<SDL_Texture*> abej2_texture;
SDL_Rect rect_abej2;
int current_abej2 = 0;

//abeja_3
vector<SDL_Texture*> abej3_texture;
SDL_Rect rect_abej3;
int current_abej3 = 0;

//Colision abeja_1
bool Colision1(SDL_Rect a, SDL_Rect b)
{
    a= rect_character;
    b= rect_abej;
    if(a.x + a.w < b.x)
        return false;
    if(b.x + b.w < a.x)
        return false;
    if(b.y + b.h < a.y)
        return false;
    if(a.y + a.h < b.y)
        return false;
    return true;
}

//Colision abeja_2
bool Colision2(SDL_Rect a, SDL_Rect b)
{
    a= rect_character;
    b= rect_abej2;
    if(a.x + a.w < b.x)
        return false;
    if(b.x + b.w < a.x)
        return false;
    if(b.y + b.h < a.y)
        return false;
    if(a.y + a.h < b.y)
        return false;
    return true;
}

//Colision abeja_3
bool Colision3(SDL_Rect a, SDL_Rect b)
{
    a= rect_character;
    b= rect_abej3;
    if(a.x + a.w < b.x)
        return false;
    if(b.x + b.w < a.x)
        return false;
    if(b.y + b.h < a.y)
        return false;
    if(a.y + a.h < b.y)
        return false;
    return true;
}

void ventanaganador()
{

    ofstream archivo ("Estadisticas de Juego.txt");
    archivo<<"GANADOR!!!"<<endl;
    archivo.close();

    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                break;
            }
        }

        SDL_RenderCopy(renderer, vgano, NULL, &rect_vgano);
        SDL_RenderPresent(renderer);
    }
}




int main( int argc, char* args[] )
{
    //Init SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        return 10;
    }
    //Creates a SDL Window
    if((window = SDL_CreateWindow("Image Loading", 100, 100, 1200/*WIDTH*/, 600/*HEIGHT*/, SDL_WINDOW_RESIZABLE | SDL_RENDERER_PRESENTVSYNC)) == NULL)
    {
        return 20;
    }
    //SDL Renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED );
    if (renderer == NULL)
    {
        std::cout << SDL_GetError() << std::endl;
        return 30;
    }

    //Init textures
    int w=0,h=0;
//Fondo
    background = IMG_LoadTexture(renderer,"fondo.jpg");
    SDL_QueryTexture(background, NULL, NULL, &w, &h);
    rect_background.x = 0;
    rect_background.y = 0;
    rect_background.w = 1200;
    rect_background.h = 600;

//Ventana Ganador
    vgano = IMG_LoadTexture(renderer,"winner.jpg");
    SDL_QueryTexture(vgano, NULL, NULL, &w, &h);
    rect_vganador.x = 0;
    rect_vganador.y = 0;
    rect_vganador.w = 1200;
    rect_vganador.h = 600;

//Personaje Principal(Ave)
    character = IMG_LoadTexture(renderer, "Bird.png");
    SDL_QueryTexture(character, NULL, NULL, &w, &h);
    rect_character.x = 10;
    rect_character.y = 500;
    rect_character.w = 60;
    rect_character.h = 60;
    SDL_Delay(1);

//Logo Juego
    Logo= IMG_LoadTexture(renderer, "Logo.png");
    SDL_QueryTexture(Logo, NULL, NULL, &w, &h);
    rect_Logo.x = 10;
    rect_Logo.y = -1;
    rect_Logo.w = 300;
    rect_Logo.h = 50;

//Enemigo Abeja1 con Movimiento
    abej_texture.push_back(IMG_LoadTexture(renderer, "bee1.png"));
    abej_texture.push_back(IMG_LoadTexture(renderer, "bee2.png"));
    rect_abej.x = 300;
    rect_abej.y = -20;
    SDL_QueryTexture(abej_texture[0], NULL, NULL, &rect_abej.w, &rect_abej.h);

    int frames=0;

//Enemigo Abeja2 con Movimiento
    abej2_texture.push_back(IMG_LoadTexture(renderer, "bee11.png"));
    abej2_texture.push_back(IMG_LoadTexture(renderer, "bee22.png"));
    rect_abej2.x = 600;
    rect_abej2.y = 300;
    SDL_QueryTexture(abej2_texture[0], NULL, NULL, &rect_abej2.w, &rect_abej2.h);

    int frames2=0;

//Enemigo Abeja3 con Movimiento
    abej3_texture.push_back(IMG_LoadTexture(renderer, "bee11.png"));
    abej3_texture.push_back(IMG_LoadTexture(renderer, "bee22.png"));
    rect_abej3.x = 900;
    rect_abej3.y = -20;
    SDL_QueryTexture(abej3_texture[0], NULL, NULL, &rect_abej3.w, &rect_abej3.h);

    int frames3=0;

    char orientation= 'j';
    char orientation2= 'k';
    char orientation3= 'l';

    bool game_over = false;


    //Main Loop
    while(true)
    {
        while(SDL_PollEvent(&Event))
        {
            if(Event.type == SDL_QUIT)
            {
                return 0;
            }
            if(Event.type == SDL_KEYDOWN)
            {
                if(Event.key.keysym.sym == SDLK_d)
                    rect_character.x+=10;
                if(Event.key.keysym.sym == SDLK_a)
                    rect_character.x-=10;
                if(Event.key.keysym.sym == SDLK_w)
                    rect_character.y-=10;
                if(Event.key.keysym.sym == SDLK_s)
                    rect_character.y+=10;
            }
        }
//Animacion Abeja1
        if(frames%10==0)
        {
            current_abej++;
            if(current_abej >=abej_texture.size())
            {
                current_abej = 0;
            }
        }

        frames++;

//Animacion Abeja2
        if(frames2%10==0)
        {
            current_abej2++;
            if(current_abej2 >=abej2_texture.size())
            {
                current_abej2= 0;
            }
        }

        frames2++;

//Animacion Abeja3
        if(frames3%10==0)
        {
            current_abej3++;
            if(current_abej3 >=abej3_texture.size())
            {
                current_abej3= 0;
            }
        }

        frames3++;

//Movimiento ascendente y descendente Abeja1
        if(rect_abej.y>500)
        {
            orientation='j';
        }
        if(rect_abej.y<0)
        {
            orientation='d';
        }
        if(orientation =='d')
        {
            rect_abej.y+=1;
        }
        if(orientation == 'j')
        {
            rect_abej.y-=1;
        }

//Movimiento ascendente y descendente Abeja2
        if(rect_abej2.y>500)
        {
            orientation2='k';
        }
        if(rect_abej2.y<0)
        {
            orientation2='a';
        }
        if(orientation2 =='a')
        {
            rect_abej2.y+=1;
        }
        if(orientation2 == 'k')
        {
            rect_abej2.y-=1;
        }

//Movimiento ascendente y descendente Abeja3
        if(rect_abej3.y>500)
        {
            orientation3='l';
        }
        if(rect_abej3.y<0)
        {
            orientation3='d';
        }
        if(orientation3 =='d')
        {
            rect_abej3.y+=1;
        }
        if(orientation3 == 'l')
        {
            rect_abej3.y-=1;
        }

//Colision Abeja1
        if(Colision1(rect_character,rect_colis))
        {
            return game_over;
        }

//Colision Abeja2
        if(Colision2(rect_character,rect_colis))
        {
            return game_over;
        }

//Colision Abeja3
        if(Colision3(rect_character,rect_colis))
        {
            return game_over;
        }

//Salto a Ventana Ganador
         if(rect_character.x>1150)
        {
            ventanagano();
        }


        SDL_RenderCopy(renderer, background, NULL, &rect_background);
        SDL_RenderCopy(renderer, character, NULL, &rect_character);
        SDL_RenderCopy(renderer, Logo, NULL, &rect_Logo);
        SDL_RenderCopy(renderer, abej_texture[current_abej], NULL, &rect_abej);
        SDL_RenderCopy(renderer, abej2_texture[current_abej2], NULL, &rect_abej2);
        SDL_RenderCopy(renderer, abej3_texture[current_abej3], NULL, &rect_abej3);

        SDL_Delay(3);

        SDL_RenderPresent(renderer);
    }

    return 0;
}
