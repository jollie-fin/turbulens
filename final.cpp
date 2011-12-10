#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <cmath>
#include "sdlglutils.h"

#define WIDTH 800
#define HEIGHT 600
#define RESOLUTION 2048
#define SRAND 17
#define NOMBRE_POINTS 10000
//#define RECIPROQUE
GLdouble projection[16]; 
GLdouble view[16];

    void init();
    void desinit();

using namespace std;
void Dessiner_pole();
void Dessiner_x();
void Dessiner_y();
void Dessiner_damier();
void Dessiner_dessin();
void Dessiner_souris();
void Dessiner_cadre();
static void afficher_scores();

static GLuint texture[10];
static SDL_Surface *texturex;
static SDL_Surface *texturey;
double X,Y,B;
static double score;
static double hiscore;

int xsouris();
int ysouris();
int montantsouris();
int sock_init();
int sock_desinit();
int echange();

bool b1()
{
  return B;
}

double x1()
{
  //return 1.-(  (double(xsouris())/640. -.5) *16./9. +.5);
  return X;
}


double y1()
{
//  return 1.-(  (double(ysouris())/480.-.5) * 16./12. + .5)-1./32.;
  return (1.-Y);
}

int main(int argc, char *argv[])
{
    double fov = 15.;
	  double r =700.;
    double xo = 256.;
    double yo = 256.;
    double anglex = 0.;
    double angley = 0.;
    double anglez = 0.;








    bool modfov = false;
    bool modr = false;
    bool modxyo = false;
    bool modanglexy = false;
    bool modanglez = false;

    SDL_Event event;

    SDL_Init(SDL_INIT_VIDEO);
    atexit(SDL_Quit);
    SDL_WM_SetCaption("SDL GL Application", NULL);
    SDL_SetVideoMode(WIDTH, HEIGHT, 32, SDL_OPENGL|SDL_FULLSCREEN);
//  sock_init();
#ifdef SERVEUR
  init();
#endif
    
    texturex = IMG_Load("x2.png");
    texturey = IMG_Load("y2.png");

    texture[0] = loadTexture("0.png");
    texture[1] = loadTexture("1.png");
    texture[2] = loadTexture("2.png");
    texture[3] = loadTexture("3.png");
    texture[4] = loadTexture("4.png");
    texture[5] = loadTexture("5.png");
    texture[6] = loadTexture("6.png");
    texture[7] = loadTexture("7.png");
    texture[8] = loadTexture("8.png");
    texture[9] = loadTexture("9.png");
    	
    Uint32 last_time = SDL_GetTicks();
    Uint32 current_time,ellapsed_time;
    Uint32 start_time;
    
    for (;;)
    {
        int x,y;
        Uint8 bouton;
        bouton = SDL_GetMouseState(&x,&y);

        start_time = SDL_GetTicks();
        while (SDL_PollEvent(&event))
        {

            switch(event.type)
            {
                case SDL_QUIT:
                  exit(0);
                  break;
                case SDL_KEYUP:
                  {
                    switch (event.key.keysym.sym)
                    {
                      case SDLK_e:
                        modfov = false;
                        break;
                      case SDLK_r:
                        modr = false;
                        break;
                      case SDLK_t:
                        modxyo = false;
                        break;
                      case SDLK_y:
                        modanglexy = false;
                        break;
                      case SDLK_u:
                        modanglez = false;
                        break;
                      default:
                        break;
                    }
                  }
                  break;
                case SDL_KEYDOWN:
                  {
                    switch (event.key.keysym.sym)
                    {
                      case SDLK_ESCAPE:
                        exit(0);
                        break;
                      case SDLK_e:
                        modfov = true;
                        break;
                      case SDLK_r:
                        modr = true;
                        break;
                      case SDLK_t:
                        modxyo = true;
                        break;
                      case SDLK_y:
                        modanglexy = true;
                        break;
                      case SDLK_u:
                        modanglez = true;
                        break;
                      default:
                        break;
                    }
                  }
                  break;
                default:
                  break;
            }
        }

        if (modfov)
          fov = double(y)/double(HEIGHT)*90.;
        if (modr)
          r = double(y)/double(HEIGHT)*10000.;
        if (modxyo)
          xo = WIDTH-double(x);
        if (modxyo)
          yo = double(y);
        if (modanglexy)
          anglex = -double(x)/double(WIDTH)*180.+90.;
        if (modanglexy)
          angley = double(y)/double(HEIGHT)*180.-90.;
        if (modanglez)
          anglez = double(x)/double(WIDTH)*180.-90.;

        current_time = SDL_GetTicks();
        ellapsed_time = current_time - last_time;
        last_time = current_time;
 	


    


     double sx = sin(anglex*M_PI/180.);
     double sy = sin(angley*M_PI/180.);
     double sz = sqrt(1-sx*sx-sy*sy);




	
#ifdef SERVEUR
/*
        fov = 36.75;
   
        r = 770.833;
        xo = 213;
        yo = 22;
        anglex =  4.78125;
        angley = -45.375;
        anglez = 3.9375;

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective(fov,double(WIDTH)/double(HEIGHT),1,200000000);
  
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    gluLookAt(xo+r*sx,yo+r*sy,r*sz,xo,yo,0,-sin(anglez*M_PI/180.),cos(anglez*M_PI/180.),0);
    glScaled(HEIGHT,HEIGHT,1.);

    unsigned char couleur[4];

    x = xsouris();
    y = ysouris();
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    Dessiner_y();
    glFlush();
    glReadPixels(x*double(WIDTH), HEIGHT-1-(y*double(HEIGHT)), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, couleur);
    Y = (double(couleur[0])+double(couleur[1])*256)/double(RESOLUTION);
    B = ((couleur[0]!=0.) || (couleur[1]!=0.));

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    Dessiner_x();
    glFlush();
    glReadPixels(x*double(WIDTH), HEIGHT-1-(y*double(HEIGHT)), 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, couleur);
    X = (double(couleur[0])+double(couleur[1])*256)/double(RESOLUTION);
    B = B || ((couleur[0]!=0.) || (couleur[1]!=0.));
    B = B && !(SDL_BUTTON(1)&bouton);*/
    Uint32 CX,CY;
    cout << montantsouris() << endl;
    CX = SDL_GetPixel(texturex,xsouris(),ysouris());
    CY = SDL_GetPixel(texturey,xsouris(),ysouris());
    Uint8 RX,RY,GX,GY,BX,BY;
    SDL_GetRGB(CX,texturex->format,&RX,&GX,&BX);
    SDL_GetRGB(CY,texturey->format,&RY,&GY,&BY);
    X = 1.-((double(RX)+256.*double(GX))/double(RESOLUTION));
    Y = 1.-((double(RY)+256.*double(GY))/double(RESOLUTION));



/*    X = 1.-(double(x) / double (WIDTH));
    Y = 1.-(double(y) / double (HEIGHT));*/
#endif
/*
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective(fov,double(WIDTH)/double(HEIGHT),1,200000000);
  
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    gluLookAt(xo+r*sx,yo+r*sy,r*sz,xo,yo,0,-sin(anglez*M_PI/180.),cos(anglez*M_PI/180.),0);
    glScaled(HEIGHT,HEIGHT,1.);




    cout << fov << " " << r << " " << xo << " " << yo << " " << anglex << " " << angley << " " << anglez << endl;
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
*/

    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );
    glScaled(WIDTH,HEIGHT,1.);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluOrtho2D(0.,double(WIDTH),0,double(HEIGHT));
//    Dessiner_cadre();


//    echange();
	//    Dessiner();
//    afficher_scores();
        fov = 15;  
        r = 1933.33;
        xo = 301;
        yo = 281;
        anglex =  -0.3375;
        angley = -40.65;
        anglez = -1.575;
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
    gluPerspective(fov,double(WIDTH)/double(HEIGHT),1,200000000);
  
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity( );

    gluLookAt(xo+r*sx,yo+r*sy,r*sz,xo,yo,0,-sin(anglez*M_PI/180.),cos(anglez*M_PI/180.),0);
    glScaled(HEIGHT,HEIGHT,1.);

    Dessiner_pole();
//    Dessiner_damier();
//    Dessiner_souris();



//    Dessiner_dessin();
    glFlush();

    SDL_GL_SwapBuffers();

    
        ellapsed_time = SDL_GetTicks() - start_time;
        if (ellapsed_time < 10)
        {
            SDL_Delay(10 - ellapsed_time);
        }

    }
