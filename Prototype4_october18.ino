#define enA 10
#define enB 11

void forward();
void realign();
void spot_left();
void spot_right();
void spot_left_atsnode();
void setup() {

   
  Serial.begin(9600);
  
  //SENSOR PINS
  pinMode(2,INPUT); //LEFT
  pinMode(3,INPUT); //FRONT
  pinMode(4,INPUT); //MIDDLE
  pinMode(5,INPUT); //RIGHT
  pinMode(6,INPUT); //MIDDLE LEFT
  pinMode(7,INPUT); //MIDDLE RIGHT
  pinMode(13,INPUT); //BACK
  pinMode(enA,OUTPUT);
  pinMode(enB,OUTPUT);
  
  //MOTOR PINS

  //RIGHT MOTORS
  
  pinMode(A0,OUTPUT);//+ve
  pinMode(A1,OUTPUT);//-ve
  pinMode(enB,OUTPUT);//enB
  //LEFT MOTORS
  
  pinMode(A2,OUTPUT);//+ve
  pinMode(A3,OUTPUT);//-ve
  pinMode(enA,OUTPUT);//enA
  

}

void loop() {

  int F,L,R,B,M,ML,MR;
  
  L = digitalRead(2);
  F = digitalRead(3);
  M = digitalRead(4);
  R = digitalRead(5);
  ML = digitalRead(6);
  MR = digitalRead(7);
  B = digitalRead(13);

  Serial.print(L);
  Serial.print(F);
  Serial.print(M);
  Serial.print(R);
  Serial.print(ML);
  Serial.print(MR);
  Serial.println(B);


    if (  ((M==1)&&(MR==1)&&(ML==1)&&(R==0)&&(L==0))  ||  ((M==1)&&(MR==1)&&(ML==1)&&(R==0)&&(L==0))  )
    {

        //STRAIGHT PATH
        
      forward();
    }

    else if ((M==0)&&(MR==1)&&(ML==0))
    {
      
      //TURN RIGHT TO REALIGN
      
      analogWrite(A0,0);
      analogWrite(A1,0);

      analogWrite(A2,255);
      analogWrite(A3,0);
    }

    else if ( ((M==0)&&(ML==1)&&(MR==0) ))
    {
      
      //TURN LEFT TO REALIGN
      
      analogWrite(A0,255);
      analogWrite(A1,0);

      analogWrite(A2,0);
      analogWrite(A3,0);
    }

    else if ( ((M==1)&&(B==1)&&(R==1)&&(L==0)&&(F==0)) || ((M==1)&&(B==1)&&(L==1)&&(R==0)&&(F==0))   || ((M==1)&&(B==1)&&(L==1)&&(R==1)&&(F==0))  ||  ((M==1)&&(B==1)&&(L==1)&&(R==1)&&(F==1))  ||  ((M==1)&&(B==1)&&(R==0)&&(L==1)&&(F==1)) ||  ((M==1)&&(B==1)&&(R==1)&&(L==0)&&(F==1)))
    {
      analogWrite(A0,128);
      analogWrite(A1,0);

      analogWrite(A2,128);
      analogWrite(A3,0);
      delay (5);

      L = digitalRead(2);
      F = digitalRead(3);
      M = digitalRead(4);
      R = digitalRead(5);
      ML = digitalRead(6);
      MR = digitalRead(7);
      B = digitalRead(13);
      if ((M==1)&&(B==1)&&(L==1)&&(R==0)&&(F==0))
    {

      //SPOT LEFT
        spot_left(); 
     
    }

    else if ((M==1)&&(B==1)&&(R==1)&&(L==0)&&(F==0))
    {

      //SPOT RIGHT
     
        spot_right();
    }

    else if ((M==1)&&(B==1)&&(L==1)&&(R==1)&&(F==0))
    {

      //T INTERESECTION PRIORTISE LEFT 
      //SPOT LEFT
      
     spot_left();
        
    }
    else if((M==1)&&(B==1)&&(L==1)&&(R==1)&&(F==1))
    {
      //+ intersection
      //prioritise left
      //initiate SPOT LEFT
      
      analogWrite(A0,255);
      analogWrite(A1,0);

      analogWrite(A2,0);
      analogWrite(A3,255);
      delay (15);
      
      spot_left();
      
    }
    else if((M==1)&&(B==1)&&(R==0)&&(L==1)&&(F==1))
    {
      //          _|    intersection
      //           |
      //initiate spot left for delay
      analogWrite(A0,255);
      analogWrite(A1,0);

      analogWrite(A2,0);
      analogWrite(A3,255);
      delay (15);
      //SPOT LEFT
      
      spot_left();
    }
    else if((M==1)&&(B==1)&&(R==1)&&(L==0)&&(F==1))
    {

      //forward

      forward();
    }
    }
 
    
     else if ((M==0)&&(B==0)&&(L==0)&&(R==0)&&(F==0))
    {

      //DEFAULT CASE TO STOP
      
      analogWrite(A0,0);
      analogWrite(A1,0);

      analogWrite(A2,0);
      analogWrite(A3,0);     
    }

    
}


void forward()
{
      analogWrite(A0,255);
      analogWrite(A1,0);

      analogWrite(A2,255);
      analogWrite(A3,0);
}


void spot_left()
{
   while((digitalRead(3)!=1))
      {
      analogWrite(A0,255);
      analogWrite(A1,0);

      analogWrite(A2,0);
      analogWrite(A3,255);
      
      }
      delay (5);
      analogWrite(A0,255);
      analogWrite(A1,0);

      analogWrite(A2,255);
      analogWrite(A3,0);
      delay (10);
}

void spot_right()
{
  while (digitalRead(3)!=1)
      {
      analogWrite(A0,0);
      analogWrite(A1,255);

      analogWrite(A2,255);
      analogWrite(A3,0);
      }

      delay (5);
      analogWrite(A0,255);
      analogWrite(A1,0);

      analogWrite(A2,255);
      analogWrite(A3,0);
      delay (10);
}

