//---------------------------------------------------------------------------
// A class to use with CustomDialPies to generate Notes and Scales

#pragma hdrstop

#include "ChordManager.h"
#include "Unit1.h"
#include "windows.h"

ChordManager::ChordManager()
{}

ChordManager::~ChordManager()
{}

void ChordManager::createChord(int selectedPieIndex)
{
	Form1->dial2->Enabled = false;
	Form1->CirclePlayScale->Enabled = false;
	Form1->ButtonPlayScale->Enabled = false;
	Form1->LabelScale->Text = "";

	destroyChords();

	if (selectedPieIndex >= 0 && selectedPieIndex < 12)
	{
		Note* note = nullptr;
		Scale* scale = nullptr;

		switch (selectedPieIndex)
		{
			case 0 :
				note = new Note{};
				this->noteObjects.push_back(note);
				scale = new Scale{*noteObjects[0]};
				scaleObjects.push_back(scale);
				break;
			case 1 :
				note = new Note{"E"};
				this->noteObjects.push_back(note);
				scale = new Scale{*noteObjects[0]};
				this->scaleObjects.push_back(scale);
				break ;
			case 2 :
				note = new Note{"B"};
				this->noteObjects.push_back(note);
				scale = new Scale{*noteObjects[0]};
				this->scaleObjects.push_back(scale);
				break;
			case 3 :
				note = new Note{"F#"};
				this->noteObjects.push_back(note);
				scale = new Scale{*noteObjects[0]};
				this->scaleObjects.push_back(scale);
				break;
			case 4 :
				note = new Note{"Db"};
				this->noteObjects.push_back(note);
				scale = new Scale{*noteObjects[0]};
				scaleObjects.push_back(scale);
				break;
			case 5 :
				note = new Note{"Ab"};
				this->noteObjects.push_back(note);
				scale = new Scale{*noteObjects[0]};
				this->scaleObjects.push_back(scale);
				break;
			case 6 :
				note = new Note{"Eb"};
				this->noteObjects.push_back(note);
				scale = new Scale{*noteObjects[0]};
				scaleObjects.push_back(scale);
				break;
			case 7 :
				note = new Note{"Bb"};
				this->noteObjects.push_back(note);
				scale = new Scale{*noteObjects[0]};
				this->scaleObjects.push_back(scale);
				break;
			case 8 :
				note = new Note{"F"};
				this->noteObjects.push_back(note);
				scale = new Scale{*noteObjects[0]};
				this->scaleObjects.push_back(scale);
				break;
			case 9 :
				note = new Note{"C"}; // create new note
				this->noteObjects.push_back(note);
				scale = new Scale{*noteObjects[0]};
				this->scaleObjects.push_back(scale); // push to scaleObjects vector
				break;
			case 10:
				note = new Note{"G"};
				this->noteObjects.push_back(note);
				scale = new Scale{*noteObjects[0]};
				this->scaleObjects.push_back(scale);
				break;
			case 11:
				note = new Note{"D"};
				this->noteObjects.push_back(note);
				scale = new Scale{*noteObjects[0]};
				this->scaleObjects.push_back(scale);
				break;
			default:
				note = nullptr;
				scale = nullptr;
				destroyChords();
				break;
		}


	//	//TEST
	//	if (std::size(noteObjects) > 0)
	//	{
	//		ShowMessage("note constructed");
	//	}
	//
	//	if (std::size(scaleObjects) > 0)
	//	{
	//		ShowMessage("scale constructed");
	//	}


		printRootNote(Form1->LabelRoot);
		printRootNoteFrequency(Form1->LabelFrequency);

		Form1->dial2->Enabled = true;
		Form1->Dial1Light->Opacity = 1;
		Form1->Dial2Light->Opacity = 1;
		Form1->setLabelsVisible(Form1->scaleNoteLabels);
		Form1->showDegreeLabels(Form1->scaleNoteLabels);
		Form1->LabelHz->Visible = true;
		Form1->CirclePlayNote->Opacity = 1;
		Form1->CirclePlayNote->Enabled = true;

	}
}

void ChordManager::destroyChords()
{
		for (auto note : noteObjects)
		{
			delete note;
		}


	noteObjects.clear();

		for (auto scale : scaleObjects)
		{
			delete scale;
		}


	scaleObjects.clear();

}


