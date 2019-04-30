//
// Created by piotr on 16.04.19.
//

#include "cFizyka.h"
#ifndef __unix__
    #include <windows.h>
#else
#include<chrono>
unsigned long long GetTickCount()
{
    using namespace std::chrono;
    return duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
}
#endif
#include <math.h>



cFizyka::cFizyka()
{
    //obiekt staly
    g_=0.0;
    alfa_g_=0.0;
    v_=0.0;
    alfa_v_=0.0;
    //ustawia domyslna obwiednie obiektu
    granica_.xa=-1.0;
    granica_.ya=-1.0;

    granica_.xb=1.0;
    granica_.yb=1.0;
    reset();
}

void cFizyka::odbicie(float alfa_n) //odbicie od sciany charakteryzowanej za pomoca normalnej alfa_n
{
    //prawo odbicia "kat padania rowny katowi odbicia (pod warunkiem, ze obiekt wnika do wnetrza)
    if(fabs(alfa_n-alfa_v_)>90.0)
        alfa_v_= alfa_n-(180.0+alfa_v_-alfa_n);

}

void cFizyka::aktualizuj(int czas_aktualny) //zmienia polozenie obiektu na podstawie aktualnego czasu
{

    float delta_t=czas_aktualny-czas_,v_x,v_y;
    if(delta_t>1000) delta_t=100;//dla przerwy dluzszej niz 1s nie przeprowadzana jest aktualizacja
    v_x=v_*cos(alfa_v_/180.0*M_PI);
    v_y=v_*sin(alfa_v_/180.0*M_PI);
    x_=x_+ v_x*delta_t + 0.5*g_*cos(alfa_g_/180.0*M_PI)*delta_t*delta_t;
    y_=y_+ v_y*delta_t + 0.5*g_*sin(alfa_g_/180.0*M_PI)*delta_t*delta_t;

    //aktualizacja predkosci
    v_x=v_x + g_*cos(alfa_g_/180.0*M_PI)*delta_t;
    v_y=v_y + g_*sin(alfa_g_/180.0*M_PI)*delta_t;
    //wypadkowa predkosc
    v_=sqrt(v_x*v_x+v_y*v_y);
    //kierunek predkosci
    alfa_v_=atan2(v_y,v_x)*180.0/M_PI;

    czas_+=delta_t;
}

void cFizyka::ustaw_predkosc(float _v, float _alfa_v) //ustawia poczatkowa predkosc
{
    v_=_v;
    alfa_v_=_alfa_v;
    reset();
}

void cFizyka::ustaw_fizyka(float _g, float _alfa_g) //ustawia poczatkowe przyspieszenie
{
    g_=_g;
    alfa_g_=_alfa_g;
    reset();
}

void cFizyka::ustaw_geometria(float _x, float _y, float _xa, float _ya, float _xb, float _yb)
{
    x_=_x;
    y_=_y;
    granica_.xa=_xa;
    granica_.xb=_xb;
    granica_.ya=_ya;
    granica_.yb=_yb;
    reset();
}

