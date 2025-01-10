# Progetto finale del gruppo ~BankAccount()
## Suddivisione del lavoro
- Giovanni: classi MyClock e Dispositivi
- Andrea:
- Giacomo:

## TO-DO List
**Generale**
- [x] creare un unico namespace per tutte le classi della casa
- [ ] uniformare lingua di variabili e classi in inglese

**MyClock**
- [x] limite MAX_HOUR a 23 al posto che a 24
- [x] bug quando si inserisce orario invalido del tipo ``:56`` o ``08:`` -> utilizzare le regex? ``^([0-1]?[0-9]|2[0-3]):([0-5]?[0-9])$``
- [x] ereditarietà eccezioni

**Dispostivi**
- [x] aggiungere ``toString`` e ``operator<<`` a ``Device.h``, eventualmente virtual
- [x] sistemare valori iniziali di onTime, offTime, cycle nei costruttori di default a invalidHour 24:00
- [x] trasformare turnOn in virtual:
  - se ho un dispositivo M e faccio turnOn, è come è stata implementata
  - se ho un dispositivo CP e faccio il turnOn, bisogna anche inserire l'orario di terminazione
  - nota, il turnOff è uguale perché non ho timer da modificare
- [x] trasformare set_OnTime in virtual come per il caso di turnOn se ho dispositivi CP
- [x] si potrebbe aggiungere la variabile offTime alla classe generale:
  - entrambi i dispositivi hanno un orario di spegnimento
  - la classe DeviceM lo implementa già
  - la classe Device CP avrà in più una variabile per la durata del ciclo che verrà usata per impostare l'offTime, quando viene impostato l'onTime
- [x] correggere il funzionamento di ID_Counter e ID con variabili statiche -> dichiarare variabile statica e inizializzarla nel file .cpp
- [x] eliminare i costruttori di default
- [x] aggiungere una funzione refreshDevice (come ha fatto Andrea) che riceve un orario e accende/spegne il dispositivo quando l'orario ricevuto supera quello di accensione/spegnimento, utilizzata per evitare di fare la multimappa...
- [x] rimovere costruttore senza ciclo nei dispositivi CP -> ciclo deve essere impostato nel costruttore e mai più modificato
- [x] riuovere funzione set_cycle nei dispositivi CP -> ciclo deve essere impostato nel costruttore e mai più modificato
- [x] creare namespace per dispositivi
- [x] sistemare consumi
- [x] aggiungere un valore di ritorno booleano alle funzioni turnOn e turnOff:
  - [x] quando il dispositivo è già spento o già acceso, si comunica al chiamante che non è stata fatta nessuna modifica e il chiamante capisce che non deve mandare nessun messaggio in stampa
  - [x] la funzionalità sopra è particolarmente utile nella funzione goForward quando è programmata l'accensione di un dispositivo che supererebbe il consumo massimo e che quindi non viene acceso; in aternativa si dovrebbe eliminare l'evento di spegnimento, ma non è facile eliminare un evento nel mezzo di una priority queue
- [ ] inserire eventuali funzioni mancanti, su richiesta della classe home e parser:
  - [ ] funzione per resettare i consumi
  - [ ] funzione per eliminare i timers programmati
- [ ] alla fine di tutto eliminare funzioni non utilizzate come il toString, chageStatus, operator<< e bool in turnOff, turnOn

**Casa**
- [x] riscrivere funzione per far avanzare il tempo con una multimappa/priority queue
- [x] sistemare formattazione output
- [x] sistemare i foreach che devono scorrere la mappa dei dispositivi e non la lista di inizializzazione
- [x] suggerimento: restituire i messaggi di output al posto di stamparli direttamente:
  - [x] inserirli in una stringa che verrà restituita dalle funzioni come valore di ritorno
  - [x] non ci sono 10 funzioni diverse che devono incastrarsi con i messaggi di output, ma il messaggio viene stampato solo alla fine
- [x] suggerimento: in caso suddividere il parser dalla classe home
- [ ] correggere i messaggi di output integrando i valori booleani delle funzioni turnOn e turnOff
- [ ] con reset time vanno resettati anche i consumi
- [ ] correggere il resetTimer
- [ ] prevedere un messaggio di output per i comandi di reset
- [ ] gestire il caso in cui voglio spegnere i pannelli, ma se li spengo supero la massima corrente assorbibile dalla rete -> politica di spegnimento
- [ ] verificare eventuali parametri errati
- [ ] terminare il programma all'arrivo delle 23:59

**Parser**
- [ ] ultimare parser con comandi mancanti
- [ ] gestire eventuali errori nel parser (boundary check / mancanze, mess)
- [ ] fare attenzione nel parser, se i dispositivi hanno uno spazio all'interno del loro nome
- [ ] catturare eventuali eccezioni della classe Casa

## REGEX
Alcune espressioni regex che possono tornare utili in una possibile implementazione, anche se non necessarie e indispensabili.

### Regex orario
per casting da string a clock: \
``^([0-1]?[0-9]|2[0-3]):([0-5]?[0-9])$``

### Regex parser comandi
- ``set devicename on/off``: \
``^set [a-zA-Z0-9]* (on|off)$``

- ``set devicename _:__ [_:__]``: \
``^set [a-zA-Z0-9]* ([0-1]?[0-9]|2[0-3]):([0-5]?[0-9])( ([0-1]?[0-9]|2[0-3]):([0-5]?[0-9]))?$``

- ``set time _:__``: \
``^set time ([0-1]?[0-9]|2[0-3]):([0-5]?[0-9])$``

- ``rm devicename``: \
``^rm [a-zA-Z0-9]*$``

- ``show``: \
``^show$``

- ``show devicename``: \
``^show [a-zA-Z0-9]*$``

- ``reset time, timer, all``: \
``^reset (time|timers|all)$``