void ChordManager::createScale(int selectedPieIndex)
{
	Form1->setLabelsVisible(Form1->scaleNoteLabels);
	Form1->CirclePlayScale->Opacity = LOW_OPACITY;
	Form1->CirclePlayScale->Enabled = false;
    Form1->ButtonPlayScale->Enabled = false;

	switch (selectedPieIndex)
	{
		case 0 :
			this->scaleObjects[0]->setScale("Harmonic minor");
			break;
		case 1 :
			this->scaleObjects[0]->setScale("Mixolydian");
			break ;
		case 2 :
			this->scaleObjects[0]->setScale("Melodic minor up");
			break;
		case 3 :
			this->scaleObjects[0]->setScale("Melodic minor down");
			break;
		case 4 :
			this->scaleObjects[0]->setScale("Phrygian");
			break;
		case 5 :
			this->scaleObjects[0]->setScale("Lydian");
			break;
		case 6 :
			this->scaleObjects[0]->setScale("Locrian");
			break;
		case 7 :
			this->scaleObjects[0]->setScale("Minor Pentatonic");
			setLabelInvisible(Form1->scaleNoteLabels, 1);
			setLabelInvisible(Form1->scaleNoteLabels, 5);
			break;
		case 8 :
			this->scaleObjects[0]->setScale("Major Pentatonic");
			setLabelInvisible(Form1->scaleNoteLabels, 3);
			setLabelInvisible(Form1->scaleNoteLabels, 6);
			break;
		case 9 :
			this->scaleObjects[0]->setScale("Major");
			break;
		case 10:
			this->scaleObjects[0]->setScale("Minor");
			break;
		case 11:
			this->scaleObjects[0]->setScale("Dorian");
			break;
		default:
			break;
	}

	printScale(Form1->LabelScale);
	printNotesToLabels(Form1->scaleNoteLabels);

	Form1->CirclePlayScale->Opacity = 1;
	Form1->CirclePlayScale->Enabled = true;
	Form1->ButtonPlayScale->Enabled = true;
}

// Function to for allowing continuous scale creation. To be finished...
void ChordManager::createScaleFromPrevious(int selectedPieIndex, int index)
{

	if (selectedPieIndex >= 0 && selectedPieIndex < 12)
	{
		destroyScales();
		Note* note = nullptr;
		Scale* scale = nullptr;
		std::string scaleName = " ";

		switch (index)
		{
			case 0 : scaleName = "Harmonic Minor";
			case 1 : scaleName = "Mixolydian";	break ;
			case 2 : scaleName = "Melodic minor up";	break;
			case 3 : scaleName = "Melodic minor down";	break;
			case 4 : scaleName = "Phrygian"; break;
			case 5 : scaleName = "Lydian"; break;
			case 6 : scaleName = "Locrian"; break;
			case 7 : scaleName = "Minor Pentatonic"; break;
			case 8 : scaleName = "Major Pentatonic"; break;
			case 9 : scaleName = "Major"; break;
			case 10: scaleName = "Minor"; break;
			case 11: scaleName = "Dorian";break;
			default: break;
		}

		switch (selectedPieIndex)
		{
			case 0 :
				note = new Note{"A"};
				this->noteObjects.push_back(note);
				break;
			case 1 :
				note = new Note{"E"};
				this->noteObjects.push_back(note);
				break ;
			case 2 :
				note = new Note{"B"};
				this->noteObjects.push_back(note);
				break;
			case 3 :
				note = new Note{"F#"};
				this->noteObjects.push_back(note);
				break;
			case 4 :
				note = new Note{"Db"};
				this->noteObjects.push_back(note);	
			case 5 :
				note = new Note{"Ab"};
				this->noteObjects.push_back(note);
				break;
			case 6 :
				note = new Note{"Eb"};
				this->noteObjects.push_back(note);
				break;
			case 7 :
				note = new Note{"Bb"};
				this->noteObjects.push_back(note);
				break;
			case 8 :
				note = new Note{"F"};
				this->noteObjects.push_back(note);
				break;
			case 9 :
				note = new Note{"C"}; // create new note
				this->noteObjects.push_back(note);
				break;
			case 10:
				note = new Note{"G"};
				this->noteObjects.push_back(note);
				break;
			case 11:
				note = new Note{"D"};
				this->noteObjects.push_back(note);
				break;
			default:
				destroyScales();
				note = nullptr;
				scale = nullptr;
				break;
		}

		if (note)
		{
			scale = new Scale{*note}; // Initialize with root note
			if (scale)
			{
				scale->setScale(scaleName); // Set scale type
				scaleObjects.push_back(scale);
			}
		}
		else
			ShowMessage("scaleObjectsEmpty");

		printRootNote(Form1->LabelRoot);
		printRootNoteFrequency(Form1->LabelFrequency);

		printNotesToLabels(Form1->scaleNoteLabels);
		
		Form1->CirclePlayScale->Opacity = 1;
		Form1->CirclePlayScale->Enabled = true;
		Form1->ButtonPlayScale->Enabled = true;

	}
}

