
/*  ███╗░░░███╗░█████╗░██████╗░░█████╗░
    ████╗░████║██╔══██╗██╔══██╗██╔══██╗
    ██╔████╔██║██║░░██║██████╔╝██║░░██║
    ██║╚██╔╝██║██║░░██║██╔══██╗██║░░██║
    ██║░╚═╝░██║╚█████╔╝██║░░██║╚█████╔╝
    ╚═╝░░░░░╚═╝░╚════╝░╚═╝░░╚═╝░╚════╝░
*/

/*   
 * @Arquivo PPPainelSolar.ino
 * @autor Orom
 * @version 1.00
 * @date 2022-11-05 Pt-BR
 *
 * @Copyright (c) 2022
 * 
*/

/*
    ░█████╗░██████╗░░█████╗░███╗░░░███╗
    ██╔══██╗██╔══██╗██╔══██╗████╗░████║
    ██║░░██║██████╔╝██║░░██║██╔████╔██║
    ██║░░██║██╔══██╗██║░░██║██║╚██╔╝██║
    ╚█████╔╝██║░░██║╚█████╔╝██║░╚═╝░██║
    ░╚════╝░╚═╝░░╚═╝░╚════╝░╚═╝░░░░░╚═╝
*/


// Projeto de um suporte de placa solar que acompanha a luminosidade do SOL.


    // Poderia ter usado vetor, porem achei mais facil assim!
    #define SensorLuz1 A0 // Definindo o pino SensorLuz1 como o pino
    #define SensorLuz2 A1 // Definindo o pino SensorLuz2 como o pino 
    #define SensorLuz3 A2 // Definindo o pino SensorLuz3 como o pino 
    #define SensorLuz4 A3 // Definindo o pino SensorLuz4 como o pino 
    #define SensorLuz5 A4 // Definindo o pino SensorLuz5 como o pino 
    #define SensorLuz6 A5 // Definindo o pino SensorLuz6 como o pino 
    #define SensorLuz7 A6 // Definindo o pino SensorLuz7 como o pino 
    #define SensorLuz8 A7 // Definindo o pino SensorLuz8 como o pino 
    #define SensorLuz9 A8 // Definindo o pino SensorLuz9 como o pino 
    
    // Poderia ter usado vetor, porem achei mais facil assim!
    int ValorSensor1; // Define uma variavel para setar o valor do sensor
    int ValorSensor2; // Define uma variavel para setar o valor do sensor
    int ValorSensor3; // Define uma variavel para setar o valor do sensor
    int ValorSensor4; // Define uma variavel para setar o valor do sensor
    int ValorSensor5; // Define uma variavel para setar o valor do sensor
    int ValorSensor6; // Define uma variavel para setar o valor do sensor
    int ValorSensor7; // Define uma variavel para setar o valor do sensor
    int ValorSensor8; // Define uma variavel para setar o valor do sensor
    int ValorSensor9; // Define uma variavel para setar o valor do sensor

    int ColunaVerticalEsquerda; // Define uma variavel para somar os valores da coluna Vertical
    int ColunaVerticalMeio; // Define uma variavel para somar os valores da coluna Vertical
    int ColunaVerticalDireita; // Define uma variavel para somar os valores da coluna Vertical

    int ColunaHorizontalBaixo; // Define uma variavel para somar os valores da coluna Vertical
    int ColunaHorizontalMeio; // Define uma variavel para somar os valores da coluna Vertical
    int ColunaHorizontalCima; // Define uma variavel para somar os valores da coluna Vertical

    int DiferencaHorizontalCimaMeio;// Define uma variavel para diferença dos valores da coluna Horizontal
    int DiferencaHorizontalBaixoMeio; // Define uma variavel para diferença dos valores da coluna Horizontal

    int DiferencaVerticalEsquerdaMeio; // Define uma variavel para diferença dos valores da coluna Verticais
    int DiferencaVerticalDireitaMeio;// Define uma variavel para diferença dos valores da coluna Verticais

    // Motor Vidro Eletrico
    #define pMotorVidroD 9 // Definindo o pino PMotorVidroD como o pino 
    #define pMotorVidroE 8 // Definindo o pino PMotorVidroE como o pino 

    // Motor Passo
    #define EnablePasso 7 // Definindo o pino Enable como o pino 
    #define DirecaoPasso 6 // Definindo o pino DirecaoPasso como o pino 
    #define PulsoPasso 5 // Definindo o pino PulsoPassocomo o pino 

    // definição de variaveis de limite
    int posicaoGiro;
    int posicaoPasso = 50;
    int tempo;
    int tempo1;
 
