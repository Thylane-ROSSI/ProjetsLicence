#include <iostream>
#include <cmath>
#include <time.h>
using namespace std;
#include <Grapic.h>
using namespace grapic;
const int DIMW = 500;

///Les complexes
struct Complex
{
    float x, y;
};

Complex make_complex(float x, float y)
{
    Complex c;
    c.x = x;
    c.y = y;
    return c;
}


Complex operator+ (Complex a, Complex b)
{
    Complex c;
    c.x = a.x + b.x;
    c.y = a.y + b.y;
    return c;
}

Complex operator- (Complex a, Complex b)
{
    Complex c;
    c.x = a.x - b.x;
    c.y = a.y - b.y;
    return c;
}


Complex operator* (float lambda , Complex b)
{
    Complex c;
    c.x = lambda*b.x;
    c.y = lambda*b.y;
    return c;
}


Complex operator* (Complex a , Complex b)
{
    Complex c;
    c.x = a.x*b.x - a.y*b.y;
    c.y = a.x*b.y + a.y*b.x;
    return c;
}



///Les fonctions pour l'Altitude
const int ALTITUDE_MAX = 200;

struct Altitude
{
  float v[ALTITUDE_MAX];
  int n;
};

void altitudeInit(Altitude& A,int R)
{
  A.n = R;
  for (int i = 0;i<R;i++)
  {
    A.v[i] = frand(0,1);
  }
}

float altitudeEval(Altitude A,float x)
{
  int index = int (x*(A.n-1));
  float interp = (x*(A.n-1)) - index;
  if (x == 1)
  {
    return A.v[A.n-1];
  }
  return A.v[index] * (1-interp) + A.v[index+1]*(interp);
}

void altitudeDraw(Altitude A,float scale)
{
  for (int i = 0;i<DIMW;i++)
  {
    line(i,0,i,altitudeEval(A,float(i)/DIMW)*scale);
  }
}

Altitude operator+(Altitude A, Altitude B)
{
    Altitude C;
    C.n = max(A.n,B.n);
    float x;

    for (int i = 0;i<C.n;i++){
      x = float(i)/(C.n-1);
      C.v[i] = altitudeEval(A,x) + altitudeEval(B,x);
    }
    return C;
}


Altitude operator*(Altitude A,float k)
{
    Altitude C;
    C.n = A.n;

    for (int i = 0;i<C.n;i++){
      C.v[i] = A.v[i]*k;
    }
    return C;
}



///La structure Couleur
struct Couleur
{
  int r;
  int g;
  int b;
};

Couleur  make_couleur(int r,int g,int b)
{
    Couleur C;
    C.r = r;
    C.g = g;
    C.b = b;
    return C;
}


///La structure Montagne
struct Montagne
{
  Altitude alt;
  Couleur col;
};

void montagneDraw(Montagne &M)
{
    color(M.col.r,M.col.g,M.col.b);
    altitudeDraw(M.alt,1);
}



///Initialisation des différentes montagnes de chaque monde
void PlaineInit(Montagne &m, Couleur C,float alti_moyenne)
{
  m.col = C;
  Altitude niveaux[6];
  for (int i = 0;i<6;i++)
  {
    altitudeInit(niveaux[i],6*pow(2,i*0.1));
  }
  m.alt = niveaux[0]*alti_moyenne;
  for (int i = 1;i<6;i++)
  {
    m.alt = m.alt + niveaux[i]*alti_moyenne*pow(0.5,i*1.2);
  }
}

void DesertInit(Montagne &m, Couleur C,float alti_moyenne)
{
  m.col = C;
  Altitude niveaux[6];
  for (int i = 0;i<6;i++)
  {
    altitudeInit(niveaux[i],6*pow(2,i*0.7));
  }
  m.alt = niveaux[0]*alti_moyenne;
  for (int i = 1;i<6;i++)
  {
    m.alt = m.alt + niveaux[i]*alti_moyenne*pow(0.5,i*1);
  }
}

void NeigeInit(Montagne &m, Couleur C,float alti_moyenne)
{
  m.col = C;
  Altitude niveaux[6];
  for (int i = 0;i<6;i++)
  {
    altitudeInit(niveaux[i],6*pow(2,i));
  }
  m.alt = niveaux[0]*alti_moyenne;
  for (int i = 1;i<6;i++)
  {
    m.alt = m.alt + niveaux[i]*alti_moyenne*pow(0.5,i);
  }
}


///Le personnage et ses fonctions
struct Perso
{
    Complex pos;
    Image im;
};

void init(Perso &b)
{
    b.im = image("data/Mini_Projet/Stickman.png");
    b.pos.x = DIMW/2;
    b.pos.y = 30;
}

void draw (Perso b)
{
    image_draw( b.im, b.pos.x, b.pos.y, 30, 50, 180, 2);
}

///Les particules
struct Particule
{
    Complex p;
    Complex v;
    Complex f;
    float m;
};


