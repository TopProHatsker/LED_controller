//Created by Artem Karchenko (2018 02 11)




//===========================================
//-----------ИСПРАВИТЬ ДОБАВИТЬ--------------
// СТРОКА 65 минимальное время меньше
// ВО ВСЕХ МОДАХ УБРАТЬ delay;
//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//===========================================





#include <EEPROM.h> // подключаем библиотеку EEPROM


//------------------settings-----------------
    double version = 6.40;
    short const cells = 10;
    #define R 9
    #define G 10
    #define B 11
//------------------settings-----------------

 String str;
 float  light=0, real_light=0, a=0, b=0;
 byte i=0, j=0, val=0; 
 
 boolean prev_LED=0, LED=0, up=0;
 short int num=0;
 unsigned long time=0;
 
 short int buff[cells][5], x[5];


byte R_val, G_val, B_val;
byte prev_R_val, prev_G_val, prev_B_val;


void setup(){
  
  pinMode (2, INPUT_PULLUP);
  pinMode (R, OUTPUT);
  pinMode (G, OUTPUT);
  pinMode (B, OUTPUT);
  
   delay (2000);
   if (digitalRead(2) == 0){
     Serial.begin(9600);
      Serial.println ("debug mode:"); 
      Serial.print ("version: "); 
      Serial.println (version);
      Serial.println ();
     Debg();
   }
  Serial.begin (9600);
  mem_Read();                          //считываем данные в оперативку
}


void loop(){
    
      if (digitalRead(2) == 0){                                         //НАЖАТА  
         if (millis()-time >= 1000){
           LED =! LED;
         }                   
      }
      
      else {                                                            //ОТПУЩЕНА
         if (millis()-time > 70 && millis()-time < 400 and LED == 1){         //изменение цвета       
            num++; num %= 10;
            delay (100);
            //Serial.println (num);
         }    
         time = millis(); 
      }
      

//---------------------LED-----------------------
      
      if (prev_LED==0 and LED==1){                       //включение
        
        while (a<=buff[num][3]){
          analogWrite (R,buff[num][0]*a/256);
          analogWrite (G,buff[num][1]*a/256);
          analogWrite (B,buff[num][2]*a/256);
          
          a++;
          delay (1);
        }
        prev_LED = LED;
        delay (500);
      
      }
      
      if (prev_LED==1 and LED==1){                      //светит
        if (buff[num][4]==0) mode_0(num);
        if (buff[num][4]==1) mode_1(num);
        if (buff[num][4]==2){randomSeed (millis()); mode_2(num);}
        if (buff[num][4]==3){randomSeed (millis()); mode_3(num);}
        if (buff[num][4]==4) mode_4(num);
      }
      
      else if (prev_LED==1 and LED==0){                 //выключение
        for (a=buff[num][3]; a >= 0; a--){                   
          analogWrite (R,buff[num][0]*a/256);
          analogWrite (G,buff[num][1]*a/256);
          analogWrite (B,buff[num][2]*a/256);
          delay (1);
        }
        prev_LED = LED;
        delay (600);
      }

      else {                                            //не светит
          analogWrite (R,0);
          analogWrite (G,0);
          analogWrite (B,0);
      }
      
//-------------------LED---------------------
 

  Serial.println (millis()-time);

}      



//------------------------------MODS-------------------------------

void mode_0(int){                                          //просто свечение 
     analogWrite (R,buff[num][0]*buff[num][3]/256.0); 
     analogWrite (G,buff[num][1]*buff[num][3]/256.0);
     analogWrite (B,buff[num][2]*buff[num][3]/256.0);  
}


void mode_1(int){                                          //плавное включение и выключение
     
     light = buff[num][3];
     
     if (up == 1) real_light++;
     if (up == 0) real_light--;
     
     if (real_light > light)  up=0;
     if (real_light < 0)      up=1;
     
     analogWrite (R,buff[num][0]*real_light/256.0); 
     analogWrite (G,buff[num][1]*real_light/256.0);
     analogWrite (B,buff[num][2]*real_light/256.0); 

     delay (7);                        // <=== ЭТОГО ЗДЕСЬ БЫТЬ НЕДОЛЖНО !!!!!!!!!
 
}


void mode_2(int){                       //плавно от случайного к случайному
     
     if (prev_R_val == R_val&& prev_G_val == G_val&& prev_B_val == B_val){    //создание новых целей к которым нужно стремиться!!!
       R_val = random(255); 
       G_val = random(255);
       B_val = random(255);
     }
     
     if (prev_R_val < R_val)          //R
       prev_R_val++;
     else if (prev_R_val > R_val)
       prev_R_val--;
     
     if (prev_G_val < G_val)          //G
       prev_G_val++;
     else if (prev_G_val > G_val)
       prev_G_val--;
       
     if (prev_B_val < B_val)          //B
       prev_B_val++;
     else if (prev_B_val > B_val)
       prev_B_val--;
       

     buff[num][0] = prev_R_val;
     buff[num][1] = prev_G_val;
     buff[num][2] = prev_B_val;
     
     analogWrite (R,prev_R_val); 
     analogWrite (G,prev_G_val);
     analogWrite (B,prev_B_val); 

     /*Serial.println ("$");         //для проги (SerialPortPlotter.exe)
     Serial.println (prev_R_val); 
     Serial.println (" ");
     Serial.println (prev_G_val); 
     Serial.println (" ");
     Serial.println (prev_B_val); 
     Serial.println (";");*/
     
     delay (10);                   // <=== ЭТОГО ЗДЕСЬ БЫТЬ НЕДОЛЖНО !!!!!!!!!

}



void mode_3(int){
       
     if (real_light == 0){    //создание новых целей к которым нужно стремиться!!!
       R_val = random(255); 
       G_val = random(255);
       B_val = random(255);
     }
     
     light = buff[num][3];
     buff[num][0] = R_val;
     buff[num][1] = G_val;
     buff[num][2] = B_val;
     
   
     if (up == 1) real_light++;
     if (up == 0) real_light--;
     
     if (real_light > light)  up=0;
     if (real_light < 0)      up=1;
     
    
     analogWrite (R,R_val*real_light/256.0); 
     analogWrite (G,G_val*real_light/256.0);
     analogWrite (B,B_val*real_light/256.0); 

    /*
     Serial.println ("$");         //для проги (SerialPortPlotter.exe)
     Serial.println (R_val); 
     Serial.println (" ");
     Serial.println (G_val); 
     Serial.println (" ");
     Serial.println (B_val); 
     Serial.println (";");
    */ 
     
     delay (9);               // <=== ЭТОГО ЗДЕСЬ БЫТЬ НЕДОЛЖНО !!!!!!!!!

}


void mode_4(int){       //радуга
 
}

//------------------------------MODS-------------------------------




