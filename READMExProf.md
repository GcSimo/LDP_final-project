# Progetto finale del gruppo ~BankAccount()
## Suddivisione del lavoro
- Giovanni Bordignon: classi Dispositivi
- Giacomo Simonetto: classe Home
- Andrea Visonà: classe Clock, funzione parser e main

## Scelte progettuali
### Classe ``Clock``
Abbiamo scelto di creare una classe ``Clock`` ausiliaria per gestire meglio gli orari di accensione, spegnimento ed eventuali operazioni di confronto, ordinamento e somma/differenza di tempi.

Nel corso della implementazione è stata richiesta la necessità di definire un orario al di fuori della giornata (non in [0:00, 23:59]) per inizializzare i tempi di accensione e spegnimento dei dispositivi all'inizio del programma. Se avessimo scelto come orario di inizializzazione 0:00, avremmo avuto che tutti i dispositivi si sarebbero accesi e poi spenti all'inizio del prgramma, analogamente se l'orario di inizializzazione fosse stato 23:59. Per ovviare a questo problema abbiamo creato una funzione ``setInvalid`` che imposta l'ora a 24:00 (ovvero l'ora che abbiamo scelto come orario fuori da [0:00, 23:59]) e una funzione ``isValid`` per verificare se un orario si trova nell'intervallo [0:00, 23:59] o no.

### Classi ``Device``, ``DeviceM``, ``DeviceCP``
Abbiamo scelto di creare una classe astratta ``Device`` che implementa un generico dispositivo con alcune funzioni di base. Poi abbiamo specializzato la classe astratta in due classi derivate ``DeviceM`` e ``DeviceCP`` per implementare rispettivamente i dispositivi manuali e quelli a ciclo prefissato.

Per evitare di accendere/spegnere due volte un dispositivo, le funzioni ``turnOn`` e ``turnOff`` eseguono un controllo per determinare se serve accendere/spegnere il dispositvo o se l'operazione è superflua. Nonostante ciò, abbiamo scelto comunque di reimpostare il timer (ricalcolare l'orario di spegnimento) nel caso in cui un dispositivo a ciclo prefissato viene "riacceso".

Per ottimizzare il calcolo della potenza consumata complessiva, abbiamo scelto di procedere in questo modo:
- quando il dispositivo viene acceso, salviamo l'orario di accensione in ``lastEnergyUpdate``
- quando il dispositivo viene "riacceso", non faccio nulla
- quando il dispositivo viene spento, calcolo l'intervallo di tempo in cui è rimasto acceso (orario_di_spegnimento - orario_ultima_accensione) e calcolo la potenza consumata in quell'intervallo
- quando il dispositivo viene "rispento", non faccio nulla

Inoltre, abbiamo previsto una funzione ``refreshDevice`` che ci permette di tenere aggiornati i consumi complessivi del dispositivo per ogni orario della casa. Il calcolo del consumo complessivo di un dispositivo, come indicato poc'anzi, viene aggiornato allo spegnimento dello stesso. Ne consegue che quando viene fatto avanzare l'orario della casa e, in tale avanzamento, il dispositivo è interessato dal solo evento di accensione, il consumo complessivo del dispositivo non varia. Esso rimane infatti costante al valore precedente all'accensione, fino al successivo spegnimento dello stesso. La funzione ``refreshDevice`` risponde a questa necessità: viene aggiornato il consumo complessivo fino all'orario indicato come parametro; la variabile ``lastEnergyUpdate`` tiene traccia dell'orario a cui è stato effettuato tale aggiornamento, garantendo la corretta del calcolo del consumo.

### Classe ``Home``
La classe in questione implementa le funzioni previste nelle specifiche del progetto, ma non prevede l'interfacciamento con l'utente in quanto è esente di un parser per processare i comandi forniti in input da riga di comando dall'utente.

I dispositivi sono salvati in una mappa e hanno il nome del dispositivo come chiave per un accesso più efficiente. Siccome i dispositivi sono memorizzati tramite puntatori e sono allocati dinamicamente, è necessario prevedere un distruttore che libera la memoria dei dispositivi quando l'istanza della casa viene distrutta.