void addforce(Particule &Pa, Complex f)
{
    Pa.f = Pa.f + f;
}

void drawP(Particule P)
{
    color(255, 0,0);
    circleFill(P.p.x, P.p.y, 10);
}

///La structure Piece
struct Piece
{
    Complex pos;
    int score;
};

void initpiece(Piece &P)
{
    P.score = 0;
    P.pos.x = (rand()%DIMW-1);
    P.pos.y = 60;
}

void drawPiece(Piece P)
{
    color(255,255,0);
    circleFill(P.pos.x, P.pos.y, 8);
}


///Le Monde
const int MAX_NIV = 110;
const int maxi_parts = 100;
float const friction = 1.0;

struct Monde
{
  Montagne rocks[MAX_NIV];
  int n;
  int nbp;
  Particule TP[maxi_parts];
  float dt;
  Piece P;
};

///Initialisation d'une particule
void init_particule(Monde &W, float m, float px, float py,float vx, float vy, float fx, float fy)
{
    Particule P;
    P.m = m;
    P.p = make_complex(px, py);
    P.v = make_complex(vx,vy);
    P.f = make_complex(fx, fy);
    W.TP[W.nbp]=P;
    W.nbp++;
}

///Initilisation des 3 mondes
//Plaine
void mondeInit_plaine(Monde &M,int planes, Perso &b)
{
  M.n = planes;
  Couleur C;
  float s;
  for (int i = 0;i<M.n;i++)
    {
    s = (1-(float(i)/M.n));
    C = make_couleur(34  * s,139* s,34 * s);
    PlaineInit(M.rocks[i],C,0.5*s*DIMW);
    }
  init(b);
  M.nbp = 0;
  init_particule(M,1,(rand()%DIMW-1),(rand()%DIMW-1),-3000,3000,0,-5000);
  initpiece(M.P);

}

//Désert
void mondeInit_desert(Monde &M,int planes, Perso &b)
{
  M.n = planes;

  Couleur C;
  float s;
  for (int i = 0;i<M.n;i++)
  {
    s = (1-(float(i)/M.n));
    C = make_couleur(255  * s,216* s,17 * s);
    DesertInit(M.rocks[i],C,0.5*s*DIMW);
  }
  init(b);
  M.nbp = 0;
  init_particule(M,1,(rand()%DIMW-1),(rand()%DIMW-1),3000,3000,5000,50000);
  init_particule(M,1,(rand()%DIMW-1),(rand()%DIMW-1),3000,3000,0,0);
  initpiece(M.P);
}

//Neige
void mondeInit_neige(Monde &M,int planes, Perso &b)
{
  M.n = planes;
  Couleur C;
  float s;
  for (int i = 0;i<M.n;i++){
    s = (1-(float(i)/M.n));
    C = make_couleur(255 *s ,255*s, 255*s);
    NeigeInit(M.rocks[i],C,0.5*s*DIMW);
  }
  init(b);
  M.nbp = 0;
  init_particule(M,1,(rand()%DIMW-1),(rand()%DIMW-1),-3000,3000,0,0);
  init_particule(M,1,(rand()%DIMW-1),(rand()%DIMW-1),3000,3000,0,0);
  init_particule(M,1,(rand()%DIMW-1),(rand()%DIMW-1),-3000,3000,0,0);
  initpiece(M.P);
}

void mondeDraw(Monde M, Perso b)
{
  for (int i = 0;i<M.n;i++)
    {
    montagneDraw(M.rocks[i]);
    }
    draw(b);
    for(int i=0; i<M.nbp; i++)
    {
     drawP(M.TP[i]);
    }
    drawPiece(M.P);
}

