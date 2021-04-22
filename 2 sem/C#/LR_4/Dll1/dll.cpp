#include "pch.h"
#include "dll.h"
#include <iostream>
#include <windows.h>
#include <time.h>
#include <string>

dllka dllC;

void __stdcall dllact()
{
    dllC.dllAction();
}

void  dllka::dllAction()
{
    srand(time(0));
    ReceivingData();
    switch (rand() % 9)
    {
    case (0):
    {
        Beethoven();
        break;
    }
    case (1):
    {
        Grasshoper();
        break;
    }
    case (2):
    {
        HappyBirthday();
        break;
    }
    case (3):
    {
        MissionImpossible();
        break;
    }
    case (4):
    {
        StarWars();
        break;
    }
    case (5):
    {
        SuperMario();
        break;
    }
    case (6):
    {
        Tannenbaum();
        break;
    }
    case (7):
    {
        coupleSolo();
        break;
    }
    case (8):
    {
        refrenSolo();
        break;
    }
    }
}

void  dllka::ReceivingData()
{
    srand(time(0));
    int a = 60 + (rand() % 50 + 1) * ((rand() % 2 == 0) ? (1) : (-1));
    for (unsigned short i = 0; i <= a; i++)
    {
        system("cls");
        std::cout << "RECEIVING DATA " << (i * 100) / a << "%";
        Sleep(10);
    }
    Sleep(rand() % 4000);
    std::cout << "\nPROCESSING DATA";
    Sleep(rand() % 4000);
    std::cout << "\nSTARTING";
    Sleep(rand() % 4000);
    system("cls");


}

void  dllka::HappyBirthday()
{
    Sleep(2000);
    Beep(264, 125);
    Sleep(250);
    Beep(264, 125);
    Sleep(125);
    Beep(297, 500);
    Sleep(125);
    Beep(264, 500);
    Sleep(125);
    Beep(352, 500);
    Sleep(125);
    Beep(330, 1000);
    Sleep(250);
    Beep(264, 125);
    Sleep(250);
    Beep(264, 125);
    Sleep(125);
    Beep(297, 500);
    Sleep(125);
    Beep(264, 500);
    Sleep(125);
    Beep(396, 500);
    Sleep(125);
    Beep(352, 1000);
    Sleep(250);
    Beep(264, 125);
    Sleep(250);
    Beep(264, 125);
    Sleep(125);
    Beep(2642, 500);
    Sleep(125);
    Beep(440, 500);
    Sleep(125);
    Beep(352, 250);
    Sleep(125);
    Beep(352, 125);
    Sleep(125);
    Beep(330, 500);
    Sleep(125);
    Beep(297, 1000);
    Sleep(250);
    Beep(466, 125);
    Sleep(250);
    Beep(466, 125);
    Sleep(125);
    Beep(440, 500);
    Sleep(125);
    Beep(352, 500);
    Sleep(125);
    Beep(396, 500);
    Sleep(125);
    Beep(352, 1000);
}

void  dllka::Beethoven()
{
    Beep(659, 120);
    Sleep(130);
    Beep(622, 120);
    Sleep(130);

    Beep(659, 120);
    Sleep(130);
    Beep(622, 120);
    Sleep(130);
    Beep(659, 120);
    Sleep(130);
    Beep(494, 120);
    Sleep(130);
    Beep(587, 120);
    Sleep(130);
    Beep(523, 120);
    Sleep(130);

    Beep(440, 120);
    Sleep(150);
    Beep(262, 120);
    Sleep(130);
    Beep(330, 120);
    Sleep(130);
    Beep(440, 120);
    Sleep(130);

    Beep(494, 120);
    Sleep(150);
    Beep(330, 120);
    Sleep(130);
    Beep(415, 120);
    Sleep(130);
    Beep(494, 120);
    Sleep(130);

    Beep(523, 120);
    Sleep(150);
    Beep(330, 120);
    Sleep(130);
    Beep(659, 120);
    Sleep(130);
    Beep(622, 120);
    Sleep(130);

    Beep(659, 120);
    Sleep(130);
    Beep(622, 120);
    Sleep(130);
    Beep(659, 120);
    Sleep(130);
    Beep(494, 120);
    Sleep(130);
    Beep(587, 120);
    Sleep(130);
    Beep(523, 120);
    Sleep(130);

    Beep(440, 120);
    Sleep(150);
    Beep(262, 120);
    Sleep(130);
    Beep(330, 120);
    Sleep(130);
    Beep(440, 120);
    Sleep(130);

    Beep(494, 120);
    Sleep(150);
    Beep(330, 120);
    Sleep(130);
    Beep(523, 120);
    Sleep(130);
    Beep(494, 120);
    Sleep(150);
    Beep(440, 120);
}

