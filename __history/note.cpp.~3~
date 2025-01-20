//---------------------------------------------------------------------------

// A Note class to hold note objects

#pragma hdrstop

#include "note.h"

Note::Note() // default constructor
{
	m_noteName = "A";
	m_octaveId = 2;
	m_semitonesFromC = 9;
	m_frequency = MIDDLE_A;
}

Note::Note(const std::string& noteName)
{
	m_noteName = noteName;
	m_octaveId = 2;
	m_semitonesFromC = 0;
	m_frequency = 0.0;
	setSemitonesFromC();
	setFrequency();
}

//Note::Note(const std::string& noteName, int octave, int semitones)
//	: m_noteName{noteName}, m_octaveId{octave}
//	, m_semitonesFromC{semitones}
//{}
	


Note::~Note()
{}

void Note::setName(const std::string& noteName)
{
	m_noteName = noteName;
}

void Note::setFrequency()
{
	// Frequency = f_0 x 2^(N/12) where N is the number of notes away from the start
	// note, F_0
	double n = m_semitonesFromC + (m_octaveId * 12);
	double expoResult{n / 12};
	double frequency{C_ZERO * pow(2, expoResult) * pow(m_octaveId, 2)};
	m_frequency = std::round(frequency / 0.01) * 0.01;
}

void Note::setFrequencyFromRef(const Note& ref, int value)
{
	this->m_frequency = ref.m_frequency * value;
}

void Note::setOctaveId(int octave)
{
	m_octaveId = octave;
	setFrequency();
};

void Note::setSemitonesFromC()
{
	if (m_noteName == "C")
		m_semitonesFromC = 0;
	else if (m_noteName == "C#" || m_noteName == "Db")
		m_semitonesFromC = 1;
	else if (m_noteName == "D")
		m_semitonesFromC = 2;
	else if (m_noteName == "D#" || m_noteName == "Eb")
		m_semitonesFromC = 3;
	else if (m_noteName == "E")
		m_semitonesFromC = 4;
	else if (m_noteName == "F")
		m_semitonesFromC = 5;
	else if (m_noteName == "F#" || m_noteName == "Gb")
		m_semitonesFromC = 6;
	else if (m_noteName == "G")
		m_semitonesFromC = 7;
	else if (m_noteName == "G#" || m_noteName == "Ab")
		m_semitonesFromC = 8;
	else if (m_noteName == "A")
		m_semitonesFromC = 9;
	else if (m_noteName == "A#" || m_noteName == "Bb")
		m_semitonesFromC = 10;
	else if (m_noteName == "B")
		m_semitonesFromC = 11;
	else
		m_semitonesFromC = 0;
}

void Note::setFlat()
{
	isFlat = true;
}

void Note::setSharp()
{
	isSharp = true;
}

void Note::increaseOctave(int value)
{
	//m_frequency *= value;
	m_octaveId += value;
    //setFrequency();
}

void Note::decreaseOctave(int value)
{
	m_octaveId -= value;
    //setFrequency();
}

void Note::increaseFrequency(int value)
{
	m_frequency *= value;
}

std::string Note::getName() const
{
	return m_noteName;
}

double Note::getFrequency() const
{
	return m_frequency;
}

int Note::getOctaveId() const
{
	return m_octaveId;
}
//---------------------------------------------------------------------------
#pragma package(smart_init)