void setup() 
  {
    Serial.begin(9600); // Configura a velocidade de leitura do arduino

    // Ponte H de 40A

    pinMode(11, OUTPUT); //Deixa sempre ativado esse lado da ponte H
    pinMode(10, OUTPUT); //Deixa sempre ativado esse lado da ponte H
    digitalWrite(11, HIGH); //Deixa sempre ativado esse lado da ponte H
    digitalWrite(10, HIGH); //Deixa sempre ativado esse lado da ponte H

    pinMode(pMotorVidroD, OUTPUT);  // Pino de sinal para a ponte H
    pinMode(pMotorVidroE, OUTPUT);  // Pino de sinal para a ponte H

    // Modulo Do MotorDePasso
    pinMode(EnablePasso, OUTPUT);  // Pino de sinal para o motorPasso
    pinMode(DirecaoPasso, OUTPUT);  // Pino de sinal para a motorPasso
    pinMode(PulsoPasso, OUTPUT);  // Pino de sinal para a motorPasso

  }


void loop()
{
      // Seta o motor de passo para ligar.
        digitalWrite(EnablePasso, LOW);

      // Faz a leitura e a lógica de coluna.
        Sensores();
        
      // Confere qual a diferença em destaque, para tomar a primeira decisão
        
        if(((DiferencaVerticalDireitaMeio) || (DiferencaVerticalEsquerdaMeio)) > ((DiferencaHorizontalCimaMeio) || (DiferencaHorizontalBaixoMeio)))
        {
          tempo = 0;
              if(((DiferencaVerticalDireitaMeio) > (DiferencaVerticalEsquerdaMeio)) && (posicaoGiro != 2))
            {
              while(((DiferencaVerticalDireitaMeio) > (DiferencaVerticalEsquerdaMeio)) && (tempo < 3))
              {
                GiroDireita();
                delay(1000);
                tempo++;
                Sensores();

              }
              posicaoGiro = 2;
            }
  
              if((DiferencaVerticalEsquerdaMeio) > (DiferencaVerticalDireitaMeio) && (posicaoGiro != 1))
            {
              while(((DiferencaVerticalDireitaMeio) > (DiferencaVerticalEsquerdaMeio)) && (tempo < 3))
              {
                GiroEsquerda();
                delay(1000);
                tempo++;
                Sensores();

              }
              posicaoGiro = 1;
            }
        }
          
        
        // Confere qual a diferença em destaque, para tomar a primeira decisão
        
        if(((DiferencaHorizontalCimaMeio) || (DiferencaHorizontalBaixoMeio)) >  ((DiferencaVerticalDireitaMeio) || (DiferencaVerticalEsquerdaMeio)))
        {
          tempo1 = 0;
              if(((DiferencaHorizontalCimaMeio) > (DiferencaHorizontalBaixoMeio)) && (posicaoPasso > 30))
            {
              while(((DiferencaHorizontalCimaMeio) > (DiferencaHorizontalBaixoMeio)) && (tempo1 < 5))
              {
              inclinarBaixo();
              tempo1++;
              posicaoPasso = posicaoPasso - 1;
              Sensores();
              }

          }
              if((DiferencaHorizontalBaixoMeio) > (DiferencaHorizontalCimaMeio) && (posicaoPasso < 70))
            {
              while(((DiferencaHorizontalBaixoMeio) > (DiferencaHorizontalCimaMeio)) && (tempo1 < 5))
              inclinarCima();
              tempo1++;
              posicaoPasso = posicaoPasso + 1;
              Sensores();
            }
        }
    // Delay de 30 minutos
    delay(1800000);
        
}