void  dllka::SuperMario()
{
    Beep(659, 125);
    Beep(659, 125);
    Sleep(125);
    Beep(659, 125);
    Sleep(167);
    Beep(523, 125);
    Beep(659, 125);
    Sleep(125);
    Beep(784, 125);
    Sleep(375);
    Beep(392, 125);
    Sleep(375);
    Beep(523, 125);
    Sleep(250);
    Beep(392, 125);
    Sleep(250);
    Beep(330, 125);
    Sleep(250);
    Beep(440, 125);
    Sleep(125);
    Beep(494, 125);
    Sleep(125);
    Beep(466, 125);
    Sleep(42);
    Beep(440, 125);
    Sleep(125);
    Beep(392, 125);
    Sleep(125);
    Beep(659, 125);
    Sleep(125);
    Beep(784, 125);
    Sleep(125);
    Beep(880, 125);
    Sleep(125);
    Beep(698, 125);
    Beep(784, 125);
    Sleep(125);
    Beep(659, 125);
    Sleep(125);
    Beep(523, 125);
    Sleep(125);
    Beep(587, 125);
    Beep(494, 125);
    Sleep(125);
    Beep(523, 125);
    Sleep(250);
    Beep(392, 125);
    Sleep(250);
    Beep(330, 125);
    Sleep(250);
    Beep(440, 125);
    Sleep(125);
    Beep(494, 125);
    Sleep(125);
    Beep(466, 125);
    Sleep(42);
    Beep(440, 125);
    Sleep(125);
    Beep(392, 125);
    Sleep(125);
    Beep(659, 125);
    Sleep(125);
    Beep(784, 125);
    Sleep(125);
    Beep(880, 125);
    Sleep(125);
    Beep(698, 125);
    Beep(784, 125);
    Sleep(125);
    Beep(659, 125);
    Sleep(125);
    Beep(523, 125);
    Sleep(125);
    Beep(587, 125);
    Beep(494, 125);
    Sleep(375);
    Beep(784, 125);
    Beep(740, 125);
    Beep(698, 125);
    Sleep(42);
    Beep(622, 125);
    Sleep(125);
    Beep(659, 125);
    Sleep(167);
    Beep(415, 125);
    Beep(440, 125);
    Beep(523, 125);
    Sleep(125);
    Beep(440, 125);
    Beep(523, 125);
    Beep(587, 125);
    Sleep(250);
    Beep(784, 125);
    Beep(740, 125);
    Beep(698, 125);
    Sleep(42);
    Beep(622, 125);
    Sleep(125);
    Beep(659, 125);
    Sleep(167);
    Beep(698, 125);
    Sleep(125);
    Beep(698, 125);
    Beep(698, 125);
    Sleep(625);
    Beep(784, 125);
    Beep(740, 125);
    Beep(698, 125);
    Sleep(42);
    Beep(622, 125);
    Sleep(125);
    Beep(659, 125);
    Sleep(167);
    Beep(415, 125);
    Beep(440, 125);
    Beep(523, 125);
    Sleep(125);
    Beep(440, 125);
    Beep(523, 125);
    Beep(587, 125);
    Sleep(250);
    Beep(622, 125);
    Sleep(250);
    Beep(587, 125);
    Sleep(250);
    Beep(523, 125);
    Sleep(1125);
    Beep(784, 125);
    Beep(740, 125);
    Beep(698, 125);
    Sleep(42);
    Beep(622, 125);
    Sleep(125);
    Beep(659, 125);
    Sleep(167);
    Beep(415, 125);
    Beep(440, 125);
    Beep(523, 125);
    Sleep(125);
    Beep(440, 125);
    Beep(523, 125);
    Beep(587, 125);
    Sleep(250);
    Beep(784, 125);
    Beep(740, 125);
    Beep(698, 125);
    Sleep(42);
    Beep(622, 125);
    Sleep(125);
    Beep(659, 125);
    Sleep(167);
    Beep(698, 125);
    Sleep(125);
    Beep(698, 125);
    Beep(698, 125);
    Sleep(625);
    Beep(784, 125);
    Beep(740, 125);
    Beep(698, 125);
    Sleep(42);
    Beep(622, 125);
    Sleep(125);
    Beep(659, 125);
    Sleep(167);
    Beep(415, 125);
    Beep(440, 125);
    Beep(523, 125);
    Sleep(125);
    Beep(440, 125);
    Beep(523, 125);
    Beep(587, 125);
    Sleep(250);
    Beep(622, 125);
    Sleep(250);
    Beep(587, 125);
    Sleep(250);
    Beep(523, 125);
    Sleep(625);
}

