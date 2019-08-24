# RG153-absolutely-anything
### Koncept

Absolutely Anything je igra za koju je originalno ceo koncept bilo generisanje i odgenerisanje objekata na osnovu srodnih atributa. Ovaj koncept je implementiran u prvom nivou, ali na mnogo manjoj skali s obzirom da je autor skapirao koliko je to Mission Impossible .

### Pokretanje Programa

Kada se pokrene program, igra vas stavi u nivo `0` odnosno na prazan ekran. Da biste izabrali nivo, prosto kliknite:

- `0` za nulti nivo
- `1` za prvi nivo
- `2` za drugi nivo

### Prvi Nivo

Prvi nivo pocinje tako sto se pred vama stvori polje sa drvecem, kamenjem i degenerisani star cruiseri (oblaci) razlicitih boja. Poenta prvog nivoa je da sve vratite u prvobitno stanje, odnosno da na polju ostane samo **zeleno drvece, crno kamenje i sivi oblac**i.

Ovo se postize tako sto koristite odredjene atribute kao prekidace za prikazivanje odnosno neprikazivanje odredjene grupine objekata. Na primer, ako kliknete `V` promenicete stanje svih **zivih** objekata, znaci drvece koje nije bilo prikazivano ce se pojaviti i drvece koje e bilo vec prikazivano se nece vise pojavljivati. Ovaj princip vazi za sve atribute:

- `D` za mrtve objekte
- `V` za zive objekte
- `Q` za sive objekte
- `R` za crvene objekte
- `G` za zelene objekte
- `B` za plave objekte
- `S` za cvrste objekte
- `A` za vazdusaste objekte
- `L` za velike objekte
- `T` za male objekte

Osim ovih komandi, moze se kliknuti i `]` da bi se simulirao kraj nivoa, ovo vazi isto i za drugi nivo.

> Vazna napomena, boje kao atributi su potpuno odvojeni od ostalih atributa, znaci ako kliknete `G` dok je prisutno samo svo drvece i oblaci, bez kamenja. Efekat ce se videti samo na drvecu i oblacima, ali ne i na kamenju kada ih opet generisete. Boje i ostali atributi su namenjeni da se racunaju kao dve skupine objekata.

### Drugi Nivo

Drugi nivo se zasniva na trazenju zajednickih atributa (filmova) koji povezuju odredjene objekte. Selektovanje objekata se navigira sa `n` i `m` tasterima (trenutno izabran objekat ce hover-ovati). Objekat ubacujete u svoju selekciju tako sto stisnete taster `s`, a izbacujete ga iz selekcije tasterom `a`. Mozete da proverite da li datu selekciju povezuje neki filmski naslov pritisom na taster `x`. Da bi se doslo do kraja, potrebno je "naci" sve filmove u datim objektima.

### LORE

One day, The Great All Father went drinking with Mother Nature and Quentin Tarantino. While drinking, God screwed up movies and nature. **YOU** are his disciple and the only one capable of fixing this situation, you would wait for God to do it, but Tarantino really needs movies to work by like 9:00 AM cause Once Upon A Time In Hollywood is coming out, and you can't find God by then because he's been drinking the Heavenly Russian Teleporting Elixir....again. But because you're quite new to this **divinity** deal, you only know how to manipulate objects using the **POWER OF ATTRIBUTES**. Better get crackin'.

