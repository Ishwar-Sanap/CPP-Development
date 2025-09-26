#include <bits/stdc++.h>
using namespace std;

/*
Proxy = a stand-in object that controls access to another object.
Instead of using the real object directly, the client interacts with a proxy that:
*/

class Image
{
public:
    virtual void showDetails() = 0;
    virtual ~Image() = default;
};

class RealImage : public Image
{
    string m_strName;

public:
    RealImage(string name) : m_strName(name)
    {
        loadImageFromDisk();
    }

    void showDetails() override
    {
        cout << "Showing deatils of " << m_strName << endl;
    }

    void loadImageFromDisk()
    {
        cout << "Loading Image from disk..." << endl;
    }

    ~RealImage()
    {
        cout << "Unloading Image " << endl;
    }
};

class ImageProxy : public Image
{
    string m_strName;
    Image *ptrImg;

public:
    ImageProxy(string name) : m_strName(name), ptrImg(nullptr) {}
    void showDetails()
    {
        if (ptrImg == nullptr)
        {
            ptrImg = new RealImage(m_strName);
        }

        ptrImg->showDetails();
    }

    ~ImageProxy(){
        delete ptrImg;
        ptrImg = nullptr;
    }
};
int main()
{
    ImageProxy img1("sounds.png");
    img1.showDetails();
    img1.showDetails();
    img1.showDetails();

    return 0;
}