void  dllka::StarWars()
{
    Beep(300, 500);
    Sleep(50);
    Beep(300, 500);
    Sleep(50);
    Beep(300, 500);
    Sleep(50);
    Beep(250, 500);
    Sleep(50);
    Beep(350, 250);
    Beep(300, 500);
    Sleep(50);
    Beep(250, 500);
    Sleep(50);
    Beep(350, 250);
    Beep(300, 500);
    Sleep(50);
}

void  dllka::MissionImpossible()
{
    Beep(784, 150);
    Sleep(300);
    Beep(784, 150);
    Sleep(300);
    Beep(932, 150);
    Sleep(150);
    Beep(1047, 150);
    Sleep(150);
    Beep(784, 150);
    Sleep(300);
    Beep(784, 150);
    Sleep(300);
    Beep(699, 150);
    Sleep(150);
    Beep(740, 150);
    Sleep(150);
    Beep(784, 150);
    Sleep(300);
    Beep(784, 150);
    Sleep(300);
    Beep(932, 150);
    Sleep(150);
    Beep(1047, 150);
    Sleep(150);
    Beep(784, 150);
    Sleep(300);
    Beep(784, 150);
    Sleep(300);
    Beep(699, 150);
    Sleep(150);
    Beep(740, 150);
    Sleep(150);
    Beep(932, 150);
    Beep(784, 150);
    Beep(587, 1200);
    Sleep(75);
    Beep(932, 150);
    Beep(784, 150);
    Beep(554, 1200);
    Sleep(75);
    Beep(932, 150);
    Beep(784, 150);
    Beep(523, 1200);
    Sleep(150);
    Beep(466, 150);
    Beep(523, 150);
}

void  dllka::Tannenbaum()
{
    Beep(247, 500);
    Beep(417, 500);
    Beep(417, 500);
    Beep(370, 500);
    Beep(417, 500);
    Beep(329, 500);
    Beep(247, 500);
    Beep(247, 500);
    Beep(247, 500);
    Beep(417, 500);
    Beep(417, 500);
    Beep(370, 500);
    Beep(417, 500);
    Beep(497, 500);
    Sleep(500);
    Beep(497, 500);
    Beep(277, 500);
    Beep(277, 500);
    Beep(440, 500);
    Beep(440, 500);
    Beep(417, 500);
    Beep(370, 500);
    Beep(329, 500);
    Beep(247, 500);
    Beep(417, 500);
    Beep(417, 500);
    Beep(370, 500);
    Beep(417, 500);
    Beep(329, 500);
}

