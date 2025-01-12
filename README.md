# Progetto finale del gruppo ~BankAccount()
## Suddivisione del lavoro
- Giovanni: classi MyClock e Dispositivi
- Andrea: funzione parser e main
- Giacomo: classe Home

## TO-DO List
**Generale**
- [x] creare un unico namespace per tutte le classi della casa
- [ ] uniformare lingua di variabili e classi in inglese

**MyClock**
- [x] limite MAX_HOUR a 23 al posto che a 24
- [x] bug quando si inserisce orario invalido del tipo ``:56`` o ``08:`` -> utilizzare le regex? ``^([0-1]?[0-9]|2[0-3]):([0-5]?[0-9])$``
- [x] ereditarietà eccezioni
- [ ] verificare comportamenti inattesi quando si passa un Invalid alle diverse funzioni (es. orarioValido + orarioInvalid, orarioValido - orarioInvalid)
- [ ] inserire sempre doppia cifra nelle ore da stampare es. 00:00 e non 0:00

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
- [x] inserire eventuali funzioni mancanti, su richiesta della classe home e parser:
  - [x] funzione per resettare i consumi
  - [x] funzione per eliminare i timers programmati
- [x] alla fine di tutto eliminare funzioni non utilizzate come il toString, chageStatus, operator<<
- [ ] eliminare valore di ritorno bool su turnOn e turnOff
- [ ] se status == true e viene chiamata turnOn, ricalcolare orario di spegnimento dei CP
- [ ] rendere le funzioni get_... inline come per la classe Clock?

**Casa**
- [x] riscrivere funzione per far avanzare il tempo con una multimappa/priority queue
- [x] sistemare formattazione output
- [x] sistemare i foreach che devono scorrere la mappa dei dispositivi e non la lista di inizializzazione
- [x] suggerimento: restituire i messaggi di output al posto di stamparli direttamente:
  - [x] inserirli in una stringa che verrà restituita dalle funzioni come valore di ritorno
  - [x] non ci sono 10 funzioni diverse che devono incastrarsi con i messaggi di output, ma il messaggio viene stampato solo alla fine
- [x] suggerimento: in caso suddividere il parser dalla classe home
- [x] correggere i messaggi di output integrando i valori booleani delle funzioni turnOn e turnOff
- [x] verificare eventuali parametri errati
- [x] resettare consumi in reset_time
- [x] correggere il reset_timer
- [x] implementare reset_all
- [x] implementare rm
- [x] prevedere un messaggio di output per i comandi di reset
- [x] inserire la possibilità di impostare la potenza massima da parametro della CLI in fase di costruzione
- [x] se imposto un timer per l'ora in cui sono, accendo il dispositivo
- [x] fare in modo di reimpostare l'offTime dei CP quando vengono riaccesi
- [x] fare attenzione alla conversione preferita ``const char * -> bool`` rispetto a ``const char * -> clock`` per funzione set(devicename, on/off - clock)
- [x] implementare politica di spegnimento
- [x] verificare memory leak per deviceList e indipendenza dispositivi per due case diverse
- [x] controllare confronti tra double e in caso definire eventuali errore/epsilon
- [x] prevedere costruttore/assegnamento di copy e move?

**Parser**
- [ ] ultimare parser con comandi mancanti
- [ ] gestire eventuali errori nel parser (boundary check / mancanze / parametri in eccesso)

**Main**
- [ ] sviluppare main che riceve comandi inseriti dall'ultente
- [ ] gestire eventuali eccezioni di Parser e Home (es. comandi errati, nome non valido, ...)
- [ ] salvare l'output del programma su file oltre che stamparlo a stdout
- [ ] terminare il programma all'arrivo delle 23:59 con ``if (home.isDayEnded()) -> end program``

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

