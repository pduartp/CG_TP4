#pragma hdrstop

// Se voc� estiver usando o Builder defina BUILDER para desabilitar
// excess�es em ponto flutuante
#ifdef BUILDER
  #include <float.h>
#endif


#pragma argsused
#include <stdlib.h>
#include <gl\glut.h>
#include <math.h>

#define ESCAPE 27
#define TAMANHO_ESFERA 0.04

#define ALT_QUADRIL 0.4
#define LARG_QUADRIL 0.4
#define COMP_QUADRIL 0.11

#define LARG_TRONCO 2.0
#define ALT_TRONCO  0.8
#define COMP_TRONCO  0.5

#define ALT_FEMUR 0.5
#define LARG_FEMUR 0.2
#define COMP_FEMUR 0.1

#define ALT_CANELA 0.35
#define LARG_CANELA 0.1
#define COMP_CANELA 0.08

#define ALT_PATA  0.15
#define BASE_PATA 0.1

#define ALT_PESCOCO  0.2
#define LARG_PESCOCO 0.2
#define COMP_PESCOCO 0.2

#define ALT_PESCOCO  0.4
#define LARG_PESCOCO 1.4
#define COMP_PESCOCO 0.2

#define ALT_CABECA  0.3
#define LARG_CABECA 0.4
#define COMP_CABECA 0.15


#define ESQUERDA_ANTERIOR 0
#define DIREITA_ANTERIOR 1
#define ESQUERDA_POSTERIOR 2
#define DIREITA_POSTERIOR 3

int window;
int Width;
int Height;
int deslocamento_rotacao_X = 0;
int deslocamento_rotacao_Y = 0;

int deslocamento_translation_X = 1;
int deslocamento_translation_Y = 1;
int deslocamento_translation_Z = 1;

GLfloat fAspect;

GLuint idTextura;
unsigned char *imagemTextura;



#define QUADRIL 0
#define FEMUR 1
#define CANELA 2
#define PATA 3
// angulos[estagio][posicao][quadril/femur/canela/pata]
float angulosCaminhada[6][4][4];
float angulosTrote[6][4][4];
float anguloCabeca;

float anguloTronco;
float deslocamento = 0.0;
float anguloRabo = 0.0;

int estagio = 0;
int passo = 0; // 0 - 10
int caminhando = 1;
float deslocamentoYTronco = 0.0;
int movimentarCavalo = 1;
float anguloCavalo = 0.0;
int passoRabo = 0;
int passoRaboSubindo = 1;
int iluminacao = 1;
int arvores = 1;
float anguloPescoco = 0.0;
int anguloPescocoSubindo = 1;

float xCavalo = 0.0;
float zCavalo = 1.5;


// Prototipo das funcoes
void desenhaEsfera();
void desenhaFemur(int posicao);
void desenhaCanela(int posicao);
void desenhaPata(int posicao);
void desenhaCabeca();
void desenhaCorpo();
void inicializaAngulos();
void renderScene();
void timer(int value);
GLUquadricObj *params = gluNewQuadric();

static float angle=0.0,ratio;
static float x=0.0f,y=0.75f,z=5.0f;
static float lx=0.0f,ly=0.0f,lz=-1.0f;
static float x2 = 0.0f,y2=-0.75f,z2=5.0f;

static float zoom = 1.0f;
//---------------------------------------------------------------------------


/** Função para ler a textura */

/*
unsigned char *leTextura(char *filename, int &width, int &height, int &channels)
{
  unsigned char *img_data = stbi_load(filename, &width, &height, &channels, 3);

  return img_data;
}



// Carrega uma textura
void LoadTexture(char *nomeImagem) {
  // Comandos de inicialização para textura
  int sizeX, sizeY, comp;
  unsigned char *imagemTextura = leTextura(nomeImagem, sizeX, sizeY, comp);

  glGenTextures(1, &idTextura);
  glBindTexture(GL_TEXTURE_2D, idTextura);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, sizeX, sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, imagemTextura);

  // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);  
  // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);

  // Alterações: A resolução da cubo com a textura (imagem) melhora significamente
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);  
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);

  // Inclusão dos comandos
  // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_CLAMP);
  // glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_CLAMP);

  //Alterações: A imagem face frontal do cubo é duplicada
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
 

  // Acrescentando novos comandos
  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

  // EXPERIMENTAÇÕES
  // GL_DECAL: A imagem volta para a cor anterior
  //GL_BLEND: Há uma mudança de cores para cores mais claras na imagem

  glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  // glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
 
  glEnable(GL_TEXTURE_2D);    
}


*/




void PosicionaObservador(void)
{
  // Especifica sistema de coordenadas do modelo
  glMatrixMode(GL_MODELVIEW);
  // Inicializa sistema de coordenadas do modelo
  glLoadIdentity();
  //DefineIluminacao();
  // Especifica posição do observador e do alvo
  glTranslatef(x2,y2,z2);
  glRotatef(deslocamento_rotacao_X,1,0,0);
  glRotatef(deslocamento_rotacao_Y,0,1,0);
}



////////////////////////
////////////////////////

void EspecificaParametrosVisualizacao(void)
{
  // Especifica sistema de coordenadas de projeção
  glMatrixMode(GL_PROJECTION);
  // Inicializa sistema de coordenadas de projeção
  glLoadIdentity();

  // Especifica a projeção perspectiva(angulo,aspecto,zMin,zMax)
  gluPerspective(angle,fAspect,0.5,500);

  PosicionaObservador();

}

