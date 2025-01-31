//---------------------------------------------------------------------------

#pragma hdrstop

#include "SFDial.h"

__fastcall NoteDial::NoteDial(TComponent* Owner, int pieCount,
		TAlphaColor pieColour, TAlphaColor selectedColour, TAlphaColor textColour)
		: TCustomDialPies{Owner, pieCount, pieColour, selectedColour, textColour}
		, chordManager(nullptr) // initialize ChordManager ptr in this dial
{
    // Initialization code
	setPieCount(pieCount);
	setPieAngle(360 / pieCount);
	setOffset(getPieAngle() / 2);

	setPieColour(pieColour);
	setSelectedColour(selectedColour);
	setTextColour(textColour);

	this->StyleLookup = "arcdialstyle"; // force setting to TArcDial default
    // or leave empty for invisibe dial
}

__fastcall NoteDial::~NoteDial()
{
	// Clean up any dynamically created TPie objects
	for(auto pie : m_pies)
	{
		if (pie)
		{
			pie = nullptr;
			delete pie;
		}
	}
	m_pies.clear();
}

// Event handler to select a pie for general use
void __fastcall NoteDial::SelectPie(TObject* sender)
{
	// Things to happen first each time dial is turned
	collapseElements();


	double angle = -(this->Value); // current angle of the dial

	if (getPieCount() == 0) {return;}



	for (int i{0}; i < this->getPieCount(); i++)
	{

		double startAngle = i * getPieAngle() - getOffset();
		double endAngle = (i + 1) * getPieAngle() - getOffset();

		if (angle < 0)
			angle += 360.0;

        if (this->getSelectedPieIndex() < 0 || this->getSelectedPieIndex() >= this->getPieCount())
			{
				this->setSelectedPieIndex(0);
			}

        // Side case possible fix
		if ((angle >= 345 && angle < 360) || (angle >= 45 && angle < -15))
		{
			expandElements(i);
			setSelectedPieIndex(i);

			if (dialPtr)
			{
				collapseOtherDial(dialPtr);
			}

				chordManager->createChord(0);

			//TEST
			//printSelected(testLabels[0]);
			break;
		}

		if (startAngle < endAngle)
		{

			if (angle >= startAngle && angle < endAngle)
			{
				expandElements(i);
				setSelectedPieIndex(i);

					if (dialPtr)
					{
						collapseOtherDial(dialPtr);
						//Test
						//chordManager->changeScaleRoot(i);
						//ShowMessage("making new scale");
					}

					chordManager->createChord(i);

				//TEST
				printSelected(testLabels[0]);
				break;
			}
		}
		else
		{
			if ((angle >= startAngle && angle < 360) || (angle >= 0.0 && angle < endAngle)
				|| (angle <= startAngle && angle <= endAngle))
			{
				expandElements(i);
				setSelectedPieIndex(i);

				if (dialPtr)
				{
					collapseOtherDial(dialPtr);

				}

				chordManager->createChord(i);

				// TEST
				//printSelected(testLabels[0]);
				break;
			}
		}

	}
}


void __fastcall NoteDial::SetOnChange(TNotifyEvent event)
{
	this->OnChange = event;
}

void NoteDial::setChordManager(ChordManager* cm)
{
    chordManager = cm;
}

void NoteDial::setIndexPtr(int* ptr)
{
    indexPtr = ptr;
}

void NoteDial::setDialPtr(ScaleDial* ptr)
{
	dialPtr = ptr;
}

void NoteDial::collapseOtherDial(ScaleDial* dial)
{
	dial->collapseElements();
}


//-----------------------------------------------------------------------

// ScaleDial definitions

__fastcall ScaleDial::ScaleDial(TComponent* Owner, int pieCount,
		TAlphaColor pieColour, TAlphaColor selectedColour, TAlphaColor textColour)
		: TCustomDialPies{Owner, pieCount, pieColour, selectedColour, textColour}
		, indexPtr(nullptr)
{
    // Initialization code
	setPieCount(pieCount);
	setPieAngle(360 / pieCount);
	setOffset(getPieAngle() / 2);

	setPieColour(pieColour);
	setSelectedColour(selectedColour);
	setTextColour(textColour);

    setSelectedPieIndex(-1);

	this->StyleLookup = "arcdialstyle"; // force setting to TArcDial default

	// Test
	//this->OnMouseEnter = &ShowDialPosition;
}

void __fastcall ScaleDial::SelectPie(TObject* sender)
{
    // Things to happen first each time dial is turned
	collapseElements();
	setSelectedPieIndex(0);

	double angle = -(this->Value); // current angle of the dial

	if (getPieCount() == 0) {return;}
//
//
	for (int i{0}; i < getPieCount(); i++)
	{
		double startAngle = i * getPieAngle() - getOffset();
		double endAngle = (i + 1) * getPieAngle() - getOffset();

		if (angle < 0)
			angle += 360.0;

            // Side case possible fix
		if ((angle >= 345 && angle < 360) || (angle >= 45 && angle < -15))
		{
            expandElements(i);
			setSelectedPieIndex(i);
			indexPtr = &i;
			if (chordManager) // Check if chordManager is set
			{
				chordManager->createScale(i);
			}
			else
				ShowMessage("dial 2 error");

	  		//Test
			//printSelected(testLabels[0]);
			break;
		}

		if (startAngle < endAngle)
		{
			if (angle >= startAngle && angle < endAngle)
			{
				expandElements(i);
				setSelectedPieIndex(i);
				indexPtr = &i;
				if (chordManager) // Check if chordManager is set
				{
					chordManager->createScale(i);
				}
				else
					ShowMessage("dial 2 error");

				//Test
				//printSelected(testLabels[0]);
				break;
			}
		}
		else
		{
			if ((angle >= startAngle && angle < 360) || (angle >= 0.0 && angle < endAngle))
			{
				expandElements(i);
				setSelectedPieIndex(i);
                indexPtr = &i;
				if (chordManager) // Check if chordManager is set
				{
					chordManager->createScale(i);
				}
				else
					ShowMessage("dial 2 error");

				// Test
				//printSelected(testLabels[0]);
				break;
			}
		}
//
		repaintDial();
	}
}

__fastcall ScaleDial::~ScaleDial()
{
	// Clean up any dynamically created TPie objects
	for(auto pie : m_pies)
	{
		if (pie)
		{
			pie = nullptr;
			delete pie;
		}
	}
	m_pies.clear();
}


void __fastcall ScaleDial::SetOnChange(TNotifyEvent event)
{
	this->OnChange = event;
}

void ScaleDial::setChordManager(ChordManager* cm)
{
	chordManager = cm;
}

void ScaleDial::setIndexPtr(int* ptr)
{
	indexPtr = ptr;
}

void ScaleDial::repaintDial()
{
    this->Repaint();
}

// TEST
//void __fastcall ScaleDial::ShowDialPosition(TObject* Sender)
//{
//    ShowMessage(IntToStr(static_cast<int>(this->Position->X)) + ", " +
//		IntToStr(static_cast<int>(this->Position->Y)));
//}
void setScale1(ChordManager* cm, int index, TCustomDialPies* dial)
{
}

void ScaleDial::setDialPtr(ScaleDial* ptr)
{
	dialPtr = ptr;
}


//---------------------------------------------------------------------------
#pragma package(smart_init)
