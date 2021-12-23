#include <Arduino.h>
#define R_direction    4  //控制右邊馬達方向的Pin腳
#define RightWheel_Pin 5  //速度
#define LeftWheel_Pin  6  //速度
#define L_direction    7  //控制左邊馬達方向的Pin腳
int plauseLeft = 0;
int bb=8;
//------avoid-------
int trig = 13 , echo = 12;
//-------PID--------
float Kp=20,Ki=2.5,Kd=2;
float error=0, P=0, I=0, D=0, PID_value=0;
float previous_error=0, previous_I=0;
int initial_motor_speed = 75;
float right_motor_speed;
float left_motor_speed;
//-------PID--------
//-------IRsensor--------
int IRstatus;
int line;
int outline;
int sensor[5]={0, 0, 0, 0, 0};
int SL;
int SML;
int SM;
int SMR;
int SR;
int counterBB = 0;
int counterT =0; //數轉彎
//-------IRsensor--------

int LED_ON = 9 ; 
int counterLL = 0 ; 
int counterRR = 0 ; 


void TurnRight() ; 
void TurnLeft() ; 
void TurnLeft2() ; 


void Forward()
{
  digitalWrite(R_direction,LOW);  
  digitalWrite(L_direction,LOW);
  analogWrite(RightWheel_Pin,80);  //right_motor_speed
  analogWrite(LeftWheel_Pin,80);    //left_motor_speed 80  zuobianbixu kuaiyidian caineng pingheng 
}

void TurnLeft2()  //定位左轉  
{
  counterLL +=1 ; 

  digitalWrite(R_direction,LOW);  
  digitalWrite(L_direction,HIGH);
  analogWrite(RightWheel_Pin,60);  //right_motor_speed
  analogWrite(LeftWheel_Pin,60);                   //left_motor_speed
  delay(150);
  while(1)
  { int a =  analogRead(A2);
    if ( a > 40 )
    break;
    }
}


void TurnLeft()
{
  counterLL += 1 ; 

  if(counterRR + counterLL ==3 && counterBB ==0)  //yuan tu 第一個黑橫線 
  {
    Forward();
    counterLL = 0 ; 
    counterRR  = 0 ; 

  } 

  else
  {
  digitalWrite(R_direction,LOW);  
  digitalWrite(L_direction,LOW);
  analogWrite(RightWheel_Pin,right_motor_speed);  //right_motor_speed
  analogWrite(LeftWheel_Pin,0);                   //left_motor_speed
  delay(150);
  while(1)
  { int a =  analogRead(A2);
    if ( a > 40 )
    break;
    }
  }


}




void TurnRight() 
{

  counterRR +=1 ; 

  if(counterRR==2 || counterRR ==3)   //yuan tu 第二個右轉
  {
    
    
    delay(150);
    digitalWrite(R_direction,HIGH);  
    digitalWrite(L_direction,LOW);
    analogWrite(RightWheel_Pin,80);  //right_motor_speed
    analogWrite(LeftWheel_Pin,80);                   //left_motor_speed
    delay(150);
    
  while(1)
  { int a =  analogRead(A2);
    if ( a > 40 )
    
    break;
    }
      
      
                   
             
      
    /*   新式转弯

    delay(150);
    digitalWrite(R_direction,HIGH);  
    digitalWrite(L_direction,LOW);
    analogWrite(RightWheel_Pin,80);  //right_motor_speed
    analogWrite(LeftWheel_Pin,80);                   //left_motor_speed
    delay(150);
    
  while(1)
  { int a =  analogRead(A2);
    if ( a > 40 )
    break;
    }


digitalWrite(R_direction,LOW);  
      digitalWrite(L_direction,LOW);
      analogWrite(RightWheel_Pin,0);                  //right_motor_speed
      analogWrite(LeftWheel_Pin,left_motor_speed);    //left_motor_speed
      delay(50); //150
            
      int a =  analogRead(A2);
      while(1){

        if ( a > 40 ){
            Forward() ; 
            delay(50) ; 
            break ; 
          }

      }





    */




  }
  


  else if(counterRR+ counterLL==3 && counterBB==0)  //yuan tu 第一個黑橫線
  {
    Forward();

    counterLL = 0 ; 
    counterRR = 0 ; 
  } 
  /*
  if(counterRR ==1 && counterLL ==2  )  // 定位左轉  yinggai yao 7caidui 但是不知道寫8才行 
  { 
    TurnLeft2();

  }
*/


  else{
      digitalWrite(R_direction,LOW);  
      digitalWrite(L_direction,LOW);
      analogWrite(RightWheel_Pin,0);                  //right_motor_speed
      analogWrite(LeftWheel_Pin,left_motor_speed);    //left_motor_speed
      delay(150);
            while(1)
             { int a =  analogRead(A2);
                 if ( a > 40 )
                   break;
             }
      }

}