int cFizyka::kolizja(cFizyka &X) //wykrywanie kolizji z innym obiektem (funkcja przekazuje 1 gdy jest kolizja 0 gdy brak)
{
    //jesli wystepuje kolizja to przynajmniej jeden z wierzcholkow musi zawierac sie wewnatrz
    //sprawdzenie czy ktorys z wierzcholkow obiektu nie zawiera sie w obiekcie sprawdzanym
    int kolizja=0;
    if(w_prosokacie(x_ + granica_.xa, y_ + granica_.ya, X) == 1 ) kolizja = 1;
    else if(w_prosokacie(x_ + granica_.xa, y_ + granica_.yb, X) == 1 ) kolizja = 1;
    else if(w_prosokacie(x_ + granica_.xb, y_ + granica_.yb, X) == 1 ) kolizja = 1;
    else if(w_prosokacie(x_ + granica_.xb, y_ + granica_.ya, X) == 1 ) kolizja = 1;
        //odworcenie sprawdzania
    else if(w_prosokacie(X.x_ + X.granica_.xa, X.y_ + X.granica_.ya, *this) == 1 ) kolizja = 1;
    else if(w_prosokacie(X.x_ + X.granica_.xa, X.y_ + X.granica_.yb, *this) == 1 ) kolizja = 1;
    else if(w_prosokacie(X.x_ + X.granica_.xb, X.y_ + X.granica_.yb, *this) == 1 ) kolizja = 1;
    else if(w_prosokacie(X.x_ + X.granica_.xb, X.y_ + X.granica_.ya, *this) == 1 ) kolizja = 1;

    //obsluga kolizji
    if (kolizja)
    {
        //znalezienie boku od ktorego nastapi odbicie
        float alfa_n= znajdz_normalna(X);
        odbicie(alfa_n);
        float kat=(alfa_n>0)?alfa_n-180:alfa_n+180;
        X.odbicie(kat);
    }

    return kolizja;
}

int cFizyka::w_prosokacie(float _x, float _y, const cFizyka &X)//wykrywa czy dany punkt (_x,_y) znajduje sie wewnatrz pewnego kwadratu
{
    if( ( (_x < X.x_+X.granica_.xb) && (_x > X.x_+X.granica_.xa)) && ((_y < X.y_+X.granica_.yb) && (_y > X.y_+X.granica_.ya)))
        return 1;
    else return 0;
}

float cFizyka::odleglosc(float _x, float _y, float _xa,float _ya,float _xb,float _yb)//wyznacza odleglosc od pewnej prostej przechodzacej przez 2 punkty
{
    //rownanie prostej pzrechodzacej pzrez 2 punkty: y_=Ax+B
    float d;
    if(_xb != _xa)
    {
        float A = (_yb - _ya)/(_xb - _xa);
        float B = _ya - A * _xa;
        //wyznaczenie odleglosci:
        d= fabs(A*_x-_y+B)/sqrt(A*A+1.0);
    }
    else
        d=fabs(_x-_xb);
    return d;
}


float cFizyka::znajdz_normalna(const cFizyka &X)//znajduje normalna boku ktory jest najblizej srodka obiektu (wynikiem funkcji jest orientacja normalnej);
{
    float tab[4];//tablica zawierajaca odleglosci srodka obiektu od bokow, przyjmuje sie ze odbicie nastepuje od boku lezacego najblizej srodka obiektu
    int min_idx=0;
    tab[0]=odleglosc(x_,y_,X.x_+X.granica_.xa,X.y_+X.granica_.ya,X.x_+X.granica_.xa,X.y_+X.granica_.yb);
    tab[1]=odleglosc(x_,y_,X.x_+X.granica_.xa,X.y_+X.granica_.yb,X.x_+X.granica_.xb,X.y_+X.granica_.yb);
    tab[2]=odleglosc(x_,y_,X.x_+X.granica_.xb,X.y_+X.granica_.yb,X.x_+X.granica_.xb,X.y_+X.granica_.ya);
    tab[3]=odleglosc(x_,y_,X.x_+X.granica_.xb,X.y_+X.granica_.ya,X.x_+X.granica_.xa,X.y_+X.granica_.ya);

    //poszukiwanie minimalnej wartosci odleglosci
    for (int i=1;i<4;i++)
        if (tab[i]<tab[min_idx]) min_idx=i;

    //wyznaczenie normalnych najblizej lezacego boku, (dla aktualnej wersji zawsze leza wzdloz osi X lub Y)
    switch(min_idx) //do modyfikacji gdy beda obr�cone
    {
        case 0: return 180.0;
        case 1: return 90.0;
        case 2: return 0.0;
        case 3: return -90.0;
    }

}

void cFizyka::reset() //resetuje czas_
{

    czas_=GetTickCount();

}


