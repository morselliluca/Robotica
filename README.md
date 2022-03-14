# Robotica

Tutti i ptogetti robotica del Gruppo DKV Lab<br/>
Siamo un gruppo di 2 persone dell'Itis rossi che hanno partecipato alla Robocup per 4 anni consecutivi con questi progetti.<br/>
il gruppo è formato da:

	Luca Morselli
		-Arduino e Teensyduino:
			-Data collection -> lettura sensori di calore, ultrasuono, riflesso, encoder
			-Serial and comunication -> comunicazione in seriale tra arduino / teensy e Raspberry
			-Movement -> libreria e calibrazione driver e motori dc
		-Pcb design 
		-Mechanical part design
		
	Luca Barban:
		-On Raspberry:
			-Opencv -> riconoscimento caratteri e colori
			-Navigation -> navigazione della mappa
			-Mapping -> creazione della mappa partendo da ultrasuoni o lidar
			-Data Collection -> salvare i dati sulla mappa del nero calore lettere ecc.
			-Serial and comunication -> comunicazione in seriale tra arduino / teensy e Raspberry
			
Cosa troverete all'interno di questa repository:

All'interno di 1. lego line troverete (Line):

	/programmi
		Il codice per la rescue line per un EV3 della lego
		/programmi/Blocchi
			Dei Blocchi custom per leggere il riflesso RGB separatamente da i sensori Stock della lego