//    sock_desinit();
#ifdef SERVEUR
    desinit();
#endif
    return 0;
}

void Dessiner_dessin()
{
  static double affx[NOMBRE_POINTS];
  static double affy[NOMBRE_POINTS];
  static bool aff[NOMBRE_POINTS];
  static int offset = 0;
  static int debut = 0;
  static bool en_marche = true;


  affx[offset] = x1();
  affy[offset] = y1();
  if (b1())
  {
    aff[offset] = true;
    en_marche = true;
  }
  else
  {
    if (en_marche)
    {



      for (int i=0;i<NOMBRE_POINTS;i++)
      {
        aff[i] = false;
      }
    }
    debut = offset;
  }

  offset++;
  if (offset >= NOMBRE_POINTS)
    offset = 0;

  glBegin(GL_LINE_STRIP);
  glColor3ub(255,255,255);

  for (int i=1;i<NOMBRE_POINTS-1;i++)
  {
     int indice = (i+offset)%NOMBRE_POINTS;
     if (aff[indice])
     {
       glVertex2d(affx[indice],affy[indice]);
     }
     else
     {
       glEnd();
       glBegin(GL_LINE_STRIP);
     }
  }
  glEnd();
}



void Dessiner_pole()
{
  static int etat = -1; //-1 tout début 0 hors zone 1 initialisation 2 pret 3 go
  static double diff=1.;
  static double affxg[RESOLUTION];
  static double affxd[RESOLUTION];
  static int offset = 0;
  double xg;
  double xd;
  static double xgobj = .3;
  static double xdobj = .5;
  static double oldxgobj = .3;
  static double oldxdobj = .5;
  static double orixgobj = 0;
  static double orixdobj = 0;
  static double t = 0.;
  static double nbv = 0.;
  static double nbvobj = 0.;
  static double dt=0.01;
  static double periode = 5;
  static double v=.4; 

  if (etat == 4)
  {
    score+=diff;
  }
  else
  {
    score=0;
  }
  if (score > hiscore)
    hiscore = score;

  if (etat == -1)
  {
    srand(SRAND);
    {
      double c = double(rand()%801+100)/1000.;
      double w = double(rand()%41+60)/1000.;
      oldxgobj = orixgobj = c-w;
      oldxdobj = orixdobj = c+w;
      c = double(rand()%801+100)/1000.;
      w = double(rand()%41+60)/1000.;
      xgobj = c-w;
      xdobj = c+w;
    }
    etat = 0;
    for (int i=0;i<RESOLUTION;i++)
    {
      double coeff = 0.5+0.5*cos(double(offset)*M_PI/double(RESOLUTION));
      xg = oldxgobj*coeff + xgobj*(1.-coeff);
      xd = oldxdobj*coeff + xdobj*(1.-coeff);
      affxg[offset]=xg;
      affxd[offset]=xd;
      offset++;
    }
    offset=0;
    {
      double c = double(rand()%801+100)/1000.;
      double w = double(rand()%41+60)/1000.;
      oldxgobj = xgobj;
      oldxdobj = xdobj;

      xgobj = c-w;
      xdobj = c+w;
    }
  }
  double xsouris=x1();
  double ysouris=y1();
  bool b = (xsouris>=affxg[(int((1-ysouris)*double(RESOLUTION))+offset)%RESOLUTION])&&(xsouris<=affxd[(int((1-ysouris)*double(RESOLUTION))+offset)%RESOLUTION]);
  diff*=1.0001;
  if (!b && (etat == 4 || etat == 0))
  {
    diff = 1.;
    etat = 0;
  }
  if (b && etat == 0)
  {
      diff = 20.;
      etat = 1;
  }
  if (etat == 1 || etat == 2)
  {
      srand(SRAND);
  }
  
  v=.1*diff; 
  periode = 1./v;//5*diff;
              
  glBegin(GL_LINES);

  if (etat>=1 && etat<=3)
    glColor3ub(0,255,255);
  else if (etat == 4)
      glColor3ub(32,0,0);
  else
      glColor3ub(255,0,0);
  for (int y=0; y<RESOLUTION; y++)
  {
    if ((y+offset)%RESOLUTION>RESOLUTION/2)
    {
    glVertex2d(0.,1.-y/double(RESOLUTION));
    glVertex2d(1.,1.-y/double(RESOLUTION));
    }
  }


  glColor3ub(255,255,255); //face rouge
  for (int y=1; y<RESOLUTION; y++)
  {
    glVertex2d(affxg[(y+offset)%RESOLUTION],1.-y/double(RESOLUTION));
    glVertex2d(affxd[(y+offset)%RESOLUTION],1.-y/double(RESOLUTION));
  }

  glColor3ub(0,0,0); //face rouge
  for (int y=0; y<RESOLUTION; y++)
  {
    double mil = (affxg[(y+offset)%RESOLUTION] + affxd[(y+offset)%RESOLUTION])/2.;
    if ((y+offset)%(RESOLUTION/16)>(RESOLUTION/32))
    {
      glVertex2d(mil-.005,1.-y/double(RESOLUTION));
      glVertex2d(mil+.005,1.-y/double(RESOLUTION));
    }
  }


  glEnd();
  
  double xoff = 0.,yoff = 0.;
  
  if (etat==0)
      {xoff=(rand()%15-7)/1000.;yoff=(rand()%15-7)/1000.;}

  glBegin(GL_QUADS);

  glColor3ub(0,255,0);
  glVertex2d(xsouris+xoff-.005,(ysouris+yoff-.005));
  glVertex2d(xsouris+xoff+.005,(ysouris+yoff-.005));
  glVertex2d(xsouris+xoff+.005,(ysouris+yoff+.005));
  glVertex2d(xsouris+xoff-.005,(ysouris+yoff+.005));
  glEnd();    

  nbvobj = nbvobj+v*dt*double(RESOLUTION);

  int nb_iteration = ceil(nbvobj-nbv);

  double i;
  for (i=0;nbv < nbvobj;nbv++,i++)
  {
    offset++;
    if (offset==RESOLUTION)
    {
      offset=0;
    }
    
    if (offset==0)
    {
      if (etat == 3) diff = 2.;
      if (etat < 4 && etat > 0) etat++;
      double c = double(rand()%801+100)/1000.;
      double w = double(rand()%41+60)/1000.;
      oldxgobj = xgobj;
      oldxdobj = xdobj;
      xgobj = c-w;
      xdobj = c+w;
    }
  
    double coeff = 0.5+0.5*cos(double(offset)*M_PI/double(RESOLUTION));
    xg = oldxgobj*coeff + xgobj*(1.-coeff);
    xd = oldxdobj*coeff + xdobj*(1.-coeff);
    affxg[offset]=xg;
    affxd[offset]=xd;

  }

  nbv-=i;
  nbvobj-=i;
}

