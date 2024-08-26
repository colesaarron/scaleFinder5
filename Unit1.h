//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Menus.hpp>
#include <FMX.Objects.hpp>
#include <vector>
#include "CustomDialPies.h"
#include "SFDial.h"
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TBrushObject *gradBluePurple1;
	TMainMenu *MainMenu1;
	TMenuItem *MenuItem1;
	TMenuItem *Exit;
	TBrushObject *gradBluePurple2;
	void __fastcall ExitClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
	//TCustomDialPies* dial1;
	//TCustomDialPies* dial2;
    TTimer* Timer1;
	NoteDial* dial1;
    ScaleDial* dial2;
	TButton* ButtonPlayNote;
	TButton* ButtonPlayScale;
	TCircle* CirclePlayNote;
	TCircle* CirclePlayScale;
	TCircle* Dial1Light;
	TCircle* Dial2Light;
	TLabel* LabelHz;
	TLabel* LabelFrequency;
    TLabel* LabelScale;
    TLabel* LabelRoot;
    TLabel* LabelAppTitle;
	TLabel* LabelOnOff1;
	TLabel* LabelOnOff2;
//	TLabel* Label1st;
//	TLabel* Label2nd;
//	TLabel* Label3rd;
//	TLabel* Label4th;
//	TLabel* Label5th;
//	TLabel* Label6th;
//	TLabel* Label7th;
//	TLabel* Label8th;
    int beepCount;

    std::vector<TLabel*> scaleNoteLabels;
	__fastcall TForm1(TComponent* Owner);
	//void __fastcall CreateKey(TCustomDialPies* dial);
	//void __fastcall CreateScale(TCustomDialPies* dial1, TCustomDialPies* dial2);
	void __fastcall HandleDialChange(TObject* Sender);
	void setLabelsVisible(std::vector<TLabel*> labelVector);
	void showDegreeLabels(std::vector<TLabel*> labelVector);
	void setLabelInvisible(std::vector<TLabel*> labelVector, int index);
	void clearLabelText(TLabel* label);
	void changeLabelFontSize(TLabel* label, int size);

    void __fastcall Timer1Timer(TObject *Sender);


};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
