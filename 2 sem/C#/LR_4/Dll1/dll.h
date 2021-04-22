#pragma once
#if defined(dllka_EXPORT) // внутри DLL
#   define dllka_API   __declspec(dllexport)
#else // вне DLL
#   define dllka_API   __declspec(dllimport)
#endif  // XYZLIBRARY_EXPORT

#include <cstdint>


//extern "C" __declspec(dllexport) 
struct dllka
{
public:
    void  dllAction();

private:
    void  ReceivingData();

    void  HappyBirthday();

    void  Beethoven();

    void  SuperMario();

    void  StarWars();

    void  MissionImpossible();

    void  Tannenbaum();

    void  Grasshoper();

    void  refrenSolo();

    void  coupleSolo();
};



extern "C" void  __declspec(dllexport) __stdcall dllact();