///fonction update
void update(Monde &M,Perso &b, float dt, int choix)
{
    int i,j;
    float s;
    //Pour le déplacement du personnage
    if (isKeyPressed(SDLK_LEFT))
        {
            if (b.pos.x>=0)
            {
             //Il ne peut pas revenir en arrière à partir du mur de gauche
             b.pos.x = b.pos.x - 20;
            }
        }
    if (isKeyPressed(SDLK_RIGHT))

        {
          b.pos.x = b.pos.x + 20;
          //Si le personnage dépasse le mur de droite il arrive sur un nouveau paysage
          if(b.pos.x>DIMW)
          {
              b.pos.x = b.pos.x - 500;
             for(i=0; i<MAX_NIV; i++)
              {
                if(choix==1)
                {
                    s = (1-(float(i)/M.n));
                    Couleur C = make_couleur(34  * s,139* s,34 * s);
                    PlaineInit(M.rocks[i],C,0.5*s*DIMW);
                }
                if (choix==2)
                {
                    s = (1-(float(i)/M.n));
                    Couleur C = make_couleur(255  * s,216* s,17 * s);
                    DesertInit(M.rocks[i],C,0.5*s*DIMW);
                }

                if (choix==3)
                {
                    s = (1-(float(i)/M.n));
                    Couleur C = make_couleur(255 *s ,255*s, 255*s);
                    NeigeInit(M.rocks[i],C,0.5*s*DIMW);
                }
            }

        }
      }
    //Déplacement des particules
    Particule Pa;
    for (i=0 ; i<M.nbp; i++)
    {
        Pa = M.TP[i];
        Pa.f = make_complex(rand()%6000,rand()%6000);
        addforce(Pa, make_complex(rand()%DIMW, rand()%DIMW));
        M.TP[i]=Pa;
    }
    for (i=0 ; i<M.nbp; i++)
    {
        Pa = M.TP[i];
        Pa.v = Pa.v + (1/Pa.m) * dt * Pa.f;
        Pa.p = Pa.p + dt * Pa.v;

        //Mur du haut
        if (Pa.p.y>DIMW)
        {
            Pa.p.y = DIMW - (Pa.p.y - DIMW);
            Pa.v.y = - Pa.v.y;
            Pa.v= friction * Pa.v;
        }
        //Mur du bas
        else
        {
            if (Pa.p.y < 0)
            {
                Pa.p.y = - Pa.p.y;
                Pa.v.y = - Pa.v.y;
                Pa.v = friction * Pa.v;
            }
        }
        //Mur de gauche
        if (Pa.p.x < 0)
        {
            Pa.p.x = - Pa.p.x;
            Pa.v.x = - Pa.v.x;
            Pa.v = friction * Pa.v;

        }
        //Mur de droite
        else
        {
            if (Pa.p.x > DIMW)
            {
                Pa.p.x = DIMW - (Pa.p.x - DIMW);
                Pa.v.x = - Pa.v.x;
                Pa.v = friction * Pa.v;
            }
        }
        M.TP[i] = Pa;

        Piece P;

        //Si le personnage trouve une des balles, le programme s'arrête, il a perdu
        if((int(b.pos.x)<=int(Pa.p.x))and (int(Pa.p.x)<=int(b.pos.x)+25)and(int(b.pos.y)<=int(Pa.p.y))and (int(Pa.p.y)<=int(b.pos.y)+37))
        {
            cout<<"Perdu !";
            winQuit();
        }
        //Il y a des pièces qui apparaissent une par une sur le jeu, il faut
        //en récupérer un certain nombre

         if((int(b.pos.x)<=int(M.P.pos.x))and(int(M.P.pos.x)<=int(b.pos.x)+25))
        {
            float c = M.P.pos.x;
            M.P.pos.x = rand()%DIMW;
            if (c != M.P.pos.x)
            {
                M.P.score ++;
                cout<<"score : "<<M.P.score<<endl;
            }
            else
            {
                M.P.pos.x = rand()%DIMW;
            }
            if (M.P.score == 30)
            {
                winQuit();
                cout<<"Gagne !"<<endl;
            }
        }


    }

}


///Initialisation du fond de la fenêtre
void backgroundDraw()
{
    int i,x,y;
    for(i=0;i<DIMW;i++)
    {
        const float c = 0.28f;
        color(0.f*(c*i+15), 1.91f*(c*i+15), 2.55f*(c*i+15));
        line( 0, DIMW-i, DIMW, DIMW-i);
    }
    srand(217);
    for(i=0;i<100;++i)
    {
        x = irand(0,DIMW);
        y = irand(DIMW/3, DIMW);
        int add = (DIMW-y)/3;
        color( 100+add, 130+add, 100+add);
        circleFill( x, y, 1);
    }
}



int main(int, char ** )
{
    Menu m;
    Monde M;
    bool stop=false;
	winInit("Jeu", DIMW, DIMW);
	menu_add( m, "default");
    menu_add( m, "Plaine Niveau 1");
    menu_add( m, "Désert Niveau 2");
    menu_add( m, "Neige Niveau 3");
    Perso b;
    init(b);
    mondeInit_plaine(M,20,b);

	while( !stop )
    {
        int choix;
        winClear();
        backgroundDraw();
        mondeDraw(M, b);
        menu_draw(m, 5,DIMW-81, 105, DIMW+26);
        switch(menu_select(m))
        {
            case 0 : srand(time(NULL));update(M,b,0.001,choix);mondeDraw(M, b);menu_setSelect(m, 0);break;
            case 1 : srand(time(NULL));mondeInit_plaine(M,20,b); mondeDraw(M, b);menu_setSelect(m, 0);choix = 1;break;
            case 2 : srand(time(NULL));mondeInit_desert(M,20,b); mondeDraw(M, b);menu_setSelect(m, 0);choix = 2;break;
            case 3 : srand(time(NULL));mondeInit_neige(M,20,b);mondeDraw(M, b);menu_setSelect(m, 0);choix = 3;break;
        }
        menu_draw(m, 5,DIMW-81, 105, DIMW+26);
        stop = winDisplay();
    }
    winQuit();
	return 0;
}

