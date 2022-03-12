# Robotica

Tutta la roba ddi robotica del Gruppo DKV Lab

Potete prendere tutto ci che volete e copiare a vostro piacemento

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


Source:


Sensori di distanza arduino:

https://www.youtube.com/watch?v=6F1B_N6LuKw
https://dronebotworkshop.com/hc-sr04-ultrasonic-distance-sensor-arduino/

		
Libreria Pololu vnh5019, la base della libreria custom che troverete in/arduino-1.8.19/libraries/DriverDkv

https://github.com/pololu/dual-vnh5019-motor-shield
	
	
Tutorial per Rosserail da parte della teensy

https://www.youtube.com/watch?v=q1u_cC-5Sac
https://www.youtube.com/watch?v=HLLmV9LQoac

	
Ros navigation

https://emanual.robotis.com/docs/en/platform/turtlebot3/learn/#books
http://wiki.ros.org/ROS/Installation
http://wiki.ros.org/catkin/Tutorials/create_a_workspace
http://wiki.ros.org/navigation/Tutorials/RobotSetup

		
Mlx90614 come usarle e cambiare indirizzo

https://www.instructables.com/Multiple-IR-Temperature-Sensors/

		
Il software per disegnare pcb che consiglio

https://easyeda.com/editor

		
Dove ordinare le pcb online

https://jlcpcb.com/
		
		
Dove ho ordinato i pezzi tagliati al laser in alluminio

https://www.laserboost.com/en/create
	
	
Arduino ide (non la 2.0 che non funziona con teensyduino)

https://www.arduino.cc/en/software
		
		
Teensyduino

https://www.pjrc.com/teensy/teensyduino.html
		
		
Software Modellazione 3d (Fusion360 e gratis per gli studenti)	

https://www.autodesk.com/products/fusion-360/free-trial

	
	
NOTA:
Usare in maniera informativa nessuno di questi progetti e perfetto ma possono essere usati come una buona base per capire il funzionamento dei vari componenti
					
Siamo felici di aiutarvi per qualunque dubbio o perplessita

Luca Morselli:

+39 3318670782 

lucamorselli03@gmail.com
