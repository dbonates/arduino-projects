//Programa: Medidor de distancia com 
//          display Oled Colorido SSD1331
//Autor: Arduino e Cia

#include <Ultrasonic.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1331.h>
#include <SPI.h>

//Pinos de ligacao do display SSD1331
#define sclk 13
#define mosi 11
#define cs   10
#define rst  9
#define dc   8

//Definicao de cores
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0
#define WHITE           0xFFFF

//Ligacao do pino Trigger do HC-SR04
#define PINO_TRIGGER  5

//Ligacao do pino Echo do HC-SR04
#define PINO_ECHO     6

//Inicializa o sensor ultrassonico
Ultrasonic Ultrasonic(PINO_TRIGGER, PINO_ECHO);

//Inicializa o display Oled
Adafruit_SSD1331 display = Adafruit_SSD1331(cs, dc, rst);

//Posicao inicial do grafico
int posicao_x = 72;
int posicao_y = 26;
int largura = 8;
int altura = 2;

void setup(void)
{
  Serial.begin(9600);
  display.begin();
  //Informacoes iniciais do display
  display.fillScreen(BLACK);
  display.drawRect(0, 0, 96, 17, WHITE);
  display.fillRect(0, 0, 96, 17, YELLOW);
  display.drawRect(0, 0, 96, 17, WHITE);
  display.drawRect(0, 19 , 54, 44, WHITE);
  display.drawRect(55, 19 , 41, 44, WHITE);
  display.setCursor( 22, 50 );
  display.print("cm");
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor( 22, 5 );
  display.print( "DISTANCIA" );
}

void loop(void)
{
  //Leitura da distancia do HC-SR04
  long distancia = Ultrasonic.distanceRead();

  //Atualiza as informacoes na tela
  AtualizaDisplay(distancia);

  delay(30);
}

void AtualizaDisplay(long val)
{
  //Atualiza a distancia na tela
  display.fillRect(1, 20 , 50, 23, BLACK);
  display.setTextSize(2);
  display.setTextColor(BLUE);
  display.setCursor( 10, 29 );
  display.print( val );

  //Atualiza a animacao da distancia
  display.fillRect(57, 20 , 38, 42, BLACK);
  posicao_x = 72;
  posicao_y = 26;
  largura = 8;
  altura = 2;


  int grafico = map(val, 0, 200, 1, 8);
  if (grafico >= 8)
  {
    grafico = 8;
  }

  //Preenche animacao distancia
  for (int i = 1; i <= grafico; i++)
  {
    display.fillRect(posicao_x, posicao_y , largura, altura, GREEN);
    posicao_x = posicao_x - 2;
    posicao_y = posicao_y + 4;
    largura = largura + 4;
  }
}