void Sensores()
  {
    // Leitura sensor - Setando valor na variavel
    ValorSensor1 = analogRead(SensorLuz1);
    ValorSensor2 = analogRead(SensorLuz2);
    ValorSensor3 = analogRead(SensorLuz3);
    
    // Leitura sensor - Setando valor na variavel
    ValorSensor4 = analogRead(SensorLuz4);
    ValorSensor5 = analogRead(SensorLuz5);
    ValorSensor6 = analogRead(SensorLuz6);
    
    // Leitura sensor - Setando valor na variavel
    ValorSensor7 = analogRead(SensorLuz7);
    ValorSensor8 = analogRead(SensorLuz8);
    ValorSensor9 = analogRead(SensorLuz9);

    // Logica de coluna aqui sao as colunas verticais
    ColunaVerticalEsquerda = ValorSensor1 + ValorSensor4 + ValorSensor7;
    ColunaVerticalMeio = ValorSensor2 + ValorSensor5 + ValorSensor8;
    ColunaVerticalDireita = ValorSensor3 + ValorSensor6 + ValorSensor9;
    
    // Logica de coluna aqui sao as colunas Horizontais
    ColunaHorizontalCima = ValorSensor7 + ValorSensor8 + ValorSensor9;
    ColunaHorizontalMeio = ValorSensor4 + ValorSensor5 + ValorSensor6;
    ColunaHorizontalBaixo = ValorSensor1 + ValorSensor2 + ValorSensor3;

    // Aqui ele pega a coluna do meio e compara a de cima e a de baixo resultando em um valor
    DiferencaHorizontalBaixoMeio = ColunaHorizontalMeio - ColunaHorizontalBaixo;
    DiferencaHorizontalCimaMeio = ColunaHorizontalMeio - ColunaHorizontalCima;
    
    // Aqui ele pega a coluna do meio e compara a de cima e a de baixo resultando em um valor
    DiferencaVerticalDireitaMeio = ColunaVerticalMeio - ColunaVerticalDireita;
    DiferencaVerticalEsquerdaMeio = ColunaVerticalMeio - ColunaVerticalEsquerda;
  }

void GiroDireita()
  {
  digitalWrite(pMotorVidroD, HIGH);
  digitalWrite(pMotorVidroE, LOW);
  }

void GiroEsquerda()
  {
  digitalWrite(pMotorVidroD, LOW);
  digitalWrite(pMotorVidroE, HIGH);
  }

void GiroParado()
  {
  digitalWrite(pMotorVidroD, LOW);
  digitalWrite(pMotorVidroE, LOW);
  }

void inclinarBaixo()
   {
  PulsoPasso = !PulsoPasso
  digitalWrite(DirecaoPasso, HIGH);
  digitalWrite(PulsoPasso, HIGH);
  delayMicroseconds(100);
  }

void inclinarCima()
  {
  PulsoPasso = !PulsoPasso
  digitalWrite(DirecaoPasso, LOW);
  digitalWrite(PulsoPasso, HIGH);
  delayMicroseconds(100);
  }

void inclinarParado()
  {
  digitalWrite(PulsoPasso, LOW);
  }




/*

░██████╗██╗░░░██╗██████╗░░█████╗░██████╗░████████╗███████╗  ██████╗░██╗░░░░░░█████╗░░█████╗░░█████╗░
██╔════╝██║░░░██║██╔══██╗██╔══██╗██╔══██╗╚══██╔══╝██╔════╝  ██╔══██╗██║░░░░░██╔══██╗██╔══██╗██╔══██╗
╚█████╗░██║░░░██║██████╔╝██║░░██║██████╔╝░░░██║░░░█████╗░░  ██████╔╝██║░░░░░███████║██║░░╚═╝███████║
░╚═══██╗██║░░░██║██╔═══╝░██║░░██║██╔══██╗░░░██║░░░██╔══╝░░  ██╔═══╝░██║░░░░░██╔══██║██║░░██╗██╔══██║
██████╔╝╚██████╔╝██║░░░░░╚█████╔╝██║░░██║░░░██║░░░███████╗  ██║░░░░░███████╗██║░░██║╚█████╔╝██║░░██║
╚═════╝░░╚═════╝░╚═╝░░░░░░╚════╝░╚═╝░░╚═╝░░░╚═╝░░░╚══════╝  ╚═╝░░░░░╚══════╝╚═╝░░╚═╝░╚════╝░╚═╝░░╚═╝

░██████╗░█████╗░██╗░░░░░░█████╗░██████╗░  ██████╗░███████╗███╗░░░███╗
██╔════╝██╔══██╗██║░░░░░██╔══██╗██╔══██╗  ██╔══██╗██╔════╝████╗░████║
╚█████╗░██║░░██║██║░░░░░███████║██████╔╝  ██████╔╝█████╗░░██╔████╔██║
░╚═══██╗██║░░██║██║░░░░░██╔══██║██╔══██╗  ██╔═══╝░██╔══╝░░██║╚██╔╝██║
██████╔╝╚█████╔╝███████╗██║░░██║██║░░██║  ██║░░░░░██║░░░░░██║░╚═╝░██║
╚═════╝░░╚════╝░╚══════╝╚═╝░░╚═╝╚═╝░░╚═╝  ╚═╝░░░░░╚═╝░░░░░╚═╝░░░░░╚═╝

*/