I messaggi di ouptut non sono stampati direttamente dalle funzioni della classe casa, ma sono restituiti in una stringa al chiamate. In questo modo si è più comodi con la gestione di più funzioni che concorrono a stampare i vari messaggi di output. Inoltre si passa al chiamante l'eventuale gestione della stampa dei diversi messaggi di output (es. se voglio sia salvarli in un file, sia mandarli a stdout, ...).
Sono stati aggiunti/modificati alcuni messaggi di output in caso di situazioni particolari per esplicitare meglio il contesto e le operazioni svolte:
- quando si tenta di accendere/spegnere un dispositivo già spento/acceso: \
  ``[13:00] Il dispositivo ${devicename} è già acceso/spento``
- quando si imposta solo il timer di accensione di un dispositivoM: \
  ``[13:00] Impostato un timer per il dispositivo ${devicename} dalle 7:00 in poi`` al posto che ``... dalle 7:00 alle 24:00``
- quando si tenta di accendere/spegnere un dispositivo che provocherebbe il superamento della potenza massima prelevabile dalla rete: \
  ``[13:00] Il dispositivo ${devicename} non si è acceso/spento perché si supererebbe la potenza massima prelevabile dalla rete``
- quando un dispositivo viene spento per ridurre il consumo dalla rete elettrica: \
  ``[13:00] Il dispositivo ${devicename} si è spento per ridurre il consumo del sistema``

Sappiamo che si può evitare di stampare un messaggio di output quando si tenta di accendere/spegnere un dispositivo già spento/acceso, ma abbiamo deciso che era necessario tenerlo per due motivi. Il primo è che quando l'utente esegue una "riaccensione" o uno "rispegnimento" manuale (in caso involontaria), si aspetta che il programma gli restituisca un messaggio di output. Il secondo è che, sebbene un dispositivo già acceso/spento non ha bisogno di essere "riacceso"/"rispento", comunque vengono eseguite altre operazioni (es. ricalcolare l'orario di spegnimento) ed è bene informare l'utente di ciò per una completa trasparenza.

Per una maggiore praticità e minore rindondanza del codice, abbiamo scelto di implementare una funzione ausiliaria privata ``set(devicename, new_status, cmd_time)``per gestire l'accensione e lo spegnimento dei dispositivi ed eventuali controlli da fare ad ogni accensione. Di seguito come sono stati gestiti i diversi casi:
- controllo che il dispositivo non sia già acceso o spento -> in caso affermativo non faccio nulla ad eccezione di quando provo ad accendere un dispositivo già acceso: eseguo comunque la chiamata di ``device.turnOn`` perché se ho un dispositivo CP, ricalcolo il timer.
- controllo se è necessario spengnere dei dispositivi per ridurre il consumo dalla rete -> in caso applico la politica di spegnimento
- accendo/spengo il dispositivo in questione e aggiorno eventuali variabili da aggiornare

In questo modo la potenza massima prelevabile dalla rete non viene mai superata e tale condizione viene verificata in ogni accensione.

Per implementare la politica di spegnimento *First_ON_First_OFF* abbiamo creato una linked-list ``turned_on_devices`` che memorizza i riferimenti ai dispositivi accesi che consumano. Quando un dispositivo che consuma corrente viene acceso, si aggiunge il suo riferimento in coda, quando un dispositivo viene spento, si rimuove, se presente, il suo riferimento dalla lista. Se è necessario applicare la politica di spegnimento, implementata nella funzione ``turn_off_policy``, si estrae il dispositivo in testa alla lista e lo si spegne. Come struttura dati è stata scelta la lista (e non una coda), in quanto in una coda non è possibile rimuovere agevolmente dispositivi dal mezzo.

Per quanto riguarda il settaggio dei timer dei diversi dispositivi, abbiamo fatto alcune considerazioni:
- non è possibile impostare timer con orari nel passato, per cui deve essere sempre verificata la seguente disuguaglianza: ``0:00 <= orario_sistema <= start < stop <= 23:59``
- se l'orario di accensione impostato corrisponde con l'orario del sistema, il dispositivo viene acceso
- le accensioni e gli spegnimenti manuali non influiscono in alcun modo sui timer dei dispositivi manuali:
  - considerando il caso in cui impostiamo che il riscaldamento si accenda automaticamente alle 7:00 e che si spenga alle 20:00
  - verso pranzo vediamo che fuori è una giornata limpida e pulita e ci piacerebbe cambiare aria alla casa, ma siccome fuori fa freddo e non vogliamo consumare corrente, decidiamo di spegnere momentaneamente il riscaldamento alle 13:00, mentre lasciamo aperte le finestre
  - poi alle 14:00 chiudiamo le finestre e riattiviamo il riscaldamento
  - ci aspettiamo/vogliamo che il sistema ritorni alle impostazioni automatiche e che spegna automaticamente il riscaldamento alle 20:00 ed è proprio quello che fa

