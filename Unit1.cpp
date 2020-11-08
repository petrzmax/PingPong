//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop
#include "mmsystem.h"

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//------GAME SETTINGS------
int playerSpeed = 4;
int ballHorizontalSpeed = 4;
int ballVerticalSpeed = 4;

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

//-----SCORE-----
int numberOfBallPlayersCollisions = 0;
int leftPlayerPoints = 0;
int rightPlayerPoints = 0;


//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
srand(time(NULL));
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        //Update players positions
        player1->Top += (player1MoveDown - player1MoveUp) * playerSpeed;
        player2->Top += (player2MoveDown - player2MoveUp) * playerSpeed;

        //Player1 movement limit
        if( player1->Top <= 0) player1->Top = 0;
        if( player1->Top >= Form1->Height - player1->Height - dialogHeight )
                player1->Top = Form1->Height - player1->Height - dialogHeight;

        //Player2 movement limit
        if( player2->Top <= 0) player2->Top = 0;
        if( player2->Top >= Form1->Height - player2->Height - dialogHeight )
                player2->Top = Form1->Height - player2->Height - dialogHeight;

        //Update ball position
        if(ballMoveVerticalDirectionUp) ball->Top -= ballVerticalSpeed;
        else ball->Top += ballVerticalSpeed;

        if(ballMoveHorizontalDirectionRight) ball->Left += ballHorizontalSpeed;
        else ball->Left -= ballHorizontalSpeed;

        //ball movement limit
        if( ball->Top <= 0)
        {
                sndPlaySound("snd/collision2.wav", SND_ASYNC);
                ballMoveVerticalDirectionUp = !ballMoveVerticalDirectionUp;
        }
        if( ball->Top >= Form1->Height - ball->Height - dialogHeight )
        {
                sndPlaySound("snd/collision2.wav", SND_ASYNC);
                ballMoveVerticalDirectionUp = !ballMoveVerticalDirectionUp;
        }
        //ball Left player1 collision
        if(ball->Left <= player1->Left + player1->Width && collisionYdetect(player1))
        {
                    numberOfBallPlayersCollisions++;
                    ballMoveHorizontalDirectionRight = !ballMoveHorizontalDirectionRight;
                    sndPlaySound("snd/collision1.wav", SND_ASYNC);

                    if(centerCollisionYdetect(player1))
                    {
                          sndPlaySound("snd/ballUp.wav", SND_ASYNC);
                          ballHorizontalSpeed++;
                    }
        }

        //ball Right player2 collision
        if(ball->Left + ball->Width >= player2->Left && collisionYdetect(player2))
        {
                    numberOfBallPlayersCollisions++;
                    ballMoveHorizontalDirectionRight = !ballMoveHorizontalDirectionRight;
                    sndPlaySound("snd/collision1.wav", SND_ASYNC);

                    if(centerCollisionYdetect(player2))
                    {
                          sndPlaySound("snd/ballUp.wav", SND_ASYNC);
                          ballHorizontalSpeed++;
                    }
        }

        //Left player1 Loose detection
        if(ball->Left <= playerBorderOffset)
        {
                rightPlayerPoints++;
                sndPlaySound("snd/lose.wav", SND_ASYNC);
                pointFor->Caption = "Punkt dla gracza prawego";
                showScoreBoard();
        }

        //Right player2 Loose detection
        if(ball->Left +  ball->Width >= Form1->Width - playerBorderOffset)
        {
                leftPlayerPoints++;
                sndPlaySound("snd/lose.wav", SND_ASYNC);
                pointFor->Caption = "Punkt dla gracza lewego";
                showScoreBoard();
        }
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
void __fastcall TForm1::newGameButtonClick(TObject *Sender)
{
        sndPlaySound("snd/click.wav", SND_ASYNC);
        gameReset();
        hideScoreBoard();

        leftPlayerPoints = 0;
        rightPlayerPoints = 0;
}
//---------------------------------------------------------------------------
void TForm1::gameReset()
{
        //Reset all game variables
        numberOfBallPlayersCollisions = 0;
        ballHorizontalSpeed = 4;
        ballVerticalSpeed = 4;

        //Reset player1 position
        player1->Top = Form1->Height/2 - player1->Height/2;
        player1->Left = playerBorderOffset;

        //Reset player2 position
        player2->Top = Form1->Height/2 - player2->Height/2;
        player2->Left = Form1->Width - playerBorderOffset - player2->Width;

        //Reset ball position
        ball->Top = Form1->Height/2 - ball->Height/2;
        ball->Left = Form1->Width/2 - ball->Width/2;

}
//---------------------------------------------------------------------------
void TForm1::showScoreBoard()
{       //Stop the game
        Timer1->Enabled = false;
        ball->Visible = false;

        //Enable buttons
        newGameButton->Visible = true;
        nextRoundButton->Visible = true;

        //Enable Score
        collisionsNumber->Visible = true;
        score->Visible = true;
        pointFor->Visible = true;

        collisionsNumber->Caption = "Iloœæ odbiæ: " + IntToStr(numberOfBallPlayersCollisions);
        score->Caption = "Wynik: " + IntToStr(leftPlayerPoints) + ":" + IntToStr(rightPlayerPoints);

}
//---------------------------------------------------------------------------
void TForm1::hideScoreBoard()
{
        //Start the game
        Timer1->Enabled = true;
        ball->Visible = true;

        //Hide buttons
        newGameButton->Visible = false;
        nextRoundButton->Visible = false;

        //Hide score
        collisionsNumber->Visible = false;
        score->Visible = false;
        pointFor->Visible = false;
}
//---------------------------------------------------------------------------
bool TForm1::collisionYdetect(TImage *Sender)
{
   if(ball->Top + ball->Height / 2 >= Sender->Top &&
        ball->Top + ball->Height / 2 <= Sender->Top + Sender->Height)
        return true;
   else
        return false;
}
//---------------------------------------------------------------------------
bool TForm1::centerCollisionYdetect(TImage *Sender)
{
if(Sender->Top + (Sender->Height/5)*2 <= ball->Top + ball->Height/2 &&
        Sender->Top + (Sender->Height/5)*3 >= ball->Top + ball->Height/2)
        return true;
else
        return false;
}
//---------------------------------------------------------------------------
bool TForm1::randomBool()
{
     return rand()%2 == 1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::nextRoundButtonClick(TObject *Sender)
{
        sndPlaySound("snd/click.wav", SND_ASYNC);
       gameReset();
       hideScoreBoard();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
     char *startMessage = "Witaj w grze PingPong!\n\n"
          "Sterowanie:\n"
          "Gracz z lewej: A - w górê, B - w dó³\n"
          "Gracz z prawej: Strza³ka w górê - w górê, Strza³ka w dó³ - w dó³\n\n"
          "Gdy odbijesz pi³kê œrodkiem paletki, pi³ka przyœpieszy!\n"

          "Skaluj¹c okno mo¿esz dowolnie zmieniaæ pole gry.\n"
          "\nMi³ego granka!";

     Application->MessageBoxA(startMessage, "PingPong", MB_OK);
     hideScoreBoard();
     Timer1->Enabled = false;
     ball->Visible = false;
     newGameButton->Visible = true;

}
//---------------------------------------------------------------------------