All'inerno di 2. project manta troverete (Maze):

	/documentazione
		Un foglio xsl (foglio di calcolo) con tutti i pinout dell'arduino mega, nano e raspberry 
		
	/pcb
		Le Pcb logic e Power usate per il robot + i file gerber per ordinarli
		
	/programma
		/programma/arduino
			/programma/arduino/mega
				il programma per l'arduino mega
			/programma/arduino/nano
				il programma per l'arduino nano
			/programma/arduino/test
				programmi di test vari
		
		/programma/rsby
			programma di test per la raspberry
	
	/scocca
		/scocca/3d
			pezzi da stampare 3d per la scocca (non utilizzati per l'ultima verisone )
		/scocca/logo
			il logo del team
		/scocca/ruote
			ruote da tagliare al laser (non le consiglio, compratele fatte bene Pololu o simili)
		/scocca/taglio
			la scocca del robot da tagliare al laser 
				bello = il piu recente
				manta = delle prove 
				cobra = il primo tentativo
				
	lista.xls 
		la lista dei pezzi che compongono il robot


All'inerno di 3. project Hive troverete (Maze):

	/cagacubi
		le varie versioni del hopper per buttare giu i cubi
		
	/documentazione
		la varia documentazione per tutti i pezzi del robot +  i vari modelli 3d + regole
	
	/foto
		delle foto del robot renderizzato
	
	/pcb 
		file pdf delle schematiche delle 2 pcb del robot + i file gerber per ordinarli
	
	/programma
		/programma/teensy
			il programma per la teensy per interfacciarsi a ros
		/programma/test
			test vari per la teensy e i sensori
	
	/ros documentation
		buona fortuna ragazzi, questo e l'unico pezzo di documentazione ti ros olte il sito ufficiale fatto da cani
	
	/scocca
		disegni di fuzion della scocca del robot per il taglio a laser
	
	/taglio
		progetti in dxf pronti per il taglio laser
		
	Lista.xls
		la lista dei pezzi che compongono il robot

Faq:

E presente anche una ide di arduino munita di Teensyduino, rosserial e tutte le librerie da noi utilizzate.

Le parti di raspberry degli ultimi 2 progetti mancano e verra aggiunta solo quella dell'ultimo progetto in quanto quella di Manta e stata persa.

I pezzi per il taglio laser sono stati provati principalmente in legno (pippo), plexiglass ed alluminio

I pezzi stampati sono sati stampati solo con stampanti 3d a filamento in quanto della a resina non funzionava (prusa MK.3)

Il grosso dei pezzi e stato acquistato da Aliexpress

Nella lista di Manta ci sono i driver dei motori cinesi NON COMPRATELI si bruciano subito prendete i pololu anche se costano di piu valgono la spesa

Non usate amg8833 come in Manta costano tanto e non e possibile cambiare l'indirizzo i2c nella libreria per leggerli in maniera semplice noi abbiamo usato 2 arduini in piu per questo motvo (i nano), la soluzione migliore e acquistare gli mlx90614

Le batterie consiglio Lipo o 18650 almeno una 3s per portare la tensione intorno i 12v () noi usiamo 2 2s in serie

Consiglio di usare ruote e non cingoli

Consiglio motori con encoder tornano utili per contare i giri che ha fatto la ruota

Per collegare raspberry ad arduino o simili usate la seriale e usate direttamente la porta USB poer evitare di bruciarlo in quanto la maggior parte degli arduino sono a 5v e la raspby supporta solo 3.3v

Quando usate i driver della pololu come MC33926 portate il pin EN -> HIGH e i pin PWM(Negato)/D1 -> Low

I pin INA e INB sono usati per la direzione, vanno messi uno in HIGH uno in LOW 

Da prova_v17 sul progetto Hive le funzioni hanno un timing e vengono eseguite esattamente ogni N millisecondi (la funzione si trova all'interno del void loop)<br/>
	Odom viene mandata 100HZ<br/>
	velocita e encoder sono calcolati 1000HZ<br/>

Dalla prova_v18 su Hive la velocita viene controllata su ogni motore per fali girare alla stessa velocita tutti



Source:<br/>

Sensori di distanza arduino<br/>
https://www.youtube.com/watch?v=6F1B_N6LuKw<br/>
https://dronebotworkshop.com/hc-sr04-ultrasonic-distance-sensor-arduino/<br/>

Libreria Pololu vnh5019, la base della libreria custom che troverete in/arduino-1.8.19/libraries/DriverDkv<br/>
https://github.com/pololu/dual-vnh5019-motor-shield<br/>
	
Tutorial per Rosserail + navigation<br/>
https://www.youtube.com/watch?v=q1u_cC-5Sac<br/>
https://www.youtube.com/watch?v=HLLmV9LQoac<br/>

Ros navigation<br/>
https://emanual.robotis.com/docs/en/platform/turtlebot3/learn/#books<br/>
http://wiki.ros.org/ROS/Installation<br/>
http://wiki.ros.org/catkin/Tutorials/create_a_workspace<br/>
http://wiki.ros.org/navigation/Tutorials/RobotSetup<br/>

		
Mlx90614 come usarle e cambiare indirizzo<br/>
https://www.instructables.com/Multiple-IR-Temperature-Sensors/<br/>
	
Il software per disegnare pcb che consiglio<br/>
https://easyeda.com/editor<br/>
		
Dove ordinare le pcb online<br/>
https://jlcpcb.com/<br/>
		
Dove ho ordinato i pezzi tagliati al laser in alluminio<br/>
https://www.laserboost.com/en/create<br/>
	
Arduino ide (non la 2.0 che non funziona con teensyduino)<br/>
https://www.arduino.cc/en/software<br/>
			
Teensyduino<br/>
https://www.pjrc.com/teensy/teensyduino.html<br/>
		
Software Modellazione 3d (Fusion360 e gratis per gli studenti)<br/>	
https://www.autodesk.com/products/fusion-360/free-trial<br/>

	
	
NOTA:<br/>
Usare in maniera informativa nessuno di questi progetti e perfetto ma possono essere usati come una buona base per capire il funzionamento dei vari componenti<br/>
Siamo felici di aiutarvi per qualunque dubbio o perplessita<br/>
Se pensate di copiare pari pari il robot....non fatelo se avete bisogno di copiare tutto pari pari non avete le competenze per farlo andare<br/>

Luca Morselli:<br/>
+39 3318670782 <br/>
lucamorselli03@gmail.com<br/>
