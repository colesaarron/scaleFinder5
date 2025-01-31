//---------------------------------------------------------------------------

#pragma hdrstop

#include "CustomDialPies.h"


__fastcall TCustomDialPies::TCustomDialPies(TComponent* Owner)
	: TArcDial(Owner)  // Call the base class constructor
{
	// Initialization code
	//createPies(pieElements);

}

__fastcall TCustomDialPies::TCustomDialPies(TComponent* Owner, int pieCount,
	TAlphaColor pieColour, TAlphaColor selectedColour, TAlphaColor textColour)
	: TArcDial(Owner)  // Call the base class constructor
{
	// Initialization code
	m_pieCount = pieCount;
	m_pieAngle = 360 / pieCount;
	m_offset = m_pieAngle / 2;

	m_pieColour = pieColour;
	m_selectedColour = selectedColour;
	m_textColour = textColour;

	// Use this if not overriding the OnChange event
	//this->OnChange = &SelectPie; // sets onChange event handler to custom handler

}


__fastcall TCustomDialPies::~TCustomDialPies()
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

//------------------------------------------------------------------------

// Function to generate the dial pies
void TCustomDialPies::createPolarPie(int scale, int angle = 0)
{
	// TPie objects have their X and Y positions given by the top left corner.
	// We cannot position the pies using polar corrdinates. Instead we can
    // adjust the rotation by setting the Start and End angles

	double dialRadius = this->Width / 2;
	double pieRadius = dialRadius * scale * 2;
	double dialCentreX = this->Position->X + pieRadius;
	double dialCentreY = this->Position->Y + pieRadius;

	TPie* pie = new TPie(this);
	pie->Parent = this->Parent;
	pie->StartAngle = angle - m_offset;
	pie->EndAngle = pie->StartAngle + m_pieAngle;

	pie->Position->X = this->Position->X - dialRadius;
	pie->Position->Y = this->Position->Y - dialRadius;

	pie->Width = pieRadius;
	pie->Height = pieRadius;


	m_pies.push_back(pie); // push pie object to pie container

	// Create label

	TLabel* label = new TLabel(this);
	label->Parent = this->Parent;
	label->Position->X = (pie->Position->X + pie->Width / 2) +
		(0.8 * this->Width) * std::cos(angle * (PI/180)) - m_offset;
	label->Position->Y = (pie->Position->Y + pie->Height / 2) +
		(0.8 * this->Width) * std::sin(angle * (PI/180)) - m_offset;
	label->Width = m_pieAngle;
	label->Height = m_pieAngle;
	label->BringToFront();
	label->TextSettings->VertAlign = TTextAlign::Center;
	label->TextSettings->HorzAlign = TTextAlign::Center;
	label->StyledSettings = label->StyledSettings >> TStyledSetting::Family;
	label->StyledSettings = label->StyledSettings >> TStyledSetting::Style;
	label->StyledSettings = label->StyledSettings >> TStyledSetting::Size;
	label->StyledSettings = label->StyledSettings >> TStyledSetting::FontColor;
	label->TextSettings->Font->Family = "Source Code Pro";
	label->TextSettings->Font->Size = 16;
	label->Font->Style = TFontStyles() << TFontStyle::fsBold;
	label->TextSettings->FontColor = m_textColour;
	label->Text = "L";

	m_labels.push_back(label); // push label to label container

	//---------------------------------------------------------------

	// TEST labels
//	TLabel* labelTest = new TLabel(this);
//	labelTest->Parent = this->Parent;
//	labelTest->Position->X = (pie->Position->X + pie->Width / 2) +
//		120 * std::cos(angle * (PI/180)) - m_offset - 10;
//	labelTest->Position->Y = (pie->Position->Y + pie->Height / 2) +
//		120 * std::sin(angle * (PI/180)) - m_offset - 10;
//	labelTest->Width = 50;
//	labelTest->Height = 50;
//	labelTest->BringToFront();
//	labelTest->TextSettings->VertAlign = TTextAlign::Center;
//	labelTest->TextSettings->HorzAlign = TTextAlign::Center;
//	//labelTest->StyledSettings = TStyledSettings(); // dissable all styled settings
//	labelTest->StyledSettings = labelTest->StyledSettings >> TStyledSetting::Family;
//	labelTest->StyledSettings = labelTest->StyledSettings >> TStyledSetting::Style;
//	labelTest->StyledSettings = labelTest->StyledSettings >> TStyledSetting::Size;
//	labelTest->StyledSettings = labelTest->StyledSettings >> TStyledSetting::FontColor;
//	labelTest->TextSettings->Font->Family = "Source Code Pro";
//	labelTest->TextSettings->Font->Size = 6; //m_pieAngle / 2;
//	labelTest->Font->Style = TFontStyles() << TFontStyle::fsBold;
//	labelTest->TextSettings->FontColor = claBlack;
//	labelTest->Text = static_cast<String>(std::acos(labelTest->Position->X / 120) * (180 / PI));

	// TEST label to show index, useful for assigning the pies to something
    TLabel* labelTest2 = new TLabel(this);
	labelTest2->Parent = this->Parent;
	labelTest2->Position->X = this->Position->X + dialRadius;
	labelTest2->Position->Y = this->Position->Y + dialRadius * 3;
	labelTest2->TextSettings->VertAlign = TTextAlign::Center;
	//labelTest2->TextSettings->HorzAlign = TTextAlign::Center;

	testLabels.push_back(labelTest2);

	for (auto label : testLabels)
		label->Visible = True; // set to True to see which pies map to index
        label->SendToBack();

	//---------------------------------------------------------------

}