void ChordManager::changeScaleRoot(int index)
{
	if (index >= 0 && index < 12)
	{
		Note* note = nullptr;
		Scale* scale = nullptr;
		std::string scaleName = " ";


		switch (index)
		{
			case 0 :
				note = new Note{"A"};
				break;
			case 1 :
				note = new Note{"E"};
				break ;
			case 2 :
				note = new Note{"B"};
				break;
			case 3 :
				note = new Note{"F#"};
				break;
			case 4 :
				note = new Note{"Db"};
			case 5 :
				note = new Note{"Ab"};
				break;
			case 6 :
				note = new Note{"Eb"};
				break;
			case 7 :
				note = new Note{"Bb"};
				break;
			case 8 :
				note = new Note{"F"};			   
				break;
			case 9 :
				note = new Note{"C"}; // create new note
				break;
			case 10:
				note = new Note{"G"};
				break;
			case 11:
				note = new Note{"D"};			   
				break;
			default:			   
				note = nullptr;
				scale = nullptr;
				break;
		}

		if (note)
		{
				scaleObjects[0]->setScaleRoot(note);
		}
		else
			ShowMessage("scaleObjectsEmpty");

		printRootNote(Form1->LabelRoot);
		printRootNoteFrequency(Form1->LabelFrequency);

		printNotesToLabels(Form1->scaleNoteLabels);
		
		Form1->CirclePlayScale->Opacity = 1;
		Form1->CirclePlayScale->Enabled = true;
		Form1->ButtonPlayScale->Enabled = true;

	}
}

void ChordManager::destroyScales()
{
		for (auto note : noteObjects)
		{
			delete note;
		}


	noteObjects.clear();

		for (auto scale : scaleObjects)
		{
			delete scale;
		}

	scaleObjects.clear();

}

// Function to print the scale notes to each label box
void ChordManager::printNotesToLabels(std::vector<TLabel*> labelVector)
{
	if (scaleObjects.empty() || scaleObjects[0] == nullptr)
	{
        ShowMessage("scaleObjects is null or empty!");
        return;
    }

	if (scaleObjects[0]->m_notes2.size() < 8)
	{
		Form1->showDegreeLabels(Form1->scaleNoteLabels);
		return;
	}

	for (int i{0}; i < 8; i++)
	{
		if (i < scaleObjects[0]->m_notes2.size() && scaleObjects[0]->m_notes2[i] != nullptr)
		{
            labelVector[i]->Opacity = 1;
			labelVector[i]->TextSettings->Font->Size = 28;
            labelVector[i]->Text = scaleObjects[0]->m_notes2[i]->getName().c_str();
		}
		else
		{
			labelVector[i]->Text = "Invalid";
		}
	}

}

// Display note frequency
void ChordManager::printRootNoteFrequency(TLabel* label)
{
	if (label != nullptr)
	{
		label->Text = noteObjects[0]->getFrequency();
	}
	else
	{
		ShowMessage("note label error");
	}

}

// Display root note
void ChordManager::printRootNote(TLabel* label)
{
	if (label != nullptr)
	{
		label->Text = scaleObjects[0]->getTonic().c_str();
	}
	else
	{
		ShowMessage("scale label error");
	}
}

void ChordManager::printScale(TLabel* label)
{
	if (label != nullptr)
	{
		label->Text = scaleObjects[0]->getName().c_str();
	}
}

void ChordManager::setLabelInvisible(std::vector<TLabel*> labelVector, int index)
{
	labelVector[index]->Visible = false;
}

// Functions for playing sound

// Function to play note sound using note frequency
void ChordManager::playTone(std::vector<Note*> noteObjects)
{
	for (auto note : noteObjects)
	{
		Beep(note->getFrequency(), 500);
	}
}

// Function to play note sounds of scale. Current version uses the simple Beep()
// function to produce the sound

void ChordManager::playScaleTones(std::vector<Scale*> scaleObjects,
	std::vector<TLabel*> labelVector)
{
	if (scaleObjects[0]->getName() == "Major Pentatonic")
	{
		for (int i{0}; i < 8; i++)
		{
			if (i == 3 || i == 6)
				continue;
			else
			{
				Beep(scaleObjects[0]->m_notes2[i]->getFrequency(), 500);
			}

		}
	}

	else if (scaleObjects[0]->getName() == "Minor Pentatonic")
	{
		for (int i{0}; i < 8; i++)
		{
			if (i == 1 || i == 5)
				continue;
			else
			{
				Beep(scaleObjects[0]->m_notes2[i]->getFrequency(), 500);
			}
		}
	}

	else if (scaleObjects[0]->getName() == "Melodic minor down")
	{
		for (int i{7}; i >= 0; i--) // play in reverse order
		{
			Beep(scaleObjects[0]->m_notes2[i]->getFrequency(), 500);
		}
	}

	else
	{
		for (int i{0}; i < 8; i++)
		{
			Beep(scaleObjects[0]->m_notes2[i]->getFrequency(), 500);
		}
	}



}

void __fastcall ChordManager::PlayNoteOnClick(TObject *Sender)
{
	if (Form1->CirclePlayNote->Enabled == true)
	{
		playTone(noteObjects);
	}
}


void __fastcall ChordManager::PlayScaleOnClick(TObject *Sender)
{
	if (Form1->CirclePlayScale->Enabled == true)
	{
		playScaleTones(scaleObjects, Form1->scaleNoteLabels);
	}
}


//---------------------------------------------------------------------------
#pragma package(smart_init)
