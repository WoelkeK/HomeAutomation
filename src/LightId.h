#pragma once

// Etap 9: logiczne identyfikatory obwodów światła według rzeczywistych lokalizacji.
// Kolejność enum MUSI odpowiadać istniejącej numeracji MySensors 0..19.
// Dzięki temu OpenHAB/Domoticz dalej widzi te same kanały, a kod może używać nazw.

enum class LightId : byte
{
  Garderoba = 0,              // sensor 0,  Mega pin 37
  Sportowy = 1,               // sensor 1,  Mega pin 43
  Gabinet = 2,                // sensor 2,  Mega pin 8
  Rozdzielnia = 3,            // sensor 3,  Mega pin A14
  Lazienka = 4,               // sensor 4,  Mega pin 45
  Garaz = 5,                  // sensor 5,  Mega pin 34
  KuchniaOczka = 6,           // sensor 6,  Mega pin 35
  KuchniaSufit = 7,           // sensor 7,  Mega pin 46
  OswietlenieZewnetrzne1 = 8, // sensor 8,  Mega pin 49
  RezerwaPin7 = 9,            // sensor 9,  Mega pin 7 - brak opisu w starej tabeli
  SalonStol = 10,             // sensor 10, Mega pin A12
  SalonScianaZegar = 11,      // sensor 11, Mega pin 36
  HolSpoty = 12,              // sensor 12, Mega pin 47
  SalonSufitRGB = 13,         // sensor 13, Mega pin 41
  SalonOknoTvPlyta = 14,      // sensor 14, Mega pin 40
  SalonOczka = 15,            // sensor 15, Mega pin 39
  KorytarzSchodyRGB = 16,     // sensor 16, Mega pin 42
  KorytarzHolSpot2x = 17,     // sensor 17, Mega pin A13
  KorytarzOczkaSufit = 18,    // sensor 18, Mega pin 44
  Kotlownia = 19              // sensor 19, Mega pin 38
};

inline byte lightIndex(LightId id)
{
  return static_cast<byte>(id);
}