void TCustomDialPies::createPolarPies()
{
    // Clear existing pies
	for(auto pie : m_pies)
	{
		delete pie;
	}
	m_pies.clear();

	for (int i{0}; i < m_pieCount; i++)
	{
		createPolarPie(2, m_pieAngle * i);
	}

	for (auto pie : m_pies)
	{
		pie->Fill->Kind = TBrushKind::Solid;
		pie->Stroke->Kind = TBrushKind::Solid;
		pie->Stroke->Color = 0x0013D9E0;
		pie->Fill->Color = m_pieColour; // claTurquoise
		pie->Opacity = LOW_OPACITY;
		pie->SendToBack();
	}

	for (auto label : m_labels)
	{
		label->SendToBack();
	}

}

void TCustomDialPies::setPiePosition(TPie* pie, int scale)
{
	double dialRadius = this->Width / 2;
	double pieRadius = dialRadius * scale * 2;
	double dialCentreX = this->Position->X + dialRadius;
	double dialCentreY = this->Position->Y + dialRadius;

	pie->Position->X = this->Position->X - 1.5 * dialRadius;
	pie->Position->Y = this->Position->Y - 1.5 * dialRadius;
}

void TCustomDialPies::expandElements(int index)
{
	double baseWidth = m_pies[index]->Width;
	double baseHeight = m_pies[index]->Height;
	m_pies[index]->Size->Width = baseWidth * 1.25;
	m_pies[index]->Size->Height = baseHeight * 1.25;
	setPiePosition(m_pies[index], 2);
	m_pies[index]->Fill->Color = m_selectedColour; // claAquamarine
	m_pies[index]->Opacity = 1;
    m_pies[index]->SendToBack();
	m_pies[index]->Repaint();

	m_labels[index]->Position->X = (m_pies[index]->Position->X +
		m_pies[index]->Width / 2) + this->Width * std::cos((m_pies[index]->StartAngle +
		m_offset)  * (PI/180)) - m_offset;
	m_labels[index]->Position->Y = (m_pies[index]->Position->Y +
		m_pies[index]->Height / 2) + this->Width * std::sin((m_pies[index]->StartAngle +
		m_offset) * (PI/180)) - m_offset;

	m_labels[index]->TextSettings->Font->Size = 20;



}


void TCustomDialPies::collapseElements()
{
	double dialRadius = this->Width / 2;
	double pieRadius = dialRadius * 4;
	double dialCentreX = this->Position->X + dialRadius;
	double dialCentreY = this->Position->Y + dialRadius;

	for (auto pie : m_pies)
	{
		pie->Position->X = this->Position->X - dialRadius;
		pie->Position->Y = this->Position->Y - dialRadius;

		pie->Width = pieRadius;
		pie->Height = pieRadius;
		pie->Fill->Color = m_pieColour;
		pie->Opacity = MID_OPACITY;
        pie->SendToBack();
	}

	for (int i{0}; i < std::size(m_labels); i++)
	{
		double angle = m_pies[i]->StartAngle + m_offset;
		double initFont = 16;

		m_labels[i]->Position->X = (m_pies[i]->Position->X + m_pies[i]->Width / 2) +
			(0.8 * this->Width) * std::cos(angle * (PI/180)) - m_offset;
		m_labels[i]->Position->Y = (m_pies[i]->Position->Y + m_pies[i]->Height / 2) +
			(0.8 * this->Width) * std::sin(angle * (PI/180)) - m_offset;

		m_labels[i]->TextSettings->Font->Size = initFont;
	}
}


void TCustomDialPies::setLabels(int index, String text)
{
	m_labels[index]->Text = text;
	m_labels[index]->Repaint();
    this->Repaint();
}

void TCustomDialPies::repaintDial()
{
    this->Repaint();
}

void TCustomDialPies::resetTextColours(TAlphaColor colour)
{
	m_textColour = colour;
	for (auto label : m_labels)
		label->Repaint();
}
void TCustomDialPies::resetPieColours(TAlphaColor colour1, TAlphaColor colour2)
{
	m_pieColour = colour1;
	m_selectedColour = colour2;

	for (auto pie : m_pies)
		pie->Repaint();
}

// Function to set the selected pie index (for use with derived classes)
void TCustomDialPies::setSelectedPieIndex(int index)
{
    m_selectedPieIndex = index;
}

//-----------------------------------------------------------------------

