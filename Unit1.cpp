//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int playerSpeed = 4;

bool player1MoveUp = false;
bool player1MoveDown = false;

bool player2MoveUp = false;
bool player2MoveDown = false;

int dialogHeight = 30;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
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
