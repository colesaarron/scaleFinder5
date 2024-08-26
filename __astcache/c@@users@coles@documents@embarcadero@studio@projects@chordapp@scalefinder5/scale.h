//---------------------------------------------------------------------------

#ifndef scaleH
#define scaleH
//---------------------------------------------------------------------------

#pragma hdrstop

#include "note.h"
#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <array>



inline const std::string notes[]
{
	"C", "C#", "D", "Eb", "E", "F", "F#", "G", "Ab", "A", "Bb", "B",
    "C", "C#", "D", "Eb", "E", "F", "F#", "G", "Ab", "A", "Bb", "B", "C"
};

inline const std::string *first{notes};
inline const std::string *last{notes + std::size(notes)};

// Not currently in use. Potential replacement for notes[]
//inline const Note notesArray[]
//{
//	Note{"C", 1, 0}, Note{"C#", 1, 1}, Note{"D", 1, 2}, Note{"Eb", 1, 3},
//	Note{"E", 1, 4}, Note{"F", 1, 5}, Note{"F#", 1, 6}, Note{"G", 1, 7},
//	Note{"Ab", 1, 8}, Note{"A", 1, 9}, Note{"Bb", 1, 10}, Note{"B", 1, 11},
//	Note{"C", 2, 0}, Note{"C#", 2, 1}, Note{"D", 2, 2}, Note{"Eb", 2, 3},
//	Note{"E", 2, 4}, Note{"F", 2, 5}, Note{"F#", 2, 6}, Note{"G", 2, 7},
//	Note{"Ab", 2, 8}, Note{"A", 2, 9}, Note{"Bb", 2, 10}, Note{"B", 2, 11},
//	Note{"C", 3, 0}
//};

// Chord class for use in next version
//class Chord
//{
//private:
//	std::string m_chordName;
//	std::vector<Note*> m_chordNotes;
//	std::vector m_triad;
//
//public:
//	Chord();
//};

class Scale
{
private:
	Note m_root;
    std::string m_tonic;
	std::string m_name;
public:
	std::vector<Note*> m_notes2{};

	// Used for tests
    std::string first_note;
	std::vector<std::string> m_notes{};
    std::string m_noteString;
	std::string m_noteString2;


private:
	bool isMajor;
	int startIndex;

public:
	Scale(const Note& root);

	Scale(const Note& root, std::string& name);

	~Scale();

    void checkNoteFrequency();

	void stepArray(int arr[7]);
	void setStartIndex();
	void setNoteString();
	void setNotes();
	void setScale(std::string scale);

	std::string getTonic() const;
	std::string getName() const;

	//Testing functions
	int getNoteVectorSize();
	std::string getNoteString();

    void setScaleRoot(Note* note);

};


//---------------------------------------------------------------------------
#pragma package(smart_init)

//---------------------------------------------------------------------------
#endif
