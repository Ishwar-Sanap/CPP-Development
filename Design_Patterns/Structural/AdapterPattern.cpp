#include <bits/stdc++.h>
using namespace std;

/*
It allows objects with incompatible interfaces to collaborate.
Think of it like a universal travel adapter for your electronic devices.
The adapter acts as a bridge, translating the interface of one class into an interface that another class expects.



Problem: AudioPlayer only supports .mp3; new formats require different interfaces.
Constraint: Can’t modify AdvancedMediaPlayer.
Solution: Create MediaAdapter that bridges AudioPlayer and AdvancedMediaPlayer.
Result: Now AudioPlayer can play .mp3, .mp4, and .vlc seamlessly, without rewriting old code.

*/

//Target Interface
class MediaPlayer
{
public:
    virtual void play(string fName) = 0;
    virtual ~MediaPlayer() = default;
};

//Adaptee (Incompatible class)
class AdvancedPlayer
{
public:
    void playMp4(string file)
    {
        cout << "Playing " << file << " from advanced player" << endl;
    }
    void playVlc(string file)
    {
        cout << "Playing " << file << " from advanced player" << endl;
    }
};

//Adapter : which acts as bridge between Target & Adaptee.
class MediaAdapter : MediaPlayer
{
    AdvancedPlayer *m_ptrObj; // composition (holds the object of another class)
    string m_format;

public:
    MediaAdapter(string f)
    {
        m_format = f;
        m_ptrObj = new AdvancedPlayer();
    }

    void play(string fName) override
    {
        if (m_format == "mp4")
            m_ptrObj->playMp4(fName);
        else if (m_format == "vlc")
            m_ptrObj->playVlc(fName);
        else
            cout << fName << " is not supported by Adapter" << endl;
    }

    ~MediaAdapter()
    {
        delete m_ptrObj;
        m_ptrObj = nullptr;
    }
};

//client using Adapter
class AudioPlayer : public MediaPlayer
{
    MediaAdapter *m_ptrObj;

public:
    void play(string fName) override
    {
        if (fName.find(".mp3") != string::npos)
        {
            cout << "Playing " << fName << endl;
        }
        else if (fName.find(".mp4") != string::npos)
        {
            m_ptrObj = new MediaAdapter("mp4");
            m_ptrObj->play(fName);
            delete m_ptrObj;
            m_ptrObj = nullptr;
        }
        else if (fName.find(".vlc") != string::npos)
        {
            m_ptrObj = new MediaAdapter("vlc");
            m_ptrObj->play(fName);
            delete m_ptrObj;
            m_ptrObj = nullptr;
        }
        else
        {
            cout << "Not supprted format :(" << endl;
        }
    }

    ~AudioPlayer()
    {
        delete m_ptrObj;
        m_ptrObj = nullptr;
    }
};

int main()
{
    MediaPlayer *player = new AudioPlayer();
    player->play("abc.mp3");
    player->play("sffe3abc.mp4");
    player->play("abc.vlc");
    player->play("etererg.mp2");

    return 0;
}