// Função callback chamada quando o tamanho da janela é alterado
void AlteraTamanhoJanela(GLsizei w, GLsizei h)
{
  // Para previnir uma divisão por zero
  if ( h == 0 ) h = 1;

  // Especifica as dimensões da viewport
  glViewport(0, 0, w, h);
 
  // Calcula a correção de aspecto
  fAspect = (GLfloat)w/(GLfloat)h;

  EspecificaParametrosVisualizacao();
}



////////////////////////
////////////////////////








void changeSize(int w, int h)
{
  // Prevent a divide by zero, when window is too short
  // (you cant make a window of zero width).
  if(h == 0)
    h = 1;

  ratio = 1.0f * w / h;
  // Reset the coordinate system before modifying
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();

  // Set the viewport to be the entire window
  glViewport(0, 0, w, h);

  // Set the clipping volume
  gluPerspective(45,ratio,1,1000);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  gluLookAt(x, y, z, x + lx,y + ly,z + lz,0.0f,1.0f,0.0f);
}

//---------------------------------------------------------------------------
void desenhaArvore()
{
  glColor3f(0.54,0.4,0.3);
  glRotatef(-90,1,0,0);
  gluCylinder(params,0.2,0.2,2,15,2);
  glTranslatef(0,0,2);
  glColor3f(0.14,0.42,0.13);
  gluCylinder(params,0.8,0.0,2,15,2);

}

void DefineIluminacao (void)
{
  //GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
  //GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};    // "cor"
  GLfloat luzEspecular[4]={10.0, 10.0, 10.0, 100.0};// "brilho"
  //GLfloat posicaoLuz[4]={0.0,-40.0, 0.0, 1.0};

  // Capacidade de brilho do material
  GLfloat especularidade[4]={10.0,1.0,5.0,8.0};
  GLint especMaterial = 60;

  // Define a refletância do material
  glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
  // Define a concentração do brilho
  glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

  // Ativa o uso da luz ambiente
  //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

  // Define os parâmetros da luz de número 0
  //glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
  //glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
  glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
  //glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

  // Nova fonte de luz de número 1
  //glLightfv(GL_LIGHT1, GL_AMBIENT, luzAmbiente);
  //glLightfv(GL_LIGHT1, GL_DIFFUSE, luzDifusa );
  glLightfv(GL_LIGHT1, GL_SPECULAR, luzEspecular );
  //glLightfv(GL_LIGHT1, GL_POSITION, posicaoLuz );    
 
  // Habilita o modelo de colorização de Gouraud
  glShadeModel(GL_SMOOTH);
}



//---------------------------------------------------------------------------
void initScene()
{
  glEnable(GL_DEPTH_TEST);
  fAspect =(GLfloat)Width/ (GLfloat)Height;
}
//---------------------------------------------------------------------------
void renderScene(void) {

 

  int i;
  int j;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpe a tela e o buffer

  GLfloat diffuseLight[] = { 1, 1, 1, 1};
  GLfloat ambientLight[] = { 1, 1, 1, 1};
  GLfloat specularLight[] = { 0.2, 0.3, 0.3, 1};
  GLfloat lightPos[] = { 300.0f, 2000.0f, -20.0f, 1.0f };
  if(iluminacao)
    glEnable(GL_LIGHTING);
  else
    glDisable(GL_LIGHTING);
  glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
  glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
  glEnable(GL_LIGHT0);
  glEnable(GL_COLOR_MATERIAL);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, diffuseLight );
  glMateriali(GL_FRONT_AND_BACK, GL_SHININESS, 50);

  // deseha ch�o
  glPushMatrix();
      glColor3f(0.05f, 0.25f, 0.05f);
    glBegin(GL_QUADS);
      glVertex3f(-100.0f, 0.1f, -100.0f);
      glVertex3f(-100.0f, 0.1f,  100.0f);
      glVertex3f( 100.0f, 0.1f,  100.0f);
      glVertex3f( 100.0f, 0.1f, -100.0f);
    glEnd();
  glPopMatrix();

  if(arvores) {

    DefineIluminacao();
    // Desenha 64  �rvores
    for(i = -4; i < 4; i++)
      for(j=-4; j < 4; j++) {
        glPushMatrix();
          glTranslatef(i*10.0,0,j * 10.0);
          desenhaArvore();
        glPopMatrix();
    }
  }
  glPushMatrix();
    glTranslatef(xCavalo, 0.945,zCavalo);
    glRotatef(anguloCavalo,0,1,0);
    desenhaCorpo();
  glPopMatrix();
  glutSwapBuffers();


}
//---------------------------------------------------------------------------
void orientMe(float ang)
{
  lx = sin(ang);
  lz = -cos(ang);
  glLoadIdentity();
  gluLookAt(x, y, z,
                x + lx,y + ly,z + lz,
                    0.0f,1.0f,0.0f);    


}

void moveFrente(int i){

  x = x + i*(lx)*0.1;
  z = z + i*(lz)*0.1;
 
  glLoadIdentity();
  gluLookAt(x, y, z,
                z + lz,y+ly,-(x+lx),
                    0.0f,1.0f,0.0f);
}

