//---------------------------------------------------------------------------

#ifndef SFDialH
#define SFDialH

#include "CustomDialPies.h"
#include "ChordManager.h"

class ScaleDial : public TCustomDialPies
{
public:
    void __fastcall SelectPie(TObject* Sender) override;
	//void __fastcall OnDialChange(TObject* Sender) override;
	void __fastcall SetOnChange(TNotifyEvent event) override;
	void setChordManager(ChordManager* cm);
	void setIndexPtr(int* ptr);

public:
	__fastcall ScaleDial(TComponent* Owner, int pieCount,
		TAlphaColor pieColour, TAlphaColor selectedColour, TAlphaColor textColour);
	__fastcall ~ScaleDial() override;
	void repaintDial() override;

	ChordManager* chordManager;

	int* indexPtr;

	ScaleDial* dialPtr;

	void setDialPtr(ScaleDial* ptr);

	// TEST for dial coordinates
	//void __fastcall ShowDialPosition(TObject* Sender);
};

class NoteDial : public TCustomDialPies
{
public:
	void __fastcall SelectPie(TObject* Sender) override;
	void __fastcall SetOnChange(TNotifyEvent event) override;
	void setChordManager(ChordManager* cm);
    void setIndexPtr(int* ptr);

public:
	__fastcall NoteDial(TComponent* Owner, int pieCount,
		TAlphaColor pieColour, TAlphaColor selectedColour, TAlphaColor textColour);
	__fastcall ~NoteDial() override;

	ChordManager* chordManager; // Make sure ChordManager is accessible to dial

	int* indexPtr;

	ScaleDial* dialPtr;

    void setDialPtr(ScaleDial* ptr);

	void collapseOtherDial(ScaleDial* dail);
};
//---------------------------------------------------------------------------
#endif
