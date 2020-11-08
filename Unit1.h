//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Graphics.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TImage *player1;
        TTimer *Timer1;
        TImage *player2;
        TImage *ball;
        TButton *newGameButton;
        TButton *nextRoundButton;
        TLabel *collisionsNumber;
        TLabel *score;
        TLabel *pointFor;
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall newGameButtonClick(TObject *Sender);
        void __fastcall nextRoundButtonClick(TObject *Sender);
        void __fastcall FormCreate(TObject *Sender);
private:	// User declarations
        void gameReset();
        void showScoreBoard();
        void hideScoreBoard();
        bool collisionYdetect(TImage *Sender);


public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