//---------------------------------------------------------------------------
void moveMeFlat(int i) {
  x = x + i*(lx)*0.1;
  z = z + i*(lz)*0.1;
  glLoadIdentity();
  gluLookAt(x, y, z,
                x + lx,y + ly,z + lz,
                    0.0f,1.0f,0.0f);
}



//---------------------------------------------------------------------------
void processNormalKeys(unsigned char key, int x, int y)
{
  switch(key){
    case 27:
      exit(0);
      break;
    case 'b': {

      x2 = -xCavalo;
      z2 = zCavalo - zoom*15.0f;
      y2 = -2.0f;  
      deslocamento_rotacao_X = 0.0f;
      deslocamento_rotacao_Y = 0.0f;
      PosicionaObservador();

      float maiorAngulo = caminhando ? 20.0 : 15.0;
      if(anguloPescoco > maiorAngulo || anguloPescoco < 0.0)
        anguloPescocoSubindo = !anguloPescocoSubindo;
      float incremento = caminhando ? 1.5 : 3.0;
      anguloPescoco = anguloPescocoSubindo ? anguloPescoco + incremento : anguloPescoco - incremento;
      if(passo < 10) {
        caminhando ? passo +=2 : passo +=3;
        if(estagio==0 || estagio==2)
          deslocamentoYTronco += 0.01;
        else if(estagio==1 || estagio==3)
          deslocamentoYTronco -= 0.01;
      } else {
        passo = 0;
        int estagioFinal = 5;
        if(!caminhando)
          estagioFinal = 3;
        if(estagio < estagioFinal)
          estagio++;
        else
          estagio = 0;
      }
      if(movimentarCavalo){
        float deslocamento = caminhando ? 0.03 : 0.12;
        float anguloGraus = anguloCavalo*(M_PI/180);
        xCavalo += deslocamento*cos(anguloGraus);
        zCavalo -= deslocamento*sin(anguloGraus);
      }
      break;
    }
    case ',':
      anguloCavalo += 5;
      break;
    case '.':
      anguloCavalo -= 5;
      break;
  }
  renderScene();
}
//---------------------------------------------------------------------------
/*
void moveCam( float angle, float UpDown )
{
    float dist = sqrt( pow( x-lookAt_x, 2 ) + pow( y-lookAt_y, 2 ) );

    if (UpDown == 0.0)
    {
        cam_pos_x = dist * cos(angle)+ lookAt_x;
        cam_pos_y = dist * sin(angle)+ lookAt_y;
    }
    else
        if ( z + UpDown > -(deslocamentoYTronco+1*0.5) )
            z += UpDown;

    glLoadIdentity();
  gluLookAt(cam_pos_x, cam_pos_y,z,
          lookAt_x, lookAt_y, z,  
        0.0,0.0,1.0 );  
}
*/




void inputKey(int key, int x, int y) {




  switch (key) {
    case GLUT_KEY_LEFT :    
           
      x2+=2;
      PosicionaObservador();
     
      break;
    case GLUT_KEY_RIGHT :  

      x2-=2;
      PosicionaObservador();
     
      break;
    case GLUT_KEY_UP :

      z2+=2;    
      PosicionaObservador();
      //moveMeFlat(5);

      break;
    case GLUT_KEY_DOWN :

      z2-=2;  
      PosicionaObservador();      
      //moveMeFlat(-5);

      break;

    case GLUT_KEY_PAGE_UP:
      //glTranslatef(0, -deslocamento_translation_Z ,0);
      y2-=2;    
      PosicionaObservador();
     
      break;
    case GLUT_KEY_PAGE_DOWN:
      y2+=2;
      PosicionaObservador();
      //glTranslatef(0,deslocamento_translation_Z ,0);
      break;

    case GLUT_KEY_F1:
      deslocamentoYTronco = 0.0;
      caminhando = !caminhando;
      break;
    case GLUT_KEY_F2:
      glutFullScreen ( );
      break;
    case GLUT_KEY_F3:
      glutReshapeWindow ( 640, 360 );
      break;
    case GLUT_KEY_F4:
      iluminacao = !iluminacao;
      break;
    case GLUT_KEY_F5:
      arvores = !arvores;
      break;
    case GLUT_KEY_F6:
      movimentarCavalo = !movimentarCavalo;
      break;
    case GLUT_KEY_F7:
      //glRotatef(angle,1,0,0);      
     
      //angle += 0.05f;
      //orientMe(angle);

      deslocamento_rotacao_Y += 2;

      PosicionaObservador();

      break;
    case GLUT_KEY_F8:
      //glRotatef(angle,0,1,0);
   
      //angle -= 0.05f;
      //orientMe(angle);

      deslocamento_rotacao_Y -= 2;
      PosicionaObservador();

      break;  
    case GLUT_KEY_F9:
      //glRotatef(angle,0,0,1);
      //orientMe(angle);

      //deslocamento_rotacao_Y += 2;
      //PosicionaObservador();

      if(zoom<1.5){
        zoom = zoom +0.1;
      }  

      x2 = -xCavalo;
      z2 = zCavalo - zoom*15.0f;
      y2 = -2.0f;  
      deslocamento_rotacao_X = 0.0f;
      deslocamento_rotacao_Y = 0.0f;
      PosicionaObservador();

      break;

    case GLUT_KEY_F10:
      //glRotatef(angle,0,0,1);
      //orientMe(angle);

      //deslocamento_rotacao_Y += 2;
      //PosicionaObservador();
     
      if(zoom >0.5){
        zoom = zoom-0.1;
      }

      x2 = -xCavalo;
      z2 = zCavalo - zoom*15.0f;
      y2 = -2.0f;  
      deslocamento_rotacao_X = 0.0f;
      deslocamento_rotacao_Y = 0.0f;
      PosicionaObservador();

      break;  
 

  }
  renderScene();
}

