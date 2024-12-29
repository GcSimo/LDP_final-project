--- DESCRIZIONE FILE ---
1. Dispositivo.h	--> File header della classe base Dispositivo
2. Dispositivo.cpp	--> File con l'implementazione della classe Dispositivo
3. Disp_M.h		--> File header della classe derivata DispM (--> Dispositivo Manuale)
4. DispositivoM.cpp	--> File con l'implementazione della classe derivata DispM
5. Disp_CP.h		--> File header della classe derivata DispCP (--> Dispositivo Ciclo Prefissato)
6. DispositivoCP.cpp	--> File con l'implementazione della classe derivata DispCP
7. MyClock.h		--> File header della classe Clock
8. MyClock.cpp		--> File con l'implementazione della classe Clock
-- Tester --
9. Main.cpp		--> File eseguibile con piccole operazioni sul singolo dispositivo
10. TestMapHour.cpp	--> Esemplificazione del funzionamento con una MultiMappa ordinata secondo chiavi
			    di oggetti Clock.


Comandi riga di comando per la compilazione dei due eseguibili:

g++ Main.cpp DispositivoM.cpp DispositivoCP.cpp Dispositivo.cpp MyClock.cpp -o testMain.exe

g++ TestMapHour.cpp DispositivoM.cpp DispositivoCP.cpp Dispositivo.cpp MyClock.cpp -o TestMapHour.exe