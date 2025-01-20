//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "Unit1.h"
#include "scale.h"
#include "note.h"
#include "ChordManager.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource ("*.Windows.fmx", _PLAT_MSWINDOWS)
#pragma resource ("*.Surface.fmx", _PLAT_MSWINDOWS)

constexpr int NOTE_LABEL_SIZE = 50;
constexpr int SCREEN_WIDTH = 780;
constexpr int SCREEN_HEIGHT = 480;

// Vectors to hold objects
std::vector<Scale> scaleObjects{};
std::vector<Note> noteObjects{};


TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	beepCount = 8;

	this->Width = 780;
	this->Height = 480;
	this->BorderStyle = TFmxFormBorderStyle::Sizeable;

	// Initialize form background colour settings
	this->Fill->Kind = TBrushKind::Resource;
	this->Fill->Resource->StyleResource = gradBluePurple2;
	this->Position = TFormPosition::ScreenCenter;
	this->WindowState = TWindowState::wsNormal;

	ChordManager* chordManager = new ChordManager(); // creat ChordManager instance
	int* indexPtr = new int();

	Timer1 = new TTimer(this);
	Timer1->Interval = 500;
    Timer1->OnTimer = Timer1Timer;

	// Generate two custom SFDial dials (derived from TCustomDialPies)
	dial1 = new NoteDial(this, 12, claTurquoise, claAquamarine, claBlack);
	dial1->Parent = this;
	// Here, we set the ChordManager pointer if the NoteDial object
	// to the pointer created with the form
	dial1->setChordManager(chordManager);
	// We want to set the SelectPie() function as the OnChange event handler
	// Since they are overrides sepcific to each dial, we set the Onchange
	// event here
	dial1->setIndexPtr(indexPtr);
	dial1->OnChange = dial1->SelectPie;
	dial1->Width = 100;
	dial1->Height = 100;
	dial1->Position->X = 150;
	dial1->Position->Y = 150;
	dial1->createPolarPies();
	dial1->setLabels(0, "A");
	dial1->setLabels(1, "E");
	dial1->setLabels(2, "B");
	dial1->setLabels(3, "F#");
	dial1->setLabels(4, "Db");
	dial1->setLabels(5, "Ab");
	dial1->setLabels(6, "Eb");
	dial1->setLabels(7, "Bb");
	dial1->setLabels(8, "F");
	dial1->setLabels(9, "C");
	dial1->setLabels(10, "G");
	dial1->setLabels(11, "D");
	dial1->Enabled = true;
	dial1->Opacity = 1;
	dial1->Visible = true;
	dial1->BringToFront();
	dial1->Cursor = crHandPoint;

	dial2 = new ScaleDial(this, 12, claTurquoise, claAquamarine, claBlack);
	dial2->Parent = this;
	dial2->OnChange = dial2->SelectPie;
	// We assign the same ChordManager pointer declared in the form to this
	// dial. Dial2 can then access the ChordManager object created by dail1.
	dial2->setChordManager(chordManager);
	dial2->setIndexPtr(indexPtr);
    dial2->setDialPtr(dial2);
	dial2->Width = 100;
	dial2->Height = 100;
	dial2->Position->X = 510;
	dial2->Position->Y = 150;
	dial2->createPolarPies();
	dial2->setLabels(0, "Hm");
	dial2->setLabels(1, "Mx");
	dial2->setLabels(2, "Mm");
	dial2->setLabels(3, "Mm");
	dial2->setLabels(4, "Ph");
	dial2->setLabels(5, "Ly");
	dial2->setLabels(6, "Lo");
	dial2->setLabels(7, "Pm");
	dial2->setLabels(8, "PM");
	dial2->setLabels(9, "M");
	dial2->setLabels(10, "m");
	dial2->setLabels(11, "D");
	//dial2->StyleLookup = "arcdialstyle"; // important for derived dials
	dial2->Enabled = false;
	dial2->Visible = true;
	dial2->BringToFront();
	dial2->repaintDial();
	dial2->Cursor = crHandPoint;

	dial1->setDialPtr(dial2);

	//----------------------------------------------------------------

	// Initialize play buttons and play circles
	CirclePlayNote = new TCircle(this);
	CirclePlayNote->Parent = this;
	CirclePlayNote->Width = 75;
	CirclePlayNote->Height = 75;
	CirclePlayNote->Position->X = 50;
	CirclePlayNote->Position->Y = 320;
	CirclePlayNote->Fill->Kind = TBrushKind::Solid;
	CirclePlayNote->Fill->Color = claAquamarine;
	CirclePlayNote->Stroke->Color = claAquamarine;
	CirclePlayNote->Opacity = LOW_OPACITY;
	CirclePlayNote->Enabled = false;
	CirclePlayNote->OnClick = chordManager->PlayNoteOnClick;

	CirclePlayScale = new TCircle(this);
	CirclePlayScale->Parent = this;
	CirclePlayScale->Width = 75;
	CirclePlayScale->Height = 75;
	CirclePlayScale->Position->X = 640;
	CirclePlayScale->Position->Y = 320;
	CirclePlayScale->Fill->Kind = TBrushKind::Solid;
	CirclePlayScale->Fill->Color = claAquamarine;
    CirclePlayScale->Stroke->Color = claAquamarine;
	CirclePlayScale->Opacity = LOW_OPACITY;
	CirclePlayScale->Enabled = false;
	CirclePlayScale->OnClick = chordManager->PlayScaleOnClick;

    // Initialize play buttons and play circles
	ButtonPlayNote = new TButton(this);
	ButtonPlayNote->Parent = this;
	ButtonPlayNote->Position->X = CirclePlayNote->Position->X;
	ButtonPlayNote->Position->Y = CirclePlayNote->Position->Y + dial1->Height / 4;
	ButtonPlayNote->StyledSettings = TStyledSettings();
	ButtonPlayNote->StyleLookup = "playtoolbutton";
	ButtonPlayNote->Enabled = false;
    ButtonPlayNote->OnClick = chordManager->PlayNoteOnClick;
	//ButtonPlayNote->Opacity = LOW_OPACITY;

	ButtonPlayScale = new TButton(this);
	ButtonPlayScale->Parent = this;
	ButtonPlayScale->Position->X = CirclePlayScale->Position->X;
	ButtonPlayScale->Position->Y = CirclePlayScale->Position->Y + dial2->Height / 4;
	ButtonPlayScale->StyledSettings = TStyledSettings();
	ButtonPlayScale->StyleLookup = "playtoolbutton";
	ButtonPlayScale->Enabled = false;
    ButtonPlayScale->OnClick = chordManager->PlayScaleOnClick;
	//ButtonPlayScale->Opacity = LOW_OPACITY;

	ButtonPlayNote->SetFocus();
