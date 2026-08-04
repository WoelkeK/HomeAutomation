#pragma once

// Etap 9: logiczne nazwy rolet przygotowane pod dalsze porządkowanie.
// UWAGA: na tym etapie nie zmieniamy działania rolet ani mapowania pinów,
// bo rolety mają zostać chwilowo na lokalnych wyjściach Mega.

enum class RollerId : byte
{
  Sportowy = 0,
  Wykusz = 1,
  Lazienka = 2,
  Kuchnia = 3,
  Gabinet = 4,
  SalonSrodek = 5,
  SalonLewa = 6,
  SalonPrawa = 7
};
