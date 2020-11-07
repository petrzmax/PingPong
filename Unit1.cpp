//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

int playerSpeed = 3;
int player1Move = 0;
int dialogHeight = 30;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        player1->Top += player1Move * playerSpeed;

        //Player movement limit
        if( player1->Top <= 0) player1->Top = 0;
        if( player1->Top >= Form1->Height - player1->Height - dialogHeight )
                player1->Top = Form1->Height - player1->Height - dialogHeight;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
       if( Key == 'A') player1Move = 0;
       if( Key == 'Z') player1Move = 0;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        if( Key == 'Z') player1Move = 1;
        if( Key == 'A') player1Move = -1;
}
//---------------------------------------------------------------------------
