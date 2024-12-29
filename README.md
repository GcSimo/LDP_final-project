# Progetto finale del gruppo ~BankAccount()
## Suddivisione del lavoro
- Giovanni: classi MyClock e Dispositivi
- Andrea:
- Giacomo:

## TO-DO List
Generale:
- uniformare lingua di variabili e classi in inglese

MyClock
- ereditarietà eccezioni
- limite MAX_HOUR a 23 al posto che a 24

Dispostivi
- creare namespace per dispositivi
- aggiungere ``toString`` e ``operator<<`` a ``Device.h``, eventualmente virtual
- sistemare valori iniziali di onTime, offTime, cycle nei costruttori di default a invalidHour 24:00
- trasformare turnOn in virtual:
  - se ho un dispositivo M e faccio turnOn, è come è stata implementata
  - se ho un dispositivo CP e faccio il turnOn, bisogna anche inserire l'orario di terminazione
  - nota, il turnOff è uguale perché non ho timer da modificare
- trasformare set_OnTime in virtual come per il caso di turnOn se ho dispositivi CP
- si potrebbe aggiungere la variabile offTime alla classe generale:
  - entrambi i dispositivi hanno un orario di spegnimento
  - la classe DeviceM lo implementa già
  - la classe Device CP avrà in più una variabile per la durata del ciclo che verrà usata per impostare l'offTime, quando viene impostato l'onTime
