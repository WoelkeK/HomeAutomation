#pragma once
#include <Arduino.h>
// Kolejność enum MUSI odpowiadać istniejącej numeracji MySensors 0..19.
// Dzięki temu OpenHAB/Domoticz dalej widzi te same kanały, a kod może używać nazw.

enum class LightId : byte
{
  Archiwum = 0,                // sensor 0,  Mega pin 37
  Biuro = 1,                   // sensor 1,  Mega pin 43
  Sportowy = 2,                // sensor 2,  Mega pin 8
  Rozdzielnia = 3,             // sensor 3,  Mega pin A14
  Lazienka = 4,                // sensor 4,  Mega pin 45
  Garaz = 5,                   // sensor 5,  Mega pin 34
  KuchniaOczka = 6,            // sensor 6,  Mega pin 35
  KuchniaSufit = 7,            // sensor 7,  Mega pin 46
  Oswietlenie_Zew_Trojkat = 8, // sensor 8,  Mega pin 49
  RezerwaPin7 = 9,             // sensor 9,  Mega pin 7 - brak opisu w starej tabeli
  SalonStol = 10,              // sensor 10, Mega pin A12
  Wykusz = 11,                 // sensor 11, Mega pin 36
  HolSpoty = 12,               // sensor 12, Mega pin 47
  SalonSufitRGB = 13,          // sensor 13, Mega pin 41
  SalonOknoTvPlyta = 14,       // sensor 14, Mega pin 40
  SalonOczka = 15,             // sensor 15, Mega pin 39
  KorytarzSchodyRGB = 16,      // sensor 16, Mega pin 42
  KorytarzHolSpot2x = 17,      // sensor 17, Mega pin A13
  KorytarzOczkaSufit = 18,     // sensor 18, Mega pin 44
  Kotlownia = 19               // sensor 19, Mega pin 38

};

inline const char *lightName(LightId id)
{
  switch (id)
  {
  case LightId::Archiwum:
    return "Archiwum";

  case LightId::Biuro:
    return "Biuro";

  case LightId::Sportowy:
    return "Sportowy";

  case LightId::Rozdzielnia:
    return "Rozdzielnia";

  case LightId::Lazienka:
    return "Lazienka";

  case LightId::Garaz:
    return "Garaz";

  case LightId::KuchniaOczka:
    return "Kuchnia Oczka";

  case LightId::KuchniaSufit:
    return "Kuchnia Sufit";

  case LightId::Oswietlenie_Zew_Trojkat:
    return "Oswietlenie Zewnetrzne 1";

  case LightId::RezerwaPin7:
    return "Rezerwa Pin 7";

  case LightId::SalonStol:
    return "Salon Stol";

  case LightId::Wykusz:
    return "Wykusz";

  case LightId::HolSpoty:
    return "Hol Spoty";

  case LightId::SalonSufitRGB:
    return "Salon Sufit RGB";

  case LightId::SalonOknoTvPlyta:
    return "Salon Okno TV Plyta";

  case LightId::SalonOczka:
    return "Salon Oczka";

  case LightId::KorytarzSchodyRGB:
    return "Korytarz Schody RGB";

  case LightId::KorytarzHolSpot2x:
    return "Korytarz Hol Spot 2x";

  case LightId::KorytarzOczkaSufit:
    return "Korytarz Oczka Sufit";

  case LightId::Kotlownia:
    return "Kotlownia";

  default:
    return "Unknown";
  }
}
