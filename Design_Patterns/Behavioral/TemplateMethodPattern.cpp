#include <bits/stdc++.h>
using namespace std;

/*
Define the skeleton of an algorithm in a base class.
Allow subclasses to redefine some steps of the algorithm without changing its structure.
*/

class MusicPlayer
{
public:
    //Template method fixed skeleton
    void playSong()
    {
        openFile();

        play(); // virtul method allow subclasse to define it..
    }

    void openFile()
    {
        cout << "Opening the file explore\n";
    }

    virtual void play() = 0;
};

class Mp4Player : public MusicPlayer
{
public:
    void play() override
    {
        cout << "Playing MP4 Song\n";
    }
};

class Mp3Player : public MusicPlayer
{
public:
    void play() override
    {
        cout << "Playing MP3 Song\n";
    }
};

int main()
{
    MusicPlayer *ptrMp3 = new Mp3Player();
    ptrMp3->playSong();

    MusicPlayer *ptrMp4 = new Mp4Player();
    ptrMp4->playSong();

    delete ptrMp3;
    delete ptrMp4;

    ptrMp3 = nullptr;
    ptrMp4 = nullptr;

    return 0;
}