void StraightLeft()
{
  counterLL +=1 ; 

 delay(100);
  digitalWrite(R_direction,LOW);  
  digitalWrite(L_direction,HIGH);
  analogWrite(RightWheel_Pin,right_motor_speed);  //right_motor_speed
  analogWrite(LeftWheel_Pin,60);                   //left_motor_speed
  delay(500);
  while(1)
  {
    int M = analogRead(A2);
    if(M > 40)
      break;
  }
  
}


  



void StraightRight()
{
  counterRR += 1 ; 

 digitalWrite(R_direction,HIGH);  
  digitalWrite(L_direction,LOW);
  analogWrite(RightWheel_Pin,60);  //right_motor_speed
  analogWrite(LeftWheel_Pin,left_motor_speed);                   //left_motor_speed
  delay(500);
   while(1)
  {
    int M = analogRead(A2);
    if(M > 40)
      break;
  }
}

void Stop()
{
  digitalWrite(R_direction,LOW);  
  digitalWrite(L_direction,LOW);
  analogWrite(RightWheel_Pin,0);  //right_motor_speed
  analogWrite(LeftWheel_Pin,0);    //left_motor_speed
  delay(5000);
}

float cm(int trig, int echo) 
{
  pinMode(trig,OUTPUT);
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig,LOW);
  pinMode(echo, INPUT);
  return pulseIn(echo,HIGH,30000)/58.0;
}

void US()
{
  int Ultrasound = cm(trig,echo);
  if(Ultrasound < 13 && Ultrasound > 4.5) 
  {
    digitalWrite(R_direction,LOW);
    digitalWrite(L_direction,LOW);
    analogWrite(RightWheel_Pin,80);
    analogWrite(LeftWheel_Pin,0);
    delay(550);   //US 500 -> 600
    
    digitalWrite(R_direction,LOW);
    digitalWrite(L_direction,LOW);
    analogWrite(RightWheel_Pin,45);  //45   48
    analogWrite(LeftWheel_Pin,85);  //82   79  改delay 之后切太直变左转 
    while(1)
    {
      int R = analogRead(A2);
      if(R > 40)
        break;
    }
  }
}

void BB()
{
  
  counterBB +=1  ;
/*  if(counterLL ==2 && counterRR== 1)
  {
    TurnLeft2();
  }
  if(counterRR==1  && counterLL ==2 ){  //進入方框

    TurnLeft() ; 

  }

  */

  if( counterLL==2 && counterRR==1){

    digitalWrite(bb,HIGH);
    TurnLeft();

  }
  else if(counterRR  + counterLL ==2 && counterBB==1)  //第一個黑橫線
  {
    Forward();
    counterRR = 0 ; 
    counterLL = 0 ; 
  } 


   if(counterRR + counterLL >=12) //15  quanhei ting 
  { 
    delay(200);
    digitalWrite(R_direction,LOW);
    digitalWrite(L_direction,LOW);
    analogWrite(RightWheel_Pin,0);
    analogWrite(LeftWheel_Pin,0);
    delay(3000000);
  }

  else 
  {
      digitalWrite(R_direction,LOW);  
    digitalWrite(L_direction,LOW);
    analogWrite(RightWheel_Pin,right_motor_speed);  //right_motor_speed
    analogWrite(LeftWheel_Pin,0);                   //left_motor_speed
    delay(150);
    while(1)
    { int a =  analogRead(A2);
      if ( a > 40 )
      break;
      }

     
    
  }
digitalWrite(bb,LOW) ; 
}


void IRAD()
{
  if(analogRead(A0) > 40)  {SL = 1;}else{SL = 0;}
  if(analogRead(A1) > 40) {SML = 1;}else{SML = 0;}
  if(analogRead(A2) > 40)  {SM = 1;}else{SM = 0;}
  if(analogRead(A3) > 40) {SMR = 1;}else{SMR = 0;}
  if(analogRead(A4) > 40)  {SR = 1;}else{SR = 0;}
}
void calculate_pid()
{
  //--------紅外線誤差-------------------
  line = 1;
  outline = 0;

  sensor[0]= SL;
  sensor[1]= SML;
  sensor[2]= SM;
  sensor[3]= SMR;
  sensor[4]= SR;

  if((sensor[0]==outline)&&(sensor[1]==outline)&&(sensor[2]==outline)&&(sensor[3]==outline)&&(sensor[4]==line))
    error=4;
  else if((sensor[0]==line)&&(sensor[1]==outline)&&(sensor[2]==outline)&&(sensor[3]==outline)&&(sensor[4]==outline))
    error=-4;
  
  if((sensor[0]==outline)&&(sensor[1]==outline)&&(sensor[2]==outline)&&(sensor[3]==line)&&(sensor[4]==line))
    error=3;
  else if((sensor[0]==line)&&(sensor[1]==line)&&(sensor[2]==outline)&&(sensor[3]==outline)&&(sensor[4]==outline))
    error=-3;

  if((sensor[0]==outline)&&(sensor[1]==outline)&&(sensor[2]==outline)&&(sensor[3]==line)&&(sensor[4]==outline))
      error=2;
  else if((sensor[0]==outline)&&(sensor[1]==line)&&(sensor[2]==outline)&&(sensor[3]==outline)&&(sensor[4]==outline))
    error=-2;

  if((sensor[0]==outline)&&(sensor[1]==outline)&&(sensor[2]==line)&&(sensor[3]==line)&&(sensor[4]==outline))
    error=1;
  else if((sensor[0]==outline)&&(sensor[1]==line)&&(sensor[2]==line)&&(sensor[3]==outline)&&(sensor[4]==outline))
    error=-1;

  if((sensor[0]==outline)&&(sensor[1]==outline)&&(sensor[2]==line)&&(sensor[3]==outline)&&(sensor[4]==outline))
    error=0;
//--------紅外線誤差-------------------
  P = error;
  I = I + previous_I;
  D = error-previous_error;

  PID_value =(Kp*P) + (Ki*I) + (Kd*D);

  previous_I=I;
  previous_error=error;
}

