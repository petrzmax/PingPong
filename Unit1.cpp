//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//------GAME SETTINGS------
int playerSpeed = 4;
int ballSpeed = 4;

int dialogHeight = 30;
int playerBorderOffset = 50;

//-----PLAYER MOVEMENT-----
bool player1MoveUp = false;
bool player1MoveDown = false;

bool player2MoveUp = false;
bool player2MoveDown = false;

//-----BALL MOVEMENT-----
bool ballMoveVerticalDirectionUp = false;
bool ballMoveHorizontalDirectionRight = false;

int numberOfBallPlayersCollisions = 0;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        //Update players positions
        player1->Top += (-1*player1MoveUp + player1MoveDown) * playerSpeed;
        player2->Top += (-1*player2MoveUp + player2MoveDown) * playerSpeed;

        //Player1 movement limit
        if( player1->Top <= 0) player1->Top = 0;
        if( player1->Top >= Form1->Height - player1->Height - dialogHeight )
                player1->Top = Form1->Height - player1->Height - dialogHeight;

        //Player2 movement limit
        if( player2->Top <= 0) player2->Top = 0;
        if( player2->Top >= Form1->Height - player2->Height - dialogHeight )
                player2->Top = Form1->Height - player2->Height - dialogHeight;

        //Update ball position
        if(ballMoveVerticalDirectionUp) ball->Top -= ballSpeed;
        else ball->Top += ballSpeed;

        if(ballMoveHorizontalDirectionRight) ball->Left += ballSpeed;
        else ball->Left -= ballSpeed;



        //ball movement limit
        if( ball->Top <= 0) ballMoveVerticalDirectionUp = !ballMoveVerticalDirectionUp;
        if( ball->Top >= Form1->Height - ball->Height - dialogHeight )
                ballMoveVerticalDirectionUp = !ballMoveVerticalDirectionUp;

        //ball Left player1 collision
        if(ball->Left <= player1->Left + player1->Width)
            if(ball->Top + ball->Height / 2 >= player1->Top &&
                ball->Top + ball->Height / 2 <= player1->Top + player1->Height)
            {
                    numberOfBallPlayersCollisions++;
                    ballMoveHorizontalDirectionRight = !ballMoveHorizontalDirectionRight;
            }

        //ball Right player2 collision
        if(ball->Left + ball->Width >= player2->Left)
            if(ball->Top + ball->Height / 2 >= player2->Top &&
                ball->Top + ball->Height / 2 <= player2->Top + player2->Height)
            {
                    numberOfBallPlayersCollisions++;
                    ballMoveHorizontalDirectionRight = !ballMoveHorizontalDirectionRight;
            }

        //Left player1 Loose detection
        if(ball->Left <= playerBorderOffset) Timer1->Enabled = false;

        //Right player2 Loose detection
        if(ball->Left +  ball->Width >= Form1->Width - playerBorderOffset) Timer1->Enabled = false;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
       //Player1 movement pause
       if( Key == 'A') player1MoveUp = false;
       if( Key == 'Z') player1MoveDown = false;

       //Player2 movement pause
       if( Key == VK_UP) player2MoveUp = false;
       if( Key == VK_DOWN) player2MoveDown = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
       //Player1 movement
       if( Key == 'A') player1MoveUp = true;
       if( Key == 'Z') player1MoveDown = true;

       //Player2 movement
       if( Key == VK_UP) player2MoveUp = true;
       if( Key == VK_DOWN) player2MoveDown = true;
}
//---------------------------------------------------------------------------