// ----------------------------------------------------------------

	Dial1Light = new TCircle(this);
	Dial1Light->Parent = this;
	Dial1Light->Position->X = dial1->Position->X + (dial1->Width / 4);
	Dial1Light->Position->Y = dial1->Position->Y + (dial1->Height / 4);
	Dial1Light->Fill->Kind = TBrushKind::Solid;
	Dial1Light->Fill->Color = claAquamarine;
	Dial1Light->Stroke->Color = claAquamarine;
	Dial1Light->Opacity = LOW_OPACITY;

	Dial2Light = new TCircle(this);
	Dial2Light->Parent = this;
	Dial2Light->Position->X = dial2->Position->X + (dial2->Width / 4);;
	Dial2Light->Position->Y = dial2->Position->Y + (dial2->Height / 4);
	Dial2Light->Fill->Kind = TBrushKind::Solid;
	Dial2Light->Fill->Color = claAquamarine;
    Dial2Light->Stroke->Color = claAquamarine;
	Dial2Light->Opacity = LOW_OPACITY;

	LabelHz = new TLabel(this);
	LabelHz->Parent = this;
	LabelHz->Width = 65;
    LabelHz->Height = 20;
	LabelHz->Position->X = SCREEN_WIDTH / 2 + 10;
	LabelHz->Position->Y = dial2->Position->Y;// SCREEN_HEIGHT / 2;
    LabelHz->StyledSettings = TStyledSettings();
	LabelHz->TextSettings->VertAlign = TTextAlign::Trailing;
	LabelHz->TextSettings->HorzAlign = TTextAlign::Leading;
	LabelHz->TextSettings->Font->Family = "Source Code Pro";
	LabelHz->TextSettings->Font->Size = 12;
	LabelHz->Font->Style = TFontStyles() << TFontStyle::fsBold;
	LabelHz->TextSettings->FontColor = claSnow;
	LabelHz->Visible = false;

	// Test
	LabelHz->Text = "Hz";
	//LabelHz->Visible = false;

	LabelFrequency = new TLabel(this);
	LabelFrequency->Parent = this;
	LabelFrequency->Width = 65;
	LabelFrequency->Height = 20;
	LabelFrequency->Position->X = SCREEN_WIDTH / 2 - 55;
	LabelFrequency->Position->Y = dial2->Position->Y;
	LabelFrequency->StyledSettings = TStyledSettings();
	LabelFrequency->TextSettings->VertAlign = TTextAlign::Trailing;
	LabelFrequency->TextSettings->HorzAlign = TTextAlign::Center;
	LabelFrequency->TextSettings->Font->Family = "Source Code Pro";
	LabelFrequency->TextSettings->Font->Size = 10;
	LabelFrequency->Font->Style = TFontStyles() << TFontStyle::fsBold;
	LabelFrequency->TextSettings->FontColor = claSnow;

	//Test
	//LabelFrequency->Text = "Frequency";

	LabelRoot = new TLabel(this);
	LabelRoot->Parent = this;
	LabelRoot->Width = 50;
	LabelRoot->Height = 50;
	LabelRoot->Position->X = SCREEN_WIDTH / 2 - 20;
	LabelRoot->Position->Y = dial1->Position->Y - dial1->Height / 2;
	LabelRoot->StyledSettings = TStyledSettings();
	LabelRoot->TextSettings->VertAlign = TTextAlign::Center;
	LabelRoot->TextSettings->HorzAlign = TTextAlign::Leading;
	LabelRoot->TextSettings->Font->Family = "Source Code Pro";
	LabelRoot->TextSettings->Font->Size = 28;
	LabelRoot->Font->Style = TFontStyles() << TFontStyle::fsBold;
	LabelRoot->TextSettings->FontColor = claSnow;

	//Test
	//LabelRoot->Text = "N";

	LabelScale = new TLabel(this);
	LabelScale->Parent = this;
	LabelScale->Width = 120;
	LabelScale->Height = 120;
	LabelScale->Position->X = SCREEN_WIDTH / 2 - 72;
	LabelScale->Position->Y = dial1->Position->Y + dial1->Height / 4;
	LabelScale->StyledSettings = TStyledSettings();
	LabelScale->TextSettings->VertAlign = TTextAlign::Trailing;
	LabelScale->TextSettings->HorzAlign = TTextAlign::Center;
	LabelScale->TextSettings->Font->Family = "Magneto";
	LabelScale->TextSettings->Font->Size = 20;
	LabelScale->Font->Style = TFontStyles() << TFontStyle::fsBold;
	LabelScale->TextSettings->FontColor = claSnow;

	//Test
	//LabelScale->Text = "Scale";

	LabelAppTitle = new TLabel(this);
	LabelAppTitle->Parent = this;
	LabelAppTitle->Width  = 400;
	LabelAppTitle->Height = 64;
	LabelAppTitle->Position->X = dial1->Position->X + 5 + dial1->Width / 4;
	LabelAppTitle->Position->Y = 310;
    LabelAppTitle->Scale->Y = 1.5;
	LabelAppTitle->StyledSettings = TStyledSettings();
    LabelAppTitle->TextSettings->VertAlign = TTextAlign::Center;
	LabelAppTitle->TextSettings->HorzAlign = TTextAlign::Center;
	LabelAppTitle->TextSettings->Font->Family = "Magneto";
	LabelAppTitle->TextSettings->Font->Size = 48;
	LabelAppTitle->Font->Style = TFontStyles() << TFontStyle::fsBold;
	LabelAppTitle->Font->Style = TFontStyles() << TFontStyle::fsUnderline;
	LabelAppTitle->TextSettings->FontColor = claSnow;
	LabelAppTitle->Text = "Scale Finder";
	LabelAppTitle->Visible = true;

	LabelOnOff1 = new TLabel(this);
	LabelOnOff1->Parent = this;
	LabelOnOff1->Position->X = dial1->Position->X + (dial1->Width / 2);
	LabelOnOff1->Position->Y = dial1->Position->Y + (dial1->Height / 2);
    LabelOnOff1->Scale->X = 1.0;
	LabelOnOff1->Scale->Y = 1.0;

	LabelOnOff2 = new TLabel(this);
	LabelOnOff2->Parent = this;
	LabelOnOff2->Position->X = dial2->Position->X + (dial2->Width / 2);
	LabelOnOff2->Position->Y = dial2->Position->Y + (dial2->Height / 2);
	LabelOnOff2->Scale->X = 1.0;
	LabelOnOff2->Scale->Y = 1.0;


	for (int i{0}; i < 8; i++)
	{
		TLabel* scaleNoteLabel = new TLabel(this);
		scaleNoteLabel->Parent = this;
		scaleNoteLabel->Width = NOTE_LABEL_SIZE;
		scaleNoteLabel->Height = NOTE_LABEL_SIZE;
		scaleNoteLabel->Position->X = dial1->Position->X + 5 + (dial1->Width / 4) + (NOTE_LABEL_SIZE * i);
		scaleNoteLabel->Position->Y = 20;
		scaleNoteLabel->StyledSettings = TStyledSettings(); // dissable all styled settings
		scaleNoteLabel->TextSettings->VertAlign = TTextAlign::Center;
		scaleNoteLabel->TextSettings->HorzAlign = TTextAlign::Center;
		scaleNoteLabel->TextSettings->Font->Family = "Source Code Pro";
		scaleNoteLabel->TextSettings->Font->Size = 28;
		scaleNoteLabel->Font->Style = TFontStyles() << TFontStyle::fsBold;
		scaleNoteLabel->TextSettings->FontColor = claSnow;
		scaleNoteLabel->Visible = true;

		// TEST
		//scaleNoteLabel->Text = "L";

		scaleNoteLabels.push_back(scaleNoteLabel);
	}


}
//---------------------------------------------------------------------------