void Dessiner_y()
{
    glBegin(GL_LINES);
    for (int y=0; y<RESOLUTION; y++)
    {
      glColor4ub(y%256,y/256,0,0);
      glVertex2d(0.,y/double(RESOLUTION));
      glVertex2d(1.,y/double(RESOLUTION));
    }
    glEnd();
}

void Dessiner_x()
{
    glBegin(GL_LINES);
    for (int y=0; y<RESOLUTION; y++)
    {
      glColor4ub(y%256,y/256,0,0);
      glVertex2d(y/double(RESOLUTION),0.);
      glVertex2d(y/double(RESOLUTION),1.);
    }
    glEnd();
}

void Dessiner_damier()
{
    glColor3ub(255,255,255);
    glBegin(GL_LINES);
    for (int y=0; y<RESOLUTION; y++)
    {
      if (y%(RESOLUTION/8) > (RESOLUTION/16))
      {
        for (int x=0; x<8; x++)
        {
          glVertex2d(double(x)/8.,double(y)/double(RESOLUTION));
          glVertex2d(double(x)/8.+1./16.,double(y)/double(RESOLUTION));
        }
      }
      else
      {
        for (int x=0; x<8; x++)
        {
          glVertex2d(double(x)/8.+1./16.,double(y)/double(RESOLUTION));
          glVertex2d(double(x)/8.+2./16.,double(y)/double(RESOLUTION));
        }
      }
    }
    glEnd();
}

