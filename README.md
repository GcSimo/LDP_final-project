# Progetto finale del gruppo ~BankAccount()
## Suddivisione del lavoro
- Giovanni: classi MyClock e Dispositivi
- Andrea:
- Giacomo:

## TO-DO List
**Generale**
- [ ] uniformare lingua di variabili e classi in inglese

**MyClock**
- [x] limite MAX_HOUR a 23 al posto che a 24
- [ ] eliminare costruttore con ``const char[]`` perché viene eseguito il cast implicito da ``const char[]`` a ``string``
- [ ] bug quando si inserisce orario invalido del tipo ``:56`` o ``08:`` -> utilizzare le regex? ``^([0-1]?[0-9]|2[0-3]):([0-5]?[0-9])$``
- [ ] ereditarietà eccezioni

**Dispostivi**
- [ ] creare namespace per dispositivi
- [ ] aggiungere ``toString`` e ``operator<<`` a ``Device.h``, eventualmente virtual
- [ ] sistemare valori iniziali di onTime, offTime, cycle nei costruttori di default a invalidHour 24:00
- [ ] trasformare turnOn in virtual:
  - [ ] se ho un dispositivo M e faccio turnOn, è come è stata implementata
  - [ ] se ho un dispositivo CP e faccio il turnOn, bisogna anche inserire l'orario di terminazione
  - [ ] nota, il turnOff è uguale perché non ho timer da modificare
- [ ] trasformare set_OnTime in virtual come per il caso di turnOn se ho dispositivi CP
- [ ] si potrebbe aggiungere la variabile offTime alla classe generale:
  - [ ] entrambi i dispositivi hanno un orario di spegnimento
  - [ ] la classe DeviceM lo implementa già
  - [ ] la classe Device CP avrà in più una variabile per la durata del ciclo che verrà usata per impostare l'offTime, quando viene impostato l'onTime
- [ ] correggere il funzionamento di ID_Counter e ID con variabili statiche -> dichiarare variabile statica e inizializzarla nel file .cpp
- [ ] eliminare i costruttori di default?
- [ ] aggiungere una funzione refreshDevice (come ha fatto Andrea) che riceve un orario e accende/spegne il dispositivo quando l'orario ricevuto supera quello di accensione/spegnimento, utilizzata per evitare di fare la multimappa...
- [ ] rimovere costruttore senza ciclo nei dispositivi CP -> ciclo deve essere impostato nel costruttore e mai più modificato
- [ ] riuovere funzione set_cycle nei dispositivi CP -> ciclo deve essere impostato nel costruttore e mai più modificato

**Casa**
- [ ] ...