void motorcontrol()
{
  left_motor_speed = initial_motor_speed+PID_value;
  right_motor_speed = initial_motor_speed-PID_value;  

  if(left_motor_speed < 0)
    left_motor_speed = 0;
  if(right_motor_speed < 0)
    right_motor_speed = 0;
    
  digitalWrite(R_direction,LOW);
  digitalWrite(L_direction,LOW);
  analogWrite(RightWheel_Pin,right_motor_speed);
  analogWrite(LeftWheel_Pin,left_motor_speed);
}




void T() //轉彎加一
 { 
  counterT+=1;
  }

/*void IRcount() 不知道為什麼寫副程式IRstatus就不會+
{
int IRstatus = 0;
int val = analogRead(A0);  //SL +1
    if(val > 40)
      IRstatus= IRstatus + 1;

    val = analogRead(A1);  //SML +2
    if(val > 40)
      IRstatus= IRstatus + 2;

    val = analogRead(A2);  //SM +4
    if(val > 40)
      IRstatus= IRstatus + 4;

    val = analogRead(A3);  //SMR +8
    if(val > 40)
      IRstatus= IRstatus + 8;

    val = analogRead(A4);  //SR +16
    if(val > 40)
      IRstatus= IRstatus + 16;
}*/

void SC()
{
  switch(IRstatus)
  { 
    case 0: //全白 前進
      Forward();
      break;
    case 4: //SM  前進
      motorcontrol();
      break;
    case 2: //SML 向右微調前進
      motorcontrol();
      break;
    case 8: //SMR 向左微調前進
      motorcontrol();
      break;
    case 6: //SM+SML 向右微調前進
      motorcontrol();
      break;
    case 12: //SM+SMR 向左微調前進
      motorcontrol();
      break;
    case 7:  //SM+SML+SL 左轉
      digitalWrite(bb,HIGH);
      T();
      TurnLeft();
      digitalWrite(bb,LOW);
      break;
    case 15: //SMR+SM+SML+SL 左轉
      digitalWrite(bb,HIGH);
      T();
      TurnLeft();
     digitalWrite(bb,LOW);
      break;
    case 3: //SML+SL 左轉
      TurnLeft();
      break;
    case 28: //SM+SMR+SR 右轉
      digitalWrite(bb,HIGH);
      T();
      TurnRight();
      digitalWrite(bb,LOW);
      break;
    case 30: //SML+SM+SMR+SR 右轉
      digitalWrite(bb,HIGH);
      T();
      TurnRight();
     digitalWrite(bb,LOW);
      break;
    case 24: //SMR+SR 右轉
      TurnRight();
      break;
    case 5: //SM+SL 左轉45度轉
      StraightLeft();
      break;
    case 31:
    //digitalWrite(bb,HIGH);
      T();
      BB();
      //digitalWrite(bb,LOW);
      break;
  }
}



void Report()
{
  Serial.print(analogRead(A0));Serial.print("\t");
  Serial.print(analogRead(A1));Serial.print("\t");
  Serial.print(analogRead(A2));Serial.print("\t");
  Serial.print(analogRead(A3));Serial.print("\t");
  Serial.print(analogRead(A4));Serial.print("\t");
  Serial.print(counterBB);Serial.print("\t");
  Serial.println(IRstatus);
}

void setup() 
{
Serial.begin(9600);
pinMode(R_direction,OUTPUT);
pinMode(RightWheel_Pin,OUTPUT);
pinMode(LeftWheel_Pin,OUTPUT);
pinMode(L_direction,OUTPUT);

pinMode(A0,INPUT);
pinMode(A1,INPUT);
pinMode(A2,INPUT);
pinMode(A3,INPUT);
pinMode(A4,INPUT);

pinMode(trig, OUTPUT);
pinMode(echo, INPUT);
}

void loop() 
{
  IRAD();
  calculate_pid();

  IRstatus = 0;
    if(SL == 1)
      IRstatus= IRstatus + 1;

    if(SML == 1)
      IRstatus= IRstatus + 2;

    if(SM == 1)
      IRstatus= IRstatus + 4;

    if(SMR == 1)
      IRstatus= IRstatus + 8;

    if(SR == 1)
      IRstatus= IRstatus + 16;

  SC();

  Report();

  US();

}

