# Progetto finale del gruppo ~BankAccount()
## Suddivisione del lavoro
- Giovanni Bordignon: classi Dispositivi
- Giacomo Simonetto: classe Home
- Andrea Visonà: classe Clock, funzione parser e main

## Scelte progettuali
### Classe ``Clock``
Abbiamo scelto di creare una classe ``Clock`` ausiliaria per gestire meglio gli orari di accensione, spegnimento ed eventuali operazioni di confronto, ordinamento e somma/differenza di tempi.

Nel corso della implementazione è stata richiesta la necessità di definire un orario al di fuori della giornata (non in [0:00, 23:59]) per inizializzare i tempi di accensione e spegnimento dei dispositivi all'inizio del programma. Se avessimo scelto come orario di inizializzazione 0:00, avremmo avuto che tutti i dispositivi si sarebbero accesi e poi spenti all'inizio del prgramma, analogamente se l'orario di inizializzazione fosse stato 23:59. Per ovviare a questo problema abbiamo creato una funzione ``setInvalid`` che imposta l'ora a 24:00 (ovvero l'ora che abbiamo scelto come orario fuori da [0:00, 23:59]) e una funzione ``isValid`` per verificare se un orario è valido o no.

### Classi ``Device``, ``DeviceM``, ``DeviceCP``
Abbiamo scelto di creare una classe virtuale ``Device`` che implementa in maniera astratta un generico dispositivo con alcune funzioni di base. Poi abbiamo specializzato la classe virtuale in due classi derivate ``DeviceM`` e ``DeviceCP`` per implementare rispettivamente i dispositivi manuali e quelli a ciclo prefissato.

Per evitare di accendere/spegnere due volte un dispositivo, le funzioni ``turnOn`` e ``turnOff`` eseguono un controllo per determinare se serve accendere/spegnere il dispositvo o se l'operazione è superflua.

Per ottimizzare il calcolo della potenza consumata complessiva, abbiamo scelto che:
- quando il dispositivo viene acceso, salviamo l'orario di accensione in ``lastEnergyUpdate``
- quando il dispositivo viene riacceso, non faccio nulla
- quando il dispositivo viene spento, calcolo il tempo in cui è rimasto acceso (orario_di_spegnimento - orario_ultima_accensione) e calcolo la potenza consumata
- quando il dispositivo viene rispento, non faccio nulla

Inoltre, abbiamo previsto una funzione ``refeshDevice`` che ci permette di tenere aggiornati i consumi complessivi del dispositivo per ogni orario della casa. Quando viene fatto avanzare l'orario della casa e nell'avanzamento il dispositivo viene acceso, ma non viene spento, il consumo complessivo del dispositivo non contegga anche il periodo in cui è stato acceso. La funzione ``refeshDevice`` serve per includere anche questo tempo: viene aggiornato il consumo complessivo fino all'orario indicato come parametro e ``lastEnergyUpdate`` diventa l'orario indicato come parametro.

### Classe ``Home``
La classe implementa le funzioni previste nelle specifiche del progetto e non prevede l'interfacciamento con l'utente.

I dispositivi sono salvati in una mappa e hanno il nome del dispositivo come chiave per un accesso più efficiente. Siccome i dispositivi sono memorizzati tramite puntatori e sono allocati dinamicamente, è necessario prevedere un distruttore che libera la memoria dei dispositivi quando l'istanza della casa viene distrutta.

I messaggi di ouptut non sono stampati direttamente dalle funzioni della classe casa, ma sono restituiti in una stringa al chiamate. In questo modo si è più comodi con la gestione di più funzioni che concorrono a stampare i vari messaggi di output. Inoltre si passa al chiamante l'eventuale gestione della stampa dei diversi messaggi di output (es. se li voglio salvare in un file e non mandarli a stdout, ...).
Sono stati aggiunti/modificati alcuni messaggi di output in caso di situazioni particolari per esplicitare meglio il contesto:
- quando si tenta di accendere/spegnere un dispositivo già spento/acceso: \
  ``[13:00] Il dispositivo ${devicename} è già acceso/spento``
- quando si imposta solo il timer di accensione di un dispositivoM: \
  ``[13:00] Impostato un timer per il dispositivo ${devicename} dalle 7:00 in poi`` al posto che ``... dalle 7:00 alle 24:00``
- quando si tenta di accendere/spegnere un dispositivo che provocherebbe il superamento della potenza massima prelevabile dalla rete: \
  ``[13:00] Il dispositivo ${devicename} non si è acceso/spento perché si supererebbe la potenza massima prelevabile dalla rete``
- quando un dispositivo viene spento per ridurre il consumo dalla rete elettrica
  ``[13:00] Il dispositivo ${devicename} si è spento per ridurre il consumo del sistema``

Per una maggiore praticità e minore rindondanza del codice, abbiamo scelto di implementare una funzione ausiliaria privata ``set(devicename, new_status, cmd_time)``per gestire l'accensione e lo spegnimento dei dispositivi ed eventuali controlli da fare ad ogni accensione:
- controllo che il dispositivo non sia già acceso o spento -> in caso affermativo non faccio nulla *(*eccezione)*
- controllo se è necessario spengnere dei dispositivi per ridurre il consumo dalla rete -> in caso applico la politica di spegnimento
- accendo/spengo il dispositivo in questione e aggiorno eventuali variabili da aggiornare
**eccezione:* quando provo ad accendere un dispositivo già acceso, eseguo comunque la chiamata di ``device.turnOn`` perché nel caso di un dispositivo CP, faccio ripartire il timer del ciclo di funzionamento. \
In questo modo la potenza massima prelevabile dalla rete non viene mai superata e la condizione viene verificata in ogni accensione

Come politica di spegnimento, nel caso si vada incontro ad operazioni che facciano superare il limite del consumo massimo della rete, abbiamo scelto di iniziare a spegnere i dispositivi da quello che è stato acceso per primo fino all'ultimo acceso (una specie di politica First_ON_First_OFF). Per implementare ciò abbiamo creato una linked-list ``turned_on_devices`` che memorizza i riferimenti ai dispositivi accesi che consumano. Quando un dispositivo che consuma corrente viene acceso, si aggiunge il suo riferimento in coda, quando un dispositivo viene spento, si rimuove, se presente, il suo riferimento dalla lista. Se è necessario applicare la politica di spegnimento, implementata nella funzione ``turn_off_policy``, si estrae il dispositivo in testa alla lista e lo si spegne. Come struttura dati è stata scelta la lista (e non una coda), in quanto in una coda non è possibile rimuovere agevolmente dispositivi dal mezzo.

Per far avanzare il tempo del sistema, abbiamo scelto di visitare ogni dispositivo della casa, costruirci un nuovo oggetto "evento" per ogni operazione/comando da eseguire ed infine inserire tutti gli eventi in una priority queue. L'oggetto "evento" è stato definito di tipo struct ``event`` in quanto è solo un contenitore di dati. Per specificare come ordinare gli eventi nella priority queue è stato definito un function object ``eventCompare`` in modo da assegnare priorità più alta agli eventi che hanno orario minore.

### Libreria ``Parser``

