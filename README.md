# BAMBI
# Házi
Kígyós játék (nyomógomb)
Írjátok meg az alábbi játékot az STK3700-as kártyára! A feladat minél több ennivaló felfalása egy kígyóval.

/Általános szabályok

A pálya az LCD kijelző alfanumerikus részének az ábrán beszínezett szegmenseiből áll. A kígyó a játék kezdetekor egy szegmens hosszú (a középső vízszintes pozíciók esetén a két kis szegmens (G + M) együttesen ér fel egy szegmenssel). A kezdeti pozíció legyen a pálya bal szélének két középső szegmense (az ábrán pirossal színezve)! A játék kezdetén helyezzetek el egy véletlenszerűen kiválasztott szegmenset a kígyó testén kívül. Ez jelképezi az ennivalót.

![image](https://github.com/bnyitrai03/BAMBI/assets/126956031/57f1f925-c607-422d-b0f0-a929dfb9f86e)

A játék menete

A kígyó egy megadott sebességgel induljon el jobbra! A PB0 nyomógombbal a kígyó feje forduljon 90°-ot balra, a PB1 nyomógombbal pedig 90°-ot jobbra! Ha bekapta az ételt, akkor egy szegmenssel növekedjen a kígyó hossza, és gyulladjon ki egy másik, véletlenszerűen választott szegmens a kígyó testén kívül. A kijelzőről való lemenetel esetén az átellenes oldalon jöjjön vissza a kígyó! Ellenőrizzétek, hogy a kígyó nem harap-e a saját testébe (nem lép-e arra a pozícióra, ahol már van). Ha igen, megáll a játék, és villogtassa a tizedes pontokat. A kígyó aktuális hosszát mindig jelezzétek ki a számkijelzőn!
