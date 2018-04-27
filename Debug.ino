
void Debg(){
  
  while(1){ 
    str = Serial.readString();    //чтение комманды  

    if (str != 0){
      Serial.println (str);
      comm();
    }
  }

}


void comm(){
    
    if (str == "help" || str == "/help"){
        Serial.println ("dir; cd_free; new; del; edit; change; reduce; format;");
        Serial.println ("mem_format; mem_write; mem_read; light_ON; light_OFF;");
        Serial.println ("reboot, restart, reset;");
    }
    
    
    else if (str == "LED")
        Serial.println (LED);
    
    
    else if (str == "light_ON")
        lightOn();
    
    else if (str == "light_OFF")
        lightOff();
    
    
  
    else if (str == "dir")
        dir();

    else if (str == "cd_free")
        cd_free();

    else if (str == "new")
        New();

    else if (str == "del")
        del();
    
    else if (str == "edit")
        edit();
    
    else if (str == "change")
        change();
    
    else if (str == "format")
        format();
  
    else if (str == "reduce")
        reduce();
   
    
   
    else if (str == "mem_format")
        mem_format();
    
    else if (str == "mem_write")
        mem_Write();
    
    else if (str == "mem_read")
        mem_Read();
    
    else if (str == "mem_dir")
        mem_dir();
   
    
    else if (str == "reboot" || str == "reset" || str == "restart"){
       for (int a=0; a<3; a++){ Serial.print ("."); delay (500);}
       void(* resetFunc) (void) = 0; 
       resetFunc();
    }
    
    else
        Serial.println ("no command!");
}





void cd_free(){
    for (i=0; i<cells; i++){
          if (buff[i][0]==0 && buff[i][1]==0 && buff[i][2]==0 && buff[i][3]==0 && buff[i][4]==0){
           Serial.print (" free: "); Serial.println (i);
          } 
    }
}


void New(){   
        cd_free();
        Serial.print ("\ncell: ");   i = intIn();        
        Serial.print (" R = ");      buff[i][0] = intIn();        
        Serial.print (" G = ");      buff[i][1] = intIn();        
        Serial.print (" B = ");      buff[i][2] = intIn();        
        Serial.print (" light = ");  buff[i][3] = intIn();
        Serial.print (" mode: ");    buff[i][4] = intIn();
        
   Serial.println ("...");
}


void del(){

       Serial.print (" cell: ");  i = intIn(); 
        buff[i][0]=0;
        buff[i][1]=0;
        buff[i][2]=0;
        buff[i][3]=0;
        buff[i][4]=0;
       Serial.println ("...");
}


void edit(){
   
    Serial.print (" cell: ");   i = intIn();    
    Serial.println ("\tR\tB\tG\tLight\tMode ");
  
    Serial.print (" old = ");
     Serial.print (buff[i][0]); Serial.print ("\t");
     Serial.print (buff[i][1]); Serial.print ("\t");
     Serial.print (buff[i][2]); Serial.print ("\t");
     Serial.print (buff[i][3]); Serial.print ("\t");
     Serial.print (buff[i][4]); Serial.print ("\n\n");

    Serial.println (" new: ");
     Serial.print ("  R = ");     buff[i][0] = intIn();     
     Serial.print ("  G = ");     buff[i][1] = intIn();     
     Serial.print ("  B = ");     buff[i][2] = intIn();     
     Serial.print ("  light = "); buff[i][3] = intIn(); 
     Serial.print ("  mode: ");   buff[i][4] = intIn();
     
  Serial.println ("...");
}


void change(){
    Serial.print (" cell_1: "); 
    i = intIn();
    
     x[0] = buff[i][0];
     x[1] = buff[i][1];
     x[2] = buff[i][2];
     x[3] = buff[i][3];
     x[4] = buff[i][4];
     
    Serial.print (" cell_2: "); 
    j = intIn();
   
     buff[i][0]=buff[j][0];
     buff[i][1]=buff[j][1];
     buff[i][2]=buff[j][2];
     buff[i][3]=buff[j][3];
     buff[i][4]=buff[j][4];

     buff[j][0]=x[0];
     buff[j][1]=x[1];
     buff[j][2]=x[2];
     buff[j][3]=x[3];
     buff[j][3]=x[4];
     
    Serial.println ("...");  
} 


void dir(){
    Serial.println ("\t   R\t B\t G     Light\tMode");
    for (i=0; i<cells; i++){
        Serial.print (" cell_"); Serial.print (i); Serial.print (" = ");
        Serial.print (buff[i][0]); Serial.print ("\t");
        Serial.print (buff[i][1]); Serial.print ("\t");
        Serial.print (buff[i][2]); Serial.print ("\t");
        Serial.print (buff[i][3]); Serial.print ("\t");
        Serial.print (buff[i][4]); Serial.print ("\n");
    }
}