// Event handler to select a pie for general use
void __fastcall TCustomDialPies::SelectPie(TObject* sender)
{
	// Things to happen first each time dial is turned
	collapseElements();

	double angle = -(this->Value); // current angle of the dial

	if (m_pieCount == 0) {return;}


	for (int i{0}; i < m_pieCount; i++)
	{
		double startAngle = i * m_pieAngle - m_offset;
		double endAngle = (i + 1) * m_pieAngle - m_offset;

		if (angle < 0)
			angle += 360.0;

        // Side case possible fix
		if ((angle >= 345 && angle < 360) || (angle >= 45 && angle < -15))

		{
			expandElements(i);
			setSelectedPieIndex(i);

            // User code should go here if overriding this fucntion

			//TEST
			printSelected(testLabels[0]);
			break;
		}

		if (startAngle < endAngle) 
		{
			if (angle >= startAngle && angle < endAngle) 
			{
				expandElements(i);
				m_selectedPieIndex = i;

				// User code

				//TEST
				printSelected(testLabels[0]);
				break;    
			}	
		}
		else
		{
			if ((angle >= startAngle && angle < 360) || (angle >= 0.0 && angle < endAngle))
			{
				expandElements(i);
				m_selectedPieIndex = i;

                // User code

				// Test
				printSelected(testLabels[0]);
				break;
			}
		}
	}
}

void __fastcall TCustomDialPies::OnDialChange(TObject* Sender)
{
	this->SelectPie(Sender);

}

void __fastcall TCustomDialPies::SetOnChange(TNotifyEvent event)
{
	this->OnChange = event;
}

// Setter functions for derived classes
void TCustomDialPies::setPieCount(int pieCount) {m_pieCount = pieCount;}
void TCustomDialPies::setPieAngle(int pieAngle) {m_pieAngle = pieAngle;}
void TCustomDialPies::setOffset(double offset) {m_offset = offset;}
void TCustomDialPies::setPieColour(TAlphaColor colour) {m_pieColour = colour;}
void TCustomDialPies::setSelectedColour(TAlphaColor colour)
{
	m_selectedColour = colour;
}
void TCustomDialPies::setTextColour(TAlphaColor colour) {m_textColour = colour;}

// Getter functions for derived classes

int TCustomDialPies::getPieCount() const {return m_pieCount;}

int TCustomDialPies::getPieAngle() const {return m_pieAngle;}

double TCustomDialPies::getOffset() const {return m_offset;}

int TCustomDialPies::getSelectedPieIndex() const {return m_selectedPieIndex;}

// TEST to show direction of pie indices in relation to dial
void TCustomDialPies::printSelected(TLabel* label)
{
	label->Text = getSelectedPieIndex();
}

// testLabels contains index label by default
void TCustomDialPies::showTestLabel()
{
	for (auto label : testLabels)
		label->Visible = True;
}

void TCustomDialPies::hideTestLabel()
{
	for (auto label : testLabels)
        label->Visible = False;
}

void TCustomDialPies::makeInvisible()
{
	// Make actual dial invisible
	this->StyleLookup = "";
    this->Visible = false;
	this->Enabled = false;

	// Make pies invisible
	for (auto pie : m_pies)
	{
		pie->Visible = false;
	}

    // Make labels invisible
	for (auto label : m_labels)
	{
		label->Visible = false;
	}

    this->hideTestLabel();
}

void TCustomDialPies::makeVisible()
{
	// Reset visibility to all elements
	this->StyleLookup = "arcdialstyle";
	this->Visible = true;
	this->Enabled = true;

	for (auto pie : m_pies)
	{
		pie->Visible = true;
	}

	for (auto label : m_labels)
	{
		label->Visible = true;
	}

	this->showTestLabel();
}

void TCustomDialPies::hideElements(bool dial, bool pies, bool labels)
{
	if (dial)
	{
		this->StyleLookup = "";
		this->Visible = false;
		this->Enabled = true;
	}

	if (pies)
	{
		for (auto pie : m_pies)
		{
			pie->Visible = false;
		}
	}

	if (labels)
	{
		for (auto label : m_labels)
		{
			label->Visible = false;
		}

		this->hideTestLabel();
	}

}

void TCustomDialPies::setElementVisibility(bool pie, bool label, int index, bool visible)
{
	if (pie)
	{
		if (visible)
			// Hide individual pie
			this->m_pies[index]->Visible = true;
		else
			this->m_pies[index]->Visible = false;
	}

	if (label)
	{
		if (visible)
			this->m_labels[index]->Visible = true;
		else
			this->m_labels[index]->Visible = false;
    }
}

void TCustomDialPies::showElements(bool dial, bool pies, bool labels)
{
	if (dial)
	{
		this->StyleLookup = "";
		this->Visible = false;
		this->Enabled = true;
	}

	if (pies)
	{
		for (auto pie : m_pies)
		{
			pie->Visible = true;
		}
	}

	if (labels)
	{
		for (auto label : m_labels)
		{
			label->Visible = true;
		}

		this->showTestLabel();
	}
}

void TCustomDialPies::setTransparency(bool dial, bool pies, bool labels, int value)
{
	if (dial)
	{
		this->Opacity = value;
	}

	if (pies)
	{
		for (auto pie : m_pies)
		{
			pie->Opacity = value;
        }
	}

	if (labels)
	{
		for (auto label : m_labels)
		{
            label->Opacity = value;
        }
    }
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