void afficher_chiffre(int x,int y,int chiffre)
{
    double xd = double(x)/20., yd = double(y)/20.;

    glBindTexture(GL_TEXTURE_2D, texture[chiffre]);
    glBegin(GL_QUADS);
      glColor3ub(255,255,255);
      glTexCoord2d(0,0);  glVertex2d(xd,yd);
      glTexCoord2d(1,0);  glVertex2d(xd+.05,yd);
      glTexCoord2d(1,1);  glVertex2d(xd+.05,yd+.05);
      glTexCoord2d(0,1);  glVertex2d(xd,yd+.05);
    glEnd();
}

int log(int z)
{
  int retour = 0;
  while (z >= 10.)
  {
     z/=10; retour++;
  }
  return retour;
}

void afficher_scores()
{
  glEnable(GL_TEXTURE_2D);
	
  glBlendFunc (GL_ONE, GL_ONE);
  glEnable(GL_BLEND);

  int scoretmp = score;
  if (scoretmp == 0)
  {
    afficher_chiffre (1,1,0);
  }
  else
  {
    int i = log(scoretmp);
    while (scoretmp>0)
    {
      afficher_chiffre(i+1,1,scoretmp%10);
      i--;
      scoretmp/=10;
    }
  }

  int hiscoretmp = hiscore;
  if (hiscoretmp == 0)
  {
    afficher_chiffre (18,1,0);
  }
  else
  {
    int i = 0;
    while (hiscoretmp>0)
    {
      afficher_chiffre(i+18,1,hiscoretmp%10);
      i--;
      hiscoretmp/=10;
    }
  }


  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
}

void Dessiner_souris()
{
  double xsouris = x1();
  double ysouris = y1();
  glBegin(GL_QUADS);

  glColor3ub(0,255,0);
  glVertex2d(xsouris-.05,ysouris-.05);
  glVertex2d(xsouris+.05,ysouris-.05);
  glVertex2d(xsouris+.05,ysouris+.05);
  glVertex2d(xsouris-.05,ysouris+.05);
  glEnd();    

}

void Dessiner_point(double x, double y)
{
  glBegin(GL_QUADS);

  glColor3ub(0,255,0);
  glVertex2d(x-.005,y-.005);
  glVertex2d(x+.005,y-.005);
  glVertex2d(x+.005,y+.005);
  glVertex2d(x-.005,y+.005);
  glEnd();    
}
void Dessiner_cadre()
{
  Dessiner_point(3./16.,7.5/16.);
  Dessiner_point(14.5/16.,7.5/16.);
  Dessiner_point(13./16.,15./16.);
  Dessiner_point(5./16.,15./16.);
}
