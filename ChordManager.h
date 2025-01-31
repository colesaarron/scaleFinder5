//---------------------------------------------------------------------------

#ifndef ChordManagerH
#define ChordManagerH

#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Menus.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Objects.hpp>
#include <FMX.Graphics.hpp>
#include <FMX.Ani.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.ScrollBox.hpp>
#include <FMX.Edit.hpp>

#include <vector>
#include <string>
#include "Note.h"
#include "Scale.h"
//#include "SFDial.h"

class ChordManager
{
private:

public:
	ChordManager();
	~ChordManager();

	void createChord(int selectedPieIndex);
	void destroyChords();
	void createScale(int selectedPieIndex);
	void createScaleFromPrevious(int selectedPieIndex, int index);
    void changeScaleRoot(int index);
	void destroyScales();


	std::vector<Note*> noteObjects;
	std::vector<Scale*> scaleObjects;

	// Audio control functions
	void playTone(std::vector<Note*> noteObjects);
	void playScaleTones(std::vector<Scale*> scaleObjects, std::vector<TLabel*> labelVector);

	void printNotesToLabels(std::vector<TLabel*> labelVector);
	void printRootNoteFrequency(TLabel* label);
	void printRootNote(TLabel* label);
	void printScale(TLabel* label);
	void setLabelInvisible(std::vector<TLabel*> labelvecotr, int index);

	void __fastcall PlayNoteOnClick(TObject *Sender);

	void __fastcall PlayScaleOnClick(TObject *Sender);


};
//---------------------------------------------------------------------------
#endif
