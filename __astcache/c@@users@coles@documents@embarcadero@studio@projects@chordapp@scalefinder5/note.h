//---------------------------------------------------------------------------

#ifndef noteH
#define noteH

#include <iostream>
#include <string>
#include <string_view>
#include <math.h>

constexpr double MIDDLE_A{440.00};
constexpr double C_ZERO{16.35};

class Note
{
private:
	std::string m_noteName;
	double m_frequency;
	int m_octaveId;
    int m_semitonesFromC;
	bool isFlat{m_noteName.find('#') != std::string::npos};
	bool isSharp{m_noteName.find('b') != std::string::npos};

public:
	Note();

	//For use with new notes initial array (currently unused)
    //Note(const std::string& noteName, int octave, int semitones);

	Note(const std::string& noteName);

    ~Note();

	void setName(const std::string& noteName);
	void setFrequency();
    void setFrequencyFromRef(const Note& root, int value);
	void setOctaveId(int id);
    void setSemitonesFromC();
	void setFlat();
	void setSharp();
	void increaseOctave(int value);
	void decreaseOctave(int value);
    void increaseFrequency(int value);

	std::string getName() const;
	double getFrequency() const;
	int getOctaveId() const;

    Note* notePtr;
};
//---------------------------------------------------------------------------
#endif
