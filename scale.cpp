//---------------------------------------------------------------------------

#pragma hdrstop

#include "scale.h"

Scale::Scale(const Note& root)
{
	m_root = root;
	m_tonic = root.getName();
	m_name = "Major";
	setStartIndex();
}

Scale::Scale(const Note& root, std::string& name)
{
	m_root = root;
	m_tonic = root.getName();
	m_name = name;
	setStartIndex();
	setScale(name);
}

Scale::~Scale()
{
    for (auto notePtr : m_notes2) {
		if (notePtr)
		{
			notePtr = nullptr;
            delete notePtr;
        }
    }
    m_notes2.clear();
};

void Scale::checkNoteFrequency()
{
	// Make sure scale note frequencies are in ascending order

	for (int i{1}; i < 8; ++i)
	{

		if (m_notes2[i]->getFrequency() < m_notes2[i - 1]->getFrequency())
			{
				m_notes2[i]->increaseOctave(1);
				m_notes2[i]->increaseFrequency(2);
			}
	}

    m_notes2[7]->setFrequencyFromRef(m_notes[0], 2);
}


void Scale::stepArray(int arr[7])
{
	const std::string* arrayPtr{first + startIndex}; // pointer to notes array
	// sets pointer to element based on startIndex

	m_notes.push_back(*arrayPtr); // set first note of m_notes

	std::string currentNote{*arrayPtr};
	m_notes2.push_back(new Note{currentNote});
	m_noteString.append(currentNote);

	for (int i{0}; i < 7; i++)
	{
		arrayPtr += arr[i];
		m_notes.push_back(*arrayPtr);
		m_notes2.push_back(new Note{*arrayPtr});
        m_noteString.append(*arrayPtr);
	}


	checkNoteFrequency();
}

void Scale::setStartIndex()
{
	if (m_tonic == "C")
		startIndex = 0;
	else if (m_tonic == "Db" || m_tonic == "C#")
		startIndex = 1;
	else if (m_tonic == "D")
		startIndex = 2;
	else if (m_tonic == "Eb" || m_tonic == "D#")
		startIndex = 3;
	else if (m_tonic == "E")
		startIndex = 4;
	else if (m_tonic == "F")
		startIndex = 5;
	else if (m_tonic == "F#" || m_tonic == "Gb")
		startIndex = 6;
	else if (m_tonic == "G")
		startIndex = 7;
	else if (m_tonic == "Ab" || m_tonic == "G#")
		startIndex = 8;
	else if (m_tonic == "A")
		startIndex = 9;
	else if (m_tonic == "Bb" || m_tonic == "A#")
		startIndex = 10;
	else if (m_tonic == "B")
		startIndex = 11;
	else
		startIndex = 0;
}


void Scale::setNoteString()
{
	for (auto note : m_notes2)
	{
		 m_noteString.append(note->getName());
	}
}


void Scale::setNotes()
{
	int majorStep[7] {2, 2, 1, 2, 2, 2, 1}; // int array of major scale steps
	int natMinorStep[7] {2, 1, 2, 2, 1, 2, 2}; // int array of minor scale steps
	int harMinorStep[7] {2, 1, 2, 2, 1, 3, 1}; // int array of harmonic minor scale steps
	int melMinorStepUp[7] {2, 1, 2, 2, 2, 2, 1}; // int array of melodic minor scale up steps
	int melMinorStepDwn[7] {2, 2, 1, 2, 2, 1, 2}; // int array of melodic minor scale down steps
	int dorianStep[7] {2, 1, 2, 2, 2, 1, 2}; // int array of dorian scale steps
	int phrygianStep[7] {1, 2, 2, 2, 1, 2, 2};
	int lydianStep[7] {2, 2, 2, 1, 2, 2, 1};
	int locrianStep[7] {1, 2, 2, 1, 2, 2, 2};
	int mixolydStep[7] {2, 2, 1, 2, 2, 1, 2}; // int array of mixolydian scale steps


	if (m_name == "Major" || m_name == "major" || m_name == "M")
		stepArray(majorStep);
	else if (m_name == "Major Pentatonic" || m_name == "PM" || m_name == "MP")
		stepArray(majorStep);
	else if (m_name == "Minor" || m_name == "minor" || m_name == "m")
		stepArray(natMinorStep);
    else if (m_name == "Minor Pentatonic" || m_name == "mP" || m_name == "Pm")
		stepArray(natMinorStep);
	else if (m_name == "Harmonic minor" || m_name == "hm" || m_name == "Hm")
		stepArray(harMinorStep);
	else if (m_name == "Dorian" || m_name == "dorian")
		stepArray(natMinorStep);
	else if (m_name == "Mixolydian" || m_name == "Mixo" || m_name == "Mx")
		stepArray(mixolydStep);
	else if (m_name == "Melodic minor up" || m_name == "MmU" || m_name == "melU")
		stepArray(melMinorStepUp);
	else if (m_name == "Melodic minor down" || m_name == "MmD" || m_name == "melD")
		stepArray(melMinorStepDwn);
	else if (m_name == "Phrygian" || m_name == "Ph" || m_name == "ph")
		stepArray(phrygianStep);
	else if (m_name == "Lydian" || m_name == "Ly" || m_name == "ly")
		stepArray(lydianStep);
	else if (m_name == "Locrian" || m_name == "Lo" || m_name == "lo")
		stepArray(locrianStep);
}


void Scale::setScale(std::string scale)
{
    m_noteString.clear();
	m_notes.clear();

	for (auto notePtr : m_notes2)
	{
		delete notePtr; // delete note pointers
	}
    m_notes2.clear(); // clear the noteObjects vector
    m_name = scale;
	setNotes();
}

std::string Scale::getTonic() const {return m_tonic;}
std::string Scale::getName() const {return m_name;}

//Testing functions
int Scale::getNoteVectorSize()
{
	return m_notes2.size();
}

std::string Scale::getNoteString()
{
    return m_noteString;
}

void Scale::setScaleRoot(Note* note)
{
	m_tonic = note->getName();
	setStartIndex();
	setScale(this->m_name);
}


//---------------------------------------------------------------------------
#pragma package(smart_init)