void format(){
  for (i=0; i<cells; i++){
    buff[i][0]=0;
    buff[i][1]=0;
    buff[i][2]=0;
    buff[i][3]=0;
    buff[i][4]=0;
  }  
Serial.println ("...");
}


void reduce(){

    for (i=0; i<cells; i++){
        if (buff[i][0]==0 && buff[i][1]==0 && buff[i][2]==0 && buff[i][3]==0 && buff[i][4]==0){

          j=i;
          for (j; j<cells; j++){
            if (buff[j][0]!=0 || buff[j][1]!=0 || buff[j][2]!=0 || buff[j][3]!=0 || buff[j][4]!=0){

              buff[i][0]=buff[j][0];
              buff[i][1]=buff[j][1];
              buff[i][2]=buff[j][2];
              buff[i][3]=buff[j][3];
              buff[i][4]=buff[j][4];

              buff[j][0]=0;
              buff[j][1]=0;
              buff[j][2]=0;
              buff[j][3]=0;
              buff[j][4]=0;

              break;
            }
          }
        }
    }
  Serial.println ("...");
}



//--------------------------EEPROM-------------------------------

void mem_Read(){

  for (i=0; i<cells; i++){
    buff[i][0]=EEPROM.read(i*5+0); 
    buff[i][1]=EEPROM.read(i*5+1);
    buff[i][2]=EEPROM.read(i*5+2);
    buff[i][3]=EEPROM.read(i*5+3);
    buff[i][4]=EEPROM.read(i*5+4);
  }
 Serial.println ("...");
}


void mem_Write(){
  for (i=0; i<cells; i++){ 
    if (buff[i][0] != EEPROM.read(i*5+0))  EEPROM.write(i*5+0, buff[i][0]);    
    if (buff[i][1] != EEPROM.read(i*5+1))  EEPROM.write(i*5+1, buff[i][1]);     
    if (buff[i][2] != EEPROM.read(i*5+2))  EEPROM.write(i*5+2, buff[i][2]);     
    if (buff[i][3] != EEPROM.read(i*5+3))  EEPROM.write(i*5+3, buff[i][3]);
    if (buff[i][3] != EEPROM.read(i*5+4))  EEPROM.write(i*5+4, buff[i][4]);      
  }
  Serial.println ("...");
}


void mem_dir(){
  for (i=0; i<cells; i++){
     Serial.print ("\t");   Serial.print (EEPROM.read(i*5+0));      
     Serial.print ("\t");   Serial.print (EEPROM.read(i*5+1));                 
     Serial.print ("\t");   Serial.print (EEPROM.read(i*5+2));       
     Serial.print ("\t");   Serial.print (EEPROM.read(i*5+3));  
     Serial.print ("\t");   Serial.print (EEPROM.read(i*5+4)); 
        
     Serial.print ("\n");
  }
}


void mem_format(){
  for (i=0; i<cells; i++){
    if (0 != EEPROM.read(i*5+0))  EEPROM.write(i*5+0, 0);    
    if (0 != EEPROM.read(i*5+1))  EEPROM.write(i*5+1, 0);   
    if (0 != EEPROM.read(i*5+2))  EEPROM.write(i*5+2, 0);       
    if (0 != EEPROM.read(i*5+3))  EEPROM.write(i*5+3, 0);
    if (0 != EEPROM.read(i*5+4))  EEPROM.write(i*5+4, 0);      
  }
  Serial.println ("...");
}
//--------------------------EEPROM-------------------------------




//---------------------------LED-------------------------------

void lightOn(){
  Serial.print (" !!![ using mode=0 ]!!! ");
  Serial.print (" sell: ");
  
   i = intIn(); 
   light = map(buff[i][3], 0, 255, 0, 100);
   light /= 100;
  
  analogWrite (R,buff[i][0]*light); 
  analogWrite (G,buff[i][1]*light);
  analogWrite (B,buff[i][2]*light);  

}


void lightOff(){
  analogWrite (R,0);
  analogWrite (G,0);
  analogWrite (B,0);
  Serial.println ("...");
}
//---------------------------LED-------------------------------




int intIn(){                                      //убрать костыль!!!!!!!!!!!!
    
    if (Serial.available() > 0){
      val = Serial.parseInt();
      Serial.println(val);
      return val;
    }

intIn();    
}  


