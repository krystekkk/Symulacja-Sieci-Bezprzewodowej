# Symulacja sieci bezprzewodowej

Treść problemu:

W sieci bezprzewodowej stacje nadawcze konkurują o dostęp do łącza. W losowych odstępach
czasu CGPk k-ta stacja nadawcza generuje pakiety gotowe do wysłania. Po uzyskaniu dostępu do łącza
zgodnie z algorytmem A, k-ty terminal podejmuje próbę transmisji najstarszego pakietu ze swojego
bufora. Czas transmisji wiadomości z k-tej stacji nadawczej do k-tej stacji odbiorczej wynosi CTPk. Jeśli
transmisja pakietu zakończyła się sukcesem, stacja odbiorcza przesyła potwierdzenie ACK (ang.
Acknowledgment) poprawnego odebrania wiadomości. Czas transmisji ACK wynosi CTIZ. Jeśli
transmisja pakietu nie powiodła się, stacja odbiorcza nie przesyła ACK. Odbiór pakietu uznajemy za
niepoprawny, jeśli w kanale transmisyjnym wystąpiła kolizja lub błąd. Przez kolizję rozumiemy
nałożenie się jakiejkolwiek części jednego pakietu na inny pakiet (pochodzący z innego nadajnika).
Dodatkowo każda transmisja pakietu może zakończyć się błędem TER. Brak wiadomości ACK po czasie
(CTPk + CTIZ) od wysłania pakietu jest dla stacji nadawczej sygnałem o konieczności retransmisji
pakietu. Każdy pakiet może być retransmitowany maksymalnie LR razy. Dostęp do łącza w przypadku
retransmisji opiera się na tych samych zasadach co transmisja pierwotna. Jeśli mimo LR-krotnej próby
retransmisji pakietu nie udało się poprawnie odebrać, wówczas stacja nadawcza odrzuca pakiet i – jeśli
jej bufor nie jest pusty – przystępuje do próby transmisji kolejnego pakietu.


Algorytm:

Protokół CSMA (ang. Carrier Sense Multiple Access) z wymuszaniem transmisji z
prawdopodobieństwem p (ang. p-persistent) – w protokole tym czas jest podzielony jest na szczeliny
o długości CSC. Po wygenerowaniu nowego pakietu, stacja nadawcza sprawdza zajętość kanału
transmisyjnego. Jeśli kanał jest zajęty, to dalsze odpytywanie kanału odbywa się w odstępach co 0.5
ms. Gdy stacja wykryje, że kanał jest wolny, rozpoczyna transmisję w najbliższej szczelinie z
prawdopodobieństwem PT. Z prawdopodobieństwem (1-PT) stacja wstrzymuje się z transmisją do
następnej szczeliny, w której ponownie sprawdza status kanału. Jeśli następna szczelina okaże się
również wolna, terminal rozpoczyna transmisję z prawdopodobieństwem PT lub wstrzymuje się z
prawdopodobieństwem (1-PT). Ta procedura jest powtarzana tak długo, aż pakiet zostanie wysłany lub
kanał stanie się zajęty. W tym ostatnim przypadku terminal nasłuchuje kanał w odstępach co 1 ms i
gdy wykryje, że jest wolny, rozpoczyna opisaną wyżej procedurę od nowa. W przypadku retransmisji,
stacja nadawcza sprawdza stan kanału po losowym czasie CRP równym R*CTPk, gdzie R jest losową
liczbą z przedziału od <0, (2r – 1)> , a r jest numerem aktualnej retransmisji (przy każdej retransmisji
czas ten jest losowany ponownie). Wówczas uruchamiana jest taka sama procedura jak w przypadku
transmisji pierwotnej. PT = 0.6


Parametry wywołania programu:

Czas trwania symulacji – wartość czasu symulacji, jaki użytkownik wprowadza na początku trwania
programu. Z racji posiadanego algorytmu, w którym odpytywanie kanału gdy ten jest zajęty odbywa
się w czasie 0.5 ms, obowiązuje następujący przelicznik jednostki czasu: np. 100 jednostek czasu
symulacji = 10 milisekund. Użytkownik wprowadza wartość w milisekundach a program przelicza ją
na jednostkę czasu symulacji.

Lambda – intensywność rozkładu wykładniczego.

Czas trwania fazy początkowej – czas, po upływie którego program rozpoczyna zbieranie statystyk.
Wartości bowiem po upływie czasu trwania fazy początkowej stabilizują się.

Tryb pracy symulatora – program symulacyjny pracuje w trypie krokowym lub ciągłym. Program
prosi o wprowadzenie wartości 1 oznaczającej tryb ciągły lub wartości 2 oznaczającej tryb krokowy.
W przypadku podania wartości spoza zakresu domyślnie wykonuje się tryb ciągły.