Per far avanzare il tempo del sistema, abbiamo scelto di visitare ogni dispositivo della casa, costruirci un nuovo oggetto "evento" per ogni operazione/comando da eseguire ed infine inserire tutti gli eventi in una priority queue. L'oggetto "evento" è stato definito di tipo struct ``event`` in quanto è solo un contenitore di dati. Per specificare come ordinare gli eventi nella priority queue è stato definito un function object ``eventCompare`` in modo da assegnare priorità più alta agli eventi che hanno orario minore e a parità di orario, hanno priorià gli spegnimenti (per ridurre il consumo per eventuali accensioni). Una volta che abbiamo tutti gli eventi ordinati all'interno della priority queue, non ci resta altro da fare che estrarli ed eseguirli.

Durante dei test, abbiamo notato che i confronti tra double possono dare problemi dovuti alle approsimazioni delle conversioni da binario a decimale. In particolare nel caso di confronti tra potenza istantanea assorbita dalla rete e il limite di potenza prelevabile. Per ovviare a questo problema abbiamo scelto di inserire un certo scarto di 1e-15. Infatti intorno a 1, la differenza tra 1 e il successivo numero rappresentabile in un double è di 2^-52 = 2.220446...e-16.

### Libreria ``Parser``
Abbiamo scelto di separare la funzione di ``parser`` dalla classe ``Home`` in modo da poterci dividere meglio il lavoro e non appesantire troppo la classe in questione. La funzione riceve il comando inserito dall'utente sottoforma di stringa e una reference dell'oggetto di classe ``Home`` su cui invocare i comandi specificati dall'utente. Si suppone che il comando da interpretare non sia una stringa vuota (caso gestito dal main). Nel caso in cui le funzioni invocate producano eccezioni, queste non vengono catturate, per gestirle meglio nel main. I messaggi di output delle funzioni vengono restituiti come stringa al main.

### File sorgente ``main.cpp``
Il ``main`` si occupa di gestire l'input, l'output e l'interfacciamento con l'utente. Si occupa di creare l'oggetto della classe ``Home`` con la potenza massima prelevabile dalla rete ricevuta sottoforma di parametro da riga di comando. Gestisce la scrittura sul file di log e stampa a standard output i diversi messaggi ottenuti dalla funzione ``parser``. Non appena l'orario del sistema raggiunge le 23:59, il programma termina la sua esecuzione, in quanto non ha senso eseguire ulteriori comandi.


Abbiamo scelto di salvare il file di log chiamato ``log.txt`` nella cartella ``log`` situata nella cartella principale del progetto. Si suppone che il progetto venga compilato all'interno della cartella ``build`` e che l'eseguibile finale ``main`` si trovi in quella cartella. Ci aspettiamo che il file venga eseguito dalla cartella ``build`` per cui il path relativo al file di log è ``../log/log.txt``. Il file eseguibile viene spostato, il file di log potrà non trovarsi nella cartella di log.

## Errore non gestito
Ci siamo accorti all'ultimo di un problema dovuto ad un mancato aggiornamento della priority queue durante l'estrazione ed esecuzione degli eventi in set_time:
```
> ⁠set Asciugatrice 12:00
[11:30] L'orario attuale è 11:30
[11:30] Impostato un timer per il dispositivo Asciugatrice dalle 12:00 alle 13:00

> ⁠set Asciugatrice on
[11:30] L'orario attuale è 11:30
[11:30] Il dispositivo Asciugatrice si è acceso

> ⁠set time 13:30
[11:30] L'orario attuale è 11:30
[12:00] Il dispositivo Asciugatrice è già acceso
[12:30] Il dispositivo Asciugatrice si è spento
[13:30] L'orario attuale è 13:30
```
In pratica l'accensione dell'asciugatrice delle 12:00 dovrebbe impostare il timer di spegnimento alle 13:00 come effettivamente fa, soltanto che l'evento non viene caricato nella priority queue e di conseguenza non viene eseguito. Viene eseguito, invece l'evento di spegnimento precedente che andrebbe rimosso. Non siamo riusciti a trovare una soluzione semplice perché ce ne siamo accorti troppo tardi per sistemare in sicurezza senza provocare altri danni.
