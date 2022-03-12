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
		Le Pcb logic e Power usate per il robot
		
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
		file pdf delle schematiche delle 2 pcb del robot
	
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

Non usate amg8833 come in Manta costano tanto e non e possibile cambiare l'indirizzo i2c nella libreria per leggerli in maniera semplice noi abbiamo usato 2 arduini in piu per questo motvo (i nano), la soluzione migliore e acquistare gli mlx90 

NOTA:
Usare in maniera informativa nessuno di questi progetti e perfetto ma possono essere usati come una buona base per capire il funzionamento dei vari componenti
					
Siamo felici di aiutarvi per qualunque dubbio o perplessita

Luca Morselli:
+39 3318670782 
lucamorselli03@gmail.com