//---------------------------------------------------------------------------
int main(int argc, char **argv)
{
  #ifdef BUILDER
    _control87(MCW_EM,MCW_EM); // Desabilitar excessoes em ponto flutuante (builder)
  #endif

  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
  glutInitWindowPosition(100,100);
  glutInitWindowSize(640,360);
  glutCreateWindow("Trabalho de computa��o gr�fica");

  initScene();

  glutKeyboardFunc(processNormalKeys);
  glutSpecialFunc(inputKey);

  glutDisplayFunc(renderScene);
  glutReshapeFunc(changeSize);
  glutTimerFunc (100, timer, 0);

  inicializaAngulos();
  glutMainLoop();

  return(0);
}
//---------------------------------------------------------------------------
float pegaAngulo(int posicao, int parte, bool posicaoAtual)
{
  int estagioDoAngulo = estagio;
  int estagioFinal = caminhando ? 5 : 3;
  if(!posicaoAtual){
    if(estagioDoAngulo==estagioFinal)
      estagioDoAngulo = 0;
    else
      estagioDoAngulo++;
  }

  float (*vetor)[4][4] = caminhando ? angulosCaminhada : angulosTrote;

  int estagioDeTroca = caminhando ? 2 : 1;
  if(estagioDoAngulo>estagioDeTroca) {
    switch(posicao){
      case ESQUERDA_ANTERIOR:
        return vetor[estagioDoAngulo-estagioDeTroca-1][DIREITA_ANTERIOR][parte];
      case DIREITA_ANTERIOR:
        return vetor[estagioDoAngulo-estagioDeTroca-1][ESQUERDA_ANTERIOR][parte];
      case ESQUERDA_POSTERIOR:
        return vetor[estagioDoAngulo-estagioDeTroca-1][DIREITA_POSTERIOR][parte];
      case DIREITA_POSTERIOR:
        return vetor[estagioDoAngulo-estagioDeTroca-1][ESQUERDA_POSTERIOR][parte];
    }
  } else {
    return vetor[estagioDoAngulo][posicao][parte];
  }
  return 0.0;
}
//---------------------------------------------------------------------------
float pegaAngulo(int posicao, int parte)
{
  float fatorPasso = passo/10.0;
  float anguloAtual = pegaAngulo(posicao, parte, true);
  float proximoAngulo = pegaAngulo(posicao, parte, false);

  return anguloAtual + (proximoAngulo - anguloAtual)*fatorPasso;

}
//---------------------------------------------------------------------------
void inicializaAngulos()
{
  angulosCaminhada[0][ESQUERDA_POSTERIOR][FEMUR] = 7;
  angulosCaminhada[0][ESQUERDA_POSTERIOR][CANELA] = -33;
  angulosCaminhada[0][ESQUERDA_POSTERIOR][PATA] = 0;
  angulosCaminhada[0][DIREITA_POSTERIOR][FEMUR] = 4;
  angulosCaminhada[0][DIREITA_POSTERIOR][CANELA] = -4;
  angulosCaminhada[0][DIREITA_POSTERIOR][PATA] = 0;
  angulosCaminhada[0][ESQUERDA_ANTERIOR][QUADRIL] = 15;
  angulosCaminhada[0][ESQUERDA_ANTERIOR][FEMUR] = -35;
  angulosCaminhada[0][ESQUERDA_ANTERIOR][CANELA] = 70;
  angulosCaminhada[0][ESQUERDA_ANTERIOR][PATA] = 0;
  angulosCaminhada[0][DIREITA_ANTERIOR][QUADRIL] = -20;
  angulosCaminhada[0][DIREITA_ANTERIOR][FEMUR] = -26;
  angulosCaminhada[0][DIREITA_ANTERIOR][CANELA] = 39;
  angulosCaminhada[0][DIREITA_ANTERIOR][PATA] = 0;

  angulosCaminhada[1][ESQUERDA_POSTERIOR][FEMUR] = 43;
  angulosCaminhada[1][ESQUERDA_POSTERIOR][CANELA] = -81;
  angulosCaminhada[1][ESQUERDA_POSTERIOR][PATA] = 0;
  angulosCaminhada[1][DIREITA_POSTERIOR][FEMUR] = -8;
  angulosCaminhada[1][DIREITA_POSTERIOR][CANELA] = -6;
  angulosCaminhada[1][DIREITA_POSTERIOR][PATA] = -4;
  angulosCaminhada[1][ESQUERDA_ANTERIOR][QUADRIL] = 5;
  angulosCaminhada[1][ESQUERDA_ANTERIOR][FEMUR] = -20;
  angulosCaminhada[1][ESQUERDA_ANTERIOR][CANELA] = 38;
  angulosCaminhada[1][ESQUERDA_ANTERIOR][PATA] = 0;
  angulosCaminhada[1][DIREITA_ANTERIOR][QUADRIL] = -27;
  angulosCaminhada[1][DIREITA_ANTERIOR][FEMUR] = -25;
  angulosCaminhada[1][DIREITA_ANTERIOR][CANELA] = 30;
  angulosCaminhada[1][DIREITA_ANTERIOR][PATA] = 0;

  angulosCaminhada[2][ESQUERDA_POSTERIOR][FEMUR] = 35;
  angulosCaminhada[2][ESQUERDA_POSTERIOR][CANELA] = -30;
  angulosCaminhada[2][ESQUERDA_POSTERIOR][PATA] = 0;
  angulosCaminhada[2][DIREITA_POSTERIOR][FEMUR] = -20;
  angulosCaminhada[2][DIREITA_POSTERIOR][CANELA] = 0;
  angulosCaminhada[2][DIREITA_POSTERIOR][PATA] = 0;
  angulosCaminhada[2][ESQUERDA_ANTERIOR][QUADRIL] = 20;
  angulosCaminhada[2][ESQUERDA_ANTERIOR][FEMUR] = -60;
  angulosCaminhada[2][ESQUERDA_ANTERIOR][CANELA] = 38;
  angulosCaminhada[2][ESQUERDA_ANTERIOR][PATA] = 0;
  angulosCaminhada[2][DIREITA_ANTERIOR][QUADRIL] = 5;
  angulosCaminhada[2][DIREITA_ANTERIOR][FEMUR] = -70;
  angulosCaminhada[2][DIREITA_ANTERIOR][CANELA] = 40;
  angulosCaminhada[2][DIREITA_ANTERIOR][PATA] = 0;


  angulosTrote[0][ESQUERDA_POSTERIOR][FEMUR] = 70;
  angulosTrote[0][ESQUERDA_POSTERIOR][CANELA] = -70;
  angulosTrote[0][ESQUERDA_POSTERIOR][PATA] = -50;
  angulosTrote[0][DIREITA_POSTERIOR][FEMUR] = -15;
  angulosTrote[0][DIREITA_POSTERIOR][CANELA] = 0;
  angulosTrote[0][DIREITA_POSTERIOR][PATA] = -10;
  angulosTrote[0][ESQUERDA_ANTERIOR][QUADRIL] =-5;
  angulosTrote[0][ESQUERDA_ANTERIOR][FEMUR] = -25;
  angulosTrote[0][ESQUERDA_ANTERIOR][CANELA] = 30;
  angulosTrote[0][ESQUERDA_ANTERIOR][PATA] = -20;
  angulosTrote[0][DIREITA_ANTERIOR][QUADRIL] = 33;
  angulosTrote[0][DIREITA_ANTERIOR][FEMUR] = -75;
  angulosTrote[0][DIREITA_ANTERIOR][CANELA] = 95;
  angulosTrote[0][DIREITA_ANTERIOR][PATA] = -05;

  angulosTrote[1][ESQUERDA_POSTERIOR][FEMUR] = 45;
  angulosTrote[1][ESQUERDA_POSTERIOR][CANELA] = 0;
  angulosTrote[1][ESQUERDA_POSTERIOR][PATA] = 0;
  angulosTrote[1][DIREITA_POSTERIOR][FEMUR] = 25;
  angulosTrote[1][DIREITA_POSTERIOR][CANELA] = -75;
  angulosTrote[1][DIREITA_POSTERIOR][PATA] = 15;
  angulosTrote[1][ESQUERDA_ANTERIOR][QUADRIL] = -25;
  angulosTrote[1][ESQUERDA_ANTERIOR][FEMUR] = -35;
  angulosTrote[1][ESQUERDA_ANTERIOR][CANELA] = 75;
  angulosTrote[1][ESQUERDA_ANTERIOR][PATA] = 0;
  angulosTrote[1][DIREITA_ANTERIOR][QUADRIL] = 10;
  angulosTrote[1][DIREITA_ANTERIOR][FEMUR] = -5;
  angulosTrote[1][DIREITA_ANTERIOR][CANELA] = 45;
  angulosTrote[1][DIREITA_ANTERIOR][PATA] = 0;

  anguloCabeca = 90.0;
  anguloTronco = -3.75;
}
//---------------------------------------------------------------------------
void desenhaCabeca()
{
  glPushMatrix();
  glRotatef(45-anguloPescoco, 0,0,1);
  glPushMatrix();
  glScalef(LARG_PESCOCO,ALT_PESCOCO, COMP_PESCOCO);
  glutSolidCube(0.5);
  glPopMatrix();
  glTranslatef(LARG_PESCOCO*0.19, -ALT_PESCOCO*0.4,0);
  glRotatef(anguloCabeca, 0,0,1);
  glScalef(LARG_CABECA,ALT_CABECA, COMP_CABECA);
  glutSolidCube(0.5);
  glPopMatrix();
}
//---------------------------------------------------------------------------
void desenhaRabo()
{
  float angulo = caminhando ? 0.0 : 5.0;
  float angulo2 = caminhando ? passoRabo  : passoRabo/2;

  // primeiro segmento
  glColor3f(0.6, 0.5, 0.3);
  glutSolidSphere(TAMANHO_ESFERA/1.25,8,8);
  glColor3f(1.0,0.8,0);
  glRotatef(90-angulo2,0,1,0);
  glRotatef(-45+angulo,1,0,0);
  glTranslatef(0,0,-0.20);
  gluCylinder(params,0.020,0.03,0.20,15,2);

  // segundo segmento
  glColor3f(0.6, 0.5, 0.3);
  glutSolidSphere(TAMANHO_ESFERA/1.5,8,8);
  glColor3f(1.0,0.8,0);
  glRotatef(-angulo2*2,0,1,0);
  glRotatef(-24+angulo/2,1,0,0);
  glTranslatef(0,0,-0.15);
  gluCylinder(params,0.015,0.020,0.15,15,2);

  // terceiro segmento
  glColor3f(0.6, 0.5, 0.3);
  glutSolidSphere(TAMANHO_ESFERA/2,8,8);
  glRotatef(-angulo2*3,0,1,0);
  glColor3f(1.0,0.8,0);
  glTranslatef(0,0,-0.25);
  gluCylinder(params,0.0,0.015,0.25,15,2);

}
//---------------------------------------------------------------------------
void desenhaQuadril(int posicao)
{
  glPushMatrix();
  glRotatef(pegaAngulo(posicao,QUADRIL),0,0,1);
  glTranslatef(0.0,-TAMANHO_ESFERA,0.0);
//  glTranslatef(0.0,-ALT_QUADRIL*0.25,0.0);
  glPushMatrix();
  glScalef(LARG_QUADRIL,ALT_QUADRIL, COMP_QUADRIL);

  glRotatef(90,1,0,0);
  gluCylinder(params,0.3,0.3,0.5,15,2);

//  glutSolidCube(0.5);
  glPopMatrix();
  glTranslatef(0.0,-ALT_QUADRIL*0.5-TAMANHO_ESFERA,0.0);
  desenhaEsfera();
  desenhaFemur(posicao);
  glPopMatrix();
}
//---------------------------------------------------------------------------
void desenhaFemur(int posicao)
{
  glPushMatrix();
  glRotatef(pegaAngulo(posicao, FEMUR),0,0,1);
  glTranslatef(0.0,-TAMANHO_ESFERA,0.0);
//  glTranslatef(0.0,-ALT_FEMUR*0.25,0.0);
  glPushMatrix();
  glScalef(LARG_FEMUR,ALT_FEMUR, COMP_FEMUR);

  glRotatef(90,1,0,0);
  gluCylinder(params,0.3,0.3,0.5,15,2);

//  glutSolidCube(0.5);
  glPopMatrix();
  glTranslatef(0.0,-ALT_FEMUR*0.5-TAMANHO_ESFERA,0.0);
  desenhaEsfera();
  desenhaCanela(posicao);
  glPopMatrix();
}
//---------------------------------------------------------------------------
void desenhaCanela(int posicao)
{
  glPushMatrix();
  glRotatef(pegaAngulo(posicao,CANELA),0,0,1);
  glTranslatef(0.0,-TAMANHO_ESFERA,0.0);
//  glTranslatef(0.0,-ALT_CANELA*0.25,0.0);
  glPushMatrix();
  glScalef(LARG_CANELA,ALT_CANELA, COMP_CANELA);

  glRotatef(90,1,0,0);
  gluCylinder(params,0.3,0.3,0.5,15,2);


//  glutSolidCube(0.5);
  glPopMatrix();
  glTranslatef(0.0,-ALT_CANELA*0.5-TAMANHO_ESFERA,0.0);
  desenhaEsfera();
  desenhaPata(posicao);
  glPopMatrix();
}
//---------------------------------------------------------------------------
void desenhaPata(int posicao)
{
  glPushMatrix();
  glRotatef(pegaAngulo(posicao,PATA),0,0,1);
  glTranslatef(0.0,-TAMANHO_ESFERA,0.0);
  glTranslatef(0.0,-ALT_PATA*0.35,0.0);
  glScalef(BASE_PATA,ALT_PATA,BASE_PATA);
  glRotatef(-90,1,0,0);
  glutSolidCone (0.5,0.6,8,6);
  glPopMatrix();
}
//---------------------------------------------------------------------------
void desenhaTronco()
{
  if(!caminhando)
    glTranslatef(0.0,deslocamentoYTronco,0.0);

  glPushMatrix();
  glColor3f(0.6,0.4,0.1);
  glPushMatrix();
    glTranslatef(-LARG_TRONCO*0.2,0,0.0);
    glPushMatrix();
      glScalef(1,ALT_TRONCO*1.5, 1);
      glutSolidSphere(COMP_TRONCO*0.335,8,8);
    glPopMatrix();
    glScalef(LARG_TRONCO,ALT_TRONCO, COMP_TRONCO);
    glRotatef(90,0,1,0);
    gluCylinder(params,0.25,0.25,0.4,15,2);
  glPopMatrix();
  glPushMatrix();
    glTranslatef(LARG_TRONCO*0.2,0,0.0);
    glScalef(1,ALT_TRONCO*1.5, 0.75);
    glutSolidSphere(COMP_TRONCO*0.335,8,8);
  glPopMatrix();

//  glutSolidCube(0.5);
  glColor3f(0.6, 0.25, 0.1);
  glPopMatrix();
}
//---------------------------------------------------------------------------
void desenhaPerna(int posicao)
{
  glPushMatrix();
  if(posicao == ESQUERDA_ANTERIOR || posicao == DIREITA_ANTERIOR)
    desenhaQuadril(posicao);
  else
    desenhaFemur(posicao);
  glPopMatrix();
}
//---------------------------------------------------------------------------
void desenhaEsfera()
{
  glColor3f(0.6, 0.5, 0.3);
  glutSolidSphere(TAMANHO_ESFERA,8,8);
  glColor3f(1.0,0.8,0);
}
//---------------------------------------------------------------------------
void desenhaCorpo()
{
  desenhaTronco();

  glPushMatrix();
  glTranslatef(-LARG_TRONCO*0.17, ALT_TRONCO*0.1, COMP_TRONCO*0.3);
  desenhaEsfera();
  desenhaPerna(ESQUERDA_ANTERIOR);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(LARG_TRONCO*0.22, -ALT_TRONCO*0.2, COMP_TRONCO*0.2);
  desenhaEsfera();
  desenhaPerna(ESQUERDA_POSTERIOR);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(LARG_TRONCO*0.22, -ALT_TRONCO*0.2, -COMP_TRONCO*0.2);
  desenhaEsfera();
  desenhaPerna(DIREITA_POSTERIOR);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-LARG_TRONCO*0.17, ALT_TRONCO*0.1, -COMP_TRONCO*0.3);
  desenhaEsfera();
  desenhaPerna(DIREITA_ANTERIOR);
  glPopMatrix();

  glPushMatrix();
  glTranslatef(LARG_TRONCO*0.25, ALT_TRONCO*0.2, 0.0);
  desenhaCabeca();
  glPopMatrix();
  glPushMatrix();
  glTranslatef(-LARG_TRONCO*0.28, ALT_TRONCO*0.1, 0.0);
  desenhaRabo();
  glPopMatrix();
}
//---------------------------------------------------------------------------
void timer(int value)
{
  if(passoRabo > 15){
    passoRaboSubindo = 0;
    if(caminhando)
      passoRabo--;
    else
      passoRabo -= 2;
  } else if(passoRabo < -15){
    passoRaboSubindo = 1;
    if(caminhando)
      passoRabo++;
    else
      passoRabo += 2;
  } else {
    if(caminhando)
      passoRaboSubindo ? passoRabo++ : passoRabo--;
    else
      passoRaboSubindo ? passoRabo += 2 : passoRabo -=2;
  }

  renderScene();
  glutTimerFunc (50, timer, 0);
}
//---------------------------------------------------------------------------