// Function to reset label visibility
void TForm1::setLabelsVisible(std::vector<TLabel*> labelVector)
{
	for (auto label : labelVector)
	{
		label->Visible = true;
	}
}

//---------------------------------------------------------------

// Data display functions


// Function to remove notes from labels held in a vector
void removeLabelNotes(std::vector<TLabel*> labelVector)
{
	for (auto label : labelVector)
	{
		label->Text = " ";
	}
}

// Function to reset scale note labels
void TForm1::showDegreeLabels(std::vector<TLabel*> labelVector)
{
	for (int i{0}; i < std::size(labelVector); i++)
	{
		labelVector[i]->Opacity = LOW_OPACITY;
		labelVector[i]->TextSettings->Font->Size = 14;

		std::string scaleDegree = std::to_string(i + 1);

		if (i == 0)
			scaleDegree.append("st");
		else if (i == 1)
			scaleDegree.append("nd");
		else if (i == 2)
			scaleDegree.append("rd");
		else
			scaleDegree.append("th");

		labelVector[i]->Text = scaleDegree.c_str();
	}
}

// Function to set label visibility to false
void TForm1::setLabelInvisible(std::vector<TLabel*> labelVector, int index)
{
	labelVector[index]->Visible = false;
}


// Function to clear individual label box text
void TForm1::clearLabelText(TLabel* label)
{
	if (label->Text != " ")
		label->Text = " ";
}

//----------------------------------------------------------------------


void __fastcall TForm1::ExitClick(TObject *Sender)
{
	Close();
}

void TForm1::changeLabelFontSize(TLabel* label, int size)
{
	label->TextSettings->Font->Size = size;
}

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
//	for (int i {0}; i < 8; i++)
//	{
//		chordManager->play
//		ResizeLabel();
//		beepCount++;
//	}
//	}
//    else
//	{
//		Timer1->Enabled = false; // Stop the timer after sequence is complete
//	}
}


//---------------------------------------------------------------------------

