//---------------------------------------------------------------------------

#ifndef CustomDialPiesH
#define CustomDialPiesH

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
#include <cmath>

// Constants used for formatting
constexpr double LOW_OPACITY = 0.2;
constexpr double MID_OPACITY = 0.5;
constexpr double NOTE_LABEL_ORIGIN = 200;
constexpr double SCALE_LABEL_ORIGIN = 600;
constexpr double PI = 3.14159;

class TCustomDialPies : public TArcDial
{
private:
	int m_pieCount;
    int m_pieAngle;
	double m_offset;
    TAlphaColor m_pieColour;
	TAlphaColor m_selectedColour;
	TAlphaColor m_textColour;
	int m_selectedPieIndex;
	TAlphaColor dialColour;
protected:
    std::vector<TPie*> m_pies;
	std::vector<TLabel*> m_labels;

public:
	__fastcall TCustomDialPies(TComponent* Owner);
	__fastcall TCustomDialPies(TComponent* Owner, int pieCount,
		TAlphaColor pieColour, TAlphaColor selectedColour, TAlphaColor textColour);
	virtual __fastcall ~TCustomDialPies();


	// Public methods to manage pies
	void createPolarPie(int scale, int angle);
	void createPolarPies();

	void setPiePosition(TPie* pie, int scale);
	void expandElements(int pieIndex);
	void collapseElements();

	void setLabels(int index, String text);

    virtual void repaintDial();
	void resetTextColours(TAlphaColor colour);
	void resetPieColours(TAlphaColor colour, TAlphaColor selectColour);

    void setSelectedPieIndex(int index);

	// Methods to override depending on application
	// Override this to set what happens when dial changes
	virtual void __fastcall SelectPie(TObject* Sender);
	virtual void __fastcall OnDialChange(TObject* Sender);
	virtual void __fastcall SetOnChange(TNotifyEvent event);

	// Getters and setters for using with derived classes
	void setPieCount(int pieCount);
	void setPieAngle(int pieAngle);
	void setOffset(double offset);
	void setPieColour(TAlphaColor colour);
	void setSelectedColour(TAlphaColor colour);
	void setTextColour(TAlphaColor colour);

	int getPieCount() const;
	int getPieAngle() const;
	double getOffset() const;
    int getSelectedPieIndex() const;

	// Test
	void printSelected(TLabel* label);
	void showTestLabel();
	void hideTestLabel();
	std::vector<TLabel*> testLabels;

    void makeInvisible();
	void makeVisible();
	void hideElements(bool dial, bool pies, bool labels);
	void setElementVisibility(bool pie, bool label, int index, bool visible);
	void showElements(bool dial, bool pies, bool labels);
	void setTransparency(bool dial, bool pies, bool labels, int value);

};

//---------------------------------------------------------------------------
#endif