/*
FUNÇÕES DE MOVIMENTAÇÃO DE CÂMERA DO OUTRO CÓDIGO
*/



/*







// FUNÇÃO PARA MOVER A CÂMERA DESCREVENDO UMA TRAJETÓRIA CIRCULAR
// EM TORNO DA POSIÇÃO (lookAt_x, lookAt_y), ou ...
// MOVER A CÂMERA NO EIXO Z PARA CIMA OU PARA BAIXO
void moveCam( float angle, float UpDown )
{
    float dist = sqrt( pow( cam_pos_x-lookAt_x, 2 ) + pow( cam_pos_y-lookAt_y, 2 ) );

    if (UpDown == 0.0)
    {
        cam_pos_x = dist * cos(angle)+ lookAt_x;
        cam_pos_y = dist * sin(angle)+ lookAt_y;
    }
    else
        if ( cam_pos_z + UpDown > -(LEG_HEIGHT+BASE_HEIGHT*0.5) )
            cam_pos_z += UpDown;

    glLoadIdentity();
  gluLookAt(cam_pos_x, cam_pos_y, cam_pos_z,
          lookAt_x, lookAt_y, lookAt_z,  
        0.0,0.0,1.0 );  
}


// APROXIMAR OU AFASTAR A CÂMERA DO CENTRO DO OBJETO (lookAt_x, lookAt_y)
void zoomCam( int op )
{
    if ( op == ZOOM_IN )
    {
        // verificar se a distância da câmera ao centro de visualização estarão
        // dentro de uma distância mínima após aplicar o 'zoom in'
        if ( sqrt(pow(cam_pos_x-lookAt_x,2) + pow(cam_pos_y-lookAt_y,2)+pow(cam_pos_z-lookAt_z, 2) ) > MIN_ZOOM )
        {
            cam_pos_x -= (cam_pos_x-lookAt_x)*0.1;
            cam_pos_y -= (cam_pos_y-lookAt_y)*0.1;
            cam_pos_z -= (cam_pos_z-lookAt_z)*0.1;
        }
    }
    else
    {
        // verificar se a distância da câmera ao centro de visualização estarão
        // dentro de uma distância máxima após aplicar o 'zoom out'
        if ( sqrt(pow(cam_pos_x-lookAt_x,2) + pow(cam_pos_y-lookAt_y,2) + pow(cam_pos_z-lookAt_z, 2) ) < MAX_ZOOM )
        {
            cam_pos_x += (cam_pos_x-lookAt_x)*0.1;
            cam_pos_y += (cam_pos_y-lookAt_y)*0.1;
            cam_pos_z += (cam_pos_z-lookAt_z)*0.1;
        }
    }
    glLoadIdentity();
  gluLookAt(cam_pos_x, cam_pos_y, cam_pos_z,
          lookAt_x, lookAt_y, lookAt_z,  
        0.0,0.0,1.0 );  
}



// FUNÇÃO USADA PARA MANTER A RAZÃO DE ASPECTO DOS OBJETOS
// QUANDO A JANELA É REDIMENSIONADA
void reshapeWindow(int w, int h)
{
    float ratio;
  // Evitar uma divisão por zero quando a janela se torna muito pequena.
  // (janelas de dimensão zero não são permitidas)
  h == 0 ? h = 1 : h;
    ratio = w / h;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
 
  // viewport redimensionado para as dimensões da janela
  glViewport(0, 0, w, h);

  gluPerspective(45, // campo de visão no plano yz
                   ratio, // razão de aspecto
                   1,     // plano near
                   1000); // planos far

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();

  gluLookAt(cam_pos_x, cam_pos_y, cam_pos_z, // posição da câmera
          lookAt_x, lookAt_y, lookAt_z,  // look-at
        0.0,0.0,1.0 );  // vetor up
}



// PROCESSAMENTO DE TECLAS ESPECIAIS
void processSpecialKeys(int key, int x, int y)
{
    float d_x, d_y; // deslocamento nos eixos x e y

  switch (key)
    {
        // rotaciona a camêra em torno do robo para esquerda em 4º
    case GLUT_KEY_LEFT :
            rot_angle += 3;
            rot_angle_aux = -PI + rot_angle*RADIANS;
            break;
        // rotaciona a camêra em torno do robo para direita em 4º
    case GLUT_KEY_RIGHT :
            rot_angle -= 3;
            rot_angle_aux = PI + rot_angle*RADIANS;
            break;
        // move o robo para frente e atualiza os parâmetros de
        // posição e orientação da câmera para acompanhar o deslocamento
    case GLUT_KEY_UP :
            d_y = -DESLOC*cos(rot_angle_aux);
            d_x = DESLOC*sin(rot_angle_aux);
           
            if ( fabs(walk_y - d_y) < (GROUND_WIDTH*0.48) &&
                 fabs(walk_x - d_x) < (GROUND_WIDTH*0.48) )
            {
                lookAt_y -= d_y;
                cam_pos_y -= d_y;
                 lookAt_x -= d_x;
                cam_pos_x -= d_x;

                walk_y -= d_y;
                walk_x -= d_x;

                animate_base(1);
            }
            break;
        // move a câmera para baixo
    case GLUT_KEY_PAGE_DOWN :
      moveCam(0.0, -0.5);
            break;
        // move a câmera para cima
        case GLUT_KEY_PAGE_UP :
      moveCam(0.0, 0.5);
            break;
  }

    glLoadIdentity();
  gluLookAt(cam_pos_x, cam_pos_y, cam_pos_z, // posição da câmera
          lookAt_x, lookAt_y, lookAt_z,  // look-at
        0.0,0.0,1.0 );  // vetor up
}


// PROCESSA AS TECLAS 'NORMAIS'
void processNormalKeys(unsigned char key, int x, int y )
{
    switch (key)
    {
        // reinicializa os parâmetros
        case 'r':case 'R':
            init();
            glLoadIdentity();
          gluLookAt(cam_pos_x, cam_pos_y, cam_pos_z, // posição da câmera
                  lookAt_x, lookAt_y, lookAt_z,  // look-at
                0.0,0.0,1.0 );  // vetor up
            break;

        //fecha o braço esquerdo do robo
        case 'w':case 'W':
            if ( open_arm_angles[LEFT] + 1 <= 0 )
             open_arm_angles[LEFT] += 3;
            break;

        // abre o braço esquerdo do robo
        case 'q': case 'Q':
            if ( open_arm_angles[LEFT] - 1 >= -180 )
                open_arm_angles[LEFT] -= 3;
            break;

        //abre o braço direito do robo
        case 'p': case 'P':
            if ( open_arm_angles[RIGHT] + 1 <= 180 )
             open_arm_angles[RIGHT] += 3;
            break;

        // fecha o braço esquerdo do robo
        case 'o': case 'O':
            if ( open_arm_angles[RIGHT] - 1 >= 0 )
                open_arm_angles[RIGHT] -= 3;
            break;

        case '+':
            zoomCam( ZOOM_IN );
            break;
        case '-':
            zoomCam( ZOOM_OUT );
            break;

        // move a camera em torno do robo para esquerda
        case '<': case ',':
      move_angle -= 0.1;
      moveCam(move_angle, 0.0);
            break;
        // move a camera em torno do robo para direita
        case '>': case '.':
      move_angle += 0.1;
      moveCam(move_angle, 0.0);
            break;

        // exibe/oculta o menu
        case 'h':case 'H':
            flag_help = !flag_help;
            break;

        // move head up
        case 's':case 'S':
            if ( walking_angles[UP_DOWN][HEAD_JOINT] >= -30 )
                walking_angles[UP_DOWN][HEAD_JOINT] -= 1;
            break;
        // move head down
        case 'x':case 'X':
            if ( walking_angles[UP_DOWN][HEAD_JOINT] <= 60 )
                walking_angles[UP_DOWN][HEAD_JOINT] += 1;
            break;

        // turn head left
        case 'z':case 'Z':
            if ( walking_angles[LEFT_RIGHT][HEAD_JOINT] <= 60 )
                walking_angles[LEFT_RIGHT][HEAD_JOINT] += 1;
            break;
           
        // turn head right
        case 'c': case 'C':
            if ( walking_angles[LEFT_RIGHT][HEAD_JOINT] >= -60 )
                walking_angles[LEFT_RIGHT][HEAD_JOINT] -= 1;
            break;

        // modelo do robo solid/wire
        case 'f': case 'F':
            type_model = !type_model;
            break;

        // chão quadriculado / liso (normal)
        case ' ':
            checkered_ground = !checkered_ground;
            break;

        case KEY_ESC:
            exit(0);
            break;
    }  
}





*/