void  dllka::Grasshoper()
{
    Beep(440, 300);
    Beep(330, 300);
    Beep(440, 300);
    Beep(330, 300);
    Beep(440, 300);
    Beep(415, 300);
    Beep(415, 300);
    Sleep(600);
    Beep(415, 300);
    Beep(330, 300);
    Beep(415, 300);
    Beep(330, 300);
    Beep(415, 300);
    Beep(440, 300);
    Beep(440, 300);
    Sleep(600);
    Beep(440, 300);
    Beep(494, 300);
    Beep(494, 100);
    Beep(494, 100);
    Beep(494, 300);
    Beep(494, 300);
    Beep(523, 300);
    Beep(523, 100);
    Beep(523, 100);
    Beep(523, 300);
    Beep(523, 300);
    Beep(523, 300);
    Beep(494, 300);
    Beep(440, 300);
    Beep(415, 300);
    Beep(440, 800);
}

void  dllka::refrenSolo()
{
    Beep(659, 300);
    Beep(659, 300);
    Beep(659, 300);
    Sleep(300);
    Beep(659, 300);
    Beep(659, 300);
    Beep(659, 300);
    Sleep(300);
    Beep(659, 300);
    Beep(783, 300);
    Beep(523, 300);
    Beep(587, 300);
    Beep(659, 300);
    Beep(261, 300);
    Beep(293, 300);
    Beep(329, 300);
    Beep(698, 300);
    Beep(698, 300);
    Beep(698, 300);
    Sleep(300);
    Beep(698, 300);
    Beep(659, 300);
    Beep(659, 300);
    Sleep(300);
    Beep(659, 300);
    Beep(587, 300);
    Beep(587, 300);
    Beep(659, 300);
    Beep(587, 300);
    Sleep(300);
    Beep(783, 300);
    Sleep(300);
    Beep(659, 300);
    Beep(659, 300);
    Beep(659, 300);
    Sleep(300);
    Beep(659, 300);
    Beep(659, 300);
    Beep(659, 300);
    Sleep(300);
    Beep(659, 300);
    Beep(783, 300);
    Beep(523, 300);
    Beep(587, 300);
    Beep(659, 300);
    Beep(261, 300);
    Beep(293, 300);
    Beep(329, 300);
    Beep(698, 300);
    Beep(698, 300);
    Beep(698, 300);
    Sleep(300);
    Beep(698, 300);
    Beep(659, 300);
    Beep(659, 300);
    Sleep(300);
    Beep(783, 300);
    Beep(783, 300);
    Beep(698, 300);
    Beep(587, 300);
    Beep(523, 600);
    Sleep(600);
}

void  dllka::coupleSolo()
{
    Beep(392, 300);
    Beep(659, 300);
    Beep(587, 300);
    Beep(523, 300);
    Beep(392, 600);
    Sleep(300 * 2);
    Beep(392, 300);
    Beep(659, 300);
    Beep(587, 300);
    Beep(523, 300);
    Beep(440, 600);
    Sleep(600);
    Beep(440, 300);
    Beep(698, 300);
    Beep(659, 300);
    Beep(587, 300);
    Beep(783, 600);
    Sleep(600);
    Beep(880, 300);
    Beep(880, 300);
    Beep(783, 300);
    Beep(622, 300);
    Beep(659, 600);
    Sleep(600);
    Beep(392, 300);
    Beep(659, 300);
    Beep(587, 300);
    Beep(523, 300);
    Beep(392, 600);
    Sleep(600);
    Beep(392, 300);
    Beep(659, 300);
    Beep(587, 300);
    Beep(523, 300);
    Beep(440, 600);
    Sleep(600);
    Beep(440, 300);
    Beep(698, 300);
    Beep(659, 300);
    Beep(587, 300);
    Beep(783, 600);
    Sleep(600);
    Beep(880, 300);
    Beep(783, 300);
    Beep(698, 300);
    Beep(587, 300);
    Beep(523, 600);
    Sleep(600);
}